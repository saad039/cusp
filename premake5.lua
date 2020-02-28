workspace "cusp"

    startproject "cusp"
    architecture "x86_64"

    configurations{
        "Debug",
        "Release"
    }


project "spdlog"
    
    location "build/spdlog"
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

project "json"
    
    location "build/json"
    kind "Sharedlib"
    language"C++"
    toolset "gcc"
    cppdialect "C++17"
    staticruntime "on"


    targetdir ("bin/%{prj.name}")
    objdir("bin-init/%{prj.name}")
     

    files{
        "dependencies/json/single_include/nlohmann"
    }
    
    includedirs{
        "dependencies/json/single_include/nlohmann",
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
    location "build/cusp"
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
        "dependencies/json/single_include/nlohmann",
        "cusp/include"
    }

    pchheader "cusppch.h"
    pchsource "cusp/src/cusppch.cpp"

    links{
        "spdlog",
        "json"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "on"