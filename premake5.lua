backends = {
	opengl = {
		name = "OpenGL",
		default = "glfw",
		unix = {"GL", "GLU"},
		windows = {"opengl32", "glu32"},
		backends = {
			glx = {"GLX", {"X11"}},
			wgl = {"WGL", {"gdi32"}},
			glfw = {"GLFW", {"glfw"}}
		}
	}
}

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

l = {}
for k,v in pairs(backends) do
	allowed = {}
	for k2,v2 in pairs(v["backends"]) do
		table.insert(allowed, {k2, v2[1]})
	end
	newoption({
		trigger = k,
		value = "API",
		description = "Choose a backend for " .. v["name"],
		allowed = allowed,
		default = v["default"]
	})
	table.insert(l, {k, v["name"]})
end

newoption({
	trigger = "backend",
	value = "API",
	description = "Choose a backend for rendering",
	allowed = l,
	default = "opengl"
})

newoption({
	trigger = "engine",
	value = "type",
	description = "Choose an engine type",
	allowed = {
		{"static", "Static library"},
		{"dynamic", "Dynamic library"}
	},
	default = "static"
})

newaction({
	trigger = "clean",
	description = "Clean the files",
	execute = function()
		os.rmdir("bin")
		os.rmdir("obj")
		os.rmdir("lib")
	end
})

function msvc_filters()
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
		runtime(rt)
		staticruntime("On")
	end
end

include "engine"

project("NishBox")
	kind("ConsoleApp")
	language("C")
	targetdir("bin/%{cfg.buildcfg}/%{cfg.platform}")
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
	filter({
		"options:cc=msc",
		"options:engine=static"
	})
		linkoptions({"/MANIFEST"})
	filter({})
