#include "Buttons_Update.h"
#include "gpio.h"
#include "usart.h"

//----------------------------------------------------------------------------------------------------//

extern char Hello_String[];
extern char Busy_String[];
extern uint16_t Counter_of_Pressed;
extern bool Busy_Mode;
extern bool Blink_Mode;

extern T_Button Button_1;
extern T_Button Button_2;
extern T_Button Button_3;
extern T_Button Button_4;

//----------------------------------------------------------------------------------------------------//

void Button_Init(T_Button* p,
								 uint16_t* Short_Response_Time,
								 uint16_t* Long_Response_Time,
								 uint16_t  Freq_Update)
{
	
	p->pShort_Response_Time = Short_Response_Time;
	p->pLong_Response_Time = Long_Response_Time;
	p->Freq_Update = Freq_Update;
	p->bIs_Init = true;
	
}

//----------------------------------------------------------------------------------------------------//

E_Buttons_Pressed Button_Update(T_Button* p, uint16_t GPIO_Status)
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

//----------------------------------------------------------------------------------------------------//

void Buttons_Update(void)
{
	
	uint16_t gpio_status_1 = Button_Update(&Button_1, HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4));
	uint16_t gpio_status_2 = Button_Update(&Button_2, HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5));
	uint16_t gpio_status_3 = Button_Update(&Button_3, HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6));
	uint16_t gpio_status_4 = Button_Update(&Button_4, HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7));
	
	if (gpio_status_1 == BUTTON_LONG_PRESSED && Busy_Mode)
	{
		Busy_Mode = false;
	}
	
	bool bWas_Button_Pressed = gpio_status_1 || gpio_status_2 || gpio_status_3 || gpio_status_4;
	if (bWas_Button_Pressed && Busy_Mode)
	{
		HAL_UART_Transmit_DMA(&huart1, (uint8_t*)Busy_String, 16);
		return;
	}

	if (gpio_status_1 == BUTTON_SHORT_PRESSED)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	}
	else if (gpio_status_1 == BUTTON_LONG_PRESSED)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	}
	else if (gpio_status_2 == BUTTON_SHORT_PRESSED)
	{
		Busy_Mode = true;
	}
	else if (gpio_status_2 == BUTTON_LONG_PRESSED)
	{
		HAL_UART_Transmit_DMA(&huart1, (uint8_t*)Hello_String, 6);
	}
	else if (gpio_status_3 == BUTTON_SHORT_PRESSED)
	{
		Counter_of_Pressed++;
		HAL_UART_Transmit_DMA(&huart1, (uint8_t*)&Counter_of_Pressed, 1);
	}
	else if (gpio_status_3 == BUTTON_LONG_PRESSED)
	{
		Counter_of_Pressed = 0;
	}
	else if (gpio_status_4 == BUTTON_LONG_PRESSED)
	{
		Blink_Mode = true;
	}
	
	
	
}

//----------------------------------------- END OF FILE ----------------------------------------------//
