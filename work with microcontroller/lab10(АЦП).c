#include "stm32f4xx.h" 
#include "stm32f4xx_rcc.h" 
#include "stm32f4xx_gpio.h" 
#include "stm32f4xx_adc.h" 
 
 
int data=0xFFFF,i=0; //объявление переменных 
ADC_InitTypeDef ADC_InitStructure; //объявление структуры настройки АЦП 
ADC_CommonInitTypeDef ADC_CommonInitStructure; //объявление структуры общей настройки АЦП 
 
GPIO_InitTypeDef GPIO_InitStructure; //объявление структуры настройки портов 
 
//основная программа 
int main(void) 
{ 
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOD, ENABLE); //тактирование портов 
RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //тактирование таймера TIM8 и АЦП1 
 
//настройка PA1 на аналоговый вход (вход АЦП) 
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //выбор настраиваемых выводов 
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN; //режим - аналоговый (для АЦП) 
 
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //без подтягивающего резистора 
 
GPIO_Init(GPIOA, &GPIO_InitStructure); //заполнение объявленной структуры 
 
//настройка порта D на вывод (светодиоды платы STM32F4Discovery) 
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15; //выбор настраиваемых выводов 
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //режим - вывод 
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //тип - push-pull 
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //выбор максимальной частоты 
 
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // без подтягивающего резистора 
 
GPIO_Init(GPIOD, &GPIO_InitStructure); //заполнение объявленнойструктуры 
 
 
//настройка АЦП 
ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent; //режим независимого преобразования 
ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2; //предварительный делитель 
ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //без прямого доступа к памяти 
ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles; //задержка между двумя выборками 
ADC_CommonInit(&ADC_CommonInitStructure); //заполнение объявленной структуры 
 
ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b; //12 битный результат 
 
ADC_InitStructure.ADC_ScanConvMode = DISABLE; //без сканирования 
ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; //непрерывное преобразование запрещено 
 
ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //выравнивание по правому краю 
ADC_InitStructure.ADC_NbrOfConversion = 1; //одно преобразование 
ADC_Init(ADC1, &ADC_InitStructure); //заполнение объявленной структуры 
 
//настройка регулярного канала АЦП1, канал 1, PA1 
ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_3Cycles); 
ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE); //включение прерываний по завершению преобразования 
 
//разрешение прерывания от АЦП 
NVIC_EnableIRQ (ADC_IRQn); 
 
ADC_Cmd(ADC1, ENABLE); //включение АЦП 1 
ADC_SoftwareStartConv(ADC1); 
 
while(1) 
{ 
 
GPIO_SetBits(GPIOD,GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14|GPIO_Pin_15); 
for (i=0;i<data;i++); 
GPIO_ResetBits(GPIOD,GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14|GPIO_Pin_15); 
for (i=0;i<(8000-data);i++); 
 
 
} //while(1) 
} //main 
 
//обработчик прерывания АЦП 
void ADC_IRQHandler(void) 
{ADC_ClearFlag(ADC1, ADC_FLAG_EOC); //Сброс флага 
data=ADC_GetConversionValue(ADC1); //получение результата преобразования 
 
}