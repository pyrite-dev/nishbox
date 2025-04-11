project("Engine")
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
	link_stuffs("options:engine=dynamic")
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
	msvc_filters()
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

	default_stuffs()
	for k,v in pairs(backends) do
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

	generateheader("external/ode/include/ode/precision.h", "@ODE_PRECISION@", "dDOUBLE")
	generateheader("external/ode/libccd/src/ccd/precision.h", "@CCD_PRECISION@", "CCD_DOUBLE")
	generateheader("external/ode/include/ode/version.h", "@ODE_VERSION@", "Custom-ODE")
end
