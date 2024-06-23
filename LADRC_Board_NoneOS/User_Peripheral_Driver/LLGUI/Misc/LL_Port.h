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

#ifndef _LL_PORT_H_
#define _LL_PORT_H_

#include "stdint.h"
#include "stdbool.h"
#include "LL_Config.h"

bool llClickGetPoint(int16_t *x,int16_t *y);

void llSetPoint(int16_t x,int16_t y,llColor color);
void llFillSingleColor(int16_t x0,int16_t y0,int16_t x1,int16_t y1,llColor color);
void llFillMultipleColors(int16_t x0,int16_t y0,int16_t x1,int16_t y1,llColor *color);

#if USE_USER_MEM == 0
void *llMalloc(uint32_t size);
void llFree(void *p);
void *llRealloc(void *ptr,uint32_t newSize);
#endif

void llDrawLine(int16_t x0,int16_t y0,int16_t x1,int16_t y1,llColor color);
void llDrawLineD(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t d, llColor color);
void llDrawCircle(int16_t x0, int16_t y0, int16_t r, llColor color);
void llFillCircle(int16_t x0, int16_t y0, uint16_t d, llColor color);
void llDrawRect(int16_t x, int16_t y, int16_t w, int16_t h, llColor color);
void llDrawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, llColor color);
void llFillRect(int16_t x, int16_t y, int16_t w, int16_t h, llColor color);
void llFillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, llColor color);
void llDrawEllipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, llColor color);
void llFillEllipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, llColor color);
void llDrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, llColor color);
void llFillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, llColor color);

//双缓冲
void llDoubleBufferStart(bool isCopy);
void llDoubleBufferEnd(bool isRefreshNow);
    
#endif //_LL_PORT_H_






