#ifndef BUTTONS_UPDATE_H_
#define BUTTONS_UPDATE_H_

//----------------------------------------------------------------------------------------------------//

#include "stdint.h"

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

typedef struct
{
	
	uint16_t 	Pressed_Counter;			// Счетчик, считающий время, сколько кнопка находится в нажатом состоянии
	uint16_t* Short_Response_Time;	// Уставка по времени, через которое будет зафиксировано короткое нажатие
	uint16_t* Long_Response_Time;		// Уставка по времени, через которое будет зафиксировано длинное нажатие
	uint16_t	Freq_Update;					// Частота, на которой вызывается функция обработки кнопки
	T_Statuses Statuses;						// Статус кнопки
	
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

void Button_Update(T_Button* p);

void Buttons_Init(T_Buttons* p);
void Buttons_Update(T_Buttons* p);

#endif // BUTTONS_UPDATE_H_


//----------------------------------------- END OF FILE ----------------------------------------------//
