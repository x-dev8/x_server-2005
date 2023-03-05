/********************************************************************
Created by UIEditor.exe
FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\Soul.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "EquipEvolve.h"
#include "Pack.h"
#include "NetworkInput.h"
#include "PlayerRole.h"
#include "Core/Name.h"
#include "XmlStringLanguage.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "MeUI/ExpressionManager.h"
#include "ShowScreenText.h"
#include "color_config.h"
#include "IconManagerClient.h"
#include "Common.h"
#include "StarLevelUpConfig.h"
#include "PackItemEnableManager.h"
#include "MessageBox.h"
#include "Star.h"

EquipEvolveUI::EquipEvolveUI()
{
    ResetUIObjects();
    m_bStartAnim = false;
	m_bIsPocket = false;
}
void EquipEvolveUI::SetAtomVisible( bool bVisible )
{
}
void EquipEvolveUI::RefreshAllBagEnable()
{
    if( !m_pID_FRAME_EquipEvolve )
        return;
    // 颜色ui全灰
    SetAtomVisible( false );
    if( m_stEquipBagIndex != -1 )
    {
        if( m_bEquipBagEnable )
        {
            m_stEquipBagGuid = 0;
        }
        if (m_stEquipBagType == BT_MaterialBag)
        {
            // 刷背包物品 Enable 态统一流程     modified by zhuomeng.hu		[12/30/2010]
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stEquipBagIndex, true );
        }
        else
        {
            // 刷背包物品 Enable 态统一流程     modified by zhuomeng.hu		[12/30/2010]
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_stEquipBagIndex, true );
        }
        SetAtomVisible( true );
        if (m_bEquipBagEnable)
        {
            m_stEquipBagIndex = -1;
        }
    }

    for (int i = 0; i < m_nsMaxMaterialNum;++i)
    {
        if( m_stMaterialIndex[i] != -1 )
        {
            if (m_bMaterialBagEnable[i])
            {
                m_n64MaterialGuid[i] = 0;
            }

            // 刷背包物品 Enable 态统一流程     modified by zhuomeng.hu		[12/30/2010]
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stMaterialIndex[i], true );
            if (m_bMaterialBagEnable[i])
            {
                m_stMaterialIndex[i] = -1;
                m_shMaterialBagType[i] = -1;
            }
        }

    }

}


// 是否可视
bool EquipEvolveUI::_IsVisable()
{
    return m_pID_FRAME_EquipEvolve->IsVisable();
}
void EquipEvolveUI::_SetVisable( const bool bVisable )
{
    OnSetVisable(bVisable);

}

bool EquipEvolveUI::UpdateGem()
{
	int nMatchMaterialEnableCount = 0; 

	if (s_CUI_ID_FRAME_Star.IsVisable())
	{
		if( !m_pID_FRAME_EquipEvolve )
			return false;
		if( !IsVisable() )
			return false;
		if(m_pID_LISTIMG_Material == NULL)
		{
			return false;
		}
		ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( m_stEquipBagType, m_stEquipBagIndex );
		if( !pItemImg )
			return false;
		SCharItem* pEquipItem = (SCharItem*)pItemImg->m_pkIconInfo->GetData();
		if (!pEquipItem)
			return false;

		if (m_nSelectMaterialIndex == -1 || m_nSelectMaterialIndex >= m_nsMaxMaterialNum)
			return false;

		m_pID_LISTIMG_Material->Clear();
		m_pID_TEXT_T3->SetVisable(false);

		unsigned short usMaterialId = m_MatchMaterialArray[m_nSelectMaterialIndex];
		//int nMatchMaterialEnableCount = 0; 
		int nBagIndex = -1;
		nBagIndex = m_stMaterialIndex[m_nSelectMaterialIndex];
		/*ControlIconDrag::S_ListImg * pListImgItem = RetriveMaterialImg(m_MatchMaterialArray[m_nSelectMaterialIndex],nBagIndex);*/
		ControlIconDrag::S_ListImg * pListImgItem = s_CUI_ID_FRAME_PACK.GetItemByIndex( BT_MaterialBag, nBagIndex );
		SCharItem* pMaterialItem = (SCharItem*)pListImgItem->m_pkIconInfo->GetData();
		if (pListImgItem && pMaterialItem && pMaterialItem->GetItemID() > 0)
		{
			assert(nBagIndex != -1);
			m_stMaterialIndex[m_nSelectMaterialIndex] = nBagIndex;
			m_n64MaterialGuid[m_nSelectMaterialIndex] = pListImgItem->m_pkIconInfo->GetOnlyId();
			m_shMaterialBagType[m_nSelectMaterialIndex] = BT_MaterialBag;
			m_pID_LISTIMG_Material->SetItem( pListImgItem, /*nMatchMaterialCount*/0 );
			ControlIconDrag::S_ListImg* pNewImg = m_pID_LISTIMG_Material->GetItemByIndex( /*nMatchMaterialCount*/ 0);
			if (pNewImg)
			{
				pNewImg->m_pkIconInfo->Count() = pListImgItem->m_pkIconInfo->Count();
				pNewImg->m_eEnable = eIcon_Enable;
				m_pSelectItem = pNewImg;
				m_bMaterialBagEnable[m_nSelectMaterialIndex] = false;
				++nMatchMaterialEnableCount;
				SetCheckNumBox(pNewImg->m_pkIconInfo->Count());
			}

			 SetTip3Show(pEquipItem, usMaterialId);
		}

		if (!nMatchMaterialEnableCount )
		{
			m_nSelectMaterialIndex = -1;
			for (int i = 0; i < m_nsMaxMaterialNum; ++i)
			{
				m_n64MaterialGuid[i] = 0;
				m_stMaterialIndex[i] = -1;
				m_shMaterialBagType[i] = -1;
			}
		}

		for (int i = 0; i < m_nsMaxMaterialNum; ++i)
		{
			// enable原材料的icon
			if( m_stMaterialIndex[i] != -1 )
			{
				//m_n64MaterialGuid[i] = 0;

				// 刷背包物品 Enable 态统一流程     modified by zhuomeng.hu		[12/30/2010]
				CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stMaterialIndex[i], true );
				/*m_stMaterialIndex[i] = -1;
				m_shMaterialBagType[i] = -1;*/
			}
		}
	}
	else
	{
		int nLastItemId = -1;
		if (m_nSelectMaterialIndex != -1)
		{
		    nLastItemId = m_stMaterialIndex[m_nSelectMaterialIndex];
		    m_nSelectMaterialIndex = -1;
		}
		for (int i = 0; i < m_nsMaxMaterialNum;++i)
		{
		    // enable原材料的icon
		    if( m_stMaterialIndex[i] != -1 )
		    {
		        m_n64MaterialGuid[i] = 0;

		        // 刷背包物品 Enable 态统一流程     modified by zhuomeng.hu		[12/30/2010]
		        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stMaterialIndex[i], true );

		        m_stMaterialIndex[i] = -1;
		        m_shMaterialBagType[i] = -1;
		    }
		}
		m_pID_LISTIMG_Material->Clear();
		ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( m_stEquipBagType, m_stEquipBagIndex );
		if( !pItemImg )
		    return false;
		ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemImg->m_pkIconInfo->GetItemId() );
		if( !pItemCommon )
		    return false;
		ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
		if( !pCanEquip )
		    return false;

		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if ( !pMe )
		{
		    return false;
		}
		int nMeLevel = pMe->GetLevel();
		int nMatchMaterialCount = 0; 
		//int nMatchMaterialEnableCount = 0; 
		for (int i = 0; i < m_MatchMaterialArray.size(); ++i)
		{
		    ItemDefine::SCreateMaterial* pMaterial = ( ItemDefine::SCreateMaterial* )GettheItemDetail().GetItemByID(m_MatchMaterialArray[i]);
		    if( pMaterial->levelLowLimit <= pCanEquip->stEquipLevelReq && pMaterial->levelUpLimit >= pCanEquip->stEquipLevelReq //符合装备等级
		        && pMaterial->useLevel <= nMeLevel																				//符合人物等级
		        && ((pMaterial->equipQuality == 0) || (pMaterial->equipQuality == pCanEquip->ustLevel))							//符合装备品质
		        && pMaterial->CanEquipPart(pCanEquip->ustEquipType)																//符合部位需求
		        && IsMatchOther(pMaterial))																						//符合其他条件，比如打孔的孔数
		    {
		        int nBagIndex = -1;
		        ControlIconDrag::S_ListImg * pListImgItem = RetriveMaterialImg(m_MatchMaterialArray[i],nBagIndex);
		        ControlIconDrag::S_ListImg ImgItem;
		        if (NULL == pListImgItem)
		        {
		            ImgItem.SetData(m_MatchMaterialArray[i],1,eIcon_Disable);
		            pListImgItem = &ImgItem;
		            m_pID_LISTIMG_Material->SetItem( pListImgItem, nMatchMaterialCount );
		        }
		        else
		        {
		            assert(nBagIndex != -1);
		            m_stMaterialIndex[nMatchMaterialCount] = nBagIndex;
		            m_n64MaterialGuid[nMatchMaterialCount] = pListImgItem->m_pkIconInfo->GetOnlyId();
		            m_shMaterialBagType[nMatchMaterialCount] = BT_MaterialBag;
		            m_pID_LISTIMG_Material->SetItem( pListImgItem, nMatchMaterialCount );
		            ControlIconDrag::S_ListImg* pNewImg = m_pID_LISTIMG_Material->GetItemByIndex( nMatchMaterialCount );
		            if (pNewImg)
		            {
		                pNewImg->m_pkIconInfo->Count() = pListImgItem->m_pkIconInfo->Count();
		                pNewImg->m_eEnable = eIcon_Enable;
		                m_pSelectItem = pNewImg;
		                m_nSelectMaterialIndex = nMatchMaterialCount;
		                m_bMaterialBagEnable[nMatchMaterialCount] = false;
		                ++nMatchMaterialEnableCount;
		            }
		        }			
		        ++nMatchMaterialCount;
		        if (nMatchMaterialCount >= m_nsMaxMaterialNum)
		        {
		            break;
		        }
		    }
		}
		if (nLastItemId != -1)
		{
		    for (int i = 0; i <m_nsMaxMaterialNum; ++i)
		    {
		        if (m_stMaterialIndex[i] == nLastItemId)
		        {
		            m_pSelectItem = m_pID_LISTIMG_Material->GetItemByIndex( i );
		            m_nSelectMaterialIndex = i;
		        }
		    }
		}
	}

    TipVisible(nMatchMaterialEnableCount > 0);
	//RefreshAllBagEnable();
    RefreshNeedMoney();
	RefreshProbability();
    SetDirty( true );

    return true;
}

bool EquipEvolveUI::OnMaterialDragOn( ControlIconDrag::S_ListImg* pItemDrag, ControlObject* pSender ,short	stEquipBagType)
{
	if( !m_pID_FRAME_EquipEvolve )
		return false;
	if( !IsVisable() )
		return false;
	if( !m_pID_LISTIMG_Material )
		return false;
	ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( m_stEquipBagType, m_stEquipBagIndex );
	if( !pItemImg )
		return false;
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemImg->m_pkIconInfo->GetItemId() );
	if( !pItemCommon )
		return false;
	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if( !pCanEquip )
		return false;
	SCharItem* pEquipItem = (SCharItem*)pItemImg->m_pkIconInfo->GetData();
	if (!pEquipItem)
		return false;

	unsigned short usMaterialId = pItemDrag->m_pkIconInfo->GetItemId();
	bool bflag = false;
	int nMatchMaterialCount = 0; 

	 for (int i = 0; i < m_MatchMaterialArray.size() && i < m_nsMaxMaterialNum; ++i)
	 {
		if (m_MatchMaterialArray[i] == usMaterialId)
		{
			bflag = true;
			break;
		}
		++nMatchMaterialCount;
	 }
	 if (!bflag)
	 {
		 //该材料不能升星
		 return false;
	 }

	 m_pID_LISTIMG_Material->Clear();
	 m_pID_TEXT_T3->SetVisable(false);
	 if (pItemImg)
	 {
		SetTip3Show(pEquipItem, usMaterialId);
	 }

	if (m_nSelectMaterialIndex != -1)
		m_nSelectMaterialIndex = -1;
	for (int i = 0; i < m_nsMaxMaterialNum; ++i)
	{
		// enable原材料的icon
		if( m_stMaterialIndex[i] != -1 )
		{
			m_n64MaterialGuid[i] = 0;

			// 刷背包物品 Enable 态统一流程     modified by zhuomeng.hu		[12/30/2010]
			CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stMaterialIndex[i], true );

			m_stMaterialIndex[i] = -1;
			m_shMaterialBagType[i] = -1;
		}
	}

	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
	if ( !pMe )
	{
		return false;
	}
	int nMeLevel = pMe->GetLevel();
	int nMatchMaterialEnableCount = 0; 

	ItemDefine::SCreateMaterial* pMaterial = ( ItemDefine::SCreateMaterial* )GettheItemDetail().GetItemByID(usMaterialId);
	if( pMaterial && pMaterial->levelLowLimit <= pCanEquip->stEquipLevelReq && pMaterial->levelUpLimit >= pCanEquip->stEquipLevelReq //符合装备等级
		&& pMaterial->useLevel <= nMeLevel																				//符合人物等级
		&& ((pMaterial->equipQuality == 0) || (pMaterial->equipQuality == pCanEquip->ustLevel))							//符合装备品质
		&& pMaterial->CanEquipPart(pCanEquip->ustEquipType)																//符合部位需求
		&& IsMatchOther(pMaterial))	
	{
		int nBagIndex = -1;
		/*ControlIconDrag::S_ListImg * pListImgItem = RetriveMaterialImg(usMaterialId,nBagIndex);*/
		nBagIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem(BT_MaterialBag, pItemDrag);
		ControlIconDrag::S_ListImg * pListImgItem = pItemDrag;
		if (pListImgItem)
		{
			assert(nBagIndex != -1);
			m_stMaterialIndex[nMatchMaterialCount] = nBagIndex;
			m_n64MaterialGuid[nMatchMaterialCount] = pListImgItem->m_pkIconInfo->GetOnlyId();
			m_shMaterialBagType[nMatchMaterialCount] = BT_MaterialBag;
			m_pID_LISTIMG_Material->SetItem( pListImgItem, /*nMatchMaterialCount*/0 );
			ControlIconDrag::S_ListImg* pNewImg = m_pID_LISTIMG_Material->GetItemByIndex( /*nMatchMaterialCount*/ 0);
			if (pNewImg)
			{
				pNewImg->m_pkIconInfo->Count() = pListImgItem->m_pkIconInfo->Count();
				pNewImg->m_eEnable = eIcon_Enable;
				m_pSelectItem = pNewImg;
				m_nSelectMaterialIndex = nMatchMaterialCount;
				m_bMaterialBagEnable[nMatchMaterialCount] = false;
				++nMatchMaterialEnableCount;
				SetCheckNumBox(pNewImg->m_pkIconInfo->Count());
			}
		}
	}

	TipVisible(nMatchMaterialEnableCount > 0);
	RefreshNeedMoney();
	RefreshProbability();
	SetDirty( true );

	return true;
}

void EquipEvolveUI::SetTip3Show(SCharItem* pEquipItem, unsigned short usMaterialId)
{
	if (!pEquipItem || !usMaterialId)
		return;
	if (!m_pID_TEXT_T3 || !m_pID_TEXT_T4)
		return;

	if (pEquipItem->equipdata.ucLevel >= 6 && pEquipItem->equipdata.ucLevel < 12)
	{
		if (usMaterialId == m_MatchMaterialArray[0])
			m_pID_TEXT_T3->SetVisable(true);
	}
	else if (pEquipItem->equipdata.ucLevel >= 12 && pEquipItem->equipdata.ucLevel < 15)
	{
		if (usMaterialId <= m_MatchMaterialArray[1])
			m_pID_TEXT_T3->SetVisable(true);
	}
	else if (pEquipItem->equipdata.ucLevel >= 15)
	{
		if (usMaterialId <= m_MatchMaterialArray[2])
			m_pID_TEXT_T3->SetVisable(true);
	}

	if (m_pID_TEXT_T3->IsVisable())
		m_pID_TEXT_T4->SetVisable(false);
	else
		m_pID_TEXT_T4->SetVisable(true);
}

void EquipEvolveUI::ClearEquip()
{
    if( !m_pID_FRAME_EquipEvolve )
        return;
    m_bEquipBagEnable = true;				
    m_pID_LISTIMG_Equip->Clear();
    for (int i = 0; i < m_nsMaxMaterialNum;++i)
    {
        if( m_stMaterialIndex[i] != -1 )
        {
            m_bMaterialBagEnable[i] = true;
        }
    }
    if(m_pID_LISTIMG_Material)
    {
        m_pID_LISTIMG_Material->Clear();
    }
    if (m_pID_TEXT_Money)
    {
        m_pID_TEXT_Money->SetText("");
    }
	if ( m_pID_TEXT_SuccessRatio )
	{
		m_pID_TEXT_SuccessRatio->SetText("");
	}
	if (m_pID_CHECKBOX_X1 && m_pID_CHECKBOX_X2 && m_pID_CHECKBOX_X3 && m_pID_CHECKBOX_X4)
	{
		m_pID_CHECKBOX_X1->SetEnable(true);
		m_pID_CHECKBOX_X2->SetEnable(true);
		m_pID_CHECKBOX_X3->SetEnable(true);
		m_pID_CHECKBOX_X4->SetEnable(true);
	}
	if (m_pID_CHECKBOX_Protect_NoUse /*&& m_pID_CHECKBOX_Protect_SixStar && m_pID_CHECKBOX_Protect_NineStar
		&& m_pID_CHECKBOX_Protect_TwelStar && m_pID_CHECKBOX_Protect_FiftStar*/)
	{
		m_pID_CHECKBOX_Protect_NoUse->SetEnable(true);
		/*m_pID_CHECKBOX_Protect_SixStar->SetEnable(true);
		m_pID_CHECKBOX_Protect_NineStar->SetEnable(true);
		m_pID_CHECKBOX_Protect_TwelStar->SetEnable(true);
		m_pID_CHECKBOX_Protect_FiftStar->SetEnable(true);*/
	}
    m_pSelectItem = NULL;
    m_nSelectMaterialIndex = -1;
    SetDirty(true);
}
void EquipEvolveUI::RefreshEquipInfo()
{
    if( !m_pID_FRAME_EquipEvolve )
        return;
    if (m_stEquipBagIndex != -1)
    {
        ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( m_stEquipBagType, m_stEquipBagIndex );
        if( !pItemImg || pItemImg->IsNull())
        {
            ClearEquip();
            return;
        }

        _RefreshEquipInfo( pItemImg );
    }

}

void EquipEvolveUI::_RefreshEquipInfo( ControlIconDrag::S_ListImg* pListImg )
{
    if( !m_pID_FRAME_EquipEvolve )
        return;
    m_pID_LISTIMG_Equip->Clear();
    m_pID_LISTIMG_Equip->SetItem( pListImg, 0 );
    m_pID_LISTIMG_Equip->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;
    m_pID_LISTIMG_Equip->GetItemByIndex( 0 )->m_eEnable = eIcon_Enable;	

}
short EquipEvolveUI::GetItemMaterialType( unsigned short ustId )
{
    if (!m_pID_FRAME_EquipEvolve)
        return false;
    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( ustId );
    if( pItemCommon && pItemCommon->ucItemType == ItemDefine::ITEMTYPE_MATERIAL )
    {
        ItemDefine::SCreateMaterial* pMaterial = ( ItemDefine::SCreateMaterial* )pItemCommon;	
        return pMaterial->stMaterialType;			
    }
    return -1;
}
void EquipEvolveUI::RefreshNeedMoney(   )
{
    int nMoney = GetEvolveMoneyCost();
    if (nMoney <= 0)
    {
		if (m_pID_TEXT_Money)
		{
			m_pID_TEXT_Money->SetText("");
		}
        return;
    }
    std::string text = "";
    thePlayerRole.GetGSCStringFromJiaoZi(nMoney, text);
    DWORD dwColor = 0xffffffff;
    if(!thePlayerRole.HaveEnoughMoney(nMoney))
    {
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_StarLEvolveNoMomeny), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true);
        dwColor = 0xffff0000;
    }
	if (m_pID_TEXT_Money)
	{
		m_pID_TEXT_Money->SetText(text,dwColor);
	}	
}

void EquipEvolveUI::RefreshProbability()
{
	if (m_pID_TEXT_SuccessRatio)
		m_pID_TEXT_SuccessRatio->SetText("");

	float prob = GetEvolveProbability();
	ControlIconDrag::S_ListImg* pItemImg = NULL;
	if (m_pID_LISTIMG_Material)
		pItemImg = m_pID_LISTIMG_Material->GetItemByIndex( /*m_nSelectMaterialIndex*/0 );
	if (pItemImg &&  !pItemImg->IsNull() && s_CUI_ID_FRAME_Star.IsVisable())
	{
		ItemDefine::SCreateMaterial* pMaterial = ( ItemDefine::SCreateMaterial* )GettheItemDetail().GetItemByID(pItemImg->m_pkIconInfo->Id());
		if (pMaterial && m_pID_LISTIMG_Equip)
		{
			SCharItem* pEquipItem = (SCharItem*)m_pID_LISTIMG_Equip->GetItemByIndex( 0 )->m_pkIconInfo->GetData();
			if (pEquipItem)
			{
				uint8 unStar = pEquipItem->equipdata.ucLevel;
				prob += (pMaterial->fAddIntensifyRate[unStar] / 100 * m_stMaterialUseNum);
				if (prob >= 1.0f)
					prob = 1.0f;
			}

			if ( m_pID_TEXT_SuccessRatio )
			{
				int nProb = int(prob * 100);
				char tmpStr[32] = {};
				MeSprintf( tmpStr, sizeof(tmpStr)/sizeof(char) - 1, "%d%%", nProb );
				m_pID_TEXT_SuccessRatio->SetText(tmpStr);
			}
		}
	}
	else if(!s_CUI_ID_FRAME_Star.IsVisable())
	{
		if ( m_pID_TEXT_SuccessRatio )
		{
			int nProb = int(prob * 100);
			char tmpStr[32] = {};
			MeSprintf( tmpStr, sizeof(tmpStr)/sizeof(char) - 1, "%d%%", nProb );
			m_pID_TEXT_SuccessRatio->SetText(tmpStr);
		}
	}
}

void EquipEvolveUI::RefreshOkButton()
{
    if( !m_pID_FRAME_EquipEvolve )
        return;
    if(!IsVisable())
        return;
	//if (!m_pID_BUTTON_Ok->IsEnable())
	//{
	//	return;
	//}
    RefreshBeginPic();
    if (NULL != m_pID_TEXT_TipAllDone)
    {
        m_pID_TEXT_TipAllDone->SetVisable(false);
    }

    
    if( m_stEquipBagIndex == -1 )
    {
        m_pID_BUTTON_Ok->SetEnable( false );
        return;
    }
    ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
    if(!pImg || pImg->IsNull())
    {
        m_pID_BUTTON_Ok->SetEnable( false );
        return;
    }
    if (ProcessAllDone(pImg))
    {
        m_pID_BUTTON_Ok->SetEnable( false );
        return;
    }

    if (m_nSelectMaterialIndex == -1)
    {
        m_pID_BUTTON_Ok->SetEnable( false );
        return;
    }

    int nNeedMoney = GetEvolveMoneyCost();
    if (nNeedMoney == -1)
    {
        m_pID_BUTTON_Ok->SetEnable( false );
        return;
    }

    if(!thePlayerRole.HaveEnoughMoney(nNeedMoney))
    {
        m_pID_BUTTON_Ok->SetEnable(false);
        return;
    }

	m_pID_BUTTON_Ok->SetEnable( true );
    return;
}

int EquipEvolveUI::GetItemLevel(unsigned short ustItemID )
{
    if(ustItemID < 0)
        return -1;

    ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID(ustItemID);
    if(!pItemCommon)
        return -1;

    ItemDefine::SItemCanEquip *pCanEquip = (ItemDefine::SItemCanEquip*)pItemCommon;
    if(!pCanEquip)
        return -1;

    return pCanEquip->stEquipLevelReq;
}

void EquipEvolveUI::ResetUIObjects()
{
    // Member
    m_pID_FRAME_EquipEvolve = NULL;
    m_pID_TEXT_Money = NULL;
    m_pID_LISTIMG_Material = NULL;
    m_pID_BUTTON_Cancel = NULL;
    m_pID_BUTTON_Ok = NULL;
    m_pID_PICTURE_Begin = NULL;
    m_pID_LISTIMG_Equip = NULL;

	m_pID_TEXT_Effect = NULL;
	m_pID_TEXT_Success = NULL;
	m_pID_TEXT_Fail = NULL;
	m_status = EffectStatus_No;
	dwBeginTime = 0;
	m_bSendMsg = false;

    m_bNeedUpdate = false;

    m_stEquipBagIndex = -1;
    m_stEquipBagGuid = 0;
    m_bEquipBagEnable = true;

    for (int i = 0; i < m_nsMaxMaterialNum;++i)
    {
        m_shMaterialBagType[i] = -1;
        m_stMaterialIndex[i] = -1;  
        m_n64MaterialGuid[i] = 0;
        m_bMaterialBagEnable[i] = true;
    }
    m_pSelectItem = NULL;
    m_nSelectMaterialIndex = -1;

	m_pID_CHECKBOX_X1 = NULL;
	m_pID_CHECKBOX_X2 = NULL;
	m_pID_CHECKBOX_X3 = NULL;
	m_pID_CHECKBOX_X4 = NULL;
	m_pID_CHECKBOX_Protect_NoUse = NULL;
	m_pID_CHECKBOX_Protect_SixStar = NULL;
	m_pID_CHECKBOX_Protect_NineStar = NULL;
	m_pID_CHECKBOX_Protect_TwelStar = NULL;
	m_pID_CHECKBOX_Protect_FiftStar = NULL;
	m_pID_TEXT_MaterialNum = NULL;
	m_pID_TEXT_ProtectMaterial = NULL;
	m_pID_TEXT_T3 = NULL;
	m_pID_TEXT_T4 = NULL;

	m_stMaterialUseNum = 1;
	m_unProtectStarNum = 0;

}

bool EquipEvolveUI::OnDirty()
{
    if( !IsDirty() )
        return false;

    SetDirty( false );

    RefreshAllBagEnable();	

    RefreshOkButton();
    m_pID_FRAME_EquipEvolve->SetRedraw();

    return true;
}

void EquipEvolveUI::OnRender()
{
    if( IsVisable() )
    {
        CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
        if ( pMe )
        {
            float fMeX,fMeY,fMeZ;			
            pMe->GetPos( &fMeX, &fMeY, &fMeZ );
            float dist = pMe->GetDistToTarget( m_vVisiblePos.x, m_vVisiblePos.y );			
            if( dist > 12.0f && !GetIsPocket())			//距离太远 并且不是通过背包快捷方式打开
            {
                SetVisable( false );
            }
        }
        if( m_bStartAnim )
        {
            RECT rc;
            m_pID_PICTURE_StarEffect->GetRealRect(&rc);
            m_slideAnim.Update(HQ_TimeGetTime(),&rc);
            if (!m_slideAnim.IsInAnimation())
            {
                m_bStartAnim = false;
                m_slideAnim.UnRelativePicResource();
            }
        }
    }
}

bool EquipEvolveUI::OnOkClick()
{
    if (!m_pID_FRAME_EquipEvolve)
        return false;
    if (-1 == m_nSelectMaterialIndex)
    {
        return false;
    }
    // 播放序列帧动画
    m_slideAnim.StartAnimation(HQ_TimeGetTime());
    m_bStartAnim = true;

    SendEvolveMsg();

    return true;
}


bool EquipEvolveUI::OnEquipDragOn( ControlIconDrag::S_ListImg* pItemDrag, ControlObject* pSender ,short	stEquipBagType)
{
    ClearEquip();
    RefreshAllBagEnable();

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
    if(IsMatchEquipType(pItemCommon)  )
    {
        ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
        if( !pImageSender )
            return false;

        // 包裹里
        if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(stEquipBagType, pImageSender) )
        {
            m_stEquipBagType = stEquipBagType;
            CItemBag2* pBag = &thePlayerRole.m_bag;
            if (m_stEquipBagType == BT_NormalItemBag)
            {
                m_stEquipBagIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItemDrag );
            }
            else
            {
                m_stEquipBagIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_MaterialBag, pItemDrag );
                pBag = &thePlayerRole.m_bagMaterial;
            }

            SCharItem item;
            if(m_stEquipBagIndex != -1 && pBag->GetItem(m_stEquipBagIndex,&item))
                m_stEquipBagGuid = item.itembaseinfo.nOnlyInt;
            else
                m_stEquipBagGuid = 0;
        }
        else
        {
            return false;
        }		

        m_bEquipBagEnable = false;			
        RefreshEquipInfo();
		if (!s_CUI_ID_FRAME_Star.IsVisable())
			UpdateGem();

        SetDirty( true );
    }	
	OnDirty();	
    return false;
}

void EquipEvolveUI::EquipEvolveIntialize()
{
    m_bStartAnim = false;
    RECT rc;
    m_pID_PICTURE_StarEffect->GetRealRect(&rc);
    if (GetSlideEffectPath())
    {
        m_slideAnim.Initialize(GetSlideEffectPath(), 20, rc, 1400);
    }
    /*if (m_pID_LISTIMG_Material)
    {
        m_pID_LISTIMG_Material->SetEnableDrag(false);
    }	*/	
    SetDirty(true);
    theUiManager.SetFrameLayout(UI_LAYOUT_1, m_pID_FRAME_EquipEvolve);
}

void EquipEvolveUI::ResetEquipEvolve()
{
    theUiManager.RemoveFrameLayout(m_pID_FRAME_EquipEvolve);
    if( m_bStartAnim )
    {
        m_bStartAnim = false;
        m_slideAnim.StopAnimation();
        m_slideAnim.UnRelativePicResource();
    }
	m_pSelectItem = NULL;
    ResetUIObjects();
}

void EquipEvolveUI::OnSetVisable( const bool bVisable )
{
    if( !m_pID_FRAME_EquipEvolve )
        return;
    m_pID_FRAME_EquipEvolve->SetVisable( bVisable );	
    if( m_bStartAnim )
    {
        m_bStartAnim = false;
        m_slideAnim.StopAnimation();
        m_slideAnim.UnRelativePicResource();
    }
    if (m_MatchMaterialArray.empty())
    {
        const std::vector<ItemDefine::SItemCommon*>& MaterialItemList = GettheItemDetail().GetMaterialItemList();
        for (int i = 0; i < MaterialItemList.size();++i)
        {
            ItemDefine::SCreateMaterial* pMaterial = ( ItemDefine::SCreateMaterial* )MaterialItemList[i];
            if (pMaterial->stMaterialType == GetEvolveMaterialType())
            {
                m_MatchMaterialArray.push_back(pMaterial->ustItemID);
            }
        }
    }
}
void EquipEvolveUI::SetSelectItem( ControlIconDrag::S_ListImg* pItem )
{
    if (m_pSelectItem)
        m_pSelectItem->m_pkIconInfo->SetColorFrameType(eColorFrame_None);

    m_pSelectItem = pItem;
    if (m_pSelectItem)
    {
        m_pSelectItem->m_pkIconInfo->SetColorFrameType(eColorFrame_Select);
    }

}

int EquipEvolveUI::GetEvolveMoneyCost(  )
{
	if(!m_pID_FRAME_EquipEvolve)
		return -1;

	if (m_pID_LISTIMG_Material == 0)
	{
		return -1;
	}
	
    int nIndex = m_nSelectMaterialIndex;
    if (m_nSelectMaterialIndex == -1)
    {//没有合适的材料
        nIndex = 0;
    }

    ControlIconDrag::S_ListImg* pItemImg = m_pID_LISTIMG_Material->GetItemByIndex(nIndex);
    if (pItemImg->IsNull())
    {
        return -1;
    }
    ItemDefine::SCreateMaterial* pMaterial = ( ItemDefine::SCreateMaterial* )GettheItemDetail().GetItemByID(pItemImg->m_pkIconInfo->GetItemId());
    if (!pMaterial)
    {
        return -1;
    }
    return pMaterial->useCostMoney;
}

float EquipEvolveUI::GetEvolveProbability()
{
	return 0.0f;
}

bool EquipEvolveUI::IsNearAttackAttribute( ItemDefine::SItemCanEquip* pCanEquip )
{
    return (pCanEquip->arrayEquipArmsReq[EArmType_Warrior] || pCanEquip->arrayEquipArmsReq[EArmType_Assassin] );		
}

bool EquipEvolveUI::IsLongAttackAttribute( ItemDefine::SItemCanEquip* pCanEquip )
{
    return (pCanEquip->arrayEquipArmsReq[EArmType_Hunter] || pCanEquip->arrayEquipArmsReq[EArmType_Sniper] );		
}

bool EquipEvolveUI::IsMagicAttackAttribute( ItemDefine::SItemCanEquip* pCanEquip )
{
    return (pCanEquip->arrayEquipArmsReq[EArmType_Taoist] || pCanEquip->arrayEquipArmsReq[EArmType_Mage] );		
}

void EquipEvolveUI::AddAttackString( ItemDefine::SItemCanEquip* pWeapon, SCharItem* pItem, ControlList* pList, bool bNextLevel ,bool bSoul )
{
    char szBuf[256] = {0};
    ControlList::S_List sList;
    sList.clear();

    //if( pWeapon->attack != 0 )
    {
        if (IsNearAttackAttribute(pWeapon))
        {//近程攻击
        int nValue = (int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->attackPhysics, pItem->equipdata.ucLevel + (int)bNextLevel );
//             if (bSoul)
//             {
//                 int nAddValue = theStarLevelUpConfig.GetEquipStampAttrAddition( pItem, RT_AddShortAttack );
//                 MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d (%s + %d)", theXmlString.GetString(eTip_sAddShortAttack), nValue
//                     , theXmlString.GetString(eText_Soul_Soul), nAddValue);
//             }
//             else
            {
                MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddShortAttack), nValue);
            }
            sList.SetData( szBuf, 0, 0, 0xffffffff );
            pList->AddItem( &sList );
            sList.clear();
        }
         if (IsLongAttackAttribute(pWeapon))
         {
			  int nValue = (int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->exact, pItem->equipdata.ucLevel + (int)bNextLevel );
//             if (bSoul)
//            {
//                int nAddValue = theStarLevelUpConfig.GetEquipStampAttrAddition( pItem, RT_AddLongAttack );
//                 MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d (%s + %d)", theXmlString.GetString(eTip_sAddLongAttack), nValue
//                     , theXmlString.GetString(eText_Soul_Soul), nAddValue);
//             }
//             else
//             {
                 MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddExact), nValue);
//             }
             sList.SetData( szBuf, 0, 0, 0xffffffff );
             pList->AddItem( &sList );
             sList.clear();
         }
        if (IsMagicAttackAttribute(pWeapon))
        {
            int nValue = (int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->attackMagic, pItem->equipdata.ucLevel + (int)bNextLevel );
//             if (bSoul)
//             {
//                 int nAddValue = theStarLevelUpConfig.GetEquipStampAttrAddition( pItem, RT_AddMagicAttack );
//                 MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d (%s + %d)", theXmlString.GetString(eTip_sAddMagicAttack), nValue
//                     , theXmlString.GetString(eText_Soul_Soul), nAddValue);
//             }
//             else
            {
                MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddMagicAttack), nValue);
            }
            sList.SetData( szBuf, 0, 0, 0xffffffff );
            pList->AddItem( &sList );
            sList.clear();
        }

    }

}

void EquipEvolveUI::AddDefendString( ItemDefine::SItemArmour* pArmour, SCharItem* pItem, ControlList* pList, bool bNextLevel ,bool bSoul )
{
    char szBuf[256] = {0};
    ControlList::S_List sList;
    sList.clear();

	//物理防御
    if( pArmour->defendPhysics > 0 )
    {
        // 远程防御
        sList.clear();
        int nValue = (int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->defendPhysics, pItem->equipdata.ucLevel + (int)bNextLevel);        
		MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddLongDefend), nValue);
        
        sList.SetData( szBuf, 0, 0, 0xffffffff );
        pList->AddItem( &sList );
    }

    if( pArmour->defendMagic > 0 )
    {
        sList.clear();
        // 魔法防御
        int nValue = (int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->defendMagic, pItem->equipdata.ucLevel + (int)bNextLevel);
		MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddMagicDefend), nValue);

        sList.SetData( szBuf, 0, 0, 0xffffffff );
        pList->AddItem( &sList );		
    }
	if( pArmour->Hp > 0 )
	{
		// Hp
		sList.clear();
		int nValue = (int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->Hp, pItem->equipdata.ucLevel + (int)bNextLevel);        
		MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddHPMax), nValue);

		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );
	}

	if( pArmour->Mp > 0 )
	{
		sList.clear();
		// 魔
		int nValue = (int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->Mp, pItem->equipdata.ucLevel + (int)bNextLevel);
		MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddMPMax), nValue);

		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );		
	}

}

void EquipEvolveUI::AddHpMpString( ItemDefine::SItemArmour* pArmour, SCharItem* pItem, ControlList* pList, bool bNextLevel ,bool bSoul )
{
	char szBuf[256] = {0};
	ControlList::S_List sList;
	sList.clear();

	//
	if( pArmour->Hp > 0 )
	{
		// Hp
		sList.clear();
		int nValue = (int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->Hp, pItem->equipdata.ucLevel + (int)bNextLevel);        
		MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddHPMax), nValue);

		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );
	}

	if( pArmour->Mp > 0 )
	{
		sList.clear();
		// 魔
		int nValue = (int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->Mp, pItem->equipdata.ucLevel + (int)bNextLevel);
		MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddMPMax), nValue);

		sList.SetData( szBuf, 0, 0, 0xffffffff );
		pList->AddItem( &sList );		
	}

}

bool EquipEvolveUI::ProcessAllDone( ControlIconDrag::S_ListImg * pImg )
{
    bool bRet = IsEvolveAllDone(pImg);
    {
        m_pID_TEXT_TipAllDone->SetVisable(bRet);
		if (m_pID_TEXT_Money)
		{
			m_pID_TEXT_Money->SetVisable(!bRet);
		}
        if (m_pID_LISTIMG_Material)
        {
            //m_pID_LISTIMG_Material->SetVisable(!bRet);
        }
		if (m_pID_TEXT_T3 && m_pID_TEXT_T4)
		{
			if (m_pID_TEXT_TipAllDone->IsVisable())
			{
				m_pID_TEXT_T3->SetVisable(false);
				m_pID_TEXT_T4->SetVisable(false);
			}
		}
    }
    return bRet;
}

void EquipEvolveUI::SendEvolveMsg()
{
    MsgEquipEvolve msgEvolve;
    msgEvolve.nEvolveType = GetEvolveType();

    msgEvolve.nNormalBagIndex = m_stEquipBagIndex;
    msgEvolve.nNormalGuid      = m_stEquipBagGuid;

    msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType= m_shMaterialBagType[m_nSelectMaterialIndex];
    msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex = m_stMaterialIndex[m_nSelectMaterialIndex];
    msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid = m_n64MaterialGuid[m_nSelectMaterialIndex];
	msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].value = m_stMaterialUseNum;
	msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].protectStar = m_unProtectStarNum;

	msgEvolve.SendEquipMsg();
    //GettheNetworkInput().SendMsg( &msgEvolve );
}

ControlIconDrag::S_ListImg * EquipEvolveUI::RetriveMaterialImg( short itemId ,int& nIndex)
{
    nIndex = -1;
    ControlListImage* pMaterialBag = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_MaterialBag);
    for(int index = 0; index < pMaterialBag->GetItemCnt(); ++index)
    {
        ControlIconDrag::S_ListImg * pListImg = pMaterialBag->GetItemByIndex(index);
        if (!pListImg || pListImg->IsNull() || NULL == pListImg->m_pkIconInfo)
        {
            continue;
        }
        if (pListImg->m_pkIconInfo->Id() == itemId && MatchMaterialOption((SCharItem*)pListImg->m_pkIconInfo->GetData()))
        {
            nIndex =  index;
            return pListImg;
        }						
    }
    return NULL;

}

void EquipEvolveUI::RefreshBeginPic()
{
    if (m_stEquipBagIndex == -1)
    {
        m_pID_PICTURE_Begin->SetVisable(true);
    }
    else
    {
        m_pID_PICTURE_Begin->SetVisable(false);
    }
}

void EquipEvolveUI::FillBlueAttriList( ControlIconDrag::S_ListImg* pEquipImg ,ControlList* pLIST_Attribute )
{
    if (NULL == pLIST_Attribute)
    {
        return;
    }
    pLIST_Attribute->Clear();

    SCharItem* pEquipItem = (SCharItem*)pEquipImg->m_pkIconInfo->GetData();
    int nRandValue = 0;
    char szTemp[256] = {0};
    char szMiddle[256] = {0};
    int nTipPreTextIndex = 0;
    for (int nloop=0;nloop<SCharItem::EConstDefine_BaseRandMaxCount;++nloop)
    {
        if (pEquipItem->equipdata.baseRands[nloop] != InvalidLogicNumber)
        {
            ItemDefine::SRandAttribute* pArmourRand = GettheItemDetail().GetRandByID(pEquipItem->equipdata.baseRands[nloop]);
            if (!pArmourRand)
                continue;

            for( int i = 0 ; i < ItemDefine::SRandAttribute::CD_TypeCount ; ++ i )
            {
                nRandValue = S_IconInfoHero::GetRandValueByType( pArmourRand, i );
                if( pArmourRand->type[i] == RT_None )
                    continue;

                if( pArmourRand->type[i] == RT_AddMoveSpeed )
                {
                    sprintf( szTemp, "%s+%.2f", S_IconInfoHero::GetRandStringByType( pArmourRand->type[i] ).c_str(), ( float )nRandValue / 100.0f );
                }
                else
                {
                    // 对同一buff使用拷贝危险 [11/18/2010 zhangjiayi]
                    sprintf( szMiddle, "%s+%d", S_IconInfoHero::GetRandStringByType( pArmourRand->type[i] ).c_str(), nRandValue );  
                    if( pArmourRand->type[i] == RT_AddExpPer )
                        sprintf( szTemp, "%s%s", szMiddle, "%" );
                    else
                        strcpy_s( szTemp, 256, szMiddle );
                }
                ControlList::S_List listItem;
                listItem.SetData(szTemp,0,NULL,S_IconInfoHero::GetQualityColor( ItemDefine::EQL_Blue ));
                pLIST_Attribute->AddItem(&listItem);
            }
        }
    }

}

bool EquipEvolveUI::IsMatchEquipType( ItemDefine::SItemCommon* pItemCommon )
{
    return pItemCommon 
        && 
        ( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_WEAPON ||
        pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR );
}

bool EquipEvolveUI::IsPackItemBeUsing( __int64 nGuid )
{
    if( !IsVisable() || nGuid <= 0 )
        return false;

    if( m_stEquipBagGuid == nGuid )
        return true;

    for( int i = 0; i < m_nsMaxMaterialNum; ++i )
    {
        if( m_n64MaterialGuid[i] == nGuid )
        {
            return true;
        }
    }
    return false;
}

void EquipEvolveUI::RefreshByItemChange()
{
	UpdateGem();
	if (s_CUI_ID_FRAME_Star.IsVisable())
		s_CUI_ID_FRAME_Star.ShowProtectStarIcon();
}

void EquipEvolveUI::RefreshByMoneyChange()
{
	/*RefreshNeedMoney();
	RefreshProbability();
	RefreshOkButton();*/
}

void EquipEvolveUI::SetCheckNumBox(int num)
{
	if (!m_pID_CHECKBOX_X1 || !m_pID_CHECKBOX_X2 || !m_pID_CHECKBOX_X3 || !m_pID_CHECKBOX_X4)
		return;

	m_pID_CHECKBOX_X1->SetEnable(true);
	m_pID_CHECKBOX_X2->SetEnable(true);
	m_pID_CHECKBOX_X3->SetEnable(true);
	m_pID_CHECKBOX_X4->SetEnable(true);

	switch (num)
	{
	case 1:
		{
			m_pID_CHECKBOX_X2->SetEnable(false);
			m_pID_CHECKBOX_X3->SetEnable(false);
			m_pID_CHECKBOX_X4->SetEnable(false);
			m_pID_CHECKBOX_X2->SetCheck(false);
			m_pID_CHECKBOX_X3->SetCheck(false);
			m_pID_CHECKBOX_X4->SetCheck(false);

			if (m_stMaterialUseNum > 1)
			{
				m_pID_CHECKBOX_X1->SetCheck(true);
				m_stMaterialUseNum = 1;

				s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_StarMaterialNoEnough), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true);
			}
		}
		break;
	case 2:
		{
			m_pID_CHECKBOX_X3->SetEnable(false);
			m_pID_CHECKBOX_X4->SetEnable(false);
			m_pID_CHECKBOX_X3->SetCheck(false);
			m_pID_CHECKBOX_X4->SetCheck(false);

			if (m_stMaterialUseNum > 2)
			{
				/*m_pID_CHECKBOX_X2->SetCheck(true);
				m_stMaterialUseNum = 2;*/
				m_pID_CHECKBOX_X1->SetCheck(true);
				m_stMaterialUseNum = 1;

				s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_StarMaterialNoEnough), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true);
			}
		}
		break;
	case 3:
		{
			m_pID_CHECKBOX_X4->SetEnable(false);
			m_pID_CHECKBOX_X4->SetCheck(false);

			if (m_stMaterialUseNum > 3)
			{
				/*m_pID_CHECKBOX_X3->SetCheck(true);
				m_stMaterialUseNum = 3;*/
				m_pID_CHECKBOX_X1->SetCheck(true);
				m_stMaterialUseNum = 1;

				s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_StarMaterialNoEnough), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true);
			}
		}
		break;
	default:
		break;
	}
}

void EquipEvolveUI::SetProtectStarBox(uint8 unstar)
{
	if (!m_pID_CHECKBOX_Protect_NoUse || !m_pID_CHECKBOX_Protect_SixStar || !m_pID_CHECKBOX_Protect_NineStar
		|| !m_pID_CHECKBOX_Protect_TwelStar || !m_pID_CHECKBOX_Protect_FiftStar)
		return;

	m_pID_CHECKBOX_Protect_SixStar->SetEnable(true);
	m_pID_CHECKBOX_Protect_NineStar->SetEnable(true);
	m_pID_CHECKBOX_Protect_TwelStar->SetEnable(true);
	m_pID_CHECKBOX_Protect_FiftStar->SetEnable(true);

	m_pID_CHECKBOX_Protect_SixStar->SetCheck(false);
	m_pID_CHECKBOX_Protect_NineStar->SetCheck(false);
	m_pID_CHECKBOX_Protect_TwelStar->SetCheck(false);
	m_pID_CHECKBOX_Protect_FiftStar->SetCheck(false);


	if (unstar < 6)
	{
		m_pID_CHECKBOX_Protect_SixStar->SetEnable(false);
		m_pID_CHECKBOX_Protect_NineStar->SetEnable(false);
		m_pID_CHECKBOX_Protect_TwelStar->SetEnable(false);
		m_pID_CHECKBOX_Protect_FiftStar->SetEnable(false);

		m_pID_CHECKBOX_Protect_NoUse->SetCheck(true);
		m_unProtectStarNum = 0;
		return;
	}

	if (unstar < 9)
	{
		m_pID_CHECKBOX_Protect_NineStar->SetEnable(false);
		m_pID_CHECKBOX_Protect_TwelStar->SetEnable(false);
		m_pID_CHECKBOX_Protect_FiftStar->SetEnable(false);

		if (m_unProtectStarNum >= 6 && thePlayerRole.m_bagMaterial.IsHaveItemById(SID_ProtectStarSix))
		{
			m_pID_CHECKBOX_Protect_SixStar->SetCheck(true);
			m_unProtectStarNum = 6;
		}
		else
		{
			m_pID_CHECKBOX_Protect_NoUse->SetCheck(true);
			m_unProtectStarNum = 0;
		}
		
		return;
	}

	if (unstar < 12)
	{
		m_pID_CHECKBOX_Protect_SixStar->SetEnable(false);
		m_pID_CHECKBOX_Protect_TwelStar->SetEnable(false);
		m_pID_CHECKBOX_Protect_FiftStar->SetEnable(false);

		if (m_unProtectStarNum >= 9 && thePlayerRole.m_bagMaterial.IsHaveItemById(SID_ProtectStarNine))
		{
			m_pID_CHECKBOX_Protect_NineStar->SetCheck(true);
			m_unProtectStarNum = 9;
		}
		else
		{
			m_pID_CHECKBOX_Protect_NoUse->SetCheck(true);
			m_unProtectStarNum = 0;
		}
		
		return;
	}

	if (unstar < 15)
	{
		m_pID_CHECKBOX_Protect_SixStar->SetEnable(false);
		m_pID_CHECKBOX_Protect_NineStar->SetEnable(false);
		m_pID_CHECKBOX_Protect_FiftStar->SetEnable(false);

		if (m_unProtectStarNum >= 12 && thePlayerRole.m_bagMaterial.IsHaveItemById(SID_ProtectStarTwelve))
		{
			m_pID_CHECKBOX_Protect_TwelStar->SetCheck(true);
			m_unProtectStarNum = 12;
		}
		else
		{
			m_pID_CHECKBOX_Protect_NoUse->SetCheck(true);
			m_unProtectStarNum = 0;
		}
		
		return;
	}

	if (unstar >= 15)
	{
		m_pID_CHECKBOX_Protect_SixStar->SetEnable(false);
		m_pID_CHECKBOX_Protect_NineStar->SetEnable(false);
		m_pID_CHECKBOX_Protect_TwelStar->SetEnable(false);

		if (m_unProtectStarNum >= 15 && thePlayerRole.m_bagMaterial.IsHaveItemById(SID_ProtectStarFifteen))
		{
			m_pID_CHECKBOX_Protect_FiftStar->SetCheck(true);
			m_unProtectStarNum = 15;
		}
		else
		{
			m_pID_CHECKBOX_Protect_NoUse->SetCheck(true);
			m_unProtectStarNum = 0;
		}

		return;
	}
}

bool EquipEvolveUI::HasMaterialItem(unsigned short usID)
{
	if(!m_pID_FRAME_EquipEvolve)
		return false;
	if (thePlayerRole.m_bagMaterial.IsHaveItemById(usID))
		return true;
	else
	{
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_NoProtectStarMaterial), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true);
		return false;
	}
}
//UiEffectBase::UiEffectBase()
//{
//	m_pID_TEXT_Effect = NULL;
//	m_pID_TEXT_Fail = NULL;
//	m_pID_TEXT_Success = NULL;
//	m_StartTime = 0;
//	m_eStatus = EffectStatus_No;
//}
//UiEffectBase::~UiEffectBase()
//{
//	m_pID_TEXT_Effect = NULL;
//	m_pID_TEXT_Fail = NULL;
//	m_pID_TEXT_Success = NULL;
//	m_StartTime = 0;
//	m_eStatus = EffectStatus_No;
//}
//bool UiEffectBase::DoControlConnect(IN const char* szFrameID)
//{
//	m_pID_TEXT_Effect = (ControlText*)theUiManager.FindControl(szFrameID, ID_TEXT_Effect );
//	m_pID_TEXT_Fail = (ControlText*)theUiManager.FindControl(szFrameID, ID_TEXT_Fail );
//	m_pID_TEXT_Success = (ControlText*)theUiManager.FindControl(szFrameID, ID_TEXT_Success );
//	assert(m_pID_TEXT_Effect);
//	assert(m_pID_TEXT_Fail);
//	assert(m_pID_TEXT_Success);
//	return true;
//}
//void UiEffectBase::Render()
//{
//	DWORD time = timeGetTime();
//	if ((time - m_StartTime>=1000*2) || m_StartTime == 0 || m_eStatus == EffectStatus_No)
//	{
//		if (m_pID_TEXT_Effect && m_pID_TEXT_Effect->IsVisable())
//		{
//			m_pID_TEXT_Effect->SetVisable(false);
//		}
//		if (m_pID_TEXT_Fail && m_pID_TEXT_Fail->IsVisable())
//		{
//			m_pID_TEXT_Fail->SetVisable(false);
//		}
//		if (m_pID_TEXT_Success && m_pID_TEXT_Success->IsVisable())
//		{
//			m_pID_TEXT_Success->SetVisable(false);
//		}
//		m_StartTime = 0;
//		m_eStatus = EffectStatus_No;
//		return;
//	}
//
//	switch (m_eStatus)
//	{
//	case EffectStatus_No:
//		return;
//	case EffectStatus_Start:
//		if (m_pID_TEXT_Effect && !m_pID_TEXT_Effect->IsVisable())
//		{
//			m_pID_TEXT_Effect->SetVisable(true);
//			if(m_pID_TEXT_Fail) m_pID_TEXT_Fail->SetVisable(false);
//			if(m_pID_TEXT_Success) m_pID_TEXT_Success->SetVisable(false);
//		}
//		break;
//	case EffectStatus_Fail:
//		if (m_pID_TEXT_Fail && !m_pID_TEXT_Fail->IsVisable())
//		{
//			m_pID_TEXT_Fail->SetVisable(true);
//			if(m_pID_TEXT_Effect) m_pID_TEXT_Effect->SetVisable(false);
//			if(m_pID_TEXT_Success) m_pID_TEXT_Success->SetVisable(false);
//		}
//		break;
//	case EffectStatus_Success:
//		if (m_pID_TEXT_Success && !m_pID_TEXT_Success->IsVisable())
//		{
//			m_pID_TEXT_Success->SetVisable(true);
//			if (m_pID_TEXT_Effect) m_pID_TEXT_Effect->SetVisable(false);
//			if (m_pID_TEXT_Fail) m_pID_TEXT_Fail->SetVisable(false);
//		}
//		break;
//	}
//}
