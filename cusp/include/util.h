#ifndef _UTIL_H_
#define _UTIL_H_

#define ALL_COLOR_TEXT "%^%v%$"
#define ALL_WHITE_TEXT "%^%v"
#define LOG_INFO(...)           cuspLogger->info(__VA_ARGS__)
#define LOG_WARNING(...)        cuspLogger->warn(__VA_ARGS__)
#define LOG_ERROR(...)          cuspLogger->error(__VA_ARGS__)
#define __SET_PATTERN_BW__      cuspLogger->set_pattern(ALL_WHITE_TEXT)
#define __SET_PATTERN_COL__     cuspLogger->set_pattern(ALL_COLOR_TEXT)
#define EXIT_EXECUTION          std::exit(1)

extern std::shared_ptr<spdlog::logger> cuspLogger;

namespace util {
    extern std::vector<std::string> tokenizer(const std::string& str,const char delimeter);
    extern std::string plainTimeStamp();
    extern std::map<std::string, std::string> timeStamp();
    extern std::string replaceAll(std::string str, const std::string& from, const std::string& to);
    extern std::map<std::wstring, std::wstring> getEnvironmentVars();

    template<typename Callable>
    std::string takeConsoleInput(Callable logMessage){
        std::invoke(logMessage);
        std::string input;
        std::getline(std::cin,input);
        return input;
    }

    template<typename Callable, typename... Args>
    auto assert_validity(Callable&& condition, Args... args) -> decltype(condition(args...)){
        return std::invoke(condition,args...);
    }


} // namespace util


#endif //_UTIL_H_