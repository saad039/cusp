#ifndef SOLUTION_H
#define SOLUTION_H
#include"input_handler.h"
#include"project.h"

using csref =const std::string&;
class Solution
{
    private:
        std::string                 solution_name;          //solution exclusive
        std::string                 author_name;            //solution exclusive 
        std::string                 architecture;           //solution exclusive
        std::string                 toolset;                //solution exclusive
        
        std::string                 project_name;
        std::string                 kind;
        std::vector<std::string>    libs;
        std::string                 cppDialect;             

        std::vector<Project>        projects;

        static const std::string configuationFile;

    public:
        Solution()=default;
        void init(csref sln,csref proj, csref arch, csref tlset, csref cppDial, csref type,
                    const std::vector<std::string>& links, csref author);
        void deserializeCuspDotJson();
        void addProject(csref newProjectName,csref newProjectKind,
                        const std::vector<std::string>& newProjectLibs, 
                        csref newProjectCppDialect);
        void addHeader(csref projectName, csref header) const; 
        void addSourceFile(csref projectName, csref File); 
        void addClass(csref projectName, csref className); 
        void generateProjectDirectories(csref path,csref ProjectName) const;
        void serializeCuspDotJson(csref path) const; 
        void generateNewProjectDirectories(csref pjName) const;
        bool checkCuspInitPreconditions()       const; 
        
};
    
    

    
    
    






#endif // SOLUTION_H
