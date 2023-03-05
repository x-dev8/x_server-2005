#pragma once
#include "Me3d/Me3d.h"
#include <commctrl.h>

#include "mapstrtoid.h"
#include <iostream>

using namespace std;
#define DEFAULT_AVATARSETTING_NAME "Default"
enum
{
	eMexCfg_SubsetVisible = 1<<0,
};
// class MexCfgActions
// {
// public:
// 	enum
// 	{
// 		eMaxFieldSize	= 128
// 	};
// 
// 	struct Record
// 	{
// 		char szTitle[eMaxFieldSize];
// 		char szName[eMaxFieldSize];
// 	};
// public:
// 	BOOL	LoadFromSlk( const char* pszFilename );
// 	int		GetRecordCount(){ return m_vectorRecord.size(); }
// 	Record* GetRecord( int i ){ return &m_vectorRecord[i]; }
// 	Record* FindRecordByName( const char* pszAnimName );
// protected:
// 	std::vector<Record> m_vectorRecord;
// };

// class MexCfgModels
// {
// public:
// 	struct Record
// 	{
// 		DWORD dwId;
// 		char szFilename[MAX_PATH];
// 	};
// public:
// 	BOOL LoadFromSlk( const char* pszFilename );
// 	BOOL LoadFromDirectory( const char* pszDir );
// 	BOOL CreateTree( HWND hTree );
// 
// 	Record* GetRecord( int i ){ return &m_vectorRecord[i]; }
// //protected:
// public:
// 	std::vector<Record> m_vectorRecord;
// };

union UPointer
{
	int*			i;
	DWORD*			dw;
	char*			c;
	void*			p;
	float*			f;
	UPointer(void* in) :p(in)
	{
	}
};

class I_MexTreeNode : public MeCommonAllocObj<I_MexTreeNode>
{
public:
	enum
	{
		eMaxString = 256
	};
	enum
	{
		eMex,
		eSequences,
		eSequence,
		eHitPoint,
		eHitPoints,
		eNumberParam,
		eStringParam,
		eModelScale,
		eModelBoundingObject,
		eSoundEffect,
		eAvatarSetting,
		eAvatarSettings,
		eBodyRadius,
		eIsComponent,
	};
public:
	I_MexTreeNode():	m_hItem(NULL),
						m_pParent(NULL){}
	virtual DWORD GetType() = 0;
	virtual const char*  GetText() = 0;
	virtual BOOL CanModify(){ return FALSE; }
	virtual BOOL SetValue( const char* pszValue ){ return FALSE; }

	void	SetItem( HTREEITEM hItem ){ m_hItem = hItem; }
	HTREEITEM GetItem(){ return m_hItem; }
	void	SetParent( I_MexTreeNode* pParent ){ m_pParent = pParent; }
	I_MexTreeNode* GetParent(){ return m_pParent; }
protected:
	HTREEITEM m_hItem;
	I_MexTreeNode* m_pParent;
};

class CNumberParam:public I_MexTreeNode
{
public:
	CNumberParam()
	{
		m_nNumber = 0;
		m_szTitle[0] = 0;
	}
	virtual DWORD GetType(){ return I_MexTreeNode::eNumberParam; }
	const char*  GetText()
	{ 
		static char s[I_MexTreeNode::eMaxString];
		memset( s, 0x00, sizeof(s) );
		sprintf( s, "%s:%ld", m_szTitle, m_nNumber );
		return s; 
	}
	virtual BOOL CanModify(){ return TRUE; }
	virtual BOOL SetValue( const char* pszValue )
	{ 
		m_nNumber = atoi( pszValue ); 
		return TRUE; 
	}
	
	void	SetNumber( int nNumber ){ m_nNumber = nNumber; }
	int		GetNumber(){ return m_nNumber; }
	void	SetTitle( const char* pszTitle ){ strcpy( m_szTitle, pszTitle ); }
protected:
	int		m_nNumber;
	char	m_szTitle[I_MexTreeNode::eMaxString];
};
class CStringParam:public I_MexTreeNode
{
public:
	CStringParam()
	{
		memset( m_szTitle, 0x00, sizeof(m_szTitle) );
		memset( m_szString, 0x00, sizeof(m_szString) );
	};
	virtual DWORD GetType(){ return I_MexTreeNode::eNumberParam; }
	const char*  GetText()
	{ 
		static char s[I_MexTreeNode::eMaxString];
		memset( s, 0x00, sizeof(s) );

		sprintf( s, "%s:%s", m_szTitle, m_szString );
//		assert( strlen( s ) <= I_MexTreeNode::eMaxString );
		return s; 
	}
	virtual BOOL CanModify(){ return TRUE; }
	virtual BOOL SetValue( const char* pszValue )
	{ 
		SetString( pszValue ); 
		return TRUE; 
	}
	
	void	SetString( const char* pszString ){ strcpy( m_szString, pszString ); }
	const char* GetString(){ return m_szString; }
	void	SetTitle( const char* pszTitle ){ strcpy( m_szTitle, pszTitle ); }
protected:
	char	m_szTitle[I_MexTreeNode::eMaxString];
	char	m_szString[I_MexTreeNode::eMaxString];
};


class MexCfgHitPoint:public I_MexTreeNode
{
public:
	MexCfgHitPoint()
	{
		m_npFrameId.SetTitle( "FrameId" );
		m_spWavFilename.SetTitle( "WavFilename" );
		m_npHitTarget.SetTitle( "Hit Target" );
		m_npSrcEffect.SetTitle( "Src Effect" );
		m_npSrcEffect.SetNumber( -1 );
		m_npDstEffect.SetTitle( "Dst Effect" );
		m_npDstEffect.SetNumber( -1 );

	}
	virtual DWORD GetType(){ return I_MexTreeNode::eHitPoint; }
	const char*  GetText(){ return "HitPoint"; }

	CNumberParam m_npFrameId;
	CStringParam m_spWavFilename;
	CNumberParam m_npHitTarget;
	CNumberParam m_npSrcEffect;
	CNumberParam m_npDstEffect;
	BOOL	Read( UPointer inP, int nSize );
	BOOL	CreateTree( I_MexTreeNode* pParent,
						HWND hTree, HTREEITEM hRoot );
};

class MexCfgHitPoints:public I_MexTreeNode
{
public:
	MexCfgHitPoints()
	{
	}
	~MexCfgHitPoints()
	{
		for( int i = 0; i < (int)m_vectorHitPoint.size(); i++ )
		{
			if( m_vectorHitPoint[i] )
			{
				delete m_vectorHitPoint[i];
			}
		}
		m_vectorHitPoint.clear();
	}
	virtual DWORD GetType(){ return I_MexTreeNode::eHitPoints; }
	const char*  GetText(){ return "HitPoints"; }
	BOOL	Read( UPointer inP, int nSize );
	BOOL	Read_Old( UPointer inP, int nSize );
	BOOL	CreateTree( I_MexTreeNode* pParent,
						HWND hTree, HTREEITEM hRoot );
	std::vector<MexCfgHitPoint*> m_vectorHitPoint;
};

class MexCfgSequence:public I_MexTreeNode/*, public IOXMLObjectInstance*/
{
public:
	//virtual bool loadXMLSettings(XMLElement *element);
	//virtual bool exportXMLSettings(std::ofstream &xmlFile  );
	MexCfgSequence()/*:
	  IOXMLObjectInstance("sequ")*/
	{
		m_spAnimName.SetTitle( "Name" );
		m_npStartFrameId.SetTitle( "StartFrameId" );
		m_npEndFrameId.SetTitle( "EndFrameId" );
		m_npRealHitPoint.SetTitle( "Real Hit Point" );
		m_npHasLightTrack.SetTitle( "Has Light Track" );
	}
	virtual DWORD GetType(){ return I_MexTreeNode::eSequence; }
	const char*  GetText()
	{ 
		static char s[I_MexTreeNode::eMaxString];
		memset( s, 0x00, sizeof(s) );
		sprintf( s, "%s", m_spAnimName.GetString() );
		return s;
	}

	BOOL	Read( UPointer inP, int nSize );
	BOOL	Read_Old( UPointer inP, int nSize );
	BOOL	CreateTree( I_MexTreeNode* pParent, HWND hTree, HTREEITEM hRoot );	
	int		BlendFrame( float t );
	float	GetBlendFrame( float t );

	CStringParam m_spAnimName;
	CNumberParam m_npStartFrameId;
	CNumberParam m_npEndFrameId;
	MexCfgHitPoints m_hitpoints;
	CNumberParam m_npRealHitPoint;
	CNumberParam m_npHasLightTrack;
};

class MexCfgSequences:public I_MexTreeNode
{
public:
	MexCfgSequences()
	{
		m_hRootItem = NULL;	
	}
	~MexCfgSequences()
	{
		for( int i = 0; i < (int)m_vectorSequence.size(); i++ )
		{
			if( m_vectorSequence[i] )
				delete m_vectorSequence[i];
		}
		m_vectorSequence.clear();
	}
	virtual DWORD GetType(){ return I_MexTreeNode::eSequences; }
	const char*  GetText(){ return "Sequences"; }

	BOOL	Read( UPointer inP, int nSize );
	BOOL	Read_Old( UPointer inP, int nSize );
	BOOL	CreateTree( I_MexTreeNode* pParent, HWND hTree, HTREEITEM hRoot );
	std::vector<MexCfgSequence*> m_vectorSequence;
	HTREEITEM m_hRootItem;

};

class MexCfgModelScale:public I_MexTreeNode
{
public:
	MexCfgModelScale()
	{
		m_npScale.SetNumber( 100 );
	}
	virtual DWORD GetType(){ return I_MexTreeNode::eModelScale; }
	const char*  GetText()
	{ 
		static char s[I_MexTreeNode::eMaxString];
		sprintf( s, "Model Scale:%ld", m_npScale.GetNumber() );
		return s;
	}
	virtual BOOL CanModify(){ return TRUE; }
	virtual BOOL SetValue( const char* pszValue )
	{ 
		m_npScale.SetNumber( atoi( pszValue ) );
		return TRUE;
	}

	BOOL	Read( UPointer inP, int nSize );
	BOOL	CreateTree( I_MexTreeNode* pParent, HWND hTree, HTREEITEM hRoot );	

	CNumberParam m_npScale;
};
class MexCfgBodyRadius:public I_MexTreeNode
{
public:
	MexCfgBodyRadius()
	{
		m_npRadius.SetNumber( 10 );
	}
	virtual DWORD GetType(){ return I_MexTreeNode::eBodyRadius; }
	const char*  GetText()
	{ 
		static char s[I_MexTreeNode::eMaxString];
		sprintf( s, "Body Radius:%ld", m_npRadius.GetNumber() );
		return s;
	}
	virtual BOOL CanModify(){ return TRUE; }
	virtual BOOL SetValue( const char* pszValue )
	{ 
		m_npRadius.SetNumber( atoi( pszValue ) );
		return TRUE;
	}

	BOOL	Read( UPointer inP, int nSize );	
	BOOL	CreateTree( I_MexTreeNode* pParent, HWND hTree, HTREEITEM hRoot );	

	CNumberParam m_npRadius;
};
class MexCfgComponent:public I_MexTreeNode
{
public:
	MexCfgComponent()
	{
		m_npIsComponent.SetNumber( 0 );
	}
	virtual DWORD GetType(){ return I_MexTreeNode::eIsComponent; }
	const char*  GetText()
	{ 
		static char s[I_MexTreeNode::eMaxString];
		sprintf( s, "Is Component:%ld", m_npIsComponent.GetNumber() );
		return s;
	}
	virtual BOOL CanModify(){ return TRUE; }
	virtual BOOL SetValue( const char* pszValue )
	{ 
		m_npIsComponent.SetNumber( atoi( pszValue ) );
		return TRUE;
	}

	BOOL	Read( UPointer inP, int nSize );
	//BOOL	CreateTree( I_MexTreeNode* pParent, HWND hTree, HTREEITEM hRoot );	

	CNumberParam m_npIsComponent;
};
class MexCfgModelBoundingObject:public I_MexTreeNode
{
public:
	MexCfgModelBoundingObject()
	{
		m_npBBoxWidth.SetTitle( "Width" );
		m_npBBoxLength.SetTitle( "Length" );
		m_npBBoxHeight.SetTitle( "Height" );
		m_npBBoxLift.SetTitle( "Lift" );
	}
	virtual DWORD GetType(){ return I_MexTreeNode::eModelBoundingObject; }
	const char*  GetText()
	{ 
		static char s[I_MexTreeNode::eMaxString];
		sprintf( s, "BoundingObject" );
		return s;
	}

	BOOL	Read( UPointer inP, int nSize );
	BOOL	CreateTree( I_MexTreeNode* pParent, HWND hTree, HTREEITEM hRoot );	

	CNumberParam m_npBBoxWidth;
	CNumberParam m_npBBoxLength;
	CNumberParam m_npBBoxHeight;
	CNumberParam m_npBBoxLift;
	
};
class MexCfgAvatarSetting:public I_MexTreeNode
{
public:
	struct ReplaceableTexture
	{
		char szFileName[MAX_PATH];
		int nRenderTextureID;
//		bool	bMult;		//..bMult
		ReplaceableTexture()
		{
			memset( szFileName, 0x00, sizeof(szFileName ));
			nRenderTextureID = -1;
//bMult = FALSE;
		}
	};
	

public:
	MexCfgAvatarSetting();
	~MexCfgAvatarSetting()
	{
		m_vectorSubsetFlag.clear();
		m_vectorReplaceableTexture.clear();
	}
	virtual DWORD GetType(){ return I_MexTreeNode::eAvatarSetting; }
	const char*  GetText(){ return m_spName.GetString(); }
	BOOL CanModify(){ return TRUE; }
	BOOL SetValue( const char* pszValue ){ m_spName.SetString( pszValue ); return TRUE; }
	BOOL	CreateTree( I_MexTreeNode* pParent, HWND hTree, HTREEITEM hRoot );

	BOOL	Read( UPointer inP, int nSize );
	std::vector<DWORD> m_vectorSubsetFlag;
	std::vector<ReplaceableTexture> m_vectorReplaceableTexture;
	CStringParam	m_spName;
	BOOL	m_bTextureLoaded;
};
class MexCfgAvatarSettings:public I_MexTreeNode
{
public:
	MexCfgAvatarSettings();
	~MexCfgAvatarSettings()
	{
		for( int i = 0; i < m_vectorSetting.size(); i++ )
		{
			delete m_vectorSetting[i];
		}
		m_vectorSetting.clear();
	}
	virtual DWORD GetType(){ return I_MexTreeNode::eAvatarSettings; }
	const char*  GetText(){ return "AvatarSettings"; }
	BOOL	Read( UPointer inP, int nSize );
	BOOL	Read_Old( UPointer inP, int nSize );
	BOOL	CreateTree( I_MexTreeNode* pParent, HWND hTree, HTREEITEM hRoot );
	MexCfgAvatarSetting* FindByName( const char* pszName );
	std::vector<MexCfgAvatarSetting*> m_vectorSetting;
	HTREEITEM m_hRootItem;
};
class MexCfgSoundEffect:public I_MexTreeNode
{
public:
	MexCfgSoundEffect()
	{
		m_spSoundFilename.SetTitle( "SoundFilename" );
		m_npRange.SetTitle( "Range" );
		m_npLoopFlag.SetTitle( "Loop" );
		m_npFrequence.SetTitle( "Frequence" );
		m_npIntensity.SetTitle( "Intensity" );

	}
	virtual DWORD GetType(){ return I_MexTreeNode::eSoundEffect; }
	const char*  GetText(){ return "Sound Effect" ;}

	BOOL	Read( UPointer inP, int nSize );
	BOOL	CreateTree( I_MexTreeNode* pParent,
		HWND hTree, HTREEITEM hRoot );

	CStringParam m_spSoundFilename;
	CNumberParam m_npRange;
	CNumberParam m_npLoopFlag;
	CNumberParam m_npFrequence;
	CNumberParam m_npIntensity;
};

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif

class MexCfg:public I_MexTreeNode/*, public IOXMLObjectInstance*/
{
public:
	//virtual bool loadXMLSettings(const char *path  );
	//virtual bool loadXMLSettings(XMLElement *element);
	//virtual bool exportXMLSettings(std::ofstream &xmlFile  );
	//virtual bool exportXMLSettings(const char* xmlPath);
	MexCfg()
		/*:IOXMLObjectInstance("MexCfg")*/
	{
		m_pMemoryBuffer = NULL;
		m_dwFileSize = 0;
		m_FrameOffset = 0;
	};
	~MexCfg(){Destroy();};
	void Destroy();;
	DWORD GetType(){ return I_MexTreeNode::eMex; }
	const char*  GetText(){ return "Mex"; }

	BOOL	LoadFromFile( const char* pszFilename );
	BOOL	LoadFromFile_Old( const char* pszFilename );
	BOOL	LoadFromMemory(BYTE* pBuffer, DWORD dwFileSize);
	BOOL	SaveToFile( const char* pszFilename );
	BOOL    SaveToFile_Old( const char* pszFilename );
	BOOL	CreateTree( I_MexTreeNode* pParent, 
						HWND hTree, HTREEITEM hRoot );

	MexCfgSequence* GetSequence( const char* pszActionName );
	MexCfgSequence* FindIdleSequence();
	BYTE*	GetMemory(){return m_pMemoryBuffer;};
	DWORD	GetFileSize(){return m_dwFileSize;};

	/* 把通用动画序列合并到武器动画里，并修正武器动画序列的startframe和endframe，
	nFrameOffset是前面动画数据的总帧数 */
	BOOL	CombineCommonSequences(MexCfg* pCommonCfg, int nFrameOffset);
	int GetFrameOffset() const { return m_FrameOffset; }

public:
	MexCfgSequences m_sequences;
	MexCfgModelScale m_mdlScale;	
	MexCfgSoundEffect m_soundEffect;
	MexCfgModelBoundingObject m_BObj;
	CMapStrToIDMgr	m_seqMapStrToIdMgr;
	MexCfgAvatarSettings m_AvatarSettings;
	MexCfgBodyRadius	m_BodyRadius;
	MexCfgComponent	m_Component;
	HTREEITEM		m_hRootItem;

protected:
	BYTE*	m_pMemoryBuffer;		// 第一份资源读入内存
	DWORD	m_dwFileSize;
	int		m_FrameOffset;
};

