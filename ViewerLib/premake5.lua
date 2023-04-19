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
		"vendor/lodepng/lodepng.cpp",
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
		"%{IncludeDir.lodepng}",
		"%{IncludeDir.imgui}"
	}

	links
	{
		"glad",
		"glfw3",
		"imgui",
		"opengl32.lib"
	}

	libdirs 
	{
		"%{LibraryDir.glfw}",
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

	filter "files:vendor/lodepng/lodepng.cpp"
		flags { "NoPCH" }
	
		
