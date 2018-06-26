--Scene Machine Initialization

SCENES = {
	Scene_1 = {
		name = "Test Scene 1",
		file = "SC_One.lua",
		paths = { "Scene_2" },
		first = true
	},

	Scene_2 = {
		name = "Test Scene 2",
		file = "SC_Two.lua",
		paths = { "Scene_1" },
	}
}