#include "Buttons_Update.h"

//----------------------------------------------------------------------------------------------------//

#define SET 1U;
#define RESET 0U;

enum
{
	
	BUTTON_SHORT_PRESSED = 0,
	BUTTON_LONG_PRESSED
	
} E_Buttons_Pressed;

//----------------------------------------------------------------------------------------------------//

void Button_Init(T_Button* p,
								 uint16_t* Short_Response_Time,
								 uint16_t* Long_Response_Time,
								 uint16_t  Freq_Update)
{
	
	p->Short_Response_Time = Short_Response_Time;
	p->Long_Response_Time = Long_Response_Time;
	p->Freq_Update = Freq_Update;
	p->Statuses.bit.Init = SET;
	
}

//----------------------------------------------------------------------------------------------------//

void Button_Update(T_Button* p)
{
	
	
	
}

//----------------------------------------------------------------------------------------------------//

void Buttons_Init(T_Buttons* p)
{
	
	
	
}

//----------------------------------------------------------------------------------------------------//

void Buttons_Update(T_Buttons* p)
{
	
	
	
}

//----------------------------------------- END OF FILE ----------------------------------------------//
