#include <Arduino_FreeRTOS.h>
// define as duas tarefas, Blink e AnalogRead
void TaskBlink( void *pvParameters );
void TaskAnalogRead( void *pvParameters );
void setup() {
  
  // inicializa a comunicação serial a 115200 bits/s:
  Serial.begin(115200);
  
  while (!Serial) {
    ; // Somente para placas que usam ATMEGA 32u4.
  }
  // Criando as tarefas (Tasks)
  xTaskCreate(
    TaskBlink
    ,  (const portCHAR *)"Blink" // Nome
    ,  128 // Stack size
    ,  NULL
    , 1   // Prioridade
    ,  NULL );
  xTaskCreate(
    TaskAnalogRead
    ,  (const portCHAR *) "AnalogRead" // Nome
    ,  128  // Stack size
    ,  NULL
    ,  2  // Prioridade
    ,  NULL );
}
void loop()
{
  // Vazio. Todo trabalho já foi feito nas Tasks.
}
/*---------------------- Tasks ---------------------*/
void TaskBlink(void *pvParameters)  // Isto é uma tarefa
{
  (void) pvParameters;
  pinMode(LED_BUILTIN, OUTPUT);
  for (;;)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay( 1000 / portTICK_PERIOD_MS );
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay( 1000 / portTICK_PERIOD_MS );
  }
}
void TaskAnalogRead(void *pvParameters)
{
  (void) pvParameters;
  
  for (;;)
  {
    int sensorValue = analogRead(A0);
    Serial.println(sensorValue);
    vTaskDelay(1);
  }
}
