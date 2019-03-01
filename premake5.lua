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
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		"ws2_32.lib",
		"winmm.lib"
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
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines { "B_DEBUG" }
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "B_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "B_DIST"
		runtime "Release"
		optimize "On"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"B_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines { "B_DEBUG" }
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "B_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "B_DIST"
		runtime "Release"
		optimize "On"