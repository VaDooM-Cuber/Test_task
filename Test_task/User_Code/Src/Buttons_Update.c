#include "Buttons_Update.h"
#include "gpio.h"

//----------------------------------------------------------------------------------------------------//

#define BIT_SET 	1U
#define BIT_RESET 0U

//----------------------------------------------------------------------------------------------------//

void Button_Init(T_Button* p,
								 uint16_t* Short_Response_Time,
								 uint16_t* Long_Response_Time,
								 uint16_t  Freq_Update)
{
	
	p->pShort_Response_Time = Short_Response_Time;
	p->pLong_Response_Time = Long_Response_Time;
	p->Freq_Update = Freq_Update;
	p->Statuses.bit.Init = BIT_SET;
	
}

//----------------------------------------------------------------------------------------------------//

E_Buttons_Pressed Button_Update(T_Button* p, uint16_t GPIO_Status)
{
	
	if (!p->Statuses.bit.Init)
		return NO_INITIALIZE;
	
	E_Buttons_Pressed Button_Stauts = BUTTON_NONE_PRESSED;
	
	if (GPIO_Status)
	{
//		if (p->Pressed_Counter >= (*p->pLong_Response_Time))
//			Button_Stauts = BUTTON_LONG_PRESSED;
		
		if (p->bFlag_Long_Pressed)
		{
			p->Pressed_Counter = 0;
			p->bFlag_Long_Pressed = false;
		}
		
		if (p->Pressed_Counter >= (*p->pShort_Response_Time))
			Button_Stauts = BUTTON_SHORT_PRESSED;
		
		p->Pressed_Counter = 0;
	}
	else
	{
		p->Pressed_Counter++;
		if (p->Pressed_Counter >= (*p->pLong_Response_Time))
		{
			Button_Stauts = BUTTON_LONG_PRESSED;
			p->Pressed_Counter = 0;
			p->bFlag_Long_Pressed = true;
		}
	}
	
	return Button_Stauts;
	
}

//----------------------------------------------------------------------------------------------------//

void Get_GPIO_Status(void)
{
	
	HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4);
	HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
	HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
	HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);
	
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
