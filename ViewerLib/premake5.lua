project "ViewerLib"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	targetdir ("%{wks.location}/bin/".. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/".. outputdir .. "/%{prj.name}")

	pchheader "pch.hpp"
	pchsource "src/pch.cpp"

	files
	{
		"src/**.cpp",
		"src/**.hpp",
		"src/**.inl",
		"vendor/stb/stb_image.h"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"src",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.imgui}"
	}

	links
	{
		"opengl32.lib",
		"GLFW",
		"glad",
		"ImGui",		
	}

	libdirs 
	{
		"%{LibraryDir.assimp}"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "_DEBUG"
		runtime "Debug"
		symbols "on"
			
	filter "configurations:Release"
		defines "RELEASE"
		runtime "Release"
		optimize "on"

	filter "files:vendor/stb/stb_image.h"
		flags { "NoPCH" }
		
