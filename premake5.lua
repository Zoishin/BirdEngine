workspace "BirdEngine" 

	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "BirdEngine"
	location "BirdEngine"
	kind "SharedLib"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")



	files

	{

		"%{prj.name}/src/**.h",

		"%{prj.name}/src/**.cpp",

		"%{prj.name}/src/**.hpp"

	}



	includedirs

	{

		"%{prj.name}/vendor/spdlog/include",

		"%{prj.name}/src/Hazel/vendor/spdlog/include"

	}



	filter "system:windows"

		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines

		{

			"SPDLOG_COMPILED_LIB",

			"BE_PLATFORM_WINDOWS",

			"BE_BUILD_DLL",

			"_WINDLL"

		}



		postbuildcommands

		{

			("{COPY} %{cfg.buildtarget.relpath} ../bin/".. outputdir .."/SandBox")

		}



	filter "configurations:Debug"

		defines "HZ_DEBUG"

		symbols "On"

	



	filter "configurations:Release"

		defines "HZ_RELEASE"

		optimize "On"





	filter "configurations:Dist"

		defines "HZ_DIST"

		optimize "On"



project "SandBox"

	location "SandBox"

	kind "ConsoleApp"

	language "C++"



	targetdir("bin/" .. outputdir .. "/%{prj.name}")

	objdir("bin-int/" .. outputdir .. "/%{prj.name}")



	files

	{

		"%{prj.name}/src/**.h",

		"%{prj.name}/src/**.cpp",

		"%{prj.name}/src/**.hpp"

	}



	includedirs

	{

		"Hazel/src/Hazel/vendor/spdlog/include",

		"Hazel/src" 

	}



	links

	{

		"Hazel"

	}



	filter "system:windows"

		cppdialect "C++17"

		staticruntime "On"

		systemversion "latest"



		defines

		{

			"HZ_PLATFORM_WINDOWS",

		}



	filter "configurations:Debug"

		defines "HZ_DEBUG"

		symbols "On"

	



	filter "configurations:Release"

		defines "HZ_RELEASE"

		optimize "On"





	filter "configurations:Dist"

		defines "HZ_DIST"

		optimize "On"