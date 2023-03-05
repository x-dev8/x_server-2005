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
    {//���ｫ���г�������Ϊδ��ս״̬
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

    // һ�������ܺ�=24+�ȼ�*4 
    // ����һ��������Сֵ=4+�ȼ�*1 
    // ���䷽ʽ:�ȼ���������Ժ�Ȼ������������������.	
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

    // ���ﵥ������=��������*(�����������*(1������ֵ))
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

    // �ҵ��������� ����������Ŀ
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

	//�жϼ������� ������������������õ�����
	//int SkillSum = thePetDefineConfig.GetLevelSkillSum(pet.baseInfo.level);//���ݵȼ���ȡ����������
	//bool IsCanAddSkill = (SkillSum<=(manualSkillNum + autoSkillNum))?false:true;

    // ��ʼ�����µļ���
    for (int i=0; i< ItemDefine::SPetMonster::EPet_LvRealizeCount; ++i)
    {
        if ( pPetMonster->lvRealizeSkill[i] <= pet.baseInfo.lastRealizeSkillLevel )
        { continue; }

        if ( pPetMonster->lvRealizeSkill[i] > pet.baseInfo.level )
        { continue; }

        for (int index = 0; index < ItemDefine::SPetMonster::EPet_RandSkillCount; ++index )
        {
            int nRandom = theRand.rand16() % RAND_NUM;

            //��������
            if ( nRandom < pPetMonster->manualSkillRate[index] )
            {
                if ( manualSkillNum >= ItemDefine::SPetMonster::EPet_ManualSkillCount )
                { continue; }

                ItemDefine::SItemSkill* pManualSkill = GettheItemDetail().GetSkillByID( pPetMonster->manualSkillId[index], 1 );
                if (pManualSkill == NULL)
                { continue; }

                // ����Ƿ��滻���м���
                int repalceIndex = -1; 
                for (int findIndex=0; findIndex<SPetItem::PetDefine_MaxSkillCount; ++findIndex )
                {//�����滻����
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

                if ( repalceIndex >= 0 )  // �ҵ����滻����
                { pet.skillInfo.ReplaceSkill(pPetMonster->manualSkillId[index], 1, repalceIndex); }
                else
                { 
                    pet.skillInfo.AddSkill( pPetMonster->manualSkillId[i], 1 ); 
                    if ( !bInit )
                    { vecNewSkill.push_back( pPetMonster->manualSkillId[i] ); }
                    
                }
            }

            //��������
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


    // ��鼼�ܵȼ�
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
				//_pGamePlayer->Log("�õ�����PetId[%d] BigId[%I64u] ", PetItem.baseInfo.petId,  PetItem.baseInfo.guid );
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

    // �Ƿ�����˳�ս�ĳ���
    if ( _pPetItems[ nIndex ].baseInfo.isActive == AT_Active )
    {
        isActiveIndex   = true;
        _activeIndex    = -1;
    }

    if ( _pGamePlayer )
    { 
        SPetItem* pPet = &_pPetItems[ nIndex ];
        //_pGamePlayer->Log("ʧȥ����PetId[%d] Name[%s] BigId[%I64u]", pPet->baseInfo.petId, pPet->baseInfo.szName , pPet->baseInfo.guid );
		_pGamePlayer->Log(theXmlString.GetString(eServerLog_DelPet), pPet->baseInfo.petId, pPet->baseInfo.szName , pPet->baseInfo.guid );
    }

    // ɾ�����λ�õ���
    _pPetItems[ nIndex ].baseInfo.Reset();
    _pPetItems[ nIndex ].skillInfo.Reset();

    // ���� �������ǰ��
    for ( int i=nIndex, I=nIndex+1; i<_nPetCount; ++i, ++I )
    {  
        // ����Ѿ������������ ͨ��I���ж�
        if ( I >= _nPetCount )
        { break; }

        // ���i�Ѿ������һ���� ͨ��I���ж�
        if ( _pPetItems[I].baseInfo.petId == InvalidLogicNumber )
        { break; }

        _pPetItems[i] = _pPetItems[I];

        // ������ں��������
        _pPetItems[I].baseInfo.Reset();
        _pPetItems[I].skillInfo.Reset();
    }

    // ˢ��һ�� _activeIndex �п���ɾ���м�λ�õĳ��� λ������λ
    UpdateActiveIndex();

    return ER_Success;
}

long PetManager::PopPetByBigId( __int64 nBigId, bool& bActiveIndex )
{
    if ( _pPetItems == NULL || NULL == _pGamePlayer  )
    { return ER_Failed; }

    // �ҵ���ӦbigId���±�
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

    // ɾ������
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
	//��������ֻ�ܷ����Ե�Ӱ��
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

    // Я���ȼ�
    int petTakeLevel = PET_LEVEL_OVERTOP_MAX + thePetSettingConfig.GetSavvyAddTakeLevel( pCurrentPet->baseInfo.savvy );
    if ( nNewLevel > _pGamePlayer->GetLevel() + petTakeLevel  )
    { 
        nNewLevel = _pGamePlayer->GetLevel() + petTakeLevel;
        newExp    = theExpStage.GetPetLevelupExp( _pGamePlayer->GetLevel() + petTakeLevel );
    }
	//������ߵȼ�
	if(nNewLevel>thePetDefineConfig.GetMaxLevel())
	{
		nNewLevel = thePetDefineConfig.GetMaxLevel();
        newExp    = theExpStage.GetPetLevelupExp(thePetDefineConfig.GetMaxLevel());
	}
	if(newExp ==  pCurrentPet->baseInfo.exp)
		return false;
    pCurrentPet->baseInfo.exp = newExp;
    if ( nNewLevel != pCurrentPet->baseInfo.level )
    { // ����ı�

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

        // ��ֳ����
        //pCurrentPet->baseInfo.breedNum  = thePetSettingConfig.GetPetBreedNum( pCurrentPet->baseInfo.level );

        // ���¼�������
        //UpdatePetAttribute( *pCurrentPet );

        // ��������
        RealizePetSkill( *pCurrentPet , vecNewSkill );

        // ����ս����
        CalcBattleEffectiveness( *pCurrentPet );

        // ��������Ӱ��
        //ApplyPassiveSkillToPet( pCurrentPet );

        pCurrentPet->baseInfo.hp = pCurrentPet->baseInfo.GetFightAttribute( CharAttr_HPMax ) ;

        if ( nIndex == _activeIndex )
        { // ��ս�����������
            MonsterNurturePet* pNurturePet = (MonsterNurturePet*)GetMonsterNurturePet();
            if ( pNurturePet != NULL )
            { pNurturePet->UpdatePetData(); }

            UpdateActiveSkillBag();
        }

        if ( vecNewSkill.size() > 0 )
        {// ����ѧ�����µļ���
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

    // ���ͳ����þ���
    _pGamePlayer->ChangeAttr( CharAttr_ActivePetCurGetExp, iAddExp, true );

    // �·���Ϣ
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
        { // ��ս�����������
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

    // ���³�ս
    for ( int i=0; i<_nPetCount; ++i )
    {
        if ( _pPetItems[i].baseInfo.petId == InvalidLogicNumber )
            break;
        if ( _pPetItems[i].baseInfo.isActive == AT_Active )
        {
            _activeIndex = i;

            // ��ս�����������
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
				//��������ı������ܣ�����buff
				_pGamePlayer->ApplyPetAttrToChar(pPetSkill,true);
			}
		}
		_pGamePlayer->RefreshLieutenantAttr(false);
	}
	if(pActivePetItem/* && pActivePetItem->baseInfo.petType == EPT_Capture*/)
	{
		_pGamePlayer->GetCharInfo().otherdata.nsuanimalID = 0;//��¼��ս�ĸ���ID
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
		//�������ֶ���ص����ݶ���Ҫ  by liaojie  11.21
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
		_pGamePlayer->GetCharInfo().otherdata.nsuanimalID = 0;//��¼��ս�ĸ���ID
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
				//��������ı������ܣ�����buff
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

    // �±��Ƿ񳬳�
    if ( nIndex < 0 || nIndex >= _nPetCount )
    { return ER_IndexOutOfRange;}

    // ��λ�õ������Ƿ񲻴���
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
			//��������ı������ܣ��������Ե���������
			_pGamePlayer->ApplyPetAttrToChar(pPetSkill,false);
		}
	}
	//������ս�Ļ� ��¼ID
	if(pPet/* && pPet->baseInfo.petType == EPT_Capture*/)
	{
		_pGamePlayer->GetCharInfo().otherdata.nsuanimalID = pPet->GetPetGuid();//��¼��ս�ĸ���ID
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
    { // �м��������
        _accumulateActionTime += elapsTime; 
        _refreshLifeTime      += elapsTime;
        _refreshLoyaltyTime   += elapsTime;

        if ( _refreshLifeTime >= thePetSettingConfig.GetRefreshDurationTime() )
        {
            _refreshLifeTime = 0;
            if ( InvalidLogicNumber == _pPetItems[_activeIndex].baseInfo.petId )
            { return; }

            // ��ʼ�۳�������
			// ������ҵ�ָ�ӵ�
			_pGamePlayer->SetPetDuration(-1);

            //_pPetItems[_activeIndex].baseInfo.duration -= 1;
        }

		//��Ҫ���ֶ���  by liaojie 11.21
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

    //// �﹥
    //pet.baseInfo.fightAttribute[CharAttr_AttackPhysics] = ProcessCharInfo::PetBaseAttrToFightAttr( pet, CharAttr_AttackPhysics );

    //// ħ��
    //pet.baseInfo.fightAttribute[CharAttr_AttackMagic]   = ProcessCharInfo::PetBaseAttrToFightAttr( pet, CharAttr_AttackMagic );

    //// ���
    //pet.baseInfo.fightAttribute[CharAttr_DefendPhysics] = ProcessCharInfo::PetBaseAttrToFightAttr( pet, CharAttr_DefendPhysics );

    //// ħ��
    //pet.baseInfo.fightAttribute[CharAttr_DefendMagic]   = ProcessCharInfo::PetBaseAttrToFightAttr( pet, CharAttr_DefendMagic );

    //// ����
    //pet.baseInfo.fightAttribute[CharAttr_Exact]         = ProcessCharInfo::PetBaseAttrToFightAttr( pet, CharAttr_Exact );

    //// ����
    //pet.baseInfo.fightAttribute[CharAttr_Dodge]         = ProcessCharInfo::PetBaseAttrToFightAttr( pet, CharAttr_Dodge );

    //// ����
    //pet.baseInfo.fightAttribute[CharAttr_Critical]      = ProcessCharInfo::PetBaseAttrToFightAttr( pet, CharAttr_Critical );

    //// ����
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
    { // ��ս�����������
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

	//��ո�����Ǳ���� �����ж� �޸ĵĸ����Ƿ��ǵ�ǰ��ս�ĸ���
	if(GetActivePet() == pPet)
	{
		_pGamePlayer->RefreshLieutenantAttr(true);//��ǰ����һ�����ڳ�ս״̬
	}

	return true;
}
bool PetManager::RemovePetEquip(__int64 nBigId,int Index,int bagIndex)//��������װ�� ��������ָ��λ��
{
	if(Index >= SPetItem::PetEquip_MaxSum || Index <0)
		return false;//���ڷ�Χ��
	SPetItem * pPet = GetPetByGuid(nBigId);
	if(!pPet)
		return false;
	if(pPet != GetActivePet())
		return false;
	SCharItem* pItem = &pPet->baseInfo.PetEquip[Index];
	if(pItem->itembaseinfo.ustItemID == 0 || pItem->itembaseinfo.nOnlyInt == 0)
		return false;//��ǰλ������װ�� �޷�����
	if(bagIndex != -1)
	{
		SCharItem * pBagItem = _pGamePlayer->GetNormalBagPointerByIndex(bagIndex);
		if(!pBagItem || pBagItem->itembaseinfo.ustItemID != 0 || pBagItem->itembaseinfo.nOnlyInt != 0)
			return false;//Ŀ����λΪ��
		//��ʼ����װ��
		unsigned short CountSum = 1;
		//int nRes =_pGamePlayer->_NormalItemBag.PushItem(*pItem,CountSum,bagIndex);
		//���������װ��
		int nRes = _pGamePlayer->AddItemToBagByIndex(*pItem,bagIndex,CountSum);

		if ( nRes != ierr_Success )
			return false;
		else
		{
			//װ���Ѿ��ŵ������� ����ɾ���������ϵ�װ��
			if(pItem->petequipdata.isTimeEnd = true)
				pItem->petequipdata.isTimeEnd = false;
			memset( pItem,0, sizeof(SCharItem));//ֱ����������
			//���߿ͻ��� �����������Ѿ����ͱ仯��
			UpdateActionPetInfo(pPet);
			_pGamePlayer->RefreshLieutenantAttr(true);
			return true;
		}
	}		
	else
	{
		int Count = _pGamePlayer->GetNullItemCount(BT_NormalItemBag);
		if(Count <1)
			return false;//�����޿�λ�� �޷���װ��
		unsigned short CountSum = 1;
		int nRes = _pGamePlayer->AddItemToBag(*pItem,CountSum);
		if ( nRes != ierr_Success )
			return false;
		else
		{
			//װ���Ѿ��ŵ������� ����ɾ���������ϵ�װ��
			if(pItem->petequipdata.isTimeEnd = true)
				pItem->petequipdata.isTimeEnd = false;
			memset( pItem,0, sizeof(SCharItem));//ֱ����������
			UpdateActionPetInfo(pPet);
			_pGamePlayer->RefreshLieutenantAttr(true);
			return true;
		}
	}
	
}
bool PetManager::ChangePetEquip(__int64 nBigId,__int64 ItemOnlyID,int Index)
{
	//��������ָ��λ�õ���Ʒɾ���� ������������
	if(Index >= SPetItem::PetEquip_MaxSum || Index <0)
		return false;//���ڷ�Χ��
	SPetItem * pPet = GetPetByGuid(nBigId);
	if(!pPet)
		return false;
	if(pPet != GetActivePet())
		return false;
	//�жϱ�����װ���Ƿ����װ��
	SCharItem * pBagItem = _pGamePlayer->GetBagItemByGuid(ItemOnlyID);
	if(!pBagItem)
		return false;
	ItemDefine::SItemCommon *  pItemCommon =  theItemDetailConfig.GetItemByID(pBagItem->itembaseinfo.ustItemID);
	if(!pItemCommon)
		return false;//��Ʒ������
	if(pItemCommon->ucItemType != ItemDefine::ITEMTYPE_PETEQUIP)
		return false;//��Ʒ���Ͳ���ȷ
	ItemDefine::SItemPetEquip* pPetEquip = (ItemDefine::SItemPetEquip*)pItemCommon;
	int Level = pPetEquip->iEquipLevelReq;
	if(pPet->baseInfo.level < Level)
		return false;//�ȼ�����
	//�ж�λ��
	if(pPetEquip->iPos != Index)
		return false;
	if(pBagItem->petequipdata.isTimeEnd = true)
		pBagItem->petequipdata.isTimeEnd = false;
	if(pBagItem->IsOverdue())
		return false;//�Ѿ�����
	//unsigned int BagIndex = pBagItem->itembaseinfo.stPacketIdx;
	SCharItem* pItem = &pPet->baseInfo.PetEquip[Index];
	if(pItem->itembaseinfo.ustItemID != 0 && pItem->itembaseinfo.nOnlyInt != 0 /*&& !RemovePetEquip(nBigId,Index)*/)//����������װ�� ��������ʧ����
	{
		//���ǽ���װ������
		SCharItem pPetLogItem = pPet->baseInfo.PetEquip[Index];//��ʱ�����װ��
		pPet->baseInfo.PetEquip[Index] = *pBagItem;//ֱ�Ӹ��ƹ�ȥ
		//ɾ����������Ʒ
		if(!_pGamePlayer->RemoveBagItemByGuid(ItemOnlyID,pBagItem->GetItemCount()))
		{
			pPet->baseInfo.PetEquip[Index] = pPetLogItem;
			return false;
		}
		//��ָ����Ʒ��ӵ�����ȥ
		unsigned short CountSum = 1;		
		int nRes =_pGamePlayer->AddItemToBag(pPetLogItem,CountSum);
		if ( nRes != ierr_Success )
		{
			//���뱳��ʧ�� ���Ƿ����ʼ������ ���ҽ�װ�����Ӵ���
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
		//ֱ�Ӵ���װ��
		pPet->baseInfo.PetEquip[Index] = *pBagItem;//ֱ�Ӹ��ƹ�ȥ
		//ɾ����������Ʒ
		if(!_pGamePlayer->RemoveBagItemByGuid(ItemOnlyID,pBagItem->GetItemCount()))
		{
			memset( pItem,0, sizeof(SCharItem));
			return false;
		}
	}
	//����װ����
	if(pItemCommon->bIsCanBound)
		pPet->baseInfo.PetEquip[Index].SetBounded(true);
	UpdateActionPetInfo(pPet);
	_pGamePlayer->RefreshLieutenantAttr(true);
	return true;
}
void PetManager::UpdateActionPetInfo(SPetItem * pPet)
{
	//������������װ�� ��������װ����ʱ��  ������ͻ���ͬ������������
    // ����ս����
	if(!pPet)
		return;
    CalcBattleEffectiveness( *pPet );
    pPet->baseInfo.hp = pPet->baseInfo.GetFightAttribute( CharAttr_HPMax ) ;

    if(GetActivePet() == pPet)
    { // ��ս�����������
		_pGamePlayer->RefreshLieutenantAttr(true);

        MonsterNurturePet* pNurturePet = (MonsterNurturePet*)GetMonsterNurturePet();
        if ( pNurturePet != NULL )
        { pNurturePet->UpdatePetData(); }
        UpdateActiveSkillBag();
    }
    // �·���Ϣ
    MsgAddUpdatePet msg;
    msg.header.stID = _pGamePlayer->GetID();
    msg.pet = *pPet;
    msg.type = MsgAddUpdatePet::OT_Update;
    GettheServer().SendMsgToSingle( &msg, _pGamePlayer);
}
void PetManager::UpdatePetEquipTime()
{
	//�������и������ϵ�װ������ʵ
	//ֻ���³�ս�ĸ���������
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
			pPet->baseInfo.PetEquip[i].petequipdata.isTimeEnd = true;//������Ч��
			IsNeedUpdate = true;
		}
	}
	if(IsNeedUpdate)
	{ 
		MonsterNurturePet* pNurturePet = (MonsterNurturePet*)GetMonsterNurturePet();
        if ( pNurturePet != NULL )
			pNurturePet->UpdatePetData();//���¸���������
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
	//���µ�ǰ
	SPetItem* pPet = GetActivePet();
	if(!pPet)
		return;//�޳�ս�ĸ��������и���
	if(pPet->baseInfo.PetModeID == 0)
		return;
	if(pPet->baseInfo.PetModeID != pPet->baseInfo.GetPetNewModeID())
	{
		//SPetItem ���ͱ仯�� ������Ҫ�����µ�PetItem���ͻ���ȥ
		pPet->baseInfo.PetModeID = pPet->baseInfo.GetPetNewModeID();
		MsgAddUpdatePet msg;
		msg.header.stID = _pGamePlayer->GetID();
		msg.pet = *pPet;
		msg.type = MsgAddUpdatePet::OT_Update;
		GettheServer().SendMsgToSingle( &msg, _pGamePlayer);
		//������ģ�ͷ��ͱ仯��ʱ�� �����������úø�����ģ��ID
		MonsterNurturePet* pNurturePet = (MonsterNurturePet*)GetMonsterNurturePet();
        if ( pNurturePet != NULL )
        { 
			pNurturePet->UpdatePetMode(); 
		}
	}
}
void PetManager::ChangePetAtterValue(__int64 nBigId,__int64 TargetPetID)
{
	//�޸ĸ��������� ��Ʒ��  ����ģ�� ������ ����������޸�
	SPetItem * pPet = GetPetByGuid(nBigId);
	if(!pPet)
		return;
	SPetItem * pTargetPet = GetPetByGuid(TargetPetID);
	if(!pTargetPet ||  GetActivePet() == pTargetPet)
		return;
	//�޸ĸ���������
	//1.�ȼ��޸�
	pPet->baseInfo.level = pTargetPet->baseInfo.level;
	pPet->baseInfo.exp = pTargetPet->baseInfo.exp;
	//��������Ǳ�ܵ�
	for(int i =0;i<EBaseAttr_MaxSize;++i)
	{
		pPet->baseInfo.baseAttribute[i] = pTargetPet->baseInfo.baseAttribute[i];
		pPet->baseInfo.potentialAttribute[i] = pTargetPet->baseInfo.potentialAttribute[i];
	}
	pPet->baseInfo.nPotentialPoint = pTargetPet->baseInfo.nPotentialPoint;
	//2.����ָ�������ļ��� ��ͨ����ת�ƹ�ȥ
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
	//3����������
	pPet->baseInfo.savvy = pTargetPet->baseInfo.savvy;
	//ͬ�����Ե��ͻ���ȥ
	UpdateActionPetInfo(pPet);
	//�Ƴ�����ĸ���
	_pGamePlayer->RemovePetByGuid(TargetPetID);
}