//
// Created by 83503 on 2023/2/16.
//

#include "service_main.h"
#include "sg90.h"

/* 定义全局变量，用于存储红外接收数据 */
uint16_t IRvalue = 0;    // 键码值
uint8_t IRcount = 0;     // 接收计数器
uint8_t IRstatus = 0;    // 接收状态标志

volatile int ledGroupOpenState = 0;
volatile int sg90OpenState = 0;

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
    handlerLEDGroup(ledGroupOpenState);
    handlerSG90(sg90OpenState);
}


/**
 * 下降沿触发回调函数
 * @param GPIO_Pin
 */
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == VS1838B_Pin) {
        //如果是红外头引脚触发中断
        static uint32_t lastTime = 0;
        uint32_t currentTime = HAL_GetTick();
        uint32_t timeInterval = currentTime - lastTime;
        lastTime = currentTime;

        if (timeInterval > 1000)  // 起始位
        {
            IRvalue = 0;
            IRcount = 0;
            IRstatus = 1;
        } else if (IRstatus == 1)   // 数据位
        {
            if (timeInterval > 500)
                IRvalue |= (1 << IRcount);
            IRcount++;

            if (IRcount >= 8)  // 接收完成
            {
//                printf("IR value: %04x\n", IRvalue);
                IRcount = 0;
                IRstatus = 0;
                IRvalue = 0;
            }
        }
    }
}

void handlerSmallLED(int openState) {
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