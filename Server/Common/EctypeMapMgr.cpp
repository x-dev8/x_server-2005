#include "EctypeMapMgr.h"
#include "ShareData.h"
#include "GameWorld.h"

CEctypeMapMgr* GetEctypeMapMgr()
{
	static CEctypeMapMgr s;
	return &s;
}

CEctypeMapMgr::CEctypeMapMgr()
{
}

CEctypeMapMgr::~CEctypeMapMgr()
{
}

void CEctypeMapMgr::UpdateEctypeInfoToClient( BaseCharacter* pChar )
{
	if ( !pChar )
		return;

	DWORD dwEctypeId = pChar->GetMapID();
	GameStage *pStage = theGameWorld.GetStageById( dwEctypeId );
	if ( !pStage )
		return;

	DWORD dwMapId = EctypeId2MapId( dwEctypeId );

	std::vector<DWORD> vtEctypes;
	theGameWorld.GetCurEctypesId( dwEctypeId, vtEctypes );

	MsgAckEctypeMapInfo msg;
	msg.dwCurEctypeId = dwEctypeId;
	msg.dwCurMapId = dwMapId;

	DWORD dwLimitTime = pStage->GetLiftLimitTime();
	if( dwLimitTime != 0 )
	{
		msg.dwLifeLimitTime = dwLimitTime - pStage->GetPassTime();
	}
	else
	{
		msg.dwLifeLimitTime = 0;
	}

	// ��������ִ帱��
	if ( dwMapId == 1 )
	{
		//// ����Ҫ��������IDҲ�·�
		//msg.AddEctype( 0 );
		for( int n=0; n<vtEctypes.size(); n++ )
		{
			msg.AddEctype( vtEctypes[n] );
		}
	}

	GettheServer().SendMsgToSingle( &msg, pChar );
}
