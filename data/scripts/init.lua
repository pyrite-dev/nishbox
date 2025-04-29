-- Initialize NishBox

local gf = goldfish

font = gf.font.load("base:/font/default.bdf")
bold_font = gf.font.load("base:/font/bold.bdf")
mono_font = gf.font.load("base:/font/mono.bdf")
mono_bold_font = gf.font.load("base:/font/monobold.bdf")

gf.font.default(bold_font)

require("base:/scripts/gui.lua")
require("base:/scripts/loop.lua")
require("base:/scripts/close.lua")
