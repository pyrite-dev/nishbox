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

function generateheader(headerfile, placeholder, precstr)
	if os.isfile(headerfile) then
		return
	end
	local outfile = io.open(headerfile, "w")
	for i in io.lines(headerfile .. ".in") do
		local j,_ = string.gsub(i, placeholder, precstr)
		outfile:write(j .. "\n")
	end
	outfile:close()
end

function default_stuffs()
	characterset("MBCS")
	defines({
		"HAVE_STDARG_H=1",
		"dIDEDOUBLE",
		"CCD_IDEDOUBLE"
	})
	filter("toolset:not msc")
		defines({
			"HAVE_UNISTD_H=1"
		})
	filter("system:windows")
		defines({
			"THREAD_WIN32",
			"WIN32"
		})
	filter("system:not windows")
		defines({
			"THREAD_POSIX"
		})
	filter("platforms:Native")
		includedirs({
			"/usr/local/include",
			"/usr/X11R*/include"
		})
		libdirs({
			"/usr/local/lib",
			"/usr/X11R*/lib"
		})
	filter({
		"platforms:Native",
		"system:bsd"
	})
		includedirs({
			"/usr/pkg/include"
		})
		libdirs({
			"/usr/pkg/lib"
		})

	for k,v in pairs(backends) do
		for k2,v2 in pairs(v["backends"]) do
			filter({
				"options:backend=" .. k,
				"options:" .. k .. "=" .. k2
			})
				defines({
					"DRV_" .. string.upper(k),
					"USE_" .. string.upper(k2)
				})
		end
	end

	filter({})
		includedirs({
			"deps/include"
		})
		libdirs({
			"deps/lib"
		})
end

function link_stuffs(cond)
	filter({
		"toolset:gcc or toolset:clang",
		"system:windows",
		cond
	})
		linkoptions({
			"-static-libgcc",
			"-static-libstdc++"
		})
		links({
			"stdc++:static"
		})
	for k,v in pairs(backends) do
		for k2,v2 in pairs(v["backends"]) do
			filter({
				"options:backend=" .. k,
				"options:" .. k .. "=" .. k2,
				"system:windows",
				cond
			})
				links(v.windows)
				links(v2[2])
			filter({
				"options:backend=" .. k,
				"options:" .. k .. "=" .. k2,
				"system:not windows",
				cond
			})
				links(v.unix)
				links(v2[2])
		end
	end
	filter({
		"system:windows",
		cond
	})
		links({
			"user32",
			"ws2_32"
		})
	filter({
		"system:not windows",
		cond
	})
		links({
			"m",
			"pthread"
		})
end

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
		"Engine"
	})
	default_stuffs()
	link_stuffs("options:engine=static")
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

include "engine"
