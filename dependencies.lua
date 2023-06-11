IncludeDir = {}
IncludeDir["viewerLib"] = "%{wks.location}/ViewerLib/src"
IncludeDir["gtest"] = "%{wks.location}/ViewerLibTest/vendor/gtest/include"
IncludeDir["gmock"] = "%{wks.location}/ViewerLibTest/vendor/gmock/include"
IncludeDir["glfw"] = "%{wks.location}/ViewerLib/vendor/glfw/include"
IncludeDir["glad"] = "%{wks.location}/ViewerLib/vendor/glad/include"
IncludeDir["lodepng"] = "%{wks.location}/ViewerLib/vendor/lodepng"
IncludeDir["imgui"] = "%{wks.location}/ViewerLib/vendor/imgui"
IncludeDir["assimp"] = "%{wks.location}/ViewerApp/vendor/assimp/include"
IncludeDir["nfd"] = "%{wks.location}/ViewerApp/vendor/nativefiledialog/src/include"

LibraryDir = {}
LibraryDir["gtest"] = "%{wks.location}/ViewerLibTest/vendor/gtest/lib"
LibraryDir["gmock"] = "%{wks.location}/ViewerLibTest/vendor/gmock/lib"
LibraryDir["glfw"] = "%{wks.location}/ViewerLib/vendor/glfw/lib"
LibraryDir["assimp"] = "%{wks.location}/ViewerApp/vendor/assimp/lib"
LibraryDir["nfd"] = "%{wks.location}/ViewerApp/vendor/nativefiledialog/build/lib/Debug/x64"
