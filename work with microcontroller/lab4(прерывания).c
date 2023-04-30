#include "stm32f4xx.h" 
#include "stm32f4xx_rcc.h" 
#include "stm32f4xx_gpio.h" 
#include "stm32f4xx_tim.h" 
#include "misc.h" 
GPIO_InitTypeDef GPIO_InitStructure; //объявление структуры настройки 
 //портов 
TIM_TimeBaseInitTypeDef TIM_InitStructure; //объявление структуры 
 //настройки таймера 
NVIC_InitTypeDef NVIC_InitStructure; //объявление структуры настройки 
 //контроллера прерываний 
//основная программа 
int period = 1; 
int a; 
int main(void) 
{ 
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); 
//тактирование таймера TIM8 
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 
//тактирование порта D 
//настройка порта D на вывод (светодиоды платы STM32F4Discovery) 
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| 
GPIO_Pin_14| GPIO_Pin_15; //выбор настраиваемых выводов 
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //выбор режима – 
 //вывод 
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //тип - push/pull 
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //определение 
 //максимальной частоты 
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //без 
 //подтягивающего резистора 
GPIO_Init(GPIOD, &GPIO_InitStructure); //заполнение объявленной 
 //структуры настройки порта D 
 //вышеперечисленными 
//параметрами 
//настройка таймера 
TIM_InitStructure.TIM_RepetitionCounter = 0; //значение счетчика повторений 
TIM_InitStructure.TIM_Prescaler = 200; //значение предварительного делителя 
TIM_InitStructure.TIM_Period = period; //величина периода счетчика 
TIM_InitStructure.TIM_ClockDivision = 0; //деление частоты 
TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up; //режим 
 //счета вверх 
TIM_TimeBaseInit(TIM8, &TIM_InitStructure); //заполнение объявленной 
 //структуры 
TIM_ITConfig(TIM8,TIM_IT_Update,ENABLE); //разрешение прерываний 
 //по переполнению таймера 
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn ; //выбор 
 //источника прерывания 
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //основной 
 //приоритет 
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //вложенный 
 //приоритет 
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //разрешение 
 //прерывания 
NVIC_Init(&NVIC_InitStructure); //заполнение объявленной структуры 
TIM_Cmd(TIM8, ENABLE); //включение таймера 8 
while(1) 
{ 
} //while 
} //main 
//обработчик прерывания таймера 8 
void TIM8_UP_TIM13_IRQHandler(void) 
{ 
 
 switch(a){ 
 case(1): 
   GPIO_ToggleBits(GPIOD,GPIO_Pin_12); 
   period = 2*period; 
   TIM_InitStructure.TIM_Period =period; 
   TIM_TimeBaseInit(TIM8, &TIM_InitStructure); 
   break; 
 
 case(2): 
   GPIO_ToggleBits(GPIOD,GPIO_Pin_13); 
   period = 2*period; 
   TIM_InitStructure.TIM_Period =period; 
      TIM_TimeBaseInit(TIM8, &TIM_InitStructure); 
   break; 
 case(3): 
   GPIO_ToggleBits(GPIOD,GPIO_Pin_14); 
   period = 2*period; 
   TIM_InitStructure.TIM_Period =period; 
   TIM_TimeBaseInit(TIM8, &TIM_InitStructure); 
   break; 
 case(4): 
   GPIO_ToggleBits(GPIOD,GPIO_Pin_15); 
   period = 2*period; 
   TIM_InitStructure.TIM_Period =period; 
   TIM_TimeBaseInit(TIM8, &TIM_InitStructure); 
   break; 
 } 
 a++; 
 if (a>4){ 
  a = 1; 
 } 
 
} 
 
 TIM_ClearITPendingBit(TIM8, TIM_IT_Update); //очистка флага прерывания 
 
}