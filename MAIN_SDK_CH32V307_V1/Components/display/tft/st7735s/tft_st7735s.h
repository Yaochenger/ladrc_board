/**
 * @file tft_st7735s.h
 * @brief ST7735S TFT display driver interface.
 */

#ifndef USER_PERIPHERAL_DRIVER_TFT_ST7735S_TFT_ST7735S_H_
#define USER_PERIPHERAL_DRIVER_TFT_ST7735S_TFT_ST7735S_H_

#include "spi.h"

#define X_MAX_PIXEL         128
#define Y_MAX_PIXEL         128

#define RED     0xf800
#define GREEN   0x07e0
#define BLUE    0x001f
#define WHITE   0xffff
#define BLACK   0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D // cleaned legacy comment
#define GRAY1   0x8410 // cleaned legacy comment
#define GRAY2   0x4208 // cleaned legacy comment

#define LCD_LED_SET
#define LCD_LED_CLR

#define LCD_CS_CLR  GPIO_ResetBits(GPIOA,GPIO_Pin_15)//CS
#define LCD_CS_SET  GPIO_SetBits(GPIOA,GPIO_Pin_15)

#define LCD_RS_CLR  GPIO_ResetBits(GPIOD,GPIO_Pin_14)//DC
#define LCD_RS_SET  GPIO_SetBits(GPIOD,GPIO_Pin_14)

#define LCD_RST_CLR GPIO_ResetBits(GPIOD,GPIO_Pin_12)//RES
#define LCD_RST_SET GPIO_SetBits(GPIOD,GPIO_Pin_12)


void LCD_GPIO_Init(void);
void LCD_ON(void);
void LCD_OFF(void);
void Lcd_WriteIndex(u8 Index);
void Lcd_WriteData(u8 Data);
void Lcd_WriteReg(u8 Index, u8 Data);
u16 Lcd_ReadReg(u8 LCD_Reg);
void Lcd_Reset(void);
void LCD_INIT(void);
void Lcd_Clear(u16 Color);
void Lcd_SetXY(u16 x, u16 y);
void Gui_DrawPoint(u16 x, u16 y, u16 Data);
void Gui_FillRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
unsigned int Lcd_ReadPoint(u16 x, u16 y);
void Lcd_SetRegion(u16 x_start, u16 y_start, u16 x_end, u16 y_end);
void LCD_WriteData_16Bit(u16 Data);
#endif /* USER_PERIPHERAL_DRIVER_TFT_ST7735S_TFT_ST7735S_H_ */


