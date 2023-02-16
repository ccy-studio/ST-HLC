//
// Created by 83503 on 2023/2/16.
//

#ifndef ST_HLC_SG90_H
#define ST_HLC_SG90_H

#include "main.h"


#define SG90_ANGLE_MIN 0    // 最小旋转角度
#define SG90_ANGLE_MAX 180  // 最大旋转角度


void SG90_init();
void SG90_rotate_to(uint8_t angle);

#endif //ST_HLC_SG90_H
