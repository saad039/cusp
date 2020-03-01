#ifndef SOLUTION_H
#define SOLUTION_H
#include"input_handler.h"
#include"project.h"

using csref =const std::string&;
class Solution{
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
        void update();
        void addProject(csref newProjectName,csref newProjectKind,
                        const std::vector<std::string>& newProjectLibs, 
                        csref newProjectCppDialect);
        void addHeader(csref projectName, csref header) const; 
        void addSourceFile(csref projectName, csref File); 
        void addClass(csref projectName, csref className); 
        void generateProjectDirectories(csref path,csref ProjectName) const;
        void generateCuspDotJson(csref path) const; 
        void generateNewProjectDirectories(csref pjName) const;
        bool checkCuspInitPreconditions()       const; 
        
};
    
    

    
    
    






#endif // SOLUTION_H

/*
First, when cusp runs, it makes sure premake5 is installed in the pc. Do it using filefinding

When the user run cusp init, cusp will ask about
Name of solution:
Name of project:
Author:
Architecture x86 or x86_64
Language C++
toolset
cpp dialect
Kind: console,static or dynamic lib
Licence MIT
Links
Defines

This will create a project with file projname.cpp

cusp init > create a new solution
cusp create project > creates a new project under same solution 

cusp add project_name head/src/class > takes inoit and creates files in respective directories


Project flow:
Create a Cusp.json file and transpile it into Lua to generate premake.lua file.  
This automatically generate scripts building project. Bash in Linux and powershell in windows

*/