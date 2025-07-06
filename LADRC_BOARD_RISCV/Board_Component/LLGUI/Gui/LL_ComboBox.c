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

#include "LL_ComboBox.h"
#include "LL_Linked_List.h"

void pComboBoxFree(llComboBox *widget)
{
    uint8_t i;
    for(i=0; i<widget->itemCount; i++)
    {
        llFree(widget->textList[i]);
    }
    llFree(widget);
}

void nComboBoxDelete(uint16_t nameId)
{
    llListHead *tempPos,*safePos;
    llListWidgetInfo *linkInfo;
    llListWidgetInfo *parentInfo;
    llListWidgetInfo *tempInfo;
    llComboBox *widget;

    if(llList_GetInfoByName(&linkInfo,nameId)==true)
    {
        widget=linkInfo->widget;

        //查找父链表
        llList_GetInfoByName(&parentInfo,((llGeneral*)widget->parentWidget)->nameId);
        //消除自身在父链表中的位置数据
        list_for_each_prev_safe(tempPos, safePos,&parentInfo->child_link)
        {
            tempInfo = list_entry(tempPos, llListWidgetInfo, parent_link_pos);
            if(tempInfo->widget==widget)
            {
                llLinkedListDelete(tempPos);
                pComboBoxFree(widget);
                llFree(tempInfo);
            }
        }
    }
}

void llComboBoxAction(void *widget,uint8_t touchSignal)
{
    uint16_t xOffset;
    uint16_t yOffset;
    static bool isMove;
    if((((llComboBox*)widget)->isEnable)&&(((llComboBox*)widget)->isHidden==false))
    {
        switch(touchSignal)
        {
            case SIGNAL_CLICK_PRESSED:
            case SIGNAL_CLICK_RELEASED:
            {
                isMove=false;
                llEmitSignal(widget,touchSignal);
                break;
            }
            case SIGNAL_CLICK_HOLD_MOVE:
            {
                if(!isMove)
                {
                    llGuiGetMoveOffset(&xOffset,&yOffset);
                    if((xOffset>=LL_MOVE_START_PIXEL)||(yOffset>=LL_MOVE_START_PIXEL))
                    {
                        isMove=true;
                    }
                }
                else
                {
                    llEmitSignal(widget,touchSignal);
                }
                break;
            }
            default:
                break;
        }
    }
}

void pComboBoxRefresh(llComboBox *widget)
{
    llPoint globalPos,tempPos1,tempPos2;
    llChar textInfo;
    uint8_t i;

    int16_t itemPosOffset;

    if((widget->isEnable)&&(!widget->isHidden))
    {
        if(llGeneralParentLinkHidden((llGeneral*)widget)==false)
        {
            llCharOpenLibrary(widget->fontLibInfo->libType,(uint8_t *)widget->fontLibInfo->name,widget->fontLibInfo->fontSize);
            textInfo.text=llMalloc(widget->itemLenMax);
            textInfo.isAutoLineBreak=false;
            globalPos=llListGetGlobalPos(widget->parentWidget);
            globalPos.x=globalPos.x+widget->geometry.x;
            globalPos.y=globalPos.y+widget->geometry.y;

            if(widget->isSlide==false)
            {
                //显示外框
                llDrawLine(globalPos.x,globalPos.y,globalPos.x+widget->geometry.width-1,globalPos.y,RGB888(0xABACAD));
                llDrawLine(globalPos.x,globalPos.y,globalPos.x,globalPos.y+widget->itemHeight-1,RGB888(0xABACAD));
                llDrawLine(globalPos.x+widget->geometry.width-1,globalPos.y,globalPos.x+widget->geometry.width-1,globalPos.y+widget->itemHeight-1,RGB888(0xABACAD));
                llDrawLine(globalPos.x,globalPos.y+widget->itemHeight-1,globalPos.x+widget->geometry.width-1,globalPos.y+widget->itemHeight-1,RGB888(0xABACAD));
                //显示底色
                llFillSingleColor(globalPos.x+1,globalPos.y+1,globalPos.x+widget->geometry.width-2,globalPos.y+widget->itemHeight-2,widget->bgColor);
                //画箭头
                tempPos1.x=globalPos.x+widget->geometry.width-1-(widget->itemHeight>>2);
                tempPos1.y=globalPos.y+widget->itemHeight/3;
                tempPos2.x=globalPos.x+widget->geometry.width-1-(widget->itemHeight>>1);
                tempPos2.y=globalPos.y+widget->itemHeight/3*2;
                llDrawLine(tempPos1.x,tempPos1.y,tempPos2.x,tempPos2.y,0);
                tempPos1.x=tempPos2.x-(widget->itemHeight>>2);
                llDrawLine(tempPos1.x,tempPos1.y,tempPos2.x,tempPos2.y,0);

                if(widget->itemCount==0)
                {
                    return ;
                }
                memset(textInfo.text,0,widget->itemLenMax);

                //更新文字坐标
                textInfo.geometry.x=globalPos.x+5;
                textInfo.geometry.y=globalPos.y;
                textInfo.geometry.width=widget->geometry.width-5-widget->itemHeight;
                textInfo.geometry.height=widget->itemHeight-1;
                textInfo.showGeometry=textInfo.geometry;
                textInfo.isPassword=false;
                textInfo.isTransparent=false;
                textInfo.hAlign=llAlignHLeft;
                textInfo.vAlign=llAlignVCenter;
                textInfo.charColor=widget->textColor;
                textInfo.backgroundColor=widget->bgColor;

                strcpy((char*)textInfo.text,(const char*)widget->textList[widget->selectNum]);
                llCharDisplay((llGeneral*)widget,&textInfo,false);

                if(widget->geometry.height!=widget->itemHeight)
                {
                    //显示底色
                    llFillSingleColor(globalPos.x+1,globalPos.y+widget->itemHeight,globalPos.x+widget->geometry.width-1,globalPos.y+(widget->itemCount+1)*widget->itemHeight-2,widget->listBgColor);
                    //显示外框
                    llDrawLine(globalPos.x,globalPos.y+widget->itemHeight,globalPos.x,globalPos.y+(widget->itemCount+1)*widget->itemHeight-1,RGB888(0xABACAD));
                    llDrawLine(globalPos.x+widget->geometry.width-1,globalPos.y+widget->itemHeight,globalPos.x+widget->geometry.width-1,globalPos.y+(widget->itemCount+1)*widget->itemHeight-1,RGB888(0xABACAD));
                    llDrawLine(globalPos.x,globalPos.y+(widget->itemCount+1)*widget->itemHeight-1,globalPos.x+widget->geometry.width-1,globalPos.y+(widget->itemCount+1)*widget->itemHeight-1,RGB888(0xABACAD));

                    //选中项底色
                    llFillSingleColor(globalPos.x+1,globalPos.y+widget->itemHeight*(widget->selectNum+1),globalPos.x+widget->geometry.width-1,globalPos.y+widget->itemHeight*(widget->selectNum+1)+widget->itemHeight-1,widget->selectBgColor);

                    for(i=0; i<LL_COMBOBOX_ITEM_MAX; i++)
                    {
                        if(widget->textList[i]!=NULL)
                        {
                            memset(textInfo.text,0,widget->itemLenMax);

                            //更新文字坐标
                            textInfo.geometry.y=globalPos.y+(i+1)*widget->itemHeight;
                            textInfo.showGeometry.y=textInfo.geometry.y;


                            strcpy((char*)textInfo.text,(const char*)widget->textList[i]);

                            textInfo.charColor=widget->textColor;
                            textInfo.backgroundColor=widget->listBgColor;

                            if(i==widget->selectNum)
                            {
                                textInfo.charColor=RGB888(0xFFFFFF)-widget->textColor;
                                textInfo.backgroundColor=widget->selectBgColor;
                            }
                            llCharDisplay((llGeneral*)widget,&textInfo,false);
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
            else
            {
                //显示外框
                llDrawLine(globalPos.x,globalPos.y,globalPos.x+widget->geometry.width-1,globalPos.y,RGB888(0xABACAD));
                llDrawLine(globalPos.x,globalPos.y,globalPos.x,globalPos.y+widget->geometry.height-1,RGB888(0xABACAD));
                llDrawLine(globalPos.x+widget->geometry.width-1,globalPos.y,globalPos.x+widget->geometry.width-1,globalPos.y+widget->geometry.height-1,RGB888(0xABACAD));
                llDrawLine(globalPos.x,globalPos.y+widget->geometry.height-1,globalPos.x+widget->geometry.width-1,globalPos.y+widget->geometry.height-1,RGB888(0xABACAD));

                if(widget->geometry.height==widget->itemHeight)
                {
                    llFillSingleColor(globalPos.x+1,globalPos.y+1,globalPos.x+widget->geometry.width-2,globalPos.y+widget->itemHeight-2,widget->bgColor);
                    //画上下
                    tempPos1.x=globalPos.x+widget->geometry.width-1-(widget->itemHeight>>2);
                    tempPos1.y=globalPos.y+widget->itemHeight/3;
                    tempPos2.x=globalPos.x+widget->geometry.width-1-(widget->itemHeight>>1);
                    tempPos2.y=globalPos.y+widget->itemHeight/3*2;
                    llDrawLine(tempPos1.x,tempPos1.y,tempPos2.x,tempPos2.y,0);
                    tempPos1.x=tempPos2.x-(widget->itemHeight>>2);
                    llDrawLine(tempPos1.x,tempPos1.y,tempPos2.x,tempPos2.y,0);
                }

                if(widget->itemCount==0)
                {
                    return ;
                }
                //更新文字坐标
                textInfo.geometry.x=globalPos.x+5;
                textInfo.geometry.y=globalPos.y;
                textInfo.geometry.width=widget->geometry.width-5-widget->itemHeight;
                textInfo.geometry.height=widget->geometry.height;
                textInfo.showGeometry=textInfo.geometry;
                textInfo.isPassword=false;
                textInfo.isTransparent=false;
                textInfo.hAlign=llAlignHLeft;
                textInfo.vAlign=llAlignVCenter;
                textInfo.charColor=widget->textColor;

                itemPosOffset=-widget->itemHeight*widget->selectNum;

                if(widget->geometry.height!=widget->itemHeight)
                {
                    llFillSingleColor(globalPos.x+1,globalPos.y+1,globalPos.x+widget->geometry.width-2,globalPos.y+widget->itemHeight-1,widget->bgColor);
                    //选中项底色
                    llFillSingleColor(globalPos.x+1,globalPos.y+widget->itemHeight,globalPos.x+widget->geometry.width-2,globalPos.y+widget->itemHeight*2-1,widget->selectBgColor);

                    llFillSingleColor(globalPos.x+1,globalPos.y+widget->itemHeight*2,globalPos.x+widget->geometry.width-2,globalPos.y+widget->itemHeight*3-2,widget->bgColor);

                    for(i=0; i<LL_COMBOBOX_ITEM_MAX; i++)
                    {
                        if(widget->textList[i]!=NULL)
                        {
                            memset(textInfo.text,0,widget->itemLenMax);

                            //更新文字坐标
                            textInfo.geometry.y=globalPos.y+i*widget->itemHeight+itemPosOffset+widget->moveOffset;

                            strcpy((char*)textInfo.text,(const char*)widget->textList[i]);

                            if((i==widget->selectNum)&&(widget->isMove==false))
                            {
                                textInfo.charColor=RGB888(0xFFFFFF)-widget->textColor;
                                textInfo.backgroundColor=widget->selectBgColor;
                            }
                            else
                            {
                                textInfo.charColor=widget->textColor;
                                textInfo.backgroundColor=widget->bgColor;
                            }
                            llCharDisplay((llGeneral*)widget,&textInfo,false);
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                else
                {
                    memset(textInfo.text,0,widget->itemLenMax);

                    strcpy((char*)textInfo.text,(const char*)widget->textList[widget->selectNum]);
                    textInfo.backgroundColor=widget->bgColor;
                    llCharDisplay((llGeneral*)widget,&textInfo,false);
                }
            }
            llFree(textInfo.text);
        }
    }
}

void nComboBoxRefresh(uint16_t nameId)
{
    void *widget;
    widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        pComboBoxRefresh((llComboBox*)widget);
    }
}

bool slotComboBoxHoldMove(llConnectInfo info)
{
    llComboBox * widget;
    llGeometry targetGeometry;
    llPoint clickPoint;
    uint8_t i;
    llPoint globalPos;


    widget=(llComboBox*)info.sender;

    if(widget->isSlide==false)
    {
        if(widget->geometry.height!=widget->itemHeight)
        {
            globalPos=llListGetGlobalPos(widget->parentWidget);

            targetGeometry=widget->geometry;
            targetGeometry.x=widget->geometry.x+globalPos.x;
            targetGeometry.y=widget->geometry.y+globalPos.y;
            targetGeometry.height=widget->itemHeight;

            if(llClickGetPoint(&clickPoint.x,&clickPoint.y)==true)
            {
                for(i=0; i<widget->itemCount; i++)
                {
                    targetGeometry.y+=widget->itemHeight;
                    if((llPointInRect(clickPoint,targetGeometry))&&(widget->selectNum!=i))
                    {
                        widget->selectNum=i;
                        pComboBoxRefresh(widget);
                        break;
                    }
                }
            }
            else
            {
                widget->isExpand=false;
            }
        }
    }
    else//滑动
    {
        if((widget->clickCount!=0)&&(llClickGetPoint(&clickPoint.x,&clickPoint.y)==true))//第一次点击展开，不允许滑动
        {
            widget->isMove=true;
            widget->moveOffset=clickPoint.y-widget->pressPoint.y;
            pComboBoxRefresh(widget);
        }
    }
    return false;
}

bool slotComboBoxRelease(llConnectInfo info)
{
    llComboBox * widget;
    llGeometry targetGeometry;
    llPoint globalPos;
    int16_t cb0_y,sel_cb_y,itemOffset;
    int8_t calItemNum;


    widget=(llComboBox*)info.sender;
    globalPos=llListGetGlobalPos(widget->parentWidget);
    if(widget->isSlide==false)
    {
        if((widget->isExpand==false)&&(widget->geometry.height!=widget->itemHeight))//选择新项目
        {
            llGuiSetTopWidget(NULL);//取消临时提升

            targetGeometry=widget->geometry;
            targetGeometry.x=widget->geometry.x+globalPos.x;
            targetGeometry.y=widget->geometry.y+globalPos.y;
            targetGeometry.y+=widget->itemHeight;
            targetGeometry.height=widget->itemHeight*widget->itemCount;
            llGeneralRecover((llGeneral*)widget,targetGeometry);
            widget->geometry.height=widget->itemHeight;

            pComboBoxRefresh(widget);
        }
    }
    else//滑动
    {
        if(widget->clickCount==0)//第一次点击
        {
            llGuiSetTopWidget(widget);//临时提升为最顶层控件
            widget->isExpand=true;
            widget->geometry.y-=widget->itemHeight;
            widget->geometry.height=widget->itemHeight*3;
            widget->clickCount++;
        }
        else
        {
            if(widget->isMove==false)//还原comboBox
            {
                //根据select计算坐标+偏移，计算最新select

                //计算第0个选项的y坐标
                cb0_y=widget->geometry.y+(1-widget->selectNum)*widget->itemHeight+widget->moveOffset;
                //计算外框中间选中项目的坐标
                sel_cb_y=widget->geometry.y+widget->itemHeight;

                //计算差值，判断序号
                widget->selectNum=(sel_cb_y-cb0_y+0.5)/widget->itemHeight;

                llGuiSetTopWidget(NULL);//取消临时提升
                widget->isExpand=false;

                targetGeometry=widget->geometry;
                targetGeometry.x=widget->geometry.x+globalPos.x;
                targetGeometry.y=widget->geometry.y+globalPos.y;
                targetGeometry.height=widget->itemHeight*3;
                llGeneralRecover((llGeneral*)widget,targetGeometry);

                widget->geometry.y+=widget->itemHeight;
                widget->geometry.height=widget->itemHeight;
                widget->clickCount=0;
                widget->moveOffset=0;
            }
            else//移动后修正坐标
            {
                widget->isMove=false;//必须先清除,刷新显示要用到改标志

                //根据select计算坐标+偏移，计算最新select

                //计算第0个选项的y坐标
                cb0_y=widget->geometry.y+(1-widget->selectNum)*widget->itemHeight+widget->moveOffset;
                //计算外框中间选中项目的坐标
                sel_cb_y=widget->geometry.y+widget->itemHeight;

                itemOffset=sel_cb_y-cb0_y;

                //计算差值，判断序号
                calItemNum=itemOffset/widget->itemHeight;

                itemOffset=itemOffset%widget->itemHeight;

                if(calItemNum<0)
                {
                    calItemNum=0;
                }
                if(calItemNum>(widget->itemCount-1))
                {
                    calItemNum=widget->itemCount-1;
                }

                if(itemOffset>(widget->itemHeight/3))
                {
                    if(calItemNum<(widget->itemCount-1))
                    {
                        calItemNum++;
                    }
                }
                if(itemOffset<(-widget->itemHeight/3))
                {
                    if(calItemNum>0)
                    {
                        calItemNum--;
                    }
                }
                widget->selectNum=calItemNum;
                widget->moveOffset=0;
            }
            llEmitSignal(widget,SIGNAL_VALUE_CHANGED);
        }
        pComboBoxRefresh(widget);

    }
    return false;
}

bool slotComboBoxPress(llConnectInfo info)
{
    llComboBox * widget;
    llGeometry targetGeometry;
    llPoint clickPoint;
    uint8_t i;
    llPoint globalPos;

    widget=(llComboBox*)info.sender;

    globalPos=llListGetGlobalPos(widget->parentWidget);

    if(llClickGetPoint(&clickPoint.x,&clickPoint.y)==true)
    {
        if(widget->isSlide==false)
        {
            targetGeometry=widget->geometry;
            targetGeometry.x=widget->geometry.x+globalPos.x;
            targetGeometry.y=widget->geometry.y+globalPos.y;
            targetGeometry.height=widget->itemHeight;
            if(llPointInRect(clickPoint,targetGeometry))
            {
                if(widget->isExpand==false)
                {
                    llGuiSetTopWidget(widget);//临时提升为最顶层控件
                    widget->isExpand=true;
                    widget->geometry.height=widget->itemHeight*(widget->itemCount+1);
                }
                else
                {
                    llGuiSetTopWidget(NULL);//取消临时提升
                    widget->isExpand=false;
                    targetGeometry.y+=widget->itemHeight;
                    targetGeometry.height=widget->itemHeight*widget->itemCount;
                    llGeneralRecover((llGeneral*)widget,targetGeometry);
                    widget->geometry.height=widget->itemHeight;
                }
                pComboBoxRefresh(widget);
            }
            else
            {
                //选择新项目
                for(i=0; i<widget->itemCount; i++)
                {
                    targetGeometry.y+=widget->itemHeight;
                    if(llPointInRect(clickPoint,targetGeometry))
                    {
                        widget->selectNum=i;
                        llEmitSignal(widget,SIGNAL_VALUE_CHANGED);
                        break;
                    }
                }
                pComboBoxRefresh(widget);
                widget->isExpand=false;
            }
        }
        else//滑动选择
        {
            widget->isMove=false;
            if(widget->isExpand==true)
            {
                widget->pressPoint=clickPoint;
            }
        }
    }
    return false;
}

llComboBox* llComboBoxQuickCreate(uint16_t nameId, uint16_t parentNameId,int16_t x, int16_t y, int16_t width, int16_t height,
                                  llFontLib *fontLib,llColor textColor,llColor bgColor,llColor listBgColor,llColor selectBgColor,
                                  uint8_t defaultSelectNum,bool isHidden)
{
    llComboBox * pNewWidget = NULL;
    llListWidgetInfo *parentInfo;

    //检查父链表存在
    if(llList_GetInfoByName(&parentInfo,parentNameId)==true)
    {
        pNewWidget = LL_MALLOC_WIDGET_INFO(llComboBox);
        if(pNewWidget!=NULL)
        {
            pNewWidget->nameId=nameId;

            pNewWidget->widgetType=widgetTypeComboBox;
            pNewWidget->geometry.x=x;
            pNewWidget->geometry.y=y;
            pNewWidget->geometry.width=width;
            pNewWidget->geometry.height=height;
            pNewWidget->itemHeight=height;

            llListWidgetAdd(&(parentInfo->child_link),pNewWidget);
            pNewWidget->parentType=((llGeneral*)(parentInfo->widget))->widgetType;
            pNewWidget->parentWidget=parentInfo->widget;

            pNewWidget->deleteFunc=nComboBoxDelete;
            pNewWidget->actionFunc=llComboBoxAction;
            pNewWidget->refreshFunc=nComboBoxRefresh;

            pNewWidget->fontLibInfo=fontLib;
            pNewWidget->textColor=textColor;
            pNewWidget->bgColor=bgColor;
            pNewWidget->listBgColor=listBgColor;
            pNewWidget->selectBgColor=selectBgColor;
            pNewWidget->isExpand=false;
            pNewWidget->selectNum=defaultSelectNum;
            pNewWidget->itemLenMax=0;
            pNewWidget->itemCount=0;

            pNewWidget->isHidden=isHidden;
            pNewWidget->isEnable=true;
            pNewWidget->isSlide=false;
            pNewWidget->moveOffset=0;
            pNewWidget->clickCount=0;

            memset(pNewWidget->textList,0,sizeof(uint8_t*)*LL_COMBOBOX_ITEM_MAX);

            //动作
            llConnectSignal(nameId,SIGNAL_CLICK_PRESSED,nameId,slotComboBoxPress);
            llConnectSignal(nameId,SIGNAL_CLICK_RELEASED,nameId,slotComboBoxRelease);
            llConnectSignal(nameId,SIGNAL_CLICK_HOLD_MOVE,nameId,slotComboBoxHoldMove);

            pComboBoxRefresh(pNewWidget);
        }
        else
        {
            llFree(pNewWidget);
        }
    }
    return pNewWidget;
}

llComboBox* llComboBoxCreate(uint16_t nameId, uint16_t parentNameId,int16_t x, int16_t y, int16_t width, int16_t height,
                             llFontLib *fontLib,bool isHidden)
{
    return llComboBoxQuickCreate(nameId,parentNameId,x,y,width,height,fontLib,0,RGB888(0xE1E1E1),RGB888(0xFFFFFF),RGB888(0x0078d7),0,false);
}

void pComboBoxAddItem(llComboBox *widget,uint8_t *itemText)
{
    uint8_t i;
    uint16_t textLen;

    if(widget->isEnable)
    {
        //查找空位
        for(i=0; i<LL_COMBOBOX_ITEM_MAX; i++)
        {
            if(widget->textList[i]==NULL)
            {
                break;
            }
        }
        if(widget->textList[i]==NULL)
        {
            textLen=strlen((const char*)itemText)+1;
            widget->textList[i]=llMalloc(textLen);
            memset(widget->textList[i],0,textLen);
            strcpy((char *)widget->textList[i],(const char *)itemText);

            if(widget->itemLenMax<textLen)
            {
                widget->itemLenMax=textLen;
            }
            widget->itemCount++;
        }
        pComboBoxRefresh(widget);
    }
}

void nComboBoxAddItem(uint16_t nameId,uint8_t *text)
{
    void *widget;
    widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        pComboBoxAddItem((llComboBox*)widget,text);
    }
}

//void pComboBoxSetHidden(llComboBox *widget,bool isHidden)
//{
//    if(llGeometryAutoSetHiddenIsShow((llGeneral*)widget,isHidden)==true)
//    {
//        pComboBoxRefresh(widget);
//    }
//}

//void nComboBoxSetHidden(uint16_t nameId,bool isHidden)
//{
//    void *widget;
//    widget=llGeneralGetWidget(nameId);
//    if(widget!=NULL)
//    {
//        pComboBoxSetHidden(widget,isHidden);
//    }
//}

void pComboBoxSetEnabled(llComboBox *widget, bool state)
{
    widget->isEnable=state;
}

void nComboBoxSetEnabled(uint16_t nameId, bool state)
{
    void *widget;
    widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        pComboBoxSetEnabled((llComboBox*)widget,state);
    }
}

void pComboBoxSetSelect(llComboBox *widget, uint8_t num)
{
    widget->selectNum=num;
    pComboBoxRefresh(widget);
}

void nComboBoxSetSelect(uint16_t nameId, uint8_t num)
{
    void *widget;
    widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        pComboBoxSetSelect((llComboBox*)widget,num);
    }
}

uint8_t pComboBoxGetSelect(llComboBox *widget)
{
    return widget->selectNum;
}

uint8_t nComboBoxGetSelect(uint16_t nameId)
{
    void *widget;
    widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        return pComboBoxGetSelect((llComboBox*)widget);
    }
    return 0;
}

void pComboBoxSetSlide(llComboBox *widget,bool isSlide)
{
    widget->isSlide=isSlide;
}

void nComboBoxSetSlide(uint16_t nameId,bool isSlide)
{
    void *widget;
    widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        pComboBoxSetSlide((llComboBox*)widget,isSlide);
    }
}

uint8_t* pComboBoxGetText(llComboBox *widget)
{
    return widget->textList[widget->selectNum];
}

uint8_t* nComboBoxGetText(uint16_t nameId)
{
    void *widget;
    widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        return pComboBoxGetText((llComboBox*)widget);
    }
    return 0;
}
