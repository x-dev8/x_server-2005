#include "AttackInfoMan.h"
#include "ActionQueue.h"
#include "Player.h"
#include "FuncPerformanceLog.h"
#include "GameMain.h"
#include "PlayerMgr.h"

CAttackInfoMan theAttackInfoMan;
static int s_nInfoCount = 0;
CAttackInfoMan::CAttackInfoMan(void)
{
	guardfunc;
	unguard;
}

CAttackInfoMan::~CAttackInfoMan( void )
{
	guardfunc;
	int k = m_map.GetObjects( NULL );
	ClearAll();
	unguard;
}

SAttackInfo* CAttackInfoMan::AddAttackInfo( SAttackInfo &attackinfo )
{
	guardfunc;
	SAttackInfo *pAttackInfo = MeNew SAttackInfo;
	int n = sizeof( SAttackInfo );

	*pAttackInfo = attackinfo;
	pAttackInfo->bNew = true;

	CPlayer* pSrcPlayer = theHeroGame.GetPlayerMgr()->FindByID( pAttackInfo->nSrcId );
	CPlayer* pTargetPlayer = theHeroGame.GetPlayerMgr()->FindByID( pAttackInfo->nTargetId );

	if( !pSrcPlayer || !pTargetPlayer )
	{
		delete pAttackInfo;
		return NULL;
	}
    s_nInfoCount++;

	//lyh删除引用 死亡的时候已经加了 这里不能再加 
	//pSrcPlayer->AddRef();
	//if( pTargetPlayer )
	//	pTargetPlayer->AddRef();

	//int iLoop; //2013 11 20 cb2
	//for( iLoop = 0 ; iLoop < pAttackInfo->nRecordCount ; iLoop ++ )
	//{
	//	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID( pAttackInfo->records[iLoop].nTargetID );
	//	if( pPlayer && pPlayer != pTargetPlayer )
	//	{
	//		pPlayer->AddRef(); //这里加 下面那个函数对应 减
	//	}
	//}

	m_map.Add( pAttackInfo, pAttackInfo );
	return pAttackInfo;
	unguard;
}

//传入的是AddAttackInfo返回的
void CAttackInfoMan::DeleteAttackInfo( SAttackInfo *pAttackInfo )
{
	guardfunc;
	SAttackInfo* found = m_map.Find( pAttackInfo );
	if( !found )
	{
		assert( false );
		return;
	}

	CPlayer* pSrcPlayer = theHeroGame.GetPlayerMgr()->FindByID( pAttackInfo->nSrcId );
	CPlayer* pTargetPlayer = theHeroGame.GetPlayerMgr()->FindByID( pAttackInfo->nTargetId );
	//// 慎重测试。如果该角色已在死亡队列，那么这里就不会减引用了 [11/10/2010 zhangjiayi]
	//lyh删除引用
	if( !pSrcPlayer )
		pSrcPlayer = theHeroGame.GetPlayerMgr()->FindByServerIDInDeath( pAttackInfo->nSrcId );

	if( !pTargetPlayer )
		pTargetPlayer = theHeroGame.GetPlayerMgr()->FindByServerIDInDeath( pAttackInfo->nTargetId );
	//////////////////////

	//if ( pSrcPlayer ) //lyh注释 这里不应该有操作，引用-- 的时候是在尸体2秒后删除的时候自动--
	//	pSrcPlayer->Release();
	//if( pTargetPlayer )
 //   {
 //       // 复活技能结束，减少目标引用计数貌似有问题，QL
 //       if( pAttackInfo->iSkill != ItemDefine::eSSI_Relive )
 //           pTargetPlayer->Release();
 //   }

	//int iLoop; //2013 11 20 cb2
	//for( iLoop = 0 ; iLoop < pAttackInfo->nRecordCount ; iLoop ++ )
	//{
	//	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID( pAttackInfo->records[iLoop].nTargetID );
	//	if( pPlayer && pPlayer != pTargetPlayer )
	//	{
	//		pPlayer->Release();
	//	}
	//}

	assert( pAttackInfo->bNew );
	pAttackInfo->bNew = false;
	m_map.Remove( pAttackInfo );
	s_nInfoCount--;
	unguard;
}

//玩家切换地图时调用执行保存的所有AttackInfo
void CAttackInfoMan::ExcuteAllAttackInfo( void )
{
	guardfunc;
	std::vector<SAttackInfo*> vectorInfo;
	m_map.GetObjects( &vectorInfo );
	for( int i = 0; i < vectorInfo.size(); i++ )
	{
		SAttackInfo *pAttackInfo = vectorInfo[i];
		if( pAttackInfo )
		{
			CPlayer* pSrcPlayer = theHeroGame.GetPlayerMgr()->FindByID( pAttackInfo->nSrcId );
			if( pSrcPlayer )
				pSrcPlayer->OnHitPoint(TRUE, GlobalControl::eNormal,pAttackInfo );
		}
	}
	unguard;
}

void CAttackInfoMan::ClearAll( void )
{
	guardfunc;
	m_map.Destroy();
	unguard;
}