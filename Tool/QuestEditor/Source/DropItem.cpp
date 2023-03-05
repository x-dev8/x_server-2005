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
//     //Luoz add 队伍物品分配决定归属权 ------------------------------------------------
//     if( nGruopId != -1 )
//     {
//         Team * pTeam = GetTeamManager().GetTeam(nGruopId);
//         if( pTeam != NULL)
//         {
//             switch( pTeam->getAssignMode() )
//             {
//             case AN_AMT_FREEDOM://自由分配
//                 pItemChar->SetMasterGroupID( nGruopId );
//                 break;
//             case AN_AMT_TEAM://队伍
//                 assignItem_team( nGruopId, nPlayerId, pItemChar->GetID(), item.itembaseinfo.ustItemID );
//                 break;
//             case AN_AMT_RANDOM://随即
//                 assignItem_random( nGruopId, pItemChar->GetID(), item.itembaseinfo.ustItemID );
//                 break;
//             case AN_AMT_ASSIGN://分配
//                 assignItem_assign( nGruopId, pItemChar->GetID(), item.itembaseinfo.ustItemID );
//                 break;
//             }
//             //pItemChar->SetMasterGroupID( nGruopId );
//         }
//         else
//             pItemChar->SetMasterID( nPlayerId ); //如果队伍不在了~~
//     }
//     else //-----------------------------------------------------------------------------
//         pItemChar->SetMasterID( nPlayerId );
// 
//     if ( bTask )
//     {
//         pItemChar->SetTaskItem();
//     }
//     // 记录LOG,
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
//     // 获得掉落数量(用平均数量的算法)
//     while ( vtItem.size() > 0 && nCount > 0 )
//     {
//         // 掉落机率总和
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
//         //2级一下物品所有权 轮流  2级以上置筛子选择
//         CItemDetail::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( itemid );
//         ItemCharacter *itemchar = (ItemCharacter*)RunTimeData::GetInstance().GetCharacterByID( npcid );
//         if( pItemDetail && itemchar)
//         {
//             if( pItemDetail->ustLevel < GoodItem_For_AssignTeam )    //物品品质
//             {//2级以下的垃圾物品轮流归属于队伍中的某个人
//                 itemchar->SetMasterGroupID( groupid );
//                 itemchar->setPeopleOfTeamTime();
//             }
//             else
//             {/*向队伍中的每个人发消息 进行筛子选择 此时的物品还没有归属
//                如果有人选择的话 进行随即归属 如果大家都没有选择的话
//                20秒后物品归属将变成队伍公共模式--这里只单纯发消息 消息回来再处理*/
// 
//                 itemchar->setHoldGroupId( groupid );    //保留groupid
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
//         //2级一下物品自由拾取  2级以上队长所有
//         CItemDetail::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( itemid );
//         ItemCharacter *itemchar = (ItemCharacter*)RunTimeData::GetInstance().GetCharacterByID( npcid );
//         if( pItemDetail && itemchar)
//         {
//             if( pItemDetail->ustLevel < GoodItem_For_AssignTeam )    //物品品质
//             {//2级以下的垃圾物品自由拾取
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