#include "Me3d/Me3d.h"
#include "WordParser.h"
#include "helper.h"
#include "FuncPerformanceLog.h"
#include "Me3d/engine/Engine.h"
#include "Me3d/Include.h"
#include "DataChunkWriter.h"
#include "Me3d/MathEx.h"
#include "Me3d/MathLib.h"
#include "Me3d/Model/MexRes.h"
#include "Me3d/effect/MexEffectCtrl.h"
#include "Me3d/effect/effectmanager.h"
#include "Me3d/effect/missileeffect.h"


static char* GetFullFileName(const char* filename)
{
	static char strFullName[MAX_PATH];
	sprintf(strFullName, "%s\\%s", GetRootPath(), filename);
	return strFullName;
}

float CMissileEffect::BaseAndRandom::GetResult()
{
	return fBase+Random()*fRandom;
}
CMissileEffect::Action::Action():
bActive(FALSE),
dwStartTime(0),
dwPeriod(0),
fSpeed(0.0f),
fAcc(0.0f)
{}
CMissileEffect::Bullet::Bullet():
pEffectCtrl(NULL),
nFrameID(0),
nAction(eAction_WaitStart),
fAlpha(0.0f)
{}
CMissileEffect::CMissileEffect():
m_dwStartTime(0),
m_dwLife(0),
m_pMaster(NULL),
m_fScale(1.0f),
m_nNumBullet(0),
m_bIsDead(FALSE)
{
	ZeroMemory( m_abActionActive, sizeof( m_abActionActive ) );
}

void CMissileEffect::Destroy()
{
	for( int nBullet = 0; nBullet < m_nNumBullet; nBullet++ )
	{
		Bullet& bullet = m_bullets[nBullet];
		if( bullet.pEffectCtrl )
		{
			bullet.pEffectCtrl->Destroy();
			delete bullet.pEffectCtrl;
		}
	}
	m_bullets.clear();
}
void CMissileEffect::Release()
{
	Destroy();
	delete this;
}
BOOL CMissileEffect::IsDead( DWORD dwTime )
{
	return m_bIsDead;
}
void CMissileEffect::SetDead()
{
	guardfunc;
	unguard;
}
float CMissileEffect::GetBaseAndRandomResult( BaseAndRandom& bar )
{
	return bar.fBase+Random()*bar.fRandom;
}
void CMissileEffect::GetBaseAndRandom( const char* pszLine, float& fBase, float& fRandom )
{
	char s[1024];
	strcpy( s, pszLine );
	int nLength = strlen( s );
	for( int i = 0; i < nLength; i++ )
	{
		if( s[i] == '(' || s[i] == ')' )
			s[i] = ' ';
	}
	WordParser w;
	if( w.Parse( s ) == 0 )
		return;
	fBase = atof( w.GetWord(1) );
	fRandom = atof( w.GetWord(3) );
}
BOOL CMissileEffect::Compile( const char* pszFilename, BYTE** ppbyBuffer, int* pnBufferSize )
{
// 	CCfgFileLoader l;
// 	CDataChunkWriter w;
// 	if( !l.LoadFromFile( pszFilename  ) )
// 		return FALSE;
// 	if( l.HasKey( "Model" ) )
// 	{
// 		char szModel[MAX_PATH];
// 		strcpy( szModel, l.GetStringValue( "Model" ) );
// 		w.WriteBufferChunk( 'mdl0', szModel, MAX_PATH );
// 	}
// 	if( l.HasKey( "Num" ) )
// 	{
// 		w.WriteIntChunk( 'num0', l.GetIntValue( "Num" ) );
// 	}
// 	if( l.HasKey( "Scale" ) )
// 	{
// 		w.WriteFloatChunk( 'scal', l.GetFloatValue( "Scale" ) );
// 	}
// 
// 	float fBase = 0.0f, fRandom = 0.0f;
// 	if( l.OpenSession( "WaitStart" ) )
// 	{
// 		w.OpenChunk( 'wsta' );
// 		{
// 			if( l.HasKey( "Wait" ) )
// 			{
// 				w.OpenChunk( 'wait' );
// 				{
// 					GetBaseAndRandom( l.GetStringValue( "wait"), fBase, fRandom );
// 					w.WriteFloatChunk( 'base', fBase );
// 					w.WriteFloatChunk( 'rand', fRandom );
// 				}
// 				w.CloseChunk( 'wait' );
// 			}
// 			if( l.HasKey( "period" ) )
// 			{
// 				w.OpenChunk( 'perd' );
// 				{
// 					GetBaseAndRandom( l.GetStringValue( "period" ), fBase, fRandom );
// 					w.WriteFloatChunk( 'base', fBase );
// 					w.WriteFloatChunk( 'rand', fRandom );
// 				}
// 				w.CloseChunk( 'perd' );
// 			}
// 		}
// 		w.CloseChunk( 'wsta' );
// 	}
// 	if( l.OpenSession( "FadeIn" ) )
// 	{
// 		w.OpenChunk( 'fdin' );
// 		{
// 			if( l.HasKey( "period" ) )
// 			{
// 				w.OpenChunk( 'perd' );
// 				{
// 					GetBaseAndRandom( l.GetStringValue( "period" ), fBase, fRandom );
// 					w.WriteFloatChunk( 'base', fBase );
// 					w.WriteFloatChunk( 'rand', fRandom );
// 				}
// 				w.CloseChunk( 'perd' );
// 			}
// 		}
// 		w.CloseChunk( 'fdin' );
// 	}
// 	if( l.OpenSession( "Shoot" ) )
// 	{
// 		w.OpenChunk( 'shot' );
// 		{
// 			if( l.HasKey( "StartSpaceRadius" ) )
// 			{
// 				w.WriteFloatChunk( 'ssrd', l.GetFloatValue( "StartSpaceRadius" ) );
// 			}
// 			if( l.HasKey( "StartSpaceType" ) )
// 			{
// 				const char* pszType = l.GetStringValue( "StartSpaceType" );
// 				if( stricmp( pszType, "Sphere" ) == 0 )
// 					w.WriteIntChunk( 'sstp', eSpace_Sphere );
// 				else if( stricmp( pszType, "PlaneFaceToUp" ) == 0 )
// 					w.WriteIntChunk( 'sstp', eSpace_PlaneFaceToUp );
// 				else if( stricmp( pszType, "PlaneFaceToPoint" ) == 0 )
// 					w.WriteIntChunk( 'sstp', eSpace_PlaneFaceToPoint );
// 				else if( stricmp( pszType, "Line" ) == 0 )
// 					w.WriteIntChunk( 'sstp', eSpace_Line );
// 			}
// 			if( l.HasKey( "TargetSpaceRadius" ) )
// 			{
// 				w.WriteFloatChunk( 'tsrd', l.GetFloatValue( "TargetSpaceRadius" ) );
// 			}
// 			if( l.HasKey( "TargetSpaceType" ) )
// 			{
// 				const char* pszType = l.GetStringValue( "TargetSpaceType" );
// 				if( stricmp( pszType, "Sphere" ) == 0 )
// 					w.WriteIntChunk( 'tstp', eSpace_Sphere );
// 				else if( stricmp( pszType, "PlaneFaceToUp" ) == 0 )
// 					w.WriteIntChunk( 'tstp', eSpace_PlaneFaceToUp );
// 				else if( stricmp( pszType, "PlaneFaceToPoint" ) == 0 )
// 					w.WriteIntChunk( 'tstp', eSpace_PlaneFaceToPoint );
// 				else if( stricmp( pszType, "Line" ) == 0 )
// 					w.WriteIntChunk( 'tstp', eSpace_Line );
// 			}
// 			if( l.HasKey( "period" ) )
// 			{
// 				w.OpenChunk( 'perd' );
// 				{
// 					GetBaseAndRandom( l.GetStringValue( "period" ), fBase, fRandom );
// 					w.WriteFloatChunk( 'base', fBase );
// 					w.WriteFloatChunk( 'rand', fRandom );
// 				}
// 				w.CloseChunk( 'perd' );
// 			}
// 			if( l.HasKey( "Speed" ) )
// 			{
// 				w.OpenChunk( 'sped' );
// 				{
// 					GetBaseAndRandom( l.GetStringValue( "Speed" ), fBase, fRandom );
// 					w.WriteFloatChunk( 'base', fBase );
// 					w.WriteFloatChunk( 'rand', fRandom );
// 				}
// 				w.CloseChunk( 'sped' );
// 			}
// 		}
// 		w.CloseChunk( 'shot' );
// 	}
// 	if( l.OpenSession( "Drop" ) )
// 	{
// 		w.OpenChunk( 'drop' );
// 		{
// 			//if( l.HasKey( "StartSpaceRadius" ) )
// 			//{
// 			//	w.WriteFloatChunk( 'ssrd', l.GetFloatValue( "StartSpaceRadius" ) );
// 			//}
// 			//if( l.HasKey( "StartSpaceType" ) )
// 			//{
// 			//	const char* pszType = l.GetStringValue( "StartSpaceType" );
// 			//	if( stricmp( pszType, "Sphere" ) == 0 )
// 			//		w.WriteIntChunk( 'sstp', eSpace_Sphere );
// 			//	else if( stricmp( pszType, "PlaneFaceToUp" ) == 0 )
// 			//		w.WriteIntChunk( 'sstp', eSpace_PlaneFaceToUp );
// 			//	else if( stricmp( pszType, "PlaneFaceToPoint" ) == 0 )
// 			//		w.WriteIntChunk( 'sstp', eSpace_PlaneFaceToPoint );
// 			//	else if( stricmp( pszType, "Line" ) == 0 )
// 			//		w.WriteIntChunk( 'sstp', eSpace_Line );
// 			//}
// 			if( l.HasKey( "TargetSpaceRadius" ) )
// 			{
// 				w.WriteFloatChunk( 'tsrd', l.GetFloatValue( "TargetSpaceRadius" ) );
// 			}
// 			if( l.HasKey( "TargetSpaceType" ) )
// 			{
// 				const char* pszType = l.GetStringValue( "TargetSpaceType" );
// 				if( stricmp( pszType, "Sphere" ) == 0 )
// 					w.WriteIntChunk( 'tstp', eSpace_Sphere );
// 				else if( stricmp( pszType, "PlaneFaceToUp" ) == 0 )
// 					w.WriteIntChunk( 'tstp', eSpace_PlaneFaceToUp );
// 				else if( stricmp( pszType, "PlaneFaceToPoint" ) == 0 )
// 					w.WriteIntChunk( 'tstp', eSpace_PlaneFaceToPoint );
// 				else if( stricmp( pszType, "Line" ) == 0 )
// 					w.WriteIntChunk( 'tstp', eSpace_Line );
// 			}
// 			if( l.HasKey( "period" ) )
// 			{
// 				w.OpenChunk( 'perd' );
// 				{
// 					GetBaseAndRandom( l.GetStringValue( "period" ), fBase, fRandom );
// 					w.WriteFloatChunk( 'base', fBase );
// 					w.WriteFloatChunk( 'rand', fRandom );
// 				}
// 				w.CloseChunk( 'perd' );
// 			}
// 			if( l.HasKey( "Speed" ) )
// 			{
// 				w.OpenChunk( 'sped' );
// 				{
// 					GetBaseAndRandom( l.GetStringValue( "Speed" ), fBase, fRandom );
// 					w.WriteFloatChunk( 'base', fBase );
// 					w.WriteFloatChunk( 'rand', fRandom );
// 				}
// 				w.CloseChunk( 'sped' );
// 			}
// 			if( l.HasKey( "Height" ) )
// 			{
// 				w.OpenChunk( 'heig' );
// 				{
// 					GetBaseAndRandom( l.GetStringValue( "Height" ), fBase, fRandom );
// 					w.WriteFloatChunk( 'base', fBase );
// 					w.WriteFloatChunk( 'rand', fRandom );
// 				}
// 				w.CloseChunk( 'heig' );
// 			}
// 		}
// 		w.CloseChunk( 'drop' );
// 	}
// 	if( l.OpenSession( "Hit" ) )
// 	{
// 		w.OpenChunk( 'Hit0' );
// 		{
// 			if( l.HasKey( "HitFlash" ) )
// 			{
// 				char szModel[MAX_PATH] = "";
// 				strcpy( szModel, l.GetStringValue( "HitFlash" ) );
// 				w.WriteBufferChunk( 'hitf', szModel, MAX_PATH );
// 			}
// 		}
// 		w.CloseChunk( 'Hit0' );
// 	}
// 	if( l.OpenSession( "FadeOut" ) )
// 	{
// 		w.OpenChunk( 'fdot' );
// 		{
// 			if( l.HasKey( "period" ) )
// 			{
// 				w.OpenChunk( 'perd' );
// 				{
// 					GetBaseAndRandom( l.GetStringValue( "period" ), fBase, fRandom );
// 					w.WriteFloatChunk( 'base', fBase );
// 					w.WriteFloatChunk( 'rand', fRandom );
// 				}
// 				w.CloseChunk( 'perd' );
// 			}
// 		}
// 		w.CloseChunk( 'fdot' );
// 	}
// 	int nUsed = w.GetUsedSize();
// 	BYTE* pbyBuffer = MeDefaultNew BYTE[nUsed];
// 	memcpy( pbyBuffer, w.GetBuffer(), nUsed  );
// 	if( ppbyBuffer )
// 		*ppbyBuffer = pbyBuffer;
// 	if( pnBufferSize )
// 		*pnBufferSize = nUsed;
// 	w.Destroy();
	return TRUE;
}
BOOL CMissileEffect::LoadSetting( const char* pszFilename )
{
	BYTE* pbyBuffer = NULL;
	int nBufferSize = 0;
	if( !Compile( pszFilename, &pbyBuffer, &nBufferSize ) )
		return FALSE;
	LoadFromMemory( pbyBuffer, nBufferSize );
	delete[] pbyBuffer;

	return TRUE;
}
BOOL CMissileEffect::LoadFromMemory( BYTE* pbyBuffer, int nBufferSize )
{
	float fScale = GetMe3dConfig()->m_fMdlSpaceScale;

	CDataChunkLoader l(pbyBuffer,nBufferSize);
	while( !l.IsEndOfMemory() )
	{
		if( l.IsChunk( 'mdl0' ) )
		{
			l.OpenChunk();
			l.ReadToBuffer( (BYTE*)m_szModel, MAX_PATH );
			l.CloseChunk();
		}
		else if( l.TryReadIntChunk( 'num0', m_nNumBullet ) ){}
		else if( l.TryReadFloatChunk( 'scal', m_fScale ) ){}
		else if( l.IsChunk( 'wsta' ) )
		{
			m_abActionActive[eAction_WaitStart] = TRUE;

			l.OpenChunk();
			while( !l.IsEndOfChunk()  )
			{
				if( l.IsChunk( 'wait' ) )
				{
					l.OpenChunk();
					l.TryReadFloatChunk( 'base', m_params.WaitStart_Wait.fBase );
					l.TryReadFloatChunk( 'rand', m_params.WaitStart_Wait.fRandom );
					l.CloseChunk();
					
				}
				else if( l.IsChunk( 'perd' ) )
				{
					l.OpenChunk();
					l.TryReadFloatChunk( 'base', m_params.WaitStart_Period.fBase );
					l.TryReadFloatChunk( 'rand', m_params.WaitStart_Period.fRandom );
					l.CloseChunk();
				}
				else l.SkipChunk();
			}
			l.CloseChunk();
		}
		else if( l.IsChunk( 'fdin' ) )
		{
			m_abActionActive[eAction_FadeIn] = TRUE;
			l.OpenChunk();
			while( !l.IsEndOfChunk() )
			{
				if( l.IsChunk( 'perd' ) )
				{
					l.OpenChunk();
					l.TryReadFloatChunk( 'base', m_params.FadeIn_Period.fBase );
					l.TryReadFloatChunk( 'rand', m_params.FadeIn_Period.fRandom );
					l.CloseChunk();
				}
				else l.SkipChunk();
			}
			l.CloseChunk();
		}
		else if( l.IsChunk( 'shot' ) )
		{
			m_abActionActive[eAction_Shoot] = TRUE;
			l.OpenChunk();
			while( !l.IsEndOfChunk() )
			{
				if( l.TryReadFloatChunk( 'ssrd', m_ShootStartSpace.fRadius ) ){}
				else if( l.TryReadIntChunk( 'sstp', m_ShootStartSpace.nType ) ){}
				else if( l.TryReadFloatChunk( 'tsrd', m_ShootTargetSpace.fRadius ) ){}
				else if( l.TryReadIntChunk( 'tstp', m_ShootTargetSpace.nType ) ){}
				else if( l.IsChunk( 'perd' ) )
				{
					l.OpenChunk();
					l.TryReadFloatChunk( 'base', m_params.Shoot_Period.fBase );
					l.TryReadFloatChunk( 'rand', m_params.Shoot_Period.fRandom );
					l.CloseChunk();
				}
				else if( l.IsChunk( 'sped' ) )
				{
					l.OpenChunk();
					l.TryReadFloatChunk( 'base', m_params.Shoot_Speed.fBase );
					l.TryReadFloatChunk( 'rand', m_params.Shoot_Speed.fRandom );
					l.CloseChunk();
				}
				else l.SkipChunk();
			}
			l.CloseChunk();

			m_ShootStartSpace.fRadius *= fScale;
			m_ShootTargetSpace.fRadius *= fScale;
			m_DropStartSpace.fRadius *= fScale;
			m_DropTargetSpace.fRadius *= fScale;

			m_params.Shoot_Speed.fBase *= fScale;
			m_params.Shoot_Speed.fRandom *= fScale;
		}
		else if( l.IsChunk( 'drop' ) )
		{
			m_abActionActive[eAction_Drop] = TRUE;
			l.OpenChunk();
			while( !l.IsEndOfChunk() )
			{
				//if( l.TryReadFloatChunk( 'ssrd', m_DropStartSpace.fRadius ) ){}
				//else if( l.TryReadIntChunk( 'sstp', m_DropStartSpace.nType ) ){}
				if( l.TryReadFloatChunk( 'tsrd', m_DropTargetSpace.fRadius ) ){}
				else if( l.TryReadIntChunk( 'tstp', m_DropTargetSpace.nType ) ){}
				else if( l.IsChunk( 'perd' ) )
				{
					l.OpenChunk();
					l.TryReadFloatChunk( 'base', m_params.Drop_Period.fBase );
					l.TryReadFloatChunk( 'rand', m_params.Drop_Period.fRandom );
					l.CloseChunk();
				}
				else if( l.IsChunk( 'sped' ) )
				{
					l.OpenChunk();
					l.TryReadFloatChunk( 'base', m_params.Drop_Speed.fBase );
					l.TryReadFloatChunk( 'rand', m_params.Drop_Speed.fRandom );
					l.CloseChunk();
				}
				else if( l.IsChunk( 'heig' ) )
				{
					l.OpenChunk();
					l.TryReadFloatChunk( 'base', m_params.Drop_Height.fBase );
					l.TryReadFloatChunk( 'rand', m_params.Drop_Height.fRandom );
					l.CloseChunk();
				}
				else l.SkipChunk();
			}
			l.CloseChunk();

			m_DropTargetSpace.fRadius *= fScale;
			m_params.Drop_Speed.fBase *= fScale;
			m_params.Drop_Speed.fRandom *= fScale;
			m_params.Drop_Height.fBase *= fScale;
			m_params.Drop_Height.fRandom *= fScale;
		}
		else if( l.IsChunk( 'Hit0' ) )
		{
			m_abActionActive[eAction_Hit] = TRUE;
			l.OpenChunk();
			while( !l.IsEndOfChunk() )
			{
				if( l.IsChunk( 'hitf' ) )
				{
					l.OpenChunk();
					l.ReadToBuffer( (BYTE*)m_szHitEffect, MAX_PATH );
					l.CloseChunk();
				}
				else l.SkipChunk();
			}
			l.CloseChunk();
		}
		else if( l.IsChunk( 'fdot' ) )
		{
			m_abActionActive[eAction_FadeOut] = TRUE;
			l.OpenChunk();
			while( !l.IsEndOfChunk() )
			{
				if( l.IsChunk( 'perd' ) )
				{
					l.OpenChunk();
					l.TryReadFloatChunk( 'base', m_params.FadeOut_Period.fBase );
					l.TryReadFloatChunk( 'rand', m_params.FadeOut_Period.fRandom );
					l.CloseChunk();
				}
				else l.SkipChunk();
			}
			l.CloseChunk();
		}
		else l.SkipChunk();
	}
	return TRUE;
}
void CMissileEffect::Start()
{
	m_dwStartTime = HQ_TimeGetTime();

	m_bullets.reserve( m_nNumBullet );
	m_bullets.resize( m_nNumBullet );


	float fScale = GetMe3dConfig()->m_fMdlSpaceScale*m_fScale;
	
	//m_ShootStartSpace.fRadius *= fScale;
	//m_DropTargetSpace.fRadius *= fScale;

	

	//m_DropTargetSpace.vCenter = m_ShootTargetSpace.vCenter;
	int nModelId = GetMexResMgr()->AddExternalFile( m_szModel );
	//GetMexResMgr()->CreateModel( nModelId );

	if( nModelId == -1 )
	{
		assert( false && "GetMexResMgr()->AddExternalFile() Error" );
		return;
	}

	for( int nBullet = 0; nBullet < m_nNumBullet; nBullet++ )
	{
		Bullet& bullet = m_bullets[nBullet];
		bullet.pEffectCtrl = MeNew CMexEffectCtrl;
		
		bullet.pEffectCtrl->ChangeModel( nModelId );


		Action* pAction = NULL;
		
		DWORD dwTime = 0;

		if( m_abActionActive[eAction_Shoot] )
		{
			switch( m_ShootStartSpace.nType )
			{
			case eSpace_Sphere:
				bullet.vShootStartPos = m_ShootStartSpace.vCenter+*(D3DXVECTOR3*)&RandomDirection()*m_ShootStartSpace.fRadius;
				break;
			}
			switch( m_ShootTargetSpace.nType )
			{
			case eSpace_Sphere:
				bullet.vShootEndPos = m_ShootTargetSpace.vCenter+*(D3DXVECTOR3*)&RandomDirection()*m_ShootTargetSpace.fRadius;
			}
			bullet.vShootDir = bullet.vShootEndPos-bullet.vShootStartPos;
			bullet.fShootDistance = D3DXVec3Length( &bullet.vShootDir );
			D3DXVec3Normalize( &bullet.vShootDir, &bullet.vShootDir );
		}
		if( m_abActionActive[eAction_Drop] )
		{
			switch( m_DropTargetSpace.nType )
			{
			case eSpace_Sphere:
				bullet.vDropEndPos = m_DropTargetSpace.vCenter+*(D3DXVECTOR3*)&RandomDirection()*m_DropTargetSpace.fRadius;
			case eSpace_PlaneFaceToUp:
				{
					D3DXVECTOR3 v( -0.5f+Random(), -0.5f+Random(), 0 );
					D3DXVec3Normalize( &v, &v );
					bullet.vDropEndPos = m_DropTargetSpace.vCenter+*(D3DXVECTOR3*)&v*m_DropTargetSpace.fRadius;
				}
				break;
			}
			bullet.fDropDistance = m_params.Drop_Height.GetResult();
			bullet.vDropStartPos = bullet.vDropEndPos+D3DXVECTOR3(0,0,1)*bullet.fDropDistance;
		}


		// waitstart
		if( m_abActionActive[eAction_WaitStart] )
		{
			pAction = &bullet.actions[eAction_WaitStart];
			pAction->bActive = TRUE;
			pAction->dwStartTime = m_dwStartTime+m_params.WaitStart_Wait.GetResult();
			pAction->dwPeriod = m_params.WaitStart_Period.GetResult();
			dwTime = pAction->dwStartTime+pAction->dwPeriod;
		}
		// fadein
		if( m_abActionActive[eAction_FadeIn] )
		{
			pAction = &bullet.actions[eAction_FadeIn];
			pAction->bActive = TRUE;
			pAction->dwStartTime = dwTime;
			pAction->dwPeriod = m_params.FadeIn_Period.GetResult();
			dwTime = pAction->dwStartTime+pAction->dwPeriod;
		}
		// shoot
		if( m_abActionActive[eAction_Shoot] )
		{
			pAction = &bullet.actions[eAction_Shoot];
			pAction->bActive = TRUE;
			pAction->dwStartTime = dwTime;
			pAction->dwPeriod = m_params.Shoot_Period.GetResult();
			dwTime = pAction->dwStartTime+pAction->dwPeriod;

			float s = bullet.fShootDistance;
			pAction->fSpeed = m_params.Shoot_Speed.GetResult()/1000.0f;
			pAction->fAcc = 
				(s-pAction->fSpeed*pAction->dwPeriod)/(0.5f*pAction->dwPeriod*pAction->dwPeriod);
		}
		if( m_abActionActive[eAction_Drop] )
		{
			// drop
			pAction = &bullet.actions[eAction_Drop];
			pAction->bActive = TRUE;
			pAction->dwStartTime = dwTime;
			pAction->dwPeriod = m_params.Drop_Period.GetResult();
			dwTime = pAction->dwStartTime+pAction->dwPeriod;

			float s = bullet.fDropDistance;
			pAction->fSpeed = m_params.Drop_Speed.GetResult()/1000.0f;
			pAction->fAcc = 
				(s-pAction->fSpeed*pAction->dwPeriod)/(0.5f*pAction->dwPeriod*pAction->dwPeriod);

		}
		if( m_abActionActive[eAction_Hit] )
		{
			pAction = &bullet.actions[eAction_Hit];
			pAction->bActive = TRUE;
			pAction->dwStartTime = dwTime;
			pAction->dwPeriod = 100;
			dwTime = pAction->dwStartTime+pAction->dwPeriod;
		}
		if( m_abActionActive[eAction_FadeOut] )
		{
			// fadeout
			pAction = &bullet.actions[eAction_FadeOut];
			pAction->bActive = TRUE;
			pAction->dwStartTime = dwTime;
			pAction->dwPeriod = m_params.FadeOut_Period.GetResult();
			dwTime = pAction->dwStartTime+pAction->dwPeriod;
		}
	}

}
void CMissileEffect::Update( DWORD dwTime, D3DXVECTOR3 vPos, float fDistance )
{
	float fScale = GetMe3dConfig()->m_fMdlSpaceScale;
	int nNumDeadBullet = 0;
	for( int nBullet = 0; nBullet < m_nNumBullet; nBullet++ )
	{
		Bullet& bullet = m_bullets[nBullet];
		if( bullet.nAction == eAction_Dead )
		{
			nNumDeadBullet++;
			continue;
		}
		Action& action = bullet.actions[bullet.nAction];

		if( dwTime < action.dwStartTime )
		{
			continue;
		}
		DWORD dwPassed = dwTime-action.dwStartTime;
		if( dwPassed >= action.dwPeriod )
		{
			bullet.nAction++;
			continue;
		}
		if( bullet.nAction == eAction_WaitStart )
		{
			continue;
		}
		if( !action.bActive )
		{
			bullet.nAction++;
			continue;
		}

		if( !bullet.pEffectCtrl )
			continue;

		
		bullet.nFrameID = dwPassed/ONEFRAMEINTERVAL;
		if( bullet.pEffectCtrl->GetFrameCount() == 0 )
			bullet.nFrameID = 0;
		else
			bullet.nFrameID %= bullet.pEffectCtrl->GetFrameCount();

		bullet.pEffectCtrl->SetFrameID( bullet.nFrameID );

		D3DXVECTOR3 vPos(0,0,0);
		D3DXVECTOR3 vDir(0,0,1);
		float fAlpha = 0.0f;
		switch( bullet.nAction )
		{
		case eAction_FadeIn:
			if( m_abActionActive[eAction_Shoot] )
			{
				vPos = bullet.vShootStartPos;
				vDir = bullet.vShootDir;
			}
			else if( m_abActionActive[eAction_Drop] )
			{
				vPos = bullet.vDropStartPos;
				vDir = D3DXVECTOR3(0,0,-1);
			}
			else
			{
				vPos = D3DXVECTOR3(0,0,0);
				vDir = D3DXVECTOR3(0,0,1);
			}
			fAlpha = dwPassed/(float)(action.dwPeriod);
			break;
		case eAction_Shoot:
			{
				DWORD dwFlyTime = dwPassed;
				float dist = action.fSpeed*dwFlyTime+0.5f*action.fAcc*dwFlyTime*dwFlyTime;

				vPos = bullet.vShootStartPos+dist*bullet.vShootDir;
				vDir = bullet.vShootDir;
				fAlpha = 1.0f;
			}
			break;
		case eAction_Drop:
			{
				DWORD dwFlyTime = dwPassed;
				float dist = action.fSpeed*dwFlyTime+0.5f*action.fAcc*dwFlyTime*dwFlyTime;

				
				vDir = D3DXVECTOR3(0,0,-1);
				vPos = bullet.vDropStartPos+dist*vDir;
				fAlpha = 1.0f;
			}
			break;
		case eAction_Hit:
			{
				if( m_abActionActive[eAction_Drop] )
				{
					vPos = bullet.vDropEndPos;
					vDir = D3DXVECTOR3(0,0,-1);
				}
				else if( m_abActionActive[eAction_Shoot] )
				{
					vPos = bullet.vShootEndPos;
					vDir = bullet.vShootDir;
				}
				else
				{
					vPos = D3DXVECTOR3(0,0,0);
					vDir = D3DXVECTOR3(0,0,1);
				}
				fAlpha = 1.0f;
				CHitFlashEffect* pEffect = MeNew CHitFlashEffect;
				if( !pEffect->LoadSetting( GetFullFileName(m_szHitEffect) ) )
				{
					pEffect->Release();
				}
				else
				{
					if( GetEffectMgr()->RegisterEffect( pEffect ) == -1 )
					{
						pEffect->Release();
						pEffect = NULL;
						return;
					}
					pEffect->m_vPos = vPos;
					pEffect->Start();
				}
				bullet.nAction++;
			}
			break;
		case eAction_FadeOut:
			if( m_abActionActive[eAction_Drop] )
			{
				vPos = bullet.vDropEndPos;
				vDir = D3DXVECTOR3(0,0,-1);
			}
			else if( m_abActionActive[eAction_Shoot] )
			{
				vPos = bullet.vShootEndPos;
				vDir = bullet.vShootDir;
			}
			else
			{
				vPos = D3DXVECTOR3(0,0,0);
				vDir = D3DXVECTOR3(0,0,1);
			}
			fAlpha = 1.0f-dwPassed/(float)(action.dwPeriod);
			break;
		}

		bullet.pEffectCtrl->SetPosition( 
			vPos.x, 
			vPos.y, 
			vPos.z );
		bullet.pEffectCtrl->SetRotationZ( 0 );
		bullet.pEffectCtrl->SetScale( m_fScale*GetMe3dConfig()->m_fMdlSpaceScale );
		bullet.fAlpha = fAlpha;

		MeMatrix m;
		bullet.pEffectCtrl->CalcTransformMatrix( &m );
		D3DXMATRIX m2;
		//D3DXVECTOR3 vDir = bullet.vDir;
		//D3DXVec3Normalize( &vDir, &vDir );

		//if( m_abActionActive[eAction_Shoot] )
		BuildMatrixFromVectorToVector( (float*)&vDir, (float*)&D3DXVECTOR3(0,0,1), (float*)&m2 );

		D3DXMatrixMultiply( (D3DXMATRIX*)&m, (D3DXMATRIX*)&m2, (D3DXMATRIX*)&m );
		bullet.pEffectCtrl->UpdateComponents( dwTime, &m );

		//pInstance->pEffectCtrl->Render3( fAlpha );
	}
	if( nNumDeadBullet == m_nNumBullet )
		m_bIsDead = TRUE;
}
//void CMissileEffect::Update( DWORD dwTime )
//{
//	float t = (dwTime-m_dwStartTime)/(float)m_dwLife;
//	if( t >= 1.0f )
//		return;
//	DWORD dwPassed = dwTime-m_dwStartTime;
//	for( int nBullet = 0; nBullet < m_nNumBullet; nBullet++ )
//	{
//		Bullet& bullet = m_bullets[nBullet];
//		switch( bullet.nState )
//		{
//		case eState_WaitStart:
//			break;
//		case eState_FadeIn:
//			break;
//		case eState_Shoot:
//			break;
//		case eState_DropOrRaise:
//			break;
//		case eState_Hit:
//			break;
//		case eState_FadeOut:
//			break;
//		case eState_Dead:
//			break;
//		default:
//		}
//		{
//			if( dwPassed >= bullet.timers[eState_WaitStart].dwStartTime )
//			{
//				
//			}
//		}
//		if( !bullet.pEffectCtrl )
//			continue;
//
//		bullet.nFrameID = dwPassed/ONEFRAMEINTERVAL;
//		if( bullet.pEffectCtrl->GetFrameCount() == 0 )
//			bullet.nFrameID = 0;
//		else
//			bullet.nFrameID %= bullet.pEffectCtrl->GetFrameCount();
//
//		bullet.pEffectCtrl->SetFrameID( bullet.nFrameID );
//
//		if( t < bullet.fShootTime )
//		{
//			bullet.pEffectCtrl->SetPosition( 
//				bullet.vStartPos.x, 
//				bullet.vStartPos.y, 
//				bullet.vStartPos.z );
//			if( bullet.fShootTime == 0.0f )
//				bullet.fAlpha = 1.0f;
//			else
//				bullet.fAlpha = dwPassed/(float)(bullet.dwLife*bullet.fShootTime);
//		}
//		else
//		{
//			DWORD dwShootStartTime = bullet.dwLife*bullet.fShootTime;
//			float s = (dwPassed-dwShootStartTime)/(float)(bullet.dwLife-dwShootStartTime);
//			DWORD dwFlyTime = dwPassed-dwShootStartTime;
//			//D3DXVECTOR3 vPos = bullet.vStartPos+s*(bullet.vEndPos-bullet.vStartPos);
//			float dist = bullet.fSpeed*dwFlyTime+0.5f*bullet.fAcc*dwFlyTime*dwFlyTime;
//			D3DXVECTOR3 vPos = bullet.vStartPos+dist*bullet.vShootDir;
//			bullet.pEffectCtrl->SetPosition( vPos.x, vPos.y, vPos.z );
//			
//			
//			bullet.fAlpha = 1.0f;
//		}
//		bullet.pEffectCtrl->SetRotationZ( 0 );
//		bullet.pEffectCtrl->SetScale( m_fScale );
//
//		MeMatrix m;
//		bullet.pEffectCtrl->CalcTransformMatrix( &m );
//		D3DXMATRIX m2;
//		D3DXVECTOR3 vDir = bullet.vEndPos-bullet.vStartPos;
//		D3DXVec3Normalize( &vDir, &vDir );
//
//		BuildMatrixFromVectorToVector( (float*)&vDir, (float*)&D3DXVECTOR3(0,0,1), (float*)&m2 );
//
//		D3DXMatrixMultiply( (D3DXMATRIX*)&m, (D3DXMATRIX*)&m2, (D3DXMATRIX*)&m );
//		bullet.pEffectCtrl->UpdateComponents( dwTime, &m );
//
//		//pInstance->pEffectCtrl->Render3( fAlpha );
//	}
//}
void CMissileEffect::Render()
{
	guardfunc;
	for( int nBullet = 0; nBullet < m_nNumBullet; nBullet++ )
	{
		Bullet& bullet = m_bullets[nBullet];
		if( bullet.nAction == eAction_WaitStart ||
			bullet.nAction == eAction_Dead )
			continue;
		if( !bullet.pEffectCtrl )
			continue;
		bullet.pEffectCtrl->Render3( bullet.fAlpha );
	}
	unguard;
}

//void CMissileEffect::Cull( D3DXVECTOR3 vPos, float fDistance )
//{
//	guardfunc;
//
//	unguard;
//}