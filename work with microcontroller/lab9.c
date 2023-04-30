#include "stm32f4xx.h" 
#include "stm32f4xx_gpio.h" 
#include "stm32f4xx_rcc.h" 
#include "misc.h" 
#include "stm32f4xx_tim.h" 
GPIO_InitTypeDef GPIO_InitStructure; //объявление структуры 
 //настройки портов 
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //объявление структуры 
 //настройки таймера 
TIM_OCInitTypeDef TIM_OCInitStructure; //объявление структуры настройки 
 //выходных каналов таймера 
//основная программа 
int main(void) 
{ 
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
//тактирование таймера TIM1 
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE); //тактирование портов 
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8; //выбор настраиваемых выводов 
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; //выбор режима – 
 //альтернативная функция 
GPIO_InitStructure.GPIO_OType=GPIO_OType_PP; //тип - push/pull 
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //определение 
 //максимальной частоты 
GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP; //подтяжка к питанию 
GPIO_Init(GPIOA,&GPIO_InitStructure); //заполнение объявленной структуры 
GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1); 
//настройка альтернативной функции 8 вывода порта A 
TIM_TimeBaseStructure.TIM_Period = 1000; //значение периода 
TIM_TimeBaseStructure.TIM_Prescaler = 839; //величина предварительного делителя 
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //режим счета вверх 
TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //заполнение объявленной структуры 
 
TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //выбор режима - ШИМ1 
TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //включение выхода 
TIM_OCInitStructure.TIM_Pulse = 60; //время импульса 
TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //полярность выхода 
TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; //инверсный выход выключен 
TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //низкий неактивный уровень 
TIM_OC1Init(TIM1, &TIM_OCInitStructure); //заполнение объявленной cтруктуры 
 
TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); //разрешение предварительной загрузки CCR1 
TIM_ARRPreloadConfig(TIM1,ENABLE); //разрешение предварительной загрузки ARR 
TIM_CtrlPWMOutputs(TIM1, ENABLE); //включение выходов ШИМ, только для таймеров TIM8 и TIM1 
TIM_Cmd(TIM1,ENABLE); //запуск таймера 
 
int a = 0; 
int p = 50; 
while(1) 
{ 
 if (a == 0){ 
  TIM_OCInitStructure.TIM_Pulse = p; 
  TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
  p++; 
  if(p > 99) 
   a = 1; 
  for (int i=0; i<100000; i++) {}; 
 } 
 if (a == 1){ 
  TIM_OCInitStructure.TIM_Pulse = p; 
  TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
  p--; 
  for (int i=0; i<100000; i++) {}; 
  if (p < 1){ 
   p = 50; 
   a = 0;} 
 } 
 
}//while 
}//main#include "stm32f4xx.h" 
#include "stm32f4xx_gpio.h" 
#include "stm32f4xx_rcc.h" 
#include "misc.h" 
#include "stm32f4xx_tim.h" 
GPIO_InitTypeDef GPIO_InitStructure; //объявление структуры 
 //настройки портов 
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //объявление структуры 
 //настройки таймера 
TIM_OCInitTypeDef TIM_OCInitStructure; //объявление структуры настройки 
 //выходных каналов таймера 
//основная программа 
int main(void) 
{ 
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
//тактирование таймера TIM1 
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE); //тактирование портов 
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8; //выбор настраиваемых выводов 
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; //выбор режима – 
 //альтернативная функция 
GPIO_InitStructure.GPIO_OType=GPIO_OType_PP; //тип - push/pull 
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //определение 
 //максимальной частоты 
GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP; //подтяжка к питанию 
GPIO_Init(GPIOA,&GPIO_InitStructure); //заполнение объявленной структуры 
GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1); 
//настройка альтернативной функции 8 вывода порта A 
TIM_TimeBaseStructure.TIM_Period = 1000; //значение периода 
TIM_TimeBaseStructure.TIM_Prescaler = 839; //величина предварительного делителя 
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //режим счета вверх 
TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //заполнение объявленной структуры 
 
TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //выбор режима - ШИМ1 
TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //включение выхода 
TIM_OCInitStructure.TIM_Pulse = 60; //время импульса 
TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //полярность выхода 
TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; //инверсный выход выключен 
TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //низкий неактивный уровень 
TIM_OC1Init(TIM1, &TIM_OCInitStructure); //заполнение объявленной cтруктуры 
 
TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); //разрешение предварительной загрузки CCR1 
TIM_ARRPreloadConfig(TIM1,ENABLE); //разрешение предварительной загрузки ARR 
TIM_CtrlPWMOutputs(TIM1, ENABLE); //включение выходов ШИМ, только для таймеров TIM8 и TIM1 
TIM_Cmd(TIM1,ENABLE); //запуск таймера 
 
int a = 0; 
int p = 50; 
while(1) 
{ 
 if (a == 0){ 
  TIM_OCInitStructure.TIM_Pulse = p; 
  TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
  p++; 
  if(p > 99) 
   a = 1; 
  for (int i=0; i<100000; i++) {}; 
 } 
 if (a == 1){ 
  TIM_OCInitStructure.TIM_Pulse = p; 
  TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
  p--; 
  for (int i=0; i<100000; i++) {}; 
  if (p < 1){ 
   p = 50; 
   a = 0;} 
 } 
 
}//while 
}//main