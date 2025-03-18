#ifndef ROCK_H_INCLUDED
#define ROCK_H_INCLUDED

#include <cstdlib>
#include <ctime>

#include "enemy.h"

int rock_image;

// Rock attributes
struct Rock {
	int x, y;
	int dimension_x, dimension_y;
	int speed;
	bool active;

	Rock() {
		reset();
	}

	void reset() {
		x = rand() % 800 + 100;  // Random start position (within screen bounds)
		y = 600;                  // Start from the top of the screen
		dimension_x = 50;         // Width of the rock
		dimension_y = 50;         // Height of the rock
		speed = rand() % 5 + 5;  // Random falling speed (between 5 and 9)
		active = true;            // Rock starts active
	}

	void updatePosition(int background_speed) {
		y -= speed;  // Rock moves upward instead of downward
		x += background_speed;  // Move with background

		// If the rock moves off-screen, reset it
		if (y + dimension_y < 0) {
			reset();  // Reset the rock to the top
			active = true;  // Reactivate the rock
		}
	}


	bool checkCollision(Player &ground_player) {
		return active &&
			x < ground_player.x + ground_player.dimension_x &&
			x + dimension_x > ground_player.x &&
			y < ground_player.y + ground_player.dimension_y &&
			y + dimension_y > ground_player.y;
	}
};

// Falling rock object
Rock fallingRock1, fallingRock2, fallingRock3;

void updateRocksPosition(int background_speed, Player &ground_player) {
	// Update position and check for collisions for all three rocks
	if (fallingRock1.active) {
		fallingRock1.updatePosition(background_speed);
		if (fallingRock1.checkCollision(ground_player)) {
			reducePlayerHealth(1);
			fallingRock1.reset();  // Respawn the rock
		}
	}

	if (fallingRock2.active) {
		fallingRock2.updatePosition(background_speed);
		if (fallingRock2.checkCollision(ground_player)) {
			reducePlayerHealth(1);
			fallingRock2.reset();  // Respawn the rock
		}
	}

	if (fallingRock3.active) {
		fallingRock3.updatePosition(background_speed);
		if (fallingRock3.checkCollision(ground_player)) {
			reducePlayerHealth(1);
			fallingRock3.reset();  // Respawn the rock
		}
	}
}

void showRocks() {
	// Display all three rocks
	if (fallingRock1.active) {
		iShowImage(fallingRock1.x, fallingRock1.y, fallingRock1.dimension_x, fallingRock1.dimension_y, rock_image);
	}
	if (fallingRock2.active) {
		iShowImage(fallingRock2.x, fallingRock2.y, fallingRock2.dimension_x, fallingRock2.dimension_y, rock_image);
	}
	if (fallingRock3.active) {
		iShowImage(fallingRock3.x, fallingRock3.y, fallingRock3.dimension_x, fallingRock3.dimension_y, rock_image);
	}
}

#endif // ROCK_H_INCLUDED
