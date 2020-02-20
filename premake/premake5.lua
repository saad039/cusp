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

    targetdir ("../bin/%{prj.name}/")
    objdir("../bin-init/%{prj.name}/")
    flags { cppdialect "C++17" }

    files{
        "../dependencies/spdlog/include/**.h",
        "../dependencies/spdlog/src/**.cpp",        
    }

    defines{
        "SPDLOG_COMPILED_LIB"
    }

    includedirs{
        "../dependencies/spdlog/include"
    }

    toolset("clang")
    filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      
  
   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

    project "cusp"
    location "cusp"
    kind "ConsoleApp"
    language "C++"
	cppdialect "C++17"
    staticruntime "on"
    

    targetdir ("../bin/%{prj.name}/")
    objdir("../bin-init/%{prj.name}/")
    
    files{
		"../src/**.h",
		"../src/**.cpp"
    }
    
    includedirs{
        "../dependencies/spdlog/include"
    }

    links{
        "spdlog"
    }
  
    toolset("clang")
    filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      
  
   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"