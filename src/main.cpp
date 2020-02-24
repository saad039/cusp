#include "cusppch.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#define COLOR_LOGGING_PATTERN "%^%v%$"
#define WHITE_LOGGING_PATTERN "%^%v"

int main()
{
    auto console = spdlog::stdout_color_mt("console");
    console->set_pattern(COLOR_LOGGING_PATTERN);

    console->info("Welcome to spdlog!");
    console->warn("please be careful");
    console->error("Some error message with arg{}..", 1);
    console->info("Welcome to spdlog!");
    
    console->set_pattern(WHITE_LOGGING_PATTERN);

    console->error("Some error message with arg{}..", 1);
    console->info("Welcome to spdlog!");
    console->error("Some error messages with arg{}..", 1);

    // Set the default logger to file logger
    // auto file_logger = spdlog::basic_logger_mt("basic_logger", "logs/basic.txt");
    // spdlog::set_default_logger(file_logger);

    return 0;
}