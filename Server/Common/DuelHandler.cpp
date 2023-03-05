#include "DuelHandler.h"
#include "ShareData.h"
#include "MonsterBaseEx.h"
#include "GamePlayer.h"
#include "Configure.h"

CDuelHandler::CDuelHandler()
{
    m_mapDuelList.clear();
    m_mapReadyList.clear();
}

CDuelHandler::~CDuelHandler()
{
    m_mapDuelList.clear();
    m_mapReadyList.clear();
}

void CDuelHandler::Process()
{

}

bool CDuelHandler::CreateDuel(GameObjectId shInviteCharID, GameObjectId shTargetCharID)
{
    if(shInviteCharID == shTargetCharID)
        return false;
    // 得到邀请者
    BaseCharacter* pInviteChar = theRunTimeData.GetCharacterByID( shInviteCharID );
    if( !pInviteChar || !pInviteChar->IsPlayer() )
        return false;
    // 得到被邀请者
    BaseCharacter* pTargetChar = theRunTimeData.GetCharacterByID( shTargetCharID );
    if( !pTargetChar || !pTargetChar->IsPlayer())
        return  false;
    // 判断比武两者的地图
    if (pInviteChar->GetMapID() != pTargetChar->GetMapID())
    { return false; }

    //判断两者距离
    D3DXVECTOR3 vDist = pInviteChar->GetPos() - pTargetChar->GetPos();
    float fDistSq = D3DXVec3LengthSq( &vDist );

    if( fDistSq > fDuelLength * fDuelLength )
        return false;
    // 设置比武区域中心点
    D3DXVECTOR3 vCenter(0.0, 0.0, 0.0);
    vCenter.x = (pInviteChar->GetPos().x + pTargetChar->GetPos().x) / 2;
    vCenter.y = (pInviteChar->GetPos().y + pTargetChar->GetPos().y) / 2;
    // 保存决斗两人的信息
    DuelInfo info;
    info.shDuelCharID[0]    = shInviteCharID;
    info.shDuelCharID[1]    = shTargetCharID;
    info.strDuelCharName[0] = pInviteChar->GetCharName();
    info.strDuelCharName[1] = pTargetChar->GetCharName();
    info.nMapID             = pInviteChar->GetMapID();
    info.vPos               = vCenter;
    m_mapReadyList.insert(std::pair<short, DuelInfo>(shInviteCharID, info));

    info.shDuelCharID[0]    = shTargetCharID;
    info.shDuelCharID[1]    = shInviteCharID;
    info.strDuelCharName[0] = pTargetChar->GetCharName();
    info.strDuelCharName[1] = pInviteChar->GetCharName();
    info.nMapID             = pInviteChar->GetMapID();
    info.vPos               = vCenter;
    m_mapReadyList.insert(std::pair<short, DuelInfo>(shTargetCharID, info));

    //通知双方切磋开始
    MsgDuelStart start;
    start.vFlagPos = vCenter;

    start.shTargetID = shTargetCharID;
    GettheServer().SendMsgToSingle(&start, pInviteChar);    // 发给邀请者
    start.shTargetID = shInviteCharID;
    GettheServer().SendMsgToSingle(&start, pTargetChar);    // 发给被邀请者

    static_cast<GamePlayer*>(pInviteChar)->AddCharToFirstList(shTargetCharID);
    static_cast<GamePlayer*>(pTargetChar)->AddCharToFirstList(shInviteCharID);
    return true;
}

bool CDuelHandler::DuelReady(GameObjectId shReadyCharID, bool bExitGame /* = false */)
{
    bool bRemoveDuel = false;
    if(m_mapReadyList.find(shReadyCharID) != m_mapReadyList.end())
    {
        GamePlayer* pReadyPlayer = (GamePlayer*) theRunTimeData.GetCharacterByID(shReadyCharID);    // 玩家自己，邀请者
        if ( bExitGame || pReadyPlayer == NULL || 
            !pReadyPlayer->IsInMapArea(m_mapReadyList[shReadyCharID].nMapID, m_mapReadyList[shReadyCharID].vPos.x, m_mapReadyList[shReadyCharID].vPos.y, fDuelLength))
        {
            m_mapReadyList[shReadyCharID].bInArea = false;
        }

        m_mapReadyList[shReadyCharID].bReady = true;

        short shTarget = m_mapReadyList[shReadyCharID].shDuelCharID[1];
        GamePlayer* pTargetPlayer = (GamePlayer*) theRunTimeData.GetCharacterByID(shTarget);

        if( !m_mapReadyList[shReadyCharID].bInArea || m_mapReadyList[shTarget].bReady )
        {
            // 双方都准备好了。开始!
            m_mapDuelList.insert(std::pair<GameObjectId, DuelInfo>(shReadyCharID, m_mapReadyList[shReadyCharID]));
            m_mapDuelList.insert(std::pair<GameObjectId, DuelInfo>(shTarget, m_mapReadyList[shTarget]));

            bool bTargetInArea = m_mapReadyList[shTarget].bInArea;  // 目标是否在区域中
            bool bSelfInArea = m_mapReadyList[shReadyCharID].bInArea;   // 自己是否在区域中

            m_mapReadyList.erase(shReadyCharID);
            m_mapReadyList.erase(shTarget);

            if ( !bTargetInArea )            
            {// 对方已经不在范围内
                bRemoveDuel = RemoveDuel(shTarget);
            }
            else if ( !bSelfInArea )   
            {// 对方在范围内,自己不在范围内
                bRemoveDuel = RemoveDuel(shReadyCharID);
            }
        }
    }

    return bRemoveDuel;
}

void CDuelHandler::RemovePlayer( BaseCharacter* pChar, BaseCharacter* pTarget, MsgDuelEnd* pEnd, GameObjectId shCharID, DWORD dwTime, bool bIsSelf )
{
    GamePlayer* pPlayer = static_cast< GamePlayer* >(pChar);
    if ( bIsSelf )  // 如果是玩家自己，则移除目标的仇恨列表
    { pPlayer->RemoveEnmity( m_mapDuelList[shCharID].shDuelCharID[1] ); }
    else    // 如果是目标，则移除自己对目标的仇恨列表
    { pPlayer->RemoveEnmity( m_mapDuelList[shCharID].shDuelCharID[0] ); }

    if ( pPlayer->HaveSummonPet() )
    {
        for ( int i = 0; i < CharSummonPetMaxCount; ++i )
        {
            SSummonPet* pMonster = pPlayer->GetSummonPet(i);
            if ( NULL == pMonster )
            { continue; }

            BaseCharacter* pPet = theRunTimeData.GetCharacterByID( pMonster->petId );
            if ( pPet && pPet->IsMonster() )
            {
                if (bIsSelf)
                { pPet->RemoveEnmity(m_mapDuelList[shCharID].shDuelCharID[1]); }
                else
                { pPet->RemoveEnmity(m_mapDuelList[shCharID].shDuelCharID[0]); }

                MonsterBaseEx* pPetMonster = static_cast< MonsterBaseEx* >( pPet );
                pPetMonster->SetAiStatus( AiDefine::ThinkingMoveToMaster );

                if (pTarget != NULL)
                { pTarget->RemoveEnmity(pPet->GetID()); }
            }
        }
    }
    else if ( pPlayer->HaveCapturePet() )
    {
        BaseCharacter* pPet = theRunTimeData.GetCharacterByID( pPlayer->GetCapturePetId() );
        if ( pPet && pPet->IsMonster() )
        {
            if (bIsSelf)
            { pPet->RemoveEnmity( m_mapDuelList[shCharID].shDuelCharID[1] ); }
            else
            { pPet->RemoveEnmity( m_mapDuelList[shCharID].shDuelCharID[0] ); }
            
            MonsterBaseEx* pPetMonster = static_cast< MonsterBaseEx* >( pPet );
            pPetMonster->SetAiStatus( AiDefine::ThinkingMoveToMaster );

            if (pTarget != NULL)
            { pTarget->RemoveEnmity(pPet->GetID()); }
        }
    }
    else if ( pPlayer->_petManager.HaveActivePet() )
    {
        BaseCharacter* pPet = theRunTimeData.GetCharacterByID( pPlayer->_petManager.GetActivePetCharId() );
        if ( pPet && pPet->IsMonster() )
        {
            if (bIsSelf)
            { pPet->RemoveEnmity( m_mapDuelList[shCharID].shDuelCharID[1] ); }
            else
            { pPet->RemoveEnmity( m_mapDuelList[shCharID].shDuelCharID[0] ); }
            
            MonsterBaseEx* pPetMonster = static_cast< MonsterBaseEx* >( pPet );
            pPetMonster->SetAiStatus( AiDefine::ThinkingMoveToMaster );

            if (pTarget != NULL)
            { pTarget->RemoveEnmity(pPet->GetID()); }
        }
    }
     

    // 结束技能
    pPlayer->CancelSkill();

    // 清除比武时给予的状态
    if (bIsSelf)
    { pPlayer->_buffManager.ClearBuffByMasterCharID(m_mapDuelList[shCharID].shDuelCharID[1]); }
    else
    { pPlayer->_buffManager.ClearBuffByMasterCharID(m_mapDuelList[shCharID].shDuelCharID[0]); }

    //pPlayer->_buffManager.ApplyBuffsToChar( pPlayer->GetProfession(), pPlayer->GetCharBaseAttr(), pPlayer->GetCharFightAttr() );
    pPlayer->ApplyBuffStatusToCharAttr();
    pPlayer->UpdateCharAllAttibute();
    pPlayer->SendCharAttibuteToClient(); 
    pPlayer->SendMessageToClient( pEnd );

    if (bIsSelf)
    { pPlayer->RemoveCharToFirstList(m_mapDuelList[shCharID].shDuelCharID[1]); }
    else
    { pPlayer->RemoveCharToFirstList(m_mapDuelList[shCharID].shDuelCharID[0]); }

    // PK完之后加一个5秒无敌的状态
    pPlayer->ApplyBufferStatus  ( g_Cfg.nProtectStatusId, g_Cfg.nProtectStatusLevel, pPlayer->GetID(), SCharBuff::StatusEventType_Other, 0 );
    pPlayer->OnBuffStatusChanged( true );

    //pPlayer->SetProtectTime(dwTime);
}

bool CDuelHandler::RemoveDuel( GameObjectId shCharID, bool bRecvStopMessage /* = true */)
{
    // 切服或者下线了, 还没有开始的话, 给他准备状态
    if ( DuelReady(shCharID, !bRecvStopMessage) )
    { return true; }

    //如果还没有开始状态,
    if( m_mapDuelList.find(shCharID) == m_mapDuelList.end() )
    { return false; }  

    MsgDuelEnd end;
    end.shWinCharID = m_mapDuelList[shCharID].shDuelCharID[1];
    end.shLostCharID = m_mapDuelList[shCharID].shDuelCharID[0];
    GettheServer().SendMsgToView( &end, shCharID, true );

    BaseCharacter* pChar   = theRunTimeData.GetCharacterByID( shCharID );
    BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( m_mapDuelList[shCharID].shDuelCharID[1] );
    if ( pTarget == NULL || pChar == NULL )
    { return false; }

    uint32 nCurrentTime = HQ_TimeGetTime();
    RemovePlayer( pChar, pTarget, &end, shCharID, nCurrentTime, true );   // 自己
    RemovePlayer( pTarget, pChar, &end, shCharID, nCurrentTime, false );  // 目标

    m_mapDuelList.erase(end.shWinCharID);
    m_mapDuelList.erase(end.shLostCharID);

    return true;
}

void CDuelHandler::OutDuleRange(GameObjectId shCharID)
{
    if( m_mapDuelList.find(shCharID) == m_mapDuelList.end() )
        return;

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID(shCharID);
    if(!pChar)
        return;

    D3DXVECTOR3 vPos = pChar->GetPos();
    vPos.z = 0.0f;

    D3DXVECTOR3 vDist = vPos - m_mapDuelList[shCharID].vPos;
    float fDistSq = D3DXVec3LengthSq( &vDist );

    if( fDistSq < fDuelLength * fDuelLength )
        return;

    RemoveDuel(shCharID);
}

bool CDuelHandler::IsDuelFight(GameObjectId shAttackID, GameObjectId shTargetID)
{
    if( m_mapDuelList.find(shAttackID) == m_mapDuelList.end() )
        return false;

    if(m_mapDuelList[shAttackID].shDuelCharID[1] == shTargetID)
        return true;

    return false;
}

bool CDuelHandler::IsInDuel(GameObjectId shCharID)
{
    if( m_mapDuelList.find(shCharID) != m_mapDuelList.end() )
        return true;

    if( m_mapReadyList.find(shCharID) != m_mapReadyList.end() )
        return true; 

    return false;
}

CDuelHandler* theDuelHandler()
{
    static CDuelHandler duelhandler;
    return &duelhandler;
}
