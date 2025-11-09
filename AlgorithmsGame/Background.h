#ifndef BACKGROUND_CLASS
#define BACKGROUND_CLASS
#include "SpriteHandler.h"
#include "GameParameters.h"
#include "Collision.h"

class Background {
	Sprite* tiles;
	int coordinates[2]{};  // world coordinates of image pixel (0, 0) of tile[0][0]
	int tile_width = GameParameters::Background::map_size[0];
	int tile_height = GameParameters::Background::map_size[1];
	int* tile_index;  // y * x_size + x
	int tile_size[2] { GameParameters::Background::tile_size[0], GameParameters::Background::tile_size[1]};
	bool isInside(int x, int y);
	bool infinite_world = true;
	Collision* tile_collisions;
public:
	Background();
	~Background();
	Background& operator=(const Background&) = delete;
	Background(const Background&) = delete;
	void loadAllTiles();
	void populateMap(int* indices);
	void setFixedWorld();
	void getPixelColour(int pixel[2], unsigned char colour[4]);
};

#endif
