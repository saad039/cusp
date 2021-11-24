#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

namespace inputHandler
{

    namespace helpers
    {
        extern std::string getSolutionName();
        extern std::string getProjectName();
        extern std::string getNewProjectName();
        extern std::string getAuthorName();
        extern std::string getTargetArchitecture();
        extern std::string getLanguageDialect();
        extern std::string getToolset();
        extern std::string getKindOfProject();
        extern bool shouldaddMITLicense();
        extern std::string getLibsToLinksAgainst();
        extern std::string getHeaderName();
        extern std::string getSourceFileName();
        extern std::string getClassName();

    } // namespace helpers
    extern std::string solutionName();
    extern std::string projectName(const std::string &solName);
    extern std::string newProjectName();
    extern std::string author();
    extern std::string architecture();
    extern std::string cppDialect();
    extern std::string kind();
    extern std::string toolset();
    extern std::vector<std::string> libsTolinks();
    extern bool HeaderFileName(const std::string &project, const std::string &header);
    extern bool SourceFileName(const std::string &project, const std::string &src);
    extern bool ClassName(const std::string &project, const std::string &cName);
    extern std::string MITLicense(const std::string &year, const std::string &author);
    extern bool initializeGitRepository();
} // namespace inputHandler

#endif //INPUT_HANDLER_H