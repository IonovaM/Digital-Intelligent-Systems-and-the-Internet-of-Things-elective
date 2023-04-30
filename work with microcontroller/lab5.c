#include "stm32f4xx.h" 
#include "stm32f4xx_rcc.h" 
#include "stm32f4xx_gpio.h" 
#include "stm32f4xx_exti.h" 
#include "misc.h" 
 
 
GPIO_InitTypeDef GPIO_InitStructure; //объявление структуры настройки портов 
NVIC_InitTypeDef NVIC_InitStructure; //объявление структуры настройки контроллера прерываний 
EXTI_InitTypeDef EXTI_InitStructure; //объявление структуры настройки внешних прерываний 
 
//основная программа 
int main(void) 
{ 
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOA, ENABLE); //тактирование портов и периферии настройка порта D на вывод (светодиоды платы STM32F4Discovery) 
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; //выбор настраиваемых выводов 
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //выбор режима – вывод 
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //тип - push/pull 
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //определение максимальной частоты 
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //без подтяжки 
GPIO_Init(GPIOD, &GPIO_InitStructure); //заполнение объявленной структуры 
 
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //выбор настраиваемых выводов 
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN; // выбор режима - вход 
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // тип - push-pull 
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //подтяжка к земле 
GPIO_Init(GPIOA, &GPIO_InitStructure); //заполнение объявленной структуры 
 
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); //настройка группы приоритетов 
NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn; //выбор источника прерывания 
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //основной приоритет 
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //вложенный приоритет 
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //разрешение прерывания 
NVIC_Init(&NVIC_InitStructure); //заполнение объявленной структуры 
 
EXTI_InitStructure.EXTI_Line=EXTI_Line0; //номер линии внешнего прерывания 
EXTI_InitStructure.EXTI_LineCmd=ENABLE; //разрешение прерывания на линии 
EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt; //прерывание/событие 
EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;  //по переднему фронту 
EXTI_Init(&EXTI_InitStructure); //заполнение объявленной структуры 
while(1) //бесконечный цикл 
{ 
} //while 
} //main 
 
 
 
int a = 0; 
//обработчик внешнего прерывания на нулевой линии 
void EXTI0_IRQHandler(void) 
{ 
 a++; 
 if (a == 1){ 
  for (int j=0;j<3;j++){ 
   for(int i=0;i<1000000;i++){ }//wait 
   GPIO_ToggleBits(GPIOD,GPIO_Pin_12); 
   for(int i=0;i<1000000;i++){ }//wait 
   GPIO_ToggleBits(GPIOD,GPIO_Pin_12); 
   GPIO_ToggleBits(GPIOD,GPIO_Pin_13); 
   for(int i=0;i<1000000;i++){ }//wait 
   GPIO_ToggleBits(GPIOD,GPIO_Pin_13); 
   GPIO_ToggleBits(GPIOD,GPIO_Pin_14); 
   for(int i=0;i<1000000;i++){ }//wait 
   GPIO_ToggleBits(GPIOD,GPIO_Pin_14); 
   GPIO_ToggleBits(GPIOD,GPIO_Pin_15); 
   for(int i=0;i<1000000;i++){ }//wait 
   GPIO_ToggleBits(GPIOD,GPIO_Pin_15); 
  } 
 
 } 
 if (a == 2){ 
  for (int j=0;j<3;j++){ 
   for(int i=0;i<1000000;i++){ }//wait 
   GPIO_ToggleBits(GPIOD,GPIO_Pin_15); 
   for(int i=0;i<1000000;i++){ }//wait 
   GPIO_ToggleBits(GPIOD,GPIO_Pin_15); 
   GPIO_ToggleBits(GPIOD,GPIO_Pin_14); 
   for(int i=0;i<1000000;i++){ }//wait 
   GPIO_ToggleBits(GPIOD,GPIO_Pin_14); 
   GPIO_ToggleBits(GPIOD,GPIO_Pin_13); 
   for(int i=0;i<1000000;i++){ }//wait 
   GPIO_ToggleBits(GPIOD,GPIO_Pin_13); 
   GPIO_ToggleBits(GPIOD,GPIO_Pin_12); 
   for(int i=0;i<1000000;i++){ }//wait 
   GPIO_ToggleBits(GPIOD,GPIO_Pin_12); 
  } 
 } 
 
 if (a == 3) { 
  for (int j=0;j<3;j++){ 
   int b = 0; 
   while(b < 1500) 
   { 
    if (b <= 750){ 
     GPIO_SetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); 
     for(int ti=0;ti<b;ti++){} 
     GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); 
     for(int tp=0;tp<(750-b);tp++){}} 
    else { 
      GPIO_SetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); 
      for(int ti=0; ti<(1500-b); ti++){} 
      GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); 
      for(int tp=0; tp<b-750; tp++){}} 
 
    b++; 
   } //while 
  } 
  a = 0; 
 } 
EXTI_ClearITPendingBit(EXTI_Line0); //очистка флага прерывания 
}