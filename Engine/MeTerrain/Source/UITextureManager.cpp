/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	UITextureManager.cpp
* Create: 	10/15/2006
* Desc:		UI图标管理
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#include "stdafx.h"
#include "UITextureManager.h"
#include "SlkReader.h"
#include "SwGlobal.h"

using namespace std;

/*******************************************************************************/
UITexture::UITexture()
{}

UITexture::~UITexture()
{

	m_screenTex->RemoveAll();
	m_screenTex = NULL;
}

void UITexture::SetScreenRect( short top, short left, short width, short height )
{
	ASSERT_NOTNULL( m_screenTex );

	m_screenTex->RemoveAll();
	m_screenTex->AddNewScreenRect(top, left, width, height, 0, 0);
//	m_screenTex->MarkAsChanged(NiScreenTexture::EVERYTHING_MASK);
}

void UITexture::AddScreenRect( short top, short left, short width, short height )
{
	ASSERT_NOTNULL( m_screenTex );

	m_screenTex->AddNewScreenRect(top, left, width, height, 0, 0);
//	m_screenTex->MarkAsChanged(NiScreenTexture::EVERYTHING_MASK);
}

void UITexture::Render()
{
	ASSERT_NOTNULL( m_screenTex );

	if (m_screenTex != NULL)
	{
		SwGlobal::GetRender()->RenderScreenElement(m_screenTex);
	}
}

void UITexture::Release()
{
	ASSERT_NOTNULL( SwGlobal::GetUITextureManager() );
	if ( SwGlobal::GetUITextureManager() != NULL )
	{
		SwGlobal::GetUITextureManager()->ReleaseTexture( this );
	}
	else
	{
		delete this;
	}
}

/*******************************************************************************/

UITextureManager::UITextureManager()
{
	m_path = "";

	m_maxCache = 30;
	m_textureNum = 0;
}

UITextureManager::~UITextureManager()
{
	Assert( m_textureNum==0 );   // m_textureNum不为0则表示有内存泄漏
}

bool UITextureManager::ReadConfig(const char* filename )
{	
	SlkReader* reader = new SlkReader();

	if( !reader->LoadFromFile( filename ) )
	{
		Trace( "--纹理配置文件[%s]读取失败！！\n", filename );
		return false;
	}

	int nGet = reader->GetFirstRow();
	if ( nGet!=SLK_EOF && reader->GetData("id")->ToInt32()==0 )
	{
		m_path = reader->GetData("file")->ToString();
		reader->GetNextRow();
	}

	while ( nGet!=SLK_EOF )
	{
		m_textureName.insert( make_pair(reader->GetData("id")->ToInt32(),
			reader->GetData("file")->ToString()) );
		nGet = reader->GetNextRow();
	}

	reader->Close();
	return true;
}

bool UITextureManager::Init()
{
	ReadConfig("./data/slkfile/Texture.slk");
	m_bInited =	true;

	return true;
}

void UITextureManager::Destroy()
{
	ClearTextureNameMap();
	ClearUnusedTextureMap();
}

void UITextureManager::	ClearUnusedTextureMap()
{
	TEXTURE_MAP::iterator iter = m_unusedTexture.begin();
	TEXTURE_MAP::iterator end  = m_unusedTexture.end();

	for ( ; iter!=end; iter++)
	{
		delete (iter->second);
		--m_textureNum;
	}

	m_unusedTexture.clear();
}

void UITextureManager::ClearTextureNameMap()
{
	m_textureName.clear();
}

const char* UITextureManager::GetTextureName(DWORD id )
{
	TEXTURE_NAME_MAP::iterator iter = m_textureName.find( id );
	if ( iter!=m_textureName.end() )
	{
		m_filename = m_path;
		m_filename += iter->second.c_str();
		return m_filename.c_str();
	}
	return NULL;
}

UITexture* UITextureManager::GetInUnusedTexture(DWORD id )
{
	TEXTURE_MAP::iterator iter = m_unusedTexture.find( id );
	if ( iter!=m_unusedTexture.end() )
	{
		UITexture* tex = iter->second;

		m_unusedTexture.erase( iter );

		return tex;
	}

	return NULL;
}

UITexture* UITextureManager::GetTexture( DWORD id )
{
	if ( !m_bInited )
	{
		return NULL;
	}

	UITexture* tex = GetInUnusedTexture( id );
	if ( tex != NULL )
	{
		return tex;
	}

	const char* filename = GetTextureName( id );
	if ( NULL != filename )
	{
		tex = new UITexture();

		NiSourceTexturePtr pkSourceTexture = NiSourceTexture::Create( filename );

		if ( pkSourceTexture != NULL )
		{
			tex->m_screenTex = NiMeshScreenElements::Create(pkSourceTexture);
			tex->m_id = id;

			++m_textureNum;
			return tex;
		}
		else
		{
			delete tex;
			return NULL;
		}
	}
	return NULL;
}

void UITextureManager::ReleaseTexture( UITexture* tex )
{
	if ( m_unusedTexture.size() > m_maxCache )
	{
		ClearUnusedTextureMap();
	}

	ASSERT_NOTNULL( tex );
	TEXTURE_MAP::iterator iter = m_unusedTexture.find( tex->m_id );

	if ( iter!=m_unusedTexture.end() )
	{
		--m_textureNum;
		delete tex;
	}
	else 
	{
		m_unusedTexture.insert( std::make_pair( tex->m_id, tex ) );
	}
}

void UITextureManager::SetMaxCache(unsigned int maxCache )
{
	if ( maxCache<1 )
	{
		maxCache = 1;
	}

	m_maxCache = maxCache;

	if ( m_unusedTexture.size() > m_maxCache )
	{
		ClearUnusedTextureMap();
	}
}