workspace "Bell"
    architecture "x86_64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Debug_Server",
        "Release",
        "Release_Server",
        "Dist"
    }
    
    flags
    {
        "MultiProcessorCompile"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Bell/vendor/GLFW/include"
IncludeDir["Glad"] = "Bell/vendor/glad/include"
IncludeDir["ImGui"] = "Bell/vendor/imgui"

IncludeDir["glm"] = "Bell/vendor/glm"
IncludeDir["stb_image"] = "Bell/vendor/stb_image"
IncludeDir["enet"] = "Bell/vendor/enet/include"

group "Dependencies"
    include "Bell/vendor/glfw"
    include "Bell/vendor/glad"
    include "Bell/vendor/imgui"
    include "Bell/vendor/enet"

group ""

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
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
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
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.enet}"
    }

    links 
    { 
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib",
        "ws2_32.lib",
        "winmm.lib",
        "enet"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "B_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
            "UNICODE",
            "_UNICODE"
        }

    filter "configurations:Debug"
        defines { "B_DEBUG", "B_CLIENT" }
        runtime "Debug"
        symbols "on"

    filter "configurations:Debug_Server"
        defines { "B_DEBUG", "B_SERVER" }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines { "B_RELEASE", "B_CLIENT" }
        runtime "Release"
        optimize "on"

    filter "configurations:Release_Server"
        defines { "B_RELEASE", "B_SERVER" }
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
        "Bell/vendor/spdlog/include",
        "Bell/src",
        "Bell/vendor",
        "%{IncludeDir.glm}",
        "%{IncludeDir.enet}"
    }

    links
    {
        "Bell"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "UNICODE",
            "_UNICODE"
        }

    filter "configurations:Debug"
        defines { "B_DEBUG", "B_CLIENT" }
        runtime "Debug"
        symbols "on"

    filter "configurations:Debug_Server"
        defines { "B_DEBUG", "B_SERVER" }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines { "B_RELEASE", "B_CLIENT" }
        runtime "Release"
        optimize "on"

    filter "configurations:Release_Server"
        defines { "B_RELEASE", "B_SERVER" }
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "B_DIST"
        runtime "Release"
        optimize "on"