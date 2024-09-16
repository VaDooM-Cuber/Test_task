#ifndef BUTTONS_UPDATE_H_
#define BUTTONS_UPDATE_H_

//----------------------------------------------------------------------------------------------------//

#include "General_Params.h"

//----------------------------------------------------------------------------------------------------//

typedef enum
{
	
	BUTTON_NONE_PRESSED = 0,		// Кнопка не нажата
	BUTTON_SHORT_PRESSED,				// Короткое нажатие кнопки
	BUTTON_LONG_PRESSED					// Длинное нажатие кнопки
	
} E_Buttons_Pressed;

//----------------------------------------------------------------------------------------------------//

typedef struct
{
	
	uint16_t 	 Pressed_Counter;					 	 // Счетчик, считающий время, сколько кнопка находится в нажатом состоянии
	uint16_t*  pShort_Response_Time;			 // Уставка по времени, через которое будет зафиксировано короткое нажатие
	uint16_t*  pLong_Response_Time;			 	 // Уставка по времени, через которое будет зафиксировано длинное нажатие
	bool			 bIs_Init;									 // Статус инициализации кнопки
	bool			 bFlag_Long_Pressed;				 // Флаг, указывающий, что кнопка была зажата и не отпущена
	
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
