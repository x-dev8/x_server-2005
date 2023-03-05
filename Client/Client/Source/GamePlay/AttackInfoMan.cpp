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

	//lyhɾ������ ������ʱ���Ѿ����� ���ﲻ���ټ� 
	//pSrcPlayer->AddRef();
	//if( pTargetPlayer )
	//	pTargetPlayer->AddRef();

	//int iLoop; //2013 11 20 cb2
	//for( iLoop = 0 ; iLoop < pAttackInfo->nRecordCount ; iLoop ++ )
	//{
	//	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID( pAttackInfo->records[iLoop].nTargetID );
	//	if( pPlayer && pPlayer != pTargetPlayer )
	//	{
	//		pPlayer->AddRef(); //����� �����Ǹ�������Ӧ ��
	//	}
	//}

	m_map.Add( pAttackInfo, pAttackInfo );
	return pAttackInfo;
	unguard;
}

//�������AddAttackInfo���ص�
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
	//// ���ز��ԡ�����ý�ɫ�����������У���ô����Ͳ���������� [11/10/2010 zhangjiayi]
	//lyhɾ������
	if( !pSrcPlayer )
		pSrcPlayer = theHeroGame.GetPlayerMgr()->FindByServerIDInDeath( pAttackInfo->nSrcId );

	if( !pTargetPlayer )
		pTargetPlayer = theHeroGame.GetPlayerMgr()->FindByServerIDInDeath( pAttackInfo->nTargetId );
	//////////////////////

	//if ( pSrcPlayer ) //lyhע�� ���ﲻӦ���в���������-- ��ʱ������ʬ��2���ɾ����ʱ���Զ�--
	//	pSrcPlayer->Release();
	//if( pTargetPlayer )
 //   {
 //       // ����ܽ���������Ŀ�����ü���ò�������⣬QL
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

//����л���ͼʱ����ִ�б��������AttackInfo
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