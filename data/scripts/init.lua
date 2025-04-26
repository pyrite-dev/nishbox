-- Initialize NishBox

win = goldfish.gui.create("window", 0, 0, 640, 480)
win:text("test")

btn = goldfish.gui.create("button", 0, 0, 200, 200)
btn:text("test button")

local n = 0

btn:callback(function (w, type)
	if type == goldfish.gui.PRESS_EVENT then
		if n == 1 then
			win:destroy()
		else
			w:text("wow")
		end
		n = 1
	end
end)
btn:parent(win:prop("id", "frame"))

win:prop("integer", "resizable", 1)

goldfish.gui.sort()
