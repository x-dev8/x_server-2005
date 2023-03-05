#include "CharChunkWR.h"
#include "GameDefineSerialize.h"
bool CharChunkWR::WriteCharData( SCharBaseInfo* pInfo, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
{
    CDataChunkWriter w( pOutBuffer, outBufferSize );

    w.StartChunk(DC_TAG('apto'));
    {
        w.StartChunk(DC_TAG('ap05'));
        {
            w.StartChunk(DC_TAG('cn01'));
            w.WriteString(pInfo->aptotic.szCharacterName);
            w.EndChunk(DC_TAG('cn01'));

            w.StartChunk(DC_TAG('sx01'));
            w.WriteChar(pInfo->aptotic.ucSex);
            w.EndChunk(DC_TAG('sx01'));

            w.StartChunk(DC_TAG('pf01'));
            w.WriteShort(pInfo->aptotic.usProfession);
            w.EndChunk(DC_TAG('pf01'));

            w.StartChunk(DC_TAG('hc01'));
            w.WriteChar(pInfo->aptotic.ucHeadPic);
            w.EndChunk(DC_TAG('hc01'));

            w.StartChunk(DC_TAG('ct01'));
            w.WriteChar(pInfo->aptotic.ucCountry);
            w.EndChunk(DC_TAG('ct01'));

            w.StartChunk(DC_TAG('yn01'));
            w.WriteString(pInfo->aptotic.szYearName);
            w.EndChunk(DC_TAG('yn01'));

            w.StartChunk(DC_TAG('yr01'));
            w.WriteByte(pInfo->aptotic.byYear);
            w.EndChunk(DC_TAG('yr01'));

            w.StartChunk(DC_TAG('mt01'));
            w.WriteByte(pInfo->aptotic.byMonth);
            w.EndChunk(DC_TAG('mt01'));

            w.StartChunk(DC_TAG('dy01'));
            w.WriteByte(pInfo->aptotic.byDay);
            w.EndChunk(DC_TAG('dy01'));
        }
        w.EndChunk(DC_TAG('ap05'));
    }
    w.EndChunk(DC_TAG('apto'));

    w.StartChunk(DC_TAG('live'));
    {
        w.OpenChunk('lv11');
        {
            w.WriteWordChunk ('levl', pInfo->liveinfo.ustLevel         );
            w.WriteDwordChunk('mony', pInfo->liveinfo.dwMoney          );
            w.WriteDwordChunk('repu', pInfo->liveinfo.reputation       );
            w.WriteDwordChunk('expt', pInfo->liveinfo.exploit          );
            w.WriteDwordChunk('honr', pInfo->liveinfo.honour           );
            w.WriteDwordChunk('bls1', pInfo->liveinfo.battleScore      );
            w.WriteDwordChunk('cos1', pInfo->liveinfo.dwCountryScore   );
            w.WriteDwordChunk('hpfg', pInfo->liveinfo.dwHelpFlag       );
            w.WriteDwordChunk('hsct', pInfo->liveinfo.nHighShoutCount  );
            w.WriteIntChunk  ('hp01', pInfo->liveinfo.nHp              );
            w.WriteIntChunk  ('mp01', pInfo->liveinfo.nMp              );
            w.WriteIntChunk  ('xp01', pInfo->liveinfo.nXp              );
            w.WriteInt64Chunk('exp0', pInfo->liveinfo.dwExp            );
            w.WriteInt64Chunk('epnu', pInfo->liveinfo.dwExpNotUsed     );
            w.WriteDwordChunk('slep', pInfo->liveinfo.dwSkillExp       );
            w.WriteDwordChunk('spnu', pInfo->liveinfo.dwSkillExpNotUsed);
            w.WriteWordChunk ('seid', pInfo->liveinfo.ustSkillExpForSkillID);
            w.WriteCharChunk ('nbgs', pInfo->liveinfo.ucNormalBagSize  );
            w.WriteCharChunk ('mbgs', pInfo->liveinfo.ucMaterialBagSize);
            w.WriteCharChunk ('moco', pInfo->liveinfo.ucMountCount     );
            w.WriteWordChunk ('ene1', pInfo->liveinfo.activity         );
            w.WriteWordChunk ('enm1', pInfo->liveinfo.activityMax      );
            w.WriteWordChunk ('vig1', pInfo->liveinfo.vigor            );
            w.WriteWordChunk ('vim1', pInfo->liveinfo.vigorMax         );
            w.WriteDwordChunk('olt2', pInfo->liveinfo.dwOnlineTime     );
            w.WriteDwordChunk('olre', pInfo->liveinfo.dwRewardItemInfo );
            w.WriteShortChunk('ttle', pInfo->liveinfo.nCurrentTitleID  );  //当前称号
            w.WriteDwordChunk('jzi1', pInfo->liveinfo.jiaoZi           );
            w.WriteByteChunk ('stig', pInfo->liveinfo.nStorageItemGrid );
            w.WriteByteChunk ('stmg', pInfo->liveinfo.nStorageMountGrid);

            w.WriteDwordChunk('rlit', pInfo->liveinfo.nRecordReliveTime);
            w.WriteByteChunk ('flic', pInfo->liveinfo.nFreeReliveCount );

            w.WriteDwordChunk('sdet', pInfo->liveinfo.nSysDoubleExpTime);
            w.WriteDwordChunk('idet', pInfo->liveinfo.nItemDoubleExpTime);

            w.WriteDwordChunk('daox', pInfo->liveinfo.daoxing);

            //称号列表
            w.StartChunk(DC_TAG('tt02'));
            w.Write( pInfo->liveinfo.xTitleData, sizeof(TitleData) * MAX_TITLE_COUNT, 1 );
            w.EndChunk(DC_TAG('tt02'));

            w.StartChunk(DC_TAG('are1'));
            w.Write( pInfo->liveinfo.xArea, sizeof( SAreaRepulation ) * MAX_AREAREPULATION_COUNT, 1 );
            w.EndChunk(DC_TAG('are1'));

            w.StartChunk(DC_TAG('msd2'));
            w.Write( &pInfo->liveinfo.xMasterData, sizeof( MasterData ) , 1 );
            w.EndChunk(DC_TAG('msd2'));
            
            w.WriteWordChunk ('skn1', pInfo->liveinfo.nRecipeSkillNum  );

            w.StartChunk(DC_TAG('skp1'));
            w.Write( pInfo->liveinfo.nSkillPoint, sizeof( unsigned short ) * ERT_MaxType , 1 );
            w.EndChunk(DC_TAG('skp1'));

            w.WriteWordChunk ('bapt', pInfo->liveinfo.basePotential  );

            w.StartChunk(DC_TAG('bav1'));
            w.Write( pInfo->liveinfo.baseAssignValue, sizeof( unsigned short ) * EBaseAttr_MaxSize , 1 );
            w.EndChunk(DC_TAG('bav1'));

			w.WriteShortChunk('hrid', pInfo->liveinfo.hero_id);
			w.WriteCharChunk ('tphj', pInfo->liveinfo.TPHJRank);
			w.WriteDwordChunk('akp', pInfo->liveinfo.dwKillPlayerSum);
			w.WriteDwordChunk('wkp', pInfo->liveinfo.dwKillPlayerWeekSum);
		
			w.WriteByteChunk('upos', pInfo->liveinfo.uchPosition);
			w.StartChunk(DC_TAG('cold'));
			w.Write( pInfo->liveinfo.xItemColdDown, sizeof( SColdDown ) * MAX_SAVERESTORE_COUNT , 1 );
			w.WriteDwordChunk('cs', pInfo->liveinfo.ConsumeScore);	
			w.EndChunk(DC_TAG('cold'));
        }
        w.CloseChunk('lv11');
	}
    w.EndChunk(DC_TAG('live'));

    nActualSize = w.GetUsedSize();
    if( nActualSize == 0 )
    {
        w.Destroy();
        return false;
    }

    if ( nActualSize > outBufferSize )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteCharData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
        return false;
    }

    w.Destroy();
    return true;
}

bool CharChunkWR::WriteItemData( SCharItem* pItem, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
{
    CDataChunkWriter w( pOutBuffer, outBufferSize );

    pItem->Write(&w);

    nActualSize = w.GetUsedSize();
    if( nActualSize == 0 )
    {
        w.Destroy();
        return false;
    }

    if ( nActualSize > outBufferSize)
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteItemData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
        return false;
    }
    w.Destroy();
    return true;
}

bool CharChunkWR::WriteVisualData( SCharVisual* pInfo, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
{
    CDataChunkWriter w( pOutBuffer, outBufferSize );
    w.StartChunk(DC_TAG('visl'));
    pInfo->WriteVisual(&w);
    w.EndChunk(DC_TAG('visl'));

    nActualSize = w.GetUsedSize();
    if( nActualSize == 0 )
    {
        w.Destroy();
        return false;
    }

    if ( nActualSize > outBufferSize )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteVisualData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
        return false;
    }
    w.Destroy();
    return true;
}

bool CharChunkWR::WriteOtherData( SCharOtherData* pOtherData, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
{
    CDataChunkWriter w( pOutBuffer, outBufferSize );

    w.StartChunk(DC_TAG('otda'));
    pOtherData->WriteOtherDataBlob(&w);
    w.EndChunk(DC_TAG('otda'));

    nActualSize = w.GetUsedSize();
    if( nActualSize == 0 )
    {
        w.Destroy();
        return false;
    }

    if ( nActualSize > outBufferSize )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteOtherData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
        return false;
    }
    w.Destroy();
    return true;
}
bool CharChunkWR::WriteKillInfo( SCharOtherData*  pOtherData,     uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
{
    CDataChunkWriter w( pOutBuffer, outBufferSize );

    w.StartChunk(DC_TAG('inf1'));
	for(size_t i =0;i<MAX_KILLSUM;++i)
	{
		//读取数组
		w.WriteDword(pOtherData->KillList[i].PlayerDBID);
		w.WriteShort(pOtherData->KillList[i].Num);
	}
    w.EndChunk(DC_TAG('inf1'));

    nActualSize = w.GetUsedSize();
    if( nActualSize == 0 )
    {
        w.Destroy();
        return false;
    }

    if ( nActualSize > outBufferSize )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteOtherData KillPlayer Chunk(%d)>(%d) ", nActualSize, outBufferSize );
        return false;
    }
    w.Destroy();
    return true;
}
bool CharChunkWR::WriteExtendData( SExtendData* pExtendData, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
{
    CDataChunkWriter w( pOutBuffer, outBufferSize );

    w.StartChunk(DC_TAG('exda'));
    pExtendData->Write(&w);
    w.EndChunk(DC_TAG('exda'));

    nActualSize = w.GetUsedSize();
    if( nActualSize == 0 )
    {
        w.Destroy();
        return false;
    }

    if ( nActualSize > outBufferSize )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteExtendData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
        return false;
    }

    w.Destroy();
    return true;
}

bool CharChunkWR::WriteAchieveData( SAchieveData* pAchieveData, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
{
    CDataChunkWriter w( pOutBuffer, outBufferSize );

    w.StartChunk(DC_TAG('ahda'));
    pAchieveData->Write(&w);
    w.EndChunk(DC_TAG('ahda'));

    nActualSize = w.GetUsedSize();
    if( nActualSize == 0 )
    {
        w.Destroy();
        return false;
    }

    if ( nActualSize > outBufferSize )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteAchieveData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
        return false;
    }

    w.Destroy();
    return true;
}

bool CharChunkWR::WriteIdentifyData( SIdentifyData* pIdentifyData, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
{
    CDataChunkWriter w( pOutBuffer, outBufferSize );

    w.StartChunk(DC_TAG('inda'));
    pIdentifyData->Write(&w);
    w.EndChunk(DC_TAG('inda'));

    nActualSize = w.GetUsedSize();
    if( nActualSize == 0 )
    {
        w.Destroy();
        return false;
    }

    if ( nActualSize > outBufferSize )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteIdentifyData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
        return false;
    }

    w.Destroy();
    return true;
}

bool CharChunkWR::WriteMountData ( SMountItem* pMount, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
{
    CDataChunkWriter w( pOutBuffer, outBufferSize);
    pMount->Write(&w);

    nActualSize = w.GetUsedSize();
    if( nActualSize == 0 )
    {
        w.Destroy();
        return false;
    }

    if ( nActualSize > outBufferSize )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteMountData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
        return false;
    }

    w.Destroy();
    return true;
}

bool CharChunkWR::WritePetData ( SPetItem* pPet, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
{
    CDataChunkWriter w( pOutBuffer, outBufferSize);
    pPet->Write(&w);

    nActualSize = w.GetUsedSize();
    if( nActualSize == 0 )
    {
        w.Destroy();
        return false;
    }

    if ( nActualSize > outBufferSize )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WritePetData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
        return false;
    }

    w.Destroy();
    return true;
}

bool CharChunkWR::LoadCharData( uint8* buffer, uint32 bufferSize, SCharBaseInfo* pInfo)
{
    CDataChunkLoader l( buffer, bufferSize );

    while( !l.IsEndOfMemory() )
    {
        if( l.IsChunk(  'apto' ) )
        {
            l.StartChunk('apto');
            ReadCharData p( l.GetPointer().c );
            LoadCharApto( p, l.GetChunkSize(), pInfo );
            l.EndChunk('apto');
        }
        else if (l.IsChunk('live'))
        {
            l.StartChunk('live');
            ReadCharData p( l.GetPointer().c );
            LoadCharLive( p, l.GetChunkSize(), pInfo );
            l.EndChunk('live');

        }
        else 
        { l.SkipChunk(); }
    }
    return true;
}

void CharChunkWR::LoadCharApto( ReadCharData inP, int nSize, SCharBaseInfo* pInfo )
{
    CDataChunkLoader l(inP.byte,nSize);

    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('ap05'))
        {
            l.StartChunk( 'ap05' );
            CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
            while (!r.IsEndOfMemory())
            {
                if (r.IsChunk('cn01'))
                {
                    r.StartChunk('cn01');
                    CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());

                    int nStrSize = p.ReadInt();

                    memset(&pInfo->aptotic.szCharacterName, 0, sizeof(pInfo->aptotic.szCharacterName));
                    memcpy(&pInfo->aptotic.szCharacterName, p.GetPointer().byte, min(sizeof(CHAR)*nStrSize, sizeof(pInfo->aptotic.szCharacterName)));
                    p.GetPointer().c += nStrSize;

                    r.EndChunk('cn01');
                }
                else if (r.IsChunk('sx01'))
                {
                    r.StartChunk('sx01');
                    CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());
                    pInfo->aptotic.ucSex = p.ReadChar();
                    r.EndChunk('sx01');
                }
                else if (r.IsChunk('pf01'))
                {
                    r.StartChunk('pf01');
                    CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());

                    pInfo->aptotic.usProfession = p.ReadShort();
                    r.EndChunk('pf01');
                }
                else if (r.IsChunk('hc01'))
                {
                    r.StartChunk('hc01');
                    CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());

                    pInfo->aptotic.ucHeadPic = p.ReadChar();
                    r.EndChunk('hc01');
                }
                else if (r.IsChunk('ct01'))
                {
                    r.StartChunk('ct01');
                    CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());

                    pInfo->aptotic.ucCountry = p.ReadChar();
                    r.EndChunk('ct01');
                }
                else if (r.IsChunk('yn01'))
                {
                    r.StartChunk('yn01');
                    CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());

                    int nStrSize1 = p.ReadInt();

                    memset(&pInfo->aptotic.szYearName, 0, sizeof(pInfo->aptotic.szYearName));
                    memcpy(&pInfo->aptotic.szYearName, p.GetPointer().byte, min(sizeof(CHAR)*nStrSize1, sizeof(pInfo->aptotic.szYearName)));
                    p.GetPointer().c += nStrSize1;

                    r.EndChunk('yn01');
                }
                else if (r.IsChunk('yr01'))
                {
                    r.StartChunk('yr01');
                    CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());

                    pInfo->aptotic.byYear = p.ReadByte();
                    r.EndChunk('yr01');
                }
                else if (r.IsChunk('mt01'))
                {
                    r.StartChunk('mt01');
                    CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());

                    pInfo->aptotic.byMonth = p.ReadByte();
                    r.EndChunk('mt01');
                }
                else if (r.IsChunk('dy01'))
                {
                    r.StartChunk('dy01');
                    CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());

                    pInfo->aptotic.byDay = p.ReadByte();
                    r.EndChunk('dy01');
                }
                else
                    r.SkipChunk();
            }                
            l.EndChunk('ap05');
        }
        else 
            l.SkipChunk();
    }
}
void CharChunkWR::LoadCharLive( ReadCharData inP, int nSize, SCharBaseInfo* pInfo )
{
    CDataChunkLoader l(inP.byte,nSize);
    while( !l.IsEndOfMemory() )
    {
        if (l.IsChunk('lv05'))
        {
            l.OpenChunk();
            short stTemp = -1;
			pInfo->liveinfo.hero_id = INVALID_HERO_ID;
            while (!l.IsEndOfChunk())
            {
                if(l.TryReadWordChunk('levl',pInfo->liveinfo.ustLevel))                   {}
                else if (l.TryReadDwordChunk('mony',pInfo->liveinfo.dwMoney))             {}
                else if (l.TryReadDwordChunk('repu',pInfo->liveinfo.reputation))          {}
                else if (l.TryReadDwordChunk('expt',pInfo->liveinfo.exploit))             {}
                else if (l.TryReadDwordChunk('honr',pInfo->liveinfo.honour))              {}
                else if (l.TryReadDwordChunk('bls1', pInfo->liveinfo.battleScore))        {}
                else if (l.TryReadDwordChunk('cos1', pInfo->liveinfo.dwCountryScore))     {}
                else if (l.TryReadDwordChunk('sile',pInfo->liveinfo.jinDing))             {}
                else if (l.TryReadDwordChunk('prsr',pInfo->liveinfo.jinPiao))             {}
                else if (l.TryReadDwordChunk('hpfg',pInfo->liveinfo.dwHelpFlag))          {}
                else if (l.TryReadDwordChunk('hsct',pInfo->liveinfo.nHighShoutCount))     {}
                else if (l.TryReadIntChunk('hp01', pInfo->liveinfo.nHp))                  {}
                else if (l.TryReadIntChunk('mp01', pInfo->liveinfo.nMp))                  {}
                else if (l.TryReadIntChunk('xp01', pInfo->liveinfo.nXp))                  {}
                else if (l.TryReadInt64Chunk('exp0', pInfo->liveinfo.dwExp))              {}
                else if (l.TryReadInt64Chunk('epnu', pInfo->liveinfo.dwExpNotUsed))       {}
                else if (l.TryReadDwordChunk('slep', pInfo->liveinfo.dwSkillExp))         {}
                else if (l.TryReadDwordChunk('spnu', pInfo->liveinfo.dwSkillExpNotUsed))  {}                
                else if (l.TryReadWordChunk('seid',pInfo->liveinfo.ustSkillExpForSkillID)){}
                else if (l.TryReadByteChunk('nbgs',pInfo->liveinfo.ucNormalBagSize))      {}
                else if (l.TryReadByteChunk('mbgs',pInfo->liveinfo.ucMaterialBagSize))    {}
                else if (l.TryReadByteChunk('moco',pInfo->liveinfo.ucMountCount))         {}
                else if (l.TryReadWordChunk('ene1',pInfo->liveinfo.activity))             {}
                else if (l.TryReadWordChunk('enm1',pInfo->liveinfo.activityMax))          {}
                else if (l.TryReadWordChunk('vig1',pInfo->liveinfo.vigor))                {}
                else if (l.TryReadWordChunk('vim1',pInfo->liveinfo.vigorMax))             {}
                else if (l.TryReadDwordChunk('olt1', pInfo->liveinfo.dwOnlineTime))       { pInfo->liveinfo.dwOnlineTime /= 60000; }  // 以前是毫秒 NND
                else if (l.TryReadDwordChunk('olt2', pInfo->liveinfo.dwOnlineTime))       {}     
                else if (l.TryReadDwordChunk('olre', pInfo->liveinfo.dwRewardItemInfo))   {}
                else if (l.TryReadShortChunk('ttle',pInfo->liveinfo.nCurrentTitleID))     {}
                else if (l.TryReadDwordChunk('jzi1',pInfo->liveinfo.jiaoZi))              {}
                else if (l.TryReadByteChunk('stig',pInfo->liveinfo.nStorageItemGrid))     {}
                else if (l.TryReadByteChunk('stmg',pInfo->liveinfo.nStorageMountGrid))    {}

                else if (l.TryReadDwordChunk('rlit',pInfo->liveinfo.nRecordReliveTime))   {}
                else if (l.TryReadByteChunk ('flic',pInfo->liveinfo.nFreeReliveCount))    {}

                else if (l.TryReadDwordChunk('sdet',pInfo->liveinfo.nSysDoubleExpTime))   {}
                else if (l.TryReadDwordChunk('idet',pInfo->liveinfo.nItemDoubleExpTime))  {}

                else if (l.TryReadDwordChunk('daox',pInfo->liveinfo.daoxing))  {}

                else if (l.IsChunk('tt01'))
                {
                    l.StartChunk('tt01');
                    {   
                        CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                        short nTitleArray[MAX_TITLE_COUNT];
                        memset( nTitleArray, 0, sizeof( nTitleArray ) );
                        r.ReadToBuffer( (BYTE*)nTitleArray, sizeof(nTitleArray) );
                        for ( int i = 0; i < MAX_TITLE_COUNT; ++i )
                        {
                            pInfo->liveinfo.xTitleData[i].SetTitleID( nTitleArray[i] );
                        }
                    }   
                    l.EndChunk('tt01');
                }
                else if (l.IsChunk('tt02'))
                {
                    l.StartChunk('tt02');
                    {   
                        CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                        r.ReadToBuffer((BYTE*)pInfo->liveinfo.xTitleData, sizeof(pInfo->liveinfo.xTitleData));
                    }   
                    l.EndChunk('tt02');
                }
                else if ( l.IsChunk('are1') )
                {
                    l.StartChunk('are1');
                    {   
                        CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                        r.ReadToBuffer((BYTE*)pInfo->liveinfo.xArea, sizeof(pInfo->liveinfo.xArea));
                    }   
                    l.EndChunk('are1');
                }
                else if ( l.IsChunk('msd2') )
                {
                    l.StartChunk('msd2');
                    {   
                        CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                        r.ReadToBuffer((BYTE*)&pInfo->liveinfo.xMasterData, sizeof(pInfo->liveinfo.xMasterData));
                    }   
                    l.EndChunk('msd2');
                }
                else if(l.TryReadWordChunk('skn1',pInfo->liveinfo.nRecipeSkillNum))                   {}
                else if ( l.IsChunk( 'skp1') )
                {
                    l.StartChunk('skp1');
                    {   
                        CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                        r.ReadToBuffer( (BYTE*)pInfo->liveinfo.nSkillPoint, sizeof(pInfo->liveinfo.nSkillPoint) );
                    }   
                    l.EndChunk('skp1');
                }
                else if(l.TryReadWordChunk('bapt',pInfo->liveinfo.basePotential))                   {}
                else if ( l.IsChunk( 'bav1') )
                {
                    l.StartChunk('bav1');
                    {   
                        CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
                        r.ReadToBuffer( (BYTE*)pInfo->liveinfo.baseAssignValue, sizeof(pInfo->liveinfo.baseAssignValue) );
                    }   
                    l.EndChunk('bav1');
                }
              
                else{ l.SkipChunk();}

				pInfo->liveinfo.uchPosition = 0xFF;//标记当前玩家的职位不目前 在玩家初始化函数重新获取职位
            }
        }
		if (l.IsChunk('lv06'))
		{
			l.OpenChunk();
			short stTemp = -1;
			while (!l.IsEndOfChunk())
			{
				if(l.TryReadWordChunk('levl',pInfo->liveinfo.ustLevel))                   {}
				else if (l.TryReadDwordChunk('mony',pInfo->liveinfo.dwMoney))             {}
				else if (l.TryReadDwordChunk('repu',pInfo->liveinfo.reputation))          {}
				else if (l.TryReadDwordChunk('expt',pInfo->liveinfo.exploit))             {}
				else if (l.TryReadDwordChunk('honr',pInfo->liveinfo.honour))              {}
				else if (l.TryReadDwordChunk('bls1', pInfo->liveinfo.battleScore))        {}
				else if (l.TryReadDwordChunk('cos1', pInfo->liveinfo.dwCountryScore))     {}
				else if (l.TryReadDwordChunk('sile',pInfo->liveinfo.jinDing))             {}
				else if (l.TryReadDwordChunk('prsr',pInfo->liveinfo.jinPiao))             {}
				else if (l.TryReadDwordChunk('hpfg',pInfo->liveinfo.dwHelpFlag))          {}
				else if (l.TryReadDwordChunk('hsct',pInfo->liveinfo.nHighShoutCount))     {}
				else if (l.TryReadIntChunk('hp01', pInfo->liveinfo.nHp))                  {}
				else if (l.TryReadIntChunk('mp01', pInfo->liveinfo.nMp))                  {}
				else if (l.TryReadIntChunk('xp01', pInfo->liveinfo.nXp))                  {}
				else if (l.TryReadInt64Chunk('exp0', pInfo->liveinfo.dwExp))              {}
				else if (l.TryReadInt64Chunk('epnu', pInfo->liveinfo.dwExpNotUsed))       {}
				else if (l.TryReadDwordChunk('slep', pInfo->liveinfo.dwSkillExp))         {}
				else if (l.TryReadDwordChunk('spnu', pInfo->liveinfo.dwSkillExpNotUsed))  {}                
				else if (l.TryReadWordChunk('seid',pInfo->liveinfo.ustSkillExpForSkillID)){}
				else if (l.TryReadByteChunk('nbgs',pInfo->liveinfo.ucNormalBagSize))      {}
				else if (l.TryReadByteChunk('mbgs',pInfo->liveinfo.ucMaterialBagSize))    {}
				else if (l.TryReadByteChunk('moco',pInfo->liveinfo.ucMountCount))         {}
				else if (l.TryReadWordChunk('ene1',pInfo->liveinfo.activity))             {}
				else if (l.TryReadWordChunk('enm1',pInfo->liveinfo.activityMax))          {}
				else if (l.TryReadWordChunk('vig1',pInfo->liveinfo.vigor))                {}
				else if (l.TryReadWordChunk('vim1',pInfo->liveinfo.vigorMax))             {}
				else if (l.TryReadDwordChunk('olt1', pInfo->liveinfo.dwOnlineTime))       { pInfo->liveinfo.dwOnlineTime /= 60000; }  // 以前是毫秒 NND
				else if (l.TryReadDwordChunk('olt2', pInfo->liveinfo.dwOnlineTime))       {}     
				else if (l.TryReadDwordChunk('olre', pInfo->liveinfo.dwRewardItemInfo))   {}
				else if (l.TryReadShortChunk('ttle',pInfo->liveinfo.nCurrentTitleID))     {}
				else if (l.TryReadDwordChunk('jzi1',pInfo->liveinfo.jiaoZi))              {}
				else if (l.TryReadByteChunk('stig',pInfo->liveinfo.nStorageItemGrid))     {}
				else if (l.TryReadByteChunk('stmg',pInfo->liveinfo.nStorageMountGrid))    {}

				else if (l.TryReadDwordChunk('rlit',pInfo->liveinfo.nRecordReliveTime))   {}
				else if (l.TryReadByteChunk ('flic',pInfo->liveinfo.nFreeReliveCount))    {}

				else if (l.TryReadDwordChunk('sdet',pInfo->liveinfo.nSysDoubleExpTime))   {}
				else if (l.TryReadDwordChunk('idet',pInfo->liveinfo.nItemDoubleExpTime))  {}

				else if (l.TryReadDwordChunk('daox',pInfo->liveinfo.daoxing))  {}

				else if (l.IsChunk('tt01'))
				{
					l.StartChunk('tt01');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						short nTitleArray[MAX_TITLE_COUNT];
						memset( nTitleArray, 0, sizeof( nTitleArray ) );
						r.ReadToBuffer( (BYTE*)nTitleArray, sizeof(nTitleArray) );
						for ( int i = 0; i < MAX_TITLE_COUNT; ++i )
						{
							pInfo->liveinfo.xTitleData[i].SetTitleID( nTitleArray[i] );
						}
					}   
					l.EndChunk('tt01');
				}
				else if (l.IsChunk('tt02'))
				{
					l.StartChunk('tt02');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xTitleData, sizeof(pInfo->liveinfo.xTitleData));
					}   
					l.EndChunk('tt02');
				}
				else if ( l.IsChunk('are1') )
				{
					l.StartChunk('are1');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xArea, sizeof(pInfo->liveinfo.xArea));
					}   
					l.EndChunk('are1');
				}
				else if ( l.IsChunk('msd2') )
				{
					l.StartChunk('msd2');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)&pInfo->liveinfo.xMasterData, sizeof(pInfo->liveinfo.xMasterData));
					}   
					l.EndChunk('msd2');
				}
				else if(l.TryReadWordChunk('skn1',pInfo->liveinfo.nRecipeSkillNum))                   {}
				else if ( l.IsChunk( 'skp1') )
				{
					l.StartChunk('skp1');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.nSkillPoint, sizeof(pInfo->liveinfo.nSkillPoint) );
					}   
					l.EndChunk('skp1');
				}
				else if(l.TryReadWordChunk('bapt',pInfo->liveinfo.basePotential))                   {}
				else if ( l.IsChunk( 'bav1') )
				{
					l.StartChunk('bav1');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.baseAssignValue, sizeof(pInfo->liveinfo.baseAssignValue) );
					}   
					l.EndChunk('bav1');
				}
				else if (l.TryReadShortChunk('hrid',(short&)pInfo->liveinfo.hero_id))  {}

				else{ l.SkipChunk();}

				pInfo->liveinfo.uchPosition = 0xFF;//标记当前玩家的职位不目前 在玩家初始化函数重新获取职位
			}
		}
		if (l.IsChunk('lv07'))
		{
			l.OpenChunk();
			short stTemp = -1;
			while (!l.IsEndOfChunk())
			{
				if(l.TryReadWordChunk('levl',pInfo->liveinfo.ustLevel))                   {}
				else if (l.TryReadDwordChunk('mony',pInfo->liveinfo.dwMoney))             {}
				else if (l.TryReadDwordChunk('repu',pInfo->liveinfo.reputation))          {}
				else if (l.TryReadDwordChunk('expt',pInfo->liveinfo.exploit))             {}
				else if (l.TryReadDwordChunk('honr',pInfo->liveinfo.honour))              {}
				else if (l.TryReadDwordChunk('bls1', pInfo->liveinfo.battleScore))        {}
				else if (l.TryReadDwordChunk('cos1', pInfo->liveinfo.dwCountryScore))     {}
				else if (l.TryReadDwordChunk('sile',pInfo->liveinfo.jinDing))             {}
				else if (l.TryReadDwordChunk('prsr',pInfo->liveinfo.jinPiao))             {}
				else if (l.TryReadDwordChunk('hpfg',pInfo->liveinfo.dwHelpFlag))          {}
				else if (l.TryReadDwordChunk('hsct',pInfo->liveinfo.nHighShoutCount))     {}
				else if (l.TryReadIntChunk('hp01', pInfo->liveinfo.nHp))                  {}
				else if (l.TryReadIntChunk('mp01', pInfo->liveinfo.nMp))                  {}
				else if (l.TryReadIntChunk('xp01', pInfo->liveinfo.nXp))                  {}
				else if (l.TryReadInt64Chunk('exp0', pInfo->liveinfo.dwExp))              {}
				else if (l.TryReadInt64Chunk('epnu', pInfo->liveinfo.dwExpNotUsed))       {}
				else if (l.TryReadDwordChunk('slep', pInfo->liveinfo.dwSkillExp))         {}
				else if (l.TryReadDwordChunk('spnu', pInfo->liveinfo.dwSkillExpNotUsed))  {}                
				else if (l.TryReadWordChunk('seid',pInfo->liveinfo.ustSkillExpForSkillID)){}
				else if (l.TryReadByteChunk('nbgs',pInfo->liveinfo.ucNormalBagSize))      {}
				else if (l.TryReadByteChunk('mbgs',pInfo->liveinfo.ucMaterialBagSize))    {}
				else if (l.TryReadByteChunk('moco',pInfo->liveinfo.ucMountCount))         {}
				else if (l.TryReadWordChunk('ene1',pInfo->liveinfo.activity))             {}
				else if (l.TryReadWordChunk('enm1',pInfo->liveinfo.activityMax))          {}
				else if (l.TryReadWordChunk('vig1',pInfo->liveinfo.vigor))                {}
				else if (l.TryReadWordChunk('vim1',pInfo->liveinfo.vigorMax))             {}
				else if (l.TryReadDwordChunk('olt1', pInfo->liveinfo.dwOnlineTime))       { pInfo->liveinfo.dwOnlineTime /= 60000; }  // 以前是毫秒 NND
				else if (l.TryReadDwordChunk('olt2', pInfo->liveinfo.dwOnlineTime))       {}     
				else if (l.TryReadDwordChunk('olre', pInfo->liveinfo.dwRewardItemInfo))   {}
				else if (l.TryReadShortChunk('ttle',pInfo->liveinfo.nCurrentTitleID))     {}
				else if (l.TryReadDwordChunk('jzi1',pInfo->liveinfo.jiaoZi))              {}
				else if (l.TryReadByteChunk('stig',pInfo->liveinfo.nStorageItemGrid))     {}
				else if (l.TryReadByteChunk('stmg',pInfo->liveinfo.nStorageMountGrid))    {}

				else if (l.TryReadDwordChunk('rlit',pInfo->liveinfo.nRecordReliveTime))   {}
				else if (l.TryReadByteChunk ('flic',pInfo->liveinfo.nFreeReliveCount))    {}

				else if (l.TryReadDwordChunk('sdet',pInfo->liveinfo.nSysDoubleExpTime))   {}
				else if (l.TryReadDwordChunk('idet',pInfo->liveinfo.nItemDoubleExpTime))  {}

				else if (l.TryReadDwordChunk('daox',pInfo->liveinfo.daoxing))  {}

				else if (l.IsChunk('tt01'))
				{
					l.StartChunk('tt01');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						short nTitleArray[MAX_TITLE_COUNT];
						memset( nTitleArray, 0, sizeof( nTitleArray ) );
						r.ReadToBuffer( (BYTE*)nTitleArray, sizeof(nTitleArray) );
						for ( int i = 0; i < MAX_TITLE_COUNT; ++i )
						{
							pInfo->liveinfo.xTitleData[i].SetTitleID( nTitleArray[i] );
						}
					}   
					l.EndChunk('tt01');
				}
				else if (l.IsChunk('tt02'))
				{
					l.StartChunk('tt02');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xTitleData, sizeof(pInfo->liveinfo.xTitleData));
					}   
					l.EndChunk('tt02');
				}
				else if ( l.IsChunk('are1') )
				{
					l.StartChunk('are1');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xArea, sizeof(pInfo->liveinfo.xArea));
					}   
					l.EndChunk('are1');
				}
				else if ( l.IsChunk('msd2') )
				{
					l.StartChunk('msd2');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)&pInfo->liveinfo.xMasterData, sizeof(pInfo->liveinfo.xMasterData));
					}   
					l.EndChunk('msd2');
				}
				else if(l.TryReadWordChunk('skn1',pInfo->liveinfo.nRecipeSkillNum))                   {}
				else if ( l.IsChunk( 'skp1') )
				{
					l.StartChunk('skp1');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.nSkillPoint, sizeof(pInfo->liveinfo.nSkillPoint) );
					}   
					l.EndChunk('skp1');
				}
				else if(l.TryReadWordChunk('bapt',pInfo->liveinfo.basePotential))                   {}
				else if ( l.IsChunk( 'bav1') )
				{
					l.StartChunk('bav1');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.baseAssignValue, sizeof(pInfo->liveinfo.baseAssignValue) );
					}   
					l.EndChunk('bav1');
				}
				else if (l.TryReadShortChunk('hrid',(short&)pInfo->liveinfo.hero_id))  {}
				else if (l.TryReadCharChunk('tphj',pInfo->liveinfo.TPHJRank))          {}
				else{ l.SkipChunk();}

				pInfo->liveinfo.uchPosition = 0xFF;//标记当前玩家的职位不目前 在玩家初始化函数重新获取职位
			}
		}
		if (l.IsChunk('lv08'))
		{
			l.OpenChunk();
			short stTemp = -1;
			while (!l.IsEndOfChunk())
			{
				if(l.TryReadWordChunk('levl',pInfo->liveinfo.ustLevel))                   {}
				else if (l.TryReadDwordChunk('mony',pInfo->liveinfo.dwMoney))             {}
				else if (l.TryReadDwordChunk('repu',pInfo->liveinfo.reputation))          {}
				else if (l.TryReadDwordChunk('expt',pInfo->liveinfo.exploit))             {}
				else if (l.TryReadDwordChunk('honr',pInfo->liveinfo.honour))              {}
				else if (l.TryReadDwordChunk('bls1', pInfo->liveinfo.battleScore))        {}
				else if (l.TryReadDwordChunk('cos1', pInfo->liveinfo.dwCountryScore))     {}
				else if (l.TryReadDwordChunk('sile',pInfo->liveinfo.jinDing))             {}
				else if (l.TryReadDwordChunk('prsr',pInfo->liveinfo.jinPiao))             {}
				else if (l.TryReadDwordChunk('hpfg',pInfo->liveinfo.dwHelpFlag))          {}
				else if (l.TryReadDwordChunk('hsct',pInfo->liveinfo.nHighShoutCount))     {}
				else if (l.TryReadIntChunk('hp01', pInfo->liveinfo.nHp))                  {}
				else if (l.TryReadIntChunk('mp01', pInfo->liveinfo.nMp))                  {}
				else if (l.TryReadIntChunk('xp01', pInfo->liveinfo.nXp))                  {}
				else if (l.TryReadInt64Chunk('exp0', pInfo->liveinfo.dwExp))              {}
				else if (l.TryReadInt64Chunk('epnu', pInfo->liveinfo.dwExpNotUsed))       {}
				else if (l.TryReadDwordChunk('slep', pInfo->liveinfo.dwSkillExp))         {}
				else if (l.TryReadDwordChunk('spnu', pInfo->liveinfo.dwSkillExpNotUsed))  {}                
				else if (l.TryReadWordChunk('seid',pInfo->liveinfo.ustSkillExpForSkillID)){}
				else if (l.TryReadByteChunk('nbgs',pInfo->liveinfo.ucNormalBagSize))      {}
				else if (l.TryReadByteChunk('mbgs',pInfo->liveinfo.ucMaterialBagSize))    {}
				else if (l.TryReadByteChunk('moco',pInfo->liveinfo.ucMountCount))         {}
				else if (l.TryReadWordChunk('ene1',pInfo->liveinfo.activity))             {}
				else if (l.TryReadWordChunk('enm1',pInfo->liveinfo.activityMax))          {}
				else if (l.TryReadWordChunk('vig1',pInfo->liveinfo.vigor))                {}
				else if (l.TryReadWordChunk('vim1',pInfo->liveinfo.vigorMax))             {}
				else if (l.TryReadDwordChunk('olt1', pInfo->liveinfo.dwOnlineTime))       { pInfo->liveinfo.dwOnlineTime /= 60000; }  // 以前是毫秒 NND
				else if (l.TryReadDwordChunk('olt2', pInfo->liveinfo.dwOnlineTime))       {}     
				else if (l.TryReadDwordChunk('olre', pInfo->liveinfo.dwRewardItemInfo))   {}
				else if (l.TryReadShortChunk('ttle',pInfo->liveinfo.nCurrentTitleID))     {}
				else if (l.TryReadDwordChunk('jzi1',pInfo->liveinfo.jiaoZi))              {}
				else if (l.TryReadByteChunk('stig',pInfo->liveinfo.nStorageItemGrid))     {}
				else if (l.TryReadByteChunk('stmg',pInfo->liveinfo.nStorageMountGrid))    {}

				else if (l.TryReadDwordChunk('rlit',pInfo->liveinfo.nRecordReliveTime))   {}
				else if (l.TryReadByteChunk ('flic',pInfo->liveinfo.nFreeReliveCount))    {}

				else if (l.TryReadDwordChunk('sdet',pInfo->liveinfo.nSysDoubleExpTime))   {}
				else if (l.TryReadDwordChunk('idet',pInfo->liveinfo.nItemDoubleExpTime))  {}

				else if (l.TryReadDwordChunk('daox',pInfo->liveinfo.daoxing))  {}

				else if (l.IsChunk('tt01'))
				{
					l.StartChunk('tt01');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						short nTitleArray[MAX_TITLE_COUNT];
						memset( nTitleArray, 0, sizeof( nTitleArray ) );
						r.ReadToBuffer( (BYTE*)nTitleArray, sizeof(nTitleArray) );
						for ( int i = 0; i < MAX_TITLE_COUNT; ++i )
						{
							pInfo->liveinfo.xTitleData[i].SetTitleID( nTitleArray[i] );
						}
					}   
					l.EndChunk('tt01');
				}
				else if (l.IsChunk('tt02'))
				{
					l.StartChunk('tt02');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xTitleData, sizeof(pInfo->liveinfo.xTitleData));
					}   
					l.EndChunk('tt02');
				}
				else if ( l.IsChunk('are1') )
				{
					l.StartChunk('are1');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xArea, sizeof(pInfo->liveinfo.xArea));
					}   
					l.EndChunk('are1');
				}
				else if ( l.IsChunk('msd2') )
				{
					l.StartChunk('msd2');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)&pInfo->liveinfo.xMasterData, sizeof(pInfo->liveinfo.xMasterData));
					}   
					l.EndChunk('msd2');
				}
				else if(l.TryReadWordChunk('skn1',pInfo->liveinfo.nRecipeSkillNum))                   {}
				else if ( l.IsChunk( 'skp1') )
				{
					l.StartChunk('skp1');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.nSkillPoint, sizeof(pInfo->liveinfo.nSkillPoint) );
					}   
					l.EndChunk('skp1');
				}
				else if(l.TryReadWordChunk('bapt',pInfo->liveinfo.basePotential))                   {}
				else if ( l.IsChunk( 'bav1') )
				{
					l.StartChunk('bav1');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.baseAssignValue, sizeof(pInfo->liveinfo.baseAssignValue) );
					}   
					l.EndChunk('bav1');
				}
				else if (l.TryReadShortChunk('hrid',(short&)pInfo->liveinfo.hero_id))  {}
				else if (l.TryReadCharChunk('tphj',pInfo->liveinfo.TPHJRank))          {}
				else if (l.TryReadDwordChunk('akp',pInfo->liveinfo.dwKillPlayerSum))  {}
				else if (l.TryReadDwordChunk('wkp',pInfo->liveinfo.dwKillPlayerWeekSum))  {}
				else{ l.SkipChunk();}

				pInfo->liveinfo.uchPosition = 0xFF;//标记当前玩家的职位不目前 在玩家初始化函数重新获取职位
			}
		}
		if (l.IsChunk('lv09'))
		{
			l.OpenChunk();
			short stTemp = -1;
			while (!l.IsEndOfChunk())
			{
				if(l.TryReadWordChunk('levl',pInfo->liveinfo.ustLevel))                   {}
				else if (l.TryReadDwordChunk('mony',pInfo->liveinfo.dwMoney))             {}
				else if (l.TryReadDwordChunk('repu',pInfo->liveinfo.reputation))          {}
				else if (l.TryReadDwordChunk('expt',pInfo->liveinfo.exploit))             {}
				else if (l.TryReadDwordChunk('honr',pInfo->liveinfo.honour))              {}
				else if (l.TryReadDwordChunk('bls1', pInfo->liveinfo.battleScore))        {}
				else if (l.TryReadDwordChunk('cos1', pInfo->liveinfo.dwCountryScore))     {}
				else if (l.TryReadDwordChunk('sile',pInfo->liveinfo.jinDing))             {}
				else if (l.TryReadDwordChunk('prsr',pInfo->liveinfo.jinPiao))             {}
				else if (l.TryReadDwordChunk('hpfg',pInfo->liveinfo.dwHelpFlag))          {}
				else if (l.TryReadDwordChunk('hsct',pInfo->liveinfo.nHighShoutCount))     {}
				else if (l.TryReadIntChunk('hp01', pInfo->liveinfo.nHp))                  {}
				else if (l.TryReadIntChunk('mp01', pInfo->liveinfo.nMp))                  {}
				else if (l.TryReadIntChunk('xp01', pInfo->liveinfo.nXp))                  {}
				else if (l.TryReadInt64Chunk('exp0', pInfo->liveinfo.dwExp))              {}
				else if (l.TryReadInt64Chunk('epnu', pInfo->liveinfo.dwExpNotUsed))       {}
				else if (l.TryReadDwordChunk('slep', pInfo->liveinfo.dwSkillExp))         {}
				else if (l.TryReadDwordChunk('spnu', pInfo->liveinfo.dwSkillExpNotUsed))  {}                
				else if (l.TryReadWordChunk('seid',pInfo->liveinfo.ustSkillExpForSkillID)){}
				else if (l.TryReadByteChunk('nbgs',pInfo->liveinfo.ucNormalBagSize))      {}
				else if (l.TryReadByteChunk('mbgs',pInfo->liveinfo.ucMaterialBagSize))    {}
				else if (l.TryReadByteChunk('moco',pInfo->liveinfo.ucMountCount))         {}
				else if (l.TryReadWordChunk('ene1',pInfo->liveinfo.activity))             {}
				else if (l.TryReadWordChunk('enm1',pInfo->liveinfo.activityMax))          {}
				else if (l.TryReadWordChunk('vig1',pInfo->liveinfo.vigor))                {}
				else if (l.TryReadWordChunk('vim1',pInfo->liveinfo.vigorMax))             {}
				else if (l.TryReadDwordChunk('olt1', pInfo->liveinfo.dwOnlineTime))       { pInfo->liveinfo.dwOnlineTime /= 60000; }  // 以前是毫秒 NND
				else if (l.TryReadDwordChunk('olt2', pInfo->liveinfo.dwOnlineTime))       {}     
				else if (l.TryReadDwordChunk('olre', pInfo->liveinfo.dwRewardItemInfo))   {}
				else if (l.TryReadShortChunk('ttle',pInfo->liveinfo.nCurrentTitleID))     {}
				else if (l.TryReadDwordChunk('jzi1',pInfo->liveinfo.jiaoZi))              {}
				else if (l.TryReadByteChunk('stig',pInfo->liveinfo.nStorageItemGrid))     {}
				else if (l.TryReadByteChunk('stmg',pInfo->liveinfo.nStorageMountGrid))    {}

				else if (l.TryReadDwordChunk('rlit',pInfo->liveinfo.nRecordReliveTime))   {}
				else if (l.TryReadByteChunk ('flic',pInfo->liveinfo.nFreeReliveCount))    {}

				else if (l.TryReadDwordChunk('sdet',pInfo->liveinfo.nSysDoubleExpTime))   {}
				else if (l.TryReadDwordChunk('idet',pInfo->liveinfo.nItemDoubleExpTime))  {}

				else if (l.TryReadDwordChunk('daox',pInfo->liveinfo.daoxing))  {}

				else if (l.IsChunk('tt01'))
				{
					l.StartChunk('tt01');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						short nTitleArray[MAX_TITLE_COUNT];
						memset( nTitleArray, 0, sizeof( nTitleArray ) );
						r.ReadToBuffer( (BYTE*)nTitleArray, sizeof(nTitleArray) );
						for ( int i = 0; i < MAX_TITLE_COUNT; ++i )
						{
							pInfo->liveinfo.xTitleData[i].SetTitleID( nTitleArray[i] );
						}
					}   
					l.EndChunk('tt01');
				}
				else if (l.IsChunk('tt02'))
				{
					l.StartChunk('tt02');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xTitleData, sizeof(pInfo->liveinfo.xTitleData));
					}   
					l.EndChunk('tt02');
				}
				else if ( l.IsChunk('are1') )
				{
					l.StartChunk('are1');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xArea, sizeof(pInfo->liveinfo.xArea));
					}   
					l.EndChunk('are1');
				}
				else if ( l.IsChunk('msd2') )
				{
					l.StartChunk('msd2');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)&pInfo->liveinfo.xMasterData, sizeof(pInfo->liveinfo.xMasterData));
					}   
					l.EndChunk('msd2');
				}
				else if(l.TryReadWordChunk('skn1',pInfo->liveinfo.nRecipeSkillNum))                   {}
				else if ( l.IsChunk( 'skp1') )
				{
					l.StartChunk('skp1');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.nSkillPoint, sizeof(pInfo->liveinfo.nSkillPoint) );
					}   
					l.EndChunk('skp1');
				}
				else if(l.TryReadWordChunk('bapt',pInfo->liveinfo.basePotential))                   {}
				else if ( l.IsChunk( 'bav1') )
				{
					l.StartChunk('bav1');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.baseAssignValue, sizeof(pInfo->liveinfo.baseAssignValue) );
					}   
					l.EndChunk('bav1');
				}
				else if (l.TryReadShortChunk('hrid',(short&)pInfo->liveinfo.hero_id))  {}
				else if (l.TryReadCharChunk('tphj',pInfo->liveinfo.TPHJRank))          {}
				else if (l.TryReadDwordChunk('akp',pInfo->liveinfo.dwKillPlayerSum))  {}
				else if (l.TryReadDwordChunk('wkp',pInfo->liveinfo.dwKillPlayerWeekSum))  {}
				else if (l.TryReadByteChunk('upos',pInfo->liveinfo.uchPosition))  {}
				else{ l.SkipChunk();}
			}
		}
		else if (l.IsChunk('lv10'))
		{
			l.OpenChunk();
			short stTemp = -1;
			while (!l.IsEndOfChunk())
			{
				if(l.TryReadWordChunk('levl',pInfo->liveinfo.ustLevel))                   {}
				else if (l.TryReadDwordChunk('mony',pInfo->liveinfo.dwMoney))             {}
				else if (l.TryReadDwordChunk('repu',pInfo->liveinfo.reputation))          {}
				else if (l.TryReadDwordChunk('expt',pInfo->liveinfo.exploit))             {}
				else if (l.TryReadDwordChunk('honr',pInfo->liveinfo.honour))              {}
				else if (l.TryReadDwordChunk('bls1', pInfo->liveinfo.battleScore))        {}
				else if (l.TryReadDwordChunk('cos1', pInfo->liveinfo.dwCountryScore))     {}
				else if (l.TryReadDwordChunk('sile',pInfo->liveinfo.jinDing))             {}
				else if (l.TryReadDwordChunk('prsr',pInfo->liveinfo.jinPiao))             {}
				else if (l.TryReadDwordChunk('hpfg',pInfo->liveinfo.dwHelpFlag))          {}
				else if (l.TryReadDwordChunk('hsct',pInfo->liveinfo.nHighShoutCount))     {}
				else if (l.TryReadIntChunk('hp01', pInfo->liveinfo.nHp))                  {}
				else if (l.TryReadIntChunk('mp01', pInfo->liveinfo.nMp))                  {}
				else if (l.TryReadIntChunk('xp01', pInfo->liveinfo.nXp))                  {}
				else if (l.TryReadInt64Chunk('exp0', pInfo->liveinfo.dwExp))              {}
				else if (l.TryReadInt64Chunk('epnu', pInfo->liveinfo.dwExpNotUsed))       {}
				else if (l.TryReadDwordChunk('slep', pInfo->liveinfo.dwSkillExp))         {}
				else if (l.TryReadDwordChunk('spnu', pInfo->liveinfo.dwSkillExpNotUsed))  {}                
				else if (l.TryReadWordChunk('seid',pInfo->liveinfo.ustSkillExpForSkillID)){}
				else if (l.TryReadByteChunk('nbgs',pInfo->liveinfo.ucNormalBagSize))      {}
				else if (l.TryReadByteChunk('mbgs',pInfo->liveinfo.ucMaterialBagSize))    {}
				else if (l.TryReadByteChunk('moco',pInfo->liveinfo.ucMountCount))         {}
				else if (l.TryReadWordChunk('ene1',pInfo->liveinfo.activity))             {}
				else if (l.TryReadWordChunk('enm1',pInfo->liveinfo.activityMax))          {}
				else if (l.TryReadWordChunk('vig1',pInfo->liveinfo.vigor))                {}
				else if (l.TryReadWordChunk('vim1',pInfo->liveinfo.vigorMax))             {}
				else if (l.TryReadDwordChunk('olt1', pInfo->liveinfo.dwOnlineTime))       { pInfo->liveinfo.dwOnlineTime /= 60000; }  // 以前是毫秒 NND
				else if (l.TryReadDwordChunk('olt2', pInfo->liveinfo.dwOnlineTime))       {}     
				else if (l.TryReadDwordChunk('olre', pInfo->liveinfo.dwRewardItemInfo))   {}
				else if (l.TryReadShortChunk('ttle',pInfo->liveinfo.nCurrentTitleID))     {}
				else if (l.TryReadDwordChunk('jzi1',pInfo->liveinfo.jiaoZi))              {}
				else if (l.TryReadByteChunk('stig',pInfo->liveinfo.nStorageItemGrid))     {}
				else if (l.TryReadByteChunk('stmg',pInfo->liveinfo.nStorageMountGrid))    {}

				else if (l.TryReadDwordChunk('rlit',pInfo->liveinfo.nRecordReliveTime))   {}
				else if (l.TryReadByteChunk ('flic',pInfo->liveinfo.nFreeReliveCount))    {}

				else if (l.TryReadDwordChunk('sdet',pInfo->liveinfo.nSysDoubleExpTime))   {}
				else if (l.TryReadDwordChunk('idet',pInfo->liveinfo.nItemDoubleExpTime))  {}

				else if (l.TryReadDwordChunk('daox',pInfo->liveinfo.daoxing))  {}

				else if (l.IsChunk('tt01'))
				{
					l.StartChunk('tt01');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						short nTitleArray[MAX_TITLE_COUNT];
						memset( nTitleArray, 0, sizeof( nTitleArray ) );
						r.ReadToBuffer( (BYTE*)nTitleArray, sizeof(nTitleArray) );
						for ( int i = 0; i < MAX_TITLE_COUNT; ++i )
						{
							pInfo->liveinfo.xTitleData[i].SetTitleID( nTitleArray[i] );
						}
					}   
					l.EndChunk('tt01');
				}
				else if (l.IsChunk('tt02'))
				{
					l.StartChunk('tt02');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xTitleData, sizeof(pInfo->liveinfo.xTitleData));
					}   
					l.EndChunk('tt02');
				}
				else if ( l.IsChunk('are1') )
				{
					l.StartChunk('are1');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xArea, sizeof(pInfo->liveinfo.xArea));
					}   
					l.EndChunk('are1');
				}
				else if ( l.IsChunk('msd2') )
				{
					l.StartChunk('msd2');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)&pInfo->liveinfo.xMasterData, sizeof(pInfo->liveinfo.xMasterData));
					}   
					l.EndChunk('msd2');
				}
				else if(l.TryReadWordChunk('skn1',pInfo->liveinfo.nRecipeSkillNum))                   {}
				else if ( l.IsChunk( 'skp1') )
				{
					l.StartChunk('skp1');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.nSkillPoint, sizeof(pInfo->liveinfo.nSkillPoint) );
					}   
					l.EndChunk('skp1');
				}
				else if(l.TryReadWordChunk('bapt',pInfo->liveinfo.basePotential))                   {}
				else if ( l.IsChunk( 'bav1') )
				{
					l.StartChunk('bav1');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.baseAssignValue, sizeof(pInfo->liveinfo.baseAssignValue) );
					}   
					l.EndChunk('bav1');
				}
				else if (l.TryReadShortChunk('hrid',(short&)pInfo->liveinfo.hero_id))  {}
				else if (l.TryReadCharChunk('tphj',pInfo->liveinfo.TPHJRank))          {}
				else if (l.TryReadDwordChunk('akp',pInfo->liveinfo.dwKillPlayerSum))  {}
				else if (l.TryReadDwordChunk('wkp',pInfo->liveinfo.dwKillPlayerWeekSum))  {}
				else if (l.TryReadByteChunk('upos',pInfo->liveinfo.uchPosition))  {}
				else if ( l.IsChunk('cold'))
				{
					l.StartChunk('cold');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xItemColdDown, sizeof(pInfo->liveinfo.xItemColdDown));
					}   
					l.EndChunk('cold');
				}
				else{ l.SkipChunk();}
			}
		}
		else if(l.IsChunk('lv11'))
		{
			l.OpenChunk();
			short stTemp = -1;
			while (!l.IsEndOfChunk())
			{
				if(l.TryReadWordChunk('levl',pInfo->liveinfo.ustLevel))                   {}
				else if (l.TryReadDwordChunk('mony',pInfo->liveinfo.dwMoney))             {}
				else if (l.TryReadDwordChunk('repu',pInfo->liveinfo.reputation))          {}
				else if (l.TryReadDwordChunk('expt',pInfo->liveinfo.exploit))             {}
				else if (l.TryReadDwordChunk('honr',pInfo->liveinfo.honour))              {}
				else if (l.TryReadDwordChunk('bls1', pInfo->liveinfo.battleScore))        {}
				else if (l.TryReadDwordChunk('cos1', pInfo->liveinfo.dwCountryScore))     {}
				else if (l.TryReadDwordChunk('sile',pInfo->liveinfo.jinDing))             {}
				else if (l.TryReadDwordChunk('prsr',pInfo->liveinfo.jinPiao))             {}
				else if (l.TryReadDwordChunk('hpfg',pInfo->liveinfo.dwHelpFlag))          {}
				else if (l.TryReadDwordChunk('hsct',pInfo->liveinfo.nHighShoutCount))     {}
				else if (l.TryReadIntChunk('hp01', pInfo->liveinfo.nHp))                  {}
				else if (l.TryReadIntChunk('mp01', pInfo->liveinfo.nMp))                  {}
				else if (l.TryReadIntChunk('xp01', pInfo->liveinfo.nXp))                  {}
				else if (l.TryReadInt64Chunk('exp0', pInfo->liveinfo.dwExp))              {}
				else if (l.TryReadInt64Chunk('epnu', pInfo->liveinfo.dwExpNotUsed))       {}
				else if (l.TryReadDwordChunk('slep', pInfo->liveinfo.dwSkillExp))         {}
				else if (l.TryReadDwordChunk('spnu', pInfo->liveinfo.dwSkillExpNotUsed))  {}                
				else if (l.TryReadWordChunk('seid',pInfo->liveinfo.ustSkillExpForSkillID)){}
				else if (l.TryReadByteChunk('nbgs',pInfo->liveinfo.ucNormalBagSize))      {}
				else if (l.TryReadByteChunk('mbgs',pInfo->liveinfo.ucMaterialBagSize))    {}
				else if (l.TryReadByteChunk('moco',pInfo->liveinfo.ucMountCount))         {}
				else if (l.TryReadWordChunk('ene1',pInfo->liveinfo.activity))             {}
				else if (l.TryReadWordChunk('enm1',pInfo->liveinfo.activityMax))          {}
				else if (l.TryReadWordChunk('vig1',pInfo->liveinfo.vigor))                {}
				else if (l.TryReadWordChunk('vim1',pInfo->liveinfo.vigorMax))             {}
				else if (l.TryReadDwordChunk('olt1', pInfo->liveinfo.dwOnlineTime))       { pInfo->liveinfo.dwOnlineTime /= 60000; }  // 以前是毫秒 NND
				else if (l.TryReadDwordChunk('olt2', pInfo->liveinfo.dwOnlineTime))       {}     
				else if (l.TryReadDwordChunk('olre', pInfo->liveinfo.dwRewardItemInfo))   {}
				else if (l.TryReadShortChunk('ttle',pInfo->liveinfo.nCurrentTitleID))     {}
				else if (l.TryReadDwordChunk('jzi1',pInfo->liveinfo.jiaoZi))              {}
				else if (l.TryReadByteChunk('stig',pInfo->liveinfo.nStorageItemGrid))     {}
				else if (l.TryReadByteChunk('stmg',pInfo->liveinfo.nStorageMountGrid))    {}

				else if (l.TryReadDwordChunk('rlit',pInfo->liveinfo.nRecordReliveTime))   {}
				else if (l.TryReadByteChunk ('flic',pInfo->liveinfo.nFreeReliveCount))    {}

				else if (l.TryReadDwordChunk('sdet',pInfo->liveinfo.nSysDoubleExpTime))   {}
				else if (l.TryReadDwordChunk('idet',pInfo->liveinfo.nItemDoubleExpTime))  {}

				else if (l.TryReadDwordChunk('daox',pInfo->liveinfo.daoxing))  {}

				else if (l.IsChunk('tt01'))
				{
					l.StartChunk('tt01');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						short nTitleArray[MAX_TITLE_COUNT];
						memset( nTitleArray, 0, sizeof( nTitleArray ) );
						r.ReadToBuffer( (BYTE*)nTitleArray, sizeof(nTitleArray) );
						for ( int i = 0; i < MAX_TITLE_COUNT; ++i )
						{
							pInfo->liveinfo.xTitleData[i].SetTitleID( nTitleArray[i] );
						}
					}   
					l.EndChunk('tt01');
				}
				else if (l.IsChunk('tt02'))
				{
					l.StartChunk('tt02');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xTitleData, sizeof(pInfo->liveinfo.xTitleData));
					}   
					l.EndChunk('tt02');
				}
				else if ( l.IsChunk('are1') )
				{
					l.StartChunk('are1');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xArea, sizeof(pInfo->liveinfo.xArea));
					}   
					l.EndChunk('are1');
				}
				else if ( l.IsChunk('msd2') )
				{
					l.StartChunk('msd2');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)&pInfo->liveinfo.xMasterData, sizeof(pInfo->liveinfo.xMasterData));
					}   
					l.EndChunk('msd2');
				}
				else if(l.TryReadWordChunk('skn1',pInfo->liveinfo.nRecipeSkillNum))                   {}
				else if ( l.IsChunk( 'skp1') )
				{
					l.StartChunk('skp1');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.nSkillPoint, sizeof(pInfo->liveinfo.nSkillPoint) );
					}   
					l.EndChunk('skp1');
				}
				else if(l.TryReadWordChunk('bapt',pInfo->liveinfo.basePotential))                   {}
				else if ( l.IsChunk( 'bav1') )
				{
					l.StartChunk('bav1');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.baseAssignValue, sizeof(pInfo->liveinfo.baseAssignValue) );
					}   
					l.EndChunk('bav1');
				}
				else if (l.TryReadShortChunk('hrid',(short&)pInfo->liveinfo.hero_id))  {}
				else if (l.TryReadCharChunk('tphj',pInfo->liveinfo.TPHJRank))          {}
				else if (l.TryReadDwordChunk('akp',pInfo->liveinfo.dwKillPlayerSum))  {}
				else if (l.TryReadDwordChunk('wkp',pInfo->liveinfo.dwKillPlayerWeekSum))  {}
				else if (l.TryReadByteChunk('upos',pInfo->liveinfo.uchPosition))  {}
				else if ( l.IsChunk('cold'))
				{
					l.StartChunk('cold');
					{   
						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xItemColdDown, sizeof(pInfo->liveinfo.xItemColdDown));
					}   
					l.EndChunk('cold');
				}
				else if(l.TryReadDwordChunk('cs',pInfo->liveinfo.ConsumeScore))  {}
				else{ l.SkipChunk();}
			}
		}
        else 
            l.SkipChunk();
    }
}

bool CharChunkWR::LoadOtherData( uint8* buffer, uint32 bufferSize, SCharOtherData* pOtherData )
{
    if ( buffer == NULL || bufferSize == 0|| pOtherData == NULL )
    { return false;}

    CDataChunkLoader l( buffer, bufferSize );
    if (l.IsChunk('otda'))
    {
        l.StartChunk('otda');
        {   
            pOtherData->ReadOtherDataBlob( l.GetPointer().byte,l.GetBufferSize());
        }
        l.EndChunk('otda');
    }
    else 
    { l.SkipChunk(); }

    return true;
}
bool CharChunkWR::LoadKillInfo( uint8* buffer,    uint32 bufferSize, SCharOtherData* pOtherData)
{
	if ( buffer == NULL || bufferSize == 0|| pOtherData == NULL )
    { return false;}

    CDataChunkLoader l( buffer, bufferSize );
    if (l.IsChunk('inf1'))
    {
        l.StartChunk('inf1');
        {   
            for(size_t i =0;i<MAX_KILLSUM;++i)
			{
				//读取数组
				pOtherData->KillList[i].PlayerDBID = l.ReadDword();
				pOtherData->KillList[i].Num = (unsigned short)l.ReadShort();
			}
		}
		l.EndChunk('inf1');
    }
    else 
    { l.SkipChunk(); }
    return true;
}
bool CharChunkWR::LoadExtendData( uint8* buffer, uint32 bufferSize, SExtendData* pExtendData )
{
    if ( buffer == NULL || bufferSize == 0 || pExtendData == NULL )
    { return false; }

    CDataChunkLoader l( buffer, bufferSize );

    if (l.IsChunk('exda'))
    {
        l.StartChunk('exda');
        {   
            pExtendData->Read( l.GetPointer().byte, l.GetChunkSize());
        }
        l.EndChunk('exda');
    }
    else 
        l.SkipChunk();

    return true;
}

bool CharChunkWR::LoadAchieveData( uint8* buffer, uint32 bufferSize, SAchieveData* pAchieveData )
{
    if ( buffer == NULL || bufferSize == 0 || pAchieveData == NULL )
    { return false; }

    CDataChunkLoader l( buffer, bufferSize );

    if (l.IsChunk('ahda'))
    {
        l.StartChunk('ahda');
        {   
            pAchieveData->Read( l.GetPointer().byte, l.GetChunkSize());
        }
        l.EndChunk('ahda');
    }
    else 
        l.SkipChunk();

    return true;
}

bool CharChunkWR::LoadIdentifyData( uint8* buffer,    uint32 bufferSize, SIdentifyData* pIdentifyData )
{
    if ( buffer == NULL || bufferSize == 0 || pIdentifyData == NULL )
    { return false; }

    CDataChunkLoader l( buffer, bufferSize );

    if (l.IsChunk('inda'))
    {
        l.StartChunk('inda');
        {   
            pIdentifyData->Read( l.GetPointer().byte, l.GetChunkSize());
        }
        l.EndChunk('inda');
    }
    else 
        l.SkipChunk();

    return true;
}

bool CharChunkWR::LoadVisuals( uint8* buffer, uint32 bufferSize, SCharVisual* pInfo )
{
    if ( buffer == NULL || bufferSize == 0 ||  pInfo == NULL )
    { return false; }

    CDataChunkLoader l( buffer, bufferSize );
    if (l.IsChunk('visl'))
    {
        l.StartChunk('visl');
        pInfo->ReadVisual( l.GetPointer().byte, l.GetBufferSize() );
        l.EndChunk('visl');
    }
    else 
    { l.SkipChunk(); }
    return true;
}
