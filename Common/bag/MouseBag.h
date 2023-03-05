#ifndef __COMMON_MOUSEBAG_H__
#define __COMMON_MOUSEBAG_H__

#pragma once

#include "GlobalDef.h"
#include "ItemDetail.h"

class CMouseBag
{
private:
    SMouseItem* m_pdata;

public:
    CMouseBag();
    ~CMouseBag();

    void	Clear();	//�������
    void	SetMouseItem(SCharItem *pItem);	//��������ϵĵ���
    void	SetMouseItem(SMouseItem *pItem);
    void	SetMouseShortCut(int bag_type, int bag_index);
    void	SetMouseShortCut(SShortCut *pShortCut);////��������ϵĿ��
    bool	GetMouseItem(SCharItem *pItem);	//ȡ������ϵĵ���
    bool	GetMouseItem(SMouseItem *pItem);

    bool	GetMouseItemAndClear(SCharItem *pItem);//ȡ������ϵĵ���,�����������ϵĵ���
    bool	GetMouseBag(SMouseItem *pItem);	//ȡ����걳��
    bool	GetMouseShortCut(SShortCut *pShortCut);//ȡ������ϵĿ��
    bool	GetMouseShortCutAndClear(SShortCut *pShortCut);//ȡ������ϵĿ�ݣ�����������
    bool	IsMouseHaveFactItem();	//�ж�������Ƿ���ʵ���ϵĵ���
    bool	IsMouseHaveShortCut();//�ж�������Ƿ��е��ߵ�����
    bool	CreateFromData( SMouseItem *pMouseData);
};

#endif // __COMMON_MOUSEBAG_H__
