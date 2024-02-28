#include "stm32f10x.h"
#include "delay.h"
#include "u8g2.h"
#include "oled.h"

u8g2_t u8g2;

void Delay(u32 count)
{
	u32 i=0;
	for(;i<count;i++);
}

int main(void)
{	
	/* LED */	
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE, ENABLE);	//使能PB,PE端口时钟
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_5;			    					//LED0-->PB.5 端口配置
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_PP; 	 						//推挽输出
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;	 							//IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);			    							//初始化GPIOB.5
	GPIO_SetBits(GPIOB, GPIO_Pin_5);												//PB.5 输出高
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_5;	            					//LED1-->PE.5推挽输出
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  	        							//初始化GPIO
	GPIO_SetBits(GPIOE, GPIO_Pin_5); 			 									//PE.5 输出高 	 

	/* Init */
	delay_init();
	u8g2_Init(&u8g2);
	
	while(1)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		GPIO_SetBits(GPIOE,GPIO_Pin_5);
		Delay(3000000);
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);
		Delay(3000000);
		u8g2_FirstPage(&u8g2);
		do
		{
			u8g2_SetFontMode(&u8g2, 1);
			u8g2_SetFontDirection(&u8g2, 0);
			u8g2_SetFont(&u8g2, u8g2_font_inb24_mf);
			u8g2_DrawStr(&u8g2, 0, 20, "U");
			u8g2_SetFontDirection(&u8g2, 1);
			u8g2_SetFont(&u8g2, u8g2_font_inb24_mf);
			u8g2_DrawStr(&u8g2, 21, 8, "8");
			u8g2_SetFontDirection(&u8g2, 0);
			u8g2_SetFont(&u8g2, u8g2_font_inb24_mf);
			u8g2_DrawStr(&u8g2, 51, 30, "g");
			u8g2_DrawStr(&u8g2, 67, 30, "\xb2");
			u8g2_DrawHLine(&u8g2, 2, 35, 47);
			u8g2_DrawHLine(&u8g2, 3, 36, 47);
			u8g2_DrawVLine(&u8g2, 45, 32, 12);
			u8g2_DrawVLine(&u8g2, 46, 32, 12);
			u8g2_SetFont(&u8g2, u8g2_font_5x7_tf);
			u8g2_DrawStr(&u8g2, 1, 54, "github.com/olikraus/u8g2");
		} while(u8g2_NextPage(&u8g2));
	}
}


