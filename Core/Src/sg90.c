//
// Created by 83503 on 2023/2/16.
//
#include "sg90.h"
#include "tim.h"

void SG90_init() {
    HAL_GPIO_WritePin(SG90_V_GPIO_Port, SG90_V_Pin, GPIO_PIN_RESET);
}

void SG90_rotate_to(uint8_t angle) {
    // 限制角度范围在 SG90_ANGLE_MIN 和 SG90_ANGLE_MAX 之间
    angle = angle < SG90_ANGLE_MIN ? SG90_ANGLE_MIN : angle;
    angle = angle > SG90_ANGLE_MAX ? SG90_ANGLE_MAX : angle;

    // 根据角度计算脉冲宽度（单位：us）
    uint16_t pulse_width = 500 + angle * 10 / 18;

    // 计算延时时间（单位：us）
    uint32_t delay_us = 20000 - pulse_width;

    //打开SG90的供电
    //SET 为开漏输出
    HAL_GPIO_WritePin(SG90_V_GPIO_Port, SG90_V_Pin, GPIO_PIN_SET);
    Delay_us(1000);
    // 产生脉冲信号
    HAL_GPIO_WritePin(SG90_D_GPIO_Port, SG90_D_Pin, GPIO_PIN_SET);
    Delay_us(pulse_width);
    HAL_GPIO_WritePin(SG90_D_GPIO_Port, SG90_D_Pin, GPIO_PIN_RESET);
    Delay_us(delay_us);

    //等待一秒拉低电平断电
    HAL_Delay(1000);
    HAL_GPIO_WritePin(SG90_V_GPIO_Port, SG90_V_Pin, GPIO_PIN_RESET);
}