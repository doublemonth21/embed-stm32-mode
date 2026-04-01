#include "lcd_init.h"
#include "board.h"

SPI_HandleTypeDef hspi1;

void LCD_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = LCD_RES_PIN | LCD_DC_PIN | LCD_CS_PIN | LCD_BLK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOA, LCD_RES_PIN | LCD_DC_PIN | LCD_CS_PIN | LCD_BLK_PIN, GPIO_PIN_SET);

    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
    hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 7;

    if (HAL_SPI_Init(&hspi1) != HAL_OK) {
        Error_Handler();
    }
}

void LCD_Writ_Bus(u8 dat)
{
    LCD_CS_Clr();
    if (HAL_SPI_Transmit(&hspi1, &dat, 1U, HAL_MAX_DELAY) != HAL_OK) {
        Error_Handler();
    }
    LCD_CS_Set();
}

void LCD_WR_DATA8(u8 dat)
{
    LCD_Writ_Bus(dat);
}

void LCD_WR_DATA(u16 dat)
{
    LCD_Writ_Bus((u8)(dat >> 8));
    LCD_Writ_Bus((u8)dat);
}

void LCD_WR_REG(u8 dat)
{
    LCD_DC_Clr();
    LCD_Writ_Bus(dat);
    LCD_DC_Set();
}

void LCD_Address_Set(u16 x1, u16 y1, u16 x2, u16 y2)
{
    LCD_WR_REG(0x2A);
    LCD_WR_DATA(x1);
    LCD_WR_DATA(x2);
    LCD_WR_REG(0x2B);
    LCD_WR_DATA(y1);
    LCD_WR_DATA(y2);
    LCD_WR_REG(0x2C);
}

void LCD_Init(void)
{
    LCD_GPIO_Init();

    LCD_RES_Clr();
    delay_ms(100U);
    LCD_RES_Set();
    delay_ms(100U);

    LCD_BLK_Set();
    delay_ms(100U);

    LCD_WR_REG(0xEF);
    LCD_WR_REG(0xEB);
    LCD_WR_DATA8(0x14);

    LCD_WR_REG(0xFE);
    LCD_WR_REG(0xEF);

    LCD_WR_REG(0xEB);
    LCD_WR_DATA8(0x14);

    LCD_WR_REG(0x84);
    LCD_WR_DATA8(0x40);

    LCD_WR_REG(0x85);
    LCD_WR_DATA8(0xFF);

    LCD_WR_REG(0x86);
    LCD_WR_DATA8(0xFF);

    LCD_WR_REG(0x87);
    LCD_WR_DATA8(0xFF);

    LCD_WR_REG(0x88);
    LCD_WR_DATA8(0x0A);

    LCD_WR_REG(0x89);
    LCD_WR_DATA8(0x21);

    LCD_WR_REG(0x8A);
    LCD_WR_DATA8(0x00);

    LCD_WR_REG(0x8B);
    LCD_WR_DATA8(0x80);

    LCD_WR_REG(0x8C);
    LCD_WR_DATA8(0x01);

    LCD_WR_REG(0x8D);
    LCD_WR_DATA8(0x01);

    LCD_WR_REG(0x8E);
    LCD_WR_DATA8(0xFF);

    LCD_WR_REG(0x8F);
    LCD_WR_DATA8(0xFF);

    LCD_WR_REG(0xB6);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x20);

    LCD_WR_REG(0x36);
    if (USE_HORIZONTAL == 0) {
        LCD_WR_DATA8(0x08);
    } else if (USE_HORIZONTAL == 1) {
        LCD_WR_DATA8(0xC8);
    } else if (USE_HORIZONTAL == 2) {
        LCD_WR_DATA8(0x68);
    } else {
        LCD_WR_DATA8(0xA8);
    }

    LCD_WR_REG(0x3A);
    LCD_WR_DATA8(0x05);

    LCD_WR_REG(0x90);
    LCD_WR_DATA8(0x08);
    LCD_WR_DATA8(0x08);
    LCD_WR_DATA8(0x08);
    LCD_WR_DATA8(0x08);

    LCD_WR_REG(0xBD);
    LCD_WR_DATA8(0x06);

    LCD_WR_REG(0xBC);
    LCD_WR_DATA8(0x00);

    LCD_WR_REG(0xFF);
    LCD_WR_DATA8(0x60);
    LCD_WR_DATA8(0x01);
    LCD_WR_DATA8(0x04);

    LCD_WR_REG(0xC3);
    LCD_WR_DATA8(0x13);
    LCD_WR_REG(0xC4);
    LCD_WR_DATA8(0x13);

    LCD_WR_REG(0xC9);
    LCD_WR_DATA8(0x22);

    LCD_WR_REG(0xBE);
    LCD_WR_DATA8(0x11);

    LCD_WR_REG(0xE1);
    LCD_WR_DATA8(0x10);
    LCD_WR_DATA8(0x0E);

    LCD_WR_REG(0xDF);
    LCD_WR_DATA8(0x21);
    LCD_WR_DATA8(0x0C);
    LCD_WR_DATA8(0x02);

    LCD_WR_REG(0xF0);
    LCD_WR_DATA8(0x45);
    LCD_WR_DATA8(0x09);
    LCD_WR_DATA8(0x08);
    LCD_WR_DATA8(0x08);
    LCD_WR_DATA8(0x26);
    LCD_WR_DATA8(0x2A);

    LCD_WR_REG(0xF1);
    LCD_WR_DATA8(0x43);
    LCD_WR_DATA8(0x70);
    LCD_WR_DATA8(0x72);
    LCD_WR_DATA8(0x36);
    LCD_WR_DATA8(0x37);
    LCD_WR_DATA8(0x6F);

    LCD_WR_REG(0xF2);
    LCD_WR_DATA8(0x45);
    LCD_WR_DATA8(0x09);
    LCD_WR_DATA8(0x08);
    LCD_WR_DATA8(0x08);
    LCD_WR_DATA8(0x26);
    LCD_WR_DATA8(0x2A);

    LCD_WR_REG(0xF3);
    LCD_WR_DATA8(0x43);
    LCD_WR_DATA8(0x70);
    LCD_WR_DATA8(0x72);
    LCD_WR_DATA8(0x36);
    LCD_WR_DATA8(0x37);
    LCD_WR_DATA8(0x6F);

    LCD_WR_REG(0xED);
    LCD_WR_DATA8(0x1B);
    LCD_WR_DATA8(0x0B);

    LCD_WR_REG(0xAE);
    LCD_WR_DATA8(0x77);

    LCD_WR_REG(0xCD);
    LCD_WR_DATA8(0x63);

    LCD_WR_REG(0x70);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x04);
    LCD_WR_DATA8(0x0E);
    LCD_WR_DATA8(0x0F);
    LCD_WR_DATA8(0x09);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x08);
    LCD_WR_DATA8(0x03);

    LCD_WR_REG(0xE8);
    LCD_WR_DATA8(0x34);

    LCD_WR_REG(0x62);
    LCD_WR_DATA8(0x18);
    LCD_WR_DATA8(0x0D);
    LCD_WR_DATA8(0x71);
    LCD_WR_DATA8(0xED);
    LCD_WR_DATA8(0x70);
    LCD_WR_DATA8(0x70);
    LCD_WR_DATA8(0x18);
    LCD_WR_DATA8(0x0F);
    LCD_WR_DATA8(0x71);
    LCD_WR_DATA8(0xEF);
    LCD_WR_DATA8(0x70);
    LCD_WR_DATA8(0x70);

    LCD_WR_REG(0x63);
    LCD_WR_DATA8(0x18);
    LCD_WR_DATA8(0x11);
    LCD_WR_DATA8(0x71);
    LCD_WR_DATA8(0xF1);
    LCD_WR_DATA8(0x70);
    LCD_WR_DATA8(0x70);
    LCD_WR_DATA8(0x18);
    LCD_WR_DATA8(0x13);
    LCD_WR_DATA8(0x71);
    LCD_WR_DATA8(0xF3);
    LCD_WR_DATA8(0x70);
    LCD_WR_DATA8(0x70);

    LCD_WR_REG(0x64);
    LCD_WR_DATA8(0x28);
    LCD_WR_DATA8(0x29);
    LCD_WR_DATA8(0xF1);
    LCD_WR_DATA8(0x01);
    LCD_WR_DATA8(0xF1);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x07);

    LCD_WR_REG(0x66);
    LCD_WR_DATA8(0x3C);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0xCD);
    LCD_WR_DATA8(0x67);
    LCD_WR_DATA8(0x45);
    LCD_WR_DATA8(0x45);
    LCD_WR_DATA8(0x10);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x00);

    LCD_WR_REG(0x67);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x3C);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x01);
    LCD_WR_DATA8(0x54);
    LCD_WR_DATA8(0x10);
    LCD_WR_DATA8(0x32);
    LCD_WR_DATA8(0x98);

    LCD_WR_REG(0x74);
    LCD_WR_DATA8(0x10);
    LCD_WR_DATA8(0x85);
    LCD_WR_DATA8(0x80);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x4E);
    LCD_WR_DATA8(0x00);

    LCD_WR_REG(0x98);
    LCD_WR_DATA8(0x3E);
    LCD_WR_DATA8(0x07);

    LCD_WR_REG(0x35);
    LCD_WR_REG(0x21);

    LCD_WR_REG(0x11);
    delay_ms(120U);
    LCD_WR_REG(0x29);
    delay_ms(20U);
}
