workspace "cusp"

    startproject "cusp"
    architecture "x86_64"

    configurations{
        "Debug",
        "Release"
    }


group "Dependencies"
include "dependencies/spdlog"
group ""

project "cusp"
    location "build/cusp"
    kind "ConsoleApp"
    language "C++"
    toolset "msc"
    cppdialect "C++17"
    staticruntime "on"
    
    targetdir ("bin/%{prj.name}")
    objdir("bin-init/%{prj.name}")

    files{
        
		"cusp/src/**.cpp",
        "cusp/include/**.h",
        "dependencies/nlohmannJson"
    }


    includedirs{
        "dependencies/spdlog/include",
        "dependencies/nlohmannJson",
        "cusp/include"
    }

    pchheader "cusppch.h"
    pchsource "cusp/src/cusppch.cpp"

    links{
        "spdlog"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "on"