workspace("NishBox")
	configurations({
		"Debug",
		"Release"
	})
	platforms({
		"Native",
		"Win32",
		"Win64"
	})
	defaultplatform("Native")

filter("platforms:Win32")
	system("windows")
	architecture("x86")
	gccprefix("i686-w64-mingw32-")

filter("platforms:Win64")
	system("windows")
	architecture("x86_64")
	gccprefix("x86_64-w64-mingw32-")

newaction({
	trigger = "clean",
	description = "Clean the files",
	execute = function()
		os.rmdir("bin")
		os.rmdir("obj")
		os.rmdir("lib")
		os.rmdir("engine/bin")
		os.rmdir("engine/obj")
		os.rmdir("engine/lib")
	end
})

function msvc_filters()
	filter({})
	characterset("MBCS")
	for k,rt in ipairs({"Debug", "Release"}) do
	filter({
			"options:cc=msc",
			"options:engine=dynamic",
			"configurations:" .. rt
		})
		linkoptions({"/MANIFEST"})
		runtime(rt)
		staticruntime("Off")
	filter({
			"options:cc=msc",
			"options:engine=static",
			"configurations:" .. rt
		})
		linkoptions({"/MANIFEST"})
		runtime(rt)
		staticruntime("On")
	end
end

include "engine"

project("EngineInfo")
	filter("system:windows")
		kind("WindowedApp")
	filter("system:not windows")
		kind("ConsoleApp")
	filter({})
	language("C")
	targetdir("bin/%{cfg.buildcfg}/%{cfg.platform}")
	targetname("nishbox_engineinfo")
	includedirs({
		"engine/include"
	})
	files({
		"src/engineinfo/*.c"
	})
	removefiles({
		"src/engineinfo/main_windows.c"
	})
	filter("system:windows")
		removefiles({
			"src/engineinfo/main_console.c"
		})
		files({
			"src/engineinfo/main_windows.c"
		})
	filter({})
	links({
		"GoldFish"
	})
	-- Call this if you are gonna use my engine...
	gf_link_stuffs("options:engine=static")
	filter("system:windows")
		files({
			"src/*.rc"
		})
	filter("configurations:Debug")
		defines({
			"DEBUG"
		})
		symbols("On")
	filter("configurations:Release")
		defines({
			"NDEBUG"
		})
		optimize("On")
	msvc_filters()
	filter({})

project("NishBoxServer")
	kind("ConsoleApp")
	language("C")
	targetdir("bin/%{cfg.buildcfg}/%{cfg.platform}")
	targetname("nishbox_server")
	includedirs({
		"engine/include"
	})
	files({
		"src/server/*.c"
	})
	links({
		"GoldFish"
	})
	-- Call this if you are gonna use my engine...
	gf_link_stuffs("options:engine=static")
	filter("system:windows")
		files({
			"src/*.rc"
		})
	filter("configurations:Debug")
		defines({
			"DEBUG"
		})
		symbols("On")
	filter("configurations:Release")
		defines({
			"NDEBUG"
		})
		optimize("On")
	msvc_filters()
	filter({})

project("NishBox")
	kind("ConsoleApp")
	language("C")
	targetdir("bin/%{cfg.buildcfg}/%{cfg.platform}")
	targetname("nishbox")
	includedirs({
		"engine/include"
	})
	files({
		"src/client/*.c"
	})
	links({
		"GoldFish"
	})
	-- Call this if you are gonna use my engine...
	gf_link_stuffs("options:engine=static")
	filter("system:windows")
		files({
			"src/*.rc"
		})
	filter("configurations:Debug")
		defines({
			"DEBUG"
		})
		symbols("On")
	filter("configurations:Release")
		defines({
			"NDEBUG"
		})
		optimize("On")
	msvc_filters()
	filter({})
