#include "RankManager.h"
#include "tinyxml.h"
#include "MeRapidXml.h"
#include "zlib/zlib.h"
#include "json/writer.h"

//bool CharChunkWR::WriteCharData( SCharBaseInfo* pInfo, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
//{
//	CDataChunkWriter w( pOutBuffer, outBufferSize );
//
//	w.StartChunk(DC_TAG('apto'));
//	{
//		w.StartChunk(DC_TAG('ap05'));
//		{
//			w.StartChunk(DC_TAG('cn01'));
//			w.WriteString(pInfo->aptotic.szCharacterName);
//			w.EndChunk(DC_TAG('cn01'));
//
//			w.StartChunk(DC_TAG('sx01'));
//			w.WriteChar(pInfo->aptotic.ucSex);
//			w.EndChunk(DC_TAG('sx01'));
//
//			w.StartChunk(DC_TAG('pf01'));
//			w.WriteShort(pInfo->aptotic.usProfession);
//			w.EndChunk(DC_TAG('pf01'));
//
//			w.StartChunk(DC_TAG('hc01'));
//			w.WriteChar(pInfo->aptotic.ucHeadPic);
//			w.EndChunk(DC_TAG('hc01'));
//
//			w.StartChunk(DC_TAG('ct01'));
//			w.WriteChar(pInfo->aptotic.ucCountry);
//			w.EndChunk(DC_TAG('ct01'));
//
//			w.StartChunk(DC_TAG('yn01'));
//			w.WriteString(pInfo->aptotic.szYearName);
//			w.EndChunk(DC_TAG('yn01'));
//
//			w.StartChunk(DC_TAG('yr01'));
//			w.WriteByte(pInfo->aptotic.byYear);
//			w.EndChunk(DC_TAG('yr01'));
//
//			w.StartChunk(DC_TAG('mt01'));
//			w.WriteByte(pInfo->aptotic.byMonth);
//			w.EndChunk(DC_TAG('mt01'));
//
//			w.StartChunk(DC_TAG('dy01'));
//			w.WriteByte(pInfo->aptotic.byDay);
//			w.EndChunk(DC_TAG('dy01'));
//		}
//		w.EndChunk(DC_TAG('ap05'));
//	}
//	w.EndChunk(DC_TAG('apto'));
//
//	w.StartChunk(DC_TAG('live'));
//	{
//		w.OpenChunk('lv10');
//		{
//			w.WriteWordChunk ('levl', pInfo->liveinfo.ustLevel         );
//			w.WriteDwordChunk('mony', pInfo->liveinfo.dwMoney          );
//			w.WriteDwordChunk('repu', pInfo->liveinfo.reputation       );
//			w.WriteDwordChunk('expt', pInfo->liveinfo.exploit          );
//			w.WriteDwordChunk('honr', pInfo->liveinfo.honour           );
//			w.WriteDwordChunk('bls1', pInfo->liveinfo.battleScore      );
//			w.WriteDwordChunk('cos1', pInfo->liveinfo.dwCountryScore   );
//			w.WriteDwordChunk('hpfg', pInfo->liveinfo.dwHelpFlag       );
//			w.WriteDwordChunk('hsct', pInfo->liveinfo.nHighShoutCount  );
//			w.WriteIntChunk  ('hp01', pInfo->liveinfo.nHp              );
//			w.WriteIntChunk  ('mp01', pInfo->liveinfo.nMp              );
//			w.WriteIntChunk  ('xp01', pInfo->liveinfo.nXp              );
//			w.WriteInt64Chunk('exp0', pInfo->liveinfo.dwExp            );
//			w.WriteInt64Chunk('epnu', pInfo->liveinfo.dwExpNotUsed     );
//			w.WriteDwordChunk('slep', pInfo->liveinfo.dwSkillExp       );
//			w.WriteDwordChunk('spnu', pInfo->liveinfo.dwSkillExpNotUsed);
//			w.WriteWordChunk ('seid', pInfo->liveinfo.ustSkillExpForSkillID);
//			w.WriteCharChunk ('nbgs', pInfo->liveinfo.ucNormalBagSize  );
//			w.WriteCharChunk ('mbgs', pInfo->liveinfo.ucMaterialBagSize);
//			w.WriteCharChunk ('moco', pInfo->liveinfo.ucMountCount     );
//			w.WriteWordChunk ('ene1', pInfo->liveinfo.activity         );
//			w.WriteWordChunk ('enm1', pInfo->liveinfo.activityMax      );
//			w.WriteWordChunk ('vig1', pInfo->liveinfo.vigor            );
//			w.WriteWordChunk ('vim1', pInfo->liveinfo.vigorMax         );
//			w.WriteDwordChunk('olt2', pInfo->liveinfo.dwOnlineTime     );
//			w.WriteDwordChunk('olre', pInfo->liveinfo.dwRewardItemInfo );
//			w.WriteShortChunk('ttle', pInfo->liveinfo.nCurrentTitleID  );  //当前称号
//			w.WriteDwordChunk('jzi1', pInfo->liveinfo.jiaoZi           );
//			w.WriteByteChunk ('stig', pInfo->liveinfo.nStorageItemGrid );
//			w.WriteByteChunk ('stmg', pInfo->liveinfo.nStorageMountGrid);
//
//			w.WriteDwordChunk('rlit', pInfo->liveinfo.nRecordReliveTime);
//			w.WriteByteChunk ('flic', pInfo->liveinfo.nFreeReliveCount );
//
//			w.WriteDwordChunk('sdet', pInfo->liveinfo.nSysDoubleExpTime);
//			w.WriteDwordChunk('idet', pInfo->liveinfo.nItemDoubleExpTime);
//
//			w.WriteDwordChunk('daox', pInfo->liveinfo.daoxing);
//
//			//称号列表
//			w.StartChunk(DC_TAG('tt02'));
//			w.Write( pInfo->liveinfo.xTitleData, sizeof(TitleData) * MAX_TITLE_COUNT, 1 );
//			w.EndChunk(DC_TAG('tt02'));
//
//			w.StartChunk(DC_TAG('are1'));
//			w.Write( pInfo->liveinfo.xArea, sizeof( SAreaRepulation ) * MAX_AREAREPULATION_COUNT, 1 );
//			w.EndChunk(DC_TAG('are1'));
//
//			w.StartChunk(DC_TAG('msd2'));
//			w.Write( &pInfo->liveinfo.xMasterData, sizeof( MasterData ) , 1 );
//			w.EndChunk(DC_TAG('msd2'));
//
//			w.WriteWordChunk ('skn1', pInfo->liveinfo.nRecipeSkillNum  );
//
//			w.StartChunk(DC_TAG('skp1'));
//			w.Write( pInfo->liveinfo.nSkillPoint, sizeof( unsigned short ) * ERT_MaxType , 1 );
//			w.EndChunk(DC_TAG('skp1'));
//
//			w.WriteWordChunk ('bapt', pInfo->liveinfo.basePotential  );
//
//			w.StartChunk(DC_TAG('bav1'));
//			w.Write( pInfo->liveinfo.baseAssignValue, sizeof( unsigned short ) * EBaseAttr_MaxSize , 1 );
//			w.EndChunk(DC_TAG('bav1'));
//
//			w.WriteShortChunk('hrid', pInfo->liveinfo.hero_id);
//			w.WriteCharChunk ('tphj', pInfo->liveinfo.TPHJRank);
//			w.WriteDwordChunk('akp', pInfo->liveinfo.dwKillPlayerSum);
//			w.WriteDwordChunk('wkp', pInfo->liveinfo.dwKillPlayerWeekSum);
//
//			w.WriteByteChunk('upos', pInfo->liveinfo.uchPosition);
//
//			w.StartChunk(DC_TAG('cold'));
//			w.Write( pInfo->liveinfo.xItemColdDown, sizeof( SColdDown ) * MAX_SAVERESTORE_COUNT , 1 );
//			w.EndChunk(DC_TAG('cold'));
//		}
//		w.CloseChunk('lv10');
//	}
//	w.EndChunk(DC_TAG('live'));
//
//	nActualSize = w.GetUsedSize();
//	if( nActualSize == 0 )
//	{
//		w.Destroy();
//		return false;
//	}
//
//	if ( nActualSize > outBufferSize )
//	{ 
//		//LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteCharData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
//		return false;
//	}
//
//	w.Destroy();
//	return true;
//}
//
//bool CharChunkWR::WriteItemData( SCharItem* pItem, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
//{
//	CDataChunkWriter w( pOutBuffer, outBufferSize );
//
//	pItem->Write(&w);
//
//	nActualSize = w.GetUsedSize();
//	if( nActualSize == 0 )
//	{
//		w.Destroy();
//		return false;
//	}
//
//	if ( nActualSize > outBufferSize)
//	{ 
//		//LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteItemData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
//		return false;
//	}
//	w.Destroy();
//	return true;
//}
//
//bool CharChunkWR::WriteVisualData( SCharVisual* pInfo, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
//{
//	CDataChunkWriter w( pOutBuffer, outBufferSize );
//	w.StartChunk(DC_TAG('visl'));
//	pInfo->WriteVisual(&w);
//	w.EndChunk(DC_TAG('visl'));
//
//	nActualSize = w.GetUsedSize();
//	if( nActualSize == 0 )
//	{
//		w.Destroy();
//		return false;
//	}
//
//	if ( nActualSize > outBufferSize )
//	{ 
//		//LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteVisualData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
//		return false;
//	}
//	w.Destroy();
//	return true;
//}
//
//bool CharChunkWR::WriteOtherData( SCharOtherData* pOtherData, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
//{
//	CDataChunkWriter w( pOutBuffer, outBufferSize );
//
//	w.StartChunk(DC_TAG('otda'));
//	pOtherData->WriteOtherDataBlob(&w);
//	w.EndChunk(DC_TAG('otda'));
//
//	nActualSize = w.GetUsedSize();
//	if( nActualSize == 0 )
//	{
//		w.Destroy();
//		return false;
//	}
//
//	if ( nActualSize > outBufferSize )
//	{ 
//		//LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteOtherData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
//		return false;
//	}
//	w.Destroy();
//	return true;
//}
//
//bool CharChunkWR::WriteExtendData( SExtendData* pExtendData, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
//{
//	CDataChunkWriter w( pOutBuffer, outBufferSize );
//
//	w.StartChunk(DC_TAG('exda'));
//	pExtendData->Write(&w);
//	w.EndChunk(DC_TAG('exda'));
//
//	nActualSize = w.GetUsedSize();
//	if( nActualSize == 0 )
//	{
//		w.Destroy();
//		return false;
//	}
//
//	if ( nActualSize > outBufferSize )
//	{ 
//		//LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteExtendData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
//		return false;
//	}
//
//	w.Destroy();
//	return true;
//}
//
//bool CharChunkWR::WriteAchieveData( SAchieveData* pAchieveData, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
//{
//	CDataChunkWriter w( pOutBuffer, outBufferSize );
//
//	w.StartChunk(DC_TAG('ahda'));
//	pAchieveData->Write(&w);
//	w.EndChunk(DC_TAG('ahda'));
//
//	nActualSize = w.GetUsedSize();
//	if( nActualSize == 0 )
//	{
//		w.Destroy();
//		return false;
//	}
//
//	if ( nActualSize > outBufferSize )
//	{ 
//		//LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteAchieveData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
//		return false;
//	}
//
//	w.Destroy();
//	return true;
//}
//
//bool CharChunkWR::WriteIdentifyData( SIdentifyData* pIdentifyData, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
//{
//	CDataChunkWriter w( pOutBuffer, outBufferSize );
//
//	w.StartChunk(DC_TAG('inda'));
//	pIdentifyData->Write(&w);
//	w.EndChunk(DC_TAG('inda'));
//
//	nActualSize = w.GetUsedSize();
//	if( nActualSize == 0 )
//	{
//		w.Destroy();
//		return false;
//	}
//
//	if ( nActualSize > outBufferSize )
//	{ 
//		//LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteIdentifyData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
//		return false;
//	}
//
//	w.Destroy();
//	return true;
//}
//
//bool CharChunkWR::WriteMountData ( SMountItem* pMount, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
//{
//	CDataChunkWriter w( pOutBuffer, outBufferSize);
//	pMount->Write(&w);
//
//	nActualSize = w.GetUsedSize();
//	if( nActualSize == 0 )
//	{
//		w.Destroy();
//		return false;
//	}
//
//	if ( nActualSize > outBufferSize )
//	{ 
//		//LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WriteMountData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
//		return false;
//	}
//
//	w.Destroy();
//	return true;
//}
//
//bool CharChunkWR::WritePetData ( SPetItem* pPet, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
//{
//	CDataChunkWriter w( pOutBuffer, outBufferSize);
//	pPet->Write(&w);
//
//	nActualSize = w.GetUsedSize();
//	if( nActualSize == 0 )
//	{
//		w.Destroy();
//		return false;
//	}
//
//	if ( nActualSize > outBufferSize )
//	{ 
//		//LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "WritePetData Chunk(%d)>(%d) ", nActualSize, outBufferSize );
//		return false;
//	}
//
//	w.Destroy();
//	return true;
//}
//
//bool CharChunkWR::LoadCharData( uint8* buffer, uint32 bufferSize, SCharBaseInfo* pInfo)
//{
//	CDataChunkLoader l( buffer, bufferSize );
//
//	while( !l.IsEndOfMemory() )
//	{
//		if( l.IsChunk(  'apto' ) )
//		{
//			l.StartChunk('apto');
//			ReadCharData p( l.GetPointer().c );
//			LoadCharApto( p, l.GetChunkSize(), pInfo );
//			l.EndChunk('apto');
//		}
//		else if (l.IsChunk('live'))
//		{
//			l.StartChunk('live');
//			ReadCharData p( l.GetPointer().c );
//			LoadCharLive( p, l.GetChunkSize(), pInfo );
//			l.EndChunk('live');
//
//		}
//		else 
//		{ l.SkipChunk(); }
//	}
//	return true;
//}
//
//void CharChunkWR::LoadCharApto( ReadCharData inP, int nSize, SCharBaseInfo* pInfo )
//{
//	CDataChunkLoader l(inP.byte,nSize);
//
//	while( !l.IsEndOfMemory() )
//	{
//		if (l.IsChunk('ap05'))
//		{
//			l.StartChunk( 'ap05' );
//			CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//			while (!r.IsEndOfMemory())
//			{
//				if (r.IsChunk('cn01'))
//				{
//					r.StartChunk('cn01');
//					CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());
//
//					int nStrSize = p.ReadInt();
//
//					memset(&pInfo->aptotic.szCharacterName, 0, sizeof(pInfo->aptotic.szCharacterName));
//					memcpy(&pInfo->aptotic.szCharacterName, p.GetPointer().byte, min(sizeof(CHAR)*nStrSize, sizeof(pInfo->aptotic.szCharacterName)));
//					p.GetPointer().c += nStrSize;
//
//					r.EndChunk('cn01');
//				}
//				else if (r.IsChunk('sx01'))
//				{
//					r.StartChunk('sx01');
//					CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());
//					pInfo->aptotic.ucSex = p.ReadChar();
//					r.EndChunk('sx01');
//				}
//				else if (r.IsChunk('pf01'))
//				{
//					r.StartChunk('pf01');
//					CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());
//
//					pInfo->aptotic.usProfession = p.ReadShort();
//					r.EndChunk('pf01');
//				}
//				else if (r.IsChunk('hc01'))
//				{
//					r.StartChunk('hc01');
//					CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());
//
//					pInfo->aptotic.ucHeadPic = p.ReadChar();
//					r.EndChunk('hc01');
//				}
//				else if (r.IsChunk('ct01'))
//				{
//					r.StartChunk('ct01');
//					CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());
//
//					pInfo->aptotic.ucCountry = p.ReadChar();
//					r.EndChunk('ct01');
//				}
//				else if (r.IsChunk('yn01'))
//				{
//					r.StartChunk('yn01');
//					CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());
//
//					int nStrSize1 = p.ReadInt();
//
//					memset(&pInfo->aptotic.szYearName, 0, sizeof(pInfo->aptotic.szYearName));
//					memcpy(&pInfo->aptotic.szYearName, p.GetPointer().byte, min(sizeof(CHAR)*nStrSize1, sizeof(pInfo->aptotic.szYearName)));
//					p.GetPointer().c += nStrSize1;
//
//					r.EndChunk('yn01');
//				}
//				else if (r.IsChunk('yr01'))
//				{
//					r.StartChunk('yr01');
//					CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());
//
//					pInfo->aptotic.byYear = p.ReadByte();
//					r.EndChunk('yr01');
//				}
//				else if (r.IsChunk('mt01'))
//				{
//					r.StartChunk('mt01');
//					CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());
//
//					pInfo->aptotic.byMonth = p.ReadByte();
//					r.EndChunk('mt01');
//				}
//				else if (r.IsChunk('dy01'))
//				{
//					r.StartChunk('dy01');
//					CDataChunkLoader p(r.GetPointer().byte,r.GetChunkSize());
//
//					pInfo->aptotic.byDay = p.ReadByte();
//					r.EndChunk('dy01');
//				}
//				else
//					r.SkipChunk();
//			}                
//			l.EndChunk('ap05');
//		}
//		else 
//			l.SkipChunk();
//	}
//}
//void CharChunkWR::LoadCharLive( ReadCharData inP, int nSize, SCharBaseInfo* pInfo )
//{
//	CDataChunkLoader l(inP.byte,nSize);
//	while( !l.IsEndOfMemory() )
//	{
//		if (l.IsChunk('lv05'))
//		{
//			l.OpenChunk();
//			short stTemp = -1;
//			pInfo->liveinfo.hero_id = INVALID_HERO_ID;
//			while (!l.IsEndOfChunk())
//			{
//				if(l.TryReadWordChunk('levl',pInfo->liveinfo.ustLevel))                   {}
//				else if (l.TryReadDwordChunk('mony',pInfo->liveinfo.dwMoney))             {}
//				else if (l.TryReadDwordChunk('repu',pInfo->liveinfo.reputation))          {}
//				else if (l.TryReadDwordChunk('expt',pInfo->liveinfo.exploit))             {}
//				else if (l.TryReadDwordChunk('honr',pInfo->liveinfo.honour))              {}
//				else if (l.TryReadDwordChunk('bls1', pInfo->liveinfo.battleScore))        {}
//				else if (l.TryReadDwordChunk('cos1', pInfo->liveinfo.dwCountryScore))     {}
//				else if (l.TryReadDwordChunk('sile',pInfo->liveinfo.jinDing))             {}
//				else if (l.TryReadDwordChunk('prsr',pInfo->liveinfo.jinPiao))             {}
//				else if (l.TryReadDwordChunk('hpfg',pInfo->liveinfo.dwHelpFlag))          {}
//				else if (l.TryReadDwordChunk('hsct',pInfo->liveinfo.nHighShoutCount))     {}
//				else if (l.TryReadIntChunk('hp01', pInfo->liveinfo.nHp))                  {}
//				else if (l.TryReadIntChunk('mp01', pInfo->liveinfo.nMp))                  {}
//				else if (l.TryReadIntChunk('xp01', pInfo->liveinfo.nXp))                  {}
//				else if (l.TryReadInt64Chunk('exp0', pInfo->liveinfo.dwExp))              {}
//				else if (l.TryReadInt64Chunk('epnu', pInfo->liveinfo.dwExpNotUsed))       {}
//				else if (l.TryReadDwordChunk('slep', pInfo->liveinfo.dwSkillExp))         {}
//				else if (l.TryReadDwordChunk('spnu', pInfo->liveinfo.dwSkillExpNotUsed))  {}                
//				else if (l.TryReadWordChunk('seid',pInfo->liveinfo.ustSkillExpForSkillID)){}
//				else if (l.TryReadByteChunk('nbgs',pInfo->liveinfo.ucNormalBagSize))      {}
//				else if (l.TryReadByteChunk('mbgs',pInfo->liveinfo.ucMaterialBagSize))    {}
//				else if (l.TryReadByteChunk('moco',pInfo->liveinfo.ucMountCount))         {}
//				else if (l.TryReadWordChunk('ene1',pInfo->liveinfo.activity))             {}
//				else if (l.TryReadWordChunk('enm1',pInfo->liveinfo.activityMax))          {}
//				else if (l.TryReadWordChunk('vig1',pInfo->liveinfo.vigor))                {}
//				else if (l.TryReadWordChunk('vim1',pInfo->liveinfo.vigorMax))             {}
//				else if (l.TryReadDwordChunk('olt1', pInfo->liveinfo.dwOnlineTime))       { pInfo->liveinfo.dwOnlineTime /= 60000; }  // 以前是毫秒 NND
//				else if (l.TryReadDwordChunk('olt2', pInfo->liveinfo.dwOnlineTime))       {}     
//				else if (l.TryReadDwordChunk('olre', pInfo->liveinfo.dwRewardItemInfo))   {}
//				else if (l.TryReadShortChunk('ttle',pInfo->liveinfo.nCurrentTitleID))     {}
//				else if (l.TryReadDwordChunk('jzi1',pInfo->liveinfo.jiaoZi))              {}
//				else if (l.TryReadByteChunk('stig',pInfo->liveinfo.nStorageItemGrid))     {}
//				else if (l.TryReadByteChunk('stmg',pInfo->liveinfo.nStorageMountGrid))    {}
//
//				else if (l.TryReadDwordChunk('rlit',pInfo->liveinfo.nRecordReliveTime))   {}
//				else if (l.TryReadByteChunk ('flic',pInfo->liveinfo.nFreeReliveCount))    {}
//
//				else if (l.TryReadDwordChunk('sdet',pInfo->liveinfo.nSysDoubleExpTime))   {}
//				else if (l.TryReadDwordChunk('idet',pInfo->liveinfo.nItemDoubleExpTime))  {}
//
//				else if (l.TryReadDwordChunk('daox',pInfo->liveinfo.daoxing))  {}
//
//				else if (l.IsChunk('tt01'))
//				{
//					l.StartChunk('tt01');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						short nTitleArray[MAX_TITLE_COUNT];
//						memset( nTitleArray, 0, sizeof( nTitleArray ) );
//						r.ReadToBuffer( (BYTE*)nTitleArray, sizeof(nTitleArray) );
//						for ( int i = 0; i < MAX_TITLE_COUNT; ++i )
//						{
//							pInfo->liveinfo.xTitleData[i].SetTitleID( nTitleArray[i] );
//						}
//					}   
//					l.EndChunk('tt01');
//				}
//				else if (l.IsChunk('tt02'))
//				{
//					l.StartChunk('tt02');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xTitleData, sizeof(pInfo->liveinfo.xTitleData));
//					}   
//					l.EndChunk('tt02');
//				}
//				else if ( l.IsChunk('are1') )
//				{
//					l.StartChunk('are1');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xArea, sizeof(pInfo->liveinfo.xArea));
//					}   
//					l.EndChunk('are1');
//				}
//				else if ( l.IsChunk('msd2') )
//				{
//					l.StartChunk('msd2');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer((BYTE*)&pInfo->liveinfo.xMasterData, sizeof(pInfo->liveinfo.xMasterData));
//					}   
//					l.EndChunk('msd2');
//				}
//				else if(l.TryReadWordChunk('skn1',pInfo->liveinfo.nRecipeSkillNum))                   {}
//				else if ( l.IsChunk( 'skp1') )
//				{
//					l.StartChunk('skp1');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.nSkillPoint, sizeof(pInfo->liveinfo.nSkillPoint) );
//					}   
//					l.EndChunk('skp1');
//				}
//				else if(l.TryReadWordChunk('bapt',pInfo->liveinfo.basePotential))                   {}
//				else if ( l.IsChunk( 'bav1') )
//				{
//					l.StartChunk('bav1');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.baseAssignValue, sizeof(pInfo->liveinfo.baseAssignValue) );
//					}   
//					l.EndChunk('bav1');
//				}
//
//				else{ l.SkipChunk();}
//
//				pInfo->liveinfo.uchPosition = 0xFF;//标记当前玩家的职位不目前 在玩家初始化函数重新获取职位
//			}
//		}
//		if (l.IsChunk('lv06'))
//		{
//			l.OpenChunk();
//			short stTemp = -1;
//			while (!l.IsEndOfChunk())
//			{
//				if(l.TryReadWordChunk('levl',pInfo->liveinfo.ustLevel))                   {}
//				else if (l.TryReadDwordChunk('mony',pInfo->liveinfo.dwMoney))             {}
//				else if (l.TryReadDwordChunk('repu',pInfo->liveinfo.reputation))          {}
//				else if (l.TryReadDwordChunk('expt',pInfo->liveinfo.exploit))             {}
//				else if (l.TryReadDwordChunk('honr',pInfo->liveinfo.honour))              {}
//				else if (l.TryReadDwordChunk('bls1', pInfo->liveinfo.battleScore))        {}
//				else if (l.TryReadDwordChunk('cos1', pInfo->liveinfo.dwCountryScore))     {}
//				else if (l.TryReadDwordChunk('sile',pInfo->liveinfo.jinDing))             {}
//				else if (l.TryReadDwordChunk('prsr',pInfo->liveinfo.jinPiao))             {}
//				else if (l.TryReadDwordChunk('hpfg',pInfo->liveinfo.dwHelpFlag))          {}
//				else if (l.TryReadDwordChunk('hsct',pInfo->liveinfo.nHighShoutCount))     {}
//				else if (l.TryReadIntChunk('hp01', pInfo->liveinfo.nHp))                  {}
//				else if (l.TryReadIntChunk('mp01', pInfo->liveinfo.nMp))                  {}
//				else if (l.TryReadIntChunk('xp01', pInfo->liveinfo.nXp))                  {}
//				else if (l.TryReadInt64Chunk('exp0', pInfo->liveinfo.dwExp))              {}
//				else if (l.TryReadInt64Chunk('epnu', pInfo->liveinfo.dwExpNotUsed))       {}
//				else if (l.TryReadDwordChunk('slep', pInfo->liveinfo.dwSkillExp))         {}
//				else if (l.TryReadDwordChunk('spnu', pInfo->liveinfo.dwSkillExpNotUsed))  {}                
//				else if (l.TryReadWordChunk('seid',pInfo->liveinfo.ustSkillExpForSkillID)){}
//				else if (l.TryReadByteChunk('nbgs',pInfo->liveinfo.ucNormalBagSize))      {}
//				else if (l.TryReadByteChunk('mbgs',pInfo->liveinfo.ucMaterialBagSize))    {}
//				else if (l.TryReadByteChunk('moco',pInfo->liveinfo.ucMountCount))         {}
//				else if (l.TryReadWordChunk('ene1',pInfo->liveinfo.activity))             {}
//				else if (l.TryReadWordChunk('enm1',pInfo->liveinfo.activityMax))          {}
//				else if (l.TryReadWordChunk('vig1',pInfo->liveinfo.vigor))                {}
//				else if (l.TryReadWordChunk('vim1',pInfo->liveinfo.vigorMax))             {}
//				else if (l.TryReadDwordChunk('olt1', pInfo->liveinfo.dwOnlineTime))       { pInfo->liveinfo.dwOnlineTime /= 60000; }  // 以前是毫秒 NND
//				else if (l.TryReadDwordChunk('olt2', pInfo->liveinfo.dwOnlineTime))       {}     
//				else if (l.TryReadDwordChunk('olre', pInfo->liveinfo.dwRewardItemInfo))   {}
//				else if (l.TryReadShortChunk('ttle',pInfo->liveinfo.nCurrentTitleID))     {}
//				else if (l.TryReadDwordChunk('jzi1',pInfo->liveinfo.jiaoZi))              {}
//				else if (l.TryReadByteChunk('stig',pInfo->liveinfo.nStorageItemGrid))     {}
//				else if (l.TryReadByteChunk('stmg',pInfo->liveinfo.nStorageMountGrid))    {}
//
//				else if (l.TryReadDwordChunk('rlit',pInfo->liveinfo.nRecordReliveTime))   {}
//				else if (l.TryReadByteChunk ('flic',pInfo->liveinfo.nFreeReliveCount))    {}
//
//				else if (l.TryReadDwordChunk('sdet',pInfo->liveinfo.nSysDoubleExpTime))   {}
//				else if (l.TryReadDwordChunk('idet',pInfo->liveinfo.nItemDoubleExpTime))  {}
//
//				else if (l.TryReadDwordChunk('daox',pInfo->liveinfo.daoxing))  {}
//
//				else if (l.IsChunk('tt01'))
//				{
//					l.StartChunk('tt01');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						short nTitleArray[MAX_TITLE_COUNT];
//						memset( nTitleArray, 0, sizeof( nTitleArray ) );
//						r.ReadToBuffer( (BYTE*)nTitleArray, sizeof(nTitleArray) );
//						for ( int i = 0; i < MAX_TITLE_COUNT; ++i )
//						{
//							pInfo->liveinfo.xTitleData[i].SetTitleID( nTitleArray[i] );
//						}
//					}   
//					l.EndChunk('tt01');
//				}
//				else if (l.IsChunk('tt02'))
//				{
//					l.StartChunk('tt02');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xTitleData, sizeof(pInfo->liveinfo.xTitleData));
//					}   
//					l.EndChunk('tt02');
//				}
//				else if ( l.IsChunk('are1') )
//				{
//					l.StartChunk('are1');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xArea, sizeof(pInfo->liveinfo.xArea));
//					}   
//					l.EndChunk('are1');
//				}
//				else if ( l.IsChunk('msd2') )
//				{
//					l.StartChunk('msd2');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer((BYTE*)&pInfo->liveinfo.xMasterData, sizeof(pInfo->liveinfo.xMasterData));
//					}   
//					l.EndChunk('msd2');
//				}
//				else if(l.TryReadWordChunk('skn1',pInfo->liveinfo.nRecipeSkillNum))                   {}
//				else if ( l.IsChunk( 'skp1') )
//				{
//					l.StartChunk('skp1');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.nSkillPoint, sizeof(pInfo->liveinfo.nSkillPoint) );
//					}   
//					l.EndChunk('skp1');
//				}
//				else if(l.TryReadWordChunk('bapt',pInfo->liveinfo.basePotential))                   {}
//				else if ( l.IsChunk( 'bav1') )
//				{
//					l.StartChunk('bav1');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.baseAssignValue, sizeof(pInfo->liveinfo.baseAssignValue) );
//					}   
//					l.EndChunk('bav1');
//				}
//				else if (l.TryReadShortChunk('hrid',(short&)pInfo->liveinfo.hero_id))  {}
//
//				else{ l.SkipChunk();}
//
//				pInfo->liveinfo.uchPosition = 0xFF;//标记当前玩家的职位不目前 在玩家初始化函数重新获取职位
//			}
//		}
//		if (l.IsChunk('lv07'))
//		{
//			l.OpenChunk();
//			short stTemp = -1;
//			while (!l.IsEndOfChunk())
//			{
//				if(l.TryReadWordChunk('levl',pInfo->liveinfo.ustLevel))                   {}
//				else if (l.TryReadDwordChunk('mony',pInfo->liveinfo.dwMoney))             {}
//				else if (l.TryReadDwordChunk('repu',pInfo->liveinfo.reputation))          {}
//				else if (l.TryReadDwordChunk('expt',pInfo->liveinfo.exploit))             {}
//				else if (l.TryReadDwordChunk('honr',pInfo->liveinfo.honour))              {}
//				else if (l.TryReadDwordChunk('bls1', pInfo->liveinfo.battleScore))        {}
//				else if (l.TryReadDwordChunk('cos1', pInfo->liveinfo.dwCountryScore))     {}
//				else if (l.TryReadDwordChunk('sile',pInfo->liveinfo.jinDing))             {}
//				else if (l.TryReadDwordChunk('prsr',pInfo->liveinfo.jinPiao))             {}
//				else if (l.TryReadDwordChunk('hpfg',pInfo->liveinfo.dwHelpFlag))          {}
//				else if (l.TryReadDwordChunk('hsct',pInfo->liveinfo.nHighShoutCount))     {}
//				else if (l.TryReadIntChunk('hp01', pInfo->liveinfo.nHp))                  {}
//				else if (l.TryReadIntChunk('mp01', pInfo->liveinfo.nMp))                  {}
//				else if (l.TryReadIntChunk('xp01', pInfo->liveinfo.nXp))                  {}
//				else if (l.TryReadInt64Chunk('exp0', pInfo->liveinfo.dwExp))              {}
//				else if (l.TryReadInt64Chunk('epnu', pInfo->liveinfo.dwExpNotUsed))       {}
//				else if (l.TryReadDwordChunk('slep', pInfo->liveinfo.dwSkillExp))         {}
//				else if (l.TryReadDwordChunk('spnu', pInfo->liveinfo.dwSkillExpNotUsed))  {}                
//				else if (l.TryReadWordChunk('seid',pInfo->liveinfo.ustSkillExpForSkillID)){}
//				else if (l.TryReadByteChunk('nbgs',pInfo->liveinfo.ucNormalBagSize))      {}
//				else if (l.TryReadByteChunk('mbgs',pInfo->liveinfo.ucMaterialBagSize))    {}
//				else if (l.TryReadByteChunk('moco',pInfo->liveinfo.ucMountCount))         {}
//				else if (l.TryReadWordChunk('ene1',pInfo->liveinfo.activity))             {}
//				else if (l.TryReadWordChunk('enm1',pInfo->liveinfo.activityMax))          {}
//				else if (l.TryReadWordChunk('vig1',pInfo->liveinfo.vigor))                {}
//				else if (l.TryReadWordChunk('vim1',pInfo->liveinfo.vigorMax))             {}
//				else if (l.TryReadDwordChunk('olt1', pInfo->liveinfo.dwOnlineTime))       { pInfo->liveinfo.dwOnlineTime /= 60000; }  // 以前是毫秒 NND
//				else if (l.TryReadDwordChunk('olt2', pInfo->liveinfo.dwOnlineTime))       {}     
//				else if (l.TryReadDwordChunk('olre', pInfo->liveinfo.dwRewardItemInfo))   {}
//				else if (l.TryReadShortChunk('ttle',pInfo->liveinfo.nCurrentTitleID))     {}
//				else if (l.TryReadDwordChunk('jzi1',pInfo->liveinfo.jiaoZi))              {}
//				else if (l.TryReadByteChunk('stig',pInfo->liveinfo.nStorageItemGrid))     {}
//				else if (l.TryReadByteChunk('stmg',pInfo->liveinfo.nStorageMountGrid))    {}
//
//				else if (l.TryReadDwordChunk('rlit',pInfo->liveinfo.nRecordReliveTime))   {}
//				else if (l.TryReadByteChunk ('flic',pInfo->liveinfo.nFreeReliveCount))    {}
//
//				else if (l.TryReadDwordChunk('sdet',pInfo->liveinfo.nSysDoubleExpTime))   {}
//				else if (l.TryReadDwordChunk('idet',pInfo->liveinfo.nItemDoubleExpTime))  {}
//
//				else if (l.TryReadDwordChunk('daox',pInfo->liveinfo.daoxing))  {}
//
//				else if (l.IsChunk('tt01'))
//				{
//					l.StartChunk('tt01');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						short nTitleArray[MAX_TITLE_COUNT];
//						memset( nTitleArray, 0, sizeof( nTitleArray ) );
//						r.ReadToBuffer( (BYTE*)nTitleArray, sizeof(nTitleArray) );
//						for ( int i = 0; i < MAX_TITLE_COUNT; ++i )
//						{
//							pInfo->liveinfo.xTitleData[i].SetTitleID( nTitleArray[i] );
//						}
//					}   
//					l.EndChunk('tt01');
//				}
//				else if (l.IsChunk('tt02'))
//				{
//					l.StartChunk('tt02');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xTitleData, sizeof(pInfo->liveinfo.xTitleData));
//					}   
//					l.EndChunk('tt02');
//				}
//				else if ( l.IsChunk('are1') )
//				{
//					l.StartChunk('are1');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xArea, sizeof(pInfo->liveinfo.xArea));
//					}   
//					l.EndChunk('are1');
//				}
//				else if ( l.IsChunk('msd2') )
//				{
//					l.StartChunk('msd2');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer((BYTE*)&pInfo->liveinfo.xMasterData, sizeof(pInfo->liveinfo.xMasterData));
//					}   
//					l.EndChunk('msd2');
//				}
//				else if(l.TryReadWordChunk('skn1',pInfo->liveinfo.nRecipeSkillNum))                   {}
//				else if ( l.IsChunk( 'skp1') )
//				{
//					l.StartChunk('skp1');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.nSkillPoint, sizeof(pInfo->liveinfo.nSkillPoint) );
//					}   
//					l.EndChunk('skp1');
//				}
//				else if(l.TryReadWordChunk('bapt',pInfo->liveinfo.basePotential))                   {}
//				else if ( l.IsChunk( 'bav1') )
//				{
//					l.StartChunk('bav1');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.baseAssignValue, sizeof(pInfo->liveinfo.baseAssignValue) );
//					}   
//					l.EndChunk('bav1');
//				}
//				else if (l.TryReadShortChunk('hrid',(short&)pInfo->liveinfo.hero_id))  {}
//				else if (l.TryReadCharChunk('tphj',pInfo->liveinfo.TPHJRank))          {}
//				else{ l.SkipChunk();}
//
//				pInfo->liveinfo.uchPosition = 0xFF;//标记当前玩家的职位不目前 在玩家初始化函数重新获取职位
//			}
//		}
//		if (l.IsChunk('lv08'))
//		{
//			l.OpenChunk();
//			short stTemp = -1;
//			while (!l.IsEndOfChunk())
//			{
//				if(l.TryReadWordChunk('levl',pInfo->liveinfo.ustLevel))                   {}
//				else if (l.TryReadDwordChunk('mony',pInfo->liveinfo.dwMoney))             {}
//				else if (l.TryReadDwordChunk('repu',pInfo->liveinfo.reputation))          {}
//				else if (l.TryReadDwordChunk('expt',pInfo->liveinfo.exploit))             {}
//				else if (l.TryReadDwordChunk('honr',pInfo->liveinfo.honour))              {}
//				else if (l.TryReadDwordChunk('bls1', pInfo->liveinfo.battleScore))        {}
//				else if (l.TryReadDwordChunk('cos1', pInfo->liveinfo.dwCountryScore))     {}
//				else if (l.TryReadDwordChunk('sile',pInfo->liveinfo.jinDing))             {}
//				else if (l.TryReadDwordChunk('prsr',pInfo->liveinfo.jinPiao))             {}
//				else if (l.TryReadDwordChunk('hpfg',pInfo->liveinfo.dwHelpFlag))          {}
//				else if (l.TryReadDwordChunk('hsct',pInfo->liveinfo.nHighShoutCount))     {}
//				else if (l.TryReadIntChunk('hp01', pInfo->liveinfo.nHp))                  {}
//				else if (l.TryReadIntChunk('mp01', pInfo->liveinfo.nMp))                  {}
//				else if (l.TryReadIntChunk('xp01', pInfo->liveinfo.nXp))                  {}
//				else if (l.TryReadInt64Chunk('exp0', pInfo->liveinfo.dwExp))              {}
//				else if (l.TryReadInt64Chunk('epnu', pInfo->liveinfo.dwExpNotUsed))       {}
//				else if (l.TryReadDwordChunk('slep', pInfo->liveinfo.dwSkillExp))         {}
//				else if (l.TryReadDwordChunk('spnu', pInfo->liveinfo.dwSkillExpNotUsed))  {}                
//				else if (l.TryReadWordChunk('seid',pInfo->liveinfo.ustSkillExpForSkillID)){}
//				else if (l.TryReadByteChunk('nbgs',pInfo->liveinfo.ucNormalBagSize))      {}
//				else if (l.TryReadByteChunk('mbgs',pInfo->liveinfo.ucMaterialBagSize))    {}
//				else if (l.TryReadByteChunk('moco',pInfo->liveinfo.ucMountCount))         {}
//				else if (l.TryReadWordChunk('ene1',pInfo->liveinfo.activity))             {}
//				else if (l.TryReadWordChunk('enm1',pInfo->liveinfo.activityMax))          {}
//				else if (l.TryReadWordChunk('vig1',pInfo->liveinfo.vigor))                {}
//				else if (l.TryReadWordChunk('vim1',pInfo->liveinfo.vigorMax))             {}
//				else if (l.TryReadDwordChunk('olt1', pInfo->liveinfo.dwOnlineTime))       { pInfo->liveinfo.dwOnlineTime /= 60000; }  // 以前是毫秒 NND
//				else if (l.TryReadDwordChunk('olt2', pInfo->liveinfo.dwOnlineTime))       {}     
//				else if (l.TryReadDwordChunk('olre', pInfo->liveinfo.dwRewardItemInfo))   {}
//				else if (l.TryReadShortChunk('ttle',pInfo->liveinfo.nCurrentTitleID))     {}
//				else if (l.TryReadDwordChunk('jzi1',pInfo->liveinfo.jiaoZi))              {}
//				else if (l.TryReadByteChunk('stig',pInfo->liveinfo.nStorageItemGrid))     {}
//				else if (l.TryReadByteChunk('stmg',pInfo->liveinfo.nStorageMountGrid))    {}
//
//				else if (l.TryReadDwordChunk('rlit',pInfo->liveinfo.nRecordReliveTime))   {}
//				else if (l.TryReadByteChunk ('flic',pInfo->liveinfo.nFreeReliveCount))    {}
//
//				else if (l.TryReadDwordChunk('sdet',pInfo->liveinfo.nSysDoubleExpTime))   {}
//				else if (l.TryReadDwordChunk('idet',pInfo->liveinfo.nItemDoubleExpTime))  {}
//
//				else if (l.TryReadDwordChunk('daox',pInfo->liveinfo.daoxing))  {}
//
//				else if (l.IsChunk('tt01'))
//				{
//					l.StartChunk('tt01');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						short nTitleArray[MAX_TITLE_COUNT];
//						memset( nTitleArray, 0, sizeof( nTitleArray ) );
//						r.ReadToBuffer( (BYTE*)nTitleArray, sizeof(nTitleArray) );
//						for ( int i = 0; i < MAX_TITLE_COUNT; ++i )
//						{
//							pInfo->liveinfo.xTitleData[i].SetTitleID( nTitleArray[i] );
//						}
//					}   
//					l.EndChunk('tt01');
//				}
//				else if (l.IsChunk('tt02'))
//				{
//					l.StartChunk('tt02');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xTitleData, sizeof(pInfo->liveinfo.xTitleData));
//					}   
//					l.EndChunk('tt02');
//				}
//				else if ( l.IsChunk('are1') )
//				{
//					l.StartChunk('are1');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xArea, sizeof(pInfo->liveinfo.xArea));
//					}   
//					l.EndChunk('are1');
//				}
//				else if ( l.IsChunk('msd2') )
//				{
//					l.StartChunk('msd2');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer((BYTE*)&pInfo->liveinfo.xMasterData, sizeof(pInfo->liveinfo.xMasterData));
//					}   
//					l.EndChunk('msd2');
//				}
//				else if(l.TryReadWordChunk('skn1',pInfo->liveinfo.nRecipeSkillNum))                   {}
//				else if ( l.IsChunk( 'skp1') )
//				{
//					l.StartChunk('skp1');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.nSkillPoint, sizeof(pInfo->liveinfo.nSkillPoint) );
//					}   
//					l.EndChunk('skp1');
//				}
//				else if(l.TryReadWordChunk('bapt',pInfo->liveinfo.basePotential))                   {}
//				else if ( l.IsChunk( 'bav1') )
//				{
//					l.StartChunk('bav1');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.baseAssignValue, sizeof(pInfo->liveinfo.baseAssignValue) );
//					}   
//					l.EndChunk('bav1');
//				}
//				else if (l.TryReadShortChunk('hrid',(short&)pInfo->liveinfo.hero_id))  {}
//				else if (l.TryReadCharChunk('tphj',pInfo->liveinfo.TPHJRank))          {}
//				else if (l.TryReadDwordChunk('akp',pInfo->liveinfo.dwKillPlayerSum))  {}
//				else if (l.TryReadDwordChunk('wkp',pInfo->liveinfo.dwKillPlayerWeekSum))  {}
//				else{ l.SkipChunk();}
//
//				pInfo->liveinfo.uchPosition = 0xFF;//标记当前玩家的职位不目前 在玩家初始化函数重新获取职位
//			}
//		}
//		if (l.IsChunk('lv09'))
//		{
//			l.OpenChunk();
//			short stTemp = -1;
//			while (!l.IsEndOfChunk())
//			{
//				if(l.TryReadWordChunk('levl',pInfo->liveinfo.ustLevel))                   {}
//				else if (l.TryReadDwordChunk('mony',pInfo->liveinfo.dwMoney))             {}
//				else if (l.TryReadDwordChunk('repu',pInfo->liveinfo.reputation))          {}
//				else if (l.TryReadDwordChunk('expt',pInfo->liveinfo.exploit))             {}
//				else if (l.TryReadDwordChunk('honr',pInfo->liveinfo.honour))              {}
//				else if (l.TryReadDwordChunk('bls1', pInfo->liveinfo.battleScore))        {}
//				else if (l.TryReadDwordChunk('cos1', pInfo->liveinfo.dwCountryScore))     {}
//				else if (l.TryReadDwordChunk('sile',pInfo->liveinfo.jinDing))             {}
//				else if (l.TryReadDwordChunk('prsr',pInfo->liveinfo.jinPiao))             {}
//				else if (l.TryReadDwordChunk('hpfg',pInfo->liveinfo.dwHelpFlag))          {}
//				else if (l.TryReadDwordChunk('hsct',pInfo->liveinfo.nHighShoutCount))     {}
//				else if (l.TryReadIntChunk('hp01', pInfo->liveinfo.nHp))                  {}
//				else if (l.TryReadIntChunk('mp01', pInfo->liveinfo.nMp))                  {}
//				else if (l.TryReadIntChunk('xp01', pInfo->liveinfo.nXp))                  {}
//				else if (l.TryReadInt64Chunk('exp0', pInfo->liveinfo.dwExp))              {}
//				else if (l.TryReadInt64Chunk('epnu', pInfo->liveinfo.dwExpNotUsed))       {}
//				else if (l.TryReadDwordChunk('slep', pInfo->liveinfo.dwSkillExp))         {}
//				else if (l.TryReadDwordChunk('spnu', pInfo->liveinfo.dwSkillExpNotUsed))  {}                
//				else if (l.TryReadWordChunk('seid',pInfo->liveinfo.ustSkillExpForSkillID)){}
//				else if (l.TryReadByteChunk('nbgs',pInfo->liveinfo.ucNormalBagSize))      {}
//				else if (l.TryReadByteChunk('mbgs',pInfo->liveinfo.ucMaterialBagSize))    {}
//				else if (l.TryReadByteChunk('moco',pInfo->liveinfo.ucMountCount))         {}
//				else if (l.TryReadWordChunk('ene1',pInfo->liveinfo.activity))             {}
//				else if (l.TryReadWordChunk('enm1',pInfo->liveinfo.activityMax))          {}
//				else if (l.TryReadWordChunk('vig1',pInfo->liveinfo.vigor))                {}
//				else if (l.TryReadWordChunk('vim1',pInfo->liveinfo.vigorMax))             {}
//				else if (l.TryReadDwordChunk('olt1', pInfo->liveinfo.dwOnlineTime))       { pInfo->liveinfo.dwOnlineTime /= 60000; }  // 以前是毫秒 NND
//				else if (l.TryReadDwordChunk('olt2', pInfo->liveinfo.dwOnlineTime))       {}     
//				else if (l.TryReadDwordChunk('olre', pInfo->liveinfo.dwRewardItemInfo))   {}
//				else if (l.TryReadShortChunk('ttle',pInfo->liveinfo.nCurrentTitleID))     {}
//				else if (l.TryReadDwordChunk('jzi1',pInfo->liveinfo.jiaoZi))              {}
//				else if (l.TryReadByteChunk('stig',pInfo->liveinfo.nStorageItemGrid))     {}
//				else if (l.TryReadByteChunk('stmg',pInfo->liveinfo.nStorageMountGrid))    {}
//
//				else if (l.TryReadDwordChunk('rlit',pInfo->liveinfo.nRecordReliveTime))   {}
//				else if (l.TryReadByteChunk ('flic',pInfo->liveinfo.nFreeReliveCount))    {}
//
//				else if (l.TryReadDwordChunk('sdet',pInfo->liveinfo.nSysDoubleExpTime))   {}
//				else if (l.TryReadDwordChunk('idet',pInfo->liveinfo.nItemDoubleExpTime))  {}
//
//				else if (l.TryReadDwordChunk('daox',pInfo->liveinfo.daoxing))  {}
//
//				else if (l.IsChunk('tt01'))
//				{
//					l.StartChunk('tt01');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						short nTitleArray[MAX_TITLE_COUNT];
//						memset( nTitleArray, 0, sizeof( nTitleArray ) );
//						r.ReadToBuffer( (BYTE*)nTitleArray, sizeof(nTitleArray) );
//						for ( int i = 0; i < MAX_TITLE_COUNT; ++i )
//						{
//							pInfo->liveinfo.xTitleData[i].SetTitleID( nTitleArray[i] );
//						}
//					}   
//					l.EndChunk('tt01');
//				}
//				else if (l.IsChunk('tt02'))
//				{
//					l.StartChunk('tt02');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xTitleData, sizeof(pInfo->liveinfo.xTitleData));
//					}   
//					l.EndChunk('tt02');
//				}
//				else if ( l.IsChunk('are1') )
//				{
//					l.StartChunk('are1');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xArea, sizeof(pInfo->liveinfo.xArea));
//					}   
//					l.EndChunk('are1');
//				}
//				else if ( l.IsChunk('msd2') )
//				{
//					l.StartChunk('msd2');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer((BYTE*)&pInfo->liveinfo.xMasterData, sizeof(pInfo->liveinfo.xMasterData));
//					}   
//					l.EndChunk('msd2');
//				}
//				else if(l.TryReadWordChunk('skn1',pInfo->liveinfo.nRecipeSkillNum))                   {}
//				else if ( l.IsChunk( 'skp1') )
//				{
//					l.StartChunk('skp1');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.nSkillPoint, sizeof(pInfo->liveinfo.nSkillPoint) );
//					}   
//					l.EndChunk('skp1');
//				}
//				else if(l.TryReadWordChunk('bapt',pInfo->liveinfo.basePotential))                   {}
//				else if ( l.IsChunk( 'bav1') )
//				{
//					l.StartChunk('bav1');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.baseAssignValue, sizeof(pInfo->liveinfo.baseAssignValue) );
//					}   
//					l.EndChunk('bav1');
//				}
//				else if (l.TryReadShortChunk('hrid',(short&)pInfo->liveinfo.hero_id))  {}
//				else if (l.TryReadCharChunk('tphj',pInfo->liveinfo.TPHJRank))          {}
//				else if (l.TryReadDwordChunk('akp',pInfo->liveinfo.dwKillPlayerSum))  {}
//				else if (l.TryReadDwordChunk('wkp',pInfo->liveinfo.dwKillPlayerWeekSum))  {}
//				else if (l.TryReadByteChunk('upos',pInfo->liveinfo.uchPosition))  {}
//				else{ l.SkipChunk();}
//			}
//		}
//		else if (l.IsChunk('lv10'))
//		{
//			l.OpenChunk();
//			short stTemp = -1;
//			while (!l.IsEndOfChunk())
//			{
//				if(l.TryReadWordChunk('levl',pInfo->liveinfo.ustLevel))                   {}
//				else if (l.TryReadDwordChunk('mony',pInfo->liveinfo.dwMoney))             {}
//				else if (l.TryReadDwordChunk('repu',pInfo->liveinfo.reputation))          {}
//				else if (l.TryReadDwordChunk('expt',pInfo->liveinfo.exploit))             {}
//				else if (l.TryReadDwordChunk('honr',pInfo->liveinfo.honour))              {}
//				else if (l.TryReadDwordChunk('bls1', pInfo->liveinfo.battleScore))        {}
//				else if (l.TryReadDwordChunk('cos1', pInfo->liveinfo.dwCountryScore))     {}
//				else if (l.TryReadDwordChunk('sile',pInfo->liveinfo.jinDing))             {}
//				else if (l.TryReadDwordChunk('prsr',pInfo->liveinfo.jinPiao))             {}
//				else if (l.TryReadDwordChunk('hpfg',pInfo->liveinfo.dwHelpFlag))          {}
//				else if (l.TryReadDwordChunk('hsct',pInfo->liveinfo.nHighShoutCount))     {}
//				else if (l.TryReadIntChunk('hp01', pInfo->liveinfo.nHp))                  {}
//				else if (l.TryReadIntChunk('mp01', pInfo->liveinfo.nMp))                  {}
//				else if (l.TryReadIntChunk('xp01', pInfo->liveinfo.nXp))                  {}
//				else if (l.TryReadInt64Chunk('exp0', pInfo->liveinfo.dwExp))              {}
//				else if (l.TryReadInt64Chunk('epnu', pInfo->liveinfo.dwExpNotUsed))       {}
//				else if (l.TryReadDwordChunk('slep', pInfo->liveinfo.dwSkillExp))         {}
//				else if (l.TryReadDwordChunk('spnu', pInfo->liveinfo.dwSkillExpNotUsed))  {}                
//				else if (l.TryReadWordChunk('seid',pInfo->liveinfo.ustSkillExpForSkillID)){}
//				else if (l.TryReadByteChunk('nbgs',pInfo->liveinfo.ucNormalBagSize))      {}
//				else if (l.TryReadByteChunk('mbgs',pInfo->liveinfo.ucMaterialBagSize))    {}
//				else if (l.TryReadByteChunk('moco',pInfo->liveinfo.ucMountCount))         {}
//				else if (l.TryReadWordChunk('ene1',pInfo->liveinfo.activity))             {}
//				else if (l.TryReadWordChunk('enm1',pInfo->liveinfo.activityMax))          {}
//				else if (l.TryReadWordChunk('vig1',pInfo->liveinfo.vigor))                {}
//				else if (l.TryReadWordChunk('vim1',pInfo->liveinfo.vigorMax))             {}
//				else if (l.TryReadDwordChunk('olt1', pInfo->liveinfo.dwOnlineTime))       { pInfo->liveinfo.dwOnlineTime /= 60000; }  // 以前是毫秒 NND
//				else if (l.TryReadDwordChunk('olt2', pInfo->liveinfo.dwOnlineTime))       {}     
//				else if (l.TryReadDwordChunk('olre', pInfo->liveinfo.dwRewardItemInfo))   {}
//				else if (l.TryReadShortChunk('ttle',pInfo->liveinfo.nCurrentTitleID))     {}
//				else if (l.TryReadDwordChunk('jzi1',pInfo->liveinfo.jiaoZi))              {}
//				else if (l.TryReadByteChunk('stig',pInfo->liveinfo.nStorageItemGrid))     {}
//				else if (l.TryReadByteChunk('stmg',pInfo->liveinfo.nStorageMountGrid))    {}
//
//				else if (l.TryReadDwordChunk('rlit',pInfo->liveinfo.nRecordReliveTime))   {}
//				else if (l.TryReadByteChunk ('flic',pInfo->liveinfo.nFreeReliveCount))    {}
//
//				else if (l.TryReadDwordChunk('sdet',pInfo->liveinfo.nSysDoubleExpTime))   {}
//				else if (l.TryReadDwordChunk('idet',pInfo->liveinfo.nItemDoubleExpTime))  {}
//
//				else if (l.TryReadDwordChunk('daox',pInfo->liveinfo.daoxing))  {}
//
//				else if (l.IsChunk('tt01'))
//				{
//					l.StartChunk('tt01');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						short nTitleArray[MAX_TITLE_COUNT];
//						memset( nTitleArray, 0, sizeof( nTitleArray ) );
//						r.ReadToBuffer( (BYTE*)nTitleArray, sizeof(nTitleArray) );
//						for ( int i = 0; i < MAX_TITLE_COUNT; ++i )
//						{
//							pInfo->liveinfo.xTitleData[i].SetTitleID( nTitleArray[i] );
//						}
//					}   
//					l.EndChunk('tt01');
//				}
//				else if (l.IsChunk('tt02'))
//				{
//					l.StartChunk('tt02');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xTitleData, sizeof(pInfo->liveinfo.xTitleData));
//					}   
//					l.EndChunk('tt02');
//				}
//				else if ( l.IsChunk('are1') )
//				{
//					l.StartChunk('are1');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xArea, sizeof(pInfo->liveinfo.xArea));
//					}   
//					l.EndChunk('are1');
//				}
//				else if ( l.IsChunk('msd2') )
//				{
//					l.StartChunk('msd2');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer((BYTE*)&pInfo->liveinfo.xMasterData, sizeof(pInfo->liveinfo.xMasterData));
//					}   
//					l.EndChunk('msd2');
//				}
//				else if(l.TryReadWordChunk('skn1',pInfo->liveinfo.nRecipeSkillNum))                   {}
//				else if ( l.IsChunk( 'skp1') )
//				{
//					l.StartChunk('skp1');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.nSkillPoint, sizeof(pInfo->liveinfo.nSkillPoint) );
//					}   
//					l.EndChunk('skp1');
//				}
//				else if(l.TryReadWordChunk('bapt',pInfo->liveinfo.basePotential))                   {}
//				else if ( l.IsChunk( 'bav1') )
//				{
//					l.StartChunk('bav1');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer( (BYTE*)pInfo->liveinfo.baseAssignValue, sizeof(pInfo->liveinfo.baseAssignValue) );
//					}   
//					l.EndChunk('bav1');
//				}
//				else if (l.TryReadShortChunk('hrid',(short&)pInfo->liveinfo.hero_id))  {}
//				else if (l.TryReadCharChunk('tphj',pInfo->liveinfo.TPHJRank))          {}
//				else if (l.TryReadDwordChunk('akp',pInfo->liveinfo.dwKillPlayerSum))  {}
//				else if (l.TryReadDwordChunk('wkp',pInfo->liveinfo.dwKillPlayerWeekSum))  {}
//				else if (l.TryReadByteChunk('upos',pInfo->liveinfo.uchPosition))  {}
//				else if ( l.IsChunk('cold'))
//				{
//					l.StartChunk('cold');
//					{   
//						CDataChunkLoader r(l.GetPointer().byte,l.GetChunkSize());
//						r.ReadToBuffer((BYTE*)pInfo->liveinfo.xItemColdDown, sizeof(pInfo->liveinfo.xItemColdDown));
//					}   
//					l.EndChunk('cold');
//				}
//				else{ l.SkipChunk();}
//			}
//		}
//		else 
//			l.SkipChunk();
//	}
//}
//
//bool CharChunkWR::LoadOtherData( uint8* buffer, uint32 bufferSize, SCharOtherData* pOtherData )
//{
//	if ( buffer == NULL || bufferSize == 0|| pOtherData == NULL )
//	{ return false;}
//
//	CDataChunkLoader l( buffer, bufferSize );
//	if (l.IsChunk('otda'))
//	{
//		l.StartChunk('otda');
//		{   
//			pOtherData->ReadOtherDataBlob( l.GetPointer().byte,l.GetBufferSize());
//		}
//		l.EndChunk('otda');
//	}
//	else 
//	{ l.SkipChunk(); }
//
//	return true;
//}
//
//bool CharChunkWR::LoadExtendData( uint8* buffer, uint32 bufferSize, SExtendData* pExtendData )
//{
//	if ( buffer == NULL || bufferSize == 0 || pExtendData == NULL )
//	{ return false; }
//
//	CDataChunkLoader l( buffer, bufferSize );
//
//	if (l.IsChunk('exda'))
//	{
//		l.StartChunk('exda');
//		{   
//			pExtendData->Read( l.GetPointer().byte, l.GetChunkSize());
//		}
//		l.EndChunk('exda');
//	}
//	else 
//		l.SkipChunk();
//
//	return true;
//}
//
//bool CharChunkWR::LoadAchieveData( uint8* buffer, uint32 bufferSize, SAchieveData* pAchieveData )
//{
//	if ( buffer == NULL || bufferSize == 0 || pAchieveData == NULL )
//	{ return false; }
//
//	CDataChunkLoader l( buffer, bufferSize );
//
//	if (l.IsChunk('ahda'))
//	{
//		l.StartChunk('ahda');
//		{   
//			pAchieveData->Read( l.GetPointer().byte, l.GetChunkSize());
//		}
//		l.EndChunk('ahda');
//	}
//	else 
//		l.SkipChunk();
//
//	return true;
//}
//
//bool CharChunkWR::LoadIdentifyData( uint8* buffer,    uint32 bufferSize, SIdentifyData* pIdentifyData )
//{
//	if ( buffer == NULL || bufferSize == 0 || pIdentifyData == NULL )
//	{ return false; }
//
//	CDataChunkLoader l( buffer, bufferSize );
//
//	if (l.IsChunk('inda'))
//	{
//		l.StartChunk('inda');
//		{   
//			pIdentifyData->Read( l.GetPointer().byte, l.GetChunkSize());
//		}
//		l.EndChunk('inda');
//	}
//	else 
//		l.SkipChunk();
//
//	return true;
//}
//
//bool CharChunkWR::LoadVisuals( uint8* buffer, uint32 bufferSize, SCharVisual* pInfo )
//{
//	if ( buffer == NULL || bufferSize == 0 ||  pInfo == NULL )
//	{ return false; }
//
//	CDataChunkLoader l( buffer, bufferSize );
//	if (l.IsChunk('visl'))
//	{
//		l.StartChunk('visl');
//		pInfo->ReadVisual( l.GetPointer().byte, l.GetBufferSize() );
//		l.EndChunk('visl');
//	}
//	else 
//	{ l.SkipChunk(); }
//	return true;
//}


CRankInfo::CRankInfo()
{
	_mySqlConnection = NULL;
	serverid = 0xffff;
	_workState = SS_TryConnect;
	_lastUpdateTime = HQ_TimeGetTime();
	_lastSaveTime = 0;
	bInit = false;
	bBuildRank = true;
	
	
	sPersonalRank* _rankinfo_LV		 = new sPersonalRank[ECD_PersonalRankCount]; //等级排行榜
	rankinfo_LV = _rankinfo_LV;
	sPersonalRank* _rankinfo_Fortune = new sPersonalRank[ECD_PersonalRankCount]; //财富排行榜
	rankinfo_Fortune = _rankinfo_Fortune;
	sPersonalRank* _rankinfo_Honor   = new sPersonalRank[ECD_PersonalRankCount]; //荣誉排行榜
	rankinfo_Honor = _rankinfo_Honor;
	sPersonalRank* _rankinfo_Offer	 = new sPersonalRank[ECD_PersonalRankCount]; //军功排行榜
	rankinfo_Offer = _rankinfo_Offer;
	sPersonalRank* _rankinfo_Fame	 = new sPersonalRank[ECD_PersonalRankCount]; //功勋排行榜
	rankinfo_Fame = _rankinfo_Fame;
	sPersonalRank* _rankinfo_Kill	 = new sPersonalRank[ECD_PersonalRankCount]; //杀敌排行榜
	rankinfo_Kill = _rankinfo_Kill;
	sPersonalRank* _rankinfo_Charm	 = new sPersonalRank[ECD_PersonalRankCount]; //魅力排行榜
	rankinfo_Charm = _rankinfo_Charm;
	sPersonalRank* _rankinfo_PK		 = new sPersonalRank[ECD_PersonalRankCount]; //红名排行榜
	rankinfo_PK = _rankinfo_PK;
	sPersonalRank* _rankinfo_EquipAllScore	= new sPersonalRank[ECD_PersonalRankCount]; //装备总评分
	rankinfo_EquipAllScore = _rankinfo_EquipAllScore;

	sGuildRank* _guildrankinfo	 = new sGuildRank[ECD_GuildRankCount];//军团排行榜
	guildrankinfo = _guildrankinfo;

	sCountryRank* _countryrankinfo_Power	= new sCountryRank[ECD_CountryRankCount]; //国家实力榜
	countryrankinfo_Power = _countryrankinfo_Power;
	sCountryRank* _countryrankinfo_Tribute = new sCountryRank[ECD_CountryRankCount]; //兵书排行榜
	countryrankinfo_Tribute = _countryrankinfo_Tribute;

	sEquipScore* _equipscore = new sEquipScore[ECD_EquipScoreRank];//装备评分排行榜
	equip_score_Weapon = _equipscore;
	_equipscore = new sEquipScore[ECD_EquipScoreRank];//装备评分排行榜
	equip_score_Helmet = _equipscore;
	_equipscore = new sEquipScore[ECD_EquipScoreRank];//装备评分排行榜
	equip_score_Shoulder = _equipscore;
	_equipscore = new sEquipScore[ECD_EquipScoreRank];//装备评分排行榜
	equip_score_Armour = _equipscore;
	_equipscore = new sEquipScore[ECD_EquipScoreRank];//装备评分排行榜
	equip_score_Glove = _equipscore;
	_equipscore = new sEquipScore[ECD_EquipScoreRank];//装备评分排行榜
	equip_score_Sash = _equipscore;
	_equipscore = new sEquipScore[ECD_EquipScoreRank];//装备评分排行榜
	equip_score_Shoe = _equipscore;
	_equipscore = new sEquipScore[ECD_EquipScoreRank];//装备评分排行榜
	equip_score_Necklace = _equipscore;
	_equipscore = new sEquipScore[ECD_EquipScoreRank];//装备评分排行榜
	equip_score_Ring = _equipscore;
	_equipscore = new sEquipScore[ECD_EquipScoreRank];//装备评分排行榜
	equip_score_Bangle = _equipscore;
	_equipscore = new sEquipScore[ECD_EquipScoreRank];//装备评分排行榜
	equip_score_WeaponMinor = _equipscore;

	sGuildCampBattlePoint* pGuildCampPoint = new sGuildCampBattlePoint[ECD_GuildRankCount];
	guildcampbattle_pint = pGuildCampPoint;
}

CRankInfo::~CRankInfo()
{
	if (_mySqlConnection)
	{
		delete _mySqlConnection;
	}

	delete[] rankinfo_LV;
	delete[] rankinfo_Fortune;
	delete[] rankinfo_Honor;
	delete[] rankinfo_Offer;
	delete[] rankinfo_Fame;
	delete[] rankinfo_Kill;
	delete[] rankinfo_Charm;
	delete[] rankinfo_PK;
	delete[] rankinfo_EquipAllScore;

	delete[] guildrankinfo;

	delete[] countryrankinfo_Power;
	delete[] countryrankinfo_Tribute;

	delete[] equip_score_Weapon;
	delete[] equip_score_Helmet;
	delete[] equip_score_Shoulder;
	delete[] equip_score_Armour;
	delete[] equip_score_Glove;
	delete[] equip_score_Sash;
	delete[] equip_score_Shoe;
	delete[] equip_score_Necklace;
	delete[] equip_score_Ring;
	delete[] equip_score_Bangle;
	delete[] equip_score_WeaponMinor;

	delete[] guildcampbattle_pint;
}

void CRankInfo::_TryConnectToSqlDb()
{
	if ( _mySqlConnection == NULL )
	{
		_mySqlConnection = new mysqlpp::Connection();
		if ( _mySqlConnection == NULL )
		{
			return;
		}
	}
	switch ( _workState )
	{
	case SS_TryConnect:
	case SS_ReConnected:
		{
			CDataCenterConfig::sRankConfig* pConfig = theConfig.GetRankConifg(serverid);
			if (!pConfig)
			{
				printf("conncet mysql error! NO config info server id:%d\n",serverid);
				return;
			}

			try
			{
				if ( _workState == SS_ReConnected)
				{ 
					_mySqlConnection->disconnect();
				}
				_mySqlConnection->set_option(new mysqlpp::MultiStatementsOption(true));
				_mySqlConnection->set_option(new mysqlpp::SetCharsetNameOption("utf8"));
				bool ConnectOk = _mySqlConnection->connect(pConfig->strDatabaseName.c_str(), 
					pConfig->strDatabaseIP.c_str(), 
					pConfig->strDatabaseUser.c_str(),
					pConfig->strDatabasePwd.c_str(), 
					pConfig->DatabasePort);

				if ( !ConnectOk )
				{
					printf("connect mysql error!\n");
					return;
				}

				// 设置mysql超时为24小时
				mysqlpp::Query query =_mySqlConnection->query("set interactive_timeout = 24*3600");
				query.execute();

				_workState = SS_Connected; 

			}
			catch (exception& er)
			{				
			}
		}
		break;
	}
}

bool CRankInfo::_CheckState()
{    
	if (!_mySqlConnection||!_mySqlConnection->connected())
	{
		_workState = SS_ReConnected;
		return false;
	}

	// 3分钟PING一次
	if ( _lastUpdateTime == 0)
	{ _lastUpdateTime = timeGetTime(); }

	if ( !GameTime::IsPassCurrentTime( _lastUpdateTime, ECD_PingTime ) )
	{ return true; }

	_lastUpdateTime = timeGetTime();
	if (! _mySqlConnection->ping())
	{
		_workState = SS_ReConnected;
		return false;
	}

	return true;
}

bool CRankInfo::LoadRankFile()
{
	CDataCenterConfig::sRankConfig* pConfig = theConfig.GetRankConifg(serverid);
	if (!pConfig)
	{
		return false;
	}

	TiXmlDocument doc;
	if( !doc.LoadFile( pConfig->strFileAddr.c_str()))
	{
		_lastSaveTime = 0;
		return true;
	}

	double _value = 0;
	TiXmlElement *lpproject = doc.FirstChildElement("Project");
	if( !lpproject)
		return false;
	else
	{
		TiXmlElement *lpRanks = lpproject->FirstChildElement("Ranks");
		if (!lpRanks)
		{
			return false;
		}
		else
		{
			lpRanks->QueryDoubleAttribute("LastUpdateTime", &_value);
			_lastSaveTime = _value;			
		}
	}
	return true;
}

bool CRankInfo::SaveRankFile(const char *szFileName)
{
	printf("begin save FilePath : %s\n",szFileName);
	if (szFileName == NULL)
	{ return false; }

	MeXmlDocument rankxml;
	rankxml.InsertEndChild(MeXmlDeclaration("1.0", "utf-8", "yes"));
	MeXmlElement *pProject = rankxml.InsertEndChild(("Project"))->ToElement();
	if (pProject == NULL)
	{ return false; }

	MeXmlElement *pRanks = pProject->InsertEndChild(("Ranks"))->ToElement();
	if (pRanks == NULL)
	{ return false; }
	pRanks->SetAttribute("LastUpdateTime", _lastSaveTime);

	Common::_tstring strValue = "";
	//个人排行榜
	sPersonalRank* pPersonalRank = NULL;
	//1,等级排行榜
	if ((&rankinfo_LV[0])->usRank != 0)
	{
		MeXmlElement *pLvType = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pLvType == NULL)
		{ return false; }
		strValue = "总经验排行榜";
		pLvType->SetAttribute("Name", strValue.toUTF8().c_str());

		pPersonalRank = NULL;
		for (int n =0;n < ECD_PersonalRankCount;n++)
		{
			pPersonalRank = &rankinfo_LV[n];
			if (!pPersonalRank||pPersonalRank->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pLvType->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pPersonalRank->usRank);
			strValue = pPersonalRank->chName;
			pRank->SetAttribute("CharacterName", strValue.toUTF8().c_str());
			pRank->SetAttribute("Level", pPersonalRank->ulValue);
			pRank->SetAttribute("Country", pPersonalRank->usCountryID);
			strValue = pPersonalRank->chGuildName;
			pRank->SetAttribute("Guild", strValue.toUTF8().c_str());
			pRank->SetAttribute("Reward", 0);
		}
		printf("save secc: %s\n","总经验排行榜");
	}
	
	//2,财富排行榜
	if ((&rankinfo_Fortune[0])->usRank != 0)
	{
		MeXmlElement *pFortuneType = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pFortuneType == NULL)
		{ return false; }
		strValue = "财富排行榜";
		pFortuneType->SetAttribute("Name", strValue.toUTF8().c_str());

		pPersonalRank = NULL;
		for (int n =0;n < ECD_PersonalRankCount;n++)
		{
			pPersonalRank = &rankinfo_Fortune[n];
			if (!pPersonalRank||pPersonalRank->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pFortuneType->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank",pPersonalRank->usRank);
			strValue = pPersonalRank->chName;
			pRank->SetAttribute("CharacterName", strValue.toUTF8().c_str());
			pRank->SetAttribute("Fortune", pPersonalRank->ulValue);
			pRank->SetAttribute("Country", pPersonalRank->usCountryID);
			strValue = pPersonalRank->chGuildName;
			pRank->SetAttribute("Guild", strValue.toUTF8().c_str());
			pRank->SetAttribute("Reward", 0);
		}
		printf("save secc: %s\n","财富排行榜");
	}
	

	//3,荣誉排行榜
	if ((&rankinfo_Honor[0])->usRank != 0)
	{
		MeXmlElement *pHonorType = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pHonorType == NULL)
		{ return false; }
		strValue = "荣誉排行榜";
		pHonorType->SetAttribute("Name", strValue.toUTF8().c_str());

		pPersonalRank = NULL;
		for (int n =0;n < ECD_PersonalRankCount;n++)
		{
			pPersonalRank = &rankinfo_Honor[n];
			if (!pPersonalRank||pPersonalRank->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pHonorType->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pPersonalRank->usRank);
			strValue = pPersonalRank->chName;
			pRank->SetAttribute("CharacterName", strValue.toUTF8().c_str());
			pRank->SetAttribute("Honor", pPersonalRank->ulValue);
			pRank->SetAttribute("Country", pPersonalRank->usCountryID);
			strValue = pPersonalRank->chGuildName;
			pRank->SetAttribute("Guild", strValue.toUTF8().c_str());
			pRank->SetAttribute("Reward", 0);
		}
		printf("save secc: %s\n","荣誉排行榜");
	}
	

	//4,军功排行榜
	if ((&rankinfo_Offer[0])->usRank != 0)
	{
		MeXmlElement *pOfferType = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pOfferType == NULL)
		{ return false; }
		strValue = "军功排行榜";
		pOfferType->SetAttribute("Name", strValue.toUTF8().c_str());

		pPersonalRank = NULL;
		for (int n =0;n < ECD_PersonalRankCount;n++)
		{
			pPersonalRank = &rankinfo_Offer[n];
			if (!pPersonalRank||pPersonalRank->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pOfferType->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pPersonalRank->usRank);
			strValue = pPersonalRank->chName;
			pRank->SetAttribute("CharacterName", strValue.toUTF8().c_str());
			pRank->SetAttribute("Offer", pPersonalRank->ulValue);
			pRank->SetAttribute("Country", pPersonalRank->usCountryID);
			strValue = pPersonalRank->chGuildName;
			pRank->SetAttribute("Guild", strValue.toUTF8().c_str());
			pRank->SetAttribute("Reward", 0);
		}
		printf("save secc: %s\n","军功排行榜");
	}
	

	//5,功勋排行榜
	if ((&rankinfo_Fame[0])->usRank != 0)
	{
		MeXmlElement *pFameType = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pFameType == NULL)
		{ return false; }
		strValue = "功勋排行榜";
		pFameType->SetAttribute("Name", strValue.toUTF8().c_str());

		pPersonalRank = NULL;
		for (int n =0;n < ECD_PersonalRankCount;n++)
		{
			pPersonalRank = &rankinfo_Fame[n];
			if (!pPersonalRank||pPersonalRank->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pFameType->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pPersonalRank->usRank);
			strValue = pPersonalRank->chName;
			pRank->SetAttribute("CharacterName", strValue.toUTF8().c_str());
			pRank->SetAttribute("Fame", pPersonalRank->ulValue);
			pRank->SetAttribute("Country", pPersonalRank->usCountryID);
			strValue = pPersonalRank->chGuildName;
			pRank->SetAttribute("Guild", strValue.toUTF8().c_str());
			pRank->SetAttribute("Reward", 0);
		}
		printf("save secc: %s\n","功勋排行榜");
	}
	

	//6,杀敌排行榜
	if ((&rankinfo_Kill[0])->usRank != 0)
	{
		MeXmlElement *pKillType = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pKillType == NULL)
		{ return false; }
		strValue = "杀敌排行榜";
		pKillType->SetAttribute("Name", strValue.toUTF8().c_str());

		pPersonalRank = NULL;
		for (int n =0;n < ECD_PersonalRankCount;n++)
		{
			pPersonalRank = &rankinfo_Kill[n];
			if (!pPersonalRank||pPersonalRank->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pKillType->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pPersonalRank->usRank);
			strValue = pPersonalRank->chName;
			pRank->SetAttribute("CharacterName", strValue.toUTF8().c_str());
			pRank->SetAttribute("Kill", pPersonalRank->ulValue);
			pRank->SetAttribute("Country", pPersonalRank->usCountryID);
			strValue = pPersonalRank->chGuildName;
			pRank->SetAttribute("Guild", strValue.toUTF8().c_str());
			pRank->SetAttribute("Reward", 0);
		}
		printf("save secc: %s\n","杀敌排行榜");
	}
	

	//7,魅力排行榜
	if ((&rankinfo_Charm[0])->usRank != 0)
	{
		MeXmlElement *pCharmType = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pCharmType == NULL)
		{ return false; }
		strValue = "魅力排行榜";
		pCharmType->SetAttribute("Name", strValue.toUTF8().c_str());

		pPersonalRank = NULL;
		for (int n =0;n < ECD_PersonalRankCount;n++)
		{
			pPersonalRank = &rankinfo_Charm[n];
			if (!pPersonalRank||pPersonalRank->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pCharmType->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pPersonalRank->usRank);
			strValue = pPersonalRank->chName;
			pRank->SetAttribute("CharacterName", strValue.toUTF8().c_str());
			pRank->SetAttribute("Charm", pPersonalRank->ulValue);
			pRank->SetAttribute("Country", pPersonalRank->usCountryID);
			strValue = pPersonalRank->chGuildName;
			pRank->SetAttribute("Guild", strValue.toUTF8().c_str());
			pRank->SetAttribute("Reward", 0);
		}
		printf("save secc: %s\n","魅力排行榜");
	}
	

	//8,红名排行榜
	if ((&rankinfo_PK[0])->usRank != 0)
	{
		MeXmlElement *pPKType = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pPKType == NULL)
		{ return false; }
		strValue = "红名排行榜";
		pPKType->SetAttribute("Name", strValue.toUTF8().c_str());

		pPersonalRank = NULL;
		for (int n =0;n < ECD_PersonalRankCount;n++)
		{
			pPersonalRank = &rankinfo_PK[n];
			if (!pPersonalRank||pPersonalRank->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pPKType->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pPersonalRank->usRank);
			strValue = pPersonalRank->chName;
			pRank->SetAttribute("CharacterName", strValue.toUTF8().c_str());
			pRank->SetAttribute("PK", pPersonalRank->ulValue);
			pRank->SetAttribute("Country", pPersonalRank->usCountryID);
			strValue = pPersonalRank->chGuildName;
			pRank->SetAttribute("Guild", strValue.toUTF8().c_str());
			pRank->SetAttribute("Reward", 0);
		}
		printf("save secc: %s\n","红名排行榜");
	}

	//装备总分排行榜
	if ((&rankinfo_PK[0])->usRank != 0)
	{
		MeXmlElement *pPKType = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pPKType == NULL)
		{ return false; }
		strValue = "装备总分排行榜";
		pPKType->SetAttribute("Name", strValue.toUTF8().c_str());

		pPersonalRank = NULL;
		for (int n =0;n < ECD_PersonalRankCount;n++)
		{
			pPersonalRank = &rankinfo_EquipAllScore[n];
			if (!pPersonalRank||pPersonalRank->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pPKType->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pPersonalRank->usRank);
			strValue = pPersonalRank->chName;
			pRank->SetAttribute("CharacterName", strValue.toUTF8().c_str());
			pRank->SetAttribute("Score", pPersonalRank->ulValue);
			pRank->SetAttribute("Country", pPersonalRank->usCountryID);
			strValue = pPersonalRank->chGuildName;
			pRank->SetAttribute("Guild", strValue.toUTF8().c_str());
			pRank->SetAttribute("Reward", 0);
		}
		printf("save secc: %s\n","装备总分排行榜");
	}
	

	//军团排行榜
	if ((&guildrankinfo[0])->usRank != 0)
	{
		MeXmlElement *pGuildType = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pGuildType == NULL)
		{ return false; }
		strValue = "军团排行榜";
		pGuildType->SetAttribute("Name", strValue.toUTF8().c_str());

		sGuildRank* pGuildRank = NULL;
		for (int n =0;n < ECD_GuildRankCount;n++)
		{
			pGuildRank = &guildrankinfo[n];
			if (!pGuildRank||pGuildRank->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pGuildType->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pGuildRank->usRank);
			strValue = pGuildRank->chGuildName;
			pRank->SetAttribute("GuildName", strValue.toUTF8().c_str());
			pRank->SetAttribute("GuildPower", pGuildRank->ulGuildPower);
			pRank->SetAttribute("GuildMember", pGuildRank->usGuildMemberCount);
			pRank->SetAttribute("GuildLevel", pGuildRank->usGuildLevel);
			pRank->SetAttribute("Country", pGuildRank->usCountryID);
		}
		printf("save secc: %s\n","军团排行榜");
	}
	

	//国家排行榜
	sCountryRank* pCountryRank = NULL;
	if ((&countryrankinfo_Power[0])->usRank != 0)
	{
		//1,国家实力榜
		MeXmlElement *pCPowerType = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pCPowerType == NULL)
		{ return false; }
		strValue = "国家实力榜";
		pCPowerType->SetAttribute("Name", strValue.toUTF8().c_str());

		pCountryRank = NULL;
		for (int n =0;n < ECD_CountryRankCount;n++)
		{
			pCountryRank = &countryrankinfo_Power[n];
			if (!pCountryRank||pCountryRank->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pCPowerType->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pCountryRank->usRank);
			pRank->SetAttribute("Country", pCountryRank->usCountryID);
			strValue = pCountryRank->chKingName;
			pRank->SetAttribute("King", strValue.toUTF8().c_str());		
			pRank->SetAttribute("Power", pCountryRank->ulValue);
		}
		printf("save secc: %s\n","国家实力榜");
	}
	

	//兵书排行榜
	if ((&countryrankinfo_Tribute[0])->usRank != 0)
	{
		MeXmlElement *pCTributeType = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pCTributeType == NULL)
		{ return false; }
		strValue = "兵书排行榜";
		pCTributeType->SetAttribute("Name", strValue.toUTF8().c_str());

		pCountryRank = NULL;
		for (int n =0;n < ECD_CountryRankCount;n++)
		{
			pCountryRank = &countryrankinfo_Tribute[n];
			if (!pCountryRank||pCountryRank->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pCTributeType->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pCountryRank->usRank);
			pRank->SetAttribute("Country", pCountryRank->usCountryID);
			strValue = pCountryRank->chKingName;
			pRank->SetAttribute("King", strValue.toUTF8().c_str());		
			pRank->SetAttribute("Tribute", pCountryRank->ulValue);
		}
		printf("save secc: %s\n","兵书排行榜");
	}

	//武器评分排行榜
	sEquipScore* pES = NULL;

	if ((&equip_score_Weapon[0])->usRank != 0)
	{
		MeXmlElement *pEquiSocre = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pEquiSocre == NULL)
		{ return false; }
		strValue = "武器评分排行榜";
		pEquiSocre->SetAttribute("Name", strValue.toUTF8().c_str());

		pES = NULL;
		for (int n =0;n < ECD_EquipScoreRank;n++)
		{
			pES = &equip_score_Weapon[n];
			if (!pES||pES->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pEquiSocre->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pES->usRank);
			strValue = pES->chName;
			pRank->SetAttribute("CharacterName", strValue.toUTF8().c_str());
			pRank->SetAttribute("score", pES->score);
			/*pRank->SetAttribute("Country", pES->usCountryID);
			strValue = pES->chGuildName;
			pRank->SetAttribute("Guild", strValue.toUTF8().c_str());*/
			pRank->SetAttribute("Reward", 0);
			AppedItem(&pES->sItem,strValue);
			pRank->SetAttribute("data", strValue.toUTF8().c_str());
		}
		printf("save secc: %s\n","武器评分排行榜");
	}

	if ((&equip_score_Helmet[0])->usRank != 0)
	{
		MeXmlElement *pEquiSocre = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pEquiSocre == NULL)
		{ return false; }
		strValue = "头盔评分排行榜";
		pEquiSocre->SetAttribute("Name", strValue.toUTF8().c_str());

		pES = NULL;
		for (int n =0;n < ECD_EquipScoreRank;n++)
		{
			pES = &equip_score_Helmet[n];
			if (!pES||pES->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pEquiSocre->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pES->usRank);
			strValue = pES->chName;
			pRank->SetAttribute("CharacterName", strValue.toUTF8().c_str());
			pRank->SetAttribute("score", pES->score);
			/*pRank->SetAttribute("Country", pES->usCountryID);
			strValue = pES->chGuildName;
			pRank->SetAttribute("Guild", strValue.toUTF8().c_str());*/
			pRank->SetAttribute("Reward", 0);
			AppedItem(&pES->sItem,strValue);
			pRank->SetAttribute("data", strValue.toUTF8().c_str());
		}
		printf("save secc: %s\n","头盔评分排行榜");
	}

	if ((&equip_score_Shoulder[0])->usRank != 0)
	{
		MeXmlElement *pEquiSocre = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pEquiSocre == NULL)
		{ return false; }
		strValue = "肩甲评分排行榜";
		pEquiSocre->SetAttribute("Name", strValue.toUTF8().c_str());

		pES = NULL;
		for (int n =0;n < ECD_EquipScoreRank;n++)
		{
			pES = &equip_score_Shoulder[n];
			if (!pES||pES->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pEquiSocre->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pES->usRank);
			strValue = pES->chName;
			pRank->SetAttribute("CharacterName", strValue.toUTF8().c_str());
			pRank->SetAttribute("score", pES->score);
			/*pRank->SetAttribute("Country", pES->usCountryID);
			strValue = pES->chGuildName;
			pRank->SetAttribute("Guild", strValue.toUTF8().c_str());*/
			pRank->SetAttribute("Reward", 0);
			AppedItem(&pES->sItem,strValue);
			pRank->SetAttribute("data", strValue.toUTF8().c_str());
		}
		printf("save secc: %s\n","肩甲评分排行榜");
	}

	if ((&equip_score_Armour[0])->usRank != 0)
	{
		MeXmlElement *pEquiSocre = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pEquiSocre == NULL)
		{ return false; }
		strValue = "铠甲评分排行榜";
		pEquiSocre->SetAttribute("Name", strValue.toUTF8().c_str());

		pES = NULL;
		for (int n =0;n < ECD_EquipScoreRank;n++)
		{
			pES = &equip_score_Armour[n];
			if (!pES||pES->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pEquiSocre->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pES->usRank);
			strValue = pES->chName;
			pRank->SetAttribute("CharacterName", strValue.toUTF8().c_str());
			pRank->SetAttribute("score", pES->score);
			/*pRank->SetAttribute("Country", pES->usCountryID);
			strValue = pES->chGuildName;
			pRank->SetAttribute("Guild", strValue.toUTF8().c_str());*/
			pRank->SetAttribute("Reward", 0);
			AppedItem(&pES->sItem,strValue);
			pRank->SetAttribute("data", strValue.toUTF8().c_str());
		}
		printf("save secc: %s\n","铠甲评分排行榜");
	}

	if ((&equip_score_Glove[0])->usRank != 0)
	{
		MeXmlElement *pEquiSocre = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pEquiSocre == NULL)
		{ return false; }
		strValue = "护手评分排行榜";
		pEquiSocre->SetAttribute("Name", strValue.toUTF8().c_str());

		pES = NULL;
		for (int n =0;n < ECD_EquipScoreRank;n++)
		{
			pES = &equip_score_Glove[n];
			if (!pES||pES->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pEquiSocre->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pES->usRank);
			strValue = pES->chName;
			pRank->SetAttribute("CharacterName", strValue.toUTF8().c_str());
			pRank->SetAttribute("score", pES->score);
			/*pRank->SetAttribute("Country", pES->usCountryID);
			strValue = pES->chGuildName;
			pRank->SetAttribute("Guild", strValue.toUTF8().c_str());*/
			pRank->SetAttribute("Reward", 0);
			AppedItem(&pES->sItem,strValue);
			pRank->SetAttribute("data", strValue.toUTF8().c_str());
		}
		printf("save secc: %s\n","护手评分排行榜");
	}

	if ((&equip_score_Sash[0])->usRank != 0)
	{
		MeXmlElement *pEquiSocre = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pEquiSocre == NULL)
		{ return false; }
		strValue = "腰带评分排行榜";
		pEquiSocre->SetAttribute("Name", strValue.toUTF8().c_str());

		pES = NULL;
		for (int n =0;n < ECD_EquipScoreRank;n++)
		{
			pES = &equip_score_Sash[n];
			if (!pES||pES->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pEquiSocre->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pES->usRank);
			strValue = pES->chName;
			pRank->SetAttribute("CharacterName", strValue.toUTF8().c_str());
			pRank->SetAttribute("score", pES->score);
			/*pRank->SetAttribute("Country", pES->usCountryID);
			strValue = pES->chGuildName;
			pRank->SetAttribute("Guild", strValue.toUTF8().c_str());*/
			pRank->SetAttribute("Reward", 0);
			AppedItem(&pES->sItem,strValue);
			pRank->SetAttribute("data", strValue.toUTF8().c_str());
		}
		printf("save secc: %s\n","腰带评分排行榜");
	}

	if ((&equip_score_Shoe[0])->usRank != 0)
	{
		MeXmlElement *pEquiSocre = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pEquiSocre == NULL)
		{ return false; }
		strValue = "鞋子评分排行榜";
		pEquiSocre->SetAttribute("Name", strValue.toUTF8().c_str());

		pES = NULL;
		for (int n =0;n < ECD_EquipScoreRank;n++)
		{
			pES = &equip_score_Shoe[n];
			if (!pES||pES->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pEquiSocre->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pES->usRank);
			strValue = pES->chName;
			pRank->SetAttribute("CharacterName", strValue.toUTF8().c_str());
			pRank->SetAttribute("score", pES->score);
			/*pRank->SetAttribute("Country", pES->usCountryID);
			strValue = pES->chGuildName;
			pRank->SetAttribute("Guild", strValue.toUTF8().c_str());*/
			pRank->SetAttribute("Reward", 0);
			AppedItem(&pES->sItem,strValue);
			pRank->SetAttribute("data", strValue.toUTF8().c_str());
		}
		printf("save secc: %s\n","鞋子评分排行榜");
	}

	if ((&equip_score_Necklace[0])->usRank != 0)
	{
		MeXmlElement *pEquiSocre = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pEquiSocre == NULL)
		{ return false; }
		strValue = "项链评分排行榜";
		pEquiSocre->SetAttribute("Name", strValue.toUTF8().c_str());

		pES = NULL;
		for (int n =0;n < ECD_EquipScoreRank;n++)
		{
			pES = &equip_score_Necklace[n];
			if (!pES||pES->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pEquiSocre->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pES->usRank);
			strValue = pES->chName;
			pRank->SetAttribute("CharacterName", strValue.toUTF8().c_str());
			pRank->SetAttribute("score", pES->score);
			/*pRank->SetAttribute("Country", pES->usCountryID);
			strValue = pES->chGuildName;
			pRank->SetAttribute("Guild", strValue.toUTF8().c_str());*/
			pRank->SetAttribute("Reward", 0);
			AppedItem(&pES->sItem,strValue);
			pRank->SetAttribute("data", strValue.toUTF8().c_str());
		}
		printf("save secc: %s\n","项链评分排行榜");
	}

	if ((&equip_score_Ring[0])->usRank != 0)
	{
		MeXmlElement *pEquiSocre = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pEquiSocre == NULL)
		{ return false; }
		strValue = "戒指评分排行榜";
		pEquiSocre->SetAttribute("Name", strValue.toUTF8().c_str());

		pES = NULL;
		for (int n =0;n < ECD_EquipScoreRank;n++)
		{
			pES = &equip_score_Ring[n];
			if (!pES||pES->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pEquiSocre->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pES->usRank);
			strValue = pES->chName;
			pRank->SetAttribute("CharacterName", strValue.toUTF8().c_str());
			pRank->SetAttribute("score", pES->score);
			/*pRank->SetAttribute("Country", pES->usCountryID);
			strValue = pES->chGuildName;
			pRank->SetAttribute("Guild", strValue.toUTF8().c_str());*/
			pRank->SetAttribute("Reward", 0);
			AppedItem(&pES->sItem,strValue);
			pRank->SetAttribute("data", strValue.toUTF8().c_str());
		}
		printf("save secc: %s\n","戒指评分排行榜");
	}

	if ((&equip_score_Bangle[0])->usRank != 0)
	{
		MeXmlElement *pEquiSocre = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pEquiSocre == NULL)
		{ return false; }
		strValue = "手镯评分排行榜";
		pEquiSocre->SetAttribute("Name", strValue.toUTF8().c_str());

		pES = NULL;
		for (int n =0;n < ECD_EquipScoreRank;n++)
		{
			pES = &equip_score_Bangle[n];
			if (!pES||pES->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pEquiSocre->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pES->usRank);
			strValue = pES->chName;
			pRank->SetAttribute("CharacterName", strValue.toUTF8().c_str());
			pRank->SetAttribute("score", pES->score);
			/*pRank->SetAttribute("Country", pES->usCountryID);
			strValue = pES->chGuildName;
			pRank->SetAttribute("Guild", strValue.toUTF8().c_str());*/
			pRank->SetAttribute("Reward", 0);
			AppedItem(&pES->sItem,strValue);
			pRank->SetAttribute("data", strValue.toUTF8().c_str());
		}
		printf("save secc: %s\n","手镯评分排行榜");
	}

	if ((&equip_score_WeaponMinor[0])->usRank != 0)
	{
		MeXmlElement *pEquiSocre = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pEquiSocre == NULL)
		{ return false; }
		strValue = "手套评分排行榜";
		pEquiSocre->SetAttribute("Name", strValue.toUTF8().c_str());

		pES = NULL;
		for (int n =0;n < ECD_EquipScoreRank;n++)
		{
			pES = &equip_score_WeaponMinor[n];
			if (!pES||pES->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pEquiSocre->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pES->usRank);
			strValue = pES->chName;
			pRank->SetAttribute("CharacterName", strValue.toUTF8().c_str());
			pRank->SetAttribute("score", pES->score);
			/*pRank->SetAttribute("Country", pES->usCountryID);
			strValue = pES->chGuildName;
			pRank->SetAttribute("Guild", strValue.toUTF8().c_str());*/
			pRank->SetAttribute("Reward", 0);
			AppedItem(&pES->sItem,strValue);
			pRank->SetAttribute("data", strValue.toUTF8().c_str());
		}
		printf("save secc: %s\n","手套评分排行榜");
	}

	//军团排行榜
	if ((&guildcampbattle_pint[0])->usRank != 0)
	{
		MeXmlElement *pGuildType = pRanks->InsertEndChild(("Type"))->ToElement();
		if (pGuildType == NULL)
		{ return false; }
		strValue = "军团积分排行榜";
		pGuildType->SetAttribute("Name", strValue.toUTF8().c_str());

		sGuildCampBattlePoint* pGuildRank = NULL;
		for (int n =0;n < ECD_GuildRankCount;n++)
		{
			pGuildRank = &guildcampbattle_pint[n];
			if (!pGuildRank||pGuildRank->usRank == 0)
			{
				break;
			}
			MeXmlElement *pRank = pGuildType->InsertEndChild(("Rank"))->ToElement();
			if (pRank == NULL)
			{ break;}
			pRank->SetAttribute("Rank", pGuildRank->usRank);
			strValue = pGuildRank->chGuildName;
			pRank->SetAttribute("GuildName", strValue.toUTF8().c_str());
			pRank->SetAttribute("GuildCampBattlePoint", pGuildRank->Point);
			pRank->SetAttribute("GuildMember", pGuildRank->usGuildMemberCount);
			pRank->SetAttribute("GuildLevel", pGuildRank->usGuildLevel);
			pRank->SetAttribute("Country", pGuildRank->usCountryID);
		}
		printf("save secc: %s\n","军团积分排行榜");
	}

	bool isOk = rankxml.SaveFile(szFileName);
	if(isOk)
		printf("FilePath save secc\n");
	else
		printf("FilePath save error\n");
	return isOk;
}

void CRankInfo::AppedItem(SCharItem* pItem,Common::_tstring& strContent)
{
	if (!pItem)
	{
		return ;
	}

	Json::Value root;
	root["id"]			= Json::Value(pItem->itembaseinfo.ustItemID);//物品ID
	for(int n =0;n < SCharItem::EConstDefine_BaseRandMaxCount;n++)// 基本附加随机属性
	{
		root["baserands"].append(pItem->equipdata.baseRands[n]);
	}
	for(int n =0;n < SCharItem::EConstDefine_PurpleRandMaxCount;n++)// 紫色附加随机属性
	{
		root["purplerands"].append(pItem->equipdata.purpleRands[n]);
	}
	for(int n =0;n < SCharItem::EConstDefine_SuitRandMaxCount;n++)// 技能套装附加随机属性
	{
		root["suitrands"].append(pItem->equipdata.suitRands[n]);
	}
	for(int n =0;n < SCharItem::EConstDefine_GemHoleMaxCount;n++)// 嵌套宝石
	{
		root["gemids"].append(pItem->equipdata.gemIds[n]);
	}
	root["gemhole"] = Json::Value(pItem->equipdata.gemHoleCount);// 装备打孔数
	root["level"]	= Json::Value(pItem->equipdata.ucLevel);// 装备星级
	root["quality"]	= Json::Value(pItem->equipdata.quality);// 装备品质
	root["score"]	= Json::Value(pItem->equipdata.fScore);// 装备评分
	root["soulper"]	= Json::Value(pItem->equipdata.ucSoulPer);// 装备铭刻加成百分比

	Json::FastWriter fast_writer;
	strContent = fast_writer.write(root);
}

void CRankInfo::ResetRankInfos()
{
	for (int n =0;n < ECD_PersonalRankCount;n++)
	{
		(&rankinfo_LV[n])->sPersonalRank::sPersonalRank();
		(&rankinfo_Fortune[n])->sPersonalRank::sPersonalRank();
		(&rankinfo_Honor[n])->sPersonalRank::sPersonalRank();
		(&rankinfo_Fame[n])->sPersonalRank::sPersonalRank();
		(&rankinfo_Kill[n])->sPersonalRank::sPersonalRank();
		(&rankinfo_Charm[n])->sPersonalRank::sPersonalRank();
		(&rankinfo_Offer[n])->sPersonalRank::sPersonalRank();
		(&rankinfo_PK[n])->sPersonalRank::sPersonalRank();
		(&rankinfo_EquipAllScore[n])->sPersonalRank::sPersonalRank();
	}

	for (int n =0;n < ECD_GuildRankCount;n++)
	{
		(&guildrankinfo[n])->sGuildRank::sGuildRank();
	}

	for (int n =0;n < ECD_CountryRankCount;n++)
	{
		(&countryrankinfo_Power[n])->sCountryRank::sCountryRank();
		(&countryrankinfo_Tribute[n])->sCountryRank::sCountryRank();
	}

	for (int n =0;n < ECD_EquipScoreRank;n++)
	{
		(&equip_score_Weapon[n])->sEquipScore::sEquipScore();
		(&equip_score_Helmet[n])->sEquipScore::sEquipScore();
		(&equip_score_Shoulder[n])->sEquipScore::sEquipScore();
		(&equip_score_Armour[n])->sEquipScore::sEquipScore();
		(&equip_score_Glove[n])->sEquipScore::sEquipScore();
		(&equip_score_Sash[n])->sEquipScore::sEquipScore();
		(&equip_score_Shoe[n])->sEquipScore::sEquipScore();
		(&equip_score_Necklace[n])->sEquipScore::sEquipScore();
		(&equip_score_Ring[n])->sEquipScore::sEquipScore();
		(&equip_score_Bangle[n])->sEquipScore::sEquipScore();
		(&equip_score_WeaponMinor[n])->sEquipScore::sEquipScore();
	}
}

static unsigned char Decode6BitMask[5] = { 0xfc, 0xf8, 0xf0, 0xe0, 0xc0 };

uint32 DeCodeToBuffer(const int8* pszSrc, uint8* pszDest, size_t nDestLen)
{
	if ( pszSrc == NULL || pszDest == NULL )
	{ return 0; }

	int nLen = strlen( pszSrc );
	int nDestPos = 0, nBitPos = 2;
	int nMadeBit = 0;
	unsigned char ch, chCode, tmp = 0;

	for (int i=0; i<nLen; ++i)
	{
		if (( (uint8)pszSrc[i] - 0x3c) >= 0)
		{ ch = (uint8)pszSrc[i] - 0x3c; }
		else
		{
			nDestPos = 0;
			break;
		}

		if (nDestPos >= nDestLen) 
		{ break; }

		if ((nMadeBit + 6) >= 8)
		{
			chCode = (tmp | ((ch & 0x3f) >> (6 - nBitPos)));
			pszDest[nDestPos++] = chCode;

			nMadeBit = 0;

			if (nBitPos < 6) 
			{ nBitPos += 2; }
			else
			{
				nBitPos = 2;
				continue;
			}
		}

		tmp = ((ch << nBitPos) & Decode6BitMask[nBitPos - 2]);
		nMadeBit += (8 - nBitPos);
	}
	return nDestPos;
}

const char* NL = "NULL";

void CRankInfo::BuildRankFile()
{
	printf("begin build FilePath server id:%d\n",GetServerId());
	ResetRankInfos();

	char szSql[512] = {0};
	

	Common::_tstring strCharName = "";
	Common::_tstring strGuildName = "";
	sPersonalRank* pPersonalRank = NULL;
	//个人排行榜
	//1,等级排行榜
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1, "SELECT characterid AS CharID, CharName, Lev, country AS Country, (SELECT guild FROM guildmember where id = CharID) AS GuildID, (SELECT name FROM guild where id = GuildID) AS GuildName, AllExp FROM t_game_character where CharName not in (SELECT RoleName from t_game_gminfo) ORDER BY AllExp DESC LIMIT 100;");

	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pPersonalRank = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_PersonalRankCount)
				{
					break;
				}

				int64 AllExp = res[n]["AllExp"];
				if (AllExp <= 0)
				{
					continue;
				}

				pPersonalRank = &rankinfo_LV[n];
				pPersonalRank->usRank = n+1;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chName, sizeof( pPersonalRank->chName), strCharName.c_str(), sizeof( pPersonalRank->chName ) - 1 );
				}
				pPersonalRank->ulValue = res[n]["Lev"];
				pPersonalRank->usCountryID = res[n]["country"];
				strGuildName.fromUTF8(res[n]["GuildName"]);
				if (!strGuildName.empty()&&strcmp(strGuildName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chGuildName, sizeof( pPersonalRank->chGuildName), strGuildName.c_str(), sizeof( pPersonalRank->chGuildName ) - 1 );
				}
				pPersonalRank->usReward = 0;
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("总经验排行榜\n");
		printf("error!%s\n",er.what());
	}
	


	//2,财富排行榜
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1, "SELECT characterid AS CharID,CharName, Money, country, (SELECT guild FROM guildmember where id = CharID) AS GuildID, (SELECT name FROM guild where id = GuildID) AS GuildName FROM t_game_character where CharName not in (SELECT RoleName from t_game_gminfo) ORDER BY Money DESC LIMIT 100;");

	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pPersonalRank = NULL;
		if (res&&!res.empty())
		{	
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_PersonalRankCount)
				{
					break;
				}
				pPersonalRank = &rankinfo_Fortune[n];
				pPersonalRank->ulValue = res[n]["Money"];
				if (pPersonalRank->ulValue <= 0)
				{
					break;
				}
				pPersonalRank->usRank = n+1;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chName, sizeof( pPersonalRank->chName), strCharName.c_str(), sizeof( pPersonalRank->chName ) - 1 );
				}				
				pPersonalRank->usCountryID = res[n]["country"];
				strGuildName.fromUTF8(res[n]["GuildName"]);
				if (!strGuildName.empty()&&strcmp(strGuildName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chGuildName, sizeof( pPersonalRank->chGuildName), strGuildName.c_str(), sizeof( pPersonalRank->chGuildName ) - 1 );
				}
				pPersonalRank->usReward = 0;
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("财富排行榜\n");
		printf("error!%s\n",er.what());
	}	
	

	//3,荣誉排行榜
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1, "SELECT characterid AS CharID, CharName, honour, country, (SELECT guild FROM guildmember where id = CharID) AS GuildID, (SELECT name FROM guild where id = GuildID) AS GuildName FROM t_game_character where CharName not in (SELECT RoleName from t_game_gminfo)  ORDER BY honour DESC LIMIT 100;");
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pPersonalRank = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_PersonalRankCount)
				{
					break;
				}
				pPersonalRank = &rankinfo_Honor[n];
				pPersonalRank->ulValue = res[n]["honour"];
				if (pPersonalRank->ulValue <= 0)
				{
					break;
				}				
				pPersonalRank->usRank = n+1;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chName, sizeof( pPersonalRank->chName), strCharName.c_str(), sizeof( pPersonalRank->chName ) - 1 );
				}
				pPersonalRank->usCountryID = res[n]["country"];
				strGuildName.fromUTF8(res[n]["GuildName"]);
				if (!strGuildName.empty()&&strcmp(strGuildName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chGuildName, sizeof( pPersonalRank->chGuildName), strGuildName.c_str(), sizeof( pPersonalRank->chGuildName ) - 1 );
				}
				pPersonalRank->usReward = 0;
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("荣誉排行榜\n");
		printf("error!%s\n",er.what());
	}
	

	//4,军功排行榜
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1, "SELECT guild AS Gid,id AS CharID,offer,(SELECT name FROM guild where id = Gid) AS GuildName,(SELECT country from t_game_character where characterid = CharID ) AS country,(SELECT CharName from t_game_character where characterid = CharID ) AS CharName FROM guildmember ORDER BY offer DESC LIMIT 100;");
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pPersonalRank = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_PersonalRankCount)
				{
					break;
				}
				pPersonalRank = &rankinfo_Offer[n];
				pPersonalRank->ulValue = res[n]["offer"];
				if (pPersonalRank->ulValue <= 0)
				{
					break;
				}
				
				pPersonalRank->usRank = n+1;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chName, sizeof( pPersonalRank->chName), strCharName.c_str(), sizeof( pPersonalRank->chName ) - 1 );
				}			
				pPersonalRank->usCountryID = res[n]["country"];
				strGuildName.fromUTF8(res[n]["GuildName"]);
				if (!strGuildName.empty()&&strcmp(strGuildName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chGuildName, sizeof( pPersonalRank->chGuildName), strGuildName.c_str(), sizeof( pPersonalRank->chGuildName ) - 1 );
				}
				pPersonalRank->usReward = 0;
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("军功排行榜\n");
		printf("error!%s\n",er.what());
	}
	

	//5,功勋排行榜
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1, "SELECT characterid AS CharID, CharName, exploit,country, (SELECT guild FROM guildmember where id = CharID) AS GuildID, (SELECT name FROM guild where id = GuildID) AS GuildName FROM t_game_character  where CharName not in (SELECT RoleName from t_game_gminfo) ORDER BY exploit DESC LIMIT 100;");
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pPersonalRank = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_PersonalRankCount)
				{
					break;
				}
				pPersonalRank = &rankinfo_Fame[n];
				pPersonalRank->ulValue = res[n]["exploit"];
				if (pPersonalRank->ulValue <= 0)
				{
					break;
				}

				
				pPersonalRank->usRank = n+1;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()||strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chName, sizeof( pPersonalRank->chName), strCharName.c_str(), sizeof( pPersonalRank->chName ) - 1 );
				}			
				pPersonalRank->usCountryID = res[n]["country"];
				strGuildName.fromUTF8(res[n]["GuildName"]);
				if (!strGuildName.empty()&&strcmp(strGuildName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chGuildName, sizeof( pPersonalRank->chGuildName), strGuildName.c_str(), sizeof( pPersonalRank->chGuildName ) - 1 );
				}
				pPersonalRank->usReward = 0;
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("功勋排行榜\n");
		printf("error!%s\n",er.what());
	}
	

	//6,杀敌排行榜
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1, "SELECT characterid AS CharID, CharName, KillPlayerSum,country, (SELECT guild FROM guildmember where id =  CharID) AS GuildID, (SELECT name FROM guild where id = GuildID) AS GuildName FROM t_game_character  where CharName not in (SELECT RoleName from t_game_gminfo)  ORDER BY KillPlayerSum DESC LIMIT 100;");
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pPersonalRank = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_PersonalRankCount)
				{
					break;
				}
				pPersonalRank = &rankinfo_Kill[n];
				pPersonalRank->ulValue = res[n]["KillPlayerSum"];
				if (pPersonalRank->ulValue <= 0)
				{
					break;
				}

				
				pPersonalRank->usRank = n+1;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chName, sizeof( pPersonalRank->chName), strCharName.c_str(), sizeof( pPersonalRank->chName ) - 1 );
				}			
				pPersonalRank->usCountryID = res[n]["country"];
				strGuildName.fromUTF8(res[n]["GuildName"]);
				if (!strGuildName.empty()&&strcmp(strGuildName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chGuildName, sizeof( pPersonalRank->chGuildName), strGuildName.c_str(), sizeof( pPersonalRank->chGuildName ) - 1 );
				}
				pPersonalRank->usReward = 0;
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("杀敌排行榜\n");
		printf("error!%s\n",er.what());
	}
	

	//7,魅力排行榜
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1, "SELECT id1 AS CharID, friendly ,(SELECT CharName FROM t_game_character where characterid = CharID) AS CharName,(SELECT country FROM t_game_character where characterid = CharID) AS Country ,(SELECT guild FROM guildmember where id = CharID) AS GuildID, (SELECT name FROM guild where id = GuildID) AS GuildName FROM relationdata ORDER BY friendly DESC LIMIT 100;");
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pPersonalRank = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_PersonalRankCount)
				{
					break;
				}
				uint32 friendly = res[n]["friendly"];				
				if (friendly <= 0)
				{
					break;
				}

				pPersonalRank = &rankinfo_Charm[n];
				pPersonalRank->ulValue = friendly;
				pPersonalRank->usRank = n+1;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chName, sizeof( pPersonalRank->chName), strCharName.c_str(), sizeof( pPersonalRank->chName ) - 1 );
				}			
				pPersonalRank->usCountryID = res[n]["country"];
				strGuildName.fromUTF8(res[n]["GuildName"]);
				if (!strGuildName.empty()&&strcmp(strGuildName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chGuildName, sizeof( pPersonalRank->chGuildName), strGuildName.c_str(), sizeof( pPersonalRank->chGuildName ) - 1 );
				}
				pPersonalRank->usReward = 0;
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("魅力排行榜\n");
		printf("error!%s\n",er.what());
	}
	

	//8,红名排行榜
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1, "SELECT characterid AS CharID, CharName, KillValue, country, (SELECT guild FROM guildmember where id = CharID) AS GuildID, (SELECT name FROM guild where id = GuildID) AS GuildName FROM t_game_character  where CharName not in (SELECT RoleName from t_game_gminfo)  ORDER BY KillValue DESC LIMIT 100;");
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pPersonalRank = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_PersonalRankCount)
				{
					break;
				}				
				pPersonalRank = &rankinfo_PK[n];
				pPersonalRank->ulValue = res[n]["KillValue"];
				if (pPersonalRank->ulValue <= 0)
				{
					break;
				}

				
				pPersonalRank->usRank = n+1;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chName, sizeof( pPersonalRank->chName), strCharName.c_str(), sizeof( pPersonalRank->chName ) - 1 );
				}			
				pPersonalRank->usCountryID = res[n]["country"];
				strGuildName.fromUTF8(res[n]["GuildName"]);
				if (!strGuildName.empty()&&strcmp(strGuildName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chGuildName, sizeof( pPersonalRank->chGuildName), strGuildName.c_str(), sizeof( pPersonalRank->chGuildName ) - 1 );
				}
				pPersonalRank->usReward = 0;
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("红名排行榜\n");
		printf("error!%s\n",er.what());
	}
	

	//军团排行榜
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1, "SELECT id AS Gid,name,strength,level,country,(SELECT count(*) from guildmember where guild = Gid) AS membercount from guild ORDER BY strength DESC LIMIT 100;");
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		sGuildRank* pGuildRank = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_PersonalRankCount)
				{
					break;
				}
				pGuildRank = &guildrankinfo[n];
				pGuildRank->ulGuildPower = res[n]["strength"];
				if (pGuildRank->ulGuildPower <= 0)
				{
					break;
				}

				pGuildRank->usRank = n+1;
				strGuildName.fromUTF8(res[n]["name"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pGuildRank->chGuildName, sizeof( pGuildRank->chGuildName), strGuildName.c_str(), sizeof( pGuildRank->chGuildName ) - 1 );
				}
				pGuildRank->ulGuildPower = res[n]["strength"];
				pGuildRank->usGuildMemberCount = res[n]["membercount"];
				pGuildRank->usGuildLevel = res[n]["level"];
				pGuildRank->usCountryID = res[n]["country"];			
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("军团排行榜\n");
		printf("error!%s\n",er.what());
	}
	


	//国家排行榜
	//1,国家实力榜
	sCountryRank* pCountryRank = NULL;
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1, "SELECT kingguild AS Guildid, id, strength ,(SELECT master FROM guild where id =Guildid) AS CharID, (SELECT CharName FROM t_game_character where characterid = CharID) AS CharName from countrys ORDER BY strength DESC LIMIT 3;");
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pCountryRank = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_PersonalRankCount)
				{
					break;
				}
				pCountryRank = &countryrankinfo_Power[n];
				pCountryRank->usRank = n+1;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pCountryRank->chKingName, sizeof( pCountryRank->chKingName), strCharName.c_str(), sizeof( pCountryRank->chKingName ) - 1 );
				}
				pCountryRank->usCountryID = res[n]["id"];
				pCountryRank->ulValue = res[n]["strength"];
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("国家实力榜\n");
		printf("error!%s\n",er.what());
	}
	

	//2,兵书排行榜
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1, "SELECT kingguild AS Guildid, id, Tribute,(SELECT master FROM guild where id =Guildid) AS CharID,(SELECT CharName FROM t_game_character where characterid = CharID) AS CharName from countrys ORDER BY Tribute DESC LIMIT 3;");
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pCountryRank = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_PersonalRankCount)
				{
					break;
				}
				pCountryRank = &countryrankinfo_Tribute[n];
				pCountryRank->usRank = n+1;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pCountryRank->chKingName, sizeof( pCountryRank->chKingName), strCharName.c_str(), sizeof( pCountryRank->chKingName ) - 1 );
				}
				pCountryRank->usCountryID = res[n]["id"];
				pCountryRank->ulValue = res[n]["Tribute"];
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("兵书排行榜\n");
		printf("error!%s\n",er.what());
	}

	//装备评分排行
	sEquipScore* pES = NULL;
	uint32 equiptype = 1;
	memset( szSql, 0, sizeof(szSql));

	//1武器
	equiptype = 1;
	equiptype <<= equip_Weapon;
	sprintf_s( szSql, sizeof( szSql ) - 1, "select 	CharacterId AS CharID, ItemData ,score,(select CharName from t_game_character where characterid = CharID) as CharName from t_game_item where equiptype = %u ORDER BY score DESC LIMIT 100;",equiptype);
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pES = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_EquipScoreRank)
				{
					break;
				}
				float fscore = res[n]["score"];
				if (fscore <= 0.0f)
				{
					break;
				}

				pES = &equip_score_Weapon[n];
				pES->usRank = n+1;
				pES->score = fscore;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pES->chName, sizeof( pES->chName), strCharName.c_str(), sizeof( pES->chName ) - 1 );
				}
				/*pPersonalRank->ulValue = res[n]["Lev"];
				pPersonalRank->usCountryID = res[n]["country"];
				strGuildName.fromUTF8(res[n]["GuildName"]);
				if (!strGuildName.empty()&&strcmp(strGuildName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chGuildName, sizeof( pPersonalRank->chGuildName), strGuildName.c_str(), sizeof( pPersonalRank->chGuildName ) - 1 );
				}*/
				pES->usReward = 0;

				SCharItem ItemTemp;
				memset( &ItemTemp, 0, sizeof(SCharItem));
				ItemTemp.itembaseinfo.ustItemID = InvalidLogicNumber;
				static uint8 bufferDecodeField[ CharChunkWR::CD_DecodeFieldBufferSize_Item ] = {0};
				static uint8 bufferTempUnZip  [ CharChunkWR::CD_UnZipTempBufferSize_Item   ] = {0};

				memset( bufferDecodeField, 0, CharChunkWR::CD_DecodeFieldBufferSize_Item );
				memset( bufferTempUnZip,   0, CharChunkWR::CD_UnZipTempBufferSize_Item );

				// itemdata
				uint32 uncompressBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Item;
				uint32 nDecodeBufferActualSize = DeCodeToBuffer( res[n]["ItemData"].c_str(), bufferDecodeField,  CharChunkWR::CD_DecodeFieldBufferSize_Item );                
				uncompress( bufferTempUnZip, &uncompressBufferSize, bufferDecodeField, nDecodeBufferActualSize );
				ItemTemp.Read( bufferTempUnZip, uncompressBufferSize );
				memcpy(&pES->sItem,&ItemTemp,sizeof(SCharItem));
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("武器\n");
		printf("error!%s\n",er.what());
	}

	//2头盔
	equiptype = 1;
	equiptype <<= equip_Helmet;
	sprintf_s( szSql, sizeof( szSql ) - 1, "select 	CharacterId AS CharID, ItemData ,score,(select CharName from t_game_character where characterid = CharID) as CharName from t_game_item where equiptype = %u ORDER BY score DESC LIMIT 100;",equiptype);
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pES = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_EquipScoreRank)
				{
					break;
				}
				float fscore = res[n]["score"];
				if (fscore <= 0.0f)
				{
					break;
				}

				pES = &equip_score_Helmet[n];
				pES->usRank = n+1;
				pES->score = fscore;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pES->chName, sizeof( pES->chName), strCharName.c_str(), sizeof( pES->chName ) - 1 );
				}
				/*pPersonalRank->ulValue = res[n]["Lev"];
				pPersonalRank->usCountryID = res[n]["country"];
				strGuildName.fromUTF8(res[n]["GuildName"]);
				if (!strGuildName.empty()&&strcmp(strGuildName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chGuildName, sizeof( pPersonalRank->chGuildName), strGuildName.c_str(), sizeof( pPersonalRank->chGuildName ) - 1 );
				}*/
				pES->usReward = 0;

				SCharItem ItemTemp;
				memset( &ItemTemp, 0, sizeof(SCharItem));
				ItemTemp.itembaseinfo.ustItemID = InvalidLogicNumber;
				static uint8 bufferDecodeField[ CharChunkWR::CD_DecodeFieldBufferSize_Item ] = {0};
				static uint8 bufferTempUnZip  [ CharChunkWR::CD_UnZipTempBufferSize_Item   ] = {0};

				memset( bufferDecodeField, 0, CharChunkWR::CD_DecodeFieldBufferSize_Item );
				memset( bufferTempUnZip,   0, CharChunkWR::CD_UnZipTempBufferSize_Item );

				// itemdata
				uint32 uncompressBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Item;
				uint32 nDecodeBufferActualSize = DeCodeToBuffer( res[n]["ItemData"].c_str(), bufferDecodeField,  CharChunkWR::CD_DecodeFieldBufferSize_Item );                
				uncompress( bufferTempUnZip, &uncompressBufferSize, bufferDecodeField, nDecodeBufferActualSize );
				ItemTemp.Read( bufferTempUnZip, uncompressBufferSize );
				memcpy(&pES->sItem,&ItemTemp,sizeof(SCharItem));
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("头盔\n");
		printf("error!%s\n",er.what());
	}

	//3铠甲
	equiptype = 1;
	equiptype <<= equip_Armour;
	sprintf_s( szSql, sizeof( szSql ) - 1, "select 	CharacterId AS CharID, ItemData ,score,(select CharName from t_game_character where characterid = CharID) as CharName from t_game_item where equiptype = %u ORDER BY score DESC LIMIT 100;",equiptype);
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pES = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_EquipScoreRank)
				{
					break;
				}
				float fscore = res[n]["score"];
				if (fscore <= 0.0f)
				{
					break;
				}

				pES = &equip_score_Armour[n];
				pES->usRank = n+1;
				pES->score = fscore;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pES->chName, sizeof( pES->chName), strCharName.c_str(), sizeof( pES->chName ) - 1 );
				}
				/*pPersonalRank->ulValue = res[n]["Lev"];
				pPersonalRank->usCountryID = res[n]["country"];
				strGuildName.fromUTF8(res[n]["GuildName"]);
				if (!strGuildName.empty()&&strcmp(strGuildName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chGuildName, sizeof( pPersonalRank->chGuildName), strGuildName.c_str(), sizeof( pPersonalRank->chGuildName ) - 1 );
				}*/
				pES->usReward = 0;

				SCharItem ItemTemp;
				memset( &ItemTemp, 0, sizeof(SCharItem));
				ItemTemp.itembaseinfo.ustItemID = InvalidLogicNumber;
				static uint8 bufferDecodeField[ CharChunkWR::CD_DecodeFieldBufferSize_Item ] = {0};
				static uint8 bufferTempUnZip  [ CharChunkWR::CD_UnZipTempBufferSize_Item   ] = {0};

				memset( bufferDecodeField, 0, CharChunkWR::CD_DecodeFieldBufferSize_Item );
				memset( bufferTempUnZip,   0, CharChunkWR::CD_UnZipTempBufferSize_Item );

				// itemdata
				uint32 uncompressBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Item;
				uint32 nDecodeBufferActualSize = DeCodeToBuffer( res[n]["ItemData"].c_str(), bufferDecodeField,  CharChunkWR::CD_DecodeFieldBufferSize_Item );                
				uncompress( bufferTempUnZip, &uncompressBufferSize, bufferDecodeField, nDecodeBufferActualSize );
				ItemTemp.Read( bufferTempUnZip, uncompressBufferSize );
				memcpy(&pES->sItem,&ItemTemp,sizeof(SCharItem));
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("铠甲\n");
		printf("error!%s\n",er.what());
	}

	//4护手
	equiptype = 1;
	equiptype <<= equip_Glove;
	sprintf_s( szSql, sizeof( szSql ) - 1, "select 	CharacterId AS CharID, ItemData ,score,(select CharName from t_game_character where characterid = CharID) as CharName from t_game_item where equiptype = %u ORDER BY score DESC LIMIT 100;",equiptype);
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pES = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_EquipScoreRank)
				{
					break;
				}
				float fscore = res[n]["score"];
				if (fscore <= 0.0f)
				{
					break;
				}

				pES = &equip_score_Glove[n];
				pES->usRank = n+1;
				pES->score = fscore;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pES->chName, sizeof( pES->chName), strCharName.c_str(), sizeof( pES->chName ) - 1 );
				}
				/*pPersonalRank->ulValue = res[n]["Lev"];
				pPersonalRank->usCountryID = res[n]["country"];
				strGuildName.fromUTF8(res[n]["GuildName"]);
				if (!strGuildName.empty()&&strcmp(strGuildName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chGuildName, sizeof( pPersonalRank->chGuildName), strGuildName.c_str(), sizeof( pPersonalRank->chGuildName ) - 1 );
				}*/
				pES->usReward = 0;

				SCharItem ItemTemp;
				memset( &ItemTemp, 0, sizeof(SCharItem));
				ItemTemp.itembaseinfo.ustItemID = InvalidLogicNumber;
				static uint8 bufferDecodeField[ CharChunkWR::CD_DecodeFieldBufferSize_Item ] = {0};
				static uint8 bufferTempUnZip  [ CharChunkWR::CD_UnZipTempBufferSize_Item   ] = {0};

				memset( bufferDecodeField, 0, CharChunkWR::CD_DecodeFieldBufferSize_Item );
				memset( bufferTempUnZip,   0, CharChunkWR::CD_UnZipTempBufferSize_Item );

				// itemdata
				uint32 uncompressBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Item;
				uint32 nDecodeBufferActualSize = DeCodeToBuffer( res[n]["ItemData"].c_str(), bufferDecodeField,  CharChunkWR::CD_DecodeFieldBufferSize_Item );                
				uncompress( bufferTempUnZip, &uncompressBufferSize, bufferDecodeField, nDecodeBufferActualSize );
				ItemTemp.Read( bufferTempUnZip, uncompressBufferSize );
				memcpy(&pES->sItem,&ItemTemp,sizeof(SCharItem));
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("护手\n");
		printf("error!%s\n",er.what());
	}

	//5鞋子
	equiptype = 1;
	equiptype <<= equip_Shoe;
	sprintf_s( szSql, sizeof( szSql ) - 1, "select 	CharacterId AS CharID, ItemData ,score,(select CharName from t_game_character where characterid = CharID) as CharName from t_game_item where equiptype = %u ORDER BY score DESC LIMIT 100;",equiptype);
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pES = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_EquipScoreRank)
				{
					break;
				}
				float fscore = res[n]["score"];
				if (fscore <= 0.0f)
				{
					break;
				}

				pES = &equip_score_Shoe[n];
				pES->usRank = n+1;
				pES->score = fscore;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pES->chName, sizeof( pES->chName), strCharName.c_str(), sizeof( pES->chName ) - 1 );
				}
				/*pPersonalRank->ulValue = res[n]["Lev"];
				pPersonalRank->usCountryID = res[n]["country"];
				strGuildName.fromUTF8(res[n]["GuildName"]);
				if (!strGuildName.empty()&&strcmp(strGuildName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chGuildName, sizeof( pPersonalRank->chGuildName), strGuildName.c_str(), sizeof( pPersonalRank->chGuildName ) - 1 );
				}*/
				pES->usReward = 0;

				SCharItem ItemTemp;
				memset( &ItemTemp, 0, sizeof(SCharItem));
				ItemTemp.itembaseinfo.ustItemID = InvalidLogicNumber;
				static uint8 bufferDecodeField[ CharChunkWR::CD_DecodeFieldBufferSize_Item ] = {0};
				static uint8 bufferTempUnZip  [ CharChunkWR::CD_UnZipTempBufferSize_Item   ] = {0};

				memset( bufferDecodeField, 0, CharChunkWR::CD_DecodeFieldBufferSize_Item );
				memset( bufferTempUnZip,   0, CharChunkWR::CD_UnZipTempBufferSize_Item );

				// itemdata
				uint32 uncompressBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Item;
				uint32 nDecodeBufferActualSize = DeCodeToBuffer( res[n]["ItemData"].c_str(), bufferDecodeField,  CharChunkWR::CD_DecodeFieldBufferSize_Item );                
				uncompress( bufferTempUnZip, &uncompressBufferSize, bufferDecodeField, nDecodeBufferActualSize );
				ItemTemp.Read( bufferTempUnZip, uncompressBufferSize );
				memcpy(&pES->sItem,&ItemTemp,sizeof(SCharItem));
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("鞋子\n");

		printf("error!%s\n",er.what());
	}

	//6副武器/手套
	equiptype = 1;
	equiptype <<= equip_WeaponMinor;
	sprintf_s( szSql, sizeof( szSql ) - 1, "select 	CharacterId AS CharID, ItemData ,score,(select CharName from t_game_character where characterid = CharID) as CharName from t_game_item where equiptype = %u ORDER BY score DESC LIMIT 100;",equiptype);
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pES = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_EquipScoreRank)
				{
					break;
				}
				float fscore = res[n]["score"];
				if (fscore <= 0.0f)
				{
					break;
				}

				pES = &equip_score_WeaponMinor[n];
				pES->usRank = n+1;
				pES->score = fscore;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pES->chName, sizeof( pES->chName), strCharName.c_str(), sizeof( pES->chName ) - 1 );
				}
				/*pPersonalRank->ulValue = res[n]["Lev"];
				pPersonalRank->usCountryID = res[n]["country"];
				strGuildName.fromUTF8(res[n]["GuildName"]);
				if (!strGuildName.empty()&&strcmp(strGuildName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chGuildName, sizeof( pPersonalRank->chGuildName), strGuildName.c_str(), sizeof( pPersonalRank->chGuildName ) - 1 );
				}*/
				pES->usReward = 0;

				SCharItem ItemTemp;
				memset( &ItemTemp, 0, sizeof(SCharItem));
				ItemTemp.itembaseinfo.ustItemID = InvalidLogicNumber;
				static uint8 bufferDecodeField[ CharChunkWR::CD_DecodeFieldBufferSize_Item ] = {0};
				static uint8 bufferTempUnZip  [ CharChunkWR::CD_UnZipTempBufferSize_Item   ] = {0};

				memset( bufferDecodeField, 0, CharChunkWR::CD_DecodeFieldBufferSize_Item );
				memset( bufferTempUnZip,   0, CharChunkWR::CD_UnZipTempBufferSize_Item );

				// itemdata
				uint32 uncompressBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Item;
				uint32 nDecodeBufferActualSize = DeCodeToBuffer( res[n]["ItemData"].c_str(), bufferDecodeField,  CharChunkWR::CD_DecodeFieldBufferSize_Item );                
				uncompress( bufferTempUnZip, &uncompressBufferSize, bufferDecodeField, nDecodeBufferActualSize );
				ItemTemp.Read( bufferTempUnZip, uncompressBufferSize );
				memcpy(&pES->sItem,&ItemTemp,sizeof(SCharItem));
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("副武器/手套\n");
		printf("error!%s\n",er.what());
	}

	//7戒指
	equiptype = 1;
	equiptype <<= equip_Ring;
	sprintf_s( szSql, sizeof( szSql ) - 1, "select 	CharacterId AS CharID, ItemData ,score,(select CharName from t_game_character where characterid = CharID) as CharName from t_game_item where equiptype = %u ORDER BY score DESC LIMIT 100;",equiptype);
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pES = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_EquipScoreRank)
				{
					break;
				}
				float fscore = res[n]["score"];
				if (fscore <= 0.0f)
				{
					break;
				}

				pES = &equip_score_Ring[n];
				pES->usRank = n+1;
				pES->score = fscore;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pES->chName, sizeof( pES->chName), strCharName.c_str(), sizeof( pES->chName ) - 1 );
				}
				/*pPersonalRank->ulValue = res[n]["Lev"];
				pPersonalRank->usCountryID = res[n]["country"];
				strGuildName.fromUTF8(res[n]["GuildName"]);
				if (!strGuildName.empty()&&strcmp(strGuildName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chGuildName, sizeof( pPersonalRank->chGuildName), strGuildName.c_str(), sizeof( pPersonalRank->chGuildName ) - 1 );
				}*/
				pES->usReward = 0;

				SCharItem ItemTemp;
				memset( &ItemTemp, 0, sizeof(SCharItem));
				ItemTemp.itembaseinfo.ustItemID = InvalidLogicNumber;
				static uint8 bufferDecodeField[ CharChunkWR::CD_DecodeFieldBufferSize_Item ] = {0};
				static uint8 bufferTempUnZip  [ CharChunkWR::CD_UnZipTempBufferSize_Item   ] = {0};

				memset( bufferDecodeField, 0, CharChunkWR::CD_DecodeFieldBufferSize_Item );
				memset( bufferTempUnZip,   0, CharChunkWR::CD_UnZipTempBufferSize_Item );

				// itemdata
				uint32 uncompressBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Item;
				uint32 nDecodeBufferActualSize = DeCodeToBuffer( res[n]["ItemData"].c_str(), bufferDecodeField,  CharChunkWR::CD_DecodeFieldBufferSize_Item );                
				uncompress( bufferTempUnZip, &uncompressBufferSize, bufferDecodeField, nDecodeBufferActualSize );
				ItemTemp.Read( bufferTempUnZip, uncompressBufferSize );
				memcpy(&pES->sItem,&ItemTemp,sizeof(SCharItem));
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("戒指\n");
		printf("error!%s\n",er.what());
	}

	//8手镯
	equiptype = 1;
	equiptype <<= equip_Bangle;
	sprintf_s( szSql, sizeof( szSql ) - 1, "select 	CharacterId AS CharID, ItemData ,score,(select CharName from t_game_character where characterid = CharID) as CharName from t_game_item where equiptype = %u ORDER BY score DESC LIMIT 100;",equiptype);
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pES = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_EquipScoreRank)
				{
					break;
				}
				float fscore = res[n]["score"];
				if (fscore <= 0.0f)
				{
					break;
				}

				pES = &equip_score_Bangle[n];
				pES->usRank = n+1;
				pES->score = fscore;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pES->chName, sizeof( pES->chName), strCharName.c_str(), sizeof( pES->chName ) - 1 );
				}
				/*pPersonalRank->ulValue = res[n]["Lev"];
				pPersonalRank->usCountryID = res[n]["country"];
				strGuildName.fromUTF8(res[n]["GuildName"]);
				if (!strGuildName.empty()&&strcmp(strGuildName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chGuildName, sizeof( pPersonalRank->chGuildName), strGuildName.c_str(), sizeof( pPersonalRank->chGuildName ) - 1 );
				}*/
				pES->usReward = 0;

				SCharItem ItemTemp;
				memset( &ItemTemp, 0, sizeof(SCharItem));
				ItemTemp.itembaseinfo.ustItemID = InvalidLogicNumber;
				static uint8 bufferDecodeField[ CharChunkWR::CD_DecodeFieldBufferSize_Item ] = {0};
				static uint8 bufferTempUnZip  [ CharChunkWR::CD_UnZipTempBufferSize_Item   ] = {0};

				memset( bufferDecodeField, 0, CharChunkWR::CD_DecodeFieldBufferSize_Item );
				memset( bufferTempUnZip,   0, CharChunkWR::CD_UnZipTempBufferSize_Item );

				// itemdata
				uint32 uncompressBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Item;
				uint32 nDecodeBufferActualSize = DeCodeToBuffer( res[n]["ItemData"].c_str(), bufferDecodeField,  CharChunkWR::CD_DecodeFieldBufferSize_Item );                
				uncompress( bufferTempUnZip, &uncompressBufferSize, bufferDecodeField, nDecodeBufferActualSize );
				ItemTemp.Read( bufferTempUnZip, uncompressBufferSize );
				memcpy(&pES->sItem,&ItemTemp,sizeof(SCharItem));
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("手镯\n");
		printf("error!%s\n",er.what());
	}

	//9肩甲
	equiptype = 1;
	equiptype <<= equip_Shoulder;
	sprintf_s( szSql, sizeof( szSql ) - 1, "select 	CharacterId AS CharID, ItemData ,score,(select CharName from t_game_character where characterid = CharID) as CharName from t_game_item where equiptype = %u ORDER BY score DESC LIMIT 100;",equiptype);
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pES = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_EquipScoreRank)
				{
					break;
				}
				float fscore = res[n]["score"];
				if (fscore <= 0.0f)
				{
					break;
				}

				pES = &equip_score_Shoulder[n];
				pES->usRank = n+1;
				pES->score = fscore;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pES->chName, sizeof( pES->chName), strCharName.c_str(), sizeof( pES->chName ) - 1 );
				}
				/*pPersonalRank->ulValue = res[n]["Lev"];
				pPersonalRank->usCountryID = res[n]["country"];
				strGuildName.fromUTF8(res[n]["GuildName"]);
				if (!strGuildName.empty()&&strcmp(strGuildName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chGuildName, sizeof( pPersonalRank->chGuildName), strGuildName.c_str(), sizeof( pPersonalRank->chGuildName ) - 1 );
				}*/
				pES->usReward = 0;

				SCharItem ItemTemp;
				memset( &ItemTemp, 0, sizeof(SCharItem));
				ItemTemp.itembaseinfo.ustItemID = InvalidLogicNumber;
				static uint8 bufferDecodeField[ CharChunkWR::CD_DecodeFieldBufferSize_Item ] = {0};
				static uint8 bufferTempUnZip  [ CharChunkWR::CD_UnZipTempBufferSize_Item   ] = {0};

				memset( bufferDecodeField, 0, CharChunkWR::CD_DecodeFieldBufferSize_Item );
				memset( bufferTempUnZip,   0, CharChunkWR::CD_UnZipTempBufferSize_Item );

				// itemdata
				uint32 uncompressBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Item;
				uint32 nDecodeBufferActualSize = DeCodeToBuffer( res[n]["ItemData"].c_str(), bufferDecodeField,  CharChunkWR::CD_DecodeFieldBufferSize_Item );                
				uncompress( bufferTempUnZip, &uncompressBufferSize, bufferDecodeField, nDecodeBufferActualSize );
				ItemTemp.Read( bufferTempUnZip, uncompressBufferSize );
				memcpy(&pES->sItem,&ItemTemp,sizeof(SCharItem));
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("肩甲\n");
		printf("error!%s\n",er.what());
	}

	//10项链
	equiptype = 1;
	equiptype <<= equip_Necklace;
	sprintf_s( szSql, sizeof( szSql ) - 1, "select 	CharacterId AS CharID, ItemData ,score,(select CharName from t_game_character where characterid = CharID) as CharName from t_game_item where equiptype = %u ORDER BY score DESC LIMIT 100;",equiptype);
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pES = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_EquipScoreRank)
				{
					break;
				}
				float fscore = res[n]["score"];
				if (fscore <= 0.0f)
				{
					break;
				}

				pES = &equip_score_Necklace[n];
				pES->usRank = n+1;
				pES->score = fscore;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pES->chName, sizeof( pES->chName), strCharName.c_str(), sizeof( pES->chName ) - 1 );
				}
				/*pPersonalRank->ulValue = res[n]["Lev"];
				pPersonalRank->usCountryID = res[n]["country"];
				strGuildName.fromUTF8(res[n]["GuildName"]);
				if (!strGuildName.empty()&&strcmp(strGuildName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chGuildName, sizeof( pPersonalRank->chGuildName), strGuildName.c_str(), sizeof( pPersonalRank->chGuildName ) - 1 );
				}*/
				pES->usReward = 0;

				SCharItem ItemTemp;
				memset( &ItemTemp, 0, sizeof(SCharItem));
				ItemTemp.itembaseinfo.ustItemID = InvalidLogicNumber;
				static uint8 bufferDecodeField[ CharChunkWR::CD_DecodeFieldBufferSize_Item ] = {0};
				static uint8 bufferTempUnZip  [ CharChunkWR::CD_UnZipTempBufferSize_Item   ] = {0};

				memset( bufferDecodeField, 0, CharChunkWR::CD_DecodeFieldBufferSize_Item );
				memset( bufferTempUnZip,   0, CharChunkWR::CD_UnZipTempBufferSize_Item );

				// itemdata
				uint32 uncompressBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Item;
				uint32 nDecodeBufferActualSize = DeCodeToBuffer( res[n]["ItemData"].c_str(), bufferDecodeField,  CharChunkWR::CD_DecodeFieldBufferSize_Item );                
				uncompress( bufferTempUnZip, &uncompressBufferSize, bufferDecodeField, nDecodeBufferActualSize );
				ItemTemp.Read( bufferTempUnZip, uncompressBufferSize );
				memcpy(&pES->sItem,&ItemTemp,sizeof(SCharItem));
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("项链\n");
		printf("error!%s\n",er.what());
	}

	//11腰带
	equiptype = 1;
	equiptype <<= equip_Sash;
	sprintf_s( szSql, sizeof( szSql ) - 1, "select 	CharacterId AS CharID, ItemData ,score,(select CharName from t_game_character where characterid = CharID) as CharName from t_game_item where equiptype = %u ORDER BY score DESC LIMIT 100;",equiptype);
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pES = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_EquipScoreRank)
				{
					break;
				}
				float fscore = res[n]["score"];
				if (fscore <= 0.0f)
				{
					break;
				}

				pES = &equip_score_Sash[n];
				pES->usRank = n+1;
				pES->score = fscore;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pES->chName, sizeof( pES->chName), strCharName.c_str(), sizeof( pES->chName ) - 1 );
				}
				/*pPersonalRank->ulValue = res[n]["Lev"];
				pPersonalRank->usCountryID = res[n]["country"];
				strGuildName.fromUTF8(res[n]["GuildName"]);
				if (!strGuildName.empty()&&strcmp(strGuildName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chGuildName, sizeof( pPersonalRank->chGuildName), strGuildName.c_str(), sizeof( pPersonalRank->chGuildName ) - 1 );
				}*/
				pES->usReward = 0;

				SCharItem ItemTemp;
				memset( &ItemTemp, 0, sizeof(SCharItem));
				ItemTemp.itembaseinfo.ustItemID = InvalidLogicNumber;
				static uint8 bufferDecodeField[ CharChunkWR::CD_DecodeFieldBufferSize_Item ] = {0};
				static uint8 bufferTempUnZip  [ CharChunkWR::CD_UnZipTempBufferSize_Item   ] = {0};

				memset( bufferDecodeField, 0, CharChunkWR::CD_DecodeFieldBufferSize_Item );
				memset( bufferTempUnZip,   0, CharChunkWR::CD_UnZipTempBufferSize_Item );

				// itemdata
				uint32 uncompressBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Item;
				uint32 nDecodeBufferActualSize = DeCodeToBuffer( res[n]["ItemData"].c_str(), bufferDecodeField,  CharChunkWR::CD_DecodeFieldBufferSize_Item );                
				uncompress( bufferTempUnZip, &uncompressBufferSize, bufferDecodeField, nDecodeBufferActualSize );
				ItemTemp.Read( bufferTempUnZip, uncompressBufferSize );
				memcpy(&pES->sItem,&ItemTemp,sizeof(SCharItem));
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("腰带\n");
		printf("error!%s\n",er.what());
	}

	//装备总分排行榜
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1, "SELECT characterid AS CharID, CharName, Lev, country AS Country, (SELECT guild FROM guildmember where id = CharID) AS GuildID, (SELECT name FROM guild where id = GuildID) AS GuildName , equipTotalScore FROM t_game_character where CharName not in (SELECT RoleName from t_game_gminfo) ORDER BY equipTotalScore  DESC LIMIT 100;");
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		pPersonalRank = NULL;
		if (res&&!res.empty())
		{
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_PersonalRankCount)
				{
					break;
				}				
				pPersonalRank = &rankinfo_EquipAllScore[n];
				pPersonalRank->ulValue = res[n]["equipTotalScore"];
				if (pPersonalRank->ulValue <= 0)
				{
					break;
				}


				pPersonalRank->usRank = n+1;
				strCharName.fromUTF8(res[n]["CharName"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chName, sizeof( pPersonalRank->chName), strCharName.c_str(), sizeof( pPersonalRank->chName ) - 1 );
				}			
				pPersonalRank->usCountryID = res[n]["country"];
				strGuildName.fromUTF8(res[n]["GuildName"]);
				if (!strGuildName.empty()&&strcmp(strGuildName.c_str(),NL) != 0)
				{
					strncpy_s( pPersonalRank->chGuildName, sizeof( pPersonalRank->chGuildName), strGuildName.c_str(), sizeof( pPersonalRank->chGuildName ) - 1 );
				}
				pPersonalRank->usReward = 0;
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("装备总分排行榜\n");
		printf("error!%s\n",er.what());
	}

	//军团血战沙场排行榜
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1, "SELECT id AS Gid,name,level,country,(SELECT count(*) from guildmember where guild = Gid) AS membercount,GuildCampBattlePoint from guild ORDER BY GuildCampBattlePoint DESC LIMIT 100;");
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		sGuildCampBattlePoint* pGuildRank = NULL;
		if (res&&!res.empty())
		{		
			for (int n =0;n < res.num_rows();n++)
			{
				if (n >= ECD_PersonalRankCount)
				{
					break;
				}
				pGuildRank = &guildcampbattle_pint[n];
				pGuildRank->Point = res[n]["GuildCampBattlePoint"];
				if (pGuildRank->Point <= 0)
				{
					break;
				}

				pGuildRank->usRank = n+1;
				strGuildName.fromUTF8(res[n]["name"]);
				if (!strCharName.empty()&&strcmp(strCharName.c_str(),NL) != 0)
				{
					strncpy_s( pGuildRank->chGuildName, sizeof( pGuildRank->chGuildName), strGuildName.c_str(), sizeof( pGuildRank->chGuildName ) - 1 );
				}
				pGuildRank->usGuildMemberCount = res[n]["membercount"];
				pGuildRank->usGuildLevel = res[n]["level"];
				pGuildRank->usCountryID = res[n]["country"];			
			}
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("军团血战沙场排行榜\n");
		printf("error!%s\n",er.what());
	}

	time_t ltime;
	time(&ltime);
	_lastSaveTime = ltime;

	CDataCenterConfig::sRankConfig* pConfig = theConfig.GetRankConifg(serverid);
	if (!pConfig)
	{
		printf("FilePath Error serverid:%d\n",serverid);
		return;
	}

	SaveRankFile(pConfig->strFileAddr.c_str());
}

void CRankInfo::ProcessRank()
{
	bool bneedbuild = false;
	if (_lastSaveTime == 0)
	{
		//先生成一个
		bneedbuild = true;
	}
	else
	{
		SYSTEMTIME xSystem;
		::GetLocalTime( &xSystem );
		if (xSystem.wHour == theConfig.GetAutoHour()&&xSystem.wMinute >= theConfig.GetAutoMin())
		{			
			time_t ltime;
			time(&ltime);
			double elapsedTime = difftime(ltime, _lastSaveTime);
			if (elapsedTime >= 60*60)
			{
				//如果在规定的时间内,最后的生成时间跟规定的时间大于1个小时才继续生成
				bneedbuild = true;
			}
		}
	}
	bBuildRank = bneedbuild;
}

void CRankInfo::Run()
{
	if (!bInit)
	{
		bInit = LoadRankFile();
		return;
	}

	if (!_CheckState())
	{
		if (_workState != SS_Connected)
		{
			_TryConnectToSqlDb();
			return;
		}
	}

	if (theConfig.IsAutoLoad())
	{
		ProcessRank();
	}

	if (bBuildRank)
	{
		BuildRankFile();
		//不管成功失败
		bBuildRank = false;
	}
}

CRankManager::CRankManager(void)
{
	IsInit = false;
	if (!_mapRankInfo.empty())
	{
		mapRankInfo::iterator itr = _mapRankInfo.begin();
		while(itr != _mapRankInfo.end())
		{
			if (!itr->second)
			{
				delete itr->second;
			}
			itr =  _mapRankInfo.erase(itr);
		}
	}
	
}

CRankManager::~CRankManager(void)
{
	if (!_mapRankInfo.empty())
	{
		mapRankInfo::iterator itr = _mapRankInfo.begin();
		while(itr != _mapRankInfo.end())
		{
			if (!itr->second)
			{
				delete itr->second;
			}
			itr =  _mapRankInfo.erase(itr);
		}
	}
}

bool CRankManager::AddRankInfo(CRankInfo* pInfo)
{
	if (!pInfo)
	{
		return false;
	}

	mapRankInfo::iterator itr = _mapRankInfo.find(pInfo->GetServerId());
	if (itr != _mapRankInfo.end())
	{
		return false;
	}

	_mapRankInfo.insert(mapRankInfo::value_type(pInfo->GetServerId(),pInfo));
	return true;

}

bool CRankManager::InitRank()
{
	CDataCenterConfig::sRankConfig* pRankConfig = NULL;
	CDataCenterConfig::mapRankConfig::iterator itr = theConfig._mapRankConfig.begin();
	while(itr != theConfig._mapRankConfig.end())
	{
		pRankConfig = itr->second;
		if (!pRankConfig)
		{
			itr = theConfig._mapRankConfig.erase(itr);
		}

		CRankInfo* pRankInfo = new CRankInfo;
		pRankInfo->SetServerid(pRankConfig->Serverid);

		if (!AddRankInfo(pRankInfo))
		{
			printf("add rank info error!server id:%d\n",pRankInfo->GetServerId());
			delete pRankInfo;
			itr = theConfig._mapRankConfig.erase(itr);
		}
		else
		{
			printf("add rank info secc !server id:%d\n",pRankInfo->GetServerId());
		}
		itr++;
	}
	return true;
}

void CRankManager::Run()
{
	if (!IsInit)
	{
		IsInit = InitRank();
		if (!IsInit)
		{
			printf("init rank error!\n");
			return;
		}
		else
		{
			printf("init rank secc!\n");
		}
	}

	mapRankInfo::iterator itr = _mapRankInfo.begin();
	while(itr != _mapRankInfo.end())
	{
		if (!itr->second)
		{
			itr = _mapRankInfo.erase(itr);
			continue;
		}
		itr->second->Run();
		itr++;
	}
}