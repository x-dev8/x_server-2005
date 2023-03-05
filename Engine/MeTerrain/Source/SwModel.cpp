/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwModel.cpp
* Create: 	10/16/2006
* Desc:		从NIF或KFM加载模型的类，不支持渲染
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#include "stdafx.h"
#include "SwModel.h"

////////////////////////////////////////////////////////////////////////////////
SwModel::SwModel()	  
{
	m_actorMgr		= NULL;
	m_rootNode		= NULL;

	m_cameraList.clear();
}

SwModel::~SwModel()
{
	ASSERT_NULL( m_rootNode );
	ASSERT_NULL( m_actorMgr );
}

bool SwModel::Create( const char* pFileName )
{
	ASSERT_NULL( m_rootNode );
	ASSERT_NULL( m_actorMgr );

	m_rootNode			= NiNew NiSwitchNode();

	if( !LoadByFileName( pFileName ) ) 
	{
		Destroy();
		return false;
	}

	m_rootNode->SetIndex( 0 );
// 	m_rootNode->UpdateOnlyActiveChild( true );

	m_rootNode->Update( 0.0f );
	m_rootNode->UpdateNodeBound();
	m_rootNode->UpdateProperties();
	m_rootNode->UpdateEffects();

	return true;
}

bool SwModel::LoadByFileName( const char* pName )
{
	if ( SwPublicFunc::IsEndof( pName, ".nif" ) )
	{
		return LoadNif( pName );
	}
	else if ( SwPublicFunc::IsEndof( pName, ".kfm" ) )
	{
		return LoadKfm( pName );
	}

	return false;
}

bool SwModel::LoadNif( const char* pName )
{
	NiStream kStream;

	if( !kStream.Load( pName ) )
	{
		return false;
	}

	int objCount = kStream.GetObjectCount();

	NiObject* pkObject = NULL;
	for( int i = 0; i < objCount; i++ )
	{
		pkObject = kStream.GetObjectAt(i);

		if( NiIsKindOf( NiNode, pkObject ) )
		{
			m_rootNode->AttachChild( (NiNode*) pkObject );
		}
		else if( NiIsKindOf( NiCamera, pkObject ) )
		{
			NiCamera* camera = (NiCamera*) pkObject;
			m_cameraList.push_back( camera );
		}
		else
		{
			Trace( "<<<WARNING>>>: unknown node type!" );
		}
	}

	return true;
}

bool SwModel::LoadKfm( const char* pName )
{
	ASSERT_NULL( m_actorMgr );

	m_actorMgr			= NiActorManager::Create( pName );
	if( m_actorMgr == NULL )
	{
		return false;
	}

	NiAVObject* root	= m_actorMgr->GetNIFRoot();
	m_rootNode->AttachChild( root );

	m_actorMgr->SetTargetAnimation( 0 );

	return true;
}

void SwModel::Destroy()
{	
	m_actorMgr		= NULL;
	m_rootNode		= NULL;

	m_cameraList.clear();
}

NiCamera* SwModel::GetCamera( int idx )
{
	if( idx>=0 && idx<(int)m_cameraList.size() )
	{
		return m_cameraList[idx];
	}

	return NULL;
}

void SwModel::Update( float pTime, float pDeltaTime )
{
	ASSERT_NOTNULL( m_rootNode );
	m_rootNode->Update( pTime );

	if ( m_actorMgr != NULL )
	{
		m_actorMgr->Update( pTime );
	}
}

void SwModel::Render( NiCamera* pCamera )
{
}

void SwModel::SetScale( float scale )
{
	if ( m_rootNode )
	{
		m_rootNode->SetScale( scale );
	}
}

