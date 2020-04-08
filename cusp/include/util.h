#ifndef _UTIL_H_
#define _UTIL_H_
#include<variant>

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
    extern std::string plainTimeStamp();
    extern std::map<std::string, std::string> timeStamp();
    extern std::map<std::wstring, std::wstring> getGitEnvironmentVars();
    extern std::vector<std::variant<std::string,std::wstring>> getEnvironmentVars();
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

    template<typename str_t, typename char_t>
    std::vector<str_t> tokenizer(const str_t& str, const char_t delimeter)
    {
        std::vector<str_t> tokens;
        str_t temp;
        temp.reserve(50);
        const auto  len = str.length();
        for (std::size_t i = 0, size = len; i < size; i++){
            if (str[i] != delimeter)
            {
                temp += str[i];
            }
            else
            {
                if (len)
                {
                    tokens.push_back(temp);
                    temp.clear();
                    temp.reserve(50);
                }
            }
        }
        if (len)
            tokens.push_back(temp);
        return tokens;
    }
    template<typename str_t>
    str_t replaceAll(str_t str, const str_t& from, const str_t& to) {
        size_t start_pos = 0;
        while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length();
        }
        return str;
    }
} // namespace util


#endif //_UTIL_H_