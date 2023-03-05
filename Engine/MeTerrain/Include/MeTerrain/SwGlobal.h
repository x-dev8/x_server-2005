/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwGlobal.h
* Create: 	10/06/06
* Desc:		SwGlobal�࣬���ڻ�ȡȫ������
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


// Input��Ϣ���壬��Ϣ��Ӧ�ļ�ֵ��GameInput��ʼ��ʱ����
enum EGameInputMessage
{
	// �������
	GIM_MOUSELEFTKEY = 0,			// ����������/�ͷ�
	GIM_MOUSERIGHTKEY,				// ����Ҽ�����/�ͷ�
	GIM_MOUSEROLLUP,				// ����Ϲ�
	GIM_MOUSEROLLDOWN,				// ����¹�
	GIM_MOUSEMOVE,					// ����ƶ������ؾ������꣩

	GIM_DISPLAY_COLLISION,			// ��ʾ���������������ײģ��
	GIM_DISPLAY_VIEWBLOCK,			// ��ʾ�����ڵ�ģ��
	GIM_DISPLAY_DOODAD,				// ��ʾ�͹رղ�Ƥ����

	// ����������Ϣ
	GIM_GO_UP,
	GIM_GO_DOWN,
	GIM_GO_LEFT,
	GIM_GO_RIGHT,

	GIM_SMALLMAP_ZOOMIN,			// С��ͼ��С
	GIM_SMALLMAP_ZOOMOUT,			// С��ͼ�Ŵ�

	GIM_CANCEL_SELECT,				// ȡ������ѡ��״̬

	// ��Ӳ���
	GIM_INVITE_TO_TEAM,				// �������

	// �������룬�ɶ�����ϼ���Ϣ
	// ����
	GIM_ITEMPANEL_HIDE_SHOW,		//������ݼ�������/����
	GIM_ITEMPANEL_SHORTCUT1,		//������ݼ�ʹ��
	GIM_ITEMPANEL_SHORTCUT2,
	GIM_ITEMPANEL_SHORTCUT3,
	GIM_ITEMPANEL_SHORTCUT4,
	GIM_ITEMPANEL_SHORTCUT5,
	GIM_ITEMPANEL_SHORTCUT6,
	GIM_ITEMPANEL_SHORTCUT7,
	GIM_ITEMPANEL_SHORTCUT8,
	GIM_CHARACTOR_PROPERTY,			// ����������壨�����ܣ�
	GIM_FRIEND,						// ���ѣ�ʦͽ���
	GIM_PET,						// �������
	GIM_SYSTEM,						// ϵͳ���
	GIM_FACE_ACTION,				// ���鶯�����
	GIM_PRINTSCEEN,					// ��ͼ
	GIM_HIDE_CHARACTOR,				// �����������
	GIM_TEAM,						// ������
	GIM_TASK,						// �������
	GIM_INVENTORY,					// ����
	GIM_TRADE,						// ����
	GIM_GIVE,						// ����
	GIM_CHAT_FACEPANEL,				// ����������
	GIM_HIDE_STALLAGE,				// ���ΰ�̯����
	GIM_REGION_MAP,					// �����ͼ
	GIM_WORLD_MAP,					// �����ͼ

	// ����
	GIM_AUTOATTACK,					// �Զ�����
	GIM_SET_DEFAULSKILL,			// ����Ĭ�Ϸ���
	GIM_AUTOUSE_DEFAULTSKILL,		// �Զ�ʹ��Ĭ�Ϸ���
	GIM_ATTACK_OPEN_INVENTORY,		// ս���д򿪰�����ִ�н׶ο�ʹ����Ʒ/��ִ�н׶β鿴��Ʒ��
	GIM_ATTACK_OPEN_SKILL,			// ս���д򿪷����б�
	GIM_ATTACKING_DEFEND,			// ս���з���
	GIM_ATTACKING_PROTECT,			// ս���б���
	GIM_CATCH_PET,					// ��׽����
	GIM_REPEAT_ATTACKING,			// ս�����ظ���һ�β���

	// ��ݼ�ʹ�ü��ܣ��ڷ�ս����ս���ж���ѡ�У�Ȼ�����жϸü����ܷ�ʹ��
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
	static void				SetMousePosition(int posX, int posY);				// ���õ�ǰ֡�����λ�ã�ÿ֡����һ��
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

	// ��ͼ���ؽ��ȣ�ֵ��ΧΪ 0.0 - 100.0
	static void				SetLoadProgress(float progress);
	static float			GetLoadProgress() { return s_lLoadProgress / 10.0f; }

protected:
	static SwRender*		s_pRender;
// 	static SwCamera*		s_pCamera;
	static int				s_nMousePosX, s_nMousePosY;			// ��¼���λ��
	static int				s_nMouseLastPosX, s_nMouseLastPosY;	// ��¼����ϴ�updateʱ���λ�� 
	static int				s_nMouseZ;							// ��¼����������
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