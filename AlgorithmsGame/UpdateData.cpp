#include "UpdateData.h"

UpdateData::UpdateData(float dt, GamesEngineeringBase::Window* canvas) {
	delta = dt;
	for (int i = 0; i < GameParameters::UpdateData::inputs_to_check_length; i++) {
		int key_check = GameParameters::UpdateData::inputs_to_check[i];
		is_key_pressed[key_check] = canvas->keyPressed(key_check);
	}
}