workspace "Bell"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{(cfg.system)}-%{cfg.architecture}"

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
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"B_PLATFORM_WINDOWS",
			"B_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "B_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "B_RELEASE"
		optimize "On"

	filter "configurations:Debug"
		defines "B_DIST"
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
		defines "B_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "B_RELEASE"
		optimize "On"

	filter "configurations:Debug"
		defines "B_DIST"
		optimize "On"