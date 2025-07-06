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

    //按键
    llButtonQuickCreate(ID_BUTTON_0,ID_BACKGROUND,70,50,40,20,(uint8_t *)"Button",FONT_LIB_C_ARIAL_9,RGB888(0x000000),RGB888(0x55aaff),RGB888(0x55aaff),0xFFFFFFFF,0xFFFFFFFF,BUTTON_DIS_TYPE_COLOR,false);
    nButtonSetEnabled(ID_BUTTON_0,true);
    nButtonSetCheckable(ID_BUTTON_0,false);
    nButtonSetKeyValue(ID_BUTTON_0,0);

    //按键
    llButtonQuickCreate(ID_BUTTON_1,ID_BACKGROUND,20,50,40,20,(uint8_t *)"Button",FONT_LIB_C_ARIAL_9,RGB888(0x000000),RGB888(0x55aaff),RGB888(0x55aaff),0xFFFFFFFF,0xFFFFFFFF,BUTTON_DIS_TYPE_COLOR,false);
    nButtonSetEnabled(ID_BUTTON_1,true);
    nButtonSetCheckable(ID_BUTTON_1,false);
    nButtonSetKeyValue(ID_BUTTON_1,0);

    llWindowQuickCreate(ID_WINDOW_0,ID_BACKGROUND,0,0,128,128,true,RGB888(0xf0f0f0),NULL,false,false);
    nWindowSetEnabled(ID_WINDOW_0,true);

    //文本
    llTextQuickCreate(ID_TEXT_3,ID_WINDOW_0,20,50,80,30,(uint8_t *)"text",FONT_LIB_C_ARIAL_9,RGB888(0x000000),RGB888(0xffffff),llAlignHLeft,llAlignVTop,0,0,false,false,false);
    nTextSetEnabled(ID_TEXT_3,true);

    llWindowQuickCreate(ID_WINDOW_1,ID_WINDOW_0,0,0,128,128,true,RGB888(0xf0f0f0),NULL,false,false);
    nWindowSetEnabled(ID_WINDOW_1,true);

    //文本
    llTextQuickCreate(ID_TEXT_4,ID_WINDOW_1,30,40,80,30,(uint8_t *)"123",FONT_LIB_C_ARIAL_9,RGB888(0x000000),RGB888(0xffffff),llAlignHLeft,llAlignVTop,0,0,false,false,false);
    nTextSetEnabled(ID_TEXT_4,true);

    //连接
    llConnectSignal(ID_BUTTON_0,SIGNAL_CLICK_PRESSED,ID_TEXT_1,ui_guiAction_Button_0_pressed_Text_1);

    //连接
    llConnectSignal(ID_BUTTON_1,SIGNAL_CLICK_PRESSED,ID_TEXT_2,ui_guiAction_Button_1_pressed_Text_2);

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

