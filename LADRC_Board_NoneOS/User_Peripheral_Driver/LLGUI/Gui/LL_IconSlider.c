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

#include "LL_IconSlider.h"
#include "LL_Linked_List.h"
#include "LL_Gui.h"
#include "LL_Timer.h"

#ifndef LL_ICON_SLIDER_RET_OFFSET
#define LL_ICON_SLIDER_RET_OFFSET    4
#endif

void llIconSliderAction(void *widget, uint8_t touchSignal);
void nIconSliderDelete(uint16_t nameId);
void pIconSliderRefresh(llIconSlider *widget);
void nIconSliderRefresh(uint16_t nameId);

bool slotIconSliderPressed(llConnectInfo info)
{
    llIconSlider * widget;
    int16_t x,y;
    widget=(llIconSlider*)info.receiver;

    if((widget->isEnable)&&(!widget->isHidden))
    {
        if(llClickGetPoint(&x,&y)==true)
        {
            llTimer_stop(&widget->clickTimer);
            widget->isClickItem=true;
            widget->clickPoint.x=x;
            widget->clickPoint.y=y;
            widget->releaseTargetX=widget->moveX;
            widget->releaseTargetY=widget->moveY;
            widget->moveOffset=0;
//            llEmitSignal(widget,SIGNAL_CLICK_PRESSED);
            return true;
        }
    }
    return false;
}

bool slotIconSliderReleased(llConnectInfo info)
{
    llIconSlider * widget;
    uint8_t minShowItemCount;

    widget=(llIconSlider*)info.receiver;
    if((widget->isEnable)&&(!widget->isHidden))
    {
        if((widget->moveOffset>30)||(widget->moveOffset<-30))
        {
            if(widget->isHorizontalScroll)//水平
            {
                if(widget->moveOffset<0)//向左拖动
                {
                    widget->itemNum=(-widget->moveX)/(widget->itemWidth*widget->columnCount+widget->pageSpacing)*widget->columnCount;
                    widget->itemNum+=widget->rowCount*widget->columnCount;

                    //计算能显示几个图片
                    minShowItemCount=(widget->geometry.width+widget->pageSpacing)/(widget->itemWidth*widget->columnCount+widget->pageSpacing)*(widget->rowCount*widget->columnCount);

                    if(widget->imageCount>minShowItemCount)
                    {
                        if(widget->itemNum>=(widget->imageCount-minShowItemCount))
                        {
                            widget->itemNum=widget->imageCount-minShowItemCount;
                        }
                        widget->releaseTargetX=-(widget->itemNum/(widget->columnCount*widget->rowCount))*(widget->itemWidth*widget->columnCount+widget->pageSpacing);
                    }
                    else
                    {
                        widget->releaseTargetX=0;
                        widget->itemNum=0;
                    }
                }
                else//向右拖动
                {
                    if(widget->moveX>0)
                    {
                        widget->releaseTargetX=0;
                        widget->itemNum=0;
                    }
                    else
                    {
                        widget->itemNum=(-widget->moveX)/(widget->itemWidth*widget->columnCount+widget->pageSpacing)*widget->columnCount;

                        if(widget->itemNum>=widget->imageCount)
                        {
                            widget->itemNum=widget->imageCount-1;
                        }

                        widget->releaseTargetX=-(widget->itemNum/(widget->columnCount*widget->rowCount))*(widget->itemWidth*widget->columnCount+widget->pageSpacing);
                    }
                }
            }
            else
            {
                if(widget->moveOffset<0)//向上拖动
                {
                    widget->itemNum=(-widget->moveY)/(widget->itemHeight*widget->rowCount+widget->pageSpacing)*widget->rowCount;
                    widget->itemNum+=widget->rowCount*widget->columnCount;

                    //计算能显示几个图片
                    minShowItemCount=(widget->geometry.height+widget->pageSpacing)/(widget->itemHeight*widget->rowCount+widget->pageSpacing)*(widget->rowCount*widget->columnCount);

                    if(widget->imageCount>minShowItemCount)
                    {
                        if(widget->itemNum>=(widget->imageCount-minShowItemCount))
                        {
                            widget->itemNum=widget->imageCount-minShowItemCount;
                        }
                        widget->releaseTargetY=-(widget->itemNum/(widget->columnCount*widget->rowCount))*(widget->itemHeight*widget->rowCount+widget->pageSpacing);
                    }
                    else
                    {
                        widget->releaseTargetY=0;
                        widget->itemNum=0;
                    }
                }
                else//向下拖动
                {
                    if(widget->moveY>0)
                    {
                        widget->releaseTargetY=0;
                        widget->itemNum=0;
                    }
                    else
                    {
                        widget->itemNum=(-widget->moveY)/(widget->itemHeight*widget->rowCount+widget->pageSpacing)*widget->rowCount;

                        if(widget->itemNum>=widget->imageCount)
                        {
                            widget->itemNum=widget->imageCount-1;
                        }

                        widget->releaseTargetY=-(widget->itemNum/(widget->columnCount*widget->rowCount))*(widget->itemHeight*widget->rowCount+widget->pageSpacing);
                    }
                }
            }
        }
        else
        {
            //还原
//            if(widget->isHorizontalScroll)//水平
//            {
//                widget->releaseTargetX=-widget->itemNum*(widget->itemWidth+widget->pageSpacing);
//            }
//            else
//            {
//                widget->releaseTargetY=-widget->itemNum*(widget->itemHeight+widget->pageSpacing);
//            }
            if(widget->isHorizontalScroll)//水平
            {
                widget->releaseTargetX=-(widget->columnCount*widget->itemWidth+widget->pageSpacing)*widget->currentPage;
            }
            else
            {
                widget->releaseTargetY=-(widget->rowCount*widget->itemHeight+widget->pageSpacing)*widget->currentPage;
            }
        }

        if(widget->isClickItem==true)
        {
            llTimer_start(&widget->clickTimer);
        }

//        llEmitSignal(widget,SIGNAL_CLICK_RELEASED);
//        pIconSliderRefresh(widget);
    }
    return false;
}

bool slotIconSliderMove(llConnectInfo info)
{
    llIconSlider * widget;
    int16_t nowX,nowY;

    widget=(llIconSlider*)info.receiver;

    if((widget->isEnable)&&(!widget->isHidden))
    {
        if(llClickGetPoint(&nowX,&nowY)==true)
        {
            if(widget->isClickItem==true)//判断是移动还是点击
            {
                if((abs(nowX-widget->clickPoint.x)>5)||(abs(nowY-widget->clickPoint.y)>5))
                {
                    widget->isClickItem=false;
                }
            }

            if(widget->isHorizontalScroll)//水平
            {
                widget->moveOffset=nowX-widget->clickPoint.x;
                //拉到尽头偏移减半
                if((widget->moveOffset>0)||((widget->moveOffset+widget->columnCount*widget->itemWidth)<widget->geometry.width))
                {
                    widget->moveOffset/=2;
                }
                widget->moveX=widget->moveOffset-((widget->itemNum/(widget->columnCount*widget->rowCount))*(widget->itemWidth*widget->columnCount+widget->pageSpacing));
                pIconSliderRefresh(widget);
            }
            else
            {
                widget->moveOffset=nowY-widget->clickPoint.y;
                //拉到尽头偏移减半
                if((widget->moveOffset>0)||((widget->moveOffset+widget->rowCount*widget->itemHeight)<widget->geometry.height))
                {
                    widget->moveOffset/=2;
                }
                widget->moveY=widget->moveOffset-((widget->itemNum/(widget->columnCount*widget->rowCount))*(widget->itemHeight*widget->rowCount+widget->pageSpacing));
                pIconSliderRefresh(widget);
            }
            widget->releaseTargetX=widget->moveX;
            widget->releaseTargetY=widget->moveY;
        }
    }
    return false;
}

llIconSlider *llIconSliderQuickCreate(uint16_t nameId, uint16_t parentNameId,
                                      int16_t x, int16_t y, int16_t width, int16_t height,
                                      uint8_t rowCount,uint8_t columnCount,
                                      uint16_t itemWidth,uint16_t itemHeight,
                                      uint8_t pageMax,uint8_t pageSpacing,
                                      bool isHorizontalScroll,bool isHidden)
{
    llIconSlider * pNewWidget = NULL;
    llListWidgetInfo *parentInfo;
    uint32_t *imageAddrBuf;

    //检查父链表存在
    if(llList_GetInfoByName(&parentInfo,parentNameId)==true)
    {
        pNewWidget = LL_MALLOC_WIDGET_INFO(llIconSlider);
        imageAddrBuf = llMalloc(sizeof (uint32_t)*rowCount*columnCount*pageMax);
        if((pNewWidget!=NULL)&&(imageAddrBuf!=NULL))
        {
            pNewWidget->nameId=nameId;

            pNewWidget->parentType=((llGeneral*)(parentInfo->widget))->widgetType;
            pNewWidget->parentWidget=parentInfo->widget;

            pNewWidget->widgetType=widgetTypeIconSlider;
            pNewWidget->geometry.x=x;
            pNewWidget->geometry.y=y;
            pNewWidget->geometry.width=width;
            pNewWidget->geometry.height=height;

            pNewWidget->moveX=0;
            pNewWidget->moveY=0;
            pNewWidget->releaseTargetX=0;
            pNewWidget->releaseTargetY=0;
            pNewWidget->isReleaseMove=false;
            pNewWidget->itemNum=0;

            pNewWidget->rowCount=rowCount;
            pNewWidget->columnCount=columnCount;
            pNewWidget->itemWidth=itemWidth;
            pNewWidget->itemHeight=itemHeight;

            pNewWidget->deleteFunc=nIconSliderDelete;
            pNewWidget->actionFunc=llIconSliderAction;
            pNewWidget->refreshFunc=nIconSliderRefresh;
            pNewWidget->isHidden=isHidden;
            pNewWidget->isEnable=true;
            pNewWidget->pageMax=pageMax;
            pNewWidget->imageCount=0;
            pNewWidget->isHorizontalScroll=isHorizontalScroll;
            pNewWidget->currentPage=0;
            pNewWidget->imageAddr=imageAddrBuf;
            pNewWidget->pageSpacing=pageSpacing;
            pNewWidget->isClickItem=true;
            pNewWidget->isWaitRefresh=false;
            //add linked list
            llListWidgetAdd(&(parentInfo->child_link),pNewWidget);

            //动作
            llConnectSignal(nameId,SIGNAL_CLICK_PRESSED,nameId,slotIconSliderPressed);
            llConnectSignal(nameId,SIGNAL_CLICK_HOLD_MOVE,nameId,slotIconSliderMove);
            llConnectSignal(nameId,SIGNAL_CLICK_RELEASED,nameId,slotIconSliderReleased);
        }
        else
        {
            llFree(pNewWidget);
            llFree(imageAddrBuf);
        }
    }

    return pNewWidget;
}

llIconSlider *llIconSliderCreate(uint16_t nameId, uint16_t parentNameId,
                                 int16_t x, int16_t y, int16_t width, int16_t height,
                                 uint8_t rowCount,uint8_t columnCount,
                                 uint8_t pageMax,uint8_t pageSpacing,
                                 bool isHorizontalScroll,bool isHidden)
{
    return llIconSliderQuickCreate(nameId,parentNameId,x,y,width,height,rowCount,columnCount,
                                   (uint8_t)(width/rowCount),(uint8_t)(height/columnCount),
                                   pageMax,pageSpacing,
                                   isHorizontalScroll,isHidden);
}


void llIconSliderAction(void *widget,uint8_t touchSignal)
{
    if(((llIconSlider*)widget)->isEnable)
    {
        switch(touchSignal)
        {
        case SIGNAL_CLICK_PRESSED:
        case SIGNAL_CLICK_RELEASED:
        case SIGNAL_CLICK_HOLD_MOVE:
        {
            llEmitSignal(widget,touchSignal);
            break;
        }
        default:
            break;
        }
    }
}

void pIconSliderLoop(llIconSlider *widget)
{
    int16_t calX,calY;
    uint8_t row,column;

    int16_t nowX,nowY,moveOffsetTemp;

    uint8_t groupNum;

    if(widget->isHorizontalScroll)
    {
    if(widget->releaseTargetX>widget->moveX)
    {
        widget->moveX+=LL_ICON_SLIDER_RET_OFFSET;
        if(widget->moveX>widget->releaseTargetX)
        {
            widget->moveX=widget->releaseTargetX;
        }
        widget->isWaitRefresh=true;
        widget->isReleaseMove=true;
    }
    else
    {
        if(widget->releaseTargetX<widget->moveX)
        {
            widget->moveX-=LL_ICON_SLIDER_RET_OFFSET;
            if(widget->moveX<widget->releaseTargetX)
            {
                widget->moveX=widget->releaseTargetX;
            }
            widget->isWaitRefresh=true;
            widget->isReleaseMove=true;
        }
        else
        {
            if(widget->isReleaseMove==true)
            {
                widget->isReleaseMove=false;
                moveOffsetTemp=widget->moveX;
                if(moveOffsetTemp<0)
                {
                    moveOffsetTemp=-moveOffsetTemp;
                }
                widget->currentPage=moveOffsetTemp/(widget->itemWidth*widget->columnCount+widget->pageSpacing);
            }
        }
    }
    }
    else
    {
    if(widget->releaseTargetY>widget->moveY)
    {
        widget->moveY+=LL_ICON_SLIDER_RET_OFFSET;
        if(widget->moveY>widget->releaseTargetY)
        {
            widget->moveY=widget->releaseTargetY;
        }
        widget->isWaitRefresh=true;
        widget->isReleaseMove=true;
    }
    else
    {
        if(widget->releaseTargetY<widget->moveY)
        {
            widget->moveY-=LL_ICON_SLIDER_RET_OFFSET;
            if(widget->moveY<widget->releaseTargetY)
            {
                widget->moveY=widget->releaseTargetY;
            }
            widget->isWaitRefresh=true;
            widget->isReleaseMove=true;
        }
        else
        {
            if(widget->isReleaseMove==true)
            {
                widget->isReleaseMove=false;

                moveOffsetTemp=widget->moveY;
                if(moveOffsetTemp<0)
                {
                    moveOffsetTemp=-moveOffsetTemp;
                }
                widget->currentPage=moveOffsetTemp/(widget->itemHeight*widget->rowCount+widget->pageSpacing);
             }
        }
    }
    }
    if(widget->isWaitRefresh)
    {
        widget->isWaitRefresh=false;
        pIconSliderRefresh((llIconSlider*)widget);
    }
    if(llTimer_timeOut(&widget->clickTimer,200,false))
    {
        if(llClickGetPoint(&nowX,&nowY)==false)
        {
            //计算点击item序号
            calX=widget->clickPoint.x-widget->geometry.x;
            calY=widget->clickPoint.y-widget->geometry.y;
            if(widget->isHorizontalScroll)//水平
            {
                groupNum=(-widget->moveX+calX)/(widget->itemWidth*widget->columnCount+widget->pageSpacing);
                column=calX%(widget->itemWidth*widget->columnCount+widget->pageSpacing)/widget->itemWidth;
                row=calY/widget->itemHeight;
            }
            else
            {
                groupNum=(-widget->moveY+calY)/(widget->itemHeight*widget->rowCount+widget->pageSpacing);
                row=calY%(widget->itemHeight*widget->rowCount+widget->pageSpacing)/widget->itemHeight;
                column=calX/widget->itemWidth;
            }
            if((column>=widget->columnCount)||(row>=widget->rowCount))//空白处
            {
                return;
            }
            widget->clickItemNum=groupNum*widget->columnCount*widget->rowCount;
            widget->clickItemNum+=row*widget->columnCount+column;

            llEmitSignal(widget,SIGNAL_WIDGET_ACTIVE);
        }
    }
}

void nIconSliderLoop(uint16_t nameId)
{
    void *widget;
    widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        pIconSliderLoop((llIconSlider*)widget);
    }
}

void pIconSliderFree(llIconSlider *widget)
{
    llFree(widget->imageAddr);
    llFree(widget);
}

void nIconSliderDelete(uint16_t nameId)
{
    llListHead *tempPos,*safePos;
    llListWidgetInfo *linkInfo;
    llListWidgetInfo *parentInfo;
    llListWidgetInfo *tempInfo;
    llIconSlider *widget;

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
                pIconSliderFree(widget);
                llFree(tempInfo);
            }
        }
    }
}

void pIconSliderRefresh(llIconSlider *widget)
{
    llPoint globalPos;
    int16_t x,y;
    uint8_t page;
    uint8_t i;
    llGeometry imgGeometry,showGeometry;
    llSize imgSize;

    if((widget->isEnable)&&(!widget->isHidden))
    {
        globalPos=llListGetGlobalPos((llGeneral*)widget);

        //空余区域填充
        if((widget->moveX>0)||(widget->moveY>0))//左侧，上方
        {
            imgGeometry.x=globalPos.x;
            imgGeometry.y=globalPos.y;
            if(widget->moveX>0)
            {
                imgGeometry.width=widget->moveX;
                imgGeometry.height=widget->geometry.height;

                if( llRectIntersect(widget->geometry, imgGeometry,&showGeometry))
                {
                    llGeneralWidgetParentRecover((llGeneral*)widget,showGeometry);
                }
            }
            else
            {
                imgGeometry.width=widget->geometry.width;
                imgGeometry.height=widget->moveY;
                if( llRectIntersect(widget->geometry, imgGeometry,&showGeometry))
                {
                    llGeneralWidgetParentRecover((llGeneral*)widget,showGeometry);
                }
            }
        }

        else//右侧，下方
        {
            if(widget->isHorizontalScroll)//水平
            {
                imgGeometry.x=globalPos.x+widget->moveX+widget->itemWidth*widget->columnCount*widget->pageMax+widget->pageSpacing*(widget->pageMax-1);
                if(imgGeometry.x<(widget->geometry.x+widget->geometry.width))
                {
                    imgGeometry.y=globalPos.y;
                    imgGeometry.width=widget->geometry.x+widget->geometry.width-imgGeometry.x;
                    imgGeometry.height=widget->geometry.height;
                    if( llRectIntersect(widget->geometry, imgGeometry,&showGeometry))
                    {
                        llGeneralWidgetParentRecover((llGeneral*)widget,showGeometry);
                    }
                }
            }
            else
            {
                imgGeometry.y=globalPos.y+widget->moveY+widget->itemHeight*widget->rowCount*widget->pageMax+widget->pageSpacing*(widget->pageMax-1);
                if(imgGeometry.y<(widget->geometry.y+widget->geometry.height))
                {
                    imgGeometry.x=globalPos.x;
                    imgGeometry.width=widget->geometry.width;
                    imgGeometry.height=widget->geometry.y+widget->geometry.height-imgGeometry.y;
                    if( llRectIntersect(widget->geometry, imgGeometry,&showGeometry))
                    {
                        llGeneralWidgetParentRecover((llGeneral*)widget,showGeometry);
                    }
                }
            }
        }

        //填充中间空余区域
        for(i=0; i<(widget->pageMax-1); i++)
        {
            if(widget->isHorizontalScroll)//水平
            {
                imgGeometry.x=globalPos.x+widget->moveX+widget->itemWidth*widget->columnCount+(i*(widget->itemWidth*widget->columnCount+widget->pageSpacing));
                imgGeometry.y=globalPos.y;
                imgGeometry.width=widget->pageSpacing;
                imgGeometry.height=widget->geometry.height;

                if( llRectIntersect(widget->geometry, imgGeometry,&showGeometry))
                {
                    llGeneralWidgetParentRecover((llGeneral*)widget,showGeometry);
                }
            }
            else
            {
                imgGeometry.x=globalPos.x;
                imgGeometry.y=globalPos.y+widget->moveY+widget->itemHeight*widget->rowCount+(i*(widget->itemHeight*widget->rowCount+widget->pageSpacing));
                imgGeometry.width=widget->geometry.width;
                imgGeometry.height=widget->pageSpacing;

                if( llRectIntersect(widget->geometry, imgGeometry,&showGeometry))
                {
                    llGeneralWidgetParentRecover((llGeneral*)widget,showGeometry);
                }
            }
        }

        for(i=0; i<(widget->rowCount*widget->columnCount*widget->pageMax); i++)
        {
            //计算坐标
            //页
            page=i/(widget->rowCount*widget->columnCount);

            //窗口内坐标
            x=(i%widget->columnCount)*widget->itemWidth;
            y=(i/widget->columnCount)*widget->itemHeight;

            //换页坐标
            if(widget->isHorizontalScroll)
            {
                x+=page*(widget->itemWidth*widget->columnCount+widget->pageSpacing);
                y-=page*widget->itemHeight*widget->rowCount;
            }
            else
            {
                y+=page*widget->pageSpacing;
            }

            //全局坐标
            x+=globalPos.x+widget->moveX;
            y+=globalPos.y+widget->moveY;

            if(i<widget->imageCount)
            {
                imgGeometry.x=x;
                imgGeometry.y=y;

                imgSize=llGeneralGetImageSize(widget->imageAddr[i]);
                imgGeometry.width=imgSize.width;
                imgGeometry.height=imgSize.height;

                if( llRectIntersect(widget->geometry, imgGeometry,&showGeometry))
                {
                    llGeneralImageSpecificAreaShow((llGeneral*)widget,imgGeometry, showGeometry,widget->imageAddr[i]);
                }
            }
            else
            {
                imgGeometry.x=x;
                imgGeometry.y=y;
                imgGeometry.width=widget->itemWidth;
                imgGeometry.height=widget->itemHeight;
                if( llRectIntersect(widget->geometry, imgGeometry,&showGeometry))
                {
                    llGeneralWidgetParentRecover((llGeneral*)widget,showGeometry);
                }
            }
        }

    }
}

void nIconSliderRefresh(uint16_t nameId)
{
    void *widget;
    widget=llGeneralGetWidget(nameId);

    if(widget!=NULL)
    {
        pIconSliderRefresh((llIconSlider*)widget);
    }
}

void pIconSliderAddImage(llIconSlider *widget,uint32_t imageAddr)
{
    if(widget->imageCount<(widget->rowCount*widget->columnCount*widget->pageMax))
    {
        widget->imageAddr[widget->imageCount++]=imageAddr;
    }
}

void nIconSliderAddImage(uint16_t nameId,uint32_t imageAddr)
{
    void *widget;
    widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        pIconSliderAddImage((llIconSlider*)widget,imageAddr);
        ((llIconSlider*)widget)->isWaitRefresh=true;
    }
}

uint16_t pIconSliderGetClickItemNum(llIconSlider *widget)
{
    return widget->clickItemNum;
}

uint16_t nIconSliderGetClickItemNum(uint16_t nameId)
{
    void *widget;
    widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        return pIconSliderGetClickItemNum((llIconSlider*)widget);
    }
    return 0;
}

uint8_t pIconSliderGetCurrentPage(llIconSlider *widget)
{
    return widget->currentPage;
}

uint8_t nIconSliderGetCurrentPage(uint16_t nameId)
{
    void *widget;
    widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        return pIconSliderGetCurrentPage((llIconSlider*)widget);
    }
    return 0;
}

void pIconSliderSetCurrentPage(llIconSlider *widget,uint8_t pageNum)
{
    if(pageNum>=widget->pageMax)
    {
        return;
    }
    if(widget->isHorizontalScroll)//水平
    {
        widget->releaseTargetX+=(widget->columnCount*widget->itemWidth+widget->pageSpacing)*(widget->currentPage-pageNum);
        widget->itemNum=pageNum*widget->columnCount;
    }
    else
    {
        widget->releaseTargetY+=(widget->rowCount*widget->itemHeight+widget->pageSpacing)*(widget->currentPage-pageNum);
        widget->itemNum=pageNum*widget->rowCount;
    }
    widget->currentPage=pageNum;
    
}

void nIconSliderSetCurrentPage(uint16_t nameId,uint8_t pageNum)
{
    void *widget;
    widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        pIconSliderSetCurrentPage((llIconSlider*)widget,pageNum);
    }
}

