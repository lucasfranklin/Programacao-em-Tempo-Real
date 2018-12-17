//Foi implementado Mutex no ajuste de hora do projeto, agora ao ajustar a hora todas as outras tarefas estarão suspensas até a operação seja finalizada.

#include <Arduino_FreeRTOS.h>
#include <LiquidCrystal.h>
#include <semphr.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

SemaphoreHandle_t xSemaphore  = NULL;  //Cria Mutex do tipo semaforo na biblioteca FreeRTOS

//Pinagem
#define btPin1 6
#define btPin2 7
#define tempPin A0

//Variáveis Auxiliares
int count = 0;
int val1, val2;

//Temperatura
int tempC;
int tempMed;
int temperatura;

//Tempo
int h=0; 
int m; 
int s; 

// define as tarefas
void ajustarHora(void *pvParameters);
void mostrarTemperatura(void *pvParameters);
void mostrarHora(void *pvParameters);


void setup() {

  xTaskCreate(
    mostrarHora
    ,  (const portCHAR *)"mostrarHora"
    ,  128 
    ,  NULL
    ,  1  // prioridade 1
    ,  NULL );

  xTaskCreate(
      mostrarTemperatura
      ,  (const portCHAR *)"mostrarTemperatura"
      ,  128 // This stack size can be checked & adjusted by reading Highwater
      ,  NULL
      ,  2  // prioridade 2
      ,  NULL );


  xTaskCreate(
    ajustarHora
    ,  (const portCHAR *)"ajustarHora"   
    ,  128  // Stack size
    ,  NULL
    ,  3  // prioridade 3
    ,  NULL );
  // Configurações para que as tarefas rodem concorrentemente


  //Cria o mutex
  xSemaphore = xSemaphoreCreateMutex();

  
  Serial.begin(9600);
}

void loop()
{
  // Vazio
}

/*---------------------- Tarefas ---------------------*/

// Ajustar Hora
void ajustarHora(void *pvParameters){

  (void) pvParameters;

  pinMode(btPin1, INPUT);    
  pinMode(btPin2, INPUT);  
  lcd.begin(16, 2);
  
  for (;;) // Loop para tarefa número 1
  {
   
  val1 = digitalRead(btPin1); 
  
  if (val1 == LOW) { 
    if( xSemaphore != NULL ) {  //Testa se o semaforo foi criado
    if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE ) { //Checa se está livre        
      m = m + 1;  
      Serial.println(val1);
      lcd.clear();
      xSemaphoreGive( xSemaphore );  //Libera as outras threads
  }
  }
  }

  val2 = digitalRead(btPin2); 
  
  if (val2 == HIGH) {
    if( xSemaphore != NULL ) {  //Testa se o semaforo foi criado
    if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE ) { //Checa se está livre               
      h = h + 1;  
      Serial.println(h);
      lcd.clear();
      xSemaphoreGive( xSemaphore );  //Libera as outras threads
  }
  }
  }

  if(s==60){ 
   s=0; 
   m=m+1; 
  } 
  if(m==60) 
  { 
   m=0; 
   h=h+1; 
  } 
  
  if(h==24) 
  { 
   h=0; 
  } 
 
    vTaskDelay(1);
  }
}

// Mostrar Hora
void mostrarHora(void *pvParameters){

  (void) pvParameters;
  
  for (;;) // Loop para tarefa número 2
  {

  s=s+1; 
  
  delay(1000); // Delay de 1 segundo
  
  if(s==60){ 
   s=0; 
   m=m+1; 
  } 
  if(m==60) 
  { 
   m=0; 
   h=h+1; 
  } 
  
  if(h==24) 
  { 
   h=0; 
  } 
   //Imprime do display LCD
  lcd.setCursor(0, 0);
  lcd.print("Hora:");lcd.print(h, 10);
  lcd.print(":"); lcd.print(m, 10);
  lcd.print(":");lcd.print(s, 10);

  vTaskDelay(1);
}
}

// Mostrar Temperatura
void mostrarTemperatura(void *pvParameters){

  (void) pvParameters;
  
  for (;;) // Loop para tarefa número 3
  {
    tempC = leitura_LM35(); // Leitura a partir da função de amostragem
    // Imprime no display de LCD
    lcd.setCursor(0, 1);
    lcd.print("Temp:"); lcd.print(tempC, 10); lcd.print(" Graus");
    vTaskDelay(1);
  }
}

//Leitura da porta análogica através de amostragem
int leitura_LM35(){

  pinMode(tempPin, INPUT);
  
  tempMed=0;
  int i;
  int amostragem = 100;

  for(i=0; i<amostragem; i++){
    temperatura = (float(analogRead(tempPin))*5/(1023))/0.01;
    tempMed = tempMed + temperatura;
  }
  tempMed = tempMed/amostragem;
  return tempMed;
}
