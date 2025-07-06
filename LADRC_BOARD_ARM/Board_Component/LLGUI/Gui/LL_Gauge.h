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

#ifndef _LL_GAUGE_H_
#define _LL_GAUGE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "LL_General.h"
#include "LL_Gui.h"


typedef struct llGaugeInfo
{
    LLGENERAL_ATTRIBUTES;
    bool isColor:1;
    bool isInit:1;
    bool isForward:1;
    uint32_t bgImageAddr;
    llColor pointerColor;
    int16_t rotaryAngle;
    int16_t angleBuffer;
    uint16_t pointerLength;
    uint8_t pointerWidth1;
    uint8_t pointerWidth2;
    llPoint originalPoint;
    int16_t originalPointerDistance;
    llPoint *pointBackup;
    uint32_t pointCount;
    llPoint oldEndpoint[4];
    llPoint newEndpoint[4];
    llPoint pointerPos0;
    llPoint pointerPos1;
    uint32_t loopCounter;
    imageBufferTypedef imageBuf;
    struct llGaugeInfo* pNext;
    uint8_t angleSpeed;//1 - 10
#ifdef USE_LLGAUGE_EX
    void *exInfo;
#endif
}llGauge;

llGauge *llGaugeCreate(uint16_t nameId, uint16_t parentNameId, int16_t bgX, int16_t bgY, uint32_t bgImageAddr,bool isColor,
                                                               int16_t obgX, int16_t obgY,
                                                               uint32_t ptImageAddr, int16_t optX,int16_t optY,
                                                               int16_t optDistance,uint16_t ptLength,uint8_t ptWidth1,uint8_t ptWidth2,llColor ptColor,
                                                               uint8_t angleSpeed,bool isHidden);
void pGaugeSetRotaryAngle(llGauge *widget,int16_t rotaryAngle,bool isInit);
void nGaugeSetRotaryAngle(uint16_t nameId,int16_t rotaryAngle,bool isInit);
int16_t pGaugeGetRotaryAngle(llGauge *widget);
int16_t nGaugeGetRotaryAngle(uint16_t nameId);
void pGaugeLoop(llGauge *widget,uint16_t refreshMs,uint8_t moveValue);
void nGaugeLoop(uint16_t nameId,uint16_t refreshMs,uint8_t moveValue);
void pGaugeSetEnabled(llGauge *widget, bool state);
void nGaugeSetEnabled(uint16_t nameId, bool state);
void pGaugeSetHidden(llGauge *widget,bool isHidden);
void nGaugeSetHidden(uint16_t nameId,bool isHidden);

void llGaugeInit(void);
void llGaugeLoop(void);
void llGaugeQuit(void);

#ifdef __cplusplus
}
#endif

#endif //_LL_GAUGE_H_
