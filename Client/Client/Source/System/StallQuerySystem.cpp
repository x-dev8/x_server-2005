#include "GameMain.h"
#include "StallQuerySystem.h"
#include "SearchPrivateShop.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "NetworkInput.h"
#include "MeTerrain/stdafx.h"
#include "CrossMapPF.h"
#include "ScreenInfoManager.h"

CStallQuerySystem::CStallQuerySystem(void)
{
}

CStallQuerySystem::~CStallQuerySystem(void)
{
}

void CStallQuerySystem::Reset(void)
{
	m_stallInfos.clear();
}

void CStallQuerySystem::AddStallInfo(StallDefine::SStallInfo *pInfos_, int count_)
{
	assert(pInfos_ != NULL);

	for(int i=0; i<count_; ++i)
	{
		m_stallInfos.push_back(pInfos_[i]);
	}
}

const StallDefine::SStallInfo *CStallQuerySystem::GetItem(size_t index_)
{
	if(index_ < GetStallCount())
	{
		return &m_stallInfos.at(index_);
	}

	return NULL;
}

CStallQueryManager::CStallQueryManager():
m_dataStatus(E_Data_Invalid)
{

}

CStallQueryManager::~CStallQueryManager()
{

}

void CStallQueryManager::MoveToStall(size_t index_)
{
	const StallDefine::SStallInfo *pStallInfo = m_data.GetItem(index_);
	if(NULL == pStallInfo)
		return;

	CWorldTile* pCurrTile = CURRENTTILE;
	assert(pCurrTile);
	if (pCurrTile->GetMapId() == pStallInfo->dwMapID)
	{
		theHeroGame.GetPlayerMgr()->MoveRoleTo(pStallInfo->nX, pStallInfo->nY, false, true);
	}
	else if( theHeroGame.GetPlayerMgr()->GetMe() )
	{//跨地图寻路
		float x,y;
		theHeroGame.GetPlayerMgr()->GetMe()->GetPos(&x, &y, NULL);
		bool bRet = CrossMapPF::Instance()->CrossMapFindPath(pCurrTile->GetMapId(), x, y, 
					pStallInfo->dwMapID, pStallInfo->nX, pStallInfo->nY);
		if (!bRet)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_FindPathFailed, theXmlString.GetString(eText_CannotCrossMapPathFindAddress) );
		}
	}
}

CStallQueryManager::EQueryStatus CStallQueryManager::QueryStall(uint8 fieldType_, char *buf_/* = NULL*/, UINT size_/* = 0*/)
{
	if(MsgStallQuery::ESF_NONE != fieldType_ &&
		MsgStallQuery::ESF_StallName != fieldType_ &&
		MsgStallQuery::ESF_ChaName != fieldType_)
		return E_Query_Status_KeyFieldInvalid;

	if(NULL == buf_)
		return E_Query_Status_KeyInvalid;

	MsgStallQuery msg;
	//if(size_ > sizeof(MsgStallQuery::szKeyWord))
	if(size_ > sizeof(msg.szKeyWord))
		return E_Query_Status_KeyTooLong;

	Reset();

	msg.nSearchField = fieldType_;
	memcpy(msg.szKeyWord, buf_, size_);

	GettheNetworkInput().SendMsg( &msg );

	return E_Query_Status_Succeed;
}

void CStallQueryManager::AddStallInfo(StallDefine::SStallInfo *pInfos_, int count_, bool bLastMsg_)
{
	if(!s_CUI_ID_FRAME_QueryStall.IsVisable())
		return;

	//如果是超时后再陆续接到消息包，则不要改变状态，并且扔掉后续的消息包
	if(GetDataStatus() != E_Data_TimeOut)
	{
		//这种情况有可能发生在两次查询中间没有重新初始化状态（主要是为了防止接口的不正确调用）
		if(E_Data_Completed == GetDataStatus())
		{
			return;
		}
		else
		{
			if(bLastMsg_)
			{
				SetDataStatus(E_Data_Completed);
			}
			else
			{	
				SetDataStatus(E_Data_Uncompleted);
			}

			m_data.AddStallInfo(pInfos_, count_);
			s_CUI_ID_FRAME_QueryStall.AddStallInfo(pInfos_, count_);
		}
	}
}

void CStallQueryManager::Reset(void)
{
	m_data.Reset();
	m_dataStatus = E_Data_Invalid;
}
