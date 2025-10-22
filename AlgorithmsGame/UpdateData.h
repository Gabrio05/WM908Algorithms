#ifndef UPDATE_DATA
#define UPDATE_DATA
#include "GameBase/GamesEngineeringBase.h"
#include "GameParameters.h"

class UpdateData {
public:
	bool is_key_pressed[256];
	float delta;
	UpdateData(float dt, GamesEngineeringBase::Window* canvas);
};

#endif
