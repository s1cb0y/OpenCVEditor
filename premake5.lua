workspace "OpenCVEditorWS"
    architecture "x86_64"
    startproject "OpenCVEditor"
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    flags
    {
       "MultiProcessorCompile"
   }
   

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"    

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["Glad"] = "vendor/Glad/include"
IncludeDir["ImGui"] = "vendor/imgui"

group "Dependencies"
    include "vendor/Glad"
    include "vendor/GLFW"
    include "vendor/imgui"

project "OpenCVEditor"
    location "build"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files { "src/**" }
    
    includedirs
    {
        "src",
        "vendor/GLFW/include",
        "vendor/Glad/include",
        "vendor/imgui"
    }
    
    defines 
    {
        "GLFW_INCLUDE_NONE"
    }

    filter "system:macosx"
        links
        {
            "OpenGL.framework",
            "IOKit.framework",
            "Cocoa.framework",
            "GLFW",
            "Glad",
            "ImGui"
        }

    filter "system:linux"
        linkoptions { "-ldl -lpthread" }
        links
        {
            "GLFW",
            "Glad",
            "ImGui",
            "GL",
            "X11"
        }
    
    filter "system:windows"
        links
        {
            "GLFW",
            "Glad",
            "ImGui",
            "opengl32.lib"
        }


   	filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "on"    

    filter "configurations:Release"
        defines "RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "DIST"
        runtime "Release"
        optimize "on"