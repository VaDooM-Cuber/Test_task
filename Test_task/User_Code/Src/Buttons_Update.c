#include "Buttons_Update.h"
#include "gpio.h"
#include "usart.h"

//----------------------------------------------------------------------------------------------------//

T_Button Button_1;
T_Button Button_2;
T_Button Button_3;
T_Button Button_4;

//----------------------------------------------------------------------------------------------------//

static E_Buttons_Pressed Button_Update(T_Button* p, uint16_t GPIO_Status);

//----------------------------------------------------------------------------------------------------//

void Button_Init(T_Button* p,
								 uint16_t* Short_Response_Time,
								 uint16_t* Long_Response_Time)
{
	
	p->pShort_Response_Time = Short_Response_Time;
	p->pLong_Response_Time = Long_Response_Time;
	p->bIs_Init = true;
	
}

//----------------------------------------------------------------------------------------------------//

E_Commands Buttons_Update(void)
{
	
	E_Commands Current_command = CMD_NONE;
	
	uint16_t gpio_status_1 = Button_Update(&Button_1, HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4));
	uint16_t gpio_status_2 = Button_Update(&Button_2, HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5));
	uint16_t gpio_status_3 = Button_Update(&Button_3, HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6));
	uint16_t gpio_status_4 = Button_Update(&Button_4, HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7));
	

	if (gpio_status_1 == BUTTON_SHORT_PRESSED)
		Current_command = CMD_POWER_ON;
	else if (gpio_status_1 == BUTTON_LONG_PRESSED)
		Current_command = CMD_RESET;
	else if (gpio_status_2 == BUTTON_SHORT_PRESSED)
		Current_command = CMD_SEND_BUSY;
	else if (gpio_status_2 == BUTTON_LONG_PRESSED)
		Current_command = CMD_SEND_MESSAGE;
	else if (gpio_status_3 == BUTTON_SHORT_PRESSED)
		Current_command = CMD_SEND_BUTTON_PRESSED_COUNTER; 
	else if (gpio_status_3 == BUTTON_LONG_PRESSED)
		Current_command = CMD_RESET_BUTTON_COUNTER;
	else if (gpio_status_4 == BUTTON_SHORT_PRESSED)
		Current_command = CMD_SEND_DEVIDER;
	else if (gpio_status_4 == BUTTON_LONG_PRESSED)
		Current_command = CMD_BLINK_LED;
	
	
	return Current_command;
	
}

//----------------------------------------------------------------------------------------------------//

static E_Buttons_Pressed Button_Update(T_Button* p, uint16_t GPIO_Status)
{
	
	if (!p->bIs_Init)
		return BUTTON_NONE_PRESSED;
	
	E_Buttons_Pressed Button_Stauts_Temp = BUTTON_NONE_PRESSED;
	
	if (GPIO_Status)
	{
		if (p->bFlag_Long_Pressed)
		{
			p->Pressed_Counter = 0;
			p->bFlag_Long_Pressed = false;
		}
		
		if (p->Pressed_Counter >= (*p->pShort_Response_Time))
			Button_Stauts_Temp = BUTTON_SHORT_PRESSED;
		
		p->Pressed_Counter = 0;
	}
	else
	{
		p->Pressed_Counter++;
		if (p->Pressed_Counter >= (*p->pLong_Response_Time))
		{
			Button_Stauts_Temp = BUTTON_LONG_PRESSED;
			p->Pressed_Counter = 0;
			p->bFlag_Long_Pressed = true;
		}
	}
	
	return Button_Stauts_Temp;
	
}

//----------------------------------------- END OF FILE ----------------------------------------------//
