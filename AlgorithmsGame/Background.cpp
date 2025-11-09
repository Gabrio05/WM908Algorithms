#include "Background.h"

Background::Background() {
	tile_index = new int[GameParameters::Background::map_size[0] * GameParameters::Background::map_size[1]] {};
	tile_collisions = new Collision[GameParameters::Background::number_of_tiles]{ GameParameters::Background::environment_collision };
	tiles = new Sprite[GameParameters::Background::number_of_tiles]{};
	false;
}

Background::~Background() {
	delete[] tiles;
	delete[] tile_collisions;
	delete[] tile_index;
}

void Background::loadAllTiles() {
	for (int i = 0; i < GameParameters::Background::number_of_tiles; i++) {
		tiles[i].image.load(GameParameters::Background::filenames[i]);
	}
}

void Background::populateMap(int* indices) {
	for (int i = 0; i < GameParameters::Background::map_size[0] * GameParameters::Background::map_size[1]; i++) {
		tile_index[i] = indices[i];
	}
}

void Background::setFixedWorld() {
	infinite_world = false;
}

bool Background::isInside(int x, int y) {
	return (x >= coordinates[0] && x < coordinates[0] + tile_width * tile_size[0]
		&& y >= coordinates[1] && y < coordinates[1] + tile_height * tile_size[1]);
}

void Background::getPixelColour(int pixel[2], unsigned char colour[4]) {
	int actual_pixel[2];
	actual_pixel[0] = pixel[0] - coordinates[0];  // Coordinate from pov of (0, 0) of background
	actual_pixel[1] = pixel[1] - coordinates[1];  // Potential BUG? TODO, fine as long as coordinates{0, 0}
	if (infinite_world) {
		actual_pixel[0] = actual_pixel[0] % (tile_width * tile_size[0]);
		actual_pixel[1] = actual_pixel[1] % (tile_height * tile_size[1]);
		if (actual_pixel[0] < 0) {
			actual_pixel[0] = tile_width * tile_size[0] + actual_pixel[0];
		}
		if (actual_pixel[1] < 0) {
			actual_pixel[1] = tile_height * tile_size[1] + actual_pixel[1];
		}
	}
	if (isInside(actual_pixel[0], actual_pixel[1])) {
		int sprite_index = tile_index[(int)(actual_pixel[0] / tile_size[0]) 
			+ (int)(actual_pixel[1] / tile_size[1]) * GameParameters::Background::map_size[0]];
		actual_pixel[0] = actual_pixel[0] % tile_size[0];
		actual_pixel[1] = actual_pixel[1] % tile_size[1];
		tiles[sprite_index].getPixelColour(actual_pixel, colour);
	}
	else {
		colour[0] = colour[1] = colour[2] = 0;
		colour[3] = 0;
	}
}