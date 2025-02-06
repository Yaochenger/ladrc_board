/*
 * Copyright 2021-2024 Ou Jianbo 59935554@qq.com
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
 * must be released under GPL compatible free software license or commercial license.
*/

#include "LL_ZkBin.h"

static llLatticeLibraryInfo * latticeActiveFont;

void llZkBinFontOpenLibrary(llLatticeLibraryInfo * libPointer)
{
    latticeActiveFont=libPointer;
}

void llZkBinFontCloseLibrary(void)
{
    if(latticeActiveFont!=NULL)
    {
        latticeActiveFont=NULL;
    }
}

void llZkBinFontGetData(uint8_t * utf8In,uint8_t *dataBits, uint32_t *addr, uint16_t *retWidth, uint16_t *retHeight)
{
    uint8_t unicode[2]={0};
    uint32_t fontCount,i;
    uint8_t ret;

    ret=llUtf8ToUnicode(unicode,utf8In);

    if(ret!=0)
    {
        //查找unicode

        fontCount=latticeActiveFont->totalCharNum;
        *dataBits=latticeActiveFont->dataBits;

        for(i=0;i<fontCount;i++)
        {
            if(ret==1)
            {
                if((latticeActiveFont->dataInfo[i].unicodeL==unicode[0])&&(latticeActiveFont->dataInfo[i].unicodeH==0))
                {
                    *retHeight=latticeActiveFont->dataInfo[i].height;
                    *retWidth=latticeActiveFont->dataInfo[i].width;
                    *addr=latticeActiveFont->dataInfo[i].dataAddr;
                    break;
                }
            }
            else
            {
                if((latticeActiveFont->dataInfo[i].unicodeL==unicode[1])&(latticeActiveFont->dataInfo[i].unicodeH==unicode[0]))
                {
                    *retHeight=latticeActiveFont->dataInfo[i].height;
                    *retWidth=latticeActiveFont->dataInfo[i].width;
                    *addr=latticeActiveFont->dataInfo[i].dataAddr;
                    break;
                }
            }


        }
    }
}

uint8_t llZkBinFontGetWidthSize(uint8_t * utf8In)
{
    unsigned char unicode[2]={0};
    uint32_t fontCount,i;
    uint8_t ret;

    ret=llUtf8ToUnicode(unicode,utf8In);

    if(ret!=0)
    {
        //查找unicode

        fontCount=latticeActiveFont->totalCharNum;

        for(i=0;i<fontCount;i++)
        {
            if(ret==1)
            {
                if((latticeActiveFont->dataInfo[i].unicodeL==unicode[0])&&(latticeActiveFont->dataInfo[i].unicodeH==0))
                {
                    return latticeActiveFont->dataInfo[i].width;
                }
            }
            else
            {
                if((latticeActiveFont->dataInfo[i].unicodeL==unicode[1])&&(latticeActiveFont->dataInfo[i].unicodeH==unicode[0]))
                {
                    return latticeActiveFont->dataInfo[i].width;
                }
            }

        }
    }
    return 0;
}

uint8_t llZkBinFontGetHeightSize(void)
{
    return (uint8_t)latticeActiveFont->dataInfo[0].height;
}

void llZkBinGetTinyData(uint32_t allBitNum,uint32_t *byteNum,uint8_t *word,uint8_t *dataBits, uint16_t *width, uint16_t *height,uint8_t* outBuf,uint16_t *byteCount)
{
//CHAR_BUFFER_BYTE_MAX
}



