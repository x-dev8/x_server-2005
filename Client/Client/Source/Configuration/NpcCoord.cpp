//npc指引系统用的客户端信息及相关操作 画npc、怪物、物品 指引
#include "MeTerrain/stdafx.h"
#include "NpcCoord.h"
#include "include/MiniMap.h"
// #include "Tinyxml/tinyxml.h"
#include "SlkReader.h"
#include <algorithm>
#include "FuncPerformanceLog.h"
#include "NpcInfo.h"
#include "PositionInfo.h"
#include "ItemDetail.h"
#include "logmgr.h"
#include "CrossMapPF.h"
#include "Cfg.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "QuestData.h"
#include "QuestManager.h"
#include "MeUi/UiParseData.h"
#include "core/Name.h"
#include "XmlStringLanguage.h"
#include "Common.h"
#include "ScreenInfoManager.h"
#include "QuestDefine.h"
#include "Pet.h"

#define ERROR_INFO_LOG	"ErrorInfo.log"

#define NPC_PATH		"..\\Data\\Config\\Npc.config"
#define POSITION_PATH	"..\\Data\\Config\\Position.config"

#define LEN_HYBER	2

using namespace Common;

// struct SQuestCallbackData : public UiCallbackDataBase
// {
// 	SQuestCallbackData(void* pData){	m_nQuestId = -1;}
// 	~SQuestCallbackData(){}
// 	int m_nQuestId;
// 	virtual	void*		GetData() {return &m_nQuestId;}
// 	virtual int			GetType() {return eQuestId_UI_Callback;}
// };

struct SMapIdCallbackData : public UiCallbackDataBase
{
	SMapIdCallbackData(int nMapId){	m_nMapId = nMapId;}
	~SMapIdCallbackData(){}
	int m_nMapId;
	virtual	void*		GetData() {return &m_nMapId;}
	virtual int			GetType() {return eMapId_UI_Callback;}
};

NpcCoord::~NpcCoord()
{
	guardfunc;
	_CurHyberName.clear();
	_vecNpcCoord.clear();
	m_mapById.clear();
	m_mapByName.clear();
	unguard;
}
NpcCoord::FINDRESAULT_TYPE NpcCoord::checkNpcRepeat(const char* szNpcName, bool bigmap)
{
	guardfunc;
	if(_vecNpcCoord.empty())
		load();
	int repeat = 0;
	std::wstring wNpcName = _tstring::toWideString(szNpcName);
	for(int i=0; i<_vecNpcCoord.size(); ++i)
	{
		if (wNpcName == _vecNpcCoord[i]._szName)
		{
			++repeat;
		}
	}
	
	if(repeat == 0)
		return NONE;
	else if(repeat == 1)
		return ONE;
	else
		return REPEAT;
	unguard;
}

const NpcCoordInfo* NpcCoord::getNpcCoord( int nMapId,int nPFX,int nPFY )
{
	guardfunc;
	if(_vecNpcCoord.empty())
		load();
	{
		for(int i=0; i<_vecNpcCoord.size(); ++i)
		{
			const NpcCoordInfo* pInfo = &_vecNpcCoord[i];
			if (pInfo->_mapId == nMapId 
				&& abs(pInfo->_pfMapX - nPFX) < 1 
				&& abs(pInfo->_pfMapY - nPFY) < 1)
			{
				return pInfo;
			}
		}
	}
	return NULL;
	unguard;
}

const NpcCoordInfo*	NpcCoord::getNpcCoord(const char* szNpcName,int mapId)
{
	guardfunc;
	if (NULL == szNpcName)
	{
		return NULL;
	}
	if(_vecNpcCoord.empty())
		load();
	std::wstring wNpcName = _tstring::toWideString(szNpcName);
	CoordPairResultByName pairResult = m_mapByName.equal_range(wNpcName.c_str());
	if (( pairResult.first == m_mapByName.end( ) ) )
	{
		return NULL;
	}
	ItrCoordContainerByName it = pairResult.first;
	if (mapId == -1)
	{
		return it->second;
	}
	else
	{
		for ( ; it!=pairResult.second; ++it)
		{
			const NpcCoordInfo* pCoord = it->second;
			if ( !pCoord)
				continue;
			if( pCoord->_szName != wNpcName )
			{
				break;
			}
			if (pCoord->_mapId == mapId)
			{
				return pCoord;
			}
		}
	}
	return NULL;
	unguard;
}

const NpcCoordInfo* NpcCoord::getNpcCoord( int npcId ,int mapId)
{
	guardfunc;
	if (-1 == npcId)
	{
		return NULL;
	}
	if(_vecNpcCoord.empty())
		load();
	CoordPairResultById pairResult = m_mapById.equal_range(npcId);
	if (( pairResult.first == m_mapById.end( ) ) || ( pairResult.second == m_mapById.end( ) ))
	{
		return NULL;
	}
	ItrCoordContainerById it = pairResult.first;
	if (mapId == -1)
	{
		return it->second;
	}
	else
	{
		for ( ; it!=pairResult.second; ++it)
		{
			const NpcCoordInfo* pCoord = it->second;
			if ( !pCoord)
				continue;
			if( pCoord->_nID != npcId )
			{
				break;
			}
			if (pCoord->_mapId == mapId)
			{
				return pCoord;
			}
		}
	}
	return NULL;
	unguard;

}

std::vector<NpcCoordInfo>& NpcCoord::getNpcVec()
{
	guardfunc;
	if(_vecNpcCoord.empty())
		load();

	return _vecNpcCoord;
	unguard;
}
void NpcCoord::load()
{
	if (_initialized)
		return;

	if (NpcInfo::Instance().LoadConfig(NPC_PATH) != 0)
		return;
	if (PositionInfo::Instance().LoadConfig(POSITION_PATH) != 0)
		return;

	// 半身像
	m_bDialogPic = NpcInfo::Instance().IsDialogPic();

	NpcInfo::NpcsIter it,end = NpcInfo::Instance().npcs_.end();
	for (it = NpcInfo::Instance().npcs_.begin(); it != end; ++it)
	{
		NpcCoordInfo info;
		info._nID = it->second.id;				//npcID
		info._szName = _tstring::toWideString(it->second.name.c_str());			//npc名字
		info._szPinyin = it->second.pinyin;			//npc名字
		info._mapX = it->second.x;				//地图x坐标
		info._mapY = it->second.y;				//y坐标
		info._mapId = it->second.mapId;			//npc所在map
		info._nType = it->second.type;			//npcType	
		// modified jiayi, [2009/7/26]
		// 这里读的所有信息都是npc
		info._bNpc = true;						//用来区分是npc 还是 怪物 因为两个用的图片不一样
		info._bMask = it->second.isCollision;	//是否挡路
		info._title = it->second.title;         //称号
		info._scale = it->second.bodyScale;		//模型缩放
		info._modelId = it->second.modelId;		//模型ID
		info._worldShow = it->second.isWorldShow;//显示模型
        // 增加NPC等级 added by zhuomeng.hu		[11/8/2010]
        info._level = it->second.level;         //等级
		info.uchCountryID = it->second.uchCountryID;//国家
		info._miniShow = it->second.isMiniShow;
		PositionInfo::Position* pos = PositionInfo::Instance().GetPositionById(info._nID);
		if (pos)
		{
			info._bPFPossible = true;
			info._pfMapX = pos->x;		//地图x坐标
			info._pfMapY = pos->y;		//y坐标
			info._miniShow = pos->isShow;
		}
		else
		{
			info._bPFPossible = false;
			info._pfMapX = 0;		//地图x坐标
			info._pfMapY = 0;		//y坐标
		}
		_vecNpcCoord.push_back(info);
	}
	// added, jiayi, [2009/7/26]
	// 把monster信息全部写入_vecNpcCoord中，
	// 因为所有在position.config中的怪物都是
	// 可寻路
	for (int i = 0; i < GettheItemDetail().GetMonsterNumber();++i)
	{
		ItemDefine::SMonster* pMonster = GettheItemDetail().GetMonster( i );
		if (!pMonster)
		{
			continue;
		}
		PositionInfo::Position* pos = PositionInfo::Instance().GetPositionById(pMonster->stMonsterId);
		if (NULL == pos)
		{
			if(getNpcCoord(pMonster->GetName()))
			{//不可寻的怪只保留一份数据
				continue;
			}
		}
		NpcCoordInfo info;
		info._nID = pMonster->stMonsterId;				//npcID
		info._szName = _tstring::toWideString(pMonster->GetName());			//npc名字
		info._title = pMonster->GetTitle();         //称号
		info._scale = pMonster->fBodySize;		//模型缩放
		info._modelId = pMonster->iModelID;		//模型ID
		info._bNpc = false;						//用来区分是npc 还是 怪物 因为两个用的图片不一样
        // 增加等级     added by zhuomeng.hu		[11/8/2010]
        info._level = pMonster->stLevel;
		if (pos)
		{
			info._mapX = pos->x;				//地图x坐标
			info._mapY = pos->y;				//y坐标
			info._nType = pos->type;			//npcType	
			info._bMask = pos->isShow;					//是否显示
			info._mapId = pos->mapId;			//npc所在map
			info._bPFPossible = true;
			info._pfMapX = pos->x;		//地图x坐标
			info._pfMapY = pos->y;		//y坐标
			info._miniShow = pos->isShow;
			info._campType = pos->campType;
		}
		else
		{
			info._bPFPossible = false;
			info._pfMapX = 0;		//地图x坐标
			info._pfMapY = 0;		//y坐标

		}
		_vecNpcCoord.push_back(info);
	}

	//--这里 策划要求做个排序 排序的要求 按文字的长度。没有别的要求 
	sort(_vecNpcCoord.begin(), _vecNpcCoord.end(), lt_sort);

	for(int i = 0; i < _vecNpcCoord.size(); ++i)
	{
		const NpcCoordInfo* pInfo = &_vecNpcCoord[i];
		m_mapById.insert(CoordContainerById::value_type(pInfo->_nID,pInfo));
		m_mapByName.insert(CoordContainerByName::value_type(pInfo->_szName,pInfo));

	}
	_initialized = true;
}

bool NpcCoord::IsHalfChar( const char* pStr, unsigned int nOff )
{
	if ( !pStr )
	{
		return false;
	}
	int nLen = strlen( pStr );
	if ( nLen <= 0 )
	{
		return false;
	}
	for ( int n=0; n<nLen; )
	{
		if ( n > nOff )
		{
			return true;
		}
		else if ( n == nOff )
		{
			return false;
		}
		// 是汉字
		if ( pStr[n] & 0x80 )
		{
			n+=2;
		}
		else
		{
			n+=1;
		}
	}
	return false;
}

const std::string NpcCoord::FindFirstNpcName(const std::string& text)
{
	if(_vecNpcCoord.empty())
		load();

	for(int i=0; i<_vecNpcCoord.size(); ++i)
	{
		std::wstring wText = _tstring::toWideString(text.c_str());
		static  std::string narrowName;
		if (wText.find(_vecNpcCoord[i]._szName) != std::wstring::npos)
		{
			narrowName = _tstring::toNarrowString(_vecNpcCoord[i]._szName.c_str());
			return narrowName;
		}
// 		if (text.find(_vecNpcCoord[i]._szName) != std::string::npos)
// 			return _vecNpcCoord[i]._szName;
	}
	return "";
}
void NpcCoord::addNpcHyber(std::string& szString, const char* hyberLeft, const char* hyberRight,NpcCoordInfo** ppInfo )	//改变szString 如果有npc名字 加入超链接 {h.... h}
{
	guardfunc;
	if(_vecNpcCoord.empty())
		load();	

	int hl = strlen(hyberLeft);
	int hr = strlen(hyberRight);

	std::wstring wString = _tstring::toWideString(szString.c_str());
	
	size_t pos = 0;
	while(pos < wString.length())
	{
		size_t verifyPos = std::wstring::npos;
		int index = -1;
		for(int i=0; (i<_vecNpcCoord.size()); ++i)
		{
			size_t findPos = wString.find(_vecNpcCoord[i]._szName, pos);
			if (findPos != std::wstring::npos)
			{
				if (verifyPos == std::wstring::npos)
				{
					verifyPos = findPos;
					index = i;
				}
				else
				{
					if (findPos < verifyPos)
					{
						verifyPos = findPos;
						index = i;
					}
				}
			}
		}

		if (verifyPos == std::wstring::npos)
		{
			break;
		}
		size_t end = verifyPos + _vecNpcCoord[index]._szName.length();
		if (!_vecNpcCoord[index]._bPFPossible)
		{
			pos = end;
			continue;
		}

		wString.insert(verifyPos, _tstring::toWideString(hyberLeft).c_str());
		end += hl;
		wString.insert(end, _tstring::toWideString(hyberRight).c_str());

		szString = _tstring::toNarrowString(wString.c_str());
		pos = end + hr;
		if (ppInfo)
		{
			if (*ppInfo == NULL)
			{
				*ppInfo = (NpcCoordInfo*)/*getNpcCoordInPrimaryMap*/getNpcCoord(_vecNpcCoord[index]._nID);
			}
		}

	}
	unguard;
}


bool NpcCoord::clickHyberToMiniMapForText( const char* szData, UiCallbackDataBase* pBase /*= NULL*/ )
{
	bool bRet = false;
	if (pBase == NULL)
	{
		bRet = clickHyberToMiniMap(szData,-1);
	}
	else
	{
		assert(pBase->GetType() == eMapId_UI_Callback);
		SMapIdCallbackData* pMapIdData = (SMapIdCallbackData* )pBase;
		bRet = clickHyberToMiniMap(szData,pMapIdData->m_nMapId);		
	}
	return bRet;
}


bool NpcCoord::clickHyberToMiniMap(const NpcCoordInfo* pInfo )
{
	GetAdvancedMiniMap()->SetNpcInfo(pInfo );
	return GetAdvancedMiniMap()->MoveRoleToNPC();
}

bool NpcCoord::clickHyberToMiniMap(const char* szData,int mapId )//zhuxincong点击任务显示上的NPC 然后上马寻路
{
	guardfunc;
	
	float fXOff = 0;
	float fYOff = 0;
	float fDist = 0;

	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	
	PositionInfo::Position* pos = PositionInfo::Instance().GetPositionByName(szData);
	
	_CurHyberName = szData;

	std::string	strData = szData;//如果szData有 \n 的话 去掉它
	int enterPos = strData.find('\n');
	if(enterPos != -1)
		strData.erase(enterPos, 1);

	int dollarPos = strData.find('$');
	if (dollarPos != std::string::npos)
		strData = strData.substr(0, dollarPos);

 	const NpcCoordInfo *pNpcInfo = NULL;
 	NpcInfo::Npc* pInfo = theNpcInfo.GetNpcByName(strData, mapId);

	if(pInfo)
 	{

		fXOff = pInfo->x - pMe->GetPos().x;
		fYOff = pInfo->y - pMe->GetPos().y;
		fDist = sqrtf(fXOff*fXOff+fYOff*fYOff);//zhuxincong 距离不到50 不上马

		if (pos == NULL)
		{
			if (fDist>=50)
			{
				if (thePlayerRole.GetActivedMount())
				{
					if (!(theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsMounting()))//zhuxincong 8.2 2012 寻路上马，没有判断距离长度
					{
						// 压镖状态下寻路禁止上马
						if (!theHeroGame.GetPlayerMgr()->GetMe()->IsYabiaoState())
							s_CUI_ID_FRAME_Pet.Mount();
					}
				}
			}
		}
		else if (pos->needMount && fDist>=50)
		{
			if (thePlayerRole.GetActivedMount())
			{
				if (!(theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsMounting()))//zhuxincong 8.2 2012 寻路上马，没有判断距离长度
				{
					// 压镖状态下寻路禁止上马
					if (!theHeroGame.GetPlayerMgr()->GetMe()->IsYabiaoState())
						s_CUI_ID_FRAME_Pet.Mount();
				}
			}
		}

// 		std::vector<NpcInfo::Npc*> outResult;
// 		theNpcInfo.GetNpcs(pInfo->id,outResult);//多图
// 		CWorldTile* pCurrTile = CURRENTTILE;
// 		int nMinPathLength = 200000;
// 		int nMinPathIndex = -1;
// 		for (int i = 0; i < outResult.size();++i)
// 		{
// 			if (pCurrTile->GetMapId() == outResult[i]->mapId)
// 			{
// 				nMinPathIndex = i;
// 				break;			
// 			}
// 			else
// 			{
// 				int nPathLength = 200000;
// 				if (CrossMapPF::Instance()->CrossMapPathEvaluation(pCurrTile->GetMapId(),outResult[i]->mapId,nPathLength))
// 				{
// 					if (nPathLength < nMinPathLength)
// 					{
// 						nMinPathLength = nPathLength;
// 						nMinPathIndex = i;
// 					}
// 				}
// 			}
// 		}
// 		if (nMinPathIndex == -1)
// 		{
// 			return false;
// 		}
// 		pNpcInfo = getNpcCoord(strData.c_str(), outResult[nMinPathIndex]->mapId);
		if (mapId == -1)
		{
			CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
			int nMapIdInMyCountry = pInfo->mapId;
			if (pMe && nMapIdInMyCountry != -1)
			{
				nMapIdInMyCountry = gCfg.GetMyCountryMapId(pInfo->mapId,pMe->GetRealCountry());
			}
			pNpcInfo = getNpcCoord(strData.c_str(),nMapIdInMyCountry);
		}
		else
		{
			pNpcInfo = getNpcCoord(pInfo->id,mapId);//zhuxincong 9.4 原本第一个参数是strData.c_str() 其实这个函数是有重载的。
		}
 	}
	else
	{
		pNpcInfo =  getNpcCoord(strData.c_str());
	}
	return clickHyberToMiniMap(pNpcInfo);
	unguard;
}
const char*	NpcCoord::GetNpcName(int nID)
{
	guardfunc;
	for(int i=0; i<_vecNpcCoord.size(); ++i)
	{
		if( _vecNpcCoord[i]._nID == nID)
		{
			static std::string narrowStr;
			narrowStr = _tstring::toNarrowString(_vecNpcCoord[i]._szName.c_str());
			return narrowStr.c_str();
		}
	}

	return NULL;
	unguard;
}
bool NpcCoord::hasName( const char* name )
{
	guardfunc;
	std::wstring wText = _tstring::toWideString(name);
	for(int i=0; i<_vecNpcCoord.size(); ++i)
	{
		if(wText == _vecNpcCoord[i]._szName)
// 		if( strcmp(_vecNpcCoord[i]._szName.c_str(), name) == 0 )
			return true;
	}

	return false;
	unguard;
}

void NpcCoord::MarkNpcOnReachableMap( CWorldTile* pTile )
{
	for(int i=0; i<getNpcVec().size(); ++i)
	{
		NpcCoordInfo* pInfo = &getNpcVec()[i];
		if (pInfo->_bNpc && pInfo->_bMask && pInfo->_mapId == pTile->GetMapId())
		{
			pTile->MarkNPCPosOnReachableMap(pInfo->_mapX,pInfo->_mapY);
		}
	}
}

void NpcCoord::GetNpcListInMap( int mapId, std::vector<int>* pNpcList )
{
    if(_vecNpcCoord.empty())
        load();	

	if( _vecNpcCoord.size() )
	{
		for(UINT i=0; i<_vecNpcCoord.size(); i++)
		{
			if( _vecNpcCoord[i]._mapId == mapId && _vecNpcCoord[i]._modelId >= 0 )
			{
				if( pNpcList->size() <= 0 )
					pNpcList->push_back(_vecNpcCoord[i]._modelId);
				else
				{
					BOOL bFind = FALSE;
					for(UINT j=0; j<pNpcList->size(); j++)
					{
						if( (*pNpcList)[j] == _vecNpcCoord[i]._modelId )
						{
							bFind = TRUE;
							break;
						}
					}
					if( !bFind )
					{
						pNpcList->push_back(_vecNpcCoord[i]._modelId);
					}
				}
			}
		}
	}
}

const NpcCoordInfo* NpcCoord::getNpcCoordInCurrTile( int nNpcID )
{
	CWorldTile* pTile = CURRENTTILE;
	if (pTile)
	{
		return getNpcCoord(nNpcID,pTile->GetMapId());
	}
	return NULL;
}

const NpcCoordInfo* NpcCoord::getNpcCoordInPrimaryMap( const char* szNpcName )
{
	if (NULL == szNpcName)
	{
		return NULL;
	}
	if(_vecNpcCoord.empty())
		load();
	const NpcCoordInfo *pNpcInfo = getNpcCoord(szNpcName);
	if (pNpcInfo)
	{
		std::vector<NpcInfo::Npc*> outResult;
		theNpcInfo.GetNpcs(pNpcInfo->_nID,outResult);//多图
		if (outResult.size() > 0)
		{
			for (int i = 0; i < outResult.size(); ++i)
			{
				if (!gCfg.IsMirrorMapIds(outResult[i]->mapId))
				{
					pNpcInfo = NpcCoord::getInstance()->getNpcCoord(szNpcName,outResult[i]->mapId);
					break;
				}
			}
		}
	}
	return pNpcInfo;
}

const NpcCoordInfo* NpcCoord::getNpcCoordInPrimaryMap( int npcId )
{
	if (-1 == npcId)
	{
		return NULL;
	}
	if(_vecNpcCoord.empty())
		load();

	std::vector<NpcInfo::Npc*> outResult;
	theNpcInfo.GetNpcs(npcId,outResult);//多图
	if (outResult.size() > 0)
	{
		for (int i = 0; i < outResult.size(); ++i)
		{
			if (!gCfg.IsMirrorMapIds(outResult[i]->mapId))
			{
				return NpcCoord::getInstance()->getNpcCoord(npcId,outResult[i]->mapId);
				break;
			}
		}
	}
	return NULL;

}

void NpcCoord::addNpcHyberForTextName(std::string& szString,ETextDataType eDataType,int nDataValue,std::vector<UiCallbackDataBase*>* pCallBackDataArr ,bool bInsertMapName/* = false*/,bool bInserHyper/* = true*/)
{
	guardfunc;
	if(_vecNpcCoord.empty())
		load();	
	const wchar_t* hyberLeft = L"<"; 
	const wchar_t* hyberRight = L">";
	wchar_t hyberRight2 [32] = {0};
	wcscpy(hyberRight2, hyberRight);

	int hl = wcslen(hyberLeft);
	int hr = wcslen(hyberRight2);

	std::wstring wString = _tstring::toWideString(szString.c_str());

	size_t pos = 0;
	while(pos < wString.length())
	{
		size_t verifyPos = std::wstring::npos;
		int index = -1;
		for(int i=0; (i<_vecNpcCoord.size()); ++i)
		{
			size_t findPos = wString.find(_vecNpcCoord[i]._szName, pos);
			if (findPos != std::wstring::npos)
			{
				if (verifyPos == std::wstring::npos)
				{
					verifyPos = findPos;
					index = i;
				}
				else
				{
					if (findPos < verifyPos)
					{
						verifyPos = findPos;
						index = i;
					}
				}
			}
		}

		if (verifyPos == std::wstring::npos)
		{
			break;
		}
		size_t end = verifyPos + _vecNpcCoord[index]._szName.length();
		if (!_vecNpcCoord[index]._bPFPossible)
		{
			pos = end;
			continue;
		}

		if(bInserHyper)
		{
			wString.insert(verifyPos, hyberLeft);
			end += hl;
			wString.insert(end, hyberRight2);

			pos = end + hr;
		}
		else
		{
			pos = end;
		}

		if (pCallBackDataArr || bInsertMapName)
		{
			std::string strName = _tstring::toNarrowString(_vecNpcCoord[index]._szName.c_str());
			int nMapId = -1;
			if (eDataType == eQuestId)
			{
				nMapId = RetriveMapIdFromQuest(nDataValue,strName);
			}
			else if(eDataType == eMapId)
			{
				if (-1 == nDataValue)
				{
					CWorldTile* pCurrTile = CURRENTTILE;
					const NpcCoordInfo* pNpcInfo = NpcCoord::getInstance()->getNpcCoord(strName.c_str(),pCurrTile->GetMapId());
					if (pNpcInfo)
					{
						nMapId = pCurrTile->GetMapId();
					}
					else
					{
						nMapId = GetMyCountryMapId(_vecNpcCoord[index]._mapId,_vecNpcCoord[index]._bNpc);
					}
				}
				else
				{
					nMapId = nDataValue;
				}
			}
			if (bInsertMapName)
			{
				//zhuxincong 12.4 注释 会让任务面板出现多个 npc所在地图
				
				CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(nMapId);
				if (pTile)
				{
					char szMapName[256]={0};
					MeSprintf_s(szMapName,sizeof(szMapName),theXmlString.GetString(eText_Quest_MapName),pTile->GetTileName());
					std::wstring wMapName = Common::_tstring::toWideString(szMapName);
					wString.insert(verifyPos,wMapName);
					pos += wMapName.length();
				}
			}
			if(pCallBackDataArr)
			{
				SMapIdCallbackData* pCallbackData = MeNew SMapIdCallbackData(nMapId);
				pCallBackDataArr->push_back(pCallbackData);
				const NpcCoordInfo* pNpcInfo = NpcCoord::getInstance()->getNpcCoord(strName.c_str(),nMapId);
				if (pNpcInfo)
				{
					CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(pNpcInfo->_mapId);
					if (pTile)
					{
						char cTip[256] = {0};
						sprintf(cTip,"%s(%d,%d)",pTile->GetTileName(),(int)pNpcInfo->_pfMapX,(int)pNpcInfo->_pfMapY);
						pCallbackData->SetTip(cTip);
					}
				}
			}
		}
	}
	szString = _tstring::toNarrowString(wString.c_str());
	unguard;
}

void NpcCoord::addNpcHyberForText( std::string& szString,ETextDataType eDataType,int nDataValue,int npcId,std::vector<UiCallbackDataBase*>* pCallBackDataArr ,bool bInsertMapName/* = false*/,bool bInserHyper/* = true*/)
{
	guardfunc;
	if (_vecNpcCoord.empty())
	{
		load();
	}

	const wchar_t* hyberLeft = L"<"; 
	const wchar_t* hyberRight = L">";
	wchar_t hyberRight2 [32] = {0};

	if (npcId != -1)
		//swprintf_s(hyberRight2,31,L"$%d%s",npcId,hyberRight);
		wcscpy(hyberRight2, hyberRight);
	else
		wcscpy(hyberRight2, hyberRight);

	int hl = wcslen(hyberLeft);
	int hr = wcslen(hyberRight2);
	int nCount = 0;

	std::wstring wString = _tstring::toWideString(szString.c_str());
	size_t pos = 0;
	size_t verifyPos = std::wstring::npos;
	//判读NPCID是否为空
	if (-1 != npcId)
	{
		for (int i=0;i<_vecNpcCoord.size();++i)
		{
			//得到NPC的信息
			if (_vecNpcCoord[i]._nID == npcId)
			{
				nCount = i;//找到NPC ID 记录下标
				size_t findPos = wString.find(_vecNpcCoord[i]._szName, pos);
				if (findPos != std::wstring::npos)
				{
					if (verifyPos == std::wstring::npos)
					{
						verifyPos = findPos;
					}
					else
					{
						if (findPos < verifyPos)
						{
							verifyPos = findPos;
						}
								
					}
				 }

				 if (verifyPos == std::wstring::npos)
				 {
					 break;
				 }
				
				 size_t end = verifyPos + _vecNpcCoord[nCount]._szName.length();
				 if (!_vecNpcCoord[nCount]._bPFPossible)
				 {
					 pos = end;
					 continue;
				 }
				
				 if(bInserHyper)
				 {
				 	wString.insert(verifyPos, hyberLeft);
				 	end += hl;
				 	wString.insert(end, hyberRight2);

				 	pos = end + hr;
				 }
				 else
				 {
				 	pos = end;
				 }

				 if (pCallBackDataArr || bInsertMapName)
				 {
					 std::string strName = _tstring::toNarrowString(_vecNpcCoord[nCount]._szName.c_str());
					 int nMapId = -1;
					 if (eDataType == eQuestId)
					 {
						 nMapId = RetriveMapIdFromQuest(nDataValue,strName);
					 }
					 else if(eDataType == eMapId)
					 {
						 if (-1 == nDataValue)
						 {
							 CWorldTile* pCurrTile = CURRENTTILE;
							 const NpcCoordInfo* pNpcInfo = NpcCoord::getInstance()->getNpcCoord(strName.c_str(),pCurrTile->GetMapId());
							 if (pNpcInfo)
							 {
								 nMapId = pCurrTile->GetMapId();
							 }
							 else
							 {
								 nMapId = GetMyCountryMapId(_vecNpcCoord[nCount]._mapId,_vecNpcCoord[nCount]._bNpc);
							 }
						 }
						 else
						 {
							 nMapId = nDataValue;
						 }
					 }
					 if (bInsertMapName)
					 {
						 CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(nMapId);
						 if (pTile)
						 {
							 char szMapName[256]={0};
							 MeSprintf_s(szMapName,sizeof(szMapName),theXmlString.GetString(eText_Quest_MapName),pTile->GetTileName());
							 std::wstring wMapName = Common::_tstring::toWideString(szMapName);
							 wString.insert(verifyPos,wMapName);
							 pos += wMapName.length();
						 }
					 }
					 if(pCallBackDataArr)
					 {
						 SMapIdCallbackData* pCallbackData = MeNew SMapIdCallbackData(nMapId);
						 pCallBackDataArr->push_back(pCallbackData);
						 const NpcCoordInfo* pNpcInfo = NpcCoord::getInstance()->getNpcCoord(strName.c_str(),nMapId);
						 if (pNpcInfo)
						 {
							 CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(pNpcInfo->_mapId);
							 if (pTile)
							 {
								 char cTip[256] = {0};
								 sprintf(cTip,"%s(%d,%d)",pTile->GetTileName(),(int)pNpcInfo->_pfMapX,(int)pNpcInfo->_pfMapY);
								 pCallbackData->SetTip(cTip);
							 }
						 }
					 }
				 }
				 break;
			}
		}
	}

	szString = _tstring::toNarrowString(wString.c_str());
	unguard;
	//guardfunc;
	//if(_vecNpcCoord.empty())
	//	load();	
	//const wchar_t* hyberLeft = L"<"; 
	//const wchar_t* hyberRight = L">";
	////wchar_t hyberRight2 [32] = {0};
	////if (npcId != -1)
	////	//swprintf_s(hyberRight2,31,L"$%d%s",npcId,hyberRight);
	////	wcscpy(hyberRight2, hyberRight);
	////else
	////	wcscpy(hyberRight2, hyberRight);

	//int hl = wcslen(hyberLeft);
	//int hr = wcslen(hyberRight2);

	//std::wstring wString = _tstring::toWideString(szString.c_str());

	//size_t pos = 0;
	//while(pos < wString.length())
	//{
	//	size_t verifyPos = std::wstring::npos;
	//	int index = -1;
	//	for(int i=0; (i<_vecNpcCoord.size()); ++i)
	//	{
	//		size_t findPos = wString.find(_vecNpcCoord[i]._szName, pos);
	//		if (findPos != std::wstring::npos)
	//		{
	//			if (verifyPos == std::wstring::npos)
	//			{
	//				verifyPos = findPos;
	//				index = i;
	//			}
	//			else
	//			{
	//				if (findPos < verifyPos)
	//				{
	//					verifyPos = findPos;
	//					index = i;
	//				}
	//			}
	//		}
	//	}

	//	if (verifyPos == std::wstring::npos)
	//	{
	//		break;
	//	}
	//	size_t end = verifyPos + _vecNpcCoord[index]._szName.length();
 //		if (!_vecNpcCoord[index]._bPFPossible)
 //		{
 //			pos = end;
 //			continue;
 //		}

	//	if(bInserHyper)
	//	{
	//		wString.insert(verifyPos, hyberLeft);
	//		end += hl;
	//		wString.insert(end, hyberRight2);

	//		pos = end + hr;
	//	}
	//	else
	//	{
	//		pos = end;
	//	}

		/*if (pCallBackDataArr || bInsertMapName)
		{
			std::string strName = _tstring::toNarrowString(_vecNpcCoord[index]._szName.c_str());
			int nMapId = -1;
			if (eDataType == eQuestId)
			{
				nMapId = RetriveMapIdFromQuest(nDataValue,strName);
			}
			else if(eDataType == eMapId)
			{
				if (-1 == nDataValue)
				{
					CWorldTile* pCurrTile = CURRENTTILE;
					const NpcCoordInfo* pNpcInfo = NpcCoord::getInstance()->getNpcCoord(strName.c_str(),pCurrTile->GetMapId());
					if (pNpcInfo)
					{
						nMapId = pCurrTile->GetMapId();
					}
					else
					{
						nMapId = GetMyCountryMapId(_vecNpcCoord[index]._mapId,_vecNpcCoord[index]._bNpc);
					}
				}
				else
				{
					nMapId = nDataValue;
				}
			}
			if (bInsertMapName)
			{
				CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(nMapId);
				if (pTile)
				{
					char szMapName[256]={0};
					MeSprintf_s(szMapName,sizeof(szMapName),theXmlString.GetString(eText_Quest_MapName),pTile->GetTileName());
					std::wstring wMapName = Common::_tstring::toWideString(szMapName);
					wString.insert(verifyPos,wMapName);
					pos += wMapName.length();
				}
			}
			if(pCallBackDataArr)
			{
				SMapIdCallbackData* pCallbackData = MeNew SMapIdCallbackData(nMapId);
				pCallBackDataArr->push_back(pCallbackData);
				const NpcCoordInfo* pNpcInfo = NpcCoord::getInstance()->getNpcCoord(strName.c_str(),nMapId);
				if (pNpcInfo)
				{
					CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(pNpcInfo->_mapId);
					if (pTile)
					{
						char cTip[256] = {0};
						sprintf(cTip,"%s(%d,%d)",pTile->GetTileName(),(int)pNpcInfo->_pfMapX,(int)pNpcInfo->_pfMapY);
						pCallbackData->SetTip(cTip);
					}
				}
			}
		}*/
	//}
	//szString = _tstring::toNarrowString(wString.c_str());
	//unguard;

}

int NpcCoord::RetriveMapIdFromQuest( int nQuestId, const std::string& content )
{
	CWorldTile* pCurrTile = CURRENTTILE;
	SQuest* pQuest = theQuestManager.GetQuest(nQuestId);
	if(!pQuest)
		return -1;

	std::wstring wText = _tstring::toWideString(content.c_str());

	int nMapId = -1;
	const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(pQuest->AcceptTargetId);

	if (pInfo && wText == pInfo->_szName)
	{
		nMapId = pInfo->_mapId;
	}
	else
	{
		pInfo = NpcCoord::getInstance()->getNpcCoord(pQuest->ReplyTargetId);
		if (pInfo && wText == pInfo->_szName)
		{
			nMapId = pInfo->_mapId;
		}
	}
	if (nMapId == -1)
	{		
		if (pCurrTile)
		{
			pInfo = NpcCoord::getInstance()->getNpcCoord(content.c_str(),pCurrTile->GetMapId());
		}
		if (pInfo == NULL)
		{
			pInfo = NpcCoord::getInstance()->getNpcCoord(content.c_str());
		}
		if (pInfo)
		{
			nMapId = pInfo->_mapId;
		}
		//return nMapId;
	}
	//任务数据只有一份，所以要给npc自己国家对应地图的id
	nMapId = GetMyCountryMapId(nMapId, pInfo->_bNpc);

	if (pCurrTile&&gCfg.IsMirrorMapIds(pCurrTile->GetMapId()))
	{
		int32 primaryid = gCfg.GetPrimaryMapId(pCurrTile->GetMapId());
		if (primaryid == nMapId)
		{
			nMapId = pCurrTile->GetMapId();
		}
	}
	return nMapId;
}

int NpcCoord::GetMyCountryMapId( int nMapId, bool isNpc )
{
	int nMapIdInMyCountry = nMapId;
	if (isNpc && nMapIdInMyCountry != -1)
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
		nMapIdInMyCountry = gCfg.GetMyCountryMapId(nMapId,pMe->GetRealCountry());
	}
	return nMapIdInMyCountry;
}

char* NpcCoord::GetNpcDialogPicture( const char* headpic, char* dialogpic, short headid )
{
	if( !headpic || !dialogpic )
		return dialogpic;

	if( !m_bDialogPic )
	{
		strncpy(dialogpic, headpic, strlen(headpic));
		return dialogpic;
	}

	char *p = strrchr((char*)headpic, '.');
	if( p )
	{
		strncpy(dialogpic, (char*)headpic, p-headpic);
		strcat(dialogpic, "Dlg");
		if( headid >= 0 )
		{
			char szHead[128] = {0};
			sprintf_s(szHead, sizeof(szHead)-1, "%d", headid);
			strcat(dialogpic, szHead);
		}
		strcat(dialogpic, p);
	}
	else
		strncpy(dialogpic, headpic, strlen(headpic));


	return dialogpic;
}