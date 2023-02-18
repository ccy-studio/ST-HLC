//
// Created by 83503 on 2023/2/16.
//
#include "sg90.h"
#include "tim.h"

void SG90_init() {
    HAL_GPIO_WritePin(SG90_V_GPIO_Port, SG90_V_Pin, GPIO_PIN_RESET);
}

void SG90_rotate_to(uint8_t angle) {

}