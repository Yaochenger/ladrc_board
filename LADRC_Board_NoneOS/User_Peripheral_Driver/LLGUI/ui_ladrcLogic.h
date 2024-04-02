#ifndef _UI_LADRC_LOGIC_H_
#define _UI_LADRC_LOGIC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "LL_Background.h"
#include "LL_Button.h"
#include "LL_Image.h"
#include "LL_Text.h"
#include "LL_CheckBox.h"
#include "LL_LineEdit.h"
#include "LL_Slider.h"
#include "LL_ProgressBar.h"
#include "LL_Window.h"
#include "LL_QRCode.h"
#include "LL_Gauge.h"
#include "LL_Timer.h"
#include "LL_DateTime.h"
#include "LL_IconSlider.h"
#include "LL_ComboBox.h"
#ifdef USE_LLGUI_EX
#include "LL_Graph.h"
#endif
#include "LL_User.h"

#define ID_BACKGROUND          0x400
#define ID_BUTTON_0          0x401
#define ID_TEXT_0          0x402
#define ID_CHECKBOX_0          0x403
#define ID_LINEEDIT_0          0x404
#define ID_SLIDER_0          0x405
#define ID_PROGRESSBAR_0          0x406

bool ui_ladrcAction_Button_0_pressed_LineEdit_0(llConnectInfo info);

void ui_ladrcLogicInit(void);
void ui_ladrcLogicLoop(void);
void ui_ladrcLogicQuit(void);
#ifdef __cplusplus
}
#endif

#endif //_UI_LADRC_LOGIC_H_

