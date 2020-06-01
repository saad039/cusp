#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <vector>
#include "json.hpp"
class Project
{
private:
    const std::string project_name;
    const std::string cppDialect;
    std::string kind;
    std::vector<std::string> libs;
    nlohmann::json tree;

public:
    Project(const std::string &name, const std::string &cppver,
            const std::string &type, const std::vector<std::string> &linklibs);

    const std::string &Name() const;
    const std::string &CppDialect() const;
    const std::string &Kind() const;
    const std::vector<std::string> &Libs() const;
    const nlohmann::json &getTree() const;
};

#endif // PROJECT_H
