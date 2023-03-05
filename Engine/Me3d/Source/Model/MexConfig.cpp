#include <assert.h>
#include "Me3d/Model/MexConfig.h"
//#include "SlkReader\SlkReader.h"
#include "datachunkwriter.h"
#include "wordparser.h"
#include "FuncPerformanceLog.h"
#include "Me3d/engine/Engine.h"
//
// #include "VirtualFileSystem/vfs.h"
//#include "Cipher/cipher_factory.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "vector"
//#include "Launcher/DataLauncher.h"
#include "../filepacket/packet_interface.h"

//extern bool g_DirectReadInPackage;

// commented out,jiayi, [2009/10/8]
// extern FileIO::CVFS	g_ModelVfs;
// extern FileIO::CVFS	g_WorldVfs;
//
// MexCfgActions::Record* MexCfgActions::FindRecordByName( const char* pszAnimName )
// {
// 	guardfunc;
// 	for( int i = 0; i < m_vectorRecord.size(); i++ )
// 	{
// 		if( stricmp( pszAnimName, m_vectorRecord[i].szName ) == 0 )
// 			return &m_vectorRecord[i];
// 	}
// 	return NULL;
// 	unguard;
// }
// BOOL MexCfgActions::LoadFromSlk( const char* pszFilename )
// {
// 	guardfunc;
// 	CSlkReader r;
// 	if( !r.ReadFromFile( (char*)pszFilename ) )
// 	{
// 		assert(false);
// 		return FALSE;
// 	}
// 
// 	int nLine = 2;
// 	int iRet;
// 
// 	while( CSlkReader::ret_readover != ( iRet = r.GotoNextLine( nLine++ ) ) )
// 	{
// 		if( CSlkReader::ret_nothisline == iRet )
// 			continue;
// 		Record record;
// 		
// 		CSlkReader::SField* field;
// 		
// 		field = r.GetFieldOfLine( 3 );
// 		if( !field || field->iFieldType != CSlkReader::field_string )
// 			continue;
// 		strcpy( record.szTitle, field->data.szValue );
// 		field = r.GetFieldOfLine( 4 );
// 		if( !field || field->iFieldType != CSlkReader::field_string )
// 			continue;
// 		strcpy( record.szName, field->data.szValue );
// 		
// 		assert( !FindRecordByName( record.szName ) &&
// 				"Has same action name" );
// 		
// 		m_vectorRecord.push_back( record );
// 	}
// 	return TRUE;
// 	unguard;
// }

//////////////////////////////////////////////////////////////////////
// BOOL MexCfgModels::LoadFromDirectory( const char* pszDir )
// {
// 	guardfunc;
// 	char szCommand[1024];
// 	char szListFile[256] = "filelist.txt";
// 	sprintf( szCommand, //jiayi [09.2.19]
// 		"dir %s\\*%s /s /b  > %s", 
// 		pszDir, 
// 		".mex",
// 		szListFile );
// 	system( szCommand );
// 
// 	FILE* fp = fopen( szListFile, "r" );
// 	if( fp )
// 	{
// 		// 去掉全局路径名+字符'\\'
// 		int nSkipLength = strlen( pszDir )+1;
// 		char s[MAX_PATH];
// 		int id = 1;
// 		while( fgets( s, 256, fp ) )
// 		{
// 			
// 			int nLength = strlen( s );
// 			if( s[nLength-1] == '\n' )
// 				s[nLength-1] = 0;
// 			Record record;
// 			record.dwId = id++;
// 			strcpy( record.szFilename, &s[nSkipLength] );
// 			m_vectorRecord.push_back( record );
// 		}
// 		fclose( fp );
// 	}		
// 	return TRUE;
// 	unguard;
// }
// BOOL MexCfgModels::LoadFromSlk( const char* pszFilename )
// {
// 	guardfunc;
// 	CSlkReader r;
// 	if( !r.ReadFromFile( (char*)pszFilename ) )
// 	{
// 		assert(false);
// 		return FALSE;
// 	}
// 
// 	int nLine = 2;
// 	int iRet;
// 
// 	while( CSlkReader::ret_readover != ( iRet = r.GotoNextLine( nLine++ ) ) )
// 	{
// 		if( CSlkReader::ret_nothisline == iRet )
// 			continue;
// 		CSlkReader::SField* field;
// 		field = r.GetFieldOfLine( 2 );
// 		if( !field )
// 			continue;
// 		Record record;
// 		record.dwId = field->data.iValue;
// 		field = r.GetFieldOfLine( 3 );
// 		if( !field )
// 			continue;
// 		strcpy( record.szFilename, field->data.szValue );
// 		m_vectorRecord.push_back( record );
// 	}
// 	return TRUE;
// 	unguard;
// }
// BOOL MexCfgModels::CreateTree( HWND hTree )
// {
// 	guardfunc;
// 	TVINSERTSTRUCT	is;
// 	ZeroMemory(&is,sizeof(TVINSERTSTRUCT));
// 	
// 	is.item.mask = TVIF_TEXT | TVIF_PARAM;
// 	is.item.lParam = 0;
// 	is.item.pszText = "ArabianNights Models";
// 	is.hParent = NULL;
// 	
// 	HTREEITEM  hRoot = TreeView_InsertItem(hTree,&is);
// 	HTREEITEM	hparent,hchild = hRoot ;
// 	
// 	for(DWORD j=0;j<m_vectorRecord.size();++j)
// 	{
// 		if( 1 )
// 		{	
// 			char* p = m_vectorRecord[j].szFilename;
// 			char tempstr[MAX_PATH] = {0};
// 			char	str2[MAX_PATH] = {0};
// 			
// 			hparent = hRoot;
// 			
// 			while(*p != 0x00)
// 			{
// 				int n=0;
// 				
// 				while(*p != '\\' && *p != 0x00 ) tempstr[n++] = *p++;
// 				
// 				tempstr[n] = 0x00;
// 				
// 				if(*p == 0x00)
// 					break;
// 				
// 				p++;
// 				
// 				
// 				BOOL found = false;
// 				hchild = TreeView_GetChild(hTree,hparent);
// 				while(hchild && !found)
// 				{
// 					TVITEM item;
// 					str2[0] = 0x00;
// 					
// 					item.mask = TVIF_TEXT;
// 					item.hItem = hchild;
// 					item.pszText = str2;
// 					item.cchTextMax = MAX_PATH;
// 					
// 					TreeView_GetItem(hTree,&item);
// 					
// 					if(!stricmp(tempstr,str2))
// 						found = true;
// 					else
// 						hchild = TreeView_GetNextSibling(hTree,hchild);
// 				}
// 				
// 				if(!found)
// 				{
// 					is.item.lParam = 0;
// 					is.item.pszText = tempstr;
// 					is.hParent = hparent;
// 					
// 					hchild = hparent = TreeView_InsertItem(hTree,&is);
// 				}
// 				
// 				hparent = hchild;
// 			}
// 			
// 			is.item.lParam = j+1;
// 			is.item.pszText = tempstr;
// 			is.hParent = hchild;
// 			
// 			HTREEITEM hItem = TreeView_InsertItem(hTree,&is);
// 		}
// 	}
// 	return TRUE;
// 	unguard;
// }
//////////////////////////////////////////////////////////////////////
BOOL MexCfgHitPoint::CreateTree(	I_MexTreeNode* pParent,
									HWND hTree, HTREEITEM hRoot )
{
	guardfunc;
	TVINSERTSTRUCT tvInsert;
	ZeroMemory(&tvInsert,sizeof(TVINSERTSTRUCT));
	
	tvInsert.hParent = hRoot;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT|TVIF_PARAM;

	tvInsert.item.pszText = LPSTR( GetText() );
	tvInsert.item.lParam = (LPARAM)this;
	HTREEITEM hHitPoint = TreeView_InsertItem(hTree,&tvInsert);
	SetItem( hHitPoint );
	SetParent( pParent );


	tvInsert.hParent = hHitPoint;
	tvInsert.item.pszText = LPSTR( m_npFrameId.GetText() );
	tvInsert.item.lParam = (LPARAM)&m_npFrameId;
	HTREEITEM hFrameId = TreeView_InsertItem(hTree,&tvInsert);
	m_npFrameId.SetItem( hFrameId );
	m_npFrameId.SetParent( this );

	tvInsert.hParent = hHitPoint;
	tvInsert.item.pszText = LPSTR( m_spWavFilename.GetText() );
	tvInsert.item.lParam = (LPARAM)&m_spWavFilename;
	HTREEITEM hWavFilename = TreeView_InsertItem(hTree,&tvInsert);
	m_spWavFilename.SetItem( hWavFilename );
	m_spWavFilename.SetParent( this );

	tvInsert.hParent = hHitPoint;
	tvInsert.item.pszText = LPSTR( m_npHitTarget.GetText() );
	tvInsert.item.lParam = (LPARAM)&m_npHitTarget;
	HTREEITEM hHitTarget = TreeView_InsertItem(hTree,&tvInsert);
	m_npHitTarget.SetItem( hHitTarget );
	m_npHitTarget.SetParent( this );
	
	tvInsert.hParent = hHitPoint;
	tvInsert.item.pszText = LPSTR( m_npSrcEffect.GetText() );
	tvInsert.item.lParam = (LPARAM)&m_npSrcEffect;
	HTREEITEM hSrcEffect = TreeView_InsertItem(hTree,&tvInsert);
	m_npSrcEffect.SetItem( hSrcEffect );
	m_npSrcEffect.SetParent( this );

	tvInsert.hParent = hHitPoint;
	tvInsert.item.pszText = LPSTR( m_npDstEffect.GetText() );
	tvInsert.item.lParam = (LPARAM)&m_npDstEffect;
	HTREEITEM hEffect = TreeView_InsertItem(hTree,&tvInsert);
	m_npDstEffect.SetItem( hEffect );
	m_npDstEffect.SetParent( this );

	return TRUE;
	unguard;
}
BOOL MexCfgHitPoint::Read( UPointer inP, int nSize )
{
	guardfunc;
	UPointer p(inP.p);

	m_npFrameId.SetNumber( *p.i++ );
	m_spWavFilename.SetString( p.c );
	p.c += I_MexTreeNode::eMaxString;
	//p.c += I_MexTreeNode::eMaxString;

	if( p.c < inP.c+nSize )
	{
		m_npHitTarget.SetNumber( *p.i++ );
		m_npSrcEffect.SetNumber( *p.i++ );
		m_npDstEffect.SetNumber( *p.i++ );
	}
	//assert( m_npFrameId.GetNumber() < 1500 );
	return TRUE;
	unguard;
}
BOOL MexCfgHitPoints::Read( UPointer inP, int nSize )
{
	guardfunc;
	UPointer p(inP.p);

	while( p.c < inP.c+nSize )
	{
		switch( DC_TAG( *p.dw ) )
		{
		case 'htpt':
			{
				p.dw++;
				int size = *p.i++;
				MexCfgHitPoint* hpt = MeNew MexCfgHitPoint;
				hpt->Read( p, size );
				m_vectorHitPoint.push_back( hpt );
				p.c += size; 
			}
			break;
		default:
			assert( false );
		}
	}
	return TRUE;
	unguard;
}
BOOL MexCfgHitPoints::Read_Old( UPointer inP, int nSize )
{
	guardfunc;
	UPointer p(inP.p);

	while( p.c < inP.c+nSize )
	{
		switch( DC_TAG( *p.dw ) )
		{
		case 'hitp':
			{
				p.dw++;
				int size = *p.i++;
				MexCfgHitPoint* hpt = MeNew MexCfgHitPoint;
				hpt->Read( p, size );
				m_vectorHitPoint.push_back( hpt );
				p.c += size; 
			}
			break;
		default:
			assert( false );
		}
	}
	return TRUE;
	unguard;
}
BOOL MexCfgHitPoints::CreateTree(	I_MexTreeNode* pParent,
									HWND hTree, HTREEITEM hRoot )
{
	guardfunc;
	TVINSERTSTRUCT tvInsert;
	ZeroMemory(&tvInsert,sizeof(TVINSERTSTRUCT));

	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT|TVIF_PARAM;
	tvInsert.hParent = hRoot;
	tvInsert.item.pszText = LPSTR("HitPoints");
	tvInsert.item.lParam = (LPARAM)this;
	HTREEITEM hHitPoints = TreeView_InsertItem(hTree,&tvInsert);
	SetParent( pParent );
	SetItem( hHitPoints );
	for( int i = 0; i < m_vectorHitPoint.size(); i++ )
		m_vectorHitPoint[i]->CreateTree( this, hTree, hHitPoints );
	return TRUE;
	unguard;
}

int	MexCfgSequence::BlendFrame( float t )
{
	if( t < 0 )
		t = 0;
	if( t > 1 )
		t = 1;
	int nFrame = m_npStartFrameId.GetNumber()+t*(m_npEndFrameId.GetNumber()-m_npStartFrameId.GetNumber());
	return nFrame;
}

float MexCfgSequence::GetBlendFrame( float t )
{
	if( t < 0 )
		t = 0;
	if( t > 1 )
	{
		t = 1;
	}
	float fFrame = (float)m_npStartFrameId.GetNumber()*ONEFRAMEINTERVAL + t*(float)(m_npEndFrameId.GetNumber()-m_npStartFrameId.GetNumber())*ONEFRAMEINTERVAL + 0.005f;
	return fFrame;
}

BOOL MexCfgSequence::CreateTree(	I_MexTreeNode* pParent,  
									HWND hTree, HTREEITEM hRoot )
{
	guardfunc;
	TVINSERTSTRUCT tvInsert;
	ZeroMemory(&tvInsert,sizeof(TVINSERTSTRUCT));
	
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT|TVIF_PARAM;
	
	tvInsert.hParent = hRoot;
	tvInsert.item.pszText = LPSTR( GetText() );
	tvInsert.item.lParam = (LPARAM)this;
	HTREEITEM hSequence = TreeView_InsertItem(hTree,&tvInsert);
	SetItem( hSequence );
	SetParent( pParent );

	
	tvInsert.hParent = hSequence;
	tvInsert.item.pszText = LPSTR( m_spAnimName.GetText() );
	tvInsert.item.lParam = (LPARAM)&m_spAnimName;
	HTREEITEM hAnimName = TreeView_InsertItem(hTree,&tvInsert);
	m_spAnimName.SetParent( this );
	m_spAnimName.SetItem( hAnimName );
	

	tvInsert.hParent = hSequence;
	tvInsert.item.pszText = LPSTR( m_npStartFrameId.GetText() );
	tvInsert.item.lParam = (LPARAM)&m_npStartFrameId;
	HTREEITEM hStartFrameIdId = TreeView_InsertItem(hTree,&tvInsert);
	m_npStartFrameId.SetParent( this );
	m_npStartFrameId.SetItem( hStartFrameIdId );

	tvInsert.hParent = hSequence;
	tvInsert.item.pszText = LPSTR( m_npEndFrameId.GetText() );
	tvInsert.item.lParam = (LPARAM)&m_npEndFrameId;
	HTREEITEM hEndFrameIdId = TreeView_InsertItem(hTree,&tvInsert);
	m_npEndFrameId.SetParent( this );
	m_npEndFrameId.SetItem( hEndFrameIdId );
	
	m_hitpoints.CreateTree( this, hTree, hSequence );

	tvInsert.hParent = hSequence;
	tvInsert.item.pszText = LPSTR( m_npRealHitPoint.GetText() );
	tvInsert.item.lParam = (LPARAM)&m_npRealHitPoint;
	HTREEITEM hAttack = TreeView_InsertItem(hTree,&tvInsert);
	m_npRealHitPoint.SetParent( this );
	m_npRealHitPoint.SetItem( hAttack );


	tvInsert.hParent = hSequence;
	tvInsert.item.pszText = LPSTR( m_npHasLightTrack.GetText() );
	tvInsert.item.lParam = (LPARAM)&m_npHasLightTrack;
	HTREEITEM hLightTrack = TreeView_InsertItem(hTree,&tvInsert);
	m_npHasLightTrack.SetParent( this );
	m_npHasLightTrack.SetItem( hLightTrack );
	
	return TRUE;
	unguard;
}

BOOL MexCfgSequence::Read_Old( UPointer inP, int nSize )
{
	guardfunc;
	UPointer p(inP.p);

	char* pName = p.c;
	m_spAnimName.SetString( pName );
	p.c += I_MexTreeNode::eMaxString;
	m_npStartFrameId.SetNumber( *p.dw++ );
	m_npEndFrameId.SetNumber( *p.dw++ );

	assert( m_npEndFrameId.GetNumber() >= m_npStartFrameId.GetNumber() );

	while( p.c < inP.c+nSize )
	{
		switch( DC_TAG( *p.dw ) )
		{
		case 'hpts':
			{
				p.dw++;
				int size = *p.i++;
				m_hitpoints.Read_Old( p, size );
				p.c += size; 
			}
			break;

		case 'rhpt':
			{
				p.dw++;
				int size = *p.i++;
				m_npRealHitPoint.SetNumber( *p.i );
				p.c += size; 
			}
			break;
		case 'ltrk':
			{
				p.dw++;
				int size = *p.i++;
				m_npHasLightTrack.SetNumber( *p.i );
				p.c += size;
			}
			break;
		default:
			assert( false );
		}
	}
	return TRUE;
	unguard;
}

BOOL MexCfgSequence::Read( UPointer inP, int nSize )
{
	guardfunc;
	UPointer p(inP.p);

	char* pName = p.c;
	m_spAnimName.SetString( pName );
	p.c += I_MexTreeNode::eMaxString;
	m_npStartFrameId.SetNumber( *p.dw++ );
	m_npEndFrameId.SetNumber( *p.dw++ );

	assert( m_npEndFrameId.GetNumber() >= m_npStartFrameId.GetNumber() );
	
	while( p.c < inP.c+nSize )
	{
		switch( DC_TAG( *p.dw ) )
		{
		case 'htps':
			{
				p.dw++;
				int size = *p.i++;
				m_hitpoints.Read( p, size );
				p.c += size; 
			}
			break;

		case 'rlht':
			{
				p.dw++;
				int size = *p.i++;
				m_npRealHitPoint.SetNumber( *p.i );
				p.c += size; 
			}
			break;
		case 'lttk':
			{
				p.dw++;
				int size = *p.i++;
				m_npHasLightTrack.SetNumber( *p.i );
				p.c += size;
			}
			break;
		default:
			assert( false );
		}
	}
	return TRUE;
	unguard;
}

BOOL MexCfgSequences::CreateTree(	I_MexTreeNode* pParent, 
									HWND hTree, HTREEITEM hRoot )
{
	guardfunc;
	TVINSERTSTRUCT tvInsert;
	ZeroMemory(&tvInsert,sizeof(TVINSERTSTRUCT));
	
	tvInsert.hParent = hRoot;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT|TVIF_PARAM;
	tvInsert.item.pszText = LPSTR(GetText());
	tvInsert.item.lParam = (LPARAM)this;
	HTREEITEM hChild = TreeView_InsertItem(hTree,&tvInsert);
	SetItem( hChild );
	SetParent( pParent );

	for( int i = 0; i < m_vectorSequence.size(); i++ )
		m_vectorSequence[i]->CreateTree( this, hTree, hChild );
	m_hRootItem = hChild;
	return TRUE;
	unguard;
}

BOOL MexCfgSequences::Read_Old( UPointer inP, int nSize )
{
	guardfunc;
	UPointer p(inP.p);
	while( p.c < inP.c+nSize )
	{
		switch( DC_TAG( *p.dw ) )
		{
		case 'sequ':
			{
				p.dw++;
				int size = *p.i++;
				MexCfgSequence* sequence = MeNew MexCfgSequence;
				sequence->Read_Old( p, size );
				m_vectorSequence.push_back( sequence );
				p.c += size; 
			}
			break;
		default:
			assert( false );
		}
	}
	return TRUE;
	unguard;
}

BOOL MexCfgSequences::Read( UPointer inP, int nSize )
{
	guardfunc;
	UPointer p(inP.p);
	while( p.c < inP.c+nSize )
	{
		switch( DC_TAG( *p.dw ) )
		{
		case 'sqce':
			{
				p.dw++;
				int size = *p.i++;
				MexCfgSequence* sequence = MeNew MexCfgSequence;
				sequence->Read( p, size );
				m_vectorSequence.push_back( sequence );
				p.c += size; 
			}
			break;
		default:
			assert( false );
		}
	}
	return TRUE;
	unguard;
}

BOOL MexCfgModelScale::Read( UPointer inP, int nSize )
{
	guardfunc;
	UPointer p(inP.p);
	m_npScale.SetNumber( *p.i++ );
	return TRUE;
	unguard;
}
BOOL MexCfgBodyRadius::CreateTree( I_MexTreeNode* pParent, HWND hTree, HTREEITEM hRoot )
{
	guardfunc;
	TVINSERTSTRUCT tvInsert;
	ZeroMemory(&tvInsert,sizeof(TVINSERTSTRUCT));

	tvInsert.hParent = hRoot;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT|TVIF_PARAM;
	tvInsert.item.pszText = LPSTR(GetText());
	tvInsert.item.lParam = (LPARAM)this;
	HTREEITEM hChild = TreeView_InsertItem(hTree,&tvInsert);
	SetItem( hChild );
	SetParent( pParent );
	return TRUE;
	unguard;
}
BOOL MexCfgModelScale::CreateTree( I_MexTreeNode* pParent, 
									HWND hTree, 
									HTREEITEM hRoot )
{
	guardfunc;
	TVINSERTSTRUCT tvInsert;
	ZeroMemory(&tvInsert,sizeof(TVINSERTSTRUCT));

	tvInsert.hParent = hRoot;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT|TVIF_PARAM;
	tvInsert.item.pszText = LPSTR(GetText());
	tvInsert.item.lParam = (LPARAM)this;
	HTREEITEM hChild = TreeView_InsertItem(hTree,&tvInsert);
	SetItem( hChild );
	SetParent( pParent );
	return TRUE;
	unguard;
}

BOOL MexCfgModelBoundingObject::Read( UPointer inP, int nSize )
{
	guardfunc;
	UPointer p(inP.p);
	m_npBBoxWidth.SetNumber( *p.i++ );
	m_npBBoxLength.SetNumber( *p.i++ );
	m_npBBoxHeight.SetNumber( *p.i++ );
	m_npBBoxLift.SetNumber( *p.i++ );
	return TRUE;
	unguard;
}
BOOL MexCfgModelBoundingObject::CreateTree( I_MexTreeNode* pParent, 
											HWND hTree, 
											HTREEITEM hRoot )
{
	guardfunc;
	TVINSERTSTRUCT tvInsert;
	ZeroMemory(&tvInsert,sizeof(TVINSERTSTRUCT));

	tvInsert.hParent = hRoot;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT|TVIF_PARAM;

	tvInsert.item.pszText = LPSTR( GetText() );
	tvInsert.item.lParam = (LPARAM)this;
	HTREEITEM hBoundingObject = TreeView_InsertItem(hTree,&tvInsert);
	SetItem( hBoundingObject );
	SetParent( pParent );


	tvInsert.hParent = hBoundingObject;
	tvInsert.item.pszText = LPSTR( m_npBBoxWidth.GetText() );
	tvInsert.item.lParam = (LPARAM)&m_npBBoxWidth;
	HTREEITEM hBBoxWidth = TreeView_InsertItem(hTree,&tvInsert);
	m_npBBoxWidth.SetItem( hBBoxWidth );
	m_npBBoxWidth.SetParent( this );

	tvInsert.hParent = hBoundingObject;
	tvInsert.item.pszText = LPSTR( m_npBBoxLength.GetText() );
	tvInsert.item.lParam = (LPARAM)&m_npBBoxLength;
	HTREEITEM hBBoxLength = TreeView_InsertItem(hTree,&tvInsert);
	m_npBBoxLength.SetItem( hBBoxLength );
	m_npBBoxLength.SetParent( this );

	tvInsert.hParent = hBoundingObject;
	tvInsert.item.pszText = LPSTR( m_npBBoxHeight.GetText() );
	tvInsert.item.lParam = (LPARAM)&m_npBBoxHeight;
	HTREEITEM hBBoxHeight = TreeView_InsertItem(hTree,&tvInsert);
	m_npBBoxHeight.SetItem( hBBoxHeight );
	m_npBBoxHeight.SetParent( this );

	tvInsert.hParent = hBoundingObject;
	tvInsert.item.pszText = LPSTR( m_npBBoxLift.GetText() );
	tvInsert.item.lParam = (LPARAM)&m_npBBoxLift;
	HTREEITEM hBBoxLift = TreeView_InsertItem(hTree,&tvInsert);
	m_npBBoxLift.SetItem( hBBoxLift );
	m_npBBoxLift.SetParent( this );
	return TRUE;
	unguard;
}
BOOL MexCfgAvatarSetting::Read( UPointer inP, int nSize )
{
	guardfunc;
	UPointer p(inP.p);


	m_spName.SetString( p.c );
	p.c += I_MexTreeNode::eMaxString;
	
	int nSubsetCount = *p.i++;
	if( nSubsetCount > 0 )
	{
		m_vectorSubsetFlag.reserve( nSubsetCount );
		m_vectorSubsetFlag.resize( nSubsetCount );

		memcpy( &m_vectorSubsetFlag[0], p.dw, sizeof(DWORD)*nSubsetCount );
		p.dw += nSubsetCount;
	}
	int nReplaceableTextureCount = *p.i++;
	if( nReplaceableTextureCount > 0 )
	{
		m_vectorReplaceableTexture.reserve( nReplaceableTextureCount );
		m_vectorReplaceableTexture.resize( nReplaceableTextureCount );
		for( int nTexture  = 0; nTexture < nReplaceableTextureCount; nTexture++ )
		{
			memcpy( m_vectorReplaceableTexture[nTexture].szFileName, p.c, MAX_PATH );
			p.c += MAX_PATH;
		}
	}


	return TRUE;
	unguard;
}
MexCfgAvatarSetting::MexCfgAvatarSetting():
m_bTextureLoaded(FALSE)
{
	guardfunc;
	unguard;
}
BOOL MexCfgAvatarSetting::CreateTree( I_MexTreeNode* pParent, HWND hTree, HTREEITEM hRoot )
{
	guardfunc;
	TVINSERTSTRUCT tvInsert;
	ZeroMemory(&tvInsert,sizeof(TVINSERTSTRUCT));

	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT|TVIF_PARAM;

	tvInsert.hParent = hRoot;
	tvInsert.item.pszText = LPSTR( GetText() );
	tvInsert.item.lParam = (LPARAM)this;
	HTREEITEM hSetting = TreeView_InsertItem(hTree,&tvInsert);
	SetItem( hSetting );
	SetParent( pParent );
	return TRUE;
	unguard;
}
BOOL MexCfgAvatarSettings::Read( UPointer inP, int nSize )
{
	guardfunc;
	UPointer p(inP.p);
	while( p.c < inP.c+nSize )
	{
		switch( DC_TAG( *p.dw ) )
		{
		case 'arsg':
			{
				p.dw++;
				int size = *p.i++;
				MexCfgAvatarSetting* pSetting = MeNew MexCfgAvatarSetting;
				pSetting->Read( p, size );
				m_vectorSetting.push_back( pSetting );
				p.c += size; 
			}
			break;
		default:
			assert( false );
		}
	}
	return TRUE;
	unguard;
}
BOOL MexCfgAvatarSettings::Read_Old( UPointer inP, int nSize )
{
	guardfunc;
	UPointer p(inP.p);
	while( p.c < inP.c+nSize )
	{
		switch( DC_TAG( *p.dw ) )
		{
		case 'ast0':
			{
				p.dw++;
				int size = *p.i++;
				MexCfgAvatarSetting* pSetting = MeNew MexCfgAvatarSetting;
				pSetting->Read( p, size );
				m_vectorSetting.push_back( pSetting );
				p.c += size; 
			}
			break;
		default:
			assert( false );
		}
	}
	return TRUE;
	unguard;
}
MexCfgAvatarSettings::MexCfgAvatarSettings()
{
	guardfunc;
	MexCfgAvatarSetting* pSetting = MeNew MexCfgAvatarSetting;
	pSetting->m_spName.SetString( DEFAULT_AVATARSETTING_NAME );
	m_vectorSetting.push_back( pSetting );
	unguard;
}
MexCfgAvatarSetting* MexCfgAvatarSettings::FindByName( const char* pszName )
{
	guardfunc;
	if( !pszName )
	{
		//assert( false );
		return NULL;
	}
	for( int nSetting = 0; nSetting < m_vectorSetting.size(); nSetting++ )
	{
		MexCfgAvatarSetting* pSetting = m_vectorSetting[nSetting];
		if( !pSetting )
		{
			assert( false );
			continue;
		}
		if( stricmp( pSetting->m_spName.GetString(), pszName ) == 0 )
			return pSetting;
	}
	return NULL;
	unguard;
}
BOOL MexCfgAvatarSettings::CreateTree( I_MexTreeNode* pParent, HWND hTree, HTREEITEM hRoot )
{
	guardfunc;
	TVINSERTSTRUCT tvInsert;
	ZeroMemory(&tvInsert,sizeof(TVINSERTSTRUCT));

	tvInsert.hParent = hRoot;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT|TVIF_PARAM;
	tvInsert.item.pszText = LPSTR(GetText());
	tvInsert.item.lParam = (LPARAM)this;
	HTREEITEM hChild = TreeView_InsertItem(hTree,&tvInsert);
	SetItem( hChild );
	SetParent( pParent );

	for( int i = 0; i < m_vectorSetting.size(); i++ )
		m_vectorSetting[i]->CreateTree( this, hTree, hChild );
	m_hRootItem = hChild;
	return TRUE;
	unguard;
}
BOOL MexCfgBodyRadius::Read( UPointer inP, int nSize )
{
	guardfunc;
	UPointer p(inP.p);
	m_npRadius.SetNumber( *p.f++ );
	p.f++;
	p.f++;
	p.f++;
	p.f++;
	return TRUE;
	unguard;
}
//BOOL MexCfgComponent::CreateTree( I_MexTreeNode* pParent, HWND hTree, HTREEITEM hRoot )
//{
//	guardfunc;
//	TVINSERTSTRUCT tvInsert;
//	ZeroMemory(&tvInsert,sizeof(TVINSERTSTRUCT));
//
//	tvInsert.hParent = hRoot;
//	tvInsert.hInsertAfter = NULL;
//	tvInsert.item.mask = TVIF_TEXT|TVIF_PARAM;
//	tvInsert.item.pszText = LPSTR(GetText());
//	tvInsert.item.lParam = (LPARAM)this;
//	HTREEITEM hChild = TreeView_InsertItem(hTree,&tvInsert);
//	SetItem( hChild );
//	SetParent( pParent );
//	return TRUE;
//	unguard;
//}
BOOL MexCfgComponent::Read( UPointer inP, int nSize )
{
	guardfunc;
	UPointer p(inP.p);
	m_npIsComponent.SetNumber( *p.i++ );
	return TRUE;
	unguard;
}
BOOL MexCfgSoundEffect::Read( UPointer inP, int nSize )
{
	guardfunc;
	UPointer p(inP.p);
	m_spSoundFilename.SetString( p.c );
	p.c += I_MexTreeNode::eMaxString;
	m_npRange.SetNumber( *p.i++ );
	m_npLoopFlag.SetNumber( *p.i++ );
	m_npFrequence.SetNumber( *p.i++ );
	m_npIntensity.SetNumber( *p.i++ );
	return TRUE;
	unguard;
}

BOOL MexCfgSoundEffect::CreateTree( I_MexTreeNode* pParent, 
								   HWND hTree, 
								   HTREEITEM hRoot )
{
	guardfunc;
	TVINSERTSTRUCT tvInsert;
	ZeroMemory(&tvInsert,sizeof(TVINSERTSTRUCT));

	tvInsert.hParent = hRoot;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT|TVIF_PARAM;

	tvInsert.item.pszText = LPSTR( GetText() );
	tvInsert.item.lParam = (LPARAM)this;
	HTREEITEM hSoundEffect = TreeView_InsertItem(hTree,&tvInsert);
	SetItem( hSoundEffect );
	SetParent( pParent );


	tvInsert.hParent = hSoundEffect;
	tvInsert.item.pszText = LPSTR( m_spSoundFilename.GetText() );
	tvInsert.item.lParam = (LPARAM)&m_spSoundFilename;
	HTREEITEM hSoundFilename = TreeView_InsertItem(hTree,&tvInsert);
	m_spSoundFilename.SetItem( hSoundFilename );
	m_spSoundFilename.SetParent( this );

	tvInsert.hParent = hSoundEffect;
	tvInsert.item.pszText = LPSTR( m_npRange.GetText() );
	tvInsert.item.lParam = (LPARAM)&m_npRange;
	HTREEITEM hRange = TreeView_InsertItem(hTree,&tvInsert);
	m_npRange.SetItem( hRange );
	m_npRange.SetParent( this );


	tvInsert.hParent = hSoundEffect;
	tvInsert.item.pszText = LPSTR( m_npLoopFlag.GetText() );
	tvInsert.item.lParam = (LPARAM)&m_npLoopFlag;
	HTREEITEM hLoopFlag = TreeView_InsertItem(hTree,&tvInsert);
	m_npLoopFlag.SetItem( hLoopFlag );
	m_npLoopFlag.SetParent( this );

	tvInsert.hParent = hSoundEffect;
	tvInsert.item.pszText = LPSTR( m_npFrequence.GetText() );
	tvInsert.item.lParam = (LPARAM)&m_npFrequence;
	HTREEITEM hFrequence = TreeView_InsertItem(hTree,&tvInsert);
	m_npFrequence.SetItem( hFrequence );
	m_npFrequence.SetParent( this );

	tvInsert.hParent = hSoundEffect;
	tvInsert.item.pszText = LPSTR( m_npIntensity.GetText() );
	tvInsert.item.lParam = (LPARAM)&m_npIntensity;
	HTREEITEM hIntensity = TreeView_InsertItem(hTree,&tvInsert);
	m_npIntensity.SetItem( hIntensity );
	m_npIntensity.SetParent( this );


	return TRUE;
	unguard;
}



BOOL MexCfg::CreateTree(	I_MexTreeNode* pParent, 
							HWND hTree, HTREEITEM hRoot )
{
	guardfunc;
	TreeView_DeleteAllItems( hTree );
	
	TVINSERTSTRUCT tvInsert;
	ZeroMemory(&tvInsert,sizeof(TVINSERTSTRUCT));
	
	tvInsert.hParent = hRoot;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT|TVIF_PARAM;
	tvInsert.item.pszText = LPSTR(GetText());
	tvInsert.item.lParam = (LPARAM)this;
	HTREEITEM hChild = TreeView_InsertItem(hTree,&tvInsert);
	SetItem( hChild );
	SetParent( pParent );

	//m_sequences.CreateTree( this, hTree, hChild );
	
	
	m_mdlScale.CreateTree( this, hTree, hChild );
	
	m_soundEffect.CreateTree( this, hTree, hChild );

	m_BObj.CreateTree( this, hTree, hChild );

	m_AvatarSettings.CreateTree( this, hTree, hChild );
	m_BodyRadius.CreateTree( this, hTree, hChild );

	m_hRootItem = hChild;
	return TRUE;
	unguard;
}


BOOL MexCfg::SaveToFile( const char* pszFilename )
{
	CDataChunkWriter w( 1024*1024 );	// 1 mega memory
	w.StartChunk( DC_TAG( 'mexa' ) );
	{
		w.WriteInt( 1000 );
	}
	w.EndChunk( DC_TAG( 'mexa' ) );
	w.StartChunk( DC_TAG( 'sqcs' ) );
	{
		for( int i = 0; i < m_sequences.m_vectorSequence.size(); i++ )
		{
			MexCfgSequence* pSequence = m_sequences.m_vectorSequence[i];
			w.StartChunk( DC_TAG( 'sqce' ) );
			{
				w.Write( (char*)pSequence->m_spAnimName.GetString(), I_MexTreeNode::eMaxString, 1 );
				w.WriteInt( pSequence->m_npStartFrameId.GetNumber() );
				w.WriteInt( pSequence->m_npEndFrameId.GetNumber() );

				//for( int j = 0; j < pSequence->m_vectorHitPoint.size(); j++ )
				w.StartChunk( DC_TAG( 'htps' ) );
				{
					MexCfgHitPoints* pHpts = &pSequence->m_hitpoints;
					for( int j = 0; j < pHpts->m_vectorHitPoint.size(); j++ )
					{
						MexCfgHitPoint* pHPt = pHpts->m_vectorHitPoint[j];
						w.StartChunk( DC_TAG( 'htpt' ) );
						{
							w.WriteInt( pHPt->m_npFrameId.GetNumber() );
							w.Write( (char*)pHPt->m_spWavFilename.GetString(), I_MexTreeNode::eMaxString, 1 );
							w.WriteInt( pHPt->m_npHitTarget.GetNumber() );
							w.WriteInt( pHPt->m_npSrcEffect.GetNumber() );
							w.WriteInt( pHPt->m_npDstEffect.GetNumber() );
						}
						w.EndChunk( DC_TAG( 'htpt' ) );
					}
				}
				w.EndChunk( DC_TAG( 'htps' ) );
				//   added 2004.03.26
				w.StartChunk( DC_TAG( 'rlht' ) );
				{
					w.WriteInt( pSequence->m_npRealHitPoint.GetNumber() );
				}
				w.EndChunk( DC_TAG( 'rlht' ) );
				//   added 2004.09.25
				w.StartChunk( DC_TAG( 'lttk' ) );
				{
					w.WriteInt( pSequence->m_npHasLightTrack.GetNumber() );
				}
				w.EndChunk( DC_TAG( 'lttk' ) );

			}
			w.EndChunk( DC_TAG( 'sqce' ) );
		}
	}
	w.EndChunk( DC_TAG( 'sqcs' ) );
	w.StartChunk( DC_TAG( 'mxse' ) );
	{
		w.WriteInt( m_mdlScale.m_npScale.GetNumber() );
	}
	w.EndChunk( DC_TAG( 'mxse' ) );
	w.StartChunk( DC_TAG( 'sond' ) );
	{
		w.Write( (char*)m_soundEffect.m_spSoundFilename.GetString(), I_MexTreeNode::eMaxString, 1 );
		w.WriteInt( m_soundEffect.m_npRange.GetNumber() );
		w.WriteInt( m_soundEffect.m_npLoopFlag.GetNumber() );
		w.WriteInt( m_soundEffect.m_npFrequence.GetNumber() );
		w.WriteInt( m_soundEffect.m_npIntensity.GetNumber() );

	}
	w.EndChunk( DC_TAG( 'sond' ) );

	w.StartChunk( DC_TAG( 'bbox' ) );
	{
		w.WriteInt( m_BObj.m_npBBoxWidth.GetNumber() );
		w.WriteInt( m_BObj.m_npBBoxLength.GetNumber() );
		w.WriteInt( m_BObj.m_npBBoxHeight.GetNumber() );
		w.WriteInt( m_BObj.m_npBBoxLift.GetNumber() );
	}
	w.EndChunk( DC_TAG( 'bbox' ) );
	w.StartChunkWithTag( 'arss' );
	{
		for( int nSetting = 0; nSetting < m_AvatarSettings.m_vectorSetting.size(); nSetting++ )
		{
			MexCfgAvatarSetting* pSetting = m_AvatarSettings.m_vectorSetting[nSetting];
			// Default的配置是载入的时候自动生成的，不需要存储
			if( stricmp( pSetting->m_spName.GetString(), DEFAULT_AVATARSETTING_NAME ) == 0 )
				continue;
			w.StartChunkWithTag( 'arsg' );
			{
				w.Write( (char*)pSetting->m_spName.GetString(), I_MexTreeNode::eMaxString, 1 );
				w.WriteInt( pSetting->m_vectorSubsetFlag.size() );
				for( int nSubset = 0; nSubset < pSetting->m_vectorSubsetFlag.size(); nSubset++ )
				{
					w.WriteInt( pSetting->m_vectorSubsetFlag[nSubset] );
				}
				w.WriteInt( pSetting->m_vectorReplaceableTexture.size() );
				for( int nTexture = 0; nTexture < pSetting->m_vectorReplaceableTexture.size(); nTexture++ )
				{
					w.Write( pSetting->m_vectorReplaceableTexture[nTexture].szFileName,
						MAX_PATH,
						1 );
				}
			}
			w.EndChunkWithTag( 'arsg' );
		}
	}
	w.EndChunkWithTag( 'arss' );
	w.StartChunkWithTag( 'byrs' );
	{
		// 预留几个空间
		w.WriteFloat( m_BodyRadius.m_npRadius.GetNumber() );
		w.WriteFloat( 0.0f );
		w.WriteFloat( 0.0f );
		w.WriteFloat( 0.0f );
		w.WriteFloat( 0.0f );

	}
	w.EndChunkWithTag( 'byrs' );
	w.StartChunkWithTag( 'cmpt' );
	{
		w.WriteInt( m_Component.m_npIsComponent.GetNumber() );
	}
	w.EndChunkWithTag( 'cmpt' );

	BOOL bOK = w.SaveToFile( pszFilename );
	assert( bOK );
	w.Destroy();
	return true;
}
BOOL MexCfg::SaveToFile_Old( const char* pszFilename )
{
	guardfunc;
	CDataChunkWriter w( 1024*1024 );	// 1 mega memory
	w.StartChunk( DC_TAG( 'mdxc' ) );
	{
		w.WriteInt( 1000 );
	}
	w.EndChunk( DC_TAG( 'mdxc' ) );
	w.StartChunk( DC_TAG( 'seqs' ) );
	{
		for( int i = 0; i < m_sequences.m_vectorSequence.size(); i++ )
		{
			MexCfgSequence* pSequence = m_sequences.m_vectorSequence[i];
			w.StartChunk( DC_TAG( 'sequ' ) );
			{
				w.Write( (char*)pSequence->m_spAnimName.GetString(), I_MexTreeNode::eMaxString, 1 );
				w.WriteInt( pSequence->m_npStartFrameId.GetNumber() );
				w.WriteInt( pSequence->m_npEndFrameId.GetNumber() );
				
				//for( int j = 0; j < pSequence->m_vectorHitPoint.size(); j++ )
				w.StartChunk( DC_TAG( 'hpts' ) );
				{
					MexCfgHitPoints* pHpts = &pSequence->m_hitpoints;
					for( int j = 0; j < pHpts->m_vectorHitPoint.size(); j++ )
					{
						MexCfgHitPoint* pHPt = pHpts->m_vectorHitPoint[j];
						w.StartChunk( DC_TAG( 'hitp' ) );
						{
							w.WriteInt( pHPt->m_npFrameId.GetNumber() );
							w.Write( (char*)pHPt->m_spWavFilename.GetString(), I_MexTreeNode::eMaxString, 1 );
							w.WriteInt( pHPt->m_npHitTarget.GetNumber() );
							w.WriteInt( pHPt->m_npSrcEffect.GetNumber() );
							w.WriteInt( pHPt->m_npDstEffect.GetNumber() );
						}
						w.EndChunk( DC_TAG( 'hitp' ) );
					}
				}
				w.EndChunk( DC_TAG( 'hpts' ) );
				//   added 2004.03.26
				w.StartChunk( DC_TAG( 'rhpt' ) );
				{
					w.WriteInt( pSequence->m_npRealHitPoint.GetNumber() );
				}
				w.EndChunk( DC_TAG( 'rhpt' ) );
				//   added 2004.09.25
				w.StartChunk( DC_TAG( 'ltrk' ) );
				{
					w.WriteInt( pSequence->m_npHasLightTrack.GetNumber() );
				}
				w.EndChunk( DC_TAG( 'ltrk' ) );

			}
			w.EndChunk( DC_TAG( 'sequ' ) );
		}
	}
	w.EndChunk( DC_TAG( 'seqs' ) );
	w.StartChunk( DC_TAG( 'mdsc' ) );
	{
		w.WriteInt( m_mdlScale.m_npScale.GetNumber() );
	}
	w.EndChunk( DC_TAG( 'mdsc' ) );
	w.StartChunk( DC_TAG( 'snd0' ) );
	{
		w.Write( (char*)m_soundEffect.m_spSoundFilename.GetString(), I_MexTreeNode::eMaxString, 1 );
		w.WriteInt( m_soundEffect.m_npRange.GetNumber() );
		w.WriteInt( m_soundEffect.m_npLoopFlag.GetNumber() );
		w.WriteInt( m_soundEffect.m_npFrequence.GetNumber() );
		w.WriteInt( m_soundEffect.m_npIntensity.GetNumber() );
		
	}
	w.EndChunk( DC_TAG( 'snd0' ) );

	w.StartChunk( DC_TAG( 'bobj' ) );
	{
		w.WriteInt( m_BObj.m_npBBoxWidth.GetNumber() );
		w.WriteInt( m_BObj.m_npBBoxLength.GetNumber() );
		w.WriteInt( m_BObj.m_npBBoxHeight.GetNumber() );
		w.WriteInt( m_BObj.m_npBBoxLift.GetNumber() );
	}
	w.EndChunk( DC_TAG( 'bobj' ) );
	w.StartChunkWithTag( 'asts' );
	{
		for( int nSetting = 0; nSetting < m_AvatarSettings.m_vectorSetting.size(); nSetting++ )
		{
			MexCfgAvatarSetting* pSetting = m_AvatarSettings.m_vectorSetting[nSetting];
			// Default的配置是载入的时候自动生成的，不需要存储
			if( stricmp( pSetting->m_spName.GetString(), DEFAULT_AVATARSETTING_NAME ) == 0 )
				continue;
			w.StartChunkWithTag( 'ast0' );
			{
				w.Write( (char*)pSetting->m_spName.GetString(), I_MexTreeNode::eMaxString, 1 );
				w.WriteInt( pSetting->m_vectorSubsetFlag.size() );
				for( int nSubset = 0; nSubset < pSetting->m_vectorSubsetFlag.size(); nSubset++ )
				{
					w.WriteInt( pSetting->m_vectorSubsetFlag[nSubset] );
				}
				w.WriteInt( pSetting->m_vectorReplaceableTexture.size() );
				for( int nTexture = 0; nTexture < pSetting->m_vectorReplaceableTexture.size(); nTexture++ )
				{
					w.Write( pSetting->m_vectorReplaceableTexture[nTexture].szFileName,
						MAX_PATH,
						1 );
				}
			}
			w.EndChunkWithTag( 'ast0' );
		}
	}
	w.EndChunkWithTag( 'asts' );
	w.StartChunkWithTag( 'bdyr' );
	{
		// 预留几个空间
		w.WriteFloat( m_BodyRadius.m_npRadius.GetNumber() );
		w.WriteFloat( 0.0f );
		w.WriteFloat( 0.0f );
		w.WriteFloat( 0.0f );
		w.WriteFloat( 0.0f );
		
	}
	w.EndChunkWithTag( 'bdyr' );
	w.StartChunkWithTag( 'comp' );
	{
		w.WriteInt( m_Component.m_npIsComponent.GetNumber() );
	}
	w.EndChunkWithTag( 'comp' );

	BOOL bOK = w.SaveToFile( pszFilename );
	assert( bOK );
	w.Destroy();
	return TRUE;
	unguard;
}

//bool MexCfg::loadXMLSettings(const char *path  )
//{
//	guardfunc;
//	
//	return true;
//	unguard;
//}

BOOL MexCfg::LoadFromFile( const char* pszFilename )
{
	guardfunc;

	size_t dwFileSize = 0;
	BYTE* pBuffer = NULL;
	f_Handle* fp = NULL;
// 	if (g_DirectReadInPackage)
// 	{
// 		fp = packet_namespace::w_fopen( pszFilename, "rb" );
// // 		fp = Cipher::CipherFactory::OpenCipherFile(pszFilename);
// 		if( !fp )
// 		{
// 			return FALSE;
// 		}
// 	}
// 	else
	{
		fp = packet_namespace::w_fopen( pszFilename, "rb" );
		if( fp == 0 )
		{
// 			fp = Cipher::CipherFactory::OpenCipherFile(pszFilename);
// 			if( !fp )
			{
				return FALSE;
			}
		}

	}
	{
		packet_namespace::w_fseek ( fp, 0, SEEK_END );
		dwFileSize = packet_namespace::w_ftell( fp );
		if( dwFileSize == 0 )
		{
			packet_namespace::w_fclose( fp );
			return FALSE;
		}
		//pBuffer = MeDefaultNew BYTE[dwFileSize];
		// 分配备份内存
		m_pMemoryBuffer = MeDefaultNew BYTE[dwFileSize];
		pBuffer = m_pMemoryBuffer;

		packet_namespace::w_rewind( fp );
		packet_namespace::w_fread( pBuffer, dwFileSize, 1, fp );
		packet_namespace::w_fclose( fp );
	}


	int nSize = dwFileSize;
	m_dwFileSize = dwFileSize;
	UPointer p( pBuffer );

	while( p.c < (char*)pBuffer+nSize )
	{
		switch( DC_TAG( *p.dw ) )
		{
		case 'mexa':
			{
				p.dw++;
				int size = *p.i++;
				p.c += size; 
			}
			break;
		case 'sqcs':
			{
				p.dw++;
				int size = *p.i++;
				m_sequences.Read( p, size );
				p.c += size; 
			}
			break;
		case 'mxse':
			{
				p.dw++;
				int size = *p.i++;
				m_mdlScale.Read( p, size );
				p.c += size; 
			}
			break;
		case 'sond':
			{
				p.dw++;
				int size = *p.i++;
				m_soundEffect.Read( p, size );
				p.c += size;
			}
			break;
		case 'bbox':
			{
				p.dw++;
				int size = *p.i++;
				m_BObj.Read( p, size );
				p.c += size;
			}
			break;
		case 'arss':
			{
				p.dw++;
				int size = *p.i++;
				m_AvatarSettings.Read( p, size );
				p.c += size;
			}
			break;
		case 'byrs':
			{
				p.dw++;
				int size = *p.i++;
				m_BodyRadius.Read( p, size );
				p.c += size;
			}
			break;
		case 'cmpt':
			{
				p.dw++;
				int size = *p.i++;
				m_Component.Read( p, size );
				p.c += size;
			}
			break;
		default:
			{
				assert( false && pszFilename );
				delete []m_pMemoryBuffer;
				m_pMemoryBuffer = NULL;
				return FALSE;
			}			
		};
	}
	
	delete []m_pMemoryBuffer;
	m_pMemoryBuffer = NULL;

	for( int i = 0; i < m_sequences.m_vectorSequence.size(); i++ )
	{
		MexCfgSequence* pSeq = m_sequences.m_vectorSequence[i];
		m_seqMapStrToIdMgr.Register( pSeq->m_spAnimName.GetString(), pSeq );
	}

	return TRUE;
	unguard;

}

BOOL MexCfg::LoadFromFile_Old( const char* pszFilename )
{
	guardfunc;

	size_t dwFileSize = 0;
	BYTE* pBuffer = NULL;
	f_Handle* fp = NULL;
// 	if (g_DirectReadInPackage)
// 	{
// // 		fp = Cipher::CipherFactory::OpenCipherFile(pszFilename);
// 		fp = packet_namespace::w_fopen( pszFilename, "rb" );
// 		if( !fp )
// 		{
// 			return FALSE;
// 		}
// 	}
// 	else
	{
		fp = packet_namespace::w_fopen( pszFilename, "rb" );
		if( fp == 0 )
		{
// 			fp = Cipher::CipherFactory::OpenCipherFile(pszFilename);
// 			if( !fp )
// 			{
				return FALSE;
// 			}
		}
	}
	{
		packet_namespace::w_fseek ( fp, 0, SEEK_END );
		dwFileSize = packet_namespace::w_ftell( fp );
		if( dwFileSize == 0 )
		{
			packet_namespace::w_fclose( fp );
			return FALSE;
		}
		//pBuffer = MeDefaultNew BYTE[dwFileSize];
		// 分配备份内存
		m_pMemoryBuffer = MeDefaultNew BYTE[dwFileSize];
		pBuffer = m_pMemoryBuffer;

		packet_namespace::w_rewind( fp );
		packet_namespace::w_fread( pBuffer, dwFileSize, 1, fp );
		packet_namespace::w_fclose( fp );
	}

	
	int nSize = dwFileSize;
	m_dwFileSize = dwFileSize;
	UPointer p( pBuffer );

	while( p.c < (char*)pBuffer+nSize )
	{
		switch( DC_TAG( *p.dw ) )
		{
		case 'mdxc':
			{
				p.dw++;
				int size = *p.i++;
				p.c += size; 
			}
			break;
		case 'seqs':
			{
				p.dw++;
				int size = *p.i++;
				m_sequences.Read_Old( p, size );
				p.c += size; 
			}
			break;
		case 'mdsc':
			{
				p.dw++;
				int size = *p.i++;
				m_mdlScale.Read( p, size );
				p.c += size; 
			}
			break;
		case 'snd0':
			{
				p.dw++;
				int size = *p.i++;
				m_soundEffect.Read( p, size );
				p.c += size;
			}
			break;
		case 'bobj':
			{
				p.dw++;
				int size = *p.i++;
				m_BObj.Read( p, size );
				p.c += size;
			}
			break;
		case 'asts':
			{
				p.dw++;
				int size = *p.i++;
				m_AvatarSettings.Read_Old( p, size );
				p.c += size;
			}
			break;
		case 'bdyr':
			{
				p.dw++;
				int size = *p.i++;
				m_BodyRadius.Read( p, size );
				p.c += size;
			}
			break;
		case 'comp':
			{
				p.dw++;
				int size = *p.i++;
				m_Component.Read( p, size );
				p.c += size;
			}
			break;
		default:
			assert( false && pszFilename );
		};
	}
	//delete []pBuffer;
	for( int i = 0; i < m_sequences.m_vectorSequence.size(); i++ )
	{
		MexCfgSequence* pSeq = m_sequences.m_vectorSequence[i];
		m_seqMapStrToIdMgr.Register( pSeq->m_spAnimName.GetString(), pSeq );
	}

	return TRUE;
	unguard;

}

MexCfgSequence* MexCfg::FindIdleSequence()
{
	guardfunc;
	for( int i = 0; i < m_sequences.m_vectorSequence.size(); i++ )
	{
		MexCfgSequence* pSeq = m_sequences.m_vectorSequence[i];
		//m_seqMapStrToIdMgr.Register( pSeq->m_spAnimName.GetString(), pSeq );
		if( strnicmp( pSeq->m_spAnimName.GetString(), "idle", 4 ) == 0 )
			return pSeq;
	}
	return NULL;
	unguard;
}
MexCfgSequence* MexCfg::GetSequence( const char* pszActionName )
{
	guardfunc;
	if( pszActionName )
	{
		MexCfgSequence* pSeq = (MexCfgSequence*)m_seqMapStrToIdMgr.GetDstByName( pszActionName );
		return pSeq;
	}
	return NULL;
	unguard;
}

BOOL MexCfg::LoadFromMemory( BYTE* pBuffer, DWORD dwFileSize )
{
	guardfunc;

	int nSize = dwFileSize;
	UPointer p( pBuffer );

	while( p.c < (char*)pBuffer+nSize )
	{
		switch( DC_TAG( *p.dw ) )
		{
		case 'mexa':
			{
				p.dw++;
				int size = *p.i++;
				p.c += size; 
			}
			break;
		case 'sqcs':
			{
				p.dw++;
				int size = *p.i++;
				m_sequences.Read( p, size );
				p.c += size; 
			}
			break;
		case 'mxse':
			{
				p.dw++;
				int size = *p.i++;
				m_mdlScale.Read( p, size );
				p.c += size; 
			}
			break;
		case 'sond':
			{
				p.dw++;
				int size = *p.i++;
				m_soundEffect.Read( p, size );
				p.c += size;
			}
			break;
		case 'bbox':
			{
				p.dw++;
				int size = *p.i++;
				m_BObj.Read( p, size );
				p.c += size;
			}
			break;
		case 'arss':
			{
				p.dw++;
				int size = *p.i++;
				m_AvatarSettings.Read( p, size );
				p.c += size;
			}
			break;
		case 'byrs':
			{
				p.dw++;
				int size = *p.i++;
				m_BodyRadius.Read( p, size );
				p.c += size;
			}
			break;
		case 'cmpt':
			{
				p.dw++;
				int size = *p.i++;
				m_Component.Read( p, size );
				p.c += size;
			}
			break;
		default:
			break;
		};
	}
	//delete []pBuffer;
	for( int i = 0; i < m_sequences.m_vectorSequence.size(); i++ )
	{
		MexCfgSequence* pSeq = m_sequences.m_vectorSequence[i];
		m_seqMapStrToIdMgr.Register( pSeq->m_spAnimName.GetString(), pSeq );
	}

	return TRUE;
	unguard;
}
void MexCfg::Destroy()
{
	if(m_pMemoryBuffer){ delete[] (m_pMemoryBuffer); (m_pMemoryBuffer)=NULL; }
}

BOOL MexCfg::CombineCommonSequences(MexCfg* pCommonCfg, int nFrameOffset)
{
	if( !pCommonCfg )
		return FALSE;

	m_FrameOffset = nFrameOffset;
	// 修正原有动画序列（加上偏移量）
	for(UINT nSeq = 0; nSeq<m_sequences.m_vectorSequence.size(); nSeq++)
	{
		MexCfgSequence* pSequence = m_sequences.m_vectorSequence[nSeq];
		pSequence->m_npStartFrameId.SetNumber( pSequence->m_npStartFrameId.GetNumber() + nFrameOffset );
		pSequence->m_npEndFrameId.SetNumber( pSequence->m_npEndFrameId.GetNumber() + nFrameOffset );
		pSequence->m_npRealHitPoint.SetNumber( pSequence->m_npRealHitPoint.GetNumber() + nFrameOffset );
		// commented out, jiayi, [2009.4.23],bool值而已
		//pSequence->m_npHasLightTrack.SetNumber( pSequence->m_npHasLightTrack.GetNumber() + nFrameOffset );
		for( UINT i = 0; i < pSequence->m_hitpoints.m_vectorHitPoint.size(); i++ )
		{
			if( pSequence->m_hitpoints.m_vectorHitPoint[i] )
			{
				MexCfgHitPoint* pHpt = pSequence->m_hitpoints.m_vectorHitPoint[i];
				pHpt->m_npFrameId.SetNumber( pHpt->m_npFrameId.GetNumber() + nFrameOffset );
				pHpt->m_npHitTarget.SetNumber( pHpt->m_npHitTarget.GetNumber() + nFrameOffset );
				pHpt->m_npSrcEffect.SetNumber( pHpt->m_npSrcEffect.GetNumber() + nFrameOffset );
				pHpt->m_npDstEffect.SetNumber( pHpt->m_npDstEffect.GetNumber() + nFrameOffset );
			}
		}
	}

	// 把pCommonCfg里动画序列拷贝到当前动画里
	MexCfgSequences* pCommonSequences = &pCommonCfg->m_sequences;
	for(UINT nSeq = 0; nSeq<pCommonSequences->m_vectorSequence.size(); nSeq++)
	{
		MexCfgSequence* pDstSequence = MeNew MexCfgSequence;
		MexCfgSequence* pSrcSequence = pCommonSequences->m_vectorSequence[nSeq];
		pDstSequence->m_spAnimName.SetString(pSrcSequence->m_spAnimName.GetString());
		pDstSequence->m_npStartFrameId.SetNumber( pSrcSequence->m_npStartFrameId.GetNumber() );
		pDstSequence->m_npEndFrameId.SetNumber( pSrcSequence->m_npEndFrameId.GetNumber() );
		pDstSequence->m_npRealHitPoint.SetNumber( pSrcSequence->m_npRealHitPoint.GetNumber() );
		// commented out, jiayi, [2009.4.23]
		//pDstSequence->m_npHasLightTrack.SetNumber( pSrcSequence->m_npHasLightTrack.GetNumber() );
		for( UINT i = 0; i < pSrcSequence->m_hitpoints.m_vectorHitPoint.size(); i++ )
		{
			if( pSrcSequence->m_hitpoints.m_vectorHitPoint[i] )
			{
				MexCfgHitPoint* pSrcHpt = pSrcSequence->m_hitpoints.m_vectorHitPoint[i];
				MexCfgHitPoint* hpt = MeNew MexCfgHitPoint;
				hpt->m_npFrameId.SetNumber( pSrcHpt->m_npFrameId.GetNumber() );
				hpt->m_spWavFilename.SetString( pSrcHpt->m_spWavFilename.GetString() );
				hpt->m_npHitTarget.SetNumber( pSrcHpt->m_npHitTarget.GetNumber() );
				hpt->m_npSrcEffect.SetNumber( pSrcHpt->m_npSrcEffect.GetNumber() );
				hpt->m_npDstEffect.SetNumber( pSrcHpt->m_npDstEffect.GetNumber() );

				pDstSequence->m_hitpoints.m_vectorHitPoint.push_back( hpt );
			}
		}
		// 注册新动画
		m_sequences.m_vectorSequence.push_back(pDstSequence);
		m_seqMapStrToIdMgr.Register( pDstSequence->m_spAnimName.GetString(), pDstSequence );
	}
	return TRUE;
}

