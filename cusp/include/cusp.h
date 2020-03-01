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

#include"solution.h"


namespace cusp
{
    const std::string confFile= "Cusp.json";
    extern bool premake_precondition();
    extern bool checkAddOperationPreconditions();
    extern void cusp_init_wizard();
    extern void cusp_add_project(Solution& workspace);
    extern void cusp_add_header_file(Solution& workspace, const std::string& project);
    extern void cusp_add_source_file(Solution& workspace, const std::string& project);
    extern void cusp_add_class(Solution& workspace, const std::string& project);
    extern void cusp_add_wizard(const std::vector<std::string>& commands);

} // namespace cusp

#endif // _CUSP_H_



// cusp-init
// cusp run
// 