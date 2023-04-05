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
includeDir["glad"] = "Petal/external/glad/include"

include "Petal/external/glad"

project "Petal"
	location "%{prj.name}"
	kind "SharedLib"
	language "C++"

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
		"%{prj.name}/external/spdlog/include",
		"%{prj.name}/external/GLFW/include",
		"%{includeDir.glad}"
	}

	libdirs
	{
		"%{prj.name}/external/GLFW/lib-vc2022"
	}

	links
	{
		"opengl32.lib",
		"glfw3.lib",
		"glad"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "Off"
		systemversion "latest"

		defines
		{
			"PTL_PLATFORM_WINDOWS",
			"PTL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Sandbox")
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		buildoptions "/MDd"
		defines
		{
			"PTL_DEBUG",
			"PTL_ENABLE_ASSERTS"
		}

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		buildoptions "/MD"
		defines "PTL_RELEASE"

project "Sandbox"
	location "%{prj.name}"
	kind "ConsoleApp"
	language "C++"

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
		"Petal/external/spdlog/include"
	}

	links
	{
		"Petal"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PTL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		symbols "On"
		buildoptions "/MDd"
		defines
		{
			"PTL_DEBUG",
			"PTL_ENABLE_ASSERTS"
		}

	filter "configurations:Release"
		optimize "On"
		buildoptions "/MD"
		defines "PTL_RELEASE"