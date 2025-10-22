#ifndef GAMEPARAMETERS
#define GAMEPARAMETERS

namespace GameParameters {

	constexpr int window_width = 1024;
	constexpr int window_height = 768;

	namespace Camera {
		constexpr float time_to_destination = 0.2f;  // secs
	}

	namespace Player {
		constexpr float speed = 1000.0f;  // pixels per second
		constexpr char fileName[] = "PlaneResources/L.png";
	}

	namespace UpdateData {
		constexpr int inputs_to_check[] = { 0x25, 0x26, 0x27, 0x28 };
		constexpr int inputs_to_check_length = 4;
	}

}

#endif
