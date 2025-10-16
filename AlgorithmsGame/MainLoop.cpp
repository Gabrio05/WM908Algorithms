#include "GameBase/GamesEngineeringBase.h"
#include "GameParameters.h"
 
class Camera {
	int x_position;
	int y_position;
	float x_velocity;
	float y_velocity;
	const float acceleration = GameParameters::Camera::acceleration;
public:
	// Update camera position smoothly based on objective destination
	void update_position(int x, int y, float delta) {

	}
	int get_x() { return (int)(x_position + 0; }
	int get_y() { return y_position; }
};

void drawImage(GamesEngineeringBase::Window &canvas) {
	// Background -> Effects (if any) -> Hero -> Enemies -> Hero Projectiles -> Enemy Projectiles
	// Background
	for (int i = 0; i < GameParameters::window_height; i++) {
		for (int j = 0; j < GameParameters::window_width; j++) {
			if (i % 50 == 0 && j % 50 == 0) {
				canvas.draw(j, i, 255, 255, 128);
			}
		}
	}
}

int main() {
	GamesEngineeringBase::Window canvas;
	canvas.create(GameParameters::window_width, GameParameters::window_height, "Test");
	bool isRunning = true;

	while (isRunning) {
		canvas.clear();
		drawImage(canvas);
		canvas.present();
	}
	return 0;
}