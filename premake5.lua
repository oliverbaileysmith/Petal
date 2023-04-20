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
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

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
		"glfw3.lib",
		"glad",
		"ImGui"
	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"

		defines
		{
			"PTL_PLATFORM_WINDOWS",
			"PTL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputDir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		defines
		{
			"PTL_DEBUG",
			"PTL_ENABLE_ASSERTS"
		}

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		defines "PTL_RELEASE"

project "Sandbox"
	location "%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

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
		cppdialect "C++20"
		systemversion "latest"

		defines
		{
			"PTL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		defines
		{
			"PTL_DEBUG",
			"PTL_ENABLE_ASSERTS"
		}

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		defines "PTL_RELEASE"