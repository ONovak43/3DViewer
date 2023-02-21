include "dependencies.lua"

workspace "3DViewer"
	startproject "ViewerLibTest"
	architecture "x64"

	configurations 
	{ 
		"Debug", 
		"Release" 
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/premake"
	include "ViewerLib/vendor/glad"
group ""

group "Core"
	include "ViewerLib"
group ""

group "Tests"
	include "ViewerLibTest"
group ""

