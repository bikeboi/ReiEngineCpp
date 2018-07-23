-- MOVEMENT SCRIPT --
-- DIR
local RIGHT = 0
local UP = 1
local LEFT = 2
local DOWN = 3
local movespeed
local face = RIGHT
local pre_face = face

function Init()
	movespeed = 0.01
	setAnimSpeed(Anim, 1)
end

function Update()
	numX = getX(Trans)
	numY = getY(Trans)
	--print("X = ", numX, " Y = ", numY)
	if getKey(Input, KEY.A) then 
		addVel(Phys, -movespeed, 0)
		face = LEFT
	end
	if getKey(Input, KEY.W) then 
		addVel(Phys, 0, -movespeed)
		face = UP 
	end
	if getKey(Input, KEY.S) then 
		addVel(Phys, 0, movespeed) 
		face = DOWN
	end
	if getKey(Input, KEY.D) then 
		addVel(Phys, movespeed, 0) 
		face = RIGHT
	end
	if face ~= pre_face then setAnim(Anim, face, 0) end
	pre_face = face
end

