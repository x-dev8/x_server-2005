#pragma once

#pragma warning(disable:4996)

/*
* 将应用程序绑定到所有Visual C++ 库的当前版本
*/
#define _BIND_TO_CURRENT_VCLIBS_VERSION 1

// Windows Header Files
#include <Windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// C++ STL Header Files
#include <map>

// TODO: reference additional headers your program requires here
#include <d3d9.h>

// wxWidgets Header Files
#include "wx/wx.h"
#include "wx/snglinst.h"
#include "wx/spinctrl.h"
#include "wx/statline.h"
#include "wx/gbsizer.h"
#include "wx/dirctrl.h"
#include "wx/slider.h"
#include "wx/treectrl.h"
#include "wx/colordlg.h"
#include "wx/aboutdlg.h"
#include "wx/progdlg.h"
#include "wx/artprov.h"
#include "wx/numdlg.h"
#include "wx/tipdlg.h"
#include "wx/clntdata.h"
#include "wx/config.h"
#include "wx/dnd.h"
#include "wx/filename.h"
#include "wx/spinctrl.h"
#include "wx/statline.h"
#include "wx/dcmemory.h"
#include "wx/generic/aboutdlgg.h"
#include "wx/ribbon/bar.h"
#include "wx/ribbon/page.h"
#include "wx/ribbon/toolbar.h"
#include "wx/ribbon/buttonbar.h"
#include "wx/propgrid/propgrid.h"
#include "wx/propgrid/advprops.h"

// Me3d Header Files
#include "MeUtility/MeRTLibs.h"

#include "Me3d/Include.h"
#include "Me3d/Utility.h"
#include "Me3d/D3dutil.h"
#include "Me3d/Camera.h"
#include "Me3d/ShaderManager.h"
#include "Me3d/ShaderMgr.h"
#include "Me3d/Model/MexRes.h"
#include "Me3d/Model/MexAnimCtrl.h"
#include "Me3d/Model/MexGeoChunk.h"
#include "Me3d/Model/Mex2.h"
#include "Me3d/Effect/MexEffectCtrl.h"
#include "Me3d/PostProcess/PostProcess.h"
#include "Me3d/PostProcess/PostProcessManager.h"
#include "Me3d/Engine/EngineInstance.h"
#include "Me3d/Engine/MeRenderManager.h"
#include "Me3d/Engine/MeBitSorter.h"
#include "Me3d/Engine/MeShimmerCollector.h"
#include "Me3d/Engine/MeAlphaCollector.h"
#include "Me3d/Engine/RendererDX.h"
#include "Me3d/Engine/TextureDx8.h"
#include "Me3d/Effect/MexEffectCtrl.h"

#include "MeTerrain/NiColor.h"
#include "MeTerrain/SwType.h"
#include "MeTerrain/SwDebug.h"
#include "MeTerrain/STCommon.h"
#include "MeUtility/Singleton.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/SwPublicFunc.h"
#include "MeTerrain/HashTable.h"
#include "MeTerrain/MapFile.h"
#include "MeTerrain/MapUtil.h"
#include "MeTerrain/World.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/WorldTile.h"
#include "MeTerrain/WorldChunk.h"
#include "MeTerrain/NdlRes.h"
#include "MeTerrain/NdlResMgr.h"

/*
* 控件id
*/
enum eWindowCtrlIds
{
	IDC_MAIN_TOOLBAR = wxID_HIGHEST + 1,
	IDC_SHOW_MENU_SHOW_SKELETON,
	IDC_SHOW_MENU_SHOW_AABB,
	IDC_SHOW_MENU_SHOW_GRID,
	IDC_SHOW_MENU_SHOW_WIREFRAME,
	IDC_SHOW_MENU_SHOW_HELPER,
	IDC_SHOW_MENU_HIDE_ALL_HELPER,
	IDC_SHOW_MENU_SHOW_FLOOR,
	IDC_SHOW_MENU_SHOW_SUPER_FLOOR,
	IDC_SHOW_MENU_SHOW_COLLISION,
	IDC_SHOW_MENU_SHOW_ALPHA_BOX,
	IDC_SHOW_MENU_SHOW_RIBBON_PANELS,
	IDC_SHOW_MENU_SHOW_LEFTWND,
	IDC_SHOW_MENU_SHOW_RIGHTWND,
	IDC_EFFECT_MENU_BLOOM,
	IDC_EFFECT_MENU_LIGHT_SHAFT,
	IDC_SCENE_MENU_LIGHT_COLOR_AMBIENT,
	IDC_SCENE_MENU_LIGHT_COLOR_DIFFUSE,
	IDC_SCENE_MENU_LIGHT_COLOR_SPECULAR,
	IDC_SCENE_MENU_LIGHT_COLOR_DEFAULT,
	IDC_SCENE_MENU_BACKGROUND_COLOR,
	IDC_HELP_MENU_HELP,
	IDC_HELP_MENU_ABOUT,
	IDC_RIBBON_BAR,
	IDC_LEFT_WND_DIR_CTRL,
	IDC_LEFT_WND_MENU_COPY_FILENAME,
	IDC_LEFT_WND_MENU_FILE_RENAME,
	IDC_LEFT_WND_MENU_BROWSER_FILE,	
	IDC_MODEL_INFO_PG,
	IDC_MODEL_INFO_MEXCONF_TREE,
	IDC_MODEL_INFO_ADD_SKIN,
	IDC_MODEL_INFO_SKIN_RENAME,
	IDC_MODEL_INFO_DEL_SKIN,
	IDC_PARTICLE_EDIT_PG,
	IDC_BTN_SMALLER,
	IDC_BTN_LARGER,
	IDC_BTN_SAVEMEX,
	IDC_RIGHT_WND_PARTICLES_CHOICE,
	IDC_RIGHT_WND_PART_EMITTER_EXPORT_BTN,
	IDC_AVATAR_BTN_HAT,
	IDC_AVATAR_BTN_HAIR,
	IDC_AVATAR_BTN_FACE,
	IDC_AVATAR_BTN_SHOULDER,
	IDC_AVATAR_BTN_CLOTHES,
	IDC_AVATAR_BTN_WAISTBAND,
	IDC_AVATAR_BTN_RIGHT_HAND,
	IDC_AVATAR_BTN_GLOVE,
	IDC_AVATAR_BTN_LEFT_HAND,
	IDC_AVATAR_BTN_SHIELD,
	IDC_AVATAR_BTN_TROUSERS,
	IDC_AVATAR_BTN_SHOES,
	IDC_NEW_ANIM_DLG_NAME_EDIT,
	IDC_NEW_ANIM_DLG_START_SPIN,
	IDC_NEW_ANIM_DLG_END_SPIN,
	IDC_NEW_ANIM_DLG_HIT_POINT_SPIN,
	IDC_ANIM_WND_TOTAL_FRM_STATIC,
	IDC_ANIM_WND_ANIM_LIST_BOX,
	IDC_ANIM_WND_LIGHT_TRACK_CHECK_BOX,
	IDC_ANIM_WND_NAME_EDIT,
	IDC_ANIM_WND_START_SPIN,
	IDC_ANIM_WND_END_SPIN,
	IDC_ANIM_WND_HIT_POINT_SPIN,
	IDC_ANIM_WND_ONE_LOOP_TIME_SLIDER,
	IDC_ANIM_WND_ADD_BTN,
	IDC_ANIM_WND_DEL_BTN,
	IDC_ANIM_WND_SAVE_ANI_BTN,
	IDC_ANIM_WND_IMPORT_ANI_TEMP_BTN,
	IDC_ANIM_WND_EXPORT_ANI_TEMP_BTN,
	IDC_FRAME_WND_SLIDER,
	IDC_FRAME_WND_PREV_BTN,
	IDC_FRAME_WND_PLAY_PAUSE_BTN,
	IDC_FRAME_WND_NEXT_BTN,
	IDC_FRAME_WND_ENTER_FRM_BTN,
	IDC_FRAME_WND_MODELCONFIG_OUT_BTN,
};

#define MEXVIEWER_FRAME_WND_TIMER_ID		1000