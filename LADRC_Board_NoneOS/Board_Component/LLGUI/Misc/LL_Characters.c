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

#include "LL_Characters.h"
#include "LL_Timer.h"
#include "LL_Gui.h"
#include "LL_Linked_List.h"
#include "LL_Background.h"
#include "LL_Window.h"

llColor fixColor(llColor bgColor,llColor wrColor,uint8_t alpha)
{
    uint8_t r1=0,g1=0,b1=0,r2=0,g2=0,b2=0;
    uint32_t r,g,b;

    llGeometryGetR_G_B(bgColor,&r1,&g1,&b1);
    llGeometryGetR_G_B(wrColor,&r2,&g2,&b2);

//            R(C)=(1-alpha)*R(B) + alpha*R(A)
//            G(C)=(1-alpha)*G(B) + alpha*G(A)
//            B(C)=(1-alpha)*B(B) + alpha*B(A)

    r = (255-alpha)*r1 + alpha*r2;
    g = (255-alpha)*g1 + alpha*g2;
    b = (255-alpha)*b1 + alpha*b2;
    r=r/255;
    g=g/255;
    b=b/255;

    return ((r<<11)+(g<<5)+b);
}



//单字显示
void llCharShowChar(llGeneral* widget,int16_t x, int16_t y,llChar* charInfo,uint8_t *charStr,bool isColorBlock,imageBufferTypedef *imageBuf)
{
    uint16_t i, j;
    llGeometry charGeometry,charGeometryShow;
    llPoint point;
    uint32_t All_Bit_Num=0;
    uint32_t Byte_Num=0;
    uint32_t Bit_Offset=0;
    uint8_t clolrLevel=0;

    llColor bgColor,*pImageColor;
    uint32_t bgAddr=IMAGE_NONE;
    uint32_t imgColorCount,imgColorBufferCount=0;
    uint8_t imgReadCount=0;

    uint16_t width,height;
    uint8_t *buffer=NULL;
    uint8_t dataBits;
    uint16_t imageReadByteMax=IMAGE_READ_BYTE_MAX/sizeof(llColor);//一次最多读多少字节
    
    imgColorCount=imageReadByteMax;
    uint8_t passwordStr='*';
    uint8_t *str;
    
    void * pColorBuf;
    uint16_t bolckWidth=0;

    uint32_t charAddr;

    uint16_t xBitCount=0;
    uint8_t byteCount=0;

    pImageColor=(llColor*)imageBuf;
    //英文 0x0-0x7F
    if(charInfo->isPassword)
    {
        str=&passwordStr;
    }
    else
    {
        str=charStr;
    }

    if(llFontGetLibType()==typeBinFile)
    {
        buffer=llMalloc(CHAR_BUFFER_BYTE_MAX);
    }

    buffer=llFontGetData(str,&dataBits,&width,&height,buffer,&charAddr,0);  /* 取字模数据 */

    if(isColorBlock)
    {
        pColorBuf=llMalloc(width*sizeof(llColor));

        if(pColorBuf==NULL)
        {
            return;
        }
    }
    
    charGeometry.x=x;
    charGeometry.y=y;
    charGeometry.width=width;
    charGeometry.height=height;
    //计算文字是否超出显示区域

    if(llRectIsOverlap(charInfo->showGeometry,charGeometry))//在区域内,需要显示
    {
        bgColor=charInfo->backgroundColor;
        if(charInfo->isTransparent)
        {
            widget= llGeneralGetParentBackgroundWidget(widget,&bgColor,&bgAddr);
        }

        if(llRectIsFullIn(charInfo->showGeometry,charGeometry))
        {
            xBitCount=0;
            byteCount=0;
            for(i=0; i<height; i++)
            {
                for(j=0; j<width; j++)
                {
                    All_Bit_Num=i*width+j;
                    Byte_Num=All_Bit_Num/(8/dataBits);

                    Byte_Num-=byteCount;

                    point.x=x + j;
                    point.y=y + i;

                    switch (dataBits)
                    {
                    case 1:
                    {
                        Bit_Offset=All_Bit_Num%8;

                        if(((imgColorCount>=imageReadByteMax)||(imgColorCount>=imgColorBufferCount))&&(bgAddr!=IMAGE_NONE))
                        {
                            //读取图片数据
                            imgColorBufferCount=llGeneralImageSpecificAreaRead(&imgReadCount,widget,bgAddr,charGeometry,(imageBufferTypedef*)pImageColor);
                            imgColorCount=0;
                        }
                        //先取低位
                        if(GETBIT(buffer[Byte_Num],Bit_Offset))
                        {
                            /* 字符颜色 */
                            if(isColorBlock)
                            {
                                ((llColor*) pColorBuf)[j]=charInfo->charColor;
                            }
                            else
                            {
                                llSetPoint( point.x, point.y, charInfo->charColor );
                            }
                        }
                        else
                        {
                            if(isColorBlock)
                            {
                                if(bgAddr==IMAGE_NONE)
                                {
                                    ((llColor*) pColorBuf)[j]=bgColor;
                                }
                                else
                                {
                                    ((llColor*) pColorBuf)[j]=pImageColor[imgColorCount];
                                }
                            }
                        }
                        if(bgAddr!=IMAGE_NONE)
                        {
                            imgColorCount++;
                        }
                        break;
                    }
                    case 2:
                    {
                        Bit_Offset=All_Bit_Num%4;
                        Bit_Offset*=2;
                        clolrLevel=GETBIT(buffer[Byte_Num],Bit_Offset);
                        clolrLevel=clolrLevel<<1;
                        clolrLevel+=GETBIT(buffer[Byte_Num],Bit_Offset+1);

                        if(((imgColorCount>=imageReadByteMax)||(imgColorCount>=imgColorBufferCount))&&(bgAddr!=IMAGE_NONE))
                        {
                            //读取图片数据
                            imgColorBufferCount=llGeneralImageSpecificAreaRead(&imgReadCount,widget,bgAddr,charGeometry,(imageBufferTypedef*)pImageColor);
                            imgColorCount=0;
                        }
                        if(clolrLevel!=0)
                        {
                            /* 字符颜色 */
                            if(isColorBlock)
                            {
                                if(bgAddr==IMAGE_NONE)
                                {
                                    ((llColor*) pColorBuf)[j]=fixColor(bgColor,charInfo->charColor,clolrLevel<<6);
                                }
                                else
                                {
                                    ((llColor*) pColorBuf)[j]=fixColor(pImageColor[imgColorCount],charInfo->charColor,clolrLevel<<6);
                                }
                            }
                            else
                            {
                                if(bgAddr==IMAGE_NONE)
                                {
                                    llSetPoint( point.x, point.y,fixColor(bgColor,charInfo->charColor,clolrLevel<<6) );
                                }
                                else
                                {
                                    llSetPoint( point.x, point.y,fixColor(pImageColor[imgColorCount],charInfo->charColor,clolrLevel<<6) );
                                }
                            }
                        }
                        else
                        {
                            if(isColorBlock)
                            {
                                if(bgAddr==IMAGE_NONE)
                                {
                                    ((llColor*) pColorBuf)[j]=bgColor;
                                }
                                else
                                {
                                    ((llColor*) pColorBuf)[j]=pImageColor[imgColorCount];
                                }
                            }
                        }
                        if(bgAddr!=IMAGE_NONE)
                        {
                            imgColorCount++;
                        }
                        break;
                    }
                    case 4:
                    {
                        Bit_Offset=All_Bit_Num%2;
                        Bit_Offset*=4;
                        clolrLevel=GETBIT(buffer[Byte_Num],Bit_Offset);
                        clolrLevel=clolrLevel<<1;
                        clolrLevel+=GETBIT(buffer[Byte_Num],Bit_Offset+1);
                        clolrLevel=clolrLevel<<1;
                        clolrLevel+=GETBIT(buffer[Byte_Num],Bit_Offset+2);
                        clolrLevel=clolrLevel<<1;
                        clolrLevel+=GETBIT(buffer[Byte_Num],Bit_Offset+3);

                        if(((imgColorCount>=imageReadByteMax)||(imgColorCount>=imgColorBufferCount))&&(bgAddr!=IMAGE_NONE))
                        {
                            //读取图片数据
                            imgColorBufferCount=llGeneralImageSpecificAreaRead(&imgReadCount,widget,bgAddr,charGeometry,(imageBufferTypedef*)pImageColor);
                            imgColorCount=0;
                        }
                        if(clolrLevel!=0)
                        {
                            /* 字符颜色 */
                            if(isColorBlock)
                            {
                                if(bgAddr==IMAGE_NONE)
                                {
                                    ((llColor*) pColorBuf)[j]=fixColor(bgColor,charInfo->charColor,clolrLevel<<4);
                                }
                                else
                                {
                                    ((llColor*) pColorBuf)[j]=fixColor(pImageColor[imgColorCount],charInfo->charColor,clolrLevel<<4);
                                }
                            }
                            else
                            {
                                if(bgAddr==IMAGE_NONE)
                                {
                                    llSetPoint( point.x, point.y,fixColor(bgColor,charInfo->charColor,clolrLevel<<4) );
                                }
                                else
                                {
                                    llSetPoint( point.x, point.y,fixColor(pImageColor[imgColorCount],charInfo->charColor,clolrLevel<<4) );
                                }
                            }
                        }
                        else
                        {
                            if(isColorBlock)
                            {
                                if(bgAddr==IMAGE_NONE)
                                {
                                    ((llColor*) pColorBuf)[j]=bgColor;
                                }
                                else
                                {
                                    ((llColor*) pColorBuf)[j]=pImageColor[imgColorCount];
                                }
                            }
                        }
                        if(bgAddr!=IMAGE_NONE)
                        {
                            imgColorCount++;
                        }
                        break;
                    }
                    case 8:
                    {
                        clolrLevel=buffer[Byte_Num];

                        if(((imgColorCount>=imageReadByteMax)||(imgColorCount>=imgColorBufferCount))&&(bgAddr!=IMAGE_NONE))
                        {
                            //读取图片数据
                            imgColorBufferCount=llGeneralImageSpecificAreaRead(&imgReadCount,widget,bgAddr,charGeometry,(imageBufferTypedef*)pImageColor);
                            imgColorCount=0;
                        }
                        if(clolrLevel!=0)
                        {
                            /* 字符颜色 */
                            if(isColorBlock)
                            {
                                if(bgAddr==IMAGE_NONE)
                                {
                                    ((llColor*) pColorBuf)[j]=fixColor(bgColor,charInfo->charColor,clolrLevel);
                                }
                                else
                                {
                                    ((llColor*) pColorBuf)[j]=fixColor(pImageColor[imgColorCount],charInfo->charColor,clolrLevel);
                                }
                            }
                            else
                            {
                                if(bgAddr==IMAGE_NONE)
                                {
                                    llSetPoint( point.x, point.y,fixColor(bgColor,charInfo->charColor,clolrLevel) );
                                }
                                else
                                {
                                    llSetPoint( point.x, point.y,fixColor(pImageColor[imgColorCount],charInfo->charColor,clolrLevel) );
                                }
                            }
                        }
                        else
                        {
                            if(isColorBlock)
                            {
                                if(bgAddr==IMAGE_NONE)
                                {
                                    ((llColor*) pColorBuf)[j]=bgColor;
                                }
                                else
                                {
                                    ((llColor*) pColorBuf)[j]=pImageColor[imgColorCount];
                                }
                            }
                        }
                        if(bgAddr!=IMAGE_NONE)
                        {
                            imgColorCount++;
                        }
                        break;
                    }
                    default:
                        break;
                    }

                    xBitCount++;
                    if((xBitCount%(8/dataBits))==0)
                    {
                        uint16_t bbCount=xBitCount/(8/dataBits);
                        if((bbCount%CHAR_BUFFER_BYTE_MAX)==0)
                        {
                            byteCount+=CHAR_BUFFER_BYTE_MAX;
                            llFontGetTinyData(charAddr,buffer,byteCount);
                        }
                    }
                }
                if(isColorBlock)
                {
                    llFillMultipleColors(x,y+i,x+width-1,y+i,pColorBuf);
                }
            }
        }
        else
        {
            //取相交范围
            llRectIntersect(charInfo->showGeometry,charGeometry,&charGeometryShow);
            width=charGeometry.width;
            height=charGeometry.height;
            if(charGeometryShow.x<0)
            {
                charGeometryShow.width+=charGeometryShow.x;
                charGeometryShow.x=0;
            }
            if(charGeometryShow.y<0)
            {
                charGeometryShow.height+=charGeometryShow.y;
                charGeometryShow.y=0;
            }
            xBitCount=0;
            byteCount=0;
            for(i=0; i<height; i++)
            {
                bolckWidth=0;
                for(j=0; j<width; j++)
                {
                    All_Bit_Num=i*width+j;
                    Byte_Num=All_Bit_Num/(8/dataBits);

                    Byte_Num-=byteCount;

                    point.x=x + j;
                    point.y=y + i;
                    if(llPointInRect(point,charGeometryShow))
                    {
                        bolckWidth++;
                        switch (dataBits)
                        {
                        case 1:
                        {
                            Bit_Offset=All_Bit_Num%8;
                            if(((imgColorCount>=imageReadByteMax)||(imgColorCount>=imgColorBufferCount))&&(bgAddr!=IMAGE_NONE))
                            {
                                //读取图片数据
                                imgColorBufferCount=llGeneralImageSpecificAreaRead(&imgReadCount,widget,bgAddr,charGeometryShow,(imageBufferTypedef*)pImageColor);
                                imgColorCount=0;
                            }
                            //先取低位
                            if(GETBIT(buffer[Byte_Num],Bit_Offset))
                            {
                                /* 字符颜色 */
                                if(isColorBlock)
                                {
                                    ((llColor*) pColorBuf)[j]=charInfo->charColor;
                                }
                                else
                                {
                                    llSetPoint( point.x, point.y, charInfo->charColor );
                                }
                            }
                            else
                            {
                                if(isColorBlock)
                                {
                                    if(bgAddr==IMAGE_NONE)
                                    {
                                        ((llColor*) pColorBuf)[j]=bgColor;
                                    }
                                    else
                                    {
                                        ((llColor*) pColorBuf)[j]=pImageColor[imgColorCount];
                                    }
                                }
                            }
                            if(bgAddr!=IMAGE_NONE)
                            {
                                imgColorCount++;
                            }
                            break;
                        }
                        case 2:
                        {
                            Bit_Offset=All_Bit_Num%4;
                            Bit_Offset*=2;
                            clolrLevel=GETBIT(buffer[Byte_Num],Bit_Offset);
                            clolrLevel=clolrLevel<<1;
                            clolrLevel+=GETBIT(buffer[Byte_Num],Bit_Offset+1);

                            if(((imgColorCount>=imageReadByteMax)||(imgColorCount>=imgColorBufferCount))&&(bgAddr!=IMAGE_NONE))
                            {
                                //读取图片数据
                                imgColorBufferCount=llGeneralImageSpecificAreaRead(&imgReadCount,widget,bgAddr,charGeometryShow,(imageBufferTypedef*)pImageColor);
                                imgColorCount=0;
                            }
                            if(clolrLevel!=0)
                            {
                                /* 字符颜色 */
                                if(isColorBlock)
                                {
                                    ((llColor*) pColorBuf)[j]=fixColor(bgColor,charInfo->charColor,clolrLevel<<6);
                                }
                                else
                                {
                                    llSetPoint( point.x, point.y, fixColor(bgColor,charInfo->charColor,clolrLevel<<6) );
                                }
                            }
                            else
                            {
                                if(isColorBlock)
                                {
                                    if(bgAddr==IMAGE_NONE)
                                    {
                                        ((llColor*) pColorBuf)[j]=bgColor;
                                    }
                                    else
                                    {
                                        ((llColor*) pColorBuf)[j]=pImageColor[imgColorCount];
                                    }
                                }
                            }
                            if(bgAddr!=IMAGE_NONE)
                        {
                            imgColorCount++;
                        }
                            break;
                        }
                        case 4:
                        {
                            Bit_Offset=All_Bit_Num%2;
                            Bit_Offset*=4;
                            clolrLevel=GETBIT(buffer[Byte_Num],Bit_Offset);
                            clolrLevel=clolrLevel<<1;
                            clolrLevel+=GETBIT(buffer[Byte_Num],Bit_Offset+1);
                            clolrLevel=clolrLevel<<1;
                            clolrLevel+=GETBIT(buffer[Byte_Num],Bit_Offset+2);
                            clolrLevel=clolrLevel<<1;
                            clolrLevel+=GETBIT(buffer[Byte_Num],Bit_Offset+3);

                            if(((imgColorCount>=imageReadByteMax)||(imgColorCount>=imgColorBufferCount))&&(bgAddr!=IMAGE_NONE))
                            {
                                //读取图片数据
                                imgColorBufferCount=llGeneralImageSpecificAreaRead(&imgReadCount,widget,bgAddr,charGeometryShow,(imageBufferTypedef*)pImageColor);
                                imgColorCount=0;
                            }
                            if(clolrLevel!=0)
                            {
                                /* 字符颜色 */
                                if(isColorBlock)
                                {
                                    ((llColor*) pColorBuf)[j]=fixColor(bgColor,charInfo->charColor,clolrLevel<<4);
                                }
                                else
                                {
                                    llSetPoint( point.x, point.y,fixColor(bgColor,charInfo->charColor,clolrLevel<<4) );
                                }
                            }
                            else
                            {
                                if(isColorBlock)
                                {
                                    if(bgAddr==IMAGE_NONE)
                                    {
                                        ((llColor*) pColorBuf)[j]=bgColor;
                                    }
                                    else
                                    {
                                        ((llColor*) pColorBuf)[j]=pImageColor[imgColorCount];
                                    }
                                }
                            }
                            if(bgAddr!=IMAGE_NONE)
                            {
                                imgColorCount++;
                            }
                            break;
                        }
                        case 8:
                        {
                            clolrLevel=buffer[Byte_Num];

                            if(((imgColorCount>=imageReadByteMax)||(imgColorCount>=imgColorBufferCount))&&(bgAddr!=IMAGE_NONE))
                            {
                                //读取图片数据
                                imgColorBufferCount=llGeneralImageSpecificAreaRead(&imgReadCount,widget,bgAddr,charGeometryShow,(imageBufferTypedef*)pImageColor);
                                imgColorCount=0;
                            }
                            if(clolrLevel!=0)
                            {
                                /* 字符颜色 */
                                if(isColorBlock)
                                {
                                    ((llColor*) pColorBuf)[j]=fixColor(bgColor,charInfo->charColor,clolrLevel);
                                }
                                else
                                {
                                    llSetPoint( point.x, point.y,fixColor(bgColor,charInfo->charColor,clolrLevel) );
                                }
                            }
                            else
                            {
                                if(isColorBlock)
                                {
                                    if(bgAddr==IMAGE_NONE)
                                    {
                                        ((llColor*) pColorBuf)[j]=bgColor;
                                    }
                                    else
                                    {
                                        ((llColor*) pColorBuf)[j]=pImageColor[imgColorCount];
                                    }
                                }
                            }
                            if(bgAddr!=IMAGE_NONE)
                            {
                                imgColorCount++;
                            }
                            break;
                        }
                        default:
                            break;
                        }
                    }
                    xBitCount++;
                    if((xBitCount%(8/dataBits))==0)
                    {
                        uint16_t bbCount=xBitCount/(8/dataBits);
                        if((bbCount%CHAR_BUFFER_BYTE_MAX)==0)
                        {
                            byteCount+=CHAR_BUFFER_BYTE_MAX;
                            llFontGetTinyData(charAddr,buffer,byteCount);
                        }
                    }
                }
                if(isColorBlock)
                {
                    if(bolckWidth!=0)
                    {
                        llFillMultipleColors(x,y+i,x+bolckWidth-1,y+i,pColorBuf);
                    }
                }
            }
        }
    }

    if(llFontGetLibType()==typeBinFile)
    {
        llFree(buffer);
    }
    if(isColorBlock)
    {
        llFree(pColorBuf);
    }
}

llGeometry llCharGetCharPos(llChar* charInitStruct,uint8_t *str,uint16_t offsetStr)
{
    uint16_t w,h;
    uint16_t addWidth=0;
    llGeometry retGeometry={0};
    int16_t x, y;
    int16_t oldX;
    uint16_t offsetCount=0;
    uint8_t utf8_len,i;

    x=charInitStruct->geometry.x;
    y=charInitStruct->geometry.y;
    oldX=x;
    while(*str!=0)
    {
        h= llFontGetHeightSize();
        w=llFontGetWidthSize(str);
        retGeometry.x=x;
        retGeometry.y=y;
        retGeometry.height=h;
        retGeometry.width=w;
        if(charInitStruct->isAutoLineBreak)
        {
            addWidth+=w;
            if(addWidth>charInitStruct->geometry.width)
            {
                addWidth=w;
                y=y+h;
                x=oldX;
            }
        }

        utf8_len=llGetUtf8Len(str);
        for(i=0;i<utf8_len;i++)
        {
            str++;
            offsetCount++;
        }

        x=x+w;
        if(*str=='\n')
        {
            y=y+h;
            x=oldX;
            str++;
        }
        if(offsetCount>offsetStr)
        {
            return retGeometry;
        }
    }
    return retGeometry;
}

void llCharSetText(llGeneral* widget, int16_t x, int16_t y,llChar* charInfo,bool isColorBlock)
{
    //x y 为绝对坐标
    uint16_t w,h;
    int16_t oldX;
    uint16_t addWidth=0;
    uint8_t utf8_len,i;
    uint8_t *str;
    llGeometry recoverGeometry;
    llPoint globalPos;
    
    globalPos=llListGetGlobalPos(widget->parentWidget);
            
    str=charInfo->text;
    oldX=x;
    imageBufferTypedef *imageBuf;
    
    imageBuf=llMalloc(sizeof(imageBufferTypedef));
    
    if(imageBuf==NULL)
    {
        return ;
    }

    //顶部空白刷新
    if(isColorBlock)
    {
        h=globalPos.y+widget->geometry.y+widget->geometry.height-y;
        if((globalPos.y+widget->geometry.y)<y)
        {
            if(!charInfo->isTransparent)
            {
                llFillSingleColor(globalPos.x+widget->geometry.x,globalPos.y+widget->geometry.y,charInfo->geometry.x+charInfo->geometry.width-1,y+h-1,charInfo->backgroundColor);
            }
            else
            {
                recoverGeometry.x=globalPos.x+widget->geometry.x;
                recoverGeometry.y=globalPos.y+widget->geometry.y;
                recoverGeometry.width=charInfo->geometry.x+charInfo->geometry.width-widget->geometry.x-globalPos.x;
                recoverGeometry.height=y-widget->geometry.y-globalPos.y;
                llGeneralWidgetParentRecover((llGeneral*)widget,recoverGeometry);
            }
        }
        
        if((globalPos.x+widget->geometry.x)<x)
        {
            if(!charInfo->isTransparent)
            {
                llFillSingleColor(globalPos.x+widget->geometry.x,y,x-1,y+h-1,charInfo->backgroundColor);
            }
            else
            {
                recoverGeometry.x=globalPos.x+widget->geometry.x;
                recoverGeometry.y=y;
                recoverGeometry.width=x-widget->geometry.x-globalPos.x;
                recoverGeometry.height=h;
                llGeneralWidgetParentRecover((llGeneral*)widget,recoverGeometry);
            }
        }
    }

    while(*str!=0)
    {
        if(*str=='\n')
        {
            h=llFontGetHeightSize();
            if(h>widget->geometry.height)
            {
                h=widget->geometry.height;
            }
            //当前行剩余刷新
            if((x<(charInfo->geometry.x+charInfo->geometry.width))&&(isColorBlock))
            {
                if(!charInfo->isTransparent)
                {
                    llFillSingleColor(x,y,charInfo->geometry.x+charInfo->geometry.width-1,y+h-1,charInfo->backgroundColor);
                }
                else
                {
                    recoverGeometry.x=x;
                    recoverGeometry.y=y;
                    recoverGeometry.width=globalPos.x+widget->geometry.x+widget->geometry.width-x;
                    recoverGeometry.height=h;
                    llGeneralWidgetParentRecover((llGeneral*)widget,recoverGeometry);
                }
            }
            y=y+h;
            x=oldX;
            str++;
            
        }
        else
        {
            w= llFontGetWidthSize(str);
            
        if(charInfo->isAutoLineBreak)
        {
            addWidth+=w;
            if(addWidth>charInfo->geometry.width)
            {
                h=llFontGetHeightSize();
                if(h>widget->geometry.height)
                {
                    h=widget->geometry.height;
                }
                //当前行剩余刷新
                if((x<(charInfo->geometry.x+charInfo->geometry.width))&&(isColorBlock))
                {
                    if(!charInfo->isTransparent)
                    {
                        llFillSingleColor(x,y,charInfo->geometry.x+charInfo->geometry.width-1,charInfo->geometry.y+h-1,charInfo->backgroundColor);
                    }
                    else
                    {
                        recoverGeometry.x=x;
                        recoverGeometry.y=y;
                        recoverGeometry.width=globalPos.x+widget->geometry.x+widget->geometry.width-x;
                        recoverGeometry.height=h;
                        llGeneralWidgetParentRecover((llGeneral*)widget,recoverGeometry);
                    }
                }
                addWidth=w;
                y=y+h;
                x=oldX;
            }
        }

        llCharShowChar(widget,x, y,charInfo,str,isColorBlock,imageBuf);

        utf8_len=llGetUtf8Len(str);
        for(i=0;i<utf8_len;i++)
        {
            str++;
        }

        x=x+w;
    }
        
    }
    
    llFree(imageBuf);

    h=llFontGetHeightSize();
    if(h>widget->geometry.height)
    {
        h=widget->geometry.height;
    }
    //当前行剩余刷新
    if((x<(charInfo->geometry.x+charInfo->geometry.width))&&(isColorBlock))
    {
        if(!charInfo->isTransparent)
        {
            llFillSingleColor(x,y,charInfo->geometry.x+charInfo->geometry.width-1,y+h-1,charInfo->backgroundColor);
        }
        else
        {
            recoverGeometry.x=x;
            recoverGeometry.y=y;
            recoverGeometry.width=globalPos.x+widget->geometry.x+widget->geometry.width-x;
            recoverGeometry.height=h;
            llGeneralWidgetParentRecover((llGeneral*)widget,recoverGeometry);
        }
    }

    x=oldX;
    
    //剩余行刷新
    if(((y+h)<(charInfo->geometry.y+charInfo->geometry.height))&&(isColorBlock))
    {
        if(!charInfo->isTransparent)
        {
            llFillSingleColor(x,y+h,charInfo->geometry.x+charInfo->geometry.width-1,charInfo->geometry.y+charInfo->geometry.height-1,charInfo->backgroundColor);
        }
        else
        {
            recoverGeometry.x=x;
            recoverGeometry.y=y+h;
            recoverGeometry.width=charInfo->geometry.x+charInfo->geometry.width-x;
            recoverGeometry.height=charInfo->geometry.y+charInfo->geometry.height-recoverGeometry.y;
            llGeneralWidgetParentRecover((llGeneral*)widget,recoverGeometry);
        }
    }
}

int16_t llCharCalVerticalPos(llChar* charInitStruct,int16_t textHeight)
{
    int16_t y = 0;

    if(charInitStruct->vAlign==llAlignVCenter)
    {
        y=RECTANGLE_MID_Y_POS(charInitStruct->geometry.y,charInitStruct->geometry.height,textHeight);
    }
    else
    {
        if(charInitStruct->vAlign==llAlignVTop)
        {
            y=charInitStruct->geometry.y;
        }
        else
        {
            if(charInitStruct->vAlign==llAlignVBottom)
            {
                if(charInitStruct->fontLibInfo->fontSize<charInitStruct->geometry.height)//文字高度<显示高度
                {
                    y=RECTANGLE_BUTTOM_Y_POS(charInitStruct->geometry.y,charInitStruct->geometry.height,textHeight);
                }
                else
                {
                    y=charInitStruct->geometry.y;
                }
            }
        }
    }
    return y;
}

int16_t llCharCalHorizontalPos(llChar* charInitStruct,int16_t textWidth)
{
    int16_t x = 0;

    switch (charInitStruct->hAlign)
    {
    case llAlignHCenter:
    {
        //文字长度 text_width
        //显示长度 charInitStruct->width
        if(textWidth<charInitStruct->geometry.width)//文字长度<显示长度
        {
            x=RECTANGLE_MID_X_POS(charInitStruct->geometry.x,charInitStruct->geometry.width,textWidth);
        }
        else
        {
            x=charInitStruct->geometry.x;
        }
        break;
    }
    case llAlignHLeft:
    {
        x=charInitStruct->geometry.x;
        break;
    }
    case llAlignHRight:
    {
        //文字长度 text_width
        //显示长度 charInitStruct->width
        if(textWidth<charInitStruct->geometry.width)//文字长度<显示长度
        {
            x=RECTANGLE_RIGHT_X_POS(charInitStruct->geometry.x,charInitStruct->geometry.width,textWidth);
        }
        else
        {
            x=charInitStruct->geometry.x;
        }
        break;
    }
    default:
        break;
    }
    return x;
}

llGeometry llCharDisplay(llGeneral *widget, llChar* charInitStruct,bool isColorBlock)
{
    uint16_t charLength=0;
    int16_t x,y;
    int16_t textWidth,textHeight,textWidthTemp;
    int16_t charWidth;
    llGeometry realGeometry={0};

    realGeometry.x=charInitStruct->geometry.x;
    realGeometry.y=charInitStruct->geometry.y;

    if(charInitStruct->text==NULL)
    {
        return realGeometry;
    }

    //获取文字书写长度
    charLength=0;
    textWidth=0;
    textWidthTemp=0;
    textHeight=llFontGetHeightSize();

    //计算显示高度宽度
    while(charInitStruct->text[charLength]!=0)
    {
        charWidth=llFontGetWidthSize(&charInitStruct->text[charLength]);

        //处理换行,计算显示高度
        if((charInitStruct->text[charLength]=='\n')||(((textWidthTemp+charWidth)>charInitStruct->geometry.width)&&(charInitStruct->isAutoLineBreak==true)))
        {
            textHeight+=llFontGetHeightSize();
            textWidthTemp=0;
        }

        //计算宽度
        textWidthTemp+=charWidth;

        if(textWidth<textWidthTemp)
        {
            textWidth=textWidthTemp;
        }

        //英文 0x0-0x7F
        if(charInitStruct->text[charLength]>=0x80)
        {
            //utf8 chinese use 3 bytes
            charLength++;
            charLength++;
        }
        charLength++;
    }

    x=llCharCalHorizontalPos(charInitStruct,textWidth);

    y=llCharCalVerticalPos(charInitStruct,textHeight);

    realGeometry.width=textWidth;
    realGeometry.height=textHeight;

    llCharSetText(widget,x,y,charInitStruct,isColorBlock);

    return realGeometry;
}

void llCharDisplayCursor(llPoint pos,uint16_t height,llColor backgroundColor,bool *isShow)
{
    if(*isShow==true)
    {
        *isShow=false;
        llFillSingleColor(pos.x+2,pos.y+1,pos.x+2,pos.y+height-2,0);
    }
    else
    {
        *isShow=true;
        llFillSingleColor(pos.x+2,pos.y+1,pos.x+2,pos.y+height-2,backgroundColor);
    }
}



#define CURSOR_RUN   1
#define CURSOR_STOP   0

static uint8_t cursorBlinkState=CURSOR_STOP;
static uint32_t cursorBlinkCounter;
static llPoint cursorPos;
static uint16_t cursorHeight;
static llColor cursorBackgroundColor;
static bool cursorShow=false;
static void *cursorBlinkWidget=NULL;
static bool *cursorBlinkFlag=NULL;
void llCharSetCursor(void* blinkWidget,bool *enableFlag,int16_t x,int16_t y,uint16_t cursorBlinkHeight,llColor backgroundColor)
{
    cursorBlinkFlag=enableFlag;
    cursorBlinkWidget=blinkWidget;

    cursorPos.x=x;
    cursorPos.y=y;
    cursorHeight=cursorBlinkHeight;
    cursorBackgroundColor=backgroundColor;

    cursorBlinkState=CURSOR_RUN;
    llTimer_start(&cursorBlinkCounter);
    cursorShow=true;
    llCharDisplayCursor(cursorPos,cursorHeight,cursorBackgroundColor,&cursorShow);
}

void llCharAutoStopCursorBlink(void* clickWidget)
{
    if(cursorBlinkWidget!=NULL)
    {
        if(cursorBlinkWidget!=clickWidget)
        {
            llCharStopCursorBlink();
        }
    }
}

void llCharStopCursorBlink(void)
{
    if(cursorBlinkWidget!=NULL)
    {
        llEmitSignal(cursorBlinkWidget,SIGNAL_EIDTING_FINISHED);
        cursorBlinkWidget=NULL;
        cursorBlinkState=CURSOR_STOP;
        cursorBlinkCounter=0;
        cursorShow=false;
        *cursorBlinkFlag=false;
        llCharDisplayCursor(cursorPos,cursorHeight,cursorBackgroundColor,&cursorShow);
    }
}

void llCharCursorBlinkLoop(void)
{
    if(cursorBlinkState==CURSOR_RUN)
    {
        if(llTimer_timeOut(&cursorBlinkCounter,500,true))
        {
            //光标闪烁
            llCharDisplayCursor(cursorPos,cursorHeight,cursorBackgroundColor,&cursorShow);
        }
    }
}

//llPoint llCharGetCursorOffset(llChar* charInitStruct)
//{
//    uint16_t temp=0;
//    uint16_t text_width;
//    llPoint retPos;

//    //获取文字书写长度
//    temp=0;
//    text_width=0;

//    while(charInitStruct->text[temp]!=0)
//    {
//        //英文 0x0-0x7F
//        if(charInitStruct->text[temp]<0x80)
//        {

//            text_width+=llFontGetWidthSize(&charInitStruct->text[temp]);
//        }
//        else
//        {
//            //utf8 chinese use 3 bytes
//            text_width+=llFontGetWidthSize(&charInitStruct->text[temp]);
//            temp++;
//            temp++;
//        }
//        temp++;
//    }

//    if(charInitStruct->vAlign==llAlignVCenter)
//    {
//        retPos.y=text_mid_y_pos(charInitStruct->geometry.y,charInitStruct->geometry.height,charInitStruct->fontSize);
//    }
//    else
//    {
//        if(charInitStruct->vAlign==llAlignVTop)
//        {
//            retPos.y=charInitStruct->geometry.y;
//        }
//        else
//        {
//            if(charInitStruct->vAlign==llAlignVBottom)
//            {
//                if(charInitStruct->fontSize<charInitStruct->geometry.height)//文字高度<显示高度
//                {
//                    retPos.y=text_bottom_y_pos(charInitStruct->geometry.y,charInitStruct->geometry.height,charInitStruct->fontSize);
//                }
//                else
//                {
//                    retPos.y=charInitStruct->geometry.y;
//                }
//            }
//        }
//    }
//    retPos.x=charInitStruct->geometry.x+2;



//    return retPos;
//}







