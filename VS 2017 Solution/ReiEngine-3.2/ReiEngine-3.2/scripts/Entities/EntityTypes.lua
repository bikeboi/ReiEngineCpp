-- Entity Loading Script

sprPath = "sprites/"
bgPath = "bg/"

print("Loading Entities...")

ENTITIES = {
	sc_1 = 
	{
		class = "scene_1_listener",

		components = {
			SCRIPT = "SceneScript_1.lua",
			CONTROLLER = { source = INPUT_TYPE.KEY, mod = INPUT_MODULE.MENU }
		}
	},

	sc_2 = 
	{
		class = "scene_2_listener",

		components = {
			SCRIPT = "SceneScript_2.lua",
			CONTROLLER = { source = INPUT_TYPE.KEY, mod = INPUT_MODULE.MENU }
		}
	},

	bob = 
	{
		class = "bobtype",

		components = {
			TRANSFORM = { x=0, y=0, z=1, sX=1, sY=1 },
			CONTROLLER = { source = INPUT_TYPE.KEY, mod = INPUT_MODULE.MOVE },
			PHYSICS = true,
			COLLISION = { x=0, y=0, width=40, height=40, solid=true, mobile=true },
			SCRIPT = "MovementScript.lua",
			AUDIO = { bounce="sfx/SFX_Hit.wav" },
			ANIM = {rows=4, cols=4, width=20, height=20, spd=6, posX=0, posY=0},
			RENDER = { sprites = { pac_spr = sprPath.."SPR_Pac.png" }, text = { font="sansation", size=25, x=20, y=20 }}
		}
	},

	james = 
	{
		class = "jamestype",

		components = {
			TRANSFORM = { x=0, y=0, z=1, sX=2, sY=2 },
			ANIM = { rows=1, cols=5, width=18, height=24, spd=4, posX=0, posY=0},
			RENDER = { sprites = { jame_spr = sprPath.."SPR_Bob.png"}}
		}
	},

	background = 
	{
		class = "bg",

		components = 
		{
			TRANSFORM = { x=0, y=0, z=0, sX=1, sY=1 },
			RENDER = { sprites = { bg = bgPath.."BG_Frame.png"} }
		}
	},

	wallVert = 
	{
		class = "wall_v",

		components = {
			TRANSFORM = { x=0, y=0, z=0, sX=1, sY=1},
			COLLISION = { x=0, y=0, width=600, height=30, solid=true, mobile=false },
			PHYSICS = true,
		}
	},

	wallHorz = 
	{
		class = "wall_h",

		components = {
			TRANSFORM = { x=0, y=0, z=0, sX=1, sY=1},
			COLLISION = { x=0, y=0, width=30, height=600, solid=true, mobile=false },
			PHYSICS = true
		}
	}
}
