local gf = goldfish

windows = {}

local function spawn_credits()
	local width = 600
	local height = width / 4 * 3
	local geo = gf.geometry()
	local win = gf.gui.create("window", geo.width / 2 - width / 2, geo.height / 2 - height / 2, width, height)
	local text = gf.gui.create("text", 0, 0, 0, 0)

	win:set_text("Credits")

	text:set_parent(win:prop("id", "frame"))
	text:size(win:prop("id", "frame"):size())

	local str = ""
	str = str .. "NishBox - from Pyrite Development Team\n"
	str = str .. "Powered by GoldFish engine.\n"
	str = str .. "\n"
	str = str .. "GoldFish uses these projects:\n"
	str = str .. "  - Open Dynamics Engine\n"
	str = str .. "  - Lua\n"
	str = str .. "  - stb\n"
	str = str .. "  - zlib\n"
	str = str .. "  - miniaudio\n"
	str = str .. "  - dr_libs\n"
	str = str .. "  - jar\n"
	str = str .. "  - RGFW\n"
	str = str .. "  - OSMesa, from Mesa 3-D graphics library\n"
	str = str .. "\n"
	str = str .. "For more information, see COPYING file.\n"
	text:font(mono_font)
	text:set_text(str)

	table.insert(windows, win)
	gf.gui.sort()
	play_sound("choice.wav")
end

local windows = {}
local menu_entries = {
	{
		name = "Quit",
		callback = function()
			play_sound("choice.wav")
			gf.shutdown()
		end
	},
	{
		name = "Credits",
		callback = spawn_credits
	},
	{
		name = "Options",
		callback = function()
			play_sound("choice.wav")
		end
	},
	{},
	{
		name = "Multiplayer",
		callback = function()
			play_sound("choice.wav")
		end
	},
	{
		name = "Singleplayer",
		callback = function()
			play_sound("choice.wav")
		end
	}
}

local function cleanup_menu()
	for _,v in ipairs(menu_entries) do
		if v.component then
			v.component:destroy()
			v.component = nil
		end
	end
end

local function cleanup_window()
	for _,v in ipairs(windows) do
		v:destroy()
	end
	windows = {}
end

local function menu()
	cleanup_menu()
	for i,v in ipairs(menu_entries) do
		if v.name then
			local size = 56
			local btn = gf.gui.create("button", 5 + size / 3, 5 + size * (i - 1), gf.graphic.text_width(bold_font, size, v.name) + 5, size)
			btn:set_text(v.name)
			btn:prop("integer", "y-base", 1)
			btn:prop("floating", "font-size", size)
			btn:prop("integer", "no-border", 1)
			btn:prop("integer", "align", -1)
			btn:set_font_color({32, 128, 32, 255})
			btn:set_hover_font_color({32 + 64, 128 + 64, 32 + 64, 255})
			btn:callback(v.callback)
			v.component = btn
		end
	end
end

menu()

return true
