#ifndef FIRE_H_INCLUDED
#define FIRE_H_INCLUDED
#include <cstdlib>
#include <cmath>   

#include "player.h"
#include "enemy.h"


bool fire = false;
int bullet_image;
int bullet_back_image;
int bullet_x = ground_player.x + 110;
int bullet_back_x = ground_player.x;
int powered_bullet_image;
int powered_back_bullet_image;

#define playerX ground_player.x
#define playerY ground_player.y

#define batX bat.x
#define batY bat.y

int batAttackImage;



const int screenWidth = 1000;
const int screenHeight = 600;

struct Projectile {
	float x, y;
	float dx, dy;
	int speed;
	bool active;
};

Projectile fireball;

struct BatFireProjectile {
	float x, y;
	float dx, dy;
	int speed;
	bool active;
};

BatFireProjectile batFireball;



/*__________________________________________________Showing player's firing._______________________________________________________*/
void fireBullet() {
	/* Choose bullet type (normal or powered) */
	bool isPoweredBullet = (shield_count >= 5);

	int bulletWidth = isPoweredBullet ? 100: 40; // Increase size if powered
	int bulletHeight = isPoweredBullet ? 100: 20;

	int current_bullet_image = isPoweredBullet ? powered_bullet_image : bullet_image;
	int current_bullet_back_image = isPoweredBullet ? powered_back_bullet_image : bullet_back_image;

	/* Firing from front */
	if (fire && (ground_player.condition == 0 || ground_player.condition == 2 || ground_player.condition == 4 || ground_player.condition == 6)) {
		iShowImage(bullet_x, ground_player.y + jumping_height + 80, bulletWidth, bulletHeight, current_bullet_image);

		if (!pause) {
			bullet_x += 5; // Bullet speed
		}

		/* Check collisions for all enemies */
		bool hitEnemy = false;
		if (enemy_one1.state && checkCollision(enemy_one1.x, enemy_one1.y, 190, 135, bullet_x, ground_player.y, bulletWidth, bulletHeight)) {
			ground_player.score += 10;
			enemy_one1.x = 1020 + rand() % 200;
			hitEnemy = true;
		}

		if (enemy_one2.state && checkCollision(enemy_one2.x, enemy_one2.y, 180, 135, bullet_x, ground_player.y, bulletWidth, bulletHeight)) {
			ground_player.score += 10;
			enemy_one2.x = 1020 + rand() % 200;
			hitEnemy = true;
		}

		if (enemy_one3.state && checkCollision(enemy_one3.x, enemy_one3.y, 180, 135, bullet_x, ground_player.y, bulletWidth, bulletHeight)) {
			ground_player.score += 10;
			enemy_one3.x = 1020 + rand() % 200;
			hitEnemy = true;
		}

		if (hitEnemy && !isPoweredBullet) {
			fire = false;
			bullet_x = ground_player.x + 110;
		}

		/* Reset bullet when it leaves the screen */
		if (bullet_x > 950) {
			fire = false;
			bullet_x = ground_player.x + 110;
		}
	}

	/* Firing from back */
	if (fire && (ground_player.condition == 1 || ground_player.condition == 3 || ground_player.condition == 5 || ground_player.condition == 7)) {
		iShowImage(bullet_back_x, ground_player.y + jumping_height + 100, bulletWidth, bulletHeight, current_bullet_back_image);

		if (!pause) {
			bullet_back_x -= 5;
		}

		bool hitEnemyBack = false;
		if (enemy_one1.state && checkCollision(enemy_one1.x, enemy_one1.y, 190, 135, bullet_back_x, ground_player.y, bulletWidth, bulletHeight)) {
			ground_player.score += 10;
			enemy_one1.x = 1020 + rand() % 200;
			hitEnemyBack = true;
		}

		if (enemy_one2.state && checkCollision(enemy_one2.x, enemy_one2.y, 180, 135, bullet_back_x, ground_player.y, bulletWidth, bulletHeight)) {
			ground_player.score += 10;
			enemy_one2.x = 1020 + rand() % 200;
			hitEnemyBack = true;
		}

		if (enemy_one3.state && checkCollision(enemy_one3.x, enemy_one3.y, 180, 135, bullet_back_x, ground_player.y, bulletWidth, bulletHeight)) {
			ground_player.score += 10;
			enemy_one3.x = 1020 + rand() % 200;
			hitEnemyBack = true;
		}

		if (hitEnemyBack && !isPoweredBullet) {
			fire = false;
			bullet_back_x = ground_player.x - 110;
		}

		/* Reset bullet when it leaves the screen */
		if (bullet_back_x < -20) {
			fire = false;
			bullet_back_x = ground_player.x;
		}
	}
}


/*__________________________________________________ Bat Fire Attack Logic _______________________________________________________*/

// Bat fireball logic
void drawBatFireProjectile() {
	if (batFireball.active) {
		iShowImage(batFireball.x, batFireball.y, 50, 50, batAttackImage);
	}
}

void shootFireFromBat() {
	if (!batFireball.active) {
		batFireball.x = batX;
		batFireball.y = batY;
		batFireball.speed = 15;
		batFireball.active = true;

		float deltaX = playerX - batX;
		float deltaY = playerY - batY;
		float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

		if (distance < 1.0f) distance = 1.0f;  // Prevent division by zero

		// Normalize direction and apply speed
		batFireball.dx = (deltaX / distance) * batFireball.speed;
		batFireball.dy = (deltaY / distance) * batFireball.speed;
	}
}
void playerBatFireballCollision() {
	if (batFireball.active && checkCollision(
		batFireball.x, batFireball.y, 30, 30,  // Fireball dimensions
		ground_player.x + ground_player.extended_x,
		ground_player.y + ground_player.extended_y,
		ground_player.dimension_x, ground_player.dimension_y))
	{
		reducePlayerHealth(2);  // Fireball deals 10 damage
		batFireball.active = false;  // Fireball disappears on impact
	}
}
void updateBatFireProjectile() {
	if (batFireball.active) {
		batFireball.x += batFireball.dx;
		batFireball.y += batFireball.dy;

		// Check if fireball goes out of screen
		if (batFireball.x < 0 || batFireball.x > screenWidth ||
			batFireball.y < 0 || batFireball.y > screenHeight)
		{
			batFireball.active = false;
		}

		// **Check collision with player**
		playerBatFireballCollision();
	}
}


#endif 