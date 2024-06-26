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

#ifndef _LL_ZKBIN_H_
#define _LL_ZKBIN_H_

#include "LL_General.h"


void llZkBinFontOpenLibrary(llLatticeLibraryInfo * libPointer);
//void llZkBinFontCloseLibrary(void);
void llZkBinFontGetData(uint8_t * utf8In, uint8_t *dataBits, uint32_t *addr, uint16_t *retWidth, uint16_t *retHeight);
uint8_t llZkBinFontGetWidthSize(uint8_t * utf8In);
uint8_t llZkBinFontGetHeightSize(void);

void llZkBinGetTinyData(uint32_t allBitNum,uint32_t *byteNum,uint8_t *word,uint8_t *dataBits, uint16_t *width, uint16_t *height,uint8_t* outBuf,uint16_t *byteCount);





#endif //_LL_ZKBIN_H_
