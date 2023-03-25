#include "button.h"
	
	uint8_t test;
__weak void btn_pressing_callback(button_typdef *buttonx)
{ test =1;
}	
__weak void btn_press_short_callback(button_typdef *buttonx)
{
	test =3;
}
__weak void btn_release_callback(button_typdef *buttonx)
{
	test =2;
}
__weak void btn_press_timeout_callback(button_typdef *buttonx)
{
	test =4;
}

uint8_t test;
void button_handle(button_typdef *buttonx)
{
	//------------------ Loc nhieu ------------------------
	uint8_t sta = HAL_GPIO_ReadPin(buttonx->GPIOx,buttonx->GPIO_Pin);
	if(sta != buttonx-> btn_filter)
	{
		buttonx->btn_filter = sta;
		buttonx->is_debouncing = 1;
		buttonx->time_deboune = HAL_GetTick();
	}
	//------------------ Tin hieu da xac lap------------------------
	if(buttonx->is_debouncing && (HAL_GetTick() - buttonx-> time_deboune >= 15))
	{
		buttonx->btn_current = buttonx->btn_filter;
		buttonx->is_debouncing =0;
	}
	//---------------------Xu li nhan nha------------------------
	if(buttonx->btn_current != buttonx->btn_last)
	{
		if(buttonx->btn_current == 0)//nhan xuong
		{
			buttonx->is_press_timeout = 1;
			btn_pressing_callback(buttonx);
			buttonx->time_start_press = HAL_GetTick();
		}
		else //nha nut
		{
			if(HAL_GetTick() - buttonx->time_start_press <= 1000)
			{
				btn_press_short_callback(buttonx);
			}
			btn_release_callback(buttonx);
			buttonx->is_press_timeout=0;
		}
		buttonx->btn_last = buttonx->btn_current;
	}
	//-------------Xu li nhan giu----------------
	if(buttonx->is_press_timeout && (HAL_GetTick() - buttonx->time_start_press >= 3000))
	{
		btn_press_timeout_callback(buttonx);
		buttonx->is_press_timeout =0;
	}
}
void button_init(button_typdef *buttonx,GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
		buttonx->GPIOx = GPIOx;
		buttonx->GPIO_Pin = GPIO_Pin;
}	