#include "SpriteHandler.h"

void Sprite::setPosition(int x, int y) {
	coordinates[0] = x - image.width / 2;
	coordinates[1] = y - image.height / 2;
}

void Sprite::getPixelColour(int pixel[2], unsigned char colour[4]) {
	int x = pixel[0] - coordinates[0];
	int y = pixel[1] - coordinates[1];
	unsigned char* temp = image.at(x, y);
	colour[0] = temp[0];
	colour[1] = temp[1];
	colour[2] = temp[2];
	colour[3] = image.alphaAt(x, y);
	if (image_effect > 0) {
		if (image_effect == 1) {
			colour[0] = min(255, (int)colour[0] * 2);
			colour[1] = min(255, (int)colour[1] * 2);
			colour[2] = min(255, (int)colour[2] * 2);
		}
		else if (image_effect == 2) {
			colour[0] = min(255, (int)colour[0] * 5);
		}
		else if (image_effect == 3) {
			colour[2] = min(255, (int)colour[2] * 5);
		}
	}
}

bool Sprite::isInside(int x, int y) {
	return (x >= coordinates[0] && x <= coordinates[0] + (int)image.width && y >= coordinates[1] && y <= (coordinates[1] + (int)image.height));
}