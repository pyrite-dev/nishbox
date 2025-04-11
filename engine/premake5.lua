gf_backends = {
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

gf_l = {}
for k,v in pairs(gf_backends) do
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
	table.insert(gf_l, {k, v["name"]})
end

newoption({
	trigger = "backend",
	value = "API",
	description = "Choose a backend for rendering",
	allowed = gf_l,
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
	
function gf_default_stuffs()
	filter({})
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

	for k,v in pairs(gf_backends) do
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
end

function gf_generateheader(headerfile, placeholder, precstr)
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

function gf_link_stuffs(cond)
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
	filter({
		"toolset:gcc or toolset:clang",
		"system:not windows",
		cond
	})
		links({
			"stdc++"
		})
	for k,v in pairs(gf_backends) do
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

function gf_msvc_filters()
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

project("GoldFish")
	language("C")
	filter("options:engine=static")
		kind("StaticLib")
		defines({
			"ODE_LIB"
		})
	filter("options:engine=dynamic")
		kind("SharedLib")
		defines({
			"ODE_DLL",
			"_DLL"
		})
	filter({
		"options:engine=dynamic",
		"system:windows"
	})
		files({
			"engine.rc"		
		})
	gf_link_stuffs("options:engine=dynamic")
	filter("configurations:Debug")
		defines({
			"DEBUG",
			"_DEBUG"
		})
		symbols("On")
	filter("configurations:Release")
		defines({
			"NDEBUG",
			"dNODEBUG",
		})
		optimize("On")
	gf_msvc_filters()
	filter({})
	targetdir("lib/%{cfg.buildcfg}/%{cfg.platform}")
	targetname("goldfish")
	includedirs({
		"include",
		"external/lua",
		"external/zlib",
		"external/miniaudio",
		"external/stb"
	})
	files({
		"include/**.h",
		"*.c",
		"external/zlib/*.h",
		"external/zlib/*.c",
		"external/lua/l*.h",
		"external/lua/l*.c",
	})
	removefiles({
		"external/lua/ltests.c",
		"external/lua/ltests.h"
	})
	filter({})
	removefiles({
		"external/lua/lua.c"
	})

	filter("system:windows")
		files({
			"thread/win32/gf_thread.c"
		})
	filter("system:not windows")
		files({
			"thread/posix/gf_thread.c"
		})
	filter({})

	-- Begin ODE
	includedirs({
		"external/ode/include",
		"external/ode/ode/src",
		"external/ode/ode/src/joints",
		"external/ode/OPCODE",
		"external/ode/GIMPACT/include",
		"external/ode/libccd/src/custom",
		"external/ode/libccd/src"
	})
	files({
		"external/ode/include/ode/*.h",
		"external/ode/ode/src/joints/*.h",
		"external/ode/ode/src/joints/*.cpp",
		"external/ode/ode/src/*.h",
		"external/ode/ode/src/*.c",
		"external/ode/ode/src/*.cpp"
	})
	removefiles({
		"external/ode/ode/src/collision_trimesh_trimesh_old.cpp",
		"external/ode/ode/src/collision_trimesh_opcode.cpp",
		"external/ode/ode/src/collision_trimesh_disabled.cpp"
	})

	includedirs({
		"external/ode/ou/include"
	})
	files({
		"external/ode/ou/include/**.h",
		"external/ode/ou/src/**.h",
		"external/ode/ou/src/**.cpp"
	})
	defines({
		"_OU_NAMESPACE=odeou",
		"_OU_FEATURE_SET=_OU_FEATURE_SET_TLS"
	})

	files({
		"external/ode/GIMPACT/**.h",
		"external/ode/GIMPACT/**.cpp"
	})

	files({
		"external/ode/libccd/src/custom/ccdcustom/*.h",
		"external/ode/libccd/src/ccd/*.h",
		"external/ode/libccd/src/*.c"
	})

	defines({
		"dLIBCCD_ENABLED",
		"dLIBCCD_INTERNAL",
		"dLIBCCD_BOX_CYL",
		"dLIBCCD_CYL_CYL",
		"dLIBCCD_CAP_CYL",
		"dLIBCCD_CONVEX_BOX",
		"dLIBCCD_CONVEX_CAP",
		"dLIBCCD_CONVEX_CYL",
		"dLIBCCD_CONVEX_SPHERE",
		"dLIBCCD_CONVEX_CONVEX"
	})
	-- End ODE

	gf_default_stuffs()
	for k,v in pairs(gf_backends) do
		for k2,v2 in pairs(v["backends"]) do
			filter({
				"options:backend=" .. k,
				"options:" .. k .. "=" .. k2
			})
				files({
					"graphic/" .. k .. "/*.c",
					"graphic/" .. k .. "/" .. k2 .. "/*.c"
				})
		end
	end

if _ACTION and _ACTION ~= "clean" then
	local text = ""

	text = text .. "#ifndef _ODE_CONFIG_H_\n"
	text = text .. "#define _ODE_CONFIG_H_\n"
	text = text .. "#define dTRIMESH_ENABLED 1\n"
	text = text .. "#define dTRIMESH_GIMPACT 1\n"
	text = text .. "#define dOU_ENABLED 1\n"
	text = text .. "#define dATOMICS_ENABLED 1\n"
	text = text .. "#define dTLS_ENABLED 1\n"
	text = text .. "#define dBUILTIN_THREADING_IMPL_ENABLED 1\n"
	text = text .. "#include \"typedefs.h\"\n"
	text = text .. "#endif\n"

	if not(os.isfile("external/ode/ode/src/config.h")) then
		local outfile = io.open("external/ode/ode/src/config.h", "w")
		outfile:write(text)
		outfile:close()
	end

	gf_generateheader("external/ode/include/ode/precision.h", "@ODE_PRECISION@", "dDOUBLE")
	gf_generateheader("external/ode/libccd/src/ccd/precision.h", "@CCD_PRECISION@", "CCD_DOUBLE")
	gf_generateheader("external/ode/include/ode/version.h", "@ODE_VERSION@", "Custom-ODE")
end
