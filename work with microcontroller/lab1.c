#include "stm32f4xx.h" 
#include "stm32f4xx_rcc.h" 
#include "stm32f4xx_gpio.h" 
GPIO_InitTypeDef GPIO_InitStructure; //объявление структуры настройки 
//портов 
//основная программа 
int main(void) 
{ 
 const fr=1000000; 
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOA, ENABLE); //тактирование портов и периферии 
//настройка порта D на вывод (светодиоды платы STM32F4Discovery) 
 
GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //выбор настраиваемых 
 //выводов 
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //выбор режима – 
 //вывод 
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //тип - push/pull 
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //определение 
 //максимальной частоты 
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //без 
 //подтягивающего резистора 
GPIO_Init(GPIOD, &GPIO_InitStructure); //заполнение объявленной 
 //структуры 
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; // выбор настраиваемых выводов 
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; // выбор режима - вход 
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // тип - push-pull 
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //подтяжка к земле 
GPIO_Init(GPIOA, &GPIO_InitStructure); //заполнение объявленной 
 //структуры 
while(1) //бесконечный цикл 
{ 
if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0) //считывание 
 //состояния нажатия кнопки 
{ 
for(int i=0;i<fr;i++){ 
}//wait 
GPIO_ToggleBits(GPIOD,GPIO_Pin_12); 
for(int i=0;i<fr;i++){ 
}//wait 
GPIO_ToggleBits(GPIOD,GPIO_Pin_12); 
GPIO_ToggleBits(GPIOD,GPIO_Pin_13); 
for(int i=0;i<fr;i++){ 
}//wait 
GPIO_ToggleBits(GPIOD,GPIO_Pin_13); 
GPIO_ToggleBits(GPIOD,GPIO_Pin_14); 
for(int i=0;i<fr;i++){ 
}//wait 
GPIO_ToggleBits(GPIOD,GPIO_Pin_14); 
GPIO_ToggleBits(GPIOD,GPIO_Pin_15); 
for(int i=0;i<fr;i++){ 
}//wait 
GPIO_ToggleBits(GPIOD,GPIO_Pin_15); 
}//if 
else{ 
 for(int i=0;i<fr;i++){ 
 }//wait 
 GPIO_ToggleBits(GPIOD,GPIO_Pin_15); 
 for(int i=0;i<fr;i++){ 
 }//wait 
 GPIO_ToggleBits(GPIOD,GPIO_Pin_15); 
 GPIO_ToggleBits(GPIOD,GPIO_Pin_14); 
 for(int i=0;i<fr;i++){ 
 }//wait 
 GPIO_ToggleBits(GPIOD,GPIO_Pin_14); 
 GPIO_ToggleBits(GPIOD,GPIO_Pin_13); 
 for(int i=0;i<fr;i++){ 
 }//wait 
 GPIO_ToggleBits(GPIOD,GPIO_Pin_13); 
 GPIO_ToggleBits(GPIOD,GPIO_Pin_12); 
 for(int i=0;i<fr;i++){ 
 }//wait 
 GPIO_ToggleBits(GPIOD,GPIO_Pin_12); 
} 
} //while 
} //main