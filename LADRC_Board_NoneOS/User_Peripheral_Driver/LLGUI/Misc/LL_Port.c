/*
 * Copyright 2021-2022 Ou Jianbo 59935554@qq.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * additional license
 * If you use this software to write secondary development type products,
 * must be released under GPL compatible free software license or commercial
 * license.
*/

#include "LL_Port.h"
#include "string.h"
#include "LL_User.h"
#include "tlsf.h"

#define MIRROR_X(x,w) ((x)=(w-1)-(x))
#define MIRROR_Y(y,h) ((y)=(h-1)-(y))
#define SWAP(x,y) ((x) = (x)+(y),(y)=(x)-(y),(x)=(x)-(y))


#define ROTATE0_XY(x,y)
#define ROTATE0_RECT(x0,y0,x1,y1)

#define ROTATE90_XY(x,y)                  SWAP((x),(y));MIRROR_X((x),LL_MONITOR_WIDTH)
#define ROTATE90_RECT(x0,y0,x1,y1)        SWAP(x0,y0);MIRROR_X(x0,LL_MONITOR_WIDTH);SWAP(x1,y1);MIRROR_X(x1,LL_MONITOR_WIDTH);SWAP(x0,x1)

#define ROTATE180_XY(x,y)                  MIRROR_X((x),LL_MONITOR_WIDTH);MIRROR_Y((y),LL_MONITOR_HEIGHT)
#define ROTATE180_RECT(x0,y0,x1,y1)        MIRROR_X(x0,LL_MONITOR_WIDTH);MIRROR_Y(y0,LL_MONITOR_HEIGHT);MIRROR_X(x1,LL_MONITOR_WIDTH);MIRROR_Y(y1,LL_MONITOR_HEIGHT);SWAP(x0,x1);SWAP(y0,y1)

#define ROTATE270_XY(x,y)                  SWAP((x),(y));MIRROR_Y((y),LL_MONITOR_HEIGHT)
#define ROTATE270_RECT(x0,y0,x1,y1)        SWAP(x0,y0);MIRROR_Y(y0,LL_MONITOR_HEIGHT);SWAP(x1,y1);MIRROR_Y(y1,LL_MONITOR_HEIGHT);SWAP(y0,y1)


void llDoubleBufferStart(bool isCopy)
{
#if USE_DOUBLE_BUFFERING == 1
    llCfgDoubleBufferStart(isCopy);
#endif
}

void llDoubleBufferEnd(bool isRefreshNow)
{
#if USE_DOUBLE_BUFFERING == 1
    llCfgDoubleBufferEnd(isRefreshNow);
#endif
}

static void lcdRotateXY(uint16_t lcdAngle,int16_t *x,int16_t *y)
{
    switch(lcdAngle)
    {
        case 0:
        {
            ROTATE0_XY(*x,*y);
            break;
        }
        case 90:
        {
            ROTATE90_XY(*x,*y);
            break;
        }
        case 180:
        {
            ROTATE180_XY(*x,*y);
            break;
        }
        case 270:
        {
            ROTATE270_XY(*x,*y);
            break;
        }
        default:
            break;
    }
}

static void lcdRotateRect(uint16_t lcdAngle,int16_t *x0,int16_t *y0,int16_t *x1,int16_t *y1)
{
    switch(lcdAngle)
    {
        case 0:
        {
            ROTATE0_RECT(*x0,*y0,*x1,*y1);
            break;
        }
        case 90:
        {
            ROTATE90_RECT(*x0,*y0,*x1,*y1);
            break;
        }
        case 180:
        {
            ROTATE180_RECT(*x0,*y0,*x1,*y1);
            break;
        }
        case 270:
        {
            ROTATE270_RECT(*x0,*y0,*x1,*y1);
            break;
        }
        default:
            break;
    }
}

bool llClickGetPoint(int16_t *x,int16_t *y)
{
    bool touchState=false;
    
	touchState=llCfgClickGetPoint(x,y);
    lcdRotateXY(llUserGetAngle(),x,y);
    
    return touchState;
}

void llSetPoint(int16_t x,int16_t y,llColor color)
{
    lcdRotateXY(llUserGetAngle(),&x,&y);
    llCfgSetPoint(x,y,color);
}

void llFillSingleColor(int16_t x0,int16_t y0,int16_t x1,int16_t y1,llColor color)
{
    lcdRotateRect(llUserGetAngle(),&x0,&y0,&x1,&y1);
#if USE_USER_FILL_COLOR == 1
    llCfgFillSingleColor(x0,y0,x1,y1,color);
#else
    uint16_t height,width;
    uint16_t i,j;
    width=x1-x0+1;
    height=y1-y0+1;
    for(i=0; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            llSetPoint(x0+j,y0+i,color);
        }
    }
#endif
}

void llFillMultipleColors(int16_t x0,int16_t y0,int16_t x1,int16_t y1,llColor *color)
{
#if USE_USER_FILL_MULTIPLE_COLORS == 1
    llCfgFillMultipleColors(x0,y0,x1,y1,color);
#else
    uint16_t height,width;
    uint16_t i,j;
    width=x1-x0+1;
    height=y1-y0+1;
    for(i=0; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            llSetPoint(x0+j,y0+i,color[i*width+j]);
        }
    }
#endif
}

#if USE_USER_MEM == 0
static void * pTlsfMem=NULL;
__attribute__((aligned(4))) static uint8_t tlsfMemBuf[MEM_SIZE];

void *llMalloc(uint32_t size)
{
    if(pTlsfMem==NULL)
    {
        pTlsfMem = tlsf_create_with_pool((void *)tlsfMemBuf, MEM_SIZE);
    }
    return tlsf_malloc(pTlsfMem,size);
}

void llFree(void *p)
{
    tlsf_free(pTlsfMem, p);
}

void *llRealloc(void *ptr,uint32_t newSize)
{
    return tlsf_realloc(pTlsfMem, ptr, newSize);
}
#endif

void llDrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, llColor color)
{
    uint16_t t;
	int32_t xerr=0,yerr=0,delta_x,delta_y,distance;
	int32_t incx,incy,uRow,uCol;

    //判读是否为V线H线
    if((x0==x1)||(y0==y1))
    {
        if(y0>y1)
        {
            SWAP(y0,y1);
        }
        if(x0>x1)
        {
            SWAP(x0,x1);
        }
        llFillSingleColor(x0,y0,x1,y1,color);
    }

	delta_x=x1-x0; //计算坐标增量
	delta_y=y1-y0;
	uRow=x0;
	uCol=y0;
	if(delta_x>0)incx=1; //设置单步方向
	else if(delta_x==0)incx=0;//垂直线
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if(delta_y==0)incy=0;//水平线
	else{incy=-1;delta_y=-delta_y;}
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴
	else distance=delta_y;
	for(t=0;t<=distance+1;t++ )//画线输出
	{
		llSetPoint(uRow,uCol,color);//画点
		xerr+=delta_x ;
		yerr+=delta_y ;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}

void llDrawLineD(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t d, llColor color)
{
    uint16_t t;
	int32_t xerr=0,yerr=0,delta_x,delta_y,distance;
	int32_t incx,incy,uRow,uCol;

    delta_x=x1-x0; //计算坐标增量
	delta_y=y1-y0;
	uRow=x0;
	uCol=y0;
	if(delta_x>0)incx=1; //设置单步方向
	else if(delta_x==0)incx=0;//垂直线
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if(delta_y==0)incy=0;//水平线
	else{incy=-1;delta_y=-delta_y;}
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴
	else distance=delta_y;
	for(t=0;t<=distance+1;t++ )//画线输出
	{
        llFillCircle(uRow, uCol,d,color);

		xerr+=delta_x ;
		yerr+=delta_y ;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}

void llDrawHLine(int16_t x,int16_t y,int16_t w,llColor color)
{
    llFillSingleColor(x,y,x+w-1,y,color);
}

void llDrawVLine(int16_t x,int16_t y,int16_t h,llColor color)
{
    llFillSingleColor(x,y,x,y+h-1,color);
}

void llDrawCircle(int16_t x0, int16_t y0, int16_t r, llColor color)
{
    int16_t  x  = 1;
    int16_t  dx = 1;
    int16_t  dy = r+r;
    int16_t  p  = -(r>>1);

    llSetPoint(x0 + r, y0, color);
    llSetPoint(x0 - r, y0, color);
    llSetPoint(x0, y0 - r, color);
    llSetPoint(x0, y0 + r, color);

    while(x<r)
    {
        if(p>=0)
        {
            dy-=2;
            p-=dy;
            r--;
        }
        dx+=2;
        p+=dx;
        llSetPoint(x0 + x, y0 + r, color);
        llSetPoint(x0 - x, y0 + r, color);
        llSetPoint(x0 - x, y0 - r, color);
        llSetPoint(x0 + x, y0 - r, color);
        if (r != x)
        {
            llSetPoint(x0 + r, y0 + x, color);
            llSetPoint(x0 - r, y0 + x, color);
            llSetPoint(x0 - r, y0 - x, color);
            llSetPoint(x0 + r, y0 - x, color);
        }
        x++;
    }
}

void llDrawCircleCorner( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, llColor color)
{
    int32_t f     = 1 - r;
    int32_t ddF_x = 1;
    int32_t ddF_y = -2 * r;
    int32_t x     = 0;

    while (x < r)
    {
        if (f >= 0)
        {
            r--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        if (cornername & 0x4)
        {
            llSetPoint(x0 + x, y0 + r, color);
            llSetPoint(x0 + r, y0 + x, color);
        }
        if (cornername & 0x2)
        {
            llSetPoint(x0 + x, y0 - r, color);
            llSetPoint(x0 + r, y0 - x, color);
        }
        if (cornername & 0x8)
        {
            llSetPoint(x0 - r, y0 + x, color);
            llSetPoint(x0 - x, y0 + r, color);
        }
        if (cornername & 0x1)
        {
            llSetPoint(x0 - r, y0 - x, color);
            llSetPoint(x0 - x, y0 - r, color);
        }
    }
}

void llFillCircle(int16_t x0, int16_t y0, uint16_t d, llColor color)
{
    int16_t r=d/2;
    int16_t iPosXOffset = r;
    int16_t iPosYOffset = 0;
    int16_t iPosXOffset_Old = -1;
    int16_t iXChange = 1 - (r<<1); /* r*2 */
    int16_t iYChange = 1;
    int16_t rError = 0;

    if(1 == d)
    {
        llSetPoint( x0, y0, color);
        return ;
	}
    if(2 == d)
    {
        llSetPoint( x0, y0-1, color);
        llDrawLine( x0-1, y0, x0+1, y0,color);
        llSetPoint( x0, y0+1, color);
        return ;
	}

			while(iPosXOffset >= iPosYOffset)
			{
				// Fill the circle
				if((r > 1) &&  (iPosXOffset_Old != iPosXOffset))
				{
					llDrawLine( x0-iPosXOffset, y0-iPosYOffset+1, x0-iPosXOffset, y0+iPosYOffset-1, color);
					llDrawLine( x0+iPosXOffset, y0-iPosYOffset+1, x0+iPosXOffset, y0+iPosYOffset-1, color);
				}
				llDrawLine( x0-iPosYOffset, y0-iPosXOffset+1, x0-iPosYOffset, y0+iPosXOffset-1, color);
				llDrawLine( x0+iPosYOffset, y0-iPosXOffset+1, x0+iPosYOffset, y0+iPosXOffset-1, color);

				// Draw edge.
				llSetPoint( x0+iPosXOffset, y0-iPosYOffset, color); /*   0- 45 */
				llSetPoint( x0+iPosYOffset, y0-iPosXOffset, color); /*  45- 90 */
				llSetPoint( x0-iPosYOffset, y0-iPosXOffset, color); /*  90-135 */
				llSetPoint( x0-iPosXOffset, y0-iPosYOffset, color); /* 135-180 */
				llSetPoint( x0-iPosXOffset, y0+iPosYOffset, color); /* 180-225 */
				llSetPoint( x0-iPosYOffset, y0+iPosXOffset, color); /* 225-270 */
				llSetPoint( x0+iPosYOffset, y0+iPosXOffset, color); /* 270-315 */
				llSetPoint( x0+iPosXOffset, y0+iPosYOffset, color); /* 315-360 */

				iPosXOffset_Old = iPosXOffset;

				iPosYOffset++;
				rError += iYChange;
				iYChange += 2;
				if ((2 * rError + iXChange) > 0)
				{
					iPosXOffset--;
					rError += iXChange;
					iXChange += 2;
				}
			}
}

void llFillCircleCorner(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, llColor color)
{
    int32_t f     = 1 - r;
    int32_t ddF_x = 1;
    int32_t ddF_y = -r - r;
    int32_t y     = 0;

    delta++;
    while (y < r)
    {
        if (f >= 0)
        {
            if (cornername & 0x1) llDrawHLine(x0 - y, y0 + r, y + y + delta, color);
            if (cornername & 0x2) llDrawHLine(x0 - y, y0 - r, y + y + delta, color);
            r--;
            ddF_y += 2;
            f     += ddF_y;
        }
        y++;
        ddF_x += 2;
        f     += ddF_x;
        if (cornername & 0x1) llDrawHLine(x0 - r, y0 + y, r + r + delta, color);
        if (cornername & 0x2) llDrawHLine(x0 - r, y0 - y, r + r + delta, color);
    }
}

void llDrawRect(int16_t x, int16_t y, int16_t w, int16_t h, llColor color)
{
    llDrawHLine(x, y, w, color);
    llDrawHLine(x, y + h - 1, w, color);
    llDrawVLine(x, y+1, h-2, color);
    llDrawVLine(x + w - 1, y+1, h-2, color);
}

void llDrawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, llColor color)
{
    llDrawHLine(x+r,y,w-r-r,color);
    llDrawHLine(x+r,y+h-1,w-r-r,color);
    llDrawVLine(x,y+r,h-r-r,color);
    llDrawVLine(x+w-1,y+r,h-r-r,color);
    llDrawCircleCorner(x + r    , y + r    , r, 1, color);
    llDrawCircleCorner(x + w - r - 1, y + r    , r, 2, color);
    llDrawCircleCorner(x + w - r - 1, y + h - r - 1, r, 4, color);
    llDrawCircleCorner(x + r    , y + h - r - 1, r, 8, color);
}

void llFillRect(int16_t x, int16_t y, int16_t w, int16_t h, llColor color)
{
    llFillSingleColor(x,y,x+w-1,y+h-1,color);
}

void llFillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, llColor color)
{
    llFillRect(x, y + r, w, h - r - r, color);
    llFillCircleCorner(x + r, y + h - r - 1, r, 1, w - r - r - 1, color);
    llFillCircleCorner(x + r    , y + r, r, 2, w - r - r - 1, color);
}

void llDrawEllipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, llColor color)
{
    if (rx<2) return;
    if (ry<2) return;
    int32_t x, y;
    int32_t rx2 = rx * rx;
    int32_t ry2 = ry * ry;
    int32_t fx2 = 4 * rx2;
    int32_t fy2 = 4 * ry2;
    int32_t s;

    for (x = 0, y = ry, s = 2*ry2+rx2*(1-2*ry); ry2*x <= rx2*y; x++)
    {
        llSetPoint(x0 + x, y0 + y, color);
        llSetPoint(x0 - x, y0 + y, color);
        llSetPoint(x0 - x, y0 - y, color);
        llSetPoint(x0 + x, y0 - y, color);
        if (s >= 0) {
            s += fx2 * (1 - y);
            y--;
        }
        s += ry2 * ((4 * x) + 6);
    }

    for (x = rx, y = 0, s = 2*rx2+ry2*(1-2*rx); rx2*y <= ry2*x; y++)
    {
        llSetPoint(x0 + x, y0 + y, color);
        llSetPoint(x0 - x, y0 + y, color);
        llSetPoint(x0 - x, y0 - y, color);
        llSetPoint(x0 + x, y0 - y, color);
        if (s >= 0)
        {
            s += fy2 * (1 - x);
            x--;
        }
        s += rx2 * ((4 * y) + 6);
    }
}

void llFillEllipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, llColor color)
{
    if (rx<2) return;
    if (ry<2) return;
    int32_t x, y;
    int32_t rx2 = rx * rx;
    int32_t ry2 = ry * ry;
    int32_t fx2 = 4 * rx2;
    int32_t fy2 = 4 * ry2;
    int32_t s;

    for (x = 0, y = ry, s = 2*ry2+rx2*(1-2*ry); ry2*x <= rx2*y; x++)
    {
        llDrawHLine(x0 - x, y0 - y, x + x + 1, color);
        llDrawHLine(x0 - x, y0 + y, x + x + 1, color);
        if (s >= 0) {
            s += fx2 * (1 - y);
            y--;
        }
        s += ry2 * ((4 * x) + 6);
    }

    for (x = rx, y = 0, s = 2*rx2+ry2*(1-2*rx); rx2*y <= ry2*x; y++)
    {
        llDrawHLine(x0 - x, y0 - y, x + x + 1, color);
        llDrawHLine(x0 - x, y0 + y, x + x + 1, color);
        if (s >= 0) {
            s += fy2 * (1 - x);
            x--;
        }
        s += rx2 * ((4 * y) + 6);
    }
}

void llDrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, llColor color)
{
    llDrawLine(x0, y0, x1, y1, color);
    llDrawLine(x1, y1, x2, y2, color);
    llDrawLine(x2, y2, x0, y0, color);
}

void llFillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, llColor color)
{
    int32_t a, b, y, last;

    if (y0 > y1)
    {
        SWAP(y0, y1); SWAP(x0, x1);
    }
    if (y1 > y2)
    {
        SWAP(y2, y1); SWAP(x2, x1);
    }
    if (y0 > y1)
    {
        SWAP(y0, y1); SWAP(x0, x1);
    }

    if (y0 == y2)
    {
        a = b = x0;
        if (x1 < a)      a = x1;
        else if (x1 > b) b = x1;
        if (x2 < a)      a = x2;
        else if (x2 > b) b = x2;
        llDrawHLine(a, y0, b - a + 1, color);
        return;
    }

    int32_t
            dx01 = x1 - x0,
            dy01 = y1 - y0,
            dx02 = x2 - x0,
            dy02 = y2 - y0,
            dx12 = x2 - x1,
            dy12 = y2 - y1,
            sa   = 0,
            sb   = 0;

    // For upper part of triangle, find scanline crossings for segments
    // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
    // is included here (and second loop will be skipped, avoiding a /0
    // error there), otherwise scanline y1 is skipped here and handled
    // in the second loop...which also avoids a /0 error here if y0=y1
    // (flat-topped triangle).
    if (y1 == y2) last = y1;  // Include y1 scanline
    else last = y1 - 1; // Skip it

    for (y = y0; y <= last; y++)
    {
        a   = x0 + sa / dy01;
        b   = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        if (a > b) SWAP(a, b);
        llDrawHLine(a, y, b - a + 1, color);
    }

    // For lower part of triangle, find scanline crossings for segments
    // 0-2 and 1-2.  This loop is skipped if y1=y2.
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for (; y <= y2; y++)
    {
        a   = x1 + sa / dy12;
        b   = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        if (a > b) SWAP(a, b);
        llDrawHLine(a, y, b - a + 1, color);
    }
}
