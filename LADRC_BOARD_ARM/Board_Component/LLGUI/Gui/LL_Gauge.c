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

#include "LL_Gauge.h"
#include "LL_Linked_List.h"
#include "stdio.h"
#include "LL_Config.h"
#include "LL_Timer.h"
#include "LL_User.h"

#ifdef USE_LLGAUGE_EX
extern int16_t pGaugeExGetRotaryAngle(llGauge *widget);
extern void pGaugeExSetRotaryAngle(llGauge *widget,int16_t rotaryAngle,bool isInit);
extern void llGaugeExSetInit(llGauge * pNewWidget,int16_t bgX, int16_t bgY, uint32_t bgImageAddr,int16_t obgX, int16_t obgY, uint32_t ptImageAddr,int16_t optX,int16_t optY,uint8_t angleSpeed);
extern uint8_t llGaugeExGetInfoSize(void);
extern void llGaugeExInit(void);
extern void llGaugeExLoop(void);
extern void llGaugeExQuit(void);
#endif

#define SWAP(x,y) ((x) = (x)+(y),(y)=(x)-(y),(x)=(x)-(y))

static const float sina_val[]= {
    0.000000f, 0.017452f, 0.034899f, 0.052336f, 0.069756f, 0.087156f, 0.104528f, 0.121869f,
    0.139173f, 0.156434f, 0.173648f, 0.190809f, 0.207912f, 0.224951f, 0.241922f, 0.258819f,
    0.275637f, 0.292372f, 0.309017f, 0.325568f, 0.342020f, 0.358368f, 0.374607f, 0.390731f,
    0.406737f, 0.422618f, 0.438371f, 0.453990f, 0.469472f, 0.484810f, 0.500000f, 0.515038f,
    0.529919f, 0.544639f, 0.559193f, 0.573576f, 0.587785f, 0.601815f, 0.615662f, 0.629320f,
    0.642788f, 0.656059f, 0.669131f, 0.681998f, 0.694658f, 0.707107f, 0.719340f, 0.731354f,
    0.743145f, 0.754710f, 0.766044f, 0.777146f, 0.788011f, 0.798635f, 0.809017f, 0.819152f,
    0.829038f, 0.838671f, 0.848048f, 0.857167f, 0.866025f, 0.874620f, 0.882948f, 0.891007f,
    0.898794f, 0.906308f, 0.913545f, 0.920505f, 0.927184f, 0.933580f, 0.939693f, 0.945519f,
    0.951057f, 0.956305f, 0.961262f, 0.965926f, 0.970296f, 0.974370f, 0.978148f, 0.981627f,
    0.984808f, 0.987688f, 0.990268f, 0.992546f, 0.994522f, 0.996195f, 0.997564f, 0.998630f,
    0.999391f, 0.999848f, 1.000000f, 0.999848f, 0.999391f, 0.998630f, 0.997564f, 0.996195f,
    0.994522f, 0.992546f, 0.990268f, 0.987688f, 0.984808f, 0.981627f, 0.978148f, 0.974370f,
    0.970296f, 0.965926f, 0.961262f, 0.956305f, 0.951057f, 0.945519f, 0.939693f, 0.933580f,
    0.927184f, 0.920505f, 0.913545f, 0.906308f, 0.898794f, 0.891007f, 0.882948f, 0.874620f,
    0.866025f, 0.857167f, 0.848048f, 0.838671f, 0.829038f, 0.819152f, 0.809017f, 0.798635f,
    0.788011f, 0.777146f, 0.766044f, 0.754710f, 0.743145f, 0.731354f, 0.719340f, 0.707107f,
    0.694658f, 0.681998f, 0.669131f, 0.656059f, 0.642788f, 0.629320f, 0.615662f, 0.601815f,
    0.587785f, 0.573576f, 0.559193f, 0.544639f, 0.529919f, 0.515038f, 0.500000f, 0.484810f,
    0.469472f, 0.453990f, 0.438371f, 0.422618f, 0.406737f, 0.390731f, 0.374607f, 0.358368f,
    0.342020f, 0.325568f, 0.309017f, 0.292372f, 0.275637f, 0.258819f, 0.241922f, 0.224951f,
    0.207912f, 0.190809f, 0.173648f, 0.156434f, 0.139173f, 0.121869f, 0.104528f, 0.087156f,
    0.069756f, 0.052336f, 0.034899f, 0.017452f, 0.000000f, -0.017452f, -0.034899f, -0.052336f,
    -0.069756f, -0.087156f, -0.104528f, -0.121869f, -0.139173f, -0.156434f, -0.173648f, -0.190809f,
    -0.207912f, -0.224951f, -0.241922f, -0.258819f, -0.275637f, -0.292372f, -0.309017f, -0.325568f,
    -0.342020f, -0.358368f, -0.374607f, -0.390731f, -0.406737f, -0.422618f, -0.438371f, -0.453990f,
    -0.469472f, -0.484810f, -0.500000f, -0.515038f, -0.529919f, -0.544639f, -0.559193f, -0.573576f,
    -0.587785f, -0.601815f, -0.615662f, -0.629320f, -0.642788f, -0.656059f, -0.669131f, -0.681998f,
    -0.694658f, -0.707107f, -0.719340f, -0.731354f, -0.743145f, -0.754710f, -0.766044f, -0.777146f,
    -0.788011f, -0.798635f, -0.809017f, -0.819152f, -0.829038f, -0.838671f, -0.848048f, -0.857167f,
    -0.866025f, -0.874620f, -0.882948f, -0.891007f, -0.898794f, -0.906308f, -0.913545f, -0.920505f,
    -0.927184f, -0.933580f, -0.939693f, -0.945519f, -0.951057f, -0.956305f, -0.961262f, -0.965926f,
    -0.970296f, -0.974370f, -0.978148f, -0.981627f, -0.984808f, -0.987688f, -0.990268f, -0.992546f,
    -0.994522f, -0.996195f, -0.997564f, -0.998630f, -0.999391f, -0.999848f, -1.000000f, -0.999848f,
    -0.999391f, -0.998630f, -0.997564f, -0.996195f, -0.994522f, -0.992546f, -0.990268f, -0.987688f,
    -0.984808f, -0.981627f, -0.978148f, -0.974370f, -0.970296f, -0.965926f, -0.961262f, -0.956305f,
    -0.951057f, -0.945519f, -0.939693f, -0.933580f, -0.927184f, -0.920505f, -0.913545f, -0.906308f,
    -0.898794f, -0.891007f, -0.882948f, -0.874620f, -0.866025f, -0.857167f, -0.848048f, -0.838671f,
    -0.829038f, -0.819152f, -0.809017f, -0.798635f, -0.788011f, -0.777146f, -0.766044f, -0.754710f,
    -0.743145f, -0.731354f, -0.719340f, -0.707107f, -0.694658f, -0.681998f, -0.669131f, -0.656059f,
    -0.642788f, -0.629320f, -0.615662f, -0.601815f, -0.587785f, -0.573576f, -0.559193f, -0.544639f,
    -0.529919f, -0.515038f, -0.500000f, -0.484810f, -0.469472f, -0.453990f, -0.438371f, -0.422618f,
    -0.406737f, -0.390731f, -0.374607f, -0.358368f, -0.342020f, -0.325568f, -0.309017f, -0.292372f,
    -0.275637f, -0.258819f, -0.241922f, -0.224951f, -0.207912f, -0.190809f, -0.173648f, -0.156434f,
    -0.139173f, -0.121869f, -0.104528f, -0.087156f, -0.069756f, -0.052336f, -0.034899f, -0.017452f,
    0.000000f
};

static const float cosa_val[]= {
    1.000000f, 0.999848f, 0.999391f, 0.998630f, 0.997564f, 0.996195f, 0.994522f, 0.992546f,
    0.990268f, 0.987688f, 0.984808f, 0.981627f, 0.978148f, 0.974370f, 0.970296f, 0.965926f,
    0.961262f, 0.956305f, 0.951057f, 0.945519f, 0.939693f, 0.933580f, 0.927184f, 0.920505f,
    0.913545f, 0.906308f, 0.898794f, 0.891007f, 0.882948f, 0.874620f, 0.866025f, 0.857167f,
    0.848048f, 0.838671f, 0.829038f, 0.819152f, 0.809017f, 0.798635f, 0.788011f, 0.777146f,
    0.766044f, 0.754710f, 0.743145f, 0.731354f, 0.719340f, 0.707107f, 0.694658f, 0.681998f,
    0.669131f, 0.656059f, 0.642788f, 0.629320f, 0.615662f, 0.601815f, 0.587785f, 0.573576f,
    0.559193f, 0.544639f, 0.529919f, 0.515038f, 0.500000f, 0.484810f, 0.469472f, 0.453990f,
    0.438371f, 0.422618f, 0.406737f, 0.390731f, 0.374607f, 0.358368f, 0.342020f, 0.325568f,
    0.309017f, 0.292372f, 0.275637f, 0.258819f, 0.241922f, 0.224951f, 0.207912f, 0.190809f,
    0.173648f, 0.156434f, 0.139173f, 0.121869f, 0.104528f, 0.087156f, 0.069756f, 0.052336f,
    0.034899f, 0.017452f, 0.000000f, -0.017452f, -0.034899f, -0.052336f, -0.069756f, -0.087156f,
    -0.104528f, -0.121869f, -0.139173f, -0.156434f, -0.173648f, -0.190809f, -0.207912f, -0.224951f,
    -0.241922f, -0.258819f, -0.275637f, -0.292372f, -0.309017f, -0.325568f, -0.342020f, -0.358368f,
    -0.374607f, -0.390731f, -0.406737f, -0.422618f, -0.438371f, -0.453990f, -0.469472f, -0.484810f,
    -0.500000f, -0.515038f, -0.529919f, -0.544639f, -0.559193f, -0.573576f, -0.587785f, -0.601815f,
    -0.615662f, -0.629320f, -0.642788f, -0.656059f, -0.669131f, -0.681998f, -0.694658f, -0.707107f,
    -0.719340f, -0.731354f, -0.743145f, -0.754710f, -0.766044f, -0.777146f, -0.788011f, -0.798635f,
    -0.809017f, -0.819152f, -0.829038f, -0.838671f, -0.848048f, -0.857167f, -0.866025f, -0.874620f,
    -0.882948f, -0.891007f, -0.898794f, -0.906308f, -0.913545f, -0.920505f, -0.927184f, -0.933580f,
    -0.939693f, -0.945519f, -0.951057f, -0.956305f, -0.961262f, -0.965926f, -0.970296f, -0.974370f,
    -0.978148f, -0.981627f, -0.984808f, -0.987688f, -0.990268f, -0.992546f, -0.994522f, -0.996195f,
    -0.997564f, -0.998630f, -0.999391f, -0.999848f, -1.000000f, -0.999848f, -0.999391f, -0.998630f,
    -0.997564f, -0.996195f, -0.994522f, -0.992546f, -0.990268f, -0.987688f, -0.984808f, -0.981627f,
    -0.978148f, -0.974370f, -0.970296f, -0.965926f, -0.961262f, -0.956305f, -0.951057f, -0.945519f,
    -0.939693f, -0.933580f, -0.927184f, -0.920505f, -0.913545f, -0.906308f, -0.898794f, -0.891007f,
    -0.882948f, -0.874620f, -0.866025f, -0.857167f, -0.848048f, -0.838671f, -0.829038f, -0.819152f,
    -0.809017f, -0.798635f, -0.788011f, -0.777146f, -0.766044f, -0.754710f, -0.743145f, -0.731354f,
    -0.719340f, -0.707107f, -0.694658f, -0.681998f, -0.669131f, -0.656059f, -0.642788f, -0.629320f,
    -0.615662f, -0.601815f, -0.587785f, -0.573576f, -0.559193f, -0.544639f, -0.529919f, -0.515038f,
    -0.500000f, -0.484810f, -0.469472f, -0.453990f, -0.438371f, -0.422618f, -0.406737f, -0.390731f,
    -0.374607f, -0.358368f, -0.342020f, -0.325568f, -0.309017f, -0.292372f, -0.275637f, -0.258819f,
    -0.241922f, -0.224951f, -0.207912f, -0.190809f, -0.173648f, -0.156434f, -0.139173f, -0.121869f,
    -0.104528f, -0.087156f, -0.069756f, -0.052336f, -0.034899f, -0.017452f, -0.000000f, 0.017452f,
    0.034899f, 0.052336f, 0.069756f, 0.087156f, 0.104528f, 0.121869f, 0.139173f, 0.156434f,
    0.173648f, 0.190809f, 0.207912f, 0.224951f, 0.241922f, 0.258819f, 0.275637f, 0.292372f,
    0.309017f, 0.325568f, 0.342020f, 0.358368f, 0.374607f, 0.390731f, 0.406737f, 0.422618f,
    0.438371f, 0.453990f, 0.469472f, 0.484810f, 0.500000f, 0.515038f, 0.529919f, 0.544639f,
    0.559193f, 0.573576f, 0.587785f, 0.601815f, 0.615662f, 0.629320f, 0.642788f, 0.656059f,
    0.669131f, 0.681998f, 0.694658f, 0.707107f, 0.719340f, 0.731354f, 0.743145f, 0.754710f,
    0.766044f, 0.777146f, 0.788011f, 0.798635f, 0.809017f, 0.819152f, 0.829038f, 0.838671f,
    0.848048f, 0.857167f, 0.866025f, 0.874620f, 0.882948f, 0.891007f, 0.898794f, 0.906308f,
    0.913545f, 0.920505f, 0.927184f, 0.933580f, 0.939693f, 0.945519f, 0.951057f, 0.956305f,
    0.961262f, 0.965926f, 0.970296f, 0.974370f, 0.978148f, 0.981627f, 0.984808f, 0.987688f,
    0.990268f, 0.992546f, 0.994522f, 0.996195f, 0.997564f, 0.998630f, 0.999391f, 0.999848f,
    1.000000f
};


void pGaugePointerRotary(llGauge *widget);


void llGaugeAction(void *widget,uint8_t touchSignal)
{

}

void pGaugeFree(llGauge *widget)
{
    llFree(widget->pointBackup);
    llFree(widget);
}

void nGaugeDelete(uint16_t nameId)
{
    llListHead *tempPos,*safePos;
    llListWidgetInfo *linkInfo;
    llListWidgetInfo *parentInfo;
    llListWidgetInfo *tempInfo;
    llGauge *widget;
    if(llList_GetInfoByName(&linkInfo,nameId)==true)
    {
        widget=linkInfo->widget;

        //查找父链表
        llList_GetInfoByName(&parentInfo,((llGeneral*)widget->parentWidget)->nameId);
        //消除自身在父链表中的位置数据
        list_for_each_prev_safe(tempPos,safePos, &parentInfo->child_link)
        {
            tempInfo = list_entry(tempPos, llListWidgetInfo, parent_link_pos);
            if(tempInfo->widget==widget)
            {
                llLinkedListDelete(tempPos);
                pGaugeFree(widget);
                llFree(tempInfo);
            }
        }
    }
}

void pGaugeRefresh(llGauge *widget)
{
    if(widget->isHidden==false)
    {
        if(llGeneralParentLinkHidden((llGeneral*)widget)==false)
        {
            pGaugePointerRotary(widget);
        }
    }
}

void nGaugeRefresh(uint16_t nameId)
{
    void *widget;
    widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        pGaugeRefresh((llGauge*)widget);
    }
}

bool pGaugeLoad(llGauge *widget, uint32_t imageAddr)
{
    llGeometry newGeometry;
    llPoint globalPos;
    if((widget->isEnable)&&(!widget->isHidden))
    {
        globalPos=llListGetGlobalPos(widget->parentWidget);
//        llDoubleBufferStart();
        newGeometry=llGeneralImageShow((llGeneral*)widget,widget->bgImageAddr,widget->geometry.x+globalPos.x,widget->geometry.y+globalPos.y);
//        llDoubleBufferEnd(true);
        widget->geometry.width=newGeometry.width;
        widget->geometry.height=newGeometry.height;
        return true;
    }
    else
    {
        return false;
    }
}

//自动根据图片大小更新尺寸数据
llGauge *llGaugeCreate(uint16_t nameId, uint16_t parentNameId, int16_t bgX, int16_t bgY, uint32_t bgImageAddr,bool isColor,
                        int16_t obgX, int16_t obgY,
                        uint32_t ptImageAddr,int16_t optX,int16_t optY,
                        int16_t optDistance,uint16_t ptLength,uint8_t ptWidth1,uint8_t ptWidth2,llColor ptColor,
                        uint8_t angleSpeed,bool isHidden)
{
    llGauge * pNewWidget = NULL;
    llPoint * pPointBackup = NULL;
    uint32_t pointBufferSize=0;
    llListWidgetInfo *parentInfo;
    uint8_t widthTemp;

    //检查父链表存在
    if(llList_GetInfoByName(&parentInfo,parentNameId)==true)
    {
#ifdef USE_LLGAUGE_EX
        pNewWidget = (llGauge*)llMalloc(sizeof(llGauge)+llGaugeExGetInfoSize());
#else
        pNewWidget = (llGauge*)llMalloc(sizeof(llGauge));
#endif
        if(isColor)
        {
        widthTemp=(ptWidth1>=ptWidth2)?ptWidth1:ptWidth2;

        //背景缓存
        pointBufferSize= (ptLength*2+widthTemp*2)*1.7*sizeof (llPoint);
        pPointBackup=(llPoint*)llMalloc(pointBufferSize);
        }

        if(((pNewWidget!=NULL)&&(!isColor))||((pNewWidget!=NULL)&&(pPointBackup!=NULL)&&(isColor)))
        {
            pNewWidget->nameId=nameId;

            pNewWidget->widgetType=widgetTypeGauge;
            pNewWidget->geometry.x=bgX;
            pNewWidget->geometry.y=bgY;
            pNewWidget->geometry.width=10;
            pNewWidget->geometry.height=20;

            llListWidgetAdd(&(parentInfo->child_link),pNewWidget);
            pNewWidget->parentType=((llGeneral*)(parentInfo->widget))->widgetType;
            pNewWidget->parentWidget=parentInfo->widget;

            pNewWidget->deleteFunc=nGaugeDelete;
            pNewWidget->actionFunc=llGaugeAction;
            pNewWidget->refreshFunc=nGaugeRefresh;

            pNewWidget->bgImageAddr=bgImageAddr;
            pNewWidget->isColor=isColor;

            pNewWidget->isHidden=isHidden;
            pNewWidget->isEnable=true;

            pNewWidget->rotaryAngle=0;
            pNewWidget->angleBuffer=0;
            pNewWidget->originalPoint.x=optX;
            pNewWidget->originalPoint.y=optY;
            pNewWidget->originalPointerDistance=optDistance;
            pNewWidget->pointerLength=ptLength;
            pNewWidget->pointerWidth1=ptWidth1;
            pNewWidget->pointerWidth2=ptWidth2;
            pNewWidget->pointerColor=ptColor;

            pNewWidget->pointBackup=pPointBackup;
            pNewWidget->pointCount=0;
            memset(pNewWidget->oldEndpoint,0,sizeof(llPoint)*4);
            memset(pNewWidget->newEndpoint,0,sizeof(llPoint)*4);

            pNewWidget->angleSpeed=angleSpeed;
            pNewWidget->isInit=true;

            memset(pNewWidget->pointBackup,0,pointBufferSize);

            pNewWidget->loopCounter=0;

            pGaugeLoad(pNewWidget,bgImageAddr);

            if(!isColor)
            {
#ifdef USE_LLGAUGE_EX
                llGaugeExSetInit(pNewWidget,bgX,bgY,bgImageAddr,obgX,obgY,ptImageAddr,optX,optY,angleSpeed);
#endif
            }
        }
        else
        {
            llFree(pPointBackup);
            llFree(pNewWidget);
        }
    }
    return pNewWidget;
}


//获取两点之间画直线的所有坐标
//返回坐标数量
static uint32_t llGaugeBresenhamLine( int16_t x0, int16_t y0, int16_t x1,int16_t y1, llPoint * pos )
{
    int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
            yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
            curpixel = 0;

    deltax = abs(x1 - x0);        /* The difference between the x's */
    deltay = abs(y1 - y0);        /* The difference between the y's */
    x = x0;                       /* Start x off at the first pixel */
    y = y0;                       /* Start y off at the first pixel */

    if (x1 >= x0)                 /* The x-values are increasing */
    {
        xinc1 = 1;
        xinc2 = 1;
    }
    else                          /* The x-values are decreasing */
    {
        xinc1 = -1;
        xinc2 = -1;
    }

    if (y1 >= y0)                 /* The y-values are increasing */
    {
        yinc1 = 1;
        yinc2 = 1;
    }
    else                          /* The y-values are decreasing */
    {
        yinc1 = -1;
        yinc2 = -1;
    }

    if (deltax >= deltay)         /* There is at least one x-value for every y-value */
    {
        xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
        yinc2 = 0;                  /* Don't change the y for every iteration */
        den = deltax;
        num = deltax / 2;
        numadd = deltay;
        numpixels = deltax;         /* There are more x-values than y-values */
    }
    else                          /* There is at least one y-value for every x-value */
    {
        xinc2 = 0;                  /* Don't change the x for every iteration */
        yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
        den = deltay;
        num = deltay / 2;
        numadd = deltax;
        numpixels = deltay;         /* There are more y-values than x-values */
    }

    for (curpixel = 0; curpixel <= numpixels; curpixel++)
    {
        pos[curpixel].x=x;
        pos[curpixel].y=y;

        num += numadd;              /* Increase the numerator by the top of the fraction */
        if (num >= den)             /* Check if numerator >= denominator */
        {
            num -= den;               /* Calculate the new numerator value */
            x += xinc1;               /* Change the x as appropriate */
            y += yinc1;               /* Change the y as appropriate */
        }
        x += xinc2;                 /* Change the x as appropriate */
        y += yinc2;                 /* Change the y as appropriate */
    }
    return curpixel;
}

bool llGaugeSamePointColor(int16_t x,int16_t y,llPointColor *source,uint32_t sourceLength,llColor *sourceRetColor)
{
    uint32_t i;

    for(i=0; i<sourceLength; i++)
    {
        if((source[i].x==x)&&((source[i].y==y)))
        {
            *sourceRetColor=source[i].color;
            return true;
        }
    }
    return false;
}

void llGaugeBubbleSortI16(int16_t *buffer, uint32_t length)
{
    uint32_t i,j;
    for(i=0; i<length-1; i++)
    {
        for(j=0; j<length-i-1; j++)
        {
            if(buffer[j]>buffer[j+1])
            {
                SWAP(buffer[j],buffer[j+1]);
            }
        }
    }
}

void llGaugeReadImageInit(llGauge *widget)
{
    int16_t buf[8];
    //自动计算最小尺寸图片
    buf[0]=widget->newEndpoint[0].x;
    buf[1]=widget->newEndpoint[1].x;
    buf[2]=widget->newEndpoint[2].x;
    buf[3]=widget->newEndpoint[3].x;

    if(widget->isInit)
    {
        llGaugeBubbleSortI16(buf,4);
        widget->pointerPos1.x=buf[3];
        widget->pointerPos0.x=buf[0];
    }
    else
    {
        buf[4]=widget->oldEndpoint[0].x;
        buf[5]=widget->oldEndpoint[1].x;
        buf[6]=widget->oldEndpoint[2].x;
        buf[7]=widget->oldEndpoint[3].x;
        llGaugeBubbleSortI16(buf,8);
        widget->pointerPos1.x=buf[7];
        widget->pointerPos0.x=buf[0];
    }

    buf[0]=widget->newEndpoint[0].y;
    buf[1]=widget->newEndpoint[1].y;
    buf[2]=widget->newEndpoint[2].y;
    buf[3]=widget->newEndpoint[3].y;

    if(widget->isInit)
    {
        llGaugeBubbleSortI16(buf,4);
        widget->pointerPos1.y=buf[3];
        widget->pointerPos0.y=buf[0];
    }
    else
    {
        buf[4]=widget->oldEndpoint[0].y;
        buf[5]=widget->oldEndpoint[1].y;
        buf[6]=widget->oldEndpoint[2].y;
        buf[7]=widget->oldEndpoint[3].y;
        llGaugeBubbleSortI16(buf,8);
        widget->pointerPos1.y=buf[7];
        widget->pointerPos0.y=buf[0];
    }
    //强制加大范围
    widget->pointerPos0.y--;
    widget->pointerPos1.y++;
}

void llGaugeFillPolygon(llGauge *widget)
{
    uint32_t count;
    uint32_t i,j;
    uint8_t readCount=0;
    llGeometry imageGeometry;
    uint16_t width,imgHeight;

    llGaugeReadImageInit(widget);

    imageGeometry.x=widget->pointerPos0.x;//-widget->geometry.x;
    imageGeometry.y=widget->pointerPos0.y;//-widget->geometry.y;
    imageGeometry.width=widget->pointerPos1.x-widget->pointerPos0.x+1;
    imgHeight=widget->pointerPos1.y-widget->pointerPos0.y+1;

    count=0;
    for(i=0; i<imgHeight; i++)
    {
        imageGeometry.height=1;
        llGeneralImageSpecificAreaRead(&readCount,(llGeneral*)widget,widget->bgImageAddr,imageGeometry,&(widget->imageBuf));
        if((imageGeometry.y)==widget->pointBackup[count].y)//和指针同一行的背景才进行处理
        {
            if(widget->pointBackup[count].y==widget->pointBackup[count+1].y)
            {
                //横向划线
                width=widget->pointBackup[count+1].x-widget->pointBackup[count].x+1;
                for(j=0; j<width; j++)
                {
                    ((llColor*)((widget->imageBuf).u8ReadBuf))[widget->pointBackup[count].x-widget->pointerPos0.x+j]=widget->pointerColor;
                }
                count=count+2;
            }
            else
            {
                ((llColor*)((widget->imageBuf).u8ReadBuf))[widget->pointBackup[count].x-widget->pointerPos0.x]=widget->pointerColor;
                count++;
            }

        }
        llFillMultipleColors(widget->pointerPos0.x,widget->pointerPos0.y+i,widget->pointerPos1.x,widget->pointerPos0.y+i,((llColor*)((widget->imageBuf).u8ReadBuf)));
        imageGeometry.y++;
    }
}

void llGaugeBubbleSort(llPoint *buffer,uint32_t length)
{
    uint32_t i,j,k;

    uint32_t count=0,startPos=0,startValue=0;
    //冒泡排序,排坐标Y
    for(i=0; i<length-1; i++) //n个数的数列总共扫描n-1次
    {
        for(j=0; j<length-i-1; j++) //每一趟扫描到a[n-i-2]与a[n-i-1]比较为止结束
        {
            if(buffer[j].y>buffer[j+1].y)//后一位数比前一位数小的话，就交换两个数的位置（升序）
            {
                SWAP(buffer[j].x,buffer[j+1].x);
                SWAP(buffer[j].y,buffer[j+1].y);
            }
        }
    }

    for(k=0; k<length-1; k++) //n个数的数列总共扫描n-1次
    {
        if(buffer[k].y==buffer[k+1].y)
        {
            count++;
            if(startValue!=buffer[k].y)
            {
                startValue=buffer[k].y;
                startPos=k;
            }
        }
        else
        {
            if(count>0)
            {
                count++;

                //冒泡排序,排坐标X
                for(i=0; i<count-1; i++) //n个数的数列总共扫描n-1次
                {
                    for(j=0; j<count-i-1; j++) //每一趟扫描到a[n-i-2]与a[n-i-1]比较为止结束
                    {
                        if(buffer[startPos+j].x>buffer[startPos+j+1].x)//后一位数比前一位数小的话，就交换两个数的位置（升序）
                        {
                            SWAP(buffer[startPos+j].x,buffer[startPos+j+1].x);
                        }
                    }
                }
                count=0;
            }
        }
    }

    if(count>0)
    {
        count++;

        //冒泡排序,排坐标X
        for(i=0; i<count-1; i++) //n个数的数列总共扫描n-1次
        {
            for(j=0; j<count-i-1; j++) //每一趟扫描到a[n-i-2]与a[n-i-1]比较为止结束
            {
                if(buffer[startPos+j].x>buffer[startPos+j+1].x)//后一位数比前一位数小的话，就交换两个数的位置（升序）
                {
                    SWAP(buffer[startPos+j].x,buffer[startPos+j+1].x);
                }
            }
        }
        count=0;
    }
}

void llGaugeDeleteArr(llPoint *buffer, uint32_t pos, uint32_t length)//M是位置，val是被删除的值，n是数组个数
{
    for(uint32_t i = pos; i < length; i++)
    {
        buffer[i] = buffer[i+1];
    }
    buffer[length-1].x=0;
    buffer[length-1].y=0;
}

uint32_t llGaugeAutoDeleteSameArrX(llPoint *buffer,uint32_t length)
{
    uint32_t k;

    for(k=0; k<(length-2);) //n个数的数列总共扫描n-1次
    {
        if((buffer[k].y==buffer[k+1].y)&&((buffer[k].y==buffer[k+2].y)))
        {
            llGaugeDeleteArr(buffer,k+1,length);
            length--;
        }
        else
        {
            k++;
        }
    }
    return k+2;
}

uint32_t llGaugeAutoDeleteSameArr(llPoint *buffer,uint32_t length)
{
    uint32_t k;

    for(k=0; k<length;)
    {
        if((buffer[k].y==buffer[k+1].y)&&((buffer[k].x==buffer[k+1].x)))
        {
            llGaugeDeleteArr(buffer,k+1,length);
            length--;
        }
        else
        {
            k++;
        }
    }
    return k;
}

void pGaugePointerRotary(llGauge *widget)
{
//    图片上任意点(x,y)，绕一个坐标点(rx0,ry0)逆时针旋转RotaryAngle角度
//    新的坐标设为(x', y')，公
//    x'= (x - rx0)*cos(RotaryAngle) + (y - ry0)*sin(RotaryAngle) + rx0 ;
//    y'=-(x - rx0)*sin(RotaryAngle) + (y - ry0)*cos(RotaryAngle) + ry0 ;

//    求源坐标点的公式
//    x=(x'- rx0)*cos(RotaryAngle) - (y'- ry0)*sin(RotaryAngle) + rx0 ;
//    y=(x'- rx0)*sin(RotaryAngle) + (y'- ry0)*cos(RotaryAngle) + ry0 ;

    int16_t x0,y0;//旋转中心
    float sina,cosa;
    uint8_t u8Temp;
    int16_t xPosTemp,yPosTemp;
//    int rotaryAngle;
    llPoint posOffset;

    //获取偏移坐标
    posOffset=llListGetGlobalPos((llGeneral*)widget);

    //整理角度值,大于360度,转换为0-359度
    widget->rotaryAngle%=360;

    sina=sina_val[360-widget->rotaryAngle]; //361个角
    cosa=cosa_val[360-widget->rotaryAngle]; //361个角

    //计算原点真实坐标
    if((widget->originalPoint.x==0)&&(widget->originalPoint.y==0))//没有设定原点就默认图片中间
    {
        x0=widget->geometry.width/2+posOffset.x;
        y0=widget->geometry.height/2+posOffset.y;
    }
    else
    {
        x0=widget->originalPoint.x+posOffset.x;
        y0=widget->originalPoint.y+posOffset.y;
    }

    //初始化端点偏移前的坐标
    widget->newEndpoint[0].x=x0-widget->pointerWidth1/2;
    widget->newEndpoint[0].y=y0+widget->originalPointerDistance;
    widget->newEndpoint[1].x=x0+widget->pointerWidth1/2;
    widget->newEndpoint[1].y=y0+widget->originalPointerDistance;
    widget->newEndpoint[2].x=x0+widget->pointerWidth2/2;
    widget->newEndpoint[2].y=y0+widget->originalPointerDistance+widget->pointerLength;
    widget->newEndpoint[3].x=x0-widget->pointerWidth2/2;
    widget->newEndpoint[3].y=y0+widget->originalPointerDistance+widget->pointerLength;

    //计算端点旋转后的坐标
    for(u8Temp=0; u8Temp<4; u8Temp++)
    {
//      x'= (x - rx0)*cos(RotaryAngle) + (y - ry0)*sin(RotaryAngle) + rx0 ;
//      y'=-(x - rx0)*sin(RotaryAngle) + (y - ry0)*cos(RotaryAngle) + ry0 ;
        xPosTemp=(widget->newEndpoint[u8Temp].x-x0)*cosa +(widget->newEndpoint[u8Temp].y-y0)*sina+x0;
        yPosTemp=-(widget->newEndpoint[u8Temp].x-x0)*sina +(widget->newEndpoint[u8Temp].y-y0)*cosa+y0;

        widget->newEndpoint[u8Temp].x=xPosTemp;
        widget->newEndpoint[u8Temp].y=yPosTemp;
    }

    widget->pointCount=0;
    //获取外框坐标数据
    widget->pointCount=llGaugeBresenhamLine(widget->newEndpoint[0].x,widget->newEndpoint[0].y,widget->newEndpoint[1].x,widget->newEndpoint[1].y,&widget->pointBackup[widget->pointCount]);
    widget->pointCount+=llGaugeBresenhamLine(widget->newEndpoint[2].x,widget->newEndpoint[2].y,widget->newEndpoint[1].x,widget->newEndpoint[1].y,&widget->pointBackup[widget->pointCount]);
    widget->pointCount+=llGaugeBresenhamLine(widget->newEndpoint[2].x,widget->newEndpoint[2].y,widget->newEndpoint[3].x,widget->newEndpoint[3].y,&widget->pointBackup[widget->pointCount]);
    widget->pointCount+=llGaugeBresenhamLine(widget->newEndpoint[0].x,widget->newEndpoint[0].y,widget->newEndpoint[3].x,widget->newEndpoint[3].y,&widget->pointBackup[widget->pointCount]);

    //整理周长坐标
    llGaugeBubbleSort(widget->pointBackup,widget->pointCount);
    widget->pointCount=llGaugeAutoDeleteSameArrX(widget->pointBackup,widget->pointCount);
    widget->pointCount=llGaugeAutoDeleteSameArr(widget->pointBackup,widget->pointCount);

    //使用两个buf ，轮流保存新数据。另外一个buf保存旧数据；先显示新数据，在恢复旧背景

    llGaugeFillPolygon(widget);

    widget->oldEndpoint[0]=widget->newEndpoint[0];
    widget->oldEndpoint[1]=widget->newEndpoint[1];
    widget->oldEndpoint[2]=widget->newEndpoint[2];
    widget->oldEndpoint[3]=widget->newEndpoint[3];
}

void pGaugeSetRotaryAngle(llGauge *widget,int16_t rotaryAngle,bool isInit)
{
    if((widget->isEnable)&&(!widget->isHidden))
    {
        if(widget->isColor)
        {
            widget->rotaryAngle=rotaryAngle;
            if(widget->isInit)
            {
                llTimer_start(&widget->loopCounter);
                widget->angleBuffer=rotaryAngle;
                pGaugePointerRotary(widget);
                widget->isInit=false;
            }
        }
        else
        {
#ifdef USE_LLGAUGE_EX
            pGaugeExSetRotaryAngle(widget,rotaryAngle,isInit);
#endif
        }
    }
}

void nGaugeSetRotaryAngle(uint16_t nameId,int16_t rotaryAngle,bool isInit)
{
    void *widget;
    widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        pGaugeSetRotaryAngle((llGauge*)widget,rotaryAngle,isInit);
    }
}

int16_t pGaugeGetRotaryAngle(llGauge *widget)
{
    if(widget->isColor)
    {
        return widget->angleBuffer;
    }
    else
    {
#ifdef USE_LLGAUGE_EX
        return pGaugeExGetRotaryAngle(widget);
#else
        return 0;
#endif
    }
    
}

int16_t nGaugeGetRotaryAngle(uint16_t nameId)
{
    void *widget;
    widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        return pGaugeGetRotaryAngle((llGauge*)widget);
    }
    return 0;
}

void pGaugeLoop(llGauge *widget,uint16_t refreshMs,uint8_t moveValue)
{
    int16_t backup_target_angle;
    int16_t cal_angle;

    if((widget->isEnable)&&(!widget->isHidden))
    {
        if(widget->isColor)
        {
        if(llTimer_timeOut(&widget->loopCounter,refreshMs,true))
        {
            if(widget->rotaryAngle!=widget->angleBuffer)
            {
                backup_target_angle=widget->rotaryAngle;

                cal_angle=widget->rotaryAngle-widget->angleBuffer;

                if(moveValue==0)
                {
                    moveValue=1;
                }

                if(cal_angle>0)
                {
                    if(cal_angle>moveValue)
                    {
                        widget->angleBuffer=widget->angleBuffer+moveValue;
                    }
                    else
                    {
                        widget->angleBuffer++;
                    }
                }
                else
                {
                    if(cal_angle<moveValue)
                    {
                        widget->angleBuffer=widget->angleBuffer-moveValue;
                    }
                    else
                    {
                        widget->angleBuffer--;
                    }
                }
                widget->rotaryAngle=widget->angleBuffer;
                pGaugePointerRotary(widget);
                widget->rotaryAngle=backup_target_angle;
            }
        }
    }
    }
}

void nGaugeLoop(uint16_t nameId,uint16_t refreshMs,uint8_t moveValue)
{
    void *widget;
    widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        pGaugeLoop((llGauge*)widget,refreshMs,moveValue);
    }
}

void llGaugeInit(void)
{
#ifdef USE_LLGAUGE_EX
    llGaugeExInit();
#endif
}

void llGaugeLoop(void)
{
#ifdef USE_LLGAUGE_EX
    llGaugeExLoop();
#endif
}

void llGaugeQuit(void)
{
#ifdef USE_LLGAUGE_EX
    llGaugeExQuit();
#endif
}

void pGaugeSetEnabled(llGauge *widget, bool state)
{
    widget->isEnable=state;
}

void nGaugeSetEnabled(uint16_t nameId, bool state)
{
    void *widget;
    widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        pGaugeSetEnabled((llGauge*)widget,state);
    }
}


void pGaugeSetHidden(llGauge *widget,bool isHidden)
{
    if(llGeometryAutoSetHiddenIsShow((llGeneral*)widget,isHidden)==true)
    {
        pGaugeRefresh(widget);
    }
}

void nGaugeSetHidden(uint16_t nameId,bool isHidden)
{
    void *widget;
    widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        pGaugeSetHidden(widget,isHidden);
    }
}




