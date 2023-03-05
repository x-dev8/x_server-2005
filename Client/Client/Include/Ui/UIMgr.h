#pragma once

#include <map>
#include "GlobalDef.h"
#include "MeUi/ControlObject.h"
#include "IconManagerClient.h"
#include "LuaScript.h"
#include "Singleton.h"
#include "MeUi/IconManager.h"
#include "MeUi/ControlIconDrag.h"
#include "UIBase.h"

class CUIMgr :public Singleton<CUIMgr>
{
public:
	void			Init();										    // Init UI Mgr 
	void			Destory();										
// 	void			AddUI( UI_OBJECT_TYPE eType, CUIBase *pObj );	// ��� UI Frame Object
	void			AddUI( CUIBase *pObj );	                        // HoldInMomery ��� UIBase
// 	void			DelUI( UI_OBJECT_TYPE eType );					// Del UI
	void			DelUI( CUIBase *pObj );							// Del UI
// 	CUIBase *		GetUIObject( UI_OBJECT_TYPE eType );			// �õ�UI Frame Object
// 	UI_OBJECT_TYPE  GetUIType( CUIBase* pObject);			        // �õ�UI Type

	void			loadUIs();		// ����״ε�½��Ϸ ������Ϸ��������ʾ����
	void			clearUIs();		// �˳� ���� ���µ�½ �����Ϸ����

//     void            clearUIDatas(); // ���UI�ڲ�ʹ�õ������ݡ�

	void			ShowUIInTimeOfLoadMap(bool bVisible);

	//LuaStateOwner m_LuaScript;

	bool			OnKeyDown( WPARAM wParam, LPARAM lParam );
	bool			OnKeyUp( WPARAM wParam, LPARAM lParam );
	void			setVisableUI(CUIBase *pObj);
	void			ClearHideUI();
    void            AddUIToList( CUIBase* pUI ){m_UIList.push_back(pUI);}     // UIList ��� UIBase
    void            InitAtEnterWorld();
	void			ResetDevice( );
	void			RefreshByItemChange();						// ��Ʒ�ı䵼�µĽ������
	void			RefreshByMoneyChange();			        // ��Ǯ�ı䵼�µĽ������
	static void     RetriveSpareTimeString( S_IconInfoBase* pTip );
	static void     RetriveTimeString( char * szBuffer, COLORREF& colTime, int nDay, int nHour, int nMinute, int nSecond );

	void            ProcessUiShowOrHide(bool bValue,CUIBase *pObject = NULL);

private:
// 	typedef std::map< UI_OBJECT_TYPE, CUIBase* > UIMgr;	
	
	typedef std::list<CUIBase*>					UIBaseList;	
	typedef UIBaseList::iterator				UIBaseIter;
	UIBaseList						m_HoldInMemoryList;
	UIBaseList						m_OtherList;
	UIBaseList						&GetUIList(CUIBase* pUi);
    UIBaseList						m_UIList;

	DWORD							m_UILifeTime;
protected:
	static S_IconInfoBase* CreateIconInfo();
	static bool IconDragGlobalOnMouseMove( ControlIconDrag::S_ListImg* pItem, bool bEnableCompare, const RECT& rcItem, ControlIconDrag* pThis );
// 	static bool FindPlayerHyper(const std::wstring& wstrParse, std::wstring& wstrPlayer);
};

//---------------------------------------------------------------------------------------------------------
//��������������������freme��λ��
extern void SetContainRect(IN OUT RECT& lhs, IN RECT& rhs);
extern RECT GetBigRect(ControlFrame* pFrame);
extern void ResetWindowPosition(ControlFrame* pLeft, ControlFrame* pRight);
extern void ResetWindowPositionEx(ControlFrame* pLeft, ControlFrame* pMiddle, ControlFrame* pRight);
//---------------------------------------------------------------------------------------------------------

extern TNativeFun GNativeFun[];
extern int g_GetNativeFunNum();

extern IScript *GetLuaScript();
extern CUIMgr *GetUIScriptMgr();

#define USE_SCRIPT( type, p ) 
#define CLOSE_SCRIPT( pUI ) 

enum UI_Callback_Type
{
	eItem_UI_Callback = 0,
	eMount_UI_Callback,
	eQuestId_UI_Callback,
	eNpcId_UI_Callback,
	eMapId_UI_Callback,
	eExipTip_UI_Callback,
	eMore_UI_Callback,			// ExitTip�ϵ�����������
	eSkill_UI_Callback,			//������ʾ���ܻص�
	eTask_UI_Callback,
	ePet_UI_Callback
};


















