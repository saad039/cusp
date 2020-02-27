#include"cusppch.h"
#include"cusp.h"
#include "spdlog/sinks/stdout_color_sinks.h"


std::shared_ptr<spdlog::logger> cuspLogger{spdlog::stdout_color_mt("cuspLogger")};

#define log(x) std::cout<<x<<std::endl
int main(){
  
    __SET_PATTERN_COL__;
    if(cusp::premake_precondition()){
        LOG_INFO("File Exists\n");
    }
    else{
        LOG_WARNING("File does not exist\n");
    }
    
    log(cusp::getTargetArchitecture());
    return 0;
}


/*
  auto console = spdlog::stdout_color_mt("console");
    console->set_pattern(ALL_COLOR_TEXT);

    console->info("Welcome to spdlog!");
    console->warn("please be careful");
    console->error("Some error message with arg{}..", 1);
    console->info("Welcome to spdlog!");
    
    console->set_pattern(ALL_WHITE_TEXT);

    console->error("Some error message with arg{}..", 1);
    console->info("Welcome to spdlog!");
    console->error("Some error messages with arg{}..", 1);
    // Set the default logger to file logger
    // auto file_logger = spdlog::basic_logger_mt("basic_logger", "logs/basic.txt");
    // spdlog::set_default_logger(file_logger);

*/