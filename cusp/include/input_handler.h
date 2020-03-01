#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include "cusppch.h"

extern std::shared_ptr<spdlog::logger> cuspLogger;

#define ALL_COLOR_TEXT "%^%v%$"
#define ALL_WHITE_TEXT "%^%v"
#define LOG_INFO(...)           cuspLogger->info(__VA_ARGS__)
#define LOG_WARNING(...)        cuspLogger->warn(__VA_ARGS__)
#define LOG_ERROR(...)          cuspLogger->error(__VA_ARGS__)
#define __SET_PATTERN_BW__      cuspLogger->set_pattern(ALL_WHITE_TEXT)
#define __SET_PATTERN_COL__     cuspLogger->set_pattern(ALL_COLOR_TEXT)
#define EXIT_EXECUTION          std::exit(1)

namespace inputHandler{

    namespace helpers{
        extern std::string      getSolutionName();
        extern std::string      getProjectName();
        extern std::string      getNewProjectName();
        extern std::string      getAuthorName();
        extern std::string      getTargetArchitecture();
        extern std::string      getLanguageDialect();
        extern std::string      getToolset();
        extern std::string      getKindOfProject();
        extern bool             shouldaddMITLicense();
        extern std::string      getLibsToLinksAgainst();
        extern std::string      getHeaderName();
        extern std::string      getSourceFileName();
        extern std::string      getClassName();

    }
    extern std::string              solutionName();
    extern std::string              projectName(const std::string &solName);
    extern std::string              newProjectName();
    extern std::string              author();
    extern std::string              architecture();
    extern std::string              cppDialect();
    extern std::string              kind();
    extern std::string              toolset();
    extern std::vector<std::string> libsTolinks();
    extern bool                     HeaderFileName(const std::string &project,const std::string& header);
    extern bool                     SourceFileName(const std::string &project,const std::string& src);
    extern bool                     ClassName(const std::string &project,const std::string& cName);
    extern std::string              MITLicense(const std::string &year, const std::string &author);

}

#endif //INPUT_HANDLER_H