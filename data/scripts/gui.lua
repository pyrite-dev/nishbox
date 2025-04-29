local gf = goldfish

local b1 = gf.gui.create("button", 5, 5, 200, 50)
b1:text("Quit")
b1:prop("integer", "y-base", 1)
b1:prop("floating", "font-size", 48)
b1:prop("integer", "no-border", 1)
b1:prop("integer", "align", -1)
b1:callback(function ()
	gf.shutdown()
end)

return true
