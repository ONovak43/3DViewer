project "ViewerLibTest"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"
	targetdir ("%{wks.location}/bin/".. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/".. outputdir .. "/%{prj.name}")

	pchheader "pch.hpp"
	pchsource "pch.cpp"

	files
	{
		"tests/**.cpp",
		"main.cpp",
		"pch.cpp",
		"pch.hpp"
	}

	includedirs
	{
		"%{wks.location}/ViewerLib/src",
		"%{IncludeDir.gtest}",
	}

	links
	{
		"ViewerLib",
		"gtest"
	}

	libdirs 
	{
		"%{LibraryDir.gtest}"
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
