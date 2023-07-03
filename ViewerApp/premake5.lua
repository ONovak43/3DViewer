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
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.assimp}",
		"%{IncludeDir.nfd}",		
	}

	links
	{
		"ViewerLib",
		"GLFW",
		"ImGui",
		"assimp",
		"nfd_d.lib"
	}

	
	libdirs 
	{
		"%{LibraryDir.assimp}",
		"%{LibraryDir.nfd}",
	}

	filter "system:windows"
		systemversion "latest"
		postbuildcommands
		{
			"copy %{prj.location}vendor\\assimp\\lib\\assimp-vc143-mt.dll %{wks.location}bin\\" .. outputdir .. "\\%{prj.name}"
		}

	filter "configurations:Debug"
		defines "DEBUG"
			runtime "Debug"
			symbols "on"

			
	filter "configurations:Release"
		defines "RELEASE"
				runtime "Release"
				optimize "on"
