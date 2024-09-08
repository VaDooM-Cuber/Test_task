#include "Commands_Update.h"
#include "string.h"
#include "usart.h"


//----------------------------------------------------------------------------------------------------//

#define BUFFER_SIZE 20U

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

uint8_t USART_RxBuffer[BUFFER_SIZE];
uint8_t USART_TxBuffer[BUFFER_SIZE];

T_Commands Commands;

//----------------------------------------------------------------------------------------------------//

static void Send_Message(void);
static void Send_Pressed_Counter_Amount(T_Commands* p);

//----------------------------------------------------------------------------------------------------//

void Commands_Init(T_Commands* p)
{
	
	p->Counter_Between_Blink = 0;
	p->Time_Between_Blink = 5;
	
}

//----------------------------------------------------------------------------------------------------//

void Commands_Update(T_Commands* p)
{
	
	
	
	
	
	
	
	
	
}

//----------------------------------------------------------------------------------------------------//

void Commands_Handling(T_Commands* p)
{
	
	switch(*p->Command)
	{
		case CMD_POWER_ON : ;
			break;
		case CMD_RESET : ;
			break;
		case CMD_SEND_BUSY : ;
			break;
		case CMD_SEND_MESSAGE : Send_Message();
			break;
		case CMD_SEND_BUTTON_PRESSED_COUNTER : Send_Pressed_Counter_Amount(p);
			break;
		default : ;
			break;
	}
	
}

//----------------------------------------------------------------------------------------------------//

static void Send_Message(void)
{
	
	char Temp_String[20] = "Hello";
	memcpy(USART_TxBuffer, Temp_String, BUFFER_SIZE);
	HAL_UART_Transmit_DMA(&huart1, USART_TxBuffer, BUFFER_SIZE);
	
}

//----------------------------------------------------------------------------------------------------//

static void Send_Pressed_Counter_Amount(T_Commands* p)
{
	
	p->Pressed_counter++;
	USART_TxBuffer[0] = p->Pressed_counter;
	HAL_UART_Transmit_DMA(&huart1, USART_TxBuffer, 1);
	
}

//----------------------------------------------------------------------------------------------------//

void Led_Blink(T_Commands* p, uint16_t Amount_of_Blink, bool* Blink_Mode)
{
	
	if (*Blink_Mode)
	{
		p->Amount_of_Blink = Amount_of_Blink * 2;
		*Blink_Mode = false;
	}
	
	if (!p->Amount_of_Blink)
		return;
	
	if (++p->Counter_Between_Blink >= p->Time_Between_Blink)
	{
		p->Counter_Between_Blink = 0;
		p->Amount_of_Blink--;
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		*Blink_Mode = false;
	}
	
}


//----------------------------------------- END OF FILE ----------------------------------------------//
