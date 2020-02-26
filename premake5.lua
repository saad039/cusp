workspace "cusp"

    startproject "cusp"
    architecture "x86_64"

    configurations{
        "Debug",
        "Release"
    }


project "spdlog"
    
    location "dependencies/spdlog"
    kind "Staticlib"
    language"C++"
    toolset "gcc"
    cppdialect "C++17"
    staticruntime "on"


    targetdir ("bin/%{prj.name}")
    objdir("bin-init/%{prj.name}")
     

    defines{
        "SPDLOG_COMPILED_LIB"
    }

    files{
        "dependencies/spdlog/include/**.h",
        "dependencies/spdlog/src/**.cpp"
    }
    
    includedirs{
        "dependencies/spdlog/include"
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
    toolset "gcc"
    cppdialect "C++17"
    staticruntime "on"
    
    targetdir ("bin/%{prj.name}")
    objdir("bin-init/%{prj.name}")

    files{
		"cusp/src/**.cpp",
        "cusp/include/**.h"
    }


    includedirs{
        "dependencies/spdlog/include",
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