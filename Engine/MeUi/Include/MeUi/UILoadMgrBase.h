#pragma once

#include <map>
#include "MeUtility/Singleton.h"
#include "MeUi/IconManager.h"
#include "MeUi/ControlIconDrag.h"
#include "MeUi/UIUnit.h"

class CUILoadMgrBase 
{
public:
	virtual void			Init();										    // Init UI Mgr 
	void			Destory();										
	void			AddUI( CUIUnit *pObj );	                        // HoldInMomery ��� UIBase
	void			DelUI( CUIUnit *pObj );							// Del UI

	void			loadUIs();		// ����״ε�½��Ϸ ������Ϸ��������ʾ����
	virtual void			clearUIs();		// �˳� ���� ���µ�½ �����Ϸ����


	virtual void			ShowUIInTimeOfLoadMap(bool bVisible) = 0;


	virtual bool			OnKeyDown( WPARAM wParam, LPARAM lParam ) = 0;
	virtual bool			OnKeyUp( WPARAM wParam, LPARAM lParam ) = 0;
	void			ClearHideUI();
    void            AddUIToList( CUIUnit* pUI ){m_UIList.push_front(pUI);}     // UIList ��� UIBase
    virtual void            InitAtEnterWorld();
	void			ResetDevice( );
	void			RefreshByItemChange();						// ��Ʒ�ı䵼�µĽ������
	void			RefreshByMoneyChange();			        // ��Ǯ�ı䵼�µĽ������
private:
	
	typedef std::list<CUIUnit*>					UIBaseList;	
	typedef UIBaseList::iterator				UIBaseIter;
	UIBaseList						m_HoldInMemoryList;
	UIBaseList						m_OtherList;
	UIBaseList						&GetUIList(CUIUnit* pUi);
    UIBaseList						m_UIList;

	DWORD							m_UILifeTime;
};

//---------------------------------------------------------------------------------------------------------
//��������������������freme��λ��
extern void SetContainRect(IN OUT RECT& lhs, IN RECT& rhs);
extern RECT GetBigRect(ControlFrame* pFrame);
extern void ResetWindowPosition(ControlFrame* pLeft, ControlFrame* pRight);
//---------------------------------------------------------------------------------------------------------






