//
// Created by 83503 on 2023/2/16.
//

#include "service_main.h"
#include "sg90.h"



int ledGroupOpenState = 0;
int sg90OpenState = 0;

void handlerSG90(int openState);

void handlerLEDGroup(int openState);

void handlerSmallLED(int openState);


void Main_Init() {
    SG90_init();
}


/**
 * 程序运行入口
 */
void Main_RUN() {
    HAL_GPIO_WritePin(SG90_V_GPIO_Port, SG90_V_Pin, GPIO_PIN_SET);
    handlerSmallLED(0);
//    handlerSG90(0);
    HAL_Delay(500);

    handlerLEDGroup(ledGroupOpenState);
//    handlerSG90(1);
    handlerSmallLED(1);

    HAL_Delay(500);

}

void handlerSmallLED(int openState) {
    openState = !openState;
    if (openState) {
        HAL_GPIO_WritePin(S_LED_GPIO_Port, S_LED_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(S_LED_GPIO_Port, S_LED_Pin, GPIO_PIN_RESET);
    }
}

void handlerLEDGroup(int openState) {
    if (openState) {
        HAL_GPIO_WritePin(L_LED_GPIO_Port, L_LED_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(L_LED_GPIO_Port, L_LED_Pin, GPIO_PIN_RESET);
    }
}

void handlerSG90(int openState) {
    if (openState) {
        SG90_rotate_to(25);
    } else {
        SG90_rotate_to(0);
    }
}