local gf = goldfish

gf.close(function ()
	local geo = gf.geometry()

	local close_window = gf.gui.create("window", geo.width / 2 - 600 / 2, geo.height / 2 - 200 / 2, 600, 200)
	local close_no = gf.gui.create("button", 0, 0, 60, 20)
	local close_yes = gf.gui.create("button", 65, 0, 60, 20)

	close_window:set_text("Confirm")

	close_window:prop("id", "frame"):set_text("Are you sure that you want to quit?")

	close_no:prop("integer", "x-base", 1)
	close_no:prop("integer", "y-base", 1)
	close_no:set_text("No")
	close_no:set_parent(close_window:prop("id", "frame"))
	close_no:callback(function (id, type)
		if type == gf.gui.PRESS_EVENT then
			close_window:destroy()
		end
	end)

	close_yes:prop("integer", "x-base", 1)
	close_yes:prop("integer", "y-base", 1)
	close_yes:set_text("Yes")
	close_yes:set_parent(close_window:prop("id", "frame"))
	close_yes:callback(function (id, type)
		if type == gf.gui.PRESS_EVENT then
			gf.shutdown()
		end
	end)

	gf.gui.sort()
end)

return true
