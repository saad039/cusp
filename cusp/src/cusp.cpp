#include"cusp.h"


bool cusp::premake_precondition()
{
    return std::filesystem::exists(premakePath);
}

bool cusp::checkAddOperationPreconditions() { 
    return std::filesystem::exists(confFile);
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
    workspace.init(
        solution_name,project_name,architecture,toolset,cppDialect,kind,libs,author_name
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
    if(cusp::checkAddOperationPreconditions()){
        Solution workspace;
        const auto& targetProj = commands[2]; //contains project or project_name
        const auto& to_add     = commands.size() > 3 ? commands[3] : ""; //contains "" or header/src/class
        const auto& name   = commands.size() > 4 ? commands[4] : "";
        if (commands.size()==2){
            __SET_PATTERN_COL__;
            LOG_ERROR("no arguments provided\n");
        }
        else if(targetProj=="project" && commands.size()==3){
            workspace.update(); //initialises cusp's datastructures from Cusp.json file
            cusp::cusp_add_project(workspace);
        }
        else{
            workspace.update(); //initialises cusp's datastructures from Cusp.json file
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
        LOG_ERROR("Project Configuration File Does Not Exist\n");
        EXIT_EXECUTION;
    }
}