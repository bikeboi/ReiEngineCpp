Tree = 
{
	World_Object = 
	{
		class = "scene_1_listener",
		children = {

			Pac_Background = 
			{
				class = "bg",
				x = 0, y = 0, sX = 20, sY = 20,
				children = 
				{
					Bob = 
					{
						class = "bobtype",
						x = 200,
						y = 100,
						sX = 2,
						sY = 2
					},

					WallTop = 
					{
						class = "wall_v",
						x = 0, y = 52
					},

					WallBot = 
					{
						class = "wall_v",
						x = 0, y = 518
					},

					WallRight =
					{
						class = "wall_h",
						x = 518, y = 0
					},

					WallLeft = 
					{
						class = "wall_h",
						x = 52, y = 0
					}
				}
			}
		}
	}
}
