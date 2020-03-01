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
    llvm (Clang toolset)
    gcc (GNU Compiler Toolchain)
    msc (Microsoft C/C++ compiler))");
        });
}

std::string inputHandler::helpers::getKindOfProject()
{
    return util::takeConsoleInput(
        [&]() {
            __SET_PATTERN_BW__;
            LOG_INFO("Kind? consoleapp/sharedlib/ lib: ");
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
        LOG_INFO("Specify Libraries to link against. -1 when done: ");
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
            LOG_WARNING("Invalid Name or A Directoy With Same Name Already Exists\n");
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
            LOG_WARNING("Invalid Project Name\n");
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
            return input == "consoleapp" || input == " lib" ||
                   input == "sharedlib";
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
            return input == "gcc" || input == "llvm" ||
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
        if (input != "-1")
        {
            libs.push_back(input);
        }
    } while (input != "-1");
    return libs;
}

std::string inputHandler::HeaderFileName(const std::string &project)
{
    std::string input;
    bool isValid = true;
    do
    {
        input = inputHandler::helpers::getHeaderName();
        isValid = util::assert_validity([](const std::string &input) {
            return (input.find(".h") != std::string::npos ||
                    input.find(".hpp") != std::string::npos) &&
                   std::count(std::begin(input), std::end(input), '.') == 1;
        },
                                        input);
        if (!isValid)
        {
            __SET_PATTERN_COL__;
            LOG_ERROR("Invalid Header Name\n");
        }
    } while (!isValid);
    if (std::filesystem::exists(project + "/include/" + input))
    {
        __SET_PATTERN_COL__;
        LOG_ERROR("File Already Exists\n");
        EXIT_EXECUTION;
    }
    return input;
}

std::string inputHandler::SourceFileName(const std::string &project)
{
    std::string input;
    bool isValid = true;
    do
    {
        input = inputHandler::helpers::getSourceFileName();
        isValid = util::assert_validity([](const std::string &input) {
            return (input.find(".cpp") != std::string::npos ||
                    input.find(".cc") != std::string::npos) &&
                   std::count(std::begin(input), std::end(input), '.') == 1;
        },
                                        input);
        if (!isValid)
        {
            __SET_PATTERN_COL__;
            LOG_ERROR("Invalid Src File Name\n");
        }
    } while (!isValid);
    if (std::filesystem::exists(project + "/include/" + input))
    {
        __SET_PATTERN_COL__;
        LOG_ERROR("File Already Exists\n");
        EXIT_EXECUTION;
    }
    return input;
}

std::string inputHandler::ClassName(const std::string &project)
{
    std::string input;
    bool isValid = true;
    do
    {
        input = inputHandler::helpers::getClassName();
        isValid = util::assert_validity([](const std::string &input) {
            return std::count(std::begin(input), std::end(input), '.') == 0;
        },
                                        input);
        if (!isValid)
        {
            __SET_PATTERN_COL__;
            LOG_ERROR("Invalid Class Name\n");
        }
    } while (!isValid);
    auto head = input + ".h";
    auto src = input + ".cpp";
    if (std::filesystem::exists(project + "/include/" + head) ||
        std::filesystem::exists(project + "/src/" + src))
    {
        LOG_ERROR("Class File(s) Already Exist(s)\n");
        EXIT_EXECUTION;
    }
    return input;
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