#include "input_handler.h"

std::string inputHandler::helpers::getSolutionName()
{
    return util::takeConsoleInput(
        [&]() {
            __SET_PATTERN_BW__;
            LOG_INFO("Solution Name: ");
        });
}

std::string inputHandler::helpers::getProjectName()
{
    return util::takeConsoleInput(
        [&]() {
            __SET_PATTERN_BW__;
            LOG_INFO("Project Name. Enter for same as solution: ");
        });
}

std::string inputHandler::helpers::getNewProjectName()
{
    return util::takeConsoleInput(
        [&]() {
            __SET_PATTERN_BW__;
            LOG_INFO("Project Name: ");
        });
}

std::string inputHandler::helpers::getAuthorName()
{
    return util::takeConsoleInput(
        [&]() {
            __SET_PATTERN_BW__;
            LOG_INFO("Author Name: ");
        });
}

std::string inputHandler::helpers::getTargetArchitecture()
{
    return util::takeConsoleInput(
        [&]() {
            __SET_PATTERN_BW__;
            LOG_INFO(R"(Target Architecture: 
    32bit/x86
    64bit/x86_64: )");
        });
}

std::string inputHandler::helpers::getLanguageDialect()
{
    return util::takeConsoleInput(
        [&]() {
            __SET_PATTERN_BW__;
            LOG_INFO("C++ standard: ");
        });
}

std::string inputHandler::helpers::getToolset()
{
    return util::takeConsoleInput(
        [&]() {
            __SET_PATTERN_BW__;
            LOG_INFO(R"(Toolset: 
    clang (LLVM compiler infrastructure)
    gcc (GNU Compiler Toolchain)
    msc (Microsoft C/C++ compiler):  )");
        });
}

std::string inputHandler::helpers::getKindOfProject()
{
    return util::takeConsoleInput(
        [&]() {
            __SET_PATTERN_BW__;
            LOG_INFO("Kind? consoleapp/(shared/static)lib: ");
        });
}

bool inputHandler::helpers::shouldaddMITLicense()
{
    auto response = util::takeConsoleInput(
        [&]() {
            __SET_PATTERN_BW__;
            LOG_INFO("Add MIT Licence (y/n): ");
        });
    return response[0] == 'Y' || response[0] == 'y';
}

std::string inputHandler::helpers::getLibsToLinksAgainst()
{
    return util::takeConsoleInput([&]() {
        __SET_PATTERN_BW__;
        LOG_INFO("Specify Libraries to link against: ");
    });
};

std::string inputHandler::helpers::getHeaderName()
{
    return util::takeConsoleInput([&]() {
        __SET_PATTERN_BW__;
        LOG_INFO("Header Name (*.h/*.hpp): ");
    });
}
std::string inputHandler::helpers::getSourceFileName()
{
    return util::takeConsoleInput([&]() {
        __SET_PATTERN_BW__;
        LOG_INFO("Src File Name (*.cpp/*.cc): ");
    });
}
std::string inputHandler::helpers::getClassName()
{
    return util::takeConsoleInput([&]() {
        __SET_PATTERN_BW__;
        LOG_INFO("Class Name (string): ");
    });
}

//returns the solution name after validation
std::string inputHandler::solutionName()
{
    std::string input;
    bool isValid = true;
    do
    {
        input = std::move(inputHandler::helpers::getSolutionName());
        isValid = util::assert_validity([](const std::string &input) {
            return input.length() && !std::filesystem::exists(input);
        },
                                        input);
        if (!isValid)
        {
            __SET_PATTERN_COL__;
            LOG_ERROR("Invalid Name or A Directoy With Same Name Already Exists\n");
        }
    } while (!isValid);
    return input;
}

//return the project name if entered. Returns solution's name if omitted
std::string inputHandler::projectName(const std::string &solName)
{
    std::string input = inputHandler::helpers::getProjectName();
    return input.length() ? input : solName;
}

std::string inputHandler::newProjectName()
{
    std::string input;
    bool isValid = true;
    do
    {
        input = std::move(inputHandler::helpers::getNewProjectName());
        isValid = util::assert_validity([](const std::string &input) {
            return input.length() && !std::filesystem::exists(input);
        },
                                        input);
        if (!isValid)
        {
            __SET_PATTERN_COL__;
            LOG_ERROR("Invalid Project Name\n");
        }
    } while (!isValid);
    return input;
}

std::string inputHandler::author() { return inputHandler::helpers::getAuthorName(); }

std::string inputHandler::architecture()
{
    std::string input;
    bool isValid = true;
    do
    {
        input = inputHandler::helpers::getTargetArchitecture();
        isValid = util::assert_validity([](const std::string &input) {
            return input == "x86" || input == "32bit" ||
                   input == "x86_64" || input == "64bit";
        },
                                        input);
        if (!isValid)
        {
            __SET_PATTERN_COL__;
            LOG_ERROR("Invalid Entry\n");
        }
    } while (!isValid);
    return input;
}

std::string inputHandler::cppDialect()
{
    std::string input;
    bool isValid = true;
    do
    {
        input = inputHandler::helpers::getLanguageDialect();
        isValid = util::assert_validity([](const std::string &input) {
            return input == "c++98" || input == "c++11" ||
                   input == "c++14" || input == "c++17";
        },
                                        input);
        if (!isValid)
        {
            __SET_PATTERN_COL__;
            LOG_ERROR("Invalid Entry\n");
        }
    } while (!isValid);
    return input;
}

std::string inputHandler::kind()
{
    std::string input;
    bool isValid = true;
    do
    {
        input = inputHandler::helpers::getKindOfProject();
        isValid = util::assert_validity([](const std::string &input) {
            return input == "consoleapp" || input == "static" ||
                   input == "shared";
        },
                                        input);
        if (!isValid)
        {
            __SET_PATTERN_COL__;
            LOG_ERROR("Invalid Entry\n");
        }
    } while (!isValid);
    return input;
}

std::string inputHandler::toolset()
{
    std::string input;
    bool isValid = true;
    do
    {
        input = inputHandler::helpers::getToolset();
        isValid = util::assert_validity([](const std::string &input) {
            return input == "gcc" || input == "clang" ||
                   input == "msc";
        },
                                        input);
        if (!isValid)
        {
            __SET_PATTERN_COL__;
            LOG_ERROR("Invalid Entry\n");
        }
    } while (!isValid);
    return input;
}
std::vector<std::string> inputHandler::libsTolinks()
{
    std::vector<std::string> libs;
    std::string input;
    do
    {
        input = inputHandler::helpers::getLibsToLinksAgainst();
        if (input != "")
        {
            libs.push_back(input);
        }
    } while (input != "");
    return libs;
}

bool inputHandler::HeaderFileName(const std::string &project,const std::string& header)
{
     static const std::string headreg = "([a-zA-Z0-9\\_\\(\\):])+(.h|.hpp)$";
     if(std::regex_match(header,std::regex(headreg))){
          if (!std::filesystem::exists(project + "/include/" + header)){
              return true;
          }
          else{
              __SET_PATTERN_COL__;
              LOG_ERROR("File already exists");
              return false;
          }      
     }
     else{
         __SET_PATTERN_COL__;
         LOG_ERROR("Invalid File Name");
         return false;
     }
}

bool inputHandler::SourceFileName(const std::string &project,const std::string& srcFile)
{
   static const std::string srcreg = "([a-zA-Z0-9\\_\\(\\):])+(.cpp|.cc)$";
   if(std::regex_match(srcFile,std::regex(srcreg))){
        if (!std::filesystem::exists(project + "/src/" + srcFile)){
              return true;
        }
        else{
            __SET_PATTERN_COL__;
            LOG_ERROR("File already exists\n");
            return false;
        }         
   }
   else{
       __SET_PATTERN_COL__;
       LOG_ERROR("Invalid File Name\n");
       return false;
   }
}

bool inputHandler::ClassName(const std::string &project, const std::string& className)
{
    
    auto cHeader =  className + ".h";
    auto cSrc    =  className + ".cpp";
    if(inputHandler::HeaderFileName(project,cHeader) && inputHandler::SourceFileName(project,cSrc))
        return true;
    else
        return false;
}

std::string inputHandler::MITLicense(const std::string &year, const std::string &author)
{
    if (!inputHandler::helpers::shouldaddMITLicense())
        return std::string();
    else
    {
        std::stringstream stream;
        stream << "MIT License\n"
                  "Copyright (c) "
               << year << " " << author << "\n"

                                           "Permission is hereby granted, free of charge, to any person obtaining a copy\n"
                                           "of this software and associated documentation files (the \"Software\"), to deal\n"
                                           "in the Software without restriction, including without limitation the rights\n"
                                           "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
                                           "copies of the Software, and to permit persons to whom the Software is\n"
                                           "furnished to do so, subject to the following conditions:\n"
                                           "The above copyright notice and this permission notice shall be included in all\n"
                                           "copies or substantial portions of the Software.\n"
                                           "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
                                           "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
                                           "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
                                           "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
                                           "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
                                           "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
                                           "SOFTWARE."
               << std::endl;
        return stream.str();
    }
}