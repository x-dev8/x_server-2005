#include "GameDefineSerialize.h"
#include "DataChunkWriter.h"

//////////////////////////////////////////////////////////////////////////
//template<>
//bool GameDefineSerialize::Serialize<具体的类>( const 具体的类& inData, CDataChunkWriter* w )
//{
//    return true;
//}
//
//template<>
//bool GameDefineSerialize::UnSerialize<具体的类>( uint8* buffer, uint32 bufferSize, 具体的类& outData )
//{
//    return true;
//}
//////////////////////////////////////////////////////////////////////////
//
//template<>
//bool GameDefineSerialize::Serialize<SInt16>( const SInt16& inData, CDataChunkWriter* w )
//{
//    w->StartChunk(DC_TAG('ssd1'));
//        w->WriteShort(inData.base);
//        w->WriteShort(inData.item);
//        w->WriteShort(inData.status);
//        w->WriteShort(inData.skill);
//        w->WriteShort(inData.title);
//        w->WriteShort(inData.pet);
//        w->WriteShort(inData.suit);
//        w->WriteShort(inData.final);
//    w->EndChunk(DC_TAG('ssd1'));
//    return true;
//}
//
//template<>
//bool GameDefineSerialize::UnSerialize<SInt16>( uint8* buffer, uint32 bufferSize, SInt16& outData )
//{
//    CDataChunkLoader l( buffer, bufferSize);
//    while( !l.IsEndOfMemory() )
//    {
//        if (l.IsChunk('ssd1'))
//        {
//            l.StartChunk('ssd1');
//            {   
//                CDataChunkLoader r( l.GetPointer().byte ,l.GetChunkSize());
//                r.ReadT( outData.base  );
//                r.ReadT( outData.item  );
//                r.ReadT( outData.status);
//                r.ReadT( outData.skill );
//                r.ReadT( outData.title );
//                r.ReadT( outData.pet );
//                r.ReadT( outData.suit  );
//                r.ReadT( outData.final );
//            }
//            l.EndChunk('ssd1');
//        }
//        else
//        { l.SkipChunk(); }
//    }
//    return true;
//}
//
////////////////////////////////////////////////////////////////////////////
//template<>
//bool GameDefineSerialize::Serialize<SUInt16>( const SUInt16& inData, CDataChunkWriter* w )
//{
//    w->StartChunk(DC_TAG('usd1'));
//        w->WriteShort(inData.base);
//        w->WriteShort(inData.item);
//        w->WriteShort(inData.status);
//        w->WriteShort(inData.skill);
//        w->WriteShort(inData.title);
//        w->WriteShort(inData.pet);
//        w->WriteShort(inData.suit);
//        w->WriteShort(inData.final);
//    w->EndChunk(DC_TAG('usd1'));
//    return true;
//}
//
//template<>
//bool GameDefineSerialize::UnSerialize<SUInt16>( uint8* buffer, uint32 bufferSize, SUInt16& outData )
//{
//    CDataChunkLoader l( buffer, bufferSize);
//    while( !l.IsEndOfMemory() )
//    {
//        if (l.IsChunk('usd1'))
//        {
//            l.StartChunk('usd1');
//            {   
//                CDataChunkLoader r( l.GetPointer().byte ,l.GetChunkSize());
//                r.ReadT(outData.base  );
//                r.ReadT(outData.item  );
//                r.ReadT(outData.status);
//                r.ReadT(outData.skill );
//                r.ReadT(outData.title );
//                r.ReadT(outData.pet );
//                r.ReadT(outData.suit  );
//                r.ReadT(outData.final );
//            }
//            l.EndChunk('usd1');
//        }
//        else
//        { l.SkipChunk(); }
//    }
//    return true;
//}
////////////////////////////////////////////////////////////////////////////
//template<>
//bool GameDefineSerialize::Serialize<SInt32>( const SInt32& inData, CDataChunkWriter* w )
//{
//    w->StartChunk(DC_TAG('sid1'));
//        w->WriteInt(inData.base);
//        w->WriteInt(inData.item);
//        w->WriteInt(inData.status);
//        w->WriteInt(inData.skill);
//        w->WriteInt(inData.title);
//        w->WriteInt(inData.pet);
//        w->WriteInt(inData.suit);
//        w->WriteInt(inData.final);
//    w->EndChunk(DC_TAG('sid1'));
//    return true;
//}
//
//template<>
//bool GameDefineSerialize::UnSerialize<SInt32>( uint8* buffer, uint32 bufferSize, SInt32& outData )
//{
//    CDataChunkLoader l( buffer, bufferSize);
//    while( !l.IsEndOfMemory() )
//    {
//        if (l.IsChunk('sid1'))
//        {
//            l.StartChunk('sid1');
//            {
//                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//                r.ReadT(outData.base  );
//                r.ReadT(outData.item  );
//                r.ReadT(outData.status);
//                r.ReadT(outData.skill );
//                r.ReadT(outData.title );
//                r.ReadT(outData.pet );
//                r.ReadT(outData.suit  );
//                r.ReadT(outData.final );
//            }
//            l.EndChunk('sid1');
//        }
//        else
//        { l.SkipChunk(); }
//    }
//    return true;
//}
//
////////////////////////////////////////////////////////////////////////////
//template<>
//bool GameDefineSerialize::Serialize<SFloat>( const SFloat& inData, CDataChunkWriter* w )
//{
//    w->StartChunk(DC_TAG('fsd1'));
//        w->WriteFloat(inData.base);
//        w->WriteFloat(inData.item);
//        w->WriteFloat(inData.status);
//        w->WriteFloat(inData.skill);
//        w->WriteFloat(inData.title);
//        w->WriteFloat(inData.pet);
//        w->WriteFloat(inData.suit);
//        w->WriteFloat(inData.final);
//    w->EndChunk(DC_TAG('fsd1'));
//    return true;
//}
//
//template<>
//bool GameDefineSerialize::UnSerialize<SFloat>( uint8* buffer, uint32 bufferSize, SFloat& outData )
//{
//    CDataChunkLoader l( buffer, bufferSize);
//    while( !l.IsEndOfMemory() )
//    {
//        if (l.IsChunk('fsd1'))
//        {
//            l.StartChunk('fsd1');
//            {
//                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//                r.ReadT(outData.base  );
//                r.ReadT(outData.item  );
//                r.ReadT(outData.status);
//                r.ReadT(outData.skill );
//                r.ReadT(outData.title );
//                r.ReadT(outData.pet );
//                r.ReadT(outData.suit  );
//                r.ReadT(outData.final );
//            }
//            l.EndChunk('fsd1');
//        }
//        else
//        { l.SkipChunk(); }
//    }
//    return true;
//}

//////////////////////////////////////////////////////////////////////////
template<>
bool GameDefineSerialize::Serialize<SCharBaseAttr>( const SCharBaseAttr& inData, CDataChunkWriter* w )
{
    for (int i=0; i <EBaseAttr_MaxSize; ++i)
    {
        w->WriteFloat(inData.baseAttrValue[ i ].base);
        w->WriteFloat(inData.baseAttrValue[ i ].item);
        w->WriteFloat(inData.baseAttrValue[ i ].status);
        w->WriteFloat(inData.baseAttrValue[ i ].skill);
        w->WriteFloat(inData.baseAttrValue[ i ].final);
    }
    return true;
}

template<>
bool GameDefineSerialize::UnSerialize<SCharBaseAttr>( uint8* buffer, uint32 bufferSize, SCharBaseAttr& outData )
{   
    CDataChunkLoader l( buffer, bufferSize);
    for (int i = 0; i <EBaseAttr_MaxSize; ++i)
    {   
        outData.baseAttrValue[i].base   = l.ReadFloat();
        outData.baseAttrValue[i].item   = l.ReadFloat();
        outData.baseAttrValue[i].status = l.ReadFloat();
        outData.baseAttrValue[i].skill  = l.ReadFloat();
        outData.baseAttrValue[i].final  = l.ReadFloat();
    }
    return true;
}
//////////////////////////////////////////////////////////////////////////

#define WRITE_FIGHT_DATA( tag, member ) \
    w->StartChunk(DC_TAG(tag)); \
        GameDefineSerialize::Serialize( member, w); \
    w->EndChunk(DC_TAG(tag));

#define READ_FIGHT_DATA_BEGIN( tag, member ) \
    if (l.IsChunk(tag)) \
    { \
        l.StartChunk(tag); \
        { \
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize()); \
            GameDefineSerialize::UnSerialize( r.GetPointer().byte,l.GetChunkSize(), member); \
        } \
        l.EndChunk(tag); \
    }

#define READ_FIGHT_DATA( tag, member ) \
        else if (l.IsChunk(tag)) \
        { \
            l.StartChunk(tag); \
            { \
                CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize()); \
                GameDefineSerialize::UnSerialize( r.GetPointer().byte,l.GetChunkSize(), member); \
            } \
            l.EndChunk(tag); \
        }

#define READ_FIGHT_DATA_END \
        else \
        { l.SkipChunk(); }\

template<>
bool GameDefineSerialize::Serialize<SCharFightAttr>( const SCharFightAttr& inData, CDataChunkWriter* w )
{
    //WRITE_FIGHT_DATA( 'hpma', inData.hpMax             ); 
    //WRITE_FIGHT_DATA( 'enma', inData.energyMax         ); 
    //WRITE_FIGHT_DATA( 'atsh', inData.attack       ); 
    //WRITE_FIGHT_DATA( 'ddsh', inData.defendShort       ); 
    //WRITE_FIGHT_DATA( 'ddlo', inData.defendLong        ); 
    //WRITE_FIGHT_DATA( 'ddma', inData.defendMagic       ); 
    //WRITE_FIGHT_DATA( 'mosp', inData.moveSpeed         ); 
    //WRITE_FIGHT_DATA( 'hpre', inData.hpRestore         ); 
    //WRITE_FIGHT_DATA( 'enre', inData.energyRestore     ); 
    //WRITE_FIGHT_DATA( 'desh', inData.derateShort       ); 
    //WRITE_FIGHT_DATA( 'delo', inData.derateLong        ); 
    //WRITE_FIGHT_DATA( 'dema', inData.derateMagic       ); 
    //WRITE_FIGHT_DATA( 'deis', inData.derateIgnoreShort ); 
    //WRITE_FIGHT_DATA( 'deil', inData.derateIgnoreLong  ); 
    //WRITE_FIGHT_DATA( 'deim', inData.derateIgnoreMagic ); 
    //WRITE_FIGHT_DATA( 'dodg', inData.dodge             ); 
    //WRITE_FIGHT_DATA( 'exac', inData.exact             ); 
    //WRITE_FIGHT_DATA( 'crit', inData.critical          ); 
    //WRITE_FIGHT_DATA( 'crin', inData.criticalIntensity ); 
    //WRITE_FIGHT_DATA( 'tena', inData.tenacity          ); 
    //WRITE_FIGHT_DATA( 'redr', inData.resistDread       ); 
    //WRITE_FIGHT_DATA( 'reco', inData.resistComa        ); 
    //WRITE_FIGHT_DATA( 'resi', inData.resistSilence     ); 
    //WRITE_FIGHT_DATA( 'resl', inData.resistSlow        ); 
    //WRITE_FIGHT_DATA( 'atsp', inData.attackSpeed       ); 
    //WRITE_FIGHT_DATA( 'into', inData.intonate          ); 
    return true;
}

template<>
bool GameDefineSerialize::UnSerialize<SCharFightAttr>( uint8* buffer, uint32 bufferSize, SCharFightAttr& outData )
{
    CDataChunkLoader l( buffer, bufferSize );
    while( !l.IsEndOfMemory() )
    {
        //READ_FIGHT_DATA_BEGIN( 'hpma', outData.hpMax             )
        //      READ_FIGHT_DATA( 'enma', outData.energyMax         )
        //      READ_FIGHT_DATA( 'atsh', outData.attack            )
        //      READ_FIGHT_DATA( 'ddsh', outData.defendShort       )
        //      READ_FIGHT_DATA( 'ddlo', outData.defendLong        )
        //      READ_FIGHT_DATA( 'ddma', outData.defendMagic       )
        //      READ_FIGHT_DATA( 'mosp', outData.moveSpeed         )
        //      READ_FIGHT_DATA( 'hpre', outData.hpRestore         )
        //      READ_FIGHT_DATA( 'enre', outData.energyRestore     )
        //      READ_FIGHT_DATA( 'desh', outData.derateShort       )
        //      READ_FIGHT_DATA( 'delo', outData.derateLong        )
        //      READ_FIGHT_DATA( 'dema', outData.derateMagic       )
        //      READ_FIGHT_DATA( 'deis', outData.derateIgnoreShort )
        //      READ_FIGHT_DATA( 'deil', outData.derateIgnoreLong  )
        //      READ_FIGHT_DATA( 'deim', outData.derateIgnoreMagic )
        //      READ_FIGHT_DATA( 'dodg', outData.dodge             )
        //      READ_FIGHT_DATA( 'exac', outData.exact             )
        //      READ_FIGHT_DATA( 'crit', outData.critical          )
        //      READ_FIGHT_DATA( 'crin', outData.criticalIntensity )
        //      READ_FIGHT_DATA( 'tena', outData.tenacity          )
        //      READ_FIGHT_DATA( 'redr', outData.resistDread       )
        //      READ_FIGHT_DATA( 'reco', outData.resistComa        )
        //      READ_FIGHT_DATA( 'resi', outData.resistSilence     )
        //      READ_FIGHT_DATA( 'resl', outData.resistSlow        )
        //      READ_FIGHT_DATA( 'atsp', outData.attackSpeed       )
        //      READ_FIGHT_DATA( 'into', outData.intonate          )
        //READ_FIGHT_DATA_END
    }
    return true;
}
