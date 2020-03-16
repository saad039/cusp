#include "cusppch.h"
#include "util.h"
std::vector<std::string> util::tokenizer(const std::string &str, const char delimeter)
{
    std::vector<std::string> tokens;
    std::string temp;
    temp.reserve(50);
    const std::size_t len = str.length();
    for (std::size_t i = 0, size = len; i < size; i++)
    {
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

std::string util::plainTimeStamp()
{
    std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::stringstream stream;
    stream << std::ctime(&end_time);
    return stream.str();
}

std::map<std::string, std::string> util::timeStamp()
{
    auto stamp = util::plainTimeStamp();
    auto tokens = util::tokenizer(stamp, ' ');
    std::map<std::string, std::string> timestamp;
    timestamp["month"] = tokens[1];
    timestamp["date"] = tokens[2];
    timestamp["time"] = tokens[3];
    timestamp["year"] = tokens[5].substr(0, tokens[5].length() - 1);
    return timestamp;
}