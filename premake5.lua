workspace "Petal"
	architecture "x64"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
		defines "PTL_DEBUG"

	filter "configurations:Release"
		optimize "On"
		defines "PTL_RELEASE"

	filter "configurations:Dist"
		optimize "On"
		defines "PTL_DIST"

project "Petal"
	location "%{prj.name}"
	kind "SharedLib"
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
		"%{prj.name}/external/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PTL_PLATFORM_WINDOWS",
			"PTL_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Sandbox")
		}

	filter "configurations:Debug"
		symbols "On"
		defines "PTL_DEBUG"

	filter "configurations:Release"
		optimize "On"
		defines "PTL_RELEASE"

	filter "configurations:Dist"
		optimize "On"
		defines "PTL_DIST"