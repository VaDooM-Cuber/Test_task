#include "Commands_Update.h"

//----------------------------------------------------------------------------------------------------//

enum
{
	
	CMD_POWER_ON = 1,
	CMD_RESET,
	CMD_SEND_BUSY,
	CMD_SEND_MESSAGE,
	CMD_SEND_BUTTON_PRESSED_COUNTER,
	CMD_RESET_BUTTON_COUNTER,
	CMD_SEND_DEVIDER,
	CMD_BLINK_LED
	
} E_Commands;

//----------------------------------------------------------------------------------------------------//

T_Commands Commands;

//----------------------------------------------------------------------------------------------------//

void Commands_Init(T_Commands* p)
{
	
	
	
}

//----------------------------------------------------------------------------------------------------//

void Commands_Update(T_Commands* p)
{
	
	switch(*p->Command)
	{
		case 1 : ;
			break;
		default : ;
			break;
	}
	
}

//----------------------------------------- END OF FILE ----------------------------------------------//
