#include "GameBase/GamesEngineeringBase.h"
#define WIDTH 1024
#define HEIGHT 768

int main() {
	GamesEngineeringBase::Window canvas;
	canvas.create(WIDTH, HEIGHT, "Test");
	bool isRunning = true;

	while (isRunning) {
		canvas.clear();
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				canvas.draw(i, j, 126, 0, 0);
				canvas.draw(i, j, 126, 0, 0);
			}
		}
		canvas.present();
	}
	return 0;
}