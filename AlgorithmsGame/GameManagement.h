#ifndef GAMEMANAGEMENT
#define GAMEMANAGEMENT
#include "GameParameters.h"
#include "GameBase/GamesEngineeringBase.h"
#include "SceneManagement.h"
#include "UpdateData.h"

class GameManager {
	GamesEngineeringBase::Window* canvas;
	int width = GameParameters::window_width;
	int height = GameParameters::window_height;
	Scene scene;
	GamesEngineeringBase::Timer timer;
public:
	GameManager(GamesEngineeringBase::Window* c);
	void runUpdateLoop();
	void drawImage();
};

#endif
