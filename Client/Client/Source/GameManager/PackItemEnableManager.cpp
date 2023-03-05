/*************************************************************************************
        ��������Ʒ Enable Disable �任������    by zhuomeng.hu		[12/30/2010]
*************************************************************************************/

#include "PackItemEnableManager.h"
#include "Pack.h"
#include "PlayerRole.h"

CPackItemEnableManager::CPackItemEnableManager()
{
    m_itemEnableChangeSysVec.clear();
}

CPackItemEnableManager::~CPackItemEnableManager()
{
    m_itemEnableChangeSysVec.clear();
}

bool CPackItemEnableManager::AddItemEnableChangeSys( CItemEnableChangeSysBase* pObject )
{
    std::vector<CItemEnableChangeSysBase*>::iterator it = m_itemEnableChangeSysVec.begin();
    for( ; it != m_itemEnableChangeSysVec.end(); ++it )
    {
        if( *it == pObject )
        {
            return false;
        }
    }
    m_itemEnableChangeSysVec.push_back( pObject );
    return true;
}

bool CPackItemEnableManager::RemoveItemEnableChangeSys( CItemEnableChangeSysBase* pObject )
{
    std::vector<CItemEnableChangeSysBase*>::iterator it = m_itemEnableChangeSysVec.begin();
    for( ; it != m_itemEnableChangeSysVec.end(); ++it )
    {
        if( *it == pObject )
        {
            m_itemEnableChangeSysVec.erase( it );
            return true;
        }
    }
    return false;
}

void CPackItemEnableManager::RefreshAllPackEnables()
{
    RefreshNormalPackEnables();
    RefreshMaterialPackEnables();
    RefreshTaskPackEnables();
}

void CPackItemEnableManager::RefreshNormalPackEnables( bool bRefreshPack )
{
    RefreshBagEnables( &thePlayerRole.m_bag );
    if( bRefreshPack )
    {
        s_CUI_ID_FRAME_PACK.RefreshNormalPack();
    }
}

void CPackItemEnableManager::RefreshMaterialPackEnables( bool bRefreshPack )
{
    RefreshBagEnables( &thePlayerRole.m_bagMaterial );
    if( bRefreshPack )
    {
        s_CUI_ID_FRAME_PACK.RefreshMaterialPack();
    }
}

void CPackItemEnableManager::RefreshTaskPackEnables( bool bRefreshPack )
{
    RefreshBagEnables( &thePlayerRole.m_bagTask );
    if( bRefreshPack )
    {
        s_CUI_ID_FRAME_PACK.RefreshTaskPack();
    }
}

void CPackItemEnableManager::RefreshBagEnables( CItemBag2* pBag )
{
    if( !pBag )
        return;

    int nNormalBagSize = pBag->GetNowBagSize();
    for( int i = 0; i < nNormalBagSize; ++i )
    {
        RefreshBagItemEnable( pBag, i );
    }
}
void CPackItemEnableManager::RefreshBagItemEnable( CItemBag2* pBag, __int64 OnlyID, bool bRefreshPack)
{
	if( !pBag )
        return;
	for(int i =0;i< pBag->GetNowBagSize() ;++i)
	{
		SCharItem charItem;
		if(pBag->GetItem(i,&charItem) && charItem.GetItemGuid() == OnlyID && charItem.GetItemID() != InvalidLogicNumber)
		{
			std::vector<CItemEnableChangeSysBase*>::iterator it = m_itemEnableChangeSysVec.begin();
			for( ; it != m_itemEnableChangeSysVec.end(); ++it )
			{
				if( ( *it )->IsPackItemBeUsing( OnlyID ) )
				{
					pBag->m_bEnables[i] = false;
					if( bRefreshPack )
					{
						RefreshPackIcon( pBag,i);
					}
					return;
				}
			}

			// ����Ʒ����δ�������ûҵ�ϵͳʹ��
			pBag->m_bEnables[i] = true;
			if( bRefreshPack )
			{
				RefreshPackIcon( pBag, i );
			}
			return;
		}
	}
}
void CPackItemEnableManager::RefreshBagItemEnable( CItemBag2* pBag, int nIndex, bool bRefreshPack )
{
    if( !pBag )
        return;

    if( nIndex < 0 || nIndex >= pBag->GetNowBagSize() )
        return;

    // û�д���Ʒ�����λ����Enable��
    if( !pBag->IsHaveItem( nIndex ) )
    {
        pBag->m_bEnables[nIndex] = true;
        if( bRefreshPack )
        {
            RefreshPackIcon( pBag, nIndex );
        }
        return;
    }

    // ȡ��λ����Ʒ��Guid
    SCharItem charItem;
    if( !pBag->GetItem( nIndex, &charItem ) )
    {
        pBag->m_bEnables[nIndex] = true;
        if( bRefreshPack )
        {
            RefreshPackIcon( pBag, nIndex );
        }
        return;
    }
    __int64 nGuid = charItem.GetItemGuid();

    // �����������ܸı���ƷEnable̬��ϵͳ���Ƿ��н����û�
    std::vector<CItemEnableChangeSysBase*>::iterator it = m_itemEnableChangeSysVec.begin();
    for( ; it != m_itemEnableChangeSysVec.end(); ++it )
    {
        if( ( *it )->IsPackItemBeUsing( nGuid ) )
        {
            pBag->m_bEnables[nIndex] = false;
            if( bRefreshPack )
            {
                RefreshPackIcon( pBag, nIndex );
            }
            return;
        }
    }

    // ����Ʒ����δ�������ûҵ�ϵͳʹ��
    pBag->m_bEnables[nIndex] = true;
    if( bRefreshPack )
    {
        RefreshPackIcon( pBag, nIndex );
    }
}

void CPackItemEnableManager::RefreshPackIcon( CItemBag2* pBag, int nIndex )
{
    if( !pBag )
        return;

    if( pBag == &thePlayerRole.m_bag )
    {
        s_CUI_ID_FRAME_PACK.RefreshNormalPackByIndex( nIndex );
    }
    else if( pBag == &thePlayerRole.m_bagMaterial )
    {
        s_CUI_ID_FRAME_PACK.RefreshMaterialPackByIndex( nIndex );
    }
    else if( pBag == &thePlayerRole.m_bagTask )
    {
        s_CUI_ID_FRAME_PACK.RefreshTaskPackByIndex( nIndex );
    }
}

bool CPackItemEnableManager::IsPackItemEnable( CItemBag2* pBag, int nIndex )
{
    // Ĭ�ϵ���Ʒ������Ч�ģ���true
    if( !pBag )
        return true;

    if( nIndex < 0 || nIndex >= pBag->GetNowBagSize() )
        return true;

    return pBag->m_bEnables[nIndex];
}
