#include "Group.h"
#include "Group_Me.h"
#include "Team_Player.h"
#include "PlayerRole.h"
#include "Player.h"
#include "GameMain.h"
#include "..\PlayerMgr.h"
#include "BuffStatusManager.h"
#include "Group_StateUI.h"
#include "ItemDetail.h"
#include "Group_DeBuffUI.h"
#include "XmlStringLanguage.h"
#include "../color_config.h"
#include "Gang.h"
#include "FriendDlg.h"
#include "CharacterExp.h"
#include "core/Name.h"
#include "shortcutkey_configure.h"
#include "Dxsdk/dinput.h"
#include "ui/DemandItem.h"
#include "Cfg.h"
#include "baseProperty.h"
#include "GameDefinePlayer.h"
#include "../IntroductionManager.h"
#include "SuAnimal.h"
#include "ItemHero.h"

#define MAX_STATUS_SPARETIME 36000000
void RenderPlayerInMiniMap( int iCharType,bool bRole,bool bTeammate,int x,int y );

extern short GetKeyboardInput(int iKey);

CUI_Group s_CUI_Group;
CUI_Group::CUI_Group()
{
	m_nCurSelPalyerId = -1;
	m_nPlayerCnt = 0;
}

void CUI_Group::UnLoadUI()
{
	guardfunc;
	s_CUI_ID_FRAME_Group_Me.UnLoadUI();
	TeamPlayerFrameManage.Reset();
    DemandItemFrameManage.Reset();  // 重置掷骰子界面
	unguard;
}
void CUI_Group::LoadUI()
{
	guardfunc;
	s_CUI_ID_FRAME_Group_Me.LoadUI();
	unguard;
}

bool CUI_Group::AddPlayer( const int nId, const std::string& strName,
	const int nHp, const int nMaxHp, const int nMp, const int nMaxMp, const int nLvl )
{
	guardfunc;
	for ( int n=0; n<GROUP_MAX_PLAYER; n++ )
	{
		if ( vecPlayer[n].nId == -1 )
		{
			vecPlayer[n].nId = nId;
			vecPlayer[n].strName = strName;
			vecPlayer[n].nHp = nHp;
			vecPlayer[n].nMaxHp = nMaxHp;
			vecPlayer[n].nMp = nMp;
			vecPlayer[n].nMaxMp = nMaxMp;
			vecPlayer[n].nLvl = nLvl;

			m_nPlayerCnt++;
			Refeash();
			return true;
		}
	}
	return false;
	unguard;
}
bool CUI_Group::UpdatePlayer( const int nId ,const int nHp, const int nMaxHp, const int nMp, const int nMaxMp, const int nLvl
	,const int iMapID,const int x,const int y )
{
	guardfunc;
	m_nPlayerCnt = 0;
	for ( int n=0; n<GROUP_MAX_PLAYER; n++ )
	{
		if ( vecPlayer[n].nId == nId )
		{
			vecPlayer[n].nHp = nHp;
			vecPlayer[n].nMaxHp = nMaxHp;
			vecPlayer[n].iMapID = iMapID;
			vecPlayer[n].x = x;
			vecPlayer[n].y = y;
			vecPlayer[n].nMp = nMp;
			vecPlayer[n].nMaxMp = nMaxMp;
			vecPlayer[n].nLvl = nLvl;

			m_nPlayerCnt++;
			Refeash();
			return true;
		}
	}
	return false;
	unguard;
}

bool CUI_Group::IsTeammate( int iID )
{
	guardfunc;
	for ( int n=0; n<GROUP_MAX_PLAYER; n++ )
	{
		if ( vecPlayer[n].nId == iID )
		{				
			return true;
		}
	}
	return false;
	unguard;
}


void CUI_Group::RenderMiniMap( void )
{
	guardfunc;
	unguard;
}

bool CUI_Group::RemovePlayer( const int nId )
{
	guardfunc;
	for ( int n=0; n<GROUP_MAX_PLAYER; n++ )
	{
		if ( vecPlayer[n].nId == nId )
		{
			vecPlayer[n].nId = -1;

			for ( int m=n+1; m<GROUP_MAX_PLAYER; m++ )
			{
				if ( vecPlayer[m].nId != -1 )
				{
					vecPlayer[m-1] = vecPlayer[m];
					vecPlayer[m].nId = -1;
					m_nPlayerCnt--;
				}
			}

			Refeash();
			return true;
		}
	}
	return false;
	unguard;
}
bool CUI_Group::RemoveAllPlayer()
{
	guardfunc;
	for ( int n=0; n<GROUP_MAX_PLAYER; n++ )
	{
		vecPlayer[n].nId = -1;
		m_nPlayerCnt--;
	}
	Refeash();
	return true;
	unguard;
}
void CUI_Group::InitGroupDlg(bool bVisable)
{
	guardfunc;
	TeamPlayerFrameManage.SetVisable(bVisable);
	unguard;
}
void CUI_Group::show_assignMode_select(int headerid, unsigned char ucAssignMode)
{
	guardfunc;
	CUI_ID_FRAME_Team_Player* pFrame = TeamPlayerFrameManage.GetTeamFrameById(headerid);
	if (pFrame)
	{
		pFrame->setAssignMode_willChange(ucAssignMode);
		pFrame->showChange_assignModeUI(true);
	}
	unguard;
}
void CUI_Group::updataTeamerHP( int id, int hp)
{
	guardfunc;
	std::vector<TeamInfo> vecPlayer = thePlayerRole.GetTeamInfo();
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(id);
	if (!pPlayer)
	{
		return;
	}
	for( int i=0; i<vecPlayer.size(); ++i)
	{
		if( strcmp(vecPlayer[i].szName.c_str(),pPlayer->GetName() ))
		{
			TeamInfo InInfo;
			InInfo.nHp = hp;
			InInfo.nMaxHp = vecPlayer[i].nMaxHp;
			InInfo.nMp = vecPlayer[i].nMp;
			InInfo.nMaxMp = vecPlayer[i].nMaxMp;
			InInfo.nLvl = vecPlayer[i].nLvl;
			InInfo.nMapID = vecPlayer[i].nMapID;
			InInfo.x = vecPlayer[i].x;
			InInfo.y = vecPlayer[i].y;
			InInfo.bHeader = vecPlayer[i].bHeader;
			InInfo.bHeader2 = vecPlayer[i].bHeader2;
			InInfo.usProfession = vecPlayer[i].usProfession;
			InInfo.stManiple = vecPlayer[i].stManiple;

			thePlayerRole.UpdataPlayerInfo( InInfo, true );

		}
	}
	unguard;
}
void CUI_Group::show_talktip(const char* talk, int id)
{	
	guardfunc;
	CUI_ID_FRAME_Team_Player* pFrame = TeamPlayerFrameManage.GetTeamFrameById(id);
	if (pFrame)
	{
		pFrame->show_talktip(talk);
	}

	unguard;
}

//////////////////////////////////////////////////////////////////////////
//优化更新HP频率过高，单独出来更新
void CUI_Group::RefeashGroupMemberHP( TeamInfo &InInfo )
{
	guardfunc;

	int nValue = 0;
	if ( InInfo.nMaxHp != 0 )
	{
		nValue = InInfo.nHp*1000/InInfo.nMaxHp;
	}

	int nMpValue = 0;
	if ( InInfo.nMaxMp != 0 )
	{
		nMpValue = InInfo.nMp*1000/InInfo.nMaxMp;
	}
	CUI_ID_FRAME_Team_Player* pFrame = TeamPlayerFrameManage.GetTeamFrameByDBId(InInfo.nID);
	if (pFrame)
	{
		if( pFrame->GetPROGRESS_Hp() )
			pFrame->GetPROGRESS_Hp()->SetValue( nValue );
		char temp[256] = {0};
		sprintf_s(temp,sizeof(temp)-1,"%d/%d",InInfo.nHp,InInfo.nMaxHp);
		if( pFrame->GetTEXT_ShowHp() )
			pFrame->GetTEXT_ShowHp()->SetText(temp);
		if( pFrame->GetPROGRESS_Mp() )
			pFrame->GetPROGRESS_Mp()->SetValue( nMpValue );
		sprintf_s(temp,sizeof(temp)-1,"%d/%d",InInfo.nMp,InInfo.nMaxMp);
		if( pFrame->GetTEXT_ShowMp() )
			pFrame->GetTEXT_ShowMp()->SetText(temp);
	}

	return;
	unguard;

}
void CUI_Group::RefeashGroup()
{
	guardfunc;

	TeamPlayerFrameManage.updata();

	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if( !pMe ) return;
	INT i=0;

	// Player
	InitGroupDlg();	//init GroupDlg 也就是隐藏所有的组队界面
	//--------------------------------------------------------------------------
	std::vector<TeamInfo> vecPlayer = thePlayerRole.GetTeamInfo();
	s_CUI_ID_FRAME_Group_Me.SetPicHeader(false);
	if( vecPlayer.size() > 0 )
	{
		BOOL bMyHeader = thePlayerRole.IsTeamHeader();
		if( bMyHeader )
		{
			s_CUI_ID_FRAME_Group_Me.SetPicHeader(true);
		}
	}

	//-------------------------------------------------------------------------
	INT MyIdx = -1;
	if( theHeroGame.GetPlayerMgr() )
	{
		pMe = theHeroGame.GetPlayerMgr()->GetMe();
		if( pMe == NULL )
			return ;
	}

	for( int me=0; me< vecPlayer.size(); me++ )
	{
		if( strcmp(vecPlayer[me].szName.c_str(),pMe->GetName()) == 0)
		{
			MyIdx = me;
		}
	}

	INT nIdx = 0;
	for ( int n=0; n<vecPlayer.size(); n++ )
	{
		if ( vecPlayer[n].nID != -1 
			&& 
			MyIdx != n )
		{
			// Hp
			int nValue = 0;
			if ( vecPlayer[n].nMaxHp != 0 )
			{
				nValue = vecPlayer[n].nHp*1000/vecPlayer[n].nMaxHp;
			}

			int nMpValue = 0;
			if ( vecPlayer[n].nMaxMp != 0 )
			{
				nMpValue = vecPlayer[n].nMp*1000/vecPlayer[n].nMaxMp;
			}

			// Struct
			CPlayer *pPlayer = theHeroGame.GetPlayerMgr()->FindByName( vecPlayer[n].szName.c_str() );
			SCharBuff* pStatus = NULL;
			ControlIconDrag::S_ListImg stItem;
			CUI_ID_FRAME_Team_Player* pFrame = TeamPlayerFrameManage.GetTeamFrameByIndex(nIdx);
			if (!pFrame)
			{
				pFrame = TeamPlayerFrameManage.CreateFrame(nIdx);
			}
			assert(pFrame);
			{
				pFrame->Refreah();
				if( pFrame->GetTEXT_Name() )
					pFrame->GetTEXT_Name()->SetText( vecPlayer[n].szName );
				char temp[256];
				MeSprintf_s(temp,sizeof(temp)/sizeof(char) - 1,"%d/%d",vecPlayer[n].nHp,vecPlayer[n].nMaxHp);
				if( pFrame->GetTEXT_ShowHp() )
					pFrame->GetTEXT_ShowHp()->SetText(temp);
				if( pFrame->GetPROGRESS_Hp() )
					pFrame->GetPROGRESS_Hp()->SetValue( nValue );
				if( pFrame->GetPROGRESS_Mp() )
					pFrame->GetPROGRESS_Mp()->SetValue( nMpValue );
				MeSprintf_s(temp,sizeof(temp)/sizeof(char) - 1,"%d/%d",vecPlayer[n].nMp,vecPlayer[n].nMaxMp);
				if( pFrame->GetTEXT_ShowMp() )
					pFrame->GetTEXT_ShowMp()->SetText(temp);
				pFrame->setInfo(vecPlayer[n].nID, vecPlayer[n].ucSex);
				pFrame->SetPicHeader( vecPlayer[n].bHeader );

				if( pFrame->GetPICTURE_Header2() )
					pFrame->GetPICTURE_Header2()->SetVisable( vecPlayer[n].bHeader2 );

				pFrame->showProfessionIcon( vecPlayer[n].usProfession );
				char strLvl[24] = {0};
				MeSprintf_s( strLvl,sizeof(strLvl)/sizeof(char) - 1 ,"%d", vecPlayer[n].nLvl );
				string szLvl = strLvl;

				if( pFrame->GetTEXT_LVL() )
					pFrame->GetTEXT_LVL()->SetText( szLvl );
				pFrame->SetVisable( true );
				//
				if ( pPlayer )
				{
					if( pFrame->GetLISTIMG_Status() )
					{
						pFrame->GetLISTIMG_Status()->Clear();
						pFrame->GetLISTIMG_Status()->SetVisable(false);
					}

					i = 0;

					for ( int buff_id=0; buff_id < pPlayer->m_cFightStatus.GetBufferStatusCount(); buff_id++ )
					{
						pStatus = pPlayer->m_cFightStatus.GetBuff( buff_id );
						if ( !pStatus )
							continue;

						if( pFrame->GetLISTIMG_Status() )
							pFrame->GetLISTIMG_Status()->SetVisable(true);
						stItem.SetData( pStatus->StatusID, pStatus->iLevel, eIcon_Enable, true, eTipFlag_Status );
						if( pFrame->GetLISTIMG_Status() )
                        {
							ControlListImage* pListImg = pFrame->GetLISTIMG_Status();
                            pListImg->SetItem( &stItem, i );

                            // BUF显示剩余时间      added by zhuomeng.hu		[12/7/2010]
                            ItemDefine::SItemStatus* pItemStatus = NULL;
                            pItemStatus = GettheItemDetail().GetStatus( pStatus->StatusID, pStatus->iLevel );
                            if( pItemStatus && i < pListImg->GetEnableCnt() )
                            {
                                if( pStatus->bStop )
                                {
                                    pListImg->SetSpareTime( i, 0xffffffff, pStatus->dwStartTime );
                                }
                                else if( pItemStatus->IsForeverStatus() )
                                {
                                    pListImg->SetSpareTime( i, MAX_STATUS_SPARETIME, pStatus->dwStartTime );
                                }
                                else
                                {
                                    pListImg->SetSpareTime( i, pStatus->dwDurationTime, pStatus->dwStartTime );
                                }
                            }

                        }

						++i;
					}

					pFrame->SetVisablePetUI(pPlayer->HavePet());

					if (pPlayer->HavePet())
					{
						CPlayer* pet = theHeroGame.GetPlayerMgr()->FindByID(pPlayer->GetPetID());
						if (pet)
						{
							int progValue = pet->GetHp()*1000/pet->GetHpMax();
							if( pFrame->GetPROGRESS_Pt1() )
								pFrame->GetPROGRESS_Pt1()->SetValue(progValue);
						}
					}
				}
				else
				{
					if( pFrame->GetLISTIMG_Status() )
					{
						pFrame->GetLISTIMG_Status()->Clear();
						pFrame->GetLISTIMG_Status()->SetVisable(false);
					}

				}

			}

			nIdx++;
		}
	}

	unguard;
}

void CUI_Group::updateGroupSelect( int id )
{
	guardfunc;
	CUI_ID_FRAME_Team_Player* pFrame = TeamPlayerFrameManage.GetTeamFrameByDBId(id);
	if (pFrame)
	{
		if( pFrame->GetPICTURE_choise1() )
			pFrame->GetPICTURE_choise1()->SetVisable(false);
		if( pFrame->GetTEXT_talktip() )
			pFrame->GetTEXT_talktip()->SetVisable(false);
		if( pFrame->GetPICTURE_talktipPic() )
			pFrame->GetPICTURE_talktipPic()->SetVisable(false);
	}

	unguard;
}

void CUI_Group::Refeash()
{
	guardfunc;
	//更新团
	if( !s_CUI_ID_FRAME_Group_Me.GetFrame() )
		return;

	s_CUI_ID_FRAME_Group_Me.Refeash();

	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if( !pMe ) return;

	char    *szName     = thePlayerRole.GetName();
    __int64 nLvl        = thePlayerRole.GetLevel();
	__int64 nHp         = thePlayerRole.GetData( CPlayerRole::TYPE_HP );
	__int64 nMaxHp      = thePlayerRole.GetData( CPlayerRole::TYPE_HPMAX );
	__int64 nMp         = thePlayerRole.GetData( CPlayerRole::TYPE_MP );
	__int64 nMaxMp      = thePlayerRole.GetData( CPlayerRole::TYPE_MPMAX );
	__int64 nExPower    = thePlayerRole.GetData( CPlayerRole::TYPE_ExPower );
    __int64 nMaxExPower = DEF_CHAR_XP_LIMIT;

    // 更新PK图标
    s_CUI_ID_FRAME_Group_Me.RefreshPKShowPicture( pMe->GetPKType() );

    // 经验条   modified by zhuomeng.hu		[10/9/2010]
    int64 nCurExp = thePlayerRole.GetExpNotUsed();
	int64 nNeedExp = theExpStage.GetExpDistance( thePlayerRole.GetLevel() );
	if( nCurExp < 0 )
		nCurExp = 0;
	__int64 nExpPercent = nCurExp * 1000 / nNeedExp;
	s_CUI_ID_FRAME_CharacterExp.SetExpValue( nExpPercent );
	char szExp[64] = {0};
	MeSprintf_s( szExp, sizeof( szExp ) / sizeof( char ) - 1, "%I64u / %I64u" , nCurExp, nNeedExp );
	s_CUI_ID_FRAME_CharacterExp.SetTextExp( szExp );

    // 装备界面经验显示     modified by zhuomeng.hu		[10/9/2010]
    s_CUI_ID_FRAME_BaseProperty.Refresh();
	s_CUI_ID_FRAME_MAIN.RefreshExp();

    // 设置等级
    char szLvl[32] = {0};
    MeSprintf_s( szLvl,sizeof( szLvl ) / sizeof( char ) - 1, "%d", nLvl );
	s_CUI_ID_FRAME_Group_Me.SetTEXT_LVL(szLvl);

    // 设置名字
    DWORD col = pMe->GetPkNameColor();
    s_CUI_ID_FRAME_Group_Me.SetTEXT_Name( szName, col );
	s_CUI_ID_FRAME_Group_Me.RefreshHeadPic();

	//设置主将名字
	s_CUI_ID_FRAME_Group_Me.SetHero_Name( "", 0 );
	CItemHero::SItemHero *itemHero = theItemHero.FindHeroByHeroID(pMe->GetHeroID());
	if ( itemHero )
	{
		ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( itemHero->itemd_id );
		if( pItemCommon )
		{
			DWORD color = S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel );
			std::string strHero;
			strHero += "(" + itemHero->hero_name + ")";
			s_CUI_ID_FRAME_Group_Me.SetHero_Name( strHero.c_str(), color );
		}
	}		

	int nValue = 0;
	if ( nMaxHp != 0 )
	{
		nValue = nHp*1000/nMaxHp;

		if( nHp >= nMaxHp )
		{
			nValue = 1000;
		}
	}

	//modified by zhuomeng.hu		[9/14/2010]
	std::stringstream tipInfoAllInOne;
	tipInfoAllInOne << theXmlString.GetString(eTip_sAddHPMax) << ":" << nHp << "/" << nMaxHp << "\n";
	tipInfoAllInOne << theXmlString.GetString( eTip_sAddMPMax ) << ":";
	tipInfoAllInOne << nMp << "/" << nMaxMp << "\n";//h<< theXmlString.GetString( eText_ExPower ) << ":" << nExPower << "/" << nMaxExPower << "\n";

	ControlProgress* pGroup_Me_PROGRESS_Hp = s_CUI_ID_FRAME_Group_Me.GetPROGRESS_Hp();
	if( pGroup_Me_PROGRESS_Hp )
	{
		if( nValue <= 250 )
			pGroup_Me_PROGRESS_Hp->SetFlicker( true );
		else
			pGroup_Me_PROGRESS_Hp->SetFlicker( false );

		pGroup_Me_PROGRESS_Hp->SetValue( nValue );
		pGroup_Me_PROGRESS_Hp->setTipName(tipInfoAllInOne.str().c_str(), DT_LEFT );
		pGroup_Me_PROGRESS_Hp->setShowTip(true);

		//新手回血指引
		if( thePlayerRole.IsFinishedIntroduce(INTRO_DRINK_DRUG) == false && nValue < pGroup_Me_PROGRESS_Hp->GetMaxValue() / 2 )
		{
			CIntroductionManager::Instance()->ShowTip( INTRO_DRINK_DRUG );
			thePlayerRole.SetFinishedIntroduce(INTRO_DRINK_DRUG);
		}
	}
	ControlText* pGroup_Me_Text_Hp = s_CUI_ID_FRAME_Group_Me.GetTEXT_Hp();
	if (pGroup_Me_Text_Hp)
	{
		char MeHpAbout[512] = {0};
		sprintf_s(MeHpAbout,sizeof(MeHpAbout)/sizeof(char),"%d/%d",(int)nHp,(int)nMaxHp);
		pGroup_Me_Text_Hp->SetText(MeHpAbout);
	}

	ControlProgress* pGroup_Me_PROGRESS_Mp = s_CUI_ID_FRAME_Group_Me.GetPROGRESS_Mp();
	if( pGroup_Me_PROGRESS_Mp )
	{
		nValue = 0;
		if ( nMaxMp != 0 )
		{
			nValue = nMp * 1000 / nMaxMp;
		}
		if( nValue <= 250 )
			pGroup_Me_PROGRESS_Mp->SetFlicker( true );
		else
			pGroup_Me_PROGRESS_Mp->SetFlicker( false );

		pGroup_Me_PROGRESS_Mp->SetValue( nValue );
		pGroup_Me_PROGRESS_Mp->setTipName(tipInfoAllInOne.str().c_str(), DT_LEFT );
		pGroup_Me_PROGRESS_Mp->setShowTip( true );
	}
	ControlText* pGroup_Me_Text_Mp = s_CUI_ID_FRAME_Group_Me.GetTEXT_Mp();
	if (pGroup_Me_Text_Mp)
	{
		char MeMpAbout[512] = {0};
		sprintf_s(MeMpAbout,sizeof(MeMpAbout)/sizeof(char),"%d/%d",(int)nMp,(int)nMaxMp);
		pGroup_Me_Text_Mp->SetText(MeMpAbout);
	}

	ControlProgress* pGroup_Me_PROGRESS_ExBar = s_CUI_ID_FRAME_Group_Me.GetPROGRESS_ExPower();
	if( pGroup_Me_PROGRESS_ExBar )
	{
		pGroup_Me_PROGRESS_ExBar->setTipName( tipInfoAllInOne.str().c_str(), DT_LEFT );
		pGroup_Me_PROGRESS_ExBar->setShowTip( true );
	}

	if( pMe->HavePet()|| pMe->HaveSubPet())
	{
		MexResMgr::Record* record = NULL;
		if (pMe->HavePet())
		{//捕捉宠物
				CPlayer *pPetPlayer = theHeroGame.GetPlayerMgr()->FindByID( pMe->GetPetID() );
				if( pPetPlayer && thePlayerRole.GetActivedPet() != NULL&& !pPetPlayer->IsDead()  && pPetPlayer->GetSubMonsterType() != Object_MonsterPet)
				{
					record = GetMexResMgr()->GetRecord(pPetPlayer->GetModelId());
					if (record != NULL)
					{
						s_CUI_ID_FRAME_Group_Me.SetPetInfoVisable(true, record->headPicture.c_str());
					}
					else
						s_CUI_ID_FRAME_Group_Me.SetPetInfoVisable(true);
					s_CUI_ID_FRAME_Group_Me.SetTEXT_petname(pPetPlayer->GetName());
					nValue = 0;
					nValue = pPetPlayer->GetLevel();
					char szLevel[32] = {0};
					_snprintf( szLevel, 31, "%d", nValue );
					s_CUI_ID_FRAME_Group_Me.SetTEXT_petlevel( szLevel );

					ControlProgress* pGroup_Me_PROGRESS_petHp = s_CUI_ID_FRAME_Group_Me.GetPROGRESS_petHp();
					int nHp = pPetPlayer->GetHp();
					int nHpMax = pPetPlayer->GetHpMax();
					if( pGroup_Me_PROGRESS_petHp )
					{
						nValue = 0;
						if( nHpMax != 0 )
							nValue = nHp*1000/nHpMax;
						pGroup_Me_PROGRESS_petHp->SetValue( nValue );

						std::stringstream tipInfoHP;
						tipInfoHP << theXmlString.GetString(eTip_sAddHPMax) << " ";
						tipInfoHP << nHp;
						tipInfoHP << "/";
						tipInfoHP << nHpMax;
						pGroup_Me_PROGRESS_petHp->setTipName(tipInfoHP.str().c_str(), DT_LEFT );
						pGroup_Me_PROGRESS_petHp->setShowTip(true);
					}
					ControlText* pGroup_Me_TEXT_petHp = s_CUI_ID_FRAME_Group_Me.GetTEXT_petHp();
					if (pGroup_Me_TEXT_petHp)
					{
						char petHp[128] = {0};
						sprintf_s(petHp,sizeof(petHp)/sizeof(char),"%d/%d",nHp,nHpMax);
						pGroup_Me_TEXT_petHp->SetText(petHp);
					}

					//更新其他UI的值
					s_CUI_ID_FRAME_SuAnimal.SetActPetID(pMe->GetPetID());
				}
				else
				{
					s_CUI_ID_FRAME_Group_Me.SetPetInfoVisable(false);
				}
		}
		if (pMe->HavePet() && pMe->HaveSubPet())
		{
			CPlayer *pPetPlayer = theHeroGame.GetPlayerMgr()->FindByID( pMe->GetSubPetID() );
			if( pPetPlayer  && thePlayerRole.GetActivedPet() != NULL && !pPetPlayer->IsDead() && pPetPlayer->GetSubMonsterType() ==Object_MonsterPet )//必须是召唤宠
			{
				record = GetMexResMgr()->GetRecord(pPetPlayer->GetModelId());
				if (record != NULL)
				{
					s_CUI_ID_FRAME_Group_Me.SetPetInfoVisable_1(true, record->headPicture.c_str());
				}
				else
					s_CUI_ID_FRAME_Group_Me.SetPetInfoVisable_1(true);
				s_CUI_ID_FRAME_Group_Me.SetTEXT_petname1(pPetPlayer->GetName());
				nValue = 0;
				nValue = pPetPlayer->GetLevel();
				char szLevel[32] = {0};
				_snprintf( szLevel, 31, "%d", nValue );
				s_CUI_ID_FRAME_Group_Me.SetTEXT_petlevel1( szLevel );

				ControlProgress* pGroup_Me_PROGRESS_petHp = s_CUI_ID_FRAME_Group_Me.GetPROGRESS_petHp1();
				int nHp = pPetPlayer->GetHp();
				int nHpMax = pPetPlayer->GetHpMax();
				if( pGroup_Me_PROGRESS_petHp )
				{
					nValue = 0;
					if( nHpMax != 0 )
						nValue = nHp*1000/nHpMax;
					pGroup_Me_PROGRESS_petHp->SetValue( nValue );

					std::stringstream tipInfoHP;
					tipInfoHP << theXmlString.GetString(eTip_sAddHPMax) << " ";
					tipInfoHP << nHp;
					tipInfoHP << "/";
					tipInfoHP << nHpMax;
					pGroup_Me_PROGRESS_petHp->setTipName(tipInfoHP.str().c_str(), DT_LEFT );
					pGroup_Me_PROGRESS_petHp->setShowTip(true);
				}
				ControlText* pGroup_Me_TEXT_petHp1 = s_CUI_ID_FRAME_Group_Me.GetTEXT_petHp1();
				if (pGroup_Me_TEXT_petHp1)
				{
					char petHp1[128] = {0};
					sprintf_s(petHp1,sizeof(petHp1)/sizeof(char),"%d/%d",nHp,nHpMax);
					pGroup_Me_TEXT_petHp1->SetText(petHp1);
				}

			}
			else
			{
				s_CUI_ID_FRAME_Group_Me.SetPetInfoVisable_1(false);
			}
		}
		if (pMe->HavePet() && pMe->HaveSubPet())
		{
			CPlayer *pPetPlayer = theHeroGame.GetPlayerMgr()->FindByID( pMe->GetSubPetID() );
			if( pPetPlayer && !pPetPlayer->IsDead() &&thePlayerRole.GetActivedPet() == NULL && pPetPlayer->GetSubMonsterType() ==Object_MonsterPet )//必须是召唤宠
			{
				record = GetMexResMgr()->GetRecord(pPetPlayer->GetModelId());
				if (record != NULL)
				{
					s_CUI_ID_FRAME_Group_Me.SetPetInfoVisable(true, record->headPicture.c_str());
					s_CUI_ID_FRAME_Group_Me.SetPetInfoVisable_1(false);
				}
				else
				{
					s_CUI_ID_FRAME_Group_Me.SetPetInfoVisable(true);
					s_CUI_ID_FRAME_Group_Me.SetPetInfoVisable_1(false);
				}
				s_CUI_ID_FRAME_Group_Me.SetTEXT_petname(pPetPlayer->GetName());
				nValue = 0;
				nValue = pPetPlayer->GetLevel();
				char szLevel[32] = {0};
				_snprintf( szLevel, 31, "%d", nValue );
				s_CUI_ID_FRAME_Group_Me.SetTEXT_petlevel( szLevel );

				ControlProgress* pGroup_Me_PROGRESS_petHp = s_CUI_ID_FRAME_Group_Me.GetPROGRESS_petHp();
				if( pGroup_Me_PROGRESS_petHp )
				{
					nValue = 0;
					int nHp = pPetPlayer->GetHp();
					int nHpMax = pPetPlayer->GetHpMax();
					if( nHpMax != 0 )
						nValue = nHp*1000/nHpMax;
					pGroup_Me_PROGRESS_petHp->SetValue( nValue );

					std::stringstream tipInfoHP;
					tipInfoHP << theXmlString.GetString(eTip_sAddHPMax) << " ";
					tipInfoHP << nHp;
					tipInfoHP << "/";
					tipInfoHP << nHpMax;
					pGroup_Me_PROGRESS_petHp->setTipName(tipInfoHP.str().c_str(), DT_LEFT );
					pGroup_Me_PROGRESS_petHp->setShowTip(true);
				}
			}
		}
		
	}
	else
	{
		s_CUI_ID_FRAME_Group_Me.SetPetInfoVisable(false);
		s_CUI_ID_FRAME_Group_Me.SetPetInfoVisable_1(false);
		pMe->ReleasePet(); 
		pMe->ReleaseSubPet();
	}

	s_CUI_ID_FRAME_StateUI.SetRefresh();
	s_CUI_ID_FRAME_DeBuffUI.SetRefresh();
//     ControlListImage* pImg = NULL;
//     pImg = s_CUI_ID_FRAME_StateUI.GetListImage();
//     if(pImg)
//     {
//         pImg->Clear();
//         pImg->SetVisable(false);
//     }
// 
// 	s_CUI_ID_FRAME_DeBuffUI.ClearListImage();
// 	s_CUI_ID_FRAME_DeBuffUI.SetVisableListImage(false);
// 
// 	SCharBuff* pStatus = NULL;
// 	INT i = 0;
// 	int ndebuff = 0;
// 	for ( int n=0; n < pMe->m_cFightStatus.GetBufferStatusCount(); n++ )
// 	{
// 		pStatus = pMe->m_cFightStatus.GetBuff( n );
// 		if ( !pStatus )
// 			continue;
// 
//         if(s_CUI_ID_FRAME_StateUI.GetListImage())
// 		   s_CUI_ID_FRAME_StateUI.GetListImage()->SetVisable( true );
// 		s_CUI_ID_FRAME_DeBuffUI.SetVisableListImage(true);
// 		ControlIconDrag::S_ListImg stItem;
// 		stItem.SetData( pStatus->StatusID, pStatus->iLevel, pStatus->bStop? eIcon_Disable:eIcon_Enable, true, eTipFlag_Status );
// 
// 		//这里把status如果有持续时间的话 把这个持续时间加上去
// 		ItemDefine::SItemStatus* pItemStatus = NULL;
// 		pItemStatus = GettheItemDetail().GetStatus( pStatus->StatusID,
// 			pStatus->iLevel);
// 		if(pItemStatus)
// 		{
// 			if (pItemStatus->bAvail)
// 			{
// 				ControlListImage* p = s_CUI_ID_FRAME_StateUI.GetListImage();
//                 if(p)
//                 {
//                     int nCountPerLine = p->GetRowItemCnt();
//                     int nOriOffset = nCountPerLine - 1 - i % nCountPerLine;
//                     int nRow = i / nCountPerLine * nCountPerLine;
//                     p->SetItem( &stItem, nRow + nOriOffset);
//                     if( pStatus->bStop )	// 暂停
//                     {
//                         p->SetSpareTime( nRow + nOriOffset, 0xffffffff, pStatus->dwStartTime, true );
//                     }
//                     else if( pItemStatus->IsForeverStatus() )	// 永久BUFF
//                         p->SetSpareTime( nRow + nOriOffset, MAX_STATUS_SPARETIME, pStatus->dwStartTime, true );
//                     else
//                         p->SetSpareTime( nRow + nOriOffset, pStatus->dwDurationTime, pStatus->dwStartTime, true );
//                 }
// 				i++;
// 			}
// 			else
// 			{
// 				ControlListImage* p = s_CUI_ID_FRAME_DeBuffUI.GetListImage();
//                 if(p)
//                 {
//                     int nCountPerLine = p->GetRowItemCnt();
//                     int nOriOffset = nCountPerLine - 1 - ndebuff % nCountPerLine;
//                     int nRow = ndebuff / nCountPerLine * nCountPerLine;
//                     p->SetItem( &stItem,nRow + nOriOffset );
//                     p->SetSpareTime( nRow + nOriOffset, pStatus->dwDurationTime, pStatus->dwStartTime, true );
//                 }
// 				ndebuff++;
// 			}				
// 		}		
// 	}



	RefeashGroup();

	s_CUI_ID_FRAME_Friend.RefreshUI();

	unguard;
}

void CUI_Group::ProcessHotKey(int nKey)
{
	if (g_shortcutKey_configure.hasKey(nKey, AN_Configure_ShortcutKey::AN_SCKC_SelectMe))
	{
		s_CUI_ID_FRAME_Group_Me.ID_FRAME_Group_MeOnLBtnClick(0);
	}
	else if (g_shortcutKey_configure.hasKey(nKey, AN_Configure_ShortcutKey::AN_SCKC_SelectTeamPlayer1))
	{
		if (TeamPlayerFrameManage.GetTeamFrameByIndex(0))
		{
			CUI_ID_FRAME_Team_Player::OnSelectLookPlayer(TeamPlayerFrameManage.GetTeamFrameByIndex(0)->GetFrame());
		}
	}
	else if (g_shortcutKey_configure.hasKey(nKey, AN_Configure_ShortcutKey::AN_SCKC_SelectTeamPlayer2))
	{
		if (TeamPlayerFrameManage.GetTeamFrameByIndex(1))
		{
			CUI_ID_FRAME_Team_Player::OnSelectLookPlayer(TeamPlayerFrameManage.GetTeamFrameByIndex(1)->GetFrame());
		}
	}
	else if (g_shortcutKey_configure.hasKey(nKey, AN_Configure_ShortcutKey::AN_SCKC_SelectTeamPlayer3))
	{
		if (TeamPlayerFrameManage.GetTeamFrameByIndex(2))
		{
			CUI_ID_FRAME_Team_Player::OnSelectLookPlayer(TeamPlayerFrameManage.GetTeamFrameByIndex(2)->GetFrame());
		}
	}
	else if (g_shortcutKey_configure.hasKey(nKey, AN_Configure_ShortcutKey::AN_SCKC_SelectTeamPlayer4))
	{
		if (TeamPlayerFrameManage.GetTeamFrameByIndex(3))
		{
			CUI_ID_FRAME_Team_Player::OnSelectLookPlayer(TeamPlayerFrameManage.GetTeamFrameByIndex(3)->GetFrame());
		}
	}
	else if (g_shortcutKey_configure.hasKey(nKey, AN_Configure_ShortcutKey::AN_SCKC_SelectTeamPlayer5))
	{
		if (TeamPlayerFrameManage.GetTeamFrameByIndex(4))
		{
			CUI_ID_FRAME_Team_Player::OnSelectLookPlayer(TeamPlayerFrameManage.GetTeamFrameByIndex(4)->GetFrame());
		}
	}
}

void CUI_Group::UpdatePetInfo(GameObjectId PetID)
{
	CPlayer *pPetPlayer = theHeroGame.GetPlayerMgr()->FindByID(PetID);
	if(pPetPlayer)
	{
		int nHp = pPetPlayer->GetHp();
		int nHpMax = pPetPlayer->GetHpMax();
		ControlProgress* pGroup_Me_PROGRESS_petHp = s_CUI_ID_FRAME_Group_Me.GetPROGRESS_petHp();
		if( pGroup_Me_PROGRESS_petHp )
		{
			int nValue = 0;
			if( nHpMax != 0 )
				nValue = nHp*1000/nHpMax;
			pGroup_Me_PROGRESS_petHp->SetValue( nValue );

			std::stringstream tipInfoHP;
			tipInfoHP << theXmlString.GetString(eTip_sAddHPMax) << " ";
			tipInfoHP << nHp;
			tipInfoHP << "/";
			tipInfoHP << nHpMax;
			pGroup_Me_PROGRESS_petHp->setTipName(tipInfoHP.str().c_str(), DT_LEFT );
			pGroup_Me_PROGRESS_petHp->setShowTip(true);
		}
		ControlText* pGroup_Me_TEXT_petHp = s_CUI_ID_FRAME_Group_Me.GetTEXT_petHp();
		if (pGroup_Me_TEXT_petHp)
		{
			char petHp[128] = {0};
			sprintf_s(petHp,sizeof(petHp)/sizeof(char),"%d/%d",nHp,nHpMax);
			pGroup_Me_TEXT_petHp->SetText(petHp);
		}
	}
}