/**
 * @file tft_st7735s.c
 * @brief ST7735S TFT display driver implementation.
 */

#include "tft_st7735s.h"

#define USE_DMA
#define SPI_WriteData(data)  SPI_ReadWriteByte(SDK_USING_SPI3_DEVICE, (data))

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
#ifndef USE_DMA
u8 SPI_WriteData(u8 TxData) {
    u8 i = 0;

    while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET) // cleaned legacy comment
    {
        i++;
        if(i>200)return 0;
    }

    SPI_I2S_SendData(SPI3, TxData); // cleaned legacy comment
    i = 0;

    while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET) // cleaned legacy comment
    {
        i++;
        if(i>200)return 0;
    }

    return SPI_I2S_ReceiveData(SPI3); // cleaned legacy comment
}
#endif /* USE_DMA */

// cleaned legacy comment
void Lcd_WriteIndex(u8 Index) {
// cleaned legacy comment
    LCD_CS_CLR;
    LCD_RS_CLR;
    SPI_WriteData(Index);
    LCD_CS_SET;
}

// cleaned legacy comment
void Lcd_WriteData(u8 Data) {
    LCD_CS_CLR;
    LCD_RS_SET;
    SPI_WriteData(Data);
    LCD_CS_SET;
}
// cleaned legacy comment
void LCD_WriteData_16Bit(u16 Data) {
    LCD_CS_CLR;
    LCD_RS_SET;
    SPI_WriteData(Data >> 8); // cleaned legacy comment
    SPI_WriteData(Data); // cleaned legacy comment
    LCD_CS_SET;
}

void Lcd_WriteReg(u8 Index, u8 Data) {
    Lcd_WriteIndex(Index);
    Lcd_WriteData(Data);
}

void Lcd_Reset(void) {
    LCD_RST_CLR;
    Delay_Ms(100);
    LCD_RST_SET;
    Delay_Ms(50);
}

//LCD Init For 1.44Inch LCD Panel with ST7735R.
void LCD_INIT(void) {
    LCD_GPIO_Init();
    Lcd_Reset(); //Reset before LCD Init.

    //LCD Init For 1.44Inch LCD Panel with ST7735R.
    Lcd_WriteIndex(0x11); //Sleep exit
    Delay_Ms(120);

    //ST7735R Frame Rate
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

    Lcd_WriteIndex(0xB4); //Column inversion
    Lcd_WriteData(0x07);

    //ST7735R Power Sequence
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

    Lcd_WriteIndex(0xC5); //VCOM
    Lcd_WriteData(0x0E);

    Lcd_WriteIndex(0x36); //MX, MY, RGB mode
    Lcd_WriteData(0xC8);

    //ST7735R Gamma Sequence
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

    Lcd_WriteIndex(0xF0); //Enable test command
    Lcd_WriteData(0x01);
    Lcd_WriteIndex(0xF6); //Disable ram power save mode
    Lcd_WriteData(0x00);

    Lcd_WriteIndex(0x3A); //65k mode
    Lcd_WriteData(0x05);

    Lcd_WriteIndex(0x29); //Display on

    Lcd_Clear(WHITE); // clear lcd
}

/*************************************************
// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
 *************************************************/
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

/*************************************************
// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
 *************************************************/
void Lcd_SetXY(u16 x, u16 y) {
    Lcd_SetRegion(x, y, x, y);
}

/*************************************************
// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
 *************************************************/
void Gui_DrawPoint(u16 x, u16 y, u16 Data) {
    Lcd_SetRegion(x, y, x + 1, y + 1);
    LCD_WriteData_16Bit(Data);

}

void Gui_FillRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
// cleaned legacy comment
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

// cleaned legacy comment
    for (u16 x = x1; x <= x2; x++) {
        for (u16 y = y1; y <= y2; y++) {
            Gui_DrawPoint(x, y, color);
        }
    }
}

/*****************************************
// cleaned legacy comment
// cleaned legacy comment
 ******************************************/
unsigned int Lcd_ReadPoint(u16 x, u16 y) {
    return 0;
}
/*************************************************
// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
 *************************************************/
void Lcd_Clear(u16 Color) {
    unsigned int i, m;
    Lcd_SetRegion(0, 0, X_MAX_PIXEL - 1, Y_MAX_PIXEL - 1);
    Lcd_WriteIndex(0x2C);
    for (i = 0; i < X_MAX_PIXEL; i++)
        for (m = 0; m < Y_MAX_PIXEL; m++) {
            LCD_WriteData_16Bit(Color);
        }
}


void LCD_ON(void)
{
    GPIO_SetBits(GPIOE, GPIO_Pin_10);
}


void LCD_OFF(void)
{
    GPIO_ResetBits(GPIOE, GPIO_Pin_10);
}

