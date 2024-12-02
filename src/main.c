#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

void vTask(void *pvParameters);
void vPeriodicTask( void *pvParameters );

vPrintString(const portCHAR *pcString);

int main(void)
{
    xTaskCreate(&vTask, "Task 1", 1024,"Task 1\r\n", 1, NULL);
    xTaskCreate(&vTask, "Task 2", 1024,"Task 2\r\n", 1, NULL);
    xTaskCreate(&vPeriodicTask, "Task 3", 1024, NULL, 2, NULL);

    vTaskStartScheduler();

    return 0;
}

void vTask(void *pvParameters)
{
    char *pcStringToPrint;
    pcStringToPrint = (char *) pvParameters;
    
    for( ;; )
    {
        vPrintString(pcStringToPrint);
        
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}


void vPeriodicTask( void *pvParameters )
{
    portTickType xLastWakeTime;

    xLastWakeTime = xTaskGetTickCount();

    for( ;; )
    {
    
        vPrintString("Periodic task is running\r\n" );

        vTaskDelayUntil( &xLastWakeTime,  pdMS_TO_TICKS(1));
    }
}

 vPrintString(const portCHAR *pcString)
 {
    taskENTER_CRITICAL();
    {
        printf("%s", pcString);
        fflush( stdout );
    }
    taskEXIT_CRITICAL();

    if( kbhit() )
    {
        vTaskEndScheduler();
    }
 }

