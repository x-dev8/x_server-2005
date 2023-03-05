#include "CountryReward.h"
#include <algorithm>
#include "RapidXml/MeRapidXml.h"
#include "MailManagerMain.h"
#include "XmlStringLanguage.h"
#include "CountryDefine.h"
#include "Guild.h"
#include "GuildManager.h"
#include "GameServerManager.h"
#include "CountryManager.h"
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


//发送物品
bool CountryReward::SendCountryReward(const char * szName,int nPlayID,int nLevel,int nPosition,SCharItem pItem)
{
	/*CenterGuild* pGuild = theCenterGuildManager.GetGuild( nGuidID );
	if ( pGuild == NULL)
	{ return false; }

	GuildMember* pMember = pGuild->GetMember( nPlayID  );
	if ( pMember == NULL )
	{ return false; }*/

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
	HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName, szName/*pMember->GetName()*/, sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );
	
	//根据不同的官职设置不同的标题和内容
	switch(nPosition)
	{
	case CountryDefine::Position_King:
		{
			//国王
			sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_CountryReward_Contentt_King ) );
			sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_CountryReward_Title_King ) );
		}
		break;
	case CountryDefine::Position_Queen:
		{
			for ( int i = CountryDefine::Country_Init + 1; i < CountryDefine::Country_Max; ++i )
			{
				CenterCountry * pCountry = theCenterCountryManager.GetCountry(i);
				if(pCountry && pCountry->IsRightPosition(nPosition,nPlayID))
				{
					OfficialInfo* pOff = pCountry->GetOfficial(nPosition);
					if(pOff)
					{
						//获取到职位
						if(pOff->GetSexID() == ESexType::Sex_Male)
						{
							//男性 为亲王
							sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_CountryReward_Contentt_QinWan ) );
							sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_CountryReward_Title_QinWan ) );
						}
						else if(pOff->GetSexID() == ESexType::Sex_Female)
						{
							//女性 为王后
							sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_CountryReward_Contentt_Queen ) );
							sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_CountryReward_Title_Queen ) );
						}
					}
				}
			}
		}
		break;
	case CountryDefine::Position_General:
		{
			sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_CountryReward_Contentt_General ) );
			sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_CountryReward_Title_General ) );
		}
		break;
	case CountryDefine::Position_CouncilorRight:
		{
			sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_CountryReward_Contentt_CouncilorRight ) );
			sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_CountryReward_Title_CouncilorRight ) );
		}
		break;
	case CountryDefine::Position_CouncilorLeft:
		{
			sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_CountryReward_Contentt_CouncilorLeft ) );
			sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_CountryReward_Title_CouncilorLeft ) );
		}
		break;
	case CountryDefine::Position_CaptorRight:
		{
			sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_CountryReward_Contentt_CaptorRight ) );
			sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_CountryReward_Title_CaptorRight ) );
		}
		break;
	case CountryDefine::Position_CaptorLeft:
		{
			sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_CountryReward_Contentt_CaptorLeft ) );
			sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_CountryReward_Title_CaptorLef ) );
		}
		break;
	}
	xReq.mail.accessory.type = SMail::EAT_Item;//2是坐骑,1是物品
	//xReq->mail.accessory.type =1;
	//SMountItem* pMountItem = _mountManager.GetMountByGuid( pChange->guid );
	//::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pSetting->GetItemID() );    
	memcpy( &xReq.mail.accessory.content,  &pItem, sizeof(SCharItem) ); 
	//memcpy(&xResult.CItem,&item,sizeof(SCharItem));
	theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
	return true;
}

int CountryReward::GetSubItemID(int nLevel,int nPosition)
{
	int nItemLevel = (nLevel/10)*10;
	const CSubReward* pSetting = GetItemByLevel( nItemLevel, nPosition);//坐骑等级是和玩家等级相对应的
	int nItemID = pSetting->GetItemID();
	return nItemID;
}
//zhuxincong 获得删除时装
int CountryReward::GetSubMountID(int nLevel,int nPosition)
{
	int nMountLevel = (nLevel/10)*10;
	const CSubReward* pSetting = GetItemByLevel(nMountLevel,nPosition);
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

bool CountryReward::BSubItemAndMount(int nPosition,int nPlayID)
{
	//zhuxincong 这里不能做就发一个消息到gamesever 去处理
	if (nPosition == 0 || nPlayID ==0)
	{
		return false;
	}
	
	S2SDleteCountryBattleReward pMessage ;
	pMessage.nPosition = nPosition;
	pMessage.nPlayerID = nPlayID;
	theGameServerManager.SendMsgToSingle( &pMessage, pMessage.nPlayerID);
	return true;
}