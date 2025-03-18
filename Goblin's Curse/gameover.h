#ifndef GAMEOVER_H_INCLUDED
#define GAMEOVER_H_INCLUDED

bool game_over = false;
int game_over_image;


void gameOver()
{
	if (ground_player.health <= 0) // Check if the game is over
	{
		game_over = true;

		// Reset game conditions
		level = 1;  // Restart from level 1 (not 0)

		ground_player.health = 100;
		shield_count = 0;
		active_shield = false;

		// Reset player position
		ground_player.x = 100;  // Adjusted for 1000x600 screen
		ground_player.y = 50;   // Ensure the player is on the ground

		// Reset jump conditions
		jump = false;
		jumping = false;
		jumping_height = 0;

		// Reset player animation state
		ground_player.condition = 0;

		// Reset magic key position (place near the ground)
		magic_key.resetMagicObject(800, 50, 72, 120, false, false);

		
	}
	
}

#endif // GAMEOVER_H_INCLUDED
