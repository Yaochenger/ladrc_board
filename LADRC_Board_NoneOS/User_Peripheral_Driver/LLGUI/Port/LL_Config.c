/*
 * Copyright 2021-2024 Ou Jianbo 59935554@qq.com
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

#include "LL_Config.h"
#include "string.h"
/* loop run llGuiLoop() */
#include "timer7.h"
#include "LL_Gui.h"

uint8_t cfgColorDepth = CONFIG_COLOR_DEPTH;
uint16_t cfgMonitorWidth = 0;
uint16_t cfgMonitorHeight = 0;

void llCfgDoubleBufferStart(bool isCopy)
{
}

void llCfgDoubleBufferEnd(bool isRefreshNow)
{
}

/***************************************************************************//**
 * @fn         bool llCfgClickGetPoint(int16_t *x,int16_t *y)
 * @brief      获取触摸坐标
 * @param      *x,*y  触摸坐标
 * @return     bool 是否有触摸
 * @version    V0.1
 * @date       
 * @details    
 ******************************************************************************/
bool llCfgClickGetPoint(int16_t *x,int16_t *y)
{
    bool touchState=false;
    int16_t rx;
    int16_t ry;

    //添加触摸函数
    //touchState=touch_scan(&rx,&ry);
    *x=rx;
    *y=ry;
    if((touchState!=0)&&(((rx!=-1)&&(ry!=-1))||((rx!=0)&&(ry!=0))))
    {
        touchState=true;
    }
    else
    {
        touchState=false;
        *x=-1;
        *y=-1;
    }
    return touchState;
}

void llCfgSetPoint(int16_t x,int16_t y,llColor color)
{
    Gui_DrawPoint(x, y, color);
}

#if USE_USER_FILL_COLOR == 1
/***************************************************************************//**
 * @fn         void llCfgFillSingleColor(int16_t x0,int16_t y0,int16_t x1,int16_t y1,llColor *color)
 * @brief      单色填充
 * @param      x0,y0,x1,y1  填充单色矩形的4个点
 * @return     void
 * @version    V0.1
 * @date       
 * @details    
 ******************************************************************************/
void llCfgFillSingleColor(int16_t x0,int16_t y0,int16_t x1,int16_t y1,llColor color)
{
    Gui_FillRectangle(x0, y0,x1, y1, color);
}
#endif

#if USE_USER_FILL_MULTIPLE_COLORS == 1
/***************************************************************************//**
 * @fn         void llCfgFillMultipleColors(int16_t x0,int16_t y0,int16_t x1,int16_t y1,llColor *color)
 * @brief      彩色填充
 * @param      x0,y0,x1,y1  填充彩色矩形的4个点
 * @return     void
 * @version    V0.1
 * @date       
 * @details    
 ******************************************************************************/
void llCfgFillMultipleColors(int16_t x0,int16_t y0,int16_t x1,int16_t y1,llColor *color)
{
}
#endif

/***************************************************************************//**
 * @fn         void llExFlashInit(void)
 * @brief      配合读数据前的初始化
 * @param      
 * @return     void
 * @version    V0.1
 * @date       
 * @details    
 ******************************************************************************/
void llExFlashInit(void)
{
}

/***************************************************************************//**
 * @fn         void llReadExFlash(uint32_t addr,uint8_t* pBuffer,uint16_t length)
 * @brief      读外部flash数据
 * @param      addr    地址
 *             pBuffer 数据缓存指针
 *             length  读取数据的长度
 * @return     void
 * @version    V0.1
 * @date       
 * @details    通常是读外部norflash,可以用数组代替,也可以是tf等
 ******************************************************************************/
void llReadExFlash(uint32_t addr,uint8_t* pBuffer,uint16_t length)
{
}

/***************************************************************************//**
 * @fn         void llBuzzerBeep(void)
 * @brief      蜂鸣器触发响一声
 * @param      
 * @return     void
 * @version    V0.1
 * @date       
 * @details    
 ******************************************************************************/
void llBuzzerBeep(void)
{
}

/***************************************************************************//**
 * @fn         void llGetRtc(uint8_t *readBuf)
 * @brief      读取年月日时分秒周
 * @param      *readBuf yy yy mm dd hh mm ss ww
 * @return     void
 * @version    V0.1
 * @date       
 * @details    数据用16进制储存,2021年 yyyy=0x07E5
 ******************************************************************************/
void llGetRtc(uint8_t *readBuf)
{
}

/***************************************************************************//**
 * @fn         void llSetRtc(uint8_t *writeBuf)
 * @brief      写入年月日时分秒
 * @param      *writeBuf yy yy mm dd hh mm ss
 * @return     void
 * @version    V0.1
 * @date       
 * @details    数据用16进制储存,2021年 yyyy=0x07E5
 ******************************************************************************/
void llSetRtc(uint8_t *writeBuf)
{
}

#include "timer7.h"

void TIM7_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM7_IRQHandler(void)
{
    llGuiTick(10);
    if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
        llGuiLoop();
    }
}


