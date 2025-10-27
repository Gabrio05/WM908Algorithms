#include "GameBase/GamesEngineeringBase.h"
#include "GameParameters.h"
#include "GameManagement.h"

int main() {
	GamesEngineeringBase::Window canvas;
	canvas.create(GameParameters::window_width, GameParameters::window_height, "place");
	bool isRunning = true;

	GameManager game_manager{ canvas };
	game_manager.loadAll();

	while (isRunning) {
		game_manager.runUpdateLoop();
	}
	return 0;
}