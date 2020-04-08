#include "cusppch.h"
#include "util.h"
#include<array>
#include<cstdlib>
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
    timestamp["year"] = tokens[4].substr(0, tokens[4].length() - 1);
    return timestamp;
}

std::string util::replaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

std::map<std::wstring, std::wstring> util::getGitEnvironmentVars() {
     std::map<std::wstring, std::wstring> env;
#if defined _WIN32 || _WIN64
    auto free = [](wchar_t* p) { FreeEnvironmentStrings(p); };

    auto env_block = std::unique_ptr<wchar_t, decltype(free)>{
        GetEnvironmentStringsW(), free };

    for (const wchar_t* name = env_block.get(); *name != L'\0'; )
    {
        const wchar_t* equal = wcschr(name, L'=');
        std::wstring key(name, equal - name);

        const wchar_t* pValue = equal + 1;
        std::wstring value(pValue);

        env[key] = value;

        name = pValue + value.length() + 1;
    }    
#endif
    return env;
}

std::string util::whereIs(const std::string& bin){
    std::string result;
#if defined unix || __unix || __unix__
    std::array<char, 128> buffer;
    const std::string cmd = std::string("whereis ")+bin;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe){
#ifdef DEBUG
        throw std::runtime_error("popen failed");
#elif defined NDEBUG
        LOG_ERROR("Internal Error\n");
#endif
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        result += buffer.data();
    auto tokens = util::tokenizer(result, ':');
    result.clear();
    for (int i=1; i <tokens.size();i++)
        result += tokens[i];
#endif
    return env;
}


std::vector<std::variant<std::string,std::wstring>>  util::getEnvironmentVars() {
     std::vector<std::variant<std::string,std::wstring>>  env;
#if defined _WIN32 || _WIN64
    auto free = [](wchar_t* p) { FreeEnvironmentStrings(p); };

    auto env_block = std::unique_ptr<wchar_t, decltype(free)>{
        GetEnvironmentStringsW(), free };

    for (const wchar_t* name = env_block.get(); *name != L'\0'; )
    {
        const wchar_t* equal = wcschr(name, L'=');
        std::wstring key(name, equal - name);

        const wchar_t* pValue = equal + 1;
        std::wstring value(pValue);

        env[key] = value;

        name = pValue + value.length() + 1;
    }
#elif defined unix || __unix || __unix__
#include<cstdlib>
    std::array<char, 128> buffer;
    std::string result;
    const char* cmd = "echo $PATH";
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
#ifdef DEBUG
        throw std::runtime_error("popen failed");
#elif defined NDEBUG
        LOG_ERROR("Internal Error\n");
        EXIT_EXECUTION;
#endif
}
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    auto tokens = util::tokenizer(result,':');
    for(auto& var: tokens){
        env.push_back(std::move(var));
    }
#endif
    return env;
}



