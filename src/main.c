#include "main.h"
#include "board/board.h"
#include "bsp/uart/bsp_uart.h"
#include "bsp/LCD/lcd.h"
#include "bsp/LCD/lcd_init.h"

int main(void)
{
    float t = 0.0f;

    board_init();
    uart1_init(115200U);

    LCD_Init();
    LCD_Fill(0, 0, LCD_W, LCD_H, BLACK);

    while (1) {
        LCD_ShowString(60, 16 * 4, (uint8_t *)"LCD_W:", WHITE, BLACK, 16, 0);
        LCD_ShowIntNum(120, 16 * 4, LCD_W, 3, WHITE, BLACK, 16);
        LCD_ShowString(60, 16 * 5, (uint8_t *)"LCD_H:", WHITE, BLACK, 16, 0);
        LCD_ShowIntNum(120, 16 * 5, LCD_H, 3, WHITE, BLACK, 16);

        LCD_ShowString(76, 16 * 6, (uint8_t *)"Nun:", WHITE, BLACK, 16, 0);
        LCD_ShowFloatNum1(120, 16 * 6, t, 4, WHITE, BLACK, 16);
        t += 0.11f;

        delay_ms(1000U);
    }
}

void Error_Handler(void)
{
    __disable_irq();
    while (1) {
    }
}
