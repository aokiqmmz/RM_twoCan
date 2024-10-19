//
// Created by h on 2024/10/12.
//

#include "can.h"

CAN_RxHeaderTypeDef header;
uint8_t data[8];

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan) {
    if (hcan->Instance == CAN1) {
        if (HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &header, data) == HAL_OK) {
            HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
        }
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == KEY_Pin) {
        CAN_TxHeaderTypeDef header;
        header.StdId = 0x200;
        header.IDE = CAN_ID_STD;
        header.RTR = CAN_RTR_DATA;
        header.DLC = 1;

        uint8_t data = 0;

        uint32_t mailbox;

        HAL_CAN_AddTxMessage(&hcan1, &header, &data, &mailbox);
    }
}