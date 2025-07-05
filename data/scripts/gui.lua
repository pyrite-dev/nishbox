local gf = goldfish

windows = {}

-- Credits window
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
	str = str .. "This product includes software developed by the Pyrite Development Team.\n"
	str = str .. "For more information, see https://github.com/pyrite-dev/goldfish\n"
	text:font(mono_font)
	text:set_text(str)

	table.insert(windows, win)
	gf.gui.sort()
end

-- Options window
local function spawn_options()
	local width = 400
	local height = width / 4 * 3
	local geo = gf.geometry()
	local win = gf.gui.create("window", geo.width / 2 - width / 2, geo.height / 2 - height / 2, width, height)
	local tab = gf.gui.create("tab", 0, 0, win:prop("id", "frame"):size()[1], win:prop("id", "frame"):size()[2])
	local y = 0
	local n = 1

	tab:set_parent(win:prop("id", "frame"))

	local kv = {
		Control = {},
		Graphic = {},
		Sound = {{
			name = "Volume",
			callback = function(p, x, y, w, h)
				local volume = gf.gui.create("range", 0, 0, w - x, 0)
				volume:move({x, y + h / 2 - (volume:size()[2] - 2) / 2})

				volume:set_parent(p)
				volume:prop("floating", "min-value", 0)
				volume:prop("floating", "max-value", 1)
				volume:prop("floating", "value", gf.audio.get_volume())
				volume:callback(function ()
					gf.audio.set_volume(volume:prop("floating", "value"))
				end)
			end
		}}
	}

	win:set_text("Options")
	for k, v in sorted_pairs(kv) do
		local p = gf.gui.create("frame", 0, 0, tab:prop("id", "frame"):size()[1], tab:prop("id", "frame"):size()[2])
		p:prop("text", "title", k)
		p:set_parent(tab:prop("id", "frame"))
		n = n + 1
		for _, c in sorted_pairs(v) do
			local th = gf.graphic.text_height(font, 14, c.name)
			local eh = (th > 30) and th or 30
			local tw = gf.graphic.text_width(font, 14, c.name)
			local text = gf.gui.create("frame", 5, y, tw, eh)

			text:set_parent(p)
			text:set_text(c.name)
			text:font(font)
			text:prop("floating", "font-size", 14)

			c.callback(p, p:size()[1] / 2, y, (p:size()[1] - 5), eh)

			y = y + eh
		end
	end

	table.insert(windows, win)
	gf.gui.sort()
end

local function spawn_map ()
	local width = 600
	local height = width / 4 * 3
	local geo = gf.geometry()
	local win = gf.gui.create("window", geo.width / 2 - width / 2, geo.height / 2 - height / 2, width, height)
	local img = gf.gui.create("image", 0, 0, 100, 100)

	win:set_text("Select map")

	img:prop("text", "image", "base:/texture/test.bmp")
	img:set_parent(win:prop("id", "frame"))

	table.insert(windows, win)
	gf.gui.sort()
end

-- Currently displayed window
local windows = {}

-- Menu menu entries
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
		callback = spawn_options
	},
	{},
	{
		name = "Multiplayer",
		callback = function()
			spawn_map()
		end
	},
	{
		name = "Singleplayer",
		callback = function()
			spawn_map()
		end
	}
}

-- Destroys all currently displayed components
local function cleanup_menu()
	for _,v in ipairs(menu_entries) do
		if v.component then
			v.component:destroy()
			v.component = nil
		end
	end
end


-- Clean all windows
local function cleanup_window()
	for _,v in ipairs(windows) do
		v:destroy()
	end
	windows = {}
end

-- Draw menu
local function menu()
	cleanup_menu()
	for i,v in ipairs(menu_entries) do
		if v.name then
			local size = 48
			local btn = gf.gui.create("button", 5 + size / 3, 5 + size * (i - 1), gf.graphic.text_width(font, size, v.name) + 5, size)
			btn:set_text(v.name)
			btn:font(font)
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
