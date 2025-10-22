#include "../AlgorithmsGame/GameBase/GamesEngineeringBase.h"


int player_coord_x = 500;
int player_coord_y = 500;

void getPixelColour(int pixel[2], int colour[3]) {
	// Background -> Effects (if any) -> Hero -> Enemies -> Hero Projectiles -> Enemy Projectiles
	// Background
	if (pixel[0] % 50 == 0 && pixel[1] % 50 == 0) {  // HACK
		colour[0] = colour[1] = colour[2] = 255;
	}
	else {
		colour[0] = colour[1] = colour[2] = 0;
	}
	if (player_coord_x == pixel[0] && player_coord_y == pixel[1]) {
		colour[0] = 255;
		colour[1] = 100;
		colour[2] = 0;
	}
}

void drawImage(GamesEngineeringBase::Window& canvas) {
	for (int i = 0; i < 768; i++) {
		for (int j = 0; j < 1024; j++) {
			int colour[3];
			int pixel[2];
			pixel[0] = j;
			pixel[1] = i;
			getPixelColour(pixel, colour);
			canvas.draw(j, i, colour[0], colour[1], colour[2]);
		}
	}
}

int main() {
	GamesEngineeringBase::Window canvas;
	canvas.create(1024, 768, "place");
	bool isRunning = true;

	while (isRunning) {
		canvas.clear();
		drawImage(canvas);
		canvas.present();
		if (canvas.keyPressed(0x25)) {
			player_coord_x -= 1;
		}
		if (canvas.keyPressed(0x26)) {
			player_coord_y += 1;
		}
		if (canvas.keyPressed(0x27)) {
			player_coord_x += 1;
		}
		if (canvas.keyPressed(0x28)) {
			player_coord_y -= 1;
		}
	}
	return 0;
}