#include "CountrySave.h"

void CountrySave::SaveGameCountry( CDataChunkWriter* pWriter, CountryData& xData )
{
    if ( pWriter == NULL || xData.GetID() == CountryDefine::Country_Init )
    { return; }

    pWriter->StartChunk( DC_TAG( 'bse3' ) );
    {
        pWriter->WriteByte( xData.GetID() );
        pWriter->WriteString( const_cast< char* >( xData.GetName() ) );
        pWriter->WriteDword( xData.GetMoney() );
        pWriter->WriteString( const_cast< char* >( xData.GetNotice() ) );
        pWriter->WriteDword( xData.GetKingGuild() );
        pWriter->WriteDword( xData.GetDragonGuild() );
        pWriter->WriteDword( xData.GetRosefinchGuild() );
        pWriter->WriteDword( xData.GetLastStrength() );
        pWriter->WriteDword( xData.GetNowStrength() );
        pWriter->WriteByte( xData.GetChangeName() );
        pWriter->WriteByte( xData.GetSortIndex() );
        pWriter->WriteDword( xData.GetKillCount() );
        pWriter->WriteDword( xData.GetDeathCount() );
		pWriter->WriteDword( xData.GetTribute() );
    }
    pWriter->EndChunk( DC_TAG( 'bse3' ) );

    pWriter->StartChunk( DC_TAG( 'off1' ) );
    {
        for ( int i = CountryDefine::Position_None + 1; i < CountryDefine::Position_Max; ++i )
        {
            pWriter->StartChunk( DC_TAG( 'ofd1' ) );
            {
                SaveOfficialInfo( pWriter, xData.GetOfficial( i ) );
            }
            pWriter->EndChunk( DC_TAG( 'ofd1' ) );
        }
    }
    pWriter->EndChunk( DC_TAG( 'off1' ) );

    pWriter->StartChunk( DC_TAG( 'opt1' ) );
    {
        pWriter->WriteDword( xData.GetRecordTime() );
        pWriter->WriteByte( xData.GetPlacardCount() );
        pWriter->WriteByte( xData.GetConveneCount() );
        pWriter->WriteByte( xData.GetRaiseCount() );
        pWriter->WriteByte( xData.GetBanSpeakCount() );
        pWriter->WriteByte( xData.GetRemitCount() );
        pWriter->WriteByte( xData.GetChainCount() );
    }
    pWriter->EndChunk( DC_TAG( 'opt1' ) );

    pWriter->StartChunk( DC_TAG( 'qpt1' ) );
    {
        pWriter->Write( xData.GetQuestOperate( CountryDefine::QuestType_None ), sizeof( OperateTime ) * CountryDefine::QuestType_Max, 1 );
    }
    pWriter->EndChunk( DC_TAG( 'qpt1' ) );

	pWriter->StartChunk( DC_TAG( 'cs1' ) );
    {
        for ( int i = CountryDefine::QuestType_None; i < CountryDefine::QuestType_Max; ++i )
		{
			pWriter->WriteByte( xData.GetQuestSumByType(i));
		}
		pWriter->WriteDword(xData.GetDoneQuestAddStrength());
    }	
    pWriter->EndChunk( DC_TAG( 'cs1' ) );
}

void CountrySave::ReadGameCountry( BYTE* byBuff,DWORD dwSize, CountryData& xData )
{
    CDataChunkLoader xLoader( byBuff,dwSize );

    while ( !xLoader.IsEndOfMemory() )
    {
        if( xLoader.IsChunk( 'bse1' ) )
        {
            xLoader.StartChunk( 'bse1' );
            CDataChunkLoader xReader( xLoader.GetPointer().byte, xLoader.GetChunkSize() );
            {
                xData.SetID( xReader.ReadByte() );

                // 名字
                int nStrSize = xReader.ReadInt();
                char szName[ CountryDefine::MaxCountryLength ] = { 0 };
                memcpy_s( szName, sizeof( szName ), xReader.GetPointer().byte, min( sizeof( szName ) - 1, sizeof( CHAR ) * nStrSize ) );
                xData.SetName( szName );
                xReader.GetPointer().c += nStrSize;

                // 资金
                xData.SetMoney( xReader.ReadDword() );

                // 公告
                nStrSize = xReader.ReadInt();
                char szBuffer[ CountryDefine::MaxNoticeLength ] = { 0 };
                memcpy_s( szBuffer, sizeof( szBuffer ), xReader.GetPointer().byte, min( sizeof( szBuffer ) - 1, sizeof( CHAR ) * nStrSize ) );
                xData.SetNotice( szBuffer );
                xReader.GetPointer().c += nStrSize;

                // 国王帮会
                xData.SetKingGuild( xReader.ReadDword() );

                // 青龙帮会
                xData.SetDragonGuild( xReader.ReadDword() );

                // 朱雀帮会
                xData.SetRosefinchGuild( xReader.ReadDword() );

                // 上次综合实力
                xData.SetLastStrength( xReader.ReadDword() );
                
                // 本次综合实力
                xData.SetNowStrength( xReader.ReadDword() );

                // 是否已经改变国家名字
                xData.SetChangeName( xReader.ReadByte() );

				xData.SetTribute(InitTribute);
            }
            xLoader.EndChunk( 'bse1' );
        }
        else if( xLoader.IsChunk( 'bse2' ) )
        {
            xLoader.StartChunk( 'bse2' );
            CDataChunkLoader xReader( xLoader.GetPointer().byte, xLoader.GetChunkSize() );
            {
                xData.SetID( xReader.ReadByte() );

                // 名字
                int nStrSize = xReader.ReadInt();
                char szName[ CountryDefine::MaxCountryLength ] = { 0 };
                memcpy_s( szName, sizeof( szName ), xReader.GetPointer().byte, min( sizeof( szName ) - 1, sizeof( CHAR ) * nStrSize ) );
                xData.SetName( szName );
                xReader.GetPointer().c += nStrSize;

                // 资金
                xData.SetMoney( xReader.ReadDword() );

                // 公告
                nStrSize = xReader.ReadInt();
                char szBuffer[ CountryDefine::MaxNoticeLength ] = { 0 };
                memcpy_s( szBuffer, sizeof( szBuffer ), xReader.GetPointer().byte, min( sizeof( szBuffer ) - 1, sizeof( CHAR ) * nStrSize ) );
                xData.SetNotice( szBuffer );
                xReader.GetPointer().c += nStrSize;

                // 国王帮会
                xData.SetKingGuild( xReader.ReadDword() );

                // 青龙帮会
                xData.SetDragonGuild( xReader.ReadDword() );

                // 朱雀帮会
                xData.SetRosefinchGuild( xReader.ReadDword() );

                // 上次综合实力
                xData.SetLastStrength( xReader.ReadDword() );

                // 本次综合实力
                xData.SetNowStrength( xReader.ReadDword() );

                // 是否已经改变国家名字
                xData.SetChangeName( xReader.ReadByte() );

                // 国战杀人排行
                xData.SetSortIndex( xReader.ReadByte() );
                xData.SetKillCount( xReader.ReadDword() );
                xData.SetDeathCount( xReader.ReadWord() );
				xData.SetTribute(InitTribute);
            }
            xLoader.EndChunk( 'bse2' );
        }
		else if( xLoader.IsChunk( 'bse3' ) )
		{
			xLoader.StartChunk( 'bse3' );
			CDataChunkLoader xReader( xLoader.GetPointer().byte, xLoader.GetChunkSize() );
			{
				xData.SetID( xReader.ReadByte() );

				// 名字
				int nStrSize = xReader.ReadInt();
				char szName[ CountryDefine::MaxCountryLength ] = { 0 };
				memcpy_s( szName, sizeof( szName ), xReader.GetPointer().byte, min( sizeof( szName ) - 1, sizeof( CHAR ) * nStrSize ) );
				xData.SetName( szName );
				xReader.GetPointer().c += nStrSize;

				// 资金
				xData.SetMoney( xReader.ReadDword() );

				// 公告
				nStrSize = xReader.ReadInt();
				char szBuffer[ CountryDefine::MaxNoticeLength ] = { 0 };
				memcpy_s( szBuffer, sizeof( szBuffer ), xReader.GetPointer().byte, min( sizeof( szBuffer ) - 1, sizeof( CHAR ) * nStrSize ) );
				xData.SetNotice( szBuffer );
				xReader.GetPointer().c += nStrSize;

				// 国王帮会
				xData.SetKingGuild( xReader.ReadDword() );

				// 青龙帮会
				xData.SetDragonGuild( xReader.ReadDword() );

				// 朱雀帮会
				xData.SetRosefinchGuild( xReader.ReadDword() );

				// 上次综合实力
				xData.SetLastStrength( xReader.ReadDword() );

				// 本次综合实力
				xData.SetNowStrength( xReader.ReadDword() );

				// 是否已经改变国家名字
				xData.SetChangeName( xReader.ReadByte() );

				// 国战杀人排行
				xData.SetSortIndex( xReader.ReadByte() );
				xData.SetKillCount( xReader.ReadDword() );
				xData.SetDeathCount( xReader.ReadDword() );
				xData.SetTribute(xReader.ReadDword());
			}
			xLoader.EndChunk( 'bse3' );
		}
        else if ( xLoader.IsChunk( 'off1' ) )
        {
            xLoader.StartChunk( 'off1' );
            CDataChunkLoader xReader( xLoader.GetPointer().byte, xLoader.GetChunkSize() );
            {
                for ( int i = CountryDefine::Position_None + 1; i < CountryDefine::Position_Max; ++i )
                {
                    if ( xReader.IsChunk( 'ofd1' ) )
                    {
                        xReader.StartChunk( 'ofd1' );
                        {
                            ReadOfficialInfo( xReader.GetPointer().byte, xReader.GetChunkSize(), xData.GetOfficial( i ) );
                        }
                        xReader.EndChunk( 'ofd1' );
                    }
                    else
                    {
                        xReader.SkipChunk();
                        break;
                    }

                }
            }
            xLoader.EndChunk( 'off1' );
        }
        else if ( xLoader.IsChunk( 'opt1' ) )
        {
            xLoader.StartChunk( 'opt1' );
            CDataChunkLoader xReader( xLoader.GetPointer().byte, xLoader.GetChunkSize() );
            {
                xData.SetRecordTime( xReader.ReadDword() );
                xData.SetPlacardCount( xReader.ReadByte() );
                xData.SetConveneCount( xReader.ReadByte() );
                xData.SetRaiseCount( xReader.ReadByte() );
                xData.SetBanSpeakCount( xReader.ReadByte() );
                xData.SetRemitCount( xReader.ReadByte() );
                xData.SetChainCount( xReader.ReadByte() );
            }
            xLoader.EndChunk( 'opt1' );
        }
        else if ( xLoader.IsChunk( 'qpt1' ) )
        {
            xLoader.StartChunk( 'qpt1' );
            CDataChunkLoader xReader( xLoader.GetPointer().byte, xLoader.GetChunkSize() );
            {
                xReader.ReadToBuffer( (BYTE*)xData.GetQuestOperate( CountryDefine::QuestType_None ), sizeof( OperateTime ) * CountryDefine::QuestType_Max );
            }
            xLoader.EndChunk( 'qpt1' );
        }
		else if( xLoader.IsChunk( 'cs1' ) )
		{
			xLoader.StartChunk( 'cs1' );
            CDataChunkLoader xReader( xLoader.GetPointer().byte, xLoader.GetChunkSize() );
			for ( unsigned char i = CountryDefine::QuestType_None; i < CountryDefine::QuestType_Max; ++i )
			{
				xData.SetQuestSumBytype(i,xReader.ReadByte());
			}
			xData.SetDoneQuestStrength(xReader.ReadDword());
		}
        else
        {
            xLoader.SkipChunk();
        }
    }
}

void CountrySave::SaveOfficialInfo( CDataChunkWriter* pWriter, OfficialInfo* pInfo )
{
    pWriter->StartChunk( DC_TAG( 'oal1' ) );
    {
        pWriter->WriteDword( pInfo->GetID() );
        pWriter->WriteString( const_cast< char* >( pInfo->GetName() ) );
        pWriter->WriteByte( pInfo->GetPosition() );
        pWriter->WriteDword( pInfo->GetRight() );
    }
    pWriter->EndChunk( DC_TAG( 'oal1' ) );
}

void CountrySave::ReadOfficialInfo( BYTE* byBuff,DWORD dwSize, OfficialInfo* pInfo )
{
    CDataChunkLoader xLoader( byBuff, dwSize );

    while( !xLoader.IsEndOfMemory() )
    {
        if ( xLoader.IsChunk( 'oal1' ) )
        {
            xLoader.StartChunk( 'oal1' );
            {
                CDataChunkLoader xReader( xLoader.GetPointer().byte, xLoader.GetChunkSize() );
                
                pInfo->SetID( xReader.ReadDword() );

                int nStrSize = xReader.ReadInt();
                char szName[ CountryDefine::MaxNameLength ] = { 0 };
                memcpy_s( szName, sizeof( szName ), xReader.GetPointer().byte, min( sizeof( szName ) - 1, sizeof( CHAR ) * nStrSize ) );
                pInfo->SetName( szName );

                xReader.GetPointer().c += nStrSize;

                pInfo->SetPosition( xReader.ReadByte() );
                pInfo->SetRight( xReader.ReadDword() );	

				pInfo->SetRight(CountryDefine::GetRightByPosition(pInfo->GetPosition()));
            }
            xLoader.EndChunk( 'oal1' );
        }
        else 
        {
            xLoader.SkipChunk();
        }
    }
}


bool CountrySave::WriteGameCountry( CountryData& xData, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize )
{
    CDataChunkWriter xWriter( pOutBuffer, outBufferSize );
    SaveGameCountry( &xWriter, xData );

    nActualSize = xWriter.GetUsedSize();
    if( nActualSize == 0 )
    {
        xWriter.Destroy();
        return false;
    }

    if ( nActualSize > outBufferSize)
    { return false; }


    xWriter.Destroy();
    return true;
}