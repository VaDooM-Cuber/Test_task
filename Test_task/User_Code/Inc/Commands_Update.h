#ifndef COMMANDS_UPDATE_H_
#define COMMANDS_UPDATE_H_

//----------------------------------------------------------------------------------------------------//

#include "stdint.h"
#include "stdbool.h"

//----------------------------------------------------------------------------------------------------//

typedef struct
{
	
	uint16_t* Command;
	uint16_t	Pressed_counter;
	
	uint16_t	Counter_Between_Blink;
	uint16_t	Time_Between_Blink;
	uint16_t	Amount_of_Blink;
	
} T_Commands;

//----------------------------------------------------------------------------------------------------//

void Commands_Init(T_Commands* p);
void Commands_Update(T_Commands* p);
void Commands_Handling(T_Commands* p);

void Led_Blink(T_Commands* p, uint16_t Amount_of_Blink, bool* Blink_Mode);

//----------------------------------------------------------------------------------------------------//

#endif // COMMANDS_UPDATE_H_

//----------------------------------------- END OF FILE ----------------------------------------------//
