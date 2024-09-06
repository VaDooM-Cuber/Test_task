#ifndef COMMANDS_UPDATE_H_
#define COMMANDS_UPDATE_H_

//----------------------------------------------------------------------------------------------------//

#include "stdint.h"

//----------------------------------------------------------------------------------------------------//

typedef struct
{
	
	uint16_t* Command;
	uint16_t	Pressed_counter;
	
} T_Commands;

//----------------------------------------------------------------------------------------------------//

void Commands_Init(T_Commands* p);
void Commands_Update(T_Commands* p);

//----------------------------------------------------------------------------------------------------//

#endif // COMMANDS_UPDATE_H_

//----------------------------------------- END OF FILE ----------------------------------------------//
