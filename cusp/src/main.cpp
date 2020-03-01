#include"cusp.h"

const std::string Solution::configuationFile =cusp::confFile;

std::shared_ptr<spdlog::logger> cuspLogger{spdlog::stdout_color_mt("cuspLogger")};
void print(std::string something){
    __SET_PATTERN_BW__;
    LOG_INFO(something);
}


int main(int argc, char const *argv[])
{
    if(cusp::premake_precondition()){
        std::vector<std::string> commands(argv,argv+argc);
            //Cusp init is illegal here.
        if(argv[1]=="init"){
            cusp::cusp_init_wizard();
        }
        else if(argv[1] == "add"){
            //add new project               cusp add proj 
            //add new header                cusp add proj header
            //add new source file           cusp add proj src
            //add new class                 cusp add proj class
        }
    }
    else{
        __SET_PATTERN_COL__;
        LOG_WARNING("Fatal error.Premake does not exist in path");
    }
    return 0;   
}


//Solution must be initialised after creating or before updating 