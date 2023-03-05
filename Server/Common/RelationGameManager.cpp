#include "RelationManager.h"
#include "GamePlayer.h"
#include "RelationMessage.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

template<>
void RelationManager< GameRelation >::SendRegisterRelation( unsigned int nPlayerID, unsigned int ustRelation )
{
    GamePlayer* pPlayer = GameRelation::GetPlayer( nPlayerID );
    if ( pPlayer == NULL )
    { return; }

    MsgRegisterRelationList xList;
    xList.ustRelation = ustRelation;

    IDSetIter begin;
    IDSetIter end;
    switch( ustRelation )
    {
    case RelationDefine::Teacher:
        {
            begin = m_setTeacherID.begin();
            end   = m_setTeacherID.end();
        }
        break;
    case RelationDefine::Student:
        {
            begin = m_setStudentID.begin();
            end   = m_setStudentID.end();
        }
        break;
    default:
        return;
    }

    for ( ; begin != end; ++begin )
    {
        GameRelation* pRelation = GetPlayerRelation( *begin );
        if ( pRelation == NULL )
        { continue; }

        xList.AddAttribute( *pRelation );
    }

    pPlayer->SendMessageToClient( &xList );
}