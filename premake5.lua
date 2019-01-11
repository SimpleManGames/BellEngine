workspace "Bell"
	architecture "x64"

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

include "Bell/vendor/GLFW"
include "Bell/vendor/Glad"

project "Bell"
	location "Bell"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "bpch.h"
	pchsource "Bell/src/bpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"B_PLATFORM_WINDOWS",
			"B_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines { "B_DEBUG", "B_ENABLE_ASSERT" }
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "B_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Debug"
		defines "B_DIST"
		buildoptions "/MD"
		optimize "On"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Bell/src/"
	}

	links
	{
		"Bell"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"B_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines { "B_DEBUG", "B_ENABLE_ASSERT" }
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "B_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Debug"
		defines "B_DIST"
		buildoptions "/MD"
		optimize "On"