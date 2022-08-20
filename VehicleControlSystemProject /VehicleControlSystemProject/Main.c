/*
 * Main.c
 *
 *  Created on: Aug 20, 2022
 *  Author: ziadayman
 *
 *                                      VEHICLE CONTROL SYSTEM PROJECT
 */

#include <stdio.h>
#include "RunProgram.h"




/*                                                    Members                                                */

struct state
{
	char *EngineState;
	char *AC;
	int VehicleSpeed;
	int RoomTemp;
	char *EngineTempControllerState;
	int EngineTemp;
};




/*                                                    Functions Prototypes                                                */

void StartProgram();
void Main_Menu();
void Engine_ON();
void Sensors_set_menu();
void PrintData(struct state *now);
void Set_Speed_Value(char *ptr, struct state *now);
void Set_room_temp_data(struct state *now);
void Set_engine_temp_data(struct state *now);




/*                                                    Main Function                                                */

int main(void)
{
	StartProgram(); /* Start the program */

	return 0;
}




/*                                                    Start Function                                                */

void StartProgram() /* function that Start the Program*/
{
	int run = 1; /* condition to keep the program running*/
	char input;  /* Declare input to char */

	Main_Menu(); /* Call main menu function to display the options */

	while(run == 1)
	{
		scanf(" %c", &input); /*space before %c to prevent scanf function from take new line or enter from the above printf functions as input*/

		switch(input)
		{
		case 'a':
		case 'A':
			printf("Turn on vehicle engine\n");
			Engine_ON(&input);
			break;


		case 'b':
		case 'B':
			printf("Turn off vehicle engine\n\n");
			StartProgram();
			break;


		case 'c':
		case 'C':
			printf("Quit the system");
			run = 0;
			break;


		default:
			printf("Invalid input. Try again\n\n");
			StartProgram();
		}
	}
}




/*                                                    Main Menu Function                                                */

void Main_Menu(void) /* Display Options */
{
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n\n");
}




/*                                                    Turn on engine function                                                */

void Engine_ON(char *ptr)
{
	int run = 1;  /* condition to keep the program running*/
	struct state current = {"ON", "OFF", 0, 27, "OFF", 95}; /* initializing the struct members */

	Sensors_set_menu();

	while(run == 1)
	{
		scanf(" %c", ptr); /*space before %c to prevent scanf function from take new line or enter from the above printf functions as input*/
		switch(*ptr)
		{

		case 'a':
		case 'A':
			printf("Turn off vehicle engine\n");
			StartProgram();
			break;


		case 'b':
		case 'B':
			printf("Set the traffic light color\n");
			Set_Speed_Value(ptr, &current);
			PrintData(&current);
			Engine_ON(ptr);
			break;


		case 'c':
		case 'C':
			printf("Set the room temperature\n");
			Set_room_temp_data(&current);
			PrintData(&current);
			Engine_ON(ptr);
			break;


		case 'd':
		case 'D':
			printf("Set the engine temperature\n");
#if WITH_ENGINE_TEMP_CONTROLLER
			Set_engine_temp_data(&current);
#endif
			PrintData(&current);
			Engine_ON(ptr);
			break;


		default:
			printf("Invalid input\t Please Try again\n");
			Engine_ON(ptr);
		}
	}
}




/*                                                    Sensors Menu Function                                                */

void Sensors_set_menu(void) /*Display options */
{
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature\n");
#if WITH_ENGINE_TEMP_CONTROLLER
	printf("d. Set the engine temperature\n\n");
#endif
}




/*                                                    Set speed value Function                                                */

void Set_Speed_Value(char *ptr, struct state *now)
{
	printf("Sensor color input: ");
	scanf(" %c", ptr);

	if(*ptr == 'G' || *ptr == 'g')
	{
		(*now).VehicleSpeed = 100;
	}


	else if(*ptr == 'O' || *ptr == 'o')
	{
		(*now).VehicleSpeed = 30;
	}


	else if(*ptr == 'R' || *ptr == 'r')
	{
		(*now).VehicleSpeed = 0;
	}


	if((*now).VehicleSpeed == 30)
	{
		(*now).AC = "ON";
		(*now).RoomTemp *=(5/4)+1;
#if WITH_ENGINE_TEMP_CONTROLLER
		(*now).EngineTempControllerState = "ON";
		(*now).EngineTemp *= (5/4)+1;
#endif
	}
}




/*                                                    Print Members Function                                                */

void PrintData(struct state *now)
{
	printf("\n Engine State= %s\n", now->EngineState);
	printf("AC: %s\n", now->AC);
	printf("Vehicle Speed = %d km/hr\n", now->VehicleSpeed);
	printf("Room Temperature = %d C\n", now->RoomTemp);
#if WITH_ENGINE_TEMP_CONTROLLER
	printf("Engine Temperature Controller State: %s\n", now->EngineTempControllerState);
	printf("Engine Temperature = %d C`\n\n", now->EngineTemp);
#endif
}




/*                                                    Set room temperature Function                                                */

void Set_room_temp_data(struct state *now)
{
	int input;

	printf("Temperature sensor reading: ");
	scanf("%d", &input);

	if(input < 10 || input > 30)
	{
		(*now).AC = "ON";
		(*now).RoomTemp = 20;
	}
	else
	{
		(*now).AC = "OFF";
		(*now).RoomTemp = input;
	}
}




/*                                                    Set engine temperature Function                                                */

#if WITH_ENGINE_TEMP_CONTROLLER
void Set_engine_temp_data(struct state *now)
{
	int element;

	printf("Engine temperature sensor reading: ");
	scanf("%d", &element);

	if(element < 100 || element > 150)
	{
		(*now).EngineTempControllerState = "ON";
		(*now).EngineTemp = 125;
	}
	else
	{
		(*now).EngineTempControllerState = "OFF";
		(*now).EngineTemp = element;
	}
}
#endif



/*                                                   FINISH AFTER 5 HOURS :)                                               */

