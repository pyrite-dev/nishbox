backends = {
	glx = {"GLX", {"X11"}},
	wgl = {"WGL", {"gdi32"}},
	glfw = {"GLFW", {"glfw"}}
}

workspace("NishBox")
	configurations({
		"Release",
		"Debug"
	})
	platforms({
		"Native",
		"Win32",
		"Win64"
	})

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
	end
})

allowed = {}
for k,v in pairs(backends) do
	table.insert(allowed, {k, v[1]})
end
newoption({
	trigger		= "draw",
	value		= "API",
	description	= "Choose a render backend",
	default		= "glx",
	category	= "Build Options",
	allowed		= allowed
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
		filter("options:draw=" .. k)
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
		filter("options:draw=" .. k)
			links(v[2])
	end
	filter("toolset:gcc or toolset:clang")
		links({
			"stdc++"
		})
	filter("system:windows")
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
		filter("options:draw=" .. k)
			files({
				"engine/graphic/opengl/" .. k .. "/ne_draw.c",
				"engine/graphic/opengl/*.c"
			})
	end
