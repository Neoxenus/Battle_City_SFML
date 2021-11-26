#pragma once
#include <vector>
namespace constants
{
	//tank speed
	const int NUMBER_TYPES_OF_TANKS = 8;
	const int tankSpeed[NUMBER_TYPES_OF_TANKS] = { 3, 3, 3, 3, 2, 4, 2, 2 };

	const int NUMBER_PLAYERS_RESPAWN = 2;
	//tank default coord
	//player
	const int DEFAULT_PLAYER_COORD_X[NUMBER_PLAYERS_RESPAWN] = { 8,16 };
	const int DEFAULT_PLAYER_COORD_Y = 26;
	//enemy
	const int NUMBER_ENEMY_RESPAWN = 3;
	const int DEFAULT_ENEMY_COORD_X[NUMBER_ENEMY_RESPAWN] {0,12,24};
	const int DEFAULT_ENEMY_COORD_Y { 0};
	//directions
	enum class Directions
	{
		UP,
		DOWN,
		RIGHT,
		LEFT,
	};

	//offset
	const int WINDOW_OFFSET = 256;

	//field size
	const int FIELD_WIDTH = 32;
	const int FIELD_HEIGHT = 32;
	const int BLOCK_LENGHT = 16;

	//blocks type
	const int NUMBER_TYPE_OF_BLOCKS = 18;
	const int BLOCK_HEIGHT = 16;
	const int BLOCK_WIDTH = 16;

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
		GRAY,
		TILES_BLOCK
	};

	//tiles type
	const int NUMBER_TYPE_OF_TILES = 22;
	const int TILES_LENGHT = 8;

	enum Tiles
	{
		BLACK,
		BRICK1000, 
		BRICK0100,
		BRICK1100,
		BRICK0010,
		BRICK1010,
		BRICK0110,
		BRICK1110,
		BRICK0001,
		BRICK1001,
		BRICK0101,
		BRICK1101,
		BRICK0011,
		BRICK1011,
		BRICK0111,
		BRICK1111,
		METAL,
		TREE,
		ICE,
		WATER1,
		WATER2,
		WATER3,
		//other tiles that we dont draw
		BASE,
		FLAG,
		GRAY,
	};
	
	const std::vector<std::vector<Tiles>> toTiles
	{
		{BRICK1111, BRICK1111, BRICK1111, BRICK1111},//BRICK_ALL,
		{BLACK,     BRICK1111, BLACK    , BRICK1111},//BRICK_RIGHT,
		{BRICK1111, BRICK1111, BLACK    , BLACK    },//BRICK_DOWN
		{BRICK1111, BLACK    , BRICK1111, BLACK    },//BRICK_LEFT
		{BLACK    , BLACK    , BRICK1111, BRICK1111},//BRICK_UP,

		{METAL, METAL, METAL, METAL},//metal
		{BLACK,     METAL, BLACK    , METAL},
		{METAL, METAL, BLACK    , BLACK    },
		{METAL, BLACK    , METAL, BLACK    },
		{BLACK    , BLACK    , METAL, METAL},//
		{WATER1,WATER1,WATER1,WATER1},
		{WATER2,WATER2,WATER2,WATER2},
		{WATER3,WATER3,WATER3,WATER3},
		{TREE,TREE,TREE,TREE},
		{ICE,ICE,ICE,ICE},
		{BASE,BASE,BASE,BASE},
		{FLAG,FLAG,FLAG,FLAG},
		{BLACK,BLACK,BLACK,BLACK},
		{GRAY,GRAY,GRAY,GRAY},
	};

	//field1

	const std::vector<std::vector<int>> field1
	{
		{(int)Blocks::GRAY , (int)Blocks::GRAY ,		(int)Blocks::GRAY ,			(int)Blocks::GRAY ,			(int)Blocks::GRAY ,			(int)Blocks::GRAY ,		(int)Blocks::GRAY ,			(int)Blocks::GRAY ,			(int)Blocks::GRAY ,			(int)Blocks::GRAY ,		(int)Blocks::GRAY ,			(int)Blocks::GRAY ,			(int)Blocks::GRAY ,			(int)Blocks::GRAY ,			(int)Blocks::GRAY , (int)Blocks::GRAY },
		{(int)Blocks::GRAY , (int)Blocks::BLACK,		(int)Blocks::BLACK,			(int)Blocks::BLACK,			(int)Blocks::BLACK,			(int)Blocks::BLACK,		(int)Blocks::BLACK,			(int)Blocks::BLACK,			(int)Blocks::BLACK,			(int)Blocks::BLACK,		(int)Blocks::BLACK,			(int)Blocks::BLACK,			(int)Blocks::BLACK,			(int)Blocks::BLACK,			(int)Blocks::GRAY , (int)Blocks::GRAY },
		{(int)Blocks::GRAY , (int)Blocks::BLACK,		(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,		(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,		(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::GRAY , (int)Blocks::GRAY },
		{(int)Blocks::GRAY , (int)Blocks::BLACK,		(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,		(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,		(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::GRAY , (int)Blocks::GRAY },
		{(int)Blocks::GRAY , (int)Blocks::BLACK,		(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,		(int)Blocks::BRICK_ALL,		(int)Blocks::METAL_ALL,		(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,		(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::GRAY , (int)Blocks::GRAY },
		{(int)Blocks::GRAY , (int)Blocks::BLACK,		(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,		(int)Blocks::BRICK_UP,		(int)Blocks::BLACK,			(int)Blocks::BRICK_UP,		(int)Blocks::BLACK,		(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::GRAY , (int)Blocks::GRAY },
		{(int)Blocks::GRAY , (int)Blocks::BLACK,		(int)Blocks::BRICK_UP,		(int)Blocks::BLACK,			(int)Blocks::BRICK_UP,		(int)Blocks::BLACK,		(int)Blocks::BRICK_DOWN,	(int)Blocks::BLACK,			(int)Blocks::BRICK_DOWN,	(int)Blocks::BLACK,		(int)Blocks::BRICK_UP,		(int)Blocks::BLACK,			(int)Blocks::BRICK_UP,		(int)Blocks::BLACK,			(int)Blocks::GRAY , (int)Blocks::GRAY },
		{(int)Blocks::GRAY , (int)Blocks::BRICK_DOWN,	(int)Blocks::BLACK,			(int)Blocks::BRICK_DOWN,	(int)Blocks::BRICK_DOWN,	(int)Blocks::BLACK,		(int)Blocks::BRICK_UP,		(int)Blocks::BLACK,			(int)Blocks::BRICK_UP,		(int)Blocks::BLACK,		(int)Blocks::BRICK_DOWN,	(int)Blocks::BRICK_DOWN,	(int)Blocks::BLACK,			(int)Blocks::BRICK_DOWN,	(int)Blocks::GRAY , (int)Blocks::GRAY },
		{(int)Blocks::GRAY , (int)Blocks::METAL_UP,		(int)Blocks::BLACK,			(int)Blocks::BRICK_UP,		(int)Blocks::BRICK_UP,		(int)Blocks::BLACK,		(int)Blocks::BRICK_DOWN,	(int)Blocks::BLACK,			(int)Blocks::BRICK_DOWN,	(int)Blocks::BLACK,		(int)Blocks::BRICK_UP,		(int)Blocks::BRICK_UP,		(int)Blocks::BLACK,			(int)Blocks::METAL_UP,		(int)Blocks::GRAY , (int)Blocks::GRAY },
		{(int)Blocks::GRAY , (int)Blocks::BLACK,		(int)Blocks::BRICK_DOWN,	(int)Blocks::BLACK,			(int)Blocks::BRICK_DOWN,	(int)Blocks::BLACK,		(int)Blocks::BRICK_ALL,		(int)Blocks::BRICK_ALL,		(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,		(int)Blocks::BRICK_DOWN,	(int)Blocks::BLACK,			(int)Blocks::BRICK_DOWN,	(int)Blocks::BLACK,			(int)Blocks::GRAY , (int)Blocks::GRAY },
		{(int)Blocks::GRAY , (int)Blocks::BLACK,		(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,		(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,		(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::GRAY , (int)Blocks::GRAY },
		{(int)Blocks::GRAY , (int)Blocks::BLACK,		(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,		(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,		(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::GRAY , (int)Blocks::GRAY },
		{(int)Blocks::GRAY , (int)Blocks::BLACK,		(int)Blocks::BRICK_ALL, 	(int)Blocks::BLACK,			(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,		(int)Blocks::BRICK_UP,		(int)Blocks::BLACK,			(int)Blocks::BRICK_UP,		(int)Blocks::BLACK,		(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::GRAY , (int)Blocks::GRAY },
		{(int)Blocks::GRAY , (int)Blocks::BLACK,		(int)Blocks::BRICK_ALL, 	(int)Blocks::BLACK,			(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,		(int)Blocks::TILES_BLOCK,	(int)Blocks::BRICK_DOWN,	(int)Blocks::TILES_BLOCK,	(int)Blocks::BLACK,		(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::BRICK_ALL,		(int)Blocks::BLACK,			(int)Blocks::GRAY , (int)Blocks::GRAY },
		{(int)Blocks::GRAY , (int)Blocks::BLACK,		(int)Blocks::BLACK,		    (int)Blocks::BLACK,			(int)Blocks::BLACK,			(int)Blocks::BLACK,		(int)Blocks::BRICK_RIGHT,	(int)Blocks::BASE,			(int)Blocks::BRICK_LEFT,	(int)Blocks::BLACK,		(int)Blocks::BLACK,			(int)Blocks::BLACK,			(int)Blocks::BLACK,			(int)Blocks::BLACK,			(int)Blocks::GRAY , (int)Blocks::GRAY },
		{(int)Blocks::GRAY , (int)Blocks::GRAY ,		(int)Blocks::GRAY ,		    (int)Blocks::GRAY ,			(int)Blocks::GRAY ,			(int)Blocks::GRAY ,		(int)Blocks::GRAY ,			(int)Blocks::GRAY ,			(int)Blocks::GRAY ,			(int)Blocks::GRAY ,		(int)Blocks::GRAY ,			(int)Blocks::GRAY ,			(int)Blocks::GRAY ,			(int)Blocks::GRAY ,			(int)Blocks::GRAY , (int)Blocks::GRAY },
	};

	//std::vector<std::vector<int>> tile1 (TILES_HEIGHT, std::vector<int>(TILES_WIDTH, -1));

	/*std::vector<std::vector<int>> tile1[28][12] = (int)Tiles::BRICK0000;
	std::vector<std::vector<int>> tile1[28][13] = (int)Tiles::BRICK0000;
	std::vector<std::vector<int>> tile1[29][12] = (int)Tiles::BRICK0000;
	std::vector<std::vector<int>> tile1[29][13] = (int)Tiles::BRICK1111;

	std::vector<std::vector<int>> tile1[33][12] = (int)Tiles::BRICK0000;
	std::vector<std::vector<int>> tile1[33][13] = (int)Tiles::BRICK0000;
	std::vector<std::vector<int>> tile1[34][12] = (int)Tiles::BRICK1111;
	std::vector<std::vector<int>> tile1[34][13] = (int)Tiles::BRICK0000;*/
}