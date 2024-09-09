#include "Commands_Update.h"
#include "usart.h"


//----------------------------------------------------------------------------------------------------//

#define BUFFER_SIZE 20U

//----------------------------------------------------------------------------------------------------//

uint8_t USART_RxBuffer[BUFFER_SIZE];
uint8_t USART_TxBuffer[BUFFER_SIZE];

T_Commands Command;

uint16_t Counter_of_Pressed = 0;
char Hello_String[7] = "Hello!\n";
char Busy_String[16] = "Device is busy!\n";
bool bButtons_Was_Blocked = false;
bool bBlink_Mode = false;
uint8_t GCD_Value = 0;
uint8_t Num_of_Blink = 0;

extern uint8_t Recieve_Number;

//----------------------------------------------------------------------------------------------------//

static void Led_Blink(uint16_t Time_Between_Blinks, uint16_t Amount_of_Blink, bool* Blink_Mode);
static uint8_t GCD(uint8_t Button_Pressed_Num, uint8_t USART_Recieved_Num);

//----------------------------------------------------------------------------------------------------//

void Commands_Handling(T_Commands* p)
{
	
	if ((p->Current_Command == CMD_RESET) && bButtons_Was_Blocked)
		bButtons_Was_Blocked = false;
	
	
	if (p->Current_Command && bButtons_Was_Blocked)
	{
		HAL_UART_Transmit_DMA(&huart1, (uint8_t*)Busy_String, 16);
		p->Current_Command = CMD_NONE;
	}
	
	
	switch(p->Current_Command)
	{
		case CMD_POWER_ON : HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
 			break;
		case CMD_RESET : HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
			break;
		case CMD_SEND_BUSY : bButtons_Was_Blocked = true;
			break;
		case CMD_SEND_MESSAGE : HAL_UART_Transmit_DMA(&huart1, (uint8_t*)Hello_String, 7);
			break;
		case CMD_SEND_BUTTON_PRESSED_COUNTER :
		{
			Counter_of_Pressed++;
			HAL_UART_Transmit_DMA(&huart1, (uint8_t*)&Counter_of_Pressed, 1);
		}
			break;
		case CMD_RESET_BUTTON_COUNTER : Counter_of_Pressed = 0;
			break;
		case CMD_SEND_DEVIDER :
		{
			GCD_Value = GCD(Counter_of_Pressed, Recieve_Number);
			HAL_UART_Transmit_DMA(&huart1, &GCD_Value, 1);
		}
			break;
		case CMD_BLINK_LED : 
		{
			bBlink_Mode = true;
		}			
			break;
		default : ;
			break;
	}
	
	Led_Blink(5, Counter_of_Pressed, &bBlink_Mode);
	p->Current_Command = CMD_NONE;
	
}

//----------------------------------------------------------------------------------------------------//

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
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
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
