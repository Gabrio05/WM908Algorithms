#ifndef UPDATE_DATA
#define UPDATE_DATA
#include "GameBase/GamesEngineeringBase.h"
#include "GameParameters.h"

/* Any relevant information needed by an object for frame update. */
struct updateData {
	bool is_key_pressed[256];  // Follows virtual keys, only checks relevant keys
	float delta;
	updateData(float dt, GamesEngineeringBase::Window* canvas);
};

#endif
