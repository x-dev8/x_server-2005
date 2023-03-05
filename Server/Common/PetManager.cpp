#include "PetManager.h"
#include "GamePlayer.h"
#include "ExpStage.h"
#include "Configure.h"
#include "ShareData.h"
#include "GameWorld.h"
#include "PetSettingConfig.h"
#include "MonsterNurturePet.h"
#include "MonsterCreater.h"
#include "ProcessCharInfo.h"
#include "XmlStringLanguage.h"
#include "PetDefineConfig.h"
PetManager::PetManager() : _pPetItems( NULL ), _pGamePlayer( NULL), _nPetCount( 0 ), _activeIndex( -1 ), _activePetCharId( -1 ),
                                    _accumulateActionTime( 0 )
{
}

bool PetManager::CreateFromData( GamePlayer* pOwner, SPetItem* pPetItems, int nPetCount )
{
    if ( !pPetItems || nPetCount < 0 || !pOwner)
        return false;

    _pPetItems      = pPetItems;
    _nPetCount      = nPetCount;
    _pGamePlayer    = pOwner;

    for ( int i=0; i<_nPetCount; ++i )
    {//这里将所有宠物设置为未出战状态
        if ( _pPetItems[i].baseInfo.guid != InvalidLogicNumber && _pPetItems[i].baseInfo.petId != InvalidLogicNumber )
        { _pPetItems[i].baseInfo.isActive = AT_NotActive; }
    }

    return true;
} 

bool PetManager::InitPetAttribute ( SPetItem& pet )
{
    ItemDefine::SPetMonster* pPetMonster = GettheItemDetail().GetPetById( pet.baseInfo.petId );
    if ( pPetMonster == NULL ) 
    { return false; }

    // 一级属性总合=24+等级*4 
    // 各项一级属性最小值=4+等级*1 
    // 分配方式:先计算出总属性和然后随机分配给所有属性.	
    pet.baseInfo.ResetAttibute();
    
    int baseAttrCount = thePetSettingConfig.GetBaseAttrCount() + pet.baseInfo.level * 4 ;
    int baseAttrValue = thePetSettingConfig.GetBaseAttrValue() + pet.baseInfo.level * 1 ;

    baseAttrCount -= baseAttrValue * EBaseAttr_MaxSize;
    for (int i=0;i<EBaseAttr_MaxSize;++i)
    {
        pet.baseInfo.baseAttribute[i] = baseAttrValue;

        if ( baseAttrCount > 0 )
        {
            int randValue = GetRand( 0, baseAttrCount / EBaseAttr_MaxSize );
            pet.baseInfo.baseAttribute[i] += randValue;
            baseAttrCount -= randValue;
        }
    }

    if ( baseAttrCount > 0 )
    { pet.baseInfo.baseAttribute[GetRand( 0, EBaseAttr_MaxSize - 1 )] += baseAttrCount; }

    // 宠物单项资质=基础资质*(资质随机倍率*(1±浮动值))
    int  aptitudeLevel = pet.baseInfo.aptitudeLevel;
    for (int i=0;i<EBaseAttr_MaxSize;++i)
    { 
        float fRandAptitude  = thePetSettingConfig.GetAptitudeFloat( aptitudeLevel );
        pet.baseInfo.aptitudeAttribute[i] += pPetMonster->aptitudeAttr[i] * fRandAptitude; 
    }

    //ApplyBaseAttrToFight( pet );
    return true;
}

//bool PetManager::UpdatePetAttribute ( SPetItem& pet )
//{
//    //ApplyBaseAttrToFight( pet );
//    return true;
//}

bool PetManager::InitPetSkill ( SPetItem& pet )
{
    ItemDefine::SPetMonster* pPetMonster = GettheItemDetail().GetPetById( pet.baseInfo.petId );
    if ( pPetMonster == NULL ) 
    { return false; }

    pet.skillInfo.Reset();

    ItemDefine::SItemSkill* pTalentSkill = _pGamePlayer->GetPetTalentSkillByType( pet.baseInfo.petType );
    if( pTalentSkill != NULL )
    { 
        pet.skillInfo.AddSkill( pPetMonster->talentSkillId, pTalentSkill->ustLevel );
    }

    std::vector< uint16 > vecNewSkill;
    RealizePetSkill ( pet, vecNewSkill, true );
    CalcBattleEffectiveness( pet );
    return true;
}

bool PetManager::RealizePetSkill ( SPetItem& pet, std::vector<uint16>& vecNewSkill, bool bInit )
{
    ItemDefine::SPetMonster* pPetMonster = GettheItemDetail().GetPetById( pet.baseInfo.petId );
    if ( pPetMonster == NULL ) 
    { return false; }

    // 找到主动技能 被动技能数目
    int manualSkillNum = 0, autoSkillNum = 0;
    for (int i=0; i<SPetItem::PetDefine_MaxSkillCount; ++i )
    {
        if (pet.skillInfo.skills[i].ustSkillID == InvalidLogicNumber)
        { continue; }
        
        if (pet.skillInfo.skills[i].ustSkillID == pPetMonster->talentSkillId)
        { continue; }

        ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( pet.skillInfo.skills[i].ustSkillID, pet.skillInfo.skills[i].stSkillLevel );
        if (pSkill == NULL)
        { continue; }

        if ( pSkill->sSkillCategory == ItemDefine::SCT_PetMasterManualControl )
        { ++manualSkillNum; }
        else
        { ++autoSkillNum; }
    }

	//判断技能数量 如果技能数量大于配置的数量
	//int SkillSum = thePetDefineConfig.GetLevelSkillSum(pet.baseInfo.level);//根据等级获取技能数量型
	//bool IsCanAddSkill = (SkillSum<=(manualSkillNum + autoSkillNum))?false:true;

    // 开始领悟新的技能
    for (int i=0; i< ItemDefine::SPetMonster::EPet_LvRealizeCount; ++i)
    {
        if ( pPetMonster->lvRealizeSkill[i] <= pet.baseInfo.lastRealizeSkillLevel )
        { continue; }

        if ( pPetMonster->lvRealizeSkill[i] > pet.baseInfo.level )
        { continue; }

        for (int index = 0; index < ItemDefine::SPetMonster::EPet_RandSkillCount; ++index )
        {
            int nRandom = theRand.rand16() % RAND_NUM;

            //主动技能
            if ( nRandom < pPetMonster->manualSkillRate[index] )
            {
                if ( manualSkillNum >= ItemDefine::SPetMonster::EPet_ManualSkillCount )
                { continue; }

                ItemDefine::SItemSkill* pManualSkill = GettheItemDetail().GetSkillByID( pPetMonster->manualSkillId[index], 1 );
                if (pManualSkill == NULL)
                { continue; }

                // 检查是否替换已有技能
                int repalceIndex = -1; 
                for (int findIndex=0; findIndex<SPetItem::PetDefine_MaxSkillCount; ++findIndex )
                {//查找替换技能
                    if (pet.skillInfo.skills[findIndex].ustSkillID == InvalidLogicNumber)
                    { continue; }

                    if (pet.skillInfo.skills[findIndex].ustSkillID == pPetMonster->talentSkillId)
                    { continue; }

                    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( pet.skillInfo.skills[findIndex].ustSkillID, 1 );
                    if (pSkill == NULL)
                    { continue; }

                    if ( pSkill->sSkillCategory != ItemDefine::SCT_PetMasterManualControl )
                    { continue; }

                    if (pPetMonster->manualSkillId[index] == pet.skillInfo.skills[findIndex].ustSkillID)
                    { 
                        repalceIndex = findIndex; 
                        break;
                    }

                    if ( pSkill->petSkillCategory == EPetSkillCategory_ManualAttack  && pManualSkill->petSkillCategory == EPetSkillCategory_ManualAttack )
                    { repalceIndex = findIndex; }
                    else if ( pManualSkill->groupId == pSkill->groupId && pManualSkill->groupLevel >= pSkill->groupLevel )
                    { repalceIndex = findIndex; }
                }

                if ( repalceIndex >= 0 )  // 找到了替换技能
                { pet.skillInfo.ReplaceSkill(pPetMonster->manualSkillId[index], 1, repalceIndex); }
                else
                { 
                    pet.skillInfo.AddSkill( pPetMonster->manualSkillId[i], 1 ); 
                    if ( !bInit )
                    { vecNewSkill.push_back( pPetMonster->manualSkillId[i] ); }
                    
                }
            }

            //被动技能
            if ( nRandom < pPetMonster->autoSkillRate[index] )
            {
                if ( autoSkillNum >= ItemDefine::SPetMonster::EPet_AutoSkillCount )
                { continue; }

                ItemDefine::SItemSkill* pAutoSkill = GettheItemDetail().GetSkillByID( pPetMonster->autoSkillId[index], 1 );
                if (pAutoSkill == NULL)
                { continue; }

                int repalceIndex = -1, lastIndex = -1; 
                for (int findIndex=0; findIndex<SPetItem::PetDefine_MaxSkillCount; ++findIndex )
                {
                    if (pet.skillInfo.skills[findIndex].ustSkillID == InvalidLogicNumber)
                    { continue; }

                    if (pet.skillInfo.skills[findIndex].ustSkillID == pPetMonster->talentSkillId)
                    { continue; }

                    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( pet.skillInfo.skills[findIndex].ustSkillID, 1 );
                    if (pSkill == NULL)
                    { continue; }

                    if ( pSkill->sSkillCategory == ItemDefine::SCT_PetMasterManualControl )
                    { continue; }

                    if (pPetMonster->autoSkillId[index] == pet.skillInfo.skills[findIndex].ustSkillID)
                    { 
                        repalceIndex = findIndex; 
                        break;
                    }

                    if ( pSkill->petSkillCategory == EPetSkillCategory_AutoAttack && pAutoSkill->petSkillCategory == EPetSkillCategory_AutoAttack )
                    { repalceIndex = findIndex; }
                    else if ( pAutoSkill->groupId == pSkill->groupId && pAutoSkill->groupLevel >=  pSkill->groupLevel )
                    { repalceIndex = findIndex; }
                    else
                    { lastIndex = findIndex; }
                }

                if (repalceIndex >= 0)
                { pet.skillInfo.ReplaceSkill(pPetMonster->autoSkillId[index], 1, repalceIndex); }
                else
                { 
                    pet.skillInfo.AddSkill( pPetMonster->autoSkillId[i], 1 ); 
                    if ( !bInit )
                    { vecNewSkill.push_back( pPetMonster->autoSkillId[i] ); }
                }
            }
        }

        pet.baseInfo.lastRealizeSkillLevel = pet.baseInfo.level;
    }


    // 检查技能等级
    for (int i=0; i<SPetItem::PetDefine_MaxSkillCount; ++i )
    {
        if (pet.skillInfo.skills[i].ustSkillID == InvalidLogicNumber)
        { continue; }

        if (pet.skillInfo.skills[i].ustSkillID == pPetMonster->talentSkillId)
        { continue; }

        for (int lv=0; lv < ItemDefine::MaxLevel_Skill; ++lv )
        {
            ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( pet.skillInfo.skills[i].ustSkillID, lv );
            if (pSkill == NULL)
            { continue; }

            if (pSkill->stLearnLevelReq <= pet.baseInfo.level )
            { pet.skillInfo.skills[i].stSkillLevel = lv; }
        }
    }

    return true;
}

bool PetManager::UpdateTalentSkill( uint16 petType, uint8 skillLevel )
{
    if ( _pPetItems == NULL || NULL == _pGamePlayer )
    { return false; }

    for ( int i=0; i<_nPetCount; ++i )
    {
        if ( _pPetItems[i].baseInfo.petId   == InvalidLogicNumber )
        { continue; }

        if ( _pPetItems[i].baseInfo.petType != petType )
        { continue; }

        ItemDefine::SPetMonster* pPetMonster = GettheItemDetail().GetPetById( _pPetItems[i].baseInfo.petId );
        if ( pPetMonster == NULL ) 
        { continue; }

        if ( _pPetItems[i].skillInfo.skills[i].ustSkillID != pPetMonster->talentSkillId )
        { continue; }

        _pPetItems[i].skillInfo.skills[i].stSkillLevel = skillLevel;
    }

    return true;
}

void PetManager::SetAccumulateActionTime(unsigned long dwTime)
{
    if ( _activeIndex >= 0)
    { _accumulateActionTime = dwTime; }
}

long PetManager::PushPet( const SPetItem& PetItem )
{
    if ( _pPetItems == NULL || NULL == _pGamePlayer )
    { return ER_Failed; }

    for ( int i=0; i<_nPetCount; ++i )
    {
        if ( _pPetItems[i].baseInfo.petId == InvalidLogicNumber )
        {
            _pPetItems[i] = PetItem;
            if ( _pGamePlayer )
            { 
				//_pGamePlayer->Log("得到宠物PetId[%d] BigId[%I64u] ", PetItem.baseInfo.petId,  PetItem.baseInfo.guid );
				_pGamePlayer->Log(theXmlString.GetString(eServerLog_GetPet), PetItem.baseInfo.petId,  PetItem.baseInfo.guid );

			
			}
            
            return ER_Success;
        }
    }
    return ER_Failed;
}

long PetManager::PopPet( int nIndex, bool& isActiveIndex )
{
    if ( _pPetItems == NULL || NULL == _pGamePlayer )
    { return ER_Failed; }

    if ( nIndex < 0 || nIndex >= _nPetCount )
    { return ER_Failed; }

    if ( _pPetItems[ nIndex ].baseInfo.petId == InvalidLogicNumber )
    { return ER_Failed; }

    // 是否放生了出战的宠物
    if ( _pPetItems[ nIndex ].baseInfo.isActive == AT_Active )
    {
        isActiveIndex   = true;
        _activeIndex    = -1;
    }

    if ( _pGamePlayer )
    { 
        SPetItem* pPet = &_pPetItems[ nIndex ];
        //_pGamePlayer->Log("失去宠物PetId[%d] Name[%s] BigId[%I64u]", pPet->baseInfo.petId, pPet->baseInfo.szName , pPet->baseInfo.guid );
		_pGamePlayer->Log(theXmlString.GetString(eServerLog_DelPet), pPet->baseInfo.petId, pPet->baseInfo.szName , pPet->baseInfo.guid );
    }

    // 删除这个位置的马
    _pPetItems[ nIndex ].baseInfo.Reset();
    _pPetItems[ nIndex ].skillInfo.Reset();

    // 整理 后面的往前靠
    for ( int i=nIndex, I=nIndex+1; i<_nPetCount; ++i, ++I )
    {  
        // 如果已经到最后了跳出 通过I来判断
        if ( I >= _nPetCount )
        { break; }

        // 如果i已经是最后一个了 通过I来判断
        if ( _pPetItems[I].baseInfo.petId == InvalidLogicNumber )
        { break; }

        _pPetItems[i] = _pPetItems[I];

        // 清掉排在后面的数据
        _pPetItems[I].baseInfo.Reset();
        _pPetItems[I].skillInfo.Reset();
    }

    // 刷新一下 _activeIndex 有可能删除中间位置的宠物 位置有移位
    UpdateActiveIndex();

    return ER_Success;
}

long PetManager::PopPetByBigId( __int64 nBigId, bool& bActiveIndex )
{
    if ( _pPetItems == NULL || NULL == _pGamePlayer  )
    { return ER_Failed; }

    // 找到对应bigId的下标
    int nIndex = -1;
    for ( int i=0; i<_nPetCount; ++i )
    {
        if ( _pPetItems[i].baseInfo.guid == nBigId && _pPetItems[i].baseInfo.petId != InvalidLogicNumber)
        {   
            nIndex = i;
            break;
        }
    }

    if ( nIndex == -1 )
    { return ER_Failed; }

    // 删除宠物
    return PopPet( nIndex, bActiveIndex );
}

int PetManager::GetPetEmptyCount()
{
    if ( _pPetItems == NULL || NULL == _pGamePlayer  )
    { return 0; }

    int nPetLimit = thePetSettingConfig.GetPlayerPetLimit( _pGamePlayer->GetLevel() );
    int nEmptyCount = 0;
    for ( int i = 0; i < nPetLimit; ++i )
    {
        if ( _pPetItems[i].baseInfo.petId == InvalidLogicNumber )
        { ++nEmptyCount;}
    }
    return nEmptyCount;
}

int PetManager::GetPetNumber()
{
    if ( _pPetItems == NULL || NULL == _pGamePlayer  )
    { return 0; }

    int nPetLimit   = thePetSettingConfig.GetPlayerPetLimit( _pGamePlayer->GetLevel() );
    int nPetNumber  = 0;
    for ( int i = 0; i < nPetLimit; ++i )
    {
        if ( _pPetItems[i].baseInfo.petId != InvalidLogicNumber )
        { ++nPetNumber;}
    }
    return nPetNumber;
}

int PetManager::GetPetMaxLevel()
{
    if ( _pPetItems == NULL || NULL == _pGamePlayer  )
    { return 0; }

    int nMaxLevel   = 0;
    int nPetLimit   = thePetSettingConfig.GetPlayerPetLimit( _pGamePlayer->GetLevel() );
    for ( int i = 0; i < nPetLimit; ++i )
    {
        if ( _pPetItems[i].baseInfo.petId == InvalidLogicNumber )
        { continue; }

        if ( _pPetItems[i].baseInfo.level > nMaxLevel  )
        { nMaxLevel = _pPetItems[i].baseInfo.level; }
    }
    return nMaxLevel;
}

bool PetManager::IsHavePet( int petId )
{
    if ( _pPetItems == NULL || NULL == _pGamePlayer  )
    { return 0; }

    int nPetLimit   = thePetSettingConfig.GetPlayerPetLimit( _pGamePlayer->GetLevel() );
    for ( int i = 0; i < nPetLimit; ++i )
    {
        if ( _pPetItems[i].baseInfo.petId == petId )
        { return true; }
    }
    return false;
}

bool PetManager::IsHavePetType( int petType )
{
    if ( _pPetItems == NULL || NULL == _pGamePlayer  )
    { return 0; }

    int nPetLimit   = thePetSettingConfig.GetPlayerPetLimit( _pGamePlayer->GetLevel() );
    for ( int i = 0; i < nPetLimit; ++i )
    {
        if ( _pPetItems[i].baseInfo.petType == petType )
        { return true; }
    }
    return false;
}

SPetItem* PetManager::GetPetByGuid( __int64 nBigId )
{  
    if ( _pPetItems == NULL || NULL == _pGamePlayer  )
    { return NULL; }

    for ( int i=0; i<_nPetCount; ++i )
    {
        if ( _pPetItems[i].baseInfo.guid == nBigId && _pPetItems[i].baseInfo.petId != InvalidLogicNumber )
        {   
            return &_pPetItems[i];
        }
    }
    return NULL;
}

int PetManager::GetPetIndexByGuid( __int64 nBigId )
{
    if ( _pPetItems == NULL || NULL == _pGamePlayer  )
    { return -1; }

    for ( int i=0; i<_nPetCount; ++i )
    {
        if ( _pPetItems[i].baseInfo.guid == nBigId && _pPetItems[i].baseInfo.petId != InvalidLogicNumber )
        {   
            return i;
        }
    }
    return -1;
}

SPetItem* PetManager::GetActivePet()
{
    if ( _pPetItems == NULL || NULL == _pGamePlayer || _activeIndex < 0 )
        return NULL;

    return &_pPetItems[_activeIndex];
}

SPetItem*  PetManager::GetPetByIndex( int nIndex )
{
    if ( _pPetItems == NULL || NULL == _pGamePlayer || nIndex < 0 || nIndex > ITEM_PET_MAXCOUNT )
        return NULL;

    if ( _pPetItems[nIndex].baseInfo.petId == InvalidLogicNumber || _pPetItems[nIndex].baseInfo.guid == 0 )
        return NULL;

    return &_pPetItems[nIndex];
}

__int64 PetManager::GetNewBigID()
{   
    const int nCount = 3;
    for ( int i=0; i<nCount; ++i )
    {
        __int64 nBigId = HelperFunc::CreateID();
        if ( !GetPetByGuid( nBigId ) )
        { return nBigId; }
    }
    return -1;
}

void PetManager::AddActivePetExp( int rewardExp )
{
    if ( _pPetItems == NULL || _activeIndex < 0 || NULL ==  _pGamePlayer)
    { return; }
    
    if ( _activeIndex >= _nPetCount)
    { _activeIndex = -1; }

    SPetItem* pCurrentPet = &_pPetItems[_activeIndex];

    if (pCurrentPet == NULL)
    { return; }
	//副将经验只受防沉迷的影响
    /*rewardExp = rewardExp * ( _pGamePlayer->GetExpChangePer()                );
    rewardExp = rewardExp * ( theRunTimeData.g_nExpPer  * DEF_PERCENT        );
    rewardExp = rewardExp * ( _pGamePlayer->_buffManager.GetExpAddMul() + 1  );*/

    AddPetExp( _activeIndex, rewardExp );
}

bool PetManager::AddPetExp( int nIndex, int iAddExp )
{
    if (NULL == _pPetItems || NULL == _pGamePlayer || _nPetCount <= 0)
    { return false; }

    if ( iAddExp <= 0 )
    { return false; }

    SPetItem* pCurrentPet = GetPetByIndex(nIndex);
    if ( pCurrentPet == NULL )
    {
        MsgAckResult msg;
        msg.result = ER_NotFoundPet;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return false;
    }

    int64 newExp = pCurrentPet->baseInfo.exp + iAddExp;
    int nNewLevel = theExpStage.GetPetLevel( newExp );

    // 携带等级
    int petTakeLevel = PET_LEVEL_OVERTOP_MAX + thePetSettingConfig.GetSavvyAddTakeLevel( pCurrentPet->baseInfo.savvy );
    if ( nNewLevel > _pGamePlayer->GetLevel() + petTakeLevel  )
    { 
        nNewLevel = _pGamePlayer->GetLevel() + petTakeLevel;
        newExp    = theExpStage.GetPetLevelupExp( _pGamePlayer->GetLevel() + petTakeLevel );
    }
	//副将最高等级
	if(nNewLevel>thePetDefineConfig.GetMaxLevel())
	{
		nNewLevel = thePetDefineConfig.GetMaxLevel();
        newExp    = theExpStage.GetPetLevelupExp(thePetDefineConfig.GetMaxLevel());
	}
	if(newExp ==  pCurrentPet->baseInfo.exp)
		return false;
    pCurrentPet->baseInfo.exp = newExp;
    if ( nNewLevel != pCurrentPet->baseInfo.level )
    { // 级别改变

        std::vector< uint16 > vecNewSkill;
        int nOldLevel = pCurrentPet->baseInfo.level;
        int nAddLevel = nNewLevel - nOldLevel;
        pCurrentPet->baseInfo.level += nAddLevel;

		if(nNewLevel > thePetDefineConfig.GetAttChangeLevel())
		{
			/*for ( int i=0; i<EBaseAttr_MaxSize; ++i)
			{ 
				pCurrentPet->baseInfo.baseAttribute[i] += ( pCurrentPet->baseInfo.level - nOldLevel ) * PET_LEVELUP_BASEATTR;
			}*/

			int nAddPotentialPoint = ( pCurrentPet->baseInfo.level - nOldLevel ) * PET_LEVELUP_POTENTIALPOINT;
			pCurrentPet->baseInfo.nPotentialPoint += nAddPotentialPoint;
		}

        // 繁殖次数
        //pCurrentPet->baseInfo.breedNum  = thePetSettingConfig.GetPetBreedNum( pCurrentPet->baseInfo.level );

        // 重新计算属性
        //UpdatePetAttribute( *pCurrentPet );

        // 技能领悟
        RealizePetSkill( *pCurrentPet , vecNewSkill );

        // 计算战斗力
        CalcBattleEffectiveness( *pCurrentPet );

        // 被动技能影响
        //ApplyPassiveSkillToPet( pCurrentPet );

        pCurrentPet->baseInfo.hp = pCurrentPet->baseInfo.GetFightAttribute( CharAttr_HPMax ) ;

        if ( nIndex == _activeIndex )
        { // 出战宠物更新数据
            MonsterNurturePet* pNurturePet = (MonsterNurturePet*)GetMonsterNurturePet();
            if ( pNurturePet != NULL )
            { pNurturePet->UpdatePetData(); }

            UpdateActiveSkillBag();
        }

        if ( vecNewSkill.size() > 0 )
        {// 宠物学新了新的技能
            std::vector< uint16 >::iterator iter = vecNewSkill.begin();
            for ( ; iter != vecNewSkill.end(); ++iter )
            {
                MsgPetLearnSkill msg;
                msg.source  = MsgPetLearnSkill::ESource_Realize;
                msg.index   = nIndex;
                msg.skillId = *iter;
                msg.skillLevel = 1;
                GettheServer().SendMsgToSingle( &msg, _pGamePlayer );
            }
        }
    }

    // 发送宠物获得经验
    _pGamePlayer->ChangeAttr( CharAttr_ActivePetCurGetExp, iAddExp, true );

    // 下发消息
    MsgAddUpdatePet msg;
    msg.header.stID = _pGamePlayer->GetID();
    msg.pet = *pCurrentPet;
    msg.type = MsgAddUpdatePet::OT_Update;
    GettheServer().SendMsgToSingle( &msg, _pGamePlayer);

    return true;
}

bool PetManager::AddPetSavvy( int nIndex )
{
    if (NULL == _pPetItems || NULL == _pGamePlayer || _nPetCount <= 0)
    { return false; }

    SPetItem* pPetItem = GetPetByIndex(nIndex);
    if ( pPetItem == NULL )
    {
        MsgAckResult msg;
        msg.result = ER_NotFoundPet;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return false;
    }

    ItemDefine::SPetMonster* pMonsterConfig = GettheItemDetail().GetPetById( pPetItem->baseInfo.petId );
    if ( pMonsterConfig == NULL ) 
    { 
        MsgAckResult msg;
        msg.result = ER_NotFoundPet;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return false; 
    }

    if ( pPetItem->baseInfo.savvy == PetSettingConfig::EPetSavvy_LevelMax)
    { return false; }

    int nSavvyUpRate  = thePetSettingConfig.GetSavvyUpItemRate  ( pMonsterConfig->catchQuality, pMonsterConfig->catchLevel, pPetItem->baseInfo.savvy );
    int nSavvyUpMoney = thePetSettingConfig.GetSavvyUpItemMoney ( pMonsterConfig->catchQuality, pMonsterConfig->catchLevel, pPetItem->baseInfo.savvy );

    if( nSavvyUpMoney > _pGamePlayer->GetMoney() )
    {
        MsgAckResult msg;
        msg.result = ER_PetSavvyUpMoney;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return false;
    }

    _pGamePlayer->OperateMoney( EOT_Sub, nSavvyUpMoney, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_PetSavvyUp);

    if ( (theRand.rand16() % RAND_NUM) < nSavvyUpRate )
    {
        pPetItem->baseInfo.savvy += 1;
        //UpdatePetAttribute( *pPetItem );
        CalcBattleEffectiveness( *pPetItem );
        //ApplyPassiveSkillToPet( pPetItem );

        if ( nIndex == _activeIndex )
        { // 出战宠物更新数据
            MonsterNurturePet* pNurturePet = (MonsterNurturePet*)GetMonsterNurturePet();
            if ( pNurturePet != NULL )
            { pNurturePet->UpdatePetData(); }

            UpdateActiveSkillBag();
        }

        MsgAddUpdatePet msg;
        msg.header.stID = _pGamePlayer->GetID();
        msg.pet = *pPetItem;
        msg.type = MsgAddUpdatePet::OT_Update;
        GettheServer().SendMsgToSingle( &msg, _pGamePlayer);

        MsgPetSavvyUpAck msgAck;
        msgAck.index  = nIndex;
        msgAck.result = MsgPetSavvyUpAck::ER_Success;
        GettheServer().SendMsgToSingle( &msgAck, _pGamePlayer);

		if(pPetItem->baseInfo.savvy >= 8)
		{
			MsgChat chat(MsgChat::CHAT_TYPE_PROGRAM_SYSTEM);
			chat.type = BT_PetBag;
			chat.nHyberItemCnt = 1;
			chat.onlyId[0] = pPetItem->baseInfo.guid;
			char bufStr[BUFSIZ] = {0};
			sprintf_s( bufStr,sizeof(bufStr), theXmlString.GetString(eText_Pet_WorldInfo),_pGamePlayer->GetCharName(), pPetItem->baseInfo.szName,pPetItem->baseInfo.savvy);
			_pGamePlayer->ProcessSystem( bufStr,GamePlayer::SystemWorld, &chat );
		}
    }
    else
    {
        MsgPetSavvyUpAck msgAck;
        msgAck.index  = nIndex;
        msgAck.result = MsgPetSavvyUpAck::ER_Failed;
        GettheServer().SendMsgToSingle( &msgAck, _pGamePlayer);
    }

    return true;
}

void PetManager::UpdateActiveIndex()
{
    if ( _pPetItems == NULL )
    { return; }

    // 更新出战
    for ( int i=0; i<_nPetCount; ++i )
    {
        if ( _pPetItems[i].baseInfo.petId == InvalidLogicNumber )
            break;
        if ( _pPetItems[i].baseInfo.isActive == AT_Active )
        {
            _activeIndex = i;

            // 出战宠物更新数据
            MonsterNurturePet* pNurturePet = (MonsterNurturePet*)GetMonsterNurturePet();
            if ( pNurturePet != NULL )
            { pNurturePet->SetPetItemData( &_pPetItems[i] ); }
            break;
        }
    }
}

//void PetManager::ApplyPassiveSkillToPet( SPetItem* pPetItem )
//{
//    if ( pPetItem == NULL )
//    { return ; }
//
//    if ( pPetItem->baseInfo.petId == InvalidLogicNumber )
//    { return; }
//
//    if ( pPetItem->baseInfo.guid  == InvalidLogicNumber )
//    { return; }
//
//
//    for ( int i = 0; i < SPetItem::PetDefine_MaxSkillCount; ++i )
//    {
//        SCharSkill* pPassiveSkill = &pPetItem->skillInfo.skills[i];
//        if ( pPassiveSkill == NULL || pPassiveSkill->ustSkillID == InvalidLogicNumber )
//        { continue; }
//
//        ItemDefine::SItemSkill* pSkillConfig = GettheItemDetail().GetSkillByID(pPassiveSkill->ustSkillID, pPassiveSkill->stSkillLevel);
//        if( pSkillConfig == NULL )
//        { continue; }
//
//        if ( pSkillConfig->sSkillCategory != ItemDefine::SCT_PetPassive)
//        { continue; }
//
//        short shPassiveSkillTarget = pSkillConfig->shPassiveSkillTarget;
//
//        if( !(shPassiveSkillTarget == CItemDetail::PassiveSkillTarget_Self ||
//            shPassiveSkillTarget == CItemDetail::PassiveSkillTarget_SelfAndAllPet ||
//            shPassiveSkillTarget == CItemDetail::PassiveSkillTarget_SelfAndTargetPet) )
//        { return; }
//
//        for (int i = 0;i < ItemDefine::SItemSkill::EItemSkillConst_AddStatusMaxSize; ++i )
//        {
//            ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pSkillConfig->ustMeAddStatusID[i], pSkillConfig->ustMeAddStatusLevel[i] );
//            if( pStatus == NULL )
//            { return; }
//
//            pPetItem->baseInfo.fightAttribute[CharAttr_HPMax]         += pStatus->stChanged_HPMax;
//            pPetItem->baseInfo.fightAttribute[CharAttr_AttackPhysics] += pStatus->changePhyAttack; 
//            pPetItem->baseInfo.fightAttribute[CharAttr_AttackMagic]   += pStatus->changeMagAttack ; 
//            pPetItem->baseInfo.fightAttribute[CharAttr_DefendPhysics] += pStatus->changeDefend[EDefendType_Physical];
//            pPetItem->baseInfo.fightAttribute[CharAttr_DefendMagic]   += pStatus->changeDefend[EDefendType_Magic] ;
//
//            pPetItem->baseInfo.fightAttribute[CharAttr_Exact]         += pStatus->stChanged_Hit;  
//            pPetItem->baseInfo.fightAttribute[CharAttr_Dodge]         += pStatus->stChanged_Hedge;
//
//            pPetItem->baseInfo.fightAttribute[CharAttr_Critical]      += pStatus->changed_Critical;
//            pPetItem->baseInfo.fightAttribute[CharAttr_Tenacity]      += pStatus->changeTenacity;
//        }
//    }
//}

void PetManager::LostActivePetMonster()
{
    if ( _pPetItems == NULL || _activeIndex < 0 || _activePetCharId < 0)
    { return ; }

    MonsterBaseEx* pPetChar = (MonsterBaseEx*) theRunTimeData.GetCharacterByID( _activePetCharId );
    if ( pPetChar != NULL && pPetChar->IsPet() && !pPetChar->IsIllusionChar() && pPetChar->GetMonsterType() == eMT_Pet )
    { pPetChar->CharacterMurder();  }
	SPetItem* pActivePetItem = GetActivePet();
	if (pActivePetItem)
	{
		for (int indexSkill=0; indexSkill<pActivePetItem->skillInfo.GetCurrentSkillCount(); indexSkill++)
		{
			ItemDefine::SItemSkill* pPetSkill = GettheItemDetail().GetSkillByID( pActivePetItem->skillInfo.skills[indexSkill].ustSkillID, pActivePetItem->skillInfo.skills[indexSkill].stSkillLevel );
			if(pPetSkill && pPetSkill->petSkillCategory==EPetSkillCategory_Aptitude && pPetSkill->stGeneralType==ItemDefine::generaltype_passive)
			{
				//有资质类的被动技能，消除buff
				_pGamePlayer->ApplyPetAttrToChar(pPetSkill,true);
			}
		}
		_pGamePlayer->RefreshLieutenantAttr(false);
	}
	if(pActivePetItem/* && pActivePetItem->baseInfo.petType == EPT_Capture*/)
	{
		_pGamePlayer->GetCharInfo().otherdata.nsuanimalID = 0;//记录出战的副将ID
	}
}

void PetManager::LostActivePet( bool bIsBeKilled )
{
    if ( _pPetItems == NULL || _activeIndex < 0 || _activePetCharId < 0)
    { return ; }

    if ( _pPetItems[_activeIndex].baseInfo.petId == InvalidLogicNumber )
    { return ; }

    ItemDefine::SPetMonster* pMonsterConfig = GettheItemDetail().GetPetById( _pPetItems[_activeIndex].baseInfo.petId );
    if (pMonsterConfig == NULL)
    { return ; }

    _pPetItems[_activeIndex].baseInfo.isActive = AT_NotActive;

    if ( bIsBeKilled )
    {
		//副将快乐度相关的内容都不要  by liaojie  11.21
        /*int dropLoyalty = thePetSettingConfig.GetPetDeathDropLoyalty(_pPetItems[_activeIndex].baseInfo.level) ;
        if (dropLoyalty >= _pPetItems[_activeIndex].baseInfo.loyalty)
        { _pPetItems[_activeIndex].baseInfo.loyalty = 0; }
        else
        { _pPetItems[_activeIndex].baseInfo.loyalty -= dropLoyalty; }*/

        /*int dropLife = thePetSettingConfig.GetPetDeathDropDuration(_pPetItems[_activeIndex].baseInfo.level) ;
        if (dropLife >= _pPetItems[_activeIndex].baseInfo.duration )
        { _pPetItems[_activeIndex].baseInfo.duration = 0; }
        else
        { _pPetItems[_activeIndex].baseInfo.duration -= dropLife; }*/

        _pPetItems[_activeIndex].baseInfo.regenerateTime = HQ_TimeGetTime() + pMonsterConfig->regenerateTime * ONE_SEC;
        _pPetItems[_activeIndex].baseInfo.hp = _pPetItems[_activeIndex].baseInfo.GetFightAttribute( CharAttr_HPMax ) * 0.25;

        MsgPetRegenerate msgRegenerate;
        msgRegenerate.index = _activeIndex;
        msgRegenerate.regenerateTime = pMonsterConfig->regenerateTime;
        GettheServer().SendMsgToSingle( &msgRegenerate, _pGamePlayer );
    }

	if(_pPetItems/* && _pPetItems->baseInfo.petType == EPT_Capture*/)
	{
		_pGamePlayer->GetCharInfo().otherdata.nsuanimalID = 0;//记录出战的副将ID
	}

    MsgChangePet changeAck;
    changeAck.ucOpType  = MsgChangePet::EOT_UnActive;
    changeAck.nIndex    = _activeIndex;
    changeAck.guid      = _pPetItems[_activeIndex].baseInfo.guid;
    GettheServer().SendMsgToSingle( &changeAck, _pGamePlayer );

    MsgAddUpdatePet update;
    update.header.stID = _pGamePlayer->GetID();
    update.type = MsgAddUpdatePet::OT_Update;
    update.pet  = _pPetItems[_activeIndex];
    GettheServer().SendMsgToSingle( &update, _pGamePlayer );
    
	SPetItem* pActivePetItem = GetActivePet();
	if (pActivePetItem)
	{
		for (int indexSkill=0; indexSkill<pActivePetItem->skillInfo.GetCurrentSkillCount(); indexSkill++)
		{
			ItemDefine::SItemSkill* pPetSkill = GettheItemDetail().GetSkillByID( pActivePetItem->skillInfo.skills[indexSkill].ustSkillID, pActivePetItem->skillInfo.skills[indexSkill].stSkillLevel );
			if(pPetSkill && pPetSkill->petSkillCategory==EPetSkillCategory_Aptitude && pPetSkill->stGeneralType==ItemDefine::generaltype_passive)
			{
				//有资质类的被动技能，消除buff
				_pGamePlayer->ApplyPetAttrToChar(pPetSkill,true);
			}
		}
		_pGamePlayer->RefreshLieutenantAttr(false);
	}


    _activeIndex = -1;
    _activePetCharId = -1;
}

long PetManager::ProcessSetPetActive( int nIndex )
{
    if ( _pPetItems == NULL || NULL == _pGamePlayer )
    { return ER_Failed; }

    // 下标是否超出
    if ( nIndex < 0 || nIndex >= _nPetCount )
    { return ER_IndexOutOfRange;}

    // 此位置的坐骑是否不存在
    if ( _pPetItems[nIndex].baseInfo.petId == InvalidLogicNumber )
    { return ER_NullPointer; }

    SPetItem* pPet = &_pPetItems[nIndex];

    ItemDefine::SPetMonster* pMonsterConfig = GettheItemDetail().GetPetById( pPet->baseInfo.petId );
    if (pMonsterConfig == NULL)
    { return ER_NullPointer; }

    if ( pMonsterConfig->takeLevel > _pGamePlayer->GetLevel() )
    { 
        _pGamePlayer->SendErrorToClient( ER_PetTakeLevel, pMonsterConfig->takeLevel );
        return ER_PetTakeLevel; 
    }

    int petTakeLevel = PET_LEVEL_OVERTOP_MAX + thePetSettingConfig.GetSavvyAddTakeLevel( pPet->baseInfo.savvy );
    if ( pPet->baseInfo.level > _pGamePlayer->GetLevel() + petTakeLevel  )
    { 
        _pGamePlayer->SendErrorToClient( ER_PetTakeLevel, _pGamePlayer->GetLevel() + petTakeLevel );
        return ER_PetTakeLevel; 
    }

    MonsterCreateData xCreateData;
    xCreateData.SetMapID( _pGamePlayer->GetMapID() );
    xCreateData.SetPostionX( _pGamePlayer->GetFloatX() + 2.0f );
    xCreateData.SetPostionY( _pGamePlayer->GetFloatY() + 2.0f );
    xCreateData.SetDirX( _pGamePlayer->GetDirX() );
    xCreateData.SetDirY( _pGamePlayer->GetDirY() );
    xCreateData.SetMonsterID( pPet->baseInfo.petId );
    xCreateData.SetPetItem( pPet );

    float xOff = 2;
    float yOff = 2;

    MonsterBaseEx* pAIMonster = MonsterCreater::CreatePetNurtureMonster( xCreateData, _pGamePlayer );
    if ( pAIMonster == NULL )
    { return ER_Failed; }

    pPet->baseInfo.isActive = AT_Active;
    _activeIndex = nIndex;
    _activePetCharId = pAIMonster->GetID();
    UpdateActiveSkillBag();

	for (int indexSkill=0; indexSkill<pPet->skillInfo.GetCurrentSkillCount(); indexSkill++)
	{
		ItemDefine::SItemSkill* pPetSkill = GettheItemDetail().GetSkillByID( pPet->skillInfo.skills[indexSkill].ustSkillID, pPet->skillInfo.skills[indexSkill].stSkillLevel );
		if(pPetSkill && pPetSkill->petSkillCategory==EPetSkillCategory_Aptitude && pPetSkill->stGeneralType==ItemDefine::generaltype_passive)
		{
			//有资质类的被动技能，增加属性到人物身上
			_pGamePlayer->ApplyPetAttrToChar(pPetSkill,false);
		}
	}
	//副将出战的话 记录ID
	if(pPet/* && pPet->baseInfo.petType == EPT_Capture*/)
	{
		_pGamePlayer->GetCharInfo().otherdata.nsuanimalID = pPet->GetPetGuid();//记录出战的副将ID
		_pGamePlayer->RefreshLieutenantAttr(true);
	}

    return ER_Success;
}

void PetManager::UpdateActiveSkillBag()
{
    if ( _pPetItems == NULL || _activeIndex < 0)
        return;

    _activeSkillBag.Init( _pPetItems[_activeIndex].skillInfo.skills, SPetItem::PetDefine_MaxSkillCount, true );
}

void PetManager::RefreshPetData( unsigned long elapsTime )
{
    if ( _pPetItems == NULL )
    { return; }

    if ( _activeIndex >= 0 && _activePetCharId >= 0 )
    { // 有激活的坐骑
        _accumulateActionTime += elapsTime; 
        _refreshLifeTime      += elapsTime;
        _refreshLoyaltyTime   += elapsTime;

        if ( _refreshLifeTime >= thePetSettingConfig.GetRefreshDurationTime() )
        {
            _refreshLifeTime = 0;
            if ( InvalidLogicNumber == _pPetItems[_activeIndex].baseInfo.petId )
            { return; }

            // 开始扣宠物寿命
			// 减少玩家的指挥点
			_pGamePlayer->SetPetDuration(-1);

            //_pPetItems[_activeIndex].baseInfo.duration -= 1;
        }

		//不要快乐度了  by liaojie 11.21
        /*if ( _refreshLoyaltyTime >  thePetSettingConfig.GetRefreshLoyaltyTime() ) 
        {
            _refreshLoyaltyTime = 0;
            if ( InvalidLogicNumber == _pPetItems[_activeIndex].baseInfo.petId )
            { return; }

            _pPetItems[_activeIndex].baseInfo.loyalty -= 1;
        }*/

        if (/* _pPetItems[_activeIndex].baseInfo.duration == 0 */ _pGamePlayer->GetCharInfo().otherdata.PetDuration == 0)
        { LostActivePetMonster();  }

        /*if ( _pPetItems[_activeIndex].baseInfo.loyalty < 60 )
        { LostActivePetMonster();  }*/

        _activeSkillBag.Update();
    }
}

void PetManager::ApplyBaseAttrToFight ( SPetItem& pet )
{
    //ItemDefine::SPetMonster* pPetMonster = GettheItemDetail().GetPetById( pet.baseInfo.petId );
    //if ( pPetMonster == NULL ) 
    //{ return ; }

    //int   petLevel = pet.baseInfo.level;
    //int   growRate = pet.baseInfo.growRate;
    //
    //// HP
    //pet.baseInfo.fightAttribute[CharAttr_HPMax]         = ProcessCharInfo::PetBaseAttrToFightAttr( pet, CharAttr_HPMax );

    //// 物攻
    //pet.baseInfo.fightAttribute[CharAttr_AttackPhysics] = ProcessCharInfo::PetBaseAttrToFightAttr( pet, CharAttr_AttackPhysics );

    //// 魔攻
    //pet.baseInfo.fightAttribute[CharAttr_AttackMagic]   = ProcessCharInfo::PetBaseAttrToFightAttr( pet, CharAttr_AttackMagic );

    //// 物防
    //pet.baseInfo.fightAttribute[CharAttr_DefendPhysics] = ProcessCharInfo::PetBaseAttrToFightAttr( pet, CharAttr_DefendPhysics );

    //// 魔防
    //pet.baseInfo.fightAttribute[CharAttr_DefendMagic]   = ProcessCharInfo::PetBaseAttrToFightAttr( pet, CharAttr_DefendMagic );

    //// 命中
    //pet.baseInfo.fightAttribute[CharAttr_Exact]         = ProcessCharInfo::PetBaseAttrToFightAttr( pet, CharAttr_Exact );

    //// 闪避
    //pet.baseInfo.fightAttribute[CharAttr_Dodge]         = ProcessCharInfo::PetBaseAttrToFightAttr( pet, CharAttr_Dodge );

    //// 暴击
    //pet.baseInfo.fightAttribute[CharAttr_Critical]      = ProcessCharInfo::PetBaseAttrToFightAttr( pet, CharAttr_Critical );

    //// 韧性
    //pet.baseInfo.fightAttribute[CharAttr_Tenacity]      = ProcessCharInfo::PetBaseAttrToFightAttr( pet, CharAttr_Tenacity );
}

void PetManager::CalcBattleEffectiveness( SPetItem& pet )
{
    int lowSkillNum = 0, highSkillNum = 0;
    for (int i=0; i<SPetItem::PetDefine_MaxSkillCount; ++i )
    {
        if (pet.skillInfo.skills[i].ustSkillID == InvalidLogicNumber)
        { continue; }

        ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( pet.skillInfo.skills[i].ustSkillID, pet.skillInfo.skills[i].stSkillLevel );
        if (pSkill == NULL)
        { continue; }

        if ( pSkill->groupLevel > 1 )
        { ++highSkillNum; }
        else
        { ++lowSkillNum; }
    }

     float fValue1 = 0.0f;
     
     switch( pet.baseInfo.attackType )
     {
     case EPetAttack_Physical:
         fValue1 = ( pet.baseInfo.GetFightAttribute(CharAttr_AttackPhysics) + pet.baseInfo.GetFightAttribute(CharAttr_Exact) * 2.3 ) * 
             ( 1 + pet.baseInfo.GetFightAttribute(CharAttr_Critical) * DEF_PERCENT );
         break;
     case EPetAttack_Magic:
         fValue1 = ( pet.baseInfo.GetFightAttribute(CharAttr_AttackMagic) + pet.baseInfo.GetFightAttribute(CharAttr_Exact) * 2.3 ) * 
             ( 1 + pet.baseInfo.GetFightAttribute(CharAttr_Critical) * DEF_PERCENT );
         break;
     case EPetAttack_Both:
         fValue1 = ( (pet.baseInfo.GetFightAttribute(CharAttr_AttackPhysics) + pet.baseInfo.GetFightAttribute(CharAttr_AttackMagic)) / 2 + pet.baseInfo.GetFightAttribute(CharAttr_Exact) * 2.3 ) * 
             ( 1 + pet.baseInfo.GetFightAttribute(CharAttr_Critical) * DEF_PERCENT );
         break;
     }
     

     float fValue2 = ( pet.baseInfo.GetFightAttribute(CharAttr_HPMax) / 6 + pet.baseInfo.GetFightAttribute(CharAttr_DefendPhysics) + pet.baseInfo.GetFightAttribute(CharAttr_DefendMagic) +
            pet.baseInfo.GetFightAttribute(CharAttr_Dodge) * 7 ) * ( 1 + pet.baseInfo.GetFightAttribute(CharAttr_CriticalIntensity) * DEF_PERCENT );

     
     pet.baseInfo.battleValue = (fValue1 + fValue2) * ( pow( 1.1 , lowSkillNum ) * pow( 1.2 , highSkillNum ) ) ;
}

bool  PetManager::IsPetFull()
{
    int count = 0;
    for (int i=0; i< _nPetCount; ++i)
    {
        if (_pPetItems[i].baseInfo.petId != InvalidLogicNumber)
        { ++count; }
    }

    return (thePetSettingConfig.GetPlayerPetLimit( _pGamePlayer->GetLevel() ) == count);
}

bool  PetManager::IsSelfPet( GameObjectId petCharId )
{
    if ( _pPetItems == NULL || _activeIndex < 0 || _activePetCharId < 0)
    { return false; }

    return (_activePetCharId == petCharId );
}

bool  PetManager::HaveActivePet()
{
    if ( _pPetItems != NULL && _activeIndex >= 0 && _activePetCharId >= 0 )
    { return true; }

    return false;
}


MonsterBaseEx*  PetManager::GetMonsterNurturePet()
{
    MonsterBaseEx* pAiChar = (MonsterBaseEx*) theRunTimeData.GetCharacterByID( _activePetCharId );
    if ( pAiChar != NULL && pAiChar->IsPet() )
    { return pAiChar; }

    return NULL;
}

bool PetManager::AddPetHp( int nIndex, int hp )
{
    if ( NULL == _pPetItems || NULL == _pGamePlayer || _nPetCount <= 0 )
    { return false; }

    SPetItem* pPetItem = GetPetByIndex(nIndex);
    if ( pPetItem == NULL )
    {
        MsgAckResult msg;
        msg.result = ER_NotFoundPet;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return false;
    }

    if (pPetItem->baseInfo.hp >= pPetItem->baseInfo.GetFightAttribute(CharAttr_HPMax))
    { return false; }

    pPetItem->baseInfo.hp += hp;
    if ( pPetItem->baseInfo.hp > pPetItem->baseInfo.GetFightAttribute(CharAttr_HPMax))
    { pPetItem->baseInfo.hp = pPetItem->baseInfo.GetFightAttribute(CharAttr_HPMax); }

    if ( nIndex == _activeIndex )
    { // 出战宠物更新数据
        MonsterNurturePet* pNurturePet = (MonsterNurturePet*)GetMonsterNurturePet();
        if ( pNurturePet != NULL )
        { pNurturePet->UpdatePetData(); }
    }

    MsgAddUpdatePet msg;
    msg.header.stID = _pGamePlayer->GetID();
    msg.type = MsgAddUpdatePet::OT_Update;
    msg.pet = *pPetItem;
    GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
    return true;
}

bool PetManager::AddPetLife( int nIndex, int life )
{
	return false;

   /* if ( NULL == _pPetItems || NULL == _pGamePlayer || _nPetCount <= 0 )
    { return false; }

    SPetItem* pPetItem = GetPetByIndex(nIndex);
    if ( pPetItem == NULL )
    {
        MsgAckResult msg;
        msg.result = ER_NotFoundPet;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return false;
    }

    ItemDefine::SPetMonster* pPetMonster = GettheItemDetail().GetPetById( pPetItem->baseInfo.petId );
    if ( pPetMonster == NULL ) 
    { return false; }

    if (pPetItem->baseInfo.duration >= pPetMonster->duration)
    { return false; }

    pPetItem->baseInfo.duration += life;
    if ( pPetItem->baseInfo.duration > pPetMonster->duration)
    { pPetItem->baseInfo.duration = pPetMonster->duration; }

    MsgAddUpdatePet msg;
    msg.header.stID = _pGamePlayer->GetID();
    msg.type = MsgAddUpdatePet::OT_Update;
    msg.pet  = *pPetItem;
    GettheServer().SendMsgToSingle(&msg,_pGamePlayer);*/
    return true;
}

bool PetManager::AddPetLoyalty( int nIndex, int loyalty )
{
    if ( NULL == _pPetItems || NULL == _pGamePlayer || _nPetCount <= 0 )
    { return false; }

    SPetItem* pPetItem = GetPetByIndex(nIndex);
    if ( pPetItem == NULL )
    {
        MsgAckResult msg;
        msg.result = ER_NotFoundPet;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return false;
    }

    ItemDefine::SPetMonster* pPetMonster = GettheItemDetail().GetPetById( pPetItem->baseInfo.petId );
    if ( pPetMonster == NULL ) 
    { return false; }

    if (pPetItem->baseInfo.loyalty >= PET_LOYALTY_LIMIT)
    { return false; }

    pPetItem->baseInfo.loyalty += loyalty;
    if ( pPetItem->baseInfo.loyalty > PET_LOYALTY_LIMIT)
    { pPetItem->baseInfo.loyalty = PET_LOYALTY_LIMIT; }

    MsgAddUpdatePet msg;
    msg.header.stID = _pGamePlayer->GetID();
    msg.type = MsgAddUpdatePet::OT_Update;
    msg.pet  = *pPetItem;
    GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
    return true;
}

SPetItem* PetManager::GetBreedPet()
{
    SPetItem* pBreedPet = &_pGamePlayer->gCharInfoServer.itemData.petBreedItem;
    if ( pBreedPet->baseInfo.petId == InvalidLogicNumber )
    { return NULL; }

    return pBreedPet;
}

bool PetManager::SetBreedPet( SPetItem *pPet )
{
    if ( pPet == NULL )
    { return false; }

    if ( pPet->baseInfo.petId == InvalidLogicNumber )
    { return false; }

    if ( pPet->breedInfo.targetGuid == InvalidLogicNumber )
    { return false; }

    _pGamePlayer->gCharInfoServer.itemData.petBreedItem = *pPet;
    return true;
}

void PetManager::ClearBreedPet()
{
    SPetItem clearPet;
    _pGamePlayer->gCharInfoServer.itemData.petBreedItem = clearPet;
}

bool PetManager::ClearPetPotential(int nIndex)
{
	if (NULL == _pPetItems || NULL == _pGamePlayer || _nPetCount <= 0)
	{ return false; }

	SPetItem* pPet = GetPetByIndex(nIndex);
	if ( pPet == NULL )
	{
		MsgAckResult msg;
		msg.result = ER_NotFoundPet;
		GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
		return false;
	}

	int nPotentialPoint = 0;

	for (int i=0;i<EBaseAttr_MaxSize;++i)
	{
		nPotentialPoint += pPet->baseInfo.potentialAttribute[i];
		pPet->baseInfo.potentialAttribute[i] = 0;
	}

	pPet->baseInfo.nPotentialPoint += nPotentialPoint;
	CalcBattleEffectiveness(*pPet);

	MsgAddUpdatePet msgPet;
	msgPet.header.stID =  _pGamePlayer->GetID();
	msgPet.pet  = *pPet;
	msgPet.type = MsgAddUpdatePet::OT_Update;
	GettheServer().SendMsgToSingle( &msgPet, _pGamePlayer);

	//清空副将的潜力点 我们判断 修改的副将是否是当前出战的副将
	if(GetActivePet() == pPet)
	{
		_pGamePlayer->RefreshLieutenantAttr(true);//当前副将一定处于出战状态
	}

	return true;
}
bool PetManager::RemovePetEquip(__int64 nBigId,int Index,int bagIndex)//副将脱下装备 到背包的指定位置
{
	if(Index >= SPetItem::PetEquip_MaxSum || Index <0)
		return false;//不在范围内
	SPetItem * pPet = GetPetByGuid(nBigId);
	if(!pPet)
		return false;
	if(pPet != GetActivePet())
		return false;
	SCharItem* pItem = &pPet->baseInfo.PetEquip[Index];
	if(pItem->itembaseinfo.ustItemID == 0 || pItem->itembaseinfo.nOnlyInt == 0)
		return false;//当前位置上无装备 无法脱下
	if(bagIndex != -1)
	{
		SCharItem * pBagItem = _pGamePlayer->GetNormalBagPointerByIndex(bagIndex);
		if(!pBagItem || pBagItem->itembaseinfo.ustItemID != 0 || pBagItem->itembaseinfo.nOnlyInt != 0)
			return false;//目标栏位为空
		//开始处理装备
		unsigned short CountSum = 1;
		//int nRes =_pGamePlayer->_NormalItemBag.PushItem(*pItem,CountSum,bagIndex);
		//往背包添加装备
		int nRes = _pGamePlayer->AddItemToBagByIndex(*pItem,bagIndex,CountSum);

		if ( nRes != ierr_Success )
			return false;
		else
		{
			//装备已经放到背包后 我们删除副将身上的装备
			if(pItem->petequipdata.isTimeEnd = true)
				pItem->petequipdata.isTimeEnd = false;
			memset( pItem,0, sizeof(SCharItem));//直接清理到数据
			//告诉客户端 副将的数据已经发送变化了
			UpdateActionPetInfo(pPet);
			_pGamePlayer->RefreshLieutenantAttr(true);
			return true;
		}
	}		
	else
	{
		int Count = _pGamePlayer->GetNullItemCount(BT_NormalItemBag);
		if(Count <1)
			return false;//背包无空位置 无法放装备
		unsigned short CountSum = 1;
		int nRes = _pGamePlayer->AddItemToBag(*pItem,CountSum);
		if ( nRes != ierr_Success )
			return false;
		else
		{
			//装备已经放到背包后 我们删除副将身上的装备
			if(pItem->petequipdata.isTimeEnd = true)
				pItem->petequipdata.isTimeEnd = false;
			memset( pItem,0, sizeof(SCharItem));//直接清理到数据
			UpdateActionPetInfo(pPet);
			_pGamePlayer->RefreshLieutenantAttr(true);
			return true;
		}
	}
	
}
bool PetManager::ChangePetEquip(__int64 nBigId,__int64 ItemOnlyID,int Index)
{
	//将背包的指定位置的物品删除掉 换到副将身上
	if(Index >= SPetItem::PetEquip_MaxSum || Index <0)
		return false;//不在范围内
	SPetItem * pPet = GetPetByGuid(nBigId);
	if(!pPet)
		return false;
	if(pPet != GetActivePet())
		return false;
	//判断背包的装备是否可以装备
	SCharItem * pBagItem = _pGamePlayer->GetBagItemByGuid(ItemOnlyID);
	if(!pBagItem)
		return false;
	ItemDefine::SItemCommon *  pItemCommon =  theItemDetailConfig.GetItemByID(pBagItem->itembaseinfo.ustItemID);
	if(!pItemCommon)
		return false;//物品不存在
	if(pItemCommon->ucItemType != ItemDefine::ITEMTYPE_PETEQUIP)
		return false;//物品类型不正确
	ItemDefine::SItemPetEquip* pPetEquip = (ItemDefine::SItemPetEquip*)pItemCommon;
	int Level = pPetEquip->iEquipLevelReq;
	if(pPet->baseInfo.level < Level)
		return false;//等级不够
	//判断位置
	if(pPetEquip->iPos != Index)
		return false;
	if(pBagItem->petequipdata.isTimeEnd = true)
		pBagItem->petequipdata.isTimeEnd = false;
	if(pBagItem->IsOverdue())
		return false;//已经到期
	//unsigned int BagIndex = pBagItem->itembaseinfo.stPacketIdx;
	SCharItem* pItem = &pPet->baseInfo.PetEquip[Index];
	if(pItem->itembaseinfo.ustItemID != 0 && pItem->itembaseinfo.nOnlyInt != 0 /*&& !RemovePetEquip(nBigId,Index)*/)//副将身上有装备 并且拖下失败了
	{
		//我们将将装备穿上
		SCharItem pPetLogItem = pPet->baseInfo.PetEquip[Index];//暂时缓存的装备
		pPet->baseInfo.PetEquip[Index] = *pBagItem;//直接复制过去
		//删除背包的物品
		if(!_pGamePlayer->RemoveBagItemByGuid(ItemOnlyID,pBagItem->GetItemCount()))
		{
			pPet->baseInfo.PetEquip[Index] = pPetLogItem;
			return false;
		}
		//将指定物品添加到背包去
		unsigned short CountSum = 1;		
		int nRes =_pGamePlayer->AddItemToBag(pPetLogItem,CountSum);
		if ( nRes != ierr_Success )
		{
			//放入背包失败 我们发送邮件给玩家 并且将装备附加带上
			GS2CSSendMailReq xReq;
			xReq.charDbId = RelationDefine::InitID;
			xReq.mail.type  = SMail::EMT_System;
			xReq.mail.state = SMail::EMS_NotOpen;
			xReq.mail.sendTime = TimeEx::GetNowTime();        
			xReq.mail.owners[EM_FromIndex].charDbId = 0;
			sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
			xReq.mail.owners[EM_ToIndex].charDbId = _pGamePlayer->GetDBCharacterID();
			HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName, _pGamePlayer->GetCharInfo().baseinfo.aptotic.szCharacterName, sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );
			sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_PetEquip_Remove_Context ) );
			sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_PetEquip_Remove_Title ) );
			xReq.mail.accessory.type = SMail::EAT_Item;
			memcpy( &xReq.mail.accessory.content,  &pPetLogItem, sizeof(SCharItem) ); 
			GettheServer().SendCenterServerMsg( &xReq );
			return false;
		}
	}
	else
	{
		//直接穿上装备
		pPet->baseInfo.PetEquip[Index] = *pBagItem;//直接复制过去
		//删除背包的物品
		if(!_pGamePlayer->RemoveBagItemByGuid(ItemOnlyID,pBagItem->GetItemCount()))
		{
			memset( pItem,0, sizeof(SCharItem));
			return false;
		}
	}
	//设置装备绑定
	if(pItemCommon->bIsCanBound)
		pPet->baseInfo.PetEquip[Index].SetBounded(true);
	UpdateActionPetInfo(pPet);
	_pGamePlayer->RefreshLieutenantAttr(true);
	return true;
}
void PetManager::UpdateActionPetInfo(SPetItem * pPet)
{
	//当给副将穿上装备 或者脱下装备的时候  我们向客户端同步副将的属性
    // 计算战斗力
	if(!pPet)
		return;
    CalcBattleEffectiveness( *pPet );
    pPet->baseInfo.hp = pPet->baseInfo.GetFightAttribute( CharAttr_HPMax ) ;

    if(GetActivePet() == pPet)
    { // 出战宠物更新数据
		_pGamePlayer->RefreshLieutenantAttr(true);

        MonsterNurturePet* pNurturePet = (MonsterNurturePet*)GetMonsterNurturePet();
        if ( pNurturePet != NULL )
        { pNurturePet->UpdatePetData(); }
        UpdateActiveSkillBag();
    }
    // 下发消息
    MsgAddUpdatePet msg;
    msg.header.stID = _pGamePlayer->GetID();
    msg.pet = *pPet;
    msg.type = MsgAddUpdatePet::OT_Update;
    GettheServer().SendMsgToSingle( &msg, _pGamePlayer);
}
void PetManager::UpdatePetEquipTime()
{
	//更新所有副将身上的装备的现实
	//只更新出战的副将的属性
	SPetItem* pPet = GetActivePet(); 
	if(!pPet) 
		return;
	bool IsNeedUpdate = false;
	for(int i =0;i<SPetItem::PetEquip_MaxSum;++i)
	{
		if(pPet->baseInfo.PetEquip[i].itembaseinfo.ustItemID == 0 || pPet->baseInfo.PetEquip[i].itembaseinfo.nOnlyInt == 0)
			continue;
		if(pPet->baseInfo.PetEquip[i].IsOverdue() && !pPet->baseInfo.PetEquip[i].petequipdata.isTimeEnd)
		{
			pPet->baseInfo.PetEquip[i].petequipdata.isTimeEnd = true;//设置无效化
			IsNeedUpdate = true;
		}
	}
	if(IsNeedUpdate)
	{ 
		MonsterNurturePet* pNurturePet = (MonsterNurturePet*)GetMonsterNurturePet();
        if ( pNurturePet != NULL )
			pNurturePet->UpdatePetData();//更新副将的属性
		_pGamePlayer->RefreshLieutenantAttr(true);
	}
}
void PetManager::UpdatePetInfo()
{
	UpdatePetEquipTime();
	OnUpdateActionPetMode();
}
void PetManager::OnUpdateActionPetMode()
{
	//更新当前
	SPetItem* pPet = GetActivePet();
	if(!pPet)
		return;//无出战的副将不进行更新
	if(pPet->baseInfo.PetModeID == 0)
		return;
	if(pPet->baseInfo.PetModeID != pPet->baseInfo.GetPetNewModeID())
	{
		//SPetItem 发送变化了 我们需要发送新的PetItem到客户端去
		pPet->baseInfo.PetModeID = pPet->baseInfo.GetPetNewModeID();
		MsgAddUpdatePet msg;
		msg.header.stID = _pGamePlayer->GetID();
		msg.pet = *pPet;
		msg.type = MsgAddUpdatePet::OT_Update;
		GettheServer().SendMsgToSingle( &msg, _pGamePlayer);
		//当副将模型发送变化的时候 我们重新设置好副将的模型ID
		MonsterNurturePet* pNurturePet = (MonsterNurturePet*)GetMonsterNurturePet();
        if ( pNurturePet != NULL )
        { 
			pNurturePet->UpdatePetMode(); 
		}
	}
}
void PetManager::ChangePetAtterValue(__int64 nBigId,__int64 TargetPetID)
{
	//修改副将的属性 和品质  除了模型 其他的 按需求进行修改
	SPetItem * pPet = GetPetByGuid(nBigId);
	if(!pPet)
		return;
	SPetItem * pTargetPet = GetPetByGuid(TargetPetID);
	if(!pTargetPet ||  GetActivePet() == pTargetPet)
		return;
	//修改副将的属性
	//1.等级修改
	pPet->baseInfo.level = pTargetPet->baseInfo.level;
	pPet->baseInfo.exp = pTargetPet->baseInfo.exp;
	//计算宠物的潜能点
	for(int i =0;i<EBaseAttr_MaxSize;++i)
	{
		pPet->baseInfo.baseAttribute[i] = pTargetPet->baseInfo.baseAttribute[i];
		pPet->baseInfo.potentialAttribute[i] = pTargetPet->baseInfo.potentialAttribute[i];
	}
	pPet->baseInfo.nPotentialPoint = pTargetPet->baseInfo.nPotentialPoint;
	//2.设置指定副将的技能 普通技能转移过去
	pPet->skillInfo.initiativeSkillNumber = pTargetPet->skillInfo.initiativeSkillNumber;
	for(int i =0;i<SPetItem::PetDefine_MaxSkillCount;++i)
	{
		if (pTargetPet->skillInfo.skills[i].ustSkillID == InvalidLogicNumber)
        { continue; }

		 ItemDefine::SPetMonster* pPetMonster = GettheItemDetail().GetPetById( pTargetPet->baseInfo.petId );
		if ( pPetMonster == NULL ) 
		{ continue; }
        
        if (pTargetPet->skillInfo.skills[i].ustSkillID == pPetMonster->talentSkillId)
        { continue; }

        ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( pTargetPet->skillInfo.skills[i].ustSkillID, pTargetPet->skillInfo.skills[i].stSkillLevel );
        if (pSkill == NULL)
        { continue; }

		pPet->skillInfo.skills[i] =  pTargetPet->skillInfo.skills[i];
	}
	//3副将的悟性
	pPet->baseInfo.savvy = pTargetPet->baseInfo.savvy;
	//同步属性到客户端去
	UpdateActionPetInfo(pPet);
	//移除多余的副将
	_pGamePlayer->RemovePetByGuid(TargetPetID);
}