/*
 * IR RAW Code Capture Tool v1.0
 *
 * Copyright 2020 Expert Ninja
 *
 */

/*
 * Based on Home Accessory Architect (HAA) by José Antonio Jiménez Campos (@RavenSystem), licensed under Apache License 2.0.
 * https://github.com/RavenSystem/esp-homekit-devices
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <esp/uart.h>
#include <FreeRTOS.h>
#include <task.h>
#include <espressif/esp_common.h>

#include "../common/ir_code.h"

#define IR_RX_TASK_SIZE         (configMINIMAL_STACK_SIZE * 4)
#define IR_RX_TASK_PRIORITY     (tskIDLE_PRIORITY + 8)

#ifndef IR_RX_GPIO
#define IR_RX_GPIO              3
#endif // IR_RX_GPIO

bool read, last = true;
uint16_t buffer[1024], i, c = 0;
uint32_t new_time, current_time;

void ir_task() {
    current_time = sdk_system_get_time();

    for (;;) {
        read = gpio_read(IR_RX_GPIO);
        if (read != last) {
            new_time = sdk_system_get_time();
            buffer[c] = new_time - current_time;
            current_time = new_time;
            last = read;
            c++;
        }

        if (sdk_system_get_time() - current_time > UINT16_MAX) {
            current_time = sdk_system_get_time();
            if (c > 0) {

                printf("Packets: %i\n", c - 1);
                printf("Standard Format\n");
                for (i = 1; i < c; i++) {
                    printf("%s%5d ", i & 1 ? "+" : "-", buffer[i]);

                    if ((i - 1) % 16 == 15) {
                        printf("\n");
                    }
                }
                printf("\n\n");

                printf("ESPY RAW Format\n");
                for (i = 1; i < c; i++) {
                    char code[] = "00";

                    haa_code[0] = baseRaw_dic[(buffer[i] / IR_CODE_SCALE) / IR_CODE_LEN];
                    haa_code[1] = baseRaw_dic[(buffer[i] / IR_CODE_SCALE) % IR_CODE_LEN];

                    printf("%s", code);
                }
                printf("\n\n");

                c = 0;
            }
        }
    }
}

void user_init() {
    sdk_wifi_station_set_auto_connect(false);
    sdk_wifi_set_opmode(STATION_MODE);
    sdk_wifi_station_disconnect();

    uart_set_baud(0, 115200);

    printf("\n\nEspy House IR RAW Code Capture Tool v1.0\n");
    printf("IR RX Data GPIO: %i\n\n", IR_RX_GPIO);

    gpio_enable(IR_RX_GPIO, GPIO_INPUT);

    xTaskCreate(ir_task, "ir_task", IR_RX_TASK_SIZE, NULL, IR_RX_TASK_PRIORITY, NULL);
}
