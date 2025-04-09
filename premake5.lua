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

newaction({
	trigger = "clean",
	description = "Clean the files",
	execute = function()
		os.rmdir("bin")
		os.rmdir("obj")
		os.rmdir("lib")
	end
})

function default_stuffs()
	defines({
		"HAVE_UNISTD_H=1",
		"HAVE_STDARG_H=1"
	})
	filter("system:windows")
		defines({
			"THREAD_WIN32"
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

project("NishBox")
	kind("WindowedApp")
	language("C")
	targetdir("bin")
	targetname("nishbox")
	includedirs({
		"engine/include"
	})
	files({
		"src/*.c"
	})
	links({
		"NishEngine",
		"ode"
	})
	default_stuffs()
	filter("toolset:gcc or toolset:clang")
		links({
			"stdc++"
		})
	for k,v in pairs(backends) do
		for k2,v2 in pairs(v["backends"]) do
			filter({
				"options:backend=" .. k,
				"options:" .. k .. "=" .. k2,
				"system:windows"
			})
				links(v.windows)
				links(v2[2])
			filter({
				"options:backend=" .. k,
				"options:" .. k .. "=" .. k2,
				"system:not windows"
			})
				links(v.unix)
				links(v2[2])
		end
	end
	filter("system:windows")
		files({
			"src/*.rc"
		})
		links({
			"ws2_32"
		})
	filter("system:not windows")
		links({
			"m",
			"pthread"
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

project("NishEngine")
	kind("StaticLib")
	language("C")
	targetdir("lib")
	targetname("nishengine")
	includedirs({
		"engine/include",
		"external/lua",
		"external/zlib",
		"external/miniaudio",
		"external/stb",
	})
	files({
		"engine/include/**.h",
		"engine/*.c",
		"external/zlib/*.h",
		"external/zlib/*.c",
		"external/lua/*.h",
		"external/lua/*.c",
	})
	removefiles({
		"external/lua/lua.c"
	})
	default_stuffs()
	filter("system:windows")
		files({
			"engine/thread/win32/ne_thread.c"
		})
	filter("system:not windows")
		files({
			"engine/thread/posix/ne_thread.c"
		})
	for k,v in pairs(backends) do
		for k2,v2 in pairs(v["backends"]) do
			filter({
				"options:backend=" .. k,
				"options:" .. k .. "=" .. k2
			})
				files({
					"engine/graphic/" .. k .. "/*.c",
					"engine/graphic/" .. k .. "/" .. k2 .. "/*.c"
				})
		end
	end
