/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwGlobal.h
* Create: 	10/06/06
* Desc:		SwGlobal类，用于获取全局数据
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef __SWGLOBAL_H__
#define __SWGLOBAL_H__

// class SwTimer;
class SwRender;
// class SwCamera;
//class IPtInput;
class CWorld;
class CNdlWorldPickerBase;
// class UITextureManager;

//namespace PTGUI
//{
	class swLuaScript;
//	class PtUiManager;
//}
//typedef PTGUI::PtUiManager PtCtrlManager;
//typedef PTGUI::LuaScript		LuaScript;


// Input消息定义，消息对应的键值在GameInput初始化时定义
enum EGameInputMessage
{
	// 鼠标输入
	GIM_MOUSELEFTKEY = 0,			// 鼠标左键按下/释放
	GIM_MOUSERIGHTKEY,				// 鼠标右键按下/释放
	GIM_MOUSEROLLUP,				// 鼠标上滚
	GIM_MOUSEROLLDOWN,				// 鼠标下滚
	GIM_MOUSEMOVE,					// 鼠标移动（返回绝对坐标）

	GIM_DISPLAY_COLLISION,			// 显示可行走在上面的碰撞模型
	GIM_DISPLAY_VIEWBLOCK,			// 显示可视遮挡模型
	GIM_DISPLAY_DOODAD,				// 显示和关闭草皮绘制

	// 人物行走消息
	GIM_GO_UP,
	GIM_GO_DOWN,
	GIM_GO_LEFT,
	GIM_GO_RIGHT,

	GIM_SMALLMAP_ZOOMIN,			// 小地图缩小
	GIM_SMALLMAP_ZOOMOUT,			// 小地图放大

	GIM_CANCEL_SELECT,				// 取消人物选中状态

	// 组队测试
	GIM_INVITE_TO_TEAM,				// 邀请入队

	// 键盘输入，可定义组合键消息
	// 界面
	GIM_ITEMPANEL_HIDE_SHOW,		//法术快捷键栏呼出/隐藏
	GIM_ITEMPANEL_SHORTCUT1,		//法术快捷键使用
	GIM_ITEMPANEL_SHORTCUT2,
	GIM_ITEMPANEL_SHORTCUT3,
	GIM_ITEMPANEL_SHORTCUT4,
	GIM_ITEMPANEL_SHORTCUT5,
	GIM_ITEMPANEL_SHORTCUT6,
	GIM_ITEMPANEL_SHORTCUT7,
	GIM_ITEMPANEL_SHORTCUT8,
	GIM_CHARACTOR_PROPERTY,			// 人物属性面板（含技能）
	GIM_FRIEND,						// 好友，师徒面板
	GIM_PET,						// 宠物面板
	GIM_SYSTEM,						// 系统面板
	GIM_FACE_ACTION,				// 表情动作面板
	GIM_PRINTSCEEN,					// 截图
	GIM_HIDE_CHARACTOR,				// 屏蔽所有玩家
	GIM_TEAM,						// 组队面板
	GIM_TASK,						// 任务面板
	GIM_INVENTORY,					// 包裹
	GIM_TRADE,						// 交易
	GIM_GIVE,						// 给予
	GIM_CHAT_FACEPANEL,				// 聊天表情面板
	GIM_HIDE_STALLAGE,				// 屏蔽摆摊招牌
	GIM_REGION_MAP,					// 区域地图
	GIM_WORLD_MAP,					// 世界地图

	// 攻击
	GIM_AUTOATTACK,					// 自动攻击
	GIM_SET_DEFAULSKILL,			// 设置默认法术
	GIM_AUTOUSE_DEFAULTSKILL,		// 自动使用默认法术
	GIM_ATTACK_OPEN_INVENTORY,		// 战斗中打开包裹（执行阶段可使用物品/非执行阶段查看物品）
	GIM_ATTACK_OPEN_SKILL,			// 战斗中打开法术列表
	GIM_ATTACKING_DEFEND,			// 战斗中防御
	GIM_ATTACKING_PROTECT,			// 战斗中保护
	GIM_CATCH_PET,					// 捕捉宠物
	GIM_REPEAT_ATTACKING,			// 战斗中重复上一次操作

	// 快捷键使用技能，在非战斗和战斗中都可选中，然后再判断该技能能否使用
	GIM_SKILL_SHORTCUT1,
	GIM_SKILL_SHORTCUT2,
	GIM_SKILL_SHORTCUT3,
	GIM_SKILL_SHORTCUT4,
	GIM_SKILL_SHORTCUT5,
	GIM_SKILL_SHORTCUT6,
	GIM_SKILL_SHORTCUT7,
	GIM_SKILL_SHORTCUT8,

};

class SwGlobal
{
public:
	SwGlobal();
	virtual			~SwGlobal();

public:
	// added, jiayi, [2010/7/27]
	static void				Initialize();
	static SwRender*		GetRender(){return s_pRender;};
	static void				SetRender(SwRender* render){s_pRender = render;};

// 	static SwCamera*		GetCamera(){return s_pCamera;};
// 	static void				SetCamera(SwCamera* camera){s_pCamera = camera;};

// 	static UITextureManager* GetUITextureManager(){return s_pTexManager;};
// 	static void				SetUITextureManager(UITextureManager* pTexManager){s_pTexManager = pTexManager;};

	//static PtCtrlManager*	GetUiManager()	{return s_pCtrlManager;};
	//static void				SetUiManager(PtCtrlManager* pCtrlManager)	{s_pCtrlManager = pCtrlManager;};

	static void				GetMousePosition(int& nMouseX, int& nMouseY){nMouseX = s_nMousePosX; nMouseY = s_nMousePosY; }
	static void				SetMousePosition(int posX, int posY);				// 设置当前帧的鼠标位置，每帧调用一次
	static void				SetMouseScroll(int mouseZ){s_nMouseZ = mouseZ;};

	static CWorld*			GetWorld(){return s_pWorld;};
	static void				SetWorld(CWorld* world){s_pWorld = world;};

	static CNdlWorldPickerBase*	GetWorldPicker(){return s_pWorldPicker;};
	static void				SetWorldPicker(CNdlWorldPickerBase* pWorldPicker){s_pWorldPicker = pWorldPicker;};

	static bool				IsMouseMoving( int& x, int& y );
	static bool				IsMouseScrolling( int& z );
	static bool				IsKeyDown(WORD wKey);

// 	static void				SetLua(swLuaScript* lua) {s_Lua = lua;}

// 	static SwTimer			s_timer;
	const static D3DXCOLOR	s_globalDefaultFogColor;
// 	static swLuaScript*		s_Lua;
	static float			GetZByXY( float fCurrentZ,float x, float y,DWORD dwFlag, BOOL* bInFloor = NULL, DWORD* pdwRet = NULL, BOOL bIsRole = false, D3DXVECTOR3 *pNormal = NULL);

	// 地图加载进度，值范围为 0.0 - 100.0
	static void				SetLoadProgress(float progress);
	static float			GetLoadProgress() { return s_lLoadProgress / 10.0f; }

protected:
	static SwRender*		s_pRender;
// 	static SwCamera*		s_pCamera;
	static int				s_nMousePosX, s_nMousePosY;			// 记录鼠标位置
	static int				s_nMouseLastPosX, s_nMouseLastPosY;	// 记录鼠标上次update时鼠标位置 
	static int				s_nMouseZ;							// 记录鼠标滚动数据
	static CWorld*			s_pWorld;
// 	static UITextureManager*	s_pTexManager;
	//static PtCtrlManager*		s_pCtrlManager;
	static CNdlWorldPickerBase*	s_pWorldPicker;
	static LONG				s_lLoadProgress;
public:
	static bool				s_SimpleMapLoadMode;
	static int				s_SimpleMapLoadDistance;
};

#endif