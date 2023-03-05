/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	NdlGlobalResMgr.h
* Create: 	10/06/2006
* Desc:		全局地图资源
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef _NDL_NDLGLOBALRESMGR_H__
#define _NDL_NDLGLOBALRESMGR_H__

class CDoodadRes;
class CNdlLightRes;
class CNdlFogRes;
class CNdlEnvRes;
////////////////////////////////////////////////////////////////////////////////
class CNdlGlobalResMgr
{
	friend class					CWorldBuffer;
	friend class					CWorldReadStream;
	friend class					CWorldWriteStream;
	friend class					CNdlWorldEditor;
	friend class					CToolDoodadDlg;		// Only for world edit.
	friend class					CToolWorldLightDlg;
	friend class					CToolEnvDlg;
	friend class					CToolEnv;
	friend class					CToolWorldFogDlg;
public:
									CNdlGlobalResMgr();
									~CNdlGlobalResMgr();
	
	bool							Create();
	bool							ReCreate();
	void							Reset();
	void							Destroy();

	void							DestoryModelDoodad();
	void							UnloadModelDoodad();///卸载模型文件在内存中的镜像

	void							Update( flt32 totalTime, flt32 deltaTime );

	CNdlTextureRes*					GetCurrFrameLiquidRes( sInt32 liquidId );
	// added, jiayi, [2009.4.23]
	CNdlTextureRes*					GetCurrFrameLiquidNormalRes( sInt32 liquidId );
	//// 初始化多线程
	//bool							CreateMultiThread();
	//void							DestroyMultiThread();
	CNdlStaticModelRes*					LoadRefModel( const char* modelName );
	void							UnloadRefModel( const char* modelName );
	CNdlStaticModelRes*					FindRefStaticModel( const char* modelName );

// 	CDoodadRes*					LoadRefDoodad( const char* doodadName );
// 	void							UnloadRefDoodad( const char* doodadName );
	CDoodadRes*					RetriveRefDoodad( const char* doodadName );


	const PtHashString<CDoodadRes*>& DoodadPtrHash() const { return m_doodadPtrHash; }
protected:


	bool							LoadLiquidRes();
	bool							LoadLightRes();

	bool							LoadLiquidTexture( const char* fileName, sInt32 texCount );

	void							UpdateLiquidTexture();


protected:
	flt32							m_totalTime;
	
	std::vector< CWorldRes* >		m_liquidResList;

	PtHashString< CNdlStaticModelRes* >	m_modelPtrHash;
	PtHashString< CDoodadRes* >	m_doodadPtrHash;

};


#endif	// _NDL_NDLGLOBALRESMGR_H__

