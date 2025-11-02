#ifndef GAMEMANAGEMENT
#define GAMEMANAGEMENT
#include "GameParameters.h"
#include "GameBase/GamesEngineeringBase.h"
#include "SceneManagement.h"
#include "UpdateData.h"
#ifdef DEBUG
#include <iostream>
#endif

/* Manages entire game including scene loading and basic update loop. */
class GameManager {
	GamesEngineeringBase::Window& canvas;
	int width = GameParameters::window_width;
	int height = GameParameters::window_height;
	Scene scene;
	GamesEngineeringBase::Timer timer;
#ifdef DEBUG
	float frame_time = 0.0f;
	int frames_per_second = 0;
#endif
public:
	GameManager(GamesEngineeringBase::Window& c);
	void runUpdateLoop();  // Run update in (appropriate) scene
	void loadAll();
};

#endif
