#include "playerrole.h"
#include "DuelTips.h"
#include "GameMain.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "MeUi/UiManager.h"
#include "ui/Group.h"
//#include "ui/Guild.h"
#include "ui/Guild_Pic.h"
#include "ui/Task.h"
#include "ErrorLog.h"
#include "ShowScreenText.h"
#include "itemdetail.h"
#include "ui/ChatInfoBox.h"
#include "ui/Group_Me.h"
#include "CfgFileLoader.h"
#include "XmlStringLanguage.h"
#include "color_config.h"
#include "chatcheck.h"
#include "MeTerrain/NiColor.h"
#include "MeTerrain/SwType.h"
#include "MeTerrain/SwDebug.h"
#include "MeTerrain/HashTable.h"
#include "MeTerrain/MapFile.h"
#include "MeTerrain/MapUtil.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/World.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/WorldTile.h"
#include "MeTerrain/NdlWorldPickerBase.h"
#include "ui/Skill.h"
#include "ui/SkillLearn.h"
#include "ui/SkillTree.h"
#include "core/Name.h"
#include "ui/Main.h"
#include "ui/exmain.h"
#include "script_manager.h"
#include "Include/MiniMap.h"
#include "ui/Experience.h"
#include "MessageBox.h"
#include "ui/SkillProduce.h"
#include "SelfRbtnMenu.h"
#include "RegionMap.h"
#include "GlobalFunction.h"
#include "ui/AreaExperience.h"
#include "OnLineRewardConfig.h"
#include "ui/OnlineAward.h"
#include "ui/OnlineAward2.h"
#include "../GameUI/AutoAttackSet.h"
#include "shop.h"
#include "ui/Fcm.h"
#include "ui/PrivateShop.h"
#include "ui/FriendDlg.h"
#include "AddMember.h"
#include "../Sociality.h"
#include "GameSetting.h"
#include "RelationConfig.h"
#include "UiTitle.h"
#include "Master.h"
#include "MapConfig.h"
#include "Meui/ExpressionManager.h"
#include "WealthProtect.h"
#include "PreventWallow.h"
#include "OnlineReward.h"
#include "Ui/InfoList.h"
#include "RelationMessage.h"
#include "SettingGame.h"
#include "ProduceLearn.h"
#include "ui/GuildApply.h"
#include "Ui/AddFriend.h"
#include "SoundConfig.h"
#include "IntroductionManager.h"
#include "ItemHero.h"
#include "..\GameUI\TaiPingHuanJing.h"
#include "MessageDefine.h"
#include "Ui/OtherInfo.h"
#include "ui/GuildBaseInfo.h"
#include "GuildConfig.h"
#include "ui/Target.h"
#include "ui/CountryBaseInfo.h"
#include "GlobalDef.h"
#include "ui/SuAnimal.h"
#include "ui/Escdlg.h"
#include "ui/AddGuildGeneralBattle.h"
#include "ui/Gut.h"
#include "MessageDefine.h"

#include "ui/GemUp.h"
#include "ui/Star.h"
#include "ui/GoldPlating.h"
#include "ui/Hole.h"
#include "ui/Gem.h"
#include "ui/GemReplace.h"
#include "ui/GemRemove.h"
#include "ui/Purple.h"
#include "ui/RePurple.h"
#include "ui/Soul.h"
#include "ui/IdentifyQuality.h"
#include "../../Source/GameUI/RandAttribute.h"
extern char* GetFullFileName(const char* filename);
CPlayerRole	thePlayerRole;

extern CHeroGame	theHeroGame;
extern DWORD HQ_TimeGetTime();
extern void	World2Screen( D3DXVECTOR3 vPos,int &x,int &y );
extern int PlayEffect( const char* pEffectName, CPlayer* pSrcPlayer = NULL, float fScale = 0 , DWORD dwFlyTime = 0, CPlayer* pDestPlayer = NULL, int nSlot = 0 ,bool bCalDist = true);

extern unsigned int g_dwServerNumber;
bool MsgEquipEvolve::IsNeedChangeBound(unsigned int PlayerID)
{
	SCharItem pEquip;
	if(!thePlayerRole.GetBagItemByGUID(nNormalGuid,&pEquip))
		return false;	
	if(pEquip.IsBounded())
		return false;
	for(int i =0;i<EConstDefine_MaxMaterialCount;++i)
	{
		if(materials[i].guid == 0 || materials[i].guid==-1)
			continue;
		SCharItem pItem;
		if(!thePlayerRole.GetBagItemByGUID(materials[i].guid,&pItem))
			continue;
		if(pItem.IsBounded())
			return true;
	}
	return false;
}
void MsgEquipEvolve::SendEquipMsg()
{
	if(IsNeedChangeBound())
	{
		//设置装备绑定的提示信息
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_EquipMaterialBound), "", CUI_ID_FRAME_MessageBox::eTypeYesNo, true, MsgEquipEvolve::EquipMaterialSendMsg,this,header.stLength);
	}
	else
	{
		GettheNetworkInput().SendMsg( this );
	}
}
void MsgEquipEvolve::CloseUI()
{
	#ifdef GAME_CLIENT
	s_CUI_ID_FRAME_GemUp.SetVisable(false);
	s_CUI_ID_FRAME_Star.SetVisable(false);
	s_CUI_ID_FRAME_GoldPlating.SetVisable(false);
	s_CUI_ID_FRAME_Hole.SetVisable(false);
	s_CUI_ID_FRAME_Gem.SetVisable(false);
	s_CUI_ID_FRAME_GemReplace.SetVisable(false);
	s_CUI_ID_FRAME_GemRemove.SetVisable(false);
	s_CUI_ID_FRAME_Purple.SetVisable(false);
	s_CUI_ID_FRAME_Repurple.SetVisable(false);
	s_CUI_ID_FRAME_Soul.SetVisable(false);
	s_CUI_ID_FRAME_IdentifyQuality.SetVisable(false);
	s_CUI_ID_FRAME_RandAttribute.SetVisable(false);

	#endif 
}

BOOL CPlayerRole::IsManipleHeader()
{
	guardfunc;
	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if( pMe == NULL )
		return FALSE;

	std::vector<TeamInfo>& vecPlayer = GetTeamInfo();
	if( GetTeamMemberNum() > 0)
	{
		for(int n=0; n<vecPlayer.size(); n++)
		{
			if( strcmp(vecPlayer[n].szName.c_str(), pMe->GetName() ) == 0 )
			{
				return vecPlayer[n].bHeader2;
			}
		}
	}


	return FALSE;
	unguard;
}

BOOL CPlayerRole::IsTeamHeader()
{
	guardfunc;
	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if( pMe == NULL )
		return FALSE;

	std::vector<TeamInfo>& vecPlayer = GetTeamInfo();

	if( GetTeamMemberNum() > 0)
	{
		for(int n=0; n<vecPlayer.size(); n++)
		{
			if( strcmp(vecPlayer[n].szName.c_str(), pMe->GetName() ) == 0  )
			{
				return vecPlayer[n].bHeader;
			}
		}
	}
	return FALSE;

	unguard;
}

CPlayerRole::CPlayerRole(void)
{
    m_bMustSendMovingMessage = FALSE;
    m_dwPlayerDBID = 0;
    m_dwGameMapId = 0;

	m_isPlayerHitMe = false;
	m_dwPlayerHitMeAlphaStartTime = 0;

	m_pVecTeamSkill.clear();
	m_fCalcTeamSkillCD = 0.f;
    m_nWeakCountryId = CountryDefine::Country_Init;
	m_nStrongCountryId  = CountryDefine::Country_Init;

	WorldBattleCountryID=CountryDefine::Country_Init;

	PetDuration = 0;

	memset(m_taskState, 0, sizeof(m_taskState));
	memset(m_taskVar, 0, sizeof(m_taskVar));

	m_nSepatatePartVar = -1;

	InitInfluence();
}

CPlayerRole::~CPlayerRole(void)
{
	m_QuestTalkStates.clear();
	m_VariableInfos.clear();
	m_questInfos.clear();
	m_mapFriendInfo.clear();
}

void CPlayerRole::initialize(const SCharInfoClient& charinfo, DWORD dwDBID )
{
	InitInfluence();
	ResetGuildData();
    m_charinfo = charinfo;
	m_charLastBaseProperty = m_charinfo.baseinfo.baseProperty;
    m_dwPlayerDBID = dwDBID;

    guardfunc;
//     OutputDebugStr("CPlayerRole");
    m_bUpdateUI = false;
    m_bFighting = false;

    m_pVisual =	&(m_charinfo.visual);
    m_pBaseInfo = &(m_charinfo.baseinfo);

    m_bStartCollectPos = FALSE;
    m_dwStartCollectPosTime = 0; //开始记录坐标点的时间

    m_bCanSendActionMessage = TRUE;

    m_bCanUseSpecialSkill = FALSE;

    for(int i =0;i< STORAGE_ITEMGRID_MAX;i++)
    {
        m_stStorage.stStorageItems[i].itembaseinfo.ustItemID = InvalidLogicNumber;
        fCostOfFetchItem[i] = 0;
        strcpy_s( CityName[i], MAX_NAME_STRING, 
            "" );
    }
    strcpy(szItem_PWD,"");

    m_nNpcID = 0;
    //---- = -1;
    m_shDuelTarget = -1;
    memset(m_szDuelName, 0, sizeof(m_szDuelName));
    m_nDuelTime = 0;
    m_nDuelOutTime = 10;
    m_nSelfOutTime = 10;

    m_GroupId = -1;

    m_cLastSaveDirX = 0;
    m_cLastSaveDirY = 0;
    m_cLastSaveDirZ = 0;

    m_bCorps = false;

    m_nLockNumMax = 0;
    m_nLockNum = 0;

    m_nCompoundRateAdd = 0;
    m_nIntensifyRateAdd = 0;
    m_nShopCenterOffSell = 100;

	m_bWaitforTransport = false;

    m_bNeedSendLastPos = FALSE;

	m_bQuestInitialized = false;
    m_bCorps = FALSE;
    m_TeamData.clear();
	SetAssignMode(AssignMode_Team);
    SetItemRollLevel(eIL_Choiceness);

	CWealthProtect::Instance().SetProtectTime((short)m_charinfo.otherdataclient.chProtectLockTime);
	CWealthProtect::Instance().SetFirstEnterMap(true);

    m_dwBanSpeakEndingTime = m_charinfo.otherdataclient.dwBanSpeakTime * 60 * 1000 + HQ_TimeGetTime();
    m_bIsReliveAndWaitingToHell = FALSE;

	m_fUpdateLockItemTime = 3.0f;
	m_fUnLockTimeCount = 0;

	m_bSecondPassword = false;

	m_nSecondPasswordUnlockTime = 0;

	m_mapFriendInfo.clear();

	m_pVecTeamSkill.clear();
	m_fCalcTeamSkillCD = 0.f;

	m_nTradeGold = 0;
	m_nTradeMoney = 0;

	m_bRoleJump = false;
	m_fRoleStartJumpX = 0.f;
	m_fRoleStartJumpY = 0.f;
	m_fRoleStartJumpZ = 0.f;


	//CPreventWallow::Instance().ResetFCMState();
	CPreventWallow::Instance().ClearInfo();

	m_RestoreCoolDown.Clear();
	m_RestoreCoolDown.InitColdDown(m_charinfo.baseinfo.liveinfo.xItemColdDown,MAX_SAVERESTORE_COUNT);

    COnlineReward::Instance().Reset();      //领取新手在线奖励重置
	
	s_CUI_ID_FRAME_OtherInfo.SetKillPlayerSum(GetAllKillSum(),GetWeekKillSum());

	++g_dwServerNumber;

    unguard;
}

void CPlayerRole::InitHotKey()
{
	for( int i = 0; i < More_iHotkey; ++i )
	{
		SMouseItem* pHotkey = &m_pHotKeyBag[i];
		pHotkey->ShortCut.BagType = ErrorUnsignedShortID;
		pHotkey->ShortCut.BagIndex = ErrorUnsignedShortID;
		switch( m_charinfo.otherdataclient.hotkeys.itemHotKey[i].ShortCut.BagType )
		{
		case BagTypePack:
			{
				SCharItem item;
				if (!m_bag.GetItem(m_charinfo.otherdataclient.hotkeys.itemHotKey[i].ShortCut.BagIndex, &item))
					continue;
	
				pHotkey->ShortCut.BagType = BagTypePack;
				pHotkey->ShortCut.BagIndex = m_charinfo.otherdataclient.hotkeys.itemHotKey[i].ShortCut.BagIndex;
				pHotkey->ItemData.itembaseinfo.ustItemID = item.itembaseinfo.ustItemID;
			}
			break;
		case BagTypeSkill:
			{
				SCharSkill* pSkill = m_SkillBag.GetSkillByIndex(
					m_charinfo.otherdataclient.hotkeys.itemHotKey[i].ShortCut.BagIndex );
				if ( !pSkill )
					continue;

				pHotkey->ShortCut.BagType = BagTypeSkill;
				pHotkey->ShortCut.BagIndex = m_charinfo.otherdataclient.hotkeys.itemHotKey[i].ShortCut.BagIndex;
				pHotkey->ItemData.itembaseinfo.ustItemID = pSkill->ustSkillID;
			}
			break;
		case BagTypeMountSkill:
			{
				SCharSkill* pSkill = m_MountSkillBag.GetSkillByIndex(
					m_charinfo.otherdataclient.hotkeys.itemHotKey[i].ShortCut.BagIndex );
				if ( !pSkill )
					continue;

				pHotkey->ShortCut.BagType = BagTypeMountSkill;
				pHotkey->ShortCut.BagIndex = m_charinfo.otherdataclient.hotkeys.itemHotKey[i].ShortCut.BagIndex;
				pHotkey->ItemData.itembaseinfo.ustItemID = pSkill->ustSkillID;
			}
			break;
		case BagTypePetSkill:
			{
				SCharSkill* pSkill = m_PetSkillBag.GetSkillByIndex(
					m_charinfo.otherdataclient.hotkeys.itemHotKey[i].ShortCut.BagIndex );
				if( !pSkill )
					continue;

				pHotkey->ShortCut.BagType = BagTypePetSkill;
				pHotkey->ShortCut.BagIndex = m_charinfo.otherdataclient.hotkeys.itemHotKey[i].ShortCut.BagIndex;
				pHotkey->ItemData.itembaseinfo.ustItemID = pSkill->ustSkillID;
			}
			break;
		case BagTypeActionUI:
			{
				pHotkey->ShortCut.BagType = BagTypeActionUI;
				pHotkey->ShortCut.BagIndex = m_charinfo.otherdataclient.hotkeys.itemHotKey[i].ShortCut.BagIndex;
				pHotkey->ItemData.itembaseinfo.ustItemID = m_charinfo.otherdataclient.hotkeys.itemHotKey[i].ShortCut.BagIndex;
			}
			break;
		case BagTypeExpressionAction:
			{
				pHotkey->ShortCut.BagType = BagTypeExpressionAction;
				pHotkey->ShortCut.BagIndex = m_charinfo.otherdataclient.hotkeys.itemHotKey[i].ShortCut.BagIndex;
				pHotkey->ItemData.itembaseinfo.ustItemID = m_charinfo.otherdataclient.hotkeys.itemHotKey[i].ShortCut.BagIndex;
			}
			break;
		/************************************************************************/
		/* author:liaojie													  */
		/* Desc:  主将技能                                                    */
		/************************************************************************/
		case BagTypeHeroSkill:
			{
				SCharSkill* pSkill = m_HeroSkillBag.GetSkillByIndex(
					m_charinfo.otherdataclient.hotkeys.itemHotKey[i].ShortCut.BagIndex );
				if ( !pSkill )
					continue;

				pHotkey->ShortCut.BagType = BagTypeHeroSkill;
				pHotkey->ShortCut.BagIndex = m_charinfo.otherdataclient.hotkeys.itemHotKey[i].ShortCut.BagIndex;
				pHotkey->ItemData.itembaseinfo.ustItemID = pSkill->ustSkillID;
			}
		}
	}
}

void CPlayerRole::SendHotKeyToServer()
{
	// 更新快捷键给服务器
	MsgRefreshHotkey msgHotKey;

	for( int i = 0; i < More_iHotkey; ++i )
	{
		msgHotKey.hotkeys.itemHotKey[i].ShortCut.BagType = m_pHotKeyBag[i].ShortCut.BagType;
		msgHotKey.hotkeys.itemHotKey[i].ShortCut.BagIndex = m_pHotKeyBag[i].ShortCut.BagIndex;
	}

	GettheNetworkInput().SendMsg(&msgHotKey);
	//GettheNetworkInput().CheckSendReq();
}

void CPlayerRole::SetCharInfo( const SCharInfoClient& charinfo )
{
	guardfunc;

	m_bCorps = FALSE;
    m_questInfos.clear();
	m_VariableInfos.clear();
	m_vectorActiveQuestInfo.clear();
	m_charinfo = charinfo;
	m_pBaseInfo = &(m_charinfo.baseinfo);

	m_SkillBag.Init( m_charinfo.otherdataclient.skills.skill,
		More_iMaxSkillKnown );
	m_xinFaBag.Init(m_charinfo.otherdataclient.skills.xinfa, More_iMaxXinFa);

	//主将技能
	m_HeroSkillBag.Init(m_charinfo.otherdataclient.skills.heroSkill, More_iMaxHeroSkill);

	memset(m_MountSkill, 0, sizeof(m_MountSkill));
	for (int i = 0; i < More_iMaxSkillKnown; ++i)
		m_MountSkill[i].ustSkillID = InvalidLogicNumber;

	m_MountSkillBag.Init(m_MountSkill, More_iMaxSkillKnown);

	if (GetActivedMount())
		AddMountSkill(*GetActivedMount());

	m_PetSkillBag.Init(m_PetSkill,SPetItem::PetDefine_MaxSkillCount);
	if(GetActivedPet())
		AddPetSkill(*GetActivedPet());

	m_RestoreCoolDown.Clear();
	m_RestoreCoolDown.InitColdDown(m_charinfo.baseinfo.liveinfo.xItemColdDown,MAX_SAVERESTORE_COUNT);

	m_bag.CreateFromData( m_charinfo.ItemBagData.stPackItems, m_charinfo.baseinfo.liveinfo.ucNormalBagSize );
	m_bagMaterial.CreateFromData( m_charinfo.ItemBagData.ciMaterialItems, m_charinfo.baseinfo.liveinfo.ucMaterialBagSize );
	m_bagTask.CreateFromData( m_charinfo.ItemBagData.ciTaskItems, ITEM_BAGTASK_MAX );

	//
	QuestInfo info;
	for ( int n=dr_MinQuestId + 1; n<=dr_MaxQuestId; n++ )
	{
		SQuest* pQuest = theQuestManager.GetQuest( n );
		if (pQuest)
		{
			info.nQuestId = n;
			info.chState = 0;
			m_questInfos.insert(QuestInfos::value_type(info.nQuestId, info));
		}
	}

 	try
 	{
 		char filename[MAX_PATH] = {0};
 		MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s/Data/Quest/CalculateExp.string", GetRootPath());
 		ScriptManager::instance().executeFile( filename );
 
 		LuaObject Variable = ScriptManager::instance().getLuaStateOwner(filename)->GetGlobal("Variable" );
 		for ( int n=0; n<=dr_MinQuestId; n++ )
 			Variable.SetInteger(n, 0);
 	}
 	catch ( const LuaPlus::LuaException& e )
 	{
 		OutputDebugString( ( std::string( e.GetErrorMessage() ) + "\n" ).c_str() );
 	}

	//Reorganize Skill 
	ReOrganizeSkill( );

    // 原来刺客的能量值 此代码不用
	//for (int n= 0;n<m_SkillBag.GetSkillNum();n++)
	//{
	//	SCharSkill* pSkill = NULL;
	//	pSkill = m_SkillBag.GetSkillByIndex(n);
	//	if (pSkill&&pSkill->bAvailable)
	//	{
	//		ItemDefine::SItemSkill* pItemSkill = NULL;
	//		pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
	//		if (pItemSkill&&pItemSkill->bIsNeedAssemblePower)
	//		{
	//			//SetCanPower(TRUE);
	//			break;
	//		}
	//	}		
	//}

	if( theHeroGame.GetPlayerMgr()->GetMe() )
	{
		theHeroGame.GetPlayerMgr()->GetMe()->SetName(GetName());
		theHeroGame.GetPlayerMgr()->GetMe()->SetUncontrolMoving(FALSE);
	}
	InitHotKey();

	unguard;
}

//装备背包
int	CPlayerRole::GetEquipBagItemCount(const int BagIndex)
{
	guardfunc;
	if (BagIndex <0 || BagIndex>=m_bag.GetNowBagSize() /*ITEM_BAGMAX*/)
	{
		assert(false && "equip bag index error");
		return 0;
	}
	return 1;
	unguard;
}

//刷新装备数据
void CPlayerRole::FreshEquipData( SCharAttributeUpdate* pFightData )
{
	if( !m_pBaseInfo )
	{
		assert(false && "FreshEquipData error");
		return;
	}
	m_pBaseInfo->baseProperty.fightAttr.hpMax.final = pFightData->hpMax;
	m_pBaseInfo->baseProperty.fightAttr.mpMax.final = pFightData->mpMax;
	m_pBaseInfo->baseProperty.fightAttr.attackPhysics.final = pFightData->attackPhysics;
	m_pBaseInfo->baseProperty.fightAttr.attackMagic .final = pFightData->attackMagic;

	m_pBaseInfo->baseProperty.fightAttr.defendPhysics.final = pFightData->defendPhysics;
	m_pBaseInfo->baseProperty.fightAttr.defendMagic.final = pFightData->defendMagic;

	m_pBaseInfo->baseProperty.fightAttr.exact.final = pFightData->exact;
	m_pBaseInfo->baseProperty.fightAttr.dodge.final = pFightData->dodge;
	m_pBaseInfo->baseProperty.fightAttr.critical.final = pFightData->critical;
	//m_pBaseInfo->baseProperty.fight.usCriticalResist.final = pFightData->usCriticalResist;
	//m_pBaseInfo->baseProperty.fight.criticalIntensity.final = pFightData->criticalIntensity;
	//m_pBaseInfo->baseProperty.fight.usAddDamageResist.final = pFightData->usAddDamageResist;
	//m_pBaseInfo->baseProperty.fight.iAddDamage.final = pFightData->iAddDamage;
	//m_pBaseInfo->baseProperty.fight.usGiddyResist.final = pFightData->resistDread;
	//m_pBaseInfo->baseProperty.fight.usStandResist.final = pFightData->resistComa;
	//m_pBaseInfo->baseProperty.fight.usSlowdownResist.final = pFightData->resistSlow;
	//m_pBaseInfo->baseProperty.fight.usTorpidResist.final = pFightData->resistSilence;
	//m_pBaseInfo->baseProperty.fight.usBackAttack.final = pFightData->usBackAttack;
	//m_pBaseInfo->baseProperty.fight.usBackAttackResist.final = pFightData->usBackAttackResist;
	m_pBaseInfo->baseProperty.fightAttr.moveSpeed.final = pFightData->moveSpeed;


	if (m_pBaseInfo->liveinfo.nHp > m_pBaseInfo->baseProperty.fightAttr.hpMax.final)
	{
		m_pBaseInfo->liveinfo.nHp = m_pBaseInfo->baseProperty.fightAttr.hpMax.final;
	}
	if (m_pBaseInfo->liveinfo.nMp > m_pBaseInfo->baseProperty.fightAttr.mpMax.final)
	{
		m_pBaseInfo->liveinfo.nMp = m_pBaseInfo->baseProperty.fightAttr.mpMax.final;
	}
	
}

// 装备
bool CPlayerRole::Equip( const SCharItem* pCharItem, const int nWhere )
{
	guardfunc;
	if( !pCharItem )
	{
		assert(false);
		return false;
	}
	if (nWhere<0 || nWhere>=EEquipPartType_MaxEquitPart)
	{
		assert(false && "equip pos error");
		return false;
	}
	if( !m_pVisual )
	{
		assert(false);
		return false;
	}
	//装备上需要的道具
	m_pVisual->GetVisualArray()[nWhere] = *pCharItem;
	// 改变模型
	if( theHeroGame.GetPlayerMgr()->GetMe() )
	{
		//add by yanli  2010-9-27
		int nPart = CEquipPartMap::Instance()->GetLogicPart(nWhere);
		theHeroGame.GetPlayerMgr()->GetMe()->SetEquip( nPart,(SCharItem*)pCharItem );
		theHeroGame.GetPlayerMgr()->GetMe()->ShowHelmet(m_pVisual->IsShowHelmet());
		theHeroGame.GetPlayerMgr()->GetMe()->ShowAecpratove(m_pVisual->IsShowAecorative());
		theHeroGame.GetPlayerMgr()->GetMe()->SetShowHero(m_pVisual->IsShowHero());
	}
	return true;
	unguard;
}

// 卸载
bool CPlayerRole::UnEquip( const int nWhere )
{
	guardfunc;
	if (nWhere<0 || nWhere>=EEquipPartType_MaxEquitPart)
	{
		assert(false && "unequip pos error");
		return false;
	}
	if( !m_pVisual )
	{
		assert(false);
		return false;
	}

	//
	if ( m_pVisual->GetVisualArray()[nWhere].itembaseinfo.ustItemID != InvalidLogicNumber )
	{

		m_pVisual->GetVisualArray()[nWhere].itembaseinfo.ustItemID = InvalidLogicNumber;
		if( theHeroGame.GetPlayerMgr()->GetMe() )
			theHeroGame.GetPlayerMgr()->GetMe()->SetEquip( nWhere,0 );
		return true;
	}
	return false;
	unguard;
}
// 更新
bool CPlayerRole::Update( enUpdataType enType, const double dwValue )
{
	guardfunc;
	int nValueTemp = 0;
	if ( dwValue == ErrorUnsignedLongID )
		return false;

    bool bUpdateProduceSkill = false;
	switch( enType )
	{
	case TYPE_ShopCenterScore: //lyh++ 商城积分
		m_pBaseInfo->liveinfo.ConsumeScore = dwValue;
		break;

	case TYPE_CRITICLE:						// 暴
		{
			m_pBaseInfo->baseProperty.fightAttr.critical.final = dwValue;
		}
		break;
	case TYPE_CRITICLEINTENSITY:			// 暴击倍率
		{
			m_pBaseInfo->baseProperty.fightAttr.criticalIntensity.final = dwValue;
		}
		break;
	case TYPE_TENACITY:						// 韧性
		{
			m_pBaseInfo->baseProperty.fightAttr.tenacity.final = dwValue;
		}
		break;
	case TYPE_ExPower:
		{
			m_pBaseInfo->liveinfo.nXp = dwValue;
		}
		break;
	case TYPE_Exploit:
		{
			m_pBaseInfo->liveinfo.exploit = dwValue;
		}
		break;
	case TYPE_Reputation:
		{
			m_pBaseInfo->liveinfo.reputation = dwValue;
		}
		break;
	case TYPE_Glory:
		{
			m_pBaseInfo->liveinfo.honour = dwValue;
		}
		break;
	case TYPE_CountryScore:
		{
			m_pBaseInfo->liveinfo.dwCountryScore = dwValue;
		}
		break;
	case TYPE_HP:
		if( dwValue > m_pBaseInfo->baseProperty.fightAttr.hpMax.final )
			m_pBaseInfo->liveinfo.nHp = m_pBaseInfo->baseProperty.fightAttr.hpMax.final;
		else
            m_pBaseInfo->liveinfo.nHp = dwValue;

		if( theHeroGame.GetPlayerMgr()->GetMe() )
			theHeroGame.GetPlayerMgr()->GetMe()->SetHPInfo( m_pBaseInfo->liveinfo.nHp, m_pBaseInfo->baseProperty.fightAttr.hpMax.final );

        //HPChanged();
		break;
	
	case TYPE_HPMAX:
		m_pBaseInfo->baseProperty.fightAttr.hpMax.final = dwValue;
		if (m_pBaseInfo->liveinfo.nHp > m_pBaseInfo->baseProperty.fightAttr.hpMax.final)
		{
			m_pBaseInfo->liveinfo.nHp = m_pBaseInfo->baseProperty.fightAttr.hpMax.final;
        }
		if( theHeroGame.GetPlayerMgr()->GetMe() )
			theHeroGame.GetPlayerMgr()->GetMe()->SetHPInfo( m_pBaseInfo->liveinfo.nHp, m_pBaseInfo->baseProperty.fightAttr.hpMax.final );
        //HPChanged();
		break;

	case TYPE_HPRESTORE:
		m_charinfo.baseinfo.baseProperty.fightAttr.hpRestore.final = dwValue;
		break;
	case TYPE_MPRESTORE:
		m_charinfo.baseinfo.baseProperty.fightAttr.mpRestore.final = dwValue;
		break;
	case TYPE_MP:
		if( dwValue > m_pBaseInfo->baseProperty.fightAttr.mpMax.final )
			m_pBaseInfo->liveinfo.nMp = m_pBaseInfo->baseProperty.fightAttr.mpMax.final;
		else
			m_pBaseInfo->liveinfo.nMp = dwValue;

		if( theHeroGame.GetPlayerMgr()->GetMe() )
			theHeroGame.GetPlayerMgr()->GetMe()->SetMp(m_pBaseInfo->liveinfo.nMp);
        
        //MPChanged();
		break;
	case TYPE_MPMAX:
		m_pBaseInfo->baseProperty.fightAttr.mpMax.final = dwValue;
		if (m_pBaseInfo->liveinfo.nMp > m_pBaseInfo->baseProperty.fightAttr.mpMax.final)
		{
			m_pBaseInfo->liveinfo.nMp = m_pBaseInfo->baseProperty.fightAttr.mpMax.final;
		}

		if( theHeroGame.GetPlayerMgr()->GetMe() )
		{
			theHeroGame.GetPlayerMgr()->GetMe()->SetMp(m_pBaseInfo->liveinfo.nMp);
			theHeroGame.GetPlayerMgr()->GetMe()->SetMpMax(m_pBaseInfo->baseProperty.fightAttr.mpMax.final);
		}
        //MPChanged();
		break;
	case TYPE_EXP:
		m_pBaseInfo->liveinfo.dwExp = dwValue;
		break;
	case TYPE_EXPNOTUSED:
		m_pBaseInfo->liveinfo.dwExpNotUsed = dwValue;
		break;
	case TYPE_Silver:
		m_charinfo.baseinfo.liveinfo.jinDing = dwValue;
		break;
	case TYPE_GLOD:
		//m_charinfo.baseinfo.liveinfo.dwRMBGold = dwValue;
		break;
	case TYPE_MONEY:
		{
			if( ( dwValue - m_charinfo.baseinfo.liveinfo.dwMoney ) > 0 )
			{
				PlaySoundConfig( SoundConfig::EST_MoneyInc );
			}
			else
			{
				PlaySoundConfig( SoundConfig::EST_MoneyDec );
			}
			m_charinfo.baseinfo.liveinfo.dwMoney = dwValue;
			CUIMgr::Instance()->RefreshByMoneyChange();
		}
		break;
	case TYPE_ATTACKPHYSICS:
		m_pBaseInfo->baseProperty.fightAttr.attackPhysics.final = dwValue;
		break;
	case TYPE_AttackMagic:
		m_pBaseInfo->baseProperty.fightAttr.attackMagic.final = dwValue;
		break;
	case TYPE_DefendPhysics:
		m_pBaseInfo->baseProperty.fightAttr.defendPhysics.final = dwValue;
		break;
	case TYPE_DefendMagic:
		m_pBaseInfo->baseProperty.fightAttr.defendMagic.final = dwValue;
		break;
	case TYPE_Strength:					// 力量		
		m_pBaseInfo->baseProperty.baseAttr.baseAttrValue[EBaseAttr_Strength].final = dwValue;
		break;
	case TYPE_Stamina:						// 耐力
		m_pBaseInfo->baseProperty.baseAttr.baseAttrValue[EBaseAttr_Stamina].final = dwValue;
		break;
	case TYPE_Agility:						// 敏捷
		m_pBaseInfo->baseProperty.baseAttr.baseAttrValue[EBaseAttr_Agility].final = dwValue;
		break;
	case TYPE_Intelligence:						// 智力
		m_pBaseInfo->baseProperty.baseAttr.baseAttrValue[EBaseAttr_Intelligence].final = dwValue;
		break;
	case TYPE_EXACT:							//精确值
		m_pBaseInfo->baseProperty.fightAttr.exact.final = dwValue;
		break;
	case TYPE_DODGE:							//躲避率
		m_pBaseInfo->baseProperty.fightAttr.dodge.final = dwValue;
		break;
	case TYPE_PROFESSION:
		m_pBaseInfo->aptotic.usProfession = dwValue;
		break;
	case TYPR_SKILLEXP:
		m_pBaseInfo->liveinfo.dwSkillExp = dwValue;
		s_CUI_ID_FRAME_SKILL.NeedRefresh();
		s_CUI_ID_FRAME_SKILL_LEARN.Refresh();
		break;
	case TYPR_SKILLEXPNOTUSE:
		m_pBaseInfo->liveinfo.dwSkillExpNotUsed = dwValue;
		break;
	case TYPE_LEVEL:
		{
			m_pBaseInfo->liveinfo.ustLevel = dwValue;
			s_CUI_ID_FRAME_PACK.Refeash();			
			s_CUI_ID_FRAME_Experience.Refresh();
		}
		break;	
	case TYPE_Pkvalue:
		{
			if( theHeroGame.GetPlayerMgr() &&
				theHeroGame.GetPlayerMgr()->GetMe() )
			{
				theHeroGame.GetPlayerMgr()->GetMe()->SetPKKillValue( dwValue );
				s_CUI_ID_FRAME_Experience.Refresh();
			}
		}
		break;
	case TYPE_ENERGY://更新活力
		{
			m_pBaseInfo->liveinfo.activity = dwValue;
			s_CUI_ID_FRAME_Experience.Refresh();
            bUpdateProduceSkill = true;
		}		
		break;
	case TYPE_ENERGY_MAX://更新活力最大
		{
			m_pBaseInfo->liveinfo.activityMax = dwValue;
			s_CUI_ID_FRAME_Experience.Refresh();
		}		
		break;
	case TYPE_VIGOR://更新精力
		{
			m_pBaseInfo->liveinfo.vigor = dwValue;
			s_CUI_ID_FRAME_Experience.Refresh();
            bUpdateProduceSkill = true;
		}
		break;
	case TYPE_VIGOR_MAX://更新精力最大
		{
			m_pBaseInfo->liveinfo.vigorMax = dwValue;
			s_CUI_ID_FRAME_Experience.Refresh();
		}
		break;
	case TYPE_MOVESPEED: // 移动速度
		{
			m_pBaseInfo->baseProperty.fightAttr.moveSpeed.final = dwValue;
		}
		break;
	case TYPE_ATTACKSPEED: // 攻速
		{
			m_pBaseInfo->baseProperty.fightAttr.attackSpeed.final = dwValue;
		}
		break;    
    //商业技能
	case TYPE_CaoYao: 						// 草药
		{
			char szBuff[256] = {0};
			short stTemp = dwValue - m_pBaseInfo->liveinfo.nSkillPoint[ ERT_CaoYao ];
			MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_LifeSkillLevelupPoint ), 
                theXmlString.GetString( eText_CaoYao_SkillPoint ), stTemp );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_Learnt, szBuff );
			m_pBaseInfo->liveinfo.nSkillPoint[ ERT_CaoYao ] = dwValue;
            bUpdateProduceSkill = true;
		}
		break;
	case TYPE_ZhuBao: 						// 珠宝
		{
            char szBuff[256] = {0};
            short stTemp = dwValue - m_pBaseInfo->liveinfo.nSkillPoint[ ERT_ZhuBao ];
            MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_LifeSkillLevelupPoint ), 
                theXmlString.GetString( eText_ZhuBao_SkillPoint ), stTemp );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_Learnt, szBuff );
            m_pBaseInfo->liveinfo.nSkillPoint[ ERT_ZhuBao ] = dwValue;
            bUpdateProduceSkill = true;
		}
		break;		
	case TYPE_DuanZao:    					// 锻造
		{
			char szBuff[256] = {0};
			short stTemp = dwValue - m_pBaseInfo->liveinfo.nSkillPoint[ ERT_DuanZao ];
			MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_LifeSkillLevelupPoint ),
                theXmlString.GetString( eText_DuanZao_SkillPoint ), stTemp );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_Learnt, szBuff );
			m_pBaseInfo->liveinfo.nSkillPoint[ ERT_DuanZao ] = dwValue;
            bUpdateProduceSkill = true;			
		}
		break;
	case TYPE_ZhuJia: 						// 铸甲
		{
			char szBuff[256] = {0};
			short stTemp = dwValue - m_pBaseInfo->liveinfo.nSkillPoint[ ERT_ZhuJia ];
			MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_LifeSkillLevelupPoint ),
                theXmlString.GetString( eText_ZhuJia_SkillPoint ), stTemp );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_Learnt, szBuff );
			m_pBaseInfo->liveinfo.nSkillPoint[ ERT_ZhuJia ] = dwValue;
            bUpdateProduceSkill = true;
		}
		break;
	case TYPE_GongYi: 						// 工艺
		{
			char szBuff[256] = {0};
			short stTemp = dwValue - m_pBaseInfo->liveinfo.nSkillPoint[ ERT_GongYi ];
			MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_LifeSkillLevelupPoint ),
                theXmlString.GetString( eText_GongYi_SkillPoint ), stTemp );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_Learnt, szBuff );
			m_pBaseInfo->liveinfo.nSkillPoint[ ERT_GongYi ] = dwValue;
            bUpdateProduceSkill = true;
		}
		break;
	case TYPE_XunMa:  					    // 驯马
		{
			char szBuff[256] = {0};
			short stTemp = dwValue - m_pBaseInfo->liveinfo.nSkillPoint[ ERT_XunMa ];
			MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_LifeSkillLevelupPoint ),
                theXmlString.GetString( eText_XunMa_SkillPoint ), stTemp );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_Learnt, szBuff );
			m_pBaseInfo->liveinfo.nSkillPoint[ ERT_XunMa ] = dwValue;
            bUpdateProduceSkill = true;
		}
		break;
	case TYPE_CaiKuang:				        // 采矿
		{
			char szBuff[256] = {0};
			short stTemp = dwValue - m_pBaseInfo->liveinfo.nSkillPoint[ ERT_CaiKuang ];
			MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_LifeSkillLevelupPoint ),
                theXmlString.GetString( eText_CaiKuang_SkillPoint ), stTemp );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_Learnt, szBuff );
			m_pBaseInfo->liveinfo.nSkillPoint[ ERT_CaiKuang ] = dwValue;
            bUpdateProduceSkill = true;
		}
		break;
	case TYPE_CaiYao:				        // 采药
		{
			char szBuff[256] = {0};
			short stTemp = dwValue - m_pBaseInfo->liveinfo.nSkillPoint[ ERT_CaiYao ];
			MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_LifeSkillLevelupPoint ),
                theXmlString.GetString( eText_CaiYao_SkillPoint ), stTemp );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_Learnt, szBuff );
			m_pBaseInfo->liveinfo.nSkillPoint[ ERT_CaiYao ] = dwValue;
            bUpdateProduceSkill = true;
		}
		break;
	case TYPE_BuZhuo:                       // 捕捉
		{
            char szBuff[256] = {0};
            short stTemp = dwValue - m_pBaseInfo->liveinfo.nSkillPoint[ ERT_BuZhuo ];
            MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_LifeSkillLevelupPoint ),
                theXmlString.GetString( eText_BuChong_SkillPoint ), stTemp );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_Learnt, szBuff );
            m_pBaseInfo->liveinfo.nSkillPoint[ ERT_BuZhuo ] = dwValue;
            bUpdateProduceSkill = true;
		}
		break;
    case TYPE_BuChong:                       // 捕虫
        {
            char szBuff[256] = {0};
            short stTemp = dwValue - m_pBaseInfo->liveinfo.nSkillPoint[ ERT_BuChong ];
            MeSprintf_s( szBuff, 256, theXmlString.GetString( eText_LifeSkillLevelupPoint ),
                theXmlString.GetString( eText_BuChong_SkillPoint ), stTemp );
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_Learnt, szBuff );
            m_pBaseInfo->liveinfo.nSkillPoint[ ERT_BuChong ] = dwValue;
            bUpdateProduceSkill = true;
        }
        break;

	case TYPE_JinDing:
		{
			m_pBaseInfo->liveinfo.jinDing = dwValue;
			break;
		}
	case TYPE_JinPiao:
		{
			m_pBaseInfo->liveinfo.jinPiao = dwValue;
			break;
		}
    case TYPE_JiaoZi:
        {
            m_pBaseInfo->liveinfo.jiaoZi = dwValue;
			CUIMgr::Instance()->RefreshByMoneyChange();
		}
        break;
	case TYPE_AreaRepulation:
		{
			__int64 value = (__int64)dwValue;
			short mapId;
			int currValue;
			int maxValue;
			int addValue = 0;
			bool bFound = false;
			int nFirstEmpty = -1;
			ProcessAreaReputation::GetAreaRepulation(value, mapId, currValue, maxValue);
			for (int i = 0; i < MAX_AREAREPULATION_COUNT; ++i)
			{
				if (m_pBaseInfo->liveinfo.xArea[i].nMapID == -1 && nFirstEmpty == -1 )
					nFirstEmpty = i;

				if (m_pBaseInfo->liveinfo.xArea[i].nMapID == mapId)
				{
					addValue = currValue - m_pBaseInfo->liveinfo.xArea[i].nCurrentReputation;
					m_pBaseInfo->liveinfo.xArea[i].nCurrentReputation = currValue;
					m_pBaseInfo->liveinfo.xArea[i].nMaxReputation = maxValue;
					bFound = true;
				}
			}
			if( !bFound && nFirstEmpty != -1 && nFirstEmpty < MAX_AREAREPULATION_COUNT )
			{
				addValue = currValue - m_pBaseInfo->liveinfo.xArea[nFirstEmpty].nCurrentReputation;
				m_pBaseInfo->liveinfo.xArea[nFirstEmpty].nMapID = mapId;
				m_pBaseInfo->liveinfo.xArea[nFirstEmpty].nCurrentReputation = currValue;
				m_pBaseInfo->liveinfo.xArea[nFirstEmpty].nMaxReputation = maxValue;
			}

			CWorldBuffer* pbuffer = SwGlobal::GetWorld()->GetWorldBuffer();
			if( pbuffer )
			{
				CWorldTile* pActiveTile = pbuffer->GetTileFromMapId(mapId );
				if( pActiveTile )
				{
					char szBuff[256];
					MeSprintf_s(szBuff,sizeof(szBuff)/sizeof(char) - 1 ,theXmlString.GetString(eText_YouGetAreaReputation), addValue, pActiveTile->GetTileName());
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Reputation_Change, szBuff );

					if( theHeroGame.GetPlayerMgr()->GetMe() )
					{
						D3DXVECTOR3 pos = theHeroGame.GetPlayerMgr()->GetMe()->GetPos();
						int xEffect,yEffect;
						World2Screen( pos,xEffect,yEffect );
						theHeroGame.GetPlayerMgr()->GetMe()->OnShowFlyText( 0, addValue, 0, GlobalTexture::eAddAreaReputation );
					}
				}
			}

			s_CUI_ID_FRAME_AreaExperience.Update();
			break;
		}
	case TYPE_Storage:
		{
		    m_pBaseInfo->liveinfo.nStorageItemGrid = dwValue;
			s_CUI_ID_FRAME_Storage.Refeash();
		}
		break;
	case TYPE_PetSrorage:
		{
		    m_pBaseInfo->liveinfo.nStorageMountGrid = dwValue;
		}
		break;
	case TYPE_FreeReliveCount:
		{
			m_pBaseInfo->liveinfo.nFreeReliveCount = dwValue;
			//更新UI上的值
			s_CUI_ID_FRAME_ESCDLG.UpdateReviceSum();
		}
		break;
	case TYPE_BackStrike:                    // 背击伤害
		{
			m_pBaseInfo->baseProperty.fightAttr.backStrike.final = dwValue;
		}
		break;
	case TYPE_BackStrikeResist:              // 背击抗性
		{
			m_pBaseInfo->baseProperty.fightAttr.backStrikeResist.final = dwValue;
		}
		break;
	case TYPE_BreakStrike:                   // 破甲伤害
		{
			m_pBaseInfo->baseProperty.fightAttr.breakStrike.final = dwValue;
		}
		break;
	case TYPE_StabStrike:                    // 贯穿伤害
		{
			m_pBaseInfo->baseProperty.fightAttr.stabStrike.final = dwValue;
		}
		break;
	case TYPE_ElementStrike:                 // 元素伤害
		{
			m_pBaseInfo->baseProperty.fightAttr.elementStrike.final = dwValue;
		}
		break;
	case TYPE_ToxinStrike:                   // 毒素伤害
		{
			m_pBaseInfo->baseProperty.fightAttr.toxinStrike.final = dwValue;
		}
		break;
	case TYPE_SpiritStrike:                  // 精神伤害
		{
			m_pBaseInfo->baseProperty.fightAttr.spiritStrike.final = dwValue;
		}
		break;
	case TYPE_BreakResist:                   // 破甲抗性
		{
			m_pBaseInfo->baseProperty.fightAttr.breakResist.final = dwValue;
		}
		break;
	case TYPE_StabResist:                    // 贯穿抗性
		{
			m_pBaseInfo->baseProperty.fightAttr.stabResist.final = dwValue;
		}
		break;
	case TYPE_ElementResist:                 // 元素抗性
		{
			m_pBaseInfo->baseProperty.fightAttr.elementResist.final = dwValue;
		}
		break;
	case TYPE_ToxinResist:                   // 毒素抗性
		{
			m_pBaseInfo->baseProperty.fightAttr.toxinResist.final = dwValue;
		}
		break;
	case TYPE_SpiritResist:                  // 精神抗性
		{
			m_pBaseInfo->baseProperty.fightAttr.elementResist.final = dwValue;
		}
		break;
	case TYPE_Daoxing:
		{
			m_pBaseInfo->liveinfo.daoxing = dwValue;
		}
		break;
	case TYPE_CurGetDaoxing:
		{

		}
		break;
	case TYPE_BasePotential:
		{
			m_pBaseInfo->liveinfo.basePotential = dwValue;
		}
		break;
	default:
		return false;
	}	
    if( bUpdateProduceSkill && s_CUI_ID_FRAME_SkillProduce.IsVisable() )
        s_CUI_ID_FRAME_SkillProduce.Update();

	return true;
	unguard;
}

DWORD CPlayerRole::GetData( enUpdataType enType )
{
	guardfunc;
	DWORD dwReturn = ErrorUnsignedLongID;
	switch( enType )
	{
	case TYPE_ShopCenterScore: //lyh++ 商城积分
		dwReturn = m_pBaseInfo->liveinfo.ConsumeScore;
		break;
	case TYPE_CRITICLE:						// 暴
		{
			dwReturn = m_pBaseInfo->baseProperty.fightAttr.critical.final;
		}
		break;
	case TYPE_CRITICLEINTENSITY:			// 暴击倍率
		{
			dwReturn = m_pBaseInfo->baseProperty.fightAttr.criticalIntensity.final;
		}
		break;
	case TYPE_TENACITY:						// 韧性
		{
			dwReturn = m_pBaseInfo->baseProperty.fightAttr.tenacity.final;
		}
		break;
	case TYPE_ExPower:
		dwReturn = m_pBaseInfo->liveinfo.nXp;
		break;
	case TYPE_Reputation:
		dwReturn = m_pBaseInfo->liveinfo.reputation ;
		break;
	case TYPE_Exploit:
		dwReturn = m_pBaseInfo->liveinfo.exploit ;
		break;
	case TYPE_Glory:
		dwReturn = m_pBaseInfo->liveinfo.honour;
		break;
	case TYPE_CountryScore:
		dwReturn = m_pBaseInfo->liveinfo.dwCountryScore;
		break;
	case TYPE_HP:
		dwReturn = m_pBaseInfo->liveinfo.nHp;
		break;
	case TYPE_Silver:
		dwReturn = m_charinfo.baseinfo.liveinfo.jinDing;
		break;

	case TYPE_GLOD:
		//dwReturn = m_charinfo.baseinfo.liveinfo.dwRMBGold;
		break;

	case TYPE_HPMAX:
		dwReturn = m_pBaseInfo->baseProperty.fightAttr.hpMax.final;
		break;
	case TYPE_MP:
		dwReturn = m_pBaseInfo->liveinfo.nMp;
		break;
	case TYPE_MPMAX:
		dwReturn = m_pBaseInfo->baseProperty.fightAttr.mpMax.final;
		break;
	case TYPE_LEVEL:
		dwReturn = m_pBaseInfo->liveinfo.ustLevel;
		break;
	case TYPE_EXP:
		dwReturn = m_pBaseInfo->liveinfo.dwExp;
		break;
	case TYPE_EXPNOTUSED:
		dwReturn = m_pBaseInfo->liveinfo.dwExpNotUsed;
		break;
	case TYPE_MONEY:
		dwReturn = m_charinfo.baseinfo.liveinfo.dwMoney;
		break;
	case TYPE_ATTACKPHYSICS:
		dwReturn = m_pBaseInfo->baseProperty.fightAttr.attackPhysics.final;
		break;
	case TYPE_AttackMagic:
		dwReturn = m_pBaseInfo->baseProperty.fightAttr.attackMagic.final;
		break;
	case TYPE_DefendPhysics:
		dwReturn = m_pBaseInfo->baseProperty.fightAttr.defendPhysics.final;
		break;
	case TYPE_DefendMagic:
		dwReturn = m_pBaseInfo->baseProperty.fightAttr.defendMagic.final;
		break;
	case TYPE_Strength:					// 力量
		//dwReturn = CalcShowPropertyValue(m_pBaseInfo->baseProperty.baseAttr.baseAttrValue[EBaseAttr_Strength].final);
		dwReturn = m_pBaseInfo->baseProperty.baseAttr.baseAttrValue[EBaseAttr_Strength].final;
		break;
	case TYPE_Stamina:						// 耐力
		//dwReturn = CalcShowPropertyValue(m_pBaseInfo->baseProperty.baseAttr.baseAttrValue[EBaseAttr_Constitution].final);
		dwReturn = m_pBaseInfo->baseProperty.baseAttr.baseAttrValue[EBaseAttr_Stamina].final;
		break;
	case TYPE_Agility:						// 敏捷
		//dwReturn = CalcShowPropertyValue(m_pBaseInfo->baseProperty.baseAttr.baseAttrValue[EBaseAttr_Agility].final);
		dwReturn = m_pBaseInfo->baseProperty.baseAttr.baseAttrValue[EBaseAttr_Agility].final;
		break;
	case TYPE_Intelligence:						// 智力
		//dwReturn = CalcShowPropertyValue(m_pBaseInfo->baseProperty.baseAttr.baseAttrValue[EBaseAttr_Intelligence].final);
		dwReturn = m_pBaseInfo->baseProperty.baseAttr.baseAttrValue[EBaseAttr_Intelligence].final;
		break;
	case TYPE_EXACT:							//命中率
		dwReturn = m_pBaseInfo->baseProperty.fightAttr.exact.final;
		break;
	case TYPE_DODGE:							//躲避率
		dwReturn = m_pBaseInfo->baseProperty.fightAttr.dodge.final;
		break;
	case TYPE_PROFESSION:
		dwReturn = m_pBaseInfo->aptotic.usProfession;
		break;
	case TYPE_ATTACKSPEED:
		dwReturn = m_pBaseInfo->baseProperty.fightAttr.attackSpeed.final;
		break;
// 	case TYPE_INTONATESPEED:
// 		dwReturn = m_pBaseInfo->baseProperty.fightAttr.intonate.final;
// 		break;
	case TYPR_SKILLEXP:
		dwReturn = m_pBaseInfo->liveinfo.dwSkillExp;
		break;
	case TYPR_SKILLEXPNOTUSE:
		dwReturn = m_pBaseInfo->liveinfo.dwSkillExpNotUsed;
		break;
	case TYPE_Pkvalue:
		if (theHeroGame.GetPlayerMgr()&&theHeroGame.GetPlayerMgr()->GetMe())
		{
			dwReturn = theHeroGame.GetPlayerMgr()->GetMe()->GetPKKillValue();			
		}
		else
		{
			return 0;
		}		
		break;
	case TYPE_ENERGY:
		dwReturn = m_pBaseInfo->liveinfo.activity;
		break;
	case TYPE_VIGOR:
		dwReturn = m_pBaseInfo->liveinfo.vigor;
		break;
	case TYPE_ENERGY_MAX:		
		dwReturn = m_pBaseInfo->liveinfo.activityMax;				
		break;
	case TYPE_VIGOR_MAX:
		dwReturn = m_pBaseInfo->liveinfo.vigorMax;
		break;
	case TYPE_MOVESPEED:
		{
			dwReturn = m_pBaseInfo->baseProperty.fightAttr.moveSpeed.final;
		}
		break;
	case TYPE_CaoYao: 						// 草药
		{
			dwReturn = m_pBaseInfo->liveinfo.nSkillPoint[ ERT_CaoYao ];
		}
		break;
	case TYPE_ZhuBao: 						// 珠宝
		{
			dwReturn = m_pBaseInfo->liveinfo.nSkillPoint[ ERT_ZhuBao ];
		}
		break;		
	case TYPE_DuanZao:    					// 锻造
		{
			dwReturn = m_pBaseInfo->liveinfo.nSkillPoint[ ERT_DuanZao ];
		}
		break;
	case TYPE_ZhuJia: 						// 铸甲
		{
			dwReturn = m_pBaseInfo->liveinfo.nSkillPoint[ ERT_ZhuJia ];
		}
		break;
	case TYPE_GongYi: 						// 工艺
		{
			dwReturn = m_pBaseInfo->liveinfo.nSkillPoint[ ERT_GongYi ];
		}
		break;
	case TYPE_XunMa:  					    // 驯马
		{
			dwReturn = m_pBaseInfo->liveinfo.nSkillPoint[ ERT_XunMa ];
		}
		break;
    case TYPE_CaiYao:                       // 采药
        {
            dwReturn = m_pBaseInfo->liveinfo.nSkillPoint[ ERT_CaiYao ];
        }
        break;
    case TYPE_CaiKuang:                     // 采矿
        {
            dwReturn = m_pBaseInfo->liveinfo.nSkillPoint[ ERT_CaiKuang ];
        }
		break;
    case TYPE_BuZhuo:                       // 捕捉
        {
            dwReturn = m_pBaseInfo->liveinfo.nSkillPoint[ ERT_BuZhuo ];
        }
        break;
    case TYPE_BuChong:                       // 捕虫
        {
            dwReturn = m_pBaseInfo->liveinfo.nSkillPoint[ ERT_BuChong ];
        }
        break;
	case TYPE_JinDing:
		dwReturn = m_pBaseInfo->liveinfo.jinDing;
		break;
	case TYPE_JinPiao:
		dwReturn = m_pBaseInfo->liveinfo.jinPiao;
		break;
	case TYPE_TradeMoney:
		dwReturn = m_nTradeMoney;
		break;
	case TYPE_TradeJinDing:
		dwReturn = m_nTradeGold;
		break;
    case TYPE_JiaoZi:
        dwReturn = m_pBaseInfo->liveinfo.jiaoZi;
        break;
	case TYPE_Storage:
		dwReturn = m_pBaseInfo->liveinfo.nStorageItemGrid;
		break;
	case TYPE_PetSrorage:
		dwReturn = m_pBaseInfo->liveinfo.nStorageMountGrid;
		break;
	case TYPE_FreeReliveCount:
		dwReturn = m_pBaseInfo->liveinfo.nFreeReliveCount;
		break;
	case TYPE_BackStrike:                    // 背击伤害
		{
			dwReturn = m_pBaseInfo->baseProperty.fightAttr.backStrike.final;
		}
		break;
	case TYPE_BackStrikeResist:              // 背击抗性
		{
			dwReturn = m_pBaseInfo->baseProperty.fightAttr.backStrikeResist.final;
		}
		break;
	case TYPE_BreakStrike:                   // 破甲伤害
		{
			dwReturn = m_pBaseInfo->baseProperty.fightAttr.breakStrike.final;
		}
		break;
	case TYPE_StabStrike:                    // 贯穿伤害
		{
			dwReturn = m_pBaseInfo->baseProperty.fightAttr.stabStrike.final;
		}
		break;
	case TYPE_ElementStrike:                 // 元素伤害
		{
			dwReturn = m_pBaseInfo->baseProperty.fightAttr.elementStrike.final;
		}
		break;
	case TYPE_ToxinStrike:                   // 毒素伤害
		{
			dwReturn = m_pBaseInfo->baseProperty.fightAttr.toxinStrike.final;
		}
		break;
	case TYPE_SpiritStrike:                  // 精神伤害
		{
			dwReturn = m_pBaseInfo->baseProperty.fightAttr.spiritStrike.final;
		}
		break;
	case TYPE_BreakResist:                   // 破甲抗性
		{
			dwReturn = m_pBaseInfo->baseProperty.fightAttr.breakResist.final;
		}
		break;
	case TYPE_StabResist:                    // 贯穿抗性
		{
			dwReturn = m_pBaseInfo->baseProperty.fightAttr.stabResist.final;
		}
		break;
	case TYPE_ElementResist:                 // 元素抗性
		{
			dwReturn = m_pBaseInfo->baseProperty.fightAttr.elementResist.final;
		}
		break;
	case TYPE_ToxinResist:                   // 毒素抗性
		{
			dwReturn = m_pBaseInfo->baseProperty.fightAttr.toxinResist.final;
		}
		break;
	case TYPE_SpiritResist:                  // 精神抗性
		{
			dwReturn = m_pBaseInfo->baseProperty.fightAttr.elementResist.final;
		}
		break;
	case TYPE_Daoxing:
		{
			dwReturn = m_pBaseInfo->liveinfo.daoxing;
		}
		break;
	case TYPE_CurGetDaoxing:
		{

		}
		break;
	case TYPE_BasePotential:
		{
			dwReturn = m_pBaseInfo->liveinfo.basePotential;
		}
		break;
	}

	return dwReturn;
	unguard;
}
void CPlayerRole::SetMoneyOnPlayer(DWORD dwMoney )
{
	guardfunc;
	m_charinfo.baseinfo.liveinfo.dwMoney = dwMoney;
	unguard;
}
int		CPlayerRole::GetMyHP(void)
{
	guardfunc;
	return m_pBaseInfo->liveinfo.nHp;
	unguard;
}
int		CPlayerRole::GetMyMP(void)
{
	guardfunc;
	return m_pBaseInfo->liveinfo.nMp;
	unguard;
}

//------- 更新界面    (   at 11/10/2003)
void CPlayerRole::UpdateUI()
{
	guardfunc;
	m_bUpdateUI = true;
	unguard;
}

bool CPlayerRole::IsNeedUpdateUI()
{
	guardfunc;
	bool bResult = m_bUpdateUI;
	m_bUpdateUI = false;
	return bResult;
	unguard;
}

void CPlayerRole::SetPlayerMP(int nMPDec)
{
	guardfunc;
	Update( TYPE_MP,nMPDec);
	UpdateUI();
	unguard;
}

void CPlayerRole::DecPlayerMP( short stMPDec )
{
	guardfunc;
	int iMP = GetData( TYPE_MP );
	if( iMP > stMPDec )
		iMP -= stMPDec;
	else
		iMP = 0;
	Update( TYPE_MP,iMP );
	UpdateUI();
	unguard;
}

void CPlayerRole::IncPlayerMP( short stMPInc )
{
	guardfunc;
	int iMP = GetData( TYPE_MP );
	int iMPMax = GetData( TYPE_MPMAX );

	iMP += stMPInc;
	if(iMP>iMPMax)
		iMP = iMPMax;

	Update( TYPE_MP, iMP );
	UpdateUI();
	unguard;
}

void CPlayerRole::SetPlayerHP(int nHPDec)
{
	guardfunc;
	Update( TYPE_HP,nHPDec);
	UpdateUI();
	unguard;
}

BOOL	CPlayerRole::IsDie()
{
	guardfunc;
	if( theHeroGame.GetPlayerMgr()->GetMe() == NULL )
		return TRUE;

	return theHeroGame.GetPlayerMgr()->GetMe()->IsDead();
	unguard;
}

void CPlayerRole::DecPlayerHP( short stHPDec )
{
	guardfunc;
	int iHP = GetData( TYPE_HP );
	if( iHP > stHPDec )
		iHP -= stHPDec;
	else
		iHP = 0;
	Update( TYPE_HP,iHP );
	UpdateUI();
	unguard;
}

void CPlayerRole::IncPlayerHP( short stHPInc )
{
	guardfunc;
	int iHP = GetData( TYPE_HP );
	int iHPMax = GetData( TYPE_HPMAX );
	
	iHP += stHPInc;
	if(iHP>iHPMax)
		iHP = iHPMax;

	Update( TYPE_HP, iHP );
	UpdateUI();
	unguard;
}

void CPlayerRole::Levelup(unsigned short ustNewLevel)
{
	guardfunc;
	m_charinfo.baseinfo.liveinfo.ustLevel = ustNewLevel;
	UpdateUI();
	unguard;
}

void CPlayerRole::SkillLevelUp(unsigned short ustSkillLevel,unsigned short ustSkillID)
{
	guardfunc;
	SCharSkill* pSkill = NULL;
	pSkill = m_SkillBag.GetSkillByID( ustSkillID);
	if (pSkill)
	{
		pSkill->stSkillLevel = ustSkillLevel;

		ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
		
		if (pItemSkill)
		{
			if (ustSkillLevel > pItemSkill->ustSkillMaxLvl||ustSkillLevel == pItemSkill->ustSkillMaxLvl)
			{
				pSkill->stSkillLevel = pItemSkill->ustSkillMaxLvl;

			}
			{
				char szTemp1[128] = {0};
				MeSprintf_s( szTemp1,sizeof(szTemp1)/sizeof(char) - 1, "%s %s%d",pItemSkill->GetItemName(), theXmlString.GetString(eText_SkillLevelUp),pSkill->stSkillLevel );
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_Learnt, szTemp1 );
			}
		}
	}
    s_CUI_ID_FRAME_SkillProduce.Refresh();
    s_CUI_ID_ProduceLearn.Refresh();
	s_CUI_ID_FRAME_SKILL.NeedRefresh();
	s_CUI_ID_FRAME_SKILL_LEARN.Refresh();
	s_CUI_ID_FRAME_MAIN.RefeashHotKey();
	s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
    s_CUI_ID_FRAME_AutoAttackSet.RefreshSkillUI(true);
	unguard;
}

//对技能进行分类组织
void CPlayerRole::ReOrganizeSkill( )
{
	guardfunc;
	ItemDefine::SItemSkill *pItemSkill = NULL;
	m_iNormalSkillNum = m_iMagicSkillNum = 0;
	for( int iLoop = 0; iLoop < m_SkillBag.GetSkillNum(); iLoop++ )
	{
		SCharSkill* pSkill = m_SkillBag.GetSkillByIndex( iLoop );
		if ( !pSkill )
		{
			continue;
		}
		if( pSkill->ustSkillID == InvalidLogicNumber )
		{
			continue;
		}
		pItemSkill = GettheItemDetail().GetSkillByID( pSkill->ustSkillID,
													pSkill->stSkillLevel );
		if (NULL != pItemSkill)
		{
			if(ItemDefine::generaltype_action == pItemSkill->stGeneralType)
			{
				m_iNormalSkillIndexArray[m_iNormalSkillNum++] = iLoop;
			}
			else
			{
				m_iMagicSkillIndexArray[m_iMagicSkillNum++] = iLoop;
			}
		}
	}
	unguard;
}

void CPlayerRole::UpdateArmourUI()
{
	s_CUI_ID_FRAME_PACK.RefreshArmour();
}

//技能操作函数
short CPlayerRole::GetSkillLevel( short stSkillIndex )
{
	guardfunc;
	SCharSkill* pSkill = m_SkillBag.GetSkillByIndex( stSkillIndex );
	if ( !pSkill )
	{
		return 0;
	}
	return pSkill->stSkillLevel;
	unguard;
}
short CPlayerRole::GetSkillLevelById( short stSkillId )
{
	guardfunc;
	for ( int n = 0; n<m_SkillBag.GetSkillNum(); n++ )
	{
		SCharSkill* pSkill = m_SkillBag.GetSkillByIndex( n );
		if ( !pSkill )
		{
			continue;
		}
		if ( pSkill->ustSkillID == stSkillId )
		{
			return pSkill->stSkillLevel;
		}
	}
	return -1;
	unguard;
}

void CPlayerRole::SetSkillLevel( short stSkillIndex, short stNewLevel )
{
	guardfunc;
	SCharSkill* pSkill = m_SkillBag.GetSkillByIndex( stSkillIndex );
	if ( !pSkill )
	{
		return;
	}
	pSkill->stSkillLevel = stNewLevel;
	unguard;
}
//判断可否装备一个道具
bool CPlayerRole::IsCanEquip(SCharItem *pItem)
{
	guardfunc;
	//
	ItemDefine::SItemCanEquip *pCanEquip = NULL;
	ItemDefine::SItemCommon *pItemCommon = NULL;
	//

	//
	pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
	if(!pItemCommon)
		return false;
	//
	switch (pItemCommon->ucItemType)
	{
	case ItemDefine::ITEMTYPE_WEAPON:
	case ItemDefine::ITEMTYPE_ARMOUR:
	//case CItemDetail::ITEMTYPE_MEDAL:
		break;
	default:
		return false;
		break;
	}
	//
	pCanEquip = (ItemDefine::SItemCanEquip*)pItemCommon;	
	//装备的性别需求不符！
	if( -1 != pCanEquip->cEquipSexReq )
	{	
		if( pCanEquip->cEquipSexReq!= GetSex( ) )
		{
			return false;
		}
	}

	//职业需求	
	if (!pCanEquip->arrayEquipArmsReq[GetProfession( )])
		return false;

	//级别需求
	if(pCanEquip->stEquipLevelReq > m_charinfo.baseinfo.liveinfo.ustLevel)
		return false;

	return true;
	unguard;
}
bool CPlayerRole::IsCanEquip(SCharItem *pItem, ItemDefine::TagEquipRequest *pEquipReq)
{
	guardfunc;
	bool ret = true;
	//
	ItemDefine::SItemCanEquip *pCanEquip = NULL;
	ItemDefine::SItemCommon *pItemCommon = NULL;
	//
	memset(pEquipReq, 0x00, sizeof(*pEquipReq));
	//
	pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
	if(!pItemCommon)
		return false;
	//
	switch (pItemCommon->ucItemType)
	{
	case ItemDefine::ITEMTYPE_WEAPON:
	case ItemDefine::ITEMTYPE_ARMOUR:
		break;
	default:
		return false;
		break;
	}
	//
	pCanEquip = (ItemDefine::SItemCanEquip*)pItemCommon;	
	//装备的性别需求不符！
	if( -1 != pCanEquip->cEquipSexReq )
	{	
		if( pCanEquip->cEquipSexReq!= GetSex( ) )
		{
			ret = false;
		}
		else
		{
			pEquipReq->bSex = true;
		}
	}

	//职业需求	
	if (!pCanEquip->arrayEquipArmsReq[GetProfession( )])
		ret = false;
	else
		pEquipReq->bProfession = true;

	//级别需求
	if(pCanEquip->stEquipLevelReq > m_charinfo.baseinfo.liveinfo.ustLevel)
		ret = false;
	else
		pEquipReq->bLevel = true;

	return ret;
	unguard;
}

void	CPlayerRole::OnAddTeamMember( TeamInfo &InInfo)

{
	guardfunc;
	for(int i=0; i<m_TeamData.size(); ++i)
	{//屏蔽服务器重复发的队员信息
		if( m_TeamData[i].nID == InInfo.nID )
		{
			return;
		}
	}
	TeamInfo info;
	info.nID		= InInfo.nID;
	info.szName		= InInfo.szName;
	info.nHp		= InInfo.nHp;
	info.nMaxHp		= InInfo.nMaxHp;
	info.nMp		= InInfo.nMp;
	info.nMaxMp		= InInfo.nMaxMp;
	info.nLvl		= InInfo.nLvl;
	info.nMapID		= InInfo.nMapID;
	info.bHeader	= InInfo.bHeader;
	info.bHeader2	= InInfo.bHeader2;
	info.x			= InInfo.x;
	info.y			= InInfo.y;
	info.ucSex		= InInfo.ucSex;
	info.usProfession = InInfo.usProfession;
	info.stManiple = InInfo.stManiple;
	info.bIsNewAdd = InInfo.bIsNewAdd;
	info.bOnline	= InInfo.bOnline;

	info.nHairId = InInfo.nHairId;
	info.nFaceId = InInfo.nFaceId;
    info.nHeadPicId = InInfo.nHeadPicId;

	if (info.bIsNewAdd && strcmp(thePlayerRole.GetName() , info.szName.c_str()) != 0)
	{
		char szTemp[128] = {0};
		MeSprintf_s( szTemp,sizeof(szTemp)/sizeof(char) - 1, theXmlString.GetString(eClient_AddInfo_2slk_137), info.szName.c_str());
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, szTemp );
	}

	m_TeamData.push_back(info);
	s_CUI_ID_FRAME_Target.TeamStatesChange();//更新当前目标

	s_CUI_Group.Refeash();
	unguard;
}
void	CPlayerRole::UpdataPlayerInfo( TeamInfo &InInfo, BOOL OnlyRefeashHPUI )
{
	guardfunc;
	BOOL bHeaderChange = FALSE;
	BOOL bChangeHP = FALSE;
	BOOL bChangeMP = FALSE;
	BOOL bChangeOther = FALSE;
	for(int i=0; i<m_TeamData.size(); ++i)
	{
		if( m_TeamData[i].nID == InInfo.nID )
		{
			
			if( m_TeamData[i].nHp != InInfo.nHp )
			{
				m_TeamData[i].nHp = InInfo.nHp;
				bChangeHP = TRUE; 
			}

			if(m_TeamData[i].nMaxHp != InInfo.nMaxHp)
			{
				m_TeamData[i].nMaxHp = InInfo.nMaxHp;
				bChangeOther = TRUE;
			}
			if( m_TeamData[i].nMp != InInfo.nMp )
			{
				m_TeamData[i].nMp = InInfo.nMp;
				bChangeMP = TRUE;
			}

			if( m_TeamData[i].nMaxMp != InInfo.nMaxMp )
			{
				m_TeamData[i].nMaxMp = InInfo.nMaxMp;
				bChangeOther = TRUE;
			}
			
			if( m_TeamData[i].nLvl != InInfo.nLvl )
			{
				m_TeamData[i].nLvl = InInfo.nLvl;
				bChangeOther = TRUE;
			}

			if( m_TeamData[i].nMapID != InInfo.nMapID )
			{
				m_TeamData[i].nMapID = InInfo.nMapID;
				bChangeOther = TRUE;
			}
			
			if (abs(m_TeamData[i].fx - InInfo.fx) > 0.001f)
			{
				m_TeamData[i].fx = InInfo.fx;
				bChangeOther = TRUE;
			}
			m_TeamData[i].x = InInfo.x;
			m_TeamData[i].y = InInfo.y;
			if (abs(m_TeamData[i].fy - InInfo.fy) > 0.001f)
			{
				m_TeamData[i].fy = InInfo.fy;
				bChangeOther = TRUE;
			}

			if( m_TeamData[i].bHeader != InInfo.bHeader )
			{
				m_TeamData[i].bHeader = InInfo.bHeader;
				if (InInfo.bHeader)
				{
					for(int z=0; z<m_TeamData.size(); ++z)
					{
						if (z != i)
						{
							m_TeamData[z].bHeader = false;
						}

					}
				}

				bHeaderChange = TRUE;
			}
			

			if( m_TeamData[i].bHeader2 != InInfo.bHeader2 )
			{
				m_TeamData[i].bHeader2 = InInfo.bHeader2;
				bHeaderChange = TRUE;
			}
			if( m_TeamData[i].usProfession != InInfo.usProfession )
			{
				m_TeamData[i].usProfession = InInfo.usProfession;
				bChangeOther = TRUE;
			}

			if( m_TeamData[i].stManiple != InInfo.stManiple )
			{
				m_TeamData[i].stManiple = InInfo.stManiple;
				bChangeOther = TRUE;
			}
			if( m_TeamData[i].bOnline != InInfo.bOnline )
			{
				m_TeamData[i].bOnline = InInfo.bOnline;
				bChangeOther = TRUE;
			}
			if (m_TeamData[i].AssignMode != InInfo.AssignMode)
			{
				m_TeamData[i].AssignMode = InInfo.AssignMode;
			}

		}
	}


	if( OnlyRefeashHPUI )
	{
		s_CUI_Group.RefeashGroupMemberHP( InInfo );
		return;
	}
	else
	{
		if( bChangeHP || bChangeMP )
		{
			s_CUI_Group.RefeashGroupMemberHP( InInfo );
		}
		if( bChangeOther || bHeaderChange)
		{
			s_CUI_Group.RefeashGroup();
		}
	}

	SetAssignMode(InInfo.AssignMode);
	unguard;
}
//删除队友
void	CPlayerRole::OnDeleteTeamMember(int nID)
{
	guardfunc;
	// test
	std::vector<TeamInfo>::iterator iter = m_TeamData.begin();
	for( ; iter != m_TeamData.end(); ++iter)
	{
		if( (*iter).nID == nID )
		{
			char szTemp[128] = {0};
			MeSprintf_s( szTemp,sizeof(szTemp)/sizeof(char) - 1, theXmlString.GetString(eClient_AddInfo_2slk_138), (*iter).szName.c_str());
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, szTemp );
			m_TeamData.erase( iter );
			break;
		}
	}
	s_CUI_Group.updateGroupSelect( nID );
	s_CUI_Group.Refeash();
	unguard;
}

//离开队伍
void	CPlayerRole::OnExitTeam(void)
{
	guardfunc;
	m_bCorps = FALSE;
	m_TeamData.clear();
    SetAssignMode(AssignMode_Team);
    SetItemRollLevel(eIL_Choiceness);
	s_CUI_Group.Refeash();
	s_CUI_ID_FRAME_SelfRBMenu.SetVisable( FALSE );

	s_CUI_ID_FRAME_Target.TeamStatesChange();//更新当前目标
	SetGroupId(-1);
	unguard;
}

//使用恢复药品
void	CPlayerRole::OnRestoreItem(int ItemID, int TagNpcID)
{
	assert(false);
}

//使用基本动作
void	CPlayerRole::OnBaseAction(int ItemID, int TagNpcID)
{
	guardfunc;
	int skill_id, skill_level;
	//
	switch (ItemID)
	{
	case 902: //攻击的ID
		switch (GetProfession())
		{
		case EArmType_Warrior:
			skill_id = ConstSkillId_NormalAttack_Combat;
			break;
		case EArmType_Taoist:
			skill_id = ConstSkillId_NormalAttack_Combat;
			break;
		case EArmType_Assassin:
			skill_id = ConstSkillId_NormalAttack_Combat;
			break;		
		case EArmType_Mage:
			skill_id = ConstSkillId_NormalAttack_Combat;
			break;
		case EArmType_Hunter:
			skill_id = ConstSkillId_NormalAttack_Combat;
			break;
		default:
			skill_id = ConstSkillId_NormalAttack_Combat;
			break;
		}
		skill_level = 0;
		theHeroGame.GetPlayerMgr()->RoleAttack(TagNpcID, 0, 0, skill_id, skill_level);
		break;
	default:
		break;
	}
	unguard;
}
//社群动作
void	CPlayerRole::OnCorporation(int ItemID, int TagNpcID)
{
}
//社交动作
void	CPlayerRole::OnSociality(int ItemID, int TagNpcID)
{
	
}

//----
//	判段使用的技能是否是已学能用的
//----
BOOL	CPlayerRole::IsSkillCanUse( ItemDefine::SItemSkill* pSkill )
{
	guardfunc;
	//主角是否可以使用一个技能在这里的判定很重要
	for (int i=0; i<m_SkillBag.GetSkillNum(); i++)
	{
		SCharSkill* pCharSkill = m_SkillBag.GetSkillByIndex(i);
		if ( !pCharSkill )
		{
			continue;
		}
		if ( pCharSkill->ustSkillID == pSkill->ustItemID &&
			pCharSkill->stSkillLevel >= pSkill->ustLevel )
		{
			return pCharSkill->bAvailable;
		}
	}
	return FALSE;
	unguard;
}

//----
//	判段使用的技能是否能用
//----
bool	CPlayerRole::IsSkillCanUse(int iSkillID, int iSkillLevel)
{
	guardfunc;
	//TODO: 主角是否可以使用一个技能在这里的判定很重要
	ItemDefine::SItemSkill *pItemSkill = GettheItemDetail().GetSkillByID( iSkillID, iSkillLevel);
	if (pItemSkill->sSkillCategory>=ItemDefine::SCT_HeroPassive && pItemSkill->sSkillCategory<=ItemDefine::SCT_HeroAttack)
	{
		for (int i=0; i<More_iMaxHeroSkill; i++)
		{
			SCharSkill* pSkill = m_HeroSkillBag.GetSkillByIndex(i);
			if ( !pSkill )
			{
				continue;
			}
			if ( pSkill->ustSkillID == iSkillID &&
				pSkill->stSkillLevel >= iSkillLevel )
			{
				return pSkill->bAvailable;
			}		   
		}
	}
	for (int i=0; i<More_iMaxSkillKnown; i++)
	{
		SCharSkill* pSkill = m_SkillBag.GetSkillByIndex(i);
		if ( !pSkill )
		{
			continue;
		}
		if ( pSkill->ustSkillID == iSkillID &&
		   pSkill->stSkillLevel >= iSkillLevel )
		{
			return pSkill->bAvailable;
		}		   
	}

	return false;
	unguard;
}

void CPlayerRole::SetCountry( int iCountry )
{
	guardfunc;
	m_charinfo.baseinfo.aptotic.ucCountry = iCountry;
	unguard;
}

int	CPlayerRole::GetCountry( void )
{
	guardfunc;
	return m_charinfo.baseinfo.aptotic.ucCountry;
	unguard;
}

void CPlayerRole::SetWeakCountry( int iCountry )
{
    guardfunc;
    if( iCountry > CountryDefine::Country_Init && iCountry < CountryDefine::Country_Max )
    {
        m_nWeakCountryId = iCountry;
    }
    unguard;
}
void CPlayerRole::SetStrongCountry( int iCountry )
{
    guardfunc;
    if( iCountry > CountryDefine::Country_Init && iCountry < CountryDefine::Country_Max )
    {
        m_nStrongCountryId = iCountry;
    }
    unguard;
}
bool CPlayerRole::IsInWeakCountry()
{
    return ( GetCountry() == m_nWeakCountryId && GetCountry() != CountryDefine::Country_Init && m_nWeakCountryId !=  CountryDefine::Country_Init);
}
bool CPlayerRole::IsInStrongCountry()
{
	return ( GetCountry() == m_nStrongCountryId  && GetCountry() != CountryDefine::Country_Init && m_nStrongCountryId !=  CountryDefine::Country_Init);
}
CPlayerRole::QuestInfo* CPlayerRole::FindVariableInfoById( int nVariableId )
{
	QuestInfos::iterator it = m_VariableInfos.find(nVariableId);
	return it != m_VariableInfos.end() ? &(it->second) : NULL;
}

CPlayerRole::QuestInfo* CPlayerRole::FindQuestInfoById( int nQuestId )
{
	guardfunc;
    QuestInfos::iterator it = m_questInfos.find(nQuestId);
    return it != m_questInfos.end() ? &(it->second) : NULL;
	unguard;
}

int	CPlayerRole::GetVariableValue( int number )
{
	CPlayerRole::QuestInfo* pInfo = FindVariableInfoById(number);
	if (pInfo)
		return pInfo->chState;

	return 0;
}

bool CPlayerRole::ChangeQuestState( int nQuestId, short chState )
{
	guardfunc;
	bool bRet = false;
	QuestInfo* pInfo = FindQuestInfoById( nQuestId );
	// 如果找到，说明是状态改变，
	if( pInfo )
	{	
		pInfo->chState = chState;
		UpdateActiveQuestStateByQuest(pInfo);
		bRet = true;
	}
	else
	{
		pInfo = FindVariableInfoById( nQuestId );
		if (pInfo)
		{	
			pInfo->chState = chState;
		}
		else
		{
			// 新变量
			QuestInfo info;
			info.nQuestId = nQuestId;
			info.chState = chState;

			m_VariableInfos.insert(QuestInfos::value_type(info.nQuestId, info));

			pInfo = FindVariableInfoById( nQuestId );
		}
		if(UpdateActiveQuestStateByVariable(pInfo))
			bRet = true;
	}

 	try
 	{
 		char filename[MAX_PATH] = {0};
 		MeSprintf_s(filename, sizeof(filename)/sizeof(char) - 1,"%s/Data/Quest/CalculateExp.string", GetRootPath());
 
 		LuaObject Variable = ScriptManager::instance().getLuaStateOwner(filename)->GetGlobal("Variable" );
 		Variable.SetInteger(nQuestId, chState);
 	}
 	catch ( const LuaPlus::LuaException& e )
 	{
 		OutputDebugString( ( std::string( e.GetErrorMessage() ) + "\n" ).c_str() );
 	}
	return bRet;
	unguard;
}
void CPlayerRole::UpdateActiveQuestState( BOOL bUpDataUI ,BOOL bRefreshAll)
{
	guardfunc;
	if (!bUpDataUI)
	{
		return;
	}
	if (bRefreshAll || m_vectorActiveQuestInfo.size() == 0)
	{
		m_vectorActiveQuestInfo.clear();
		QuestInfos::iterator it/*, end = m_questInfos.end()*/;
		for(it = m_questInfos.begin(); it != m_questInfos.end(); ++it)
		{
			QuestInfo& info = it->second;

			AddToActiveQuestInfo(&info);
		}
		theHeroGame.GetPlayerMgr()->RefreshAllNpcQuest();
 		GetRegionMap()->SetUpdateStableImage(true);
		s_CUI_ID_FRAME_Task.SetDirty( true );
	}
	RefreshQuestDone();

	// 需要更新界面
	s_CUI_ID_FRAME_Task.Refresh( false);
	unguard;
}

void CPlayerRole::ReqQuestInfo( int nQuestId )
{
	guardfunc;
	unguard;
}

void CPlayerRole::StartMoving( GameObjectId id, DWORD dwStartingTime, float x, float y, float z, float DirX, float DirY, short shMovingType )
{
	guardfunc;

	if( m_bStartCollectPos)
	{
		return;
	}

	if( m_vLastSavePos.x != x || m_vLastSavePos.y != y || m_cLastSaveDirX != (char)(DirX*127) || m_cLastSaveDirY != (char)(DirY*127) )
	{
		m_bStartCollectPos = TRUE;
		m_dwStartCollectPosTime = 0;
	}
	unguard;
}

#include "Cfg.h"
#include "MeTerrain/NiColor.h"
#include "MeTerrain/SwType.h"
#include "MeTerrain/SwDebug.h"
#include "MeTerrain/STCommon.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/SwPublicFunc.h"
#include "MeTerrain/HashTable.h"
#include "MeTerrain/MapFile.h"
#include "MeTerrain/MapUtil.h"
#include "MeTerrain/World.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/WorldTile.h"
#include "MeTerrain/WorldChunk.h"
#include "MeTerrain/NdlRes.h"
#include "MeTerrain/NdlResMgr.h"
extern CCfg gCfg;
extern CHeroGame* theApp;

bool ChangeMapServerBusy_Confirm( const char bPressYesButton, void *pData )
{
    UiDrawer::StartFillFullScreen( 500, false );
    return true;
}

bool ChangeMapServerBusy( const char bPressYesButton, void *pData )
{
    s_CUI_ID_FRAME_MessageBox.Show(
        theXmlString.GetString(eText_ChangeMapServerBusy),
        theXmlString.GetString(eText_ChangeMapServerBusy),
        CUI_ID_FRAME_MessageBox::eTypeConfirm,
        true,
        ChangeMapServerBusy_Confirm );

	s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(true);
	s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(true);
    
    thePlayerRole.CloseShowingWaitforTransport();
    return true;
}

void CPlayerRole::SendMoveMessage( GameObjectId id, float x, float y, float z, float DirX, float DirY, DWORD dwCurTime, BOOL bMoving, short shMovingType, BOOL bLastFrameMoving )
{
	guardfunc;

	if( !m_bNeedSendLastPos && fabs(m_vLastSavePos.x - x) < 0.001 && fabs(m_vLastSavePos.y - y) < 0.001 && abs(m_cLastSaveDirX - (char)(DirX*127))<=1 && abs(m_cLastSaveDirY - (char)(DirY*127))<=1 )
	{
	    m_bStartCollectPos = bMoving;
		return;
	}
	m_dwStartCollectPosTime = dwCurTime;

	if( bMoving )
	{
		bool bNeedChangeMap = false;

		// 人物移动中判断是否进跳转点[QL]
		if( !m_bWaitforTransport )
		{
			int nMapId, nTargetId, nEntranceId;
			if( IsInTransport(x, y, nMapId, nTargetId, nEntranceId) )
			{
				if( !gCfg.m_bLocalVersion )
				{
                    // 等级判断
                    CWorldTile* worldTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(nMapId);
                    if( worldTile && worldTile->GetMinLevel() > GetLevel() )
                    {
                        // 等级不够无法传送
                        char msg[MAX_PATH] = {0};
                        MeSprintf_s(msg,sizeof(msg)/sizeof(char) - 1, theXmlString.GetString( eTellClient_LessMapMinLevel ), worldTile->GetMinLevel() );
                        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_FindPathFailed,  msg );
                    }
                    else
                    {
                        bNeedChangeMap = true;
                        // 等待传送
					    m_bWaitforTransport = true;
      //                  s_CUI_ID_FRAME_MessageBox.Show(
      //                      theXmlString.GetString(eText_WaitForChangeMap),
      //                      theXmlString.GetString(eText_WaitForChangeMap),
      //                      CUI_ID_FRAME_MessageBox::eTypeConfirm,
      //                      true,
      //                      ChangeMapServerBusy );
      //                  s_CUI_ID_FRAME_MessageBox.SetAutoClose(CHANGE_MAP_WAIT_TIME);

						//s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(false);
						//s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(false);
						//s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(false);

      //                  UiDrawer::StartFillFullScreen( 500, true ); // 屏幕变黑
      //                  m_bShowingWaitforTransport = true;
                    }
				}
				else
				{
					//单机版本地跳转
					theApp->JumpToWorldFromTransport(nMapId,nTargetId);
				}
			}
		}
        else
        {
            // 等待传送超时后，如果出传送区域，则重置m_bWaitforTransport
            int nMapId, nTargetId, nEntranceId;
            if( !IsInTransport(x, y, nMapId, nTargetId, nEntranceId) )
            {
                m_bWaitforTransport = false;
                m_bShowingWaitforTransport = false;
            }
        }

        m_bNeedSendLastPos = TRUE;

		if( m_cLastSaveDirX != (char)(DirX*127) || m_cLastSaveDirY != (char)(DirY*127) )
		{
			MsgPlayerMovingPosAndDirToServer msg;
			msg.header.stID = id;
			msg.header.uMsgLevel = level_high;
			msg.vPos.x = x;
			msg.vPos.y = y;
			msg.vPos.z = z;
			msg.chDirX = (char)(DirX*127);
			msg.chDirY = (char)(DirY*127);
			msg.chDirZ = 0;
			msg.dwSendTime = HQ_TimeGetTime();
			msg.bNeedChangeMap = bNeedChangeMap;
			GettheNetworkInput().SendMsg( &msg );
			//GettheNetworkInput().CheckSendReq();
			m_bCanSendActionMessage = FALSE;
            m_bMustSendMovingMessage = FALSE;
		}
		else
		{
			MsgPlayerMovingPosToServer msg;
			if( !bLastFrameMoving && !bNeedChangeMap )
			{

			}
			else
			{
				msg.header.stID = id;
				msg.header.uMsgLevel = level_high;
				msg.vPos.x = x;
				msg.vPos.y = y;
				msg.vPos.z = z;
				msg.dwSendTime = HQ_TimeGetTime();
				msg.bNeedChangeMap = bNeedChangeMap;
				GettheNetworkInput().SendMsg( &msg );
				//GettheNetworkInput().CheckSendReq();
				m_bCanSendActionMessage = FALSE;
                m_bMustSendMovingMessage = FALSE;
            }
		}
	}
	else
	{
		bool bSendMsg = false;
		if( m_vLastSavePos.x != x || m_vLastSavePos.y != y )
		{
			if( m_cLastSaveDirX != (char)(DirX*127) || m_cLastSaveDirY != (char)(DirY*127) )
			{
                MsgPlayerPosAndDirToServer msg;
				msg.header.stID = id;
				msg.header.uMsgLevel = level_high;
				msg.vPos.x = x;
				msg.vPos.y = y;
				msg.vPos.z = z;
				msg.chDirX = (char)(DirX*127);
				msg.chDirY = (char)(DirY*127);
				msg.chDirZ = 0;
				msg.dwSendTime = HQ_TimeGetTime();
				GettheNetworkInput().SendMsg( &msg );
				//GettheNetworkInput().CheckSendReq();
				bSendMsg = true;
				m_bCanSendActionMessage = TRUE;
                m_bNeedSendLastPos = FALSE;
			}
			else
			{
				MsgPlayerPosToServer msg;
				msg.header.stID = id;
				msg.header.uMsgLevel = level_high;
				msg.vPos.x = x;
				msg.vPos.y = y;
				msg.vPos.z = z;
				msg.dwSendTime = HQ_TimeGetTime();
				GettheNetworkInput().SendMsg( &msg );
				//GettheNetworkInput().CheckSendReq();
				bSendMsg = true;
				m_bCanSendActionMessage = TRUE;
                m_bNeedSendLastPos = FALSE;
			}
		}
		else
		{
			if( m_cLastSaveDirX != (char)(DirX*127) || m_cLastSaveDirY != (char)(DirY*127) )
			{
				MsgPlayerDirToServer msg;
				msg.header.stID = id;
				msg.header.uMsgLevel = level_high;
				msg.vPos.x = x;
				msg.vPos.y = y;
				msg.vPos.z = z;
				msg.chDirX = (char)(DirX*127);
				msg.chDirY = (char)(DirY*127);
				msg.chDirZ = 0;
				msg.dwSendTime = HQ_TimeGetTime();
				GettheNetworkInput().SendMsg( &msg );
				//GettheNetworkInput().CheckSendReq();
				bSendMsg = true;
				m_bCanSendActionMessage = TRUE;
                m_bNeedSendLastPos = FALSE;
			}
		}

		if( !bSendMsg )
		{
			MsgPlayerPosToServer msg;
			msg.header.stID = id;
			msg.header.uMsgLevel = level_high;
			msg.vPos.x = x;
			msg.vPos.y = y;
			msg.vPos.z = z;
			msg.dwSendTime = HQ_TimeGetTime();
			GettheNetworkInput().SendMsg( &msg );
			//GettheNetworkInput().CheckSendReq();
			m_bCanSendActionMessage = TRUE;
            m_bNeedSendLastPos = FALSE;
		}
	}

	m_vLastSavePos.x = x;
	m_vLastSavePos.y = y;
	m_cLastSaveDirX = (char)(DirX*127);
	m_cLastSaveDirY = (char)(DirY*127);

	OnCloseShopAnCK();
	unguard;
}

BOOL CPlayerRole::CanSendMoveMessage( DWORD dwCurTime )
{
	guardfunc;
	if( m_bStartCollectPos && ( (dwCurTime - m_dwStartCollectPosTime) >= 180 /*|| m_bMustSendMovingMessage*/ ))
	{
		return TRUE;
	}
	return FALSE;
	unguard;
}

BOOL CPlayerRole::CanUseSpecialSkill()
{
	guardfunc;
	return m_bCanUseSpecialSkill;
	unguard;
}

void CPlayerRole::SetCanUseSpecialSkill( BOOL bCan )
{
	guardfunc;
	m_bCanUseSpecialSkill = bCan;
	unguard;
}

BOOL CPlayerRole::CanSendActionMessage()
{
	guardfunc;
	return m_bCanSendActionMessage;
	unguard;
}

#ifdef _DEBUG
D3DXVECTOR3 g_TempVt[3];
D3DXVECTOR3 g_TempLine[2];
#endif

BOOL CPlayerRole::GetDistToCollision( D3DXVECTOR3 vStart, D3DXVECTOR3 vDir, float* fDistToCollision,
									 D3DXVECTOR3* vCollisionDir /* = NULL */, D3DXVECTOR3* vCollisionNormal /* = NULL */,
                                     float* fAngleToCollision /* = NULL  */, BOOL bNeedAdjustWithAngle/* = TRUE*/, BOOL bNeedAdjust/* = TRUE*/ )
{
	guardfunc;


	if (((abs(vDir.x) < 0.001f) && (abs(vDir.y) < 0.001f) && (abs(vDir.z) < 0.001f)))
	{
		return false;
	}
#ifdef _DEBUG
	memset( &g_TempVt, 0, sizeof(D3DXVECTOR3)*3 );
	memset( &g_TempLine, 0, sizeof(D3DXVECTOR3)*2 );
#endif
	if( SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile() )
	{
		TPickResult castDynamicResult;
		castDynamicResult.Reset();
		bool bPickDynamicCollisoin = false;
		// 判断动态碰撞
		if( theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->m_vecDynamicCollison.size() > 0 )
		{
			BspTree::SIntersect* pIntersect = theHeroGame.GetPlayerMgr()->m_DynamicCollisionBsp.GetNearestIntersect(*(Vector*)&vStart, *(Vector*)&vDir);
			if (pIntersect)
			{
				castDynamicResult.pickResultInfo[0].resultType	= emPT_CollisionObj;
				castDynamicResult.pickResultInfo[0].resultId		= 0;
				castDynamicResult.pickResultInfo[0].resultObjInfo	= 0;
				castDynamicResult.pickResultInfo[0].point			= pIntersect->pos;
				castDynamicResult.pickResultInfo[0].dist			= pIntersect->t;
				castDynamicResult.pickResultInfo[0].vFacePos[0]	= pIntersect->vFacePos[0];
				castDynamicResult.pickResultInfo[0].vFacePos[1]	= pIntersect->vFacePos[1];
				castDynamicResult.pickResultInfo[0].vFacePos[2]	= pIntersect->vFacePos[2];
				castDynamicResult.pickResultInfo[0].normal		= pIntersect->vNormal;
				castDynamicResult.pickResultCount++;
				bPickDynamicCollisoin = true;
			}
		}

		TPickResult castResult;
		bool bPick = SwGlobal::GetWorldPicker()->Pick(*(Vector*)&vStart, *(Vector*)&vDir,castResult,emPT_CollisionObj,true,WORLD_CHUNKSIZE);
		if( bPickDynamicCollisoin || bPick )
		{
			float fDist = castResult.pickResultInfo[0].dist;
			D3DXVECTOR3 p0 = *(D3DXVECTOR3*)&(castResult.pickResultInfo[0].vFacePos[0]);
			D3DXVECTOR3 p1 = *(D3DXVECTOR3*)&(castResult.pickResultInfo[0].vFacePos[1]);
			D3DXVECTOR3 p2 = *(D3DXVECTOR3*)&(castResult.pickResultInfo[0].vFacePos[2]);
			Vector vColliPoint = castResult.pickResultInfo[0].point;
			Vector vFacePos0 = castResult.pickResultInfo[0].vFacePos[0];
			Vector vFacePos1 = castResult.pickResultInfo[0].vFacePos[1];
			Vector vFacePos2 = castResult.pickResultInfo[0].vFacePos[2];

			// 没有碰到静态模型，碰到动态模型
			if( (!bPick && bPickDynamicCollisoin )
				// 静态和动态模型都碰到，且动态模型距离更近
				|| (bPick && bPickDynamicCollisoin && castDynamicResult.pickResultInfo[0].dist < castResult.pickResultInfo[0].dist) )
			{
				fDist = castDynamicResult.pickResultInfo[0].dist;

				p0 = *(D3DXVECTOR3*)&(castDynamicResult.pickResultInfo[0].vFacePos[0]);
				p1 = *(D3DXVECTOR3*)&(castDynamicResult.pickResultInfo[0].vFacePos[1]);
				p2 = *(D3DXVECTOR3*)&(castDynamicResult.pickResultInfo[0].vFacePos[2]);
				vColliPoint = castDynamicResult.pickResultInfo[0].point;
				vFacePos0 = castDynamicResult.pickResultInfo[0].vFacePos[0];
				vFacePos1 = castDynamicResult.pickResultInfo[0].vFacePos[1];
				vFacePos2 = castDynamicResult.pickResultInfo[0].vFacePos[2];
			}
#ifdef _DEBUG
			g_TempVt[0] = p0;
			g_TempVt[1] = p1;
			g_TempVt[2] = p2;

			g_TempLine[0] = vStart;
			g_TempLine[1] = vStart+vDir;
#endif

			if( vDir.z == 1.0f 
				|| vDir.z == 0.1f 
				|| !bNeedAdjust )
			{
				*fDistToCollision = fDist;	

				return TRUE;
			}

			D3DXVECTOR3 vNormal;
			D3DXVECTOR3 e0 = p1 - p0;
			D3DXVECTOR3 e1 = p2 - p0;
			D3DXVec3Cross( &vNormal, &e0, &e1 );
			D3DXVec3Normalize( &vNormal, &vNormal );

			if( vNormal.z > 0.9 )
				return FALSE;

			float fAngle = D3DXVec3Dot( &vDir, &vNormal );

			if( vCollisionDir && vCollisionNormal && fAngleToCollision )
			{
				// 2个垂直于法线的向量
				*vCollisionNormal = vNormal;
				D3DXVECTOR3 vNormal1 = D3DXVECTOR3( -vNormal.y, vNormal.x, 0 );
				D3DXVECTOR3 vNormal2 = D3DXVECTOR3( vNormal.y, -vNormal.x, 0 );

				D3DXVec3Normalize( &vNormal1, &vNormal1 );
				D3DXVec3Normalize( &vNormal2, &vNormal2 );

				float fAngleTemp = D3DXVec3Dot( &vDir, &vNormal1 );
				float fTheta1 = acosf( fAngleTemp );
				fAngleTemp = D3DXVec3Dot( &vDir, &vNormal2 );
				float fTheta2 = acosf( fAngleTemp );

				if( fTheta1 > fTheta2 )
				{
					*vCollisionDir = vNormal2;
					*fAngleToCollision = fTheta2;
				}
				else
				{
					*vCollisionDir = vNormal1;
					*fAngleToCollision = fTheta1;
				}
			}

			if( vNormal.z > 0.4 )
			{
				fDist = -fDist*fAngle - abs(vNormal.z)/fAngle*4;
			}
			else if( bNeedAdjustWithAngle )
			{
				float temp = abs(fDist*sqrt(1 - fAngle*fAngle));
				Vector vTemp0 = vColliPoint - vFacePos0;
				Vector vTemp1 = vColliPoint - vFacePos1;
				Vector vTemp2 = vColliPoint - vFacePos2;
				if ((vTemp0.length() > temp )
					|| (vTemp1.length() > temp )
					||(vTemp2.length() > temp )
					)
				{
					fDist = -fDist*fAngle;
				}
			}

			*fDistToCollision = fDist;


			return TRUE;
		}
	}
	return FALSE;
	unguard;
}

BOOL CPlayerRole::IsCollectPos()
{
	guardfunc;
	return m_bStartCollectPos;
	unguard;
}

RestoreColdDown* CPlayerRole::GetRestoreCoolDown()
{
	return &m_RestoreCoolDown;
}

void CPlayerRole::DuelProcess()
{
    guardfunc
    if(m_shDuelTarget == -1)
    {
        return;
    }
	if( !theHeroGame.GetPlayerMgr()->GetMe() )
		return;

    static unsigned int DuelTime = 0;

    // 判断是否换地图
    CWorldTile* pCurrTile = CURRENTTILE;
    if( pCurrTile && GetDuelMapID() != pCurrTile->GetMapId() )
    {
        if(m_nDuelTime > 0)
        {
            m_nDuelTime = 0;
             MsgDuelReady ready;
             GettheNetworkInput().SendMsg( &ready );
        }

        if(HQ_TimeGetTime() - DuelTime >= 1000)
        {
            DuelTime = HQ_TimeGetTime();
            MsgDuelStop stop;
			stop.shStopCharID = theHeroGame.GetPlayerMgr()->GetMe()->GetID();
            GettheNetworkInput().SendMsg( &stop );

            stop.shStopCharID = GetDuelTarget();
            GettheNetworkInput().SendMsg( &stop );
        }
        return;
    }

    static int nTime = 0;
    if(m_nDuelTime > 0)
    {
        if(HQ_TimeGetTime() - nTime >= 1000)
        {
            //显示倒计时
            m_nDuelTime --;
            theHeroGame.GetDuelTips()->AddTips(m_nDuelTime);
            nTime = HQ_TimeGetTime();
        }

        if(m_nDuelTime == 0)
        {
			theHeroGame.GetDuelTips()->AddTips(CDuelTips::Image_START_FIGHT);
             MsgDuelReady ready;
             GettheNetworkInput().SendMsg( &ready );
        }
        return;
    }

    if(HQ_TimeGetTime() - DuelTime >= 1000)
    {
        int nTimeOut = (HQ_TimeGetTime() - DuelTime)/1000;
        DuelTime = HQ_TimeGetTime();

        D3DXVECTOR3 vPos(0.0f, 0.0f, 0.0f);
        D3DXVECTOR3 vDir(0.0f, 0.0f, 0.0f);
        float fDist = 0.0f;
        if(GetDuelTarget() != -1)
        {
            vPos.x = theHeroGame.GetPlayerMgr()->GetMe()->GetPos().x;
            vPos.y = theHeroGame.GetPlayerMgr()->GetMe()->GetPos().y;
            vDir = GetDuelPos() - vPos;
            fDist = D3DXVec3Length( &vDir );
            if(fDist >= 40.0f)
            {
                if( m_nSelfOutTime > nTimeOut )
                {
                    m_nSelfOutTime -= nTimeOut;
                }
                else
                {
                    m_nSelfOutTime = 0;
                }
                if( m_nSelfOutTime > 0 )
                {
                    char szText[256] = {0};
                    _snprintf(szText, sizeof(szText)-1, theXmlString.GetString(eClient_AddInfo_2slk_129), m_nSelfOutTime);
                    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, szText );
                }
            }
            else
            {
                m_nSelfOutTime = 10;
            }

            CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(GetDuelTarget());
            if(pPlayer != NULL)
            {
                vPos.x = pPlayer->GetPos().x;
                vPos.y = pPlayer->GetPos().y;
                vDir = GetDuelPos() - vPos;
                fDist = D3DXVec3Length( &vDir );
                if(fDist >= 40.0f)
                {
                    m_nDuelOutTime--;
                }
                else
                {
                    m_nDuelOutTime = 10;
                }
            }
            else
            {
                m_nDuelOutTime--;
            }

            if(m_nSelfOutTime <= 0)
            {
                MsgDuelStop stop;
                stop.shStopCharID = theHeroGame.GetPlayerMgr()->GetMe()->GetID();
                GettheNetworkInput().SendMsg( &stop );
            }

            if(m_nDuelOutTime <= 0)
            {
                MsgDuelStop stop;
                stop.shStopCharID = GetDuelTarget();
                GettheNetworkInput().SendMsg( &stop );
            }
        }
    }
    unguard
}

//--------------------------------------------------------------------------------------------------------------------------------
//帮会GangMgr 
//--------------------------------------------------------------------------------------------------------------------------------
CGangMgr::CGangMgr()
{
	guardfunc;
	Clear();	
	unguard;
}

CGangMgr::~CGangMgr()
{
	Clear();
}

void CGangMgr::Clear()
{
    guardfunc
	ClearMember();

	memset(&m_GangInfo, 0, sizeof(GuildData));
    m_GangInfo.SetID(GuildDefine::InitID);
    m_GangInfo.SetMasterID(ErrorUnsignedLongID); 

	
    unguard
}

extern int g_nCharacterDBID;
void CGangMgr::InitGuildData(Msg* pMsg_)
{
    guardfunc
    
	if (pMsg_ == NULL)
    {
        return;
    }

	CHECK_MSGLEN(pMsg_, MsgTellGuildData);
    MsgTellGuildData* pMsg = (MsgTellGuildData*)pMsg_;
	ClearMember();
	m_GangInfo = pMsg->xData;
	m_vMember.clear();
	
	for (int i = 0; i < pMsg->ustCount; ++i)
	{
		AddMember(&(pMsg->xMember[i]));
	}

    GuildMember* pMe = FindByDBId(g_nCharacterDBID);
    if(pMe && theHeroGame.GetPlayerMgr()->GetMe())
    {
		theHeroGame.GetPlayerMgr()->GetMe()->SetGuildId(m_GangInfo.GetID());
		theHeroGame.GetPlayerMgr()->GetMe()->SetGuildName(m_GangInfo.GetName());
		theHeroGame.GetPlayerMgr()->GetMe()->SetGuildOffer(pMe->GetOffer());
		theHeroGame.GetPlayerMgr()->GetMe()->SetGangPosition(pMe->GetPosition());
    }
	//s_CUI_ID_FRAME_Gang.SetNeedRefresh(true);
	s_CUI_ID_FRAME_GuildBaseInfo.OnUpdateUiInfo();


	if(GetData().GetReleaseQuest())
	{
		MsgGuildQuestReleaseStatus xStatus;
		xStatus.nQuestType     = GetData().GetReleaseQuest();
		xStatus.n64RelasetTime = GetData().GetReleaseTime();
		theHeroGame.GetPlayerMgr()->OnMsgGuildDutyStatus(&xStatus);
	}

	unguard
}

GuildMember* CGangMgr::FindByDBId( int nDBId )
{
    guardfunc
	for( int i = 0; i < m_vMember.size(); i++ )
	{
		if( m_vMember[i]->GetID() == nDBId )
			return m_vMember[i];
	}
	return NULL;
    unguard
}

GuildMember* CGangMgr::FindByName( const char* pszName )
{
    guardfunc
	for( int i = 0; i < m_vMember.size(); i++ )
	{
		if( stricmp( m_vMember[i]->GetName(), pszName ) == 0 ) 
			return m_vMember[i];
	}
	return NULL;
    unguard
}

bool CGangMgr::AddMember( GuildMember* pSrcMember )
{
	guardfunc
	if( FindByDBId( pSrcMember->GetID() ) )
		return  false;

	GuildMember* member = MeDefaultNew GuildMember;
	memcpy(member,pSrcMember, sizeof(GuildMember));
	m_vMember.push_back(member);
	return true;
	unguard
}

//BOOL CGangMgr::DelMember( GuildMember* pMember )
//{
//    guardfunc
//	for( int i = 0; i < m_vMember.size(); i++ )
//	{
//		if( m_vMember[i]->GetID() == pMember->GetID() )
//		{
//			delete m_vMember[i];
//			m_vMember.erase( m_vMember.begin()+i );
//			return TRUE;
//        }
//	}
//	return FALSE;
//    unguard
//}

BOOL CGangMgr::DelMember( int nID )
{
	guardfunc
		for( int i = 0; i < m_vMember.size(); i++ )
		{
			if( m_vMember[i]->GetID() == nID )
			{
				delete m_vMember[i];
				m_vMember.erase( m_vMember.begin()+i );
				return TRUE;
			}
		}
		return FALSE;
		unguard
}

int CGangMgr::GetMemberOnlineCount()
{
    guardfunc
    int nCount = 0;
    for( int i = 0; i < m_vMember.size(); i++ )
    {
        if( m_vMember[i]->GetOnLine() )
        {
            nCount++;
        }
    }
    return nCount;
    unguard
}

void CGangMgr::SetGuildName( const char* pszGuildName )
{
    guardfunc
	m_GangInfo.SetName(pszGuildName);
    CChatCheck::getInstance()->CheckStringInLowMark(const_cast<char*>(m_GangInfo.GetName()), '*');
    unguard
}

void CGangMgr::ResetMemberActive()
{
	std::vector<GuildMember*>::iterator iter = m_vMember.begin();
	for (; iter != m_vMember.end(); ++iter)
	{
		(*iter)->SetActivity((*iter)->GetLastActivity());
	}
	//s_CUI_ID_FRAME_Gang.SetNeedRefresh(true);
	s_CUI_ID_FRAME_GuildBaseInfo.OnUpdateUiInfo();
}

//void CGangMgr::SetGuildIntro( const char* pszGuildIntro )
//{
//    guardfunc
//	strcpy( m_GangInfo.m_szIntro, pszGuildIntro );
//    unguard
//}

//void CGangMgr::SetGuildFlag( SGuildFlag& stFlag )
//{
//    guardfunc
//    memcpy(&m_GangInfo.m_stFlag, &stFlag, sizeof(SGuildFlag)); 
//
//    if(m_GangInfo.m_stFlag.ulCRC != 0)
//    {
//        std::string TgaName;
//        char szBuff[128] = {0};
//        TgaName = CTgaManager::GetTgaManager()->FindTgaPath();
//        TgaName = TgaName + itoa(m_GangInfo.m_stFlag.ulCRC, szBuff, 10) + ".tga";
//
//		if( theHeroGame.GetPlayerMgr()->GetMe() )
//			theHeroGame.GetPlayerMgr()->GetMe()->RegisterGuildIcon(m_GangInfo.m_stFlag.ulCRC, m_GangInfo.m_stFlag.bFlagData, sizeof(m_GangInfo.m_stFlag.bFlagData));
//    }
//    unguard
//}
//bool SortByArea(GuildMember* s1, GuildMember* s2)
//{
//    guardfunc
//	return s1->stMapID > s2->stMapID;
//    unguard
//}
//
//bool SortByArea_Order(GuildMember* s1, GuildMember* s2)
//{
//    guardfunc
//	return s1->stMapID < s2->stMapID;
//    unguard
//}

//void CGangMgr::SortMemberList(SortType type,bool bOrder)
//{
//    guardfunc
//    if(bOrder)
//    {
//        switch(type)
//        {
//        case TYPE_NAME:
//            std::sort(m_vMember.begin(), m_vMember.end(), SortByName_Order);
//            break;
//        case TYPE_LVL:
//            std::sort(m_vMember.begin(), m_vMember.end(), SortByLvl_Order);
//            break;
//		case TYPE_METIER:
//			std::sort(m_vMember.begin(), m_vMember.end(), SortByMetier_Order);
//			break;
//		case TYPE_TONG:
//			std::sort(m_vMember.begin(), m_vMember.end(), SortByTong_Order);
//			break;
//        case TYPE_JOB:
//            std::sort(m_vMember.begin(), m_vMember.end(), SortByJob_Order);
//            break;
//        case TYPE_HONOUR:
//            std::sort(m_vMember.begin(), m_vMember.end(), SortByHonour_Order);
//            break;
//        }
//    }
//    else
//    {
//        switch(type)
//        {
//        case TYPE_NAME:
//            std::sort(m_vMember.begin(), m_vMember.end(), SortByName);
//            break;
//        case TYPE_LVL:
//            std::sort(m_vMember.begin(), m_vMember.end(), SortByLvl);
//            break;
//		case TYPE_METIER:
//			std::sort(m_vMember.begin(), m_vMember.end(), SortByMetier);
//			break;
//		case TYPE_TONG:
//			std::sort(m_vMember.begin(), m_vMember.end(), SortByTong);
//			break;
//        case TYPE_JOB:
//            std::sort(m_vMember.begin(), m_vMember.end(), SortByJob);
//            break;
//        case TYPE_HONOUR:
//            std::sort(m_vMember.begin(), m_vMember.end(), SortByHonour);
//            break;
//        }
//    }
//    unguard
//}

//void CGangMgr::GetGuildCreateTime(std::string& strDate)
//{
//
//}

//bool CGangMgr::IsSameGang( const string& strName )
//{
//	guardfunc;
//	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByName( strName.c_str() );
//	if( !pPlayer )
//		return false;
//
//	unsigned long nGuildId = pPlayer->GetGuildId();
//	if ( nGuildId == GuildDefine::InitID)
//		return false;
//
//	return m_GangInfo.GetID() == nGuildId;
//
//	unguard;
//}

const char* CGangMgr::GetGuildMasterName()
{
	for( int i = 0; i < m_vMember.size(); i++ )
	{
		if( m_vMember[i]->GetPosition() == GuildDefine::Position_Master )
			return m_vMember[i]->GetName();
	}
	return NULL;
}

//const char* CGangMgr::GetGuildViceMasterName()
//{
//	for( int i = 0; i < m_vMember.size(); i++ )
//	{
//		if( m_vMember[i]->GetPosition() == GuildDefine::Position_ViceMaster )
//			return m_vMember[i]->GetName();
//	}
//	return NULL;
//
//}

//void CGangMgr::updateGuildRelation( int guildId, char relation ,bool bSilence)
//{
//	SGangRelationInfoDB* pInfoDBList = m_GangInfo.m_guildRelation;
//	int nIndex = 0;
//	bool bFound = false;
//	for (;nIndex < dr_MaxGuildRelationCount;++nIndex)
//	{
//		if (pInfoDBList[nIndex].corpsId == 0)
//		{
//			break;
//		}
//		if (pInfoDBList[nIndex].corpsId ==  guildId)
//		{
//			bFound = true;
//			break;
//		}
//	}
//	if (bFound)
//	{
//		if (!bSilence)
//		{
//			CGuildInfo* pGuild = thePlayerRole.getGuild(pInfoDBList[nIndex].corpsId);
//			if (pGuild)
//			{
//				char szContent[256] = {0};
//				if (pInfoDBList[nIndex].relation == GR_LEAGUE)
//				{
//					MeSprintf_s( szContent,sizeof(szContent)/sizeof(char) - 1, theXmlString.GetString(eGuildLoseLeague), pGuild->baseInfo.szName);
//				}
//				else
//				{
//					MeSprintf_s( szContent,sizeof(szContent)/sizeof(char) - 1 ,theXmlString.GetString(eGuildPeaseInfo), pGuild->baseInfo.szName);
//				}
//				GetShowScreenText() ->AddInfo( szContent, 0xff00ff00 );
//			}
//		}
//
//		for (int i = nIndex; i < dr_MaxGuildRelationCount - 1;++i)
//		{
//			if (pInfoDBList[i].corpsId == 0)
//			{
//				break;
//			}
//			pInfoDBList[i] = pInfoDBList[i + 1];
//		}
//		pInfoDBList[dr_MaxGuildRelationCount - 1].corpsId = 0;
//	}
//	else
//	{
//		assert(relation != GR_NEUTRALISM);
//		pInfoDBList[nIndex].corpsId = guildId;
//		pInfoDBList[nIndex].relation = relation;
//	}
//	s_CUI_Guild.Refeash();
//}

//char CGangMgr::guildRelation( CPlayer* pPlayer )
//{
//	if (!pPlayer->HasGuild())
//	{
//		return GR_NEUTRALISM;
//	}
//	int guildId = pPlayer->GetGuildId();
//	return guildRelation(guildId);
//
//}

//char CGangMgr::guildRelation( int guildId )
//{
//	SGangRelationInfoDB* pInfoDBList = m_GangInfo.m_guildRelation;
//	int nIndex = 0;
//	for (;nIndex < dr_MaxGuildRelationCount;++nIndex)
//	{
//		if (pInfoDBList[nIndex].corpsId == 0)
//		{
//			break;
//		}
//		if (pInfoDBList[nIndex].corpsId ==  guildId)
//		{
//			return pInfoDBList[nIndex].relation;
//		}
//	}
//	return GR_NEUTRALISM;
//}

//CFamilyInfo* CGangMgr::GetTong( int tongId )
//{
//	// modifed, jiayi, [2010/1/26], 小兵要改
//	if (tongId >= ProcessGuildInfo::GetGuildMaxTongCount( m_GangInfo.GetLevel() ) )
//	{
//		return NULL;
//	}
//	return &m_vTongList[tongId];
//}

void CGangMgr::ClearMember()
{
	for (int i = 0; i < m_vMember.size(); ++i)
	{
		delete m_vMember[i];
	}
	m_vMember.clear();
}

//void CGangMgr::ChangeMemberTong( GuildMember* pMember,char newTong )
//{
//	EraseFromTongMember(pMember);
//
//	pMember->SetFamilyID(newTong);
//
//	if (pMember->GetFamilyID()  != INVALID_TONG_ID)
//	{
//		m_vTongList[newTong].m_vMember.push_back(pMember);
//	}
//
//}

//void CGangMgr::EraseFromTongMember( GuildMember *pMember )
//{
//	if (pMember->GetFamilyID() != INVALID_TONG_ID)
//	{
//		std::vector<GuildMember*>& vMember = m_vTongList[pMember->GetFamilyID()].m_vMember;
//		for (int j = 0; j < vMember.size(); j++)
//		{
//			if( vMember[j]->GetID() == pMember->GetID() )
//			{
//				vMember.erase( vMember.begin()+j );
//				break;
//			}
//		}
//	}
//}


//--------------------------------------------------------------------------------------------------------------------------------
//帮会GangMgr 
//--------------------------------------------------------------------------------------------------------------------------------


void CPlayerRole::SkillExpChang(unsigned short ustSkillID,DWORD dwSkillExp)
{
	guardfunc;
	for (int n = 0; n < More_iMaxSkillKnown;n++)
	{
		if (m_charinfo.otherdataclient.skills.skill[n].ustSkillID == ustSkillID)
		{
			SCharSkill* pSkill = NULL;
			pSkill = m_SkillBag.GetSkillByID( ustSkillID );
			if (dwSkillExp > 0)
			{
				int nTempSkillExp = pSkill->dwCurSkillExp;
				pSkill->dwCurSkillExp = dwSkillExp;
			}
			else
			{
				pSkill->dwCurSkillExp = dwSkillExp;
			}
		}
	}
	unguard;
}

void CPlayerRole::HPChanged()
{
    // 当玩家HP小于一定值。
    if ( m_pBaseInfo->liveinfo.nHp < m_pBaseInfo->baseProperty.fightAttr.hpMax.final * 0.3f )
    {
        for ( int i = More_rightShortcutBegin; i < More_iHotkey; ++i )
        {
            ItemDefine::SItemCommon *pItemCommon =GettheItemDetail().GetItemByID(
                m_pHotKeyBag[i].ItemData.itembaseinfo.ustItemID );
            if ( pItemCommon && pItemCommon->ucItemType == ItemDefine::ITEMTYPE_RESTORE )
            {
                ItemDefine::SItemRestore* pItemRestore = (ItemDefine::SItemRestore*)pItemCommon;
                if ( pItemRestore->bHPAuto )
                {
                    MsgUseGoods msg;
                    msg.ustItemIndex = m_pHotKeyBag[i].ShortCut.BagIndex;
					msg.nGuid = m_pHotKeyBag[i].ItemData.itembaseinfo.nOnlyInt;
					if( theHeroGame.GetPlayerMgr()->GetMe() )
	                    msg.stDstChar = theHeroGame.GetPlayerMgr()->GetMe()->GetID();
                    GettheNetworkInput().SendMsg( &msg );
                }
            }
        }
    }
}

void CPlayerRole::MPChanged()
{
    // 当玩家MP小于一定值。
    if ( m_pBaseInfo->liveinfo.nMp < m_pBaseInfo->baseProperty.fightAttr.mpMax.final * 0.3f )
    {
        for ( int i = More_rightShortcutBegin; i < More_iHotkey; ++i )
        {
            ItemDefine::SItemCommon *pItemCommon =GettheItemDetail().GetItemByID(
                m_pHotKeyBag[i].ItemData.itembaseinfo.ustItemID );
            if ( pItemCommon && pItemCommon->ucItemType == ItemDefine::ITEMTYPE_RESTORE )
            {
                ItemDefine::SItemRestore* pItemRestore = (ItemDefine::SItemRestore*)pItemCommon;
                if ( pItemRestore->bMPAuto )
                {
                    MsgUseGoods msg;
                    msg.ustItemIndex = m_pHotKeyBag[i].ShortCut.BagIndex;
					msg.nGuid = m_pHotKeyBag[i].ItemData.itembaseinfo.nOnlyInt;
					if( theHeroGame.GetPlayerMgr()->GetMe() )
						msg.stDstChar = theHeroGame.GetPlayerMgr()->GetMe()->GetID();
                    GettheNetworkInput().SendMsg( &msg );
                }
            }
        }
    }
}

void CPlayerRole::refreshHotKey()
{
    s_CUI_ID_FRAME_MAIN.RefeashHotKey();
    s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
    // 更新快捷键给服务器
	SendHotKeyToServer();
}

bool CPlayerRole::IsInTransport( float posx, float posy, int& nMapId, int& nTargetId, int& nEntranceId )
{
	CResMgr* pResMgr = SwGlobal::GetWorld()->GetWorldBuffer()->GetResMgr();
	if( pResMgr && pResMgr->GetTransportCount() )
	{
		for(UINT i=0; i<pResMgr->GetTransportCount(); i++)
		{
			if( pResMgr->Transport(i)->IsTransport() )	// 也有可能是出生点，所以需要判断
			{
				CTransportRes* pTransportRes = (CTransportRes*)pResMgr->Transport(i);
				if( posx >= pTransportRes->GetLeft() && posx <= pTransportRes->GetRight() 
					&& posy <= pTransportRes->GetTop() && posy >= pTransportRes->GetBottom() )
				{
					nMapId = pTransportRes->GetDesMapID();
					nTargetId = pTransportRes->GetNtargetID();
					nEntranceId = pTransportRes->GetEntranceId();
					return true;
				}
			}
		}
	}
	return false;
}

BOOL CPlayerRole::IsTeamMember( const char* playername )
{
	if( !playername || playername[0] == '\0' )
		return FALSE;

	for( int n=0; n<m_TeamData.size(); n++ )
	{
		TeamInfo* pInfo = &m_TeamData[n];
		if (strcmp(pInfo->szName.c_str(), playername) == 0)
		{
			return TRUE;
		}
	}
	return FALSE;
}

DWORD CPlayerRole::GetTeamMemberId( const char* playername )
{
	for( int n=0; n<m_TeamData.size(); n++ )
	{
		TeamInfo* pInfo = &m_TeamData[n];
		if (strcmp(pInfo->szName.c_str(), playername) == 0)
		{
			return pInfo->nID;
		}
	}
	return -1;
}

TeamInfo* CPlayerRole::GetTeamInfo( DWORD dwId )
{
	for( int n=0; n<m_TeamData.size(); n++ )
	{
		TeamInfo* pInfo = &m_TeamData[n];
		if (pInfo->nID == dwId)
		{
			return pInfo;
		}
	}
	return NULL;

}

BOOL CPlayerRole::IsRole( DWORD dwId )
{
    if( dwId == m_dwPlayerDBID )
        return TRUE;
	if( !theHeroGame.GetPlayerMgr()->GetMe() )
		return FALSE;
    // 还需要判断team数据吗？
	TeamInfo* pInfo = GetTeamInfo(dwId);
	if (pInfo)
	{
		return (0 == strcmp(theHeroGame.GetPlayerMgr()->GetMe()->GetName(),pInfo->szName.c_str()));
	}
	return FALSE;
}

TeamInfo* CPlayerRole::GetMeTeamInfo(  )
{
	if( !theHeroGame.GetPlayerMgr()->GetMe() )
		return NULL;
	for( int n=0; n<m_TeamData.size(); n++ )
	{
		TeamInfo* pInfo = &m_TeamData[n];
		if (pInfo && (0 == strcmp(theHeroGame.GetPlayerMgr()->GetMe()->GetName(),pInfo->szName.c_str())))
		{
			return pInfo;
		}
	}
	return NULL;

}
extern int g_nRoleCommonAttackStatus;
void CPlayerRole::CheckFight()
{
	static bool isCanncel = false;
	static DWORD dwLastTime = HQ_TimeGetTime();
	if (theHeroGame.GetPlayerMgr()->GetLockPlayerID() != -1)
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
		CPlayer* pTargetPlayer = theApp->GetPlayerMgr()->FindByID( theHeroGame.GetPlayerMgr()->GetLockPlayerID() );
		if (pTargetPlayer && pMe &&
			(g_nRoleCommonAttackStatus == CAS_NEED_AUTO_ATTACK || g_nRoleCommonAttackStatus == CAS_ATTACK_AGAIN_WHEN_FAILED) )
		{
			//在攻击范围，而且如果当职业是弓并且没有移动的时候
			if (pMe->IsInAttackRange(pTargetPlayer->GetPos().x, pTargetPlayer->GetPos().y,
				pTargetPlayer->GetBodyLengthSize(), 0) && ( GetProfession() != EArmType_Hunter || !pMe->IsMoving() ) )
			{
				if (!pMe->IsMoving())
				{
					CPlayer* pPlayerMe = theHeroGame.GetPlayerMgr()->GetMe();
					if (pPlayerMe&&pPlayerMe->IsMounting() && pPlayerMe->GetAutoDismount() && !pPlayerMe->IsGoudaOperaMode())
					{
						//pPlayerMe->DisMount();
						//theHeroGame.GetPlayerMgr()->DisDrome();
					}
				}
				if (isCanncel)
				{
					if( GetProfession() == EArmType_Hunter )
					{
						MsgLockTarget msgLock;
						msgLock.stWho = theHeroGame.GetPlayerMgr()->GetLockPlayerID();
						GettheNetworkInput().SendMsg( &msgLock );
					}
				
					//lyh++ 打国旗
					if(pTargetPlayer->GetRealCountry() != CountryDefine::Country_Init&&
						thePlayerRole.m_charinfo.baseinfo.aptotic.ucCountry != CountryDefine::Country_Init&&
						thePlayerRole.m_charinfo.baseinfo.aptotic.ucCountry ==pTargetPlayer->GetRealCountry())
					{
					}else
					{
					MsgAttackLockTarget	msgAttack;
					GettheNetworkInput().SendMsg( &msgAttack );
				    }

					isCanncel = false;
				}
			}
			else
			{
				DWORD dwCurrTime = HQ_TimeGetTime();
				if (!isCanncel)
				{
					dwLastTime = dwCurrTime;

					if( GetProfession() == EArmType_Hunter )
					{
						MsgLockTarget msgLock;
						msgLock.stWho = -1;
						GettheNetworkInput().SendMsg( &msgLock );
					}
					else
					{		

						MsgAttackLockTarget	msgAttack;
						msgAttack.cAttack = MsgAttackLockTarget::AT_NotAttack;
						GettheNetworkInput().SendMsg( &msgAttack );
					}

					isCanncel = true;
				}
			}
		}
	}
	else
	{
		isCanncel = false;
	}
}

size_t CPlayerRole::AddMount(const SMountItem& mountItem)
{
	for (int i = 0; i < m_charinfo.baseinfo.liveinfo.ucMountCount; ++i)
	{
		if (m_charinfo.ItemBagData.miItems[i].baseInfo.id == InvalidLogicNumber)
		{
			m_charinfo.ItemBagData.miItems[i] = mountItem;
			return i;
		}
	}
	return InvalidLogicNumber;
}

void CPlayerRole::RemoveMountByIndex(int nIndex)
{
	GetMountByIndex(nIndex).baseInfo.id = InvalidLogicNumber;
	GetMountByIndex(nIndex).baseInfo.guid = 0;

	for (int i = 0; i < m_charinfo.baseinfo.liveinfo.ucMountCount - 1; ++i)
	{
		if (m_charinfo.ItemBagData.miItems[i].baseInfo.id == InvalidLogicNumber &&
			m_charinfo.ItemBagData.miItems[i + 1].baseInfo.id != InvalidLogicNumber)
		{
			std::swap(m_charinfo.ItemBagData.miItems[i], m_charinfo.ItemBagData.miItems[i + 1]);
		}
	}
}

void CPlayerRole::RemoveMountByGUID( __int64 nGUID )
{
	if( !GetMountByGUID(nGUID) )
		return;
	
	GetMountByGUID(nGUID)->baseInfo.id = InvalidLogicNumber;
	GetMountByGUID(nGUID)->baseInfo.guid = 0;
	

	for (int i = 0; i < m_charinfo.baseinfo.liveinfo.ucMountCount - 1; ++i)
	{
		if (m_charinfo.ItemBagData.miItems[i].baseInfo.id == InvalidLogicNumber &&
			m_charinfo.ItemBagData.miItems[i + 1].baseInfo.id != InvalidLogicNumber)
		{
			std::swap(m_charinfo.ItemBagData.miItems[i], m_charinfo.ItemBagData.miItems[i + 1]);
		}
	}
}

SMountItem& CPlayerRole::GetMount(int nId)
{
	for (int i = 0; i < m_charinfo.baseinfo.liveinfo.ucMountCount; ++i)
	{
		if (m_charinfo.ItemBagData.miItems[i].baseInfo.id == nId)
			return m_charinfo.ItemBagData.miItems[i];
	}
    static SMountItem mount;
    mount.baseInfo.id = InvalidLogicNumber;
    return mount;
}
SMountItem* CPlayerRole::GetMountByGUID( __int64 nGUID )
{
	for( int i = 0 ; i < m_charinfo.baseinfo.liveinfo.ucMountCount ; ++ i )
	{
		if( m_charinfo.ItemBagData.miItems[i].baseInfo.guid == nGUID )
			return &m_charinfo.ItemBagData.miItems[i];
	}
	return 0;
}

SMountItem& CPlayerRole::GetMountByIndex(size_t nIndex)
{
	if (nIndex >= ITEM_MOUNT_MAXCOUNT)
	{
		static SMountItem mount;
		mount.baseInfo.id = InvalidLogicNumber;
		return mount;
	}
	return m_charinfo.ItemBagData.miItems[nIndex];
}

size_t CPlayerRole::GetMountCount()
{
	size_t count = 0;
	for (int i = 0; i < m_charinfo.baseinfo.liveinfo.ucMountCount; ++i)
	{
		if (m_charinfo.ItemBagData.miItems[i].baseInfo.id != InvalidLogicNumber)
			++count;
	}
	return count;
}

bool CPlayerRole::HasMountSpace() const
{
	for (int i = 0; i < m_charinfo.baseinfo.liveinfo.ucMountCount; ++i)
	{
		if (m_charinfo.ItemBagData.miItems[i].baseInfo.id == InvalidLogicNumber)
			return true;
	}
	return false;
}

void CPlayerRole::AddMountSkill(const SMountItem& mountItem)
{
	for ( int i=0; i<SMountItem::MICD_MaxSkillCount; ++i)
	{
		if ( mountItem.skillInfo.skills[i].ustSkillID == 0 || mountItem.skillInfo.skills[i].ustSkillID == InvalidLogicNumber )
			continue;
		m_MountSkillBag.AddSkill(mountItem.skillInfo.skills[i].ustSkillID,
			mountItem.skillInfo.skills[i].stSkillLevel);
	}
}

void CPlayerRole::RemoveMountSkill(const SMountItem &mountItem)
{
	for ( int i=0; i<SMountItem::MICD_MaxSkillCount; ++i)
	{
		if ( mountItem.skillInfo.skills[i].ustSkillID == 0 || mountItem.skillInfo.skills[i].ustSkillID == InvalidLogicNumber )
			continue;
		m_MountSkillBag.RemoveSkill(mountItem.skillInfo.skills[i].ustSkillID);
	}
}

SMountItem* CPlayerRole::GetActivedMount()//获得当前激活坐骑的信息
{
	for (int i = 0; i < m_charinfo.baseinfo.liveinfo.ucMountCount; ++i)
	{
		if (m_charinfo.ItemBagData.miItems[i].baseInfo.isActive)
			return &m_charinfo.ItemBagData.miItems[i];
	}
	return 0;
}

int CPlayerRole::GetActivedMountIndex()//获得当前激活的ID nIndex
{
	for (int i = 0; i < m_charinfo.baseinfo.liveinfo.ucMountCount; ++i)
	{
		if (m_charinfo.ItemBagData.miItems[i].baseInfo.isActive)
			return i;
	}
	return -1;
}
__int64 CPlayerRole::GetActivedMountGUID()
{
	for (int i = 0; i < m_charinfo.baseinfo.liveinfo.ucMountCount; ++i)
	{
		if (m_charinfo.ItemBagData.miItems[i].baseInfo.isActive)
			return m_charinfo.ItemBagData.miItems[i].baseInfo.guid;
	}
	return 0;
}
void CPlayerRole::ActiveMountByGUID( __int64 nGUID )
{
	for (int i = 0; i < m_charinfo.baseinfo.liveinfo.ucMountCount; ++i)
		m_charinfo.ItemBagData.miItems[i].baseInfo.isActive = false;
	if( GetMountByGUID( nGUID ) )
		GetMountByGUID( nGUID )->baseInfo.isActive = true;
	
}
void CPlayerRole::UnactiveMountByGUID( __int64 nGUID )
{
	if( GetMountByGUID( nGUID ) )
		GetMountByGUID( nGUID )->baseInfo.isActive = false;
}
void CPlayerRole::ActiveMount(size_t nIndex)
{
	for (int i = 0; i < m_charinfo.baseinfo.liveinfo.ucMountCount; ++i)
		m_charinfo.ItemBagData.miItems[i].baseInfo.isActive = false;
	
	GetMountByIndex(nIndex).baseInfo.isActive = true;
}

void CPlayerRole::UnactiveMount(size_t nIndex)
{
	GetMountByIndex(nIndex).baseInfo.isActive = false;
}

size_t  CPlayerRole::AddPet(const SPetItem& petItem)
{
	for (int i = 0;i < ITEM_PET_MAXCOUNT;++i)
	{
		if(m_charinfo.ItemBagData.petItems[i].baseInfo.petId == InvalidLogicNumber)
		{
			m_charinfo.ItemBagData.petItems[i] = petItem;
			return i;
		}
	}
	return InvalidLogicNumber;
}

int CPlayerRole::GetPetIndex(__int64 nGUID)
{
	for (int i = 0;i < ITEM_PET_MAXCOUNT;++i)
	{
		if(m_charinfo.ItemBagData.petItems[i].baseInfo.petId != InvalidLogicNumber &&
			m_charinfo.ItemBagData.petItems[i].GetPetGuid() == nGUID)
		{
			return i;
		}
	}

	return -1;
}

void CPlayerRole::RemovePetByIndex(int nIndex)
{
	GetPetByIndex(nIndex).baseInfo.petId = InvalidLogicNumber;
	GetPetByIndex(nIndex).baseInfo.guid  = 0;
	for (int i = 0;i < ITEM_PET_MAXCOUNT;++i)
	{
		if (m_charinfo.ItemBagData.petItems[i].baseInfo.petId == InvalidLogicNumber &&
			m_charinfo.ItemBagData.petItems[i + 1].baseInfo.petId != InvalidLogicNumber)
		{
			std::swap(m_charinfo.ItemBagData.petItems[i], m_charinfo.ItemBagData.petItems[i + 1]);
		}
	}
}

void CPlayerRole::RemovePetByGUID( __int64 nGUID )
{
	if(!GetPetByGUID(nGUID))
		return;

	GetPetByGUID(nGUID)->baseInfo.petId = InvalidLogicNumber;
	GetPetByGUID(nGUID)->baseInfo.guid  = 0;

	for (int i = 0; i < ITEM_PET_MAXCOUNT; ++i)
	{
		if (m_charinfo.ItemBagData.petItems[i].baseInfo.petId == InvalidLogicNumber &&
			m_charinfo.ItemBagData.petItems[i + 1].baseInfo.petId != InvalidLogicNumber)
		{
			std::swap(m_charinfo.ItemBagData.petItems[i], m_charinfo.ItemBagData.petItems[i + 1]);
		}
	}
}

SPetItem& CPlayerRole::GetPet(int nId)
{
	for (int i = 0; i < ITEM_PET_MAXCOUNT; ++i)
	{
		if (m_charinfo.ItemBagData.petItems[i].baseInfo.petId == nId)
			return m_charinfo.ItemBagData.petItems[i];
	}
	static SPetItem pet;
	pet.baseInfo.petId = InvalidLogicNumber;
	return pet;
}

SPetItem& CPlayerRole::GetPetByIndex(size_t nIndex)
{
	if (nIndex >= ITEM_PET_MAXCOUNT)
	{
		static SPetItem pet;
		pet.baseInfo.guid = InvalidLogicNumber;
		return pet;
	}
	return m_charinfo.ItemBagData.petItems[nIndex];
}

SPetItem* CPlayerRole::GetPetByGUID( __int64 nGUID )
{
	for( int i = 0 ; i < ITEM_PET_MAXCOUNT ; ++ i )
	{
		if( m_charinfo.ItemBagData.petItems[i].baseInfo.guid == nGUID )
			return &m_charinfo.ItemBagData.petItems[i];
	}
	return 0;
}

size_t CPlayerRole::GetPetCount()
{
	size_t count = 0;
	for (int i = 0; i < ITEM_PET_MAXCOUNT; ++i)
	{
		if (m_charinfo.ItemBagData.petItems[i].baseInfo.petId != InvalidLogicNumber)
			++count;
	}
	return count;
}

bool CPlayerRole::HasPetSpace() const
{
	for (int i = 0; i < ITEM_PET_MAXCOUNT; ++i)
	{
		if (m_charinfo.ItemBagData.petItems[i].baseInfo.petId == InvalidLogicNumber)
			return true;
	}
	return false;
}


void CPlayerRole::AddPetSkill(const SPetItem& petItem)
{
	for ( int i=0; i< ITEM_PET_MAXCOUNT; ++i)
	{
		if ( petItem.skillInfo.skills[i].ustSkillID == 0 || petItem.skillInfo.skills[i].ustSkillID == InvalidLogicNumber )
			continue;

		m_PetSkillBag.AddSkill(petItem.skillInfo.skills[i].ustSkillID,
			petItem.skillInfo.skills[i].stSkillLevel);
	}
}

void CPlayerRole::RemovePetSkill(const SPetItem& petItem)
{
	for ( int i=0; i < SPetItem::PetDefine_MaxSkillCount; ++i)
	{
		if ( petItem.skillInfo.skills[i].ustSkillID == 0 || petItem.skillInfo.skills[i].ustSkillID == InvalidLogicNumber )
			continue;

		m_PetSkillBag.RemoveSkill(petItem.skillInfo.skills[i].ustSkillID);
	}
}

SPetItem* CPlayerRole::GetActivedPet()
{
	for (int i = 0; i < ITEM_PET_MAXCOUNT; ++i)
	{
		if (m_charinfo.ItemBagData.petItems[i].baseInfo.isActive)
			return &m_charinfo.ItemBagData.petItems[i];
	}
	return 0;
}

int CPlayerRole::GetActivedPetIndex()
{
	for (int i = 0; i < ITEM_PET_MAXCOUNT; ++i)
	{
		if (m_charinfo.ItemBagData.petItems[i].baseInfo.isActive)
			return i;
	}
	return -1;
}

__int64 CPlayerRole::GetActivedPetGUID()
{
	for (int i = 0; i < ITEM_PET_MAXCOUNT; ++i)
	{
		if (m_charinfo.ItemBagData.petItems[i].baseInfo.isActive)
			return m_charinfo.ItemBagData.petItems[i].baseInfo.guid;
	}
	return 0;
}

void CPlayerRole::ActivePet(size_t nIndex)
{
	for (int i = 0; i < ITEM_PET_MAXCOUNT; ++i)
		m_charinfo.ItemBagData.petItems[i].baseInfo.isActive = false;

	GetPetByIndex( nIndex ).baseInfo.isActive = true;
}

void CPlayerRole::UnactivePet(size_t nIndex)
{
	GetPetByIndex( nIndex ).baseInfo.isActive = false;
}

void CPlayerRole::ActivePetByGUID( __int64 nGUID )
{
	for (int i = 0; i < ITEM_PET_MAXCOUNT; ++i)
		m_charinfo.ItemBagData.petItems[i].baseInfo.isActive = false;

	if( GetPetByGUID( nGUID ) )
		GetPetByGUID( nGUID )->baseInfo.isActive = true;
}

void CPlayerRole::UnactivePetByGUID( __int64 nGUID )
{
	if( GetPetByGUID( nGUID ) )
		GetPetByGUID( nGUID )->baseInfo.isActive = false;
}

bool CPlayerRole::GetBagItemByGUID( __int64 nGUID, SCharItem* pItem )
{
	if( m_bag.GetItemByOnlyeID( nGUID, pItem ) )
		return true;
	if( m_bagMaterial.GetItemByOnlyeID( nGUID, pItem ) )
		return true;
	if( m_bagTask.GetItemByOnlyeID( nGUID, pItem ) )
		return true;

	return false; // not found
}

bool CPlayerRole::GetStorageItemByGUID( __int64 nGUID, SCharItem* pItem )
{
    if( nGUID == InvalidLogicNumber )
        return false;

    for( int i = 0; i < STORAGE_ITEMGRID_MAX; ++i )
    {
        if( m_stStorage.stStorageItems[i].itembaseinfo.ustItemID == InvalidLogicNumber )
            continue;

        if( m_stStorage.stStorageItems[i].itembaseinfo.nOnlyInt == nGUID )
        {
            *pItem = m_stStorage.stStorageItems[i];
            return true;
        }
    }
    return false;
}

bool CPlayerRole::GetStorageMountByGUID( __int64 nGUID, SMountItem* pItem )
{
    if( nGUID == InvalidLogicNumber )
        return false;

    for( int i = 0; i < STORAGE_MOUNTGRID_MAX; ++i )
    {
        if( m_stStorage.xStorageMounts[i].baseInfo.id == InvalidLogicNumber )
            continue;

        if( m_stStorage.xStorageMounts[i].baseInfo.guid == nGUID )
        {
            *pItem = m_stStorage.xStorageMounts[i];
            return true;
        }
    }
    return false;
}

bool CPlayerRole::GetBagTypeByItemGUID( __int64 nGUID, EBagType& eType, int* pIndex /*= 0*/ )
{
	SCharItem stItem;	
	if( m_bag.GetItemByOnlyeID( nGUID, &stItem ) )
	{
		eType = BT_NormalItemBag;
		if( pIndex )
			*pIndex = m_bag.GetItemIndexByGUID( nGUID );
		return true;
	}
	if( m_bagMaterial.GetItemByOnlyeID( nGUID, &stItem ) )
	{
		eType = BT_MaterialBag;
		if( pIndex )
			*pIndex = m_bagMaterial.GetItemIndexByGUID( nGUID );
		return true;
	}
	if( m_bagTask.GetItemByOnlyeID( nGUID, &stItem ) )
	{
		eType = BT_TaskBag;
		if( pIndex )
			*pIndex = m_bagMaterial.GetItemIndexByGUID( nGUID );
		return true;
	}

	return false; // not found
}

bool CPlayerRole::GetBagByItemGUID( __int64 nGUID, CItemBag2*& pBag )
{
	SCharItem stItem;	
	if( m_bag.GetItemByOnlyeID( nGUID, &stItem ) )
	{
		pBag = &m_bag;
		return true;
	}
	if( m_bagMaterial.GetItemByOnlyeID( nGUID, &stItem ) )
	{
		pBag = &m_bagMaterial;
		return true;
	}
	if( m_bagTask.GetItemByOnlyeID( nGUID, &stItem ) )
	{
		pBag = &m_bagTask;
		return true;
	}

	return false; // not found
}
CItemBag2* CPlayerRole::GetBagByItemID(unsigned int ItemID)
{
	ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID(ItemID);
	if(!pItemDetail)
		return NULL;
	else
		return GetBagByItemType(pItemDetail->ucItemType);
}
CItemBag2* CPlayerRole::GetBagByItemType(int nItemType)
{
	switch( nItemType )
	{
	case ItemDefine::ITEMTYPE_SKILL:
	case ItemDefine::ITEMTYPE_STATUS:    
	case ItemDefine::ITEMTYPE_ACTION:
		{
			return NULL;
		}
		break;
	case ItemDefine::ITEMTYPE_TASK:
		{
			return &m_bagTask;
		}
		break;
	case ItemDefine::ITEMTYPE_MATERIAL:
	case ItemDefine::ITEMTYPE_GEM:
		{
			return &m_bagMaterial;
		}
	case ItemDefine::ITEMTYPE_RESTORE:
	case ItemDefine::ITEMTYPE_WEAPON:
	case ItemDefine::ITEMTYPE_ARMOUR:
	case ItemDefine::ITEMTYPE_CREATEITEMRULE:
	case ItemDefine::ITEMTYPE_OTHER:
	case ItemDefine::ITEMTYPE_REEL:
	case ItemDefine::ITEMTYPE_TREASUREBOX:
	case ItemDefine::ITEMTYPE_CHECKUP:
	case ItemDefine::ITEMTYPE_REALAWARD:
	case ItemDefine::ITEMTYPE_GUILD:
	case ItemDefine::ITEMTYPE_SPECIAL:
	case ItemDefine::ITEMTYPE_PETEQUIP:
		{
			return &m_bag;
		}
		break;
	default:
		return NULL;
	}
}
int CPlayerRole::GetBagTypeByItemType( int nItemType )
{
	switch( nItemType )
	{
	case ItemDefine::ITEMTYPE_SKILL:
	case ItemDefine::ITEMTYPE_STATUS:    
	case ItemDefine::ITEMTYPE_ACTION:
		{
			return -1;
		}
		break;
	case ItemDefine::ITEMTYPE_TASK:
		{
			return BT_TaskBag;
		}
		break;
	case ItemDefine::ITEMTYPE_MATERIAL:
	case ItemDefine::ITEMTYPE_GEM:
		{
			return BT_MaterialBag;
		}
	case ItemDefine::ITEMTYPE_RESTORE:
	case ItemDefine::ITEMTYPE_WEAPON:
	case ItemDefine::ITEMTYPE_ARMOUR:
	case ItemDefine::ITEMTYPE_CREATEITEMRULE:
	case ItemDefine::ITEMTYPE_OTHER:
	case ItemDefine::ITEMTYPE_REEL:
	case ItemDefine::ITEMTYPE_TREASUREBOX:
	case ItemDefine::ITEMTYPE_CHECKUP:
	case ItemDefine::ITEMTYPE_REALAWARD:
	case ItemDefine::ITEMTYPE_GUILD:
	case ItemDefine::ITEMTYPE_SPECIAL:
	case ItemDefine::ITEMTYPE_PETEQUIP:
		{
			return BT_NormalItemBag;
		}
		break;
	default:
		return -1;
	}
}
bool CPlayerRole::TaskNeedRemind( SQuest* pQuest )
{
	if( !pQuest )
	{
		return false;
	}
	// 任务前置
	int nBeginPos = 0;
	SQuestRequirement*  pReqQuest = pQuest->GetReceiveRequirement(SQuest::eRequirement_Quest,&nBeginPos);
	while (pReqQuest  )
	{
		CPlayerRole::QuestInfo* pReqInfo = thePlayerRole.FindQuestInfoById(pReqQuest->Value );
		if ( !pReqInfo || !theQuestManager.IsQuestDone( pReqInfo->chState ) )
		{
			return false;
		}
		pReqQuest = pQuest->GetReceiveRequirement(SQuest::eRequirement_Quest,&nBeginPos);
	}
	int nPlayerLevel = GetLevel();	
	if ( nPlayerLevel < pQuest->GetPlayerReceiveQuestLevel() )//策划需求，去掉3级
		return false;
	//做过的
	CPlayerRole::QuestInfo* pInfo = FindQuestInfoById(pQuest->Id);
	if (!pInfo || QuestManager::Instance().IsQuestDone(pInfo->chState))
	{
		return false;
	}
	// 职业限制
	int nProfession = GetProfession();
	if ( !(pQuest->GetPlayerReceiveQuestProfession() & (1 << nProfession)) )
	{
		return false;
	}
	// 性别限制
	if (pQuest->GetPlayerReceiveQuestSex() == 1 - GetSex() )
	{
		return false;
	}
	// 物品前置
	pReqQuest = pQuest->GetReceiveRequirement(SQuest::eRequirement_Item,&nBeginPos);
	while (pReqQuest  )
	{
		ItemDefine::SItemCommon* pItemDetail = NULL;
		pItemDetail = GettheItemDetail().GetItemByID( pReqQuest->Value );
		if( pItemDetail )
		{
			int nItemCount = m_bag.GetItemCount( pItemDetail->ustItemID );
			if (nItemCount < 1)
			{
				nItemCount = m_bagMaterial.GetItemCount( pItemDetail->ustItemID );
				if (nItemCount < 1)
					nItemCount = m_bagTask.GetItemCount( pItemDetail->ustItemID );
			}

			if( nItemCount < pReqQuest->MaxNum )
				return false;
		}
		pReqQuest = pQuest->GetReceiveRequirement(SQuest::eRequirement_Item,&nBeginPos);
	}

	//变量限制
	{
		SQuestRequirement* pRequire = pQuest->GetReceiveRequirement(SQuest::eRequirement_Var);
		if (pRequire)
		{
			CPlayerRole::QuestInfo * pInfo = FindVariableInfoById( pRequire->wVar );
			if(!pInfo || (pInfo->chState < pRequire->MaxNum))
			{
				return false;
			}
		}

	}

    // 弱国限制     added by ZhuoMeng.Hu		[12/10/2010]
    {
        SQuestRequirement* pRequire = pQuest->GetReceiveRequirement( SQuest::eRequirement_WeakCountry );
        if( pRequire )
        {
            if( !IsInWeakCountry() )
                return false;
        }
    }

	return true;
}

bool CPlayerRole::IsQuestDone( SQuest *pQuest )
{
	if (pQuest == NULL)
	{
		return false;
	}

	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (!pMe)
	{
		return false;
	}

	CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( pQuest->Id );
	if(pInfo && pInfo->chState == QuestManager::eQuestEntrustDone)
		return true;//特殊状态

	bool bDone = true;
	for( int i = 0; i < pQuest->stCommitRequirement.size(); i++ )
	{
		SQuestRequirement *pRequirement = &pQuest->stCommitRequirement[i];
		char szInfo[256] = "";
		switch( pRequirement->byType )
		{
		case SQuest::eRequirement_Var:
			{
				CPlayerRole::QuestInfo* pVariableInfo = FindVariableInfoById( pRequirement->wVar );
				if (pVariableInfo)
				{
					if (pVariableInfo->chState != pRequirement->MaxNum)
					{
						bDone = false;
					}
					else
					{
						bDone = true;
					}
				}
				else
				{
					bDone = false;
				}
			}
			break;
		case SQuest::eRequirement_Item:
			{
				ItemDefine::SItemCommon* pItemDetail = NULL;
				pItemDetail = GettheItemDetail().GetItemByID( pRequirement->Value );
				if( pItemDetail )
				{
					int nItemCount = m_bag.GetItemCount( pItemDetail->ustItemID );
					if (nItemCount < 1)
					{
						nItemCount = m_bagMaterial.GetItemCount( pItemDetail->ustItemID );
						if (nItemCount < 1)
							nItemCount = m_bagTask.GetItemCount( pItemDetail->ustItemID );
					}

					if( nItemCount < pRequirement->MaxNum )
						bDone = false;
					else
						bDone = true;
				}
				else
					bDone = false;
			}
			break;
		case SQuest::eRequirement_Monster:
			{
				int nVar = 0;
				CPlayerRole::QuestInfo* pVariableInfo = FindVariableInfoById( pRequirement->wVar );
				if( pVariableInfo )
					nVar = pVariableInfo->chState;
				if( nVar < pRequirement->MaxNum )
					bDone = false;
				else
					bDone = true;
			}
			break;
		case SQuest::eRequirement_Action:
			{
				int nVar = 0;
				CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
				if( pVariableInfo )
					nVar = pVariableInfo->chState;
				MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, "%s (%ld/%ld)", theXmlString.GetString(pRequirement->Value), nVar, pRequirement->MaxNum );
				if( nVar < pRequirement->MaxNum )
				{
					bDone = false;
				}
				else
				{
					bDone = true;
				}
			}
			break;
		case SQuest::eRequirement_Status:
			{
				bool bBuffExist = pMe->m_cFightStatus.IsBuffExist(pRequirement->Value);
				if (!bBuffExist)
				{
					bDone = false;
				}
				else
				{
					bDone = true;
				}
			}
			break;
		case SQuest::eRequirement_NoStatus:
			{
				bool bBuffExist = pMe->m_cFightStatus.IsBuffExist(pRequirement->Value);
				if (bBuffExist)
				{
					bDone = false;
				}
				else
				{
					bDone = true;
				}
			}
			break;
		case SQuest::eRequirement_XinFaLevel:      // 心法等级
			{
				if(pRequirement->Value > 0)
				{
					SCharXinFa* pXinFa = thePlayerRole.m_xinFaBag.GetXinFaByID(pRequirement->Value);
					if(!pXinFa)
					{
						bDone = false;
					}
					else
					{
						 if( pXinFa->nXinFaLevel >= pRequirement->MaxNum )
						     bDone = true;
						 else
							 bDone = false;
					}
				}
				else
				{
					bDone = false;
					int nCount = thePlayerRole.m_xinFaBag.GetXinFaNum();
					for (int i = 0;i < nCount ;++i)
					{
						SCharXinFa *pXinFa = thePlayerRole.m_xinFaBag.GetXinFaByIndex(i);
						if(!pXinFa)
							continue;

		                if( pXinFa->nXinFaLevel >= pRequirement->MaxNum )
						{
							bDone = true;
							break;
						}
					}
				}
			}
			break;
		case SQuest::eRequirement_PetNumber:       // 宠物数量
			{
				int nSize = thePlayerRole.GetPetCount();
				if( nSize >= pRequirement->MaxNum )
				{
					bDone = true;
				}
				else
				{
					bDone = false;
				}
			}
			break;
		case SQuest::eRequirement_PetLevel:        // 宠物等级
			{
				bDone = false;

				int nCount = thePlayerRole.GetPetCount();
				for (int i = 0;i < nCount;++i)
				{
					SPetItem Pet = thePlayerRole.GetPetByIndex(i);

					if(Pet.baseInfo.level >= pRequirement->MaxNum)
					{
						bDone = true;
						break;
					}
				}
			}
			break;
		case SQuest::eRequirement_PetID:           // 宠物ID
			{
				bDone = false;

				int nCount = thePlayerRole.GetPetCount();
				for (int i = 0;i < nCount;++i)
				{
					SPetItem Pet = thePlayerRole.GetPetByIndex(i);

					if(Pet.baseInfo.petId == pRequirement->Value)
					{
						bDone = true;
						break;
					}
				}
			}
			break;
		case SQuest::eRequirement_PetType:         // 宠物类型
			{
				bDone = false;

				int nCount = thePlayerRole.GetPetCount();
				for (int i = 0;i < nCount;++i)
				{
					SPetItem Pet = thePlayerRole.GetPetByIndex(i);

					if(Pet.baseInfo.petType == pRequirement->Value)
					{
						bDone = true;
						break;
					}
				}
			}
			break;
		case SQuest::eRequirement_PetActive:       // 宠物出战
			{
				bDone = false;
				int nCount = thePlayerRole.GetPetCount();
				for (int i = 0;i < nCount;++i)
				{
					SPetItem Pet = thePlayerRole.GetPetByIndex(i);

					if(Pet.baseInfo.isActive)
					{
						bDone = true;
						break;
					}
				}
			}
			break;
		default:
			// 				assert(false);
			break;
		}

		if (bDone)
		{
			if (pQuest->IsSingleRequirement)
			{
				break;
			}
			else
			{
				continue;
			}
		}
		else
		{
			if (pQuest->IsSingleRequirement)
			{
				continue;
			}
			else
			{
				return false;	
			}
		}
	}
	return bDone;
}

void CPlayerRole::RefreshQuestDone()
{
	for(int i = 0; i < m_vectorActiveQuestInfo.size();++i)
	{
		m_vectorActiveQuestInfo[i]->bDone = IsQuestDone(theQuestManager.GetQuest( m_vectorActiveQuestInfo[i]->nQuestId ));
		if(m_vectorActiveQuestInfo[i]->chState ==  QuestManager::eQuestFrozen && m_vectorActiveQuestInfo[i]->bDone)
			m_vectorActiveQuestInfo[i]->bDone = false;
	}
	GetRegionMap()->SetUpdateStableImage(true);
	//if(s_CUI_ID_FRAME_Gut.GetFrame() && s_CUI_ID_FRAME_Gut.IsVisable())
	//{
	//	s_CUI_ID_FRAME_Gut.EndNpcScript();
 //       s_CUI_ID_FRAME_Gut.SetVisable(false); //如果gut面板已经打开，任务状态发生变化的时候 则关闭它，重新进行打开
	//}
	s_CUI_ID_FRAME_Task.SetDirty( true );
}

//===============================================================
// 称号相关
//===============================================================
void CPlayerRole::SetTitleListInfo( SCharBaseInfo::SCharLiveInfo* pMsg )
{
	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if( !pMe )
		return ;
	
	pMe->SetTitleInfoById( pMsg->nCurrentTitleID );	
	m_vTitleArray.clear();
	for( int i = 0 ; i < MAX_TITLE_COUNT ; ++ i )
	{
		if( pMsg->xTitleData[i].GetTitleID() != 0 )
			m_vTitleArray.push_back( pMsg->xTitleData[i] );
	}
}
void CPlayerRole::AddNewTitleId( short stId,__int64 n64AcquireTime ,uint32 nActiveTime )
{
	if( stId == 0 )
		return;

    TitleData tTitle;
    tTitle.SetTitleID(stId);
    tTitle.SetAcquireTime(n64AcquireTime);
    tTitle.SetActiveTime(nActiveTime);
	
	m_vTitleArray.push_back( tTitle );
}

void CPlayerRole::RemoveTitleId( short stId )
{
	if( stId == 0 )
		return;
	std::vector<TitleData>::iterator it = m_vTitleArray.begin();
	for( ; it != m_vTitleArray.end() ; ++ it )
	{
		if( (*it).GetTitleID() == stId )
		{
			m_vTitleArray.erase( it );
			return;
		}
	}
}

bool CPlayerRole::IsQuestInitialized()
{
	return m_bQuestInitialized;
}

void CPlayerRole::QuestInfoInitialized()
{
	m_bQuestInitialized = true;
}

//long CPlayerRole::deleteGuild( int id )
//{
//	GuildListType::iterator it, end = _guildList.end();
//	for ( it = _guildList.begin(); it != end; ++it )
//	{
//		if ( (*it).baseInfo.GetID() == id )
//		{
//			_guildList.erase( it );
//			break;
//		}
//	}
//	return 0;
//}

void CPlayerRole::GetGSCFromMoney( DWORD inputMoney, int& iGold, int& iSilver, int& iCopper )
{
    iGold = inputMoney / 10000;
    iSilver = (inputMoney - iGold * 10000) / 100;
    iCopper = inputMoney - iGold * 10000 - iSilver * 100;
}

void CPlayerRole::GetGSCStringFromMoney( DWORD inputMoney, std::string& strText )
{
    int gold = 0,silver = 0,copper = 0;
    GetGSCFromMoney(inputMoney,gold,silver,copper);

    std::stringstream str;
	if( gold > 0 )
		str << gold << "#81  ";
	if( silver > 0 )
		str << silver << "#82  ";
	if( copper > 0 )
		str << copper << "#83  ";

	if( str.str().size() == 0 )
		str << 0 << "#83  ";

    strText = str.str();
	ExpressionManager::GetInstance().AddExpressionAni(strText);
}

void CPlayerRole::GetGSCStringFromCurrentMoney( std::string& strText )
{
	DWORD dwMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
	GetGSCStringFromMoney(dwMoney, strText);
}

void CPlayerRole::GetGSCStringFromJiaoZi(DWORD inputJiaoZi, std::string& strText)
{
	int gold = 0,silver = 0,copper = 0;
	GetGSCFromMoney(inputJiaoZi,gold,silver,copper);

	std::stringstream str;
	if( gold > 0 )
		str << gold << "#61  ";
	if( silver > 0 )
		str << silver << "#62  ";
	if( copper > 0 )
		str << copper << "#63  ";

	if( str.str().size() == 0 )
		str << 0 << "#63  ";

	strText = str.str();
	ExpressionManager::GetInstance().AddExpressionAni(strText);
}

void CPlayerRole::GetGSCStringFromCurrentJiaoZi(std::string& strText)
{
	DWORD dwJiaoZi = thePlayerRole.GetData(CPlayerRole::TYPE_JiaoZi);
	GetGSCStringFromJiaoZi(dwJiaoZi, strText);
}

bool CPlayerRole::PackHasEnoughMoney( int iGold, int iSilver, int iCopper )
{
    DWORD dwMoney = GetMoneyFromGSC(iGold, iSilver, iCopper);
    return GetData(CPlayerRole::TYPE_MONEY) >= dwMoney;
}

bool CPlayerRole::PackHasEnoughMoney( DWORD dwMoney )
{
    return GetData(CPlayerRole::TYPE_MONEY) >= dwMoney;
}

DWORD CPlayerRole::GetMoneyFromGSC( int iGold, int iSilver, int iCopper )
{
    DWORD dwMoney = iGold * 10000 + iSilver * 100 + iCopper;
    return dwMoney;
}

bool CPlayerRole::StorageHasEnoughMoney( int iGold, int iSilver, int iCopper )
{
    DWORD dwMoney = GetMoneyFromGSC(iGold, iSilver, iCopper);
    return m_stStorage.dwStorageMoney >= dwMoney;
}

bool CPlayerRole::StorageHasEnoughMoney( DWORD dwMoney )
{
    return m_stStorage.dwStorageMoney >= dwMoney;
}

bool  CPlayerRole::HaveEnoughMoney(DWORD dwMoney)
{
    DWORD dwJiaoZi = GetData(CPlayerRole::TYPE_JiaoZi);
    if(dwJiaoZi >= dwMoney)
        return true;
    
    DWORD dwAllMoney  = GetData(CPlayerRole::TYPE_MONEY);
    if(dwMoney - dwJiaoZi <= dwAllMoney )
        return true;

    return false;
}

//GuildMember* CFamilyInfo::GetTongMaster()
//{
//	if (m_vMember.size() > 0)
//	{
//		for(int i = 0 ; i < m_vMember.size(); ++i)
//		{
//			if (m_vMember[i]->GetPosition() == GuildDefine::Position_FamilyMaster)
//			{
//				return m_vMember[i];
//			}
//		}
//	}
//	return NULL;
//}

bool CPlayerRole::UpdateActiveQuestStateByItem( int ustItemID )
{
	//if (m_vectorActiveQuestInfo.size() == 0)
	//{
	//	return false;
	//}

	bool bRet = false;
	//删除已有的和以此物品前置的任务
	std::vector<QuestInfo*>::iterator iterBegin = m_vectorActiveQuestInfo.begin();
	while(iterBegin != m_vectorActiveQuestInfo.end())
	{
		QuestInfo* pQuestInfo = (*iterBegin);
		SQuest* pQuest = theQuestManager.GetQuest( pQuestInfo->nQuestId );
		assert(pQuest);
		int nBeginPos = 0;
		SQuestRequirement* pRequire = pQuest->GetReceiveRequirement(SQuest::eRequirement_Item);
		bool bFound = false;
		while (pRequire  )
		{
			if ((pRequire->Value == ustItemID))
			{
				iterBegin = m_vectorActiveQuestInfo.erase(iterBegin);
				bFound = true;
				bRet = true;
				break;
			}
			pRequire = pQuest->GetReceiveRequirement(SQuest::eRequirement_Item,&nBeginPos);
		}
		if(!bFound)
		{
			++iterBegin;
		}
	}
	//然后重新添加以此物品前置的任务
	for (int i = 0; i < m_vectorRequirementItemQuestId.size(); ++i)
	{
		QuestInfo* pQuestInfo = FindQuestInfoById(m_vectorRequirementItemQuestId[i]);
		SQuest* pQuest = theQuestManager.GetQuest( pQuestInfo->nQuestId );
		int nBeginPos = 0;
		SQuestRequirement* pRequire = pQuest->GetReceiveRequirement(SQuest::eRequirement_Item);
		while (pRequire  )
		{
			if ((pRequire->Value == ustItemID))
			{
				if(AddToActiveQuestInfo(pQuestInfo))
					bRet = true;
				break;
			}
			pRequire = pQuest->GetReceiveRequirement(SQuest::eRequirement_Item,&nBeginPos);
		}
	}
	if(bRet)
	{
		theHeroGame.GetPlayerMgr()->RefreshAllNpcQuest();
		GetRegionMap()->SetUpdateStableImage(true);
		s_CUI_ID_FRAME_Task.SetDirty( true );
	}
	RefreshQuestDone();
	s_CUI_ID_FRAME_Task.Refresh( false);
	return bRet;
}

bool CPlayerRole::UpdateActiveQuestStateByVariable(QuestInfo* pVariableInfo)
{
	//if (m_vectorActiveQuestInfo.size() == 0)
	//{
	//	return false;
	//}
	bool bRet = false;
	//删除已有的以此变量前置的任务
	std::vector<QuestInfo*>::iterator iterBegin = m_vectorActiveQuestInfo.begin();
	while(iterBegin != m_vectorActiveQuestInfo.end())
	{
		QuestInfo* pQuestInfo = (*iterBegin);
		SQuest* pQuest = theQuestManager.GetQuest( pQuestInfo->nQuestId );
		assert(pQuest);
		SQuestRequirement* pRequire = pQuest->GetReceiveRequirement(SQuest::eRequirement_Var);
		if (pRequire && (pRequire->wVar == pVariableInfo->nQuestId))
		{
			iterBegin = m_vectorActiveQuestInfo.erase(iterBegin);
			bRet = true;
		}
		else
		{
			++iterBegin;
		}
	}
	//然后重新添加以此变量前置的任务
	for (int i = 0; i < m_vectorRequirementVariableQuestId.size(); ++i)
	{
		QuestInfo* pQuestInfo = FindQuestInfoById(m_vectorRequirementVariableQuestId[i]);
		SQuest* pQuest = theQuestManager.GetQuest( pQuestInfo->nQuestId );
		SQuestRequirement* pRequire = pQuest->GetReceiveRequirement(SQuest::eRequirement_Var);
		if (pRequire &&  (pRequire->wVar == pVariableInfo->nQuestId))
		{
			if(AddToActiveQuestInfo(pQuestInfo))
				bRet = true;
		}
	}
	return bRet;
}

bool CPlayerRole::UpdateActiveQuestStateByQuest( QuestInfo* pChangedQuestInfo )
{
	//if (m_vectorActiveQuestInfo.size() == 0)
	//{
	//	return false;
	//}
	bool bRet = false;
	//删除已有的以此任务前置的任务
	std::vector<QuestInfo*>::iterator iterBegin = m_vectorActiveQuestInfo.begin();
	while(iterBegin != m_vectorActiveQuestInfo.end())
	{
		QuestInfo* pQuestInfo = (*iterBegin);
		if (pChangedQuestInfo == pQuestInfo)
		{
			iterBegin = m_vectorActiveQuestInfo.erase(iterBegin);
			bRet = true;
		}
		else
		{
			SQuest* pQuest = theQuestManager.GetQuest( pQuestInfo->nQuestId );
			assert(pQuest);
			int nBeginPos = 0;
			bool bFound = false;
			SQuestRequirement*  pReqQuest = pQuest->GetReceiveRequirement(SQuest::eRequirement_Quest,&nBeginPos);
			while (pReqQuest  )
			{
				if ( pReqQuest->Value == pChangedQuestInfo->nQuestId)
				{
					iterBegin = m_vectorActiveQuestInfo.erase(iterBegin);
					bFound = true;
					bRet = true;
					break;
				}
				pReqQuest = pQuest->GetReceiveRequirement(SQuest::eRequirement_Quest,&nBeginPos);
			}
			if (!bFound)
			{
				++iterBegin;
			}
		}
	}
	//然后重新添加以此任务前置的任务
	QuestInfos::iterator it, end = m_questInfos.end();
	for(it = m_questInfos.begin(); it != end; ++it)
	{
		QuestInfo* pQuestInfo = &(it->second);
		SQuest* pQuest = theQuestManager.GetQuest( pQuestInfo->nQuestId );
		assert(pQuest);
		if (pChangedQuestInfo == pQuestInfo)
		{
			if(AddToActiveQuestInfo(pQuestInfo))
				bRet = true;
		}
		else
		{
			int nBeginPos = 0;
			bool bFound = false;
			SQuestRequirement*  pReqQuest = pQuest->GetReceiveRequirement(SQuest::eRequirement_Quest,&nBeginPos);
			while (pReqQuest  )
			{
				if ( pReqQuest->Value == pChangedQuestInfo->nQuestId)
				{
					if(AddToActiveQuestInfo(pQuestInfo))
						bRet = true;
					break;
				}
				pReqQuest = pQuest->GetReceiveRequirement(SQuest::eRequirement_Quest,&nBeginPos);
			}
		}

	}
	return bRet;
}

void CPlayerRole::FillRequirementQuestArr()
{
	for (int i = dr_MinQuestId + 1; i <= dr_MaxQuestId; ++i)
	{
		SQuest* pQuest = theQuestManager.GetQuest( i );
		if (!pQuest)
		{
			continue;
		}
		SQuestRequirement* pRequire = pQuest->GetReceiveRequirement(SQuest::eRequirement_Var);
		if (pRequire)
		{
			m_vectorRequirementVariableQuestId.push_back(i);
		}
		pRequire = pQuest->GetReceiveRequirement(SQuest::eRequirement_Item);
		if (pRequire)
		{
			m_vectorRequirementItemQuestId.push_back(i);
		}
	}
}

bool CPlayerRole::AddToActiveQuestInfo( QuestInfo* info )
{
	if (info == NULL)
	{
		return false;
	}
	bool bRet = false;
	assert (info->nQuestId > dr_MinQuestId && info->nQuestId <= dr_MaxQuestId) ;
	{
		SQuest* pQuest = theQuestManager.GetQuest( info->nQuestId );
		if (!pQuest)
		{
			return false;
		}
		if(pQuest->CanDisplay)
		{
			if( info->chState != QuestManager::eQuestNotGain &&
				info->chState != QuestManager::eQuestDone
				)
			{
				if (thePlayerRole.GetLevel() < pQuest->GetPlayerReceiveQuestLevel())
				{
					return false;
				}
				m_vectorActiveQuestInfo.push_back( info );
				bRet = true;
			}
			else 
			{
				if(TaskNeedRemind(pQuest))
				{
					m_vectorActiveQuestInfo.push_back( info );
					bRet = true;
				}
			}
		}
		else				
		{
			if (pQuest->IsPubQuest() || pQuest->IsConQuest())
			{
				if( info->chState != QuestManager::eQuestNotGain &&
					info->chState != QuestManager::eQuestDone 
					)
				{
					if (thePlayerRole.GetLevel() < pQuest->GetPlayerReceiveQuestLevel())
					{
						return false;
					}
					m_vectorActiveQuestInfo.push_back( info );
					bRet = true;
				}
				else 
				{
					if(TaskNeedRemind(pQuest))
					{
						m_vectorActiveQuestInfo.push_back( info );
						bRet = true;
					}
				}
			}
			else
			{
				if( info->chState != QuestManager::eQuestNotGain &&
					info->chState != QuestManager::eQuestDone )
				{
					m_vectorActiveQuestInfo.push_back( info );
					bRet = true;
				}
			}
		}
	}
	return bRet;
}

void CPlayerRole::UpdateLockItem()
{
	m_fUpdateLockItemTime -= theHeroGame.GetFrameElapsedTime();

	if(m_fUpdateLockItemTime<=0)
	{
		m_fUpdateLockItemTime = 3.0f;
	}

	m_fUnLockTimeCount += theHeroGame.GetFrameElapsedTime();

	int passedSecond = 0;
	if(m_fUnLockTimeCount >=1 )
	{
		passedSecond = (int)m_fUnLockTimeCount;
		m_fUnLockTimeCount-=(int)m_fUnLockTimeCount;
	}

	//背包
    for (int i  = 0; i < m_bag.GetNowBagSize(); ++i)
    {
		if(m_bag.m_pPackItem[i].IsLock())
		{
			if(m_bag.m_pPackItem[i].GetUnLockTime()!=0)
			{
				//计算解锁时间
				if(m_bag.m_pPackItem[i].GetUnLockLeftTime() <= passedSecond )
				{
					m_bag.m_pPackItem[i].SetUnLockLeftTime( 0 );

					if(m_fUpdateLockItemTime==3.0f)
					{
						MsgCheckUnLockItemReq msg;

						msg.uchBagType = BT_NormalItemBag;
						msg.ustItemIndex = i;
						msg.nGuID = m_bag.m_pPackItem[i].itembaseinfo.nOnlyInt;

						GettheNetworkInput().SendMsg( &msg );
					}
				}
				else
				{
					m_bag.m_pPackItem[i].SetUnLockLeftTime(m_bag.m_pPackItem[i].GetUnLockLeftTime()-passedSecond);
				}
			}
		}
		// 更新装备剩余时间
		if( m_bag.m_pPackItem[i].itembaseinfo.n64UseTime > 0 && m_bag.m_pPackItem[i].itembaseinfo.nLeftTime > 0 )
		{
			if( m_bag.m_pPackItem[i].itembaseinfo.nLeftTime >= passedSecond )
				m_bag.m_pPackItem[i].itembaseinfo.nLeftTime -= passedSecond;
			else
				m_bag.m_pPackItem[i].itembaseinfo.nLeftTime = 0;
		}
    }

	//仓库
    for (int i  = 0; i < STORAGE_ITEMGRID_MAX; ++i)
    {
		if(m_stStorage.stStorageItems[i].IsLock())
		{
			if(m_stStorage.stStorageItems[i].GetUnLockTime()!=0)
			{
				//计算解锁时间
				if(m_stStorage.stStorageItems[i].GetUnLockLeftTime() <= passedSecond )
				{
					m_stStorage.stStorageItems[i].SetUnLockLeftTime( 0 );

					if(m_fUpdateLockItemTime==3.0f)
					{
						MsgCheckUnLockItemReq msg;

						msg.uchBagType = BT_StorageBag;
						msg.ustItemIndex = i;
						msg.nGuID =m_stStorage.stStorageItems[i].itembaseinfo.nOnlyInt;

						GettheNetworkInput().SendMsg( &msg );
					}
				}
				else
				{
					m_stStorage.stStorageItems[i].SetUnLockLeftTime(m_stStorage.stStorageItems[i].GetUnLockLeftTime()-passedSecond);
				}
			}
		}
		// 更新装备剩余时间
		if( m_stStorage.stStorageItems[i].itembaseinfo.n64UseTime > 0 && m_stStorage.stStorageItems[i].itembaseinfo.nLeftTime > 0 )
		{
			if( m_stStorage.stStorageItems[i].itembaseinfo.nLeftTime >= passedSecond )
				m_stStorage.stStorageItems[i].itembaseinfo.nLeftTime -= passedSecond;
			else
				m_stStorage.stStorageItems[i].itembaseinfo.nLeftTime = 0;
		}
	}

	//坐骑
	for (int i = 0; i < m_charinfo.baseinfo.liveinfo.ucMountCount; ++i)
	{
		if (m_charinfo.ItemBagData.miItems[i].baseInfo.id != InvalidLogicNumber)
		{
			if(m_charinfo.ItemBagData.miItems[i].IsLock())
			{
				if(m_charinfo.ItemBagData.miItems[i].GetUnLockTime()!=0)
				{
					//计算解锁时间
					if(m_charinfo.ItemBagData.miItems[i].GetUnLockLeftTime() <= passedSecond )
					{
						m_charinfo.ItemBagData.miItems[i].SetUnLockLeftTime( 0 );

						if(m_fUpdateLockItemTime==3.0f)
						{
							MsgCheckUnLockItemReq msg;

							msg.uchBagType = BT_MountBag;
							msg.ustItemIndex = i;
							msg.nGuID = m_charinfo.ItemBagData.miItems[i].baseInfo.guid;

							GettheNetworkInput().SendMsg( &msg );
						}
					}
					else
					{
						m_charinfo.ItemBagData.miItems[i].SetUnLockLeftTime(m_charinfo.ItemBagData.miItems[i].GetUnLockLeftTime()-passedSecond) ;
					}
				}
			}
		}
	}

	//装备 
	for(int i=0;i<EEquipPartType_MaxEquitPart;++i)
	{
		if(m_pVisual->equipitem[i].IsLock())
		{
			if(m_pVisual->equipitem[i].GetUnLockTime()!=0)
			{
				//计算解锁时间
				if(m_pVisual->equipitem[i].GetUnLockLeftTime() <= passedSecond )
				{
					m_pVisual->equipitem[i].SetUnLockLeftTime( 0 );
				}
				else
				{
					m_pVisual->equipitem[i].SetUnLockLeftTime( m_pVisual->equipitem[i].GetUnLockLeftTime() - passedSecond );
				}
			}
		}
		// 更新装备剩余时间
		if( m_pVisual->equipitem[i].itembaseinfo.n64UseTime > 0 && m_pVisual->equipitem[i].itembaseinfo.nLeftTime > 0 )
		{
			if( m_pVisual->equipitem[i].itembaseinfo.nLeftTime >= passedSecond )
				m_pVisual->equipitem[i].itembaseinfo.nLeftTime -= passedSecond;
			else
				m_pVisual->equipitem[i].itembaseinfo.nLeftTime = 0;
		}
	}

	//回购
	for(int i=0;i<s_CUI_ID_FRAME_SHOP.GetBuyBackPack().GetMaxPackSize();++i)
	{
		SCharItem* pscItem = s_CUI_ID_FRAME_SHOP.GetBuyBackPack().GetItemByIndex(i);

		if(pscItem)
		{
			// 更新装备剩余时间
			if( pscItem->itembaseinfo.n64UseTime > 0 && pscItem->itembaseinfo.nLeftTime > 0 )
			{
				if( pscItem->itembaseinfo.nLeftTime >= passedSecond )
					pscItem->itembaseinfo.nLeftTime -= passedSecond;
				else
					pscItem->itembaseinfo.nLeftTime = 0;
			}
		}
	}

	//仓库密码
	if(m_nSecondPasswordUnlockTime >= passedSecond )
	{
		m_nSecondPasswordUnlockTime -= passedSecond;
	}
	else
	{
		m_nSecondPasswordUnlockTime = 0;
	}

	//副将装备
	for (int i = 0; i < ITEM_PET_MAXCOUNT; ++i)
	{
		SPetItem& pPet = GetPetByIndex(i);
		if(pPet.baseInfo.petId == InvalidLogicNumber)
			continue;
		for(int j =0;j<SPetItem::PetEquip_MaxSum;++j)
		{
			SCharItem& pItem = pPet.baseInfo.PetEquip[j];
			if(pItem.IsOverdue(true) && !pItem.petequipdata.isTimeEnd)
			{
				if(pPet.baseInfo.guid == s_CUI_ID_FRAME_SuAnimal.GetCurrentPet().baseInfo.guid)
				{
					s_CUI_ID_FRAME_SuAnimal.LookPet(s_CUI_ID_FRAME_SuAnimal.GetCurrentMountIndex());//刷新副将的属性 在装备到期后
					pItem.petequipdata.isTimeEnd = true;
				}
			}
		}
	}
}

void CPlayerRole::SetIsSecondPassword( bool b )
{
	m_bSecondPassword = b;
}

bool CPlayerRole::GetIsSecondPassword()
{
	return m_bSecondPassword;
}

void CPlayerRole::SetSecondPasswordUnlockTime( uint32 time )
{
	m_nSecondPasswordUnlockTime = time;
}

uint32 CPlayerRole::GetSecondPasswordUnlockTime()
{
	return m_nSecondPasswordUnlockTime;
}



//friend
int CPlayerRole::GetdbID(const char *szName)
{
	guardfunc;
	std::map<int, RelationDataToClient>::iterator iter = m_mapFriendInfo.begin();

	for( ; iter != m_mapFriendInfo.end(); ++iter)
	{
		if(0 == strcmp(iter->second.GetName() ,szName))
			return iter->first;
	}

	return -1;
	unguard;
}

const char* CPlayerRole::GetNameByDBID(uint32 uiDBID)
{
	std::map<int, RelationDataToClient>::iterator iter = m_mapFriendInfo.find( uiDBID );
	if( iter != m_mapFriendInfo.end() )
	{
		return iter->second.GetName();
	}
	return NULL;
}

bool CPlayerRole::isFrdInBlackList(const char* name)
{
	guardfunc;
	if( NULL == name )
		return false;

	std::map<int, RelationDataToClient>::iterator iter = m_mapFriendInfo.begin();
	for( ; iter != m_mapFriendInfo.end(); ++iter)
	{
		if(0 == strcmp(iter->second.GetName() ,name))
		{
//sbw_modify_binaryflag			if( iter->second._eSType == eSTP_BlackList )
			if( iter->second.HaveRelation(RelationDefine::BlackList))
				return true;
		}
	}
	return false;
	unguard;
}

bool CPlayerRole::IsPlayerLock(const char* szName)
{
	guardfunc;
	std::map<int, RelationDataToClient>::iterator iter = m_mapFriendInfo.begin();

	for( ; iter != m_mapFriendInfo.end(); ++iter)
	{
		if(0 == strcmp(iter->second.GetName() ,szName))
		{
			if( iter->second.GetLocked())
				return true;
		}
	}

	return false;
	unguard;
}

bool CPlayerRole::IsOnline(const char* szName)
{
	guardfunc;
	std::map<int, RelationDataToClient>::iterator iter = m_mapFriendInfo.begin();

	for( ; iter != m_mapFriendInfo.end(); ++iter)
	{
		if(0 == strcmp(iter->second.GetName() ,szName))
		{
			if( iter->second.GetOnLine())
				return true;
		}
	}

	return false;
	unguard;
}

bool CPlayerRole::IsFriend( const char* szName )
{
	guardfunc;
	std::map<int, RelationDataToClient>::iterator iter = m_mapFriendInfo.begin();
	for( ; iter != m_mapFriendInfo.end(); ++iter)
	{
		if(0 == strcmp(iter->second.GetName() ,szName))
		{
			if (iter->second.HaveRelation(RelationDefine::Friend))
				return true;
		}
	}
	return false;
	unguard;

}

bool CPlayerRole::IsTempFriend( const char* szName )
{
	guardfunc;
	std::map<int, RelationDataToClient>::iterator iter = m_mapFriendInfo.begin();
	for( ; iter != m_mapFriendInfo.end(); ++iter)
	{
		if(0 == strcmp(iter->second.GetName() ,szName))
		{
			if (iter->second.HaveRelation(RelationDefine::TempFriend))
				return true;
		}
	}
	return false;
	unguard;

}

bool CPlayerRole::CanAddFriend( const char* szName )
{
	guardfunc;
	std::map<int, RelationDataToClient>::iterator iter = m_mapFriendInfo.begin();
	for( ; iter != m_mapFriendInfo.end(); ++iter)
	{
		if (/*iter->second.HaveRelation(RelationDefine::BlackList) ||*/ iter->second.HaveRelation(RelationDefine::Friend) ||iter->second.HaveRelation(RelationDefine::Vendetta))
		{
			if(0 == strcmp(iter->second.GetName() ,szName))
			{
				return false;
			}
		}
	}
	return true;
	unguard;
}

bool CPlayerRole::isFrdInBlackList( uint32 nDBId )
{
    guardfunc;
    std::map<int, RelationDataToClient>::iterator iter = m_mapFriendInfo.begin();
    for( ; iter != m_mapFriendInfo.end(); ++iter)
    {
        if(iter->second.GetID() == nDBId)
        {
            if( iter->second.HaveRelation(RelationDefine::BlackList))
                return true;
        }
    }
    return false;
    unguard;
}

bool CPlayerRole::isChouRen( const char* name )
{
	guardfunc;
	if( NULL == name )
		return false;

	std::map<int, RelationDataToClient>::iterator iter = m_mapFriendInfo.begin();
	for( ; iter != m_mapFriendInfo.end(); ++iter)
	{
		if(0 == strcmp(iter->second.GetName() ,name))
		{
			if( iter->second.HaveRelation(RelationDefine::Vendetta))
				return true;
		}
	}
	return false;
	unguard;

}

const char* CPlayerRole::GetMarryerName()
{
    std::map<int, RelationDataToClient>::iterator iter = m_mapFriendInfo.begin();
    for( ; iter != m_mapFriendInfo.end(); ++iter)
    {
        if(iter->second.HaveRelation(RelationDefine::Marriage))
            return iter->second.GetName();
    }
    return NULL;
}

void CPlayerRole::OnA2CUpdateFriendInfo(Msg *pMsg)
{
	guardfunc;
	MsgUpdateRelationAck	*pFri = (MsgUpdateRelationAck*)pMsg;

	if( pFri->ustCount <= 0 || pFri->ustCount > 100 )
		return;

	RelationAttribute *pFrInfo = pFri->xAttribute;

	bool bHasTeacherStudent = false;
	std::map<int, RelationDataToClient>::iterator iter;
	for( int i=0; i<pFri->ustCount; ++i,++pFrInfo )
	{
		iter = m_mapFriendInfo.find(pFrInfo->GetID());
		if( iter != m_mapFriendInfo.end() )
		{
			iter->second.SetRelationAttribute(*pFrInfo);

			if( iter->second.HaveRelation(RelationDefine::Teacher) || iter->second.HaveRelation(RelationDefine::Student) )
				bHasTeacherStudent = true;
		}
	}

	s_CUI_ID_FRAME_Friend.NeedRefresh();
	if( bHasTeacherStudent )
		s_CUI_ID_FRAME_Master.NeedRefresh();

	unguard;
}

void CPlayerRole::OnA2CUpdateLockInfo(Msg *pMsg_)
{
	guardfunc;
	MsgRelationLockStatus* pMsg = (MsgRelationLockStatus*)pMsg_;
	std::map<int, RelationDataToClient>::iterator iter;
	iter = m_mapFriendInfo.find(pMsg->nPlayerID);
	if (iter != m_mapFriendInfo.end())
	{
		iter->second.SetLocked(pMsg->bLocked);	
	}
	unguard;
}

void CPlayerRole::OnUpdateFriendly(Msg *pMsg)
{
	guardfunc;

	MsgUpdateFriendly *pFri = (MsgUpdateFriendly*)pMsg;

	std::map<int, RelationDataToClient>::iterator iter;

	iter = m_mapFriendInfo.find( pFri->nPlayerID );
	if( iter != m_mapFriendInfo.end() )
	{
		uint32 oldfriendly = iter->second.GetFriendly();
		int friendlyUp = pFri->nFriendly - oldfriendly;
		iter->second.SetFriendly( pFri->nFriendly );

		char cTmp[256] ={0};
		
		MeSprintf_s( cTmp, sizeof(cTmp)-1, theXmlString.GetString(eText_FriendPointUp), iter->second.GetName(), friendlyUp );

		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Exploit_Change, cTmp );

		// 加亲密度特效
		if( gCfg.m_bPlayFriendPointEffect && gCfg.m_strFriendPointEffect.length() > 0 && theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->GetMe() )
		{
			PlayEffect((char*)gCfg.m_strFriendPointEffect.c_str(), theHeroGame.GetPlayerMgr()->GetMe());
			// 好友播特效
			CPlayer* pFriendPlayer = theHeroGame.GetPlayerMgr()->FindPlayerByCharacterID( pFri->nPlayerID );
			if( pFriendPlayer )
			{
				PlayEffect((char*)gCfg.m_strFriendPointEffect.c_str(), pFriendPlayer);
			}
		}

		int old_level = theRelationConfig.GetFriendLevel(oldfriendly);
		int new_level = theRelationConfig.GetFriendLevel(pFri->nFriendly);

		// 记录亲密度等级
		if( old_level != 0 )
		{
			if( old_level < new_level )
			{
				// 亲密度升级，播特效
				if( gCfg.m_bPlayFriendUpgradeEffect && gCfg.m_strFriendUpgradeEffect.length() > 0 && theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->GetMe() )
				{
					PlayEffect((char*)gCfg.m_strFriendUpgradeEffect.c_str(), theHeroGame.GetPlayerMgr()->GetMe());
					// 好友播特效
					CPlayer* pFriendPlayer = theHeroGame.GetPlayerMgr()->FindPlayerByCharacterID( pFri->nPlayerID );
					if( pFriendPlayer )
					{
						PlayEffect((char*)gCfg.m_strFriendUpgradeEffect.c_str(), pFriendPlayer);
					}
				}
			}
		}
	}

	s_CUI_ID_FRAME_Friend.NeedRefresh();
	unguard;
}


void CPlayerRole::OnA2CFriendOutline(Msg *pMsg)
{
	guardfunc;
	MsgFriendOutLine *pFri = (MsgFriendOutLine*)pMsg;

	std::map<int, RelationDataToClient>::iterator iter = m_mapFriendInfo.find(pFri->nPlayerID);
	if( iter != m_mapFriendInfo.end() )
	{
		(iter->second).SetOnLine(false);

		char szText[256] = {0};
		if (iter->second.HaveRelation(RelationDefine::Vendetta))//仇人			
		{
			MeSprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_ChouRenCutDownLine), iter->second.GetName());
		}
		else if( iter->second.HaveRelation(RelationDefine::Teacher) )	// 师傅
		{
			MeSprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_TeacherOffline), iter->second.GetName());
		}
		else if( iter->second.HaveRelation(RelationDefine::Student) )	// 徒弟
		{
			MeSprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_StudentOffline), iter->second.GetName());
		}
		else if( iter->second.HaveRelation(RelationDefine::Marriage) )	// 夫妻
		{
			if( GetSex() == Sex_Male )
				MeSprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_WifeOffline), iter->second.GetName() );
			else
				MeSprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_HusbandOffline), iter->second.GetName() );
		}
		else // 好友
			MeSprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_FriCutDownLine), iter->second.GetName());

		if (!(iter->second.HaveRelation(RelationDefine::BlackList)))
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, szText );

		s_CUI_ID_FRAME_Friend.NeedRefresh();
		if( iter->second.HaveRelation(RelationDefine::Teacher) || iter->second.HaveRelation(RelationDefine::Student) )
			s_CUI_ID_FRAME_Master.NeedRefresh();
	}
	unguard;
}
void CPlayerRole::OnA2CFriendOnline(Msg *pMsg)
{
	guardfunc;
	MsgFriendOnline *pFrInfo = (MsgFriendOnline*)pMsg;

	std::map<int, RelationDataToClient>::iterator iter = m_mapFriendInfo.find( pFrInfo->nPlayerID );
	if( iter != m_mapFriendInfo.end() )
	{
		iter->second.SetOnLine(true);
		
		char szChar[256] = {0};
		if( !( ( iter->second.HaveRelation(RelationDefine::BlackList)) || (iter->second.HaveRelation(RelationDefine::Vendetta))) )//好友
		{
			if( iter->second.HaveRelation(RelationDefine::Teacher) )		// 师傅
			{
				MeSprintf_s( szChar, sizeof(szChar)-1, theXmlString.GetString(eText_TeacherOnline), iter->second.GetName() );
			}
			else if( iter->second.HaveRelation(RelationDefine::Student) )	// 徒弟
			{
				MeSprintf_s( szChar, sizeof(szChar)-1, theXmlString.GetString(eText_StudentOnline), iter->second.GetName() );
			}
			else if( iter->second.HaveRelation(RelationDefine::Marriage) )	// 夫妻
			{
				if( GetSex() == Sex_Male )
					MeSprintf_s( szChar, sizeof(szChar)-1, theXmlString.GetString(eText_WifeOnline), iter->second.GetName() );
				else
					MeSprintf_s( szChar, sizeof(szChar)-1, theXmlString.GetString(eText_HusbandOnline), iter->second.GetName() );
			}
			else											// 好友
			{
				// 好友上线声音
				PlaySoundConfig( SoundConfig::EST_FriendOnline );
				_sntprintf( szChar, sizeof(szChar)-1, theXmlString.GetString(eClient_Frddlg_SomePersonOnline), theXmlString.GetString( eText_Friend ),
					iter->second.GetName() );
			}
		}
		else if( iter->second.HaveRelation(RelationDefine::Vendetta))
		{
			_sntprintf( szChar, sizeof(szChar)-1, theXmlString.GetString(eClient_Frddlg_SomePersonOnline), theXmlString.GetString( eText_Chouren ),
				iter->second.GetName() );
		}
		else
		{
			_sntprintf( szChar, sizeof(szChar)-1, theXmlString.GetString(eClient_Frddlg_SomePersonOnline), "", iter->second.GetName() );
		}		

		if (!(iter->second.HaveRelation(RelationDefine::BlackList)) )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, szChar );
	
		s_CUI_ID_FRAME_Friend.NeedRefresh();
		if( iter->second.HaveRelation(RelationDefine::Teacher) || iter->second.HaveRelation(RelationDefine::Student) )
			s_CUI_ID_FRAME_Master.NeedRefresh();
	}
	unguard;
}
void CPlayerRole::OnA2CAddFriend(Msg* pMsg)//...关系信息提示
{
	guardfunc;
	MsgAddRelationAck *pFr = (MsgAddRelationAck*)pMsg;

    char szContent[128] = {0};

	switch(pFr->uchResult)
	{
	case RelationDefine::AddRelationSuccess:
		{
			if(pFr->xRelationData.GetID() < 0 || pFr->xRelationData.GetName()[0] == '\0')
				return;
			//之前关系 lrt
			bool IsInBlack = false;
			bool IsInVendetta = false;

			std::map<int, RelationDataToClient>::iterator pFoundIter = m_mapFriendInfo.find(pFr->xRelationData.GetID());
			if (pFoundIter != m_mapFriendInfo.end())
			{
				IsInBlack = (*pFoundIter).second.HaveRelation(RelationDefine::BlackList);
				IsInVendetta = (*pFoundIter).second.HaveRelation(RelationDefine::Vendetta);
				//lyh添加，黑名单加好友的时候，让好友进入本次需求的好友分组。
				if((*pFoundIter).second.HaveRelation(RelationDefine::BlackList))
				{
                 (*pFoundIter).second.SetGroupID(pFr->xRelationData.GetGroupID());
				}
				(*pFoundIter).second.AddRelation(pFr->xRelationData.GetRelation());	
                (*pFoundIter).second.SetFriendly(pFr->xRelationData.GetFriendly());
			}
			else
			{
				m_mapFriendInfo[pFr->xRelationData.GetID()] = pFr->xRelationData;
			}
			if ( pFr->xRelationData.HaveRelation(RelationDefine::BlackList) && 
				!pFr->xRelationData.HaveRelation(RelationDefine::Vendetta))
			{
				char szStr[256] = {0};
				MeSprintf_s( szStr, sizeof(szStr)-1, theXmlString.GetString(eClient_Frddlg_AddFriendToBlack), pFr->xRelationData.GetName());
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, szStr );
			}
			else if ( !pFr->xRelationData.HaveRelation(RelationDefine::BlackList) && 
				pFr->xRelationData.HaveRelation(RelationDefine::Vendetta) )
			{
				char szStr[256] = {0};
				MeSprintf_s( szStr, sizeof(szStr)-1, theXmlString.GetString(eClient_Frddlg_AddFriendBlackToVendetta), pFr->xRelationData.GetName());
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, szStr );
			}
			else if (pFr->xRelationData.HaveRelation(RelationDefine::Vendetta)/*&&pFr->xRelationData.HaveRelation(RelationDefine::BlackList)*/ && IsInBlack )
				      
			{
				char szStr[256] = {0};//lyh 黑名单加入仇人的提示
				MeSprintf_s( szStr, sizeof(szStr)-1, theXmlString.GetString(eClient_Frddlg_AddFriendBlackToVendetta), pFr->xRelationData.GetName());
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, szStr );
			}
			else if ( pFr->xRelationData.HaveRelation(RelationDefine::BlackList) && IsInVendetta )
			{
				char szStr[256] = {0};
				MeSprintf_s( szStr, sizeof(szStr)-1, theXmlString.GetString(eClient_Frddlg_AddFriendToBlack), pFr->xRelationData.GetName());
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, szStr );
			}
			else if ( pFr->xRelationData.HaveRelation(RelationDefine::Marriage) )
			{
                char szStr[256] = {0};
                MeSprintf_s( szStr, sizeof(szStr)-1, theXmlString.GetString(eText_MarrySuccess), GetName(),pFr->xRelationData.GetName());
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, szStr );
                s_CUI_ID_FRAME_BaseProperty.Refresh();
			}
			else if ( pFr->xRelationData.HaveRelation(RelationDefine::Brother) )
			{
			}
			else if ( pFr->xRelationData.HaveRelation(RelationDefine::Teacher) )	// 拜师成功
			{
				char szStr[256] = {0};
				MeSprintf_s( szStr, sizeof(szStr)-1, theXmlString.GetString(eText_InviteTeacherSucceed), pFr->xRelationData.GetName());
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szStr );
				CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_ShiTu_Belongs_Success, szStr );
				s_CUI_ID_FRAME_Master.NeedRefresh();
			}
			else if ( pFr->xRelationData.HaveRelation(RelationDefine::Master) )		// 自己出师成功，师傅成为Master关系
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_FinishGraduateTask) );
				s_CUI_ID_FRAME_Master.NeedRefresh();
			}
			else if ( pFr->xRelationData.HaveRelation(RelationDefine::Student) )	// 收徒成功
			{
				char szStr[256] = {0};
				MeSprintf_s( szStr, sizeof(szStr)-1, theXmlString.GetString(eText_InviteStudentSucceed), pFr->xRelationData.GetName());
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szStr );
				CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_ShiTu_Belongs_Success, szStr );
				s_CUI_ID_FRAME_Master.NeedRefresh();
			}
			else if ( pFr->xRelationData.HaveRelation(RelationDefine::Prentice) )	// 徒弟出师成功，徒弟成为Prentice关系
			{
				char szStr[256] = {0};
				MeSprintf_s( szStr, sizeof(szStr)-1, theXmlString.GetString(eText_StudentGraduate), pFr->xRelationData.GetName());
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szStr );
				s_CUI_ID_FRAME_Master.NeedRefresh();
			}
			else if ( pFr->xRelationData.HaveRelation(RelationDefine::Friend) )
			{
				char szStr[256] = {0};
				MeSprintf_s( szStr, sizeof(szStr)-1, theXmlString.GetString(eClient_Frddlg_AddSomePerson), pFr->xRelationData.GetName());
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, szStr );
			}
		}
		break;
	case RelationDefine::NotOnLine:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eText_FriOutLine) );
			return;
		}
		break;
	case RelationDefine::TargetNotAgree:
		{
			if ( pFr->xRelationData.HaveRelation(RelationDefine::Marriage) )		// 结婚被拒
			{
				MeSprintf_s( szContent, sizeof(szContent)-1, theXmlString.GetString(eText_RefuseMarry), pFr->xRelationData.GetName());
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, szContent );
			}
			else if ( pFr->xRelationData.HaveRelation(RelationDefine::Teacher) )	// 拜师被拒
			{
				MeSprintf_s( szContent, sizeof(szContent)-1, theXmlString.GetString(eText_RefuseAddTeacher), pFr->xRelationData.GetName());
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szContent );
			}
			else if ( pFr->xRelationData.HaveRelation(RelationDefine::Student) )	// 收徒被拒
			{
				MeSprintf_s( szContent, sizeof(szContent)-1, theXmlString.GetString(eText_RefuseAddStudent), pFr->xRelationData.GetName());
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szContent );
			}
			else													// 加好友被拒
			{
				MeSprintf_s( szContent, sizeof(szContent)-1, theXmlString.GetString(eTellClient_RefuseAddFriend), pFr->xRelationData.GetName());
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, szContent );
			}
			return;
		}
		break;
	case RelationDefine::RelationFull:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eText_AddFriendFailed_SelfFull) );
		}
		break;
	case RelationDefine::TargetRelationFull:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eText_AddFriendFailed_OtherFull) );
		}
		break;
	case RelationDefine::MustBeFriendRelation:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eText_ShouldBeFriendFirst) );
		}
		break;
	case RelationDefine::AlreadyHaveRelation:
		{
			if(pFr->xRelationData.HaveRelation(RelationDefine::BlackList))
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eText_AddFriAlreadyInBlackList) );
				return;
			}
			else if(pFr->xRelationData.HaveRelation(RelationDefine::Friend))
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eClient_AddFriInFriendList) );
				return;
			}
			else if(pFr->xRelationData.HaveRelation(RelationDefine::Teacher))
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eText_IsAlreadyYourTeacher) );
				return;
			}
			else if(pFr->xRelationData.HaveRelation(RelationDefine::Student))
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eText_IsAlreadyYourStudent) );
				return;
			}
		}
		break;
	case RelationDefine::CanNotAddRelation:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eText_AddRelationFailed) );
		}
		break;
	case RelationDefine::CanNotReceivePrentice:        // 还没有师门不能招收徒弟
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_CannotBeTeacher) );
		}
		break;
	case RelationDefine::TargetCanNotReceivePrentice:  // 对方还没有师门不能招收徒弟
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_OtherCannotBeTeacher) );
		}
		break;
	case RelationDefine::StudentCountLimit:      // 当前徒弟数量已经达到最大值
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_BeyondStudentMax) );
		}
		break;
	case RelationDefine::TargetStudentCountLimit: // 对方 当前徒弟数量已经达到最大值
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_OtherBeyondStudentMax) );
		}
		break;
	case RelationDefine::AlreadyHaveTeacher: // 已经有师傅了
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_CanHaveOneTeacher) );
		}
		break;
	case RelationDefine::TargetAlreadyHaveTeacher: // 对方已经有师傅了
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_OtherHasTeacher) );
		}
		break;
	case RelationDefine::AddStudentTimeLimit:				//一天只能收三个徒弟
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_AddStudentNumLimit) );
		}
		break;
	case RelationDefine::AddTeacherTimeLimit:				//一天只能拜师一次
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_AddTeacherNumLimit) );
		}
		break;
	case RelationDefine::TargetAddStudentTimeLimit:		//对方今日收徒数量到达上限
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_TargetAddStudentLimit) );
		}
		break;
	case RelationDefine::TargetAddTeacherTimeLimit:		//对方今日已拜过师
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_TargetAddTeacherLimit) );
			CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_ShiTu_Belongs_Failed, theXmlString.GetString(eText_TargetAddTeacherLimit) );
		}
		break;
	case RelationDefine::StudentMinLevelSpan: //师徒等级限制
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_TeacherAndStudentLevelDiff) );
			CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_ShiTu_Belongs_Failed, theXmlString.GetString(eText_TeacherAndStudentLevelDiff) );
		}
		break;
	case RelationDefine::MustSameCountry: //同一国家限制
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_MustBeSameCountry) );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ShiTu_Belongs_Failed, theXmlString.GetString(eText_MustBeSameCountry) );
		}
		break;
	case RelationDefine::NameError:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs,theXmlString.GetString(eFriend_Error_Name));
		}
		break;
	default:
		{
			return;
		}
	}

	s_CUI_ID_FRAME_Friend.NeedRefresh();
	unguard;
}
void CPlayerRole::OnA2CDelFriend(Msg *pMsg)
{
	guardfunc;
	MsgDeleteRaltionAck *pFr = (MsgDeleteRaltionAck*)pMsg;

	switch( pFr->nResult)
	{
	case MsgDeleteRaltionAck::ECD_Success:
		{
			std::map<int, RelationDataToClient>::iterator pFoundIter = m_mapFriendInfo.find(pFr->nPlayerID);
			if (pFoundIter != m_mapFriendInfo.end())
			{
				(*pFoundIter).second.RemoveRelation(pFr->stRelation);
				bool bEraseRelation = false;
				if( pFr->stRelation == RelationDefine::InitRelation || pFr->stRelation == RelationDefine::Friend)//lyh 删除的只是好友 则从m_mapFriendInfo中移除
				{
					m_mapFriendInfo.erase(pFr->nPlayerID);
					bEraseRelation = true;
				}
				else
				{
					(*pFoundIter).second.SetFriendly(pFr->stFriendly);
				}

				char szText[256] = {0};
				switch (pFr->stRelation)
				{
				case RelationDefine::Marriage:
					{
						MeSprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_MailRemoveMarriage), pFoundIter->second.GetName());					
					}
					break;
				case RelationDefine::Teacher:
					{
						MeSprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_LeaveTeacherStudent), pFoundIter->second.GetName());					
					}
					break;
				case RelationDefine::Student:
					{
						MeSprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_KickTeacherStudent), pFoundIter->second.GetName());
						s_CUI_ID_FRAME_Master.SetKickRelation(false);
						s_CUI_ID_FRAME_Master.NeedRefresh();
					}
					break;
				}
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szText );
			}

			s_CUI_ID_FRAME_Friend.NeedRefresh();
			s_CUI_ID_FRAME_BaseProperty.Refresh();
		}
		break;
	case MsgDeleteRaltionAck::ECD_NotHaveThisRelation:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs,theXmlString.GetString(eText_DelFriendFailed_NotExist) );
		break;
	case MsgDeleteRaltionAck::ECD_CanNotDelRelation:
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs,theXmlString.GetString(eText_DelFriendFailed_CannotDelete) );
		break;
	default:
		break;
	}
	// 清楚师徒主动脱离关系标记
	s_CUI_ID_FRAME_Master.SetKickRelation(false);
	unguard;
}


void CPlayerRole::OnA2CRelationAttribute( Msg* pMsg )
{
	guardfunc;
	MsgRelationAttribute *pFrList = (MsgRelationAttribute*)pMsg;
	if (pFrList->ustMessageRefuse == RelationDefine::Refuse_AllPlayer)
	{
		s_CUI_ID_FRAME_GameSet.SetRefuseAllMessage(true);
		s_CUI_ID_FRAME_GameSet.SetRefuseStrangerMessage(true);
	}
	else if(pFrList->ustMessageRefuse == RelationDefine::Refuse_Stranger)
	{
		s_CUI_ID_FRAME_GameSet.SetRefuseAllMessage(false);
		s_CUI_ID_FRAME_GameSet.SetRefuseStrangerMessage(true);
	}
	else
	{
		s_CUI_ID_FRAME_GameSet.SetRefuseAllMessage(false);
		s_CUI_ID_FRAME_GameSet.SetRefuseStrangerMessage(false);
	}
	SetSignature(pFrList->szSignature);
	memcpy_s(xGroup,sizeof(RelationGroup)*RelationDefine::GroupCount,pFrList->xGroup,sizeof(RelationGroup)*RelationDefine::GroupCount);
	unguard;

}

void CPlayerRole::OnA2CTellRelationGroup( Msg* pMsg )
{
	guardfunc;
	MsgTellRelationGroup *pFrList = (MsgTellRelationGroup*)pMsg;
	if (pFrList->uchGroupID < RelationDefine::GroupCount)
	{
		if (pFrList->szGroup[0] == '\0')
		{
			xGroup[pFrList->uchGroupID].ClearGroup();
			std::map<int, RelationDataToClient>::iterator itermap = thePlayerRole.GetMapFriendInfo().begin();
			for(; itermap != thePlayerRole.GetMapFriendInfo().end(); ++itermap)
			{
				if (itermap->second.GetGroupID() ==  pFrList->uchGroupID)
				{//分组删除后，组内好友进入默认分组
					itermap->second.SetGroupID(0);
				}
			}
		}
		else
		{
			xGroup[pFrList->uchGroupID].SetName(pFrList->szGroup);
		}
	}
	s_CUI_ID_FRAME_Friend.NeedRefresh();
	unguard;
}

void CPlayerRole::OnA2CRelationGroupChange( Msg* pMsg )
{
	guardfunc;
	MsgRelationGroupChangeAck *pFrList = (MsgRelationGroupChangeAck*)pMsg;
	std::map<int, RelationDataToClient>::iterator iter = m_mapFriendInfo.find(pFrList->nPlayerID);
	if (iter != m_mapFriendInfo.end())
	{
		iter->second.SetGroupID(pFrList->uchGroupID);
	}
	s_CUI_ID_FRAME_Friend.NeedRefresh();
	unguard;

}

void CPlayerRole::OnA2CGetFriendList(Msg* pMsg)
{
	guardfunc;
	MsgRelationList *pFrList = (MsgRelationList*)pMsg;
 	if (s_CUI_ID_FRAME_Friend.IsVisable())
 	{
		s_CUI_ID_FRAME_Friend.SetTextWait();
 	}
	
	GetSocial()->InitClanBuffer();
	RelationDataToClient *pFrInfo = (RelationDataToClient*)pFrList->xDataToClient;
    bool bNeedRefresh = false;
	bool bHasTeacherStudent = false;

	// 服务端一次最多发200个好友列表，所以会发多次，不能清除好友列表

	for(int i=0; i<pFrList->ustCount; i++, pFrInfo++)
	{
		RelationDataToClient info(*pFrInfo);
        if(pFrInfo->HaveRelation(RelationDefine::Marriage))
            bNeedRefresh = true;

		if( pFrInfo->HaveRelation(RelationDefine::Teacher) || pFrInfo->HaveRelation(RelationDefine::Student) )
			bHasTeacherStudent = true;

		m_mapFriendInfo[pFrInfo->GetID()] = info;
	}

    //有婚姻关系必须重新刷新，因为婚姻关系在称号之后发
    if(bNeedRefresh)
    {
        s_CUI_ID_FRAME_Title.NeedRefresh();

        if(theHeroGame.GetPlayerMgr()&&theHeroGame.GetPlayerMgr()->GetMe()
            &&theHeroGame.GetPlayerMgr()->GetMe()->GetTitleId()== 10000)
           {
               theHeroGame.GetPlayerMgr()->GetMe()->SetTitleInfoById(theHeroGame.GetPlayerMgr()->GetMe()->GetTitleId());
           }
    }
	s_CUI_ID_FRAME_Friend.NeedRefresh();
	s_CUI_ID_FRAME_BaseProperty.Refresh();
	if( bHasTeacherStudent )
		s_CUI_ID_FRAME_Master.NeedRefresh();
	GetSocial()->CallForRepute2Server();
	unguard;
}

bool CPlayerRole::CheckNewFriendName(const char* szName, bool onlyCheck)
{
	guardfunc;
	if(strcmp(thePlayerRole.GetName(), szName) == 0)
	{
		if(! onlyCheck )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eText_NoneAddMe) );
		return false;
	}

	std::map<int, RelationDataToClient>::iterator iter = m_mapFriendInfo.begin();

	for( ; iter != m_mapFriendInfo.end(); ++iter)
	{
		if(0 == strcmp(iter->second.GetName() ,szName))
		{
// 			if ( iter->second.HaveRelation(RelationDefine::BlackList))
// 			{
// 				if(! onlyCheck )
// 					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eText_AddFriInBlackList) );
// 				return false;
// 			}
//			else 
				if(iter->second.HaveRelation(RelationDefine::Friend))
			{
				if(! onlyCheck )
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eClient_AddFriInFriendList) );
				return false;
			}
			else if(iter->second.HaveRelation(RelationDefine::Vendetta))
			{
				if(! onlyCheck )
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eText_AddFriInVendettaList) );
				return false;
			}
			break;
		}
	}
	return true;
	unguard;
}
bool CPlayerRole::CheckNewBlackName( const char* szName )
{
	guardfunc;
	if(strcmp(thePlayerRole.GetName(), szName) == 0)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eText_NoneAddMe) );
		return false;
	}

	std::map<int, RelationDataToClient>::iterator iter = m_mapFriendInfo.begin();

	for( ; iter != m_mapFriendInfo.end(); ++iter)
	{
		if(0 == strcmp(iter->second.GetName() ,szName))
		{
			if ( iter->second.HaveRelation(RelationDefine::BlackList))
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eText_AddFriAlreadyInBlackList) );
				return false;
			}
			break;
		}
	}
	return true;
	unguard;

}

struct InviteFriendInfo
{
	int  dwReqID;
	int  stRelation;
	char szAckName[dr_MaxPlayerName];       // 被邀请人的名字
};

bool inviteAddFriendCallback( const char bPressYesButton, void *pData )
{
	guardfunc;
	if( pData )
	{
		InviteFriendInfo* info = (InviteFriendInfo*)pData;

		if (bPressYesButton == CUI_ID_FRAME_MessageBox::eTypeExternal)
		{
			MsgInviteRelationAck inRes;
			inRes.nReqID = info->dwReqID;
			inRes.bAgree = false;
			inRes.stRelation = info->stRelation;
			/*strcpy(inRes.szAckName,info->szAckName);*/
			GettheNetworkInput().SendMsg( &inRes );
			s_CUI_ID_FRAME_AddFriend.sendMsgAddFriend( info->szAckName,RelationDefine::BlackList,-1 );
		}
		else
		{
			MsgInviteRelationAck inRes;
			inRes.nReqID = info->dwReqID;
			inRes.bAgree = bPressYesButton;
			inRes.stRelation = info->stRelation;
			/*strcpy(inRes.szAckName,info->szAckName);*/
			GettheNetworkInput().SendMsg( &inRes );
		}
	}

	return true;
	unguard;
}

void CPlayerRole::OnInviteAddRelation( Msg *pMsg )
{
	MsgInviteRelationReq* pAddRelation = (MsgInviteRelationReq*)pMsg;
    InviteFriendInfo info;
    info.dwReqID = pAddRelation->dwReqID;
    info.stRelation = pAddRelation->stRelation;
    strcpy(info.szAckName,pAddRelation->szReqName);

	if (RelationDataToClient::HaveRelation(pAddRelation->stRelation, RelationDefine::Friend))
	{
		// 判断是否拒绝添加好友
		bool bInFight = false;
		if( theHeroGame.GetPlayerMgr()->GetMe() )
			bInFight = theHeroGame.GetPlayerMgr()->GetMe()->HasFightFlag(eFighting);
		bool bRefuseInFight = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_RefuseAddFriendInFight );
		bool bRefuse = (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_RefuseAddFriend );
		if( (bInFight && bRefuseInFight) || (!bInFight && bRefuse) )
		{
			inviteAddFriendCallback(false, &info);
			return;
		}

		char szContent[256] = {0};
		MeSprintf_s( szContent, sizeof(szContent)/sizeof(char) - 1,theXmlString.GetString(eInviteAddFriend), pAddRelation->szReqName );
		s_CUI_ID_FRAME_MessageBox.Show( szContent, theXmlString.GetString(eInviteAddFriendCaption),
			CUI_ID_FRAME_MessageBox::eTypeYesNoExternal,
			false, inviteAddFriendCallback, &info, sizeof(InviteFriendInfo));
	}
    else if(RelationDataToClient::IsHigherRelation(pAddRelation->stRelation))  //如果为二级关系
    {        
        if(RelationDataToClient::HaveRelation(pAddRelation->stRelation, RelationDefine::Marriage))  //夫妻关系
        {
            char szContent[256];
            MeSprintf_s(szContent,sizeof(szContent)/sizeof(char) - 1,theXmlString.GetString(eText_MarryAskMarry),pAddRelation->szReqName);
            s_CUI_ID_FRAME_MessageBox.Show(szContent,theXmlString.GetString(eText_MarryAskMarryInfo),CUI_ID_FRAME_MessageBox::eTypeAcceptReject,
                false,inviteAddFriendCallback,&info,sizeof(InviteFriendInfo));
        }
        else if(RelationDataToClient::HaveRelation(pAddRelation->stRelation, RelationDefine::Brother)) //结拜关系
        {

        }
        else if(RelationDataToClient::HaveRelation(pAddRelation->stRelation, RelationDefine::Teacher)) //是否师傅
        {
			char szContent[256];
			MeSprintf_s(szContent,sizeof(szContent)/sizeof(char) - 1,theXmlString.GetString(eText_InviteYouAsTeacher),pAddRelation->szReqName);
			s_CUI_ID_FRAME_MessageBox.Show(szContent,"",CUI_ID_FRAME_MessageBox::eTypeAcceptReject,
				false,inviteAddFriendCallback,&info,sizeof(InviteFriendInfo));
        }
        else if(RelationDataToClient::HaveRelation(pAddRelation->stRelation, RelationDefine::Student))  //是否徒弟
        {
			char szContent[256];
			MeSprintf_s(szContent,sizeof(szContent)/sizeof(char) - 1,theXmlString.GetString(eText_InviteYouAsStudent),pAddRelation->szReqName);
			s_CUI_ID_FRAME_MessageBox.Show(szContent,"",CUI_ID_FRAME_MessageBox::eTypeAcceptReject,
				false,inviteAddFriendCallback,&info,sizeof(InviteFriendInfo));
        }
    }
}

const CPlayerRole::PlayerTeamSkillVector* CPlayerRole::GetTeamSkillVector()
{
	if( !IsTeamHeader() )
		return NULL;

	if( GetTeamMemberNum() < 6 )
		return NULL;

	if( m_pVecTeamSkill.size() == 0 )
		return NULL;
	
	return &m_pVecTeamSkill;
}

void CPlayerRole::CalcTeamSkillLevel()
{
	if( m_fCalcTeamSkillCD > 0 )
	{
		m_fCalcTeamSkillCD -= theHeroGame.GetFrameElapsedTime();
		if( m_fCalcTeamSkillCD > 0 )
			return;
	}

	m_fCalcTeamSkillCD = 2.f;

	// 重置小队技能等级
	m_pVecTeamSkill.clear();

	if( !IsTeamHeader() )
		return;

	if( GetTeamMemberNum() < 6 )
		return;

	if( !SwGlobal::GetWorld() || !SwGlobal::GetWorld()->GetWorldBuffer() )
		return;

	DWORD nMapId = GetGameMapId();

	// 在同张地图，统计队友亲密度
	DWORD dwMinFriendly[2] = {0,0};		// 记录最小的两个亲密度	
	short iMinFriendlyIndex[2] = {-1, -1};
	for( int n=0; n<m_TeamData.size(); n++ )
	{
		TeamInfo* pInfo = &m_TeamData[n];
		if( pInfo->nID == m_dwPlayerDBID )
			continue;
		
		if( pInfo->nMapID != nMapId )
			return;

		if( !pInfo->bOnline )
			return;

		std::map<int, RelationDataToClient>::iterator pFoundIter = m_mapFriendInfo.find(pInfo->nID);
		if (pFoundIter != m_mapFriendInfo.end())
		{
			// 非好友关系，则返回-1
			if( !pFoundIter->second.HaveRelation(RelationDefine::Friend) )
				return;

			if( dwMinFriendly[0] == 0 || dwMinFriendly[0] > pFoundIter->second.GetFriendly() )
			{
				dwMinFriendly[0] = pFoundIter->second.GetFriendly();
				iMinFriendlyIndex[0] = n;
			}
			else if( dwMinFriendly[1] == 0 || dwMinFriendly[1] > pFoundIter->second.GetFriendly() )
			{
				dwMinFriendly[1] = pFoundIter->second.GetFriendly();
				iMinFriendlyIndex[1] = n;
			}
		}
		else	// 没有关系，则返回
			return;
	}

	DWORD dwAvgFriendly = 0;
	for( int n=0; n<m_TeamData.size(); n++ )
	{
		TeamInfo* pInfo = &m_TeamData[n];
		if( pInfo->nID == m_dwPlayerDBID )
			continue;

		if( iMinFriendlyIndex[0] == n || iMinFriendlyIndex[1] == n )
			continue;

		std::map<int, RelationDataToClient>::iterator pFoundIter = m_mapFriendInfo.find(pInfo->nID);
		if (pFoundIter != m_mapFriendInfo.end())
		{
			dwAvgFriendly += pFoundIter->second.GetFriendly();
		}
	}
	dwAvgFriendly /= 3;

	//获取亲密度等级和小队技能
	if( dwAvgFriendly >= 0 )
	{
		unsigned char ucFriendLevel = theRelationConfig.GetFriendLevel(dwAvgFriendly);
		const RelationConfig::TeamSkillVector* pTeamSkillRet = theRelationConfig.GetTeamSkill(ucFriendLevel, GetProfession());
		if( pTeamSkillRet && (*pTeamSkillRet).size() > 0 )
		{
			for(int i=0; i<(*pTeamSkillRet).size(); ++i)
			{
				PlayerTeamSkill teamSkill;
				teamSkill.nSkillID = (*pTeamSkillRet)[i].GetSkillID();
				teamSkill.uchLevel = (*pTeamSkillRet)[i].GetSkillLevel();
				m_pVecTeamSkill.push_back(teamSkill);
			}
		}
	}
}

// 拜师
bool CPlayerRole::CanAddTeacher(GameObjectId playerID, bool bShowInfo)
{
	CPlayer* pTeacher = theHeroGame.GetPlayerMgr()->FindByID(playerID);
	if( !pTeacher || pTeacher->GetDistanceToRole() > ADD_TEACHER_STUDENT_MAX_DIST )
	{
		if( bShowInfo )
		{
			char szText[256] = {0};
			MeSprintf_s(szText, sizeof(szText)-1,"%s", theXmlString.GetString(eText_AddTeacherStudentMaxDist)/*, ADD_TEACHER_STUDENT_MAX_DIST*/);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs,szText );
		}
		return false;
	}

	return CanAddTeacher(pTeacher, bShowInfo);
}

bool CPlayerRole::CanAddTeacher( const char* szName, bool bShowInfo )
{
	if( !szName || szName[0] == '\0' )
		return false;

	CPlayer* pTeacher = theHeroGame.GetPlayerMgr()->FindByName(szName);
	if( !pTeacher || pTeacher->GetDistanceToRole() > ADD_TEACHER_STUDENT_MAX_DIST )
	{
		if( bShowInfo )
		{
			char szText[256] = {0};
			MeSprintf_s(szText, sizeof(szText)-1,"%s" ,theXmlString.GetString(eText_AddTeacherStudentMaxDist)/*, ADD_TEACHER_STUDENT_MAX_DIST*/);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szText );
		}
		return false;
	}

	return CanAddTeacher(pTeacher, bShowInfo);
}

bool CPlayerRole::CanAddTeacher(CPlayer* pTeacher, bool bShowInfo)
{
	if( !pTeacher )
		return false;

	// 等级判断
	// 自己等级大于等于10级
	/*if( GetLevel() < theRelationConfig.GetPrenticeLimit().GetMinLevel() )
	{
		if( bShowInfo )
		{
			char szText[256] = {0};
			MeSprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_StudentLevelLimit), theRelationConfig.GetPrenticeLimit().GetMinLevel());
			GetShowScreenText() ->AddInfo( szText, Color_Config.getColor( CC_Center_WarningErrorInfo ) );
			s_CUI_ID_FRAME_InfoList. AddInfo(szText, Color_Config.getColor( CC_SystemPromp ));
		}
		return false;
	}*/

	// 自己等级小于出师任务等级
	//if( GetLevel() >= theRelationConfig.GetPrenticeLimit().GetMaxLevel() )
	//{
	//	if( bShowInfo )
	//	{
	//		char szText[256] = {0};
	//		MeSprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_BeyondStudentLevelMax), theRelationConfig.GetPrenticeLimit().GetMaxLevel());
	//		GetShowScreenText() ->AddInfo( szText, Color_Config.getColor( CC_Center_WarningErrorInfo ) );
	//		s_CUI_ID_FRAME_InfoList. AddInfo(szText, Color_Config.getColor( CC_SystemPromp ));
	//	}
	//	return false;
	//}

	// 师父等级必须大于徒弟10级以上
	if( pTeacher->GetLevel() - GetLevel() <= theRelationConfig.GetPrenticeLimit().GetMinLevelSpan() )
	{
		if( bShowInfo )
		{
			char szText[256] = {0};
			MeSprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_TeacherStudentLevelBeyond), theRelationConfig.GetPrenticeLimit().GetMinLevelSpan());
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szText );
		}
		return false;
	}

	// 关系判断
	std::map<int, RelationDataToClient>::iterator iter = m_mapFriendInfo.begin();
	for( ; iter != m_mapFriendInfo.end(); ++iter)
	{
		if(0 == strcmp(iter->second.GetName(), pTeacher->GetName()))
		{
			break;
		}
	}

	// 不能为夫妻
	if( iter != m_mapFriendInfo.end() && iter->second.HaveRelation(RelationDefine::Marriage) )
	{
		if( bShowInfo )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_TeacherStudentCannotBeCouple) );
		}
		return false;
	}

	// 师徒个数判断
	bool bHasTeacher = false;
	int iHasStudentNum = 0;
	CalculateTeacherStudent(bHasTeacher, iHasStudentNum);
	// 徒弟只能有一个师父，徒弟不能有徒弟
	if( bHasTeacher || iHasStudentNum != 0 )
	{
		if( bShowInfo )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_CanHaveOneTeacher) );
		}
		return false;
	}

	// 已经创建师门，不能再拜师
	if( IsCanReceivePrentice() )
	{
		if( bShowInfo )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_CannotAddTeacher) );
		}
		return false;
	}

	return true;
}

// 收徒
bool CPlayerRole::CanAddStudent(GameObjectId playerID, bool bShowInfo)
{
	CPlayer* pStudent = theHeroGame.GetPlayerMgr()->FindByID(playerID);
	if( !pStudent || pStudent->GetDistanceToRole() > ADD_TEACHER_STUDENT_MAX_DIST )
	{
		if( bShowInfo )
		{
			char szText[256] = {0};
			MeSprintf_s(szText, sizeof(szText)-1,"%s", theXmlString.GetString(eText_AddTeacherStudentMaxDist)/*, ADD_TEACHER_STUDENT_MAX_DIST*/);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szText );
		}
		return false;
	}
	
	return CanAddStudent(pStudent, bShowInfo);
}

bool CPlayerRole::CanAddStudent( const char* szName, bool bShowInfo )
{
	if( !szName || szName[0] == '\0' )
		return false;

	CPlayer* pStudent = theHeroGame.GetPlayerMgr()->FindByName(szName);
	if( !pStudent || pStudent->GetDistanceToRole() > ADD_TEACHER_STUDENT_MAX_DIST )
	{
		if( bShowInfo )
		{
			char szText[256] = {0};
			MeSprintf_s(szText, sizeof(szText)-1,"%s" ,theXmlString.GetString(eText_AddTeacherStudentMaxDist)/*, ADD_TEACHER_STUDENT_MAX_DIST*/);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szText );
		}
		return false;
	}

	return CanAddStudent(pStudent, bShowInfo);
}

bool CPlayerRole::CanAddStudent(CPlayer* pStudent, bool bShowInfo)
{
	if( !pStudent )
		return false;

	// 等级判断
	// 徒弟等级大于等于10级
	/*if( pStudent->GetLevel() < theRelationConfig.GetPrenticeLimit().GetMinLevel() )
	{
		if( bShowInfo )
		{
			char szText[256] = {0};
			MeSprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_StudentLevelLimit), theRelationConfig.GetPrenticeLimit().GetMinLevel());
			GetShowScreenText() ->AddInfo( szText, Color_Config.getColor( CC_Center_WarningErrorInfo ) );
			s_CUI_ID_FRAME_InfoList. AddInfo(szText, Color_Config.getColor( CC_SystemPromp ));
		}
		return false;
	}*/

	// 师父等级必须大于徒弟10级以上
	if( GetLevel() - pStudent->GetLevel() <= theRelationConfig.GetPrenticeLimit().GetMinLevelSpan() )
	{
		if( bShowInfo )
		{
			char szText[256] = {0};
			MeSprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_TeacherStudentLevelBeyond), theRelationConfig.GetPrenticeLimit().GetMinLevelSpan());
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szText );
		}
		return false;
	}

	// 关系判断
	std::map<int, RelationDataToClient>::iterator iter = m_mapFriendInfo.begin();
	for( ; iter != m_mapFriendInfo.end(); ++iter)
	{
		if(0 == strcmp(iter->second.GetName(), pStudent->GetName()))
		{
			break;
		}
	}

	// 不能为夫妻
	if( iter != m_mapFriendInfo.end() && iter->second.HaveRelation(RelationDefine::Marriage) )
	{
		if( bShowInfo )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_TeacherStudentCannotBeCouple) );
		}
		return false;
	}

	// 未创建师门，不能收徒
	if( !IsCanReceivePrentice() )
	{
		if( bShowInfo )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_CannotBeTeacher) );
		}
		return false;
	}

	// 徒弟个数判断
	bool bHasTeacher = false;
	int iHasStudentNum = 0;
	CalculateTeacherStudent(bHasTeacher, iHasStudentNum);
	if( iHasStudentNum != 0 )
	{
		unsigned char ucMasterLevel = m_pBaseInfo->liveinfo.xMasterData.GetMasterLevel();
		const MasterInfo* pMasterInfo = theRelationConfig.GetMasterInfo(ucMasterLevel);
		if( pMasterInfo )
		{
			int iMaxStudentNum = pMasterInfo->GetRecruitCount();
			if( iHasStudentNum >= iMaxStudentNum )
			{
				if( bShowInfo )
				{
					char szText[256] = {0};
					MeSprintf_s(szText, sizeof(szText)/sizeof(char)-1, theXmlString.GetString(eText_BeyondStudentMax), iMaxStudentNum);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szText );
				}
				return false;
			}
		}
		else
		{
			assert(0&&"Friendly.config表获取不到师傅等级对应数据");
			return false;
		}
	}

	return true;
}

void CPlayerRole::CalculateTeacherStudent(bool& hasTeacher, int& iStudentNum)
{
	hasTeacher = false;
	iStudentNum = 0;

	// 计算是否有师傅，是否有徒弟，徒弟个数
	std::map<int, RelationDataToClient>::iterator iter;
	for(iter = m_mapFriendInfo.begin(); iter != m_mapFriendInfo.end(); ++iter)
	{
		if( iter->second.HaveRelation(RelationDefine::Teacher) )
			hasTeacher = true;
		else if( iter->second.HaveRelation(RelationDefine::Student) )
		{
			++iStudentNum;
		}
	}
}

bool CPlayerRole::IsCanReceivePrentice()
{
	/*if( m_pBaseInfo )
		return m_pBaseInfo->liveinfo.xMasterData.IsCanReceivePrentice();
	return false;*/
	return true;
}

void CPlayerRole::SetCanReceivePrentice()
{
	/*if( m_pBaseInfo )
		m_pBaseInfo->liveinfo.xMasterData.SetCanReceivePrentice(true);*/
}

void CPlayerRole::SetMasterLevel(unsigned char level)
{
	if( m_pBaseInfo )
		m_pBaseInfo->liveinfo.xMasterData.SetMasterLevel(level);
}

unsigned char CPlayerRole::GetMasterLevel()
{
	if( m_pBaseInfo )
		return m_pBaseInfo->liveinfo.xMasterData.GetMasterLevel();
	return 0;
}

DWORD CPlayerRole::GetMasterValue()
{
	if( m_pBaseInfo )
		return m_pBaseInfo->liveinfo.xMasterData.GetMasterValue();
	return 0;
}

void CPlayerRole::SetMasterValue( DWORD value )
{
	if( m_pBaseInfo )
		m_pBaseInfo->liveinfo.xMasterData.SetMasterValue(value);
}

void CPlayerRole::SetStudentExperience( DWORD exp )
{
	/*if( m_pBaseInfo )
		m_pBaseInfo->liveinfo.xMasterData.SetExperience(exp);*/
}

DWORD CPlayerRole::GetStudentExperience()
{
	/*if( m_pBaseInfo )
		return m_pBaseInfo->liveinfo.xMasterData.GetExperience();*/
	return 0;
}

const char* CPlayerRole::GetStudentNameById(unsigned int nId) const
{
	std::map<int, RelationDataToClient>::const_iterator iter = m_mapFriendInfo.find(nId);
	if (iter != m_mapFriendInfo.end())
	{
		return iter->second.GetName();
	}

	return NULL;
}

int CPlayerRole::GetTeacherDBID()
{
	std::map<int, RelationDataToClient>::iterator iter;
	for(iter = m_mapFriendInfo.begin(); iter != m_mapFriendInfo.end(); ++iter)
	{
		if( iter->second.HaveRelation(RelationDefine::Teacher) )
		{
			return iter->second.GetID();
		}
	}
	return -1;
}

bool  CPlayerRole::IsTeamBattleInMap()
{
    CWorldTile *pTile = CURRENTTILE;
    if(!pTile)
        return false;

    return (pTile->GetCanPk() == MapConfig::MapData::EPKM_Team_PK);
}

bool CPlayerRole::IsTeacher( const char* szName )
{
	guardfunc;
	std::map<int, RelationDataToClient>::iterator iter = m_mapFriendInfo.begin();
	for( ; iter != m_mapFriendInfo.end(); ++iter)
	{
		if(0 == strcmp(iter->second.GetName() ,szName))
		{
			if( (iter->second.HaveRelation(RelationDefine::Teacher)) )
				return true;
		}
	}
	return false;
	unguard;
}

bool CPlayerRole::IsStudent( const char* szName )
{
	guardfunc;
	std::map<int, RelationDataToClient>::iterator iter = m_mapFriendInfo.begin();
	for( ; iter != m_mapFriendInfo.end(); ++iter)
	{
		if(0 == strcmp(iter->second.GetName() ,szName))
		{
			if( (iter->second.HaveRelation(RelationDefine::Student)) )
				return true;
		}
	}
	return false;
	unguard;
}

void CPlayerRole::InitInfluence()
{
	m_nInfluence = CampDefine::NoneCamp;
	m_nRedCampResource = 0;
	m_nBlueCampResource = 0;
	InitCampData();
}

void CPlayerRole::InitCampData()
{
	m_nRedCampGuildId = GuildDefine::InitID;
	m_nBlueCampGuildId = GuildDefine::InitID;
}

void CPlayerRole::SetInfluence(int nValue)
{
	m_nInfluence = CampDefine::GetBaseFightCamp(nValue);
	m_nCampType = CampDefine::GetBattleTypeByCamp(nValue);
}

void CPlayerRole::StoreAllGuildInfo(int nNum, CGuildInfo* GuildInfoExArray)
{
	if (nNum == 0)
	{
		return;
	}

	/*m_nGuildNum = nNum;*/

	for (int i = 0; i < nNum; ++i)
	{
		m_vctGuild.push_back( GuildInfoExArray[i]);
	}

	s_CUI_ID_FRAME_GuildApply.SetNeedRefresh(true);
	s_CUI_ID_FRAME_AddGuildGeneralBattle.UpdateAllGuild();
}

void CPlayerRole::AddNewGuild(CGuildInfo& refNewGuild)
{
	for (int i = 0; i<m_vctGuild.size();i++)
	{
		if(m_vctGuild[i].GetID() == refNewGuild.GetID())
		{
			m_vctGuild[i] = refNewGuild;
			return;
		}
	}
	m_vctGuild.push_back(refNewGuild);
}

const CGuildInfo* CPlayerRole::GetGuildById(int nGuildId) const
{
	for (std::vector<CGuildInfo>::const_iterator iter = m_vctGuild.begin(); iter != m_vctGuild.end(); ++iter)
	{
		if (iter->GetID() == nGuildId)
		{
			return &(*iter);
		}
	}

	return NULL;
}

void CPlayerRole::ResetGuildData()
{
	m_GuildMgr.Clear();
	m_vctGuild.clear();
}

const char* CPlayerRole::GetGuildNameById(int nGuildId) const
{
	std::vector<CGuildInfo>::const_iterator iter = m_vctGuild.begin();
	for (; iter != m_vctGuild.end(); ++iter)
	{
		if (iter->GetID() == nGuildId)
		{
			return iter->GetName();
		}
	}
	
	return Empty_String_Value;
}

int CPlayerRole::GetGroupIndex( const char* pGroupName )
{
	if (NULL == pGroupName)
	{
		return -1;
	}
	for (int i = 0; i <  RelationDefine::GroupCount; ++i)
	{
		if (xGroup[i].IsEmpty())
		{
			continue;
		}
		if (0 == strcmp(xGroup[i].GetName(),pGroupName))
		{
			return i;
		}
	}
	return -1;
}
int CPlayerRole::GetValidFreeReliveCount()
{
	// 获得当前级别对应的可复活次数
	int nTotalReliveCount = 0;
	int nMyLevel = (int)GetData( TYPE_LEVEL );
	if( nMyLevel <= theCountryConfig.GetReliveSetting().GetLevelLimit() )
		nTotalReliveCount = theCountryConfig.GetReliveSetting().GetBeforeLevelLimit();
	else
		nTotalReliveCount = theCountryConfig.GetReliveSetting().GetAfterLevelLimit();

	int nCurrentReliveCount = (int)GetData( TYPE_FreeReliveCount );
	return max( 0, nTotalReliveCount - nCurrentReliveCount );
}

bool CPlayerRole::IsFinishedIntroduce( int id )
{
	if ( id >= 0 && id < MAX_GUIDE_COUNT )
	{
		int repTime = CIntroductionManager::Instance()->GetRepeatTime(id);
		if( m_charinfo.otherdataclient.guideVars[id] >= repTime )
		{
			return true;
		}
	}
	return false;
}

void CPlayerRole::SetFinishedIntroduce( int id )
{
	if ( id >= 0 && id < MAX_GUIDE_COUNT )
	{
		int repTime = CIntroductionManager::Instance()->GetRepeatTime(id);
		int curTime = m_charinfo.otherdataclient.guideVars[id];
		curTime ++;
		if ( curTime > repTime )	//如果指引次数超过当前操作次数，值将置成当前操作次数
		{
			curTime = repTime;
		}
		m_charinfo.otherdataclient.guideVars[id] = curTime;
		MsgUpdateGuideReq msg;
		msg.nGuidId = id;
		msg.nState = curTime;
		GettheNetworkInput().SendMsg(&msg);
	}
}

void CPlayerRole::RefreshTalkStates( int nQuestId, short stValue )
{
	if( !theQuestManager.IsQuestIdValid( nQuestId ) )
		return;

	SQuest* pQuest = theQuestManager.GetQuest( nQuestId );
	if( !pQuest )
		return;

	bool bFind = false;
	QuestTalkState kTalkState;
	for( int eP = QuestManager::HSTT_ToGain; eP < QuestManager::HSTT_Count; ++ eP )
	{
		// 该任务是否有任务对话
		if( !pQuest->HaveQuestTalk( eP ) )
			continue;

		kTalkState.SetQuestId( nQuestId );
		kTalkState.SetSawStates( eP, theQuestManager.IsHaveSaw( eP, stValue ) );
		bFind = true;
	}	
	if( !bFind )
		return;

	m_QuestTalkStates[nQuestId] = kTalkState;
}

bool CPlayerRole::GetTalkStates( int nQuestId, int nType )
{
	if( m_QuestTalkStates.find( nQuestId ) == m_QuestTalkStates.end() )
		return false;

	if( nType < 0 || nType >= QuestManager::HSTT_Count )
		return false;

	return m_QuestTalkStates[nQuestId].GetSawStates( nType );
}

int CPlayerRole::GetFriendGroupCount() const
{
	int counter = 0;
	for (int i = 0; i < RelationDefine::GroupCount; ++i)
	{
		if (!xGroup[i].IsEmpty())
			++counter;
	}
	return counter;
}

void CPlayerRole::SetSignature(const char* val) 
{ 
	if(NULL == val)
		return;

	strcpy_s(szSignature,RelationDefine::MaxSignLength,val); 
	CPlayer *me = theHeroGame.GetPlayerMgr()->GetMe();
	if(me)
	{
		me->SetSignature(val);
	}
}

uint8 CPlayerRole::GetPetIndexByName(const char* m_name)
{
	uint8 m_index = InvalidLogicNumber;
	for (int i = 0; i<ITEM_PET_MAXCOUNT; i++ )
	{
		if(strcmp(m_charinfo.ItemBagData.petItems[i].baseInfo.szName,m_name) == 0)
		{
			m_index = i ;
			return m_index;
		}
	}
	return m_index;
}

void CPlayerRole::SetTPHJRank(char value,int operType)
{
	switch (operType)
	{
	case EOT_Set:
		m_charinfo.baseinfo.liveinfo.TPHJRank = value;
		break;
	case EOT_Add:
		m_charinfo.baseinfo.liveinfo.TPHJRank += value;
		break;
	case EOT_Sub:
		m_charinfo.baseinfo.liveinfo.TPHJRank -= value;
		break;
	case EOT_Mul:
		m_charinfo.baseinfo.liveinfo.TPHJRank *= value;
		break;
	case EOT_Div:
		if (value!=0)
		{
			m_charinfo.baseinfo.liveinfo.TPHJRank /= value;
		}
		break;
	}
	if (m_charinfo.baseinfo.liveinfo.TPHJRank<0)
	{
		m_charinfo.baseinfo.liveinfo.TPHJRank=0;
	}
	s_CUI_ID_FRAME_TaiPingHuanJing.Refresh();
}

void CPlayerRole::SetPetUnactive()
{
	MsgChangePet msg;
	msg.ucOpType = MsgChangePet::EOT_UnActive;
	SPetItem* pet = GetActivedPet();
	if (!pet)
	{
		return;
	}
	msg.guid = pet->baseInfo.guid;
	msg.nIndex = GetPetIndex(pet->baseInfo.guid);
	msg.ucOpType = MsgChangePet::EOT_UnActive;
	GettheNetworkInput().SendMsg(&msg);
}

void CPlayerRole::SetHeroAddAttr(SCharHeroInfo heroAttr)
{
	SCharFightAttr &fightAttr = m_charinfo.baseinfo.baseProperty.fightAttr;
	fightAttr.hpMax.hero = heroAttr.hpMax;
	fightAttr.mpMax.hero = heroAttr.mpMax;
	fightAttr.attackPhysics.hero = heroAttr.attackPhysics;
	fightAttr.attackMagic.hero = heroAttr.attackMagic;
	fightAttr.defendPhysics.hero = heroAttr.defendPhysics;
	fightAttr.defendMagic.hero = heroAttr.defendMagic;
	fightAttr.attackSpeed.hero = heroAttr.attackSpeed;
	fightAttr.moveSpeed.hero = heroAttr.moveSpeed;
	fightAttr.hpRestore.hero = heroAttr.hpRestore;
	fightAttr.mpRestore.hero = heroAttr.mpRestore;
	fightAttr.exact.hero = heroAttr.exact;
	fightAttr.dodge.hero = heroAttr.dodge;
	fightAttr.critical.hero = heroAttr.critical;
	fightAttr.tenacity.hero = heroAttr.tenacity;
	fightAttr.criticalIntensity.hero = heroAttr.criticalIntensity;
	fightAttr.backStrike.hero = heroAttr.backStrike;
	fightAttr.backStrikeResist.hero	= heroAttr.backStrikeResist;
	fightAttr.breakStrike.hero = heroAttr.breakStrike;
	fightAttr.stabStrike.hero = heroAttr.stabStrike;
	fightAttr.elementStrike.hero = heroAttr.elementStrike;
	fightAttr.toxinStrike.hero = heroAttr.toxinStrike;
	fightAttr.spiritStrike.hero = heroAttr.spiritStrike;
	fightAttr.breakResist.hero = heroAttr.breakResist;
	fightAttr.stabResist.hero = heroAttr.stabResist;
	fightAttr.elementResist.hero = heroAttr.elementResist;
	fightAttr.toxinResist.hero = heroAttr.toxinResist;
	fightAttr.spiritResist.hero = heroAttr.spiritResist;
	ShowHeroAttrInfo();
}

void CPlayerRole::ShowHeroAttrInfo()
{
	SCharFightAttr fightAttr = m_charinfo.baseinfo.baseProperty.fightAttr;
	if (fightAttr.hpMax.hero>0)
	{
		CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_ListInfo_RandomTip,
			theXmlString.GetString(eText_ZhuJiangHpMaxAdd),int(fightAttr.hpMax.hero));
	}
	if (fightAttr.mpMax.hero>0)
	{
		CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_ListInfo_RandomTip,
			theXmlString.GetString(eText_ZhuJiangMpMaxAdd), int(fightAttr.mpMax.hero));
	}
	if (fightAttr.attackPhysics.hero>0)
	{
		CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_ListInfo_RandomTip,
			theXmlString.GetString(eText_ZhuJiangAttackPhysicsAdd),int(fightAttr.attackPhysics.hero));
	}
	if (fightAttr.defendPhysics.hero>0)
	{
		CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_ListInfo_RandomTip,
			theXmlString.GetString(eText_ZhuJiangAttackMagicAdd), int(fightAttr.defendPhysics.hero));
	}
	if (fightAttr.attackMagic.hero>0)
	{
		CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_ListInfo_RandomTip,
			theXmlString.GetString(eText_ZhuJiangDefendPhysicsAdd),int(fightAttr.attackMagic.hero));
	}
	if (fightAttr.defendMagic.hero>0)
	{
		CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_ListInfo_RandomTip,
			theXmlString.GetString(eText_ZhuJiangDefendMagicAdd), int(fightAttr.defendMagic.hero));
	}
	if (fightAttr.exact.hero>0)
	{
		CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_ListInfo_RandomTip,
			theXmlString.GetString(eText_ZhuJiangExactAdd),int(fightAttr.exact.hero));
	}
	if (fightAttr.dodge.hero>0)
	{
		CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_ListInfo_RandomTip,
			theXmlString.GetString(eText_ZhuJiangDodgeAdd), int(fightAttr.dodge.hero));
	}
	if (fightAttr.critical.hero>0)
	{
		CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_ListInfo_RandomTip,
			theXmlString.GetString(eText_ZhuJiangCriticalAdd),int(fightAttr.critical.hero));
	}
	if (fightAttr.tenacity.hero>0)
	{
		CScreenInfoManager::Instance()->ShowInfoByFormat( CScreenInfoManager::eType_ListInfo_RandomTip,
			theXmlString.GetString(eText_ZhuJiangTenacityAdd), int(fightAttr.tenacity.hero));
	}
}
void CPlayerRole::SetWeekKillSum(uint32 num)
{ 
	if(m_pBaseInfo)
		m_pBaseInfo->liveinfo.dwKillPlayerWeekSum = num;
}
void CPlayerRole::SetAllKillSum(uint32 num)
{ 
	if(m_pBaseInfo)
		m_pBaseInfo->liveinfo.dwKillPlayerSum = num;
}
uint32 CPlayerRole::GetWeekKillSum()
{
	if(m_pBaseInfo)
		return m_pBaseInfo->liveinfo.dwKillPlayerWeekSum;
	else
		return 0;
}
uint32 CPlayerRole::GetAllKillSum()
{
	if(m_pBaseInfo)
		return m_pBaseInfo->liveinfo.dwKillPlayerSum;
	else
		return 0;
}
int CGangMgr::GetGuildStrength()
{
	//获取自己公会的实力
	//1.获取总等级
	const GuildConfig::LevelSetting* pSetting = theGuildConfig.GetLevelSetting( GetGuildLevel() );
    if ( pSetting == NULL || pSetting->GetMaxCount() == 0 )
    { return 0; }
	unsigned int nTotalLevel = 0;
	std::vector<GuildMember*>::iterator Iter = m_vMember.begin();
	for(;Iter != m_vMember.end();++Iter)
	{
		GuildMember * pMember = *Iter;
		if(pMember)
			nTotalLevel += pMember->GetLevel();
	}
	const GuildConfig::StrengthSetting& xSetting = theGuildConfig.GetStrengthSetting();

	float fStrength = ( static_cast< float >( nTotalLevel ) / pSetting->GetMaxCount() ) * 
		( xSetting.GetBaseModulus() + static_cast< float >( GetGuildLevel() ) * xSetting.GetExtendModulus() );

	return static_cast< unsigned int >( fStrength );
}
void CPlayerRole::DelCountryOfficial()
{
	//辞去国家官职
	int CountryID = thePlayerRole.GetCountry();
	if(CountryID == CountryDefine::Country_Init)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Dismiss_Del_NonCountry ) );
		return;
	}
	else if(m_charinfo.baseinfo.liveinfo.uchPosition == CountryDefine::Right_None)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Dismiss_Del_Not ) );
		return;
	}
	else if(m_charinfo.baseinfo.liveinfo.uchPosition == CountryDefine::Position_King)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Dismiss_Del_King ) );
		return;
	}
	else if(m_charinfo.baseinfo.liveinfo.uchPosition == CountryDefine::Position_Queen)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Dismiss_Del_Queen ) );
		return;
	}
	//判断通过 发送命令
	MsgDelCountryOfficialReq msg;
	GettheNetworkInput().SendMsg( &msg );
}
void CPlayerRole::OnCloseShopAnCK()
{
	//关掉随身仓库 和随身商店
	if(!s_CUI_ID_FRAME_SHOP.IsRemoteClose())
	{
		if(s_CUI_ID_FRAME_SHOP.IsVisable())
		{
			s_CUI_ID_FRAME_SHOP.SetVisable(false);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_Bag_ShopMove));
		}
	}
	if(s_CUI_ID_FRAME_Storage.IsVisable() && !s_CUI_ID_FRAME_Storage.GetIsNpeStorage())
	{
		s_CUI_ID_FRAME_Storage.SetVisable(false);
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_Bag_CKMove));
	}
}
void CPlayerRole::SetFlyPosition(unsigned int MapID,float X,float Y,unsigned int Type)
{
	LogMapID = MapID;
	LogX = X;
	LogY = Y;
	EndTime = HQ_TimeGetTime() + 30000;
	LogType = Type;
}
void CPlayerRole::GetFlyPosition(unsigned int& MapID,float& X,float& Y)
{
	if(HQ_TimeGetTime() >= EndTime)
	{
		MapID = 0;
		X = 0;
		Y = 0;
	}
	else
	{
		MapID = LogMapID;
		X = LogX;
		Y = LogY;
	}
}