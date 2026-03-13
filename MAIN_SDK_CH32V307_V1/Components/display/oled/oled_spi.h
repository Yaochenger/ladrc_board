/**
 * @file oled_spi.h
 * @brief OLED SPI display driver interface.
 */

#ifndef USER_PERIPHERAL_DRIVER_OLED_SPI_OLED_SPI_H_
#define USER_PERIPHERAL_DRIVER_OLED_SPI_OLED_SPI_H_

#include "ch32v30x.h"
#include "stdlib.h"

/* OLED control pins. */
#define OLED_RES_Clr() GPIO_ResetBits(GPIOD,GPIO_Pin_12)
#define OLED_RES_Set() GPIO_SetBits(GPIOD,GPIO_Pin_12)

#define OLED_DC_Clr()  GPIO_ResetBits(GPIOD,GPIO_Pin_14)
#define OLED_DC_Set()  GPIO_SetBits(GPIOD,GPIO_Pin_14)

#define OLED_CS_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_15)
#define OLED_CS_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_15)

#define OLED_CMD  0
#define OLED_DATA 1

/**
 * @brief Exchange one byte on the SPI bus.
 * @param TxData Byte to transmit.
 * @return Received byte.
 */
u8 SPI1_ReadWriteByte(u8 TxData);

/**
 * @brief Clear a single pixel.
 * @param x X coordinate.
 * @param y Y coordinate.
 */
void OLED_ClearPoint(u8 x,u8 y);

/**
 * @brief Configure normal or inverse display mode.
 * @param i `0` for normal display, `1` for inverse display.
 */
void OLED_ColorTurn(u8 i);

/**
 * @brief Configure display scan direction.
 * @param i `0` for normal orientation, `1` for flipped orientation.
 */
void OLED_DisplayTurn(u8 i);

/**
 * @brief Write one byte to the OLED controller.
 * @param dat Data or command byte.
 * @param mode `OLED_CMD` for command, `OLED_DATA` for data.
 */
void OLED_WR_Byte(u8 dat,u8 mode);

/**
 * @brief Turn on the OLED panel.
 */
void OLED_DisPlay_On(void);

/**
 * @brief Turn off the OLED panel.
 */
void OLED_DisPlay_Off(void);

/**
 * @brief Flush the GRAM buffer to the panel.
 */
void OLED_Refresh(void);

/**
 * @brief Clear the whole display buffer and refresh the panel.
 */
void OLED_Clear(void);

/**
 * @brief Draw or clear one pixel in the buffer.
 * @param x X coordinate.
 * @param y Y coordinate.
 * @param t Non-zero to set the pixel, zero to clear it.
 */
void OLED_DrawPoint(u8 x,u8 y,u8 t);

/**
 * @brief Draw a line between two points.
 * @param x1 Start X coordinate.
 * @param y1 Start Y coordinate.
 * @param x2 End X coordinate.
 * @param y2 End Y coordinate.
 * @param mode Pixel write mode.
 */
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);

/**
 * @brief Draw a circle outline.
 * @param x Center X coordinate.
 * @param y Center Y coordinate.
 * @param r Radius.
 */
void OLED_DrawCircle(u8 x,u8 y,u8 r);

/**
 * @brief Draw one ASCII character.
 * @param x Start X coordinate.
 * @param y Start Y coordinate.
 * @param chr Character code.
 * @param size1 Font height.
 * @param mode Pixel write mode.
 */
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode);

/**
 * @brief Draw one 6x8 ASCII character.
 * @param x Start X coordinate.
 * @param y Start Y coordinate.
 * @param chr Character code.
 * @param mode Pixel write mode.
 */
void OLED_ShowChar6x8(u8 x,u8 y,u8 chr,u8 mode);

/**
 * @brief Draw a null-terminated ASCII string.
 * @param x Start X coordinate.
 * @param y Start Y coordinate.
 * @param chr String pointer.
 * @param size1 Font height.
 * @param mode Pixel write mode.
 */
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);

/**
 * @brief Draw an unsigned decimal number.
 * @param x Start X coordinate.
 * @param y Start Y coordinate.
 * @param num Number value.
 * @param len Display width in digits.
 * @param size1 Font height.
 * @param mode Pixel write mode.
 */
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);

/**
 * @brief Draw one Chinese glyph from the built-in font table.
 * @param x Start X coordinate.
 * @param y Start Y coordinate.
 * @param num Glyph index.
 * @param size1 Font size.
 * @param mode Pixel write mode.
 */
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);

/**
 * @brief Scroll Chinese glyphs continuously across the screen.
 * @param num Number of glyphs.
 * @param space Spacing between glyphs.
 * @param mode Pixel write mode.
 */
void OLED_ScrollDisplay(u8 num,u8 space,u8 mode);

/**
 * @brief Draw a bitmap.
 * @param x Start X coordinate.
 * @param y Start Y coordinate.
 * @param sizex Bitmap width.
 * @param sizey Bitmap height.
 * @param BMP Bitmap data pointer.
 * @param mode Pixel write mode.
 */
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode);

/**
 * @brief Initialize the OLED controller and clear the screen.
 */
void OLED_Init(void);

#endif /* USER_PERIPHERAL_DRIVER_OLED_SPI_OLED_SPI_H_ */

