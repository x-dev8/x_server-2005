#include "DropItem.h"
#include "ShareData.h"
#include "GameWorld.h"
#include "ItemCharacter.h"
#include "FuncPerformanceLog.h"
#include "XmlStringLanguage.h"
#include "TeamManager.h"
#include "DropItemManager.h"
#include "GamePlayer.h"

DropBaseItem::DropBaseItem()
{   
}

DropBaseItem::~DropBaseItem()
{
}

bool DropBaseItem::DropItem( int nItemId, int nCount,
                         int nMapId, float fX, float fY,
                         int nTask,
                         int nGruopId, int nPlayerId )
{
  //  SCharItem item;
  //  if( !theRunTimeData.CreateItem(nItemId, nCount, HelperFunc::CreateID(),item))
  //      return false;
  //  //
  //  ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID(item.itembaseinfo.ustItemID);
  //  if (!pCommon)
  //  {
  //      return false;
  //  }
  //  const float fRate = 3.0f;
  //  float fXOffset = 2.0f*fRate*theRand.rand32()/(float)RAND_MAX - fRate;
  //  float fYOffset = 2.0f*fRate*theRand.rand32()/(float)RAND_MAX - fRate;
  //  ItemCharacter* pItemChar = NULL;
  //  pItemChar = theGameWorld.CreateItemNpc( pCommon->GetItemName(),
  //      nMapId, fX+fXOffset, fY-fYOffset, 0,
  //      item, -1, ItemCharacter::const_drop_delay,
  //      false );
  //  if ( !pItemChar )
  //      return false;

  //  //Luoz add ������Ʒ�����������Ȩ ------------------------------------------------
  //  if( nGruopId != -1 )
  //  {
  //      //Team * pTeam = GetTeamManager().GetTeam(nGruopId);
		//TeamEx* pTeam = theTeamManager.GetTeam(nGruopId);
  //      if( pTeam != NULL)
  //      {
  //          //switch( pTeam->getAssignMode() )
		//	switch(pTeam->GetAssignModeType())
  //          {
  //          case AssignMode_FreeMode://���ɷ���
  //              pItemChar->SetMasterGroupID( nGruopId );
  //              break;
  //          case AssignMode_Team://����
  //              assignItem_team( nGruopId, nPlayerId, pItemChar->GetID(), item.itembaseinfo.ustItemID );
  //              break;
  //          case AssignMode_Random://�漴
  //              assignItem_random( nGruopId, pItemChar->GetID(), item.itembaseinfo.ustItemID );
  //              break;
  //          case AssignMode_Assign://����
  //              assignItem_assign( nGruopId, pItemChar->GetID(), item.itembaseinfo.ustItemID );
  //              break;
  //          }
  //          //pItemChar->SetMasterGroupID( nGruopId );
  //      }
  //      else
  //          pItemChar->SetMasterID( nPlayerId ); //������鲻����~~
  //  }
  //  else //-----------------------------------------------------------------------------
  //      pItemChar->SetMasterID( nPlayerId );

  //  if ( nTask > 0 )
  //  {
  //      pItemChar->SetTaskItem();
  //  }
  //  // ��¼LOG,
  //  ItemDefine::SItemCommon* pItem = NULL;
  //  pItem = GettheItemDetail().GetItemByID( nItemId );
  //  if ( pItem && pItem->ustLevel >= 2 )
  //  {
  //      BaseCharacter* pChar;
  //      pChar = theRunTimeData.GetCharacterByID( nPlayerId );
  //      if ( pChar )
  //      {
  //          char szLog[256];
  //          char szID[40];
  //          sprintf_s( szLog, 255, theXmlString.GetString(eLog_info_2slk_19),
  //              pItem->GetItemName(),
  //              BigInt2String(item.itembaseinfo.nOnlyInt, szID) );
  //          pChar->Log( szLog );
  //      }
  //  }
    return true;
}

bool DropBaseItem::DropItem( int nItemId, int nCount,
                        int nMapId, float fX, float fY,
                        int nTask, BaseCharacter* pOwner )
{
    //if ( !pOwner )
    //{ return false; }

    //short stId = -1;
    //if ( !pOwner->IsDead() )
    //{
    //    stId = pOwner->GetID();
    //}

    //return DropItem( nItemId, nCount, nMapId, fX, fY, nTask, pOwner->GetTeamID(), stId );

    return true;
}

//������Ʒ�����ﱳ��
bool DropBaseItem::DropItem(int nItemId, int nCount, GamePlayer* pOwner, int nTask /* = 0 */, int nTaskId /* = -1 */, int nTaskState /* = -1 */)
{
    if ( pOwner == NULL || !pOwner->IsPlayer() ) 
    { return false; }

    GameTeam* pTeam = theGameTeamManager.GetTeam( pOwner->GetTeamID() );
    if ( pTeam == NULL )
    {
        pOwner->AddItem( nItemId, nCount );       //���鲻����,�͸���ǰ��Ա  
        return true;
    }

    if ( ( nTask & 0x1 ) != 0  )          //���������,������,���������Ķ�Ա��Ҫ�õ�һ��
    {
        if ( ( nTask & 0x2 ) != 0 )         // �����ר���ڹ�, ֻ�й������ܵ���
        {
            pOwner->AddItem( nItemId, nCount );
        }
        else
        {
            int nTeamCount = pTeam->TeamMemberCount();
            for ( int i = 0; i < nTeamCount; ++i )
            {
                uint32 dwPlayerID = pTeam->GetMemberIDByIndex( i );
                GamePlayer* pTeamPlayer = theRunTimeData.GetGamePlayerByDBID( dwPlayerID );
                if ( pTeamPlayer == NULL || !pTeamPlayer->IsPlayer() )
                { continue; }          //�������������ϵĲ�Ҫ��

                //������Ч��Χ��
                if ( !pTeamPlayer->IsInMapArea(pOwner->GetMapID(), pOwner->GetFloatX(), pOwner->GetFloatY(), TEAM_EXP_DIS) )
                { continue; }

                if ( pTeamPlayer->GetQuestState(nTaskId) != nTaskState ) 
                { continue; }  //����״̬����

                if( GetDropItemManager().GetTaskDropItem().IsTaskItemFull(pTeamPlayer, nItemId) ) 
                { continue; }    //������Ʒ�Ѿ�����

                pTeamPlayer->AddItem( nItemId, nCount );
            }
        }

        return true;
    }

    //��ͨ�������
    switch ( pTeam->GetTeamAssignModeType() )
    {
    case AssignMode_FreeMode:               //����
        pOwner->AddItem( nItemId, nCount );       //���Լ�����
        break;

    case AssignMode_Team:                   //���� (Ŀǰֻ��һ�ַ���ģʽ - ����,�Ȳ߻������������Ժ�����ϸ��)
    case AssignMode_Random:
    case AssignMode_Assign:
        {
            //��õ�ǰ����Ķ�Ա
            uint32 dwPlayerID = pTeam->GetCurrentAssignTeamMemberID();
            GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( dwPlayerID );
            if ( pPlayer == NULL || !pPlayer->IsPlayer() ) 
            { return false; }          //����Ķ�Ա���������,��ֱ�ӷ���

            if( pPlayer->IsDead() )
            { return false; }     //���˲�����

            //����Ч��Χ�ڲŷ���
            if ( pPlayer->IsInMapArea( pOwner->GetMapID(), pOwner->GetFloatX(), pOwner->GetFloatY(), TEAM_EXP_DIS) )
            {
                //�����Ʒ
                pPlayer->AddItem( nItemId, nCount );
            }
        }
        break;

    default:
        pOwner->AddItem( nItemId, nCount );
    }

    return true;
}

//����һ������
bool DropBaseItem::DropItemPackage( DropItemVector& vecDropItem, DropCharItemVector& vecCharItem, unsigned long dwTeamSessionID, unsigned long dwPlayerID, GameObjectId nMonsterID, unsigned long nMapId, float fX, float fY, uint16 ustType )
{
    if ( ( vecDropItem.empty() && vecCharItem.empty() ) )
    { return false;}

    // ����㲥
    std::vector< SBroadcastDrop > vecBroadcast;

    // ���ݰ��������Ʒ�ȼ����жϰ�����ģ��
    int nPackItemID = NorPackageItemID;
    DropItemVectorIter iter = vecDropItem.begin();
    DropItemVectorIter end  = vecDropItem.end();
    for ( ; iter != end; ++iter )
    {
        SDropItem dropItem = *iter   ;
        if (dropItem == NULL)
        { continue; }

        if ( dropItem.nBroadcastStrID > 0 )
        { 
            SBroadcastDrop xBroadcast;
            xBroadcast.nStringID  = dropItem.nBroadcastStrID; 
            xBroadcast.nItemID = dropItem.nItemId;
            vecBroadcast.push_back(xBroadcast);
        }

        ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( dropItem.nItemId );
        if ( pCommon == NULL ) 
        { continue; }

        if ( pCommon->ustLevel >= eIL_Polish )
        {
            nPackItemID = AdvPackageItemID;
            break;      // ֱ������
        }
        else if ( pCommon->ustLevel >= eIL_Choiceness )
        {
            nPackItemID = MidPackageItemID;
        }
    }

    if ( nPackItemID != AdvPackageItemID )
    {
        DropCharItemVectorIter iter = vecCharItem.begin();
        DropCharItemVectorIter end  = vecCharItem.end();
        for ( ; iter != end; ++iter )
        {
            ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( iter->itembaseinfo.ustItemID );
            if ( pCommon == NULL ) 
            { continue; }

            if ( pCommon->ustLevel >= eIL_Polish )
            {
                nPackItemID = AdvPackageItemID;
                break;      // ֱ������
            }
            else if ( pCommon->ustLevel >= eIL_Choiceness )
            {
                nPackItemID = MidPackageItemID;
            }
        }
    }

    ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( nPackItemID );
    if ( pCommon == NULL )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "CItemDetail �Ҳ���������Ʒ��Ϣ[%u]", nPackItemID ); 
        return false;
    }

    // �ȴ���������
    SCharItem item;
    if( !theRunTimeData.CreateItem( NULL, nPackItemID, 1, HelperFunc::CreateID(), item ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "��������ʧ��[%u]", nPackItemID); 
        return false;
    }

    // �Ѱ������뵽��Ϸ����
    static const float fRate[2] = { 1.0f, -1.0f };
    static const int s_nRateCount = sizeof( fRate ) / sizeof( float );

    float fXOffset = fRate[theRand.rand32() % s_nRateCount] / ( theRand.rand32() % 2 + 1 );
    float fYOffset = fRate[theRand.rand32() % s_nRateCount] / ( theRand.rand32() % 2 + 1 );

    fX += fXOffset;
    fY -= fYOffset;
    ItemCharacter* pItemChar = theGameWorld.CreateItemPackageNpc( pCommon->ustItemID, nMapId, fX, fY, 0, 
                                                                    vecDropItem, vecCharItem, dwTeamSessionID, dwPlayerID, item,  g_Cfg.itemDropDelaySecond  /*ItemCharacter::const_drop_delay*/);
    if ( pItemChar != NULL )
    {
        if ( ustType == LogDefine::ECD_DropType_Luck )
        {
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, theXmlString.GetString( eLog_DropPackage ), ustType, nMapId, fX, fY ); 
        }

		MonsterBaseEx* pMonster = (MonsterBaseEx*)theRunTimeData.GetCharacterByID( nMonsterID );
		if ( pMonster&&pMonster->IsMonster() )
		{
			pItemChar->SetDropMonsterID( pMonster->GetMonsterID() );
		}

        pItemChar->SetPackageDropType( ustType );
        pItemChar->SetDropItemType   ( PackDropType_Package );

        if ( vecBroadcast.size() > 0 )
        {
            std::vector< SBroadcastDrop >::iterator iter = vecBroadcast.begin();
            for ( ; iter != vecBroadcast.end(); ++iter )
            {
                theDropItemManager.DropItemBroadcast( iter->nStringID, dwPlayerID, nMonsterID, iter->nItemID, pItemChar );
            }
        }
    }
 
    return pItemChar != NULL;
}

//��Ʒ�����ɢ����Χ��
bool DropBaseItem::DropItemAround( DropItemVector& vecDropItem, DropCharItemVector& vecCharItem, unsigned long dwTeamSessionID, unsigned long dwPlayerID, GameObjectId nMonsterID, unsigned long nMapId, float fX, float fY, uint16 ustType )
{
    if ( ( vecDropItem.empty() && vecCharItem.empty() ) )
    { return false;}

    ItemCharacter* pItemChar = NULL;

    DropItemVectorIter iter = vecDropItem.begin();
    DropItemVectorIter iterEnd  = vecDropItem.end();
    for ( ; iter != iterEnd; ++iter )
    {
        SDropItem dropItem = *iter   ;
        if (dropItem == NULL)
        { continue; }

        ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( iter->nItemId );
        if ( pCommon == NULL )
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "CItemDetail �Ҳ���������Ʒ��Ϣ[%u]", iter->nItemId  ); 
            return false;
        }

        // �ȴ���������
        SCharItem item;
        if( !theRunTimeData.CreateItem( NULL, iter->nItemId , 1, HelperFunc::CreateID(), item ) )
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "��������ʧ��[%u]", iter->nItemId); 
            return false;
        }

        // �Ѱ������뵽��Ϸ����
        static const float fRate[2] = { 1.0f, -1.0f };
        static const int s_nRateCount = sizeof( fRate ) / sizeof( float );

        float fXOffset = fRate[theRand.rand32() % s_nRateCount] / ( theRand.rand32() % 2 + 1 );
        float fYOffset = fRate[theRand.rand32() % s_nRateCount] / ( theRand.rand32() % 2 + 1 );

        fX += fXOffset;
        fY -= fYOffset;

		DropItemVector      vecDropItemTmep;
		DropCharItemVector  vecCharItemTemp;

        vecDropItemTmep.push_back( *iter );

        pItemChar = theGameWorld.CreateItemPackageNpc( pCommon->ustItemID, nMapId, fX, fY, 0, 
            vecDropItemTmep, vecCharItemTemp, dwTeamSessionID, dwPlayerID, item,  g_Cfg.itemDropDelaySecond /*ItemCharacter::const_drop_delay*/ );

        if ( pItemChar != NULL )
        {
            if ( ustType == LogDefine::ECD_DropType_Luck )
            { LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, theXmlString.GetString( eLog_DropPackage ), ustType, nMapId, fX, fY );  }

			MonsterBaseEx* pMonster = (MonsterBaseEx*)theRunTimeData.GetCharacterByID( nMonsterID );
			if ( pMonster&&pMonster->IsMonster() )
			{
				pItemChar->SetDropMonsterID( pMonster->GetMonsterID() );
			}

            pItemChar->SetPackageDropType( ustType );
            pItemChar->SetDropItemType   ( PackDropType_Around );

            if (dropItem.nBroadcastStrID > 0)
            {
                theDropItemManager.DropItemBroadcast( dropItem.nBroadcastStrID, dwPlayerID, nMonsterID, dropItem.nItemId, pItemChar );
            }
        }
    }

    return pItemChar != NULL;
}

void DropBaseItem::AddDropItemInPackage( DropItemVector& vecDropItem, uint16 nItemId, int nCount /* = 1 */ )
{
    SDropItem dropItem;
    dropItem.nItemId = nItemId;

    for (int i=0;i < nCount; ++i)
    {
        vecDropItem.push_back(dropItem);
    }
}

void DropBaseItem::AddDropItemInPackage( DropItemVector& vecDropItem, SDropItem dropItem, int nCount /* = 1 */ )
{
    for (int i=0;i < nCount; ++i)
    {
        vecDropItem.push_back(dropItem);
    }
}

int DropBaseItem::GetSumProbability( DropItemInfos& vtItem )
{
    int nSumPro = 0;
    for ( unsigned int i=0; i<vtItem.size(); i++ )
    {
        nSumPro += vtItem[i].nProbability;
    }
    return nSumPro;
}

int DropBaseItem::GetDropCount( DropItemInfos& vtItem, int nMinDrop, int nMaxDrop )
{
    int nCount = nMaxDrop - nMinDrop + 1;
    if ( nCount <= 0 )
        return 0;
    int nSum = GetSumProbability( vtItem );
    if ( nSum <= 0 )
        return 0;
    if ( nMinDrop <= 0 )
    {
        int nRand = theRand.rand32() % DROP_PROBABILITY;
        if ( nRand > nSum )
            return 0;
    }
    int nDropCount = nMinDrop + theRand.rand32() % nCount;
    //if ( nDropCount > vtItem.size() )
    //    nDropCount = vtItem.size();
    return nDropCount;
}

bool DropBaseItem::DropItems( DropItemInfos& vtItem, int nCount, bool bRepeat,
                         int nMapId, float fX, float fY, int nTask,
                         BaseCharacter* pOwner )
{

    // ��õ�������(��ƽ���������㷨)
    while ( vtItem.size() > 0 && nCount > 0 )
    {
        // ��������ܺ�
        int nSum = GetSumProbability( vtItem );
        if ( nSum <= 0 )
            break;
        int nRand = theRand.rand32() % nSum;
        int nCur = 0;
        for ( unsigned int n=0; n<vtItem.size(); n++ )
        {
            SDropItem* pDropItem = &vtItem[n];
            nCur += pDropItem->nProbability;
            if ( nRand < nCur )
            {
                DropItem(pDropItem->nItemId, 1, (GamePlayer*)pOwner);
                if ( bRepeat == false )
                {
                    vtItem.erase( vtItem.begin()+n );
                }
                break;
            }
        }
        --nCount;
    }


    return true;
}

