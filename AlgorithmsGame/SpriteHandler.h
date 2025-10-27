#ifndef SPRITE_HANDLER
#define SPRITE_HANDLER
#include "GameBase/GamesEngineeringBase.h"

class Sprite {
	int coordinates[2]{};  // Coordinates of (0, 0) image pixel in world pixel
public:
	GamesEngineeringBase::Image image;
	void setPosition(int x, int y);  // Center of the sprite (automatically converts based on image size)
	void getPixelColour(int pixel[2], unsigned char colour[4]);  // RGBA, converts world to image pixel automatically
	bool isInside(int x, int y);
};

#endif
