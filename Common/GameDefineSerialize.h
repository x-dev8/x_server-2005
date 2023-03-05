/********************************************************************
    Filename:    GameDefineSerialize.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_GAMEDEFINESERIALIZE_H__
#define __COMMON_GAMEDEFINESERIALIZE_H__

#pragma once

#include "MeRTLibsServer.h"
#include "GameDefineGlobal.h"
#include "GameDefineChar.h"

/* 
    序列化的规则
    成员的归属类为它的成员变量打 标识标签
    每个成员变量为自身打         版本号标签 (如果有原生类型)
    struct STestB
    {
        int16 value;
    };

    struct STestA
    {
        STestB member1;
        STestB member2;
    };

    template<>
    bool GameDefineSerialize::Serialize<STestB>( const STestB& inData, CDataChunkWriter* w )
    {
        w->StartChunk(DC_TAG('TB01'));
            w->WriteT(inData.value);
        w->EndChunk(DC_TAG('TB01'));
        return true;
    }

    template<>
    bool GameDefineSerialize::UnSerialize<STestB>( uint8* buffer, uint32 bufferSize, STestB& outData )
    {
        CDataChunkLoader l( buffer, bufferSize);
        while( !l.IsEndOfMemory() )
        {
            if (l.IsChunk('TB01'))
            {
                l.StartChunk('TB01');
                {
                    CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                    r.ReadT(outData.value );
                }
                l.EndChunk('TB01');
            }
            else
            { l.SkipChunk(); }
        }
        return true;
    }

    template<>
    bool GameDefineSerialize::Serialize<STestA>( const STestA& inData, CDataChunkWriter* w )
    {
        w->StartChunk(DC_TAG('TA01'));
            w->StartChunk(DC_TAG('TEM1'));
            GameDefineSerialize::Serialize( inData.member1, w );
            w->EndChunk(DC_TAG('TEM1'));

            w->StartChunk(DC_TAG('TEM2'));
            GameDefineSerialize::Serialize( inData.member2, w );
            w->EndChunk(DC_TAG('TEM2'));
        w->EndChunk(DC_TAG('TA01'));
        return true;
    }

    template<>
    bool GameDefineSerialize::UnSerialize<STestA>( uint8* buffer, uint32 bufferSize, STestA& outData )
    {
        CDataChunkLoader x( buffer, bufferSize);
        while( !x.IsEndOfMemory() )
        {
            if (x.IsChunk('TA01'))
            {
                x.StartChunk('TA01');
                {
                    CDataChunkLoader y(x.GetPointer().byte,x.GetChunkSize());
                    while( !y.IsEndOfMemory() )
                    {
                        if (y.IsChunk('TEM1'))
                        {
                            y.StartChunk('TEM1');
                            {   
                                GameDefineSerialize::UnSerialize( y.GetPointer().byte,y.GetChunkSize(), member1 );
                            }
                            y.EndChunk('TEM1');
                        }
                        else if (y.IsChunk('TEM2'))
                        {
                            y.StartChunk('TEM2');
                            {
                                GameDefineSerialize::UnSerialize( y.GetPointer().byte,y.GetChunkSize(), member2 );
                            }
                            y.EndChunk('TEM2');
                        }
                        else
                        { y.SkipChunk(); }
                    }
                }
                x.EndChunk('TA01');
            }
            else
            { x.SkipChunk(); }
        }
        return true;
    }
 */

class CDataChunkWriter;
class GameDefineSerialize
{
public:
    template<class T>
    static bool Serialize( const T& inData, CDataChunkWriter* w );

    template<class T>
    static bool UnSerialize( uint8* buffer, uint32 bufferSize, T& outData );
};

#endif // __COMMON_GAMEDEFINESERIALIZE_H__
