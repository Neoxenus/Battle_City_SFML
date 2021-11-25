#pragma once

namespace constants
{
	//tank speed
	const int NUMBER_TYPES_OF_TANKS = 8;
	const int tankSpeed[NUMBER_TYPES_OF_TANKS] = { 3, 3, 3, 3, 2, 4, 2, 2 };

	//directions
	enum class Directions
	{
		UP,
		DOWN,
		RIGHT,
		LEFT,
	};

	//field size
	const int FIELD_WIDTH = 16;
	const int FIELD_HEIGHT = 16;
	const int TILE_LENGHT = 16;

	//blocks type
	const int NUMBER_TYPE_OF_BLOCKS = 18;

	enum class Blocks
	{
		BRICK_ALL,
		BRICK_RIGHT,		
		BRICK_DOWN,
		BRICK_LEFT,		
		BRICK_UP,	
		METAL_ALL,
		METAL_RIGHT,
		METAL_DOWN,
		METAL_LEFT,		
		METAL_UP,
		WATER1,
		WATER2,
		WATER3,
		TREE,
		ICE,
		BASE,
		FLAG,
		BLACK,
		GRAY
	};

}