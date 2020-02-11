workspace "CopyingPocketMonster"
	configurations
	{
		"Debug",
		"Release"
	}
	startproject = "PocketMonster"

	platforms
	{
		"x86",
	}
	characterset ("MBCS")


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["FMOD"] = "vendor/fmod/inc"

project "01. PocketMonster"
	location "01. PocketMonster"
	kind "WindowedApp"
	language "C++"

	pchheader "stdafx.h"
	pchsource "01. PocketMonster/src/stdafx.cpp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/src",
	}
	libdirs
	{
		"vendor/fmod/lib",
		"vendor/Json/lib"
	}
	links
	{
		"fmod_vc.lib",
		"jsoncpp.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
	
	filter "configurations:Release"
		optimize "On"

project "02. MapTool"
	location "02. MapTool"
	kind "WindowedApp"
	language "C++"

	pchheader "stdafx.h"
	pchsource "02. MapTool/src/stdafx.cpp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/src",
	}
	libdirs
	{
		"vendor/fmod/lib",
		"vendor/Json/lib"
	}
	links
	{
		"fmod_vc.lib",
		"jsoncpp.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
	
	filter "configurations:Release"
		optimize "On"

project "03. Template"
	location "03. Template"
	kind "WindowedApp"
	language "C++"

	pchheader "stdafx.h"
	pchsource "03. Template/src/stdafx.cpp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/src",
	}
	libdirs
	{
		"vendor/fmod/lib",
		"vendor/Json/lib"
	}
	links
	{
		"fmod_vc.lib",
		"jsoncpp.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
	
	filter "configurations:Release"
		optimize "On"

project "04. Practice"
	location "04. Practice"
	kind "WindowedApp"
	language "C++"

	pchheader "stdafx.h"
	pchsource "04. Practice/src/stdafx.cpp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/src",
	}
	libdirs
	{
		"vendor/fmod/lib",
		"vendor/Json/lib"
	}
	links
	{
		"fmod_vc.lib",
		"jsoncpp.lib"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
	
	filter "configurations:Release"
		optimize "On"


project "05. WhiteBoard"
	location "05. WhiteBoard"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/src"
	}
	libdirs
	{
		"vendor/fmod/lib",
		"vendor/Json/lib"
	}
	links
	{
		"jsoncpp.lib"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
	
	filter "configurations:Release"
		optimize "On"