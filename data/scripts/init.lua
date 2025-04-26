-- Initialize NishBox

local fps = "??"
local fpscount = 0

local rad = 0
local gf = goldfish
local font = gf.font.load("base:/font/default.bdf")
local bold_font = gf.font.load("base:/font/bold.bdf")

local _ = 0
local O = 1

local points = {
	O, _, _, _, O, _, O, _, _, _, _, _, _, _, O, _, _, _, O, O, O, O, _, _, _, _, _, _, _, _, _, _, _, _,
	O, _, _, _, O, _, _, _, _, _, _, _, _, _, O, _, _, _, O, _, _, _, O, _, _, _, _, _, _, _, _, _, _, _,
	O, O, _, _, O, _, O, _, _, O, O, O, _, _, O, O, _, _, O, _, _, _, O, _, _, O, O, _, _, O, _, _, _, O,
	O, _, O, _, O, _, O, _, O, _, _, _, _, _, O, _, O, _, O, O, O, O, _, _, O, _, _, O, _, _, O, _, O, _,
	O, _, _, O, O, _, O, _, _, O, O, O, _, _, O, _, O, _, O, _, _, _, O, _, O, _, _, O, _, _, _, O, _, _,
	O, _, _, _, O, _, O, _, _, _, _, _, O, _, O, _, O, _, O, _, _, _, O, _, O, _, _, O, _, _, O, _, O, _,
	O, _, _, _, O, _, O, _, _, O, O, O, _, _, O, _, O, _, O, O, O, O, _, _, _, O, O, _, _, O, _, _, _, O,
}

gf.font.default(bold_font)

function draw_points()
	local p = {}
	local s = 0.015
	local c = #points / 7
	
	for k, v in ipairs(points) do
		if v == 1 then
			local lrad = 0
			local x = (k - 1) % c
			local y = math.floor((k - 1) / c)
			local z = 0
			local r = 0

			x = x - math.floor(c / 2)
			y = -1 * (y - math.floor(7 / 2))

			r = math.sqrt(x^2 + y^2)

			lrad = math.atan(y, x) + rad

			x = s * math.cos(lrad) * r
			y = s * math.sin(lrad + rad) * r
			z = 0

			table.insert(p, {x, y, z})
		end
	end

	gf.graphic.points({255, 255, 255, 255}, gf.graphic.DIM_3D, p)
end

gf.loop(function ()
	local geo = gf.geometry()
	local nfps = gf.fps()
	local wid = 0
	if not(nfps == -1) then
		fpscount = fpscount + (1 / nfps)
		if (fps == "??") or (fpscount >= 1) then
			fps = string.format("%.1f FPS", nfps)
			fpscount = 0
		end
	end
	wid = gf.graphic.text_width(font, 24, fps)
	gf.graphic.text(font, geo.width - wid, 0, 24, fps)

	draw_points()

	if not(nfps == -1) then
		rad = rad + math.rad(60) / nfps
	end
end)

gf.close(function ()
	local geo = gf.geometry()

	local close_window = gf.gui.create("window", geo.width / 2 - 600 / 2, geo.height / 2 - 200 / 2, 600, 200)
	local close_no = gf.gui.create("button", 0, 0, 60, 20)
	local close_yes = gf.gui.create("button", 65, 0, 60, 20)

	close_window:text("Confirm")

	close_window:prop("id", "frame"):text("Are you sure that you want to quit?")

	close_no:prop("integer", "x-base", 1)
	close_no:prop("integer", "y-base", 1)
	close_no:text("No")
	close_no:parent(close_window:prop("id", "frame"))
	close_no:callback(function (id, type)
		if type == gf.gui.PRESS_EVENT then
			close_window:destroy()
		end
	end)

	close_yes:prop("integer", "x-base", 1)
	close_yes:prop("integer", "y-base", 1)
	close_yes:text("Yes")
	close_yes:parent(close_window:prop("id", "frame"))
	close_yes:callback(function (id, type)
		if type == gf.gui.PRESS_EVENT then
			gf.shutdown()
		end
	end)

	gf.gui.sort()
end)
