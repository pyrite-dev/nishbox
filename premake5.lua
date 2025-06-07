require("gmake")
if premake.modules.gmake.cpp.pchRules and not(premake.modules.gmake.patched_resource) then
	premake.modules.gmake.patched_resource = true
	premake.override(premake.modules.gmake.cpp, "pchRules", function(base, cfg, toolset)
		base(cfg, toolset)
		_p("$(RESOURCES): | prebuild")
	end)
end

flags("MultiProcessorCompile")

workspace("NishBox")
	configurations({
		"Debug",
		"Release"
	})
	platforms({
		"Native",
		"Win32",
		"Win64",
		"ClassicMacOS"
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

filter("platforms:ClassicMacOS")
       gccprefix("powerpc-apple-macos-")
       defines({"CLASSIC_MAC_OS=1"})

filter({})

newoption({
	trigger = "destdir",
	value = "Path",
	description = "DESTDIR equiv.",
	category = "Installation",
	default = "/"
})

newoption({
	trigger = "prefix",
	value = "Path",
	description = "Installation destination",
	category = "Installation",
	default = "/usr/local"
})

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
		os.rmdir("engine/util/bin")
		os.rmdir("engine/util/obj")
		os.rmdir("engine/util/lib")
	end
})

function msvc_filters()
	-- Manifest fix by penguin2233
	require('vstudio')
	premake.override(premake.vstudio.vc200x, "generateManifest", function(base, cfg, toolset)
		if cfg.flags.NoManifest then
			premake.w('GenerateManifest="false"')
		end
	end)
	filter({})
	characterset("MBCS")
	for k,rt in ipairs({"Debug", "Release"}) do
	filter({
			"options:cc=msc",
			"options:engine=dynamic",
			"configurations:" .. rt
		})
		runtime(rt)
		staticruntime("Off")
		buildoptions({
			"/wd4819",
			"/wd4996",
			"/wd4244",
			"/wd4789"
		})
	filter({
			"options:cc=msc",
			"options:engine=static",
			"configurations:" .. rt
		})
		runtime(rt)
		staticruntime("On")
		buildoptions({
			"/wd4819",
			"/wd4996",
			"/wd4244",
			"/wd4789"
		})
	end
	filter({})
end

include "engine"

project("NishBox")
	flags("RelativeLinks")
	kind("ConsoleApp")
	language("C")
	targetdir("bin/%{cfg.buildcfg}/%{cfg.platform}")
	objdir("obj")
	targetname("nishbox")
	includedirs({
		"engine/include"
	})
	files({
		"src/*.c"
	})
	links({
		"GoldFish"
	})
	-- Call this if you are gonna use my engine...
	gf_link_stuffs("options:engine=static")
	filter("system:windows")
		defines({
			"FD_NISHBOX"
		})
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

if _ACTION and _ACTION ~= "clean" then
	local f = io.open("install.sh", "w")
	f:write("#!/bin/sh\n")
	f:write("set -e\n")
	f:write("mkdir -p " .. _OPTIONS["prefix"] .. "/lib\n")
	f:write("mkdir -p " .. _OPTIONS["prefix"] .. "/bin\n")
	f:write("mkdir -p " .. _OPTIONS["prefix"] .. "/share/NishBox\n")
	f:write("cp ./engine/lib/*/*/*.so " .. _OPTIONS["prefix"] .. "/lib/ >/dev/null 2>&1 || echo 'Failed to copy engine, but it is okay'\n")
	f:write("cp ./bin/*/*/nishbox " .. _OPTIONS["prefix"] .. "/bin/\n")
	f:write("cp ./base.pak " .. _OPTIONS["prefix"] .. "/share/NishBox/\n")
	f:write("echo 'Installation success'\n")
	f:close()
	os.chmod("install.sh", "755")

	f = io.open("src/macro.h", "w")
	f:write("#define PREFIX \"" .. _OPTIONS["prefix"] .. "\"\n")
	f:close()
end
