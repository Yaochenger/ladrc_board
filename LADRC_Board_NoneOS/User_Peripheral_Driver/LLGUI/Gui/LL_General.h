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

#ifndef _LL_GENERAL_H_
#define _LL_GENERAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "LL_Config.h"
#include "LL_Port.h"
#include <string.h>
#include "stdbool.h"
#include "LL_String.h"

#ifndef ON
#define ON           true
#endif
#ifndef OFF
#define OFF          false
#endif
#define TOUCH_CLICK          true
#define TOUCH_NO_CLICK         false

#ifndef SET_BITS
#define   SET_BITS(data,value)          ((data)|=(value))
#endif
#ifndef CLR_BITS
#define   CLR_BITS(data,value)          ((data)&=~(value))
#endif
#ifndef SETBIT
#define   SETBIT(data,move)          ((data)|=(1<<(move)))
#endif
#ifndef CLRBIT
#define   CLRBIT(data,move)          ((data)&=~(1<<(move)))
#endif
#ifndef GETBIT
#define   GETBIT(data,move)          (((data)>>(move))&0x01)
#endif
#ifndef PUTBIT
#define   PUTBIT(data,value,move)    ((value)?SETBIT(data,move):CLRBIT(data,move))
#endif
#ifndef GET16H
#define   GET16H(data)              (((data)>>8)&0xFF)
#endif
#ifndef GET16L
#define   GET16L(data)              ((data)&0xFF)
#endif
#ifndef CONNECT16
#define   CONNECT16(H,L)            (((H)<<8)+(L))
#endif

#ifndef MAX
#define MAX(a,b)    (((a) > (b)) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a,b)    (((a) < (b)) ? (a) : (b))
#endif
#ifndef MIDDLE
#define MIDDLE(dat,min,max)    (MIN(MAX(dat,min),max))
#endif

#define RECTANGLE_MID_X_POS(x,w1,w2)   (x+(w1-w2)/2)
#define RECTANGLE_MID_Y_POS(y,h1,h2)   (y+(h1-h2)/2)
#define RECTANGLE_RIGHT_X_POS(x,w1,w2)   (x+(w1-w2))
#define RECTANGLE_BUTTOM_Y_POS(y,h1,h2)   (y+(h1-h2))

#ifndef IMAGE_NONE
#define IMAGE_NONE    0xFFFFFFFF
#endif

#ifndef LL_UNUSED
#define LL_UNUSED(VAR)     (VAR) = (VAR)
#endif

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 5000000)
#define LL_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define LL_WEAK __weak
#elif defined(__MINGW32__)
#define LL_WEAK
#elif defined(__GNUC__)
#define LL_WEAK __attribute__((weak))
#endif

#ifndef CHAR_BUFFER_BYTE_MAX
#define CHAR_BUFFER_BYTE_MAX     32
#endif

typedef enum{
    widgetTypeNone,//仅background使用
    widgetTypeBackground,
    widgetTypeWindow,
    widgetTypeButton,
    widgetTypeImage,
    widgetTypeText,
    widgetTypeLineEdit,
    widgetTypeDashboardSimple,
    widgetTypeGraph,
    widgetTypeCheckBox,
    widgetTypeSlider,
    widgetTypeProgressBar,
    widgetTypeGauge,
    widgetTypeQRCode,
    widgetTypeDateTime,
    widgetTypeIconSlider,
    widgetTypeComboBox,
    widgetTypeIconRotateAround
}llWidgetType;

#define LLGENERAL_ATTRIBUTES  llWidgetType widgetType; \
                             llGeometry geometry; \
                             uint16_t nameId; \
                             llWidgetType parentType; \
                             void * parentWidget; \
                             void (*deleteFunc)(uint16_t); \
                             void (*actionFunc)(void *,uint8_t); \
                             void (*refreshFunc)(uint16_t); \
                             bool isEnable:1; \
                             bool isHidden:1

typedef struct{
    int16_t x;
    int16_t y;
    int16_t width;
    int16_t height;
}llGeometry;

typedef struct{
    LLGENERAL_ATTRIBUTES;
}llGeneral;

typedef struct{
    int16_t x;
    int16_t y;
}llPoint;

typedef struct
{
    int16_t x;
    int16_t y;
    llColor color;
}llPointColor;

typedef struct{
    int16_t width;
    int16_t height;
}llSize;

typedef enum
{
    llAlignHLeft,
    llAlignHCenter,
    llAlignHRight
}llHorizontalAlign;

typedef enum
{
    llAlignVTop,
    llAlignVCenter,
    llAlignVBottom
}llVerticalAlign;

typedef enum
{
    typeTTF,
    typeCFile,
    typeBinFile
}llFontLibType;


typedef struct
{
    llFontLibType libType;
    uint8_t name[LL_FONT_NAME_LENGTH_MAX];
    uint16_t fontSize;
    void * pointer;
}llFontLib;

typedef struct
{
    uint8_t unicodeH;
    uint8_t unicodeL;
    uint32_t width;
    uint32_t height;
    uint8_t* dataPointer;
    uint32_t dataAddr;
}llLatticeInfo;

typedef struct
{
    const llLatticeInfo *dataInfo;
    uint8_t dataBits;
    uint32_t totalCharNum;
    uint8_t charSize;
}llLatticeLibraryInfo;

typedef union
{
    uint8_t u8ReadBuf[IMAGE_READ_BYTE_MAX];
    uint16_t u16ReadBuf[IMAGE_READ_BYTE_MAX/2];
    uint32_t u32ReadBuf[IMAGE_READ_BYTE_MAX/4];
}imageBufferTypedef;

typedef struct
{
    int16_t width;
    int16_t height;
    uint8_t convertType;
    uint8_t reserved1;
    uint8_t reserved2;
    uint8_t reserved3;
    uint8_t reserved4;
    uint8_t reserved5;
    uint8_t reserved6;
    uint8_t reserved7;
    uint8_t reserved8;
    uint8_t reserved9;
    uint8_t reserved10;
    uint8_t reserved11;
}imageHeaderTypedef;

extern uint8_t convertTypeBit[6];

#define CONVERT_TYPE_565       1
#define CONVERT_TYPE_888       2
#define CONVERT_TYPE_8888       3
#define CONVERT_TYPE_8565       4
#define CONVERT_TYPE_565_MASK       5

#define LL_MALLOC_WIDGET_INFO(widget_type)      (widget_type*)llMalloc(sizeof(widget_type))

#define LL_MALLOC_STRING(str)      (uint8_t *)llMalloc((strlen((const char *)str)+1)*sizeof(uint8_t))

// 1 8(233) 16(565) 24(888)
#if CONFIG_COLOR_DEPTH == 1

#elif CONFIG_COLOR_DEPTH == 8

#elif CONFIG_COLOR_DEPTH == 16
uint16_t llRgb565ToGray(uint16_t rgb565);
#define RGB_2_GRAY(color)        llRgb565ToGray(color)
#elif CONFIG_COLOR_DEPTH == 24
uint32_t llRgb888ToGray(uint32_t rgb888);
#define RGB_2_GRAY(color)        llRgb888ToGray(color)
#endif

#ifndef LL_FONT_NAME_LENGTH_MAX
#define LL_FONT_NAME_LENGTH_MAX                    48 //byte 字体名称长度长度最大值
#endif

#ifndef LL_BUTTON_TEXT_LENGTH_MAX
#define LL_BUTTON_TEXT_LENGTH_MAX                  16 //byte button显示文本长度最大值
#endif

#ifndef LL_LINEEDIT_TEXT_LENGTH_MAX
#define LL_LINEEDIT_TEXT_LENGTH_MAX                48 //byte lineEdit显示文本长度最大值
#endif

#ifndef LL_CHECKBOX_TEXT_LENGTH_MAX
#define LL_CHECKBOX_TEXT_LENGTH_MAX                16 //byte checkBox显示文本长度最大值
#endif

#ifndef LL_COMBOBOX_ITEM_MAX
#define LL_COMBOBOX_ITEM_MAX                       8  //byte comboBox下拉项数量最大值
#endif

#ifndef LL_COMBOBOX_TEXT_LENGTH_MAX
#define LL_COMBOBOX_TEXT_LENGTH_MAX                16 //byte comboBox显示文本长度最大值
#endif

#ifndef LL_MOVE_START_PIXEL
#define LL_MOVE_START_PIXEL                        3 //滑动类控件,滑动启动偏移最小值
#endif

uint8_t llGetUtf8Len(uint8_t *utf8);
uint8_t llUtf8ToUnicode(uint8_t* unicode, uint8_t *utf8);
bool llStringCompare(uint8_t* str1,uint8_t* str2);
uint8_t* llStrcat(uint8_t* str1,uint8_t* str2);
bool llRectIsOverlap(llGeometry rc1, llGeometry rc2);
bool llRectIsFullIn(llGeometry bigRect, llGeometry smallRect);
bool llPointInRect(llPoint point, llGeometry rc);
bool llRectIntersect(const llGeometry rect1, const llGeometry rect2,llGeometry * outRect);
extern llGeometry llGeneralImageShow(llGeneral *widget,uint32_t imageAddr, int16_t x, int16_t y);
llSize llGeneralGetImageSize(uint32_t imageAddr);
llGeometry llGeneralGetImageGeometry(int16_t x,int16_t y,uint32_t imageAddr);
void llGeneralImageSpecificAreaShow(llGeneral *widget,llGeometry originGeometry,llGeometry targetGeometry,uint32_t imageAddr);

uint32_t llGeneralGetParentOverlapColor(uint32_t parentAddr,llGeometry parentGepmetry,llPoint childPos,uint8_t parentConvertTypeBit);
void* llGeneralGetWidget(uint16_t nameId);
void llGeneralWidgetSelect(llGeneral *widget);
void llGeneralWidgetParentRecover(llGeneral *widget,llGeometry geometry);
bool llGeneralParentLinkHidden(llGeneral *widget);
void llGeneralWidgetParentRecoverMove(llGeneral *widget,llGeometry oldGeometry,llGeometry newGeometry);
void llGeneralRecover(llGeneral *widget,llGeometry targetGeometry);

#define PARENT_BACKGROUND_TYPE_ERROR   0
#define PARENT_BACKGROUND_TYPE_COLOR   1
#define PARENT_BACKGROUND_TYPE_IMAGE   2

uint8_t llGeneralGetParentBackgroundInfo(llGeneral *widget,llColor* retColor,uint32_t *retImageAddr,llPoint* retImagePoint);
llGeneral* llGeneralGetParentBackgroundWidget(llGeneral *widget,llColor* retColor,uint32_t *retImageAddr);

uint32_t llGeneralImageSpecificAreaRead(uint8_t *readCount,llGeneral *widget,uint32_t imageAddr,llGeometry imageGeometry,imageBufferTypedef *unionReadBuf);

/***********************************888转换屏幕位数颜色*********************************************/

llColor RGB888(uint32_t color);
llColor RGB_CONVERT(uint8_t R,uint8_t G,uint8_t B);
void llGeometryGetR_G_B(llColor color,uint8_t *r,uint8_t *g,uint8_t *b);
bool llGeometryAutoSetHiddenIsShow(llGeneral *widget,bool isHidden);
llColor llGeometryColorMix(llColor rgb1,llColor rgb2,uint8_t alpha2);


float pGeneralGetTextFloat(llGeneral *widget);
float nGeneralGetTextFloat(uint16_t nameId);

void pGeneralSetTextFloat(llGeneral *widget,float value,uint8_t afterDecimalPointNum);
void nGeneralSetTextFloat(uint16_t nameId,float value,uint8_t afterDecimalPointNum);

bool pGeneralAutoSetTextFloat(llGeneral *widget,float newValue,uint8_t afterDecimalPointNum);
bool nGeneralAutoSetTextFloat(uint16_t nameId,float newValue,uint8_t afterDecimalPointNum);

int32_t pGeneralGetTextInt32(llGeneral *widget);
int32_t nGeneralGetTextInt32(uint16_t nameId);

void pGeneralSetTextInt32(llGeneral *widget,int32_t value);
void nGeneralSetTextInt32(uint16_t nameId,int32_t value);

bool pGeneralAutoSetTextInt32(llGeneral *widget,int32_t newValue);
bool nGeneralAutoSetTextInt32(uint16_t nameId,int32_t newValue);

//pfb 专用
void llGeneralImageBlockRead(uint32_t imgAddr,uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint8_t *outBuf);




#ifdef __cplusplus
}
#endif

#endif //_LL_GENERAL_H_
