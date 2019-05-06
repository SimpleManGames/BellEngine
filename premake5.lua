workspace "Bell"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{(cfg.system)}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Bell/vendor/GLFW/include"
IncludeDir["Glad"] = "Bell/vendor/Glad/include"
IncludeDir["ImGui"] = "Bell/vendor/imgui"
IncludeDir["glm"] = "Bell/vendor/glm"
IncludeDir["enet"] = "Bell/vendor/enet/include"

include "Bell/vendor/GLFW"
include "Bell/vendor/Glad"
include "Bell/vendor/imgui"

project "Bell"
    location "Bell"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "bpch.h"
    pchsource "Bell/src/bpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.enet}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib",
        --"ws2_32.lib",
        --"winmm.lib"
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "B_PLATFORM_WINDOWS",
            "B_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "B_DEBUG"
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        defines "B_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "B_DIST"
        runtime "Release"
        optimize "on"
        
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Bell/vendor/spdlog/include/",
        "Bell/src/",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Bell"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "B_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "B_DEBUG"
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        defines "B_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "B_DIST"
        runtime "Release"
        optimize "on"
