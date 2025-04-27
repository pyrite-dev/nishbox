gf_backends = {
	opengl = {
		name = "OpenGL",
		default = "rgfw",
		unix = {"GL"},
		windows = {"opengl32"},
		backends = {
			glx = {"GLX", {"X11"}},
			wgl = {"WGL", {"gdi32"}},
			rgfw = {"RGFW", {}}
		}
	},
	directx = {
		name = "DirectX",
		default = "dx11",
		unix = {},
		windows = {},
		backends = {
			dx11 = {"DirectX 11", {"dxguid", "dxgi", "d3d11", "d3dcompiler", "gdi32"}}
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
		category = "Engine",
		default = v["default"]
	})
	table.insert(gf_l, {k, v["name"]})
end

newoption({
	trigger = "backend",
	value = "API",
	description = "Choose a backend for rendering",
	allowed = gf_l,
	category = "Engine",
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
	category = "Engine",
	default = "static"
})
	
function gf_default_stuffs()
	filter({})
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
	filter({})
	filter({
		"platforms:Native",
		"system:not windows"
	})
		includedirs({
			"/usr/local/include",
			"/usr/X11R6/include",
			"/usr/X11R7/include",
			"/usr/X11/include"
		})
		libdirs({
			"/usr/local/lib",
			"/usr/X11R6/lib",
			"/usr/X11R7/lib",
			"/usr/X11/lib"
		})
	filter({
		"platforms:Native",
		"system:not windows",
		"toolset:gcc or toolset:clang"
	})
		linkoptions({
			"-Wl,-R/usr/local/lib",
			"-Wl,-R/usr/X11R6/lib",
			"-Wl,-R/usr/X11R7/lib",
			"-Wl,-R/usr/X11/lib"
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
	filter({
		"platforms:Native",
		"system:bsd",
		"toolset:gcc or toolset:clang"
	})
		linkoptions({
			"-Wl,-R/usr/pkg/lib"
		})

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
	filter({})
end

function gf_msvc_filters()
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

include("util")
include("src")

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

	local outfile = io.open("include/gf_config.h", "w")
	outfile:write("#ifndef __GF_CONFIG_H__\n")
	outfile:write("#define __GF_CONFIG_H__\n")
	if _OPTIONS["engine"] == "dynamic" then
	outfile:write("#define GF_BUILT_AS_DLL 1\n")
	end
	outfile:write("#endif\n")
	outfile:close()
end
