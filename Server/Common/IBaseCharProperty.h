/********************************************************************
    Filename:    BaseCharProperty.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_IBASECHARPROPERTY_H__
#define __COMMON_IBASECHARPROPERTY_H__

#pragma once

#include "GameDefineChar.h"
#include "GlobalDef.h"

#pragma warning(disable:4018)

#pragma pack( push, 1 )
/* 
 * 定义了角色基类属性操作接口(不是纯正意义上的接口类)
 * 目的是将属性数据留到派生具体类去声明。保证数据不冗余
 * 如果所有派生类都有的数据就直接声明在接口基类
 */
class IBaseCharProperty
{
public:
    IBaseCharProperty();
    virtual ~IBaseCharProperty();
    
    // 战斗属性
    virtual SCharFightAttr* GetCharFightAttr() = 0;

    // 血最大
    virtual void   SetHPMax( uint32 hpMax ) = 0;
    virtual uint32 GetHPMax()               = 0;

    // 能量最大
    virtual void   SetMPMax( uint32 mpMax ){}
    virtual uint32 GetMPMax(){ return 0; }

    // 等级
    void   SetLevel( uint16 level ) { _level = level; }
    uint16 GetLevel()               { return _level;  }

    // 血
    virtual void   SetHP( int hp );
    virtual int    GetHP() { return _hp; }
    virtual void   OperateHP( uint8 uchOperateType, int nValue );

    // 能量
    virtual void   SetMP( int mp ) {}
    virtual int    GetMP() { return 0; }
    virtual void   OperateMP( uint8 uchOperateType, int nValue ) {};

    // 名字
    virtual void        SetCharName( const char* szName );
    virtual const char* GetCharName() { return _charName; }

    // 角色的类型
    virtual void   SetObjType( uint16 type ) { _objType = type; }
    virtual uint16 GetObjType()              { return _objType; }

    // 玩家的体形
    virtual int16 GetBodyType()           { return _bodyType; }
    virtual void  SetBodyType( int16 bodyType );

    // 角色种族
    virtual unsigned char GetPhyle() const { return EPhyle_Human; }

    // 八方向
    virtual void SetDir( int8 eDir ) { _eDir = eDir; }
    virtual int8 GetDir()            { return _eDir; }

    // X方向
    void  SetDirX( float fDir ) { _fDirX = fDir; }
    float GetDirX()             { return _fDirX; }
    int8  GetDirXC()            { return (int8)(GetDirX()*127); }

    // Y方向
    void  SetDirY( float Dir ) { _fDirY = Dir; }
    float GetDirY()            { return _fDirY; }
    int8  GetDirYC()           { return (int8)(GetDirY()*127); }

    // Z方向
    int   GetDirZC()           { return 0; }

    // 移动速度
    virtual float GetMoveSpeed(){ return 0.0f; };
    virtual void  SetMoveSpeed( float fMoveSpeed ){}

    // 模型
    virtual void   SetModelId( uint16 nId ) { _modelId = nId; }
    virtual uint16 GetModelId()             { return _modelId; }

    // 动作
    virtual void  SetActionId( int16 actionId ){ _actionId = actionId; }
    virtual short GetActionId(){ return _actionId; }

    // 区块
    virtual int32 GetCurArea()                { return _curArea;    } // 当前所在的区块...9宫格的区块 
    virtual void  SetCurArea( int32 curArea ) { _curArea = curArea; }

    virtual void  SetResistBeMove( int16 value ){}
    virtual int16 GetResistBeMove(){ return 0;}

    virtual void  SetResistBeAtt( int16 value ){}
    virtual int16 GetResistBeAtt(){ return 0; }

    virtual void  SetResistBeMagic( int16 value ){}
    virtual int16 GetResistBeMagic(){ return 0;}

    virtual void  SetResistBeTools( int16 value ){}
    virtual int16 GetResistBeTools(){ return 0;}

    // 道行
    virtual void   SetDaoxing( int32 value ) {}
    virtual uint32 GetDaoxing() { return 0; }

    // 位置
    // 地图
    virtual uint32 GetMapID() const           { return _pos.dwMapID; }    // 当前所在的地图编号
    virtual void   SetMapID( uint32 dwMapID ) { _pos.dwMapID = dwMapID; } // 设置数据接口函数

    D3DXVECTOR3 GetPos(){ return _pos.vPos; }

    void  SetTileX( int16 tileX, bool bFixWorldCoordinate = true );
    void  SetTileY( int16 tileY, bool bFixWorldCoordinate = true );
    int16 GetTileX()      const { return _pos.stX; }
    int16 GetTileY()      const { return _pos.stY; }

    void  SetFloatXF( float x ){ _pos.vPos.x = x; _pos.stX = FloatToTile( x ); }
    void  SetFloatYF( float y ){ _pos.vPos.y = y; _pos.stY = FloatToTile( y ); }    
    void  SetFloatX( float x ) { _pos.vPos.x = x;                              }
    void  SetFloatY( float y ) { _pos.vPos.y = y;                              }
    void  SetFloatZ( float z ) { _pos.vPos.z = z;                              }

    float GetFloatX() const    { return _pos.vPos.x;                           }
    float GetFloatY() const    { return _pos.vPos.y;                           }
    float GetFloatZ() const    { return _pos.vPos.z;                           }

protected:
    uint16        _level                       ; // 等级
    int           _hp                          ; // 血量
    int8          _charName[ dr_MaxPlayerName ]; // 角色名
    uint16        _objType                     ; // 角色的类型
    int16         _bodyType                    ; // 体形
    int8          _eDir                        ; // 方向
    float         _fDirX                       ; // X方向
    float         _fDirY                       ; // Y方向
    uint16        _modelId                     ; // 模型ID
    int16         _actionId                    ; // 当前动作，在entermysight的时候有用
    int32         _curArea                     ; // 当前所在的区块
    int32         _rewardExp                   ; // 死亡给别人的经验值
    int32         _killSkillExp                ; // 死亡给别人的技能经验值
    SCharPosData  _pos                         ; // 玩家的位置
};

//////////////////////////////////////////////////////////////////////////
// inline
inline void IBaseCharProperty::SetBodyType( int16 bodyType ) 
{ 
    if( bodyType < 0 || bodyType >= BODYTYPE_MAX )
    { return; }
    _bodyType = bodyType; 
}

inline void IBaseCharProperty::SetTileX( int16 tileX, bool bFixWorldCoordinate/* = true */)
{ 
    _pos.stX = tileX;
    if ( bFixWorldCoordinate )
    { _pos.vPos.x = TileToFloat( tileX );  }
}

inline void IBaseCharProperty::SetTileY( int16 tileY, bool bFixWorldCoordinate/* = true */)             
{   
    _pos.stY = tileY;
    if ( bFixWorldCoordinate )
    { _pos.vPos.y = TileToFloat( tileY );  }
}

//////////////////////////////////////////////////////////////////////////
// Player对应接口的数据结构
class DPlayerChar
{
public:
    DPlayerChar();

protected:
    SCharBuff _buffs[BodyStatusType_Max]   ; // 人物身上能有的状态,记录数据
};

//////////////////////////////////////////////////////////////////////////
// NpcNormal对应接口的数据结构
class DNpcNormalChar
{
public:
    DNpcNormalChar();

protected:
    uint32 _hpMax; // 血最大
    float  _speed; // 移动速度
};

//////////////////////////////////////////////////////////////////////////
// NpcAI对应接口的数据结构
class DNpcFightChar
{
public:
    DNpcFightChar();

protected:
    SBaseProperty _baseProperty;
    SCharBuff     _buffs[BodyStatusType_Max]   ; // 人物身上能有的状态,记录数据
};

//////////////////////////////////////////////////////////////////////////
// Item对应接口的数据结构
class DItemChar
{
public:
    DItemChar();

protected:
    uint32 _hpMax; // 血最大
};

//////////////////////////////////////////////////////////////////////////
// MonsterAI对应接口的数据结构
class AICharAttribute
{
public:
    AICharAttribute();

protected:
    SBaseProperty _baseProperty    ;
    int           _nMp             ;
    SCharBuff     _buffs[BodyStatusType_Max]   ; // 人物身上能有的状态,记录数据
};

// Effect对应接口的数据结构
class DEffectChar
{
public:
    DEffectChar();

protected:
    uint32 _hpMax; // 血最大
};

//////////////////////////////////////////////////////////////////////////
// BuildChar对应接口的数据结构
class DBuildChar
{
public:
    DBuildChar();

protected:
    uint32 _hpMax; // 血最大
};

#pragma pack( pop )

#endif // __COMMON_BASECHARPROPERTYI_H__
