#ifndef _UTIL_H_
#define _UTIL_H_

#include<string>
#include<map>
namespace util
{
    template<typename Callable>
    inline std::string takeConsoleInput(Callable logMessage){
        std::invoke(logMessage);
        std::string input;
        std::getline(std::cin,input);
        return input;
    }

    template<typename Callable, typename... Args>
    auto assert_validity(Callable&& condition, Args... args) -> decltype(condition(args...)){
        return std::invoke(condition,args...);
    }
    
    inline std::vector<std::string> tokenizer(const std::string& str,const char delimeter) {
        std::vector<std::string> tokens;
		std::string temp;
		temp.reserve(50);
        const std::size_t len=str.length();
		for (std::size_t i = 0, size = len; i < size; i++) {
			if (str[i] != delimeter) {
				temp += str[i];
			}
			else {
				if (len) {
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

    inline std::string plainTimeStamp(){
        std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::stringstream stream;
        stream<<std::ctime(&end_time);
        return stream.str();
    }

    inline std::map<std::string, std::string> timeStamp(){
        auto stamp=plainTimeStamp();
        static std::map<std::string,int> months= {
            {"Jan", 1  },
            {"Feb", 2  },
            {"Mar", 3  },
            {"Apr", 4  },
            {"May", 5  },
            {"Jun", 6  },
            {"Jul", 7  },
            {"Aug", 8  },
            {"Sep", 9  },
            {"Oct", 10 },
            {"Nov", 11 },
            {"Dec", 12 }
        };
        auto tokens= util::tokenizer(stamp,' ');
        std::map<std::string,std::string> timestamp;
        timestamp["month"]=std::to_string(months[tokens[1]]);
        timestamp["date"]=tokens[2];
        timestamp["time"]=tokens[3];
        timestamp["year"]=tokens[4];
        return timestamp;
    }
} // namespace util


#endif //_UTIL_H_