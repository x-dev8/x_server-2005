#ifndef __COMMON_HOTKEYBAG_H__
#define __COMMON_HOTKEYBAG_H__

#pragma once

#include "GlobalDef.h"

class CHotkeyBag
{
public:
	CHotkeyBag();
	~CHotkeyBag();

	// ��ʼ��
	void CreateFromData( SMouseItem* pHotkeyData, int iBagSize );

	//���ÿ��
	bool PushItem( SMouseItem &item, short stIndex=-1 );
	//ȡ�����
	bool ClearItem( short stIndex );

	//��ȡָ����ݵ���Ϣ
	bool GetHotkey( short stIndex, SMouseItem *pHotkey );

	//����ָ��Hotkey�Ŀ����Ϣ
	void SetShortCut( int iHotKeyIndex, int iBagType, int iBagIndex );

	//��ȡָ��������״��...�жϸ�λ������
	bool IsHaveHotkey( short stIndex );
	bool IsHaveFactItem( short stIndex );
	bool CHotkeyBag::IsHaveShortCut( short stIndex );

	//���ָ�������Ŀ��
	bool ClearHotkey( short stIndex );
	//���ָ��ָ������,�����Ŀ��
	void ClearSpecialHotkey( int bag_type, int index );
	
	bool	GetHotKeyCanClear( short stIndex, SMouseItem *pHotkey );
	//{ add by ^^
	int		PopItem( SCharItem &item,unsigned short &ustCount );
	int		GetItemCount( int iItemID );
	//} add by ^^

private:

	//��һ���յ�λ��
	int  FindNullHotkeyOffSet( );

	//�����������Ŀ
	int	 m_iBagSize;
	//��ݵ�����ָ��
	SMouseItem *m_pHotkeyData;
};

#endif // __COMMON_HOTKEYBAG_H__
