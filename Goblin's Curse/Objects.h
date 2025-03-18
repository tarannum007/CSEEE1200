#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

#include <cstdlib> // For rand()
extern int level;
int health_bar[12];
char health_bar_image[12][40] = { "level_one\\objects\\health_bar000.png", "level_one\\objects\\health_bar001.png", "level_one\\objects\\health_bar002.png",
"level_one\\objects\\health_bar003.png", "level_one\\objects\\health_bar004.png", "level_one\\objects\\health_bar005.png", "level_one\\objects\\health_bar006.png",
"level_one\\objects\\health_bar007.png", "level_one\\objects\\health_bar008.png", "level_one\\objects\\health_bar009.png","level_one\\objects\\health_bar010.png" };

/*level bar*/
int level_time = 0;      
int level_bar_index = 0; 
bool magic_key_active = false; // Key appears when bar is full
int level_bar[11];
// Level bar images (assuming you have 10 images)
char level_bar_image[11][35] = {"level_one\\objects\\level_bar00.png",
	"level_one\\objects\\level_bar0.png", "level_one\\objects\\level_bar1.png",
	"level_one\\objects\\level_bar2.png", "level_one\\objects\\level_bar3.png",
	"level_one\\objects\\level_bar4.png", "level_one\\objects\\level_bar5.png",
	"level_one\\objects\\level_bar6.png", "level_one\\objects\\level_bar7.png",
	"level_one\\objects\\level_bar8.png", "level_one\\objects\\level_bar9.png"
};


/*Enemy bomb variables.*/
int bomb_image;
int bomb_x = 1100;
int bomb_random = 3;
bool bomb_state = false;

bool active_shield = false;
int shield_count = 0;

int shield_bar[6];
char shield_bar_image[6][30] = { "level_one\\objects\\mpbar0.png", "level_one\\objects\\mpbar1.png", "level_one\\objects\\mpbar2.png", "level_one\\objects\\mpbar3.png", "level_one\\objects\\mpbar4.png", "level_one\\objects\\mpbar5.png" };

int key;
int magic_object_gained = 0;
int stone;

bool pause = false;
int pause_screen;
bool keyCollected = false;
int levelPage = 0;

int witch_image; 

int currentStoryImage2 = 0;
int level2_story[50];
char level2_story_images[16][50] = {
	"image\\s6.jpg", "image\\s7.jpg", "image\\s8.jpg", "image\\s9.jpg", "image\\s10.jpg",
	"image\\s11.jpg", "image\\s12.jpg", "image\\s13.jpg", "image\\s14.jpg", "image\\s15.jpg",
	"image\\s16.jpg", "image\\s17.jpg", "image\\s18.jpg", "image\\s19.jpg", "image\\s20.jpg",
	"image\\s21.jpg"
};
bool showingLevel2Story = false;

bool treasureGiftActive = false;
bool treasureCollected = false;
int winImage;  



/*__________________________________________________Structure for different objects.___________________________________________________*/

struct Objects
{
	int x, y;
	int dimension_x, dimension_y;
	int value;
	bool state;
	bool taken;
	int image;

	Objects(int _x, int _y, int _dimension_x, int _dimension_y, int _value, bool _state)
	{
		// Constructor for health gem and shield.
		x = _x;
		y = _y;
		dimension_x = _dimension_x;
		dimension_y = _dimension_y;
		value = _value;
		state = _state;
	}

	Objects(int _x, int _y, int _dimension_x, int _dimension_y, bool _state, bool _taken)
	{
		// Constructor for magic objects.
		x = _x;
		y = _y;
		dimension_x = _dimension_x;
		dimension_y = _dimension_y;
		state = _state;
		taken = _taken;
		image = -1;
	}

	void resetMagicObject(int _x, int _y, int _dimension_x, int _dimension_y, bool _state, bool _taken)
	{
		// Reset method for magic objects.
		x = _x;
		y = _y;
		dimension_x = _dimension_x;
		dimension_y = _dimension_y;
		state = _state;
		taken = _taken;
		image = -1;
	}
};

// Object declarations with adjusted positions for 1000x600 screen.
Objects health(1000, 370, 55, 65, 1, false);
Objects shield(1000, 370, 55, 65, 1, false);
Objects magic_key(700, 90, 55, 65, false, false); 
Objects witch(720, 80, 200, 180, false, false); 
Objects treasureGift(500, 90, 55, 65, false, false);









/*______________________________________Bomb showing condition and position changing codes.____________________________________________*/


// Function to randomly generate bomb position
void bombRandom()
{
	static int choose_call = 0;

	if (choose_call % 3 == 0)
	{
		bomb_random = rand() % 400;  // Random offset (optional)
	}

	choose_call++;

	if (choose_call >= 300)
	{
		choose_call = 0;
	}
}

// Function to move the bomb
void changeBombPosition()
{
	bomb_x -= 6; // Move bomb left

	if (bomb_x < -50) // If bomb goes off-screen (left)
	{
		bomb_x = 1000 + (rand() % 1000); // Respawn off-screen (right)
	}
}

/*_______________________________________________________Showing enemy bomb._______________________________________________________*/
void changeFire()
{
	if (fire_index < 19)
	{
		fire_index++;
	}
	else
	{
		fire_index = 0;
		explosion = false;
		exploded1 = false;
		exploded2 = false;
		exploded3 = false;
		exploded4 = false;
		exploded5 = false;
		exploded6 = false;
	}
}
void showExplosion(int x, int y)
{
	iShowImage(x, y, 140, 140, fire_image[fire_index]);

	if (fire_index >= 19)
	{
		explosion = false;
		exploded1 = false;
		exploded2 = false;
		exploded3 = false;
		exploded4 = false;
		exploded5 = false;
		exploded6 = false;
	}
}

void showBomb()
{
	iShowImage(bomb_x, 75, 60, 60, bomb_image);

	if (ground_player.visible && checkCollision(ground_player.x + ground_player.extended_x, ground_player.y + ground_player.extended_y + jumping_height, ground_player.dimension_x, ground_player.dimension_y, bomb_x, 75, 60, 70) && ground_player.condition < 4)
	{
		if (ground_player.health >= 20)
		{
			ground_player.health -= 20;
		}
		else
		{
			ground_player.health = 0;
		}

		explosion = true;
		explosion_x = bomb_x - 100;
		bomb_x = 1020 + rand() % 500;
	}

	if (explosion)
	{
		showExplosion(explosion_x, 70);
	}
}
/*_________________________________________________________showing health bar____________________________________________________________________*/
void drawHealthBar()
{
	int healthIndex = ground_player.health / 10;  // Divide health by 10 to get the appropriate index

	if (healthIndex > 12) {
		healthIndex = 12;  // Ensure the maximum health bar is not exceeded
	}

	iShowImage(20, 460, 200, 40, health_bar[healthIndex]);  // Draw the health bar image based on the health value
}
/*________________________________________________________________showing sheild and bar___________________________________________________________*/
void shieldPositionChange() {
	static int choose_call = 0;

	// Only spawn the shield if the shield bar is NOT full
	if (level == 1 && shield_count < 5) {
		if (!shield.state && choose_call % 500 == 0) {  // Respawn shield after some time
			shield.x = rand() % (1000 - shield.dimension_x);
			shield.y = 50 + rand() % 70;
			shield.state = true;
		}
	}

	choose_call++;
	if (choose_call >= 2000) {
		choose_call = 0;
	}
}


void sheild() {
	// Draw the shield bar based on the current shield count
	iShowImage(20, 500, 200, 40, shield_bar[shield_count]);  // Show the shield bar image

	if (shield.state) {
		// Show shield image if it is not collected yet
		iShowImage(shield.x, shield.y, shield.dimension_x, shield.dimension_y, shield.image);

		// Check if player collects the shield
		if (checkCollision(ground_player.x + ground_player.extended_x, ground_player.y + ground_player.extended_y + jumping_height,
			80, 130, shield.x, shield.y, shield.dimension_x, shield.dimension_y)) {

			// Increase shield count but limit it to max (5)
			if (shield_count < 7) {
				shield_count++;
			}

			shield.state = false;  // Hide shield after collection
		}
	}
	// Ensure that shield bar stays visible even after being full (shield_count >= 5)
	if (shield_count >= 6) {
		
		iShowImage(20, 500, 200, 40, shield_bar[5]);  // Full shield bar is shown
	}
	
}



/*_______________________________________________________level bar progress by time____________________________________________________________*/
void increaseLevelTime()
{
	if (level_time < 300)  // Max level time
	{
		level_time++;  // Increase the game time

		// Increase level bar progress every 20 seconds
		if (level_time % 20 == 0 && level_bar_index < 10)
		{
			level_bar_index++;
		}
	}

	// Activate magic key and witch when level bar is full
	if (level_bar_index == 10)
	{
		magic_key_active = true;
		magic_key.state = true;

		witch.state = true; // Activate the witch when the level bar is full
	}
}



void draw_levelbar()
{
	if (level_bar_index < 10)  // Show normal level bar
	{
		iShowImage(20, 540, 200, 40, level_bar[level_bar_index]);
	}
	else if (level_bar_index == 10)  // Show full level bar
	{
		iShowImage(20, 540, 200, 40, level_bar[10]);
	}
}










/*_____________________________________________________________showing map_____________________________________________________________________*/
void showWitch() {
	if (levelPage == 1 && level_bar_index == 10) {  // Show only in Level 1
		witch.state = true;
	}

	if (levelPage == 1 && witch.state) {
		iShowImage(witch.x, witch.y, witch.dimension_x, witch.dimension_y, witch_image);
	}
}

void map() {
	if (magic_key_active && !magic_key.taken && levelPage == 1) {
		magic_key.state = true;
		iShowImage(magic_key.x, magic_key.y, magic_key.dimension_x, magic_key.dimension_y, key);

		// Check if player collects the magic key
		if (checkCollision(ground_player.x + ground_player.extended_x,
			ground_player.y + ground_player.extended_y + jumping_height,
			80, 130, magic_key.x, magic_key.y, magic_key.dimension_x, magic_key.dimension_y)) {

			magic_key.state = false;
			magic_object_gained++;
			magic_key.taken = true;
		}
	}

	// Show witch when the key appears
	showWitch();
	
}




/*__________________________________________________________When the Player Collects the Key________________________________________________________*/
void showLevel2Story()
{
	if (currentStoryImage2 < 16)  // Ensure it doesn’t go past 16 images
	{
		iShowImage(0, 0, 1000, 600, level2_story[currentStoryImage2]);
	}
	else  // If all images are shown, move to Level 2
	{
		showingLevel2Story = false;  // Stop showing story
		levelPage = 2;  // Start Level 2
	}
}


void resetLevel2()
{
	ground_player.x = 100;  // Reset player position for Level 2
	ground_player.y = 80;

	// Reset enemies for Level 2
	enemy_one1.x = 1020 + rand() % 200;
	enemy_one2.x = 1020 + rand() % 200;
	enemy_one3.x = 1020 + rand() % 200;

	keyCollected = false;  // Reset key status
	level_time = 0;  // Reset timer for new level
	level_bar_index = 0; // Reset level progress bar
	ground_player.health = 100;
	magic_key.state = false;  // Ensure key is hidden in Level 2
	magic_key.taken = false;  // Reset taken status (if needed for future levels)

	
}

void goToNextLevel()
{
	if (keyCollected)
	{
		levelPage = 0;  // Pause the game
		showingLevel2Story = true;  // Start Level 2 storyline
		currentStoryImage2 = 0;  // Reset to the first image
		keyCollected = false;  // Reset key status
		witch.state = false;  // Hide the witch

		PlaySound("level1Music.wav", NULL, SND_LOOP | SND_ASYNC);  // Change music
	}
}

void checkKeyCollection()
{
	if (magic_key_active)  // Only check when key is active
	{
		if (checkCollision(magic_key.x, magic_key.y, 50, 50,  // Adjust size if needed
			ground_player.x + ground_player.extended_x, ground_player.y + ground_player.extended_y,
			ground_player.dimension_x, ground_player.dimension_y))
		{
			keyCollected = true;
			magic_key_active = false;  // Hide the key
			goToNextLevel();  // Call function to change level
		}
	}
}

void showTreasureGift()
{
	if (levelPage == 2 && level_bar_index == 10) // Only in Level 2 when bar is full
	{
		treasureGiftActive = true;
		treasureGift.state = true;
		iShowImage(treasureGift.x, treasureGift.y, treasureGift.dimension_x, treasureGift.dimension_y, stone); // Replace 'key' with treasure image
	}
}

void checkTreasureCollection()
{
	if (treasureGiftActive && checkCollision(ground_player.x + ground_player.extended_x,
		ground_player.y + ground_player.extended_y, ground_player.dimension_x, ground_player.dimension_y,
		treasureGift.x, treasureGift.y, treasureGift.dimension_x, treasureGift.dimension_y))
	{
		treasureCollected = true;
		treasureGiftActive = false;
		treasureGift.state = false;
	}
}

void showWinScreen()
{
	if (treasureCollected) // Show win screen if treasure was collected
	{
		iShowImage(0, 0, 1000, 600, winImage);
	}
}







#endif // OBJECTS_H_INCLUDED