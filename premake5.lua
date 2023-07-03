include "dependencies.lua"

workspace "3DViewer"
	startproject "ViewerApp"
	architecture "x64"

	configurations 
	{ 
		"Debug", 
		"Release" 
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/premake"
	include "ViewerLib/vendor/glfw"
	include "ViewerLib/vendor/glad"
	include "ViewerLib/vendor/imgui"
group ""

group "Core"
	include "ViewerLib"
	include "ViewerApp"
group ""

group "Tests"
	include "ViewerLibTest"
group ""

