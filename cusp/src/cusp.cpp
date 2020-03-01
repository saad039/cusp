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
}

void cusp::cusp_add_project(Solution& workspace){
    const auto project_name         =       inputHandler::newProjectName();
    const auto kind                 =       inputHandler::kind();
    const auto libs                 =       inputHandler::libsTolinks();
    const auto cpp_dialect          =       inputHandler::cppDialect();
    workspace.addProject(project_name,kind,libs,cpp_dialect);
}
 
void cusp::cusp_add_header_file(Solution& workspace, const std::string& project){
    const auto header               =       inputHandler::HeaderFileName(project);
    workspace.addHeader(project,header);
}

void cusp::cusp_add_source_file(Solution& workspace, const std::string& project){
    const auto src                  =       inputHandler::SourceFileName(project);
    workspace.addSourceFile(project,src);
}
void cusp::cusp_add_class(Solution& workspace, const std::string& project){
    const auto Class                =       inputHandler::ClassName(project);
    workspace.addClass(project,Class);
}

void cusp_add_wizard(const std::vector<std::string>& commands){
    if(cusp::checkAddOperationPreconditions()){
        Solution workspace;
        workspace.update(); //initialises cusp's datastructures from Cusp.json file
        const auto& targetProj= commands[2];
        const auto& to_add =commands[3];
        if(targetProj=="proj" && commands.size()==2){
            cusp::cusp_add_project(workspace);
        }
        else if(to_add=="header"){
            cusp::cusp_add_header_file(workspace,targetProj);
        }
        else if(to_add=="src"){
            cusp::cusp_add_source_file(workspace,targetProj);
        }
        else if(to_add=="class"){
            cusp::cusp_add_class(workspace,targetProj);
        }
        else {
            __SET_PATTERN_COL__;
            LOG_ERROR("Invalid arguments provided\n");
            EXIT_EXECUTION;
        }
    }
    else{
        __SET_PATTERN_COL__;
        LOG_ERROR("Project Configuration File Does Not Exist\n");
        EXIT_EXECUTION;
    }
}