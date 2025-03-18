#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED
/*_____________________________________________________________Explosion.______________________________________________________________*/

bool explosion = false;
bool exploded1 = false;
bool exploded2 = false;
bool exploded3 = false;
bool exploded4 = false;
bool exploded5 = false;
bool exploded6 = false;
char fire_image_location[21][30] = { "others\\fire\\fire_001_01.png", "others\\fire\\fire_001_02.png",
"others\\fire\\fire_001_03.png", "others\\fire\\fire_001_04.png", "others\\fire\\fire_001_05.png",
"others\\fire\\fire_001_06.png", "others\\fire\\fire_001_07.png", "others\\fire\\fire_001_08.png",
"others\\fire\\fire_001_09.png", "others\\fire\\fire_001_10.png", "others\\fire\\fire_001_11.png",
"others\\fire\\fire_001_12.png", "others\\fire\\fire_001_13.png", "others\\fire\\fire_001_14.png",
"others\\fire\\fire_001_15.png", "others\\fire\\fire_001_16.png", "others\\fire\\fire_001_17.png",
"others\\fire\\fire_001_18.png", "others\\fire\\fire_001_19.png", "others\\fire\\fire_001_20.png" };
int fire_image[21];
int fire_index = 0;

int explosion_x;
int explosion_y;

/*____________________________________________Checking if collision is happenning or not.______________________________________________*/

bool current_collision = false;
bool last_collision = false;

/*This function checks if collision happened or not between two objects or characters and returns a bolean value.
It takes two objects' co-ordinates and dimensions as parameters.*/
bool checkCollision(int object1_x, int object1_y, int dim1_x, int dim1_y, int object2_x, int object2_y, int dim2_x, int dim2_y)
{
	current_collision = (object1_x >= object2_x && object1_x <= object2_x + dim2_x || object1_x + dim1_x >= object2_x && object1_x + dim1_x <= object2_x + dim2_x || object1_x <= object2_x && object1_x + dim1_x >= object2_x + dim2_x) &&
		(object1_y >= object2_y && object1_y <= object2_y + dim2_y || object1_y + dim1_y >= object2_y && object1_y + dim1_y <= object2_y + dim2_y || object1_y <= object2_y && object1_y + dim1_y >= object2_y + dim2_y);

	if (!last_collision && current_collision)
	{
		
		last_collision = current_collision;
		return true;
	}


	else if (last_collision && !current_collision)
	{
		//cout << "False!" << endl;
		last_collision = current_collision;
		return false;
	}

	

	else
	{
		
		return false;
	}
}

#endif // !COLLISION_H_INCLUDED
