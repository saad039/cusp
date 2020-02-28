#ifndef _CUSP_H_
#define _CUSP_H_
#if defined _WIN32 || _WIN64
constexpr auto premakePath = "C://premake//premake5.exe";
#elif defined __APPLE__ || __MACH__
constexpr auto premakePath = R("/bin/premake5");
#elif defined unix || __unix || __unix__
constexpr auto premakePath = "/bin/premake5";
#endif

#if     __cplusplus     ==   199711L
#define __cpp98__       
#elif   __cplusplus     ==   201103L
#define __cpp11__       
#elif   __cplusplus     ==   201402L
#define __cpp14__       
#elif   __cplusplus     ==   201703L
#define __cpp17__
#endif

#include "cusppch.h"

#define ALL_COLOR_TEXT "%^%v%$"
#define ALL_WHITE_TEXT "%^%v"

extern std::shared_ptr<spdlog::logger> cuspLogger;

#define LOG_INFO(...)           cuspLogger->info(__VA_ARGS__)
#define LOG_WARNING(...)        cuspLogger->warn(__VA_ARGS__)
#define LOG_ERROR(...)          cuspLogger->error(__VA_ARGS__)
#define __SET_PATTERN_BW__      cuspLogger->set_pattern(ALL_WHITE_TEXT)
#define __SET_PATTERN_COL__     cuspLogger->set_pattern(ALL_COLOR_TEXT)

namespace cusp
{
    static bool premake_precondition()
    {
        return std::filesystem::exists(premakePath);
    }

    static std::string getSolutionName()
    {
        return util::takeConsoleInput(
            [&]() {
                __SET_PATTERN_BW__;
                LOG_INFO("Solution Name: ");
            });
    }

    static std::string getProjectName()
    {
        return util::takeConsoleInput(
            [&]() {
                __SET_PATTERN_BW__;
                LOG_INFO("Project Name. Enter for same as solution: ");
            });
    }

    static std::string getAuthorName()
    {
        return util::takeConsoleInput(
            [&]() {
                __SET_PATTERN_BW__;
                LOG_INFO("Author Name: ");
            });
    }

    static std::string getTargetArchitecture()
    {
        return util::takeConsoleInput(
            [&]() {
                __SET_PATTERN_BW__;
                LOG_INFO(R"(Target Architecture: 
    32bit/x86
    64bit/x86_64: )");
            });
    }

    static std::string getLanguageDialect(){
        return util::takeConsoleInput(
            [&]() {
                __SET_PATTERN_BW__;
                LOG_INFO("C++ standard: ");
            });
    }

    static std::string getToolset(){
        return util::takeConsoleInput(
            [&]() {
                __SET_PATTERN_BW__;
                LOG_INFO(R"(Toolset: 
llvm
gcc: )");
            });
    }

    static std::string getKindOfProject(){
        return util::takeConsoleInput(
            [&]() {
                __SET_PATTERN_BW__;
                LOG_INFO("Kind? consoleapp/sharedlib/staticlib: ");
            });
    }

    static bool shouldaddMITLicense(){
        auto response= util::takeConsoleInput(
            [&]() {
                __SET_PATTERN_BW__;
                LOG_INFO("Add MIT Licence (y/n): ");
            });
            return response[0]=='Y' || response[0]=='y';
    }

    static std::string getLibsToLinksAgainst(){
        return util::takeConsoleInput([&](){
            __SET_PATTERN_BW__;
            LOG_INFO("Specify Libraries to link against. -1 when done: ");
        });
    };

} // namespace cusp

#endif // _CUSP_H_



// cusp-init
// cusp run
// 