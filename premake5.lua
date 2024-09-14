workspace "PANGU"
	architecture "x64"

	configurations{
		"Debug",
		"Release",
		"Dist"	
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

includeDir = {}
includeDir["GLFW"] = "PANGU/ThirdPart/GLFW/include"
includeDir["GLAD"] = "PANGU/ThirdPart/GLAD/include"
includeDir["ImGui"] = "PANGU/ThirdPart/ImGui"
includeDir["glm"] = "PANGU/ThirdPart/glm"
includeDir['stb_image'] = "PANGU/ThirdPart/stb_img"
include "PANGU/ThirdPart/GLFW"
include "PANGU/ThirdPart/GLAD"
include "PANGU/ThirdPart/ImGui"

project "PANGU"
	location "PANGU"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pgpch.h"
	pchsource "PANGU/src/pgpch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/ThirdPart/glm/glm/**.hpp",
		"%{prj.name}/ThirdPart/glm/glm/**.inl",
		"%{prj.name}/ThirdPart/stb_img/**.hpp",
		"%{prj.name}/ThirdPart/stb_img/**.cpp"
	}

	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/ThirdPart/spdlog/include",
		"%{includeDir.GLFW}",
		"%{includeDir.GLAD}",
		"%{includeDir.ImGui}",
		"%{includeDir.ImGui}/backends",
		"%{includeDir.glm}",
		"%{includeDir.stb_image}"
	}

	links{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		staticruntime "On"
		symbols "on"
		systemversion "latest"

		defines{
			"PANGU_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}


	filter "configurations:Debug"
		defines "PANGU_DEBUG"
		defines "PANGU_ENABLE_ASSERTS"
		symbols "On"

	filter "configurations:Release"
		defines "PANGU_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "PANGU_DIST"
		symbols "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"PANGU/ThirdPart/spdlog/include",
		"PANGU/src",
		"%{includeDir.glm}",
		"PANGU/ThirdPart/ImGui"
	}

	links{
		"PANGU"
	}

	filter "system:windows"
		systemversion "latest"

		defines{
			"PANGU_PLATFORM_WINDOWS",
		}


	filter "configurations:Debug"
		defines "PANGU_DEBUG"
		defines "PANGU_ENABLE_ASSERTS"
		runtime "Debug"
		optimize "on"

	filter "configurations:Release"
		defines "PANGU_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PANGU_DIST"
		runtime "Release"
		optimize "on"