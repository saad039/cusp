workspace "cusp"

    startproject "cusp"

    configurations{
        "Debug",
        "Release"
    }


project "spdlog"
    
    location "spdlog"
    kind "Staticlib"
    language"C++"
    toolset("clang")
    cppdialect "C++17"
    staticruntime "on"
    toolset("clang")


    targetdir ("../bin/%{prj.name}/")
    objdir("../bin-init/%{prj.name}/")
     

    defines{
        "SPDLOG_COMPILED_LIB"
    }

    files{
        "../dependencies/spdlog/include/**.h",
        "../dependencies/spdlog/src/**.cpp"
    }
    
    includedirs{
        "../dependencies/spdlog/include"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "on"
      
  
   filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"     
        optimize "On"

    
    
project "cusp"
    location "cusp"
    kind "ConsoleApp"
    language "C++"
	cppdialect "C++17"
    staticruntime "on"
    toolset("clang")

    targetdir ("../bin/%{prj.name}/")
    objdir("../bin-init/%{prj.name}/")

    files{
		"../src/**.h",
		"../src/**.cpp"
    }

    pchheader "../src/cusppch.h"
    pchsource "../src/cusppch.cpp"

    includedirs{
        "../dependencies/spdlog/include"
    }
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