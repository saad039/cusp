#include"cusppch.h"
#include"project.h"


Project::Project(const std::string& name,const std::string& cppver,
        const std::string&type,const std::vector<std::string>&linklibs)
        :project_name(name),cppDialect(cppver),kind(type),libs(linklibs)
    {
        this->root["projectname"]=this->project_name;
        this->root["cppdialect"]=this->cppDialect;
        this->root["kind"] =this->kind;
        this->root["links"]=this->libs;
    }

    const std::string& Project::ProjectName()               const{
        return project_name;        
    }       
    const std::string& Project::CppDialect()                const{
        return cppDialect;      
    }       
    const std::string& Project::Kind()                      const{
        return kind;        
    }       
    const std::vector<std::string>& Project::Libs()         const{
        return libs;
    }
    const nlohmann::json& Project::getRoot()                const{
        return root;
    }
