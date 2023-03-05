#include "Me3d/Me3d.h"
#include "MeRTLibs.h"
#include "Me3d/effect/flasheffect.h"
#include "WordParser.h"
#include "helper.h"
#include "FuncPerformanceLog.h"
#include "Me3d/engine/Engine.h"
#include "Me3d/include.h"
#include "DataChunkWriter.h"
#include "Me3d/MathLib.h"
#include "Me3d/effect/effectmanager.h"
CHitFlashEffect::Track::Track()
{
	guardfunc;
	keyStart.fTime = 0.0f;
	keyEnd.fTime = 1.0f;
	unguard;
}

BOOL CHitFlashEffect::Track::AddKeyFrame( KeyFrame& key )
{
	guardfunc;
	if( key.fTime <= 0.0f )
	{
		keyStart = key;
		return TRUE;
	}
	if( key.fTime >= 1.0f )
	{
		keyEnd = key;
		return TRUE;
	}
	for( int nKey = 0; nKey < keyframes.size()-1; nKey++ )
	{
		if( key.fTime >= keyframes[nKey].fTime &&
			key.fTime < keyframes[nKey+1].fTime )
		{
			keyframes.insert( keyframes.begin()+nKey, key );
			return TRUE;
		}
	}
	keyframes.push_back( key );
	return TRUE;
	unguard;
}

int CHitFlashEffect::Track::FindKeyFrame( float fTime, KeyFrame& lkey, KeyFrame& rkey )
{
	guardfunc;
	if( fTime <= 0.0f )
	{
		lkey = keyStart;
		return eKeyStart;
	}
	if( fTime >= 1.0f )
	{
		lkey = keyEnd;
		return eKeyEnd;
	}
	int nNumKey = keyframes.size();
	if( nNumKey == 0 )
	{
		lkey = keyStart;
		rkey = keyEnd;
		return eKeyAny;
	}

	if( fTime < keyframes[0].fTime )
	{
		lkey = keyStart;
		rkey = keyframes[0];
		return eKeyAny;
	}
	
	if( fTime >= keyframes[nNumKey-1].fTime )
	{
		lkey = keyframes[nNumKey-1];
		rkey = keyEnd;
		return eKeyAny;
	}

	for( int nKey = 0; nKey < keyframes.size()-1; nKey++ )
	{
		if( fTime >= keyframes[nKey].fTime &&
			fTime < keyframes[nKey+1].fTime )
		{
			lkey = keyframes[nKey];
			rkey = keyframes[nKey+1];
			return eKeyAny;
		}
	}
	return eKeyNotFound;
	unguard;
}

void CHitFlashEffect::Track::GetKeyAtTime( float fTime, KeyFrame& key )
{
	guardfunc;
	KeyFrame lkey, rkey;
	int nCode = FindKeyFrame( fTime, lkey, rkey );
	switch( nCode )
	{
	case eKeyStart:
	case eKeyEnd:
		key = lkey;
		break;
	case eKeyAny:
		{
			float t = (fTime-lkey.fTime)/(rkey.fTime-lkey.fTime);

			key.bVisible = lkey.bVisible;
			key.fAlpha = lkey.fAlpha+t*(rkey.fAlpha-lkey.fAlpha);
			key.fSize = lkey.fSize+t*(rkey.fSize-lkey.fSize);
		}
		break;
	case eKeyNotFound:
		assert( false );
		break;
	}
	unguard;
}
//void CHitFlashEffect::Track::Blend( float t ,KeyFrame& key )
//{
//	
//}
//////////////////////////////////////////////////////////////////////////

CHitFlashEffect::CHitFlashEffect():
m_dwStartTime(0),
m_dwLife(0),
m_nAction(eActionStand),
m_fScale(1.0f),
m_pMaster(NULL),
m_vPos(0,0,0),
m_bOutOfLookerView(false)
//m_fStripThickness(0.0f)
{
	guardfunc;
	ZeroMemory( m_szSound, MAX_PATH );
	unguard;
}

BOOL CHitFlashEffect::IsDead( DWORD dwTime )
{
	guardfunc;
	if( m_pMaster && m_pMaster->IsDestroy() )
	{
		m_pMaster = NULL;
		return TRUE;
	}
	return dwTime >= m_dwStartTime+m_dwLife;
	unguard;
}

void CHitFlashEffect::Release()
{ 
	guardfunc;
	Destroy(); 
	delete this;
	unguard;
}

void CHitFlashEffect::Destroy()
{
	guardfunc;
	for( int nBbrd = 0; nBbrd < m_textures.size(); nBbrd++ )
	{
		if( m_textures[nBbrd].nTextureId != -1 )
		{
			GetEngine()->GetTextureManager()->UnRegisterTexture( m_textures[nBbrd].nTextureId );
			m_textures[nBbrd].nTextureId = -1;
		}
	}
	m_bbrds.clear();
	m_textures.clear();
	unguard;
}

BOOL CHitFlashEffect::LoadSetting( const char* pszFilename )
{
	guardfunc;
	//BYTE* pbyBuffer = NULL;
	//int nBufferSize = 0;
	//if( !Compile( pszFilename, &pbyBuffer, &nBufferSize ) )
	//	return FALSE;
	//LoadFromMemory( pbyBuffer, nBufferSize );
	//delete[] pbyBuffer;
	//return TRUE;

	CEffectManager::Cache* pCache = GetEffectMgr()->GetEffectSetting( pszFilename );
	guard(test1)
	if( !pCache )
	{
		BYTE* pbyBuffer = NULL;
		int nBufferSize = 0;

		if( Compile( pszFilename, &pbyBuffer, &nBufferSize ) )
		{
			GetEffectMgr()->AddEffectSetting( pszFilename, pbyBuffer, nBufferSize );
			pCache = GetEffectMgr()->GetEffectSetting( pszFilename );
		}
		else
		{
			return FALSE;
		}
	}

	if( !pCache )
		return FALSE;
	unguard;

	guard(test2);
	if( !LoadFromMemory( pCache->pbyBuffer, pCache->nSize ) )
	{
		return FALSE;
	}
	unguard;
	//Start();
	return TRUE;

	//CCfgFileLoader l;
	//if( !l.LoadFromFile( pszFilename ) )
	//	return FALSE;
	//if( l.HasKey( "life" ) )
	//	m_dwLife = l.GetIntValue( "Life" );
	//else
	//	m_dwLife = 1000;
	//if( l.HasKey( "action" ) )
	//{
	//	const char* pszAction = l.GetStringValue( "action" );
	//	if( stricmp( pszAction, "follow" ) == 0 )
	//		m_nAction = eActionFollow;
	//	else if( stricmp( pszAction, "stand" ) == 0 )
	//		m_nAction = eActionStand;
	//}
	//if( l.HasKey( "scale" ) )
	//	m_fScale = l.GetFloatValue( "scale" );

	//for( int nSession = 0; nSession < l.GetSessionCount(); nSession++ )
	//{
	//	if( !l.OpenSession( nSession ) )
	//		continue;
	//	if( stricmp( "texture", l.GetCurrentSessionName() ) == 0 )
	//	{
	//		Texture texture;
	//		strcpy( texture.szPath, l.GetStringValue( "file" ) );
	//		m_textures.push_back( texture );
	//	}
	//	else if( stricmp( "bbrd", l.GetCurrentSessionName() ) == 0 )
	//	{
	//		Billboard bbrd;
	//		for( int nLine = 0; nLine < l.GetCurrentSessionLineCount(); nLine++ )
	//		{
	//			const char* pszName = l.GetLineKeyName( nLine );
	//			if( stricmp( pszName, "texture" ) == 0 )
	//			{
	//				bbrd.nTexture = atoi( l.GetLineStringValue( nLine ) );
	//			}
	//			else if( stricmp( pszName, "drawtime" ) == 0 )
	//			{
	//				bbrd.nNumDrawTime = atoi( l.GetLineStringValue( nLine ) );
	//			}
	//			else if( stricmp( pszName, "h" ) == 0 )
	//			{
	//				bbrd.vPos.z = atof( l.GetLineStringValue( nLine ) );
	//			}
	//			else if( stricmp( pszName, "key" ) == 0 )
	//			{
	//				const char* pszKey = l.GetLineStringValue( nLine );
	//				static char szBuf[1024];
	//				HelperFunc::SafeNCpy( szBuf, pszKey, 1024 );
	//				int nLen = strlen( szBuf );
	//				// 把,:()变成空格，让分析器分析
	//				for( int c = 0; c < nLen; c++ )
	//				{
	//					if( szBuf[c] == ',' ||
	//						szBuf[c] == ':' ||
	//						szBuf[c] == '(' ||
	//						szBuf[c] == ')' )
	//						szBuf[c] = ' ';
	//				}
	//				WordParser w;
	//				w.Parse( szBuf );
	//				float fTime = atof( w.GetWord( 1 ) );
	//				for( int nWord = 2; nWord < w.GetWordCount(); nWord += 2 )
	//				{
	//					if( stricmp( w.GetWord( nWord ), "alpha" ) == 0 )
	//					{
	//						KeyFrame key;
	//						key.fTime = fTime;
	//						key.fAlpha = atof( w.GetWord( nWord+1 ) );
	//						bbrd.tracks[eTrackAlpha].keyframes.push_back( key );
	//					}
	//					else if( stricmp( w.GetWord( nWord ), "size" ) == 0 )
	//					{
	//						KeyFrame key;
	//						key.fTime = fTime;
	//						key.fSize = atof( w.GetWord( nWord+1 ) );
	//						bbrd.tracks[eTrackSize].keyframes.push_back( key );
	//					}
	//					else if( stricmp( w.GetWord( nWord ), "visi" ) == 0 )
	//					{
	//						KeyFrame key;
	//						key.fTime = fTime;
	//						key.bVisible = atoi( w.GetWord( nWord+1 ) );
	//						bbrd.tracks[eTrackVisible].keyframes.push_back( key );
	//					}
	//				}
	//			}
	//		}
	//		m_bbrds.push_back( bbrd );
	//	}
	//}
	//return TRUE;
	unguard;
}
BOOL CHitFlashEffect::Compile( const char* pszFilename, BYTE** ppbyBuffer, int* pnBufferSize )
{
	guardfunc;
// 	CDataChunkWriter w;
// 	CCfgFileLoader l;
// 	if( !l.LoadFromFile( pszFilename ) )
// 		return FALSE;
// 	if( l.HasKey( "life" ) )
// 	{
// 		DWORD dwLife = l.GetIntValue( "life" );
// 		w.WriteDwordChunk( 'life', dwLife );
// 	}
// 	
// 	if( l.HasKey( "action" ) )
// 	{
// 		const char* pszAction = l.GetStringValue( "action" );
// 		int nAction = 0;
// 		if( stricmp( pszAction, "follow" ) == 0 )
// 			nAction = eActionFollow;
// 		else if( stricmp( pszAction, "stand" ) == 0 )
// 			nAction = eActionStand;
// 		
// 		w.WriteIntChunk( 'act0', nAction );
// 	}
// 	if( l.HasKey( "scale" ) )
// 	{
// 		float fScale = l.GetFloatValue( "scale" );
// 		w.WriteFloatChunk( 'scal', fScale );
// 	}
// 	if( l.HasKey( "StripThickness" ) )
// 	{
// 		w.WriteFloatChunk( 'sthk', l.GetFloatValue( "StripThickness" ) );
// 	}
// 	
// 	if( l.HasKey( "Sound" ) )
// 	{
// 		char szPath[MAX_PATH] = "";
// 		strcpy( szPath, l.GetStringValue( "Sound" ) );
// 		w.WriteBufferChunk( 'sund', szPath, MAX_PATH );
// 	}
// 
// 	std::vector<Texture> textures;
// 	std::vector<Billboard> bbrds;
// 	for( int nSession = 0; nSession < l.GetSessionCount(); nSession++ )
// 	{
// 		if( !l.OpenSession( nSession ) )
// 			continue;
// 		if( stricmp( "texture", l.GetCurrentSessionName() ) == 0 )
// 		{
// 			Texture texture;
// 			strcpy( texture.szPath, l.GetStringValue( "file" ) );
// 			textures.push_back( texture );
// 		}
// 		else if( stricmp( "bbrd", l.GetCurrentSessionName() ) == 0 ||
// 				 stricmp( "strip", l.GetCurrentSessionName() ) == 0 )
// 		{
// 
// 
// 			Billboard bbrd;
// 			if( stricmp( "strip", l.GetCurrentSessionName() ) == 0 )
// 				bbrd.nType = eBbrd_Strip;
// 
// 			for( int nLine = 0; nLine < l.GetCurrentSessionLineCount(); nLine++ )
// 			{
// 				const char* pszName = l.GetLineKeyName( nLine );
// 				if( stricmp( pszName, "texture" ) == 0 )
// 				{
// 					bbrd.nTexture = atoi( l.GetLineStringValue( nLine ) );
// 				}
// 				else if( stricmp( pszName, "drawtime" ) == 0 )
// 				{
// 					bbrd.nNumDrawTime = atoi( l.GetLineStringValue( nLine ) );
// 				}
// 				else if( stricmp( pszName, "h" ) == 0 )
// 				{
// 					bbrd.vPos.z = atof( l.GetLineStringValue( nLine ) );
// 				}
// 				else if( stricmp( pszName, "num" ) == 0 )
// 				{
// 					if( bbrd.nType == eBbrd_Strip )
// 						bbrd.nNumStrip = atoi( l.GetLineStringValue( nLine ) );
// 				}
// 				else if( stricmp( pszName, "half" ) == 0 )
// 				{
// 					if( bbrd.nType == eBbrd_Strip )
// 						bbrd.bHalfStrip = atoi( l.GetLineStringValue( nLine ) );
// 				}
// 				else if( stricmp( pszName, "innerradius" ) == 0 )
// 				{
// 					if( bbrd.nType == eBbrd_Strip )
// 						bbrd.fHalfStripInnerRadius = atof( l.GetLineStringValue( nLine ) );
// 				}
// 				else if( stricmp( pszName, "thickness" ) == 0 )
// 				{
// 					if( bbrd.nType == eBbrd_Strip )
// 						bbrd.fStripThickness = atof( l.GetLineStringValue( nLine ) );
// 				}
// 				else if( stricmp( pszName, "average" ) == 0 )
// 				{
// 					if( bbrd.nType == eBbrd_Strip )
// 						bbrd.bStripAverage = atoi( l.GetLineStringValue( nLine ) );
// 				}
// 
// 				else if( stricmp( pszName, "key" ) == 0 )
// 				{
// 					const char* pszKey = l.GetLineStringValue( nLine );
// 					static char szBuf[1024];
// 					HelperFunc::SafeNCpy( szBuf, pszKey, 1024 );
// 					int nLen = strlen( szBuf );
// 					// 把,:()变成空格，让分析器分析
// 					for( int c = 0; c < nLen; c++ )
// 					{
// 						if( szBuf[c] == ',' ||
// 							szBuf[c] == ':' ||
// 							szBuf[c] == '(' ||
// 							szBuf[c] == ')' )
// 							szBuf[c] = ' ';
// 
// 					}
// 					WordParser w;
// 					w.Parse( szBuf );
// 
// 					float fTime = atof( w.GetWord( 1 ) );
// 					for( int nWord = 2; nWord < w.GetWordCount(); nWord += 2 )
// 					{
// 						if( stricmp( w.GetWord( nWord ), "alpha" ) == 0 )
// 						{
// 							KeyFrame key;
// 							key.fTime = fTime;
// 							key.fAlpha = atof( w.GetWord( nWord+1 ) );
// 							bbrd.tracks[eTrackAlpha].keyframes.push_back( key );
// 						}
// 						else if( stricmp( w.GetWord( nWord ), "size" ) == 0 )
// 						{
// 							KeyFrame key;
// 							key.fTime = fTime;
// 							key.fSize = atof( w.GetWord( nWord+1 ) );
// 							bbrd.tracks[eTrackSize].keyframes.push_back( key );
// 						}
// 						else if( stricmp( w.GetWord( nWord ), "visi" ) == 0 )
// 						{
// 							KeyFrame key;
// 							key.fTime = fTime;
// 							key.bVisible = atoi( w.GetWord( nWord+1 ) );
// 							bbrd.tracks[eTrackVisible].keyframes.push_back( key );
// 						}
// 
// 					}
// 
// 				}
// 			}
// 			bbrds.push_back( bbrd );
// 		}
// 	}
// 	w.StartChunkWithTag( 'texs' );
// 	{
// 		w.WriteInt( textures.size() );
// 		for( int nTex = 0; nTex < textures.size(); nTex++ )
// 		{
// 			w.WriteBufferChunk( 'tex0', textures[nTex].szPath, MAX_PATH );
// 		}
// 	}
// 	w.EndChunkWithTag( 'texs' );
// 	w.StartChunkWithTag( 'bbds' );
// 	{
// 		w.WriteInt( bbrds.size() );
// 		for( int nBbrd = 0; nBbrd < bbrds.size(); nBbrd++ )
// 		{
// 			Billboard& bbrd = bbrds[nBbrd];
// 			w.StartChunkWithTag( 'bbrd' );
// 			{
// 				w.WriteIntChunk( 'type', bbrd.nType );
// 				w.WriteIntChunk( 'text', bbrd.nTexture );
// 				w.WriteFloatChunk( 'heig', bbrd.vPos.z );
// 				w.WriteIntChunk( 'drtm', bbrd.nNumDrawTime );
// 				w.WriteIntChunk( 'snum', bbrd.nNumStrip );
// 				w.WriteIntChunk( 'hftp', bbrd.bHalfStrip );
// 				w.WriteFloatChunk( 'hfir', bbrd.fHalfStripInnerRadius );
// 				w.WriteFloatChunk( 'sthk', bbrd.fStripThickness );
// 				w.WriteIntChunk( 'savr', bbrd.bStripAverage );
// 				w.StartChunkWithTag( 'trck' );
// 				{
// 					for( int nTrack = 0; nTrack < eTrackMax; nTrack++ )
// 					{
// 						DWORD dwName = 0;
// 						switch( nTrack )
// 						{
// 						case eTrackAlpha:
// 							dwName = 'alpa';
// 							break;
// 						case eTrackVisible:
// 							dwName = 'visi';
// 							break;
// 						case eTrackSize:
// 							dwName = 'size';
// 							break;
// 						default:
// 							continue;
// 						}
// 
// 						w.StartChunkWithTag( dwName );
// 						{
// 							Track& track = bbrd.tracks[nTrack];
// 							w.WriteInt( track.keyframes.size() );
// 							for( int nKey = 0; nKey < track.keyframes.size(); nKey++ )
// 							{
// 								w.Write( &track.keyframes[nKey], sizeof(KeyFrame), 1 );
// 							}
// 						}
// 						w.EndChunkWithTag( dwName );
// 					}
// 				}
// 				w.EndChunkWithTag( 'trck' );
// 			}
// 			w.EndChunkWithTag( 'bbrd' );
// 		}
// 	}
// 	w.EndChunkWithTag( 'bbds' );
// 
// 	int nUsed = w.GetUsedSize();
// 	BYTE* pbyBuffer = MeDefaultNew BYTE[nUsed];
// 	memcpy( pbyBuffer, w.GetBuffer(), nUsed );
// 	*ppbyBuffer = pbyBuffer;
// 	*pnBufferSize = nUsed;
// 	
// 	//CDataChunkLoader r(pbyBuffer,nUsed);
// 	//r.OpenPath( "bbds\\bbrd" );
// 	
// 	w.Destroy();
	return TRUE;
	unguard;
}
BOOL CHitFlashEffect::LoadFromMemory( BYTE* pbyBuffer, int nBufferSize )
{
	CDataChunkLoader l(pbyBuffer, nBufferSize);
	while( !l.IsEndOfMemory() )
	{
		if( l.TryReadDwordChunk( 'life', m_dwLife ) ){}
		else if( l.TryReadIntChunk( 'act0', m_nAction ) ){}
		else if( l.TryReadFloatChunk( 'scal', m_fScale ) ){}
		//else if( l.TryReadFloatChunk( 'sthk', m_fStripThickness ) ){}
		else if( l.IsChunk( 'sund' ) )
		{
			l.OpenChunk();
			l.ReadToBuffer( (BYTE*)m_szSound, MAX_PATH );
			l.CloseChunk();
		}
		else if( l.IsChunk( 'texs' ) )
		{
			l.OpenChunk();
			int nNumTexture = l.ReadInt();
			while( !l.IsEndOfChunk() )
			{
				if( l.IsChunk( 'tex0' ) )
				{
					l.OpenChunk();
					Texture texture;
					l.ReadToBuffer( (BYTE*)texture.szPath, MAX_PATH );
					m_textures.push_back( texture );
					l.CloseChunk();
				}
				else 
					l.SkipChunk();
			}
			l.CloseChunk();
		}
		else if( l.IsChunk( 'bbds' ) )
		{
			l.OpenChunk();
			int nNumBbrd = l.ReadInt();
			while( !l.IsEndOfChunk() )
			{
				if( l.IsChunk( 'bbrd' ) )
				{
					l.OpenChunk();
					
					Billboard bbrd;
					while( !l.IsEndOfChunk() )
					{
						if( l.TryReadIntChunk( 'type', bbrd.nType ) ){}
						else if( l.TryReadIntChunk( 'text', bbrd.nTexture ) ){}
						else if( l.TryReadFloatChunk( 'heig', bbrd.vPos.z ) ){}
						else if( l.TryReadIntChunk( 'drtm', bbrd.nNumDrawTime ) ){}
						// strip
						else if( l.TryReadIntChunk( 'snum', bbrd.nNumStrip ) ){}
						else if( l.TryReadIntChunk( 'hftp', bbrd.bHalfStrip ) ){}
						else if( l.TryReadFloatChunk( 'hfir', bbrd.fHalfStripInnerRadius ) ){}
						else if( l.TryReadFloatChunk( 'sthk', bbrd.fStripThickness ) ){}
						else if( l.TryReadIntChunk( 'savr', bbrd.bStripAverage ) ){}
						// track
						else if( l.IsChunk( 'trck' ) )
						{
							l.OpenChunk();
							while( !l.IsEndOfChunk() )
							{
								if( l.IsChunk( 'alpa' ) )
								{
									l.OpenChunk();
									int nNumKey = l.ReadInt();
									for( int nKey = 0; nKey < nNumKey; nKey++ )
									{
										KeyFrame key;
										l.ReadToBuffer( (BYTE*)&key, sizeof(key) );
										bbrd.tracks[eTrackAlpha].keyframes.push_back( key );
									}
									l.CloseChunk();
								}
								else if( l.IsChunk( 'visi' ) )
								{
									l.OpenChunk();
									int nNumKey = l.ReadInt();
									for( int nKey = 0; nKey < nNumKey; nKey++ )
									{
										KeyFrame key;
										l.ReadToBuffer( (BYTE*)&key, sizeof(key) );
										bbrd.tracks[eTrackVisible].keyframes.push_back( key );
									}
									l.CloseChunk();
								}
								else if( l.IsChunk( 'size' ) )
								{
									l.OpenChunk();
									int nNumKey = l.ReadInt();
									for( int nKey = 0; nKey < nNumKey; nKey++ )
									{
										KeyFrame key;
										l.ReadToBuffer( (BYTE*)&key, sizeof(key) );
										bbrd.tracks[eTrackSize].keyframes.push_back( key );
									}
									l.CloseChunk();
								}
								else 
									l.SkipChunk();
							}
							l.CloseChunk();
						}
						else 
							l.SkipChunk();
						
					}
					
					l.CloseChunk();
					m_bbrds.push_back( bbrd );
				}
				else 
					l.SkipChunk();
			}
			l.CloseChunk();
		}
		else 
			l.SkipChunk();
	}
	return TRUE;
}

void CHitFlashEffect::Start()
{
	guardfunc;
	m_dwStartTime = HQ_TimeGetTime();
	for( int nTexture = 0; nTexture < m_textures.size(); nTexture++ )
	{
		m_textures[nTexture].nTextureId = 
			GetEngine()->GetTextureManager()->RegisterTexture( m_textures[nTexture].szPath, false, TRUE );
	}
	
	for( int nBbrd = 0; nBbrd < m_bbrds.size(); nBbrd++ )
	{
		Billboard& bbrd = m_bbrds[nBbrd];
		if( bbrd.nType == eBbrd_Strip )
		{
			bbrd.strips.reserve( bbrd.nNumStrip );
			bbrd.strips.resize( bbrd.nNumStrip );
			float fRotStart = D3DX_PI*2*Random();
			for( int nStrip = 0; nStrip < bbrd.nNumStrip; nStrip++ )
			{
				Strip& strip = bbrd.strips[nStrip];
				if( bbrd.bStripAverage )
					strip.fRot = fRotStart+nStrip*(D3DX_PI*2/bbrd.nNumStrip);
				else
					strip.fRot = D3DX_PI*2*Random();
			}
		}
	}
	unguard;
}

void CHitFlashEffect::DrawBillboard( Billboard& bbrd, D3DXVECTOR3 vPos, float fRadius, int nTextureId, DWORD dwColor )
{
	guardfunc;
	float fSize = fRadius;
	D3DXVECTOR3 vUp(0,0,1);// = Config::GetCamera()->GetUpVec();
	//D3DXVECTOR3 vUp = Config::GetCamera()->GetUpVec();
	D3DXVECTOR3 vAntiView = Config::GetCamera()->GetViewDir();
	vAntiView *= -1;

	D3DXVECTOR3 vRight;
	D3DXVec3Cross( &vRight, &vAntiView, &vUp  );
	D3DXVec3Normalize( &vRight, &vRight );
	//D3DXVECTOR3 vRight = Config::GetCamera()->GetCross();

	D3DXVec3Cross( &vUp, &vAntiView, &vRight  );
	D3DXVec3Normalize( &vUp, &vUp );

	float fGlobalScale = GetMe3dConfig()->m_fMdlSpaceScale;
	fGlobalScale *= m_fScale;

	struct BillboardVert
	{
		D3DXVECTOR3 p;
		DWORD		color;
		float		u,v;
	};
	DWORD dwFlag = eOpModulate1X|eTwoSided|eLightingDisable|eDstBlendOne|eAlphaBlend|eZWriteDisable|eSortByFarZ;

	if( bbrd.nType == eBbrd_Quad )
	{

		vUp *= fRadius;
		vRight *= fRadius;

		BillboardVert vertex[4];
		vertex[0].p = vPos-vUp-vRight;
		vertex[0].color = dwColor;
		vertex[0].u = 0;
		vertex[0].v = 1;

		vertex[1].p = vPos+vUp-vRight;
		vertex[1].color = dwColor;
		vertex[1].u = 0;
		vertex[1].v = 0;


		vertex[2].p = vPos-vUp+vRight;
		vertex[2].color = dwColor;
		vertex[2].u = 1;
		vertex[2].v = 1;


		vertex[3].p = vPos+vUp+vRight;
		vertex[3].color = dwColor;
		vertex[3].u = 1;
		vertex[3].v = 0;


		short index[] = { 0, 1, 2, 2, 1, 3 };
		GetEngine()->GetRenderer()->DirectPushSurface(
			nTextureId,
			-1,
			MEX2_SHADER,

			D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1,
			sizeof(BillboardVert),
			(BYTE*)vertex,
			4,
			(BYTE*)index,
			2, 
			dwFlag );
	}
	else if( bbrd.nType == eBbrd_Strip )
	{
		int const MAX_STRIP = 32;
		int nNumStrip = bbrd.strips.size();
		if( nNumStrip >= MAX_STRIP )
			nNumStrip = MAX_STRIP;

		static BillboardVert vertex[MAX_STRIP*4];
		for( int nStrip = 0; nStrip < nNumStrip; nStrip++ )
		{
			Strip& strip = bbrd.strips[nStrip];
			D3DXVECTOR3 up = vUp*bbrd.fStripThickness*fGlobalScale;
			D3DXVECTOR3 right = vRight*fRadius;
			D3DXMATRIX m;
			D3DXMatrixRotationAxis( &m, &vAntiView, strip.fRot );

			D3DXVec3TransformCoord( &up, &up, &m );
			D3DXVec3TransformCoord( &right, &right, &m );
			
			if( bbrd.bHalfStrip )
			{

				D3DXVECTOR3 vStripRightUnit = right;
				D3DXVec3Normalize( &vStripRightUnit, &vStripRightUnit );

				D3DXVECTOR3 vTrans = vStripRightUnit*bbrd.fHalfStripInnerRadius*fGlobalScale; 
				vertex[nStrip*4+0].p = vPos-up+vTrans;
				vertex[nStrip*4+1].p = vPos+up+vTrans;
				vertex[nStrip*4+2].p = vPos-up+right+vTrans;
				vertex[nStrip*4+3].p = vPos+up+right+vTrans;
			}
			else
			{
				vertex[nStrip*4+0].p = vPos-up-right;
				vertex[nStrip*4+1].p = vPos+up-right;
				vertex[nStrip*4+2].p = vPos-up+right;
				vertex[nStrip*4+3].p = vPos+up+right;
			}
			
			
			vertex[nStrip*4+0].color = dwColor;
			vertex[nStrip*4+0].u = 0;
			vertex[nStrip*4+0].v = 1;

			
			vertex[nStrip*4+1].color = dwColor;
			vertex[nStrip*4+1].u = 0;
			vertex[nStrip*4+1].v = 0;


			
			vertex[nStrip*4+2].color = dwColor;
			vertex[nStrip*4+2].u = 1;
			vertex[nStrip*4+2].v = 1;


			
			vertex[nStrip*4+3].color = dwColor;
			vertex[nStrip*4+3].u = 1;
			vertex[nStrip*4+3].v = 0;
		}


		short index[] = { 0, 1, 2, 2, 1, 3 };
		GetEngine()->GetRenderer()->DirectPushSurface(
			nTextureId,
			-1,
			MEX2_SHADER,

			D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1,
			sizeof(BillboardVert),
			(BYTE*)vertex,
			nNumStrip*4,
			(BYTE*)Emitter::GetCWIndexBuffer(),
			nNumStrip*2, 
			dwFlag );
	}
	unguard;
}

void CHitFlashEffect::Render()
{
	guardfunc;
	if( m_bOutOfLookerView )
		return;

	if( m_pMaster )
		m_pMaster->GetPos( (float*)&m_vPos );

	DWORD dwTime = HQ_TimeGetTime();
	float fTime = 0.0f;
	guard(test0);
	if( m_dwLife == 0 )
		fTime = 1.0f;
	else
		fTime = (dwTime-m_dwStartTime)/(float)m_dwLife;
	if( fTime < 0.0f ||
		fTime > 1.0f )
		return;
	unguard;

	float fGlobalScale = GetMe3dConfig()->m_fMdlSpaceScale;
	for( int nBbrd = 0; nBbrd < m_bbrds.size(); nBbrd++ )
	{
		Billboard& bbrd = m_bbrds[nBbrd];
		KeyFrame keyVisible;
		bbrd.tracks[eTrackVisible].GetKeyAtTime( fTime, keyVisible );
		if( !keyVisible.bVisible )
			continue;
		KeyFrame keyAlpha;
		KeyFrame keySize;
		bbrd.tracks[eTrackAlpha].GetKeyAtTime( fTime, keyAlpha );
		bbrd.tracks[eTrackSize].GetKeyAtTime( fTime, keySize );
		//int k = 0;
		int nTextureId = -1;
		if( bbrd.nTexture >= 0 && bbrd.nTexture < m_textures.size() )
			nTextureId = m_textures[bbrd.nTexture].nTextureId;
		DWORD alpha = (DWORD)(keyAlpha.fAlpha*255);
		float fSize = keySize.fSize*m_fScale*fGlobalScale;
		D3DXVECTOR3 vPos = m_vPos;
		vPos.z += bbrd.vPos.z*fGlobalScale;
		for( int nTime = 0; nTime < bbrd.nNumDrawTime; nTime++ )
			DrawBillboard( bbrd, vPos, fSize, nTextureId, alpha<<24|0x00ffffff );
	}
	unguard;
}

void CHitFlashEffect::SetDead()
{
	guardfunc;
	m_dwLife = 0;
	unguard;
}

void CHitFlashEffect::Update( DWORD dwTime, D3DXVECTOR3 vPos, float fDistance )
{
	guardfunc;
	if( D3DXVec3Length( &( m_vPos - vPos ) ) > fDistance )
	{
		m_bOutOfLookerView = TRUE;
	}
	else
	{
		m_bOutOfLookerView = FALSE;
	}
	unguard;
}

//void CHitFlashEffect::Cull( D3DXVECTOR3 vPos, float fDistance )
//{
//	guardfunc;
//
//	unguard;
//}