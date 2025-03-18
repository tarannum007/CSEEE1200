#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#define JUMPLIMIT 120

/*_____________________________________________________________Level One_______________________________________________________________*/



/*Jumping variables.*/

bool jump = false;
bool jumping = false;
int jumping_height = 0;
 

     char player_running_image[10][32] = {
	"level_one/player/MiloRun1.png",
	"level_one/player/MiloRun2.png",
	"level_one/player/MiloRun3.png",
	"level_one/player/MiloRun4.png",
	"level_one/player/MiloRun5.png",
	"level_one/player/MiloRun6.png",
	"level_one/player/MiloRun7.png",
	"level_one/player/MiloRun8.png",
	"level_one/player/MiloRun9.png"
};
	 int player_running_index = 0;

	 char player_runningback_image[10][33] = {
		 "level_one/player/MiloRevRun1.png",
		 "level_one/player/MiloRevRun2.png",
		 "level_one/player/MiloRevRun3.png",
		 "level_one/player/MiloRevRun4.png",
		 "level_one/player/MiloRevRun5.png",
		 "level_one/player/MiloRevRun6.png",
		 "level_one/player/MiloRevRun7.png",
		 "level_one/player/MiloRevRun8.png",
		 "level_one/player/MiloRevRun9.png"
	 };
	 int player_runningback_index = 0;

	 char player_jumping_image[5][35] = {
	"level_one/player/MiloJump1.png",
	"level_one/player/MiloJump2.png",
	"level_one/player/MiloJump3.png",
	"level_one/player/MiloJump4.png",
	"level_one/player/MiloJump5.png"
};
	 int player_jumping_index = 0;
	 char player_jumpingback_image[5][35] = {
		 "level_one/player/MiloRevJump1.png",
		 "level_one/player/MiloRevJump2.png",
		 "level_one/player/MiloRevJump3.png",
		 "level_one/player/MiloRevJump4.png",
		 "level_one/player/MiloRevJump5.png"
	 };

	 int player_jumpingback_index = 0;
char player_idle_image[32] = "level_one/player/MiloRun5.png";
int player_idle_index = 0;


char player_idleback_image[33] = "level_one/player/MiloRevRun5.png";
int player_idleback_index = 0;

/*_____________________________________________________Structure for the player._______________________________________________________*/

struct Player {
	int x, y;
	int dimension_x, dimension_y; // Character's actual dimension
	int extended_x, extended_y;   // Blank space around the character in the image
	int condition;                // Player state (0 = standing, 1 = running, 2 = jumping)
	int condition_changer;
	bool visible;
	int score;
	int health;
	int image_running[9];
	int image_jumping[5];
	int image_runningback[9];
	int image_jumpingback[5];
	int image_idle[1];
	int image_idleback[1];

	Player(int _x, int _y, int _dimension_x, int _dimension_y, int _extended_x, int _extended_y, int _condition, int _condition_changer, bool _visible, int _score, int _health) {
		x = _x;
		y = _y;
		dimension_x = _dimension_x;
		dimension_y = _dimension_y;
		extended_x = _extended_x;
		extended_y = _extended_y;
		condition = _condition;
		condition_changer = _condition_changer;
		visible = _visible;
		score = _score;
		health = _health;
	}
};

// Initializing players for different levels
Player ground_player(100, 80, 90, 140, 35, 8, 0, 0, true, 0, 100);



/*______________________________________________Changing character images for level one._______________________________________________*/


//Function for changing the index of player�s image in idle condition where multiple images are stored in an array.
void changeIdleImage() //When standing or standing backward.
{
	player_idle_index++; //Player�s idle image index while facing right side.

	if (player_idle_index > 11)
	{
		player_idle_index = 0;
	}

	player_idleback_index++; //Player�s idle image index while facing left side.

	if (player_idleback_index > 11)
	{
		player_idleback_index = 0;
	}
}

//Function for for changing the index of player�s image in running condition(to right side) where multiple images are stored in an array.
void changeRunningImage()
{
	static int change = 0;

	if (change % 2 == 0)
	{
		player_running_index++;
	}

	if (player_running_index > 7)
	{
		player_running_index = 0;
	}

	change++;

	if (change >= 20)
	{
		change = 0;
	}
}

//Function for for changing the index of player�s image in running condition(to left side) where multiple images are stored in an array.
void changeRunningBackImage()
{
	static int change = 0;

	if (change % 2 == 0)
	{
		player_runningback_index++;
	}

	if (player_runningback_index > 7)
	{
		player_runningback_index = 0;
	}

	change++;

	if (change >= 20)
	{
		change = 0;
	}
}

/*____________________________________Funtion for jumping up and coming down. Called from a timer._____________________________________*/

void Jump()
{
	if (jump)  // If currently jumping
	{
		if (jumping) // Going up
		{
			jumping_height += 5;

			if (jumping_height >= JUMPLIMIT)
			{
				jumping = false; // Start falling down
			}

			if (player_jumping_index < 4) // Change jump animation
			{
				player_jumping_index++;
			}
		}
		else // Falling down
		{
			jumping_height -= 5;

			if (jumping_height <= 0)
			{
				jump = false; // Reset jump state
				jumping_height = 0;

				// Ensure landing state remains correct
				if (ground_player.condition == 6)  // Jumping right
				{
					ground_player.condition = 2;  // Return to running right
				}
				else if (ground_player.condition == 7) // Jumping left
				{
					ground_player.condition = 3;  // Return to running left
				}
				else
				{
					ground_player.condition = 0; // Return to standing
				}
			}

			if (player_jumping_index > 0) // Change falling animation
			{
				player_jumping_index--;
			}
		}
	}
}


/*________________________________________________For showing character.__________________________________________________*/

void showPlayerOne()
{
	if (ground_player.condition == 0) //If standing.
	{
		iShowImage(ground_player.x, ground_player.y, 160, 160, ground_player.image_idle[player_idle_index]); /*Showing idle images from an array.
																											 The image index is being changed by calling void changeIdleImage() from a timer when no key is pressed.*/
	}

	else if (ground_player.condition == 1) //If standing backward.
	{
		iShowImage(ground_player.x, ground_player.y, 160, 160, ground_player.image_idleback[player_idleback_index]); /*Showing backward idle images from an array.
																													 The image index is being changed by calling void changeIdleImage() from a timer when no key is pressed.*/
	}

	else if (ground_player.condition == 2) //If running.
	{
		iShowImage(ground_player.x, ground_player.y, 160, 160, ground_player.image_running[player_running_index]); /*Showing running images from an array.
																												   The image index is being changed by calling void changeRunningImage() from void iSpecialKeyboard() when no right key is pressed.*/

		ground_player.condition_changer++;
		if (ground_player.condition_changer >= 200)
		{
			ground_player.condition_changer = 0;
			ground_player.condition = 0;
		}
	}

	else if (ground_player.condition == 3) //If running backward.
	{
		iShowImage(ground_player.x, ground_player.y, 160, 160, ground_player.image_runningback[player_runningback_index]); /*Showing running backward images from an array.
																														   The image index is being changed by calling void changeRunningBackImage() from void iSpecialKeyboard() when left key is pressed.*/

		ground_player.condition_changer++;
		if (ground_player.condition_changer >= 200)
		{
			ground_player.condition_changer = 0;
			ground_player.condition = 1;
		}
	}

	else if (ground_player.condition == 4 || ground_player.condition == 6) //If jumping.
	{
		iShowImage(ground_player.x, ground_player.y + jumping_height, 160, 160, ground_player.image_jumping[player_jumping_index]); /*Showing jumping images from an array.
																																	The image index is being changed by calling void Jump() from void iSpecialKeyboard() when up key is pressed.*/
	}

	else if (ground_player.condition == 5 || ground_player.condition == 7) //If jumping back.
	{
		iShowImage(ground_player.x, ground_player.y + jumping_height, 160, 160, ground_player.image_jumpingback[player_jumping_index]); /*
																																	   The image index is being changed by calling void Jump() from void iSpecialKeyboard() when up key is pressed.*/
	}

	//If the player is on the screen.
	if (ground_player.x >= 0 && ground_player.x <= 1000)
	{
		ground_player.visible = true;
	}
	else
	{
		ground_player.visible = false;
	}
}








#endif // PLAYER_H_INCLUDED
