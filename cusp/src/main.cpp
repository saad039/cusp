#include"cusppch.h"
#include"cusp.h"

const std::string Solution::configuationFile =cusp::confFile;
std::shared_ptr<spdlog::logger> cuspLogger{spdlog::stdout_color_mt("cuspLogger")};
void print(std::string something){
    __SET_PATTERN_BW__;
    LOG_INFO(something);
}

//only one entry point is supported
int main(int argc, char const *argv[])
{
    if(cusp::premake_precondition()){
        std::vector<std::string> commands(argv,argv+argc);
        const auto& arg=commands.size()>1 ? commands[1]: "";
        if(arg == "init"){
            cusp::cusp_init_wizard();
        }
        else if(arg == "add"){
            cusp::cusp_add_wizard(commands);
        }
        else{
            __SET_PATTERN_COL__;
            LOG_ERROR("cusp -h for more information\n");
        }
    }
    else{
        __SET_PATTERN_COL__;
        LOG_ERROR("Fatal error.Premake does not exist in path\n");
    }

    return 0;   
}
