// #include "DropItem.h"
// #include "ShareData.h"
// #include "GameWorld.h"
// #include "ItemCharacter.h"
// #include "FuncPerformanceLog.h"
// #include "LanguageString.h"
// #include "TeamManager.h"
// 
// DropBaseItem::DropBaseItem()
// {
// }
// 
// DropBaseItem::~DropBaseItem()
// {
// }
// 
// bool DropBaseItem::DropItem( int nItemId, int nCount,
//                          int nMapId, float fX, float fY,
//                          bool bTask,
//                          int nGruopId, int nPlayerId )
// {
//     SCharItem item;
//     if( !RunTimeData::GetInstance().CreateItem(nItemId, nCount, HelperFunc::CreateID(),item))
//         return false;
//     //
//     CItemDetail::SItemCommon* pCommon = GettheItemDetail().GetItemByID(item.itembaseinfo.ustItemID);
//     if (!pCommon)
//     {
//         return false;
//     }
//     const float fRate = 3.0f;
//     float fXOffset = 2.0f*fRate*rand()/(float)RAND_MAX - fRate;
//     float fYOffset = 2.0f*fRate*rand()/(float)RAND_MAX - fRate;
//     ItemCharacter* pItemChar = NULL;
//     pItemChar = GettheWorld().CreateItemNpc( pCommon->GetItemName(),
//         nMapId, fX+fXOffset, fY-fYOffset, 0,
//         item, -1, ItemCharacter::const_drop_delay,
//         false );
//     if ( !pItemChar )
//         return false;
// 
//     //Luoz add ������Ʒ�����������Ȩ ------------------------------------------------
//     if( nGruopId != -1 )
//     {
//         Team * pTeam = GetTeamManager().GetTeam(nGruopId);
//         if( pTeam != NULL)
//         {
//             switch( pTeam->getAssignMode() )
//             {
//             case AN_AMT_FREEDOM://���ɷ���
//                 pItemChar->SetMasterGroupID( nGruopId );
//                 break;
//             case AN_AMT_TEAM://����
//                 assignItem_team( nGruopId, nPlayerId, pItemChar->GetID(), item.itembaseinfo.ustItemID );
//                 break;
//             case AN_AMT_RANDOM://�漴
//                 assignItem_random( nGruopId, pItemChar->GetID(), item.itembaseinfo.ustItemID );
//                 break;
//             case AN_AMT_ASSIGN://����
//                 assignItem_assign( nGruopId, pItemChar->GetID(), item.itembaseinfo.ustItemID );
//                 break;
//             }
//             //pItemChar->SetMasterGroupID( nGruopId );
//         }
//         else
//             pItemChar->SetMasterID( nPlayerId ); //������鲻����~~
//     }
//     else //-----------------------------------------------------------------------------
//         pItemChar->SetMasterID( nPlayerId );
// 
//     if ( bTask )
//     {
//         pItemChar->SetTaskItem();
//     }
//     // ��¼LOG,
//     CItemDetail::SItemCommon* pItem = NULL;
//     pItem = GettheItemDetail().GetItemByID( nItemId );
//     if ( pItem && pItem->ustLevel >= 2 )
//     {
//         BaseCharacter* pChar;
//         pChar = RunTimeData::GetInstance().GetCharacterByID( nPlayerId );
//         if ( pChar )
//         {
//             char szLog[256];
//             char szID[40];
//             sprintf_s( szLog, 255, theString.GetString(eLog_info_2slk_19),
//                 pItem->GetItemName(),
//                 BigInt2String(item.itembaseinfo.nOnlyInt, szID) );
//             pChar->Log( szLog );
//         }
//     }
//     return true;
// }
// 
// bool DropBaseItem::DropItem( int nItemId, int nCount,
//                         int nMapId, float fX, float fY,
//                         bool bTask, BaseCharacter* pOwner )
// {
//         
//     if ( !pOwner )
//     {
//         return false;
//     }
//     short stId = -1;
//     if (!pOwner->IsDead())
//     {
//         stId = pOwner->GetID();
//     }
// 
//     return DropItem( nItemId, nCount, nMapId, fX, fY,
//                     bTask, pOwner->GetTeamID(),
//                     /*pOwner->GetID() */stId);
//     
// }
// 
// int DropBaseItem::GetSumProbability( DropItemInfos& vtItem )
// {
//     int nSumPro = 0;
//     for ( unsigned int i=0; i<vtItem.size(); i++ )
//     {
//         nSumPro += vtItem[i].nProbability;
//     }
//     return nSumPro;
// }
// 
// int DropBaseItem::GetDropCount( DropItemInfos& vtItem, int nMinDrop, int nMaxDrop )
// {
//     
//     int nMaxCount = nMaxDrop - nMinDrop + 1;
//     if ( nMaxCount <= 0 )
//         return 0;
//     int nSum = GetSumProbability( vtItem );
//     if ( nSum <= 0 )
//         return 0;
//     if ( nMinDrop <= 0 )
//     {
//         int nRand = rand()%DROP_PROBABILITY;
//         if ( nRand > nSum )
//             return 0;
//     }
//     int nDropCount = nMinDrop + rand()%nMaxCount;
//     if ( nDropCount > vtItem.size() )
//         nDropCount = vtItem.size();
//     return nDropCount;
//     
// }
// 
// bool DropBaseItem::DropItems( DropItemInfos& vtItem, int nCount, bool IsRepeat,
//                          int nMapId, float fX, float fY, bool bTask,
//                          BaseCharacter* pOwner )
// {
//     
//     // ��õ�������(��ƽ���������㷨)
//     while ( vtItem.size() > 0 && nCount > 0 )
//     {
//         // ��������ܺ�
//         int nSum = GetSumProbability( vtItem );
//         if ( nSum <=0 )
//             break;
//         int nRand = rand()%nSum;
//         int nCur = 0;
//         for ( unsigned int n=0; n<vtItem.size(); n++ )
//         {
//             SDropItem* pDropItem = &vtItem[n];
//             nCur += pDropItem->nProbability;
//             if ( nRand < nCur )
//             {
//                 DropItem( pDropItem->nItemId, 1,
//                         nMapId, fX, fY, bTask,
//                         pOwner );
//                 if ( IsRepeat == false )
//                 {
//                     vtItem.erase( vtItem.begin()+n );
//                 }
//                 break;
//             }
//         }
//         nCount--;
//     }
//     return true;
//     
// }
// void DropBaseItem::assignItem_team( int groupid,  int playerid, int npcid, int itemid)
// {
//     
// 
//     Team * pTeam = GetTeamManager().GetTeam(groupid);
//     if( pTeam != NULL)
//     {
//         //2��һ����Ʒ����Ȩ ����  2��������ɸ��ѡ��
//         CItemDetail::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( itemid );
//         ItemCharacter *itemchar = (ItemCharacter*)RunTimeData::GetInstance().GetCharacterByID( npcid );
//         if( pItemDetail && itemchar)
//         {
//             if( pItemDetail->ustLevel < GoodItem_For_AssignTeam )    //��ƷƷ��
//             {//2�����µ�������Ʒ���������ڶ����е�ĳ����
//                 itemchar->SetMasterGroupID( groupid );
//                 itemchar->setPeopleOfTeamTime();
//             }
//             else
//             {/*������е�ÿ���˷���Ϣ ����ɸ��ѡ�� ��ʱ����Ʒ��û�й���
//                �������ѡ��Ļ� �����漴���� �����Ҷ�û��ѡ��Ļ�
//                20�����Ʒ��������ɶ��鹫��ģʽ--����ֻ��������Ϣ ��Ϣ�����ٴ���*/
// 
//                 itemchar->setHoldGroupId( groupid );    //����groupid
//                 itemchar->setPeopleOfTeamTime();
// 
//                 MsgReqAssginTeam msg;
//                 msg.itemid = itemid;
//                 msg.npcid = npcid;
//                 pTeam->SendMsgToAllMembers( &msg );
//             }
//         }
//     }
//     
// }
// void DropBaseItem::assignItem_random( int groupid, int npcid, int itemid)
// {
//     
//     Team * pTeam = GetTeamManager().GetTeam(groupid);
//     if( pTeam != NULL)
//     {
//         CItemDetail::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( itemid );
//         ItemCharacter *itemchar = (ItemCharacter*)RunTimeData::GetInstance().GetCharacterByID( npcid );
//         if( pItemDetail && itemchar)
//         {
//             itemchar->SetMasterID( pTeam->getNext_assign_team() );
//             itemchar->SetMasterGroupID( groupid );
//             itemchar->setPeopleOfTeamTime();
//         }
//     }
//     
// }
// void DropBaseItem::assignItem_assign( int groupid, int npcid, int itemid)
// {
//     
//     Team * pTeam = GetTeamManager().GetTeam(groupid);
//     if( pTeam != NULL)
//     {
//         //2��һ����Ʒ����ʰȡ  2�����϶ӳ�����
//         CItemDetail::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( itemid );
//         ItemCharacter *itemchar = (ItemCharacter*)RunTimeData::GetInstance().GetCharacterByID( npcid );
//         if( pItemDetail && itemchar)
//         {
//             if( pItemDetail->ustLevel < GoodItem_For_AssignTeam )    //��ƷƷ��
//             {//2�����µ�������Ʒ����ʰȡ
//                 itemchar->SetMasterGroupID( groupid );
//                 itemchar->setPeopleOfTeamTime();
//             }
//             else
//             {
//                 itemchar->setAdscription_teamHeader();
//                 itemchar->SetMasterGroupID( groupid );
//                 itemchar->setPeopleOfTeamTime();
//             }
//         }
//     }
//     
// }