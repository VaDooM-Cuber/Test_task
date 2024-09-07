#ifndef BUTTONS_UPDATE_H_
#define BUTTONS_UPDATE_H_

//----------------------------------------------------------------------------------------------------//

#include "stdint.h"
#include "stdbool.h"

//----------------------------------------------------------------------------------------------------//

typedef union
{
	
	uint8_t all;
	struct
	{
		uint8_t Short_Press : 1;
		uint8_t Long_Press	: 1;
		uint8_t Init				: 1;
		uint8_t Reserved		: 5;
	} bit;
	
} T_Statuses;

//----------------------------------------------------------------------------------------------------//

typedef enum
{
	
	BUTTON_NONE_PRESSED = 0,
	BUTTON_SHORT_PRESSED,
	BUTTON_LONG_PRESSED,
	NO_INITIALIZE
	
} E_Buttons_Pressed;

//----------------------------------------------------------------------------------------------------//

typedef struct
{
	
	uint16_t	 Prev_Pressed_Counter_State; // ���������� ����� ��������
	uint16_t 	 Pressed_Counter;					 	 // �������, ��������� �����, ������� ������ ��������� � ������� ���������
	uint16_t*  pShort_Response_Time;			 // ������� �� �������, ����� ������� ����� ������������� �������� �������
	uint16_t*  pLong_Response_Time;			 	 // ������� �� �������, ����� ������� ����� ������������� ������� �������
	uint16_t	 Freq_Update;							 	 // �������, �� ������� ���������� ������� ��������� ������
	T_Statuses Statuses;								 	 // ������ ������
	bool			 bFlag_Long_Pressed;				 // ����, �����������, ��� ������ ���� ������ � �� ��������
	
} T_Button;

//----------------------------------------------------------------------------------------------------//

typedef struct
{
	
	uint16_t Bt_1;
	uint16_t Bt_2;
	uint16_t Bt_3;
	uint16_t Bt_4;
	
} T_Buttons;

//----------------------------------------------------------------------------------------------------//

void Button_Init(T_Button* p, 
								 uint16_t* Short_Response_Time, 
								 uint16_t* Long_Response_Time,
								 uint16_t  Freq_Update);

E_Buttons_Pressed Button_Update(T_Button* p, uint16_t GPIO_Status);
void Get_GPIO_Status(void);

void Buttons_Init(T_Buttons* p);
void Buttons_Update(T_Buttons* p);

#endif // BUTTONS_UPDATE_H_


//----------------------------------------- END OF FILE ----------------------------------------------//
