#include"solution.h"

void Solution::cusp_init(){
    this->solution_name             =      inputHandler::solutionName();
    this->project_name              =      inputHandler::projectName(solution_name);
    this->architecture              =      inputHandler::architecture();
    this->toolset                   =      inputHandler::toolset();
    this->cppDialect                =      inputHandler::cppDialect();
    this->kind                      =      inputHandler::kind();
    this->libs                      =      inputHandler::libsTolinks();
    this->author_name               =      inputHandler::author();
    const auto license              =      inputHandler::MITLicense(util::timeStamp()["year"],author_name);
    if (license.length()){
        //TODO create a licence file in the project root directory
    }
    this->projects.emplace_back(project_name,cppDialect,kind,libs);
    generateCuspDotJson();
}

void Solution::generateCuspDotJson() const{
    nlohmann::json tree;
    tree["workspace"]       =        this->solution_name;
    tree["architecture"]    =        this->architecture;
    tree["author"]          =        this->author_name;
    tree["toolset"]         =        this->toolset;
    tree["cppdialect"]      =        this->cppDialect;
    for(const auto& prj:projects){
        tree["project"][prj.ProjectName()] =prj.getRoot();         
    }
    std::ofstream out(cuspDotJsonpath);
    if(out.is_open()){
        out<<tree<<std::endl;
        out.close();
    }
    else{
        __SET_PATTERN_COL__;
        LOG_WARNING("FAILED TO UPDATE CUSP LOG\n");
        throw std::runtime_error("");
    }
}


        
    //     Project proj(project_name,cppDialect,kind,libs);
    //     std::ofstream outfile("../../Cusp.json");
    //     std::stringstream json;
    //     if(outfile.is_open()){
    //         outfile<<proj.getRoot()<<std::endl;
    //         outfile.close();
    //     }
    // }
