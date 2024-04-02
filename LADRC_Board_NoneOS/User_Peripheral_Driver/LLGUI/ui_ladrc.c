#include "ui_ladrc.h"
#include "ui_ladrcLogic.h"
#include "LL_General.h"
#include "LL_Gui.h"
#include "LL_Linked_List.h"
#include "LL_Timer.h"
#include "LL_ButtonEx.h"
#ifdef USE_LLGUI_EX
#include "LL_GuiEx.h"
#endif


void ui_ladrcInit(void)
{
    llDoubleBufferStart(false);
    //背景
    llBackgroundQuickCreate(ID_BACKGROUND,LL_MONITOR_WIDTH,LL_MONITOR_HEIGHT,true,RGB888(0xf1f1f1),0);

    //按键
    llButtonQuickCreate(ID_BUTTON_0,ID_BACKGROUND,0,0,69,22,(uint8_t *)"Button",FONT_LIB_C_ARIAL_9,RGB888(0x000000),RGB888(0x55aaff),RGB888(0xff0000),0xFFFFFFFF,0xFFFFFFFF,BUTTON_DIS_TYPE_COLOR,false);
    nButtonSetEnabled(ID_BUTTON_0,true);
    nButtonSetCheckable(ID_BUTTON_0,true);
    nButtonSetKeyValue(ID_BUTTON_0,0);

    //文本
    llTextQuickCreate(ID_TEXT_0,ID_BACKGROUND,0,30,66,18,(uint8_t *)"text",FONT_LIB_C_ARIAL_9,RGB888(0x000000),RGB888(0xffffff),llAlignHLeft,llAlignVTop,0,0,false,false,false);
    nTextSetEnabled(ID_TEXT_0,true);

    llCheckBoxQuickCreate(ID_CHECKBOX_0,ID_BACKGROUND,0,50,98,18,(uint8_t *)"Check Box",FONT_LIB_C_ARIAL_9,RGB888(0x000000),false,false);
    nCheckBoxSetEnabled(ID_CHECKBOX_0,true);

    llLineEditQuickCreate(ID_LINEEDIT_0,ID_BACKGROUND,0,70,109,16,(uint8_t *)"LADERC",FONT_LIB_C_ARIAL_9,RGB888(0x000000),NULL,false);
    nLineEditSetKeyboard(ID_LINEEDIT_0,0);
    nLineEditSetEnabled(ID_LINEEDIT_0,true);
    nLineEditPasswordEnable(ID_LINEEDIT_0,false);

    llSliderQuickCreate(ID_SLIDER_0,ID_BACKGROUND,0,90,84,22,RGB888(0xbcbcbc),RGB888(0x2e90dd),RGB888(0xffffff),NULL,NULL,NULL,true,1,false);
    nSliderSetAutoMove(ID_SLIDER_0,true);
    nSliderSetEnabled(ID_SLIDER_0,true);


    llProgressBarQuickCreate(ID_PROGRESSBAR_0,ID_BACKGROUND,70,0,53,20,FONT_LIB_C_ARIAL_9,RGB888(0x000000),RGB_CONVERT(230,230,230),RGB_CONVERT(6,176,37),0,true,false);
    nProgressBarSetEnabled(ID_PROGRESSBAR_0,true);
    nProgressBarSetPercent(ID_PROGRESSBAR_0,10);


    //连接
    llConnectSignal(ID_BUTTON_0,SIGNAL_CLICK_PRESSED,ID_LINEEDIT_0,ui_ladrcAction_Button_0_pressed_LineEdit_0);

    llDoubleBufferEnd(true);
    ui_ladrcLogicInit();
}

void ui_ladrcLoop(void)
{
    ui_ladrcLogicLoop();
}

void ui_ladrcQuit(void)
{
    ui_ladrcLogicQuit();
}

