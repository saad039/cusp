#ifndef _UTIL_H_
#define _UTIL_H_

#include<string>
namespace util
{
    template<typename Callable>
    static std::string takeConsoleInput(Callable logMessage){
        logMessage();
        std::string input;
        std::getline(std::cin,input);
        return input;
    }
} // namespace util


#endif //_UTIL_H_