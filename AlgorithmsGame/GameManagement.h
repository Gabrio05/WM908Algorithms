#ifndef GAMEMANAGEMENT
#define GAMEMANAGEMENT
#include <iostream>
#include "GameParameters.h"
#include "GameBase/GamesEngineeringBase.h"
#include "SceneManagement.h"
#include "UpdateData.h"

/* Manages entire game including scene loading and basic update loop. */
class GameManager {
	GamesEngineeringBase::Window& canvas;
	int width = GameParameters::window_width;
	int height = GameParameters::window_height;
	Scene scene;
	GamesEngineeringBase::Timer timer;
	std::mt19937* random_engine;
#ifdef _DEBUG
	float frame_time = 0.0f;
	int frames_per_second = 0;
#endif
public:
	GameManager(GamesEngineeringBase::Window& c, std::mt19937* engine);
	void runUpdateLoop();  // Run update in (appropriate) scene
	void loadAll();
};

#endif
