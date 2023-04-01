project "ViewerLibTest"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
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
		"%{IncludeDir.gmock}",
	}

	links
	{
		"ViewerLib",
		"gtest",
		"gmock",
		"glad"
	}

	libdirs 
	{
		"%{LibraryDir.gtest}",
		"%{LibraryDir.gmock}"
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
