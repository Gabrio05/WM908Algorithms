#include "GameBase/GamesEngineeringBase.h"
#include "GameParameters.h"
#include <memory>

float smoothInterpolation(float a, float b, float t) {
	t = 3 * t * t - 2 * t * t * t;
	return (1 - t) * a + t * b;
}

class Camera {
	float position[2];
	float time_to_destination = GameParameters::Camera::time_to_destination;
public:
	Camera() {
		position[0] = 0.0f;
		position[1] = 0.0f;
	}
	Camera(int current[]) {
		position[0] = current[0];
		position[1] = current[1];
	}
	// Update camera position smoothly based on target destination
	void updatePosition(int destination[], float delta) {
		float t = delta / time_to_destination;
		if (t > 1.0f) { t = 1.0f; }

		for (int i = 0; i < 2; i++) {
			position[i] = smoothInterpolation(position[i], destination[i], t);
			if ((int)(position[i] + 0.5f) == destination[i]) { position[i] = destination[i]; }
		}
	}
	int get_position(int i) { return (int)(position[i] + 0.5f); }  // Round to nearest pixel
};

class Scene {
	Camera camera;
	int width = GameParameters::window_width;
	int height = GameParameters::window_height;

	float delta = 0.0f;
public:
	Scene() {
		camera = Camera();
	}
	void getPixelColour(int pixel[], int colour[]) {
		int actual_pixel[2];
		actual_pixel[0] = camera.get_position(0) - width / 2 + pixel[0];
		actual_pixel[1] = camera.get_position(1) - height / 2 + pixel[1];
		if (actual_pixel[0] % 50 == 0 && actual_pixel[1] % 50 == 0) {  // HACK
			colour[0] = colour[1] = colour[2] = 255;
		}
		else {
			colour[0] = colour[1] = colour[2] = 0;
		}
	}
	void updateCamera(float dt) {
		delta += dt;
		float value;
		if ((int)delta % 10 < 5) {
			value = (int)delta % 10 + (delta - (int)delta);
		}
		else {
			value = 5 - (int)delta % 10 - (delta - (int)delta);
		}
		int target[2];
		target[0] = value * value * 5;
		target[1] = value * value * 10;
		camera.updatePosition(target, dt);
	}
};

void drawImage(GamesEngineeringBase::Window &canvas, Scene &scene) {
	// Background -> Effects (if any) -> Hero -> Enemies -> Hero Projectiles -> Enemy Projectiles
	// Background
	for (int i = 0; i < GameParameters::window_height; i++) {
		for (int j = 0; j < GameParameters::window_width; j++) {
			int colour[3];
			int pixel[2];
			pixel[0] = j;
			pixel[1] = i;
			scene.getPixelColour(pixel, colour);
			canvas.draw(j, i, colour[0], colour[1], colour[3]);
		}
	}
}

int main() {
	GamesEngineeringBase::Window canvas;
	canvas.create(GameParameters::window_width, GameParameters::window_height, "Test");
	bool isRunning = true;

	GamesEngineeringBase::Timer timer;
	Scene scene = Scene();

	while (isRunning) {
		float delta = timer.dt();
		scene.updateCamera(delta);
		canvas.clear();
		drawImage(canvas, scene);
		canvas.present();
	}
	return 0;
}