project "ViewerLib"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	targetdir ("%{wks.location}/bin/".. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/".. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.cpp",
		"src/**.hpp",
		"src/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}"
	}

	links
	{
		"glfw3",
		"glad",
		"opengl32.lib"
	}

	libdirs 
	{
		"%{LibraryDir.glfw}"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG"
			runtime "Debug"
			symbols "on"

			
	filter "configurations:Release"
		defines "RELEASE"
				runtime "Release"
				optimize "on"
