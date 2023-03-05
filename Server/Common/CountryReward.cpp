#include "CountryReward.h"
#include <algorithm>
#include "RapidXml/MeRapidXml.h"
#include "XmlStringLanguage.h"
#include "CountryDefine.h"
#include "GamePlayer.h"
#include "ShareData.h"
#include "LogEventService.h"


CountryReward::CountryReward(void)
{
	_mapAddReward.clear();
	_mapSubReward.clear();
}

CountryReward::~CountryReward(void)
{

}

bool CountryReward::LoadCountryConfig( const char* szFile )
{
	if (szFile == NULL || szFile[0] == 0)
	{
		return false;
	}

	MeXmlDocument mKwameXmlDoc;
	if (!mKwameXmlDoc.LoadFile(szFile))
	{
		return false;
	}

	MeXmlElement* pRoot = mKwameXmlDoc.FirstChildElement("Project");
	if(pRoot == NULL)
	{
		return false;
	}

	MeXmlElement* pADD = pRoot->FirstChildElement("ADD");
	if (pADD == NULL)
	{
		return false;
	}
	int nAdd_Count = 0;
	if(pADD->Attribute("AddCount",&nAdd_Count) == NULL)
	{
		return false;
	}
	nAddCount = nAdd_Count;

	MeXmlElement* pPositions = pADD->FirstChildElement("Positions");
	if (pPositions == NULL)
	{
		return false;
	}
	int nID = 0;
	int nLevel = 0;
	int nMountID = 0;
	int nItemID = 0;
	while( pPositions != NULL)
	{
		CAddReward* pADDReward = new CAddReward;
		if (pPositions->Attribute("ID",&nID) == NULL)
		{
			pPositions = pPositions->NextSiblingElement("Positions");
			continue;
		}
		pADDReward->nPositionID = nID;

		MeXmlElement* pPosition = pPositions->FirstChildElement("Position");
		if (pPosition == NULL)
		{
			return false;
		}
		
		while (pPosition != NULL)
		{
			CReward pCReward ;

			if (pPosition->Attribute("Level",&nLevel) == NULL)
			{
				return false;
			}
			pCReward.SetLevel(nLevel);

			if (pPosition->Attribute("ItemID",&nItemID) == NULL)
			{
				return false;
			}
			pCReward.SetItemID(nItemID);

			//pADDReward->vecCRewardSetting.push_back(pCReward);
			pADDReward->vecCRewardSetting.push_back(pCReward);

			pPosition = pPosition->NextSiblingElement("Position");
		}
		_mapAddReward.insert(make_pair(pADDReward->nPositionID,pADDReward));
		pPositions = pPositions->NextSiblingElement("Positions");
	}

	MeXmlElement* pSUB = pRoot->FirstChildElement("SUB");
	if (pSUB == NULL)
	{
		return false;
	}

	int nSub_Count = 0;

	if (pSUB->Attribute("SubCount",&nSub_Count) == NULL)
	{
		return false;
	}
	nSubCount = nSub_Count;

	MeXmlElement* pSubPositions = pSUB->FirstChildElement("SubPositions");
	if (pSubPositions == NULL)
	{
		return false;
	}
	int nSubID = 0;
	int nSubLevel = 0;
	int nSubMountID = 0;
	int nSubItemID = 0;

	while(pSubPositions != NULL)
	{
		CSub* pCSub = new CSub;
		if (pSubPositions->Attribute("ID",&nSubID) == NULL)
		{
			pSubPositions = pSubPositions->NextSiblingElement("SubPositions");
			continue;
		}
		pCSub->nPosition = nSubID;

		MeXmlElement* pSubPosition = pSubPositions->FirstChildElement("SubPosition");
		if (pSubPosition == NULL)
		{
			return false;
		}

		while(pSubPosition != NULL)
		{
			CSubReward pCSubReward ;

			if (pSubPosition->Attribute("Level",&nSubLevel) == NULL)
			{
				return false;
			}
			pCSubReward.SetLevel(nSubLevel);

			if (pSubPosition->Attribute("MountID",&nSubMountID) == NULL)
			{
				return false;
			}
			pCSubReward.SetMountID(nSubMountID);

			if (pSubPosition->Attribute("ItemID",&nSubItemID) == NULL)
			{
				return false;
			}
			pCSubReward.SetItemID(nSubItemID);

			pCSub->_vecCSubReward.push_back(pCSubReward);
			pSubPosition = pSubPosition->NextSiblingElement("SubPosition");
		}
		_mapSubReward.insert(make_pair(pCSub->nPosition,pCSub));
		pSubPositions = pSubPositions->NextSiblingElement("SubPositions");
	}

	return true;
}



//zhuxincong 获得删除坐骑ID
int CountryReward::GetSubItemID(int nLevel,int nPosition)
{
	int nItemLevel = (nLevel/10)*10;
	const CSubReward* pSetting = GetItemByLevel( nItemLevel, nPosition);//坐骑等级是和玩家等级相对应的
	if(!pSetting)
		return 0;
	int nItemID = pSetting->GetItemID();
	return nItemID;
}
//zhuxincong 获得删除时装
int CountryReward::GetSubMountID(int nLevel,int nPosition)
{
	int nMountLevel = (nLevel/10)*10;
	const CSubReward* pSetting = GetItemByLevel(nMountLevel,nPosition);
	if(!pSetting)
		return 0;
	int nMountID = pSetting->GetMountID();
	return nMountID;
}

//删除物品
CountryReward::CSubReward* CountryReward::GetItemByLevel(unsigned int nLevel,int nPosition)
{
	mapSubReward::iterator itrSub = _mapSubReward.find(nPosition);
	if (itrSub == _mapSubReward.end())
	{
		return NULL;
	}
	
	vecCSubReward::iterator iter;
	for (iter = itrSub->second->_vecCSubReward.begin();iter != itrSub->second->_vecCSubReward.end();++iter)
	{
		if (iter->GetLevel() == nLevel)
		{
			return &(*iter);
		}
	}
	return NULL;
}


//根据坐骑等级获得坐骑
CountryReward::CReward* CountryReward::GetMountByLevel( unsigned int nLevel,int nPosition ) 
{
	mapAddReward::iterator itrAdd = _mapAddReward.find(nPosition);
	if (itrAdd == _mapAddReward.end() )
	{
		return NULL;
	}
	
	/*CRewardSettingVector::iterator itrReward = itrAdd->second.vecCRewardSetting;
	if (itrReward == itrReward = itrAdd->second.vecCRewardSetting.end())
	{
		return NULL
	}*/
	/*CRewardSettingVector::iterator iter = find( itrAdd->second->vecCRewardSetting.begin(), itrAdd->second->vecCRewardSetting.end(), nLevel );
	if ( iter == itrAdd->second->vecCRewardSetting.end() )
	{ return NULL; }

	 return *iter;*/
	CRewardSettingVector::iterator iter;  
	for (iter=itrAdd->second->vecCRewardSetting.begin();iter!=itrAdd->second->vecCRewardSetting.end();iter++)  
	{  
		if (iter->GetLevel() == nLevel)
		{
			return &(*iter);
		}
		  
	}  
	return NULL;
}


//得到物品的信息
int CountryReward::GetItemID(int nLevel,int nPosition)
{
	int nMountLevel = (nLevel/10)*10;
	const CReward* pSetting = GetMountByLevel( nMountLevel, nPosition);//坐骑等级是和玩家等级相对应的
	if(!pSetting)
		return 0;
	int nItemID = pSetting->GetItemID();
	return nItemID;
	//switch (nPosition)
	//{
	//	case CountryDefine::Position_King://国王
	//		nItemID = pSetting->SetItemID()
	//	break;
	//	
	//	case CountryDefine::Position_General://大将军
	//					
	//	break;
	//	
	//	case CountryDefine::Position_Queen://皇后
	//					
	//	break;
	//	
	//	case CountryDefine::Position_CouncilorLeft://左丞相

	//	break;
	//	
	//	case CountryDefine::Position_CouncilorRight://右丞相
	//				
	//	break;
	//	
	//	case CountryDefine::Position_CaptorLeft://左右侍郎
	//	case CountryDefine::Position_CaptorRight:
	//					
	//	break;
	//	
	//	default:
	//	
	//}
}

// zhuxincong 这个是没有用的。发送物品
bool CountryReward::SendCountryReward(const char* charPlayerName,int nPlayID,int nLevel,int nPosition )
{
	GS2CSSendMailReq xReq;
	xReq.charDbId = RelationDefine::InitID;

	xReq.mail.type  = SMail::EMT_System;
	xReq.mail.state = SMail::EMS_NotOpen;
	xReq.mail.sendTime = TimeEx::GetNowTime();        

	// 发信人
	xReq.mail.owners[EM_FromIndex].charDbId = 0;
	sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );

	// 收件人
	xReq.mail.owners[EM_ToIndex].charDbId = nPlayID;
	HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName, charPlayerName, sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );
	
	//内容
	sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_MailFamilyDisbanded ) );

	//标题
	sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_MailSystemTitle ) );
	
	//因为要发送两个物品第一个是坐骑，第二个是Item
	for (int i = 0; i < nAddCount; ++i)
	{
		//item
		if (i == 0)
		{
			// 判断等级, 领取坐骑( 玩家等级取整 )
			int nMountLevel = (nLevel/10)*10;
			const CReward* pSetting = GetMountByLevel( nMountLevel, nPosition);//坐骑等级是和玩家等级相对应的
			xReq.mail.accessory.type = 2;//2是坐骑
			switch (nPosition)
			{
			case CountryDefine::Position_King://国王
				//SCharItem* pCharItem = pItemBag->GetItemByID( pSetting->GetMountID() );
				//xReq.mail.accessory.content = pSetting->GetMountID();
				//SMountItem* pMountItem = _mountManager.GetMountByGuid( pSetting->GetMountID() );
				//SMountItem* pMountItem = _mountManager.GetMountByGuid( pChange->guid );
				//memcpy_s( xReq.mail.accessory.content, sizeof(xReq.mail.accessory.content), pMountItem, sizeof(SMountItem) );
				break;

			case CountryDefine::Position_General://大将军
				//xReq.mail.accessory.content = pSetting->GetMountID();
				break;

			case CountryDefine::Position_Queen://皇后
				//xReq.mail.accessory.content = pSetting->GetMountID();
				break;

			case CountryDefine::Position_CouncilorLeft://左丞相
				//xReq.mail.accessory.content = pSetting->GetMountID();
				break;

			case CountryDefine::Position_CouncilorRight://右丞相
				//xReq.mail.accessory.content = pSetting->GetMountID();
				break;

			case CountryDefine::Position_CaptorLeft://左右侍郎
			case CountryDefine::Position_CaptorRight:
				//xReq.mail.accessory.content = pSetting->GetMountID();
				break;

			default:
				return false;
			}
			//theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
		}

		if(i == 1)
		{
			// 判断等级, 领取坐骑( 玩家等级取整 )
			int nMountLevel = (nLevel/10)*10;
			const CReward* pSetting = GetMountByLevel( nMountLevel, nPosition);//坐骑等级是和玩家等级相对应的
			if (pSetting == NULL)
			{
				return false;
			}
			xReq.mail.accessory.type = 1;//2是坐骑,1是物品
			//xReq->mail.accessory.type =1;
			switch (nPosition)
			{
			case CountryDefine::Position_King://国王
				//xReq.mail.accessory.content[0] = pSetting->GetItemID();
				//xReq.mail.accessory.content = pSetting->GetItemID();
				break;

			case CountryDefine::Position_General://大将军
				//xReq.mail.accessory.content = pSetting->GetItemID();
				break;

			case CountryDefine::Position_Queen://皇后
				//xReq.mail.accessory.content = pSetting->GetItemID();
				break;

			case CountryDefine::Position_CouncilorLeft://左丞相
				//xReq.mail.accessory.content = pSetting->GetItemID();
				break;

			case CountryDefine::Position_CouncilorRight://右丞相
				//xReq.mail.accessory.content = pSetting->GetItemID();
				break;

			case CountryDefine::Position_CaptorLeft://左右侍郎
			case CountryDefine::Position_CaptorRight:
				//xReq.mail.accessory.content = pSetting->GetItemID();
				break;

			default:
				return false;
			}
		}
	}
}

bool CountryReward::BSubItemAndMount(int nPosition,int nPlayID)
{
	//根据玩家ID获得玩家的信息
	GamePlayer* player = theRunTimeData.GetGamePlayerByDBID(nPlayID);
	/*if (player != NULL)
	{
		return false;
	}*/
	if (player == NULL) return false;
	int nOldItemId = theCountryReward.GetSubItemID(player->GetLevel(),nPosition);
	int nOldMountID = theCountryReward.GetSubMountID(player->GetLevel(),nPosition);
	ItemDefine::SItemCommon* pOldItemCommon = GettheItemDetail().GetItemByID( nOldItemId);
	if (!pOldItemCommon)
	{
		return false;
	}
	//删除Item
	/*MsgRemoveItem msg;
	msg.ucItemBagType = 0;
	msg.ustItemID     = nOldItemId;
	msg.ustCount      = 1;
	GettheServer().SendMsgToSingle( &msg, player );*/
	//player->RemoveMountByGuid(nOldMountID);
	MsgRemoveItemByBagType msg;
	//直接删除指定类型的物品 包括 装备栏 仓库 背包
	//1.装备栏
	for( int i = 0; i< EEquipPartType_MaxEquitPart; ++i )
    {
        SCharItem* pSCharItem = player->GetVisualEquipItem(i);
        if ( pSCharItem == NULL )
        { continue; }
        if( pSCharItem->itembaseinfo.ustItemID == nOldItemId ) 
		{
			//获得装备位置后
			//删除指定位置的装备
			//pSCharItem->itembaseinfo.ustItemID  = InvalidLogicNumber;
			//pSCharItem->itembaseinfo.nOnlyInt   = InvalidLogicNumber;
			// ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( nOldItemId );
			//if ( NULL == pItemCommon || !pItemCommon->IsCanEquip() )
			//{ break; }
			//ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)pItemCommon;
			//if ( pItemCanEquip->skillId > 0 )
			//{ 
			//	player->ForgetSkill( pItemCanEquip->skillId, false ); 
			//}

			//msg.ucItemBagType = BT_EquipBag;//BT_StorageBag;
			//msg.ustItemID = nOldItemId;
			//msg.ucIndex = i;
			//GettheServer().SendMsgToSingle( &msg, player );
			player->UnEquipAndRemove(i);
			break;
		}
    }
	
	//2.判断仓库
	for(int i=0;i<STORAGE_ITEMGRID_MAX;++i)
	{
		SCharItem* pItem = &player->_StorageBag.stStorageItems[i];
		if(pItem->itembaseinfo.ustItemID == nOldItemId ) 
		{
			//在仓库找到物品 我们移除仓库物品
			pItem->itembaseinfo.ustItemID = InvalidLogicNumber;
            pItem->itembaseinfo.nOnlyInt  = 0;
			//同步到客户端
			msg.ucItemBagType = BT_StorageBag;
			msg.ustItemID = nOldItemId;
			msg.ucIndex = i;
			GettheServer().SendMsgToSingle( &msg, player );			
		}
	}
	
	//LYH日志添加
	ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(nOldItemId);
	SCharItem *_item = player->GetBagItemByGuid(player->GetItemGUIDByItemID(nOldItemId));
	if(_pitem && _item)
	theLogEventService.LogItemConsume(player->GetAccountID(),player->GetDBCharacterID(),nOldItemId,1,player->GetItemGUIDByItemID(nOldItemId),
	_item->GetItemCount()-1>=0?_item->GetItemCount()-1:0,eItemLogInfo_ItemConsume_CountryPosition,
	                                 player->GetCharName(),_pitem->GetItemName());
	//3.判断背包
	player->RemoveItem(nOldItemId,0xffff);
	player->RemoveMountByid(nOldMountID,true);

	
	return true;
}