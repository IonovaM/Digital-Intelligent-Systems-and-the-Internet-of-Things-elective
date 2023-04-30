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
int P = 1; 
//основная программа 
int main(void) 
{ 
 
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); //тактирование таймера TIM8 
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //тактирование порта D 
 
//настройка порта D на вывод (светодиоды платы STM32F4Discovery) 
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15; //выбор настраиваемых выводов 
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //выбор режима – вывод 
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //тип - push/pull 
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //определение максимальной частоты 
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //без подтягивающего резистора 
GPIO_Init(GPIOD, &GPIO_InitStructure); //заполнение объявленной структуры настройки порта D вышеперечисленными параметрами 
 
//настройка таймера 
TIM_InitStructure.TIM_RepetitionCounter = 0; //значение счетчика повторений 
TIM_InitStructure.TIM_Prescaler = 41; //значение предварительного делителя 
TIM_InitStructure.TIM_Period = P; //величина периода счетчика 
TIM_InitStructure.TIM_ClockDivision = 0; //деление частоты 
TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up; //режим счета вверх 
 
TIM_TimeBaseInit(TIM8, &TIM_InitStructure); //заполнение объявленной структуры 
 
TIM_ITConfig(TIM8,TIM_IT_Update,ENABLE); //разрешение прерываний по переполнению таймера 
 
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn ; //выбор источника прерывания 
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //основной приоритет 
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //вложенный приоритет 
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //разрешение прерывания 
NVIC_Init(&NVIC_InitStructure); //заполнение объявленной структуры 
 
TIM_Cmd(TIM8, ENABLE); //включение таймера 8 
 
while(1) {} //while 
} //main 
 
int a = 0; 
//обработчик прерывания таймера 8 
void TIM8_UP_TIM13_IRQHandler(void) 
{ 
 if ((TIM8->SR&0x01) == 1){ 
  switch(a){ 
  if (P<=5000){ 
  case(0): 
  if (a < 5000) { 
   GPIO_SetBits(GPIOD,GPIO_Pin_15); 
   TIM_InitStructure.TIM_Period = P; 
   TIM_TimeBaseInit(TIM8, &TIM_InitStructure); 
   P++; 
   break; 
  } 
  else { 
   GPIO_SetBits(GPIOD,GPIO_Pin_15); 
   TIM_InitStructure.TIM_Period = 10000-P; 
   TIM_TimeBaseInit(TIM8, &TIM_InitStructure); 
   break; 
  } 
 
 
  case(1): 
  if (a < 5000) { 
   GPIO_ResetBits(GPIOD,GPIO_Pin_15); 
   TIM_InitStructure.TIM_Period = 10000-P; 
  } 
  else { 
   GPIO_ResetBits(GPIOD,GPIO_Pin_15); 
   TIM_InitStructure.TIM_Period = P; 
   P--; 
  } 
  TIM_TimeBaseInit(TIM8, &TIM_InitStructure); 
  break; 
  if (a > 1) 
   a = 0; 
  } 
 
} 
  a++; 
} 
TIM_ClearITPendingBit(TIM8, TIM_IT_Update); //очистка флага прерывания 
} 
 
 
 
 
 
 
 
 
/* 
  if ((TIM8->SR&0x01) == 1){ 
  if (a == 0) { 
   GPIO_SetBits(GPIOD,GPIO_Pin_15); 
   I += 1; 
   TIM_InitStructure.TIM_Period = I; 
  } 
 
  if (a == 1) { 
   GPIO_ResetBits(GPIOD,GPIO_Pin_15); 
   P -= 1; 
   TIM_InitStructure.TIM_Period = P; 
   a = 0; 
  } 
  a++; 
 } 
 
  */