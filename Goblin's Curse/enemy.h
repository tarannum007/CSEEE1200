#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "Player.h"
#include"Collision.h"
extern bool pause;
int bat_image_ids[9];
int bullet_image_id;


/*__________________________________________________location of level1 enemy_____________________________________________________________*/
char enemy1_image_location[][39] = { "level_one\\enemy\\enemy_1\\WALK_000.png", "level_one\\enemy\\enemy_1\\WALK_001.png", "level_one\\enemy\\enemy_1\\WALK_002.png",
"level_one\\enemy\\enemy_1\\WALK_003.png", "level_one\\enemy\\enemy_1\\WALK_004.png", "level_one\\enemy\\enemy_1\\WALK_005.png", "level_one\\enemy\\enemy_1\\WALK_006.png",
"level_one\\enemy\\enemy_1\\WALK_007.png", "level_one\\enemy\\enemy_1\\WALK_008.png","level_one\\enemy\\enemy_1\\WALK_009.png" };

char enemy2_image_location[][39] = { "level_one\\enemy\\enemy_2\\WALK_000.png", "level_one\\enemy\\enemy_2\\WALK_001.png", "level_one\\enemy\\enemy_2\\WALK_002.png",
"level_one\\enemy\\enemy_2\\WALK_003.png", "level_one\\enemy\\enemy_2\\WALK_004.png", "level_one\\enemy\\enemy_2\\WALK_005.png", "level_one\\enemy\\enemy_2\\WALK_006.png",
"level_one\\enemy\\enemy_2\\WALK_007.png", "level_one\\enemy\\enemy_2\\WALK_008.png","level_one\\enemy\\enemy_1\\WALK_009.png" };

char enemy3_image_location[][39] = { "level_one\\enemy\\enemy_3\\WALK_000.png", "level_one\\enemy\\enemy_3\\WALK_001.png", "level_one\\enemy\\enemy_3\\WALK_002.png",
"level_one\\enemy\\enemy_3\\WALK_003.png", "level_one\\enemy\\enemy_3\\WALK_004.png", "level_one\\enemy\\enemy_3\\WALK_005.png", "level_one\\enemy\\enemy_3\\WALK_006.png",
"level_one\\enemy\\enemy_3\\WALK_007.png", "level_one\\enemy\\enemy_3\\WALK_008.png","level_one\\enemy\\enemy_1\\WALK_009.png" };

char bat_image_location[][40] = {
	"level_two\\Bat1.png", "level_two\\Bat2.png", "level_two\\Bat3.png",
	"level_two\\Bat4.png", "level_two\\Bat5.png", "level_two\\Bat6.png",
	"level_two\\Bat7.png", "level_two\\Bat8.png", "level_two\\Bat9.png"
};

/*___________________________________________________Structure for level one enemy.____________________________________________________*/
struct EnemyBullet {
	int x, y;       // Position
	int speed;      // Speed of bullet
	bool active;    // Is the bullet active

	EnemyBullet() : x(0), y(0), speed(6), active(false) {}

	void fire(int startX, int startY) {
		x = startX;
		y = startY;
		active = true;
	}

	void move() {
		if (active) {
			x -= speed; // Move left towards the player
			if (x < -50) active = false; // Deactivate when off screen
		}
	}
};

// Enemy bullets array
EnemyBullet enemy_bullets[5]; // Max 5 bullets at a time

struct Enemy {
	int x, y;
	bool state;
	int image[20];
	int value;
	int index;
	int fireCooldown; // Cooldown for shooting bullets

	Enemy(int _x, int _y, bool _state, int _value, int _index)
		: x(_x), y(_y), state(_state), value(_value), index(_index), fireCooldown(0) {}

	void shootBullet() {
		if (x <= 600 && fireCooldown == 0) {  // Only fire when enemy reaches x <= 700
			for (int i = 0; i < 5; i++) {
				if (!enemy_bullets[i].active) {
					enemy_bullets[i].fire(x, y + 30);
					fireCooldown = 600; // Delay before next shot
					break;
				}
			}
		}
		else if (fireCooldown > 0) {
			fireCooldown--;
		}
	}

};

// Declare objects outside the struct
Enemy enemy_one1(1000, 80, true, 10, 0);
Enemy enemy_one2(900, 80, true, 10, 0);
Enemy enemy_one3(800, 80, true, 10, 0);


// Adjusted enemy positions for 1000x600 screen size.

/* __________________________________ Bat Enemy Structure ________________________________ */
struct BatEnemy {
	int x, y;       // Position
	int index;      // Animation frame index
	int health;     // Health points
	bool state;
	int img[20];// If active on screen

	// Constructor
	BatEnemy(int _x, int _y, bool _state, int _health, int _index)
		: x(_x), y(_y), state(_state), health(_health), index(_index) {}

	// Reset function
	void reset(int _x, int _y, bool _state, int _health, int _index) {
		x = _x;
		y = _y;
		state = _state;
		health = _health;
		index = _index;
	}
};

// Declare bat enemy
BatEnemy bat(1200, 400, true, 100, 0);





/*_____________________________________________________Showing enemy for level one.____________________________________________________*/

void showEnemyOne()
{
	iShowImage(enemy_one1.x, enemy_one1.y, 190, 160, enemy_one1.image[enemy_one1.index]);
	iShowImage(enemy_one2.x, enemy_one2.y, 190, 160, enemy_one2.image[enemy_one2.index]);
	iShowImage(enemy_one3.x, enemy_one3.y, 190, 160, enemy_one3.image[enemy_one3.index]);
	enemy_one1.shootBullet();
	enemy_one2.shootBullet();
	enemy_one3.shootBullet();

	if (enemy_one1.x <= 750)
		enemy_one1.state = true;
	else
		enemy_one1.state = false;

	if (enemy_one2.x <= 750)
		enemy_one2.state = true;
	else
		enemy_one2.state = false;

	if (enemy_one3.x <= 750)
		enemy_one3.state = true;
	else
		enemy_one3.state = false;
}

void changeEnemyPosition()
{
	static int choose_call = 0;

	if (choose_call % 1 == 0)  // Always true, so runs every frame
	{
		enemy_one1.x -= 2;
		if (enemy_one1.x <= -100)
			enemy_one1.x = 1000;
	}

	if (choose_call % 2 == 0)  // Every second frame
	{
		enemy_one2.x -= 3;
		if (enemy_one2.x <= -100)
			enemy_one2.x = 1000;
	}

	if (choose_call % 3 == 0)  // Every third frame (Fixed: changed from 2 to 3)
	{
		enemy_one3.x -= 5;
		if (enemy_one3.x <= -100)
			enemy_one3.x = 1000;
	}

	// Animation Frame Updates
	if (choose_call % 4 == 0)
	{
		enemy_one2.index++;
		if (enemy_one2.index > 8)
			enemy_one2.index = 0;
	}

	if (choose_call % 5 == 0)
	{
		enemy_one1.index++;
		if (enemy_one1.index > 8)
			enemy_one1.index = 0;
	}

	if (choose_call % 6 == 0)
	{
		enemy_one3.index++;
		if (enemy_one3.index > 8)
			enemy_one3.index = 0;
	}

	choose_call++;

	if (choose_call >= 1000)
		choose_call = 0;
 }

void reducePlayerHealth(int damage) {
	if (ground_player.health > damage) {
		ground_player.health -= damage;
	}
	else {
		ground_player.health = 0;
	}
}


void playerEnemyCollision() {
	/* Checking collision with enemy_one1 */
	if (checkCollision(enemy_one1.x, enemy_one1.y, 190, 135,
		ground_player.x + ground_player.extended_x, ground_player.y + ground_player.extended_y,
		ground_player.dimension_x, ground_player.dimension_y))
	{
		if (ground_player.condition < 4 || ground_player.condition > 7) { // Ensure player is not jumping or running
			reducePlayerHealth(10); // Call to reduce health, use the function to handle health
			enemy_one1.state = false;
			enemy_one1.x = 1020 + rand() % 200;
		}
	}

	/* Checking collision with enemy_one2 */
	if (checkCollision(enemy_one2.x, enemy_one2.y, 180, 135,
		ground_player.x + ground_player.extended_x, ground_player.y + ground_player.extended_y,
		ground_player.dimension_x, ground_player.dimension_y))
	{
		if (ground_player.condition < 4 || ground_player.condition > 7) {
			reducePlayerHealth(10); // Call to reduce health
			enemy_one2.state = false;
			enemy_one2.x = 1020 + rand() % 200;
		}
	}

	/* Checking collision with enemy_one3 */
	if (checkCollision(enemy_one3.x, enemy_one3.y, 180, 135,
		ground_player.x + ground_player.extended_x, ground_player.y + ground_player.extended_y,
		ground_player.dimension_x, ground_player.dimension_y))
	{
		if (ground_player.condition < 4 || ground_player.condition > 7) {
			reducePlayerHealth(10); // Call to reduce health
			enemy_one3.state = false;
			enemy_one3.x = 1020 + rand() % 200;
		}
	}
}
void showEnemyBullets() {
	for (int i = 0; i < 5; i++) {
		if (enemy_bullets[i].active) {
			iShowImage(enemy_bullets[i].x, enemy_bullets[i].y+50, 70, 70, bullet_image_id);
		}
	}
}

// Move Bullets
void moveEnemyBullets() {
	for (int i = 0; i < 5; i++) {
		enemy_bullets[i].move();
	}
}

// Bullet Collision with Player
void enemyBulletCollision() {
	for (int i = 0; i < 5; i++) {
		if (enemy_bullets[i].active && checkCollision(enemy_bullets[i].x, enemy_bullets[i].y, 20, 10,
			ground_player.x, ground_player.y, ground_player.dimension_x, ground_player.dimension_y)) {
			reducePlayerHealth(1); // Reduce player health
			enemy_bullets[i].active = false; // Deactivate bullet
		}
	}
}
// Show the bat
void showBat() {
	if (!pause && bat.state) {
		iShowImage(bat.x, bat.y, 150, 120, bat.img[bat.index]);

	}
}

// Move the bat
void moveBat() {
	if (pause) return;

	if (bat.state) {
		bat.x -= 4;
		if (bat.x < -100) {
			bat.reset(2000 + rand() % 500, 350 + rand() % 100, true, 100, 0);
		}

		// Update animation frame
		bat.index = (bat.index + 1) % 9;
	}
}






   #endif // !ENEMY_H_INCLUDED

