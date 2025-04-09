backends = {
	glx = {"GLX", {"X11"}},
	wgl = {"WGL", {"gdi32"}},
	glfw = {"GLFW", {"glfw"}}
}

plt = {}

for k,v in pairs(backends) do
	table.insert(plt, "Native-" .. v[1])
	if not(v[1] == "GLX") then
		table.insert(plt, "Win32-" .. v[1])
		table.insert(plt, "Win64-" .. v[1])
	end
end

workspace("NishBox")
	configurations({
		"Debug",
		"Release"
	})
	platforms(plt)
	defaultplatform("Native-GLX")

filter("platforms:Win32-*")
	system("windows")
	architecture("x86")
	gccprefix("i686-w64-mingw32-")

filter("platforms:Win64-*")
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
	filter("platforms:Native-*")
		includedirs({
			"/usr/local/include",
			"/usr/X11R*/include"
		})
		libdirs({
			"/usr/local/lib",
			"/usr/X11R*/lib"
		})
	filter({
		"platforms:Native-*",
		"system:bsd"
	})
		includedirs({
			"/usr/pkg/include"
		})
		libdirs({
			"/usr/pkg/lib"
		})

	for k,v in pairs(backends) do
		filter("platforms:*-" .. k)
			defines({
				"DRV_OPENGL",
				"USE_" .. string.upper(k)
			})
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
	for k,v in pairs(backends) do
		filter("platforms:*-" .. k)
			links(v[2])
	end
	filter("toolset:gcc or toolset:clang")
		links({
			"stdc++"
		})
	filter("system:windows")
		files({
			"src/*.rc"
		})
		links({
			"opengl32",
			"glu32",
			"ws2_32"
		})
	filter("system:not windows")
		links({
			"GL",
			"GLU",
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
		filter("platforms:*-" .. k)
			files({
				"engine/graphic/opengl/" .. k .. "/ne_draw.c",
				"engine/graphic/opengl/*.c"
			})
	end
