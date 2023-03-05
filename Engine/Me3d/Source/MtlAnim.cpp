#include "Me3d/MtlAnim.h"
#include "Me3d/Global.h"
#include "WordParser.h"
#include "DataChunkWriter.h"
#include "Engine/Engine.h"
#include "CfgFileLoader.h"
#include "FuncPerformanceLog.h"
#include <assert.h>
#include "DataLauncher.h"

static CMtlEffectMgr gs_MtlEffectMgr;
CMtlEffectMgr* GetMtlEffectMgr()
{
	guardfunc;
	return &gs_MtlEffectMgr;
	unguard;
}
CMtlEffectMgr::CMtlEffectMgr():
m_nExternalID(eExternalBase)
{
	guardfunc;
	m_Effects.NeedDelete( FALSE );
	unguard;
}
CMtlEffectMgr::~CMtlEffectMgr()
{
	guardfunc;
	unguard;
}
int CMtlEffectMgr::AddEffect( const char* pszFileName )
{
	guardfunc;
	MtlAnim* pEffect = MeNew MtlAnim;
	if( !pEffect->LoadFromFile( pszFileName ) )
	{
		pEffect->Destroy();
		delete pEffect;
		return -1;
	}
	int nID = m_nExternalID++;
	m_Effects.Add( nID, pEffect );
	return nID;
	unguard;
}
void CMtlEffectMgr::Destroy()
{
	guardfunc;
	std::vector<MtlAnim*> vectorEffect;
	m_Effects.GetObjects( &vectorEffect );
	for( int i = 0; i < vectorEffect.size(); i++ )
	{
		vectorEffect[i]->Destroy();
		delete vectorEffect[i];
	}
	m_Effects.Destroy();
	unguard;
}


MtlAnim::SSetting::SSetting():
fUOffset(0.0f),
fVOffset(0.0f),
dwColor(0xffffffff),
nTextureId(-1),
dwBlendMode(0),
bRender2Pass(FALSE),
bGlobalTransparent(FALSE),
fAlpha(1.0f)
{
	guardfunc;
	unguard;
}

MtlAnim::MtlAnim(void):
//m_pVersion(NULL),
m_pUVTrack(NULL),
m_pColorTrack(NULL),
m_pAlphaTrack(NULL),
m_pTexture(NULL),
//m_pProperty(NULL)
m_dwStartTime(0),
m_nLayerCount(1),
m_bHasSpecular(FALSE),
m_fSpecularPower(0.0f),
m_fSpecularRed(0.0f),
m_fSpecularGreen(0.0f),
m_fSpecularBlue(0.0f)
{
	guardfunc;
	unguard;
}
void MtlAnim::Destroy()
{
	guardfunc;
	if( m_pTexture )
	{
		m_pTexture->Destroy();
		delete m_pTexture;
		m_pTexture = NULL;
	}
	if( m_pUVTrack )
	{
		delete m_pUVTrack;
		m_pUVTrack = NULL;
	}
	if( m_pColorTrack )
	{
		delete m_pColorTrack;
		m_pColorTrack = NULL;
	}
	if( m_pAlphaTrack )
	{
		delete m_pAlphaTrack;
		m_pAlphaTrack = NULL;
	}
	unguard;
}
MtlAnim::~MtlAnim(void)
{
	guardfunc;
	assert( m_pTexture == NULL );
	assert( m_pUVTrack == NULL );
	assert( m_pColorTrack == NULL );
	assert( m_pAlphaTrack == NULL );
	unguard;
}


//BOOL SMtlAnimVersion::Read( UMtlAnimPointer inP, int nSize )
//{
//	UMtlAnimPointer p(inP.p);
//	dwVersion = *p.dw++;
//
//	return TRUE;
//}

SMtlAnimBlendMode::SMtlAnimBlendMode():	
dwMethod(0),
dwFlag(eTwoSided|eAlphaBlend)
{
	guardfunc;
	unguard;
}

void SMtlAnimKeyframe::BlendFrame( SMtlAnimKeyframe* pKeyframeLeft, 
								  SMtlAnimKeyframe* pKeyframeRight, 
								  float t,
								  int nElement )
{
	guardfunc;
	assert( pKeyframeLeft && "blend frame left frame is null" );
	assert( pKeyframeRight && "blend frame right frame is null" );
	for( int i = 0; i < nElement; i++ )
	{
		fValues[i] = pKeyframeLeft->fValues[i]+t*( pKeyframeRight->fValues[i]-pKeyframeLeft->fValues[i] );
		if( fValues[i] > 0 )
		{
			int k = 0;
		}
	}
	unguard;
}
SMtlAnimTrack::SMtlAnimTrack():	dwLength(1000)
{
	guardfunc;
	AddKeyframe( 0, 0, 0, 0, 0 );
	unguard;
}
SMtlAnimTrack::~SMtlAnimTrack()
{
	guardfunc;
	for( int i = 0; i < vectorKeyframe.size(); i++ )
	{
		if( vectorKeyframe[i] )
		{
			delete vectorKeyframe[i];
		}
	}
	unguard;
}

//BOOL SMtlAnimTrack::Read( UMtlAnimPointer inP, int nSize )
//{
//	UMtlAnimPointer p(inP.p);
//
//	dwLength = *p.dw++;
//	int nKeyframeCount = *p.i++;
//
//	assert( nKeyframeCount > 0 && "mtl anim track keyframe coutn must > 0" );
//	
//	vectorKeyframe.reserve( nKeyframeCount );
//	vectorKeyframe.resize( nKeyframeCount );
//	memcpy( &vectorKeyframe[0], p.c, sizeof( SMtlAnimKeyframe )*nKeyframeCount );
//	SMtlAnimKeyframe* a = &vectorKeyframe[0];
//	
//	return TRUE;
//}

BOOL SMtlAnimTrack::GetKeyframe(	DWORD dwTime, 
									SMtlAnimKeyframe** ppKeyframeLeft, 
									SMtlAnimKeyframe** ppKeyframeRight, 
									float* t )
{
	guardfunc;
	*ppKeyframeLeft = NULL;
	*ppKeyframeRight = NULL;
	*t = 0.0f;

	assert( vectorKeyframe.size() > 0 && "mtl anim track key frame count must > 0" );
	assert( dwTime <= dwLength && "mtl anim track get key frame out of range" );
	
	SMtlAnimKeyframe** ppKeyframes = &vectorKeyframe[0];
	int nKeyCount = vectorKeyframe.size();
	for( int i = 0; i < nKeyCount-1; i++ )
	{
		if( dwTime >= ppKeyframes[i]->dwTime &&
			dwTime < ppKeyframes[i+1]->dwTime )
		{
			*ppKeyframeLeft = ppKeyframes[i];
			*ppKeyframeRight = ppKeyframes[i+1];

			float t0 = (float)(*ppKeyframeLeft)->dwTime;
			float t1 = (float)(*ppKeyframeRight)->dwTime;
			*t = (float)( dwTime-t0 )/( t1-t0 );
			if( *t < 0 || *t > 1 )
			{
				assert( false );
			}
			return TRUE;
		}
	}
	*ppKeyframeLeft = ppKeyframes[nKeyCount-1];
	*ppKeyframeRight = ppKeyframes[0];
	float t0 = (float)(*ppKeyframeLeft)->dwTime;
	*t = ( dwTime-t0 )/( dwLength-t0 );
	assert( *t >= 0.0f && *t <= 1.0f && "get keyframe error, t < 0" );
	return TRUE;
	unguard;
}

SMtlAnimKeyframe* SMtlAnimTrack::AddKeyframe( DWORD dwTime, float t0, float t1, float t2, float t3 )
{
	guardfunc;
	assert( dwLength > 0 && "mtl anim track add key frame error, length must > 0" );
	SMtlAnimKeyframe* frame = MeNew SMtlAnimKeyframe;
	frame->dwTime = dwTime;
	frame->fValues[0] = t0;
	frame->fValues[1] = t1;
	frame->fValues[2] = t2;
	frame->fValues[3] = t3;
	return AddKeyframe( frame );
	unguard;
}
SMtlAnimKeyframe* SMtlAnimTrack::AddKeyframe( SMtlAnimKeyframe* pKeyframe )
{
	guardfunc;
	if( vectorKeyframe.size() == 0 )
	{
		vectorKeyframe.push_back( pKeyframe );
		return vectorKeyframe[0];
	}
	if( pKeyframe->dwTime >= dwLength ||
		pKeyframe->dwTime == 0 )
	{
		//delete vectorKeyframe[0];
		DWORD dwTime = vectorKeyframe[0]->dwTime;
		vectorKeyframe[0] = pKeyframe;
		vectorKeyframe[0]->dwTime = dwTime;
		return pKeyframe;
	}

	for( int i = 0; i < vectorKeyframe.size()-1; i++ )
	{
		assert( pKeyframe->dwTime != vectorKeyframe[i]->dwTime && "mtl anim has same time keyframe" );
		if( pKeyframe->dwTime > vectorKeyframe[i]->dwTime &&
			pKeyframe->dwTime <= vectorKeyframe[i+1]->dwTime )
		{
			vectorKeyframe.insert( vectorKeyframe.begin()+i+1, pKeyframe );
			//return TRUE;
			return vectorKeyframe[i+1];
		}
	}
	if( pKeyframe->dwTime <= dwLength )
	{
		vectorKeyframe.push_back( pKeyframe );
		//return TRUE;
		return vectorKeyframe[vectorKeyframe.size()-1];
	}
	//return FALSE;
	return NULL;
	unguard;
}
BOOL SMtlAnimTrack::DelKeyframe( SMtlAnimKeyframe* pKeyframe )
{
	guardfunc;
	for( int i = 0; i < vectorKeyframe.size(); i++ )
	{
		if( pKeyframe == vectorKeyframe[i] )
		{
			delete pKeyframe;
			vectorKeyframe.erase( vectorKeyframe.begin()+i );
			return TRUE;
		}
	}
	return FALSE;
	unguard;
}

SMtlAnimTexture::SMtlAnimTexture():
nTextureId(-1)
{
	guardfunc;
	//strcpy( szFilename, "data\\LightingRed.tga" );
	memset( szFilename, 0x00, sizeof( szFilename ) );
	unguard;
}

SMtlAnimTexture::~SMtlAnimTexture()
{
	guardfunc;
	assert( nTextureId == -1 );
	unguard;
}
void SMtlAnimTexture::Destroy()
{
	guardfunc;
	UnRegister();
	unguard;
}
int SMtlAnimTexture::Register()
{
	guardfunc;
	//UnRegister();
	Destroy();
	nTextureId = GetEngine()->GetTextureManager()->RegisterTexture( szFilename, false, TRUE, FALSE );
	return nTextureId;
	unguard;
}
void SMtlAnimTexture::UnRegister()
{
	guardfunc;
	if( nTextureId != -1 )
	{
		//UnregisterTexture( nTextureId );
		GetEngine()->GetTextureManager()->UnRegisterTexture( nTextureId );
		nTextureId = -1;
		memset( szFilename, 0x00, sizeof( szFilename ) );
	}
	unguard;
}

void MtlAnim::GetSetting( DWORD dwTime, MtlAnim::SSetting* pSetting )
{
	guardfunc;
	// 计算偏移，因为动画要循环播放
	dwTime = dwTime-m_dwStartTime;

	SMtlAnimKeyframe* pLeft = NULL;
	SMtlAnimKeyframe* pRight = NULL;
	float t = 0.0f;
	SMtlAnimKeyframe frame;
	DWORD dwOffset = 0;
	
	DWORD a = 255, r = 255, g = 255, b = 255;
	float fUOffset = 0.0f, fVOffset = 0.0f;
	if( m_pUVTrack )
	{
		dwOffset = dwTime%m_pUVTrack->dwLength;
		m_pUVTrack->GetKeyframe( dwOffset, &pLeft, &pRight, &t );
		frame.BlendFrame( pLeft, pRight, t, 2 );
		fUOffset = frame.fValues[0];
		fVOffset = frame.fValues[1];
	}
	if( m_pColorTrack )
	{
		dwOffset = dwTime%m_pColorTrack->dwLength;
		m_pColorTrack->GetKeyframe( dwOffset, &pLeft, &pRight, &t );

		frame.BlendFrame( pLeft, pRight, t, 3 );
		r = frame.fValues[0]*255;	
		g = frame.fValues[1]*255;
		b = frame.fValues[2]*255;
	}
	if( m_pAlphaTrack )
	{
		dwOffset = dwTime%m_pAlphaTrack->dwLength;
		m_pAlphaTrack->GetKeyframe( dwOffset, &pLeft, &pRight, &t );
		frame.BlendFrame( pLeft, pRight, t, 1 );
		a = frame.fValues[0]*255;
	}
	// 初始化
	memset( pSetting, 0x00, sizeof( SSetting ) );
	pSetting->nTextureId = -1;

	// 
	pSetting->dwColor= a<<24|r<<16|g<<8|b;
	pSetting->fUOffset = fUOffset;
	pSetting->fVOffset = fVOffset;
	pSetting->dwBlendMode = m_BlendMode.dwFlag;
	
	if( m_pTexture )
		pSetting->nTextureId = m_pTexture->nTextureId;

	pSetting->bRender2Pass = m_Property.bRender2Pass;
	unguard;
}


BOOL MtlAnim::LoadFromFile( const char* pszFilename )
{
	guardfunc;
	CCfgFileLoader c;
	if( !c.LoadFromFile( pszFilename ) )
		return FALSE;
	
	for( int i = 0; i < c.GetSessionCount(); i++ )
	{
		if( !c.OpenSession( i ) )
			continue;
		if( _stricmp( c.GetCurrentSessionName(), "Main" ) == 0 )
		{
			if( c.HasKey( "length" ) )
			{
				m_dwLength = c.GetIntValue( "length" );
			}
			if( c.HasKey( "layer" ) )
			{
				m_nLayerCount = c.GetIntValue( "layer" );
			}
			if( c.HasKey( "texture" ) )
			{
				if( !m_pTexture )
				{
					m_pTexture = MeNew SMtlAnimTexture;
				}

				m_pTexture->AssignFilename( c.GetStringValue( "texture" ) );
				if( m_pTexture->Register() == -1 )
				{
					assert( false && "mtlanim register texture failed" );
				}
			}
		}
		else if( _stricmp( c.GetCurrentSessionName(), "specular" ) == 0 )
		{
			m_bHasSpecular = TRUE;
			if( c.HasKey( "power" ) )
				m_fSpecularPower = c.GetFloatValue( "power" );
			if( c.HasKey( "r" ) )
				m_fSpecularRed = c.GetFloatValue( "r" );
			if( c.HasKey( "g" ) )
				m_fSpecularGreen = c.GetFloatValue( "g" );
			if( c.HasKey( "b" ) )
				m_fSpecularBlue = c.GetFloatValue( "b" );
		}
		else if( _stricmp( c.GetCurrentSessionName(), "Keyframe" ) == 0 )
		{
			int nTime = 0;
			if( c.HasKey( "time" ) )
				nTime = c.GetIntValue( "time" );
			if( c.HasKey( "alpha" ) )
			{
				if( !m_pAlphaTrack )
				{
					m_pAlphaTrack = MeNew SMtlAnimTrack;
					m_pAlphaTrack->SetLength( m_dwLength );
				}
				m_pAlphaTrack->AddKeyframe( nTime, c.GetFloatValue( "alpha" ) );
			}
			if( c.HasKey( "r" ) ||
				c.HasKey( "g" ) ||
				c.HasKey( "b" ) )
			{
				if( !m_pColorTrack )
				{
					m_pColorTrack = MeNew SMtlAnimTrack;
					m_pColorTrack->SetLength( m_dwLength );
				}
				m_pColorTrack->AddKeyframe(
					nTime, 
					c.GetIntValue("r")/255.0f, 
					c.GetIntValue("g")/255.0f,
					c.GetIntValue("b")/255.0f );
			}
			if( c.HasKey( "u" ) ||
				c.HasKey( "v" ) )
			{
				if( !m_pUVTrack )
				{
					m_pUVTrack = MeNew SMtlAnimTrack;
					m_pUVTrack->SetLength( m_dwLength );
				}
				m_pUVTrack->AddKeyframe( 
					nTime, 
					c.GetFloatValue( "u" ), 
					c.GetFloatValue( "v" ) );
			}
		}
	}
	return TRUE;
	unguard;
}
BOOL MtlAnim::LoadFromFile2( const char* pszFilename )
{
	guardfunc;

	FILE* fp = fopen( pszFilename, "r" );
	
	if( !fp )
	{
		
		return FALSE;
	}

	char buf[1024];
	while( fgets( buf, 1024, fp ) )
	{
		WordParser words;
		if( words.Parse( buf ) == 0 )continue;

		// length 5000
		if( words.Compare( 0, "length" ) )
		{
			m_dwLength = atoi( words.GetWord( 1 ) );
		}
		// texture	data\texture\effect.tga
		else if( words.Compare( 0, "texture" ) )
		{
			if( !m_pTexture )
			{
				m_pTexture = MeNew SMtlAnimTexture;
			}
			
			m_pTexture->AssignFilename( words.GetWord( 1 ) );
			if( m_pTexture->Register() == -1 )
			{
				assert( false && "mtlanim register texture failed" );
			}
		}
		else if( words.Compare( 0, "Render" ) )
		{
			if( words.Compare( 1, "2Pass" ) )
			{
				m_Property.bRender2Pass = TRUE;
			}
		}
		else if( words.Compare( 0, "BlendMode" ) )
		{
			if( words.Compare( 1, "DstBlendOne" ) )
			{
				m_BlendMode.dwFlag |= eDstBlendOne;
			}
			else if( words.Compare( 1, "TwoSided" ) )
			{
				m_BlendMode.dwFlag |= eTwoSided;
			}
			else if( words.Compare( 1, "AlphaBlend" ) )
			{
				m_BlendMode.dwFlag |= eAlphaBlend;
			}
			else if( words.Compare( 1, "LightOff" ) )
			{
				m_BlendMode.dwFlag |= eLightingDisable;
			}
			else if( words.Compare( 1, "ZWriteOff" ) )
			{
				m_BlendMode.dwFlag |= eZWriteDisable;
			}
		}
		// u 		keyframe 	1000 0.0 1.0f
		else if( words.Compare( 0, "uv" ) )
		{
			if( words.Compare( 1, "keyframe" ) )
			{
				if( !m_pUVTrack )
				{
					m_pUVTrack = MeNew SMtlAnimTrack;
					m_pUVTrack->SetLength( m_dwLength );
				}
				
				DWORD dwTime = atof( words.GetWord( 2 ) )*m_dwLength;
				float u = atof( words.GetWord( 3 ) );
				float v = atof( words.GetWord( 4 ) );

				m_pUVTrack->AddKeyframe( dwTime, u, v );
			}
		}
		// color 	keyframe	3000 255 255 255
		else if( words.Compare( 0, "color" ) )
		{
			if( words.Compare( 1, "keyframe" ) )
			{
				if( !m_pColorTrack )
				{
					m_pColorTrack = MeNew SMtlAnimTrack;
					m_pColorTrack->SetLength( m_dwLength );
				}
				
				DWORD dwTime = atof( words.GetWord( 2 ) )*m_dwLength;
				float r = atoi( words.GetWord( 3 ) )/255.0f;
				float g = atoi( words.GetWord( 4 ) )/255.0f;
				float b = atoi( words.GetWord( 5 ) )/255.0f;
				m_pColorTrack->AddKeyframe( dwTime, r, g, b );
			}
		}
		else if( words.Compare( 0, "alpha" ) )
		{
			if( words.Compare( 1, "keyframe" ) )
			{
				if( !m_pAlphaTrack )
				{
					m_pAlphaTrack = MeNew SMtlAnimTrack;
					m_pAlphaTrack->SetLength( m_dwLength );
				}
				
				DWORD dwTime = atof( words.GetWord( 2 ) )*m_dwLength;
				float alpha = atoi( words.GetWord( 3 ) )/255.0f;
				m_pAlphaTrack->AddKeyframe( dwTime, alpha );
			}
		}
	}
	fclose( fp );
	return TRUE;
	unguard;
}

