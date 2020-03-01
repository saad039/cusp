#include"solution.h"


void Solution::init(csref sln,csref proj, csref arch, csref tlset, csref cppDial, csref type,
                    const std::vector<std::string>& links, csref author){
    this->solution_name             =   sln;   
    this->project_name              =   proj;   
    this->architecture              =   arch;   
    this->toolset                   =   tlset;   
    this->cppDialect                =   cppDial;   
    this->kind                      =   type;   
    this->libs                      =   links;   
    this->author_name               =   author;   
    this->projects.emplace_back(project_name,cppDialect,kind,libs);
    try
    {
        std::filesystem::create_directory(solution_name);
    }
    catch(const std::exception& e)
    {
        __SET_PATTERN_COL__;
        LOG_WARNING("Failed To Create Solution Directory\n");
        EXIT_EXECUTION;
    }
    generateProjectDirectories(solution_name+'/',project_name);
    auto cuspjsonpath=solution_name+"/";
    generateCuspDotJson(cuspjsonpath);
}
    
    void Solution::update(){
        std::ifstream inFile(configuationFile);
        if(inFile.is_open()){
            nlohmann::json tree;
            inFile >> tree;
            this->solution_name   =     tree["workspace"];    
            this->architecture    =     tree["architecture"]; 
            this->author_name     =     tree["author"];       
            this->toolset         =     tree["toolset"];      
            this->cppDialect      =     tree["cppdialect"];   
            nlohmann::json projs  =     tree["projects"];
            std::for_each(std::begin(projs),std::end(projs),[&](nlohmann::json& p){
                this->projects.emplace_back(p["projectname"],p["cppdialect"]
                ,p["kind"],p["links"]);
            });
        }
        else{
            __SET_PATTERN_COL__;
            LOG_ERROR("Cusp.json Not Found");
            EXIT_EXECUTION;
        }
    }


    void Solution::addProject(csref newProjectName,
                                csref newProjectKind,
                                const std::vector<std::string>& newProjectLibs,
                                csref newProjectCppDialect){
        this->projects.emplace_back(newProjectName,newProjectCppDialect,
                                        newProjectKind,newProjectLibs);
        generateProjectDirectories("",newProjectName);
        generateCuspDotJson(""); 
    }


void Solution::generateCuspDotJson(csref path) const{
    nlohmann::json tree;
    tree["workspace"]       =        this->solution_name;
    tree["architecture"]    =        this->architecture;
    tree["author"]          =        this->author_name;
    tree["toolset"]         =        this->toolset;
    tree["cppdialect"]      =        this->cppDialect;

    std::for_each(std::begin(projects),std::end(projects),[&](const Project& proj){
        tree["project"][proj.ProjectName()] =proj.getRoot();         
    });

    std::unique_ptr<std::ofstream> out;
    if(path.length()){
        out=std::make_unique<std::ofstream>(path);
    }
    else{
        out=std::make_unique<std::ofstream>();
    }
    if(out->is_open()){
        (*out)<<tree<<std::endl;
        out->close();
    }
    else{
        __SET_PATTERN_COL__;
        LOG_WARNING("FAILED TO UPDATE CUSP LOG\n");
        throw std::runtime_error("");
    }
}

    bool Solution::checkCuspInitPreconditions() const{
        return !std::filesystem::exists(configuationFile);
    }

        //Precondition: configuration file should exist. If not, it should display error
    

    void Solution::generateProjectDirectories(csref path,csref ProjectName) const{
        try{
            std::filesystem::create_directory(path+'/'+ProjectName);
            std::filesystem::create_directory(path+'/'+ProjectName+'/'+"include"  );
            std::filesystem::create_directory(path+'/'+ProjectName+'/'+"src"      );
        }
        catch(const std::exception& e)
        {
            __SET_PATTERN_COL__;
            LOG_ERROR("Failed to Create Project Directories\n");
            EXIT_EXECUTION;
        }
    }
        
    void Solution::addHeader(csref projectName, csref header) const{
        std::string up_header;
        std::transform(std::begin(header),std::end(header),std::begin(up_header),std::towupper);
        auto loc=header.find(".");
        if(std::filesystem::exists(projectName)){
            loc == std::string::npos ? header.length() : loc;
            auto includeGuard= header.substr(0,loc)+"_H_";
            try{
                std::ofstream out("/projectName/include/"+header);
                out<<"#ifndef "<<includeGuard<<"\n"
                 <<"#define "<<includeGuard<<"\n"
                 <<"\n\n\n\n\n\n\n\n\n\n"
                 <<"#endif    ////"+includeGuard<<std::endl;
                 out.close();
            }
            catch(const std::exception& e)
            {
                __SET_PATTERN_COL__;
                LOG_WARNING("Failed To add Header File\n");
                EXIT_EXECUTION;
            }
        }
        else{
             __SET_PATTERN_COL__;
            LOG_WARNING("Project Not Found\n");
        }
        
    
    }

    void Solution::addSourceFile(csref projectName,csref File){
        if(std::filesystem::exists(projectName)){
            try
            {
                std::ofstream out("/projectName/src/"+File);
                 out.close();
            }
            catch(const std::exception& e)
            {
                __SET_PATTERN_COL__;
                LOG_WARNING("Failed To add Source File\n");
                EXIT_EXECUTION;
            }
        }
        else{
             __SET_PATTERN_COL__;
            LOG_WARNING("Project Not Found\n");
        }
        
    
    }

    void Solution::addClass(csref projectName, csref className){
        if(std::filesystem::exists(projectName)){
            this->addHeader(projectName,className+".h");
            this->addSourceFile(projectName,className+".cpp");
        }
        else{
            __SET_PATTERN_COL__;
            LOG_WARNING("Project Not Found\n");
        }
    }
