#include "GamePlayer.h"
#include "StarLevelUpConfig.h"
#include "XmlStringLanguage.h"
#include "ShareData.h"
#include "ItemComposeConfig.h"
#include "EquipUpgradeConfig.h"
#include "SuitOperateConfig.h"
#include "NpcShop.h"
#include "EquipEvolveConfig.h"
#include "LogEventService.h"
#include "SoulConfig.h"
bool MsgEquipEvolve::IsNeedChangeBound(unsigned int PlayerID)
{
	//服务器端
	GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID(PlayerID);
	if(!pPlayer)
		return false;
	SCharItem * pEquip =pPlayer->GetBagItemByGuid(nNormalGuid);
	if(!pEquip)
		return false;
	if(pEquip->IsBounded())
		return false;
	for(int i =0;i<EConstDefine_MaxMaterialCount;++i)
	{
		if(materials[i].guid == 0 || materials[i].guid==-1)
			continue;
		SCharItem * pItem =pPlayer->GetBagItemByGuid(materials[i].guid);
		if(!pItem)
			continue;
		if(pItem->IsBounded())
			return true;
	}
	return false;
}

void GamePlayer::OnEquipEvolve( Msg* pMsg ) 
{
    MsgEquipEvolve* pEquipEvolve = (MsgEquipEvolve*)pMsg;

	//验证命令的数据的完整性 判断材料是否足够
	bool IsChangeBounded = pEquipEvolve->IsNeedChangeBound(GetDBCharacterID());
	if(IsChangeBounded)
	{
		SCharItem * pEquip =GetBagItemByGuid(pEquipEvolve->nNormalGuid);
		if(pEquip && !pEquip->IsBounded())
		{
			pEquip->SetBounded(true);
		}
	}
    switch ( pEquipEvolve->nEvolveType )
    {
    case MsgEquipEvolve::ET_LevelUp:
        { _ProcessEquipLevelUp( pEquipEvolve ); }
        break;
    case MsgEquipEvolve::ET_Identify:
        { _ProcessEquipIdentify( pEquipEvolve ); }
        break;
    case MsgEquipEvolve::ET_Stiletto:
        { _ProcessStiletto( pEquipEvolve ); }
        break;
    case MsgEquipEvolve::ET_Inlay:
        { _ProcessGemInlay( pEquipEvolve ); }
        break;
    case MsgEquipEvolve::ET_Replace:
        { _ProcessGemReplace( pEquipEvolve ); }
        break;
    case MsgEquipEvolve::ET_TakeDown:
        { _ProcessGemTakeDown( pEquipEvolve ); }
        break;
    case MsgEquipEvolve::ET_OpenLight:
        { _ProcessEquipOpenLight( pEquipEvolve ); }
        break;
    case MsgEquipEvolve::ET_ReOpenLight:
        { _ProcessEquipReOpenLight( pEquipEvolve ); }
        break;
    case MsgEquipEvolve::ET_SoulStamp:
        { _ProcessSoulStamp( pEquipEvolve ); }
        break;
    case MsgEquipEvolve::ET_Maintain:
        { _ProcessEquipMaintain( pEquipEvolve ); }
        break;
    case MsgEquipEvolve::ET_MaintainCross:
        { _ProcessEquipMaintainCross( pEquipEvolve ); }
        break;
    case MsgEquipEvolve::ET_Charm:
        { _ProcessEquipCharmAbsorb( pEquipEvolve ); }
        break;
    case MsgEquipEvolve::ET_Amulet:
        { _ProcessEquipAmuletAbsorb( pEquipEvolve ); }
        break;
	case MsgEquipEvolve::ET_UnknowIdentify:
		{ _ProcessEquipUnknowIdentify( pEquipEvolve ); }
		break;
    }
}

void GamePlayer::OnMsgItemComposeReq( Msg* pMsg )
{
    MsgItemComposeReq* pReq = static_cast< MsgItemComposeReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    if ( !pReq->TestCountLength() )
    { return; }
    
    MsgItemComposeAck xAck;

    SCharItem* pCharItem[ MsgItemComposeReq::ECD_MaxCount ] = { NULL };
    memset( pCharItem, NULL, sizeof( pCharItem ) );

    std::set< __int64 > setGuid;

    uint8 primaryItemIndex= MsgItemComposeReq::ECD_PrimaryItemIndex;

    // 第一个是主材料
    if ( pReq->xItem[primaryItemIndex].stItemIndex == -1 )
    { return; }
    switch ( pReq->xItem[primaryItemIndex].uchItemBagType )
    {
    case BT_MaterialBag:
        pCharItem[primaryItemIndex] = _MaterialItemBag.GetItemByIndex( pReq->xItem[primaryItemIndex].stItemIndex );
        break;
    default:
        pCharItem[primaryItemIndex] = _NormalItemBag.GetItemByIndex( pReq->xItem[primaryItemIndex].stItemIndex );
    }

    if ( pCharItem[primaryItemIndex] == NULL || pCharItem[primaryItemIndex]->GetItemGuid() != pReq->xItem[primaryItemIndex].n64ItemGuid )
    {
        xAck.uchResult = MsgItemComposeAck::ECD_ErrorComposeItem;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    // 记录材料guid
    setGuid.insert( pCharItem[primaryItemIndex]->GetItemGuid() );

    const ComposeData* pData = theItemComposeConfig.GetItemComposeData( pCharItem[primaryItemIndex]->GetItemID() );
    if ( pData == NULL )
    {
        xAck.uchResult = MsgItemComposeAck::ECD_CanNotCompose;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    int nCount = pCharItem[primaryItemIndex]->GetItemCount(); // 判断放入物品的个数
    uint16 nActiveNeedCount = 0; // 实际需要的个数

    for ( int i=1; i<pReq->count; ++i )
    {
        if ( pReq->xItem[i].stItemIndex == -1 )
        { continue; }

        switch ( pReq->xItem[i].uchItemBagType )
        {
        case BT_MaterialBag:
            pCharItem[i] = _MaterialItemBag.GetItemByIndex( pReq->xItem[i].stItemIndex );
            break;
        default:
            pCharItem[i] = _NormalItemBag.GetItemByIndex( pReq->xItem[i].stItemIndex );
        }

        if ( pCharItem[i] == NULL || pCharItem[i]->GetItemGuid() != pReq->xItem[i].n64ItemGuid  )
        {
            if ( i != pReq->count-1)
            { xAck.uchResult = MsgItemComposeAck::ECD_ErrorComposeItem; }
            else
            { xAck.uchResult = MsgItemComposeAck::ECD_ErrorMaterialItem; }
            
            GettheServer().SendMsgToSingle( &xAck, this );
            return;
        }
        
        if ( i != pReq->count-1 )
        { // 合成材料
            if ( pCharItem[i]->GetItemID() != pCharItem[primaryItemIndex]->GetItemID())
            {
                xAck.uchResult = MsgItemComposeAck::ECD_ErrorComposeItem; 
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }
        }
        else
        { // 辅助材料
            if ( pCharItem[i]->GetItemID() != pData->GetMaterialID())
            {
                xAck.uchResult = MsgItemComposeAck::ECD_ErrorMaterialItem;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }
        }

        // 判断GUID 是否已经存在了
        if ( setGuid.find( pCharItem[i]->GetItemGuid() ) != setGuid.end() )
        {
            if ( i != pReq->count-1 )
            { xAck.uchResult = MsgItemComposeAck::ECD_ErrorComposeItem; }
            else
            { xAck.uchResult = MsgItemComposeAck::ECD_ErrorMaterialItem; }
            
            GettheServer().SendMsgToSingle( &xAck, this );
            return;
        }

        if ( i != pReq->count-1 )
        { nCount += pCharItem[i]->GetItemCount(); }

        setGuid.insert( pCharItem[i]->GetItemGuid());
    }

    // 判断钱够不够
    if ( GetMoney() + GetJiaoZi() < pData->GetCostMoney() )
    {
        xAck.uchResult = MsgItemComposeAck::ECD_NotEnoughMoney;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    float fModulus = pData->GetModulus( nCount, nActiveNeedCount );
    int nRand = theRand.rand16() % RAND_NUM;
    if ( nRand < fModulus * RAND_NUM )
    {
        if ( AddItem( pData->GetNewItemID(), 1, EIGS_Compose ) != ierr_Success )    
        {
            xAck.uchResult = MsgItemComposeAck::ECD_ItemPackFull;
            GettheServer().SendMsgToSingle( &xAck, this );
            return;
        }
    }
    else
    {
        xAck.uchResult = MsgItemComposeAck::ECD_Failed;
    }

    // 扣钱
    OperateJiaoZi( EOT_Sub, pData->GetCostMoney(), true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_ItemCompose);

    // 删除物品
    for ( uint8 i=0; i<pReq->count; ++i )
    {
        if ( pCharItem[i] == NULL )
        { continue; }

        if ( i == pReq->count - 1) // 附加材料
        { 
		

			//LYH日志添加
			SCharItem *_item = GetBagItemByGuid(pReq->xItem[i].n64ItemGuid);
			if(_item)
			{
				ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
				if(_pitem)
			       theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),1,_item->GetItemGuid(),
				   _item->GetItemCount()-1 >= 0 ? _item->GetItemCount()-1 : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
			}
			
			RemoveItem( pReq->xItem[i].uchItemBagType, pReq->xItem[i].stItemIndex, NUMERIC_ONE, pReq->xItem[i].n64ItemGuid ); 
		}
        else
        { // 合成材料
            if ( nActiveNeedCount == 0)
            { continue; }

            uint16 count = 0;
            if ( pCharItem[i]->GetItemCount() < nActiveNeedCount )
            { count = pCharItem[i]->GetItemCount(); }
            else
            { count = nActiveNeedCount; }

           

			//LYH日志添加
			SCharItem *_item = GetBagItemByGuid(pReq->xItem[i].n64ItemGuid);

			if(_item)
			{
				ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
			    if(_pitem)
				theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),count,_item->GetItemGuid(),
				_item->GetItemCount()-count >= 0 ? _item->GetItemCount()-count : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
			}

			 RemoveItem( pReq->xItem[i].uchItemBagType, pReq->xItem[i].stItemIndex, count, pReq->xItem[i].n64ItemGuid );

            nActiveNeedCount -= count;
        }
    }

    xAck.dwCurrentMoney = GetMoney();
    GettheServer().SendMsgToSingle( &xAck, this );
}

void GamePlayer::OnMsgItemComposeGem( Msg* pMsg )
{
    MsgItemComposeGem* pMsgItemCompose = (MsgItemComposeGem*) pMsg ;
    if ( pMsgItemCompose == NULL )
    { return; }

    MsgItemComposeGemAck xAck;
    xAck.composeType = pMsgItemCompose->composeType;

    SCharItem* pCharItem[ MsgItemComposeGem::ECD_MaterialMaxCount ] = { NULL };
    memset( pCharItem, NULL, sizeof( pCharItem ) );

//     std::set< __int64 > setGuid;
// 
//     uint8 primaryItemIndex= MsgItemComposeGem::ECD_PrimaryItemIndex;
// 
//     // 第一个是主材料
//     if ( pMsgItemCompose->materials[primaryItemIndex].nItemIndex == -1 )
//     { return; }
// 
//     switch ( pMsgItemCompose->materials[primaryItemIndex].nItemBagType )
//     {
//     case BT_MaterialBag:
//         pCharItem[primaryItemIndex] = _MaterialItemBag.GetItemByIndex( pMsgItemCompose->materials[primaryItemIndex].nItemIndex );
//         break;
//     default:
//         pCharItem[primaryItemIndex] = _NormalItemBag.GetItemByIndex( pMsgItemCompose->materials[primaryItemIndex].nItemIndex );
//     }
// 
//     if ( pCharItem[primaryItemIndex] == NULL || pCharItem[primaryItemIndex]->GetItemGuid() != pMsgItemCompose->materials[primaryItemIndex].nItemGuid )
//     {
//         xAck.nResult = MsgItemComposeGemAck::ECD_ErrorComposeItem;
//         GettheServer().SendMsgToSingle( &xAck, this );
//         return;
//     }

//     const ComposeData2* pData = theItemComposeConfig.GetItemComposeData2( pCharItem[primaryItemIndex]->GetItemID() );
//     if ( pData == NULL )
//     {
//         xAck.nResult = MsgItemComposeGemAck::ECD_CanNotCompose;
//         GettheServer().SendMsgToSingle( &xAck, this );
//         return;
//     }
// 
//     const std::vector<ComposeData2::SMaterial> & vecMaterial = pData->GetMaterialList();
//     if (pMsgItemCompose->nMaterialCount < vecMaterial.size())
//     {
//         xAck.nResult = MsgItemComposeGemAck::ECD_CanNotCompose;
//         GettheServer().SendMsgToSingle( &xAck, this );
//         return;
//     }

    int nModulus = 0;
	bool IsGemBound = false;
    for ( int i=0; i < pMsgItemCompose->nMaterialCount; ++i )
    {
        if ( pMsgItemCompose->materials[i].nItemGuid == 0 )
        { continue; }

        switch ( pMsgItemCompose->materials[i].nItemBagType )
        {
        case BT_MaterialBag:
            pCharItem[i] = _MaterialItemBag.GetItemByIndex( pMsgItemCompose->materials[i].nItemIndex );
            break;
		case BT_NormalItemBag:
			pCharItem[i] = _NormalItemBag.GetItemByIndex( pMsgItemCompose->materials[i].nItemIndex );
			break;
        default:
            pCharItem[i] = _NormalItemBag.GetItemByIndex( pMsgItemCompose->materials[i].nItemIndex );
        }

        if ( pCharItem[i] == NULL || pCharItem[i]->GetItemGuid() != pMsgItemCompose->materials[i].nItemGuid  )
        {
            //if ( i != primaryItemIndex)
            { xAck.nResult = MsgItemComposeGemAck::ECD_ErrorComposeItem; }
            //else
            //{ xAck.nResult = MsgItemComposeGemAck::ECD_ErrorMaterialItem; }

            GettheServer().SendMsgToSingle( &xAck, this );
            return;
        }

		if ( pCharItem[i]->IsBounded() )
			IsGemBound = true;

//         if ( pCharItem[i]->GetItemID() != vecMaterial[i].nMaterialID )
//         {
//             xAck.nResult = MsgItemComposeGemAck::ECD_ErrorMaterialItem;
//             GettheServer().SendMsgToSingle( &xAck, this );
//             return;
//         }
// 
//         if ( pCharItem[i]->GetItemCount() < vecMaterial[i].nCount )
//         {
//             xAck.nResult = MsgItemComposeGemAck::ECD_ErrorMaterialItem;
//             GettheServer().SendMsgToSingle( &xAck, this );
//             return;
//         }
// 
//         nModulus += vecMaterial[i].nModulus;
    }

	const ComposeData2 *pData =  NULL;
	if (pMsgItemCompose->composeType == MsgItemComposeGem::ECT_GEM)
		pData = theItemComposeConfig.GetComposeDataNew(pCharItem[0]->GetItemID(), pMsgItemCompose->nSelectGemNum);
	else
		pData = theItemComposeConfig.GetComposeData(pCharItem,pMsgItemCompose->nMaterialCount);
	if ( NULL == pData )
	{
		xAck.nResult = MsgItemComposeGemAck::ECD_ErrorComposeItem;
		GettheServer().SendMsgToSingle( &xAck, this );
		return;
	}

	//gem compose rune
	SCharItem *pComposeRune = NULL;
	if ( pMsgItemCompose->composeRune.nItemGuid )
	{
		switch ( pMsgItemCompose->composeRune.nItemBagType )
		{
		case BT_MaterialBag:
			pComposeRune = _MaterialItemBag.GetItemByIndex( pMsgItemCompose->composeRune.nItemIndex );
			break;
		default:
			pComposeRune = _NormalItemBag.GetItemByIndex( pMsgItemCompose->composeRune.nItemIndex );
		}
	
		if ( pComposeRune == NULL || pComposeRune->GetItemGuid() != pMsgItemCompose->composeRune.nItemGuid )
		{
			xAck.nResult = MsgItemComposeGemAck::ECD_ErrorComposeRune;
			GettheServer().SendMsgToSingle( &xAck, this );
			return;
		}

		//check gem compose rune config
		ItemDefine::SCreateMaterial *pItemMaterialConfig = (ItemDefine::SCreateMaterial*) GettheItemDetail().GetItemByID(pComposeRune->GetItemID());
		if ( NULL == pItemMaterialConfig )
		{ return; }

		if ( pItemMaterialConfig->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
		{
			xAck.nResult = MsgItemComposeGemAck::ECD_ErrorComposeRune;
			GettheServer().SendMsgToSingle( &xAck, this );
			return;
		}

		if ( pItemMaterialConfig->stMaterialType != ItemDefine::ematerial_gemcomposerune)
		{
			xAck.nResult = MsgItemComposeGemAck::ECD_ErrorComposeRune;
			GettheServer().SendMsgToSingle( &xAck, this );
			return;
		}

		//add rate
		nModulus = pItemMaterialConfig->fAddIntensifyRate[0];

		if(pComposeRune && pComposeRune->IsBounded())
			IsGemBound = true;
	}

     // 判断钱够不够
     if ( pData->GetCostMoney() > GetJiaoZiMoney() )
     {
         xAck.nResult = MsgItemComposeGemAck::ECD_NotEnoughMoney;
         GettheServer().SendMsgToSingle( &xAck, this );
         return;
     }

	// 判断背包是否有位置
	ItemBag* pSelectedBag = NULL;
	switch ( pMsgItemCompose->materials[0].nItemBagType )
	{
	case BT_MaterialBag:
		pSelectedBag = &_MaterialItemBag;
		break;
	default:
		pSelectedBag = &_NormalItemBag;
	}
	if ( pSelectedBag->GetItemEmptyCount() < NUMERIC_ONE)
	{
		xAck.nResult = MsgItemComposeGemAck::ECD_ItemPackFull;
		GettheServer().SendMsgToSingle( &xAck, this );
		return; 
	}

	// 删除物品
	int ncount = pMsgItemCompose->nSelectGemNum;
	for ( uint8 i = 0 ; i < pMsgItemCompose->nMaterialCount ; ++i )
	{
		if ( pCharItem[i] == NULL )
		{ continue; }

		if (pMsgItemCompose->composeType == MsgItemComposeGem::ECT_GEM)
		{
			int nrest = ncount - pMsgItemCompose->materials[i].nCount;

			if (nrest >= 0)
			{
				
				//LYH日志添加 
				SCharItem * _Item = GetBagItemByGuid(pMsgItemCompose->materials[i].nItemGuid);
				if(_Item)
				{
					ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_Item->GetItemID());
					if(_pitem)
					theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_Item->GetItemID(),pMsgItemCompose->materials[i].nCount,_Item->GetItemGuid(),
					_Item->GetItemCount()-pMsgItemCompose->materials[i].nCount >= 0 ? _Item->GetItemCount()-pMsgItemCompose->materials[i].nCount : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
				}
				ncount -= pMsgItemCompose->materials[i].nCount;
				if (!RemoveItem( pMsgItemCompose->materials[i].nItemBagType, pMsgItemCompose->materials[i].nItemIndex, pMsgItemCompose->materials[i].nCount, pMsgItemCompose->materials[i].nItemGuid ))
				{
					xAck.nResult = MsgItemComposeGemAck::ECD_ErrorComposeItem;
					GettheServer().SendMsgToSingle( &xAck, this );
					return;
				}
				
			}
			else
			{
				SCharItem * _Item = GetBagItemByGuid(pMsgItemCompose->materials[i].nItemGuid);
				if(_Item)
				{
					ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_Item->GetItemID());
					if(_pitem)
					theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_Item->GetItemID(),ncount,_Item->GetItemGuid(),
					_Item->GetItemCount()-ncount >= 0 ? _Item->GetItemCount()-ncount : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
				}

				if (!RemoveItem( pMsgItemCompose->materials[i].nItemBagType, pMsgItemCompose->materials[i].nItemIndex, ncount, pMsgItemCompose->materials[i].nItemGuid ))
				{
					xAck.nResult = MsgItemComposeGemAck::ECD_ErrorComposeItem;
					GettheServer().SendMsgToSingle( &xAck, this );
					return;
				}

				ncount = 0;
			}
		}
		else
		{
			//LYH日志添加 
			SCharItem * _Item = GetBagItemByGuid(pMsgItemCompose->materials[i].nItemGuid);
			if(_Item)
			{
				ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_Item->GetItemID());
				if(_pitem)
				theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_Item->GetItemID(),pMsgItemCompose->materials[i].nCount,_Item->GetItemGuid(),
				_Item->GetItemCount()-pMsgItemCompose->materials[i].nCount >= 0 ? _Item->GetItemCount()-pMsgItemCompose->materials[i].nCount : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
			}

			if (!RemoveItem( pMsgItemCompose->materials[i].nItemBagType, pMsgItemCompose->materials[i].nItemIndex, pMsgItemCompose->materials[i].nCount, pMsgItemCompose->materials[i].nItemGuid ))
			{
				xAck.nResult = MsgItemComposeGemAck::ECD_ErrorComposeItem;
				GettheServer().SendMsgToSingle( &xAck, this );
				return;
			}
		}
	}
	if (pComposeRune)
	{
		//LYH日志添加 
		SCharItem * _Item = GetBagItemByGuid(pMsgItemCompose->composeRune.nItemGuid);
		if(_Item)
		{
			ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_Item->GetItemID());
			if(_pitem)
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_Item->GetItemID(),NUMERIC_ONE,_Item->GetItemGuid(),
			_Item->GetItemCount()-NUMERIC_ONE >= 0 ? _Item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
		}

		if (!RemoveItem( pMsgItemCompose->composeRune.nItemBagType, pMsgItemCompose->composeRune.nItemIndex, NUMERIC_ONE, pMsgItemCompose->composeRune.nItemGuid ))
		{
			xAck.nResult = MsgItemComposeGemAck::ECD_ErrorComposeRune;
			GettheServer().SendMsgToSingle( &xAck, this );
			return;
		}
		
	}

	//gem composing...
	int nPackIndex = 0 ;
	SCharItem  xCharItem;
    int nProbility = pData->GetProbility() + nModulus ;
    int nRand = theRand.rand16() % RAND_NUM;
	ItemDefine::SItemCommon* pItem = NULL;
	pItem = GettheItemDetail().GetItemByID( pData->GetNewItemID() );
    if ( nRand < nProbility )
    {
        xAck.nResult = MsgItemComposeGemAck::ECD_Success;

		__int64 nItemBigId = _NormalItemBag.GetNewItemID();
		if ( nItemBigId == InvalidLogicNumber ) 
		{ 
			xAck.nResult = MsgItemComposeGemAck::ECD_ItemPackFull;
			GettheServer().SendMsgToSingle( &xAck, this );
			return; 
		}

		if(pItem == NULL) 
		{ 
			xAck.nResult = MsgItemComposeGemAck::ECD_ErrorMaterialItem;
			GettheServer().SendMsgToSingle( &xAck, this ); 
			return; 
		}

		uint16     nCount = NUMERIC_ONE;
		if( !theRunTimeData.CreateItem( this, pData->GetNewItemID(), nCount , nItemBigId, xCharItem ) )
		{ 
			xAck.nResult = MsgItemComposeGemAck::ECD_Failed;
			GettheServer().SendMsgToSingle( &xAck, this ); 
			return; 
		}

		xCharItem.SetBounded( IsGemBound );

		//加入到物品包裹中
		int nResult = ierr_unknown;
		switch ( pItem->ucItemType )
		{
		case ItemDefine::ITEMTYPE_MATERIAL:
		case ItemDefine::ITEMTYPE_GEM:
			nResult = _MaterialItemBag.PushItem( xCharItem, nCount, -1, &nPackIndex ); theLogEventService.LogItemGain(GetAccountID(),GetDBCharacterID(),xCharItem.GetItemID(),nCount,xCharItem.GetItemGuid(),EIGS_Compose,GetCharName(),pItem->GetItemName());//LYH日志添加 （宝石合成）
			break;
		default:
			nResult = _NormalItemBag.PushItem( xCharItem, nCount, -1, &nPackIndex   ); theLogEventService.LogItemGain(GetAccountID(),GetDBCharacterID(),xCharItem.GetItemID(),nCount,xCharItem.GetItemGuid(),EIGS_Compose,GetCharName(),pItem->GetItemName());//LYH日志添加 （宝石合成）
			break;
		}

		if ( nResult != ierr_Success )    
		{
			xAck.nResult = MsgItemComposeGemAck::ECD_ItemPackFull;
			GettheServer().SendMsgToSingle( &xAck, this );
			return;
		}
    }
	else
	{
		xAck.nResult = MsgItemComposeGemAck::ECD_Failed;
	}

    // 扣钱
    OperateJiaoZi( EOT_Sub, pData->GetCostMoney(), true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_ComposeGem);

    // 背包里面的物品
	ItemBag*	pCreateBag = NULL;
	if (xAck.nResult != MsgItemComposeGemAck::ECD_Failed && pItem)
	{
		switch ( pItem->ucItemType )
		{
		case ItemDefine::ITEMTYPE_MATERIAL:
		case ItemDefine::ITEMTYPE_GEM:
			pCreateBag = &_MaterialItemBag;
			break;
		case ItemDefine::ITEMTYPE_ARMOUR:
		case ItemDefine::ITEMTYPE_WEAPON:
			pCreateBag = &_NormalItemBag;
		default:
			pCreateBag = &_NormalItemBag;
			break;
		}
		SCharItem *pBagCahrItem = pCreateBag->GetItemByIndex(nPackIndex);
		if (pBagCahrItem == NULL)
		{ return; }
		xCharItem = *pBagCahrItem;
	}

    //xAck.nItemBagType = pMsgItemCompose->materials[primaryItemIndex].nItemBagType  ;
	 xAck.nItemBagType = pMsgItemCompose->materials[0].nItemBagType  ;
    xAck.nPackIndex   = nPackIndex   ;
    xAck.AddCharItem(xCharItem);
    GettheServer().SendMsgToSingle( &xAck, this );
	//触发完成宝石升级任务
	TriggerSpecialQuest(ESTT_GemUp);
}


void GamePlayer::OnMsgZhuJiangCompose( Msg* pMsg )
{
	MsgZhuJiangCompose* pMsgCompose = (MsgZhuJiangCompose*) pMsg ;
	if ( !pMsgCompose )
		return; 
	MsgZhuJiangComposeAck xAck;

	SCharItem* pCharItem[ MsgZhuJiangCompose::ECD_MaterialMaxCount ] = { NULL };
	memset( pCharItem, NULL, sizeof( pCharItem ) );

	for ( int i=0; i < MsgZhuJiangCompose::ECD_MaterialMaxCount; ++i )
	{
		/*if ( pMsgCompose->materials[i].nItemGuid == 0 )
		{ 
			xAck.nResult = MsgZhuJiangComposeAck::ECD_ErrorMaterialItem;
			GettheServer().SendMsgToSingle( &xAck, this );
			return;
		}*/

		if ( pMsgCompose->materials[i].nItemGuid )
		{
			switch ( pMsgCompose->materials[i].nItemBagType )
			{
			case BT_MaterialBag:
				pCharItem[i] = _MaterialItemBag.GetItemByIndex( pMsgCompose->materials[i].nItemIndex );
				break;
			case BT_NormalItemBag:
				pCharItem[i] = _NormalItemBag.GetItemByIndex( pMsgCompose->materials[i].nItemIndex );
				break;
			default:
				pCharItem[i] = _NormalItemBag.GetItemByIndex( pMsgCompose->materials[i].nItemIndex );
			}

			if ( pCharItem[i] == NULL || pCharItem[i]->GetItemGuid() != pMsgCompose->materials[i].nItemGuid  )
			{
				xAck.nResult = MsgZhuJiangComposeAck::ECD_ErrorComposeItem; 
				GettheServer().SendMsgToSingle( &xAck, this );
				return;
			}
		}
	}

	//是否放入材料
	SCharItem *pComposeRune = NULL;
	int nModulus = 0;
	bool IsNeedBounded=false;
	if ( pMsgCompose->composeRune.nItemGuid )
	{
		switch ( pMsgCompose->composeRune.nItemBagType )
		{
		case BT_MaterialBag:
			pComposeRune = _MaterialItemBag.GetItemByIndex( pMsgCompose->composeRune.nItemIndex );
			break;
		default:
			pComposeRune = _NormalItemBag.GetItemByIndex( pMsgCompose->composeRune.nItemIndex );
		}

		if ( pComposeRune == NULL || pComposeRune->GetItemGuid() != pMsgCompose->composeRune.nItemGuid )
		{
			xAck.nResult = MsgZhuJiangComposeAck::ECD_ErrorComposeRune;
			GettheServer().SendMsgToSingle( &xAck, this );
			return;
		}

		//check gem compose rune config
		ItemDefine::SCreateMaterial *pItemMaterialConfig = (ItemDefine::SCreateMaterial*) GettheItemDetail().GetItemByID(pComposeRune->GetItemID());
		if ( !pItemMaterialConfig )
			return; 

		if ( pItemMaterialConfig->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
		{
			xAck.nResult = MsgZhuJiangComposeAck::ECD_ErrorComposeRune;
			GettheServer().SendMsgToSingle( &xAck, this );
			return;
		}
		IsNeedBounded = pComposeRune->IsBounded();
		//add rate
		nModulus = pItemMaterialConfig->fAddIntensifyRate[0];
	}

	const ComposeData2 *pData = theItemComposeConfig.GetItemComposeData2(pMsgCompose->materials[0].nItemId);
	if ( NULL == pData )
	{
		xAck.nResult = MsgZhuJiangComposeAck::ECD_ErrorComposeItem;
		GettheServer().SendMsgToSingle( &xAck, this );
		return;
	}
	// 判断背包是否有位置
	ItemBag* pSelectedBag = NULL;
	switch ( pMsgCompose->materials[0].nItemBagType )
	{
	case BT_MaterialBag:
		pSelectedBag = &_MaterialItemBag;
		break;
	default:
		pSelectedBag = &_NormalItemBag;
	}
	if ( pSelectedBag->GetItemEmptyCount() < NUMERIC_ONE)
	{
		xAck.nResult = MsgZhuJiangComposeAck::ECD_ItemPackFull;
		GettheServer().SendMsgToSingle( &xAck, this );
		return; 
	}

	// 判断钱够不够
	if ( pData->GetCostMoney() > GetJiaoZiMoney() )
	{
		xAck.nResult = MsgZhuJiangComposeAck::ECD_NotEnoughMoney;
		GettheServer().SendMsgToSingle( &xAck, this );
		return;
	}

	// 删除物品
	int ncount = MsgZhuJiangCompose::ECD_MaterialMaxCount;
	for ( uint8 i = 0 ; i < MsgZhuJiangCompose::ECD_MaterialMaxCount ; ++i )
	{
		if ( pCharItem[i] == NULL )
		{ continue; }

		int nrest = ncount - pMsgCompose->materials[i].nItemCount;

		if (nrest >= 0)
		{
			//LYH日志添加 
			SCharItem * _Item = GetBagItemByGuid(pMsgCompose->materials[i].nItemGuid);
			if(_Item)
			{
				ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_Item->GetItemID());
				if(_pitem)
				theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_Item->GetItemID(),pMsgCompose->materials[i].nItemCount,_Item->GetItemGuid(),
				_Item->GetItemCount()-pMsgCompose->materials[i].nItemCount >= 0 ? _Item->GetItemCount()-pMsgCompose->materials[i].nItemCount : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
			}

			ncount -= pMsgCompose->materials[i].nItemCount;
			if (!RemoveItem( pMsgCompose->materials[i].nItemBagType, pMsgCompose->materials[i].nItemIndex, pMsgCompose->materials[i].nItemCount, pMsgCompose->materials[i].nItemGuid ))
			{
				xAck.nResult = MsgZhuJiangComposeAck::ECD_ErrorComposeItem;
				GettheServer().SendMsgToSingle( &xAck, this );
				return;
			}
		}
		else
		{
			//LYH日志添加 
			SCharItem * _Item = GetBagItemByGuid(pMsgCompose->materials[i].nItemGuid);
			if(_Item)
			{
				ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_Item->GetItemID());
				if(_pitem)
				theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_Item->GetItemID(),ncount,_Item->GetItemGuid(),
				_Item->GetItemCount()-ncount >= 0 ? _Item->GetItemCount()-ncount : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
			}

			if (!RemoveItem( pMsgCompose->materials[i].nItemBagType, pMsgCompose->materials[i].nItemIndex, ncount, pMsgCompose->materials[i].nItemGuid ))
			{
				xAck.nResult = MsgZhuJiangComposeAck::ECD_ErrorComposeItem;
				GettheServer().SendMsgToSingle( &xAck, this );
				return;
			}
			ncount = 0;
		}
	}
	if (pComposeRune)
	{
		//LYH日志添加 
		SCharItem * _Item = GetBagItemByGuid(pMsgCompose->composeRune.nItemGuid);
		if(_Item)
		{
			ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_Item->GetItemID());
			if(_pitem)
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_Item->GetItemID(),pMsgCompose->composeRune.nItemCount,_Item->GetItemGuid(),
			_Item->GetItemCount()-pMsgCompose->composeRune.nItemCount >= 0 ? _Item->GetItemCount()-pMsgCompose->composeRune.nItemCount : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
		}


		if (!RemoveItem( pMsgCompose->composeRune.nItemBagType, pMsgCompose->composeRune.nItemIndex, pMsgCompose->composeRune.nItemCount, pMsgCompose->composeRune.nItemGuid ))
		{
			xAck.nResult = MsgZhuJiangComposeAck::ECD_ErrorComposeRune;
			GettheServer().SendMsgToSingle( &xAck, this );
			return;
		}
	}

	int nPackIndex = 0 ;
	SCharItem  xCharItem;
	int nProbility = pData->GetProbility() + nModulus ;
	int nRand = theRand.rand16() % RAND_NUM;
	ItemDefine::SItemCommon* pItem = NULL;
	pItem = GettheItemDetail().GetItemByID( pData->GetNewItemID() );
	if ( nRand < nProbility )
	{
		xAck.nResult = MsgZhuJiangComposeAck::ECD_Success;

		__int64 nItemBigId = _NormalItemBag.GetNewItemID();
		if ( nItemBigId == InvalidLogicNumber ) 
		{ 
			xAck.nResult = MsgZhuJiangComposeAck::ECD_ItemPackFull;
			GettheServer().SendMsgToSingle( &xAck, this );
			return; 
		}

		if(pItem == NULL) 
		{ 
			xAck.nResult = MsgZhuJiangComposeAck::ECD_ErrorMaterialItem;
			GettheServer().SendMsgToSingle( &xAck, this ); 
			return; 
		}

		uint16     nCount = NUMERIC_ONE;
		if( !theRunTimeData.CreateItem( this, pData->GetNewItemID(), nCount , nItemBigId, xCharItem ) )
		{ 
			xAck.nResult = MsgZhuJiangComposeAck::ECD_Failed;
			GettheServer().SendMsgToSingle( &xAck, this ); 
			return; 
		}
		xCharItem.SetBounded(IsNeedBounded);
		for (int i = 0; i < MsgZhuJiangCompose::ECD_MaterialMaxCount; ++i )
		{
			if ( pCharItem[i] == NULL )
			{ continue; }
			if (pCharItem[i]->IsBounded())
			{
				xCharItem.SetBounded(true);
				break;
			}
		}

		//加入到物品包裹中
		int nResult = ierr_unknown;
		ItemDefine::SItemOther *pOhter = (ItemDefine::SItemOther *)pItem;
		switch ( pOhter->otherType )
		{
		case ItemDefine::OtherType_ZhujiangIdentify:
			nResult = _NormalItemBag.PushItem( xCharItem, nCount, -1, &nPackIndex   );theLogEventService.LogItemGain(GetAccountID(),GetDBCharacterID(),xCharItem.GetItemID(),nCount,xCharItem.GetItemGuid(),EIGS_Compose,GetCharName(),pItem->GetItemName());//LYH日志添加
			break;
		default:
			nResult = _MaterialItemBag.PushItem( xCharItem, nCount, -1, &nPackIndex   );theLogEventService.LogItemGain(GetAccountID(),GetDBCharacterID(),xCharItem.GetItemID(),nCount,xCharItem.GetItemGuid(),EIGS_Compose,GetCharName(),pItem->GetItemName());//LYH日志添加
			break;
		}

		if ( nResult != ierr_Success )    
		{
			xAck.nResult = MsgZhuJiangComposeAck::ECD_ItemPackFull;
			GettheServer().SendMsgToSingle( &xAck, this );
			return;
		}
		else //成功压入背包，看看该物品是不是紫色品质的，如果是 发公告。 lyh+++
		{      
			if (pOhter->ustLevel >= eIL_Nonsuch)
			{


				MsgChat chat(MsgChat::CHAT_TYPE_PROGRAM_SYSTEM);
				chat.type = GetItemBagType( pOhter->ucItemType );
				chat.nHyberItemCnt = 1;
				chat.onlyId[0] = xCharItem.itembaseinfo.nOnlyInt;
				chat.itemId[0] = xCharItem.itembaseinfo.ustItemID;

				Common::_tstring strName = pOhter->GetItemName();
				ReplaceSpecifiedName( pOhter->ustLevel, strName );

				char szChat[CHAT_STRINGMAX+1] = { 0 };
				sprintf(szChat,theXmlString.GetString( eTellAllClient_GetItemToMaxLev ),GetDefaultCountryNameById( GetCountryId() ),GetCharName(),pOhter->GetItemName());	
				ProcessSystem( szChat, SystemWorld, &chat ); 

			}
		}
	}
	else
	{
		xAck.nResult = MsgZhuJiangComposeAck::ECD_Failed;
	}

	// 扣钱
	 OperateJiaoZi( EOT_Sub, pData->GetCostMoney(), true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_ComposeZhujiang);

	// 背包里面的物品
	ItemBag*	pCreateBag = NULL;
	if (xAck.nResult != MsgZhuJiangComposeAck::ECD_Failed && pItem)
	{
		ItemDefine::SItemOther *pOhter = (ItemDefine::SItemOther *)pItem;
		switch ( pOhter->otherType )
		{
		case ItemDefine::OtherType_ZhujiangIdentify:
			pCreateBag = &_NormalItemBag;
			break;
		default:
			pCreateBag = &_MaterialItemBag;
			break;
		}
		SCharItem *pBagCahrItem = pCreateBag->GetItemByIndex(nPackIndex);
		if (pBagCahrItem == NULL)
		{ return; }
		xCharItem = *pBagCahrItem;
	}

	xAck.nItemBagType = pMsgCompose->materials[0].nItemBagType  ;
	xAck.nPackIndex   = nPackIndex   ;
	xAck.AddCharItem(xCharItem);
	GettheServer().SendMsgToSingle( &xAck, this );
}

void GamePlayer::OnQueryNewCompound(Msg* pMsg)
{
    MsgQueryCompoundNew* pCompoundNewMsg = (MsgQueryCompoundNew*)pMsg;
    if ( pCompoundNewMsg == NULL )
    { return; }

    if (!pCompoundNewMsg || pCompoundNewMsg->recipeId == InvalidLogicNumber)
    { return; }

    ItemDefine::SItemCreateItemRule* pCreatItemRule = (ItemDefine::SItemCreateItemRule*)GettheItemDetail().GetItemByID(pCompoundNewMsg->recipeId);

    if (!pCreatItemRule || !pCreatItemRule->pItemTarget|| pCreatItemRule->pItemTarget->ustItemID == InvalidLogicNumber)
    { return; }

    MsgAckCompoundNew newmsg;
    newmsg.header.stID = GetID();
    newmsg.recipeId    = pCompoundNewMsg->recipeId;

    if (_NormalItemBag.FindNullItemOffset() == -1)
    {
        newmsg.stResult = MsgAckCompoundNew::eResultBagFull;
        GettheServer().SendMsgToSingle( &newmsg, this );
    }

    short stMaterialCount[4]     = {0};
    short stMaterialCountTemp[4] = {0};

    for ( int i=0; i<4; ++i )
    {
        if ( pCreatItemRule->material[i].ustItemID == InvalidLogicNumber)
        {
            stMaterialCountTemp[i] = 0;
        }
        else
        {
            stMaterialCountTemp[i] = pCreatItemRule->material[i].ustCount;
        }
    }

    for (int n = 0; n < GetMaterialBagSize(); ++n )
    {
        SCharItem sItem;
        bool bResult = _MaterialItemBag.GetItem(n,&sItem);
        if ( !bResult)
            continue;

        for (int nloop = 0; nloop < 4; ++nloop)
        {
            if ( pCreatItemRule->material[nloop].ustItemID == InvalidLogicNumber)
                continue;

            if (sItem.itembaseinfo.ustItemID == pCreatItemRule->material[nloop].ustItemID)
            {
                stMaterialCount[nloop] += sItem.itembaseinfo.ustItemCount;
            }
        }
    }

    // 判断材料是否够了
    bool bIsMaterialEnough = true;
    for (int i=0; i<4; ++i)
    {
        if ( (stMaterialCount[i] < pCreatItemRule->material[i].ustCount) )
        {   
            bIsMaterialEnough = false;
            break;
        }            
    }    

    if( !bIsMaterialEnough )
    {
        newmsg.stResult = MsgAckCompoundNew::eResultMaterialUnconformity;
        goto tagEnd;
    }

    // 钱是否够 
    if (GetMoney() + GetJiaoZi() < pCreatItemRule->nNeedMenoy)
    {   
        newmsg.stResult = MsgAckCompoundNew::eResultNotEnoughMoney;
        goto tagEnd;
    }

    bool bIsSuc = true;
    for (int m = 0; m < 4; ++m )
    {   
        if ( pCreatItemRule->material[m].ustItemID == InvalidLogicNumber)
            continue;

       // Log("合成删除物品\t%d\t%d", pCreatItemRule->material[m].ustItemID,stMaterialCountTemp[m]);
		Log(theXmlString.GetString(eServerLog_HeChengDelItem), pCreatItemRule->material[m].ustItemID,stMaterialCountTemp[m]);

        if (_MaterialItemBag.PopItemByID(pCreatItemRule->material[m].ustItemID, stMaterialCountTemp[m] ) != ierr_Success )
        {
            bIsSuc = false;
            stMaterialCountTemp[m] = 0;
            break;
        }
    }

    if ( !bIsSuc )
    {        
        newmsg.stResult = MsgAckCompoundNew::eResultMaterialUnconformity;
        goto tagEnd;
    }

    //int nLuck     = _buffManager.GetCompoundRate();
    int nRandNum  = theRand.rand32() % 10000;
    int nSuccRate = pCreatItemRule->iCreateSuccRate;
    //nSuccRate     += nLuck;

    if ( nRandNum > nSuccRate )
    {
        newmsg.stResult = MsgAckCompoundNew::eResultFaild;
        goto tagEnd;
    }

    {
        __int64 nBigId = _NormalItemBag.GetNewItemID();
        if ( nBigId == -1)
            return;

        SCharItem stItem;
        if ( theRunTimeData.CreateItem( this, pCreatItemRule->pItemTarget->ustItemID ,1, nBigId,  stItem ) )
        {
            unsigned short ustCount = 1;

            Log(theXmlString.GetString(eLog_info_2slk_155), stItem.itembaseinfo.ustItemID,ustCount);

            ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID(pCreatItemRule->pItemTarget->ustItemID);
            if (pItem == NULL)
            { return; }

            int nResult = ierr_unknown;
            switch ( pItem->ucItemType )
            {
            case ItemDefine::ITEMTYPE_MATERIAL:
            case ItemDefine::ITEMTYPE_GEM:
                nResult = _MaterialItemBag.PushItem( stItem, ustCount ); 
				theLogEventService.LogItemGain(GetAccountID(),GetDBCharacterID(),stItem.GetItemID(),ustCount,stItem.GetItemGuid(),EIGS_Compose,GetCharName(),pItem->GetItemName());//LYH日志添加
                break;
            case ItemDefine::ITEMTYPE_TASK:
                nResult = _TaskItemBag.PushItem( stItem, ustCount ); 
				theLogEventService.LogItemGain(GetAccountID(),GetDBCharacterID(),stItem.GetItemID(),ustCount,stItem.GetItemGuid(),EIGS_Compose,GetCharName(),pItem->GetItemName());//LYH日志添加
                break;
            default:
                nResult = _NormalItemBag.PushItem( stItem, ustCount ); 
				theLogEventService.LogItemGain(GetAccountID(),GetDBCharacterID(),stItem.GetItemID(),ustCount,stItem.GetItemGuid(),EIGS_Compose,GetCharName(),pItem->GetItemName());//LYH日志添加
                break;
            }

            if ( ierr_Success != nResult )
            {
                newmsg.stResult = MsgAckCompoundNew::eResultFaild;
                goto tagEnd;
            }
            newmsg.stResult = MsgAckCompoundNew::eResultSuccess;
            memcpy(&newmsg.item,&stItem,sizeof(SCharItem));        
        }

        OperateJiaoZi( EOT_Sub, pCreatItemRule->nNeedMenoy, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_ItemCompose);
    }

tagEnd:
    GettheServer().SendMsgToSingle( &newmsg, this );
}

struct SMaterialMappingIndex
{
    int   materialId; // 材料Id
    short bagIndex;   // 材料位置
};

typedef std::vector<SMaterialMappingIndex>      MaterialMappingIndexContainer;
typedef MaterialMappingIndexContainer::iterator ItrMaterialMappingIndexContainer;

void GamePlayer::OnMsgRecipeCompoundItem( Msg* pMsg )
{
    MsgQueryCompoundNew* pCompoundNewMsg = (MsgQueryCompoundNew*)pMsg;
    if ( pCompoundNewMsg == NULL || pCompoundNewMsg->recipeId == ErrorUnsignedShortID )
    { return; }

    MsgAckCompoundNew newmsg;
    newmsg.header.stID = GetID();
    newmsg.recipeId    = pCompoundNewMsg->recipeId;

    if( !_recipeManager.IsExistRecipe(pCompoundNewMsg->recipeId) )
    { return; }

    // 拿到处方
    RecipeConfig::SRecipe* pRecipe = theRecipeConfig.GetItemRuleByRuleId( pCompoundNewMsg->recipeId );
    if ( pRecipe == NULL )
    { return; }

	//判断技能等级限制
	uint16 unSkillId = theRecipeConfig.GetSkillIdByRecipeType( pRecipe->Type );
	if ( unSkillId == InvalidLogicNumber )
		return;
	SCharSkill* pCharSkill1 = _SkillBag.GetSkillByID( unSkillId );
	if ( !pCharSkill1 || pCharSkill1->stSkillLevel < pRecipe->SkillLevelLimit )
		return;

    // 材料是否够足够
	RecipeConfig::MaterialContainer mainMaterailList;
	RecipeConfig::ItrMaterialContainer it = pRecipe->PrimaryMaterials.begin();
	RecipeConfig::ItrMaterialContainer itEnd = pRecipe->PrimaryMaterials.end();
    for ( ; it != itEnd; ++it )
    {
		int nMaterailCount = 0;
		for ( int index = 0; index < it->vecMaterailIDList.size(); ++index )
		{
			RecipeConfig::SMaterial mainMaterail;
			mainMaterail.vecMaterailIDList.push_back(it->vecMaterailIDList[index]);
			//mainMaterail.Count = _MaterialItemBag.GetItemCount(it->vecMaterailIDList[index]);

			ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID( it->vecMaterailIDList[index]);
			if (!pItemCommon)
				continue;
			switch ( pItemCommon->ucItemType )
			{
			case ItemDefine::ITEMTYPE_MATERIAL:
			case ItemDefine::ITEMTYPE_GEM:
				mainMaterail.Count = _MaterialItemBag.GetItemCount(it->vecMaterailIDList[index]);
				break;
			case ItemDefine::ITEMTYPE_TASK:
				mainMaterail.Count = _TaskItemBag.GetItemCount(it->vecMaterailIDList[index]);
				break;
			default:
				mainMaterail.Count = _NormalItemBag.GetItemCount(it->vecMaterailIDList[index]);
				break;
			}

			mainMaterailList.push_back(mainMaterail);
			nMaterailCount += mainMaterail.Count;
		}
        //if ( _MaterialItemBag.GetItemCount( pRecipe->PrimaryMaterials[i].MaterialId ) < pRecipe->PrimaryMaterials[i].Count )
		if ( nMaterailCount < it->Count )
        { // 判断材料是否够了
            newmsg.stResult    = MsgAckCompoundNew::eResultMaterialUnconformity;
            GettheServer().SendMsgToSingle( &newmsg, this );
            return;
        }
    }

    // 整理辅助材料
    std::vector<short> historyIndexs;
    MaterialMappingIndexContainer   materialMappingIndexs;
    RecipeConfig::MaterialContainer materials;
    for ( int i=0; i<MsgQueryCompoundNew::ECD_MaxAssistantItemCount; ++i )
    {
        if ( pCompoundNewMsg->assistantItemBagIndex[i] == -1)
        { break; }

        std::vector<short>::iterator itIndex = std::find( historyIndexs.begin(), historyIndexs.end(), pCompoundNewMsg->assistantItemBagIndex[i] );
        if ( itIndex != historyIndexs.end() )
        {
            newmsg.stResult = MsgAckCompoundNew::eResultRepeatedIndex;
            GettheServer().SendMsgToSingle( &newmsg, this );
            return;

        }
        historyIndexs.push_back(pCompoundNewMsg->assistantItemBagIndex[i]);

        SCharItem* pCharItem = _MaterialItemBag.GetItemByIndex( pCompoundNewMsg->assistantItemBagIndex[i] );
        if ( pCharItem == NULL )
        { 
            newmsg.stResult = MsgAckCompoundNew::eResultItemNotExistByIndex;
            GettheServer().SendMsgToSingle( &newmsg, this );
            return;
        }

        ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID(pCharItem->itembaseinfo.ustItemID);
        if ( pItemCommon == NULL )
        { 
            newmsg.stResult = MsgAckCompoundNew::eResultItemConfigInvalid;
            GettheServer().SendMsgToSingle( &newmsg, this );
            return;
        }

        if ( pItemCommon->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
        { 
            newmsg.stResult = MsgAckCompoundNew::eResultItemTypeError;
            GettheServer().SendMsgToSingle( &newmsg, this );
            return;
        }

        ItemDefine::SCreateMaterial* pMaterial = (ItemDefine::SCreateMaterial*) pItemCommon;
        if ( pMaterial->stMaterialType != ItemDefine::ematerial_compound)
        { 
            newmsg.stResult = MsgAckCompoundNew::eResultItemTypeError;
            GettheServer().SendMsgToSingle( &newmsg, this );
            return;
        }

        SMaterialMappingIndex materialMappingIndex;
        materialMappingIndex.materialId = pCharItem->itembaseinfo.ustItemID;
        materialMappingIndex.bagIndex   = pCompoundNewMsg->assistantItemBagIndex[i];
        materialMappingIndexs.push_back( materialMappingIndex );

        RecipeConfig::SMaterial material;
        //material.MaterialId = pCharItem->itembaseinfo.ustItemID;
		material.vecMaterailIDList.push_back(pCharItem->itembaseinfo.ustItemID);
        materials.push_back( material );
    }   

    // 得到产品
    RecipeConfig::SProduct product;
    long nResult = pRecipe->GetProduct( materials, product );
    if ( nResult != RecipeConfig::SRecipe::EMR_OK )
    {   
        newmsg.stResult = MsgAckCompoundNew::eResultNotInvalidProduct;
        GettheServer().SendMsgToSingle( &newmsg, this );
        return;
    }

    // 钱是否够
    if ( GetMoney() + GetJiaoZi() < product.NeedMoney )
    {   
        newmsg.stResult = MsgAckCompoundNew::eResultNotEnoughMoney;
        GettheServer().SendMsgToSingle( &newmsg, this );
        return;
    }

    // 精力是否够
    if ( GetActivity() < product.NeedActivity )
    {
        newmsg.stResult = MsgAckCompoundNew::eResultNotEnoughEnergy;
        GettheServer().SendMsgToSingle( &newmsg, this );
        return;
    }
    // 随机出物品
    RecipeConfig::ItrItemContainer itItem    = product.ProductItems.begin();
    RecipeConfig::ItrItemContainer itItemEnd = product.ProductItems.end();
    std::map<unsigned char, unsigned char> randTable;
    int nKeyRand = 0;
    for ( int i=0; itItem != itItemEnd; ++itItem, ++i )
    {
        nKeyRand += (*itItem).Probility;
        randTable.insert( std::map<unsigned char, unsigned char>::value_type(nKeyRand, i));
    }

    int randNum = theRand.rand32() % RAND_NUM;
    std::map<unsigned char, unsigned char>::iterator itRand = randTable.upper_bound(randNum);
    if ( itRand == randTable.end() || itRand->second >= product.ProductItems.size() )
    { 
		newmsg.stResult = MsgAckCompoundNew::eResultFaild;
		GettheServer().SendMsgToSingle( &newmsg, this );
		return; 
	}

    __int64 nBigId = _NormalItemBag.GetNewItemID();
    if ( nBigId == -1)
    { 
        newmsg.stResult = MsgAckCompoundNew::eResultSystemBusy;
        GettheServer().SendMsgToSingle( &newmsg, this );
        return;
    }

	uint8 nBagType = 0;
    SCharItem stItem;
    if ( theRunTimeData.CreateItem( this, product.ProductItems[itRand->second ].ItemId, product.ProductItems[itRand->second ].Count, nBigId,  stItem ) )
    {
        Log(theXmlString.GetString(eLog_info_2slk_155), stItem.itembaseinfo.ustItemID, stItem.itembaseinfo.ustItemCount );
        ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID(stItem.itembaseinfo.ustItemID);
        if (pItem == NULL)
        { return; }

        stItem.SetBounded(product.ProductItems[itRand->second ].bIsBound);

        //星级处理
        stItem.SetStarLevel( product.ProductItems[itRand->second ].bIsStarRandom, product.ProductItems[itRand->second ].nStarLevel );

		theRunTimeData.EquipScore(stItem, GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID )); // 计算装备评分

		strcpy_s( stItem.itembaseinfo.szCreaterName, sizeof( stItem.itembaseinfo.szCreaterName ), GetCharName() );

        //int nResult = ierr_unknown;
		bool canPush = false;
		bool bUseNewGrid = false;
        switch ( pItem->ucItemType )
        {
        case ItemDefine::ITEMTYPE_MATERIAL:
        case ItemDefine::ITEMTYPE_GEM:
			{
				//nResult = _MaterialItemBag.PushItem( stItem, product.ProductItems[itRand->second ].Count  );
				canPush = _MaterialItemBag.CanPushItem( stItem, bUseNewGrid );
				nBagType = BT_MaterialBag;
			}
            break;
        case ItemDefine::ITEMTYPE_TASK:
			{
				//nResult = _TaskItemBag.PushItem( stItem, product.ProductItems[itRand->second ].Count  );
				canPush = _TaskItemBag.CanPushItem( stItem, bUseNewGrid );
				nBagType = BT_TaskBag;
			}
            break;
        default:
			{
				//nResult = _NormalItemBag.PushItem( stItem, product.ProductItems[itRand->second ].Count  );
				canPush = _NormalItemBag.CanPushItem( stItem, bUseNewGrid );
				nBagType = BT_NormalItemBag;
			}
            break;
        }

        if ( /*ierr_Success != nResult*/ !canPush )
        {
            newmsg.stResult = MsgAckCompoundNew::eResultBagFull;
            GettheServer().SendMsgToSingle( &newmsg, this );
            return;
        }
        memcpy(&newmsg.item,&stItem,sizeof(SCharItem));        
    }

    // 删除辅助材料
    for ( int i=0; i<product.SecondaryMaterials.size(); ++i )
    {
        ItrMaterialMappingIndexContainer it    = materialMappingIndexs.begin();
        ItrMaterialMappingIndexContainer itEnd = materialMappingIndexs.end();
        bool bHaveMiss = true;
        for ( ; it!=itEnd; ++it )
        {
			for ( int j = 0; j < product.SecondaryMaterials[i].vecMaterailIDList.size(); ++j )
			{
				//if ( product.SecondaryMaterials[i].MaterialId == (*it).materialId)
				if ( product.SecondaryMaterials[i].vecMaterailIDList[j] == (*it).materialId)
				{
					unsigned short ustCount = 1;
					//Log("合成删除物品\t%d\t%d\t%d", product.SecondaryMaterials[i].MaterialId, ustCount, (*it).bagIndex);
					//Log("合成删除物品\t%d\t%d\t%d", (*it).materialId, ustCount, (*it).bagIndex);
					Log(theXmlString.GetString(eServerLog_HeChengDelItem2), (*it).materialId, ustCount, (*it).bagIndex);

					if (_MaterialItemBag.PopItem( (*it).bagIndex, ustCount ) != ierr_Success )
					{
						newmsg.stResult    = MsgAckCompoundNew::eResultPopItem;
						GettheServer().SendMsgToSingle( &newmsg, this );
						return;
					}
					bHaveMiss = false;

					newmsg.AddConsumeAssistantItemIndex( (*it).bagIndex );
				}
			}
        }

        if ( bHaveMiss )
        {
            newmsg.stResult    = MsgAckCompoundNew::eResultFindItemException;
            GettheServer().SendMsgToSingle( &newmsg, this );
            return;
        }
    }

    // 删除主材料
    for (int i=0; i<pRecipe->PrimaryMaterials.size(); ++i )
    {
		int nNeedCount = pRecipe->PrimaryMaterials[i].Count;
		for ( int idIndex = 0; idIndex < pRecipe->PrimaryMaterials[i].vecMaterailIDList.size(); ++idIndex )
		{
			int materialID = pRecipe->PrimaryMaterials[i].vecMaterailIDList[idIndex];
			for ( int mainMaterailListIndex = 0; mainMaterailListIndex < mainMaterailList.size(); ++mainMaterailListIndex )
			{
				if ( mainMaterailList[mainMaterailListIndex].vecMaterailIDList.empty() )
				{ continue; }
				if ( mainMaterailList[mainMaterailListIndex].vecMaterailIDList[0] == materialID )
				{
					int nPopCount = min( nNeedCount, mainMaterailList[mainMaterailListIndex].Count );
					/*Log("合成删除物品\t%d\t%d]", materialID, nPopCount);*/
					Log(theXmlString.GetString(eServerLog_HeChengDelItem),materialID, nPopCount);
					//if (_MaterialItemBag.PopItemByID(materialID, nPopCount ) != ierr_Success )

					//LYH日志添加
					SCharItem *_item = GetBagItemByGuid(GetItemGUIDByItemID(materialID));
					ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(materialID);
					if(_pitem && _item)
					theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),materialID,nPopCount,GetItemGUIDByItemID(materialID),
					_item->GetItemCount()-nPopCount >= 0 ? _item->GetItemCount()-nPopCount : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());

					if ( ! RemoveItem(materialID, nPopCount) )
					{
						newmsg.stResult = MsgAckCompoundNew::eResultPopItem;
						GettheServer().SendMsgToSingle( &newmsg, this );            
						return;
					}

					nNeedCount -= nPopCount;
					if ( nNeedCount <= 0 )
					{ break; }
				}
			}
			if ( nNeedCount <= 0 )
			{ break; }
		}
//         Log("合成删除物品\t%d\t%d]", pRecipe->PrimaryMaterials[i].MaterialId, pRecipe->PrimaryMaterials[i].Count);
// 
//         if (_MaterialItemBag.PopItemByID(pRecipe->PrimaryMaterials[i].MaterialId, pRecipe->PrimaryMaterials[i].Count ) != ierr_Success )
//         {
//             newmsg.stResult = MsgAckCompoundNew::eResultPopItem;
//             GettheServer().SendMsgToSingle( &newmsg, this );            
//             return;
//         }
    }

    // 扣钱
    OperateJiaoZi( EOT_Sub, product.NeedMoney, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_ItemCompose); 

    // 扣活力
    gCharInfoServer.baseinfo.liveinfo.activity -= product.NeedActivity; 

    MsgCharAttrChanged msgChanged;
    msgChanged.iChangeCount = 0;
    msgChanged.header.stID = GetID();
    msgChanged.AddAttrShortChange( CharAttr_Energy, gCharInfoServer.baseinfo.liveinfo.activity );

    uint16 nSkillID = theRecipeConfig.GetSkillIdByRecipeType(pRecipe->Type);
    SCharSkill* pCharSkill = _SkillBag.GetSkillByID( nSkillID );
    if ( pCharSkill )
	{
		if (pCharSkill->stSkillLevel <= pRecipe->SkillLevelLimit)
		{
			unsigned short recipeValue = GetRecipeSkillPoint( pRecipe->Type );
			if ( recipeValue < pRecipe->ProficiencyLimit )
			{
				unsigned short which = GetCharAttrByRecipeType( pRecipe->Type );        // 获得类型
				int nAddValue = pRecipe->AddPointValue;
				if ( nAddValue > 0 && which > 0 )        // 有增加才改变
				{
					OperateRecipeSkillPoint( EOT_Add, nSkillID, nAddValue, __FUNCTION__, __LINE__ );
					msgChanged.AddAttrShortChange( which, GetRecipeSkillPoint( pRecipe->Type ) );
				}
			}
		}
	}

    if ( msgChanged.iChangeCount > 0 )
    { 
        msgChanged.CaluLength();
        GettheServer().SendMsgToSingle( &msgChanged, this ); 
    }

	switch ( nBagType )
	{
	case BT_NormalItemBag:
		_NormalItemBag.PushItem( stItem, product.ProductItems[itRand->second ].Count  );
		break;
	case BT_MaterialBag:
		_MaterialItemBag.PushItem( stItem, product.ProductItems[itRand->second ].Count  );
		break;
	case BT_TaskBag:
		_TaskItemBag.PushItem( stItem, product.ProductItems[itRand->second ].Count  );
		break;
	}
    
    newmsg.stResult = MsgAckCompoundNew::eResultSuccess;
    GettheServer().SendMsgToSingle( &newmsg, this );
    return;
}

uint16 GetProtectMatrial(uint16 item_star, uint16& protectLevel)
{
	if (item_star >= 6 && item_star < 9)
	{
		protectLevel = 6;
		return SID_ProtectStarSix;
	}
	else if (item_star >= 9 && item_star < 12)
	{
		protectLevel = 9;
		return SID_ProtectStarNine;
	}
	else if (item_star >= 12 && item_star < 15)
	{
		protectLevel = 12;
		return SID_ProtectStarTwelve;
	}
	else if (item_star >= 15)
	{
		protectLevel = 15;
		return SID_ProtectStarFifteen;
	}
	else
	{
		protectLevel = 0;
		return 0xffff;
	}

}

void GamePlayer::_ProcessEquipLevelUp( MsgEquipEvolve* pEquipLevelUp )
{ 
    if (pEquipLevelUp == NULL) 
    { return; }

    MsgIntensifyEquip msg;
    msg.header.stID     = GetID();
    msg.nEvolveType     = MsgEquipEvolve::ET_LevelUp;
    msg.nResult         = MsgIntensifyEquip::e_Succeed;
    msg.nNormalBagIndex = pEquipLevelUp->nNormalBagIndex;

    // 装备
    SCharItem* pEquipItem = _NormalItemBag.GetItemByOnlyBigId( pEquipLevelUp->nNormalGuid );

    // 升星材料
	bool IsMaterialBound = false;
    SCharItem* pMaterialItem = NULL;
    ItemBag*   pSelectBag    = NULL;
    switch ( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType )
    {
    case BT_MaterialBag:
        pSelectBag    = &_MaterialItemBag;
        pMaterialItem = _MaterialItemBag.GetItemByOnlyBigId( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid );
        break;
    default:
        pSelectBag    = &_NormalItemBag;
        pMaterialItem = _NormalItemBag.GetItemByOnlyBigId( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid );
    }

    if ( pEquipItem == NULL || pMaterialItem == NULL || pSelectBag == NULL )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pEquipItem->GetItemGuid() != pEquipLevelUp->nNormalGuid )
    {
        _NormalItemBag.CleanUp();
        return;
    }

    if ( pMaterialItem->GetItemGuid() != pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid )
    {
        pSelectBag->CleanUp();
        return;
    }

	if ( pMaterialItem->IsBounded() )
	{
		IsMaterialBound = true;
	}

    // 已经是最高星级
    if ( pEquipItem->equipdata.ucLevel >= SCharItem::EL_StarMax )
    {
        msg.nResult = MsgIntensifyEquip::e_IntensifyMax;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 目标装备
    ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*) GettheItemDetail().GetItemByID( pEquipItem->itembaseinfo.ustItemID );
    if ( pItemCanEquip == NULL)
    { return; }

    if ( pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    { return; }

    if (pItemCanEquip->bFashion || pItemCanEquip->IsCannotEvolve() )
    {  
        msg.nResult = MsgIntensifyEquip::e_FashionCanNotEvolve;
        GettheServer().SendMsgToSingle(&msg,this);
        return; 
    }

//      // 非紫色装备只能到9星
//     if ( pEquipItem->equipdata.ucLevel >= SCharItem::EL_Notice && pEquipItem->equipdata.quality < ItemDefine::EQL_Purple )
//     {
//         msg.nResult = MsgIntensifyEquip::e_IntensifyMax;
//         GettheServer().SendMsgToSingle(&msg,this);
//         return; 
//     }

	unsigned short oldLeve[1] = {pEquipItem->equipdata.ucLevel};

    // 得到升星数据
    StarLevelUpData* pLevelUpData = theStarLevelUpConfig.GetStarLevelUpData( pItemCanEquip->stEquipLevelReq, pEquipItem->equipdata.ucLevel );
    if ( pLevelUpData == NULL )
    { return; }

    //先判断钱够不够
    if ( pLevelUpData->GetCostMoney() > GetJiaoZiMoney() )
    {
        msg.nResult = MsgIntensifyEquip::e_NotEnoughMoney;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 判断限制条件  
    ItemDefine::SCreateMaterial* pMeterialItemConfig = (ItemDefine::SCreateMaterial*) GettheItemDetail().GetItemByID( pMaterialItem->itembaseinfo.ustItemID );
    if ( pMeterialItemConfig == NULL )
    { return; }

    if ( pMeterialItemConfig->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
    { 
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pMeterialItemConfig->stMaterialType != ItemDefine::ematerial_starlevel )    // 不是升星材料
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 判断是否是可作用的装备部位
    if ( !pMeterialItemConfig->CanEquipPart( pItemCanEquip->ustEquipType )  )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotMatch;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 材料等级装备等级限制
    if ( pMeterialItemConfig->levelLowLimit > pItemCanEquip->stEquipLevelReq  )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep; 
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pMeterialItemConfig->levelUpLimit < pItemCanEquip->stEquipLevelReq  )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep; 
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pEquipItem->equipdata.ucLevel < pMeterialItemConfig->starLevelLimit )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep; 
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 判断品质
    if ( pEquipItem->equipdata.quality < pMeterialItemConfig->equipQuality)
    {
        msg.nResult = MsgIntensifyEquip::e_NotEnoughQuality;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    float fProbability = pLevelUpData->GetProbability() + 
		pMeterialItemConfig->fAddIntensifyRate[pEquipItem->equipdata.ucLevel] / 100 * pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].value; // 升星百分比

    uint16 nResult  = MsgIntensifyEquip::e_Succeed;
    uint8  nRandNum = theRand.rand16() % RAND_NUM;

	//LYH日志添加
	SCharItem * _item = GetBagItemByGuid(pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid );
	if(_item)
	{
		uint16 nCount = pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].value;
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
		if( !theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),nCount,
			_item->GetItemGuid(),_item->GetItemCount()-nCount >= 0 ? _item->GetItemCount()-nCount : 0,
			eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName()))
		{
			/*Log("删除升星材料\t<INDEX:%d\t数量:%d>", pMaterialItem->itembaseinfo.ustItemID, pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].value);*/

			Log(theXmlString.GetString(eServerLog_UpStar_Material),pMaterialItem->itembaseinfo.ustItemID, pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].value);
		}
	}

	// 扣除升星材料
	if (!RemoveItem( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType,
		pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex,
		/*NUMERIC_ONE*/pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].value, 
		pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid ))
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

    if ( nRandNum > fProbability * RAND_NUM ) // 判断升星成功概率
    {
        nResult = MsgIntensifyEquip::e_Lost;
		if (pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].protectStar)
		{
			unsigned short protectItemId = 0xffff;
			uint16 protectLevel = 0;
			/*switch (pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].protectStar)
			{
			case 6:
				protectItemId = SID_ProtectStarSix;
				break;
			case 9:
				protectItemId = SID_ProtectStarNine;
				break;
			case 12:
				protectItemId = SID_ProtectStarTwelve;
				break;
			case 15:
				protectItemId = SID_ProtectStarFifteen;
				break;
			default:
				break;
			}*/

			protectItemId = GetProtectMatrial(pEquipItem->equipdata.ucLevel, protectLevel);

			if (protectItemId != 0xffff)
			{
				/*Log("删除保星材料\t<INDEX:%d\t数量:%d>", protectItemId, NUMERIC_ONE);*/
				//LYH日志添加
				ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(protectItemId);
				SCharItem *_pItemP = GetBagItemByGuid(GetItemGUIDByItemID(protectItemId));
				if(_pitem && _pItemP)
				{
					if(!theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),protectItemId,NUMERIC_ONE,GetItemGUIDByItemID(protectItemId),
						_pItemP->GetItemCount()-NUMERIC_ONE >= 0 ? _pItemP->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,
						GetCharName(),_pitem->GetItemName()))
						Log(theXmlString.GetString(eServerLog_UpStar_Material),protectItemId, NUMERIC_ONE);
				}

			}

			SCharItem* pProtectItem = _MaterialItemBag.GetItemByItemID( protectItemId );
			if ( pProtectItem && pProtectItem->IsBounded() )
				IsMaterialBound = true;

			//扣除保星材料
			if (protectItemId == 0xffff||!RemoveItem(protectItemId, NUMERIC_ONE) )
				pEquipItem->equipdata.ucLevel = pLevelUpData->GetLossToLevel();
			else
			{
				pEquipItem->equipdata.ucLevel = protectLevel;
			}
		}
		else
			pEquipItem->equipdata.ucLevel = pLevelUpData->GetLossToLevel();
    }
    else
    {
		
        pEquipItem->equipdata.ucLevel += 1;
		
		//扣除保星材料
		if (pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].protectStar)
		{
			unsigned short protectItemId = 0;

			switch (pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].protectStar)
			{
			case 6:
				protectItemId = SID_ProtectStarSix;
				break;
			case 9:
				protectItemId = SID_ProtectStarNine;
				break;
			case 12:
				protectItemId = SID_ProtectStarTwelve;
				break;
			case 15:
				protectItemId = SID_ProtectStarFifteen;
				break;
			default:
				break;
			}

			/*Log("删除保星材料\t<INDEX:%d\t数量:%d>", protectItemId, NUMERIC_ONE);*/
			ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(protectItemId);
			SCharItem *_pItemP = GetBagItemByGuid(GetItemGUIDByItemID(protectItemId));

			if(_pitem && _pItemP)
			{
				if(!theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),protectItemId,NUMERIC_ONE,GetItemGUIDByItemID(protectItemId),
					_pItemP->GetItemCount()-NUMERIC_ONE >= 0 ? _pItemP->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName()))
				{
					Log(theXmlString.GetString(eServerLog_UpStar_Material),protectItemId, NUMERIC_ONE);
				}
			}
			SCharItem* pProtectItem = _MaterialItemBag.GetItemByItemID( protectItemId );
			if ( pProtectItem && pProtectItem->IsBounded() )
				IsMaterialBound = true;

			RemoveItem(protectItemId, NUMERIC_ONE);
		}
    }

	if ( IsMaterialBound )
	{
		pEquipItem->SetBounded(true);
	}

    /*Log( "升星物品[%s] 结果:[%d], 目前[%d]星!", pItemCanEquip->GetItemName(), nResult, pEquipItem->equipdata.ucLevel );*/
	unsigned short CurLeve[1] = {pEquipItem->equipdata.ucLevel};

	//LYH日志添加
	if(!theLogEventService.LogItemUpgrade(GetAccountID(),GetDBCharacterID(),pEquipItem->GetItemID(),1,pEquipItem->GetItemGuid(),eItemLogInfo_ItemUpgrade_Intensify,0,oldLeve,CurLeve,
		                                  GetCharName(),pItemCanEquip->GetItemName()))
	{
        Log(theXmlString.GetString(eServerLog_UpStar), pItemCanEquip->GetItemName(), nResult, pEquipItem->equipdata.ucLevel );
	}
	

    OperateJiaoZi( EOT_Sub, pLevelUpData->GetCostMoney(), true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_Intensify );

	theRunTimeData.EquipScore(*pEquipItem, GettheItemDetail().GetItemByID( pEquipItem->itembaseinfo.ustItemID )); // 计算装备评分

	if ( nResult == MsgIntensifyEquip::e_Succeed )
	{
		// 装备星级大于12 系统提示 
		if ( pEquipItem->equipdata.ucLevel > SCharItem::EL_Notice )
		{
			MsgChat chat(MsgChat::CHAT_TYPE_PROGRAM_SYSTEM);
			chat.type = GetItemBagType( pItemCanEquip->ucItemType );
			chat.nHyberItemCnt = 1;
			chat.onlyId[0] = pEquipItem->itembaseinfo.nOnlyInt;
			chat.itemId[0] = pEquipItem->itembaseinfo.ustItemID;

			Common::_tstring strName = pItemCanEquip->GetItemName();
			ReplaceSpecifiedName( pItemCanEquip->ustLevel, strName );

			char bufStr[BUFSIZ] = {0};
			if ( pEquipItem->equipdata.ucLevel == SCharItem::EL_Notice )
			{
				sprintf_s( bufStr,sizeof(bufStr),theXmlString.GetString(eTellAllClient_EquipLevelUpToMax), GetCharName(), strName.c_str(), s_szChineseNumericString[SCharItem::EL_Notice] );
			}
			else
			{
				sprintf_s( bufStr,sizeof(bufStr),theXmlString.GetString(eTellClient_EquipLevelUpTo10), GetCharName(), strName.c_str(), s_szChineseNumericString[pEquipItem->equipdata.ucLevel] );
			}

			ProcessSystem( bufStr, SystemWorld, &chat );

			// 12星以上要全服奖励经验 策划说不要了 lrt
			/*if ( pEquipItem->equipdata.ucLevel > SCharItem::EL_Notice )
			{
			CS2GSMsgRewardOperate xReward;
			xReward.uchType = CS2GSMsgRewardOperate::ECD_Exp;
			xReward.dwValue = GetLevel() * g_Cfg.nEquipTopStarExp;
			GettheServer().SendMsgToCenterServer( &xReward );
			}*/
		}
	}

    msg.nResult = nResult;
    msg.AddCharItem( *pEquipItem );
    GettheServer().SendMsgToSingle( &msg,this );

    _achieveManager.UpdateTriggerByValueType( EAT_EquipStar ,pEquipItem->equipdata.ucLevel );
	//触发装备升星任务
	TriggerSpecialQuest(ESTT_EquipStar);
}

void GamePlayer::_ProcessEquipUnknowIdentify( MsgEquipEvolve* pEquipLevelUp )
{
	if (pEquipLevelUp == NULL) 
	{ return; }

	MsgIntensifyEquip msg;
	msg.header.stID            = GetID();
	msg.nEvolveType           = MsgEquipEvolve::ET_UnknowIdentify;
	msg.nResult               = MsgIntensifyEquip::e_Succeed;
	msg.nNormalBagIndex       = pEquipLevelUp->nNormalBagIndex;

	// 未知装备
	SCharItem* pEquipItem    = _NormalItemBag.GetItemByIndex( pEquipLevelUp->nNormalBagIndex );
	ItemBag* pMaterialBag = NULL;
	SCharItem* pMaterialItem = NULL;
	switch ( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType )
	{
	case BT_MaterialBag:
		pMaterialItem       = _MaterialItemBag.GetItemByIndex( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
		pMaterialBag = &_MaterialItemBag;
		break;
	default:
		pMaterialItem       = _NormalItemBag.GetItemByIndex( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
		pMaterialBag = &_NormalItemBag;
	}
	if ( pEquipItem == NULL || pMaterialBag == NULL || pMaterialItem == NULL)
	{
		msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

	if ( pEquipItem->GetItemGuid() != pEquipLevelUp->nNormalGuid )
	{
		_NormalItemBag.CleanUp();
		return;
	}
	if ( pMaterialItem->GetItemGuid() != pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid )
	{
		_MaterialItemBag.CleanUp();
		return;
	}

	// 目标物品属性是否存在
	ItemDefine::SItemCommon* pItemEquipCommonConfig = GettheItemDetail().GetItemByID( pEquipItem->itembaseinfo.ustItemID );
	if ( pItemEquipCommonConfig == NULL )
	{  return; }

// 	if ( pItemEquipCommonConfig->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItemEquipCommonConfig->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
// 	{ return;}

// 	ItemDefine::SItemCanEquip* pItemCanEquipConfig = (ItemDefine::SItemCanEquip*)pItemEquipCommonConfig;
// 	if ( pItemCanEquipConfig == NULL || pItemCanEquipConfig->bFashion )
// 	{ return; }

	EquipEvolveConfig::SEquipUnknowIdentify* pUnknowIdentifyConfig = theEquipEvolveConfig.GetUnknowIdentify( pEquipItem->itembaseinfo.ustItemID );
	if ( NULL == pUnknowIdentifyConfig )
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorUnknowIdentify;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

	// 是否有鉴定道具
	ItemDefine::SItemCommon* pIdentifyItemCommonConfig = GettheItemDetail().GetItemByID( pMaterialItem->itembaseinfo.ustItemID );
	if ( pIdentifyItemCommonConfig == NULL || pIdentifyItemCommonConfig->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
	{ 
		msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

	//check money
	if ( GetJiaoZiMoney() < pUnknowIdentifyConfig->nCostValue )
	{
		msg.nResult = MsgIntensifyEquip::e_NotEnoughMoney;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

	// check bag capacity
	if ( _NormalItemBag.GetItemEmptyCount() < NUMERIC_ONE)
	{
		msg.nResult = MsgIntensifyEquip::e_BagIsFull;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

	//LYH日志添加
	SCharItem * _item =  GetBagItemByGuid(pEquipLevelUp->nNormalGuid);
	if(_item)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
		theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),1,_item->GetItemGuid(),
		_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
	}

	bool IsNeedBounded = false;
	{
		if(_item)
		{
			if(_item->IsBounded())
				IsNeedBounded = true;
			for(int i =0;i<MsgEquipEvolve::EConstDefine_MaxMaterialCount;++i)
			{
				if(pEquipLevelUp->materials[i].guid == 0 || pEquipLevelUp->materials[i].guid==-1)
					continue;
				SCharItem * pItem =GetBagItemByGuid(pEquipLevelUp->materials[i].guid);
				if(!pItem)
					continue;
				if(pItem->IsBounded())
					IsNeedBounded = true;
			}
		}
	}

	// delete item
	if (!RemoveItem( BT_NormalItemBag, pEquipLevelUp->nNormalBagIndex, 1, pEquipLevelUp->nNormalGuid ))
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorUnknowIdentify;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}
	
	//LYH日志添加
	_item =  GetBagItemByGuid(pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid);
	if(_item)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
		theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
		_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
	}


	if (!RemoveItem( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType,
		pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex, 
		NUMERIC_ONE, 
		pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid ))
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

	

	//identify
	EquipEvolveConfig::SEquipUnknowIdentify::IterGetItemList it = pUnknowIdentifyConfig->getItemList.begin();
	EquipEvolveConfig::SEquipUnknowIdentify::IterGetItemList itEnd = pUnknowIdentifyConfig->getItemList.end() - 1;
	for ( ; it != itEnd; ++it )
	{
		if ( theRand.rand16() % 10000 < it->nGetItemRate )
		{
			break;
		}
	}

	//check get item
	ItemDefine::SItemCommon* pGetItemConfig = GettheItemDetail().GetItemByID( it->nGetItemID );
	if ( pGetItemConfig == NULL )
	{  return; }
	if ( pGetItemConfig->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pGetItemConfig->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
	{ return;}

	// add item
	int64 nBigID = 0;
	if ( AddEquipItem( it->nGetItemID, 1, EIGS_UnknowIdentify, IsNeedBounded /*pMaterialItem->IsBounded()*//*pUnknowIdentifyConfig->blIsBound*/, &nBigID, pUnknowIdentifyConfig->blIsStarRandom, pUnknowIdentifyConfig->nStarLevel ) != ierr_Success )
	{
		msg.nResult = MsgIntensifyEquip::e_BagIsFull;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}
	
	SCharItem* pAddItem = _NormalItemBag.GetItemByOnlyBigId(nBigID);
	if ( NULL == pAddItem )
	{ return; }

	pItemEquipCommonConfig = GettheItemDetail().GetItemByID( pAddItem->itembaseinfo.ustItemID );
	//lyh 如果随机到的物品品质是 紫色以上则发送世界公告
	if (pItemEquipCommonConfig && pItemEquipCommonConfig->ustLevel >= eIL_Nonsuch)
	{

		MsgChat chat(MsgChat::CHAT_TYPE_PROGRAM_SYSTEM);
		chat.type = 0;
		chat.nHyberItemCnt = 1;
		chat.onlyId[0] = pAddItem->itembaseinfo.nOnlyInt;
		chat.itemId[0] = pAddItem->itembaseinfo.ustItemID;

		char szChat[CHAT_STRINGMAX+1] = { 0 };
		sprintf(szChat,theXmlString.GetString( eTellAllClient_GetMaxLevItemByJD ),GetCharName(),pItemEquipCommonConfig->GetItemName());	
		ProcessSystem( szChat, SystemWorld, &chat ); 
	}

	//Log( "装备未知鉴定[%s]成功" , pGetItemConfig->GetItemName() );
	Log( theXmlString.GetString(eServerLog_IdentifyOk) , pGetItemConfig->GetItemName() );

	OperateJiaoZi( EOT_Sub, pUnknowIdentifyConfig->nCostValue, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_Identify);

	msg.AddCharItem( *pAddItem );
	SendMessageToClient( &msg );
}

void GamePlayer::_ProcessEquipIdentify( MsgEquipEvolve* pEquipLevelUp )
{
    if (pEquipLevelUp == NULL) 
    { return; }

    MsgIntensifyEquip msg;
    msg.header.stID            = GetID();
    msg.nEvolveType           = MsgEquipEvolve::ET_Identify;
    msg.nResult               = MsgIntensifyEquip::e_Succeed;
    msg.nNormalBagIndex       = pEquipLevelUp->nNormalBagIndex;


	bool IsNeedBounded = pEquipLevelUp->IsNeedChangeBound(GetDBCharacterID());
    // 装备
    SCharItem* pEquipItem    = _NormalItemBag.GetItemByIndex( pEquipLevelUp->nNormalBagIndex );

    // 宝石
    SCharItem* pIdentifyItem = NULL;
    ItemBag* pLevelupMaterialBag = NULL;
    switch ( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType )
    {
    case BT_MaterialBag:
        pIdentifyItem       = _MaterialItemBag.GetItemByIndex( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
        pLevelupMaterialBag = &_MaterialItemBag;
        break;
    default:
        pIdentifyItem       = _NormalItemBag.GetItemByIndex( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
        pLevelupMaterialBag = &_NormalItemBag;
    }

    if ( pEquipItem == NULL || pIdentifyItem == NULL || pLevelupMaterialBag == NULL )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pEquipItem->GetItemGuid() != pEquipLevelUp->nNormalGuid )
    {
        _NormalItemBag.CleanUp();
        return;
    }

    if ( pIdentifyItem->GetItemGuid() != pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid )
    {
        pLevelupMaterialBag->CleanUp();
        return;
    }

    // 目标物品属性是否存在
    ItemDefine::SItemCommon* pItemEquipCommonConfig = GettheItemDetail().GetItemByID( pEquipItem->itembaseinfo.ustItemID );
    if ( pItemEquipCommonConfig == NULL )
    {  return; }

    if ( pItemEquipCommonConfig->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItemEquipCommonConfig->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    { return;}

    ItemDefine::SItemCanEquip* pItemCanEquipConfig = (ItemDefine::SItemCanEquip*)pItemEquipCommonConfig;
    if ( pItemCanEquipConfig == NULL || pItemCanEquipConfig->bFashion )
    { return; }

    // 得到升星数据 用于鉴定
    StarLevelUpData* pUpConfig = theStarLevelUpConfig.GetStarLevelUpData( pItemCanEquipConfig->stEquipLevelReq, 0 );
    if ( pUpConfig == NULL )
    { return; }

    int costMoney = pUpConfig->GetCostMoney() * 2;
    //先判断钱够不够
    if ( GetMoney() + GetJiaoZi() < costMoney )
    {
        msg.nResult = MsgIntensifyEquip::e_NotEnoughMoney;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 是否有鉴定道具
    ItemDefine::SItemCommon* pIdentifyItemCommonConfig = GettheItemDetail().GetItemByID( pIdentifyItem->itembaseinfo.ustItemID );
    if ( pIdentifyItemCommonConfig == NULL || pIdentifyItemCommonConfig->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
    { 
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    ItemDefine::SCreateMaterial* pMaterialIdentifyItemConfig = (ItemDefine::SCreateMaterial*)pIdentifyItemCommonConfig;
    if ( pMaterialIdentifyItemConfig->stMaterialType != ItemDefine::ematerial_identify )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 宝石等级小于装备等级
    if ( pMaterialIdentifyItemConfig->levelUpLimit < pItemCanEquipConfig->stEquipLevelReq )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep; // 宝石等级不够
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }
//modified by junyi.chen begin
//     // 随机个数
//     short sRandNum = pItemCanEquipConfig->additiveRandCount;
//     if (sRandNum <= 0)
//     { 
//         msg.nResult = MsgIntensifyEquip::e_ItemCantIdentify;
//         GettheServer().SendMsgToSingle(&msg,this);
//         return;
//     }
// 
//     bool bIsFixedRand = false;
//     for (int i = 0; i<sRandNum; ++i)
//     {
//         if ( pItemCanEquipConfig->additiveRandFlags[i] )
//         { // 数值
//             bIsFixedRand = true;
//             break;
//         }
//     }
// 
//     // 是否是固定鉴定
//     if ( bIsFixedRand )
//     {
//         msg.nResult = MsgIntensifyEquip::e_ItemCantIdentify;
//         GettheServer().SendMsgToSingle(&msg,this);
//         return;
//     }
//end
    // 是否已经鉴定过
//    if ( pEquipItem->equipdata.baseRands[0] != InvalidLogicNumber )
	if ( pEquipItem->HasBaseRanded() )
    { 
        if ( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagIndex == -1 )
        {  // 已经鉴定
            msg.nResult = MsgIntensifyEquip::e_HaveIdentify;
            GettheServer().SendMsgToSingle(&msg,this);
            return;
        }

        // 如果有鉴定回炉道具, 判断鉴定回炉道具, 可以重新鉴定
        SCharItem* pMaterialItem = NULL;
        switch( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagType )
        {
        case BT_MaterialBag:
            pMaterialItem = _MaterialItemBag.GetItemByIndex( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagIndex );
            break;
        case BT_NormalItemBag:
            pMaterialItem = _NormalItemBag.GetItemByIndex( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagIndex );
            break;
        }

        if ( pMaterialItem == NULL || pMaterialItem->GetItemGuid() != pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].guid )
        {
            msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
            SendMessageToClient( &msg );
            return;
        }

        ItemDefine::SItemCommon* pIdentifyItemCommonConfig = GettheItemDetail().GetItemByID( pMaterialItem->GetItemID() );
        if ( pIdentifyItemCommonConfig == NULL || pIdentifyItemCommonConfig->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
        { 
            msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
            SendMessageToClient( &msg );
            return;
        }

        ItemDefine::SCreateMaterial* pMaterialIdentifyItemConfig = (ItemDefine::SCreateMaterial*)pIdentifyItemCommonConfig;
        if ( pMaterialIdentifyItemConfig->stMaterialType != ItemDefine::ematerial_reidentify )
        {
            msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
            SendMessageToClient( &msg );
            return;
        }

        if ( pMaterialIdentifyItemConfig->levelLowLimit > pItemCanEquipConfig->stEquipLevelReq  )
        {
            msg.nResult = MsgIntensifyEquip::e_MaterialItemLevel; // 宝石等级不够
            SendMessageToClient( &msg );
            return;
        }

        if ( pMaterialIdentifyItemConfig->levelUpLimit < pItemCanEquipConfig->stEquipLevelReq  )
        {
            msg.nResult = MsgIntensifyEquip::e_MaterialItemLevel; // 宝石等级不够
            SendMessageToClient( &msg );
            return;
        }

		//LYH日志添加
		SCharItem * _item =  GetBagItemByGuid(pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].guid);
		if(_item)
		{
			ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
			if(_pitem)
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
			_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,
			                                   GetCharName(),_pitem->GetItemName());
		}

        RemoveItem( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagType,
            pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagIndex, 
            NUMERIC_ONE, 
            pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].guid );

    }

	// 删除宝石
    if(!RemoveItem( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType, 
        pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex,
        NUMERIC_ONE, 
        pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid ))
	{
		msg.nResult = MsgIntensifyEquip::e_MaterialItemLevel; // 宝石等级不够
        SendMessageToClient( &msg );
        return;
	}

    // 鉴定
	pEquipItem->SetBounded(IsNeedBounded);
    theRunTimeData.EquipBaseRand( *pEquipItem, false ); 

	//LYH日志添加
	SCharItem * _item =  GetBagItemByGuid(pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid);
	if(_item)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
		if(!theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
			_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName()))
		{
			Log( theXmlString.GetString(eServerLog_IdentifyOk2) , pItemEquipCommonConfig->GetItemName() );
		}
	}

    

    //Log( "鉴定物品[%s]成功" , pItemEquipCommonConfig->GetItemName() );
	    
    OperateJiaoZi( EOT_Sub, costMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_EquipIdentify );
    msg.AddCharItem( *pEquipItem );
    SendMessageToClient( &msg );
}

void GamePlayer::_ProcessEquipOpenLight( MsgEquipEvolve* pEquipLevelUp )
{
    if (pEquipLevelUp == NULL) 
    { return; }

    MsgIntensifyEquip msg;
    msg.header.stID     = GetID();
    msg.nEvolveType     = MsgEquipEvolve::ET_OpenLight;
    msg.nResult         = MsgIntensifyEquip::e_Succeed;
    msg.nNormalBagIndex = pEquipLevelUp->nNormalBagIndex;

    // 装备
    SCharItem* pEquipItem = _NormalItemBag.GetItemByIndex( pEquipLevelUp->nNormalBagIndex );

    // 宝石
    SCharItem* pOpenLightItem = NULL;
    ItemBag*   pSelectBag     = NULL;
    switch( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType )
    {
    case BT_MaterialBag:
        pSelectBag = &_MaterialItemBag;
        pOpenLightItem = _MaterialItemBag.GetItemByIndex( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
        break;
    default:
        pSelectBag = &_NormalItemBag;
        pOpenLightItem = _NormalItemBag.GetItemByIndex( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
    }

    if ( pEquipItem == NULL || pOpenLightItem == NULL || pSelectBag == NULL )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }
    if ( pEquipItem->GetItemGuid() != pEquipLevelUp->nNormalGuid )
    {
        _NormalItemBag.CleanUp();
        return;
    }

    if ( pOpenLightItem->GetItemGuid() != pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid )
    {
        pSelectBag->CleanUp();
        return;
    }

	if ( !pSelectBag->IsHaveItemById( pOpenLightItem->itembaseinfo.ustItemID ) )
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

    // 目标物品
    ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pEquipItem->itembaseinfo.ustItemID );
    if ( pItemCanEquip == NULL )
    { return; }

    if ( pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    { return; }

    if ( pItemCanEquip->bFashion || pItemCanEquip->IsCannotEvolve() )
    { 
        msg.nResult = MsgIntensifyEquip::e_FashionCanNotEvolve;
        SendMessageToClient( &msg );
        return; 
    }

    // 鎏金材料
    ItemDefine::SCreateMaterial* pMaterialItem = (ItemDefine::SCreateMaterial*)GettheItemDetail().GetItemByID( pOpenLightItem->itembaseinfo.ustItemID );
    if ( pMaterialItem == NULL )
    { return; }

    if ( pMaterialItem->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
    { 
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pMaterialItem->stMaterialType != ItemDefine::ematerial_openlight )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

	bool IsNeedBound = false;

	if(pOpenLightItem->IsBounded())
		IsNeedBound = true;

    //判断品质
    if ( pEquipItem->equipdata.quality < pMaterialItem->equipQuality )
    {
        msg.nResult = MsgIntensifyEquip::e_NotEnoughQuality;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    //材料等级要求
    if ( pMaterialItem->levelLowLimit > pItemCanEquip->stEquipLevelReq  )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep;  
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pMaterialItem->levelUpLimit < pItemCanEquip->stEquipLevelReq  )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep; 
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    //判断金钱   
    int costMoney = pMaterialItem->useCostMoney ;
    if ( costMoney > GetJiaoZiMoney() )
    {
        msg.nResult = MsgIntensifyEquip::e_NotEnoughMoney;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pEquipItem->equipdata.purpleRands[0] != InvalidLogicNumber )
    {   
        msg.nResult = MsgIntensifyEquip::e_HaveLiuJin; 
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }
	// for log
	unsigned short OldValue[ SCharItem::EConstDefine_PurpleRandMaxCount];
	memcpy(OldValue,pEquipItem->equipdata.purpleRands,sizeof(OldValue));

	if(!RemoveItem( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType, 
        pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex,
        NUMERIC_ONE, 
        pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid ))
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem; 
        GettheServer().SendMsgToSingle(&msg,this);
        return;
	}

    // 鎏金
    //pEquipItem->equipdata.quality = ItemDefine::EQL_Purple;
	if(IsNeedBound)
	{
		pEquipItem->SetBounded(true);//设置绑定
	}

    theRunTimeData.EquipPurpleRand( *pEquipItem ); 

	theRunTimeData.EquipScore(*pEquipItem, GettheItemDetail().GetItemByID( pEquipItem->itembaseinfo.ustItemID )); // 计算装备评分

	//Log( "鎏金物品[%s]成功" , pItemCanEquip->GetItemName() );
	SCharItem * _item =  GetBagItemByGuid(pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid);
	if(_item)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
		if(!theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
			_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName()))
		{
			Log( theXmlString.GetString(eServerLog_LiuJinOk) , pItemCanEquip->GetItemName() );
		}
	}
	theLogEventService.LogItemUpgrade(GetAccountID(),GetDBCharacterID(),pEquipItem->GetItemID(),1,pEquipItem->GetItemGuid()
									,eItemLogInfo_ItemUpgrade_OpenLight,1,OldValue,pEquipItem->equipdata.purpleRands
									,GetCharName(),pItemCanEquip->GetItemName());

    // 扣除材料
   

    OperateJiaoZi( EOT_Sub, costMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_EquipOpenLight );

    msg.AddCharItem( *pEquipItem );
    SendMessageToClient( &msg );

    _achieveManager.UpdateTriggerByValueType( EAT_EquipOpen,pItemCanEquip->stEquipLevelReq );
}

void GamePlayer::_ProcessEquipReOpenLight( MsgEquipEvolve* pEquipLevelUp )
{
    if (pEquipLevelUp == NULL) 
    { return; }

    MsgIntensifyEquip msg;
    msg.header.stID      = GetID();
    msg.nEvolveType     = MsgEquipEvolve::ET_ReOpenLight;
    msg.nResult         = MsgIntensifyEquip::e_Succeed;
    msg.nNormalBagIndex = pEquipLevelUp->nNormalBagIndex;

    // 装备
    SCharItem* pEquipItem = _NormalItemBag.GetItemByIndex( pEquipLevelUp->nNormalBagIndex );

    // 宝石
    SCharItem* pOpenLightItem = NULL;
    ItemBag*   pSelectBag     = NULL;
    switch( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType )
    {
    case BT_MaterialBag:
        pSelectBag = &_MaterialItemBag;
        pOpenLightItem = _MaterialItemBag.GetItemByIndex( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
        break;
    default:
        pSelectBag = &_NormalItemBag;
        pOpenLightItem = _NormalItemBag.GetItemByIndex( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
    }

    if ( pEquipItem == NULL || pOpenLightItem == NULL || pSelectBag == NULL )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

	bool IsNeedBound = false;
	if(pOpenLightItem->IsBounded())
		IsNeedBound = true;

    if ( pEquipItem->GetItemGuid() != pEquipLevelUp->nNormalGuid )
    {
        _NormalItemBag.CleanUp();
        return;
    }

    if ( pOpenLightItem->GetItemGuid() != pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid )
    {
        pSelectBag->CleanUp();
        return;
    }

	if ( !pSelectBag->IsHaveItemById( pOpenLightItem->itembaseinfo.ustItemID ) )
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

    // 目标物品
    ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pEquipItem->itembaseinfo.ustItemID );
    if ( pItemCanEquip == NULL )
    { return; }

    if ( pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    { return; }

    if ( pItemCanEquip->bFashion || pItemCanEquip->IsCannotEvolve() )
    { 
        msg.nResult = MsgIntensifyEquip::e_FashionCanNotEvolve;
        SendMessageToClient( &msg );
        return; 
    }

    // 鎏金材料
    ItemDefine::SCreateMaterial* pMaterialItem = (ItemDefine::SCreateMaterial*)GettheItemDetail().GetItemByID( pOpenLightItem->itembaseinfo.ustItemID );
    if ( pMaterialItem == NULL )
    { return; }

    if ( pMaterialItem->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
    { 
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pMaterialItem->stMaterialType != ItemDefine::ematerial_reopenlight )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    //判断品质
    if ( pEquipItem->equipdata.quality < pMaterialItem->equipQuality )
    {
        msg.nResult = MsgIntensifyEquip::e_NotEnoughQuality;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    //材料等级要求
    if ( pMaterialItem->levelLowLimit > pItemCanEquip->stEquipLevelReq  )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep;  
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pMaterialItem->levelUpLimit < pItemCanEquip->stEquipLevelReq  )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep; 
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    //判断金钱   
    int costMoney = pMaterialItem->useCostMoney ;
    if ( costMoney > GetJiaoZiMoney() )
    {
        msg.nResult = MsgIntensifyEquip::e_NotEnoughMoney;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }
	// for log
	unsigned short OldValue[SCharItem::EConstDefine_PurpleRandMaxCount];
	memcpy(OldValue,pEquipItem->equipdata.purpleRands,sizeof(OldValue));


	 // 扣除材料
    if(!RemoveItem( pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType, 
        pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex,
        NUMERIC_ONE, 
        pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid ))
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
	}

    //重新鎏金
    //pEquipItem->equipdata.quality = ItemDefine::EQL_Purple;
	if(IsNeedBound)
	{
		pEquipItem->SetBounded(true);
	}
    theRunTimeData.EquipPurpleRand( *pEquipItem ); 

	theRunTimeData.EquipScore(*pEquipItem, GettheItemDetail().GetItemByID( pEquipItem->itembaseinfo.ustItemID )); // 计算装备评分

	//LYH日志添加
	SCharItem * _item =  GetBagItemByGuid(pEquipLevelUp->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid);
	if(_item)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
		if(!theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
			_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName()))
		{
			Log( theXmlString.GetString(eServerLog_LiuJinOk2) , pItemCanEquip->GetItemName() );
		}
	}
	theLogEventService.LogItemUpgrade(GetAccountID(),GetDBCharacterID(),pEquipItem->GetItemID(),1,pEquipItem->GetItemGuid()
									,eItemLogInfo_ItemUpgrade_ReOpenLight,1,OldValue,pEquipItem->equipdata.purpleRands
									,GetCharName(),pItemCanEquip->GetItemName());

   // Log( "鎏金回炉物品[%s]成功" , pItemCanEquip->GetItemName() );


    OperateJiaoZi( EOT_Sub, costMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_EquipReOpenLight );

    msg.AddCharItem( *pEquipItem );
    SendMessageToClient( &msg );
}

void GamePlayer::_ProcessStiletto( MsgEquipEvolve* pEquipEvolve )
{
    if (pEquipEvolve == NULL) 
    { return; }

    MsgIntensifyEquip msg;
    msg.header.stID      = GetID();
    msg.nEvolveType     = MsgEquipEvolve::ET_Stiletto;
    msg.nResult         = MsgIntensifyEquip::e_Succeed;
    msg.nNormalBagIndex = pEquipEvolve->nNormalBagIndex;

    // 装备
    SCharItem* pEquipItem = _NormalItemBag.GetItemByIndex( pEquipEvolve->nNormalBagIndex );

    // 打孔材料
    SCharItem* pStilettoItem = NULL;
    ItemBag*   pSelectBag    = NULL;
    switch( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType )
    {
    case BT_MaterialBag:
        pStilettoItem = _MaterialItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
        pSelectBag = &_MaterialItemBag;
        break;
    default:
        pStilettoItem = _NormalItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
        pSelectBag = &_NormalItemBag;
    }

    // 背包是否存在
    if ( pEquipItem == NULL || pStilettoItem == NULL || pSelectBag == NULL )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pEquipItem->GetItemGuid() != pEquipEvolve->nNormalGuid )
    {
        _NormalItemBag.CleanUp();
        return;
    }

    if ( pStilettoItem->GetItemGuid() != pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid )
    {
        pSelectBag->CleanUp();
        return;
    }

    // 目标物品
    ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pEquipItem->itembaseinfo.ustItemID );
    if ( pItemCanEquip == NULL )
    { return; }

    if ( pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    { return; }

    if ( pItemCanEquip->bFashion || pItemCanEquip->IsCannotEvolve() )
    { 
        msg.nResult = MsgIntensifyEquip::e_FashionCanNotEvolve;
        GettheServer().SendMsgToSingle(&msg,this);
        return; 
    }

    // 是否有钻孔材料
    ItemDefine::SCreateMaterial* pMaterialItemConfig = (ItemDefine::SCreateMaterial*)GettheItemDetail().GetItemByID( pStilettoItem->itembaseinfo.ustItemID );
    if ( pMaterialItemConfig == NULL )
    { return; }

    if ( pMaterialItemConfig->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
    { 
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pMaterialItemConfig->stMaterialType != ItemDefine::ematerial_stiletto )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

//     // 判断是否是可作用的装备部位
//     if ( !pMaterialItemConfig->CanEquipPart( pItemCanEquip->ustEquipType ) )
//     {
//         msg.nResult = MsgIntensifyEquip::e_ItemNotMatch;
//         GettheServer().SendMsgToSingle(&msg,this);
//         return;
//     }

    // 材料等级限制
    if ( pMaterialItemConfig->levelLowLimit > pItemCanEquip->stEquipLevelReq  )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep;  
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pMaterialItemConfig->levelUpLimit < pItemCanEquip->stEquipLevelReq  )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep;  
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 判断孔是否已经打满
    if ( pEquipItem->equipdata.gemHoleCount >= SCharItem::EConstDefine_GemHoleMaxCount - 2 )
    {
        msg.nResult = MsgIntensifyEquip::e_FullHole;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

//     // 判断前置孔是否已经打过
//     if ( pEquipItem->equipdata.gemHoleCount + 1 != pMaterialItemConfig->nValue )
//     {
//         msg.nResult = MsgIntensifyEquip::e_PreHoleIsExist;
//         GettheServer().SendMsgToSingle(&msg,this);
//         return;
//     }
	// 判断孔位限制
	if ( pEquipItem->equipdata.gemHoleCount + 1 > pMaterialItemConfig->nValue )
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}


    // 判断金钱
//    int costMoney = pMaterialItemConfig->useCostMoney;
	EquipEvolveConfig::SEquipStiletto *pStilettoConfig = theEquipEvolveConfig.GetStiletto(pEquipItem->equipdata.gemHoleCount + 1);
	if ( NULL == pStilettoConfig )
	{ return; }
	int costMoney = pStilettoConfig->nCostValue;
    if ( costMoney > GetJiaoZiMoney() )
    {
        msg.nResult = MsgIntensifyEquip::e_NotEnoughMoney;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

	//LYH日志添加
	SCharItem * _item = GetBagItemByGuid(pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid );
	if (_item)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
		theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
		_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
	}
	if(_item && _item->IsBounded())
	{
		pEquipItem->SetBounded(true);
	}

	// 扣除钻孔道具
	if (!RemoveItem( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType, 
		pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex, 
		NUMERIC_ONE, 
		pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid ))
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}
    // 打孔
//    pEquipItem->equipdata.gemHoleCount = pMaterialItemConfig->nValue;
	unsigned short oldHoleCnt[SCharItem::EConstDefine_GemHoleMaxCount] = {0};
	for (int i = 0 ; i < pEquipItem->equipdata.gemHoleCount ; i++)
	{
         oldHoleCnt[i] = 1;
	}
	if ( theRand.rand16() % 10000 < pStilettoConfig->nSuccessRate )
	{
		++ pEquipItem->equipdata.gemHoleCount;
	}
	else
	{
		msg.nResult = MsgIntensifyEquip::e_Lost;
	}

	unsigned short curHoleCnt[SCharItem::EConstDefine_GemHoleMaxCount] = {0};
	for (int i = 0 ; i < pEquipItem->equipdata.gemHoleCount ; i++)
	{
		curHoleCnt[i] = 1;
	}

	//LYH日志添加（打孔）
	theLogEventService.LogItemUpgrade(GetAccountID(),GetDBCharacterID(),pEquipItem->GetItemID(),1,pEquipItem->GetItemGuid(),
		eItemLogInfo_ItemUpgrade_Hole,msg.nResult!=MsgIntensifyEquip::e_Lost,oldHoleCnt,curHoleCnt,GetCharName(),pItemCanEquip->GetItemName());

	//Log( "打孔物品[%s][%I64u] %s", pItemCanEquip->GetItemName(), pEquipItem->itembaseinfo.nOnlyInt, msg.nResult == MsgIntensifyEquip::e_Succeed ? "success" : "Failure" );
	Log( theXmlString.GetString(eServerLog_OpenHole), pItemCanEquip->GetItemName(), pEquipItem->itembaseinfo.nOnlyInt, msg.nResult == MsgIntensifyEquip::e_Succeed ? "success" : "Failure" );
    OperateJiaoZi( EOT_Sub, costMoney, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Hole);
     
    msg.AddCharItem( *pEquipItem );
    SendMessageToClient( &msg );
	TriggerSpecialQuest(ESTT_Hole);
}

void GamePlayer::_ProcessGemInlay(  MsgEquipEvolve* pEquipEvolve )
{
    if (pEquipEvolve == NULL) 
    { return; }

    MsgIntensifyEquip msg;
    msg.header.stID      = GetID();
    msg.nEvolveType     = MsgEquipEvolve::ET_Inlay;
    msg.nResult         = MsgIntensifyEquip::e_Succeed;
    msg.nNormalBagIndex = pEquipEvolve->nNormalBagIndex;

    // 装备
    SCharItem* pEquipItem = _NormalItemBag.GetItemByIndex( pEquipEvolve->nNormalBagIndex );
    if ( pEquipItem == NULL )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pEquipItem->GetItemGuid() != pEquipEvolve->nNormalGuid )
    {
        _NormalItemBag.CleanUp();
        return;
    }

    // 目标装备
    ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pEquipItem->itembaseinfo.ustItemID );
    if ( pItemCanEquip == NULL )
    { return; }

    if ( pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    { return; }
    
    if ( pItemCanEquip->bFashion || pItemCanEquip->IsCannotEvolve() )
    { 
        msg.nResult = MsgIntensifyEquip::e_FashionCanNotEvolve;
        GettheServer().SendMsgToSingle(&msg,this);
        return; 
    }

//     // 宝石是否存在
//     int gemCount = 0,costMoney = 0;
//     std::vector<std::pair<uint8,SCharItem*> > gemItems;
//     for ( uint8 i=0; i<MsgEquipEvolve::EConstDefine_MaxMaterialCount; ++i)
//     {
//         if (pEquipEvolve->materials[i].guid == InvalidLogicNumber )
//         { continue; }
// 
//         SCharItem* pGemItem   = NULL;
//         ItemBag*   pSelectBag = NULL;
//         switch( pEquipEvolve->materials[i].bagType )
//         {
//         case BT_MaterialBag:
//             pSelectBag = &_MaterialItemBag;
//             pGemItem   = _MaterialItemBag.GetItemByIndex( pEquipEvolve->materials[i].bagIndex );
//             break;
//         default:
//             pSelectBag = &_NormalItemBag;
//             pGemItem   = _NormalItemBag.GetItemByIndex( pEquipEvolve->materials[i].bagIndex );
//         }
// 
//         if ( pGemItem == NULL || pSelectBag == NULL )
//         {
//             msg.nResult = MsgIntensifyEquip::e_GemIsNotExist;
//             GettheServer().SendMsgToSingle(&msg,this);
//             return;
//         }
// 
//         if ( pGemItem->GetItemGuid() != pEquipEvolve->materials[i].guid )
//         {
//             pSelectBag->CleanUp();
//             msg.nResult = MsgIntensifyEquip::e_GemIsNotExist;
//             GettheServer().SendMsgToSingle(&msg,this);
//             return;
//         }
// 
//         // 查询宝石配置
//         ItemDefine::SItemGem* pItemGemConfig = (ItemDefine::SItemGem*) GettheItemDetail().GetItemByID( pGemItem->itembaseinfo.ustItemID );
//         if ( pItemGemConfig == NULL )
//         { return; }
// 
//         if ( pItemGemConfig->ucItemType != ItemDefine::ITEMTYPE_GEM )
//         {
//             msg.nResult = MsgIntensifyEquip::e_ErrorGemItem;
//             GettheServer().SendMsgToSingle(&msg,this);
//             return;
//         }
// 
//         // 判断是否可以镶嵌该位置
//         if ( !pItemGemConfig->CanEquipPart( pItemCanEquip->ustEquipType ) )
//         {
//             msg.nResult = MsgIntensifyEquip::e_ErrorGemItem;
//             GettheServer().SendMsgToSingle(&msg,this);
//             return;
//         }
// 
//         // 使用等级限制
//         if ( pItemGemConfig->levelLimit > pItemCanEquip->stEquipLevelReq  )
//         {
//             msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep;  
//             GettheServer().SendMsgToSingle(&msg,this);
//             return;
//         }
// 
//         costMoney += pItemGemConfig->useCostMoney;
// 
//         gemItems.push_back( std::make_pair(i,pGemItem) );
//         ++gemCount;
//     }
// 
//     if ( gemItems.empty() )
//     {
//         msg.nResult = MsgIntensifyEquip::e_ErrorGemItem;
//         GettheServer().SendMsgToSingle(&msg,this);
//         return;
//     }
// 
//     if ( gemCount > pEquipItem->equipdata.gemHoleCount )
//     {
//         msg.nResult = MsgIntensifyEquip::e_HoleNotEnough;
//         GettheServer().SendMsgToSingle(&msg,this);
//         return;
//     }
// 
//     // 先判断钱够不够
//     if ( costMoney > GetJiaoZiMoney() )
//     {
//         msg.nResult = MsgIntensifyEquip::e_NotEnoughMoney;
//         GettheServer().SendMsgToSingle(&msg,this);
//         return;
//     }
// 
//     // 开始镶嵌
//     for ( std::vector<std::pair<uint8,SCharItem*> >::iterator it = gemItems.begin(); it != gemItems.end(); ++it )
//     {
//         uint8 i          = it->first;
//         SCharItem* pItem = (*it).second;
// 
//         if (pItem == NULL)
//         { continue; }
// 
//         if (pEquipItem->equipdata.gemIds[i] != InvalidLogicNumber)
//         { continue; }
// 
//         pEquipItem->equipdata.gemIds[i] = pItem->itembaseinfo.ustItemID;
// 
//         // 扣除宝石
//         RemoveItem( pEquipEvolve->materials[i].bagType, pEquipEvolve->materials[i].bagIndex, NUMERIC_ONE, pEquipEvolve->materials[i].guid );
//     }

	//检查装备是否有可镶嵌位置
	//已镶嵌宝石数
	int nInlayedGemCount = 0;
	for ( int i = 0; i < SCharItem::EConstDefine_GemHoleMaxCount; ++i )
	{
		if (pEquipItem->equipdata.gemIds[i] != InvalidLogicNumber)
		{ ++ nInlayedGemCount; }
	}
	if ( nInlayedGemCount >= pEquipItem->equipdata.gemHoleCount )
	{
		msg.nResult = MsgIntensifyEquip::e_HoleNotEnough;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

	//宝石
	SCharItem* pGemItem   = NULL;
	ItemBag*   pSelectBag = NULL;
	switch( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType )
	{
	case BT_MaterialBag:
		pSelectBag = &_MaterialItemBag;
		pGemItem   = _MaterialItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
		break;
	default:
		pSelectBag = &_NormalItemBag;
		pGemItem   = _NormalItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
	}

	if ( pGemItem == NULL || pSelectBag == NULL )
	{
		msg.nResult = MsgIntensifyEquip::e_GemIsNotExist;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

	if ( pGemItem->GetItemGuid() != pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid )
	{
		pSelectBag->CleanUp();
		msg.nResult = MsgIntensifyEquip::e_GemIsNotExist;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

	//镶嵌符
	SCharItem* pInlayItem   = NULL;
	switch( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagType )
	{
	case BT_MaterialBag:
		pSelectBag = &_MaterialItemBag;
		pInlayItem   = _MaterialItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagIndex );
		break;
	default:
		pSelectBag = &_NormalItemBag;
		pInlayItem   = _NormalItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagIndex );
	}

	if ( pInlayItem == NULL || pSelectBag == NULL )
	{
		msg.nResult = MsgIntensifyEquip::e_InlayIsNotExist;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

	if ( pInlayItem->GetItemGuid() != pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].guid )
	{
		pSelectBag->CleanUp();
		msg.nResult = MsgIntensifyEquip::e_InlayIsNotExist;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

	// 查询宝石配置
	ItemDefine::SItemGem* pItemGemConfig = (ItemDefine::SItemGem*) GettheItemDetail().GetItemByID( pGemItem->itembaseinfo.ustItemID );
	if ( pItemGemConfig == NULL )
	{ return; }

	if ( pItemGemConfig->ucItemType != ItemDefine::ITEMTYPE_GEM )
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorGemItem;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

	// 判断是否可以镶嵌该位置
	if ( !pItemGemConfig->CanEquipPart( pItemCanEquip->ustEquipType ) )
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorGemItem;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

	//检查宝石同类型重复镶嵌 lyh经策划要求可以镶嵌同类宝石
	//for ( int i = 0; i < SCharItem::EConstDefine_GemHoleMaxCount; ++i )
	//{
	//	if (pEquipItem->equipdata.gemIds[i] != InvalidLogicNumber)
	//	{
	//		ItemDefine::SItemGem* pEquipGemConfig = (ItemDefine::SItemGem*) GettheItemDetail().GetItemByID( pEquipItem->equipdata.gemIds[i] );
	//		if ( NULL == pEquipGemConfig )
	//		{ continue; }
	//		if ( pEquipGemConfig->gemType == pItemGemConfig->gemType )
	//		{
	//			msg.nResult = MsgIntensifyEquip::e_InlaySameTypeGem;
	//			GettheServer().SendMsgToSingle(&msg,this);
	//			return;
	//		}
	//	}
	//}

	//查询镶嵌符配置
	ItemDefine::SCreateMaterial *pItemMaterialConfig = (ItemDefine::SCreateMaterial*) GettheItemDetail().GetItemByID(pInlayItem->itembaseinfo.ustItemID);
	if ( NULL == pItemMaterialConfig )
	{ return; }

	if ( pItemMaterialConfig->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorInlayItem;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

	if ( pItemMaterialConfig->stMaterialType != ItemDefine::ematerial_inlay)
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorInlayItem;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

	//镶嵌成功率
	float fInlayRate = pItemMaterialConfig->fAddIntensifyRate[0];

	//几率宝珠
	bool bHasRateBoll = false;
	SCharItem* pRateItem   = NULL;
	switch( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_ThirdMaterialIndex].bagType )
	{
	case BT_MaterialBag:
		pSelectBag = &_MaterialItemBag;
		pRateItem   = _MaterialItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_ThirdMaterialIndex].bagIndex );
		break;
	default:
		pSelectBag = &_NormalItemBag;
		pRateItem   = _NormalItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_ThirdMaterialIndex].bagIndex );
	}

	if ( pRateItem != NULL && pSelectBag != NULL )
	{//有几率宝珠
		if ( pRateItem->GetItemGuid() != pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_ThirdMaterialIndex].guid )
		{
			pSelectBag->CleanUp();
			msg.nResult = MsgIntensifyEquip::e_RateBollNotExist;
			GettheServer().SendMsgToSingle(&msg,this);
			return;
		}

		//查询几率宝珠配置
		pItemMaterialConfig = (ItemDefine::SCreateMaterial*) GettheItemDetail().GetItemByID(pRateItem->itembaseinfo.ustItemID);
		if ( NULL == pItemMaterialConfig )
		{ return; }

		if ( pItemMaterialConfig->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
		{
			msg.nResult = MsgIntensifyEquip::e_ErrorRateBoll;
			GettheServer().SendMsgToSingle(&msg,this);
			return;
		}

		if ( pItemMaterialConfig->stMaterialType != ItemDefine::ematerial_rateboll )
		{
			msg.nResult = MsgIntensifyEquip::e_ErrorRateBoll;
			GettheServer().SendMsgToSingle(&msg,this);
			return;
		}

		bHasRateBoll = true;

		//check bag capacity
		switch (pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType)
		{
		case BT_MaterialBag:
			{
				if ( _MaterialItemBag.GetItemEmptyCount() <= 0 )
				{
					msg.nResult = MsgIntensifyEquip::e_BagIsFull;
					GettheServer().SendMsgToSingle(&msg,this);
					return;
				}
			}
			break;
		default:
			if ( _NormalItemBag.GetItemEmptyCount() <= 0 )
			{
				msg.nResult = MsgIntensifyEquip::e_BagIsFull;
				GettheServer().SendMsgToSingle(&msg,this);
				return;
			}
		}
	}

	unsigned short oldGem[SCharItem::EConstDefine_GemHoleMaxCount] = {0};
	for (int i = 0 ; i < SCharItem::EConstDefine_GemHoleMaxCount ; i++)
	{
		if(pEquipItem->equipdata.gemIds[i] != InvalidLogicNumber)
		{
           oldGem[i] = pEquipItem->equipdata.gemIds[i];
		}
	}

	if ( fInlayRate < theRand.rand16() % 10000 + 1 )
	{//成功
		//开始镶嵌,镶嵌到第一个可用孔位
		for ( int i = 0; i < SCharItem::EConstDefine_GemHoleMaxCount; ++i )
		{
			if ( pEquipItem->equipdata.gemIds[i] == InvalidLogicNumber )
			{//找到镶嵌位置
				pEquipItem->equipdata.gemIds[i] = pGemItem->itembaseinfo.ustItemID;
				break;
			}
		}
	}
	else
	{
		msg.nResult = MsgIntensifyEquip::e_Lost;
	}

	if ( bHasRateBoll )
	{

		//LYH日志添加
		SCharItem * _item = GetBagItemByGuid(pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_ThirdMaterialIndex].guid);
		if (_item)
		{
			ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
			if(_pitem)
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
			_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem, GetCharName(),_pitem->GetItemName());
		}

		RemoveItem( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_ThirdMaterialIndex].bagType,
					pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_ThirdMaterialIndex].bagIndex,
					NUMERIC_ONE,
					pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_ThirdMaterialIndex].guid );

		

		if ( msg.nResult == MsgIntensifyEquip::e_Lost )
		{
			//宝石降级
			if ( pItemGemConfig->downGradeID )
			{
				if ( AddItem( pItemGemConfig->downGradeID, NUMERIC_ONE, EIGS_GemInlayFail ) != ierr_Success )
				{
					msg.nResult = MsgIntensifyEquip::e_BagIsFull;
					GettheServer().SendMsgToSingle(&msg,this); 
				}
			}
		}
	}


	//LYH日志添加
	SCharItem * _item = GetBagItemByGuid(pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid);
	if (_item)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
		theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
		_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem, GetCharName(),_pitem->GetItemName());
	}

	// 扣除宝石
	RemoveItem( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType,
	pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex,
	NUMERIC_ONE, 
	pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid ); 


	//LYH日志添加
	_item = GetBagItemByGuid(pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].guid);
	if (_item)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
		if(!theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
			_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName()))
		{
			Log( theXmlString.GetString(eServerLog_XiangQian), pItemCanEquip->GetItemName(), pEquipItem->itembaseinfo.nOnlyInt, msg.nResult == MsgIntensifyEquip::e_Succeed ? "success" : "Failure" );
		}
	}

	RemoveItem( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagType,
	pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagIndex,
	NUMERIC_ONE,
	pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].guid );

	

	theRunTimeData.EquipScore(*pEquipItem, GettheItemDetail().GetItemByID( pEquipItem->itembaseinfo.ustItemID )); // 计算装备评分

    msg.AddCharItem( *pEquipItem );
    SendMessageToClient( &msg );

	unsigned short curGem[SCharItem::EConstDefine_GemHoleMaxCount] = {0};
	for (int i = 0 ; i < SCharItem::EConstDefine_GemHoleMaxCount ; i++)
	{
		if(pEquipItem->equipdata.gemIds[i] != InvalidLogicNumber)
		{
			curGem[i] = pEquipItem->equipdata.gemIds[i];
		}
	}

	//LYH日志添加
	ItemDefine::SItemCommon *pCommon =  GettheItemDetail().GetItemByID(pEquipItem->GetItemID());
	if(pCommon)
	 theLogEventService.LogItemUpgrade(GetAccountID(),GetDBCharacterID(),pEquipItem->GetItemID(),1,pEquipItem->GetItemGuid(),eItemLogInfo_ItemUpgrade_InsertHole,
		                                msg.nResult == MsgIntensifyEquip::e_Succeed,oldGem,curGem,GetCharName(),pCommon->GetItemName());


	_achieveManager.UpdateTriggerByValueType( EAT_EquipGem,pItemGemConfig->gemLevel);
	//触发镶嵌宝石任务
	TriggerSpecialQuest(ESTT_EquipGem);
}

void GamePlayer::_ProcessGemTakeDown( MsgEquipEvolve* pEquipEvolve )
{
    if (pEquipEvolve == NULL) 
    { return; }

    MsgIntensifyEquip msg;
    msg.header.stID      = GetID();
    msg.nEvolveType     = MsgEquipEvolve::ET_TakeDown;
    msg.nResult         = MsgIntensifyEquip::e_Succeed;
    msg.nNormalBagIndex = pEquipEvolve->nNormalBagIndex;

    // 装备
    SCharItem* pEquipItem = _NormalItemBag.GetItemByIndex( pEquipEvolve->nNormalBagIndex );

    // 离石剂
    SCharItem* pTakeDownItem = NULL;
    ItemBag*   pSelectBag    = NULL;
    switch( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType )
    {
    case BT_MaterialBag:
        pTakeDownItem = _MaterialItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
        pSelectBag = &_MaterialItemBag;
        break;
    default:
        pTakeDownItem = _NormalItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
        pSelectBag = &_NormalItemBag;
    }

    // 背包是否存在
    if ( pEquipItem == NULL || pTakeDownItem == NULL || pSelectBag == NULL )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pEquipItem->GetItemGuid() != pEquipEvolve->nNormalGuid )
    {
        _NormalItemBag.CleanUp();
        return;
    }

    if ( pTakeDownItem->GetItemGuid() != pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid )
    {
        pSelectBag->CleanUp();
        return;
    }

    // 目标装备
    ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pEquipItem->itembaseinfo.ustItemID );
    if ( pItemCanEquip == NULL )
    { return; }

    if ( pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    { return; }

    if ( pItemCanEquip->bFashion || pItemCanEquip->IsCannotEvolve() )
    { 
        msg.nResult = MsgIntensifyEquip::e_FashionCanNotEvolve;
        GettheServer().SendMsgToSingle(&msg,this);
        return; 
    }

    // 是否有离石材料
    ItemDefine::SCreateMaterial* pMaterialItemConfig = (ItemDefine::SCreateMaterial*)GettheItemDetail().GetItemByID( pTakeDownItem->itembaseinfo.ustItemID );
    if ( pMaterialItemConfig == NULL )
    { return; }

    if ( pMaterialItemConfig->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
    { 
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pMaterialItemConfig->stMaterialType != ItemDefine::ematerial_gemtakedown )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 判断是否是可作用的装备部位
    if ( !pMaterialItemConfig->CanEquipPart( pItemCanEquip->ustEquipType ) )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotMatch;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 材料等级限制
//     if ( pMaterialItemConfig->levelLowLimit > pItemCanEquip->stEquipLevelReq  )
//     {
//         msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep;  
//         GettheServer().SendMsgToSingle(&msg,this);
//         return;
//     }
// 
//     if ( pMaterialItemConfig->levelUpLimit < pItemCanEquip->stEquipLevelReq  )
//     {
//         msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep;  
//         GettheServer().SendMsgToSingle(&msg,this);
//         return;
//     }
	if ( pMaterialItemConfig->equipQuality != pItemCanEquip->ustLevel  )
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep;  
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

    // 目标孔位是否正确
    uint8 index =  pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].value;
    if ( index >= SCharItem::EConstDefine_GemHoleMaxCount )
    {
        msg.nResult = MsgIntensifyEquip::e_HoleIndexError;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 宝石是否存在
    uint16 nGemId = pEquipItem->equipdata.gemIds[index];
    if ( nGemId == InvalidLogicNumber )
    {
        msg.nResult = MsgIntensifyEquip::e_GemIsNotExist;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

	//TODO:判断材料与宝石的匹配度,可利用材料等级限制字段
	ItemDefine::SItemGem *pItemGemConfig = (ItemDefine::SItemGem *)GettheItemDetail().GetItemByID(nGemId);
	if ( NULL == pItemGemConfig )
	{
		msg.nResult = MsgIntensifyEquip::e_GemIsNotExist;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

	if ( pItemGemConfig->ucItemType != ItemDefine::ITEMTYPE_GEM )
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorGemItem;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	} 

	/*if ( pMaterialItemConfig->levelLowLimit > pItemGemConfig->gemLevel || pMaterialItemConfig->levelUpLimit < pItemGemConfig->gemLevel )
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep;  
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}*/


    // 判断背包是否有位置
    if ( _MaterialItemBag.GetItemEmptyCount() < NUMERIC_ONE)
    {
        msg.nResult = MsgIntensifyEquip::e_BagIsFull;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

	// 判断金钱
	int costMoney = pItemGemConfig->useCostMoney;
	if ( costMoney > GetJiaoZiMoney() )
	{
		msg.nResult = MsgIntensifyEquip::e_NotEnoughMoney;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}

	unsigned short OldGem[SCharItem::EConstDefine_GemHoleMaxCount] = {0};
	for (int i = 0 ; i < SCharItem::EConstDefine_GemHoleMaxCount ; i++)
	{
		OldGem[i] = pEquipItem->equipdata.gemIds[i];
	}

	// 扣除离石材料
	if (!RemoveItem( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType, 
		pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex, 
		NUMERIC_ONE, 
		pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid ))
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
		GettheServer().SendMsgToSingle(&msg,this);
		return;
	}


    // 创建宝石
    if ( AddItem( nGemId, NUMERIC_ONE, EIGS_GemTakeDown ) != ierr_Success )
    {
        msg.nResult = MsgIntensifyEquip::e_BagIsFull;
        GettheServer().SendMsgToSingle(&msg,this); 
        return;
    }

    // 删除孔中宝石
    pEquipItem->equipdata.gemIds[index] = InvalidLogicNumber;

    OperateJiaoZi( EOT_Sub, costMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_GemTakeDown );

   // Log( "拆卸物品[%s][%I64u] 宝石[%u]成功", pItemCanEquip->GetItemName(), pEquipItem->itembaseinfo.nOnlyInt, nGemId );
	Log(theXmlString.GetString(eServerLog_ChaiXieBaoshi), pItemCanEquip->GetItemName(), pEquipItem->itembaseinfo.nOnlyInt, nGemId );

	theRunTimeData.EquipScore(*pEquipItem, GettheItemDetail().GetItemByID( pEquipItem->itembaseinfo.ustItemID )); // 计算装备评分

    msg.value = index;
    msg.AddCharItem( *pEquipItem );
    SendMessageToClient( &msg );



	unsigned short curGem[SCharItem::EConstDefine_GemHoleMaxCount] = {0};
	for (int i = 0 ; i < SCharItem::EConstDefine_GemHoleMaxCount ; i++)
	{

		curGem[i] = pEquipItem->equipdata.gemIds[i];
	}
	
    //LYH日志添加
		ItemDefine::SItemCommon *pCommon =  GettheItemDetail().GetItemByID(pEquipItem->GetItemID());
		if(pCommon)
         	theLogEventService.LogItemUpgrade(GetAccountID(),GetDBCharacterID(),pEquipItem->GetItemID(),1,
	                                   pEquipItem->GetItemGuid(),eItemLogInfo_ItemUpgrade_OutGem,1,OldGem,
									   curGem,GetCharName(),pCommon->GetItemName());
}

void GamePlayer::_ProcessGemReplace( MsgEquipEvolve* pEquipEvolve )
{
    if (pEquipEvolve == NULL) 
    { return; }

    MsgIntensifyEquip msg;
    msg.header.stID      = GetID();
    msg.nEvolveType     = MsgEquipEvolve::ET_Replace;
    msg.nResult         = MsgIntensifyEquip::e_Succeed;
    msg.nNormalBagIndex = pEquipEvolve->nNormalBagIndex;

    // 装备
    SCharItem* pEquipItem = _NormalItemBag.GetItemByIndex( pEquipEvolve->nNormalBagIndex );
    if ( pEquipItem == NULL )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pEquipItem->GetItemGuid() != pEquipEvolve->nNormalGuid )
    {
        _NormalItemBag.CleanUp();
        return;
    }

    // 目标装备
    ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pEquipItem->itembaseinfo.ustItemID );
    if ( pItemCanEquip == NULL )
    { return; }

    if ( pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    { return; }

    if ( pItemCanEquip->bFashion || pItemCanEquip->IsCannotEvolve() )
    { 
        msg.nResult = MsgIntensifyEquip::e_FashionCanNotEvolve;
        GettheServer().SendMsgToSingle(&msg,this);
        return; 
    }

    // 宝石
    int gemCount = 0,costMoney = 0;
    int gemItems[SCharItem::EConstDefine_GemHoleMaxCount] = { 0 } ;
    for ( uint8 i=0; i<MsgEquipEvolve::EConstDefine_MaxMaterialCount; ++i)
    {
        if ( i >= SCharItem::EConstDefine_GemHoleMaxCount)
        { break; }

        if (pEquipEvolve->materials[i].guid == InvalidLogicNumber)
        { continue; }

        SCharItem* pReplaceItem = NULL;
        ItemBag*   pSelectBag   = NULL;
        switch( pEquipEvolve->materials[i].bagType )
        {
        case BT_MaterialBag:
            pSelectBag = &_MaterialItemBag;
            pReplaceItem = _MaterialItemBag.GetItemByIndex( pEquipEvolve->materials[i].bagIndex );
            break;
        default:
            pSelectBag = &_NormalItemBag;
            pReplaceItem = _NormalItemBag.GetItemByIndex( pEquipEvolve->materials[i].bagIndex );
        }

        // 背包是否存在
        if ( pReplaceItem == NULL || pSelectBag == NULL )
        {
            msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
            GettheServer().SendMsgToSingle(&msg,this);
            return;
        }

        if ( pReplaceItem->GetItemGuid() != pEquipEvolve->materials[i].guid )
        {
            pSelectBag->CleanUp();
            return;
        }

        // 宝石配置
        ItemDefine::SItemGem* pItemGemConfig = (ItemDefine::SItemGem*) GettheItemDetail().GetItemByID( pReplaceItem->itembaseinfo.ustItemID );
        if ( pItemGemConfig == NULL )
        { return; }

        if ( pItemGemConfig->ucItemType != ItemDefine::ITEMTYPE_GEM )
        {
            msg.nResult = MsgIntensifyEquip::e_ErrorGemItem;
            GettheServer().SendMsgToSingle(&msg,this);
            return;
        }

        // 判断是否可以镶嵌该位置
        if ( !pItemGemConfig->CanEquipPart( pItemCanEquip->ustEquipType ) )
        {
            msg.nResult = MsgIntensifyEquip::e_ErrorGemItem;
            GettheServer().SendMsgToSingle(&msg,this);
            return;
        }

        // 宝石是否存在
        uint16 gemId = pEquipItem->equipdata.gemIds[i];
        if ( gemId == InvalidLogicNumber )
        {
            msg.nResult = MsgIntensifyEquip::e_GemIsNotExist;
            GettheServer().SendMsgToSingle(&msg,this);
            return;
        }

        // 使用等级限制
        if ( pItemGemConfig->levelLimit > pItemCanEquip->stEquipLevelReq  )
        {
            msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep;  
            GettheServer().SendMsgToSingle(&msg,this);
            return;
        }

        costMoney += pItemGemConfig->useCostMoney;
        gemItems[i] = pReplaceItem->itembaseinfo.ustItemID;
    }

    if ( costMoney > GetJiaoZiMoney()  )
    {
        msg.nResult = MsgIntensifyEquip::e_NotEnoughMoney;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    for (int i=0;i<SCharItem::EConstDefine_GemHoleMaxCount;++i)
    {
        if ( gemItems[i] == InvalidLogicNumber )
        { continue; }

		//LYH日志添加
		SCharItem * _item = GetBagItemByGuid(pEquipEvolve->materials[i].guid);
		if (_item)
		{
			ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
			if(_pitem)
			if(!theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
				_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName()))
			{
				Log( theXmlString.GetString(eServerLog_TiHuanBaoshi), pItemCanEquip->GetItemName(), pEquipItem->itembaseinfo.nOnlyInt, gemItems[i] );
			}
		}

        // 扣除替换宝石
        RemoveItem( pEquipEvolve->materials[i].bagType, 
            pEquipEvolve->materials[i].bagIndex, 
            NUMERIC_ONE, 
            pEquipEvolve->materials[i].guid );

        // 替换宝石数据
        pEquipItem->equipdata.gemIds[i] = gemItems[i];
        //Log( "物品[%s][%I64u] 替换宝石[%u]成功", pItemCanEquip->GetItemName(), pEquipItem->itembaseinfo.nOnlyInt, gemItems[i] );
	
        
    }

    OperateJiaoZi( EOT_Sub, costMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_GemReplace );

    msg.AddCharItem( *pEquipItem );
    SendMessageToClient( &msg );
}


void GamePlayer::_ProcessSoulStamp( MsgEquipEvolve* pEquipEvolve )
{ 
    if (pEquipEvolve == NULL) 
    { return; }

    MsgIntensifyEquip msg;
    msg.header.stID      = GetID();
    msg.nEvolveType     = MsgEquipEvolve::ET_SoulStamp;
    msg.nResult         = MsgIntensifyEquip::e_Succeed;
    msg.nNormalBagIndex = pEquipEvolve->nNormalBagIndex;

    // 装备
    SCharItem* pEquipItem = _NormalItemBag.GetItemByIndex( pEquipEvolve->nNormalBagIndex );
	if ( !pEquipItem )
	{
		msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
		SendMessageToClient( &msg );
		return;
	}

	ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pEquipItem->itembaseinfo.ustItemID );
	
	if ( pItemCanEquip == NULL )	return;

	if ( pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_ARMOUR && pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_WEAPON )
	{ 
		msg.nResult = MsgIntensifyEquip::e_ItemNotMatch;
		SendMessageToClient( &msg );
		return;
	}

	if ( pItemCanEquip->bFashion || pItemCanEquip->IsCannotEvolve() )
	{  
		msg.nResult = MsgIntensifyEquip::e_FashionCanNotEvolve;
		SendMessageToClient( &msg );
		return; 
	}
	// 得到铸魂的配置数据
	SoulConfig::SData* pData = theSoulConfig.GetLevelData( pItemCanEquip->stEquipLevelReq );

	if ( !pData )		return;

    // 铸魂材料 1
    SCharItem* pMaterialItem = NULL;
    ItemBag*   pSelectBag    = NULL;
    switch ( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType )
    {
    case BT_MaterialBag:
        pSelectBag    = &_MaterialItemBag;
        pMaterialItem = _MaterialItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
        break;
    default:
        pSelectBag    = &_NormalItemBag;
        pMaterialItem = _NormalItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
    }

    if ( pMaterialItem == NULL || pSelectBag == NULL )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
        SendMessageToClient( &msg );
        return;
    }

    if ( pEquipItem->GetItemGuid() != pEquipEvolve->nNormalGuid )
    {
		msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
		SendMessageToClient( &msg );
        return;
    }

    if ( pMaterialItem->GetItemGuid() != pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid )
    {
		msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
		SendMessageToClient( &msg );
        return;
    }

	if ( !pSelectBag->IsHaveItemById( pMaterialItem->itembaseinfo.ustItemID ) )
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
		SendMessageToClient( &msg );
		return;
	}

	if ( pData->material[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].nId != pMaterialItem->itembaseinfo.ustItemID )
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
		SendMessageToClient( &msg );
		return;
	}

	int nMaterialCount = pSelectBag->GetItemCount( pMaterialItem->itembaseinfo.ustItemID );
	if ( nMaterialCount < pData->material[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].nNum )
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
		SendMessageToClient( &msg );
		return;
	}

	// 铸魂材料 2
	SCharItem* pMaterialItem1 = NULL;
	ItemBag*   pSelectBag1    = NULL;

	switch ( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagType )
	{
	case BT_MaterialBag:
		pSelectBag1    = &_MaterialItemBag;
		pMaterialItem1 = _MaterialItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagIndex );
		break;
	default:
		pSelectBag1    = &_NormalItemBag;
		pMaterialItem1 = _NormalItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagIndex );
	}

	if ( pMaterialItem1 == NULL || pSelectBag1 == NULL )
	{
		msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
		SendMessageToClient( &msg );
		return;
	}

	if ( pMaterialItem1->GetItemGuid() != pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].guid )
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
		SendMessageToClient( &msg );
		return;
	}

	if ( !pSelectBag1->IsHaveItemById( pMaterialItem1->itembaseinfo.ustItemID ) )
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
		SendMessageToClient( &msg );
		return;
	}

	if ( pData->material[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].nId != pMaterialItem1->itembaseinfo.ustItemID )
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
		SendMessageToClient( &msg );
		return;
	}

	int nMaterialCount1 = pSelectBag1->GetItemCount( pMaterialItem1->itembaseinfo.ustItemID );
	if ( nMaterialCount1 < pData->material[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].nNum )
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
		SendMessageToClient( &msg );
		return;
	}

    // 是否已经灵魂铭刻
   /* if ( pEquipItem->IsSoulStamp() )
    {
        msg.nResult = MsgIntensifyEquip::e_HaveSoulStamp;
        SendMessageToClient( &msg );
        return;
    }*/

    // 材料配置
    ItemDefine::SCreateMaterial* pMaterialItemConfig = (ItemDefine::SCreateMaterial*) GettheItemDetail().GetItemByID( pMaterialItem->itembaseinfo.ustItemID );
    if ( pMaterialItemConfig == NULL )		return;

	ItemDefine::SCreateMaterial* pMaterialItemConfig1 = (ItemDefine::SCreateMaterial*) GettheItemDetail().GetItemByID( pMaterialItem1->itembaseinfo.ustItemID );
	if ( pMaterialItemConfig1 == NULL )		return;

    if ( pMaterialItemConfig->stMaterialType != ItemDefine::ematerial_soulstamp )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        SendMessageToClient( &msg );
        return;
    }

    // 判断是否是可作用的装备部位
    if ( !pMaterialItemConfig->CanEquipPart( pItemCanEquip->ustEquipType ) )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotMatch;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 材料等级限制
    /*if ( pMaterialItemConfig->levelLowLimit > pItemCanEquip->stEquipLevelReq  )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep;  
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pMaterialItemConfig->levelUpLimit < pItemCanEquip->stEquipLevelReq  )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep;  
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }*/

    // 判断金钱要求
    int nCostMoney = /*pMaterialItemConfig->useCostMoney*/pData->nMoney;
    if ( nCostMoney > GetJiaoZiMoney() )
    {
        msg.nResult  = MsgIntensifyEquip::e_NotEnoughMoney;
        SendMessageToClient( &msg );
        return;
    }
	// for log
	unsigned short OldValue[1] = {pEquipItem->equipdata.ucSoulPer};
	unsigned short CurValue[1] = {0};

	// 扣除铭刻材料

	if(!RemoveItem( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType,
		pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex,
		pData->material[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].nNum, 
		pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid ))
	{
		msg.nResult  = MsgIntensifyEquip::e_ErrorMaterialItem;
        SendMessageToClient( &msg );
        return;
	}

	if(!RemoveItem( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagType,
		pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagIndex,
		pData->material[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].nNum, 
		pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].guid ))
	{
		msg.nResult  = MsgIntensifyEquip::e_ErrorMaterialItem;
        SendMessageToClient( &msg );
        return;
	}

    // 灵魂铭刻
    pEquipItem->SetBounded(true);
    pEquipItem->SetSoulStamp( true );

	SSoul soulData = theStarLevelUpConfig.GetSoulData();
	int nRange = soulData.nMaxPer - soulData.nMinPer + 1;
	int nPer = theRand.rand16()%nRange + soulData.nMinPer;
	pEquipItem->equipdata.ucSoulPer = nPer;
	CurValue[0] = nPer;

	theRunTimeData.EquipScore(*pEquipItem, GettheItemDetail().GetItemByID( pEquipItem->itembaseinfo.ustItemID )); // 计算装备评分


	// log
	int nLeveNum1 = pData->material[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].nNum;
	int nLeveNum2 = pData->material[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].nNum;
	if (!theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),pMaterialItem->GetItemID(),nLeveNum1,pMaterialItem->GetItemGuid(),
		nMaterialCount-nLeveNum1,eItemLogInfo_ItemConsume_UpItem,GetCharName(),pMaterialItemConfig->GetItemName()))
	{
		Log( theXmlString.GetString(eServerLog_LingHunMingke), pItemCanEquip->GetItemName(), pEquipItem->GetItemGuid() );
	}
	if (!theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),pMaterialItem1->GetItemID(),nLeveNum2,pMaterialItem1->GetItemGuid(),
		nMaterialCount1-nLeveNum2,eItemLogInfo_ItemConsume_UpItem,GetCharName(),pMaterialItemConfig1->GetItemName()))
	{
		Log( theXmlString.GetString(eServerLog_LingHunMingke), pItemCanEquip->GetItemName(), pEquipItem->GetItemGuid() );
	}

	theLogEventService.LogItemUpgrade(GetAccountID(),GetDBCharacterID(),pEquipItem->GetItemID(),1,pEquipItem->GetItemGuid()
									,eItemLogInfo_ItemUpgrade_SoulStamp,1,OldValue,CurValue
									,GetCharName(),pItemCanEquip->GetItemName());

	
    //Log( "灵魂铭刻物品[%s][%I64u] 成功", pItemCanEquip->GetItemName(), pEquipItem->GetItemGuid() );
	

    OperateJiaoZi( EOT_Sub, nCostMoney, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_SoulStamp);
    
    msg.AddCharItem( *pEquipItem );
    GettheServer().SendMsgToSingle( &msg,this );

    _achieveManager.UpdateTriggerByValueType( EAT_EquipStamp );
}


void GamePlayer::OnMsgEquipUpgradeReq( Msg* pMsg )
{
    MsgEquipUpgradeReq* pReq = static_cast< MsgEquipUpgradeReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    MsgEquipUpgradeAck xAck;

    // 判断原始装备有没有
    SCharItem* pEquip = _NormalItemBag.GetItemByIndex( pReq->ustEquipIndex );
    if ( pEquip == NULL || pEquip->itembaseinfo.nOnlyInt != pReq->nEquipGuid )
    {
        xAck.chResult = MsgEquipUpgradeAck::ECD_ErrorEquip;
        GettheServer().SendMsgToSingle( &xAck, this );
        return; 
    }

    //if ( pEquip->IsLock() )
    //{
    //    xAck.chResult = MsgEquipUpgradeAck::ECD_IsLocked;
    //    GettheServer().SendMsgToSingle( &xAck, this );
    //    return;
    //}

    const UpgradeData* pUpgradeData = theEquipUpgradeConfig.GetEquipUpgradeData( pEquip->itembaseinfo.ustItemID );
    if ( pUpgradeData == NULL )
    { 
        xAck.chResult = MsgEquipUpgradeAck::ECD_ErrorEquip;
        GettheServer().SendMsgToSingle( &xAck, this );
        return; 
    }

    const UpToEquipInfo* pUpToEquipInfo = pUpgradeData->GetUpToEquipByID( pReq->ustUpToEquipID );
    if ( pUpToEquipInfo == NULL )
    {
        xAck.chResult = MsgEquipUpgradeAck::ECD_CanNotUpgrade;
        GettheServer().SendMsgToSingle( &xAck, this );
        return; 
    }

    if ( GetJiaoZiMoney() < pUpToEquipInfo->GetCostMoney() )
    {
        xAck.chResult = MsgEquipUpgradeAck::ECD_NotEnoughMoney;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    // 判断必须的材料
    for ( int i = 0; i < pUpToEquipInfo->GetMaterialCount(); ++i )
    {
        const MaterialInfo* pInfo = pUpToEquipInfo->GetMaterialByIndex( i );
        if ( pInfo == NULL )
        { continue; }

        if ( pInfo->IsMustMaterial() )
        {   // 检查包裹有没有
            ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pInfo->GetMaterialID() );
            if ( pItemCommon == NULL )
            {
                xAck.chResult = MsgEquipUpgradeAck::ECD_Unkown;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            ItemBag* pItemBag = GetItemBagByItemType( pItemCommon->ucItemType );
            unsigned int nMaterialCount = pItemBag->GetItemCount( pInfo->GetMaterialID() );
            if ( nMaterialCount < pInfo->GetMaterialCount() )
            {
                xAck.chResult = MsgEquipUpgradeAck::ECD_LackMaterial;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }
        }
    }

    // 判断发送过来的辅助材料
    for ( int i = 0; i < pReq->ustCount; ++i )
    {
        const MaterialInfo* pInfo = pUpToEquipInfo->GetMaterialByID( pReq->xMaterialID[i] );
        if ( pInfo == NULL )
        {
            xAck.chResult = MsgEquipUpgradeAck::ECD_Unkown;
            GettheServer().SendMsgToSingle( &xAck, this );
            return;
        }

        if ( !pInfo->IsMustMaterial() )
        {
            ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pInfo->GetMaterialID() );
            if ( pItemCommon == NULL )
            {
                xAck.chResult = MsgEquipUpgradeAck::ECD_Unkown;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }

            ItemBag* pItemBag = GetItemBagByItemType( pItemCommon->ucItemType );
            unsigned int nMaterialCount = pItemBag->GetItemCount( pInfo->GetMaterialID() );
            if ( nMaterialCount < pInfo->GetMaterialCount() )
            {
                xAck.chResult = MsgEquipUpgradeAck::ECD_LackMaterial;
                GettheServer().SendMsgToSingle( &xAck, this );
                return;
            }
        }
    }

    // 条件都满足, 处理升阶
    // 创建新物品
    __int64 nGuild = 0;
    if ( AddItem( pReq->ustUpToEquipID, 1, EIGS_Upgrade, true, &nGuild ) != ierr_Success )
    {
        xAck.chResult = MsgEquipUpgradeAck::ECD_PackageFull;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    SCharItem* pNewEquip = _NormalItemBag.GetItemByOnlyBigId( nGuild );
    if ( pNewEquip == NULL )
    {
        //Log( "升阶成功后找不到新物品[%I64u]", nGuild );
		Log( theXmlString.GetString(eServerLog_UpNoFindNewItem), nGuild );

        xAck.chResult = MsgEquipUpgradeAck::ECD_Unkown;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    pNewEquip->SetBounded( pEquip->IsBounded() );

    // 删除必须的材料
    for ( int i = 0; i < pUpToEquipInfo->GetMaterialCount(); ++i )
    {
        const MaterialInfo* pInfo = pUpToEquipInfo->GetMaterialByIndex( i );
        if ( pInfo == NULL )
        { continue; }

        if ( pInfo->IsMustMaterial() )
        {   
            ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pInfo->GetMaterialID() );
            if ( pItemCommon == NULL )
            { return; }

            uint8 chBagType = GetItemBagType( pItemCommon->ucItemType );
            ItemBag* pItemBag = GetItemBagByItemType( pItemCommon->ucItemType );
            unsigned int nResult = pItemBag->PopItemByID( pInfo->GetMaterialID(), pInfo->GetMaterialCount() );
            if ( nResult == ierr_Success )
            {
                //Log( "升阶成功,删除材料[%s] [%d]个", pItemCommon->GetItemName(), pInfo->GetMaterialCount() );
				Log( theXmlString.GetString(eServerLog_UpItemOk), pItemCommon->GetItemName(), pInfo->GetMaterialCount() );

                MsgRemoveItem msg;
                msg.ucItemBagType = chBagType;
                msg.ustItemID     = pInfo->GetMaterialID();
                msg.ustCount      = pInfo->GetMaterialCount();
                GettheServer().SendMsgToSingle( &msg, this );
            }
        }
    }

    // 删除辅助材料
    for ( int i = 0; i < pReq->ustCount; ++i )
    {
        const MaterialInfo* pInfo = pUpToEquipInfo->GetMaterialByID( pReq->xMaterialID[i] );
        if ( pInfo == NULL )
        { continue; }

        if ( !pInfo->IsMustMaterial() )
        {
            // 判断辅助材料
            if( pInfo->IsSaveOpenLightMaterial() )      // 保留鎏金
            {
                pNewEquip->equipdata.purpleRands[0] = pEquip->equipdata.purpleRands[0];
            }

            if ( pInfo->IsSaveCheckupmaterial() )       // 保留鉴定
            {
                memcpy_s( pNewEquip->equipdata.baseRands, sizeof( pNewEquip->equipdata.baseRands ), pEquip->equipdata.baseRands, sizeof( unsigned short ) * SCharItem::EConstDefine_BaseRandMaxCount );
            }

            if ( pInfo->IsSaveElementsmaterial() )      // 保留五行
            {
                pNewEquip->SetElements( pEquip->GetElements() ); 
            }

            if ( pInfo->IsSaveSuitLevel() )         // 保存五行提纯和精炼等级
            {
                pNewEquip->SetSuitLevel( pEquip->GetSuitLevel() ); 
            }

            ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pInfo->GetMaterialID() );
            if ( pItemCommon == NULL )
            { return; }

            uint8 chBagType = GetItemBagType( pItemCommon->ucItemType );
            ItemBag* pItemBag = GetItemBagByItemType( pItemCommon->ucItemType );
            unsigned int nResult = pItemBag->PopItemByID( pInfo->GetMaterialID(), pInfo->GetMaterialCount() );
            if ( nResult == ierr_Success )
            {
                /*Log( "升阶成功,删除材料[%s] [%d]个", pItemCommon->GetItemName(), pInfo->GetMaterialCount() );*/
				Log( theXmlString.GetString(eServerLog_UpItemOk), pItemCommon->GetItemName(), pInfo->GetMaterialCount() );

                MsgRemoveItem msg;
                msg.ucItemBagType = chBagType;
                msg.ustItemID     = pInfo->GetMaterialID();
                msg.ustCount      = pInfo->GetMaterialCount();
                GettheServer().SendMsgToSingle( &msg, this );
            }
        }
    }

    // 扣钱
    OperateJiaoZi( EOT_Sub, pUpToEquipInfo->GetCostMoney(), true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_EquipUpgrade);

	//LYH日志添加
	SCharItem * _item = GetBagItemByGuid(pReq->nEquipGuid);
	if (_item)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
		theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
		_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetIconInItemBag());
	}

    // 删除旧装备
    RemoveItem( BT_NormalItemBag, pReq->ustEquipIndex, NUMERIC_ONE, pReq->nEquipGuid );



    xAck.nNewEquipGuid = pNewEquip->itembaseinfo.nOnlyInt;
    xAck.bIsSoulBounded = pNewEquip->IsBounded();
    memcpy_s( xAck.ustRand, sizeof( xAck.ustRand ), pNewEquip->equipdata.baseRands, sizeof( pNewEquip->equipdata.baseRands ) );
    xAck.nElemenet = pNewEquip->itembaseinfo.value1;
    GettheServer().SendMsgToSingle( &xAck, this );
}

void GamePlayer::OnMsgSuitLevelUpReq( Msg* pMsg )
{
    MsgSuitLevelUpReq* pReq = static_cast< MsgSuitLevelUpReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    MsgSuitLevelUpAck xAck;
    SCharItem* pCharEquip = _NormalItemBag.GetItemByIndex( pReq->stEquipIndex );
    if ( pCharEquip == NULL || pCharEquip->itembaseinfo.nOnlyInt != pReq->nEquipGuid )
    {
        xAck.uchResult = MsgSuitLevelUpAck::ECD_Unkown;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    ItemDefine::SItemCommon* pEquipCommon = GettheItemDetail().GetItemByID( pCharEquip->itembaseinfo.ustItemID );
    if ( pEquipCommon == NULL || pEquipCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    {
        xAck.uchResult = MsgSuitLevelUpAck::ECD_NotSuitEquip;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    ItemDefine::SItemArmour* pEquipArmour = static_cast< ItemDefine::SItemArmour* >( pEquipCommon );
    if ( pEquipArmour == NULL )
    { return; }

    if ( !pEquipArmour->IsSuitEquip() )
    {
        xAck.uchResult = MsgSuitLevelUpAck::ECD_NotSuitEquip;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    // 判断鉴定材料
    SCharItem* pCharItem = NULL;
    switch ( pReq->xItemInfo[0].chItemBagType )
    {
    case BT_MaterialBag:
        pCharItem = _MaterialItemBag.GetItemByIndex( pReq->xItemInfo[0].stItemIndex );
        break;
    default:
        pCharItem = _NormalItemBag.GetItemByIndex( pReq->xItemInfo[0].stItemIndex );
    }

    if ( pCharItem == NULL || pCharItem->itembaseinfo.nOnlyInt != pReq->xItemInfo[0].nItemGuid )
    {
        xAck.uchResult = MsgSuitLevelUpAck::ECD_Unkown;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
    if ( pItemCommon == NULL || pItemCommon->ucItemType != ItemDefine::ITEMTYPE_CHECKUP )
    {
        xAck.uchResult = MsgSuitLevelUpAck::ECD_ErrorCheckUpItem;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    ItemDefine::SItemCheckUp* pItemCheckUp = static_cast< ItemDefine::SItemCheckUp* >( pItemCommon );
    if ( pItemCheckUp == NULL )
    { return; }

    if ( pItemCheckUp->stCheckUpType != ItemDefine::SItemCheckUp::ECD_Suit )
    {
        xAck.uchResult = MsgSuitLevelUpAck::ECD_ErrorCheckUpItem;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    switch ( pReq->chOperate )
    {
    case MsgSuitLevelUpReq::ECD_SkillSuitLevelUp:
        {
            xAck.uchResult  = ProcessSkillSuitLevelUp( pReq, pCharEquip, pEquipArmour, pItemCheckUp );
            xAck.nLeftMoney = GetMoney();
            xAck.nValue     = pCharEquip->itembaseinfo.value1;
            xAck.stAttriID  = pCharEquip->equipdata.suitRands[0];
            GettheServer().SendMsgToSingle( &xAck, this );
        }
        break;
    case MsgSuitLevelUpReq::ECD_ElementSuitLevelUp:
        {
            xAck.uchResult  = ProcessElementSuitLevelUp( pReq, pCharEquip, pEquipArmour, pItemCheckUp );
            xAck.nLeftMoney = GetMoney();
            xAck.nValue     = pCharEquip->itembaseinfo.value1;
            //xAck.stAttriID  = pCharEquip->equipdata.specials[ SCharItem::e_ElementSuitIndex ];
            GettheServer().SendMsgToSingle( &xAck, this );
        }
        break;
    }
}

void GamePlayer::OnMsgRandAttribute(Msg* pMsg)
{
	if (!pMsg)
		return;

	MsgRandAttrReq* pReq = static_cast< MsgRandAttrReq* >( pMsg );

	SCharItem* pArmour = _NormalItemBag.GetItemByIndex( pReq->sArmour.nItemIndex );
	if (!pArmour)
		return;
	if ( pArmour->GetItemGuid() != pReq->sArmour.nItemGuid )
	{
		_NormalItemBag.CleanUp();
		return;
	}
	// 是否有材料
	SCharItem* pMaintainItem = NULL;
	ItemBag*   pSelectBag    = NULL;
	switch( pReq->sMaterial.nItemBagType )
	{
	case BT_MaterialBag:
		pMaintainItem = _MaterialItemBag.GetItemByIndex( pReq->sMaterial.nItemIndex );
		pSelectBag = &_MaterialItemBag;
		break;
	default:
		pMaintainItem = _NormalItemBag.GetItemByIndex( pReq->sMaterial.nItemIndex );
		pSelectBag = &_NormalItemBag;
	}

	if ( pMaintainItem == NULL || pSelectBag == NULL )
		return;

	if ( pMaintainItem->GetItemGuid() != pReq->sMaterial.nItemGuid )
	{
		pSelectBag->CleanUp();
		return;
	}

	ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pArmour->itembaseinfo.ustItemID );
	if ( !pItemCanEquip )
		return; 
	if ( !pItemCanEquip->RandWhenCreate())
		return;

	if ( pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
		return;

	unsigned short oldAtr[SCharItem::EConstDefine_BaseRandMaxCount] = {0};
	for(int i = 0; i < SCharItem::EConstDefine_BaseRandMaxCount ; i++)
	{
		oldAtr[i] = pArmour->equipdata.baseRands[i];
	}

	ItemDefine::SCreateMaterial *pMaterialItem = (ItemDefine::SCreateMaterial *)GettheItemDetail().GetItemByID( pMaintainItem->itembaseinfo.ustItemID);
	if (!pMaterialItem)
		return;

	if ( pMaterialItem->useCostMoney > GetJiaoZiMoney()  )
		return;

	bool IsNeedBounded = (pMaintainItem->IsBounded() || pArmour->IsBounded());

	//LYH日志添加
	SCharItem * _item = GetBagItemByGuid(pReq->sMaterial.nItemGuid);
	if (_item)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
		theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
		_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
	}

	// 扣除材料
	if (!RemoveItem( pReq->sMaterial.nItemBagType, 
		pReq->sMaterial.nItemIndex, 
		NUMERIC_ONE, 
		pReq->sMaterial.nItemGuid ))
		return;	

	if ( pItemCanEquip->RandWhenCreate())
		theRunTimeData.EquipBaseRand(*pArmour);
	if(IsNeedBounded)
		pArmour->SetBounded(true);

	OperateJiaoZi( EOT_Sub, pMaterialItem->useCostMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_RandAttribute );

	theRunTimeData.EquipScore(*pArmour, GettheItemDetail().GetItemByID( pArmour->itembaseinfo.ustItemID )); // 计算装备评分

	MsgRandAttrAck msg;
	msg.nNormalBagIndex = pReq->sArmour.nItemIndex;
	msg.AddCharItem(*pArmour);
	SendMessageToClient( &msg );


	unsigned short curAtr[SCharItem::EConstDefine_BaseRandMaxCount] = {0};
	for(int i = 0; i < SCharItem::EConstDefine_BaseRandMaxCount ; i++)
	{
		curAtr[i] = pArmour->equipdata.baseRands[i];
	}

	//LYH日志添加 装备属性随机
	ItemDefine::SItemCommon *pCommon =  GettheItemDetail().GetItemByID(pArmour->GetItemID());
	if(pCommon)
	theLogEventService.LogItemUpgrade(GetAccountID(),GetDBCharacterID(),pArmour->GetItemID(),1,pArmour->GetItemGuid(),eItemLogInfo_ItemUpgrade_Random,1,oldAtr,curAtr,
	                                  GetCharName(),pCommon->GetItemName());

}

void GamePlayer::OnMsgTransferStar( Msg* pMsg )
{
	MsgTransferStar* pTransferStar = static_cast< MsgTransferStar* >( pMsg );
	if (!pTransferStar)
		return;

	MsgTransferStarAck msg;
	msg.eresult = MsgTransferStarAck::eR_Success;

	// 目标装备
	SCharItem* pTargetEquipItem = _NormalItemBag.GetItemByIndex( pTransferStar->sTargetEquip.nItemIndex );
	if ( !pTargetEquipItem )
		return;
	if ( pTargetEquipItem->GetItemGuid() != pTransferStar->sTargetEquip.nItemGuid )
	{
		_NormalItemBag.CleanUp();
		return;
	}
	ItemDefine::SItemCanEquip* pItemCanEquipTarget = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pTargetEquipItem->itembaseinfo.ustItemID );
	if ( !pItemCanEquipTarget  )
		return; 

	if ( pItemCanEquipTarget->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItemCanEquipTarget->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
		return;

	// 源装备
	SCharItem* pSourceEquipItem = _NormalItemBag.GetItemByIndex( pTransferStar->sSourceEquip.nItemIndex );
	if ( pSourceEquipItem == NULL )
		return;

	if ( pSourceEquipItem->GetItemGuid() != pTransferStar->sSourceEquip.nItemGuid )
	{
		_NormalItemBag.CleanUp();
		return;
	}

	ItemDefine::SItemCanEquip* pItemCanEquipSource = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pSourceEquipItem->itembaseinfo.ustItemID );
	if ( !pItemCanEquipSource )
		return; 

	if ( pItemCanEquipSource->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItemCanEquipSource->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
		return; 

	// 是否有材料
	SCharItem* pMaintainItem = NULL;
	ItemBag*   pSelectBag    = NULL;
	switch( pTransferStar->sMaterial.nItemBagType )
	{
	case BT_MaterialBag:
		pMaintainItem = _MaterialItemBag.GetItemByIndex( pTransferStar->sMaterial.nItemIndex );
		pSelectBag = &_MaterialItemBag;
		break;
	default:
		pMaintainItem = _NormalItemBag.GetItemByIndex( pTransferStar->sMaterial.nItemIndex );
		pSelectBag = &_NormalItemBag;
	}

	if ( pMaintainItem == NULL || pSelectBag == NULL )
		return;

	if ( pMaintainItem->GetItemGuid() != pTransferStar->sMaterial.nItemGuid )
	{
		pSelectBag->CleanUp();
		return;
	}

	//是否同一个部位
	if ( pItemCanEquipTarget->ustEquipType != pItemCanEquipSource->ustEquipType )
		return;

	//源装备等级不能大于目标装备
	if ( pItemCanEquipSource->stEquipLevelReq > pItemCanEquipTarget->stEquipLevelReq )
		return;

	//是否等级差别太大
	if ( pItemCanEquipTarget->stEquipLevelReq - pItemCanEquipSource->stEquipLevelReq > 10 )
		return;

	//判断星级
	if ( pSourceEquipItem->equipdata.ucLevel <= pTargetEquipItem->equipdata.ucLevel )
		return;

	const TransferStarMaterial* pMaterial = theStarLevelUpConfig.GetTransferStarMaterial(pMaintainItem->itembaseinfo.ustItemID);
	if (!pMaterial)
		return;

	// 判断钱够不够
	int costMoney = pMaterial->GetCostMoney(pSourceEquipItem->equipdata.ucLevel);
	if ( costMoney > GetJiaoZiMoney()  )
		return;


	//LYH日志添加
	SCharItem * _item = GetBagItemByGuid(pTransferStar->sMaterial.nItemGuid);
	if (_item)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
		theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
		_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
	}


	// 扣除材料
	if (!RemoveItem( pTransferStar->sMaterial.nItemBagType, 
		pTransferStar->sMaterial.nItemIndex, 
		NUMERIC_ONE, 
		pTransferStar->sMaterial.nItemGuid ))
		return;

	
	float fProbility = 0.0f;
	fProbility = pMaterial->GetModulus(pSourceEquipItem->equipdata.ucLevel);
	/*if (pItemCanEquipSource->stEquipLevelReq == pItemCanEquipTarget->stEquipLevelReq)
		fProbility = 1.0f;*/
	uint8  nRandNum = theRand.rand16() % RAND_NUM;

	unsigned short OldLev[1] ={pTargetEquipItem->equipdata.ucLevel} ;
	unsigned short OldSourceLev[1] ={pSourceEquipItem->equipdata.ucLevel} ;

	if (pItemCanEquipSource->stEquipLevelReq == pItemCanEquipTarget->stEquipLevelReq)
	{
		pTargetEquipItem->equipdata.ucLevel = pSourceEquipItem->equipdata.ucLevel;
		pSourceEquipItem->equipdata.ucLevel = 0;

		// 两件装备都绑定
		pSourceEquipItem->SetBounded(true);
		pTargetEquipItem->SetBounded(true);
	}
	else
	{
		if (pMaintainItem->itembaseinfo.ustItemID == SID_TRABSFERSTAR_UNDROP)
		{
			if (nRandNum < fProbility * RAND_NUM) //转星成功
			{
				pTargetEquipItem->equipdata.ucLevel = pSourceEquipItem->equipdata.ucLevel;
				pSourceEquipItem->equipdata.ucLevel = 0;

				// 两件装备都绑定
				pSourceEquipItem->SetBounded(true);
				pTargetEquipItem->SetBounded(true);
			}
			else
				msg.eresult = MsgTransferStarAck::eR_Fail;
		}
		else
		{
			nRandNum = theRand.rand16() % RAND_NUM;

			if (nRandNum < pMaterial->GetDropThree(pSourceEquipItem->equipdata.ucLevel) * RAND_NUM)
			{
				if (pSourceEquipItem->equipdata.ucLevel >= 3)
					pSourceEquipItem->equipdata.ucLevel -= 3;
				else
					pSourceEquipItem->equipdata.ucLevel = 0;

				msg.eresult = MsgTransferStarAck::eR_DropThree;
			}
			else if (nRandNum < pMaterial->GetDropTwo(pSourceEquipItem->equipdata.ucLevel) * RAND_NUM)
			{
				if (pSourceEquipItem->equipdata.ucLevel >= 2)
					pSourceEquipItem->equipdata.ucLevel -= 2;
				else
					pSourceEquipItem->equipdata.ucLevel = 0;

				msg.eresult = MsgTransferStarAck::eR_DropTwo;
			}
			else if (nRandNum < pMaterial->GetDropOne(pSourceEquipItem->equipdata.ucLevel) * RAND_NUM)
			{
				if (pSourceEquipItem->equipdata.ucLevel >= 1)
					pSourceEquipItem->equipdata.ucLevel -= 1;
				else

					pSourceEquipItem->equipdata.ucLevel = 0;

				msg.eresult = MsgTransferStarAck::eR_DropOne;
			}

			pTargetEquipItem->equipdata.ucLevel = pSourceEquipItem->equipdata.ucLevel;
			pSourceEquipItem->equipdata.ucLevel = 0;
			// 两件装备都绑定
			pSourceEquipItem->SetBounded(true);
			pTargetEquipItem->SetBounded(true);
		}
	}

	OperateJiaoZi( EOT_Sub, costMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_TransferStar );

	theRunTimeData.EquipScore(*pTargetEquipItem, GettheItemDetail().GetItemByID( pTargetEquipItem->itembaseinfo.ustItemID )); // 计算装备评分
	theRunTimeData.EquipScore(*pSourceEquipItem, GettheItemDetail().GetItemByID( pSourceEquipItem->itembaseinfo.ustItemID )); // 计算装备评分

	msg.nTargetBagIndex = pTransferStar->sTargetEquip.nItemIndex;
	msg.nSourceBagIndex = pTransferStar->sSourceEquip.nItemIndex;

	msg.AddTargetCharItem( *pTargetEquipItem ) ;
	msg.AddSourcCharItem ( *pSourceEquipItem ) ;
	SendMessageToClient( &msg );

	unsigned short curLev[1] = {pTargetEquipItem->equipdata.ucLevel};
	unsigned short curSourceLev[1] = {pSourceEquipItem->equipdata.ucLevel};
	//LYH日志添加（转星）
	ItemDefine::SItemCommon *pCommon =  GettheItemDetail().GetItemByID(pTargetEquipItem->GetItemID());
	if(pCommon)
	theLogEventService.LogItemUpgrade(GetAccountID(),GetDBCharacterID(),pTargetEquipItem->GetItemID(),1,pTargetEquipItem->GetItemGuid(),eItemLogInfo_ItemUpgrade_TradeStar,0,OldLev,curLev,
	                                 GetCharName(),pCommon->GetItemName());

	pCommon =  GettheItemDetail().GetItemByID(pSourceEquipItem->GetItemID());
	if(pCommon)
	theLogEventService.LogItemUpgrade(GetAccountID(),GetDBCharacterID(),pSourceEquipItem->GetItemID(),1,pSourceEquipItem->GetItemGuid(),eItemLogInfo_ItemUpgrade_TradeStar,0,OldSourceLev,curSourceLev,
		                              GetCharName(),pCommon->GetItemName());
}

void GamePlayer::_ProcessEquipMaintain      ( MsgEquipEvolve* pEquipEvolve )
{
    if (pEquipEvolve == NULL) 
    { return; }

    MsgEquipMaintainAck msg;
    msg.header.stID     = GetID();
    msg.nEvolveType     = MsgEquipEvolve::ET_Maintain;
    msg.nResult         = MsgIntensifyEquip::e_Succeed;

    // 目标装备
    SCharItem* pTargetEquipItem = _NormalItemBag.GetItemByIndex( pEquipEvolve->nNormalBagIndex );
    if ( pTargetEquipItem == NULL )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pTargetEquipItem->GetItemGuid() != pEquipEvolve->nNormalGuid )
    {
        _NormalItemBag.CleanUp();
        return;
    }

    ItemDefine::SItemCanEquip* pItemCanEquipTarget = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pTargetEquipItem->itembaseinfo.ustItemID );
    if ( pItemCanEquipTarget == NULL )
    { return; }

    if ( pItemCanEquipTarget->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItemCanEquipTarget->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    { return; }

    if ( pItemCanEquipTarget->bFashion || pItemCanEquipTarget->IsCannotEvolve() )
    { 
        msg.nResult = MsgIntensifyEquip::e_FashionCanNotEvolve;
        GettheServer().SendMsgToSingle(&msg,this);
        return; 
    }

    // 源装备
    SCharItem* pSourceEquipItem = _NormalItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
    if ( pSourceEquipItem == NULL )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pSourceEquipItem->GetItemGuid() != pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid )
    {
        _NormalItemBag.CleanUp();
        return;
    }

    ItemDefine::SItemCanEquip* pItemCanEquipSource = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pTargetEquipItem->itembaseinfo.ustItemID );
    if ( pItemCanEquipSource == NULL )
    { return; }

    if ( pItemCanEquipSource->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItemCanEquipSource->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    { return; }

    if ( pItemCanEquipSource->bFashion || pItemCanEquipSource->IsCannotEvolve() )
    { 
        msg.nResult = MsgIntensifyEquip::e_ItemNotMatch;
        GettheServer().SendMsgToSingle(&msg,this);
        return; 
    }

    // 是否有材料
    SCharItem* pMaintainItem = NULL;
    ItemBag*   pSelectBag    = NULL;
    switch( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagType )
    {
    case BT_MaterialBag:
        pMaintainItem = _MaterialItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagIndex );
        pSelectBag = &_MaterialItemBag;
        break;
    default:
        pMaintainItem = _NormalItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagIndex );
        pSelectBag = &_NormalItemBag;
    }

    if ( pMaintainItem == NULL || pSelectBag == NULL )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pMaintainItem->GetItemGuid() != pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].guid )
    {
        pSelectBag->CleanUp();
        return;
    }

    ItemDefine::SCreateMaterial* pMaterialItemConfig = (ItemDefine::SCreateMaterial*)GettheItemDetail().GetItemByID( pMaintainItem->itembaseinfo.ustItemID );
    if ( pMaterialItemConfig == NULL )
    { return; }

    if ( pMaterialItemConfig->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
    { 
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pMaterialItemConfig->stMaterialType != ItemDefine::ematerial_maintain )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 判断是否是可作用的装备部位
    if ( !pMaterialItemConfig->CanEquipPart( pItemCanEquipTarget->ustEquipType ) )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotMatch;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 材料等级限制
    if ( pMaterialItemConfig->levelLowLimit > pItemCanEquipTarget->stEquipLevelReq  )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep;  
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pMaterialItemConfig->levelUpLimit < pItemCanEquipTarget->stEquipLevelReq  )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep;  
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 保值条件判断
    if(pItemCanEquipTarget->ustItemID != pItemCanEquipSource->ustItemID)
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotMatch;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if(pSourceEquipItem->equipdata.quality  != ItemDefine::EQL_Purple)
    {
        msg.nResult = MsgIntensifyEquip::e_NotEnoughQuality;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 判断钱够不够
    int costMoney = pMaterialItemConfig->useCostMoney;
    if ( costMoney > GetJiaoZiMoney()  )
    {
        msg.nResult = MsgIntensifyEquip::e_NotEnoughMoney;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }
	// 扣除材料
    if(!RemoveItem( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagType, 
        pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagIndex, 
        NUMERIC_ONE, 
        pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].guid ))
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
	}

    // 保值
    pTargetEquipItem->equipdata = pSourceEquipItem->equipdata ;

    // 宝石消失
    for (int i = 0; i < SCharItem::EConstDefine_GemHoleMaxCount; ++i )
    {
        pSourceEquipItem->equipdata.gemIds[i] = InvalidLogicNumber;
        pTargetEquipItem->equipdata.gemIds[i] = InvalidLogicNumber;
    }
    
    if (pSourceEquipItem->IsSoulStamp())
    { pTargetEquipItem->SetSoulStamp(true); }

    // 两件装备都绑定
    pSourceEquipItem->SetBounded(true);
    pTargetEquipItem->SetBounded(true);


	//LYH日志添加
	SCharItem * _item = GetBagItemByGuid(pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].guid);
	if (_item)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
		if(!theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
			_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName()))
		{
			Log( theXmlString.GetString(eServerLog_SameLevItemKeepValue), pItemCanEquipTarget->GetItemName() , pTargetEquipItem->itembaseinfo.nOnlyInt, pSourceEquipItem->itembaseinfo.nOnlyInt );
		}
	}

    OperateJiaoZi( EOT_Sub, costMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_EquipMaintainCross);

    /*Log( "同级保值目标[%s][%I64u] 源[%I64u] 成功", pItemCanEquipTarget->GetItemName() , pTargetEquipItem->itembaseinfo.nOnlyInt, pSourceEquipItem->itembaseinfo.nOnlyInt );*/	

    msg.nTargetBagIndex = pEquipEvolve->nNormalBagIndex;
    msg.nSourceBagIndex = pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex;

    msg.AddTargetCharItem( *pTargetEquipItem ) ;
    msg.AddSourcCharItem ( *pSourceEquipItem ) ;
    SendMessageToClient( &msg );
}

void GamePlayer::_ProcessEquipMaintainCross ( MsgEquipEvolve* pEquipEvolve )
{
    if (pEquipEvolve == NULL) 
    { return; }

    MsgEquipMaintainAck msg;
    msg.header.stID      = GetID();
    msg.nEvolveType     = MsgEquipEvolve::ET_MaintainCross;
    msg.nResult         = MsgIntensifyEquip::e_Succeed;

    // 目标装备
    SCharItem* pTargetEquipItem = _NormalItemBag.GetItemByIndex( pEquipEvolve->nNormalBagIndex );
    if ( pTargetEquipItem == NULL )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pTargetEquipItem->GetItemGuid() != pEquipEvolve->nNormalGuid )
    {
        _NormalItemBag.CleanUp();
        return;
    }

    ItemDefine::SItemCanEquip* pItemCanEquipTarget = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pTargetEquipItem->itembaseinfo.ustItemID );
    if ( pItemCanEquipTarget == NULL )
    { return; }

    if ( pItemCanEquipTarget->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItemCanEquipTarget->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    { return; }

    if ( pItemCanEquipTarget->bFashion || pItemCanEquipTarget->IsCannotEvolve() )
    { 
        msg.nResult = MsgIntensifyEquip::e_FashionCanNotEvolve;
        GettheServer().SendMsgToSingle(&msg,this);
        return; 
    }

    // 源装备
    SCharItem* pSourceEquipItem = _NormalItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
    if ( pSourceEquipItem == NULL )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pSourceEquipItem->GetItemGuid() != pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid )
    {
        _NormalItemBag.CleanUp();
        return;
    }

    ItemDefine::SItemCanEquip* pItemCanEquipSource = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pTargetEquipItem->itembaseinfo.ustItemID );
    if ( pItemCanEquipSource == NULL )
    { return; }

    if ( pItemCanEquipSource->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItemCanEquipSource->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    { return; }

    if ( pItemCanEquipSource->bFashion || pItemCanEquipSource->IsCannotEvolve() )
    { 
        msg.nResult = MsgIntensifyEquip::e_ItemNotMatch;
        GettheServer().SendMsgToSingle(&msg,this);
        return; 
    }

    int disparity = abs( pItemCanEquipTarget->stEquipLevelReq - pItemCanEquipSource->stEquipLevelReq );
    if ( (disparity == 0) || (disparity > g_Cfg.maintainCrossLevel) )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotMatch;
        GettheServer().SendMsgToSingle(&msg,this);
        return; 
    }

    // 是否有材料
    SCharItem* pMaintainItem = NULL;
    ItemBag*   pSelectBag    = NULL;
    switch( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagType )
    {
    case BT_MaterialBag:
        pMaintainItem = _MaterialItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagIndex );
        pSelectBag = &_MaterialItemBag;
        break;
    default:
        pMaintainItem = _NormalItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagIndex );
        pSelectBag = &_NormalItemBag;
    }

    if ( pMaintainItem == NULL || pSelectBag == NULL )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pMaintainItem->GetItemGuid() != pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].guid )
    {
        pSelectBag->CleanUp();
        return;
    }

    ItemDefine::SCreateMaterial* pMaterialItemConfig = (ItemDefine::SCreateMaterial*)GettheItemDetail().GetItemByID( pMaintainItem->itembaseinfo.ustItemID );
    if ( pMaterialItemConfig == NULL )
    { return; }

    if ( pMaterialItemConfig->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
    { 
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pMaterialItemConfig->stMaterialType != ItemDefine::ematerial_maintain )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 判断是否是可作用的装备部位
    if ( !pMaterialItemConfig->CanEquipPart( pItemCanEquipTarget->ustEquipType ) )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotMatch;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 材料等级限制
    if ( pMaterialItemConfig->levelLowLimit > pItemCanEquipTarget->stEquipLevelReq  )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep;  
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pMaterialItemConfig->levelUpLimit < pItemCanEquipTarget->stEquipLevelReq  )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep;  
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 保值条件判断
    if(pTargetEquipItem->equipdata.quality != ItemDefine::EQL_Golden )
    {
        msg.nResult = MsgIntensifyEquip::e_NotEnoughQuality;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if(pSourceEquipItem->equipdata.quality != ItemDefine::EQL_Purple)
    {
        msg.nResult = MsgIntensifyEquip::e_NotEnoughQuality;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 判断钱够不够
    int costMoney = pMaterialItemConfig->useCostMoney;
    if ( costMoney > GetJiaoZiMoney()  )
    {
        msg.nResult = MsgIntensifyEquip::e_NotEnoughMoney;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }
	 // 扣除材料
	if(!RemoveItem( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagType, 
        pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagIndex, 
        NUMERIC_ONE, 
        pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].guid ))
	{
		msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
	}

    // 保值
    pTargetEquipItem->equipdata = pSourceEquipItem->equipdata;

    // 宝石消失
    for (int i = 0; i < SCharItem::EConstDefine_GemHoleMaxCount; ++i )
    {
        pSourceEquipItem->equipdata.gemIds[i] = InvalidLogicNumber;
        pTargetEquipItem->equipdata.gemIds[i] = InvalidLogicNumber;
    }

    // 两件装备都绑定
    pSourceEquipItem->SetBounded(true);
    pTargetEquipItem->SetBounded(true);


	SCharItem * _item = GetBagItemByGuid( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].guid);
	if (_item)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
		if (!theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
			_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName()))
		{
			Log( theXmlString.GetString(eServerLog_UnSameLevItemKeepValue), pItemCanEquipTarget->GetItemName() , pTargetEquipItem->itembaseinfo.nOnlyInt, 
				pItemCanEquipSource->GetItemName() , pSourceEquipItem->itembaseinfo.nOnlyInt );
		}
	}

    OperateJiaoZi( EOT_Sub, costMoney, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_EquipMaintainCross);

    /*Log( "跨级保值目标[%s][%I64u] 源[[%s][%I64u] 成功", pItemCanEquipTarget->GetItemName() , pTargetEquipItem->itembaseinfo.nOnlyInt, */
	
    msg.nTargetBagIndex = pEquipEvolve->nNormalBagIndex;
    msg.nSourceBagIndex = pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex;

    msg.AddTargetCharItem( *pTargetEquipItem ) ;
    msg.AddSourcCharItem ( *pSourceEquipItem ) ;
    SendMessageToClient( &msg );
}

void GamePlayer::_ProcessEquipCharmAbsorb   ( MsgEquipEvolve* pEquipEvolve )
{
    if (pEquipEvolve == NULL) 
    { return; }

    MsgIntensifyEquip msg;
    msg.header.stID      = GetID();
    msg.nEvolveType     = MsgEquipEvolve::ET_Charm      ;
    msg.nResult         = MsgIntensifyEquip::e_Succeed  ;

    // 目标装备
    SCharItem* pEquipItem = _NormalItemBag.GetItemByIndex( pEquipEvolve->nNormalBagIndex );
    if ( pEquipItem == NULL )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pEquipItem->GetItemGuid() != pEquipEvolve->nNormalGuid )
    {
        _NormalItemBag.CleanUp();
        return;
    }

    ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pEquipItem->itembaseinfo.ustItemID );
    if ( pItemCanEquip == NULL )
    { return; }

    if ( pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    { return; }

    if ( pItemCanEquip->bFashion || pItemCanEquip->IsCannotEvolve() )
    { 
        msg.nResult = MsgIntensifyEquip::e_FashionCanNotEvolve;
        GettheServer().SendMsgToSingle(&msg,this);
        return; 
    }

    // 是否有符文
    SCharItem* pCharmItem = NULL;
    ItemBag*   pSelectBag = NULL;
    switch( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType )
    {
    case BT_MaterialBag:
        pCharmItem = _MaterialItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
        pSelectBag = &_MaterialItemBag;
        break;
    default:
        pCharmItem = _NormalItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
        pSelectBag = &_NormalItemBag;
    }

    if ( pCharmItem == NULL || pSelectBag == NULL )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pCharmItem->GetItemGuid() != pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid )
    {
        pSelectBag->CleanUp();
        return;
    }

    ItemDefine::SCreateMaterial* pMaterialItemConfig = (ItemDefine::SCreateMaterial*)GettheItemDetail().GetItemByID( pCharmItem->itembaseinfo.ustItemID );
    if ( pMaterialItemConfig == NULL )
    { return; }

    if ( pMaterialItemConfig->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
    { 
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pMaterialItemConfig->stMaterialType != ItemDefine::ematerial_charm )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 判断是否是可作用的装备部位
    if ( !pMaterialItemConfig->CanEquipPart( pItemCanEquip->ustEquipType ) )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotMatch;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 材料等级限制
    if ( pMaterialItemConfig->levelLowLimit > pItemCanEquip->stEquipLevelReq  )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep;  
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pMaterialItemConfig->levelUpLimit < pItemCanEquip->stEquipLevelReq  )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep;  
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 条件判断
    if( pEquipItem->equipdata.quality  != ItemDefine::EQL_Blue)
    {
        msg.nResult = MsgIntensifyEquip::e_NotEnoughQuality;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if (pEquipItem->equipdata.baseRands[0] == InvalidLogicNumber)
    {
        msg.nResult = MsgIntensifyEquip::e_NotEnoughQuality;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if( pCharmItem->equipdata.quality  == ItemDefine::EQL_Blue)
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if (pCharmItem->equipdata.baseRands[0] != InvalidLogicNumber)
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 判断钱够不够
    int costMoney = pMaterialItemConfig->useCostMoney;
    if ( costMoney > GetJiaoZiMoney()  )
    {
        msg.nResult = MsgIntensifyEquip::e_NotEnoughMoney;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 计算概率
    int blueCount = 0,probability = 100;
    for (int i=0;i<SCharItem::EConstDefine_BaseRandMaxCount;++i)
    {
        if (pEquipItem->equipdata.baseRands[i] != InvalidLogicNumber)
        { ++blueCount; }
    }

    probability = CharmAbsorbProbabilitys[blueCount - 1] + ( theRand.rand32() % (int)pMaterialItemConfig->fAddIntensifyRate[0] ) ;

    // 优质符文布成功率 100%
    if (pCharmItem->equipdata.quality == ItemDefine::EQL_Green)
    { probability = 100; }

    if ( ( theRand.rand32() % RAND_NUM ) > probability )
    {// 吸蓝失败


		//LYH日志添加
		SCharItem * _item = GetBagItemByGuid(pEquipEvolve->nNormalGuid);
		if(_item)
		{
			ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
			if(_pitem)
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
			_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
		}
        // 扣除装备
        RemoveItem( BT_NormalItemBag, pEquipEvolve->nNormalBagIndex, NUMERIC_ONE, pEquipEvolve->nNormalGuid );
		//LYH日志添加
		_item = GetBagItemByGuid(pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid);
		if(_item)
		{
			ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
			if(_pitem)
			if(!theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
				_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName()))
			{
				//Log( "符文布 [%I64u] 吸收 [%I64u] 蓝 失败", pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid, pEquipEvolve->nNormalGuid  );
				Log( theXmlString.GetString(eServerLog_FuWenBuXiLanShiBai), pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid, pEquipEvolve->nNormalGuid  );
			}
		}
		
        // 扣除符文布
        RemoveItem( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType, 
            pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex, 
            NUMERIC_ONE, 
            pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid );	

      
        msg.nResult = MsgIntensifyEquip::e_Lost;
        SendMessageToClient( &msg );
        return;
    }

    // 设置品质为蓝色
    int blueIndex = theRand.rand32() % blueCount;
    pCharmItem->equipdata.quality = ItemDefine::EQL_Blue;
    pCharmItem->equipdata.baseRands[0] = pEquipItem->equipdata.baseRands[blueIndex];
    
    OperateJiaoZi( EOT_Sub, costMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_EquipCharmAbsorb);


	//LYH日志添加
	SCharItem * _item = GetBagItemByGuid(pEquipEvolve->nNormalGuid);
	if(_item)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
		if(!theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
			_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName()))
		{
			// Log( "符文布 [%I64u] 吸收 [%I64u] 蓝 成功", pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid, pEquipEvolve->nNormalGuid  );
			Log( theXmlString.GetString(eServerLog_FuWenBuXiLanChengGong), pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid, pEquipEvolve->nNormalGuid  );
		}
	}

    // 扣除装备
    RemoveItem( BT_NormalItemBag, pEquipEvolve->nNormalBagIndex, NUMERIC_ONE, pEquipEvolve->nNormalGuid );

    msg.nNormalBagIndex = pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex ;
    msg.AddCharItem( *pCharmItem );
    SendMessageToClient( &msg );
}

void GamePlayer::_ProcessEquipAmuletAbsorb  ( MsgEquipEvolve* pEquipEvolve )
{
    if (pEquipEvolve == NULL) 
    { return; }

    MsgIntensifyEquip msg;
    msg.header.stID      = GetID();
    msg.nEvolveType     = MsgEquipEvolve::ET_Amulet     ;
    msg.nResult         = MsgIntensifyEquip::e_Succeed  ;
    msg.nNormalBagIndex = pEquipEvolve->nNormalBagIndex ;

    // 目标装备护身符
    SCharItem* pEquipItem = _NormalItemBag.GetItemByIndex( pEquipEvolve->nNormalBagIndex );
    if ( pEquipItem == NULL )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pEquipItem->GetItemGuid() != pEquipEvolve->nNormalGuid )
    {
        _NormalItemBag.CleanUp();
        return;
    }

    ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pEquipItem->itembaseinfo.ustItemID );
    if ( pItemCanEquip == NULL )
    { return; }

    if ( pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItemCanEquip->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    { return; }

    // 判断是否是为护身符
    if ( pItemCanEquip->ustEquipType != ItemDefine::equip_Amulet )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotMatch;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 是否有符文
    SCharItem* pCharmItem = NULL;
    ItemBag*   pSelectBag = NULL;
    switch( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType )
    {
    case BT_MaterialBag:
        pCharmItem = _MaterialItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
        pSelectBag = &_MaterialItemBag;
        break;
    default:
        pCharmItem = _NormalItemBag.GetItemByIndex( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex );
        pSelectBag = &_NormalItemBag;
    }

    if ( pCharmItem == NULL || pSelectBag == NULL )
    {
        msg.nResult = MsgIntensifyEquip::e_ItemNotExist;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pCharmItem->GetItemGuid() != pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid )
    {
        pSelectBag->CleanUp();
        return;
    }

    ItemDefine::SCreateMaterial* pMaterialItemConfig = (ItemDefine::SCreateMaterial*)GettheItemDetail().GetItemByID( pCharmItem->itembaseinfo.ustItemID );
    if ( pMaterialItemConfig == NULL )
    { return; }

    if ( pMaterialItemConfig->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
    { 
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pMaterialItemConfig->stMaterialType != ItemDefine::ematerial_charm )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorMaterialItem;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 材料等级限制
    if ( pMaterialItemConfig->levelLowLimit > pItemCanEquip->stEquipLevelReq  )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep;  
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if ( pMaterialItemConfig->levelUpLimit < pItemCanEquip->stEquipLevelReq  )
    {
        msg.nResult = MsgIntensifyEquip::e_ErrorLevelRep;  
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 符文必须是蓝色
    if( pCharmItem->equipdata.quality  != ItemDefine::EQL_Blue)
    {
        msg.nResult = MsgIntensifyEquip::e_BaseRandNotOpen;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    if (pCharmItem->equipdata.baseRands[0] == InvalidLogicNumber)
    {
        msg.nResult = MsgIntensifyEquip::e_BaseRandNotOpen;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 护身符蓝色属性
    int blueCount = 0;
    for (int i=0;i< pEquipItem->equipdata.quality ;++i)
    {
        if (pEquipItem->equipdata.baseRands[i] != InvalidLogicNumber)
        { 
            if (GettheItemDetail().HaveSameRandType( pEquipItem->equipdata.baseRands[i], pCharmItem->equipdata.baseRands[0] ))
            {
                msg.nResult = MsgIntensifyEquip::e_HaveSameBaseRand;
                GettheServer().SendMsgToSingle(&msg,this);
                return;
            }

            ++blueCount; 
        }
    }

    if (pEquipItem->equipdata.quality <= blueCount )
    {
        msg.nResult = MsgIntensifyEquip::e_AmuletRandIsFull;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 判断钱够不够
    int costMoney = pMaterialItemConfig->useCostMoney;
    if ( costMoney > GetJiaoZiMoney()  )
    {
        msg.nResult = MsgIntensifyEquip::e_NotEnoughMoney;
        GettheServer().SendMsgToSingle(&msg,this);
        return;
    }

    // 设置蓝色属性
    for (int i=0;i < pEquipItem->equipdata.quality ; ++i)
    {
        if (pEquipItem->equipdata.baseRands[i] == InvalidLogicNumber)
        { 
            pEquipItem->equipdata.baseRands[i] = pCharmItem->equipdata.baseRands[0];
            break;
        }
    }

    OperateJiaoZi( EOT_Sub, costMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_EquipAmuletAbsorb );

	SCharItem * _item = GetBagItemByGuid(pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid);
	if (_item)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
		if (!theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemGuid(),NUMERIC_ONE,_item->GetItemGuid(),
			_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName()))
		{
			// Log( "护身符 [%I64u] 吸收 [%I64u] 蓝 成功",  pEquipEvolve->nNormalGuid, pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid );
			Log( theXmlString.GetString(eServerLog_HuShenFuXiLanChengGong),  pEquipEvolve->nNormalGuid, pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid );
		}
	}

    // 扣除符文布
    RemoveItem( pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType, 
        pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex, 
        NUMERIC_ONE, 
        pEquipEvolve->materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid );

	

   

    msg.AddCharItem( *pEquipItem );
    SendMessageToClient( &msg );

    _achieveManager.UpdateTriggerByValueType( EAT_EquipAmulet );
}

// 技能套装精炼
unsigned char GamePlayer::ProcessSkillSuitLevelUp( MsgSuitLevelUpReq* pReq, SCharItem* pCharEquip, ItemDefine::SItemArmour* pEquipArmour, ItemDefine::SItemCheckUp* pItemCheckUp )
{
    if ( pReq == NULL || pCharEquip == NULL || pEquipArmour == NULL || pItemCheckUp == NULL )
    { return MsgSuitLevelUpAck::ECD_Unkown; }

    if ( pItemCheckUp->stEffectType != ItemDefine::SItemCheckUp::ECD_SkillSuitLevel )
    { return MsgSuitLevelUpAck::ECD_ErrorCheckUpItem; }

    // 判断属性
    if ( !pEquipArmour->IsSkillSuitEquip() )
    { return MsgSuitLevelUpAck::ECD_NotSkillSuitEquip; }

    if ( pItemCheckUp->nValue1 == 0 || pItemCheckUp->nValue2 == 0 ) // 错误的鉴定材料
    { return MsgSuitLevelUpAck::ECD_ErrorCheckUpItem; }
    switch ( pEquipArmour->cEquipSexReq )
    {
    case Sex_Male:
        if ( pEquipArmour->sSuitID != pItemCheckUp->nValue1 )
        { return MsgSuitLevelUpAck::ECD_ErrorCheckUpItem; }
        break;

    case Sex_Female:
        if ( pEquipArmour->sSuitID != pItemCheckUp->nValue2 )
        { return MsgSuitLevelUpAck::ECD_ErrorCheckUpItem; }
        break;
    }

    // 判断等级
    if ( pCharEquip->GetSuitLevel() == SkillSuitLevelUp::GetMaxLevel() )
    { return MsgSuitLevelUpAck::ECD_AlreadMaxLevel; }

    if ( pEquipArmour->stEquipLevelReq > pItemCheckUp->stEquipLevel )
    { return MsgSuitLevelUpAck::ECD_ErrorItemLevel; }

    if ( pCharEquip->GetSuitLevel() >= pItemCheckUp->stEffectLevel )
    { return MsgSuitLevelUpAck::ECD_ErrorItemLevel; }

    // 判断钱够不够
    int nCostMoney = theSuitOperateConfig.GetSkillSuitLevelUpCostMoney( pEquipArmour->stEquipLevelReq );     // 消耗1金
    if ( GetJiaoZiMoney() < nCostMoney )
    { return MsgSuitLevelUpAck::ECD_NotEnoughMoney; }

    // 读取config表, 获得升级属性
    const SkillSuitLevelUp* pSkillEquipData = theSuitOperateConfig.GetSkillEquipData( pEquipArmour->stEquipLevelReq, pEquipArmour->GetCanEquipIndex(), pCharEquip->GetSuitLevel() + 1 );
    if ( pSkillEquipData == NULL )
    { return MsgSuitLevelUpAck::ECD_Unkown; }

    // 计算概率
    int nModulus = pSkillEquipData->GetModulus() + ( pItemCheckUp->stEffectLevel - ( pCharEquip->GetSuitLevel() + 1 ) ) * pSkillEquipData->GetExtendModulus();
    unsigned char uchResult = MsgSuitLevelUpAck::ECD_CheckUpFailed;
    if ( ( theRand.rand32() % RAND_NUM ) < nModulus )
    { 
        // 成功了, 设置新属性
        pCharEquip->SetSuitLevel( pCharEquip->GetSuitLevel() + 1 );

        if ( pSkillEquipData->GetAttributeType() == ECD_Attribute_Level )
        {// 随即一个属性给该装备
            pCharEquip->equipdata.suitRands[0] = theRunTimeData.EquipRandByLevel( pSkillEquipData->GetAttributeValue() );
        }
        else if ( pSkillEquipData->GetAttributeType() == ECD_Attribute_ID )
        {
            pCharEquip->equipdata.suitRands[0] = pSkillEquipData->GetAttributeValue();
        }

        uchResult = MsgSuitLevelUpAck::ECD_SuccessSkillSuit;
    }

    // 扣钱
    OperateJiaoZi( EOT_Sub, nCostMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_SkillSuitLevelUp );

	//LYH日志添加
	SCharItem * _item = GetBagItemByGuid(pReq->xItemInfo[0].nItemGuid);
	if (_item)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
		theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
		_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
	}

    // 扣除物品
    RemoveItem( pReq->xItemInfo[0].chItemBagType, pReq->xItemInfo[0].stItemIndex, NUMERIC_ONE, pReq->xItemInfo[0].nItemGuid );
	
	


    return uchResult;
}

// 五行套装提纯
unsigned char GamePlayer::ProcessElementSuitLevelUp( MsgSuitLevelUpReq* pReq, SCharItem* pCharEquip, ItemDefine::SItemArmour* pEquipArmour, ItemDefine::SItemCheckUp* pItemCheckUp )
{
    if ( pReq == NULL || pCharEquip == NULL || pEquipArmour == NULL || pItemCheckUp == NULL )
    { return MsgSuitLevelUpAck::ECD_Unkown; }

    // 判断属性
    if ( !pEquipArmour->IsElementSuitEquip() )
    { return MsgSuitLevelUpAck::ECD_NotElementuitEquip; }

    if ( pItemCheckUp->stEffectType != ItemDefine::SItemCheckUp::ECD_ElementsSuitLevel ) // 错误的鉴定材料
    { return MsgSuitLevelUpAck::ECD_ErrorCheckUpItem; }

    if ( pCharEquip->GetElements() == ItemElements_Init || ( pItemCheckUp->nValue1 != ItemElements_End && pCharEquip->GetElements() != pItemCheckUp->nValue1 ) )
    { return MsgSuitLevelUpAck::ECD_ErrorCheckUpItem; }     // 不是相同五行的不能提纯

    // 判断钱够不够
    int nCostMoney = theSuitOperateConfig.GetElementSuitLevelUpCostMoney( pEquipArmour->stEquipLevelReq );
    if ( GetJiaoZiMoney() < nCostMoney )
    { return MsgSuitLevelUpAck::ECD_NotEnoughMoney; }

    // 判断第2个材料, 是一个五行鉴定符
    SCharItem* pMaterialItem1 = NULL;
    switch( pReq->xItemInfo[1].chItemBagType )
    {
    case BT_MaterialBag:
        pMaterialItem1 = _MaterialItemBag.GetItemByIndex( pReq->xItemInfo[1].stItemIndex );
        break;
    default:
        pMaterialItem1 = _NormalItemBag.GetItemByIndex( pReq->xItemInfo[1].stItemIndex );
        break;
    }
    if ( pMaterialItem1 == NULL || pMaterialItem1->itembaseinfo.nOnlyInt != pReq->xItemInfo[1].nItemGuid )
    { return MsgSuitLevelUpAck::ECD_ErrorCheckUpItem; }

    ItemDefine::SItemCommon* pMaterialCommon1 = GettheItemDetail().GetItemByID( pMaterialItem1->itembaseinfo.ustItemID );
    if ( pMaterialCommon1 == NULL || pMaterialCommon1->ucItemType != ItemDefine::ITEMTYPE_CHECKUP )
    { return MsgSuitLevelUpAck::ECD_ErrorCheckUpItem; }

    ItemDefine::SItemCheckUp* pMaterialCheckUp1 = static_cast< ItemDefine::SItemCheckUp* >( pMaterialCommon1 );
    if ( pMaterialCheckUp1 == NULL || pMaterialCheckUp1->stCheckUpType != ItemDefine::SItemCheckUp::ECD_Elements || pMaterialCheckUp1->stEffectType != ItemDefine::SItemCheckUp::ECD_ElementsCheckUp )
    { return MsgSuitLevelUpAck::ECD_ErrorCheckUpItem; }

    if ( pMaterialCheckUp1->stEquipLevel < pEquipArmour->stEquipLevelReq )
    { return MsgSuitLevelUpAck::ECD_ErrorItemLevel; }

    // 判断第3个材料 是个从商店用功勋,名望之类 换来的材料
    SCharItem* pMaterialItem2 = NULL;
    switch( pReq->xItemInfo[2].chItemBagType )
    {
    case BT_MaterialBag:
        pMaterialItem2 = _MaterialItemBag.GetItemByIndex( pReq->xItemInfo[2].stItemIndex );
        break;
    default:
        pMaterialItem2 = _NormalItemBag.GetItemByIndex( pReq->xItemInfo[2].stItemIndex );
        break;
    }
    if ( pMaterialItem2 == NULL || pMaterialItem2->itembaseinfo.nOnlyInt != pReq->xItemInfo[2].nItemGuid )
    { return MsgSuitLevelUpAck::ECD_ErrorCheckUpItem; }

    ItemDefine::SItemCommon* pMaterialCommon2 = GettheItemDetail().GetItemByID( pMaterialItem2->itembaseinfo.ustItemID );
    if ( pMaterialCommon2 == NULL )
    { return MsgSuitLevelUpAck::ECD_ErrorCheckUpItem; }

    const ElementSuitLevelUp* pElementLevelUpData = theSuitOperateConfig.GetElementEquipData( pEquipArmour->stEquipLevelReq, pCharEquip->GetSuitLevel() );
    if ( pElementLevelUpData == NULL )
    { return MsgSuitLevelUpAck::ECD_Unkown; }

    if ( pElementLevelUpData->GetCostType() != pMaterialCommon2->costType )
    { return MsgSuitLevelUpAck::ECD_ErrorCheckUpItem; }

    if ( pElementLevelUpData->GetCostType() == ItemDefine::CT_Item )
    {
        if ( pElementLevelUpData->GetCostValue() != pMaterialCommon2->costItemID || pElementLevelUpData->GetCostCount() != pMaterialCommon2->dwCost )
        { return MsgSuitLevelUpAck::ECD_ErrorCheckUpItem; }
    }
    else
    {
        if ( pElementLevelUpData->GetCostValue() != pMaterialCommon2->dwCost )
        { return MsgSuitLevelUpAck::ECD_ErrorCheckUpItem; }
    }

    // 都满足条件, 执行五行元素提纯
    unsigned char uchLevel = theSuitOperateConfig.GetElementEquipLevelByRand( pEquipArmour->stEquipLevelReq, theRand.rand32() );  // 随即一个属性
    pCharEquip->SetSuitLevel( uchLevel );

    // 扣钱
    OperateJiaoZi( EOT_Sub, nCostMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_ElementSuitLevelUp );

    ItemDefine::SItemCommon* pItemCommon[] = { pItemCheckUp, pMaterialCommon1, pMaterialCommon2, };

    // 扣除物品
	SCharItem * _item = NULL;
    for ( int i = 0; i < MsgSuitLevelUpReq::ECD_ItemCount; ++i )
    {  
        //LYH日志添加
		_item = GetBagItemByGuid(pReq->xItemInfo[i].nItemGuid);
		if (_item)
		{
			ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
			if(_pitem)
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
			_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
		}

		RemoveItem( pReq->xItemInfo[i].chItemBagType, pReq->xItemInfo[i].stItemIndex, NUMERIC_ONE, pReq->xItemInfo[i].nItemGuid );
	
		
        //Log( "五行套装提纯成功,删除装备道具[%s] GUID[%I64u] [%d]个", pItemCommon[i]->GetItemName(), pReq->xItemInfo[i].nItemGuid, nCount );
    }

    return MsgSuitLevelUpAck::ECD_SuccessElementSuit;
}

void GamePlayer::OnMsgSuitChangeReq( Msg* pMsg )
{
    MsgSuitChangeReq* pReq = static_cast< MsgSuitChangeReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    MsgSuitChangeAck xAck;
    // 判断装备
    SCharItem* pCharEquip = _NormalItemBag.GetItemByIndex( pReq->stEquipIndex );
    if ( pCharEquip == NULL || pCharEquip->itembaseinfo.nOnlyInt != pReq->nEquipGuid )
    {
        xAck.uchResult = MsgSuitChangeAck::ECD_Unkown;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    ItemDefine::SItemCommon* pEquipCommon = GettheItemDetail().GetItemByID( pCharEquip->itembaseinfo.ustItemID );
    if ( pEquipCommon == NULL || pEquipCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    {
        xAck.uchResult = MsgSuitChangeAck::ECD_NotSuitEquip;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    ItemDefine::SItemArmour* pEquipArmour = static_cast< ItemDefine::SItemArmour* >( pEquipCommon );
    if ( pEquipArmour == NULL )
    { return; }

    if ( !pEquipArmour->IsSuitEquip() )
    {
        xAck.uchResult = MsgSuitChangeAck::ECD_NotSuitEquip;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    // 判断两个物品 , 第一个是转化道具, 第2个是功勋道具
    SCharItem* pCharChangeItem = NULL;
    ItemBag* pChangeItemBag = NULL;
    switch ( pReq->xItemInfo[0].chItemBagType )
    {
    case BT_MaterialBag:
        pCharChangeItem = _MaterialItemBag.GetItemByIndex( pReq->xItemInfo[0].stItemIndex );
        pChangeItemBag = &_MaterialItemBag;
        break;
    default:
        pCharChangeItem = _NormalItemBag.GetItemByIndex( pReq->xItemInfo[0].stItemIndex );
        pChangeItemBag = &_NormalItemBag;
    }

    if ( pCharChangeItem == NULL || pChangeItemBag == NULL || pCharChangeItem->itembaseinfo.nOnlyInt != pReq->xItemInfo[0].nItemGuid )
    {
        xAck.uchResult = MsgSuitChangeAck::ECD_Unkown;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    ItemDefine::SItemCommon* pChangeItemCommon = GettheItemDetail().GetItemByID( pCharChangeItem->itembaseinfo.ustItemID );
    if ( pChangeItemCommon == NULL || pChangeItemCommon->ucItemType != ItemDefine::ITEMTYPE_CHECKUP )
    {
        xAck.uchResult = MsgSuitChangeAck::ECD_ErrorCheckUpItem;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    ItemDefine::SItemCheckUp* pChangeItemCheckUp = static_cast< ItemDefine::SItemCheckUp* >( pChangeItemCommon );
    if ( pChangeItemCheckUp == NULL || pChangeItemCheckUp->stCheckUpType != ItemDefine::SItemCheckUp::ECD_Suit )
    {
        xAck.uchResult = MsgSuitChangeAck::ECD_ErrorCheckUpItem;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    // 第2个道具
    SCharItem* pCharMaterialItem = NULL;
    ItemBag* pMaterialItemBag = NULL;
    switch ( pReq->xItemInfo[1].chItemBagType )
    {
    case BT_MaterialBag:
        pCharMaterialItem = _MaterialItemBag.GetItemByIndex( pReq->xItemInfo[1].stItemIndex );
        pMaterialItemBag  = &_MaterialItemBag;
        break;
    default:
        pCharMaterialItem = _NormalItemBag.GetItemByIndex( pReq->xItemInfo[1].stItemIndex );
        pMaterialItemBag  = &_NormalItemBag;
    }

    if ( pCharMaterialItem == NULL || pMaterialItemBag == NULL || pCharMaterialItem->itembaseinfo.nOnlyInt != pReq->xItemInfo[1].nItemGuid )
    {
        xAck.uchResult = MsgSuitChangeAck::ECD_Unkown;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    ItemDefine::SItemCommon* pMaterialItemCommon = GettheItemDetail().GetItemByID( pCharMaterialItem->itembaseinfo.ustItemID );
    if ( pMaterialItemCommon == NULL )
    {
        xAck.uchResult = MsgSuitChangeAck::ECD_ErrorMaterialItem;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    switch ( pReq->chOperate )
    {
    case MsgSuitChangeReq::ECD_SkillSuitChange:
        {
            xAck.uchResult = ProcessSkillSuitChange( pReq, pCharEquip, pEquipArmour, pChangeItemCheckUp, pMaterialItemCommon );
            xAck.nLeftMoney = GetMoney();
            xAck.nValue = pCharEquip->itembaseinfo.ustItemID;
            GettheServer().SendMsgToSingle( &xAck, this );
        }
        break;
    case MsgSuitChangeReq::ECD_ElementSuitChange:
        {
            xAck.uchResult = ProcessElementSuitChange( pReq, pCharEquip, pEquipArmour, pChangeItemCheckUp, pMaterialItemCommon );
            xAck.nLeftMoney = GetMoney();
            xAck.nValue = pCharEquip->itembaseinfo.value1;
            GettheServer().SendMsgToSingle( &xAck, this );
        }
        break;
    }
}

unsigned char GamePlayer::ProcessSkillSuitChange( MsgSuitChangeReq* pReq, SCharItem* pCharEquip, ItemDefine::SItemArmour* pEquipArmour, 
                                                 ItemDefine::SItemCheckUp* pItemCheckUp, ItemDefine::SItemCommon* pItemMaterial )
{
    if ( pReq == NULL || pCharEquip == NULL || pItemCheckUp == NULL || pItemMaterial == NULL )
    { return MsgSuitChangeAck::ECD_Unkown; }

    if ( !pEquipArmour->IsSkillSuitEquip() )
    { return MsgSuitChangeAck::ECD_NotSkillSuitEquip; }

    if ( pCharEquip->GetSuitLevel() < theSuitOperateConfig.GetMinSkillSuitChangeLevel() )
    { return MsgSuitChangeAck::ECD_LessSuitLevel; }

    if ( pItemCheckUp->stEquipLevel < pEquipArmour->stEquipLevelReq )
    { return MsgSuitChangeAck::ECD_LessEquipLevel; }

    if ( pItemCheckUp->stEffectType != ItemDefine::SItemCheckUp::ECD_SkillSuitChange )
    { return MsgSuitChangeAck::ECD_ErrorCheckUpItem; }
    if ( theSuitOperateConfig.IsCheckSkillSuitChangeLevel() )   // 如果开启了精炼等级限制
    {
        if ( pItemCheckUp->stEffectLevel < pCharEquip->GetSuitLevel() )
        { return MsgSuitChangeAck::ECD_LessItemLevel; }
    }

    const ChangeCostInfo* pCostInfo = theSuitOperateConfig.GetSkillSuitChangeCostInfo( pEquipArmour->stEquipLevelReq, pCharEquip->GetSuitLevel() );
    if ( pCostInfo == NULL )
    { return MsgSuitChangeAck::ECD_Unkown; }

    if ( pCostInfo->GetCostType() != pItemMaterial->costType )
    { return MsgSuitChangeAck::ECD_ErrorMaterialItem; }

    if ( pCostInfo->GetCostType() == ItemDefine::CT_Item )
    {   // 如果是用物品兑换来的东西, 判断数量
        if ( pCostInfo->GetCostValue() != pItemMaterial->costItemID || pCostInfo->GetCostCount() != pItemMaterial->dwCost )
        { return MsgSuitChangeAck::ECD_ErrorMaterialItem; }
    }
    else
    {
        if ( pCostInfo->GetCostValue() != pItemMaterial->dwCost )
        { return MsgSuitChangeAck::ECD_ErrorMaterialItem; }
    }

    // 判断钱够不够
    int nCostMoney = theSuitOperateConfig.GetSkillSuitChangeCostMoney( pEquipArmour->stEquipLevelReq );     // 消耗1金
    if ( GetJiaoZiMoney() < nCostMoney )
    { return MsgSuitChangeAck::ECD_NotEnoughMoney; }

    // 开始转换
    unsigned char uchSex = pEquipArmour->cEquipSexReq;
    if ( uchSex == -1 )
    { uchSex = 0; }
    unsigned short ustOldItemID = pCharEquip->itembaseinfo.ustItemID;
    pCharEquip->itembaseinfo.ustItemID = theSuitOperateConfig.GetEquipIDByRand( pEquipArmour->stEquipLevelReq, pEquipArmour->GetCanEquipIndex(), theRand.rand32(), uchSex, ustOldItemID );
    if ( ustOldItemID == pCharEquip->itembaseinfo.ustItemID )
    { return MsgSuitChangeAck::ECD_ChangeFailed; }

    // 扣钱
    OperateJiaoZi( EOT_Sub, nCostMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_SkillSuitChange);

	SCharItem * _item = NULL;
    // 扣除物品
    for ( int i = 0; i < MsgSuitChangeReq::ECD_ItemCount; ++i )
    {
		//LYH日志添加
		_item = GetBagItemByGuid(pReq->xItemInfo[i].nItemGuid);
		if (_item)
		{
			ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
			if(_pitem)
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
			_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
		}
        RemoveItem( pReq->xItemInfo[i].chItemBagType, pReq->xItemInfo[i].stItemIndex, NUMERIC_ONE, pReq->xItemInfo[i].nItemGuid );	
    }

    return MsgSuitChangeAck::ECD_SuccessChagneSkillSuit;
}

unsigned char GamePlayer::ProcessElementSuitChange( MsgSuitChangeReq* pReq, SCharItem* pCharEquip, ItemDefine::SItemArmour* pEquipArmour, 
                                                   ItemDefine::SItemCheckUp* pItemCheckUp, ItemDefine::SItemCommon* pItemMaterial )
{
    if ( pReq == NULL || pCharEquip == NULL || pItemCheckUp == NULL || pItemMaterial == NULL )
    { return MsgSuitChangeAck::ECD_Unkown; }

    if ( !pEquipArmour->IsElementSuitEquip() )
    { return MsgSuitChangeAck::ECD_NotSkillSuitEquip; }

    if ( pItemCheckUp->stEffectType != ItemDefine::SItemCheckUp::ECD_ElementsSuitChange )
    { return MsgSuitChangeAck::ECD_ErrorCheckUpItem; }

    if ( pCharEquip->GetSuitLevel() < theSuitOperateConfig.GetMinElementSuitChangeLevel() )
    { return MsgSuitChangeAck::ECD_LessSuitLevel; }

    if ( pItemMaterial->ucItemType != ItemDefine::ITEMTYPE_CHECKUP )
    { return MsgSuitChangeAck::ECD_ErrorCheckUpItem; }

    ItemDefine::SItemCheckUp* pItemCheckUp2 = static_cast< ItemDefine::SItemCheckUp* >( pItemMaterial );
    if ( pItemCheckUp2 == NULL || pItemCheckUp2->stCheckUpType != ItemDefine::SItemCheckUp::ECD_Elements || pItemCheckUp2->stEffectType != ItemDefine::SItemCheckUp::ECD_ElementsCheckUp )
    { return MsgSuitChangeAck::ECD_ErrorCheckUpItem; }

    if ( pItemCheckUp2->stEquipLevel < pEquipArmour->stEquipLevelReq )
    { return MsgSuitChangeAck::ECD_LessItemLevel; }

    unsigned int nCostMoney = theSuitOperateConfig.GetElementSuitChangeCostMoney( pEquipArmour->stEquipLevelReq );
    if ( GetJiaoZiMoney() < nCostMoney )
    { return MsgSuitChangeAck::ECD_NotEnoughMoney; }

    // 随即转换属性 ( 是否要开启定向转化 )
    unsigned char uchOldElement = pCharEquip->GetElements();
    std::vector< unsigned char > vecElement;
    for ( int i = ItemElements_Metal; i <= ItemElements_Earth; ++i )
    {
        if ( i != uchOldElement )
        {
            vecElement.push_back( i );
        }
    }
    if ( vecElement.empty() )
    { return MsgSuitChangeAck::ECD_Unkown; }

    int nIndex = theRand.rand32() % vecElement.size();
    pCharEquip->SetElements( vecElement.at( nIndex ) );

    // 扣钱
    OperateJiaoZi( EOT_Sub, nCostMoney, true , __FUNCTION__, __LINE__,ePlayerMoneySourceType_ElementSuitChange );

    // 扣除物品
	SCharItem * _item = NULL;
    for ( int i = 0; i < MsgSuitChangeReq::ECD_ItemCount; ++i )
    {
		//LYH日志添加
		_item = GetBagItemByGuid(pReq->xItemInfo[i].nItemGuid);
		if (_item)
		{
			ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
			if(_pitem)
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
			_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
		}

        RemoveItem( pReq->xItemInfo[i].chItemBagType, pReq->xItemInfo[i].stItemIndex, NUMERIC_ONE, pReq->xItemInfo[i].nItemGuid );
		
    }
    return MsgSuitChangeAck::ECD_SuccessChagneElementSuit;
}

void GamePlayer::OnMsgSuitElementMoveReq( Msg* pMsg )
{
    MsgSuitElementMoveReq* pReq = static_cast< MsgSuitElementMoveReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    MsgSuitElementMoveAck xAck;
    xAck.stSrcArmourIndex  = pReq->stSrcArmourIndex;
    xAck.n64SrcArmourGuid  = pReq->n64SrcArmourGuid;
    xAck.stDestArmourIndex = pReq->stDestArmourIndex;
    xAck.n64DestArmourGuid = pReq->n64DestArmourGuid;

    // 判断源装备
    SCharItem* pSrcEquip = _NormalItemBag.GetItemByIndex( pReq->stSrcArmourIndex );
    if ( pSrcEquip == NULL || pSrcEquip->GetItemGuid() != pReq->n64SrcArmourGuid )
    { 
        xAck.uchResult = MsgSuitElementMoveAck::ECD_EquipNotExist;
        SendMessageToClient( &xAck );
        return; 
    }

    if ( pSrcEquip->GetElements() == ItemElements_Init )
    {
        xAck.uchResult = MsgSuitElementMoveAck::ECD_NotHaveElement;
        SendMessageToClient( &xAck );
        return;
    }

    ItemDefine::SItemCommon* pSrcCommon = GettheItemDetail().GetItemByID( pSrcEquip->GetItemID() );
    if ( pSrcCommon == NULL || pSrcCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    { return; }
    ItemDefine::SItemArmour* pSrcArmour = static_cast< ItemDefine::SItemArmour* >( pSrcCommon );
    if ( !pSrcArmour->IsSuitEquip() )
    {
        xAck.uchResult = MsgSuitElementMoveAck::ECD_NotElement;
        SendMessageToClient( &xAck );
        return;
    }

    // 判断目标装备
    SCharItem* pDestEquip = _NormalItemBag.GetItemByIndex( pReq->stDestArmourIndex );
    if ( pDestEquip == NULL || pDestEquip->GetItemGuid() != pReq->n64DestArmourGuid )
    {
        xAck.uchResult = MsgSuitElementMoveAck::ECD_EquipNotExist;
        SendMessageToClient( &xAck );
        return;
    }

    ItemDefine::SItemCommon* pDestCommon = GettheItemDetail().GetItemByID( pDestEquip->GetItemID() );
    if ( pDestCommon == NULL || pDestCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    { return; }
    ItemDefine::SItemArmour* pDestArmour = static_cast< ItemDefine::SItemArmour* >( pDestCommon );
    if ( !pDestArmour->IsSuitEquip() )
    {
        xAck.uchResult = MsgSuitElementMoveAck::ECD_NotElement;
        SendMessageToClient( &xAck );
        return;
    }

    //  判断两个装备的部位
    if ( pSrcArmour->GetCanEquipIndex() != pDestArmour->GetCanEquipIndex() )
    {
        xAck.uchResult = MsgSuitElementMoveAck::ECD_CanEquipIndexError;
        SendMessageToClient( &xAck );
        return;
    }

    // 判断两个装备的级别限制
    int nSrcEquipLevel  = pSrcArmour->stEquipLevelReq / 10;
    int nDestEquipLevel = pDestArmour->stEquipLevelReq / 10;
    if ( nDestEquipLevel - nSrcEquipLevel > 1 )
    {
        xAck.uchResult = MsgSuitElementMoveAck::ECD_EquipLevelError;
        SendMessageToClient( &xAck );
        return;
    }

    // 判断材料
    SCharItem* pMaterialItem = NULL;
    switch ( pReq->chCheckUpBagType )
    {
    case BT_MaterialBag:
        pMaterialItem = _MaterialItemBag.GetItemByIndex( pReq->stCheckUpIndex );
        break;
    default:
        pMaterialItem = _NormalItemBag.GetItemByIndex( pReq->stCheckUpIndex );
        break;
    }
    if ( pMaterialItem == NULL || pMaterialItem->GetItemGuid() != pReq->n64CheckUpGuid )
    {
        xAck.uchResult = MsgSuitElementMoveAck::ECD_NotElement;
        SendMessageToClient( &xAck );
        return;
    }

    ItemDefine::SItemCommon* pMaterialCommon = GettheItemDetail().GetItemByID( pMaterialItem->GetItemID() );
    if ( pMaterialCommon == NULL || pMaterialCommon->ucItemType != ItemDefine::ITEMTYPE_CHECKUP )
    { return; }

    ItemDefine::SItemCheckUp* pCheckUpCommon = static_cast< ItemDefine::SItemCheckUp* >( pMaterialCommon );
    if ( pCheckUpCommon == NULL || pCheckUpCommon->stCheckUpType != ItemDefine::SItemCheckUp::ECD_Elements || pCheckUpCommon->stEffectType != ItemDefine::SItemCheckUp::ECD_ElementsMove )
    {
        xAck.uchResult = MsgSuitElementMoveAck::ECD_ErrorElementItem;
        SendMessageToClient( &xAck );
        return;
    }

    int nCheckUpCommon = pCheckUpCommon->stEquipLevel / 10;
    if ( nCheckUpCommon < nSrcEquipLevel )
    {
        xAck.uchResult = MsgSuitElementMoveAck::ECD_ErrorElementItemLevel;
        SendMessageToClient( &xAck );
        return;
    }

    const ElementMove& xElementMove = theSuitOperateConfig.GetElementMove();
    if ( GetJiaoZiMoney() < xElementMove.GetCostMoney() )
    {
        xAck.uchResult = MsgSuitElementMoveAck::ECD_NotEnoughMoney;
        SendMessageToClient( &xAck );
        return;
    }

    float fModulus = xElementMove.GetBaseModulus();

    // 判断加成材料
    if ( pReq->stModulusIndex != -1 )
    {
        SCharItem* pModulusItem = NULL;

        switch ( pReq->chModulusBagType )
        {
        case BT_MaterialBag:
            pModulusItem = _MaterialItemBag.GetItemByIndex( pReq->stModulusIndex );
            break;
        default:
            pModulusItem = _NormalItemBag.GetItemByIndex( pReq->stModulusIndex );
            break;
        }

        if ( pModulusItem == NULL || pModulusItem->GetItemGuid() != pReq->n64ModulusGuid || pModulusItem->GetItemID() != xElementMove.GetMaterialID() )
        {
            xAck.uchResult = MsgSuitElementMoveAck::ECD_ErrorModulusItem;
            SendMessageToClient( &xAck );
            return;
        }

        if ( pModulusItem->GetItemCount() < pReq->ustModulusCount )
        {
            xAck.uchResult = MsgSuitElementMoveAck::ECD_ErrorModulusItemCount;
            SendMessageToClient( &xAck );
            return;
        }

        if ( pReq->ustModulusCount > xElementMove.GetMaxCount() )
        { pReq->ustModulusCount = xElementMove.GetMaxCount(); }

        fModulus = xElementMove.GetModulus( pReq->ustModulusCount );

		//LYH日志添加
		SCharItem *	_item = GetBagItemByGuid(pReq->n64ModulusGuid);
		if (_item)
		{
			ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
			if(_pitem)
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),pReq->ustModulusCount,_item->GetItemGuid(),
			_item->GetItemCount()-pReq->ustModulusCount >= 0 ? _item->GetItemCount()-pReq->ustModulusCount : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
		}

        // 扣除加成的材料
        RemoveItem( pReq->chModulusBagType, pReq->stModulusIndex, pReq->ustModulusCount, pReq->n64ModulusGuid );

	
    }

    uint16 nRand = theRand.rand16() % RAND_NUM;
    if ( nRand <= ( fModulus * RAND_NUM ) )
    {
        pDestEquip->SetElements( pSrcEquip->GetElements() );
        pDestEquip->SetSuitLevel( pSrcEquip->GetSuitLevel() );
    }
    else
    {
        xAck.uchResult = MsgSuitElementMoveAck::ECD_Failed;
    }

    // 清除掉源装备的五行属性
    pSrcEquip->SetElements( ItemElements_Init );
    pSrcEquip->SetSuitLevel( 0 );

	//LYH日志添加
	SCharItem *	_item = GetBagItemByGuid(pReq->n64ModulusGuid);
	if (_item)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
		theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),NUMERIC_ONE,_item->GetItemGuid(),
		_item->GetItemCount()-NUMERIC_ONE >= 0 ? _item->GetItemCount()-NUMERIC_ONE : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
	}


    // 扣除五行材料
    RemoveItem( pReq->chCheckUpBagType, pReq->stCheckUpIndex, NUMERIC_ONE, pReq->n64CheckUpGuid );
	
    // 扣钱
    OperateJiaoZi( EOT_Sub, xElementMove.GetCostMoney(), true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_SuitElementMove);
    xAck.dwCurrentMoney = GetMoney();

    SendMessageToClient( &xAck );
}

void GamePlayer::OnMsgItemReclaim( Msg* pMsg )
{
    MsgItemReclaim* pMsgReclaim = (MsgItemReclaim*)pMsg;
    if (pMsgReclaim == NULL)
    { return; }

    MsgItemReclaimAck msgAck;
    msgAck.nResult      = MsgItemReclaimAck::error_reclaim_fail;
    msgAck.nItemBagType = pMsgReclaim->nItemBagType  ;
    msgAck.nPackIndex   = pMsgReclaim->nPackIndex    ;

    SCharItem* pCharItem = NULL;

    switch ( pMsgReclaim->nItemBagType )
    {
    case BT_NormalItemBag:
        { pCharItem = _NormalItemBag.GetItemByIndex( pMsgReclaim->nPackIndex ); }
        break;
    case BT_MaterialBag:
        {  pCharItem = _MaterialItemBag.GetItemByIndex( pMsgReclaim->nPackIndex ); }
        break;
    default:
        return;
        break;
    }

    if ( pCharItem == NULL || pCharItem->GetItemGuid() != pMsgReclaim->nGuid )
    {
        msgAck.nResult  = MsgItemReclaimAck::error_notfind_item;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return;
    }

     // 加了锁不能卖
    if ( pCharItem->IsLock() )
    { 
        msgAck.nResult  = MsgItemReclaimAck::error_item_is_lock;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    // 回收装备必须是金色以上的
    if( pCharItem->equipdata.quality < ItemDefine::EQL_Golden)
    {
        msgAck.nResult = MsgItemReclaimAck::error_item_not_reclaim;
        GettheServer().SendMsgToSingle(&msgAck,this);
        return;
    }

    if ( pCharItem->itembaseinfo.ustItemCount < pMsgReclaim->nCount )
    {   
        msgAck.nResult  = MsgItemReclaimAck::error_notfind_item;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return;
    }

    ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
    if( pItem == NULL )
    { return; }

    if (pItem->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItem->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    {
        msgAck.nResult  = MsgItemReclaimAck::error_notfind_item;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return;
    }

    int nCostReturn = theNpcShop.GetPlayerItemReclaimCost(pCharItem, pMsgReclaim->nCount );
    if (nCostReturn <= 0)
    { 
        msgAck.nResult  = MsgItemReclaimAck::error_item_not_reclaim;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return;
    }

	//LYH日志添加
	SCharItem *	_item = GetBagItemByGuid(pMsgReclaim->nGuid);
	if (_item)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
		theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),pMsgReclaim->nCount,_item->GetItemGuid(),
		                                 _item->GetItemCount()-pMsgReclaim->nCount >= 0 ? _item->GetItemCount()-pMsgReclaim->nCount : 0,eItemLogInfo_ItemConsume_UpItem,GetCharName(),_pitem->GetItemName());
	}


    // 扣去物品
    if( !RemoveItem(pMsgReclaim->nItemBagType,pMsgReclaim->nPackIndex, pMsgReclaim->nCount,pMsgReclaim->nGuid) )
    {
        msgAck.nResult = MsgItemReclaimAck::error_reclaim_fail;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return;
    }   


    // 返还花费
    switch ( pItem->costType )
    {
    case ItemDefine::CT_Reputation:
        { OperateReputation( EOT_Add, nCostReturn, __FUNCTION__, __LINE__,ePlayerMoneySourceType_ItemReclaim ); }
        break;
    case ItemDefine::CT_Exploit:
        { OperateExploit( EOT_Add, nCostReturn, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_ItemReclaim); }
        break;
    case ItemDefine::CT_Honour:
        { OperateHonour( EOT_Add, nCostReturn, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_ItemReclaim); }
        break;
    case ItemDefine::CT_GuildOffer:
        { OperateGuildOffer( GuildDefine::OperateAdd, nCostReturn ); }
        break;
    case ItemDefine::CT_Item:
        { OperateMoney( EOT_Add, nCostReturn, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_ItemReclaim); }
        break;
    default:
        return;
        break;
    }

    msgAck.nResult = MsgItemReclaimAck::error_sucess;
    msgAck.nCostType = pItem->costType  ;
    msgAck.nCostReturn = nCostReturn    ;
    GettheServer().SendMsgToSingle( &msgAck, this );
}

