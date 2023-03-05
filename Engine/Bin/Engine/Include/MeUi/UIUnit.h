#pragma once

#include "MeUi/MeUi.h"
#include "MeUi/UiManager.h"

class CUILoadMgrBase;
class CUIUnit : public MeCommonAllocObj<CUIUnit>
{
public:
				CUIUnit();
				virtual ~CUIUnit();
public:
	bool		IsUILoad() const { return m_bUILoad; }
	virtual bool	IsHoldInMemory() const { return false; }
	virtual bool	LoadUI();									
	virtual bool	UnLoadUI();									// ж��UI
	virtual bool	IsVisable();								// �Ƿ�ɼ�
	virtual void	SetVisable( const bool bVisable );			// �����Ƿ����
    virtual void	InitializeAtEnterWorld(){}			        // ÿ�ε�½��Ϸ���õ��߼�
	virtual void	RefreshByItemChange(){}						// ��Ʒ�ı䵼�µĽ������
	virtual void	RefreshByMoneyChange(){}			        // ��Ǯ�ı䵼�µĽ������
	DWORD			GetLastVisibleTime() const { return m_LastVisibleTime; }
	void			SetLastVisibleTime(DWORD val) { m_LastVisibleTime = val; }
	virtual void	ResetDevice( ){;}
	
	static			CUILoadMgrBase* GetUIMgr() {return m_uiLoadMgr;}
	static			CUILoadMgrBase* m_uiLoadMgr;
protected:
	bool		m_bUILoad;
	DWORD				m_BornTime;
	DWORD				m_LastVisibleTime;
	virtual bool _LoadUI() = 0;									// ����UI
	virtual bool	DoControlConnect() = 0;							// �����ؼ�
	virtual bool	_UnLoadUI() = 0;									// ж��UI
	virtual bool	_IsVisable() = 0;								// �Ƿ�ɼ�
	virtual void	_SetVisable( const bool bVisable );			// �����Ƿ����

};

class CUINotManagedByUIMgr : public CUIUnit
{
public:
	CUINotManagedByUIMgr()
	{
	}
	virtual bool	LoadUI(){m_bUILoad = _LoadUI(); return m_bUILoad;}									
	virtual void	SetVisable( const bool bVisable ){_SetVisable(bVisable);}			// ����������������Ϊ�˲�����uimgr�Ĺ���
};

class MexAnimCtrl;
#define UI_LAYOUT_1		1
#define UI_LAYOUT_2		2
#define UI_LAYOUT_3		3
#define UI_LAYOUT_4		4
