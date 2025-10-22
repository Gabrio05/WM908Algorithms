#include "GameBase/GamesEngineeringBase.h"
#include "SceneManagement.h"
#include "GameParameters.h"
#include "GameManagement.h"

int main() {
	GamesEngineeringBase::Window canvas;
	canvas.create(GameParameters::window_width, GameParameters::window_height, "place");
	bool isRunning = true;

	GameManager game_manager = GameManager(&canvas);

	while (isRunning) {
		game_manager.runUpdateLoop();
	}
	return 0;
}