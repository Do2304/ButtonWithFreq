#ifndef Button_h
#define Button_h
#include "main.h"
typedef struct
{
	uint8_t btn_current ;
	uint8_t btn_last ;
	uint8_t btn_filter ;
	uint8_t is_debouncing;
	uint32_t time_deboune;
	uint32_t time_start_press;
	uint8_t is_press_timeout;
	uint8_t test;
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;
}button_typdef;	

void button_handle(button_typdef *buttonx);
void button_init(button_typdef *buttonx,GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
#endif