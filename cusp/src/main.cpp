#include"cusppch.h"
#include"cusp_init.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include"input_handler.h"
using namespace std;


std::shared_ptr<spdlog::logger> cuspLogger{spdlog::stdout_color_mt("cuspLogger")};
void print(std::string something){
    __SET_PATTERN_BW__;
    LOG_INFO(something);
}

int main(){


    // if(cusp::premake_precondition()){
    //     LOG_INFO("premake Exists\n");
    // }
    // else{
    //     LOG_ERROR("premake does not exist\n");
    // }

    // std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    // std::stringstream stream;
    // stream<<std::ctime(&end_time);

    // auto strs= util::tokenizer(stream.str(),' ');
    // std::for_each(std::begin(strs),std::end(strs),[](const std::string& s){
    //     std::cout<<s<<std::endl;
    // });
    
    cusp::cusp_init();
    

    //std::cout<<inputHandler::MITLicense("2020","Hassan Bilal")<<std::endl;
   // cusp::getSolutionName();
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