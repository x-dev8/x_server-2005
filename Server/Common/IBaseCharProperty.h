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
 * �����˽�ɫ�������Բ����ӿ�(���Ǵ��������ϵĽӿ���)
 * Ŀ���ǽ�����������������������ȥ��������֤���ݲ�����
 * ������������඼�е����ݾ�ֱ�������ڽӿڻ���
 */
class IBaseCharProperty
{
public:
    IBaseCharProperty();
    virtual ~IBaseCharProperty();
    
    // ս������
    virtual SCharFightAttr* GetCharFightAttr() = 0;

    // Ѫ���
    virtual void   SetHPMax( uint32 hpMax ) = 0;
    virtual uint32 GetHPMax()               = 0;

    // �������
    virtual void   SetMPMax( uint32 mpMax ){}
    virtual uint32 GetMPMax(){ return 0; }

    // �ȼ�
    void   SetLevel( uint16 level ) { _level = level; }
    uint16 GetLevel()               { return _level;  }

    // Ѫ
    virtual void   SetHP( int hp );
    virtual int    GetHP() { return _hp; }
    virtual void   OperateHP( uint8 uchOperateType, int nValue );

    // ����
    virtual void   SetMP( int mp ) {}
    virtual int    GetMP() { return 0; }
    virtual void   OperateMP( uint8 uchOperateType, int nValue ) {};

    // ����
    virtual void        SetCharName( const char* szName );
    virtual const char* GetCharName() { return _charName; }

    // ��ɫ������
    virtual void   SetObjType( uint16 type ) { _objType = type; }
    virtual uint16 GetObjType()              { return _objType; }

    // ��ҵ�����
    virtual int16 GetBodyType()           { return _bodyType; }
    virtual void  SetBodyType( int16 bodyType );

    // ��ɫ����
    virtual unsigned char GetPhyle() const { return EPhyle_Human; }

    // �˷���
    virtual void SetDir( int8 eDir ) { _eDir = eDir; }
    virtual int8 GetDir()            { return _eDir; }

    // X����
    void  SetDirX( float fDir ) { _fDirX = fDir; }
    float GetDirX()             { return _fDirX; }
    int8  GetDirXC()            { return (int8)(GetDirX()*127); }

    // Y����
    void  SetDirY( float Dir ) { _fDirY = Dir; }
    float GetDirY()            { return _fDirY; }
    int8  GetDirYC()           { return (int8)(GetDirY()*127); }

    // Z����
    int   GetDirZC()           { return 0; }

    // �ƶ��ٶ�
    virtual float GetMoveSpeed(){ return 0.0f; };
    virtual void  SetMoveSpeed( float fMoveSpeed ){}

    // ģ��
    virtual void   SetModelId( uint16 nId ) { _modelId = nId; }
    virtual uint16 GetModelId()             { return _modelId; }

    // ����
    virtual void  SetActionId( int16 actionId ){ _actionId = actionId; }
    virtual short GetActionId(){ return _actionId; }

    // ����
    virtual int32 GetCurArea()                { return _curArea;    } // ��ǰ���ڵ�����...9��������� 
    virtual void  SetCurArea( int32 curArea ) { _curArea = curArea; }

    virtual void  SetResistBeMove( int16 value ){}
    virtual int16 GetResistBeMove(){ return 0;}

    virtual void  SetResistBeAtt( int16 value ){}
    virtual int16 GetResistBeAtt(){ return 0; }

    virtual void  SetResistBeMagic( int16 value ){}
    virtual int16 GetResistBeMagic(){ return 0;}

    virtual void  SetResistBeTools( int16 value ){}
    virtual int16 GetResistBeTools(){ return 0;}

    // ����
    virtual void   SetDaoxing( int32 value ) {}
    virtual uint32 GetDaoxing() { return 0; }

    // λ��
    // ��ͼ
    virtual uint32 GetMapID() const           { return _pos.dwMapID; }    // ��ǰ���ڵĵ�ͼ���
    virtual void   SetMapID( uint32 dwMapID ) { _pos.dwMapID = dwMapID; } // �������ݽӿں���

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
    uint16        _level                       ; // �ȼ�
    int           _hp                          ; // Ѫ��
    int8          _charName[ dr_MaxPlayerName ]; // ��ɫ��
    uint16        _objType                     ; // ��ɫ������
    int16         _bodyType                    ; // ����
    int8          _eDir                        ; // ����
    float         _fDirX                       ; // X����
    float         _fDirY                       ; // Y����
    uint16        _modelId                     ; // ģ��ID
    int16         _actionId                    ; // ��ǰ��������entermysight��ʱ������
    int32         _curArea                     ; // ��ǰ���ڵ�����
    int32         _rewardExp                   ; // ���������˵ľ���ֵ
    int32         _killSkillExp                ; // ���������˵ļ��ܾ���ֵ
    SCharPosData  _pos                         ; // ��ҵ�λ��
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
// Player��Ӧ�ӿڵ����ݽṹ
class DPlayerChar
{
public:
    DPlayerChar();

protected:
    SCharBuff _buffs[BodyStatusType_Max]   ; // �����������е�״̬,��¼����
};

//////////////////////////////////////////////////////////////////////////
// NpcNormal��Ӧ�ӿڵ����ݽṹ
class DNpcNormalChar
{
public:
    DNpcNormalChar();

protected:
    uint32 _hpMax; // Ѫ���
    float  _speed; // �ƶ��ٶ�
};

//////////////////////////////////////////////////////////////////////////
// NpcAI��Ӧ�ӿڵ����ݽṹ
class DNpcFightChar
{
public:
    DNpcFightChar();

protected:
    SBaseProperty _baseProperty;
    SCharBuff     _buffs[BodyStatusType_Max]   ; // �����������е�״̬,��¼����
};

//////////////////////////////////////////////////////////////////////////
// Item��Ӧ�ӿڵ����ݽṹ
class DItemChar
{
public:
    DItemChar();

protected:
    uint32 _hpMax; // Ѫ���
};

//////////////////////////////////////////////////////////////////////////
// MonsterAI��Ӧ�ӿڵ����ݽṹ
class AICharAttribute
{
public:
    AICharAttribute();

protected:
    SBaseProperty _baseProperty    ;
    int           _nMp             ;
    SCharBuff     _buffs[BodyStatusType_Max]   ; // �����������е�״̬,��¼����
};

// Effect��Ӧ�ӿڵ����ݽṹ
class DEffectChar
{
public:
    DEffectChar();

protected:
    uint32 _hpMax; // Ѫ���
};

//////////////////////////////////////////////////////////////////////////
// BuildChar��Ӧ�ӿڵ����ݽṹ
class DBuildChar
{
public:
    DBuildChar();

protected:
    uint32 _hpMax; // Ѫ���
};

#pragma pack( pop )

#endif // __COMMON_BASECHARPROPERTYI_H__
