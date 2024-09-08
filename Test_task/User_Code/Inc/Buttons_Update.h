#ifndef BUTTONS_UPDATE_H_
#define BUTTONS_UPDATE_H_

//----------------------------------------------------------------------------------------------------//

#include "stdint.h"
#include "stdbool.h"

#include "Commands_Update.h"

//----------------------------------------------------------------------------------------------------//

typedef enum
{
	
	BUTTON_NONE_PRESSED = 0,
	BUTTON_SHORT_PRESSED,
	BUTTON_LONG_PRESSED
	
} E_Buttons_Pressed;

//----------------------------------------------------------------------------------------------------//

typedef struct
{
	
	uint16_t	 Prev_Pressed_Counter_State; // ���������� ����� ��������
	uint16_t 	 Pressed_Counter;					 	 // �������, ��������� �����, ������� ������ ��������� � ������� ���������
	uint16_t*  pShort_Response_Time;			 // ������� �� �������, ����� ������� ����� ������������� �������� �������
	uint16_t*  pLong_Response_Time;			 	 // ������� �� �������, ����� ������� ����� ������������� ������� �������
	uint16_t	 Freq_Update;							 	 // �������, �� ������� ���������� ������� ��������� ������
	bool			 bIs_Init;									 // ������ ������������� ������
	bool			 bFlag_Long_Pressed;				 // ����, �����������, ��� ������ ���� ������ � �� ��������
	
} T_Button;

//----------------------------------------------------------------------------------------------------//

typedef struct
{
	
	T_Button* Button_1;
	T_Button* Button_2;
	T_Button* Button_3;
	T_Button* Button_4;
	
} T_Buttons;

//----------------------------------------------------------------------------------------------------//

void Button_Init(T_Button* p, 
								 uint16_t* Short_Response_Time, 
								 uint16_t* Long_Response_Time,
								 uint16_t  Freq_Update);

E_Buttons_Pressed Button_Update(T_Button* p, uint16_t GPIO_Status);

void Buttons_Update(void);

#endif // BUTTONS_UPDATE_H_


//----------------------------------------- END OF FILE ----------------------------------------------//
