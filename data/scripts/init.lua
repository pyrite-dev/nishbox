-- Initialize NishBox

win = goldfish.gui.create("window", 0, 0, 640, 480)
win:text("test")

btn = goldfish.gui.create("button", 0, 0, 200, 200)
btn:text("test button")

btn:callback(function ()
	print("boo")
end)
btn:parent(win:prop_id("frame"))

goldfish.gui.sort()
