#include"cuspProject.h"


CuspProject::CuspProject(const std::string& name,const std::string& cppver,
        const std::string&type,const std::vector<std::string>&linklibs)
        :project_name(name),cppDialect(cppver),kind(type),libs(linklibs)
    {
        this->root["projectname"]=this->project_name;
        this->root["cppdialect"]=this->cppDialect;
        this->root["kind"] =this->kind;
        this->root["links"]=this->libs;
    }

    const std::string& CuspProject::ProjectName()               const{
        return project_name;        
    }       
    const std::string& CuspProject::CppDialect()                const{
        return cppDialect;      
    }       
    const std::string& CuspProject::Kind()                      const{
        return kind;        
    }       
    const std::vector<std::string>& CuspProject::Libs()         const{
        return libs;
    }
    const nlohmann::json& CuspProject::getRoot()   const{
        return root;
    }
