#include"cusppch.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#define ALL_COLOR_TEXT "%^%v%$"
#define ALL_WHITE_TEXT "%^%v"

int main()
{
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
    std::cout<<std::endl;
    std::cout<<"Insha'Allah everything is fixed"<<std::endl;
    std::cout<<"Good Night"<<std::endl;
    return 0;
}