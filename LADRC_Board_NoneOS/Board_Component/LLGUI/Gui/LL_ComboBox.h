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

#ifndef _LL_COMBOBOX_H_
#define _LL_COMBOBOX_H_

#ifdef __cplusplus
extern "C" {
#endif



#include "LL_General.h"
#include "LL_Gui.h"
#include "LL_Characters.h"

typedef struct
{
    LLGENERAL_ATTRIBUTES;
    bool isExpand:1;
    bool isSlide:1;
    bool isMove:1;
    llFontLib *fontLibInfo;
    llColor textColor;
    llColor bgColor;
    llColor listBgColor;
    llColor selectBgColor;
    int16_t itemHeight;
    uint8_t *textList[LL_COMBOBOX_ITEM_MAX];
    uint8_t itemLenMax;
    uint8_t selectNum;
    uint8_t itemCount;
    llPoint pressPoint;
    int16_t moveOffset;
    uint8_t clickCount;
}llComboBox;

llComboBox* llComboBoxQuickCreate(uint16_t nameId, uint16_t parentNameId,int16_t x, int16_t y, int16_t width, int16_t height,
                                  llFontLib *fontLib,llColor textColor,llColor bgColor,llColor listBgColor,llColor selectBgColor,
                                  uint8_t defaultSelectNum,bool isHidden);
llComboBox* llComboBoxCreate(uint16_t nameId, uint16_t parentNameId, 
                          int16_t x, int16_t y, int16_t width, int16_t height,
                          llFontLib *fontLib,bool isHidden);
void pComboBoxAddItem(llComboBox *widget,uint8_t *itemText);
void nComboBoxAddItem(uint16_t nameId,uint8_t *text);
void pComboBoxSetEnabled(llComboBox *widget, bool state);
void nComboBoxSetEnabled(uint16_t nameId, bool state);
void pComboBoxSetSelect(llComboBox *widget, uint8_t num);
void nComboBoxSetSelect(uint16_t nameId, uint8_t num);
uint8_t pComboBoxGetSelect(llComboBox *widget);
uint8_t nComboBoxGetSelect(uint16_t nameId);
void pComboBoxSetSlide(llComboBox *widget,bool isSlide);
void nComboBoxSetSlide(uint16_t nameId,bool isSlide);
uint8_t* pComboBoxGetText(llComboBox *widget);
uint8_t* nComboBoxGetText(uint16_t nameId);
#ifdef __cplusplus
}
#endif

#endif //_LL_COMBOBOX_H_
