project "ViewerApp"
	kind "ConsoleApp"
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
		"src",
		"%{IncludeDir.viewerLib}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}"
	}

	links
	{
		"ViewerLib",
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
