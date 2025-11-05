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
		constexpr char filename[] = "Planes/Fighter_type_A1.png";
		constexpr float environment_collision[2][2] { {-4.0f, -30.0f}, {4.0f, 30.0f} };  // Should be smaller than sprite and feel fair
		constexpr int attack1_strength = 20;  // Continuous attack, does not require a button press
		constexpr float attack1_cooldown = 0.5f;
		constexpr int attack2_strength = 100;  // AoE attack around the top N enemies & around player
		constexpr float attack2_cooldown = 10.0f;
		constexpr int attack2_enemies_to_attack = 5;
		constexpr float attack2_aoe_radius = 50.0f;
		constexpr int attack3_strength = 250;  // Flare that fires in last direction the player was pointing in
		constexpr float attack3_cooldown = 15.0f;
		constexpr float global_invulnerability = 0.4f;  // The player can only be damaged every X secs
		constexpr float invulnerability_on_hit_per_hp = 0.05f;  // Time for which to decrease shield by 1HP
		constexpr int shield_multiplier = 2;  // Invulnerability allowed (1 = damage, 2 = twice damage, etc)
	}

	namespace updateData {
		constexpr int inputs_to_check_length = 7;
		constexpr int inputs_to_check[inputs_to_check_length] { 0x25, 0x26, 0x27, 0x28, 'Z', 'X', 'C'};
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
		constexpr int unique_enemies = 4;
		constexpr int max_enemy_count = 1024;  // Ignores spawns after this

		// For each enemy, gives the spawn time for each "chunk"
		// Chunk time is determined by the variable below
		constexpr float global_spawn_time_per_chunk_level_1[][12] = { { 2.0f, 1.75f, 1.5f, 1.25f, 1.0f, 3.0f, 1.5f, 1.0f, 0.75f, 0.5f, 0.25f, 0.1f },
																	  { 20.0f, 3.0f, 3.0f, 2.5f, 2.0f, 5.0f, 2.5f, 1.5f, 1.25f, 1.0f, 0.75f, 0.5f },
																	  { 45.0f, 5.0f, 5.0f, 3.0f, 2.0f, 1.0f }, 
																	  { 75.0f, 300.0f } };
		constexpr int global_spawn_time_array_length_level_1[] = { 12, 12, 6, 2 };
		constexpr float global_chunk_time_level_1[] = { 15.0f, 15.0f, 30.0f, 100.0f };

		constexpr int health_for_enemies[] = { 40, 80, 25, 1000 };
		constexpr int attack_damage_for_enemies[] = { 20, 20, 30, 50 };
		constexpr float speed_for_enemies[] = { 60.0f, 90.0f, 150.0f, 99.0f };

		constexpr float environment_collision[unique_enemies][2][2]{ { {-3.0f, -7.0f}, {3.0f, 7.0f} }, 
																	 { {-3.0f, -7.0f}, {3.0f, 7.0f} }, 
																     { {-3.0f, -7.0f}, {3.0f, 7.0f} }, 
																	 { {-4.0f, -30.0f}, {4.0f, 30.0f} } };

		constexpr char filename1[] = "Planes/GreenPlaneSingle.png";
		constexpr char filename2[] = "Planes/RedPlaneSingle.png";
		constexpr char filename3[] = "Planes/PurplePlaneSingle.png";
		constexpr char filename4[] = "Planes/Fighter_type_A2.png";
	}

	namespace Projectiles {
		constexpr int unique_friendly_sprites = 5;
		constexpr int unique_enemy_sprites = 3;
		constexpr char filename1[] = "Planes/Explosion1.png";
		constexpr char filename2[] = "Planes/Explosion2.png";
		constexpr char filename3[] = "Planes/Explosion3.png";
		constexpr char filename4[] = "Planes/Explosion4.png";
		constexpr char filename5[] = "Planes/Explosion5.png";
		constexpr char filename1e[] = "Planes/Bullet1.png";
		constexpr char filename2e[] = "Planes/Bullet2.png";
		constexpr char filename3e[] = "Planes/Bullet3.png";

		constexpr float enemy_delay = 4.0f;
		constexpr float enemy_speed = 95.0f;
		constexpr float friendly_speed = 65.0f;
		constexpr float friendly_lifespan = 4.0f;  // Automatically gets used up after this
		constexpr float max_enemy_distance_x = 300.0f;
		constexpr float max_enemy_distance_y = 200.0f;
		

		constexpr int max_projectile_count = 64;  // Ignores enemy projectile throws, replaces enemy projectiles with friendly ones
		constexpr float radius = 4.0f;
	}
}

#endif
