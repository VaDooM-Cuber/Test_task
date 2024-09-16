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
static void Command_Select(E_Commands* pCommand, uint16_t Button_Status, E_Commands Command_1, E_Commands Command_2);

//----------------------------------------------------------------------------------------------------//

/**
  * @brief  Функция инициализации кнопки
  * @param  pShort_Response_Time - указатель на задержку срабатывания короткого нажатия кнопки
	* @param	pLong_Response_Time - указатель на время срабатывания длинного нажатия книпки
	* @retval None
  */
void Button_Init(T_Button* p,
								 uint16_t* pShort_Response_Time,
								 uint16_t* pLong_Response_Time)
{
	
	p->pShort_Response_Time = pShort_Response_Time;
	p->pLong_Response_Time = pLong_Response_Time;
	p->bIs_Init = true;
	
}

//----------------------------------------------------------------------------------------------------//

/**
  * @brief  Функция обработки нажатий кнопки
  * @param  None
	* @retval E_Commands - текущая команда, в зависимости от нажатой кнопки
  */
E_Commands Buttons_Update(void)
{
	
	E_Commands Current_command = CMD_NONE;
	
	uint16_t button_status_1 = Button_Update(&Button_1, HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin));
	uint16_t button_status_2 = Button_Update(&Button_2, HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin));
	uint16_t button_status_3 = Button_Update(&Button_3, HAL_GPIO_ReadPin(BUTTON_3_GPIO_Port, BUTTON_3_Pin));
	uint16_t button_status_4 = Button_Update(&Button_4, HAL_GPIO_ReadPin(BUTTON_4_GPIO_Port, BUTTON_4_Pin));
	
	Command_Select(&Current_command, button_status_1, CMD_POWER_ON, CMD_RESET);
	Command_Select(&Current_command, button_status_2, CMD_SEND_BUSY, CMD_SEND_MESSAGE);
	Command_Select(&Current_command, button_status_3, CMD_SEND_BUTTON_PRESSED_COUNTER, CMD_RESET_BUTTON_COUNTER);
	Command_Select(&Current_command, button_status_4, CMD_SEND_DEVIDER, CMD_BLINK_LED);
	
	return Current_command;
	
}

//----------------------------------------------------------------------------------------------------//

/**
  * @brief  Функция обработки нажатия кнопки
  * @param  p - указатель на сткуктуру кнопки T_Button
	* @param	GPIO_Status - статус GPIO
	* @retval E_Buttons_Pressed - статус состояния кнопки, может иметь слудующий значения:
						* @arg BUTTON_LONG_PRESSED  - длинное нажатие
						* @arg BUTTON_SHORT_PRESSED - короткое нажатие
						* @arg BUTTON_NONE_PRESSED  - не нажата
  */
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

//----------------------------------------------------------------------------------------------------//

/**
  * @brief  Функция присваевает текущей команде статус, в зависимости от статуса кнопки
  * @param  pCommand - указатель на переменную текущей команды
	* @param	Button_Status - статус кнопки, может иметь следующие значения:
						* @arg BUTTON_LONG_PRESSED  - длинное нажатие
						* @arg BUTTON_SHORT_PRESSED - короткое нажатие
						* @arg BUTTON_NONE_PRESSED  - не нажата
  * @retval None
  */
static void Command_Select(E_Commands* pCommand, uint16_t Button_Status, E_Commands Command_1, E_Commands Command_2)
{
	
	if (!Button_Status)
		return;
	
	*pCommand = (Button_Status == BUTTON_SHORT_PRESSED) ? Command_1 : Command_2;
	
}

//----------------------------------------- END OF FILE ----------------------------------------------//
