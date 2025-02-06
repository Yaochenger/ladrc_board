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

#include "LL_General.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
#include "LL_Linked_List.h"
#include "LL_Window.h"
#include "LL_Background.h"
#include "LL_Button.h"
#include "LL_Text.h"
#include "LL_LineEdit.h"

uint8_t llGetUtf8Len(uint8_t *utf8)
{
    uint8_t nBytes = 0;

    if ((*utf8 & 0x80) == 0)
    {
        nBytes = 1;
    }
    else
    {
        if((*utf8 & 0x20) == 0)
        {
            nBytes = 2;
        }
        else
        {
            if((*utf8 & 0x10) == 0)
            {
                nBytes  = 3;
            }
            else
            {
                nBytes = 0;
            }
        }
    }
    return nBytes;
}

uint8_t llUtf8ToUnicode(uint8_t* unicode, uint8_t *utf8)
{
    uint8_t nBytes = 0;

    if ((*utf8 & 0x80) == 0)
    {
        nBytes = 1;
        unicode[0] = *utf8;
    }
    else
    {
        if((*utf8 & 0x20) == 0)
        {
            nBytes = 2;
            unicode[0] = (utf8[0] & 0x1f)>> 2;
            unicode[1] = (utf8[0] & 0x3)<<6 |  (utf8[1] & 0x3F);
        }
        else
        {
            if((*utf8 & 0x10) == 0)
            {
                nBytes  = 3;
                unicode[0] = ((utf8[0] & 0x0f) <<4) + ((utf8[1] & 0x3c) >>2);
                unicode[1] = ((utf8[1] & 0x03) <<6) + (utf8[2] & 0x3f);
            }
            else
            {
//            debug("ERROR: utf-8 to unicode\n");
                nBytes = 0;
                unicode[0] = '?';
            }
        }
    }
    return nBytes;
}

/*******************************************************************************
 * @name     :llStringCompare
 * @brief    :比较两个字符串是否相同
 * @param    :str1 str2
 * @return   :bool
 * @version  :V0.1
 * @author   :
 * @date     :2018.5.10
 * @details  :比较字符串和长度是否都相同
*******************************************************************************/
bool llStringCompare(uint8_t* str1,uint8_t* str2)
{
    uint32_t len1,len2;

    len1=strlen((char*)str1);
    len2=strlen((char*)str2);

    if(len1==len2)
    {
        if(memcmp(str1,str2,len1)==0)
        {
            return true;
        }
    }
    return false;
}

uint8_t* llStrcat(uint8_t* str1,uint8_t* str2)
{
    uint8_t *outString;
    outString=(uint8_t *)llMalloc(strlen((const char*)str1)+strlen((const char*)str2));
    if(outString)
    {
        strcpy((char*)outString,(const char*)str1);
        strcat((char*)outString,(const char*)str2);
    }

    return outString;
}

/**
 * @brief 判断两个矩形是否重叠
 * @param rc1 第一个矩阵的位置
 * @param rc2 第二个矩阵的位置
 * @return 两个矩阵是否重叠（边沿重叠，也认为是重叠）
 */
bool llRectIsOverlap(llGeometry rc1, llGeometry rc2)
{
    if((rc1.x + rc1.width-1)>=rc2.x &&
            (rc2.x + rc2.width-1)>=rc1.x &&
            (rc1.y + rc1.height-1)>=rc2.y &&
            (rc2.y + rc2.height-1)>=rc1.y )
    {
        return true;
    }
    return false;
}

/**
 * @brief 判断一个矩形是否在另一个矩形内
 * @param bigRect 大矩阵的位置
 * @param smallRect 小矩阵的位置
 * @return 小矩阵是否在大矩形内（包括边沿重叠）
 */
bool llRectIsFullIn(llGeometry bigRect, llGeometry smallRect)
{
    if((smallRect.x>=bigRect.x) &&
            (smallRect.y>=bigRect.y) &&
            ((smallRect.x+smallRect.width-1)<=(bigRect.x+bigRect.width-1)) &&
            ((smallRect.y+smallRect.height-1)<=(bigRect.y+bigRect.height-1)) )
    {
        return true;
    }
    return false;
}

bool llPointInRect(llPoint point, llGeometry rc)
{
    if((point.x>=rc.x)&&(point.x<=(rc.x+rc.width-1))&&(point.y>=rc.y)&&(point.y<=(rc.y+rc.height-1)))
    {
        return true;
    }
    return false;
}

/***************************************************************************//**
 * @fn         bool llRectIntersect(const llGeometry rect1, const llGeometry rect2,llGeometry * outRect)
 * @brief      两个矩形的相交区域
 * @param      rect1    矩形1
 *             rect2    矩形2
 *             outRect  返回矩形
 * @return     bool     是否有相交
 * @version    V0.1
 * @date       2020-11-04
 * @details
 ******************************************************************************/
bool llRectIntersect(const llGeometry rect1, const llGeometry rect2,llGeometry * outRect)
{
    int16_t outX2,outY2;

    /* Get the smaller area from 'a1_p' and 'a2_p' */
    outRect->x = MAX(rect1.x, rect2.x);
    outRect->y = MAX(rect1.y, rect2.y);
    outX2 = MIN(rect1.x+rect1.width-1, rect2.x+rect2.width-1);
    outY2 = MIN(rect1.y+rect1.height-1, rect2.y+rect2.height-1);

    /*If x1 or y1 greater then x2 or y2 then the areas union is empty*/
    bool union_ok = true;
    if((outRect->x > outX2) || (outRect->y > outY2))
    {
        union_ok = false;
    }

    outRect->width=MAX(outX2,outRect->x)-MIN(outX2,outRect->x)+1;
    outRect->height=MAX(outY2,outRect->y)-MIN(outY2,outRect->y)+1;

    return union_ok;
}

void llFillLineMultipleTransparent5515Colors(int16_t x0,int16_t x1,int16_t y,llColor *color)
{
    int16_t startX,endX;
    int16_t i;
    llColor *pos;
    bool isWait=true;

    for(i=x0; i<=x1; i++)
    {
        if(isWait)
        {
            if((((*color>>5)&1)!=0)&&(*color!=0x20))
            {
                startX=i;
                pos=color;
                isWait=false;
            }
        }
        else
        {
            if(((*color>>5)&1)==0)
            {
                endX=i-1;
                isWait=true;
                llFillMultipleColors(startX,y,endX,y,pos);
            }
        }
        color++;
    }
    if(isWait==false)
    {
        llFillMultipleColors(startX,y,x1,y,pos);
    }
}

void llFillMultipleTransparent5515Colors(int16_t x0,int16_t y0,int16_t x1,int16_t y1,llColor *color)
{
    int16_t y;

    for(y = y0; y <= y1; y++)
    {
        llFillLineMultipleTransparent5515Colors(x0,x1,y,color);
        color=color+(x1-x0)+1;
    }
}

uint8_t convertTypeBit[6]= {16,16,32,32,32,16};//数据占用多少位

llSize llGeneralGetImageSize(uint32_t imageAddr)
{
    llSize retSize= {0};
    imageHeaderTypedef imageHeader;
    if(imageAddr!=IMAGE_NONE)
    {
        llReadExFlash(imageAddr,(uint8_t*)&imageHeader,16);
        retSize.width=imageHeader.width;
        retSize.height=imageHeader.height;
    }
    return retSize;
}

llGeometry llGeneralGetImageGeometry(int16_t x,int16_t y,uint32_t imageAddr)
{
    llGeometry retGeometry= {0};
    imageHeaderTypedef imageHeader;
    if(imageAddr!=IMAGE_NONE)
    {
        llReadExFlash(imageAddr,(uint8_t*)&imageHeader,16);
        retGeometry.x=x;
        retGeometry.y=y;
        retGeometry.width=imageHeader.width;
        retGeometry.height=imageHeader.height;
    }
    return retGeometry;
}

uint32_t llGeneralGetParentOverlapColor(uint32_t parentAddr,llGeometry parentGepmetry,llPoint childPos,uint8_t parentConvertTypeBit)
{
    int16_t x;
    int16_t y;
    uint32_t retAddr;
    x=childPos.x-parentGepmetry.x;
    y=childPos.y-parentGepmetry.y;

    retAddr=parentAddr+(parentGepmetry.width*y+x)*(parentConvertTypeBit/8);//偏移*颜色字节数
    return retAddr;
}

LL_WEAK llGeometry llGeneralImageShow(llGeneral *widget,uint32_t imageAddr,int16_t x,int16_t y)
{
    uint32_t addr=0,bgAddr=0,tempAddr=0;
    llGeometry geometry= {0,0,0,0},bgGeometry= {0,0,0,0};
    llPoint tempPoint;
    uint16_t writePixelCount=0;//读取一次能写多少个像素
    uint16_t writeHeightCount=0; //一次最多能读多少行， 如果不够一行的话就是 0
    uint16_t currHeight = 0; // 当可以写多于一行， 这个是用于存储当前实际能写多少行
    uint16_t currLineX = 0 ;//下一个要写的点的x坐标， 当每次能读的像素少于 一行的宽 才会用到。
    uint16_t currPixelCount = 0; //当只能写少于一行， 这用于储存这一行实际写多少个像素

    imageHeaderTypedef imageHeader,bgImageHeader;

    imageBufferTypedef *unionReadBuf,*bgUnionReadBuf;

    uint32_t i,j,totalCount;

    uint8_t parentBackgroundType=PARENT_BACKGROUND_TYPE_ERROR;
    llColor bgColor;
    uint32_t bgImageAddr=0;
    llPoint bgImagePoint= {0};
    uint8_t alpha;

    unionReadBuf=llMalloc(sizeof(imageBufferTypedef));
    bgUnionReadBuf=llMalloc(sizeof(imageBufferTypedef));
    if((unionReadBuf==NULL)||(bgUnionReadBuf==NULL))
    {
        return geometry;
    }
    
    
    if(imageAddr!=IMAGE_NONE)
    {
        addr=imageAddr;
        llReadExFlash(addr,(uint8_t*)&imageHeader,16);
        addr=addr+16;

        geometry.x=x;
        geometry.y=y;
        geometry.width=imageHeader.width;
        geometry.height=imageHeader.height;

        totalCount=imageHeader.width*imageHeader.height;
        writePixelCount = IMAGE_READ_BYTE_MAX /( convertTypeBit[imageHeader.convertType] / 8);

        if(geometry.width>0)//0不能做除数
        {
            writeHeightCount = writePixelCount / geometry.width;
        }
        else
        {
            llFree(unionReadBuf);
            llFree(bgUnionReadBuf);
            return bgGeometry;
        }

        parentBackgroundType = llGeneralGetParentBackgroundInfo(widget,&bgColor,&bgImageAddr,&bgImagePoint);

        if(parentBackgroundType==PARENT_BACKGROUND_TYPE_IMAGE)
        {
            bgAddr=bgImageAddr;
            llReadExFlash(bgAddr,(uint8_t*)&bgImageHeader,16);
            bgAddr=bgAddr+16;
            bgGeometry.x=bgImagePoint.x;
            bgGeometry.y=bgImagePoint.y;
            bgGeometry.width=bgImageHeader.width;
            bgGeometry.height=bgImageHeader.height;
        }

        i=0;
        tempPoint.x=x;
        tempPoint.y=y;

        while(i < totalCount)
        {
            switch (imageHeader.convertType)
            {
            case CONVERT_TYPE_565:
            {
                if(writeHeightCount > 0)
                {
                    currHeight = MIN(writeHeightCount, geometry.height - i/ geometry.width );
                    llReadExFlash(addr,unionReadBuf->u8ReadBuf,2 *geometry.width*currHeight);
                    addr=addr+(2 *geometry.width*currHeight);

                    llFillMultipleColors(x, y + i/geometry.width, x+geometry.width -1,  y + i/geometry.width + currHeight -1,unionReadBuf->u16ReadBuf);

                    i += currHeight * geometry.width;
                }
                else
                {
                    currLineX = i % geometry.width;
                    currPixelCount = MIN(writePixelCount, geometry.width - currLineX);
                    llReadExFlash(addr,unionReadBuf->u8ReadBuf,2 *currPixelCount);
                    addr=addr+(2 *currPixelCount);

                    if((i %geometry.width==0)&&(tempPoint.x!=geometry.x))//换行
                {
                    tempPoint.y++;
                }
                
                tempPoint.x = x+currLineX;
                
                    llFillMultipleColors(tempPoint.x, tempPoint.y, tempPoint.x+currPixelCount -1,  tempPoint.y,unionReadBuf->u16ReadBuf);

                    i += currPixelCount;
                }
            }
            break;
            case CONVERT_TYPE_888:
            case CONVERT_TYPE_8888:
            {

            }
            break;
            case CONVERT_TYPE_8565:
            {
                if(writeHeightCount > 0)
                {
                    currHeight = MIN(writeHeightCount, geometry.height - i/ geometry.width );
                    llReadExFlash(addr,unionReadBuf->u8ReadBuf,4 *geometry.width*currHeight);
                    addr=addr+(4 *geometry.width*currHeight);

                    if(parentBackgroundType==PARENT_BACKGROUND_TYPE_IMAGE)
                    {

                        for(j=0; j<currHeight; j++)
                        {
                            tempAddr=llGeneralGetParentOverlapColor(bgAddr,bgGeometry,tempPoint,convertTypeBit[CONVERT_TYPE_565]);
                            llReadExFlash(tempAddr,&bgUnionReadBuf->u8ReadBuf[j*2*geometry.width],2 *geometry.width);
                            tempPoint.y++;
                        }
                        for(j=0; j<(geometry.width*currHeight); j++)
                        {
                            alpha=unionReadBuf->u32ReadBuf[j]>>16;

                            if(alpha==0)
                            {
                                unionReadBuf->u16ReadBuf[j]=bgUnionReadBuf->u16ReadBuf[j];
                            }
                            else
                            {
                                if(alpha==0xFF)
                                {
                                    unionReadBuf->u16ReadBuf[j]=unionReadBuf->u32ReadBuf[j]&0xFFFF;
                                }
                                else
                                {
                                    unionReadBuf->u16ReadBuf[j]=llGeometryColorMix(bgUnionReadBuf->u16ReadBuf[j],unionReadBuf->u32ReadBuf[j]&0xFFFF,alpha);
                                }
                            }
                        }
                        llFillMultipleColors(x, y + i/geometry.width, x+geometry.width -1,  y + i/geometry.width + currHeight -1,unionReadBuf->u16ReadBuf);
                    }
                    else
                    {
                        for(j=0; j<(geometry.width*currHeight); j++)
                        {
                            alpha=unionReadBuf->u32ReadBuf[j]>>16;
                            if(alpha==0)
                            {
                                unionReadBuf->u16ReadBuf[j]=bgColor;
                            }
                            else
                            {
                                if(alpha==0xFF)
                                {
                                    unionReadBuf->u16ReadBuf[j]=unionReadBuf->u32ReadBuf[j]&0xFFFF;
                                }
                                else
                                {
                                    unionReadBuf->u16ReadBuf[j]=llGeometryColorMix(bgColor,unionReadBuf->u32ReadBuf[j]&0xFFFF,alpha);
                                }
                            }
                        }
                        llFillMultipleColors(x, y + i/geometry.width, x+geometry.width -1,  y + i/geometry.width + currHeight -1,unionReadBuf->u16ReadBuf);
                    }


                    i += currHeight * geometry.width;
                }
                else
                {

                    currLineX = i % geometry.width;
                    currPixelCount = MIN(writePixelCount, geometry.width - currLineX);
                    llReadExFlash(addr,unionReadBuf->u8ReadBuf,4 *currPixelCount);
                    addr=addr+(4 *currPixelCount);

                    if((i %geometry.width==0)&&(tempPoint.x!=geometry.x))//换行
                {
                    tempPoint.y++;
                }
                
                tempPoint.x = x+currLineX;
                
                    if(parentBackgroundType==PARENT_BACKGROUND_TYPE_IMAGE)
                    {

                        tempAddr=llGeneralGetParentOverlapColor(bgAddr,bgGeometry,tempPoint,convertTypeBit[CONVERT_TYPE_565]);
                        llReadExFlash(tempAddr,bgUnionReadBuf->u8ReadBuf,2 *currPixelCount);

                        for(j=0; j<(currPixelCount); j++)
                        {
                            alpha=unionReadBuf->u32ReadBuf[j]>>16;

                            if(alpha==0)
                            {
                                unionReadBuf->u16ReadBuf[j]=bgUnionReadBuf->u16ReadBuf[j];
                            }
                            else
                            {
                                if(alpha==0xFF)
                                {
                                    unionReadBuf->u16ReadBuf[j]=unionReadBuf->u32ReadBuf[j]&0xFFFF;
                                }
                                else
                                {
                                    unionReadBuf->u16ReadBuf[j]=llGeometryColorMix(bgUnionReadBuf->u16ReadBuf[j],unionReadBuf->u32ReadBuf[j]&0xFFFF,alpha);
                                }
                            }
                        }
                        llFillMultipleColors(tempPoint.x, tempPoint.y, tempPoint.x+currPixelCount -1,  tempPoint.y,unionReadBuf->u16ReadBuf);
                    }
                    else
                    {
                        for(j=0; j<(currPixelCount); j++)
                        {
                            alpha=unionReadBuf->u32ReadBuf[j]>>16;

                            if(alpha==0)
                            {
                                unionReadBuf->u16ReadBuf[j]=bgColor;
                            }
                            else
                            {
                                if(alpha==0xFF)
                                {
                                    unionReadBuf->u16ReadBuf[j]=unionReadBuf->u32ReadBuf[j]&0xFFFF;
                                }
                                else
                                {
                                    unionReadBuf->u16ReadBuf[j]=llGeometryColorMix(bgColor,unionReadBuf->u32ReadBuf[j]&0xFFFF,alpha);
                                }
                            }
                        }
                        llFillMultipleColors(tempPoint.x, tempPoint.y, tempPoint.x+currPixelCount -1,  tempPoint.y,unionReadBuf->u16ReadBuf);
                    }
                    i += currPixelCount;
                }
                break;
            }

            default:
                break;
            }
        }
    }
    
    llFree(unionReadBuf);
    llFree(bgUnionReadBuf);
    
    return geometry;
}


//全屏绝对坐标计算
//originGeometry原图所在坐标
//targetGeometry截图显示坐标
uint32_t llGeneralImageSpecificAreaProcess(llGeneral *widget,llGeometry originGeometry,llGeometry targetGeometry,uint32_t imageAddr,imageBufferTypedef *unionReadBuf,imageBufferTypedef *bgUnionReadBuf,bool isShow,uint32_t *yCount)
{
    uint32_t addr=0,bgAddr=0,tempAddr=0;
    llPoint tempPoint,tempPoint2;
    uint16_t writePixelCount=0;//读取一次能写多少个像素
    uint16_t writeHeightCount=0; //一次最多能读多少行， 如果不够一行的话就是 0
    uint16_t currHeight = 0; // 当可以写多于一行， 这个是用于存储当前实际能写多少行
    uint16_t currLineX = 0 ;//下一个要写的点的x坐标， 当每次能读的像素少于 一行的宽 才会用到。
    uint16_t currPixelCount = 0; //当只能写少于一行， 这用于储存这一行实际写多少个像素

    imageHeaderTypedef imageHeader,bgImageHeader;

    llGeometry bgGeometry= {0,0,0,0};
    
    uint32_t i,j,totalCount;
    
uint8_t parentBackgroundType=PARENT_BACKGROUND_TYPE_ERROR;
    llColor bgColor;
    uint32_t bgImageAddr=0;
    llPoint bgImagePoint= {0};
    uint8_t alpha;
    
    addr=imageAddr;
    llReadExFlash(addr,(uint8_t*)&imageHeader,16);
    addr=addr+16;
    
    originGeometry.width=imageHeader.width;
    originGeometry.height=imageHeader.height;
    
    if((imageHeader.convertType==CONVERT_TYPE_8565)||(imageHeader.convertType==CONVERT_TYPE_8888))
    {
parentBackgroundType = llGeneralGetParentBackgroundInfo(widget,&bgColor,&bgImageAddr,&bgImagePoint);

        if(parentBackgroundType==PARENT_BACKGROUND_TYPE_IMAGE)
        {
            bgAddr=bgImageAddr;
            llReadExFlash(bgAddr,(uint8_t*)&bgImageHeader,16);
            bgAddr=bgAddr+16;
            bgGeometry.x=bgImagePoint.x;
            bgGeometry.y=bgImagePoint.y;
            bgGeometry.width=bgImageHeader.width;
            bgGeometry.height=bgImageHeader.height;
        }
    }


    totalCount =targetGeometry.width * targetGeometry.height;
    writePixelCount = IMAGE_READ_BYTE_MAX /( convertTypeBit[imageHeader.convertType] / 8);

    if(targetGeometry.width>0)//0不能做除数
    {
        writeHeightCount = writePixelCount / targetGeometry.width;
    }
    else
    {
        return 0;
    }

    tempPoint.x=targetGeometry.x;
    tempPoint.y=targetGeometry.y;

    tempPoint2.x=tempPoint.x;
    tempPoint2.y=tempPoint.y;
    i=0;
    while(i < totalCount)
    {
        switch (imageHeader.convertType)
        {
        case CONVERT_TYPE_565:
        {
            if(writeHeightCount>0)
            {
                currHeight = MIN(writeHeightCount, targetGeometry.height - i/ targetGeometry.width );
                if(!isShow)
                {
                    //第一次运行
                    if(*yCount<tempPoint.y)
                    {
                        *yCount=tempPoint.y;
                    }
                    tempPoint.y=*yCount;
                }

                for(j=0; j<currHeight; j++)
                {
                    tempAddr=llGeneralGetParentOverlapColor(addr,originGeometry,tempPoint,convertTypeBit[CONVERT_TYPE_565]);
                    llReadExFlash(tempAddr,&unionReadBuf->u8ReadBuf[j*2*targetGeometry.width],2 *targetGeometry.width);
                    tempPoint.y++;
                }
                if(isShow)
                {
                    llFillMultipleColors(targetGeometry.x, targetGeometry.y + i/targetGeometry.width, targetGeometry.x+targetGeometry.width -1,  targetGeometry.y + i/targetGeometry.width + currHeight -1,unionReadBuf->u16ReadBuf);
                }
                else
                {
                    *yCount=tempPoint.y;
                }
                i += currHeight * targetGeometry.width;
            }
            else
            {
                currLineX = i % targetGeometry.width;
                currPixelCount = MIN(writePixelCount, targetGeometry.width - currLineX);

                if(!isShow)
                {
                    //第一次运行
                    if(*yCount<tempPoint.y)
                    {
                        *yCount=tempPoint.y;
                    }
                    tempPoint.y=*yCount;
                }

                if((i %targetGeometry.width==0)&&(tempPoint.x!=targetGeometry.x))//换行
                {
                    tempPoint.y++;
                }
                
                tempPoint.x = (targetGeometry.x+currLineX);

                tempAddr=llGeneralGetParentOverlapColor(addr,originGeometry,tempPoint,convertTypeBit[CONVERT_TYPE_565]);
                llReadExFlash(tempAddr,unionReadBuf->u8ReadBuf,2 *currPixelCount);
                if(isShow)
                {
                    llFillMultipleColors(tempPoint.x, tempPoint.y, tempPoint.x+currPixelCount -1,  tempPoint.y,unionReadBuf->u16ReadBuf);
                }
                else
                {
                    *yCount=tempPoint.y;
                }
                i += currPixelCount;
            }

            break;
        }

        case CONVERT_TYPE_888:
        case CONVERT_TYPE_8888:
        {

            break;
        }
        case CONVERT_TYPE_8565:
        {
            if(writeHeightCount > 0)
                {
                    currHeight = MIN(writeHeightCount, targetGeometry.height - i/ targetGeometry.width );
                    if(!isShow)
                {
                    //第一次运行
                    if(*yCount<tempPoint.y)
                    {
                        *yCount=tempPoint.y;
                    }
                    tempPoint.y=*yCount;
                }
                    for(j=0; j<currHeight; j++)
                    {
                        tempAddr=llGeneralGetParentOverlapColor(addr,originGeometry,tempPoint,convertTypeBit[CONVERT_TYPE_8565]);
                        llReadExFlash(tempAddr,&unionReadBuf->u8ReadBuf[j*4*targetGeometry.width],4 *targetGeometry.width);
                        tempPoint.y++;
                    }

                    if(parentBackgroundType==PARENT_BACKGROUND_TYPE_IMAGE)
                    {

                        for(j=0; j<currHeight; j++)
                        {
                            tempAddr=llGeneralGetParentOverlapColor(bgAddr,bgGeometry,tempPoint2,convertTypeBit[CONVERT_TYPE_565]);
                            llReadExFlash(tempAddr,&bgUnionReadBuf->u8ReadBuf[j*2*targetGeometry.width],2 *targetGeometry.width);
                            tempPoint2.y++;
                        }
                        for(j=0; j<(targetGeometry.width*currHeight); j++)
                        {
                            alpha=unionReadBuf->u32ReadBuf[j]>>16;

                            if(alpha==0)
                            {
                                unionReadBuf->u16ReadBuf[j]=bgUnionReadBuf->u16ReadBuf[j];
                            }
                            else
                            {
                                if(alpha==0xFF)
                                {
                                    unionReadBuf->u16ReadBuf[j]=unionReadBuf->u32ReadBuf[j]&0xFFFF;
                                }
                                else
                                {
                                    unionReadBuf->u16ReadBuf[j]=llGeometryColorMix(bgUnionReadBuf->u16ReadBuf[j],unionReadBuf->u32ReadBuf[j]&0xFFFF,alpha);
                                }
                            }
                        }
                        if(isShow)
                {
                        llFillMultipleColors(targetGeometry.x, targetGeometry.y + i/targetGeometry.width, targetGeometry.x+targetGeometry.width -1,  targetGeometry.y + i/targetGeometry.width + currHeight -1,unionReadBuf->u16ReadBuf);
                }
else
                {
                    *yCount=tempPoint.y;
                }                
                }
                    else
                    {
                        for(j=0; j<(targetGeometry.width*currHeight); j++)
                        {
                            alpha=unionReadBuf->u32ReadBuf[j]>>16;
                            if(alpha==0)
                            {
                                unionReadBuf->u16ReadBuf[j]=bgColor;
                            }
                            else
                            {
                                if(alpha==0xFF)
                                {
                                    unionReadBuf->u16ReadBuf[j]=unionReadBuf->u32ReadBuf[j]&0xFFFF;
                                }
                                else
                                {
                                    unionReadBuf->u16ReadBuf[j]=llGeometryColorMix(bgColor,unionReadBuf->u32ReadBuf[j]&0xFFFF,alpha);
                                }
                            }
                        }
                        if(isShow)
                {
                        llFillMultipleColors(targetGeometry.x, targetGeometry.y + i/targetGeometry.width, targetGeometry.x+targetGeometry.width -1,  targetGeometry.y + i/targetGeometry.width + currHeight -1,unionReadBuf->u16ReadBuf);
                   
                }
                else
                {
                    *yCount=tempPoint.y;
                }
                    }


                    i += currHeight * targetGeometry.width;
                }
                else
                {
                    tempPoint.y=originGeometry.y+(i/targetGeometry.width);
                    currLineX = i % targetGeometry.width;
                    currPixelCount = MIN(writePixelCount, targetGeometry.width - currLineX);
                    tempPoint.x = targetGeometry.x+currLineX;
                    tempAddr=llGeneralGetParentOverlapColor(addr,originGeometry,tempPoint,convertTypeBit[CONVERT_TYPE_8565]);
                    llReadExFlash(tempAddr,(uint8_t*)&unionReadBuf->u8ReadBuf,4 *currPixelCount);

                    if(parentBackgroundType==PARENT_BACKGROUND_TYPE_IMAGE)
                    {

                        tempAddr=llGeneralGetParentOverlapColor(bgAddr,bgGeometry,tempPoint,convertTypeBit[CONVERT_TYPE_565]);
                        llReadExFlash(tempAddr,bgUnionReadBuf->u8ReadBuf,2 *currPixelCount);

                        for(j=0; j<(currPixelCount); j++)
                        {
                            alpha=unionReadBuf->u32ReadBuf[j]>>16;

                            if(alpha==0)
                            {
                                unionReadBuf->u16ReadBuf[j]=bgUnionReadBuf->u16ReadBuf[j];
                            }
                            else
                            {
                                if(alpha==0xFF)
                                {
                                    unionReadBuf->u16ReadBuf[j]=unionReadBuf->u32ReadBuf[j]&0xFFFF;
                                }
                                else
                                {
                                    unionReadBuf->u16ReadBuf[j]=llGeometryColorMix(bgUnionReadBuf->u16ReadBuf[j],unionReadBuf->u32ReadBuf[j]&0xFFFF,alpha);
                                }
                            }
                        }
                        if(isShow)
                {
                        llFillMultipleColors(tempPoint.x, tempPoint.y, tempPoint.x+currPixelCount -1,  tempPoint.y,unionReadBuf->u16ReadBuf);
                }
                    }
                    else
                    {
                        for(j=0; j<(currPixelCount); j++)
                        {
                            alpha=unionReadBuf->u32ReadBuf[j]>>16;

                            if(alpha==0)
                            {
                                unionReadBuf->u16ReadBuf[j]=bgColor;
                            }
                            else
                            {
                                if(alpha==0xFF)
                                {
                                    unionReadBuf->u16ReadBuf[j]=unionReadBuf->u32ReadBuf[j]&0xFFFF;
                                }
                                else
                                {
                                    unionReadBuf->u16ReadBuf[j]=llGeometryColorMix(bgColor,unionReadBuf->u32ReadBuf[j]&0xFFFF,alpha);
                                }
                            }
                        }
                        
                        if(isShow)
                {
                        llFillMultipleColors(tempPoint.x, tempPoint.y, tempPoint.x+currPixelCount -1,  tempPoint.y,unionReadBuf->u16ReadBuf);
                }
                    }
                    i += currPixelCount;
                }
            break;
        }
        default:
            break;
        }
        
        if(!isShow)
        {
            return i;
        }
    }
    return 0;
}

//全屏绝对坐标计算
void llGeneralImageSpecificAreaShow(llGeneral *widget,llGeometry originGeometry,llGeometry targetGeometry,uint32_t imageAddr)
{
    imageBufferTypedef *unionReadBuf,*bgUnionReadBuf;
    unionReadBuf=llMalloc(sizeof(imageBufferTypedef));
    bgUnionReadBuf=llMalloc(sizeof(imageBufferTypedef));
    if((unionReadBuf==NULL)||(bgUnionReadBuf==NULL))
    {
        return ;
    }
    
    llGeneralImageSpecificAreaProcess(widget,originGeometry,targetGeometry,imageAddr,unionReadBuf,bgUnionReadBuf,true,NULL);
    
    llFree(unionReadBuf);
    llFree(bgUnionReadBuf);
}

uint32_t llGeneralImageSpecificAreaRead(uint8_t *readCount,llGeneral *widget,uint32_t imageAddr,llGeometry imageGeometry,imageBufferTypedef *unionReadBuf)
{
    imageBufferTypedef *bgUnionReadBuf;
    llPoint globalPos;
//    llPoint pos;
    llGeometry originGeometry;
    uint32_t ret=0;
    static uint32_t prevYCount;

    bgUnionReadBuf=llMalloc(sizeof(imageBufferTypedef));
    if(bgUnionReadBuf==NULL)
    {
        return ret;
    }
    
    if(*readCount==0)
    {
        prevYCount=0;
    }
        globalPos=llListGetGlobalPos(widget->parentWidget);

        originGeometry.x=globalPos.x+widget->geometry.x;
        originGeometry.y=globalPos.y+widget->geometry.y;
    
       ret=llGeneralImageSpecificAreaProcess(widget,originGeometry,imageGeometry,imageAddr,unionReadBuf,bgUnionReadBuf,false,&prevYCount);
        
    (*readCount)++;
    
    llFree(bgUnionReadBuf);
    return ret;
}

void* llGeneralGetWidget(uint16_t nameId)
{
    llListWidgetInfo *widgetInfo;

    if(llList_GetInfoByName(&widgetInfo,nameId)==true)
    {
        return (llGeneral*)widgetInfo->widget;
    }
    return NULL;
}

uint8_t llRgbToGray(uint8_t r,uint8_t g,uint8_t b)
{
    return ((r*38 + g*75 + b*15) >> 7);
}

uint16_t llRgb565ToGray(uint16_t rgb565)
{
    uint8_t gray=0;

    gray= llRgbToGray(((rgb565>>11)&0x1F),(((rgb565) >> 5) & 0x3f),(rgb565&0x1F));
    return RGB_CONVERT(gray,gray,gray);
}

uint32_t llRgb888ToGray(uint32_t rgb888)
{
    uint8_t gray=0;
    gray= llRgbToGray(((rgb888>>16)&0xFF),(((rgb888) >> 8) & 0xFF),(rgb888&0xFF));
    return RGB_CONVERT(gray,gray,gray);
}


void llGeneralWidgetSelect(llGeneral *widget)
{
    int16_t x,y,width,height;

    llPoint globalPos;
    globalPos=llListGetGlobalPos(widget->parentWidget);

    x=widget->geometry.x+globalPos.x;
    y=widget->geometry.y+globalPos.y;
    width=widget->geometry.width;
    height=widget->geometry.height;

    llDrawLine(x,y,x+width,y,0);
    llDrawLine(x,y,x,y+height,0);
    llDrawLine(x,y+height,x+width,y+height,0);
    llDrawLine(x+width,y,x+width,y+height,0);
}

void llGeneralWidgetParentRecover(llGeneral *widget,llGeometry geometry)
{
    if(widget->parentType==widgetTypeBackground)
    {
        pBackgroundSpecificAreaRecover((llBackground*)widget->parentWidget,geometry);
    }
    else
    {
        if(widget->parentType==widgetTypeWindow)
        {
            pWindowSpecificAreaRecover((llWindow*)widget->parentWidget,geometry);
        }
    }
}

void llGeneralRecover(llGeneral *widget,llGeometry targetGeometry)
{
    //遍历控件,判断是否重叠
    llListHead *tempPos,*tempPos2,*safePos,*safePos2;
    llListWidgetInfo *tempInfo,*tempInfo2;
    llGeneral *tempWidget2;

    llGeneralWidgetParentRecover(widget,targetGeometry);

    //正向开始遍历
    list_for_each_safe(tempPos,safePos, &llWidgetLink)
    {
        tempInfo = list_entry(tempPos,llListWidgetInfo, parent_link_pos);

        //继续查子控件
        list_for_each_safe(tempPos2,safePos2, &(tempInfo->child_link))
        {
            tempInfo2 = list_entry(tempPos2, llListWidgetInfo, parent_link_pos);

            tempWidget2=(llGeneral*)tempInfo2->widget;

            if((tempWidget2!=widget)&&(tempWidget2->widgetType!=widgetTypeBackground)&&(tempWidget2!=widget->parentWidget))
            {
                if(llRectIsOverlap(tempWidget2->geometry,targetGeometry)==true)
                {
                    //遮盖的控件刷新
                    tempWidget2->refreshFunc(tempWidget2->nameId);
                }
            }
        }
    }
}

void llGeneralWidgetParentRecoverMove(llGeneral *widget,llGeometry oldGeometry,llGeometry newGeometry)
{
    llGeometry rect1,rect2= {0,0,0,0},rectOverlap;

    if(llRectIntersect(oldGeometry,newGeometry,&rectOverlap))
    {
        //共8种情况
        if(oldGeometry.height==rectOverlap.height)
        {
            if(oldGeometry.x==rectOverlap.x)
            {
                rect1.x=rectOverlap.x+rectOverlap.width;
                rect1.y=rectOverlap.y;
                rect1.width=oldGeometry.width-rectOverlap.width;
                rect1.height=oldGeometry.height;
            }
            else
            {
                rect1.x=oldGeometry.x;
                rect1.y=oldGeometry.y;
                rect1.width=oldGeometry.width-rectOverlap.width;
                rect1.height=oldGeometry.height;
            }
        }
        else if(oldGeometry.width==rectOverlap.width)
        {
            if(oldGeometry.y==rectOverlap.y)
            {
                rect1.x=oldGeometry.x;
                rect1.y=rectOverlap.y+rectOverlap.height;
                rect1.width=oldGeometry.width;
                rect1.height=oldGeometry.height-rectOverlap.height;
            }
            else
            {
                rect1.x=oldGeometry.x;
                rect1.y=oldGeometry.y;
                rect1.width=oldGeometry.width;
                rect1.height=oldGeometry.height-rectOverlap.height;
            }
        }
        else if((oldGeometry.x==rectOverlap.x)&&(oldGeometry.y==rectOverlap.y))
        {
            rect1.x=rectOverlap.x+rectOverlap.width;
            rect1.y=rectOverlap.y;
            rect1.width=oldGeometry.width-rectOverlap.width;
            rect1.height=rectOverlap.height;

            rect2.x=rectOverlap.x;
            rect2.y=rectOverlap.y+rectOverlap.height;
            rect2.width=oldGeometry.width;
            rect2.height=oldGeometry.height-rectOverlap.height;
        }
        else if((oldGeometry.x==rectOverlap.x)&&((oldGeometry.y+oldGeometry.height)==(rectOverlap.y+rectOverlap.height)))
        {
            rect1.x=oldGeometry.x;
            rect1.y=oldGeometry.y;
            rect1.width=oldGeometry.width;
            rect1.height=oldGeometry.height-rectOverlap.height;

            rect2.x=rectOverlap.x+rectOverlap.width;
            rect2.y=rectOverlap.y;
            rect2.width=oldGeometry.width-rectOverlap.width;
            rect2.height=rectOverlap.height;
        }
        else if(((oldGeometry.x+oldGeometry.width)==(rectOverlap.x+rectOverlap.width))&&(oldGeometry.y==rectOverlap.y))
        {
            rect1.x=oldGeometry.x;
            rect1.y=oldGeometry.y;
            rect1.width=oldGeometry.width-rectOverlap.width;
            rect1.height=rectOverlap.height;

            rect2.x=oldGeometry.x;
            rect2.y=rectOverlap.y+rectOverlap.height;
            rect2.width=oldGeometry.width;
            rect2.height=oldGeometry.height-rectOverlap.height;
        }
        else if(((oldGeometry.x+oldGeometry.width)==(rectOverlap.x+rectOverlap.width))&&((oldGeometry.y+oldGeometry.height)==(rectOverlap.y+rectOverlap.height)))
        {
            rect1.x=oldGeometry.x;
            rect1.y=oldGeometry.y;
            rect1.width=oldGeometry.width;
            rect1.height=oldGeometry.height-rectOverlap.height;

            rect2.x=oldGeometry.x;
            rect2.y=rectOverlap.y;
            rect2.width=oldGeometry.width-rectOverlap.width;
            rect2.height=rectOverlap.height;
        }
        llGeneralWidgetParentRecover(widget,rect1);
        if(rect2.width>0)
        {
            llGeneralWidgetParentRecover(widget,rect2);
        }
    }
    else
    {
        llGeneralWidgetParentRecover(widget,oldGeometry);
    }
}

//查找控件的所有父控件是否有隐藏，bg(show) - win(show) - win(hide) - btn(不能显示)
bool llGeneralParentLinkHidden(llGeneral *widget)
{
    llGeneral *w;
    w=widget->parentWidget;
    while(w->widgetType!=widgetTypeBackground)
    {
        if(w->isHidden)
        {
            return true;
        }
        w=w->parentWidget;
    }
    return false;
}


//#define monochrome_2_RGB888(color)                (color?0x000000:0xffffff)
//#define RGB233_2_RGB888(color)                    (((color&0xC0)<<16)+((color&0x38)<<10)+((color&0x07)<<5))
//#define RGB565_2_RGB888(color)                    (((color&0xF800)<<8)+((color&0x7E0)<<5)+((color&0x1F)<<3))


#define RGB888_2_monochrome(color)                ((color)?0:1)
#define RGB888_2_RGB233(color)                    ((((color&0xff0000)>>22) << 6) + (((color&0xff00)>>13) << 3) + (((color&0xff)>>5)))
#define RGB888_2_RGB565(color)                    ((((color&0xff0000)>>19) << 11) + (((color&0xff00)>>10) << 5) + (((color&0xff)>>3)))

//// 1 8(233) 16(565) 24(888)
//#if CONFIG_COLOR_DEPTH == 1
//#define RGB888(color)                  RGB888_2_monochrome(color)
//#define RGB_CONVERT(R,G,B)             RGB888((uint32_t)(((uint32_t)R<<16)|((uint32_t)G<<8)|B))
//#elif CONFIG_COLOR_DEPTH == 8
//#define RGB888(color)                 RGB888_2_RGB233(color)
//#define RGB_CONVERT(R,G,B)             RGB888((uint32_t)(((uint32_t)R<<16)|((uint32_t)G<<8)|B))
//#elif CONFIG_COLOR_DEPTH == 16
//#define RGB888(color)                  RGB888_2_RGB565(color)
//#define RGB_CONVERT(R,G,B)             RGB888((uint32_t)(((uint32_t)R<<16)|((uint32_t)G<<8)|B))
//#elif CONFIG_COLOR_DEPTH == 24
//#define RGB888(color)                 (color)
//#define RGB_CONVERT(R,G,B)             RGB888((uint32_t)(((uint32_t)R<<16)|((uint32_t)G<<8)|B))
//#endif

llColor RGB888(uint32_t color)
{
    llColor ret=0;
    // 1 8(233) 16(565) 24(888)
    switch(cfgColorDepth)
    {
    case 1:
    {
        ret= RGB888_2_monochrome(color);
        break;
    }
    case 8:
    {
        ret= RGB888_2_RGB233(color);
        break;
    }
    case 16:
    {
        ret= RGB888_2_RGB565(color);
        break;
    }
    case 24:
    {
        ret= color;
        break;
    }
    default:
        break;
    }
    return ret;
}

llColor RGB_CONVERT(uint8_t R,uint8_t G,uint8_t B)
{
    llColor ret=0;
    // 1 8(233) 16(565) 24(888)
    switch(cfgColorDepth)
    {
    case 1:
    {
        ret= RGB888((uint32_t)(((uint32_t)R<<16)|((uint32_t)G<<8)|B));
        break;
    }
    case 8:
    {
        ret= RGB888((uint32_t)(((uint32_t)R<<16)|((uint32_t)G<<8)|B));
        break;
    }
    case 16:
    {
        ret= RGB888((uint32_t)(((uint32_t)R<<16)|((uint32_t)G<<8)|B));
        break;
    }
    case 24:
    {
        ret= RGB888((uint32_t)(((uint32_t)R<<16)|((uint32_t)G<<8)|B));
        break;
    }
    default:
        break;
    }
    return ret;
}

void llGeometryGetR_G_B(llColor color,uint8_t *r,uint8_t *g,uint8_t *b)
{
    // 1 8(233) 16(565) 24(888)
    switch(cfgColorDepth)
    {
    case 1:
    {

        break;
    }
    case 8:
    {

        break;
    }
    case 16:
    {
        *r=(color>>11)&0x1F;
        *g=(color>>5)&0x3F;
        *b=color&0x1F;
        break;
    }
    case 24:
    {

        break;
    }
    default:
        break;
    }
}

llColor llGeometryColorMix(llColor rgb1,llColor rgb2,uint8_t alpha2)
{
//            R(C)=(1-alpha)*R(B) + alpha*R(A)
//            G(C)=(1-alpha)*G(B) + alpha*G(A)
//            B(C)=(1-alpha)*B(B) + alpha*B(A)

    uint32_t r,g,b;
    uint8_t r1=0,g1=0,b1=0,r2=0,g2=0,b2=0;
    llGeometryGetR_G_B(rgb1,&r1,&g1,&b1);
    llGeometryGetR_G_B(rgb2,&r2,&g2,&b2);
    r = (255-alpha2)*r1 + alpha2*r2;
    g = (255-alpha2)*g1 + alpha2*g2;
    b = (255-alpha2)*b1 + alpha2*b2;
    r=r/255;
    g=g/255;
    b=b/255;
    return (r<<11)+(g<<5)+b;;
}
bool llGeometryAutoSetHiddenIsShow(llGeneral *widget,bool isHidden)
{
    if(widget->isEnable)
    {
        if(widget->isHidden)//控件现在处于隐藏
        {
            if(isHidden==false)//变为显示
            {
                //变为显示
                widget->isHidden=false;
                return true;
            }
        }
        else//控件现在处于显示
        {
            if(isHidden==true)//变为隐藏
            {
                widget->isHidden=true;
                //变为隐藏,恢复背景
                llGeneralWidgetParentRecover(widget,widget->geometry);
            }
        }
    }
    return false;
}

uint8_t llGeneralGetParentBackgroundInfo(llGeneral *widget,llColor* retColor,uint32_t *retImageAddr,llPoint* retImagePoint)
{
    llGeneral *parent;
    parent=widget->parentWidget;
    if(widget->parentType==widgetTypeBackground)
    {
        if(((llBackground*)parent)->isColor)
        {
            *retColor=((llBackground*)parent)->color;
            return PARENT_BACKGROUND_TYPE_COLOR;
        }
        else
        {
            *retImageAddr=((llBackground*)parent)->imageAddr;
            retImagePoint->x=((llBackground*)parent)->geometry.x;
            retImagePoint->y=((llBackground*)parent)->geometry.y;
            return PARENT_BACKGROUND_TYPE_IMAGE;
        }
    }
    else
    {
        if(widget->parentType==widgetTypeWindow)
        {
            if(((llWindow*)parent)->isTransparent)
            {
                return llGeneralGetParentBackgroundInfo(parent,retColor,retImageAddr,retImagePoint);
            }
            else
            {
                if(((llWindow*)parent)->isColor)
                {
                    *retColor=((llWindow*)parent)->color;
                    return PARENT_BACKGROUND_TYPE_COLOR;
                }
                else
                {
                    *retImageAddr=((llWindow*)parent)->imageAddr;
                    retImagePoint->x=((llWindow*)parent)->geometry.x;
                    retImagePoint->y=((llWindow*)parent)->geometry.y;
                    return PARENT_BACKGROUND_TYPE_IMAGE;
                }
            }
        }
    }
    return PARENT_BACKGROUND_TYPE_ERROR;
}

//获取实际显示的背景控件
llGeneral* llGeneralGetParentBackgroundWidget(llGeneral *widget,llColor* retColor,uint32_t *retImageAddr)
{
    llGeneral *parent;
    parent=widget->parentWidget;
    if(widget->parentType==widgetTypeBackground)
    {
        if(((llBackground*)parent)->isColor)
        {
            *retColor=((llBackground*)parent)->color;
            return parent;
        }
        else
        {
            *retImageAddr=((llBackground*)parent)->imageAddr;
            return parent;
        }
    }
    else
    {
        if(widget->parentType==widgetTypeWindow)
        {
            if(((llWindow*)parent)->isTransparent)
            {
                return llGeneralGetParentBackgroundWidget(parent,retColor,retImageAddr);
            }
            else
            {
                if(((llWindow*)parent)->isColor)
                {
                    *retColor=((llWindow*)parent)->color;
                    return parent;
                }
                else
                {
                    *retImageAddr=((llWindow*)parent)->imageAddr;
                    return parent;
                }
            }
        }
    }
    return NULL;
}

uint8_t llGeneralGetImageBitWide(uint8_t convertType)
{
    uint8_t bitWide=0;
    switch(convertType)
    {
        case CONVERT_TYPE_565:
        case CONVERT_TYPE_565_MASK:
        {
            bitWide=2;
            break;
        }
        case CONVERT_TYPE_888:
        case CONVERT_TYPE_8888:
        case CONVERT_TYPE_8565:
        {
            bitWide=4;
            break;
        }
        default:
            break;
    }
    return bitWide;
}

/***************************************************************************//**
 * @fn         void llGeneralImageBlockRead(uint32_t imgAddr,uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint8_t *outBuf)
 * @brief      读取图片块数据
 * @param      uint32_t imgAddr    图片地址
 *             uint16_t x          图片块起始地址x,图片起始地址为0
 *             uint16_t y          图片块起始地址y,图片起始地址为0
 *             uint16_t w          图片块宽度
 *             uint16_t h          图片块高度
 *             uint8_t *outBuf     数据输出
 * @return     
 * @version    V0.1
 * @date       2022/6/23
 * @details    
 ******************************************************************************/
void llGeneralImageBlockRead(uint32_t imgAddr,uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint8_t *outBuf)
{
    imageHeaderTypedef imageHeader;
    uint16_t i;
    uint8_t bitWide=2;

    llReadExFlash(imgAddr,(uint8_t*)&imageHeader,16);
    imgAddr=imgAddr+16;
    bitWide=llGeneralGetImageBitWide(imageHeader.convertType);

    w*=bitWide;
    x*=bitWide;
    imageHeader.width*=bitWide;
    for(i=y;i<(y+h);i++)
    {
        llReadExFlash(imgAddr+i*imageHeader.width+x,outBuf+(i-y)*w,w);
    }
}

uint8_t* llGeneralGetText(llGeneral *widget)
{
    switch(widget->widgetType)
    {
        case widgetTypeText:
        {
            return pTextGetText((llText*)widget);
        }
        case widgetTypeButton:
        {
            return pButtonGetText((llButton*)widget);
        }
        case widgetTypeLineEdit:
        {
            return pLineEditGetText((llLineEdit*)widget);
        }
        default:
            break;
    }
    return 0;
}

void llGeneralSetText(llGeneral *widget,uint8_t* text)
{
    switch(widget->widgetType)
    {
        case widgetTypeText:
        {
            pTextSetText((llText*)widget,text);
            break;
        }
        case widgetTypeButton:
        {
            pButtonSetText((llButton*)widget,text);
            break;
        }
        case widgetTypeLineEdit:
        {
            pLineEditSetText((llLineEdit*)widget,text);
            break;
        }
        default:
            break;
    }
}

float pGeneralGetTextFloat(llGeneral *widget)
{
    uint8_t *pText=llGeneralGetText(widget);
    
    if(pText==NULL)
    {
        return 0;
    }
    return llStrToFloat(pText);
}

float nGeneralGetTextFloat(uint16_t nameId)
{
    void *widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        return pGeneralGetTextFloat((llGeneral*)widget);
    }
    return 0;
}

void pGeneralSetTextFloat(llGeneral *widget,float value,uint8_t afterDecimalPointNum)
{
    uint8_t buf[16]={0};
    
    llFloatToStr(value,afterDecimalPointNum,buf);
    llGeneralSetText(widget,buf);
}

void nGeneralSetTextFloat(uint16_t nameId,float value,uint8_t afterDecimalPointNum)
{
    void *widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        pGeneralSetTextFloat((llGeneral*)widget,value,afterDecimalPointNum);
    }
}

// change return true
bool pGeneralAutoSetTextFloat(llGeneral *widget,float newValue,uint8_t afterDecimalPointNum)
{
    if(pGeneralGetTextFloat(widget)!=newValue)
    {
        pGeneralSetTextFloat(widget,newValue,afterDecimalPointNum);
        return true;
    }
    return false;
}

// change return true
bool nGeneralAutoSetTextFloat(uint16_t nameId,float newValue,uint8_t afterDecimalPointNum)
{
    void *widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        return pGeneralAutoSetTextFloat((llGeneral*)widget,newValue,afterDecimalPointNum);
    }
    return false;
}

int32_t pGeneralGetTextInt32(llGeneral *widget)
{
    uint8_t *pText=llGeneralGetText(widget);
    
    if(pText==NULL)
    {
        return 0;
    }
    return llStrToI32(pText);
}

int32_t nGeneralGetTextInt32(uint16_t nameId)
{
    void *widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        return pGeneralGetTextInt32((llGeneral*)widget);
    }
    return 0;
}

void pGeneralSetTextInt32(llGeneral *widget,int32_t value)
{
    uint8_t buf[16]={0};
    llI32ToStr(value,buf);
    llGeneralSetText(widget,buf);
}

void nGeneralSetTextInt32(uint16_t nameId,int32_t value)
{
    void *widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        pGeneralSetTextInt32((llGeneral*)widget,value);
    }
}
// change return true
bool pGeneralAutoSetTextInt32(llGeneral *widget,int32_t newValue)
{
    if(pGeneralGetTextInt32(widget)!=newValue)
    {
        pGeneralSetTextInt32(widget,newValue);
        return true;
    }
    return false;
}

// change return true
bool nGeneralAutoSetTextInt32(uint16_t nameId,int32_t newValue)
{
    void *widget=llGeneralGetWidget(nameId);
    if(widget!=NULL)
    {
        return pGeneralAutoSetTextInt32((llGeneral*)widget,newValue);
    }
    return false;
}

