workspace "Petal"
	architecture "x64"
	configurations
	{
		"Debug",
		"Release"
	}

	startproject "Sandbox"

	outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	includeDir = {}
	includeDir["spdlog"] = "Petal/external/spdlog/include"
	includeDir["GLFW"] = "Petal/external/GLFW/include"
	includeDir["glad"] = "Petal/external/glad/include"
	includeDir["ImGui"] = "Petal/external/imgui"
	includeDir["glm"] = "Petal/external/glm"

	include "Petal/external/glad"
	include "Petal/external/imgui"

project "Petal"
	location "%{prj.name}"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	pchheader "ptlpch.h"
	pchsource "%{prj.name}/src/ptlpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{includeDir.spdlog}",
		"%{includeDir.GLFW}",
		"%{includeDir.glad}",
		"%{includeDir.ImGui}",
		"%{includeDir.glm}"
	}

	libdirs
	{
		"%{prj.name}/external/GLFW/lib-vc2022"
	}

	links
	{
		"opengl32.lib",
		"glfw3_mt.lib",
		"glad",
		"ImGui"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PTL_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		defines
		{
			"PTL_DEBUG",
			"PTL_ENABLE_ASSERTS"
		}

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines "PTL_RELEASE"

project "Sandbox"
	location "%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Petal/src",
		"%{includeDir.spdlog}",
		"%{includeDir.ImGui}",
		"%{includeDir.glm}"
	}

	links
	{
		"Petal"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PTL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		defines
		{
			"PTL_DEBUG",
			"PTL_ENABLE_ASSERTS"
		}

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines "PTL_RELEASE"
