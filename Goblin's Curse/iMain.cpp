#include "iGraphics.h"
#include "enemy.h"
#include "Objects.h"
#include "Player.h"
#include "Collision.h"
#include"fire.h"
#include"gameover.h"
#include"rock.h"


void drawMenupage();

void drawStartpage();
void startButtonClickHandler();

void drawHelppage();
void drawLevel1();
void drawLevel2();
void helpButtonClickHandler();

void drawCreditpage();
void creditButtonClickHandler();
void updateBackground2();

int level = 1;
int player_distance = 0;
int startPageImage;
int menuPage = 1;
int startButtonClick = 0;
int startPage = 0;

int helpButtonClick = 0;
int helpPage = 0;

int creditButtonClick = 0;
int creditPage = 0;

bool musicOn = true;
bool buttonOn = true;

int menuBackgroundID;
int helpBackgroundID;
int creditBackgroundID;

//for level1
int backgroundX = 0;  // Initial background position
int backgroundSpeed = 1;  // Speed at which the background moves
int levelBackgroundID;  // ID for the background image

//for level 2
int backgroundX2 = 0;
int backgroundSpeed2 = 1;

int levelBackgroundID2;

// Storyline image tracking
int currentStoryImage = 0;  // Tracks which story image is currently displayed
int storyImages[5]; // Array to hold story image IDs
int pauseButtonImage;

//int levelPage = 0; // 0 means level is not active


int timer_bg, timer_bg1, timer_enemy, timer_bomb, timer_coin, timer_jump, timer_fire, timer_sheild, timer_level, timer_rock, timer_bat, timer_battack, timer_stair, timer_goblin, timer_thirty;




//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

void iDraw()
{
	iClear();

	if (ground_player.health <= 0) {
		gameOver();  // Call gameOver to handle game-over state
	}
	if (game_over) {
		
		iShowImage(0, 0, 1000, 600, game_over_image);  // Show the game-over image
		return;  // Stop drawing anything else (game is over)
	}
	if (showingLevel2Story)  // If the story for Level 2 is active
	{
		showLevel2Story();  // Display the storyline images
	}

	// Draw the game over image if the game_over flag is true
	
	if (menuPage == 1)
	{
		drawMenupage();
	}
	else if (startPage==1)
	{
		drawStartpage();
	}
	else if (helpPage)
	{
		drawHelppage();
	}
	else if (creditPage == 1)
	{
	   drawCreditpage();
	}
	else if (levelPage == 1)  // When level 1 is active
	{
		drawLevel1();
	}
	else if (levelPage == 2)  // When level 2 is active
	{
		drawLevel2();
		
	}

	
	
	

}





/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void iMouseMove(int mx, int my)
{
	
}
//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{
	
}

void iMouse(int button, int state, int mx, int my)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//printf("x=%d y=%d", mx, my);


		if (menuPage == 1 && (mx >= 407 && mx <= 581) && (my >= 303 && my <= 348))
		{
			startButtonClickHandler();
		}

		else if (menuPage == 1 && (mx >= 407 && mx <= 583) && (my >= 209 && my <= 254))
		{
			helpButtonClickHandler();
		}
		else if (menuPage == 1 && (mx >= 407 && mx <= 583) && (my >= 116 && my <= 166))
		{
			creditButtonClickHandler();
		}

		else if (menuPage == 1 && (mx >= 407 && mx <= 583) && (my >= 25 && my <= 70))
		{
			exit(0);
		}

		else if (game_over) {

			// Menu button (corrected coordinates)
			if (mx >= 217 && mx <= 422 && my >= 147 && my <= 190) {  // Updated coordinates for Menu button
				game_over = false;  // Reset the game over flag
				menuPage = 1;
				// Reset Player
				ground_player.health = 100;
				ground_player.score = 0;
				ground_player.x = 100;
				ground_player.y = 80;

				// Reset movement/jump conditions
				jump = false;
				jumping = false;
				jumping_height = 0;

				// Reset shield and power-ups
				shield_count = 0;
				active_shield = false;
				shield.state = false;

				// Reset bullets/fire state
				fire = false;
				bullet_x = ground_player.x + 110;
				bullet_back_x = ground_player.x;

				// Reset enemies
				enemy_one1.x = 1020 + rand() % 200;
				enemy_one2.x = 1020 + rand() % 200;
				enemy_one3.x = 1020 + rand() % 200;

				// Reset level bar and key
				level_bar_index = 0;
				magic_key_active = false;
				magic_key.state = false;
				witch.state = false;

				// Make sure the key doesn't appear at the start
				magic_key.resetMagicObject(900, 90, 55, 65, false, false);
				witch.resetMagicObject(950, 100, 80, 120, false, false);
				fallingRock1.reset();
				fallingRock2.reset();
				fallingRock3.reset();
				bat.reset(1300, 450, true, 100, 0);
				treasureGiftActive = false;   // Reset treasure gift state
				treasureCollected = false;    // Reset treasure collection
				treasureGift.state = false;   // Hide treasure


			}

			// Replay button (corrected coordinates)
			if (mx >= 586 && mx <= 790 && my >= 150 && my <= 190) {  // Replay button click
				game_over = false;

				// Restart the correct level (1 or 2)
				if (level == 2) {
					resetLevel2();  // Reset Level 2 (ensure this method resets all level-specific variables)
				}
				else {
					level = 1;  // Start from level 1
				}

				// Reset Player
				ground_player.health = 100;
				ground_player.score = 0;
				ground_player.x = 100;
				ground_player.y = 80;

				// Reset movement/jump conditions
				jump = false;
				jumping = false;
				jumping_height = 0;

				// Reset shield and power-ups
				shield_count = 0;
				active_shield = false;
				shield.state = false;

				// Reset bullets/fire state
				fire = false;
				bullet_x = ground_player.x + 110;
				bullet_back_x = ground_player.x;

				// Reset enemies
				enemy_one1.x = 1020 + rand() % 200;
				enemy_one2.x = 1020 + rand() % 200;
				enemy_one3.x = 1020 + rand() % 200;

				// Reset level bar and key
				level_bar_index = 0;
				magic_key_active = false;
				magic_key.state = false;
				witch.state = false;

				// Make sure the key doesn't appear at the start
				magic_key.resetMagicObject(900, 90, 55, 65, false, false);
				witch.resetMagicObject(950, 100, 80, 120, false, false);
				fallingRock1.reset();
				fallingRock2.reset();
				fallingRock3.reset();
				bat.reset(1300, 450, true, 100, 0);
				treasureGiftActive = false;   // Reset treasure gift state
				treasureCollected = false;    // Reset treasure collection
				treasureGift.state = false;   // Hide treasure

				
			}
		}



		else if (mx >= 950 && mx <= 990 && my >= 550 && my <= 590)
		{
			if (levelPage == 1 || levelPage == 2)
			if (level != 0) {
				if (!pause) {
					pause = true;

					iPauseTimer(timer_thirty);
					iPauseTimer(timer_fire);
					iPauseTimer(timer_level);
					iPauseTimer(timer_bg1);
					iPauseTimer(timer_rock);
					iPauseTimer(timer_bat);
					iPauseTimer(timer_battack);
				}
				else {
					pause = false;

					iResumeTimer(timer_thirty);
					iResumeTimer(timer_fire);
					iResumeTimer(timer_level);
					iResumeTimer(timer_bg1);
					iResumeTimer(timer_rock);
					iResumeTimer(timer_bat);
					iResumeTimer(timer_battack);
				}
			}

		}

	}

	
	
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/


void iKeyboard(unsigned char key)
{
	if (key == 27)
	{
		startPage = 0;
		helpPage = 0;
		creditPage = 0;
		menuPage = 1;
		levelPage = 0;
		PlaySound(NULL, 0, 0);
		PlaySound("music.wav", NULL, SND_LOOP | SND_ASYNC);
	}

	if (key == 13)  // Enter key
	{
		if (startPage == 1)
		{
			if (currentStoryImage < 4)  // If not the last story image
			{
				currentStoryImage++;
			}
			else  // If last story image, start level 1
			{
				startPage = 0;  // Hide the story page
				levelPage = 1;  // Activate level 1 // Set level to 1
			}
		}
		if (showingLevel2Story)  // If story is active
		{
			if (currentStoryImage2 < 15)  // If not the last story image
			{
				currentStoryImage2++;
			}
			else  // If last story image, start Level 2
			{
				showingLevel2Story = false;  // Hide the story
				levelPage = 2;  // Activate Level 2
				resetLevel2();  // Reset Level 2 parameters
				PlaySound("storyMusic.wav", NULL, SND_LOOP | SND_ASYNC);  // Change music for Level 2
			}
		}
	}

	if (key == ' ')
	{
		fire = true;
	}

	

}
	
	


/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	
	if (key == GLUT_KEY_LEFT)
	{
		 //Moving character and background for level one.
		
			if (jumping_height == 0)
			{
				ground_player.condition = 3;//left run
			}
			else
			{
				ground_player.condition = 7; // Jumping left
			}

			if (ground_player.x > 40)
			{
				ground_player.x -= 8;
			}

			
			ground_player.condition = 3;
			changeRunningBackImage();
		
	}
		
	if (key == GLUT_KEY_RIGHT)
	{
		
			if (jumping_height == 0)
			{
				ground_player.condition = 2;
			}

			else
			{
				ground_player.condition = 6; // Jumping right
			}

			if (ground_player.x < 985)
			{
				ground_player.x += (ground_player.x < 750) ? 10 : 12;
			}
			
			
			changeRunningImage();

			
				
	}
	if (key == GLUT_KEY_UP)
	{
		if (!jump)
		{
			jump = true;
			jumping = true;

			// Check if moving left or right while jumping
			if (ground_player.condition == 2 || ground_player.condition == 6)
			{
				ground_player.condition = 6; // Jumping right
			}
			else if (ground_player.condition == 3 || ground_player.condition == 7)
			{
				ground_player.condition = 7; // Jumping left (Fixed)
			}
			else
			{
				ground_player.condition = 4; // Jumping straight up
			}
		}

		
	}
	
	
	if (key == GLUT_KEY_HOME)
	{
		
	}

	if (key == GLUT_KEY_F1)
	{
		if (musicOn)
		{
			musicOn = false;
			PlaySound(0, 0, 0);
		}

		else
		{
			musicOn = true;
			PlaySound("music.wav", NULL, SND_NOSTOP | SND_ASYNC);
		}
	}
	if (key == GLUT_KEY_F2)
	{
		if (buttonOn)
		{
			buttonOn = false;
			PlaySound(0, 0, 0);
		}

		else
		{
			buttonOn == true;
			PlaySound("Button.wav", NULL, SND_ASYNC);


		}

		
	}
	
}

void drawMenupage()
{
	
	iShowImage(0, 0, 1000, 600, menuBackgroundID); // Display menu background
	
	
}
void drawStartpage()
{
	// Draw the current story image
	iShowImage(0, 0, 1000, 600, storyImages[currentStoryImage]);
	
	static bool isStoryMusicPlaying = false;
	if (!isStoryMusicPlaying) {
		PlaySound("storyMusic.wav", NULL, SND_LOOP | SND_ASYNC);
		isStoryMusicPlaying = true;
	}
}



void drawLevel1()
{
	 
	//background is drawn
	iShowImage(backgroundX, 0, 1000, 600, levelBackgroundID);
	iShowImage(backgroundX + 1000, 0, 1000, 600, levelBackgroundID);
	iShowImage(950, 550, 40, 40, pauseButtonImage);
	showEnemyOne();
	showPlayerOne();
	showBomb();
	drawHealthBar();
	playerEnemyCollision();
	fireBullet();
	sheild();
	map();
	draw_levelbar();
	checkKeyCollection();
	showEnemyBullets();
	moveEnemyBullets();
	
	enemyBulletCollision();
	
	
	
	static bool isLevelMusicPlaying = false;
	if (!isLevelMusicPlaying) {
		PlaySound("level1Music.wav", NULL, SND_LOOP | SND_ASYNC);
		isLevelMusicPlaying = true;
	}
		
		
}



void updateBackground()
{   
	//where the background moves
	if (levelPage == 1)
	backgroundX -= backgroundSpeed;  // Move background to the left

	// Reset background position when it moves out of frame
	if (backgroundX <= -1000)
		backgroundX = 0;
}
void drawLevel2(){
	iShowImage(backgroundX2, 0, 1000, 600, levelBackgroundID2);
	iShowImage(backgroundX2 + 1000, 0, 1000, 600, levelBackgroundID2);
	iShowImage(950, 550, 40, 40, pauseButtonImage);
	showEnemyOne();
	showPlayerOne();
	drawHealthBar();
	playerEnemyCollision();
	fireBullet();
	sheild();
	map();
	draw_levelbar();
	showRocks();
	playerBatFireballCollision();
	shootFireFromBat();
	showBat();
	drawBatFireProjectile();
	showEnemyBullets();
	moveEnemyBullets();
	enemyBulletCollision();
	showTreasureGift();  
	checkTreasureCollection(); 
	showWinScreen();

	static bool isLevelMusicPlaying = false;
	if (!isLevelMusicPlaying) {
		PlaySound("level1Music.wav", NULL, SND_LOOP | SND_ASYNC);
		isLevelMusicPlaying = true;
	}


}
void updateBackground2()
{
	if (levelPage == 2)
		backgroundX2 -= backgroundSpeed2;  // Move background to the left

	if (backgroundX2 <= -1000)
		backgroundX2 += 1000;
}


void drawHelppage()
{
	iShowImage(0, 0, 1000, 600, helpBackgroundID); // Display help background
}

void drawCreditpage()
{
	iShowImage(0, 0, 1000, 600, creditBackgroundID); // Display credit background
}

void startButtonClickHandler()
{
	PlaySound("Button.wav", NULL,SND_ASYNC);
	menuPage = 0;
	startPage = 1;
	PlaySound("storyMusic.wav", NULL, SND_LOOP | SND_ASYNC); // Start story music
}

void helpButtonClickHandler()
{   
	PlaySound("Button.wav", NULL,SND_ASYNC);
	menuPage = 0;
	helpPage = 1;
}

void creditButtonClickHandler()
{
	PlaySound("Button.wav", NULL, SND_ASYNC);
	menuPage = 0;
	creditPage = 1;
}


/*________________________________________________________ Timer function______________________________________________________________________________  */
void iRockTimer() {
	int background_speed = 0;
	updateRocksPosition(background_speed, ground_player);
}

void thirtymilisec(){
	updateBackground();
	changeEnemyPosition();
	changeBombPosition();
	Jump();
}
void setupTimers() {
	timer_thirty = iSetTimer(30, thirtymilisec);
	timer_level = iSetTimer(1000, increaseLevelTime);
	timer_bg1 = iSetTimer(40, updateBackground2);
	timer_rock = iSetTimer(60, iRockTimer);
	timer_bat = iSetTimer(50, moveBat);
	timer_battack = iSetTimer(80, updateBatFireProjectile);
		
	

	if (level == 1 || explosion) {
		timer_fire = iSetTimer(20, changeFire); // Explosion animation
	}
	 timer_sheild = iSetTimer(100, shieldPositionChange);
}

int main()
{
	///srand((unsigned)time(NULL));

	if (musicOn)
		PlaySound("music.wav", NULL, SND_NOSTOP | SND_ASYNC);
	iInitialize(1000, 600, "Project Title");

	// Load background images for level 1
	menuBackgroundID = iLoadImage("image\\menu.jpg");//menu

	helpBackgroundID = iLoadImage("image\\help.jpg");//help

	creditBackgroundID = iLoadImage("image\\credit2.jpg");//credit
	
	levelBackgroundID = iLoadImage("image\\level1.jpg");//bg level 1

	levelBackgroundID2 = iLoadImage("image\\level2.jpg");//bg level 1

	/*_______________________________________Load images for level 1____________________________________________________________*/
	for (int i = 0; i <= 8; i++)
	{
		enemy_one1.image[i] = iLoadImage(enemy1_image_location[i]);
	
		enemy_one2.image[i] = iLoadImage(enemy2_image_location[i]);
		
		enemy_one3.image[i] = iLoadImage(enemy3_image_location[i]);
		
	}

	// Load story images
	storyImages[0] = iLoadImage("image\\s1.jpg");
	storyImages[1] = iLoadImage("image\\s2.jpg");
	storyImages[2] = iLoadImage("image\\s3.jpg");
	storyImages[3] = iLoadImage("image\\s4.jpg");
	storyImages[4] = iLoadImage("image\\s5.jpg");


	

	
	//character movement
	for (int i = 0; i <1; i++)
	{
		ground_player.image_idle[i] = iLoadImage(player_idle_image);
	}

	for (int i = 0; i <1; i++)
	{
		ground_player.image_idleback[i] = iLoadImage(player_idleback_image);
	}

	

	for (int i = 0; i <= 9; i++)
	{
		ground_player.image_running[i] = iLoadImage(player_running_image[i]);
	}

	for (int i = 0; i <= 9; i++)
	{
		ground_player.image_runningback[i] = iLoadImage(player_runningback_image[i]);
	}

	for (int i = 0; i <5; i++)
	{
		ground_player.image_jumping[i] = iLoadImage(player_jumping_image[i]);
	}

	

	for (int i = 0; i < 5; i++)
	{
		ground_player.image_jumpingback[i] = iLoadImage(player_jumpingback_image[i]);
	}
	for (int i = 0; i <= 12; i++)//health
	{
		health_bar[i] = iLoadImage(health_bar_image[i]);
	}
	for (int i = 0; i <=6; i++)
	{
		shield_bar[i] = iLoadImage(shield_bar_image[i]);
	}
	for (int i = 0; i <=12; i++) {
		level_bar[i] = iLoadImage(level_bar_image[i]);
	}

	for (int i = 0; i <= 15; i++) {
		level2_story[i] = iLoadImage(level2_story_images[i]);
	}


	bomb_image = iLoadImage("level_one\\enemy\\bomb.png");//bomb

	for (int i = 0; i <= 19; i++)//explosion
	{
		fire_image[i] = iLoadImage(fire_image_location[i]);
	}

	bullet_image = iLoadImage("level_one\\arms\\bullet.png");
	bullet_back_image = iLoadImage("level_one\\arms\\bullet_back.png");
	powered_bullet_image = iLoadImage("level_one\\arms\\power_bullet.png");
	powered_back_bullet_image = iLoadImage("level_one\\arms\\power_back_bullet.png");
	bullet_image_id = iLoadImage("level_one\\arms\\ebullet.png");


	pauseButtonImage = iLoadImage("image/pause.png");

	shield.image = iLoadImage("level_one\\objects\\energy.png");
	key = iLoadImage("level_one\\objects\\key.png");
	witch_image = iLoadImage("level_one\\objects\\wizard.png");

	for (int i = 0; i < 9; i++) {
		bat.img[i] = iLoadImage(bat_image_location[i]);
	}

	batAttackImage = iLoadImage("level_two\\BatAttack.png");
	rock_image = iLoadImage("level_two\\rock.png");

	game_over_image = iLoadImage("image/game_over.jpg");
	winImage = iLoadImage("image/win.jpg");
	stone = iLoadImage("level_two\\stone.png");
	

	setupTimers();
	
	
	

	
	


	
	///updated see the documentations
	iStart();
	return 0;
}