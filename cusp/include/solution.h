#ifndef SOLUTION_H
#define SOLUTION_H
#include"input_handler.h"
#include"project.h"

class Solution{
    private:
        std::string                 solution_name;          //solution exclusive
        std::string                 author_name;            //solution exclusive 
        std::string                 architecture;           //solution exclusive
        std::string                 toolset;                //solution exclusive
        std::string                 cppDialect;             //solution exclusive
        
        std::string                 project_name;
        std::string                 kind;
        std::vector<std::string>    libs;
        std::vector<Project>        projects;

        const std::string path  ="../../Cusp.json";
    public:
        Solution()=default;
        void cusp_init();
        void addProject();
        void addHeader(const std::string& projectName);
        void addSourceFile(const std::string& projectName);
        void addClass(const std::string& projectName);
        void generateCuspDotJson() const;

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