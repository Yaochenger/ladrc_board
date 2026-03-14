/**
 * @file tft_st7735s.c
 * @brief ST7735S TFT display driver implementation.
 */

#include "tft_st7735s.h"

/**
 * @brief Initialize the TFT control GPIOs and SPI pins.
 */
void LCD_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    SPI_GPIO_Init(SDK_USING_SPI3_DEVICE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_SetBits(GPIOE, GPIO_Pin_10);
}

/**
 * @brief Write an LCD command.
 * @param Index Command byte.
 */
void Lcd_WriteIndex(u8 Index) {
    LCD_CS_CLR;
    LCD_RS_CLR;
    SPI_ReadWriteByte(SDK_USING_SPI3_DEVICE, Index);
    LCD_CS_SET;
}

/**
 * @brief Write one byte of LCD data.
 * @param Data Data byte.
 */
void Lcd_WriteData(u8 Data) {
    LCD_CS_CLR;
    LCD_RS_SET;
    SPI_ReadWriteByte(SDK_USING_SPI3_DEVICE, Data);
    LCD_CS_SET;
}

/**
 * @brief Write one 16-bit pixel value in RGB565 format.
 * @param Data Pixel data.
 */
void LCD_WriteData_16Bit(u16 Data) {
    LCD_CS_CLR;
    LCD_RS_SET;
    SPI_ReadWriteByte(SDK_USING_SPI3_DEVICE, Data >> 8);
    SPI_ReadWriteByte(SDK_USING_SPI3_DEVICE, Data);
    LCD_CS_SET;
}

/**
 * @brief Write one LCD register.
 * @param Index Register address.
 * @param Data Register value.
 */
void Lcd_WriteReg(u8 Index, u8 Data) {
    Lcd_WriteIndex(Index);
    Lcd_WriteData(Data);
}

/**
 * @brief Reset the LCD hardware.
 */
void Lcd_Reset(void) {
    LCD_RST_CLR;
    Delay_Ms(100);
    LCD_RST_SET;
    Delay_Ms(50);
}

/**
 * @brief Initialize the ST7735S controller.
 */
void LCD_INIT(void) {
    LCD_GPIO_Init();
    Lcd_Reset();

    /* Exit sleep mode. */
    Lcd_WriteIndex(0x11);
    Delay_Ms(120);

    /* Frame rate control. */
    Lcd_WriteIndex(0xB1);
    Lcd_WriteData(0x01);
    Lcd_WriteData(0x2C);
    Lcd_WriteData(0x2D);

    Lcd_WriteIndex(0xB2);
    Lcd_WriteData(0x01);
    Lcd_WriteData(0x2C);
    Lcd_WriteData(0x2D);

    Lcd_WriteIndex(0xB3);
    Lcd_WriteData(0x01);
    Lcd_WriteData(0x2C);
    Lcd_WriteData(0x2D);
    Lcd_WriteData(0x01);
    Lcd_WriteData(0x2C);
    Lcd_WriteData(0x2D);

    /* Column inversion. */
    Lcd_WriteIndex(0xB4);
    Lcd_WriteData(0x07);

    /* Power sequence configuration. */
    Lcd_WriteIndex(0xC0);
    Lcd_WriteData(0xA2);
    Lcd_WriteData(0x02);
    Lcd_WriteData(0x84);
    Lcd_WriteIndex(0xC1);
    Lcd_WriteData(0xC5);

    Lcd_WriteIndex(0xC2);
    Lcd_WriteData(0x0A);
    Lcd_WriteData(0x00);

    Lcd_WriteIndex(0xC3);
    Lcd_WriteData(0x8A);
    Lcd_WriteData(0x2A);
    Lcd_WriteIndex(0xC4);
    Lcd_WriteData(0x8A);
    Lcd_WriteData(0xEE);

    /* VCOM configuration. */
    Lcd_WriteIndex(0xC5);
    Lcd_WriteData(0x0E);

    /* Memory data access control: MX, MY, RGB mode. */
    Lcd_WriteIndex(0x36);
    Lcd_WriteData(0xC8);

    /* Positive gamma correction. */
    Lcd_WriteIndex(0xe0);
    Lcd_WriteData(0x0f);
    Lcd_WriteData(0x1a);
    Lcd_WriteData(0x0f);
    Lcd_WriteData(0x18);
    Lcd_WriteData(0x2f);
    Lcd_WriteData(0x28);
    Lcd_WriteData(0x20);
    Lcd_WriteData(0x22);
    Lcd_WriteData(0x1f);
    Lcd_WriteData(0x1b);
    Lcd_WriteData(0x23);
    Lcd_WriteData(0x37);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x07);
    Lcd_WriteData(0x02);
    Lcd_WriteData(0x10);

    /* Negative gamma correction. */
    Lcd_WriteIndex(0xe1);
    Lcd_WriteData(0x0f);
    Lcd_WriteData(0x1b);
    Lcd_WriteData(0x0f);
    Lcd_WriteData(0x17);
    Lcd_WriteData(0x33);
    Lcd_WriteData(0x2c);
    Lcd_WriteData(0x29);
    Lcd_WriteData(0x2e);
    Lcd_WriteData(0x30);
    Lcd_WriteData(0x30);
    Lcd_WriteData(0x39);
    Lcd_WriteData(0x3f);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x07);
    Lcd_WriteData(0x03);
    Lcd_WriteData(0x10);

    Lcd_WriteIndex(0x2a);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x7f);

    Lcd_WriteIndex(0x2b);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x9f);

    /* Enable test command set and disable RAM power save mode. */
    Lcd_WriteIndex(0xF0);
    Lcd_WriteData(0x01);
    Lcd_WriteIndex(0xF6);
    Lcd_WriteData(0x00);

    /* 16-bit RGB565 color mode. */
    Lcd_WriteIndex(0x3A);
    Lcd_WriteData(0x05);

    /* Turn display on and clear the screen. */
    Lcd_WriteIndex(0x29);

    Lcd_Clear(WHITE);
}

/**
 * @brief Set the active drawing region.
 * @param x_start Start X coordinate.
 * @param y_start Start Y coordinate.
 * @param x_end End X coordinate.
 * @param y_end End Y coordinate.
 */
void Lcd_SetRegion(u16 x_start, u16 y_start, u16 x_end, u16 y_end) {
    Lcd_WriteIndex(0x2a);
    Lcd_WriteData(0x00);
    Lcd_WriteData(x_start + 2);
    Lcd_WriteData(0x00);
    Lcd_WriteData(x_end + 2);

    Lcd_WriteIndex(0x2b);
    Lcd_WriteData(0x00);
    Lcd_WriteData(y_start + 3);
    Lcd_WriteData(0x00);
    Lcd_WriteData(y_end + 3);

    Lcd_WriteIndex(0x2c);
}

/**
 * @brief Set the current drawing position.
 * @param x X coordinate.
 * @param y Y coordinate.
 */
void Lcd_SetXY(u16 x, u16 y) {
    Lcd_SetRegion(x, y, x, y);
}

/**
 * @brief Draw a single pixel.
 * @param x X coordinate.
 * @param y Y coordinate.
 * @param Data Pixel color in RGB565 format.
 */
void Gui_DrawPoint(u16 x, u16 y, u16 Data) {
    Lcd_SetRegion(x, y, x + 1, y + 1);
    LCD_WriteData_16Bit(Data);
}

/**
 * @brief Fill a rectangle with a solid color.
 * @param x1 First corner X coordinate.
 * @param y1 First corner Y coordinate.
 * @param x2 Opposite corner X coordinate.
 * @param y2 Opposite corner Y coordinate.
 * @param color Fill color in RGB565 format.
 */
void Gui_FillRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color) {
    if (x1 > x2) {
        u16 temp = x1;
        x1 = x2;
        x2 = temp;
    }
    if (y1 > y2) {
        u16 temp = y1;
        y1 = y2;
        y2 = temp;
    }

    for (u16 x = x1; x <= x2; x++) {
        for (u16 y = y1; y <= y2; y++) {
            Gui_DrawPoint(x, y, color);
        }
    }
}

/**
 * @brief Read the pixel color at the specified coordinate.
 * @note Readback is not implemented for this driver.
 * @param x X coordinate.
 * @param y Y coordinate.
 * @return Always returns 0.
 */
unsigned int Lcd_ReadPoint(u16 x, u16 y) {
    return 0;
}

/**
 * @brief Clear the full screen with a solid color.
 * @param Color Fill color in RGB565 format.
 */
void Lcd_Clear(u16 Color) {
    unsigned int i, m;

    Lcd_SetRegion(0, 0, X_MAX_PIXEL - 1, Y_MAX_PIXEL - 1);
    Lcd_WriteIndex(0x2C);

    for (i = 0; i < X_MAX_PIXEL; i++) {
        for (m = 0; m < Y_MAX_PIXEL; m++) {
            LCD_WriteData_16Bit(Color);
        }
    }
}

/**
 * @brief Turn on the LCD backlight.
 */
void LCD_ON(void) {
    GPIO_SetBits(GPIOE, GPIO_Pin_10);
}

/**
 * @brief Turn off the LCD backlight.
 */
void LCD_OFF(void) {
    GPIO_ResetBits(GPIOE, GPIO_Pin_10);
}

