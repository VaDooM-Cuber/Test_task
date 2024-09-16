#ifndef BUTTONS_UPDATE_H_
#define BUTTONS_UPDATE_H_

//----------------------------------------------------------------------------------------------------//

#include "General_Params.h"

//----------------------------------------------------------------------------------------------------//

typedef enum
{
	
	BUTTON_NONE_PRESSED = 0,		// ������ �� ������
	BUTTON_SHORT_PRESSED,				// �������� ������� ������
	BUTTON_LONG_PRESSED					// ������� ������� ������
	
} E_Buttons_Pressed;

//----------------------------------------------------------------------------------------------------//

typedef struct
{
	
	uint16_t 	 Pressed_Counter;					 	 // �������, ��������� �����, ������� ������ ��������� � ������� ���������
	uint16_t*  pShort_Response_Time;			 // ������� �� �������, ����� ������� ����� ������������� �������� �������
	uint16_t*  pLong_Response_Time;			 	 // ������� �� �������, ����� ������� ����� ������������� ������� �������
	bool			 bIs_Init;									 // ������ ������������� ������
	bool			 bFlag_Long_Pressed;				 // ����, �����������, ��� ������ ���� ������ � �� ��������
	
} T_Button;

//----------------------------------------------------------------------------------------------------//

void Button_Init(T_Button* p, 
								 uint16_t* pShort_Response_Time, 
								 uint16_t* pLong_Response_Time);

E_Commands Buttons_Update(void);

//----------------------------------------------------------------------------------------------------//

extern T_Button Button_1;
extern T_Button Button_2;
extern T_Button Button_3;
extern T_Button Button_4;

#endif // BUTTONS_UPDATE_H_


//----------------------------------------- END OF FILE ----------------------------------------------//
