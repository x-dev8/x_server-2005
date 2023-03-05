#pragma once

#include "MeRTLibs.h"
#include <windows.h>
#include <string>

class MouseManager
{
public:
	enum E_CursorType
	{
		Type_Arrow = 0,			// ��ͷ
		Type_Rotate,			// ��ת
		Type_Wait,				// �ȴ�
		Type_LockTarget,		// ����Ŀ��
		Type_Attack,			// ����
		Type_Dialog,			// �Ի�
		Type_Shop,				// �̵�
		Type_Pick,				// ʰ��
		Type_Group,				// ���
		Type_CollectHerb,		// �ɲ�ҩ
		Type_CollectMine,		// �ɿ�
		Type_CollectWood,		// ��ľͷ
		Type_LockItem,			// ��Ʒ����
		Type_UnLockItem,		// ��Ʒ����
		Type_UseItem,			// ʹ����Ʒ
		Type_PathFinding,		// ����Ѱ·
		Type_Destroy,			// ɾ����Ʒ
		Type_Split,				// �����Ʒ
		Type_Repair,			// ����
		Type_LeftDrag,			// �ı�UI��С
		Type_CollectMount,		// ׽���
        Type_MoveFollowMouse,	// ��������ƶ���2.5D�ӽǲ���
        Type_PickItem,			// ʰȡ����
        Type_NpcItem,			// NPC��item����
		Type_MoveWindow,        // �ƶ�����
        Type_ChatHyper,			// ���������Ʒ������
        Type_ChatPlayer,		// ��������������
        Type_CastBomb,			// Ͷ������������
		Type_CheckUp,			// ����
		Type_Decompose,			// �ֽ���Ʒ
		Type_Max
	};

public:
	void LoadCursor();
	void Render();
	void SetCursor( const E_CursorType enType );
	void SetUICursor( const E_CursorType enType );
	void ForceSetCursor() { m_bSetCursor = TRUE; }

	void SetCanSetCursor(bool b) { m_bCanSet = b; }

	E_CursorType GetCursor() { return m_enCurCursor; }
	E_CursorType GetUICursor() { return m_enUICursor; }
	HCURSOR GetCursor( E_CursorType eType ){ return m_hCursor[eType]; }

private:
//	std::string		m_strCursorName[Type_Max];
//	int				m_nCursorPicId[Type_Max];
	HCURSOR			m_hCursor[Type_Max];
	E_CursorType	m_enCurCursor;
	E_CursorType	m_enUICursor;
//	RECT			m_rcDst;
//	RECT			m_rcSrc;
//	int				m_nCurFrame;
	BOOL			m_bSetCursor;

	bool			m_bCanSet;

public:
	MouseManager(void);
	~MouseManager(void);
};

extern MouseManager theMouseManager;
