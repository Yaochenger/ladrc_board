#include "ui_gui.h"
#include "ui_guiLogic.h"
#include "LL_General.h"
#include "LL_Gui.h"
#include "LL_Linked_List.h"
#include "LL_Timer.h"
#include "LL_ButtonEx.h"
#ifdef USE_LLGUI_EX
#include "LL_GuiEx.h"
#endif


void ui_guiInit(void)
{
    llDoubleBufferStart(false);
    //背景
    llBackgroundQuickCreate(ID_BACKGROUND,LL_MONITOR_WIDTH,LL_MONITOR_HEIGHT,true,RGB888(0xf1f1f1),0);

    //文本
    llTextQuickCreate(ID_TEXT_0,ID_BACKGROUND,20,10,93,18,(uint8_t *)"LADRC GUI",FONT_LIB_C_ARIAL_10,RGB888(0x5500ff),RGB888(0xffffff),llAlignHLeft,llAlignVTop,0,0,false,true,false);
    nTextSetEnabled(ID_TEXT_0,true);

    //文本
    llTextQuickCreate(ID_TEXT_1,ID_BACKGROUND,40,80,53,19,(uint8_t *)"au:rv",FONT_LIB_C_ARIAL_9,RGB888(0x000000),RGB888(0xffffff),llAlignHLeft,llAlignVTop,0,0,false,true,false);
    nTextSetEnabled(ID_TEXT_1,true);

    //文本
    llTextQuickCreate(ID_TEXT_2,ID_BACKGROUND,40,100,80,20,(uint8_t *)"2024/08/18",FONT_LIB_C_ARIAL_9,RGB888(0x000000),RGB888(0xffffff),llAlignHLeft,llAlignVTop,0,0,false,true,false);
    nTextSetEnabled(ID_TEXT_2,true);

    llDoubleBufferEnd(true);
    ui_guiLogicInit();
}

void ui_guiLoop(void)
{
    ui_guiLogicLoop();
}

void ui_guiQuit(void)
{
    ui_guiLogicQuit();
}

