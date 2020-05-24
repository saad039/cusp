#include "cusppch.h"
#include"cusp.h"


bool cusp::premake_precondition(){
    bool premakeExist = false;
    auto paths = util::getEnvironmentVars();
#ifdef UNIX_CUSP
    const std::string exe = "/premake5";
    const std::string from = "\n";
    const std::string to = "";
    using str_t = std::string;
#elif defined WIN_CUSP
    const std::wstring exe = L"/premake5.exe";
    const std::wstring from = L"\n";
    const std::wstring to = L"";
    using str_t = std::wstring;
#else 
#error This operating system is not supported
#endif
    for (const auto& p : paths)
        if (std::get_if<str_t>(&p))
            if (std::filesystem::exists(util::replaceAll(std::get<str_t>(p), from, to) + exe)){
                premakeExist = true;
                break;
            }
    return premakeExist;
}

bool cusp::addOperationPreconditions() { 
    return std::filesystem::exists(confFile);
}

bool cusp::IDEPreconditions() {
    return std::filesystem::exists(confFile) && std::filesystem::exists("premake5.lua");
}

bool cusp::buildPreconditions(const std::string& solution) {
#if defined _WIN32 || _WIN64
    return msBuildPreconditions() && std::filesystem::exists(solution+".sln");
#elif defined unix || __unix || __unix__
    return std::filesystem::exists("Makefile");
#endif
}

bool cusp::updatePreconditions() {
    return cusp::addOperationPreconditions();
}

void cusp::cusp_init_wizard(){
    Solution    workspace;
    const auto  solution_name       =      inputHandler::solutionName();
    const auto  project_name        =      inputHandler::projectName(solution_name);
    const auto  architecture        =      inputHandler::architecture();
    const auto  toolset             =      inputHandler::toolset();
    const auto  cppDialect          =      inputHandler::cppDialect();
    const auto  kind                =      inputHandler::kind();
    const auto  libs                =      inputHandler::libsTolinks();
    const auto  author_name         =      inputHandler::author();
    const auto  license             =      inputHandler::MITLicense(util::timeStamp()["year"],author_name);
    const auto  enableGit           =      inputHandler::initializeGitRepository();
    workspace.init(
        solution_name,project_name,architecture,toolset,cppDialect,kind,libs,author_name,enableGit
    );
    if(license.length()){
        std::ofstream out(solution_name+"/"+"LICENSE");
        out<<license<<std::endl;
        out.close();
    }
    __SET_PATTERN_COL__;
    LOG_INFO("Solution Initialised\n");
}

void cusp::cusp_add_project(Solution& workspace){
    const auto project_name         =       inputHandler::newProjectName();
    const auto kind                 =       inputHandler::kind();
    const auto libs                 =       inputHandler::libsTolinks();
    const auto cpp_dialect          =       inputHandler::cppDialect();
    workspace.addProject(project_name,kind,libs,cpp_dialect);
    __SET_PATTERN_COL__;
    LOG_INFO(project_name+" added\n");
}
 
void cusp::cusp_add_header_file(Solution& workspace, const std::string& project,const std::string& name){
    if(inputHandler::HeaderFileName(project,name))
        workspace.addHeader(project,name);
        __SET_PATTERN_COL__;
        LOG_INFO(name+" added\n");
}

void cusp::cusp_add_source_file(Solution& workspace, const std::string& project, const std::string& name){
    if(inputHandler::SourceFileName(project,name))
        workspace.addSourceFile(project,name);
    __SET_PATTERN_COL__;
    LOG_INFO(name+" added\n");
}
void cusp::cusp_add_class(Solution& workspace, const std::string& project, const std::string& name){
    if(inputHandler::ClassName(project,name))
        workspace.addClass(project,name);
    __SET_PATTERN_COL__;
    LOG_INFO(name+" added\n");
}

void cusp::cusp_add_wizard(const std::vector<std::string>& commands){
    if(cusp::addOperationPreconditions()){
        Solution workspace;
        const auto& targetProj = commands[2]; //contains project or project_name
        const auto& to_add     = commands.size() > 3 ? commands[3] : ""; //contains "" or header/src/class
        const auto& name   = commands.size() > 4 ? commands[4] : "";
        if (commands.size()==2){
            __SET_PATTERN_COL__;
            LOG_ERROR("no arguments provided\n");
        }
        else if(targetProj=="project" && commands.size()==3){
            workspace.deserializeCuspDotJson(); //initialises cusp's datastructures from Cusp.json file
            cusp::cusp_add_project(workspace);
        }
        else{
            workspace.deserializeCuspDotJson(); //initialises cusp's datastructures from Cusp.json file
            if(name.length()){
                if(to_add=="header"){
                cusp::cusp_add_header_file(workspace,targetProj,name);
                }
                else if(to_add=="src"){
                    cusp::cusp_add_source_file(workspace,targetProj,name);
                }
                else if(to_add=="class"){
                    cusp::cusp_add_class(workspace,targetProj,name);
                }
                else {
                    __SET_PATTERN_COL__;
                    LOG_ERROR("Invalid arguments provided\n");
                }
            }
            else{
                __SET_PATTERN_COL__;
                LOG_ERROR("Filename Not Provided\n");
            }
        }
        
    }
    else{
        __SET_PATTERN_COL__;
        LOG_ERROR("Project Configuration(Cusp.json) File Does Not Exist\n");
    }
}

void cusp::cusp_generate_sln_files(const std::string& ide) {
    if (IDEPreconditions()) {
        std::string cmd;
        if (ide.find("vs") != std::string::npos)
            cmd = "premake5 " + ide;
        else if (ide == "xcode")
            cmd = std::string("premake5 ") + std::string("xcode4");
        else if (ide == "make") 
            cmd = std::string("premake5 ") + std::string("gmake2");
        std::system(cmd.c_str());
    }
    else {
        __SET_PATTERN_COL__;
        LOG_ERROR("Project Configuration(Cusp.json)  or Premake5.lua Does Not Exist\n");
        EXIT_EXECUTION;
    }
}

void cusp::cusp_build_project(const std::vector<std::string>& conf) {
    Solution workspace;
    workspace.deserializeCuspDotJson();
    if (buildPreconditions(workspace.getSolutionName())) {
        if (conf.size()>2){
            if (conf[2] == "debug" || conf[2] == "release") {
#if defined _WIN32 || _WIN64
                std::string config = conf[2]=="debug" ? "Debug" : "Release";
                std::string cmd = "msbuild -property:Configuration=" + config;
#elif defined unix || __unix || __unix__
                std::string cmd = "make config=" + conf[2];
#endif
                std::system(cmd.c_str());
            }
        }
        else {
            __SET_PATTERN_COL__;
            LOG_ERROR("Invalid build configuration\n");
            EXIT_EXECUTION;
        }
    }
    else {
        __SET_PATTERN_COL__;
#if defined _WIN32 || _WIN64
        LOG_ERROR("MSbuild or sln file does not exist\n");
#elif defined unix || __unix || __unix__
        LOG_ERROR("Makefile Does Not Exist\n");
#endif
        EXIT_EXECUTION;
    }
}

void cusp::cusp_update() {
    
    if (updatePreconditions()) {
        Solution workspace;
        workspace.deserializeCuspDotJson();
        workspace.generatePremakeFiles();
    }
    else {
        __SET_PATTERN_COL__;
        LOG_ERROR("Project Configuration(Cusp.json)  File Does Not Exist\n");
        EXIT_EXECUTION;
    }
}
bool cusp::msBuildPreconditions(){
    return util::getGitEnvironmentVars()[L"Path"].find(L"MSBuild") != std::string::npos;
}

void cusp::cusp_help(const std::vector<std::string>& commands){
    std::map<std::string, std::string> all_commands = {
        {"init", "Creates a new solution in the current working directory."},

        {"add", "Takes projectName as first argument and adds the following, as specified, to project projectName under your solution directory:\nhead.h/head.hpp \nsrc.cc/src.cpp \nclass className \n\nFor example, to add class Bar under project Foo, type: cusp add Foo Bar."},

         {"update","Regenerates premake5.lua for all projects and solution. This should be used if changes were made to cusp.json manually. Note that any changes made to premake5.lua files manually by you will be lost."},

        {"make", "Generates makefiles for all projects and solution."},

        {"vs2015", "Generates visual studio 2015 solution files for all projects and solution"},

        {"vs2017", "Generates visual studio 2017 solution files for all projects and solution."},

        {"vs2019", "Generates visual studio 2019 solution files for all projects and solution."},

        {"xcode", "Generates xcode solution files for all projects and solution."},

        {"build", "Specify the build type for binaries from makefiles only.\ncusp build debug -- for debug binaries\ncusp build release -- for release binaries."},

        {"-h", "Displays all available commands. Type cusp -h [command name] for information on a specific command."}
    };

    if (commands.size() > 2){
        if (all_commands.find(commands[2]) != all_commands.end())
            std::cout<<all_commands[commands[2]]<<std::endl;
        else
            std::cout<<"Command does not exist. Enter cusp -h to get a list of all available commands.\n";
    }
    else{
        std::cout << "Format: cusp -h [command]" << std::endl;
        std::cout<<"All available commands are.\n";
        for (const auto& command: all_commands)
            std::cout<<command.first<<std::endl;
    }
}

void cusp::generateVSCodeConfigurations(){
  
    if (cusp::IDEPreconditions()) {
        Solution workspace;
        workspace.deserializeCuspDotJson();
        const std::string  dir = ".vscode";
        auto buildSys = workspace.getBuildSystem();
        if (!std::filesystem::exists(dir)) {
            if (!std::filesystem::create_directory(dir)) {
                __SET_PATTERN_COL__;
                LOG_ERROR("Failed to create configuration files for vscode");
                return;
            }
        }
        nlohmann::json tasksJson;
        tasksJson["version"] = "2.0.0";
#if defined _WIN32 || _WIN64
        if (msBuildPreconditions()) {    
            tasksJson["tasks"] = getTasksJson(buildSys);
        }   
        else {
            __SET_PATTERN_COL__;
            LOG_ERROR("MSBuild was not found in your path\n");
        }
#elif defined unix || __unix || __unix__
    tasksJson["tasks"] = getTasksJson(buildSys);
#endif
        std::ofstream out(dir + "/tasks.json");
        if (out.is_open()) {
            out << tasksJson << std::endl;
            __SET_PATTERN_COL__;
            LOG_INFO("Created tasks.json for vscode\n");
            LOG_INFO("Use makefiles for unix based operating systems and sln for Windows\n");
        }
        else {
            __SET_PATTERN_COL__;
            LOG_ERROR("Failed to create tasks.json for vscode\n");
        }
    }
    else {
        __SET_PATTERN_COL__;
        LOG_ERROR("Project Configuration(Cusp.json) Does Not Exist\n");
    }
}

std::vector<nlohmann::json> cusp::getTasksJson(const std::string& buildSys) {
    std::vector<nlohmann::json> tasks;
#if defined _WIN32 || _WIN64
        
    tasks.push_back(cusp::getTask("Debug", "-property:Configuration=Debug", buildSys));
    tasks.push_back(cusp::getTask("Release", "-property:Configuration=Release", buildSys));

#elif defined unix || __unix || __unix__
    tasks.push_back(cusp::getTask("Debug",   "", buildSys+" config=debug"));
    tasks.push_back(cusp::getTask("Release", "", buildSys+" config=release"));
#endif
        return tasks;

}
nlohmann::json cusp::getTask(const std::string& label,const std::string& command, const std::string& buildSys)
{
    nlohmann::json task;
    task["label"] = label + " Build";
    task["type"] = "shell";
    task["command"] = buildSys;
#if defined _WIN32 || _WIN64
    task["args"] = std::vector<std::string>{ "/property:GenerateFullPaths=true",
                                             "/t:build",
                                             "/consoleloggerparameters:NoSummary",
                                              command };
    task["group"] = "build";
    task["problemMatcher"] = "$msCompile";
#endif
    return task;
}

