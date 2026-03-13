/**
 * @file oled_spi.c
 * @brief OLED SPI display driver implementation.
 */

#include "stdlib.h"
#include "oledfont.h"
#include "oled_spi.h"
#include "spi.h"

u8 OLED_GRAM[144][8];

/*******************************************************************************
 * Function Name  : SPI1_ReadWriteByte
 * Description    : SPI1 read or write one byte.
 * Input          : TxData: write one byte data.
 * Return         : Read one byte data.
 *******************************************************************************/

// cleaned legacy comment
void OLED_ColorTurn(u8 i) {
    if (i == 0) {
        OLED_WR_Byte(0xA6, OLED_CMD); // cleaned legacy comment
    }
    if (i == 1) {
        OLED_WR_Byte(0xA7, OLED_CMD); // cleaned legacy comment
    }
}

// cleaned legacy comment
void OLED_DisplayTurn(u8 i) {
    if (i == 0) {
        OLED_WR_Byte(0xC8, OLED_CMD); // cleaned legacy comment
        OLED_WR_Byte(0xA1, OLED_CMD);
    }
    if (i == 1) {
        OLED_WR_Byte(0xC0, OLED_CMD); // cleaned legacy comment
        OLED_WR_Byte(0xA0, OLED_CMD);
    }
}

void OLED_WR_Byte(u8 dat, u8 cmd) {

    if (cmd)
        OLED_DC_Set();
    else
        OLED_DC_Clr();

    OLED_CS_Clr();

    SPI_ReadWriteByte(SDK_USING_SPI3_DEVICE, dat);

    OLED_CS_Set();

    OLED_DC_Set();
}

// cleaned legacy comment
void OLED_DisPlay_On(void) {
    OLED_WR_Byte(0x8D, OLED_CMD); // cleaned legacy comment
    OLED_WR_Byte(0x14, OLED_CMD); // cleaned legacy comment
    OLED_WR_Byte(0xAF, OLED_CMD); // cleaned legacy comment
}

// cleaned legacy comment
void OLED_DisPlay_Off(void) {
    OLED_WR_Byte(0x8D, OLED_CMD); // cleaned legacy comment
    OLED_WR_Byte(0x10, OLED_CMD); // cleaned legacy comment
    OLED_WR_Byte(0xAE, OLED_CMD); // cleaned legacy comment
}

// cleaned legacy comment
void OLED_Refresh(void) {
    u8 i, n;
    for (i = 0; i < 8; i++) {
        OLED_WR_Byte(0xb0 + i, OLED_CMD); // cleaned legacy comment
        OLED_WR_Byte(0x00, OLED_CMD); // cleaned legacy comment
        OLED_WR_Byte(0x10, OLED_CMD); // cleaned legacy comment
        for (n = 0; n < 128; n++)
            OLED_WR_Byte(OLED_GRAM[n][i], OLED_DATA);
    }
}
// cleaned legacy comment
void OLED_Clear(void) {
    u8 i, n;
    for (i = 0; i < 8; i++) {
        for (n = 0; n < 128; n++) {
            OLED_GRAM[n][i] = 0; // cleaned legacy comment
        }
    }
    OLED_Refresh(); // cleaned legacy comment
}

// cleaned legacy comment
//x:0~127
//y:0~63
// cleaned legacy comment
void OLED_DrawPoint(u8 x, u8 y, u8 t) {
    u8 i, m, n;
    i = y / 8;
    m = y % 8;
    n = 1 << m;
    if (t) {
        OLED_GRAM[x][i] |= n;
    } else {
        OLED_GRAM[x][i] = ~OLED_GRAM[x][i];
        OLED_GRAM[x][i] |= n;
        OLED_GRAM[x][i] = ~OLED_GRAM[x][i];
    }
}

// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
void OLED_DrawLine(u8 x1, u8 y1, u8 x2, u8 y2, u8 mode) {
    u16 t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1; // cleaned legacy comment
    delta_y = y2 - y1;
    uRow = x1; // cleaned legacy comment
    uCol = y1;
    if (delta_x > 0)
        incx = 1; // cleaned legacy comment
    else if (delta_x == 0)
        incx = 0; // cleaned legacy comment
    else {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0; // cleaned legacy comment
    else {
        incy = -1;
        delta_y = -delta_x;
    }
    if (delta_x > delta_y)
        distance = delta_x; // cleaned legacy comment
    else
        distance = delta_y;
    for (t = 0; t < distance + 1; t++) {
        OLED_DrawPoint(uRow, uCol, mode); // cleaned legacy comment
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance) {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance) {
            yerr -= distance;
            uCol += incy;
        }
    }
}
// cleaned legacy comment
// cleaned legacy comment
void OLED_DrawCircle(u8 x, u8 y, u8 r) {
    int a, b, num;
    a = 0;
    b = r;
    while(2 * b * b >= r * r)
    {
        OLED_DrawPoint(x + a, y - b,1);
        OLED_DrawPoint(x - a, y - b,1);
        OLED_DrawPoint(x - a, y + b,1);
        OLED_DrawPoint(x + a, y + b,1);

        OLED_DrawPoint(x + b, y + a,1);
        OLED_DrawPoint(x + b, y - a,1);
        OLED_DrawPoint(x - b, y - a,1);
        OLED_DrawPoint(x - b, y + a,1);

        a++;
        num = (a * a + b * b) - r*r; // cleaned legacy comment
        if(num > 0)
        {
            b--;
            a--;
        }
    }
}

// cleaned legacy comment
//x:0~127
//y:0~63
// cleaned legacy comment
// cleaned legacy comment
void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 size1, u8 mode) {
    u8 i, m, temp, size2, chr1;
    u8 x0 = x, y0 = y;
    if (size1 == 8)
        size2 = 6;
    else
        size2 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * (size1 / 2); // cleaned legacy comment
    chr1 = chr - ' '; // cleaned legacy comment
    for (i = 0; i < size2; i++) {
        if (size1 == 8) {
            temp = asc2_0806[chr1][i];
        } // cleaned legacy comment
        else if (size1 == 12) {
            temp = asc2_1206[chr1][i];
        } // cleaned legacy comment
        else if (size1 == 16) {
            temp = asc2_1608[chr1][i];
        } // cleaned legacy comment
        else if (size1 == 24) {
            temp = asc2_2412[chr1][i];
        } // cleaned legacy comment
        else
            return;
        for (m = 0; m < 8; m++) {
            if (temp & 0x01)
                OLED_DrawPoint(x, y, mode);
            else
                OLED_DrawPoint(x, y, !mode);
            temp >>= 1;
            y++;
        }
        x++;
        if ((size1 != 8) && ((x - x0) == size1 / 2)) {
            x = x0;
            y0 = y0 + 8;
        }
        y = y0;
    }
}

// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
void OLED_ShowString(u8 x, u8 y, u8 *chr, u8 size1, u8 mode) {
    while((*chr>=' ')&&(*chr<='~')) // cleaned legacy comment
    {
        OLED_ShowChar(x,y,*chr,size1,mode);
        if(size1==8)x+=6;
        else x+=size1/2;
        chr++;
    }
}

//m^n
u32 OLED_Pow(u8 m, u8 n) {
    u32 result = 1;
    while(n--)
    {
        result*=m;
    }
    return result;
}

// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size1, u8 mode) {
    u8 t, temp, m = 0;
    if (size1 == 8)
        m = 2;
    for (t = 0; t < len; t++) {
        temp = (num / OLED_Pow(10, len - t - 1)) % 10;
        if (temp == 0) {
            OLED_ShowChar(x + (size1 / 2 + m) * t, y, '0', size1, mode);
        } else {
            OLED_ShowChar(x + (size1 / 2 + m) * t, y, temp + '0', size1, mode);
        }
    }
}

// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
void OLED_ShowChinese(u8 x, u8 y, u8 num, u8 size1, u8 mode) {
    u8 m, temp;
    u8 x0 = x, y0 = y;
    u16 i, size3 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * size1; // cleaned legacy comment
    for (i = 0; i < size3; i++) {
        if (size1 == 16) {
            temp = Hzk1[num][i];
        } // cleaned legacy comment
        else if (size1 == 24) {
            temp = Hzk2[num][i];
        } // cleaned legacy comment
        else if (size1 == 32) {
            temp = Hzk3[num][i];
        } // cleaned legacy comment
        else if (size1 == 64) {
            temp = Hzk4[num][i];
        } // cleaned legacy comment
        else
            return;
        for (m = 0; m < 8; m++) {
            if (temp & 0x01)
                OLED_DrawPoint(x, y, mode);
            else
                OLED_DrawPoint(x, y, !mode);
            temp >>= 1;
            y++;
        }
        x++;
        if ((x - x0) == size1) {
            x = x0;
            y0 = y0 + 8;
        }
        y = y0;
    }
}

// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
void OLED_ScrollDisplay(u8 num, u8 space, u8 mode) {
    u8 i, n, t = 0, m = 0, r;
    while(1)
    {
        if(m==0)
        {
            OLED_ShowChinese(128,24,t,16,mode); // cleaned legacy comment
            t++;
        }
        if(t==num)
        {
            for(r=0;r<16*space;r++) // cleaned legacy comment
            {
                for(i=1;i<144;i++)
                {
                    for(n=0;n<8;n++)
                    {
                        OLED_GRAM[i-1][n]=OLED_GRAM[i][n];
                    }
                }
                OLED_Refresh();
            }
            t=0;
        }
        m++;
        if(m==16) {m=0;}
        for(i=1;i<144;i++) // cleaned legacy comment
        {
            for(n=0;n<8;n++)
            {
                OLED_GRAM[i-1][n]=OLED_GRAM[i][n];
            }
        }
        OLED_Refresh();
    }
}

// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
// cleaned legacy comment
void OLED_ShowPicture(u8 x, u8 y, u8 sizex, u8 sizey, u8 BMP[], u8 mode) {
    u16 j = 0;
    u8 i, n, temp, m;
    u8 x0 = x, y0 = y;
    sizey = sizey / 8 + ((sizey % 8) ? 1 : 0);
    for (n = 0; n < sizey; n++) {
        for (i = 0; i < sizex; i++) {
            temp = BMP[j];
            j++;
            for (m = 0; m < 8; m++) {
                if (temp & 0x01)
                    OLED_DrawPoint(x, y, mode);
                else
                    OLED_DrawPoint(x, y, !mode);
                temp >>= 1;
                y++;
            }
            x++;
            if ((x - x0) == sizex) {
                x = x0;
                y0 = y0 + 8;
            }
            y = y0;
        }
    }
}

// cleaned legacy comment
void OLED_Init(void) {
    SPI_GPIO_Init(SDK_USING_SPI3_DEVICE);

    OLED_RES_Clr();
    Delay_Ms(200);
    OLED_RES_Set();

    OLED_WR_Byte(0xAE, OLED_CMD);   //--turn off oled panel
    OLED_WR_Byte(0x00, OLED_CMD);   //---set low column address
    OLED_WR_Byte(0x10, OLED_CMD);   //---set high column address
    OLED_WR_Byte(0x40, OLED_CMD); //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WR_Byte(0x81, OLED_CMD);   //--set contrast control register
    OLED_WR_Byte(0xCF, OLED_CMD);   // Set SEG Output Current Brightness
// cleaned legacy comment
// cleaned legacy comment
    OLED_WR_Byte(0xA6, OLED_CMD);   //--set normal display
    OLED_WR_Byte(0xA8, OLED_CMD);   //--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3f, OLED_CMD);   //--1/64 duty
    OLED_WR_Byte(0xD3, OLED_CMD); //-set display offset   Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WR_Byte(0x00, OLED_CMD);   //-not offset
    OLED_WR_Byte(0xd5, OLED_CMD); //--set display clock divide ratio/oscillator frequency
    OLED_WR_Byte(0x80, OLED_CMD); //--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WR_Byte(0xD9, OLED_CMD);   //--set pre-charge period
    OLED_WR_Byte(0xF1, OLED_CMD); //Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WR_Byte(0xDA, OLED_CMD);   //--set com pins hardware configuration
    OLED_WR_Byte(0x12, OLED_CMD);
    OLED_WR_Byte(0xDB, OLED_CMD);   //--set vcomh
    OLED_WR_Byte(0x40, OLED_CMD);   //Set VCOM Deselect Level
    OLED_WR_Byte(0x20, OLED_CMD);   //-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WR_Byte(0x02, OLED_CMD);   //
    OLED_WR_Byte(0x8D, OLED_CMD);   //--set Charge Pump enable/disable
    OLED_WR_Byte(0x14, OLED_CMD);   //--set(0x10) disable
    OLED_WR_Byte(0xA4, OLED_CMD);   // Disable Entire Display On (0xa4/0xa5)
    OLED_WR_Byte(0xA6, OLED_CMD);   // Disable Inverse Display On (0xa6/a7)
    OLED_Clear();
    OLED_WR_Byte(0xAF, OLED_CMD);
}


