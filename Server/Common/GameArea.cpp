#include "GameArea.h"
#include "ShareData.h"

#if 0
GameArea::GameArea()
{
    m_nAroundAreaCount = 0;
    memset( m_nAroundAreaId, 0x00, sizeof(m_nAroundAreaId) );
}

GameArea::~GameArea()
{

}

bool GameArea::CharacterEnter( uint32 dwID, bool bPlayer )
{ // ��ɫ����
    return m_CharacterTable.Add( dwID, bPlayer );
}

bool GameArea::CharacterLeave( uint32 dwID, bool bPlayer )
{ // ��ɫ�뿪
    int i = m_CharacterTable.Find( dwID );
    if( i == -1 )
    { return false; }

    return m_CharacterTable.Del( i, bPlayer );
}

bool GameArea::SendAllInfoToChar( uint32 dwID )
{ // �������˵Ļ�����Ϣ���͸��ý�ɫ
    int iMax = m_CharacterTable.Count();
    BaseCharacter* pDst = theRunTimeData.GetCharacterByID(dwID);
    if( NULL == pDst)
    { return false; }

    for( int i=0; i<iMax; ++i )
    {
        uint32 ccID = m_CharacterTable[i];
        if( ccID == dwID )
        { continue; }

        BaseCharacter* pChar = theRunTimeData.GetCharacterByID(ccID);
        if( NULL == pChar)
        {
            // ����Ҳ�������б����Ƴ�
            if ( ccID < dr_worldMaxPlayers)
            { m_CharacterTable.Del( i, TRUE );  }
            else
            { m_CharacterTable.Del( i, FALSE ); }

            --iMax;
            --i;
            continue;
        }

        pDst->EnterMySight( pChar );
        pChar->EnterMySight( pDst ); 
    }
    return true;
}

bool GameArea::AllLeaveFromCharSight( uint32 dwID )
{ // �������뿪ĳ����Ұ
    int iMax = m_CharacterTable.Count();
    BaseCharacter* pDst = theRunTimeData.GetCharacterByID(dwID);
    if( NULL == pDst)
    { return false; }

    for( int i=0; i<iMax; i++ )
    {
        uint32 ccID = m_CharacterTable[i];
        if( ccID == dwID )
        { continue; }

        BaseCharacter* pChar = theRunTimeData.GetCharacterByID(ccID);
        if( NULL == pChar )
        {
            // ����Ҳ�������б����Ƴ�
            if ( ccID < dr_worldMaxPlayers)
            { m_CharacterTable.Del( i, TRUE );  }
            else
            { m_CharacterTable.Del( i, FALSE ); }

            --iMax;
            --i;
            continue;
        }

        pDst->ExitMySight( pChar );
        pChar->ExitMySight( pDst );
    }
    return true;
}


bool GameArea::SendSpecialInfoToChar( DWORD dwID, uint8 eLimitType )
{ // ��ָ������Ϣ���͸��ý�ɫ
    int iMax = m_CharacterTable.Count();
    BaseCharacter *pDst = (BaseCharacter*)theRunTimeData.GetCharacterByID(dwID);
    if(!pDst)
    {
        G_ASSERT_RET( false, false );
        return false;
    }

    for( int i=0; i<iMax; i++ )
    {
        DWORD ccID = m_CharacterTable[i];
        if( ccID == dwID )
            continue;
        BaseCharacter * pChar = (BaseCharacter*)theRunTimeData.GetCharacterByID(ccID);
        if(!pChar)
        {	
            continue;
        }

        //������ָ�����͵Ľ�ɫ
        if( pChar->GetObjType( ) != eLimitType )
            continue;

        pDst->EnterMySight( pChar ); 
        pChar->EnterMySight( pDst ); 
    }

    return true;
}

bool GameArea::SpecialInfoLeaveFromCharSight( DWORD dwID, uint8 eLimitType )
{ // ָ����Ϣ�뿪��ɫ
    int iMax = m_CharacterTable.Count();
    BaseCharacter *pDst = (BaseCharacter*)theRunTimeData.GetCharacterByID(dwID);
    if(!pDst)
    {
        // ToLog( false);
        return false;
    }

    for( int i=0; i<iMax; i++ )
    {
        DWORD ccID = m_CharacterTable[i];
        if( ccID == dwID )
            continue;
        BaseCharacter * pChar = (BaseCharacter*)theRunTimeData.GetCharacterByID(ccID);
        if( !pChar )
        {
            // ToLog( false );
            continue;
        }

        //������ָ�����͵Ľ�ɫ
        if( pChar->GetObjType( ) != eLimitType )
            continue;

        pDst->ExitMySight( pChar );
        pChar->ExitMySight( pDst ); 
    }
    return true;
}

void GameArea::AddAroundArea( int x, int y, int l, int h )
{
    if( !( x < 0 || x >= l || y < 0 || y >= h ) )
    {
        if( m_nAroundAreaCount >= 0 && m_nAroundAreaCount < GAME_MAXAROUNDAREANUMBER )
        {
            m_nAroundAreaId[m_nAroundAreaCount] = y*l+x;
            m_nAroundAreaCount++;
        }
    }
}

#else

GameArea::GameArea()
{
    m_nAroundAreaCount = 0;
    memset( m_nAroundAreaId, 0x0, sizeof(m_nAroundAreaId) );
}

GameArea::~GameArea()
{
}

bool GameArea::CharacterEnter( GameObjectId dwID, bool bPlayer )
{
    if ( bPlayer )
    { _playerIds.insert( dwID ); }

    return _objectIds.insert( dwID ).second;
}

bool GameArea::CharacterLeave( GameObjectId dwID, bool bPlayer )
{
    if ( bPlayer )
    { _playerIds.erase( dwID ); }

    GameObjectIDSetItr it = _objectIds.find( dwID );
    if ( it != _objectIds.end())
    { 
        _objectIds.erase( it ); 
        return true;
    }

    return false;
}

bool GameArea::SendAllInfoToChar( GameObjectId dwID )
{ // �������˵Ļ�����Ϣ���͸��ý�ɫ
    BaseCharacter* pDst = theRunTimeData.GetCharacterByID( dwID );
    if( NULL == pDst)
    { return false; }

    GameObjectIDSetItr it = _objectIds.begin();
    for ( ; it!=_objectIds.end(); )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( *it );
        if( NULL == pChar)
        {
            it = _objectIds.erase( it );
            continue;
        }
        // ����Լ���Ŀ�겻ͬ
        if ( pChar->GetID() != pDst->GetID() )
        {
            pDst->EnterMySight( pChar );
            pChar->EnterMySight( pDst );
        }
        ++it;
    }
    return true;
}

bool GameArea::AllLeaveFromCharSight( GameObjectId dwID )
{ // �������뿪ĳ����Ұ
    BaseCharacter* pDst = theRunTimeData.GetCharacterByID( dwID );
    if( NULL == pDst)
    { return false; }

    GameObjectIDSetItr it = _objectIds.begin();
    for ( ; it!=_objectIds.end(); )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( *it );
        if( NULL == pChar)
        {
            it = _objectIds.erase( it );
            continue;
        }

        pDst->ExitMySight( pChar );
        pChar->ExitMySight( pDst );
        ++it;
    }

    return true;
}

bool GameArea::SendSpecialInfoToChar( GameObjectId dwID, uint8 eLimitType )
{ // ��ָ������Ϣ���͸��ý�ɫ
    BaseCharacter* pDst = theRunTimeData.GetCharacterByID(dwID);
    if( pDst == NULL )
    { return false; }

    GameObjectIDSetItr it = _objectIds.begin();
    for ( ; it!=_objectIds.end(); )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( *it );
        if( NULL == pChar)
        {
            it = _objectIds.erase( it );
            continue;
        }

        if( pChar->GetObjType() != eLimitType )
        { continue; }

        pDst->EnterMySight( pChar );
        pChar->EnterMySight( pDst );
        ++it;
    }

    return true;
}

bool GameArea::SpecialInfoLeaveFromCharSight( GameObjectId dwID, uint8 eLimitType )
{ // ָ����Ϣ�뿪��ɫ    
    BaseCharacter* pDst = theRunTimeData.GetCharacterByID(dwID);
    if( pDst == NULL )
    { return false; }

    GameObjectIDSetItr it = _objectIds.begin();
    for ( ; it!=_objectIds.end(); )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( *it );
        if( NULL == pChar)
        {
            it = _objectIds.erase( it );
            continue;
        }

        if( pChar->GetObjType() != eLimitType )
        { continue; }

        pDst->ExitMySight( pChar );
        pChar->ExitMySight( pDst );
        ++it;
    }

    return true;
}

GameObjectId GameArea::GetNextObjectBId( bool bFirst )
{
    if ( bFirst )
    { _cur = _objectIds.begin(); }

    if ( _cur != _objectIds.end() )
    { 
        GameObjectId result = *_cur;
        ++_cur;
        return result; 
    }

    return InvalidGameObjectId;
}

void GameArea::AddAroundArea( int x, int y, int l, int h )
{
    if( !( x < 0 || x >= l || y < 0 || y >= h ) )
    {
        if( m_nAroundAreaCount >= 0 && m_nAroundAreaCount < GAME_MAXAROUNDAREANUMBER )
        {
            m_nAroundAreaId[m_nAroundAreaCount] = y*l+x;
            m_nAroundAreaCount++;
        }
    }
}

#endif