#include "Me3d/Model/MexConfig.h"
#include "actionconfig.h"
#include "SlkReader.h"
#include "FuncPerformanceLog.h"
ActionConfig	g_actCfg;
ActionConfig::Keyframe::Keyframe():
dwFrame(0),
nHit(0),
nSrcEffect(-1),
nDstEffect(-1)
{
	guardfunc;
	
	szWavFilename[0] = 0;
	unguard;
}


ActionConfig::Action::Action():
dwId((DWORD)-1),	// 0xffffffff
dwModelId((DWORD)-1),
dwStartFrame((DWORD)-1),
dwEndFrame((DWORD)-1)
{
	guardfunc;
	szIntro[0] = 0;
	szName[0] = 0;
	unguard;
}

ActionConfig::Action::~Action()
{
	guardfunc;
	for( int i = 0; i < vectorKeyframe.size(); i++ )
	{
		delete vectorKeyframe[i];
	}
	unguard;
}

BOOL ActionConfig::Action::DeleteKeyframe( Keyframe* pKeyframe )
{
	guardfunc;
	for( int i = 0; i < vectorKeyframe.size(); i++ )
	{
		if( vectorKeyframe[i] == pKeyframe )
		{
			vectorKeyframe.erase( vectorKeyframe.begin()+i );
			return TRUE;
		}
	}
	return FALSE;
	unguard;

}
ActionConfig::ActionConfig(void)
{
	guardfunc;
	unguard;
}

ActionConfig::~ActionConfig(void)
{
	guardfunc;
	for( int i = 0; i < m_vectorAction.size(); i++ )
	{
		delete m_vectorAction[i];
	}
	for( int i = 0; i < m_vectorModel.size(); i++ )
	{
		delete m_vectorModel[i];
	}
	std::map<DWORD,MexCfg*>::iterator it;
	for( it = m_mapMexCfg.begin(); it != m_mapMexCfg.end(); it++ )
	{
		delete it->second;
	}
	unguard;


}

ActionConfig::Model* ActionConfig::GetModel( DWORD dwModelId )
{
	guardfunc;
	for( int i = 0; i < m_vectorModel.size(); i++ )
	{
		if( m_vectorModel[i]->dwId == dwModelId )
		{
			return m_vectorModel[i];
		}
	}
	return NULL;
	unguard;
}

MexCfg* ActionConfig::CreateMexCfg( DWORD dwModelId )
{
	guardfunc;
	std::map<DWORD,MexCfg*>::iterator it;
	it = m_mapMexCfg.find( dwModelId );

	if( it == m_mapMexCfg.end() )
	{
		Model* model = GetModel( dwModelId );
//		assert( model );
		char s[MAX_PATH];
		sprintf( s, "%s.ani", model->szFilename );
		MexCfg* cfg = new MexCfg;
		BOOL bOK = cfg->LoadFromFile( s );
//		assert( bOK );
		m_mapMexCfg[dwModelId] = cfg;
		return cfg;
	}
	return it->second;
	unguard;
}

BOOL ActionConfig::LoadActionFromSlk( const char* pszFilename )
{
	guardfunc;
	CSlkReader r;
	if( !r.ReadFromFile( (char*)pszFilename ) )
	{
//		assert(false);
		return FALSE;
	}

	int nLine = 2;
	int iRet;
	while( CSlkReader::ret_readover != ( iRet = r.GotoNextLine( nLine++ ) ) )
	{
		if( CSlkReader::ret_nothisline == iRet )
			continue;
		Action* action = new Action;
		ZeroMemory( action, sizeof( Action ) );

		CSlkReader::SField* field;

		field = r.GetFieldOfLine( 1 );
		if( !field )
			continue;
		action->dwId = field->data.iValue;

		field = r.GetFieldOfLine( 2 );
		if( !field )
			continue;
		strcpy( action->szIntro,field->data.szValue );

		field = r.GetFieldOfLine( 3 );
		if( !field )
			continue;
		strcpy( action->szName, field->data.szValue );

		field = r.GetFieldOfLine( 4 );
		if( !field )
			continue;
		action->dwModelId = field->data.iValue;

		m_vectorAction.push_back( action );
	}
	return TRUE;
	unguard;
}
BOOL ActionConfig::LoadModelFromSlk( const char* pszFilename )
{
	guardfunc;
	CSlkReader r;
	if( !r.ReadFromFile( (char*)pszFilename ) )
	{
//		assert(false);
		return FALSE;
	}

	int nLine;
	int iRet;

	nLine = 2;
	while( CSlkReader::ret_readover != ( iRet = r.GotoNextLine( nLine++ ) ) )
	{
		if( CSlkReader::ret_nothisline == iRet )
			continue;
		Model* model = new Model;
		ZeroMemory( model, sizeof( Model ) );

		CSlkReader::SField* field;

		field = r.GetFieldOfLine( 2 );
		if( !field )
		{
			delete model;
			continue;
		}
		model->dwId = field->data.iValue;

		field = r.GetFieldOfLine( 3 );
		if( !field )
		{
			delete model;
			continue;
		}
		strcpy( model->szFilename, field->data.szValue );


		m_vectorModel.push_back( model );
	}
	return TRUE;
	unguard;
}

BOOL ActionConfig::LoadKeyframes( Action* action )
{
	guardfunc;
	MexCfg* cfg = CreateMexCfg( action->dwModelId );
//	assert( cfg );
	MexCfgSequence* seq = cfg->GetSequence( action->szName );
//	assert( seq );

	action->dwStartFrame = seq->m_npStartFrameId.GetNumber();
	action->dwEndFrame = seq->m_npEndFrameId.GetNumber();

	for( int j = 0; j < seq->m_hitpoints.m_vectorHitPoint.size(); j++ )
	{
		MexCfgHitPoint* hpt = seq->m_hitpoints.m_vectorHitPoint[j];
		Keyframe* frame = new Keyframe;
		frame->dwFrame = hpt->m_npFrameId.GetNumber();
		frame->nHit = hpt->m_npHitTarget.GetNumber();
		strcpy( frame->szWavFilename, hpt->m_spWavFilename.GetString() );
		frame->nSrcEffect = hpt->m_npSrcEffect.GetNumber();
		frame->nDstEffect = hpt->m_npDstEffect.GetNumber();
		
		action->vectorKeyframe.push_back( frame );
	}
	return TRUE;
	unguard;
}

BOOL ActionConfig::SaveToFile( const char* pszFilename )
{
	guardfunc;
	FILE* fp = fopen( pszFilename, "wb" );
	if( !fp )
	{
//		assert( false );
		return FALSE;
	}
	int nActionCount = m_vectorAction.size();
	fwrite( &nActionCount, sizeof( int ), 1, fp );
	for( int i = 0; i < g_actCfg.m_vectorAction.size(); i++ )
	{
		Action* action = m_vectorAction[i];
		fwrite( &action->dwId, sizeof( DWORD ), 1, fp );
		fwrite( action->szIntro, sizeof( action->szIntro ), 1, fp );
		fwrite( action->szName, sizeof( action->szName), 1, fp );
		fwrite( &action->dwModelId, sizeof( DWORD ), 1, fp );
		fwrite( &action->dwStartFrame, sizeof( DWORD ), 1, fp );
		fwrite( &action->dwEndFrame, sizeof( DWORD ), 1, fp );
		int nKeyframeCount = action->vectorKeyframe.size();
		fwrite( &nKeyframeCount, sizeof( int ), 1, fp );
		for( int j = 0; j < nKeyframeCount; j++ )
		{
			fwrite( action->vectorKeyframe[j], sizeof( Keyframe ), 1, fp );
		}
		//if( nKeyframeCount > 0 )
		//{
		//	
		//	fwrite( &action->vectorKeyframe[0], sizeof( Keyframe ), nKeyframeCount, fp );
		//}
	}
	fclose( fp );
	return TRUE;
	unguard;
}
BOOL ActionConfig::LoadFromFile( const char* pszFilename )
{
	guardfunc;
	FILE* fp = fopen( pszFilename, "rb" );
	if( !fp )
	{
//		assert( false );
		return FALSE;
	}
	int nActionCount = 0;
	fread( &nActionCount, sizeof( int ), 1, fp );
//	assert( nActionCount > 0 );
	for( int i = 0; i < nActionCount; i++ )
	{
		Action* action = new Action;
		fread( &action->dwId, sizeof( DWORD ), 1, fp );
		fread( action->szIntro, sizeof( action->szIntro ), 1, fp );
		fread( action->szName, sizeof( action->szName), 1, fp );
		fread( &action->dwModelId, sizeof( DWORD ), 1, fp );
		fread( &action->dwStartFrame, sizeof( DWORD ), 1, fp );
		fread( &action->dwEndFrame, sizeof( DWORD ), 1, fp );
		int nKeyframeCount = 0;
		fread( &nKeyframeCount, sizeof( int ), 1, fp );
		for( int i = 0; i < nKeyframeCount; i++ )
		{
			ActionConfig::Keyframe* frame = new ActionConfig::Keyframe;
			fread( frame, sizeof( Keyframe ), 1, fp );
			action->vectorKeyframe.push_back( frame );
		}
		//if( nKeyframeCount > 0 )
		//{
		//	action->vectorKeyframe.reserve( nKeyframeCount );
		//	action->vectorKeyframe.resize( nKeyframeCount );
		//	fread( &action->vectorKeyframe[0], sizeof( Keyframe ), nKeyframeCount, fp );
		//}
		m_vectorAction.push_back( action );
	}

	fclose( fp );
	return TRUE;
	unguard;
}

BOOL ActionConfig::DeleteAction( Action* pAction )
{
	guardfunc;
	for( int i = 0; i < m_vectorAction.size(); i++ )
	{
		if( m_vectorAction[i] == pAction )
		{
			m_vectorAction.erase( m_vectorAction.begin()+i );
			return TRUE;
		}
	}
	return FALSE;
	unguard;

}