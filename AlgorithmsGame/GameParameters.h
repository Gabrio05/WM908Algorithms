#ifndef GAMEPARAMETERS
#define GAMEPARAMETERS

// _DEBUG is defined by VS automatically if in debug

namespace GameParameters {

	constexpr int window_width = 1024;
	constexpr int window_height = 768;

	namespace Camera {
		constexpr float time_to_destination = 0.3f;  // secs
	}

	namespace Player {
		constexpr int health = 100;
		constexpr float speed = 100.0f;  // pixels per second
		constexpr char filename[] = "PlaneResources/L.png";
		constexpr float environment_collision[2][2] { {-5.0f, -10.0f}, {5.0f, 10.0f} };  // Should be smaller than sprite and feel fair
		constexpr int attack1_strength = 20;
		constexpr float attack1_cooldown = 0.5f;
		constexpr float global_invulnerability = 0.4f;  // The player can only be damaged every X secs
		constexpr float invulnerability_on_hit_per_hp = 0.05f;  // Time for which to decrease shield by 1HP
		constexpr int shield_multiplier = 2;  // Invulnerability allowed (1 = damage, 2 = twice damage, etc)
	}

	namespace updateData {
		constexpr int inputs_to_check[] { 0x25, 0x26, 0x27, 0x28 };
		constexpr int inputs_to_check_length = 4;
	}

	namespace Background {
		constexpr int number_of_tiles = 24;
		constexpr int tile_size[2] = { 32, 32 };
		constexpr int filename_size = 17;
		constexpr char filenames[][filename_size] { "Resources/00.png", "Resources/01.png", "Resources/02.png", "Resources/03.png", 
												    "Resources/04.png", "Resources/05.png", "Resources/06.png", "Resources/07.png", 
												    "Resources/08.png", "Resources/09.png", "Resources/10.png", "Resources/11.png", 
													"Resources/12.png", "Resources/13.png", "Resources/14.png", "Resources/15.png", 
													"Resources/16.png", "Resources/17.png", "Resources/18.png", "Resources/19.png", 
													"Resources/20.png", "Resources/21.png", "Resources/22.png", "Resources/23.png" };
		constexpr int map_size[2] { 42, 42 };
		constexpr char map_filename[] = "Resources/tiles.txt";
		constexpr float environment_collision[2][2] { {-15.0f, -15.0f}, {15.0f, 15.0f} };  // HACK
	}

	namespace Enemies {
		constexpr int unique_enemies = 1;
		constexpr int max_enemy_count = 1024;
		constexpr float spawn_time_per_chunk_level_1[] = {2.0f, 1.75f, 1.5f, 1.25f, 1.0f, 3.0f, 1.5f, 1.0f, 0.75f, 0.5f, 0.25f, 0.1f};
		constexpr float chunk_time_level_1 = 15.0f;  // Determines, in secs, when to move to next index in spawn time array
		constexpr int spawn_time_array_length_level_1 = 12;
	}

	namespace EnemyPlane {
		constexpr float environment_collision[2][2] { {-5.0f, -10.0f}, {5.0f, 10.0f} };
		constexpr float speed = 75.0f;  // Pixels per second
		constexpr char filename[] = "PlaneResources/L2.png";
		constexpr int attack_damage = 20;
		constexpr int health = 100;
	}

}

#endif
