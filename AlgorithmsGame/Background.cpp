#include "Background.h"

Background::Background() {

}

void Background::loadAllTiles() {
	for (int i = 0; i < GameParameters::Background::number_of_tiles; i++) {
		tiles[i].load(GameParameters::Background::filenames[i]);
	}
}

bool Background::isInside(int x, int y) {
	return (x >= coordinates[0] && x <= coordinates[0] + tile_width * tile_size[0]
		&& y >= coordinates[1] && y <= (coordinates[1] + tile_height * tile_size[1]));
}

void Background::getPixelColour(int pixel[2], unsigned char colour[4]) {
	int actual_pixel[2];
	actual_pixel[0] = pixel[0] - coordinates[0];
	actual_pixel[1] = pixel[1] - coordinates[1];
	if (isInside(actual_pixel[0], actual_pixel[1])) {
		//int sprite_index = tile_index[(int)(x / tile_size[0])][(int)(y / tile_size[1])];  // TODO
		int sprite_index = 0;
		actual_pixel[0] = actual_pixel[0] % tile_size[0];
		actual_pixel[1] = actual_pixel[1] % tile_size[1];
		tiles[sprite_index].getPixelColour(actual_pixel, colour);
	}
	else {
		colour[0] = colour[1] = colour[2] = 0;
		colour[3] = 0;
	}
}