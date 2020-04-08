#include "cusppch.h"
#include"cusp.h"
const std::string Solution::configuationFile =cusp::confFile;
std::shared_ptr<spdlog::logger> cuspLogger{spdlog::stdout_color_mt("cuspLogger")};
template<typename T>
void print(const T& something){
    __SET_PATTERN_COL__;
    LOG_ERROR(something);
}


//only one entry point is supported
int main(int argc, char const *argv[]){

     if (cusp::premake_precondition()) {
         std::vector<std::string> commands(argv, argv + argc);
         const auto& arg = commands.size() > 1 ? commands[1] : "";
         if (arg == "init") {
             cusp::cusp_init_wizard();
         }
         else if (arg == "add") {
             cusp::cusp_add_wizard(commands);
         }
         else if (arg == "vs2015" || arg == "vs2017" || arg == "vs2019") { //for visual studio 
             cusp::cusp_generate_sln_files(arg);
         }
         else if (arg == "xcode") { //for xcode
             cusp::cusp_generate_sln_files(arg);
         }
         else if (arg == "make") { //for makefiles
             cusp::cusp_generate_sln_files(arg);
         }
         else if (arg == "build") { //for generating project builds using make
             cusp::cusp_build_project(commands);
         }
         else if (arg == "update") {
             cusp::cusp_update();
         }
         else if (arg == "vscode") {
             cusp::generateVSCodeConfigurations();
         }
         else{
             __SET_PATTERN_COL__;
             LOG_ERROR("cusp -h for more information\n");
         }
     }
     else {
         __SET_PATTERN_COL__;
         LOG_ERROR("Fatal error.Premake does not exist in path\n");
     }
  
    return 0;
}
