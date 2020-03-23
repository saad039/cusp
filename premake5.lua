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


    targetdir ("bin/%{prj.name}/%{cfg.buildcfg}")
    objdir("bin-init/%{prj.name}/%{cfg.buildcfg}")
     

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

project "ordered-map"
    
    location "build/ordered-map"
    kind "Staticlib"
   language"C++"
    toolset "gcc"
    cppdialect "C++17"
    staticruntime "on"
    
    
    targetdir ("bin/%{prj.name}/%{cfg.buildcfg}")
    objdir("bin-init/%{prj.name}/%{cfg.buildcfg}")
         
    files{
        "dependencies/ordered-map/include/**.h",
        "dependencies/ordered-map/src/**.cpp"
    }
        
    includedirs{
        "dependencies/ordered-map/include"
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
    kind "Staticlib"
    language"C++"
    toolset "gcc"
    cppdialect "C++17"
    staticruntime "on"


    targetdir ("bin/%{prj.name}/%{cfg.buildcfg}")
    objdir("bin-init/%{prj.name}/%{cfg.buildcfg}")
     

    files{
        "dependencies/json/single_include/nlohmann/**.hpp",
        "dependencies/json/single_include/nlohmann/**.cpp"
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
    
    targetdir ("bin/%{prj.name}/%{cfg.buildcfg}")
    objdir("bin-init/%{prj.name}/%{cfg.buildcfg}")

    files{
        
		"cusp/src/**.cpp",
        "cusp/include/**.h"
    }


    includedirs{
        "dependencies/spdlog/include",
        "dependencies/json/single_include/nlohmann",
        "dependencies/ordered-map/include",
        "cusp/include"
    }

    pchheader "cusppch.h"
    pchsource "cusp/src/cusppch.cpp"

    links{
        "spdlog",
        "json",
        "ordered-map"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "on"

  
    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "on"