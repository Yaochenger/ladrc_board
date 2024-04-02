#include "LL_User.h"
#include "ui_ladrc.h"
#include "Arial_9.h"
#ifdef USE_LLGUI_EX
#include "LL_GuiEx.h"
#endif

uint8_t userPageMax=PAGE_MAX;
uint8_t userFontLibTotalNum=FONT_LIB_TOTAL_NUM;

llFontLib userFontLibList[FONT_LIB_TOTAL_NUM]={
    {typeCFile,"Arial_9",9,&Arial_9_Lib}
};

void (*pageInitFunc[PAGE_MAX])(void);
void (*pageLoopFunc[PAGE_MAX])(void);
void (*pageQuitFunc[PAGE_MAX])(void);

void llUserInit(void)
{
    pageInitFunc[0]=ui_ladrcInit;

    pageLoopFunc[0]=ui_ladrcLoop;

    pageQuitFunc[0]=ui_ladrcQuit;

};

uint16_t llUserGetAngle(void)
{
    return LL_LCD_ANGLE;
}
