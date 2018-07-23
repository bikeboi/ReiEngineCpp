-- SCENE CONTROL SCRIPT --

function Init()
	print("Scene Initialized.\nWELCOME NEW PLAYER: SCENE 1")
end

function Update()
	--print("Scene reading input")
	if getKey(Input, KEY.N) then 
		nextScene(ActiveScene, "Scene_2") 
	end
end
