-- Initialize NishBox

local gf = goldfish
local font = gf.font.load("base:/font/default.bdf")
local bold_font = gf.font.load("base:/font/bold.bdf")

gf.font.default(bold_font)

win = gf.gui.create("window", 200, 200, 400, 400)
win:text("test")

btn = gf.gui.create("button", 0, 0, 200, 200)
btn:text("test button")

local n = 0

btn:callback(function (w, type)
	if type == gf.gui.PRESS_EVENT then
		if n == 1 then
			win:destroy()
		else
			w:text("wow")
		end
		n = 1
	end
end)
btn:parent(win:prop("id", "frame"))

win:prop("id", "frame"):font(font)
win:prop("id", "frame"):text("test")

win:prop("integer", "resizable", 1)

gf.gui.sort()

gf.loop(function ()
end)
