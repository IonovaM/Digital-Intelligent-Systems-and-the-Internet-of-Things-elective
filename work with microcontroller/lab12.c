#include "stm32f4xx.h" 
#include "stm32f4xx_rcc.h" 
#include "stm32f4xx_gpio.h" 
#include "stm32f4xx_usart.h" 
#include "stm32f4xx_exti.h" 
#include "misc.h" 
 
GPIO_InitTypeDef GPIO_InitStructure; //объявление структуры настройки 
                                                                      //портов 
USART_InitTypeDef USART_InitStructure; //объявление структуры настройки 
                                                                            //USART 
NVIC_InitTypeDef NVIC_InitStructure; //объявление структуры настройки 
                                                                       //контроллера прерываний 
EXTI_InitTypeDef EXTI_InitStructure; //объявление структуры настройки 
                                                                     //внешних прерываний 
int a[4] = {'0', '0', '0', '0'}; 
int bufer_diod=0; //объявление переменной для приемника USART 
int bufer_sost=0; 
 
//основная программа 
int main(void) { 
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOD, ENABLE); 
RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); 
RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); //тактирование портов и периферии 
 
//настройка порта D на вывод (светодиоды платы STM32F4Discovery) 
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15; //выбор настраиваемых выводов 
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //выбор режима – вывод 
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //тип - push/pull 
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //определение максимальной частоты 
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //без подтягивающего резистора 
GPIO_Init(GPIOD, &GPIO_InitStructure); //заполнение объявленной структуры 
 
//настройка выводов USART (PD8-Tx,PD9-Rx) 
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //выбор режима – альтернативная функция 
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8; //выбор настраиваемых выводов 
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //определение максимальной частоты 
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //тип - push/pull 
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //с подтягивающим резисторов к питанию 
GPIO_Init(GPIOD, &GPIO_InitStructure); //заполнение объявленной структуры 
 
 
GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3); //настройка альтернативной функции 9 вывода порта D 
GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3); //настройка альтернативной функции 8 вывода порта D 
NVIC_EnableIRQ(USART3_IRQn); //разрешение прерываний от USART 
 
USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //использование приема и передачи 
USART_InitStructure.USART_BaudRate = 115200; //скорость 
USART_InitStructure.USART_Parity = USART_Parity_No; //без проверки четности 
USART_InitStructure.USART_StopBits = USART_StopBits_1; //количество стоп бит - 1 
USART_InitStructure.USART_WordLength = USART_WordLength_8b; //длина передаваемого слова - 8 бит 
USART_Init(USART3, &USART_InitStructure); //заполнение объявленной структуры 
 
GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0; //выбор настраиваемых выводов 
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN; //выбор режима - вход 
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //тип - push/pull 
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //с подтягивающим резистором к земле 
GPIO_Init(GPIOA, &GPIO_InitStructure); //заполнение объявленной структуры 
 
 
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); //настройка группы приоритетов 
NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn; //выбор источника прерывания 
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //основной приоритет 
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //вложенный приоритет 
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //разрешение прерывания 
NVIC_Init(&NVIC_InitStructure); //заполнение объявленной структуры 
 
EXTI_InitStructure.EXTI_Line=EXTI_Line0; //номер линии 
EXTI_InitStructure.EXTI_LineCmd=ENABLE; //разрешение прерывания на линии 
 
EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;

//прерывание/событие 
EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising; //по переднему фронту 
 
EXTI_Init(&EXTI_InitStructure); //заполнение объявленной структуры 
 
USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); //разрешение прерывания приемника 
 
USART_Cmd(USART3, ENABLE); //включение USART3 
 
while(1)//бесконечный цикл 
{ 
} //while 
} //main 
//обработчик внешнего прерывания 
void EXTI0_IRQHandler(void) 
{ 
for(int i=0; i<4; i++){ 
 USART_SendData (USART3, a[i]); 
 while(!(USART_GetFlagStatus(USART3,  USART_FLAG_TC))); 
} 
EXTI_ClearITPendingBit(EXTI_Line0); //очистка флага прерывания 
} 
 
 
 
int n = 0; 
//обработчик прерывания USART 
void USART3_IRQHandler(void) 
{ 
// проверка флага приемника 
if( USART_GetITStatus(USART3, USART_IT_RXNE) ) 
{ 
  bufer_diod = USART_ReceiveData(USART3); //считывание данных с USART3 
  while(!(USART_GetFlagStatus(USART3,  USART_FLAG_RXNE))); 
  bufer_sost = USART_ReceiveData(USART3); //считывание данных с USART3 
 
if (bufer_diod == '1'){ 
  if (bufer_sost == '1'){ 
   GPIO_SetBits(GPIOD,GPIO_Pin_12); 
   a[0] = '1';} 
  if (bufer_sost == '0'){ 
   GPIO_ResetBits(GPIOD,GPIO_Pin_12); 
   a[0] = '0';}} 
if (bufer_diod == '2'){ 
  if (bufer_sost == '1'){ 
   GPIO_SetBits(GPIOD,GPIO_Pin_13); 
   a[1] = '1';} 
  if (bufer_sost == '0'){ 
   GPIO_ResetBits(GPIOD,GPIO_Pin_13); 
   a[1] = '0';}} 
if (bufer_diod == '3'){ 
  if (bufer_sost == '1'){ 
   GPIO_SetBits(GPIOD,GPIO_Pin_14); 
   a[2] = '1';} 
  if (bufer_sost == '0'){ 
   GPIO_ResetBits(GPIOD,GPIO_Pin_14); 
   a[2] = '0';}} 
if (bufer_diod == '4'){ 
  if (bufer_sost == '1'){ 
   GPIO_SetBits(GPIOD,GPIO_Pin_15); 
   a[3] = '1';} 
  if (bufer_sost == '0'){ 
   GPIO_ResetBits(GPIOD,GPIO_Pin_15); 
   a[3] = '0';}} 
 
} 
}