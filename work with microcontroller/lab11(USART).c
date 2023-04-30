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
 
 
/*if (n == 0){ 
  bufer_diod = USART_ReceiveData(USART3); //считывание данных с USART3 
  while(!(USART_GetFlagStatus(USART3,  USART_FLAG_RXNE))); 
  n++; 
 } 
 if (n == 1){ 
  bufer_sost = USART_ReceiveData(USART3); //считывание данных с USART3 
  n--; 
 } 
 
 
switch(bufer_diod){ 
case(1): 
  if (bufer_sost == '1'){ 
   GPIO_SetBits(GPIOD,GPIO_Pin_12); } 
  if (bufer_sost == '0'){ 
   GPIO_ResetBits(GPIOD,GPIO_Pin_12); } 
case(2): 
  if (bufer_sost == '1'){ 
   GPIO_SetBits(GPIOD,GPIO_Pin_13); } 
  if (bufer_sost == '0'){ 
   GPIO_ResetBits(GPIOD,GPIO_Pin_13); } 
case(3): 
  if (bufer_sost == '1'){ 
   GPIO_SetBits(GPIOD,GPIO_Pin_14); } 
  if (bufer_sost == '0'){ 
   GPIO_ResetBits(GPIOD,GPIO_Pin_14); } 
case(4): 
  if (bufer_sost == '1'){ 
   GPIO_SetBits(GPIOD,GPIO_Pin_15); } 
  if (bufer_sost == '0'){ 
   GPIO_ResetBits(GPIOD,GPIO_Pin_15); } 
 
*/ 
} 
}
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