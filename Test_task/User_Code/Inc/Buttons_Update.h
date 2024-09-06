#ifndef BUTTONS_UPDATE_H_
#define BUTTONS_UPDATE_H_

//----------------------------------------------------------------------------------------------------//

#include "stdint.h"

//----------------------------------------------------------------------------------------------------//

typedef struct
{
	
	uint16_t Bt_1;
	uint16_t Bt_2;
	uint16_t Bt_3;
	uint16_t Bt_4;
	
} T_Buttons;

#endif // BUTTONS_UPDATE_H_

void Buttons_Init(T_Buttons* p);
void Buttons_Update(T_Buttons* p);


//----------------------------------------- END OF FILE ----------------------------------------------//
