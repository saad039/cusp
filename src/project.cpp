#include "project.h"

Project::Project(const std::string &name, const std::string &cppver,
                 const std::string &type, const std::vector<std::string> &linklibs)
    : project_name(name), cppDialect(cppver), kind(type), libs(linklibs)
{
    this->tree["projectname"] = this->project_name;
    this->tree["cppdialect"] = this->cppDialect;
    this->tree["kind"] = this->kind;
    this->tree["links"] = this->libs;
}

const std::string &Project::Name() const
{
    return project_name;
}
const std::string &Project::CppDialect() const
{
    return cppDialect;
}
const std::string &Project::Kind() const
{
    return kind;
}
const std::vector<std::string> &Project::Libs() const
{
    return libs;
}
const nlohmann::json &Project::getTree() const
{
    return tree;
}
