#ifndef _CUSP_H_
#define _CUSP_H_
#if defined _WIN32 || _WIN64
constexpr auto premakePath = "C://premake//premake5.exe";
#elif defined __APPLE__ || __MACH__
constexpr auto premakePath = R("/bin/premake5");
#elif defined unix || __unix || __unix__
#define UNIX_CUSP
#endif

//#if     __cplusplus     ==   199711L
//#define __cpp98__       
//#elif   __cplusplus     ==   201103L
//#define __cpp11__       
//#elif   __cplusplus     ==   201402L
//#define __cpp14__       
//#elif   __cplusplus     ==   201703L
//#define __cpp17__
//#endif

#include"solution.h"


namespace cusp
{
    static const std::string confFile= "Cusp.json";
    extern bool premake_precondition();
    extern bool IDEPreconditions();
    extern bool buildPreconditions(const std::string& solution);
    extern bool addOperationPreconditions();
    extern bool updatePreconditions(); 
    extern bool msBuildPreconditions();
    extern void cusp_init_wizard();
    extern void cusp_add_project(Solution& workspace);
    extern void cusp_add_header_file(Solution& workspace, const std::string& project,const std::string& name);
    extern void cusp_add_source_file(Solution& workspace, const std::string& project,const std::string& name);
    extern void cusp_add_class(Solution& workspace, const std::string& project,const std::string& name);
    extern void cusp_add_wizard(const std::vector<std::string>& commands);
    
    extern void cusp_generate_sln_files(const std::string& ide); //generates visual studio 2015,17,19 and xcode4 solution files and make files
    extern void cusp_build_project(const std::vector<std::string>& conf);
    extern void cusp_update();

    extern void generateVSCodeConfigurations();
    extern std::vector<nlohmann::json> getTasksJson(const std::string& compiler);
    //@param args is for make or msbuild to generate  either debug or release build and compiler is either one of {msc,clang or gcc}
    extern nlohmann::json getTask(const std::string& label , const std::string& args, const std::string& compiler);
} // namespace cusp

#endif // _CUSP_H_

