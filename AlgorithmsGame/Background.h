#ifndef BACKGROUND_CLASS
#define BACKGROUND_CLASS
#include "SpriteHandler.h"
#include "GameParameters.h"

class Background {
	Sprite tiles[GameParameters::Background::number_of_tiles];
	int coordinates[2];  // world coordinates of image pixel (0, 0) of tile[0][0]
	int tile_width = GameParameters::Background::map_size[0];
	int tile_height = GameParameters::Background::map_size[1];
	int tile_index[GameParameters::Background::map_size[0]][GameParameters::Background::map_size[1]];  // x, y
	int tile_size[2] = { GameParameters::Background::tile_size[0], GameParameters::Background::tile_size[1]};
	bool isInside(int x, int y);
public:
	Background();
	void loadAllTiles();
	void getPixelColour(int pixel[2], unsigned char colour[4]);
};

#endif
