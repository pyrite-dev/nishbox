-- Initialize NishBox

local gf = goldfish

local musics = {names = {}}

gf.audio.set_volume(0)

current_music = nil

math.randomseed(os.time())

font = gf.font.load("base:/font/default.ttf")
bold_font = gf.font.load("base:/font/bold.ttf")
mono_font = gf.font.load("base:/font/mono.ttf")
mono_bold_font = gf.font.load("base:/font/monobold.ttf")

gf.font.default(font)

function lines(str)
	str = str:gsub("\r\n", "\n")
	if str:sub(-1) ~= "\n" then
		str = str .. "\n"
	end
	return str:gmatch("(.-)\n")
end

function play_music(name)
	if current_music and current_music.music then
		current_music.music:stop()
	end
	local music = gf.audio.create("base:/music/" .. name)
	if not(music) then
		return false
	end
	current_music = {
		title = musics[name].title,
		composer = musics[name].composer,
		music = music
	}
	music:resume()
	return true
end

function random_music()
	local st = false
	while(not(st)) do
		local name = musics.names[math.random(1, #musics.names)]
		st = play_music(name)
	end
end

function init_music()
	local ini = gf.read("base:/music/info.ini")
	local l =  lines(ini)
	local name = ""
	for v in l do
		local m = {}
		m = {v:match("^%[([^%]]+)%]$")}
		if #m > 0 then
			name = m[1]
			musics[name] = {}
			table.insert(musics.names, name)
		end
		m = {v:match("^([^%=]+)%=(.+)$")}
		if #m > 0 then
			musics[name][m[1]] = m[2]
		end
	end
end

require("base:/scripts/gui.lua")
require("base:/scripts/loop.lua")
require("base:/scripts/close.lua")

init_music()
