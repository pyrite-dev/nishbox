local gf = goldfish
local menu_entries = {
	{
		name = "Quit",
		callback = function()
			gf.shutdown()
		end
	},
	{
		name = "Options",
		callback = function()
		end
	},
	{},
	{
		name = "Multiplayer",
		callback = function()
		end
	},
	{
		name = "Singleplayer",
		callback = function()
		end
	}
}

local function menu()
	for i,v in ipairs(menu_entries) do
		if v.name then
			local size = 40
			local btn = gf.gui.create("button", 5 + size, 5 + size * (i - 1), gf.graphic.text_width(bold_font, size, v.name) + 5, size)
			if v.component then
				v.component:destroy()
			end
			btn:text(v.name)
			btn:prop("integer", "y-base", 1)
			btn:prop("floating", "font-size", size)
			btn:prop("integer", "no-border", 1)
			btn:prop("integer", "align", -1)
			btn:color("font", {32, 128, 32, 255})
			btn:color("hover-font", {32 + 64, 128 + 64, 32 + 64, 255})
			btn:callback(v.callback)
			v.component = btn
		end
	end
end

menu()

return true
