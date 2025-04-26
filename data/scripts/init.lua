-- Initialize NishBox

local fps = "??"
local fpscount = 0

local gf = goldfish
local font = gf.font.load("base:/font/default.bdf")
local bold_font = gf.font.load("base:/font/bold.bdf")

gf.font.default(bold_font)

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
end)

gf.gui.create("button", 0, 0, 200, 200):callback(function (id, type)
	if type == gf.gui.PRESS_EVENT then
		local audio = gf.audio.create("base:/music/deep_blue.xm")
		audio:resume()
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
