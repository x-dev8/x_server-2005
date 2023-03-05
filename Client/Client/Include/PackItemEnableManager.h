/*************************************************************************************
        ��������Ʒ Enable Disable �任������    by zhuomeng.hu		[12/30/2010]
*************************************************************************************/

#pragma once

#include "Singleton.h"
#include "ItemEnableChangeSysBase.h"
#include "bag/ItemBag2.h"

class CPackItemEnableManager : public Singleton<CPackItemEnableManager>
{
public:
    ~CPackItemEnableManager();
    bool AddItemEnableChangeSys( CItemEnableChangeSysBase* pObject );
    bool RemoveItemEnableChangeSys( CItemEnableChangeSysBase* pObject );

    void RefreshAllPackEnables();                                                               // ˢ���б�����Enable̬

    void RefreshNormalPackEnables( bool bRefreshPack = true );                                  // ˢ��ͨ������Enable̬
    void RefreshMaterialPackEnables( bool bRefreshPack = true );                                // ˢ���ϱ�����Enable̬
    void RefreshTaskPackEnables( bool bRefreshPack = true );                                    // ˢ���񱳰���Enable̬

    void RefreshBagItemEnable( CItemBag2* pBag, int nIndex, bool bRefreshPack = false );        // ˢ���񱳰���Enable̬
	void RefreshBagItemEnable( CItemBag2* pBag, __int64 OnlyID, bool bRefreshPack = false );   

    bool IsPackItemEnable( CItemBag2* pBag, int nIndex );                                       // ��������Ʒ�Ƿ���Ч

protected:
    void RefreshBagEnables( CItemBag2* pBag );                                                  // ˢָ��������Enable̬
    void RefreshPackIcon( CItemBag2* pBag, int nIndex );                                        // ������Iconˢ��

private:
    friend class Singleton<CPackItemEnableManager>;
    CPackItemEnableManager();

private:
    std::vector<CItemEnableChangeSysBase*>      m_itemEnableChangeSysVec;

};
