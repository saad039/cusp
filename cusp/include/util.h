#ifndef _UTIL_H_
#define _UTIL_H_

namespace util {
    extern std::vector<std::string> tokenizer(const std::string& str,const char delimeter);
    extern std::string plainTimeStamp();
    extern std::map<std::string, std::string> timeStamp();

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