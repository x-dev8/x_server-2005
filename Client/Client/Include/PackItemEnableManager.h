/*************************************************************************************
        背包内物品 Enable Disable 变换管理器    by zhuomeng.hu		[12/30/2010]
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

    void RefreshAllPackEnables();                                                               // 刷所有背包的Enable态

    void RefreshNormalPackEnables( bool bRefreshPack = true );                                  // 刷普通背包的Enable态
    void RefreshMaterialPackEnables( bool bRefreshPack = true );                                // 刷材料背包的Enable态
    void RefreshTaskPackEnables( bool bRefreshPack = true );                                    // 刷任务背包的Enable态

    void RefreshBagItemEnable( CItemBag2* pBag, int nIndex, bool bRefreshPack = false );        // 刷单格背包的Enable态
	void RefreshBagItemEnable( CItemBag2* pBag, __int64 OnlyID, bool bRefreshPack = false );   

    bool IsPackItemEnable( CItemBag2* pBag, int nIndex );                                       // 背包内物品是否有效

protected:
    void RefreshBagEnables( CItemBag2* pBag );                                                  // 刷指定背包的Enable态
    void RefreshPackIcon( CItemBag2* pBag, int nIndex );                                        // 背包的Icon刷新

private:
    friend class Singleton<CPackItemEnableManager>;
    CPackItemEnableManager();

private:
    std::vector<CItemEnableChangeSysBase*>      m_itemEnableChangeSysVec;

};
