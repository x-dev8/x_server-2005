/********************************************************************
Created by UIEditor.exe
FileName: E:\Code\RunTime\CLIENT\Data\UI\Target.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Target.h"
#include "../Player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "FuncPerformanceLog.h"
#include "ChatInfoBox.h"
#include "GlobalDef.h"
#include "RbtnMenu.h"
#include "color_config.h"
#include "Main.h"
#include "exmain.h"
#include "ItemDetail.h"
#include "Group.h"
#include "Team_Player.h"
#include "XmlStringLanguage.h"
#include "Skill.h"
#include "MeTerrain/NiColor.h"
#include "MeTerrain/SwType.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/HashTable.h"
#include "MeTerrain/MapDef.h"
#include "MeTerrain/World.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/WorldTile.h"
#include "core/Name.h"
#include "ScreenInfoManager.h"
#include "MessageDefine.h"
#include "../filepacket/packet_interface.h"
//#include "Launcher/DataLauncher.h"
#include "Common.h"
#include "Create.h"         //added by ZhuoMeng.Hu		[9/19/2010]
#include "PetMain.h"
#include "SuAnimalMenu.h"
#include "TargetProgrss.h"
#include "ItemHero.h"
#include "PlayerInfoMgr.h"
#include "AutoAttackSet.h"
#include "MonsterDefine.h"

extern DWORD g_dwLastFrameCostTime; // 上一帧花费的时间
float g_fHpTailSpeed = 0.15f;
extern bool IsCollectSkill( unsigned short ustSkillID );

#define MAX_STATUS_SPARETIME 36000000

#define LEADER_MONSTER_PIC	"data\\ui\\common\\LeaderMonster.tga"
#define BOSS_MONSTER_PIC	"data\\ui\\common\\BossMonster.tga"
#define NORMAL_MONSTER_PCI	"data\\ui\\common\\NormalMonster.tga"

CUI_ID_FRAME_Target s_CUI_ID_FRAME_Target;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Target, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Target, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Target, ID_LISTIMG_StatusOnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_Target, ID_LISTIMG_StatusOnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Target, ID_LISTIMG_StatusOnIconLDBClick )
CUI_ID_FRAME_Target::CUI_ID_FRAME_Target()
// :CUIBase(eUI_OBJECT_Target)
{
	guardfunc;
	// SGuildMember
	ResetMembers();
}

void CUI_ID_FRAME_Target::ResetMembers()
{
	m_pID_FRAME_Target = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_PROGRESS_Hp = NULL;
	m_pID_PROGRESS_HpTail = NULL;
	m_pID_LISTIMG_Status = NULL;
	//m_pID_PICTURE_MonsterType = NULL;
	m_pID_TEXT_Lvl = NULL;
	m_nSelId = -1;
	_pText_Percent = NULL;
//	m_pID_PROGRESS_Mp = NULL;
	m_pID_PICTURE_Target = NULL;
	m_pID_PICTURE_TargetHair = NULL;
	m_pID_PICTURE_TargetFace = NULL;
	m_pID_PROGRESS_TargetHp = NULL;
	m_pID_TEXT_TargetName = NULL;
	m_nFollowPlayerId = -1;

	m_pID_PICTURE_Hair = NULL;
	m_pID_PICTURE_Choose = NULL;
	m_pID_PICTURE_Face = NULL;

    m_pID_TEXT_TargetLvl = NULL;
    m_pID_PICTURE_BgTargetFace = NULL;
	m_pID_PICTURE_Ren = NULL;
	m_pID_PICTURE_Ji = NULL;
	m_pID_PICTURE_Shen = NULL;
	m_pID_PICTURE_Gui = NULL;
	m_pID_PICTURE_Xian = NULL;
	m_pID_PICTURE_Yao = NULL;
	m_pID_PICTURE_Shou = NULL;
	m_pID_PICTURE_Mo = NULL;
	m_pID_TEXT_Hero = NULL;

    for( int i = 0; i < EArmType_Sniper; ++i )
    {
        m_pID_PICTURE_ProPic[i] = NULL;
    }

	nTargetTargetId		= -1;
	unguard;
}
// Frame
bool CUI_ID_FRAME_Target::OnFrameRun()
{
	IsTargetUIUpDateIng = true;
	guardfunc;
	if(this->IsVisable() && theHeroGame.GetPlayerMgr()->GetMe() && GetPlayerID() != -1)
	{
	CPlayer* pPlayer = NULL;
	pPlayer = theHeroGame.GetPlayerMgr()->FindByID( GetPlayerID());

	if (pPlayer)
	{

		D3DXVECTOR3 TargetPos = pPlayer->GetPos();
		D3DXVECTOR3 Mepos =  theHeroGame.GetPlayerMgr()->GetMe()->GetPos();
		D3DXVECTOR3 Length = TargetPos - Mepos;

		D3DXVECTOR3 distance( TargetPos.x - Mepos.x, TargetPos.y - Mepos.y, 0 );
		
		float fDistance = D3DXVec3Length( &distance );

		if (fDistance > 100)
		{
			SetVisable(false);
			m_nSelId = -1;
		}

		
		
	}

	}
	static DWORD dwLastUpdateTime = 0;
	if (IsVisable())
	{
		if ( m_nSelId >= 0 )
		{
			CPlayer*	pPlayer = theHeroGame.GetPlayerMgr()->FindByID( m_nSelId );
			if (pPlayer)
			{
				if (pPlayer ->IsMonster())
				{						
					if (!pPlayer ->IsIntonating())
					{
						if (s_CUI_ID_FRAME_TargetProgrss.IsVisable())
						{
							//								
							if (HQ_TimeGetTime() - pPlayer->GetIntonatingStartTime() < pPlayer->GetIntonatingDelayTime())
							{
								s_CUI_ID_FRAME_TargetProgrss.SetProgressText(theXmlString.GetString(eTextPlayer_Break));
								s_CUI_ID_FRAME_TargetProgrss.BreakProgress();
							}		
							else
							{
								s_CUI_ID_FRAME_TargetProgrss.Finish();
							}
							
						}
					}
					else
					{
						if (!s_CUI_ID_FRAME_TargetProgrss.IsVisable())
						{								
							s_CUI_ID_FRAME_TargetProgrss.SetVisable(true);

							s_CUI_ID_FRAME_TargetProgrss.SetProgressText(pPlayer->GetIntonatingName());
						}
						s_CUI_ID_FRAME_TargetProgrss.SetProgressValue((HQ_TimeGetTime() - pPlayer->GetIntonatingStartTime()) * 1000/ pPlayer->GetIntonatingDelayTime());
					}
				}
			}
		}
	}
	if ( HQ_TimeGetTime() - dwLastUpdateTime >= 250 )
	{
		CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
		if( pMe == NULL )
		{
			IsTargetUIUpDateIng = false;
			return false;
		}
		CPlayer *pPlayer = theHeroGame.GetPlayerMgr()->FindByID( m_nSelId );
		bool bNeedUpdate = false;
		if(m_bForceUpdate)
		{
			bNeedUpdate = true;
			m_bForceUpdate = false;
		}
		// 人物
		for ( int n=0; n<thePlayerRole.m_SkillBag.GetSkillNum(); n++ )
		{
			SCharSkill *pSkill;
			pSkill = thePlayerRole.m_SkillBag.GetSkillByIndex( n );
			if ( !pSkill ||
				pSkill->ustSkillID == InvalidLogicNumber )
			{
				continue;
			}

			ItemDefine::SItemSkill *pItemSkill;
			pItemSkill = GettheItemDetail().GetSkillByID( pSkill->ustSkillID,
				pSkill->stSkillLevel );
			if ( !pItemSkill )
				continue;

			bool has = false;
			if (s_CUI_ID_FRAME_SKILL.IsVisable() && s_CUI_ID_FRAME_SKILL.CHECKBOX_Job_IsChecked())
				has = true;
			else if( pItemSkill->specialSkillType >= ItemDefine::ESST_Team && pItemSkill->specialSkillType < ItemDefine::ESST_TeamMax )	// 小队技能
				has = true;
			else
			{
				for (int i = 0; i < More_iHotkey; ++i)
				{
					if (thePlayerRole.m_pHotKeyBag[i].ShortCut.BagIndex == n)
					{
						has = true;
						break;
					}
				}
			}

			if( !has )
				continue;

			// 采集技能跳过
			if( IsCollectSkill(pSkill->ustSkillID) )
				continue;

			bool bAvailable = false;
			short shCastType = pItemSkill->shCastType;

			// 单一目标
            if ( (shCastType == ItemDefine::casttype_singletarget && pItemSkill->usSpecialTargetType == ItemDefine::STT_NONE) ||
				shCastType == ItemDefine::casttype_AOETargetcirclearea )
			{
				bool bIsTest = false;
                if( pItemSkill->ustCastTarget == ItemDefine::casttarget_team )
                {
                    bAvailable = pMe->TryUseSkill( pMe, pItemSkill, true );
                    bIsTest = true;
                }
                else if( !bIsTest && pItemSkill->ustCastTarget == ItemDefine::casttarget_pet )
                {
                    if( pMe->GetPetID() <= -1 )
                    {
                        bAvailable = FALSE;
                    }
                    else
                    {
                        CPlayer* pPet = theHeroGame.GetPlayerMgr()->FindByID(pMe->GetPetID());
                        if( pPet )
                            bAvailable = pMe->TryUseSkill( pPet, pItemSkill, true );
                        else
                            bAvailable = FALSE;
                    }
                    bIsTest = true;
                }
				if( bIsTest == false && ( pPlayer == NULL||pPlayer->IsMonster()||pPlayer->IsNpc()) )
				{
					if (pItemSkill->ustCastTarget == ItemDefine::casttarget_me||
						pItemSkill->ustCastTarget == ItemDefine::casttarget_friendlive )
					{						
						bAvailable = pMe->TryUseSkill( pMe, pItemSkill, true );
						bIsTest = true;
					}
				}
				if ( pPlayer&&bIsTest == false )
				{
					bool bTestAG = true;

					if (pPlayer->IsPlayer())
					{
						if (pItemSkill->ustCastTarget == ItemDefine::casttarget_me)
						{
							bAvailable = pMe->TryUseSkill( pMe, pItemSkill, true );
							bTestAG = false;
						}
					}
					if (bTestAG == true)
					{
						bAvailable = pMe->TryUseSkill( pPlayer, pItemSkill, true );
					}
				}
			}
			// 范围
			else
			{
				bAvailable = pMe->TryUseSkill( NULL, pItemSkill, true );
			}
			if ( bAvailable != pSkill->bAvailable )
			{
				bNeedUpdate = true;
			}

			pSkill->bAvailable = bAvailable;

			/*
			bool IsInSkillAttackRange = false;
			if (pPlayer != NULL)
			{
				const D3DXVECTOR3 targetPos = pPlayer->GetPos();
				BOOL bToClose = FALSE;
				IsInSkillAttackRange = pMe->IsInAttackRangeOnlyTwoPoint(targetPos.x, targetPos.y, 0, pItemSkill, true, &bToClose) && !pMe->IsSelectingPoint();
			}
			if (IsInSkillAttackRange)
				pSkill->bAvailable = bAvailable;
			else
				pSkill->bAvailable = true;
			*/
		}
		// 主将
		for ( int n=0; n<thePlayerRole.m_HeroSkillBag.GetSkillNum(); n++ )
		{
			SCharSkill *pSkill;
			pSkill = thePlayerRole.m_HeroSkillBag.GetSkillByIndex( n );
			if ( !pSkill ||
				pSkill->ustSkillID == InvalidLogicNumber )
			{
				continue;
			}

			ItemDefine::SItemSkill *pItemSkill;
			pItemSkill = GettheItemDetail().GetSkillByID( pSkill->ustSkillID,
				pSkill->stSkillLevel );
			if ( !pItemSkill )
				continue;

			bool has = false;
			if (s_CUI_ID_FRAME_SKILL.IsVisable() && s_CUI_ID_FRAME_SKILL.CHECKBOX_Job_IsChecked())
				has = true;
			else if( pItemSkill->specialSkillType >= ItemDefine::ESST_Team && pItemSkill->specialSkillType < ItemDefine::ESST_TeamMax )	// 小队技能
				has = true;
			else
			{
				for (int i = 0; i < More_iHotkey; ++i)
				{
					if (thePlayerRole.m_pHotKeyBag[i].ShortCut.BagIndex == n)
					{
						has = true;
						break;
					}
				}
			}

			if( !has )
				continue;

			// 采集技能跳过
			if( IsCollectSkill(pSkill->ustSkillID) )
				continue;

			bool bAvailable = false;
			short shCastType = pItemSkill->shCastType;

			// 单一目标
			if ( (shCastType == ItemDefine::casttype_singletarget && pItemSkill->usSpecialTargetType == ItemDefine::STT_NONE) ||
				shCastType == ItemDefine::casttype_AOETargetcirclearea )
			{
				bool bIsTest = false;
				if( pItemSkill->ustCastTarget == ItemDefine::casttarget_team )
				{
					bAvailable = pMe->TryUseSkill( pMe, pItemSkill, true );
					bIsTest = true;
				}
				else if( !bIsTest && pItemSkill->ustCastTarget == ItemDefine::casttarget_pet )
				{
					if( pMe->GetPetID() <= -1 )
					{
						bAvailable = FALSE;
					}
					else
					{
						CPlayer* pPet = theHeroGame.GetPlayerMgr()->FindByID(pMe->GetPetID());
						if( pPet )
							bAvailable = pMe->TryUseSkill( pPet, pItemSkill, true );
						else
							bAvailable = FALSE;
					}
					bIsTest = true;
				}
				if( bIsTest == false && ( pPlayer == NULL||pPlayer->IsMonster()||pPlayer->IsNpc()) )
				{
					if (pItemSkill->ustCastTarget == ItemDefine::casttarget_me||
						pItemSkill->ustCastTarget == ItemDefine::casttarget_friendlive )
					{						
						bAvailable = pMe->TryUseSkill( pMe, pItemSkill, true );
						bIsTest = true;
					}
				}
				if ( pPlayer&&bIsTest == false )
				{
					bool bTestAG = true;

					if (pPlayer->IsPlayer())
					{
						if (pItemSkill->ustCastTarget == ItemDefine::casttarget_me)
						{
							bAvailable = pMe->TryUseSkill( pMe, pItemSkill, true );
							bTestAG = false;
						}
					}
					if (bTestAG == true)
					{
						bAvailable = pMe->TryUseSkill( pPlayer, pItemSkill, true );
					}
				}
			}
			// 范围
			else
			{
				bAvailable = pMe->TryUseSkill( NULL, pItemSkill, true );
			}
			if ( bAvailable != pSkill->bAvailable )
			{
				bNeedUpdate = true;
			}
			pSkill->bAvailable = bAvailable;
		}

		// 坐骑
		for ( int n=0; n<thePlayerRole.m_MountSkillBag.GetSkillNum(); n++ )
		{
			SCharSkill *pSkill;
			pSkill = thePlayerRole.m_MountSkillBag.GetSkillByIndex( n );
			if ( !pSkill ||
				pSkill->ustSkillID == InvalidLogicNumber )
			{
				continue;
			}
			bool has = false;
			for (int i = 0; i < More_iHotkey; ++i)
			{
				if (thePlayerRole.m_pHotKeyBag[i].ShortCut.BagIndex == n)
				{
					has = true;
					break;
				}
			}

			if( !has )
				continue;

			// 采集技能跳过
			if( IsCollectSkill(pSkill->ustSkillID) )
				continue;

			ItemDefine::SItemSkill *pItemSkill;
			pItemSkill = GettheItemDetail().GetSkillByID( pSkill->ustSkillID,
				pSkill->stSkillLevel );
			if ( !pItemSkill )
				continue;

			bool bAvailable = false;
			short shCastType = pItemSkill->shCastType;

			// 单一目标
			if ( (shCastType == ItemDefine::casttype_singletarget && pItemSkill->usSpecialTargetType == ItemDefine::STT_NONE) ||
				shCastType == ItemDefine::casttype_AOETargetcirclearea )
			{
				bool bIsTest = false;
				if ( pPlayer == NULL||pPlayer->IsMonster()||pPlayer->IsNpc() )
				{
					if (pItemSkill->ustCastTarget == ItemDefine::casttarget_me||
						pItemSkill->ustCastTarget == ItemDefine::casttarget_friendlive||
						pItemSkill->ustCastTarget == ItemDefine::casttarget_team)
					{						
						bAvailable = pMe->TryUseSkill( pMe, pItemSkill, true );
						bIsTest = true;
					}				
				}
				if ( pPlayer&&bIsTest == false )
				{
					bool bTestAG = true;

					if (pPlayer->IsPlayer())
					{
						if (pItemSkill->ustCastTarget == ItemDefine::casttarget_me)
						{
							bAvailable = pMe->TryUseSkill( pMe, pItemSkill, true );
							bTestAG = false;
						}
					}
					if (bTestAG == true)
					{
						bAvailable = pMe->TryUseSkill( pPlayer, pItemSkill, true );
					}
				}
			}
			// 范围
			else
			{
				bAvailable = pMe->TryUseSkill( NULL, pItemSkill, true );
			}
			if ( bAvailable != pSkill->bAvailable )
			{
				bNeedUpdate = true;
			}
			pSkill->bAvailable = bAvailable;
		}

		if ( bNeedUpdate )
		{
			s_CUI_ID_FRAME_MAIN.RefeashHotKey();
			s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
			if(s_CUI_ID_FRAME_PetMain.IsVisable())
			{
				s_CUI_ID_FRAME_PetMain.Refresh();
			}
			if (s_CUI_ID_FRAME_SKILL.IsVisable())
				s_CUI_ID_FRAME_SKILL.NeedRefresh();
		}
		if (IsVisable())
		{
			if ( m_nSelId >= 0 )
			{
				CPlayer*	pPlayer = theHeroGame.GetPlayerMgr()->FindByID( m_nSelId );
				if (pPlayer)
				{
					
					if ( pPlayer->IsHPInfoValid() == true )
					{
						if( pPlayer->IsNpc() && !pMe->isNPCCanAttack( pPlayer ) )
						{
							m_pID_PROGRESS_Hp->SetValue( 1000 );
							//					m_pID_PROGRESS_Mp->SetValue( 1000 );

							char szPercent[56] = {0};
							MeSprintf_s( szPercent,sizeof(szPercent)/sizeof(char) - 1, theXmlString.GetString(eClient_Target_Hp_Percent), ((float)pPlayer->GetHp())/pPlayer->GetHpMax() * 100);
							_pText_Percent->SetText( szPercent );
						}
						else
						{
							int nHp = 0;
							int nHpTail = 0;

							if( (float)(pPlayer->GetHp()) >= pPlayer->GetHpMax())
							{
								m_pID_PROGRESS_Hp->SetValue( 1000 );
								char szPercent[56] = {0};
								MeSprintf_s( szPercent, sizeof(szPercent)/sizeof(char) - 1,theXmlString.GetString(eClient_Target_Hp_Percent), ((float)pPlayer->GetHp())/pPlayer->GetHpMax() * 100);
								_pText_Percent->SetText( szPercent );
								//lyh++ 解决最后一次差20点不满 ，主要是在自动恢复这一点。
								 MeSprintf_s(szPercent, sizeof(szPercent)/sizeof(char) - 1, "%d/%d", (int)pPlayer->GetHp(), (int)pPlayer->GetHpMax());
								m_pID_TEXT_HP->SetText(szPercent);
							}
							else
							{
								float fValue = ((float)pPlayer->GetHp())/pPlayer->GetHpMax() * 1000;
								if (fValue > 0 && fValue < 17)
									fValue = 17; // 不能小于20，要不然看不见了
								m_pID_PROGRESS_Hp->SetValue( fValue );
								m_pID_PROGRESS_Hp->GetFrameFather()->SetRedraw();//lyh++
								//zhuxincong 11.20 战斗中每次刷新目标的血量
								char szText[128] = {0};

								if (theHeroGame.GetPlayerMgr()&&theHeroGame.GetPlayerMgr()->GetMe() == pPlayer)
								{
									//这里只用一个值就好 当目标是自己的时候 lyh++
									MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d/%d", thePlayerRole.GetData( CPlayerRole::TYPE_HP ),thePlayerRole.GetData( CPlayerRole::TYPE_HPMAX ));
								}else
								{
                                  MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d/%d", (int)pPlayer->GetHp(), (int)pPlayer->GetHpMax());
								}
								
								m_pID_TEXT_HP->SetText(szText);
								//
								s_CUI_Group.updataTeamerHP( m_nSelId, pPlayer->GetHp() );

								char szPercent[56] = {0};
								MeSprintf_s( szPercent,sizeof(szPercent)/sizeof(char) - 1, theXmlString.GetString(eClient_Target_Hp_Percent), ((float)pPlayer->GetHp())/pPlayer->GetHpMax() * 100);
								_pText_Percent->SetText( szPercent );
							}

							nHp = m_pID_PROGRESS_Hp->GetValue();
							nHpTail = m_pID_PROGRESS_HpTail->GetValue();
							if( nHpTail > nHp )
							{
								static DWORD dwStep = 0;
								dwStep = g_fHpTailSpeed * g_dwLastFrameCostTime;
								if( dwStep < 1 )
								{
									dwStep = 1;
								}
								nHpTail -= dwStep;
							}
							else
							{
								nHpTail = nHp;
							}

							m_pID_PROGRESS_HpTail->SetValue( nHpTail );

							//
							// MP
							//
							// 					if (pPlayer->GetMp() >= pPlayer->GetMpMax())
							// 					{
							// 						m_pID_PROGRESS_Mp->SetValue( 1000 );
							// 					}
							// 					else
							// 					{
							// 						m_pID_PROGRESS_Mp->SetValue( ((float)pPlayer->GetMp())/pPlayer->GetMpMax() * 1000);
							// 					}

							// level
							if(m_nPlayerLevel != pPlayer->GetLevel())
							{
								m_nPlayerLevel = pPlayer->GetLevel();
								m_pID_TEXT_Lvl->SetText( m_nPlayerLevel );
							}
						}
					}

					// Struct
					m_pID_LISTIMG_Status->Clear();
					m_pID_LISTIMG_Status->SetVisable( false );
					SCharBuff* pStatus = NULL;
					ControlIconDrag::S_ListImg stItem;

					int i = 0;
					for ( int n=0; n < pPlayer->m_cFightStatus.GetBufferStatusCount(); n++ )
					{
						pStatus = pPlayer->m_cFightStatus.GetBuff( n );
						if ( !pStatus )
							continue;

						m_pID_LISTIMG_Status->SetVisable( true );
						stItem.SetData( pStatus->StatusID, pStatus->iLevel, eIcon_Enable, true, eTipFlag_Status );
						if(pStatus->lapoverNum <= 0)
						  stItem.m_pkIconInfo->m_strHotKey.clear();
						else
						{
							char szBuf[32] = {0};
							MeSprintf_s(szBuf,sizeof(szBuf),"%d",pStatus->lapoverNum);
							stItem.m_pkIconInfo->m_strHotKey = szBuf;
						}
						m_pID_LISTIMG_Status->SetItem( &stItem, i );

						// BUF显示剩余时间      added by zhuomeng.hu		[12/7/2010]
						ItemDefine::SItemStatus* pItemStatus = NULL;
						pItemStatus = GettheItemDetail().GetStatus( pStatus->StatusID, pStatus->iLevel );
						if( pItemStatus && i < m_pID_LISTIMG_Status->GetEnableCnt() )
						{
							if( pStatus->bStop )
							{
								m_pID_LISTIMG_Status->SetSpareTime( i, 0xffffffff, pStatus->dwStartTime );
							}
							else if( pItemStatus->IsForeverStatus() )
							{
								m_pID_LISTIMG_Status->SetSpareTime( i, MAX_STATUS_SPARETIME, pStatus->dwStartTime );
							}
							else
							{
								m_pID_LISTIMG_Status->SetSpareTime( i, pStatus->dwDurationTime, pStatus->dwStartTime );
							}
						}

						i++;
					}
					m_pID_LISTIMG_Status->RefreshTipShow(theUiManager.m_ptMoust.x,theUiManager.m_ptMoust.y);
				}
				else
				{
					theHeroGame.GetPlayerMgr()->SetLockNpc(-1);
					SetPlayer(-1);
				}
			}
		}
		//
		dwLastUpdateTime = HQ_TimeGetTime();
	}
	IsTargetUIUpDateIng = false;
	return true;
	unguard;
	

}
bool CUI_ID_FRAME_Target::OnFrameRender()
{
	guardfunc;
	return true;
	unguard;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Target::ID_LISTIMG_StatusOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														ControlIconDrag::S_ListImg* pItemDrag,
														ControlIconDrag::S_ListImg* pItemSrc )
{
	guardfunc;
	if( !m_pID_FRAME_Target )
		return false;
	return false;
	unguard;
}
bool CUI_ID_FRAME_Target::ID_LISTIMG_StatusOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
														 ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	if( !m_pID_FRAME_Target )
		return false;
	return false;
	unguard;
}
bool CUI_ID_FRAME_Target::ID_LISTIMG_StatusOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	if( !m_pID_FRAME_Target )
		return false;
	return false;
	unguard;
}

void CUI_ID_FRAME_Target::InitializeAtEnterWorld()
{
    _SetVisable( false );
}

// 装载UI
bool CUI_ID_FRAME_Target::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\Target.meui", false, UI_Render_LayerFirst );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\Target.UI]失败")
			return false;
	}
	return DoControlConnect();
	unguard;
}

void ID_FRAME_Target_onVisibleChanged( ControlObject* pUIObject )
{
    if ( !pUIObject->IsVisable() )
    {
		theHeroGame.GetPlayerMgr()->cancelBehavior();
		s_CUI_ID_FRAME_RBTNMENU.SetVisable(false);
    }
}

bool ID_FRAME_Target_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
    guardfunc
    return false;
    unguard
}

// 关连控件
bool CUI_ID_FRAME_Target::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_Target, s_CUI_ID_FRAME_TargetOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Target, s_CUI_ID_FRAME_TargetOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_Target, ID_LISTIMG_Status, s_CUI_ID_FRAME_TargetID_LISTIMG_StatusOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Target, ID_LISTIMG_Status, s_CUI_ID_FRAME_TargetID_LISTIMG_StatusOnIconLDBClick );

	m_pID_FRAME_Target = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Target );
	m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_Target, ID_TEXT_Name );
	m_pID_TEXT_HP = (ControlText*)theUiManager.FindControl(ID_FRAME_Target,ID_TEXT_HP);
	m_pID_PROGRESS_Hp = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Target, ID_PROGRESS_Hp );
	m_pID_PROGRESS_HpTail = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Target, ID_PROGRESS_HpTail );
	m_pID_LISTIMG_Status = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Target, ID_LISTIMG_Status );
	m_pID_LISTIMG_Status->ShowPressEffect( false );
	m_pID_TEXT_Lvl = (ControlText*)theUiManager.FindControl( ID_FRAME_Target, ID_TEXT_Lvl );
	_pText_TargetName = (ControlText*)theUiManager.FindControl( ID_FRAME_Target, ID_TEXT_TargetName );
	assert(_pText_TargetName);
	_pText_Percent = (ControlText*)theUiManager.FindControl( ID_FRAME_Target, ID_TEXT_percent );
	assert( _pText_Percent );
	m_pID_PICTURE_Hair = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Target, ID_PICTURE_Hair );
	assert( m_pID_PICTURE_Hair );
	m_pID_PICTURE_Face = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Target, ID_PICTURE_Face );
	assert( m_pID_PICTURE_Face );
//	m_pID_PROGRESS_Mp = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Target, ID_PROGRESS_Mp );
	m_pID_PICTURE_Target = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Target, ID_PICTURE_Target );
	m_pID_PICTURE_TargetHair = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Target, ID_PICTURE_TargetHair );
	m_pID_PICTURE_TargetFace = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Target, ID_PICTURE_TargetFace );
	m_pID_PROGRESS_TargetHp = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Target, ID_PROGRESS_TargetHp );
	
	m_pID_TEXT_TargetName = (ControlText*)theUiManager.FindControl( ID_FRAME_Target, ID_TEXT_TargetName );
	m_pID_PICTURE_Choose = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Target, ID_PICTURE_Choose );
    m_pID_TEXT_TargetLvl = (ControlText*)theUiManager.FindControl( ID_FRAME_Target, ID_TEXT_TargetLvl );
    m_pID_PICTURE_BgTargetFace = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Target, ID_PICTURE_BgTargetFace );
    m_pID_PICTURE_ProPic[0] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Target, ID_PICTURE_Warrior );
    m_pID_PICTURE_ProPic[1] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Target, ID_PICTURE_Mage );
    m_pID_PICTURE_ProPic[2] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Target, ID_PICTURE_Taoist );
    m_pID_PICTURE_ProPic[3] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Target, ID_PICTURE_Assassin );     
	m_pID_PICTURE_ProPic[4] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Target, ID_PICTURE_Hunter );
	
	m_pID_PICTURE_Group[EPhyle_Human] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Target, ID_PICTURE_Ren );
	m_pID_PICTURE_Group[EPhyle_Machine] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Target, ID_PICTURE_Ji );
	m_pID_PICTURE_Group[EPhyle_Deity] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Target, ID_PICTURE_Shen );
	m_pID_PICTURE_Group[EPhyle_Ghost] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Target, ID_PICTURE_Gui );
	m_pID_PICTURE_Group[EPhyle_Immortal] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Target, ID_PICTURE_Xian );
	m_pID_PICTURE_Group[EPhyle_Bogey] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Target, ID_PICTURE_Yao );
	m_pID_PICTURE_Group[EPhyle_Beast] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Target, ID_PICTURE_Shou );
	m_pID_PICTURE_Group[EPhyle_Demon] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Target, ID_PICTURE_Mo );

	m_pID_TEXT_Hero = (ControlText*)theUiManager.FindControl( ID_FRAME_Target, ID_TEXT_Hero );

    assert( _pText_Percent );
    assert(_pText_TargetName);
    assert( m_pID_PICTURE_Face );
    assert( m_pID_FRAME_Target );
	assert( m_pID_PICTURE_TargetHair );
	m_pID_FRAME_Target->SetVisable( false );
	assert( m_pID_TEXT_Name );
	assert( m_pID_TEXT_HP);
	assert( m_pID_PROGRESS_Hp );
	assert( m_pID_PROGRESS_HpTail );
	assert( m_pID_LISTIMG_Status );
	assert( m_pID_PICTURE_Choose );
	assert( m_pID_TEXT_Hero );
	
	SetVisable( false );

    m_pID_LISTIMG_Status->ShowPressEffect( false );
    int nConWidth = m_pID_TEXT_Name->GetWidth();
    int nShowCnt = m_pID_TEXT_Name->GetWidth() / 7 + 1;
    m_pID_TEXT_Name->SetSingleMaxTextCnt( nShowCnt );

	m_pID_FRAME_Target->SetOnRBtnDown( ID_FRAME_Target_OnRBClick );
	m_pID_FRAME_Target->SetOnClickFun( ID_FRAME_Target_OnRBClick );
    m_pID_FRAME_Target->SetOnVisibleChangedFun( ID_FRAME_Target_onVisibleChanged );
    m_pID_FRAME_Target->SetMsgProcFun( ID_FRAME_Target_MsgProc );
	m_pID_FRAME_Target->SetFadeInorFadeOut(true);
	m_pID_PICTURE_Choose->SetButtonClickFun(ID_FRAME_TargetTarget_OnClick);

	m_pID_LISTIMG_Status->SetMsgHoldup(false);
	m_pID_LISTIMG_Status->SetShowAllInfo( true );

	m_ttGroup.AddControl(m_pID_PICTURE_Target);
	m_ttGroup.AddControl(m_pID_PICTURE_TargetHair);
	m_ttGroup.AddControl(m_pID_PICTURE_TargetFace);
	m_ttGroup.AddControl(m_pID_PROGRESS_TargetHp);
	m_ttGroup.AddControl(m_pID_TEXT_TargetName);
	m_ttGroup.AddControl(m_pID_PICTURE_Choose);
    m_ttGroup.AddControl(m_pID_TEXT_TargetLvl);
    m_ttGroup.AddControl(m_pID_PICTURE_BgTargetFace);
	m_ttGroup.SetVisible(false);


	//m_ProgressGroup.SetVisible(false);
    //CreateProgressAni();

	return true;
	unguard;
}
// 卸载UI
bool CUI_ID_FRAME_Target::_UnLoadUI()
{
	guardfunc;
	m_ttGroup.Clear();

	CLOSE_SCRIPT( eUI_OBJECT_Target );
	ResetMembers();

	return theUiManager.RemoveFrame( "data\\ui\\Target.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_Target::_IsVisable()
{
	guardfunc;
    if( !m_pID_FRAME_Target )
        return false;
	return m_pID_FRAME_Target->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_Target::_SetVisable( const bool bVisable )
{
	if (!m_pID_FRAME_Target)
		return;
	if ( bVisable != m_pID_FRAME_Target->IsVisable() )
	{
		
        if (bVisable && m_nSelId == -1)
        {
			m_pID_FRAME_Target->SetVisable( false );
        }else
		{
			m_pID_FRAME_Target->SetVisable( bVisable );
		}
		
		
	}
	TeamPlayerFrameManage.HidePicChoise();
	TeamPlayerFrameManage.HidePicChoisept();
	if( !bVisable )
	{
		if (s_CUI_ID_FRAME_TargetProgrss.IsVisable())
		{
			s_CUI_ID_FRAME_TargetProgrss.Reset();
		}
	}
	else
	{
		CUI_ID_FRAME_Team_Player* pFrame = TeamPlayerFrameManage.GetTeamFrameById(m_nSelId);
		if (pFrame)
		{
			if( pFrame->GetPICTURE_choise1() )
				pFrame->GetPICTURE_choise1()->SetVisable(true);
			if( pFrame->GetPICTURE_choise1pt() )
				pFrame->GetPICTURE_choise1pt()->SetVisable(true);
		}
	}
	nTargetTargetId = -1;
	m_ttGroup.SetVisible(false);
}

void SetNameColor(DWORD& colorName, CPlayer* pPlayer)
{
	if (!pPlayer)
	{
		return;
	}

	colorName = 0xffffffff;
	switch(pPlayer->GetCharType())
	{
	case Object_Player:
		{
			if( pPlayer->GetRealCountry() != thePlayerRole.GetCountry() )
				colorName = Color_Config.getColor( CC_Player_OtherCountry ) ;
			else
				colorName = pPlayer->GetPkNameColor();
		}
		break;
	case Object_Monster:
		{
			if(pPlayer->HaveMaster())
			{
				colorName = Color_Config.getColor(CC_PetTitle);

				CPlayer *pMaster = theHeroGame.GetPlayerMgr()->FindByID( pPlayer->GetMasterID() );
				if( pMaster )
				{
					if( pMaster->GetRealCountry() != thePlayerRole.GetCountry())
						colorName = Color_Config.getColor(CC_Pet_OtherCountry);
				}

				pPlayer->SetPetNameColor(pMaster,colorName);
			}
			else
			{
				ItemDefine::SMonster *pMonster = GettheItemDetail().GetMonsterByName(pPlayer->GetName());
				if (pMonster && pMonster->nIsInitiative)
				{
					if( theHeroGame.GetPlayerMgr()->GetMe() )
					{
						int l = pPlayer->GetLevel() - theHeroGame.GetPlayerMgr()->GetMe()->GetLevel();
						if (l >= -5 && l <= 5)
							colorName = Color_Config.getColor(CC_MonsterLevelRange5);
						else if (l < -5)
							colorName = Color_Config.getColor(CC_MonsterLevelLow5);
						else
							colorName = Color_Config.getColor(CC_MonsterLevelUp5);
					}
					else
						colorName = Color_Config.getColor(CC_MonsterLevelUp5);
				}
				else
				{
					colorName = Color_Config.getColor(CC_MonsterNormal);
				}
			}
		}
		break;
	case Object_Npc:
		{
			if(pPlayer->GetRealCountry() == CountryDefine::Country_Init)
				colorName = Color_Config.getColor(CC_NPC_NoCountry);
			else if(pPlayer->GetRealCountry() == thePlayerRole.GetCountry())
                colorName = Color_Config.getColor( CC_NPC );
			else
                colorName = Color_Config.getColor( CC_NPC_OtherCountry );
		}
		break;
	}
}

void CUI_ID_FRAME_Target::SetHeroName(const char* text, DWORD color)
{
	if( !m_pID_FRAME_Target || !m_pID_TEXT_Hero )
		return;

	if( !text )
		return;

	m_pID_TEXT_Hero->SetText(text, color);
}

void CUI_ID_FRAME_Target::SetPlayer( const GameObjectId nId )
{
	guardfunc;
    if( !IsUILoad() )
        SetVisable( true );

	if( !m_pID_FRAME_Target )
		return;

	//LYH挂机中选择目标 ，如果目标是不可以被攻击的则跳过
	if(s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight() )
	{
		CPlayer* Player = theHeroGame.GetPlayerMgr()->FindByID( nId );
		if (Player && Player->IsMonster() && m_nSelId != -1)
		{
			if(Player->GetRealCountry() != CountryDefine::Country_Init&&
				thePlayerRole.m_charinfo.baseinfo.aptotic.ucCountry != CountryDefine::Country_Init&&
				thePlayerRole.m_charinfo.baseinfo.aptotic.ucCountry ==Player->GetRealCountry())
			{
				m_nSelId = -1;
				return;
			}
		}

		//挂机的时候不能手动选择玩家，不支持对玩家挂机
		if(Player && Player->IsPlayer() && !s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().GetIsNeedHpSkillTeam())
		{
			m_nSelId = -1;
			return;
		}

		if ( Player && 
			(Player->GetTypeStatus() == MonsterDefine::StatusUnMoveNpc || 
			 Player->GetTypeStatus() == MonsterDefine::StatusMoveNpc) 
			)
		{
			m_nSelId = -1;
			return;
		}

	}
      
	
   m_nSelId = nId;
	
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID( m_nSelId );

	
	//m_pID_PICTURE_Face->SetEnable(true);

	if ( !pPlayer || pPlayer->GetDistanceToRole() > PLAYER_RENDER_DIST_MAX)
	{
		m_nSelId = -1;
		SetVisable(false);
		return;
	}

    if( pPlayer->IsCollection(false) )
    {
        SetVisable(false);
        return;
    }

	DWORD colorName = 0xFFFFFFFF;
	SetNameColor(colorName, pPlayer);

	if(m_pID_TEXT_Name)
	{
		m_pID_TEXT_Name->SetText(pPlayer->GetName(), colorName);
	}

	SetHeroName( "", 0 );
	CItemHero::SItemHero *itemHero = theItemHero.FindHeroByHeroID(pPlayer->GetHeroID());
	if ( itemHero )
	{
		ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( itemHero->itemd_id );
		if( pItemCommon )
		{
			DWORD color = S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel );
			std::string strHero;
			strHero += "(" + itemHero->hero_name + ")";
			SetHeroName( strHero.c_str(), color );
		}
	}

	m_nPlayerLevel = pPlayer->GetLevel();
	if(m_pID_TEXT_Lvl)
		m_pID_TEXT_Lvl->SetText( m_nPlayerLevel );

	SetVisable(true);
	s_CUI_ID_FRAME_TargetProgrss.SetVisable(false);
    for( int i = 0; i < EArmType_Sniper; ++i )
    {
        m_pID_PICTURE_ProPic[i]->SetVisable( false );
    }
    if( pPlayer->IsPlayer() && pPlayer->GetProfession() >= 0 && pPlayer->GetProfession() < EArmType_Sniper )
    {
        m_pID_PICTURE_ProPic[pPlayer->GetProfession()]->SetVisable( true );
    }
	for (int i =EPhyle_Human; i< EPhyle_MaxCount; i++ )
	{
		m_pID_PICTURE_Group[i]->SetVisable(false);
	}
	if (pPlayer->IsMonster())
	{
		ItemDefine::SMonster *pMonster = GettheItemDetail().GetMonsterById(pPlayer->GetMonsterID() );
		if (pMonster != NULL && pMonster->phyle >=EPhyle_Human &&  pMonster->phyle < EPhyle_MaxCount)
		{
			m_pID_PICTURE_Group[pMonster->phyle]->SetVisable(true);
		}		
	}
	if (pPlayer->IsNpc())
	{
			NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByName(pPlayer->GetName());
			if (pNpc != NULL && pNpc->phyle >=EPhyle_Human &&  pNpc->phyle < EPhyle_MaxCount )
			{
				m_pID_PICTURE_Group[pNpc->phyle]->SetVisable(true);
			}
	}
	//if ( pPlayer->IsMonster() )
	//{
	//	switch( pPlayer->GetMonsterType() )
	//	{
	//	// 精英怪物
	//	case eMT_LeaderMonster:
	//		m_pID_PICTURE_MonsterType->SetPicName( LEADER_MONSTER_PIC );
	//		break;
	//	case eMT_BossMonster:
	//		m_pID_PICTURE_MonsterType->SetPicName( BOSS_MONSTER_PIC );
	//		break;
	//	default:
	//		m_pID_PICTURE_MonsterType->SetPicName( NORMAL_MONSTER_PCI );
	//		break;
	//	}
	//}
	//else
	//{
	//	m_pID_PICTURE_MonsterType->SetPicName( NORMAL_MONSTER_PCI );
	//}
    MexResMgr::Record* record = GetMexResMgr()->GetRecord(pPlayer->GetModelId());
    if (record && m_pID_PICTURE_Hair && !pPlayer->IsPlayer())
    {
		m_pID_PICTURE_Hair->SetPicName(record->headPicture.c_str());
		m_pID_PICTURE_Face->SetPicName(record->headPicture.c_str());
		
		bool IsInTeam = false;
		CPlayer* pSelBeLongPlayer = theHeroGame.GetPlayerMgr()->FindByID(pPlayer->GetBeLongID());
		if(pSelBeLongPlayer && thePlayerRole.IsTeamMember(pSelBeLongPlayer->GetName()))
		{
			IsInTeam = true;
		}
		if(pPlayer->GetBeLongID() != 0 && !pPlayer->IsPlayer() && (pPlayer->GetBeLongID() != theHeroGame.GetPlayerMgr()->GetMe()->GetID() &&  !IsInTeam  && pPlayer->GetBeLongID() !=0 ))
		{
			//m_pID_PICTURE_Face->SetEnable(false);
			SetUIPicStates(false,false);
		}
    }
	else if (pPlayer->IsPlayer())
	{
        //modified by ZhuoMeng.Hu		[9/19/2010]
        //std::string portraitName = s_CUI_ID_FRAME_CREATE.GetPortraitName( pPlayer->GetSex(), pPlayer->GetPortraitId() );
        //portraitName = "Data\\Ui\\" + portraitName;
        //m_pID_PICTURE_Face->SetPicName( portraitName.c_str() );


		char sex[2][32] = { "Male", "Female" };

		int hairId = pPlayer->GetEquip()[eKeyAll_Hair].iModelID;
		int faceId = pPlayer->GetEquip()[eKeyAll_Face].iModelID;

		bool find1 = false;
		char filename[256] = {0};

		//主将头像不显示
		/*if (pPlayer->GetHeroID() != INVALID_HERO_ID)
		{
			CItemHero::SItemHero *itemHero = theItemHero.FindHeroByHeroID(pPlayer->GetHeroID());
			if (itemHero == NULL)
				return;

			PlayerInfoMgr::Instance()->GetPlayerHeadPic(pPlayer, filename);
			m_pID_PICTURE_Hair->SetPicName(filename);
			m_pID_PICTURE_Face->SetPicName(filename);
		}
		else*/
		{
			MeSprintf_s(filename, sizeof(filename)/sizeof(char) - 1, "%s/Data/Ui/HeadPicture/Player/Target%sHairHead_%d_%d.dds",
				GetRootPath(), sex[pPlayer->GetSex()], hairId,faceId);
			f_Handle* fp = packet_namespace::w_fopen(filename, "r");
			if (fp)
			{
				find1 = true;
				packet_namespace::w_fclose(fp);
			}

			//bool find2 = false;
			//char filename2[256] = {0};
			//MeSprintf_s(filename2, sizeof(filename2)/sizeof(char) - 1, "%s/Data/Ui/HeadPicture/Player/Target%sFaceHead%d.dds",
			//	GetRootPath(), sex[pPlayer->GetSex()], faceId);
			//fp = packet_namespace::w_fopen(filename2, "r");
			//if (fp)
			//{
			//	find2 = true;
			//	packet_namespace::w_fclose(fp);
			//}

			if (find1 /*&& find2*/)
			{

				//m_pID_PICTURE_Hair->SetPicName(filename);
				m_pID_PICTURE_Face->SetPicName(filename);
			}
			else
			{
				if (pPlayer->GetSex() == Sex_Male)
				{
					//m_pID_PICTURE_Hair->SetPicName("Data/Ui/HeadPicture/Player/DefaultTargetMale.dds");
					m_pID_PICTURE_Face->SetPicName("Data/Ui/HeadPicture/Player/DefaultTargetMale.dds");
				}
				else
				{
					//m_pID_PICTURE_Hair->SetPicName("Data/Ui/HeadPicture/Player/DefaultTargetFemale.dds");
					m_pID_PICTURE_Face->SetPicName("Data/Ui/HeadPicture/Player/DefaultTargetFemale.dds");
				}
			}
		}
	}
    
	int nHp = ((float)pPlayer->GetHp())/pPlayer->GetHpMax() *1000;
	//zhuxincong 11.20 选中目标后得到目标的血量
	


	char szText[128] = {0};
	if (theHeroGame.GetPlayerMgr()&&theHeroGame.GetPlayerMgr()->GetMe() == pPlayer)
	{
        //这里只用一个值就好 当目标是自己的时候 lyh++
		MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d/%d", thePlayerRole.GetData( CPlayerRole::TYPE_HP ), thePlayerRole.GetData( CPlayerRole::TYPE_HPMAX ));
	}else
	{
       MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d/%d", (int)pPlayer->GetHp(), (int)pPlayer->GetHpMax());
	}
	
	m_pID_TEXT_HP->SetText(szText);
	m_pID_PROGRESS_Hp->SetValue( nHp );
	m_pID_PROGRESS_HpTail->SetValue( nHp );
	m_pID_PROGRESS_Hp->GetFrameFather()->SetRedraw();//lyh++ 解决实时更新

	char szPercent[56] = {0};
	MeSprintf_s( szPercent, sizeof(szPercent)/sizeof(char) - 1,theXmlString.GetString(eClient_Target_Hp_Percent), ((float)pPlayer->GetHp())/pPlayer->GetHpMax() *100);
	_pText_Percent->SetText( szPercent );
	unguard;
}

bool CUI_ID_FRAME_Target::ID_FRAME_Target_OnRBClick( ControlObject* pSender )
{
	guardfunc;
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID( s_CUI_ID_FRAME_Target.GetPlayerID() );

	if(pPlayer)
	{
		if( pPlayer->IsPlayer() && theHeroGame.GetPlayerMgr()->GetMe() != pPlayer)
		{
			if( !s_CUI_ID_FRAME_RBTNMENU.IsVisable() )
			{
				RECT rc;
				pSender->GetRealRect(&rc);
				s_CUI_ID_FRAME_RBTNMENU.SetPrivateName(pPlayer->GetName());
				s_CUI_ID_FRAME_RBTNMENU.SetDBID( thePlayerRole.GetTeamMemberId(pPlayer->GetName() ));
				s_CUI_ID_FRAME_RBTNMENU.SetVisable( true );
				s_CUI_ID_FRAME_RBTNMENU.SetPos( rc.right+5, rc.top);
			}
			else
				s_CUI_ID_FRAME_RBTNMENU.SetVisable( false );
		}
		else if (pPlayer->IsMonster()&& pPlayer->GetMasterID() > -1 && pPlayer->GetSubMonsterType() != Object_MonsterProtected) //判断宠物
		{
			//在此可以判断宠物主人身份
 			CPlayer *pMaster = theHeroGame.GetPlayerMgr()->FindByID(pPlayer->GetMasterID());
 			if (pMaster != NULL)
 			{
 				if (pMaster ->GetID() != theHeroGame.GetPlayerMgr()->GetMe()->GetID())//不是自己
 				{
					if (!s_CUI_ID_FRAME_SuAnimalMenu.IsVisable())
					{
						s_CUI_ID_FRAME_SuAnimalMenu.SetVisable(true);
						if (s_CUI_ID_FRAME_SuAnimalMenu.GetXiuXiBtn() != NULL)
						{
							s_CUI_ID_FRAME_SuAnimalMenu.GetXiuXiBtn()->SetEnable(false);
						}
						if (s_CUI_ID_FRAME_SuAnimalMenu.GetFeedBtn() != NULL)
						{
							s_CUI_ID_FRAME_SuAnimalMenu.GetFeedBtn()->SetEnable(false);
						}
						if (s_CUI_ID_FRAME_SuAnimalMenu.GetCureBtn() != NULL)
						{
							s_CUI_ID_FRAME_SuAnimalMenu.GetCureBtn()	->SetEnable(false);
						}
						s_CUI_ID_FRAME_SuAnimalMenu.SetPlayerID(pMaster->GetID());
					}
					else
					{
						s_CUI_ID_FRAME_SuAnimalMenu.SetVisable(false);
					}		
 				}
				else
				{
					/*
					 * Author: 2012-10-8 9:56:30 wangshuai
					 * Desc:   如果是护送怪, 不弹任何菜单
					 */
					if (pPlayer->GetSubMonsterType() == eMT_Protect)
						return true;

					s_CUI_ID_FRAME_SuAnimalMenu.SetVisable(true);
					s_CUI_ID_FRAME_SuAnimalMenu.SetCurrentPetIndex(pPlayer->GetName());
				}
 			}
			
		}
	}

	return true;
	unguard;
}
void CUI_ID_FRAME_Target::setTargetName( const char* szName)
{
	if (!m_pID_FRAME_Target)
		return;
	if( szName == NULL)
		_pText_TargetName->SetText("");
	else
		_pText_TargetName->SetText(szName);
}

void CUI_ID_FRAME_Target::UpdateBeLongID(uint32 ID)
{
	//目标 和 目标的目标
	CPlayer* pSelPlayer = theHeroGame.GetPlayerMgr()->FindByID(m_nSelId);//当前目标的对象
	SetUIPicStates(true,false);
	bool IsInTeam = false;
	if(pSelPlayer)
	{
		CPlayer* pSelBeLongPlayer = theHeroGame.GetPlayerMgr()->FindByID(pSelPlayer->GetBeLongID());
		if(pSelBeLongPlayer && pSelBeLongPlayer->IsPlayer() && thePlayerRole.IsTeamMember(pSelBeLongPlayer->GetName()))
		{
			IsInTeam = true;
		}
	}
	if(pSelPlayer && !pSelPlayer->IsPlayer() && pSelPlayer->GetBeLongID() == ID && (ID != theHeroGame.GetPlayerMgr()->GetMe()->GetID() && !IsInTeam && ID !=0 ))
	{
		SetUIPicStates(false,false);
	}

	CPlayer* pTargetPlayer = theHeroGame.GetPlayerMgr()->FindByID(nTargetTargetId);//目标的目标
	SetUIPicStates(true,true);
	IsInTeam = false;
	if(pTargetPlayer)
	{
		CPlayer* pTargetBeLongPlayer = theHeroGame.GetPlayerMgr()->FindByID(pTargetPlayer->GetBeLongID());
		if(pTargetBeLongPlayer && thePlayerRole.IsTeamMember(pTargetBeLongPlayer->GetName()))
		{
			IsInTeam = true;
		}
	}
	if(pTargetPlayer && !pTargetPlayer->IsPlayer() && pTargetPlayer->GetBeLongID() == ID && (ID != theHeroGame.GetPlayerMgr()->GetMe()->GetID()  &&  !IsInTeam  && ID !=0 ))
	{
		SetUIPicStates(false,true);
	}
}
void CUI_ID_FRAME_Target::SetUIPicStates(bool IsHeader,bool IsTarget)
{
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID( m_nSelId );
	if(!pPlayer) 
		return;
	MexResMgr::Record* record = GetMexResMgr()->GetRecord(pPlayer->GetModelId());
	if(!record)
		return;	
	if(IsTarget)
	{
		if(IsHeader)
		{
			m_pID_PICTURE_TargetFace->SetPicName(record->headPicture.c_str());
		}
		else
		{
			//设置UI的头像变灰
			string str = record->headPicture;
			str = str.insert(str.find_last_of("."),"_disable");
			m_pID_PICTURE_TargetFace->SetPicName(str.c_str());
		}
	}
	else
	{
		if(IsHeader)
		{
			m_pID_PICTURE_Face->SetPicName(record->headPicture.c_str());
		}
		else
		{
			//需要置灰 需要对字符串进行替换
			string str = record->headPicture;
			str = str.insert(str.find_last_of("."),"_disable");
			m_pID_PICTURE_Face->SetPicName(str.c_str());
 		}
	}
}
void CUI_ID_FRAME_Target::TeamStatesChange()
{
	//当玩家加入或者离开队伍的时候 更新目标UI
	CPlayer* pSelPlayer = theHeroGame.GetPlayerMgr()->FindByID(m_nSelId);
	CPlayer* pTargetPlayer = theHeroGame.GetPlayerMgr()->FindByID(nTargetTargetId);

	//m_pID_PICTURE_Face->SetEnable(true);
	SetUIPicStates(true,false);
	bool IsInTeam = false;
	if(pSelPlayer)
	{
		CPlayer* pSelBeLongPlayer = theHeroGame.GetPlayerMgr()->FindByID(pSelPlayer->GetBeLongID());
		if(pSelBeLongPlayer && thePlayerRole.IsTeamMember(pSelBeLongPlayer->GetName()))
		{
			IsInTeam = true;
		}
	}
	if(pSelPlayer && !pSelPlayer->IsPlayer() && (pSelPlayer->GetBeLongID() != theHeroGame.GetPlayerMgr()->GetMe()->GetID() &&  !IsInTeam  && pSelPlayer->GetBeLongID() !=0))
	{
		//m_pID_PICTURE_Face->SetEnable(false);
		SetUIPicStates(false,false);
	}

	//m_pID_PICTURE_TargetFace->SetEnable(true);
	SetUIPicStates(true,true);
	IsInTeam = false;
	if(pTargetPlayer)
	{
		CPlayer* pTargetBeLongPlayer = theHeroGame.GetPlayerMgr()->FindByID(pTargetPlayer->GetBeLongID());
		if(pTargetBeLongPlayer && thePlayerRole.IsTeamMember(pTargetBeLongPlayer->GetName()))
		{
			IsInTeam = true;
		}
	}
	if(pTargetPlayer && !pTargetPlayer->IsPlayer() && (pTargetPlayer->GetBeLongID() != theHeroGame.GetPlayerMgr()->GetMe()->GetID()  &&  !IsInTeam   && pTargetPlayer->GetBeLongID() !=0))
	{
		//m_pID_PICTURE_TargetFace->SetEnable(false);
		SetUIPicStates(false,true);
	}
}
void CUI_ID_FRAME_Target::SetPlayerTarget(CPlayer *target)
{
	if (!m_pID_FRAME_Target)
		return;
	//m_pID_PICTURE_TargetFace->SetEnable(true);
	if (!target || target->GetID() == GetPlayerID())
	{

		nTargetTargetId = -1;
		m_ttGroup.SetVisible(false);
		return;
	}

	MexResMgr::Record* record = GetMexResMgr()->GetRecord(target->GetModelId());
	if (record && (target->IsMonster() || target->IsNpc()))
	{
		m_pID_PICTURE_TargetHair->SetPicName(record->headPicture.c_str());
		m_pID_PICTURE_TargetFace->SetPicName(record->headPicture.c_str());

		bool IsInTeam = false;
		CPlayer* pSelBeLongPlayer = theHeroGame.GetPlayerMgr()->FindByID(target->GetBeLongID());
		if(pSelBeLongPlayer && thePlayerRole.IsTeamMember(pSelBeLongPlayer->GetName()))
		{
			IsInTeam = true;
		}
		if(target->GetBeLongID() != 0 && !target->IsPlayer() && (target->GetBeLongID() != theHeroGame.GetPlayerMgr()->GetMe()->GetID() &&  !IsInTeam && target->GetBeLongID() !=0 ))
		{
			//m_pID_PICTURE_TargetFace->SetEnable(false);
			SetUIPicStates(false,true);
		}
	}
	else if (target->IsPlayer())
	{
        //modified by ZhuoMeng.Hu		[9/19/2010]
        //std::string portraitName = s_CUI_ID_FRAME_CREATE.GetPortraitName( target->GetSex(), target->GetPortraitId() );
        //portraitName = "Data\\Ui\\" + portraitName;
        //m_pID_PICTURE_TargetFace->SetPicName( portraitName.c_str() );

		char sex[2][32] = { "Male", "Female" };

		int hairId = target->GetEquip()[eKeyAll_Hair].iModelID;
		int faceId = target->GetEquip()[eKeyAll_Face].iModelID;

		bool find1 = false;
		char filename[256] = {0};
		bool find2 = false;
		char filename2[256] = {0};

		//主将头像不显示
		/*if (target->GetHeroID() != INVALID_HERO_ID)
		{
			CItemHero::SItemHero *itemHero = theItemHero.FindHeroByHeroID(target->GetHeroID());
			if (itemHero == NULL)
				return;

			PlayerInfoMgr::Instance()->GetPlayerHeadPic(target, filename);
			m_pID_PICTURE_TargetHair->SetPicName(filename);
			m_pID_PICTURE_TargetFace->SetPicName(filename);
		}
		else*/
		{
			MeSprintf_s(filename, sizeof(filename)/sizeof(char) - 1, "%s/Data/Ui/HeadPicture/Player/Target%sHairHead_%d_%d.dds",
				GetRootPath(), sex[target->GetSex()], hairId,faceId);
			f_Handle* fp = packet_namespace::w_fopen(filename, "r");
			if (fp)
			{
				find1 = true;
				packet_namespace::w_fclose(fp);
			}

			if (find1)
				m_pID_PICTURE_TargetFace->SetPicName(filename);
			else
			{
				if (target->GetSex() == Sex_Male)
				{
					//m_pID_PICTURE_Hair->SetPicName("Data/Ui/HeadPicture/Player/DefaultTargetMale.dds");
					m_pID_PICTURE_TargetFace->SetPicName("Data/Ui/HeadPicture/Player/DefaultTargetMale.dds");
				}
				else
				{
					//m_pID_PICTURE_Hair->SetPicName("Data/Ui/HeadPicture/Player/DefaultTargetFemale.dds");
					m_pID_PICTURE_TargetFace->SetPicName("Data/Ui/HeadPicture/Player/DefaultTargetFemale.dds");
				}
			}

			//MeSprintf_s(filename, sizeof(filename)/sizeof(char) - 1, "%s/Data/Ui/HeadPicture/Player/Target%sHairHead%d.dds",
			//	GetRootPath(), sex[target->GetSex()], hairId);
			//// 是否要设发型
			//bool bNeedSetHair = false;
			//S_BaseData::S_Pic* pHairPic = m_pID_PICTURE_TargetHair->GetPic();
			//if( !pHairPic || stricmp(pHairPic->m_szPicName, filename) )
			//	bNeedSetHair = true;

			//MeSprintf_s(filename2, sizeof(filename2)/sizeof(char) - 1, "%s/Data/Ui/HeadPicture/Player/Target%sFaceHead%d.dds",
			//	GetRootPath(), sex[target->GetSex()], faceId);
			//// 是否要设脸型
			//bool bNeedSetFace = false;
			//S_BaseData::S_Pic* pFacePic = m_pID_PICTURE_TargetFace->GetPic();
			//if( !pFacePic || stricmp(pFacePic->m_szPicName, filename2) )
			//	bNeedSetFace = true;

			//if( bNeedSetHair || bNeedSetFace )
			//{
			//	f_Handle* fp = packet_namespace::w_fopen(filename, "r");
			//	if (fp)
			//	{
			//		find1 = true;
			//		packet_namespace::w_fclose(fp);
			//	}
			//	fp = packet_namespace::w_fopen(filename2, "r");
			//	if (fp)
			//	{
			//		find2 = true;
			//		packet_namespace::w_fclose(fp);
			//	}
			//	if (find1 && find2)
			//	{
			//		m_pID_PICTURE_TargetHair->SetPicName(filename);
			//		m_pID_PICTURE_TargetFace->SetPicName(filename2);
			//	}
			//	else
			//	{
			//		if (target->GetSex() == 0)
			//		{
			//			m_pID_PICTURE_TargetHair->SetPicName("Data/Ui/HeadPicture/Player/DefaultTargetMale.dds");
			//			m_pID_PICTURE_TargetFace->SetPicName("Data/Ui/HeadPicture/Player/DefaultTargetMale.dds");
			//		}
			//		else
			//		{
			//			m_pID_PICTURE_TargetHair->SetPicName("Data/Ui/HeadPicture/Player/DefaultTargetFemale.dds");
			//			m_pID_PICTURE_TargetFace->SetPicName("Data/Ui/HeadPicture/Player/DefaultTargetFemale.dds");
			//		}
			//	}
			//}
		}
	}
	//zhuxincong 这里是目标的目标 也就是自己
	m_pID_PROGRESS_TargetHp->SetValue( ((float)target->GetHp())/target->GetHpMax() *1000);
	DWORD colorName = 0;
	SetNameColor(colorName, target);
	m_pID_TEXT_TargetName->SetText(target->GetName(), colorName);

    m_pID_TEXT_TargetLvl->SetText( target->GetLevel() );

	nTargetTargetId = target->GetID();
	m_ttGroup.SetVisible(true);
}

void CUI_ID_FRAME_Target::SetFollowPlayerId(int id)
{
	if( !m_pID_FRAME_Target )
		return;
    if( id == -1 && m_nFollowPlayerId != id )
    {
        // 提示取消跟随，并停止移动
        CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
        if( pMe == NULL )
            return;
        pMe->StopMoving();
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Follow, theXmlString.GetString( eText_Follow_Cancel ) );
    }
	m_nFollowPlayerId = id;
}

bool CUI_ID_FRAME_Target::ID_FRAME_TargetTarget_OnClick( ControlObject* pSender )
{
	if (-1 == s_CUI_ID_FRAME_Target.nTargetTargetId)
	{
		return false;
	}
    theHeroGame.GetPlayerMgr()->SetLockNpc( s_CUI_ID_FRAME_Target.nTargetTargetId );
	s_CUI_ID_FRAME_Target.SetPlayerTarget(NULL);
	return true;
}

void CUI_ID_FRAME_Target::CreateProgressAni()
{
    if( !IsUILoad() )
        return;

    char fullname[MAX_PATH] = {0};
    MeSprintf_s( fullname, sizeof( fullname ) / sizeof( char ) - 1, "%s\\data\\ui\\UIAni\\PlayerHp.2DAni", GetRootPath() );
    m_pID_PROGRESS_Hp->CreateAnimation( fullname );
    m_pID_PROGRESS_TargetHp->CreateAnimation( fullname );
}
