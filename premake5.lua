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
    
    files 
    { 
      "src/**.h",
      "src/**.cpp" 
    } 
    
    includedirs
    {
        "src",
        "vendor/GLFW/include",
        "vendor/Glad/include",
        "vendor/imgui",
        "vendor/spdlog/include",
        "vendor/PFD"
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
        
        includedirs
        {            
            "/usr/local/include/opencv4"
        }
        linkoptions { "-ldl -lpthread" }
        libdirs 
        {
            "/usr/local/lib"
        }
        links
        {
            "GLFW",
            "Glad",
            "ImGui",
            "GL",
            "X11",
            "opencv_core", 
            "opencv_imgproc", 
            "opencv_highgui",
            "opencv_imgcodecs"

        }
    
    filter "system:windows"
        systemversion "latest"
        includedirs
        {            
            "c:/Tools/opencv/build/include"
        }
        libdirs 
        {
            "C:/Tools/opencv/build/x64/vc15/lib/Release"
        }
        links
        {
            "GLFW",
            "Glad",
            "ImGui",
            "opengl32.lib",
            "opencv_calib3d470.lib",
            "opencv_core470.lib",
            "opencv_features2d470.lib",
            "opencv_flann470.lib",
            "opencv_highgui470.lib",
            "opencv_imgproc470.lib",
            "opencv_ml470.lib",
            "opencv_objdetect470.lib",
            "opencv_photo470.lib",
            "opencv_stitching470.lib",
            "opencv_ts470.lib",
            "opencv_video470.lib",
            "opencv_imgcodecs470.lib"
        }


    filter "configurations:Debug"
        defines "APP_DEBUG"
        runtime "Debug"
        symbols "on"    

    filter "configurations:Release"
        defines "APP_RELEASE"
        runtime "Release"
        optimize "on"

    