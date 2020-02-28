#ifndef CUSP_INIT_H
#define CUSP_INIT_H
#include"input_handler.h"
#include"cuspProject.h"
namespace cusp
{
    void cusp_init() {
        const auto solution_name    =       inputHandler::solutionName();
        const auto project_name     =       inputHandler::projectName(solution_name);
        const auto author_name      =       inputHandler::author();
        const auto architecture     =       inputHandler::architecture();        
        const auto cppDialect       =       inputHandler::cppDialect();
        const auto kind             =       inputHandler::kind();
        const auto libs             =       inputHandler::libsTolinks();
        const auto license          =       inputHandler::MITLicense(util::timeStamp()["year"],author_name);
        
        CuspProject proj(project_name,cppDialect,kind,libs);
        std::ofstream outfile("../../Cusp.json");
        std::stringstream json;
        if(outfile.is_open()){
            outfile<<proj.getRoot()<<std::endl;
            outfile.close();
        }
    }


} // namespace cusp


#endif // CUSP_INIT_H

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