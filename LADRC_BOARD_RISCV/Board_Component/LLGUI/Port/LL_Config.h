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

#ifndef _LL_CONFIG_H_
#define _LL_CONFIG_H_

#include <stdlib.h>
#include "stdbool.h"
#include "stdint.h"
#include "user_peripheral_driver.h"

// 调用头文件 #include "LL_Gui.h"
// 定时器周期性运行 llGuiTick(ms);

//颜色位数
#define CONFIG_COLOR_DEPTH                          16 // 1 8 16 24 32
//屏幕宽度像素
#define LL_MONITOR_WIDTH                            128
//屏幕高度像素
#define LL_MONITOR_HEIGHT                           128
//gui内存大小
#define MEM_SIZE                                    (16*1024)
//双缓冲
#define USE_DOUBLE_BUFFERING                        0
//图片显示的缓冲大小
#define IMAGE_READ_BYTE_MAX                         1024
//调试输出
#define USE_LL_DEBUG                                0
//使用自定义单色填充函数
#define USE_USER_FILL_COLOR                         1
//使用自定义彩色填充函数
#define USE_USER_FILL_MULTIPLE_COLORS               0


/***********************************控件内存占用定义*********************************************/
#define LL_FONT_NAME_LENGTH_MAX                    48 //byte 字体名称长度长度最大值
#define LL_BUTTON_TEXT_LENGTH_MAX                  16 //byte button显示文本长度最大值
#define LL_LINEEDIT_TEXT_LENGTH_MAX                48 //byte lineEdit显示文本长度最大值
#define LL_CHECKBOX_TEXT_LENGTH_MAX                16 //byte checkBox显示文本长度最大值
#define LL_COMBOBOX_ITEM_MAX                       8  //byte comboBox下拉项数量最大值
#define LL_COMBOBOX_TEXT_LENGTH_MAX                16 //byte comboBox显示文本长度最大值
/***********************************控件性能定义*********************************************/
#define LL_MOVE_START_PIXEL                        3 //滑动类控件,滑动启动偏移最小值

extern uint8_t cfgColorDepth;
extern uint16_t cfgMonitorWidth;
extern uint16_t cfgMonitorHeight;

#if CONFIG_COLOR_DEPTH == 1
#define llColor  uint8_t
#elif CONFIG_COLOR_DEPTH == 8
#define llColor  uint8_t
#elif CONFIG_COLOR_DEPTH == 16
#define llColor  uint16_t
#elif CONFIG_COLOR_DEPTH == 24
#define llColor  uint32_t
#elif CONFIG_COLOR_DEPTH == 32
#define llColor  uint32_t
#endif

#if USE_LL_DEBUG == 1
#define LLPRINT                                   printf
#define LLPRINT_NUM(str,num)                      printf("%s:%d\n",str,num)
#define LLPRINT_STR(str)                          printf("%s\n",str)
#define LLPRINT_POINT(str,pos)                    printf("%s:%d,%d\n",str,pos.x,pos.y)
#define LLPRINT_GEOMETRY(str,geometry)            printf("%s:%d,%d,%d,%d\n",str,geometry.x,geometry.y,geometry.width,geometry.height)
#else
#define LLPRINT
#define LLPRINT_NUM(str,num)
#define LLPRINT_STR(str)
#define LLPRINT_POINT(str,pos)
#define LLPRINT_GEOMETRY(str,geometry)
#endif

void *llMalloc(uint32_t size);
void llFree(void *p);
void *llRealloc(void *ptr,uint32_t newSize);
void llCfgDoubleBufferStart(bool isCopy);
void llCfgDoubleBufferEnd(bool isRefreshNow);
void llCfgSetPoint(int16_t x,int16_t y,llColor color);
#if USE_USER_FILL_COLOR == 1
void llCfgFillSingleColor(int16_t x0,int16_t y0,int16_t x1,int16_t y1,llColor color);
#endif
#if USE_USER_FILL_MULTIPLE_COLORS == 1
void llCfgFillMultipleColors(int16_t x0,int16_t y0,int16_t x1,int16_t y1,llColor *color);
#endif
bool llCfgClickGetPoint(int16_t *x,int16_t *y);
void llExFlashInit(void);
void llReadExFlash(uint32_t addr,uint8_t* pBuffer,uint16_t length);
void llBuzzerBeep(void);
void llGetRtc(uint8_t *readBuf);
void llSetRtc(uint8_t *writeBuf);

#endif //_LL_CONFIG_H_

