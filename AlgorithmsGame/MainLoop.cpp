#include "GameBase/GamesEngineeringBase.h"
#include "GameParameters.h"
#include "GameManagement.h"

// Returns the base directional speed to be multiplied by x_percent and y_percent for fair movement
float fairMovement(float x_percent, float y_percent, float speed) {
	float inter = speed * speed / (x_percent * x_percent + y_percent * y_percent);
	return (float)sqrt(inter);
}

int main() {
	GamesEngineeringBase::Window canvas;
	canvas.create(GameParameters::window_width, GameParameters::window_height, "place");
	bool isRunning = true;

	std::random_device rd;
	std::mt19937* engine = new std::mt19937{ rd() };

	GameManager game_manager{ canvas, engine };
	game_manager.loadAll();

	while (isRunning) {
		game_manager.runUpdateLoop();
	}
	delete engine;
	return 0;
}