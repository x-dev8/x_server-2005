#pragma once

#pragma warning(disable:4996)

/*
* ��Ӧ�ó���󶨵�����Visual C++ ��ĵ�ǰ�汾
*/
#define _BIND_TO_CURRENT_VCLIBS_VERSION 1

// Windows Header Files
#include <Windows.h>
#include <DbgHelp.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// C++ STL Header Files
#include <map>

// TODO: reference additional headers your program requires here

// wxWidgets Header Files
#include "wx/wx.h"

/*
* �ؼ�id
*/
enum eWindowCtrlIds
{
	IDC_MAIN_TOOLBAR = wxID_HIGHEST + 1,
	IDC_CHOOSE_DIR_BTN,
};

#define MEXVIEWER_FRAME_WND_TIMER_ID		1000