#include "FreeTip.h"
#include "MeUI/IconManager.h"
#include "MeUI/UiPicture.h"
#include "GameMain.h"
#include "PlayerRole.h"
#include "PlayerMgr.h"
#include "Cfg.h"
#include "Skill.h"
//-----------------------------------------------------------------------------
static const int s_nClostBtnSize = 16;
//-----------------------------------------------------------------------------
//extern ControlPictureManager theControlPictureManager;
extern CPlayerRole thePlayerRole;
extern CHeroGame theHeroGame;
extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH;
//-----------------------------------------------------------------------------
FreeTip::FreeTip()
{
	m_bShowTip = false;	
	m_bHaveCompareItem = false;
	m_nTipX = 0;
	m_nTipY = 0;
	m_pkShowItemTip = 0;
	m_pkShowItemTipCompare = 0;

	mState = FS_INVALID;
	mId = POS_INVALID;

	mIsShowClose = true;
}
//-----------------------------------------------------------------------------
FreeTip::~FreeTip()
{
	if( m_pkShowItemTip )
	{
		m_pkShowItemTip->Clear();
	}

	if( m_pkShowItemTipCompare )
	{
		m_pkShowItemTipCompare->Clear();
	}

	m_bHaveCompareItem = false;
	delete m_pkShowItemTip;

	m_pkShowItemTip = 0;
	delete m_pkShowItemTipCompare;
	m_pkShowItemTipCompare = 0;
}
//-----------------------------------------------------------------------------
void FreeTip::ShowItemTip( bool bShow /* = true */ )
{
	m_bShowTip = bShow;
}
//-----------------------------------------------------------------------------
void FreeTip::Render( int nFontIndex, int nFontSizeScaled, DWORD dwFontColor )
{
	if( m_bShowTip && m_pkShowItemTip )
	{
		int nHeight = m_pkShowItemTip->m_pkIconInfo->m_usHeight;
		if( m_bHaveCompareItem )
		{
			m_pkShowItemTipCompare->m_pkIconInfo->CaculateWidthHeight( nFontSizeScaled, nFontIndex );

			if( m_pkShowItemTipCompare->m_pkIconInfo->m_usHeight > nHeight )
			{
				nHeight = m_pkShowItemTipCompare->m_pkIconInfo->m_usHeight;
			}

			if( m_nTipY + nHeight + 15 > SCREEN_HEIGHT )//超
			{
				m_nTipY = SCREEN_HEIGHT - nHeight - 15;
			}
		}

		// show tip
		m_rcLastRect = m_pkShowItemTip->m_pkIconInfo->DisplayInfo( m_nTipX, m_nTipY, false,
																nFontIndex, nFontSizeScaled,dwFontColor );
		// show compare tip
		if ( m_bHaveCompareItem )
		{
			int nX = m_nTipX;
			int nY = m_rcLastRect.top - 15;			
			//校正x,y值
			//左边出界，显示在右侧
			if( m_rcLastRect.left - m_pkShowItemTipCompare->m_pkIconInfo->m_usWidth  < 20 )
			{
				nX += m_rcLastRect.right - m_rcLastRect.left ;
			}
			else//显示在左侧
			{				
				nX = m_rcLastRect.left - m_pkShowItemTipCompare->m_pkIconInfo->m_usWidth - 20 ;
			}
			m_pkShowItemTipCompare->m_pkIconInfo->DisplayInfo( nX,nY, false,
															nFontIndex, nFontSizeScaled,dwFontColor );
		}

		// render close btn
		RECT rcCloseBtn = { m_rcLastRect.right - s_nClostBtnSize - 2, 
						m_rcLastRect.top + 2, 
						m_rcLastRect.right - 2,
						m_rcLastRect.top + s_nClostBtnSize + 2};

		// render close button
		int nFoo = -1;

		// 显示关闭按钮
		if ( mIsShowClose )
		{
			theControlPictureManager.BitBlt( &nFoo, gCfg.m_strFreeTipCloseBtn.c_str(), 
										const_cast<RECT*>(&rcCloseBtn), const_cast<RECT*>(&gCfg.m_rcFreeTipCloseRect) );
		}
	}	
}
//-----------------------------------------------------------------------------
void FreeTip::SetData( SCharItem* pItem, int nMouseX, int nMouseY, bool bCompare /* = false */,bool isShowClose /* = true */ )
{
	if( !m_pkShowItemTip )
	{
		m_pkShowItemTip = new ControlIconDrag::S_ListImg;
	}

	if( !m_pkShowItemTipCompare )
	{
		m_pkShowItemTipCompare = new ControlIconDrag::S_ListImg;
	}

	m_bHaveCompareItem = false;
	m_pkShowItemTip->Clear();
	m_pkShowItemTipCompare->Clear();
	m_pkShowItemTip->SetData( (void*)pItem, eIcon_Enable );

	if( bCompare )
	{
		if(  RetrieveCompareItem( pItem ) )
		{
			m_bHaveCompareItem = true;
		}
	}

	m_bShowTip = true;
	m_nTipX = nMouseX;
	m_nTipY = nMouseY;

	mIsShowClose = isShowClose;
}
//-----------------------------------------------------------------------------
void FreeTip::SetSkillData( /*SCharSkill* pSkill*/int skillId, /*ItemDefine::SItemSkill* pItemSKill*/int skillLvl, int nMouseX, int nMouseY, bool bCompare /*= false*/, bool isShowClose /*= true*/ )
{
	if( !m_pkShowItemTip )
	{
		m_pkShowItemTip = new ControlIconDrag::S_ListImg;
	}

	if( !m_pkShowItemTipCompare )
	{
		m_pkShowItemTipCompare = new ControlIconDrag::S_ListImg;
	}

	m_bHaveCompareItem = false;
	m_pkShowItemTip->Clear();
	m_pkShowItemTipCompare->Clear();
	//m_pkShowItemTip->SetData( (void*)pSkill, eIcon_Enable );

	//const IconManager::IconInfo*    pIcon = IconManager::Get().GetIconInfo( pSkill->ustSkillID );
	//if ( pIcon == NULL )
	//{
	//	return;
	//}


	//CUISkillTreeConfig::SkillTreePage* pSkillTree = g_UISkillMgr.m_SkillTreeConfig.
	//	GetPage(CUISkillMgr::eCommon);
	//if (!pSkillTree)
	//	return;
	//SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;
	//const SUIIconSet::SIconSet* pIcon = pSkillIcon->GetValue(skillId);


	 SUIIconSet::SIconSet* pIcon = g_UISkillMgr.GetAllSkillIconSet(/*pSkill->ustSkillID*/skillId);
	 if ( pIcon == NULL )
	 {
		 return;
	 }

	m_pkShowItemTip->m_pkIconInfo->SetIconImageInfo( pIcon->image, pIcon->iconSize, pIcon->row, pIcon->column );
	m_pkShowItemTip->SetData( pIcon->iconid, /*pSkill->stSkillLevel*/skillLvl, /*bEnable ?*/ eIcon_Enable /*: eIcon_Disable*/, 0, eTipFlag_SkillWithNextLevel );
	m_pkShowItemTip->SetFlags( CUISkillMgr::eProfession );
	//if( pSkill->stSkillLevel != pItemSKill->ustSkillMaxLvl )
	//	m_pkShowItemTip->SetOtherInfo( pItemSKill->ustSkillMaxLvl );
	//m_pkShowItemTip.SetOtherInfo( szNeedInfo );



	//m_pkShowItemTip->SetData( pSkill->ustSkillID, 1 );
	//S_IconInfoHero* iconInfo = dynamic_cast<S_IconInfoHero*>(m_pkShowItemTip->m_pkIconInfo);

	//if ( iconInfo )
	//{
	//	iconInfo->ShowSkill();
	//}

	//if( bCompare )
	//{
	//	if(  RetrieveCompareItem( pItem ) )
	//	{
	//		m_bHaveCompareItem = true;
	//	}
	//}

	m_bShowTip = true;
	m_nTipX = nMouseX;
	m_nTipY = nMouseY;

	mIsShowClose = isShowClose;
}

//-----------------------------------------------------------------------------
bool FreeTip::PtInCloseBtn( int nMouseX, int nMouseY )
{
	if( IsVisible()
		&& nMouseX >= ( m_rcLastRect.right - s_nClostBtnSize - 2 )
		&& nMouseX <= ( m_rcLastRect.right - 2 )
		&& nMouseY >= ( m_rcLastRect.top + 2 )
		&& nMouseY <= m_rcLastRect.top + s_nClostBtnSize + 2 )
	{
		//ShowItemTip(false);
		return true;
	}
	return false;
}
//-----------------------------------------------------------------------------
bool FreeTip::RetrieveCompareItem( SCharItem* pItem )
{
	if( !pItem )
		return false;

	ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );

	if( pItemDetail 
		&& ( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON || pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR ) )
	{
		ItemDefine::SItemCanEquip *pEquip = (ItemDefine::SItemCanEquip *)pItemDetail;

		int nCanEquipPart = 0;
		for( int i=0; i< EEquipPartType_MaxEquitPart; i++ )
		{
			if ( pEquip->arrayCanEquip[i] == 1 )
			{
				nCanEquipPart = i;
				break;
			}
		}
		
		bool bFashion = pEquip->bFashion;
		
		const SCharItem* pCompareEquipItem = &thePlayerRole.m_pVisual->GetVisual( (int)bFashion )[nCanEquipPart];

		m_pkShowItemTipCompare->SetData( (void*)pCompareEquipItem, 
										eIcon_Enable, eTipFlag_Normal, true, 
										theHeroGame.GetPlayerMgr()->GetMyID() );

		return true;

	}
	return false;
}

void			FreeTip::SetState( FreeTipState state )
{
	mState = state;
}

FreeTipState FreeTip::GetState()
{
	return mState;
}

void FreeTip::SetPosId( FreeTipPos id )
{
	mId = id;
}

FreeTipPos FreeTip::GetPosId() const
{
	return mId;
}

void FreeTip::SetTipPos( int x, int y )
{
	m_nTipX = x;
	m_nTipY = y;
}

int FreeTip::GetFreeTipW() const
{
	if ( m_pkShowItemTip && m_pkShowItemTip->m_pkIconInfo )
	{
		return m_pkShowItemTip->m_pkIconInfo->m_usWidth;
	}

	return 0;
}

int FreeTip::GetFreeTipH() const
{
	if ( m_pkShowItemTip && m_pkShowItemTip->m_pkIconInfo )
	{
		return m_pkShowItemTip->m_pkIconInfo->m_usHeight;
	}

	return 0;
}

void FreeTip::MoveEndProc( int x, int y )
{
	if ( IsVisible() )
	{
		/*int offsetX = x - mNotePt.x;
		int offsetY = y - mNotePt.y;

		m_nTipX = m_nTipX + offsetX;
		m_nTipY = m_nTipY + offsetY;

		mNotePt.x = m_nTipX;
		mNotePt.y = m_nTipY;*/
	}
}

void FreeTip::MoveBeginProc( int x, int y )
{
	if ( IsVisible() )
	{
		mNotePt.x = x;
		mNotePt.y = y;
	}
}



