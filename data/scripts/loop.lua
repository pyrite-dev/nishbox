local rad = 0
local fps = "??"
local fpscount = 0

local gf = goldfish

local _ = 0
local X = 1

local points = {
	X, _, _, _, X, _, X, _, _, _, _, _, _, _, X, _, _, _, X, X, X, X, _, _, _, _, _, _, _, _, _, _, _, _,
	X, _, _, _, X, _, _, _, _, _, _, _, _, _, X, _, _, _, X, _, _, _, X, _, _, _, _, _, _, _, _, _, _, _,
	X, X, _, _, X, _, X, _, _, X, X, X, _, _, X, X, _, _, X, _, _, _, X, _, _, X, X, _, _, X, _, _, _, X,
	X, _, X, _, X, _, X, _, X, _, _, _, _, _, X, _, X, _, X, X, X, X, _, _, X, _, _, X, _, _, X, _, X, _,
	X, _, _, X, X, _, X, _, _, X, X, X, _, _, X, _, X, _, X, _, _, _, X, _, X, _, _, X, _, _, _, X, _, _,
	X, _, _, _, X, _, X, _, _, _, _, _, X, _, X, _, X, _, X, _, _, _, X, _, X, _, _, X, _, _, X, _, X, _,
	X, _, _, _, X, _, X, _, _, X, X, X, _, _, X, _, X, _, X, X, X, X, _, _, _, X, X, _, _, X, _, _, _, X,
}

local function draw_points()
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

	gf.graphic.points({0x44, 0xaa, 0, 255}, gf.graphic.DIM_3D, p)
end

gf.loop(function ()
	local geo = gf.geometry()
	local nfps = gf.fps()
	local wid = 0
	local text = ""
	local y = 0
	if not(nfps == -1) then
		fpscount = fpscount + (1 / nfps)
		if (fps == "??") or (fpscount >= 1) then
			fps = string.format("%.1f FPS", nfps)
			fpscount = 0
		end
	end

	gf.graphic.rect(0, 0, geo.width, geo.height, {0, 0x11, 0x11, 255})

	text = fps
	wid = gf.graphic.text_width(mono_font, 16, text)
	gf.graphic.text(mono_font, geo.width - wid, 0, 16, text)

	draw_points()

	y = geo.height
	for _,text in ipairs({
		"Copyright (C) Pyrite Development Team",
		"Engine version " .. gf.version
	}) do
		wid = gf.graphic.text_width(mono_font, 16, text)
		gf.graphic.text(mono_font, geo.width - wid, y - 16, 16, text)
		y = y - gf.graphic.text_height(mono_font, 16, text)
	end

	if current_music then
		if not(current_music.state) then
			current_music.text = "\"" .. current_music.title .. "\" By " .. current_music.composer
			current_music.from = -gf.graphic.text_width(font, 24, current_music.text)
			current_music.to = 0
			current_music.incr = 0
			current_music.state = 1
			current_music.second = 1.5
			current_music.wait = 3
		elseif current_music.state == 1 then
			local x = current_music.from - math.log(1 / (math.min(current_music.incr, current_music.second) / current_music.second + 1), 2) * (current_music.to - current_music.from)

			gf.graphic.text(font, x, 0, 24, current_music.text, {255, 255, 255, 255})

			current_music.incr = current_music.incr + (1 / nfps)
			if (current_music.to == 0) and (x >= current_music.to) and (current_music.incr >= current_music.second + current_music.wait) then
				current_music.to = current_music.from
				current_music.from = 0
				current_music.incr = 0
				current_music.second = 0.5
			elseif (current_music.from == 0) and (x <= current_music.to) then
				current_music.state = 2
			end
		end
	end

	if not(current_music) or current_music.music:over() then
		random_music()
	end

	if playing_sound and playing_sound.music:over() then
		stop_sound()
	end



	if not(nfps == -1) then
		rad = rad + math.rad(30) / nfps
	end
end)


return true
