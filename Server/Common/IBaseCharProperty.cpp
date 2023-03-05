#include "IBaseCharProperty.h"

IBaseCharProperty::IBaseCharProperty()
{
    _level = 0;
    _hp    = 0;
    memset( _charName, 0, sizeof(_charName));
    _objType = Object_Dump;
    _bodyType = 0;
    _eDir     = 0;
    _fDirX    = 0;
    _fDirY    = 0;
    _modelId  = 0;
    _actionId = -1;
    _curArea  = -1;
    _rewardExp = 0;
    _killSkillExp = 0;
}

IBaseCharProperty::~IBaseCharProperty()
{
}

void IBaseCharProperty::SetHP( int hp )
{
    if ( hp > GetHPMax() )
    { _hp = GetHPMax(); }
    else
    { _hp = hp; }
}

void IBaseCharProperty::OperateHP( uint8 uchOperateType, int nValue )
{
    if ( nValue == 0 && uchOperateType != EOT_Set )
    { return; }

    switch ( uchOperateType )
    {
    case EOT_Add:
        { _hp += nValue; }
        break;
    case EOT_Sub:
        { _hp -= nValue; }
        break;
    case EOT_Set:
        { _hp = nValue; }
        break;
    default:
        return;
        break;
    }

    if ( _hp < 0)
    { _hp = 0; }

    if ( _hp > GetHPMax() )
    { _hp = GetHPMax(); }
}

void IBaseCharProperty::SetCharName( const char* szName )
{
    strncpy_s( _charName, sizeof(_charName), szName , sizeof( _charName) - 1);
}
//////////////////////////////////////////////////////////////////////////
DPlayerChar::DPlayerChar()
{
}

//////////////////////////////////////////////////////////////////////////
DNpcNormalChar::DNpcNormalChar()
{

}

//////////////////////////////////////////////////////////////////////////
DNpcFightChar::DNpcFightChar()
{

}

//////////////////////////////////////////////////////////////////////////
DItemChar::DItemChar()
{

}

//////////////////////////////////////////////////////////////////////////
AICharAttribute::AICharAttribute()
{
    _nMp              = 0;
}

//////////////////////////////////////////////////////////////////////////
DEffectChar::DEffectChar()
{

}

//////////////////////////////////////////////////////////////////////////
DBuildChar::DBuildChar()
{

}