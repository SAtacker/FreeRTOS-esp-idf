#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

SemaphoreHandle_t bi_sema_1 = NULL;
SemaphoreHandle_t bi_sema_2 = NULL;
static int shared_int = 0;

void led_blink_1()
{
    const char task[] = "led blink 1";
    while (1)
    {

        if (bi_sema_1 != NULL)
        {
            // See if we can obtain the semaphore.  If the semaphore is not
            // available wait 10 ticks to see if it becomes free.
            if (xSemaphoreTake(bi_sema_1, portMAX_DELAY) == pdTRUE)
            {
                // We were able to obtain the semaphore and can now access the
                // shared resource.
                shared_int += 1;
                // ...
                ESP_LOGI(task, "Semaphore 1 Taken Succesfully | Shared Res - %d", shared_int);
                // We have finished accessing the shared resource.  Release the
                // semaphore.
                if (xSemaphoreTake(bi_sema_2, portMAX_DELAY) == pdTRUE)
                {
                    // We were able to obtain the semaphore and can now access the
                    // shared resource.
                    shared_int -= 1;
                    // ...
                    ESP_LOGI(task, "Semaphore 2 Taken Succesfully | Shared Res - %d", shared_int);
                }
                else
                {
                    // We could not obtain the semaphore and can therefore not
                    // access the shared resource safely.
                    ESP_LOGW(task, "Failed in taking Semaphore 2");
                }
                xSemaphoreGive(bi_sema_1);
                xSemaphoreGive(bi_sema_2);
            }
            else
            {
                // We could not obtain the semaphore and can therefore not
                // access the shared resource safely.
                ESP_LOGW(task, "Failed in taking Semaphore 1");
            }
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void led_blink_2()
{
    const char task[] = "led blink 2";
    while (1)
    {
        if (bi_sema_2 != NULL)
        {
            // See if we can obtain the semaphore.  If the semaphore is not
            // available wait 10 ticks to see if it becomes free.
            if (xSemaphoreTake(bi_sema_2, portMAX_DELAY) == pdTRUE)
            {
                // We were able to obtain the semaphore and can now access the
                // shared resource.
                shared_int -= 1;
                // ...
                ESP_LOGI(task, "Semaphore 2 Taken Succesfully | Shared Res - %d", shared_int);
                // We have finished accessing the shared resource.  Release the
                // semaphore.
                if (xSemaphoreTake(bi_sema_1, portMAX_DELAY) == pdTRUE)
                {
                    // We were able to obtain the semaphore and can now access the
                    // shared resource.
                    shared_int -= 1;
                    // ...
                    ESP_LOGI(task, "Semaphore 1 Taken Succesfully | Shared Res - %d", shared_int);
                }
                else
                {
                    // We could not obtain the semaphore and can therefore not
                    // access the shared resource safely.
                    ESP_LOGW(task, "Failed in taking Semaphore 1");
                }
                xSemaphoreGive(bi_sema_2);
                xSemaphoreGive(bi_sema_1);
            }
            else
            {
                // We could not obtain the semaphore and can therefore not
                // access the shared resource safely.
                ESP_LOGW(task, "Failed in taking Semaphore 2");
            }
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    bi_sema_1 = xSemaphoreCreateBinary();
    bi_sema_2 = xSemaphoreCreateBinary();
    // xSemaphoreCreateBinary() Creates a new binary semaphore instance, and
    // returns a handle by which the new semaphore can be referenced.

    xSemaphoreGive(bi_sema_1);
    xSemaphoreGive(bi_sema_2);
    // The semaphore must be given before it can be taken if calls are made
    // using xSemaphoreCreateBinary()

    xTaskCreate(&led_blink_1, "Led Blink 1", 4096, NULL, 0, NULL);
    xTaskCreate(&led_blink_2, "Led Blink 2", 4096, NULL, 1, NULL);
}