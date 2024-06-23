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

    //按键
    llButtonQuickCreate(ID_BUTTON_0,ID_BACKGROUND,20,50,80,30,(uint8_t *)"Button",FONT_LIB_C_ARIAL_9,RGB888(0x000000),RGB888(0x55aaff),RGB888(0x55aaff),0xFFFFFFFF,0xFFFFFFFF,BUTTON_DIS_TYPE_COLOR,false);
    nButtonSetEnabled(ID_BUTTON_0,true);
    nButtonSetCheckable(ID_BUTTON_0,false);
    nButtonSetKeyValue(ID_BUTTON_0,0);

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

