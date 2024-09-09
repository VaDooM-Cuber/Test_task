#ifndef GENERAL_PARAMS_H_
#define GENERAL_PARAMS_H_

//----------------------------------------------------------------------------------------------------//

#include "stdint.h"
#include "stdbool.h"
#include "string.h"

//----------------------------------------------------------------------------------------------------//

typedef enum
{
	
	CMD_NONE = 0,
	CMD_POWER_ON,
	CMD_RESET,
	CMD_SEND_BUSY,
	CMD_SEND_MESSAGE,
	CMD_SEND_BUTTON_PRESSED_COUNTER,
	CMD_RESET_BUTTON_COUNTER,
	CMD_SEND_DEVIDER,
	CMD_BLINK_LED
	
} E_Commands;

//----------------------------------------------------------------------------------------------------//

#endif // GENERAL_PARAMS_H_

//----------------------------------------- END OF FILE ----------------------------------------------//
