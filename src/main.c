#include <stdbool.h>
#include <stm8s.h>
#include "main.h"
#include "milis.h"

void init(void) {
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // Taktování MCU na 16MHz

    #define LED1_PORT GPIOB
    #define LED1_PIN GPIO_PIN_1
    #define LED2_PORT GPIOB
    #define LED2_PIN GPIO_PIN_2
    #define LED3_PORT GPIOB
    #define LED3_PIN GPIO_PIN_3

    init_milis();
}

int main(void) {
    uint8_t BTNstate = 1;
    uint8_t lastBTNstate = 1;
    uint8_t led_out = 1;

    init();

    while (1) {
        BTNstate = (bool)GPIO_ReadInputPin(BTN_PORT, BTN_PIN);
        //BTNstate = READ(BTN);

        if (lastBTNstate == 0 && BTNstate == 1) {
            led_out += 1;
        }


        if (led_out > 3) {
            led_out = 1;
        }

        // Nastavení výstupů pro LED
        if (led_out == 1) {
            HIGH(LED1);
            LOW(LED3);
        } else if (led_out == 2) {
            HIGH(LED2);
            LOW(LED1);
        } else {
            HIGH(LED3);
            LOW(LED2);
        }
        lastBTNstate = BTNstate;
    }
}
