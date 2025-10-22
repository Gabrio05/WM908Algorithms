#ifndef SPRITE_HANDLER
#define SPRITE_HANDLER
#include "GameBase/GamesEngineeringBase.h"

class Sprite : public GamesEngineeringBase::Image {
	int coordinates[2] = { 0, 0 };  // Coordinates of (0, 0)
public:
	void setPosition(int x, int y);  // Center of the sprite
	void getPixelColour(int pixel[2], unsigned char colour[4]);  // RGBA, converts world to image pixel automatically
	bool isInside(int x, int y);
};

#endif
