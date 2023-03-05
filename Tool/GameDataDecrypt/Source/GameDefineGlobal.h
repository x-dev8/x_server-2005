#ifndef __COMMON_GAMEDEFINEGLOBAL_H__
#define __COMMON_GAMEDEFINEGLOBAL_H__

/********************************************************************
    Filename:    GameDefineGlobal.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#pragma pack ( push, 1 )

#include "MeRTLibsServer.h"

#define InvalidLogicNumber 0x00000000
#define ShortMin (-32768) 
#define ShortMax 32767   

enum ECustomDataPart
{
    ECustomDataPart_base  ,
    ECustomDataPart_item  ,
    ECustomDataPart_status,
    ECustomDataPart_skill ,
    ECustomDataPart_title ,
    ECustomDataPart_mount ,
    ECustomDataPart_suit  ,
    ECustomDataPart_final ,
};

union ReadData
{
    uint8*  byte;
    bool*   boolean;
    int*    i;
    uint32* dw;
    int8*   c;
    void*   p;
    float*  f;
    int16*  s;
    uint16* w;

    ReadData(void* in) :p(in)
    {}
};

struct SInt16
{
    int16 base;
    int16 item;
    int16 status;
    int16 skill;
    int16 title;
    int16 mount;
    int16 suit;
    int16 final;

    SInt16()
    { memset( this, 0, sizeof( SInt16 ));}

    void AddPartValue( uint16 part, int16 value )
    {
        switch ( part )
        {
        case ECustomDataPart_base:
            { base += value; }
            break;
        case ECustomDataPart_item:
            { item += value; }
            break;
        case ECustomDataPart_status:
            { status += value; }
            break;
        case ECustomDataPart_skill:
            { skill += value; }
            break;
        case ECustomDataPart_title:
            { title += value;  }
            break;
        case ECustomDataPart_mount:
            { mount += value; }
            break;
        case ECustomDataPart_suit:
            { suit  += value; }
            break;
        case ECustomDataPart_final:
            { final += value; }
            break;
        }
    }

    void UpdateFinal()
    {
        final = base + item + status + skill + title + mount + suit;
        if ( final < 0 )
        { final = 0; }
    }

    int16 GetFinalVal()
    {
        final = base + item + status + skill + title + mount + suit;
        if (final < 0)
        { final = 0; }
        return final;
    }
};             

struct SUInt16
{
    uint16 base;
    uint16 item;
    uint16 status;
    uint16 skill;
    uint16 title;
    uint16 mount;
    uint16 suit;
    uint16 final;

    SUInt16()
    { memset( this, 0, sizeof( SUInt16 ));}

    void AddPartValue( uint16 part, uint16 value )
    {
        switch ( part )
        {
        case ECustomDataPart_base:
            { base += value; }
            break;
        case ECustomDataPart_item:
            { item += value; }
            break;
        case ECustomDataPart_status:
            { status += value; }
            break;
        case ECustomDataPart_skill:
            { skill += value; }
            break;
        case ECustomDataPart_title:
            { title += value;  }
            break;
        case ECustomDataPart_mount:
            { mount += value; }
            break;
        case ECustomDataPart_suit:
            { suit  += value; }
            break;
        case ECustomDataPart_final:
            { final += value; }
            break;
        }
    }

    void UpdateFinal()
    {
        int nFinal = base + item + status + skill + title + mount + suit;        
        if (nFinal < 0)
        { final = 0; }
        else
        { final = nFinal; }
    }

    uint16 GetFinalVal()
    {
        int nFinal = base + item + status + skill + title + mount + suit;
        if ( nFinal < 0)
        { final = 0; }
        else
        { final = nFinal; }
        return final;
    }
};

struct SInt32
{ //有符号Int
    int base;
    int item;
    int status;
    int skill;
    int title;
    int mount;
    int suit;
    int final;

    SInt32()
    { memset( this, 0, sizeof( SInt32 ));}

    void AddPartValue( uint16 part, int32 value )
    {
        switch ( part )
        {
        case ECustomDataPart_base:
            { base += value; }
            break;
        case ECustomDataPart_item:
            { item += value; }
            break;
        case ECustomDataPart_status:
            { status += value; }
            break;
        case ECustomDataPart_skill:
            { skill += value; }
            break;
        case ECustomDataPart_title:
            { title += value;  }
            break;
        case ECustomDataPart_mount:
            { mount += value; }
            break;
        case ECustomDataPart_suit:
            { suit  += value; }
            break;
        case ECustomDataPart_final:
            { final += value; }
            break;
        }
    }

    void UpdateFinal()
    {
        final = base + item + status + skill + title + mount + suit;
        if (final < 0)
        { final = 0; }
    }

    int GetFinalVal()
    {
        final = base + item + status + skill + title + mount + suit;
        if (final < 0)
        { final = 0; }
        return final;
    }
};

struct SFloat
{ // 给角色用的
    float base;
    float item;
    float status;
    float skill;
    float title;
    float mount;
    float suit;
    float final;

    SFloat()
    { memset( this, 0, sizeof( SFloat ));}

    void AddPartValue( uint16 part, float value )
    {
        switch ( part )
        {
        case ECustomDataPart_base:
            { base += value; }
            break;
        case ECustomDataPart_item:
            { item += value; }
            break;
        case ECustomDataPart_status:
            { status += value; }
            break;
        case ECustomDataPart_skill:
            { skill += value; }
            break;
        case ECustomDataPart_title:
            { title += value;  }
            break;
        case ECustomDataPart_mount:
            { mount += value; }
            break;
        case ECustomDataPart_suit:
            { suit  += value; }
            break;
        case ECustomDataPart_final:
            { final += value; }
            break;
        }
    }

    void UpdateFinal()
    {
        final = base + item + status + skill + title + mount + suit;
        if (final < 0.0f)
        { final = 0.0f; }
    }

    float GetFinalVal()
    {
        final = base + item + status + skill + title + mount + suit;
        if (final < 0.0f)
        { final = 0.0f; }
        return final;
    }
};

// 对应 ERAttributeType
union CustomValue
{
    float          fValue;
};

//////////////////////////////////////////////////////////////////////////
template< class T, uint32 size >
class TValueArray
{
public:
    TValueArray()
    { ::memset( values, 0, sizeof( values ) ); }

    T& GetValue( uint32 index ) 
    {
        if ( index >= size )
        { return values[0]; }

        return values[index];
    }

protected:
    T values[size];
};

#pragma pack ( pop )

#endif // __COMMON_GAMEDEFINEGLOBAL_H__
