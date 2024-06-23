#ifndef _UI_GUI_LOGIC_H_
#define _UI_GUI_LOGIC_H_

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


void ui_guiLogicInit(void);
void ui_guiLogicLoop(void);
void ui_guiLogicQuit(void);
#ifdef __cplusplus
}
#endif

#endif //_UI_GUI_LOGIC_H_

