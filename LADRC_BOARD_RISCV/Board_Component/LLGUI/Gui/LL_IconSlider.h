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

#ifndef _LL_ICON_SLIDER_H_
#define _LL_ICON_SLIDER_H_

#include "LL_General.h"

typedef struct
{
    LLGENERAL_ATTRIBUTES;
    bool isHorizontalScroll:1;//水平移动
    bool isClickItem:1;
    bool isWaitRefresh:1;
    bool isReleaseMove:1;
    uint8_t rowCount;
    uint8_t columnCount;
    uint16_t itemWidth;
    uint16_t itemHeight;
    uint8_t currentPage;
    uint8_t pageMax;
    uint8_t pageSpacing;
    uint8_t itemNum;
    uint8_t imageCount;
    uint32_t *imageAddr;
    uint32_t clickTimer;
    int16_t moveX;
    int16_t moveY;
    int16_t moveOffset;
    int16_t releaseTargetX;
    int16_t releaseTargetY;
    uint16_t clickItemNum;
    llPoint clickPoint;
}llIconSlider;


llIconSlider *llIconSliderQuickCreate(uint16_t nameId, uint16_t parentNameId,
                                          int16_t x, int16_t y, int16_t width, int16_t height,
                                          uint8_t rowCount,uint8_t columnCount,
                                          uint16_t itemWidth,uint16_t itemHeight,
                                          uint8_t pageMax,uint8_t pageSpacing,
                                          bool isHorizontalScroll,bool isHidden);

llIconSlider *llIconSliderCreate(uint16_t nameId, uint16_t parentNameId,
                                     int16_t x, int16_t y, int16_t width, int16_t height,
                                     uint8_t rowCount,uint8_t columnCount,
                                     uint8_t pageMax,uint8_t pageSpacing,
                                     bool isHorizontalScroll,bool isHidden);
void nIconSliderLoop(uint16_t nameId);

void pIconSliderAddImage(llIconSlider *widget,uint32_t imageAddr);
void nIconSliderAddImage(uint16_t nameId,uint32_t imageAddr);

uint16_t pIconSliderGetClickItemNum(llIconSlider *widget);
uint16_t nIconSliderGetClickItemNum(uint16_t nameId);

uint8_t pIconSliderGetCurrentPage(llIconSlider *widget);
uint8_t nIconSliderGetCurrentPage(uint16_t nameId);

void pIconSliderSetCurrentPage(llIconSlider *widget,uint8_t pageNum);
void nIconSliderSetCurrentPage(uint16_t nameId,uint8_t pageNum);

#endif //_LL_ICON_SLIDER_H_
