#include "Commands_Update.h"
#include "usart.h"

//----------------------------------------------------------------------------------------------------//

const char Hello_String[7] = "Hello!\n";
const char Busy_String[16] = "Device is busy!\n";

//----------------------------------------------------------------------------------------------------//

T_Service Service;

extern uint8_t Recieve_Number;

//----------------------------------------------------------------------------------------------------//

static void Led_Blink(uint16_t Time_Between_Blinks, uint16_t Amount_of_Blink, bool* Blink_Mode);
static uint8_t GCD(uint8_t Button_Pressed_Num, uint8_t USART_Recieved_Num);

//----------------------------------------------------------------------------------------------------//

void Commands_Handling(uint16_t Command)
{
	
	if ((Command == CMD_RESET) && Service.bButtons_Was_Blocked)
		Service.bButtons_Was_Blocked = false;
	
	
	if (Command && Service.bButtons_Was_Blocked)
	{
		HAL_UART_Transmit_DMA(&huart1, (uint8_t*)Busy_String, 16);
		Command = CMD_NONE;
	}
	
	
	switch(Command)
	{
		case CMD_POWER_ON : HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
 			break;
		case CMD_RESET : HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
			break;
		case CMD_SEND_BUSY : Service.bButtons_Was_Blocked = true;
			break;
		case CMD_SEND_MESSAGE : HAL_UART_Transmit_DMA(&huart1, (uint8_t*)Hello_String, 7);
			break;
		case CMD_SEND_BUTTON_PRESSED_COUNTER :
		{
			Service.Counter_of_Pressed++;
			HAL_UART_Transmit_DMA(&huart1, (uint8_t*)&Service.Counter_of_Pressed, 1);
		}
			break;
		case CMD_RESET_BUTTON_COUNTER : Service.Counter_of_Pressed = 0;
			break;
		case CMD_SEND_DEVIDER :
		{
			Service.GCD_Value = GCD(Service.Counter_of_Pressed, Recieve_Number);
			HAL_UART_Transmit_DMA(&huart1, &Service.GCD_Value, 1);
		}
			break;
		case CMD_BLINK_LED : 
		{
			Service.bBlink_Mode = true;
		}			
			break;
		default : ;
			break;
	}
	
	Led_Blink(5, Service.Counter_of_Pressed, &Service.bBlink_Mode);
	
}

//----------------------------------------------------------------------------------------------------//

/**
  * @brief  Функция мигания светодиодом количестро раз, равное какому либо установленному значению
  * @param  Time_Between_Blinks - задержка между миганиями светодиодом
	* @param	Amount_of_Blink - количество раз, которое нужно помигать
	* @param	pBlink_Mode - указатель на флаг, коворящий о том, что данная функция должна работать.
													Когда функция отработает, она опускает этот флаг
	* @retval None
  */
static void Led_Blink(uint16_t Time_Between_Blinks ,uint16_t Amount_of_Blink, bool* pBlink_Mode)
{
	
	static uint16_t Amount_of_Blinks = 0;
	static uint16_t Counter_Between_Blink = 0;
	
	if (*pBlink_Mode)
	{
		Amount_of_Blinks = Amount_of_Blink * 2;
		*pBlink_Mode = false;
	}
	
	if (!Amount_of_Blinks)
		return;
	
	if (++Counter_Between_Blink >= Time_Between_Blinks)
	{
		Counter_Between_Blink = 0;
		Amount_of_Blinks--;
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		*pBlink_Mode = false;
	}
	
}

//----------------------------------------------------------------------------------------------------//

static uint8_t GCD(uint8_t Button_Pressed_Num, uint8_t USART_Recieved_Num)
{
	
	while (USART_Recieved_Num != 0) 
	{
		uint8_t temp = USART_Recieved_Num;
		USART_Recieved_Num = Button_Pressed_Num % USART_Recieved_Num;
		Button_Pressed_Num = temp;
	}
		
	return Button_Pressed_Num;
		
}


//----------------------------------------- END OF FILE ----------------------------------------------//
