#include "Me3d/Model/MexAnimCtrl.h"
#include "Me3d/effect/MexEffectCtrl.h"
#include "WSModelEffect.h"
#include "Me3d/Effect/EffectManager.h"
#include "CfgFileLoader.h"
#include "FuncPerformanceLog.h"
#include "MathLib.h"
#include "DataChunkWriter.h"
#include "FilePath.h"
// #include "Tinyxml/tinyxml.h"
#include "tstring.h"
#include "Me3d/Config.h"
#include "MultiThreadMexLoading.h"
#include "CameraStuntManager.h"
#include "Me3d/Effect/CharEffectContainer.h"
#include "Common.h"
#include "../filepacket/packet_interface.h"
#include "../filepacket//datafile.h"
#include "RapidXml/MeRapidXml.h"
//#include "Launcher/DataLauncher.h"
#include "Mex2LoadReq.h"
#include <MeFoundation/MeLoopThreadMan.h>
#include "wsCamera.h"

//攻击动作的播放时间
#define SPELLACTION_CASTTIME 200
extern BOOL g_bMultiThreadLoadingMex; //多线程加载mex
extern CCameraStuntManager g_CameraStuntManager;		//摄象机特技管理器
extern bool g_bCloseApp;
/////////////////////////
extern D3DXVECTOR3		g_vCurSelectNpcPos;			//当前选中的Npc位置
extern BOOL				g_bHaveSelectNpc;			//是否有选中的Npc



CWSModelEffect::CWSModelEffect(void)
{
	m_nModelID = -1;
}

CWSModelEffect::~CWSModelEffect(void)
{
}

void CWSModelEffect::SetModelID( int val )
{
	m_nModelID = val; 		
}

void CWSModelEffect::Update( DWORD dwTime, D3DXVECTOR3 vPos, float fDistance )
{
	guardfunc;
	if ( m_nCameraShakeType != eNoCameraStunt && dwTime - m_dwBornTime > m_dwShakeStartTime )
	{
		m_dwShakeStartTime = 0xffffffff;
		switch( m_nCameraShakeType )
		{
		case eNormalShake:
			g_CameraStuntManager.StartRandShake( m_Instances[0].vPos, m_fMaxShakeWaveRange, m_fMinShakeWaveRange,
				m_fMaxShakeRange, m_fMinShakeRange, m_dwShakeKeepTime, CCameraStuntManager::LPOT_NORMAL );
			break;
		case eHorizontalShake:
			g_CameraStuntManager.StartRandShake( m_Instances[0].vPos, m_fMaxShakeWaveRange, m_fMinShakeWaveRange,
				m_fMaxShakeRange, m_fMinShakeRange, m_dwShakeKeepTime, CCameraStuntManager::LPOT_HORIZONTAL );
			break;
		case eVerticalShake:
			g_CameraStuntManager.StartRandShake( m_Instances[0].vPos, m_fMaxShakeWaveRange, m_fMinShakeWaveRange,
				m_fMaxShakeRange, m_fMinShakeRange, m_dwShakeKeepTime, CCameraStuntManager::LPOT_VERTICAL );
			break;
		case eViewDirShake:
			g_CameraStuntManager.StartRandShake( m_Instances[0].vPos, m_fMaxShakeWaveRange, m_fMinShakeWaveRange,
				m_fMaxShakeRange, m_fMinShakeRange, m_dwShakeKeepTime, CCameraStuntManager::LPOT_VIEWDIR,getwsCamera()->GetCurCameraZoom() );
			break;
		}
	}

	for( int nInstance = 0; nInstance < m_nNumInstance; nInstance++ )
	{
		Instance* pInstance = &m_Instances[nInstance];
		// added, jiayi, [2009/10/19]
		if( pInstance->bOriginalSize )
		{
			// 这里的数值取自m_fNameShowDistance变量，参考cfg.cpp
			fDistance = 35.f;
		}
		if( D3DXVec3Length( &( pInstance->vPos - vPos ) ) > fDistance )
		{
			pInstance->bOutOfLookerView = TRUE;
		}
		else
		{
			pInstance->bOutOfLookerView = FALSE;
		}

		if( pInstance->dwBornTime > dwTime )
		{
			continue;
		}

		// 已经死亡的instance不用更新
		if( pInstance->bDead  )
		{
			continue;
		}

		// 是否播放结束
		if( !pInstance->bPlayOver )
		{
			if( IsInstancePlayOver( dwTime, pInstance ) )
			{
				pInstance->bPlayOver = TRUE;
				pInstance->dwPlayOverTime = HQ_TimeGetTime();
			}
		}

		// 判定是否死亡
		if( IsInstanceDead( dwTime, pInstance ) )
		{
			pInstance->bDead = TRUE;
			pInstance->dwDeadTime = HQ_TimeGetTime();
			continue;
		}
		UpdateInstance( dwTime, pInstance );
	}
	unguard;

}

void CWSModelEffect::Release()
{
	guardfunc;

	if (!g_bCloseApp)
	{
		CCharEffectContainer* pContainer = GetEffectMgr()->GetCharEffectContainer( m_nEffectQuoterId );
		if (pContainer)
		{
			pContainer->ClearEffectNotDestroy(GetID());
			m_nEffectQuoterId = -1;
			m_pEffectQuoter = 0;
		}

		GetEffectMgr()->ReleaseEffectNotDestroy(GetID());
	}

	if( g_bMultiThreadLoadingMex )
    {
        // modify [8/5/2008 whu]
        MeLoopThreadMan::Instance()->UnRegisterPointer( this );
	}

	for( int nInst = 0; nInst < eMaxInstance; nInst++ )
	{
		Instance* pInstance = &m_Instances[nInst];
		if( pInstance->pEffectCtrl )
		{
			pInstance->pEffectCtrl->Destroy();
			delete pInstance->pEffectCtrl;
			pInstance->pEffectCtrl = NULL;
		}
	}

	delete this;

	unguard;
}

void CWSModelEffect::TryStart()
{
	guardfunc;
	if( g_bMultiThreadLoadingMex )
	{
// 		int	nModelID = GetMexResMgr()->AddExternalFile( m_szModel );
// 		if( nModelID == -1 )
// 		{
// 			assert( false );
// 			return;
// 		}

		/////////////////////////////////////////////
		if( m_dwLife == 0 )
		{
			m_dwLife = m_dwFlyTime + SPELLACTION_CASTTIME;
		}

		float fGlobalScale = GetMe3dConfig()->m_fMdlSpaceScale;
		m_fRadius *= fGlobalScale;

		if( m_nMaxInstance > eMaxInstance )
			m_nMaxInstance = eMaxInstance;

		for( int nInst = 0; nInst < m_nMaxInstance; nInst++ )
		{
			Instance* pInstance = AllocInstance();
			pInstance->fScale *= fGlobalScale;

			if( pInstance->dwLife == 0 )
			{
				pInstance->dwLife = m_dwFlyTime + SPELLACTION_CASTTIME;
			}

			if( pInstance->nActionTime == 0 )
			{
				pInstance->nActionTime = m_dwFlyTime - SPELLACTION_CASTTIME;
			}
// 
// 			if( pInstance->szModel[0] != 0 )
// 			{
// 				int	nMexResID = -1;
// 				nMexResID =  GetMexResMgr()->AddExternalFile( pInstance->szModel );
// 
// 				if( nMexResID == -1 )
// 					continue;

// 				pInstance->pEffectCtrl = MeNew CMexEffectCtrl;
// 				if( pInstance->pEffectCtrl->ChangeModel( nMexResID ) )
// 				{
// 					int nNumFrame = pInstance->pEffectCtrl->GetFrameCount();
// 					m_nOneLoopTime = nNumFrame*ONE_FRAME_TIME;
// 				}
// 			}

			MeLoopThreadMan::Instance()->RegisterPointer( this );
			MeLoopThreadReq* reqb = MeNew ModelEffectReq;
			ModelEffectReq* req = dynamic_cast< ModelEffectReq* >( reqb );
			if( !req )
				return;
			req->m_nObjectType = LoopLoadType::eModelEffect;
			req->m_nModelId = -1;
			memset( req->m_szFileName, 0, sizeof( req->m_szFileName ) );
			if( pInstance->szModel[0] != 0 )
			{
				strcpy(req->m_szFileName, pInstance->szModel);
			}
			else
			{
				strcpy( req->m_szFileName, m_szModel );
			}
			req->m_pModelEffect = this;
			MeLoopThreadMan::Instance()->PostMexLoadingReq( req );
 		}
		return;
	}
	else
	{
		Start();
	}
	unguard;
}

void CWSModelEffect::Start()
{
	/*if(m_nModelID== -1 && m_szModel[0] != 0 )
	{
        m_nModelID = GetMexResMgr()->GetIdByName( m_szModel );
        if( m_nModelID == -1 )
		    m_nModelID = GetMexResMgr()->AddExternalFile( m_szModel );
	}*/
	//if( m_nModelID == -1 )
	//{
	//	assert( false );
	//	return;
	//}
	m_bMexLoaded = TRUE;

	if( m_dwLife == 0 )
	{
		m_dwLife = m_dwFlyTime + SPELLACTION_CASTTIME;
	}

	float fGlobalScale = GetMe3dConfig()->m_fMdlSpaceScale;
	m_fRadius *= fGlobalScale;

	if( m_nMaxInstance > eMaxInstance )
		m_nMaxInstance = eMaxInstance;

	for( int nInst = 0; nInst < m_nMaxInstance; nInst++ )
	{
		/////////////////////old project
		Instance* pInstance = NULL;
		if( g_bMultiThreadLoadingMex )
		{
			pInstance = &m_Instances[nInst];
		}
		else
		{
			pInstance = AllocInstance();
			pInstance->fScale *= fGlobalScale;
		}

		if( !pInstance )
			continue;

		if( pInstance->dwLife == 0 )
		{
			pInstance->dwLife = m_dwFlyTime + SPELLACTION_CASTTIME;
		}

		if( pInstance->nActionTime == 0 )
		{
			pInstance->nActionTime = m_dwFlyTime - SPELLACTION_CASTTIME;
		}

		if( pInstance->pEffectCtrl )
			continue;

		pInstance->pEffectCtrl = MeNew CMexEffectCtrl;

		if (pInstance->szModel[0] != 0)
		{
			m_nModelID = GetMexResMgr()->GetIdByName(pInstance->szModel);
		}
		else
		{
			m_nModelID = GetMexResMgr()->GetIdByName( m_szModel );
		}

		if (m_nModelID == -1)
		{
			m_nModelID = GetMexResMgr()->AddExternalFile( m_szModel );
		}

		if( pInstance->pEffectCtrl->ChangeModel( m_nModelID ) )
		{
			int nNumFrame = pInstance->pEffectCtrl->GetFrameCount();
			m_nOneLoopTime = nNumFrame*ONE_FRAME_TIME;
		}
	}
	return ;
}

typedef bool (*swFileOperation)(LPCTSTR strPath,void* point);
extern bool	EnumFile(LPCTSTR strPath,swFileOperation opt,void* point,bool isRecursive);

bool ReadInEffectSetting(LPCTSTR szFile,void* point)
{
	const char* pos  =  strstr( szFile, _T(".effect")); 
	if(!pos ||  (strlen(szFile) - 7 != pos - szFile )) 
	{
		return false;
	}
// 	char pszFilename[_MAX_PATH + 1] = {0};
// 	sprintf_s(pszFilename, sizeof(pszFilename) - 1, "%s\\%s", pPath, xFindData.cFileName);

	BYTE* pbyBuffer = NULL;
	int nBufferSize = 0;
	if( CModelEffect::Compile( szFile, &pbyBuffer, &nBufferSize ) )
	{
		GetEffectMgr()->AddEffectSetting( szFile, pbyBuffer, nBufferSize );
		return true;
	}
	return false;
}

void CWSModelEffectReader::PreLoadWSModelEffectSetting(bool isCipher)
{
	if (GetEffectMgr()->IsEffectCachePreLoadOK())
	{
		return;
	}
	GetEffectMgr()->SetEffectCachePreLoadOK(true);
	char filename[MAX_PATH] = {0};
	MeSprintf_s( filename, sizeof(filename)/sizeof(char) -1, "%s\\Data\\Effect", GetRootPath());
	bool result = true;
	Common::_tstring sourceFilePath = filename;


	char szFile[_MAX_PATH + 1] = "";
	// 加密格式修正，加载加密格式文件
	if (isCipher)
	{
		sprintf_s(szFile, sizeof(szFile) - 1, "%s\\*", sourceFilePath.toNarrowString().c_str());

		WIN32_FIND_DATA xFindData;
		HANDLE hFile = FindFirstFile(szFile, &xFindData);
		if(hFile != INVALID_HANDLE_VALUE)
		{
			do
			{
				const char* pos  =  strstr( xFindData.cFileName, _T(".effectc")); 
				if(!pos ||  (strlen(szFile) - 8 != pos - szFile )) 
				{
					continue;
				}
				char pszFilename[_MAX_PATH + 1] = {0};
				sprintf_s(pszFilename, sizeof(pszFilename) - 1, "%s\\%s", sourceFilePath.toNarrowString().c_str(), xFindData.cFileName);

				int length = strlen(pszFilename);
				if (length > 1)
				{
					pszFilename[length - 1] = '\0';
				}

				BYTE* pbyBuffer = NULL;
				int nBufferSize = 0;
				if( CModelEffect::Compile( pszFilename, &pbyBuffer, &nBufferSize ) )
				{
					GetEffectMgr()->AddEffectSetting( pszFilename, pbyBuffer, nBufferSize );
				}
				else
				{
					result = false;
				}
			}while(FindNextFile(hFile, &xFindData));                      
			FindClose(hFile);
		}
	}
	else
	{
	/*		MeXmlDocument xMeXml;
			std::string path="..\\data\\effect\\effect.xml";
			if (!xMeXml.LoadFile( path.c_str() ))
			{ return ; }
			MeXmlElement* pRoot = xMeXml.FirstChildElement("mapping");
			if(!pRoot)return ;
			MeXmlElement*pconfiginfo1 = pRoot->FirstChildElement("fileMd5");
			while (pconfiginfo1)
			{
				char * file=(char *)pconfiginfo1->Attribute("fileName");
				if(!file)
				{
					pconfiginfo1= pconfiginfo1->NextSiblingElement();
					continue;
				}
				std::string strname = file;
				int  nfilename,nfilesize;
				pconfiginfo1->QueryIntAttribute("md5",&nfilename);
				pconfiginfo1->QueryIntAttribute("file",&nfilesize);
				
				char szEffectFile[_MAX_PATH + 1] = {0};
				sprintf_s(szEffectFile, sizeof(szEffectFile) - 1, "%s\\%s", GetRootPath(), strname.c_str());
				ReadInEffectSetting(szEffectFile,NULL);
				pconfiginfo1= pconfiginfo1->NextSiblingElement();
			}*/

			//packet * pack=packet_namespace::findpacket("..\\data\\Effect.data");
			packet * pack=packet_namespace::findpacket("Data4.tz");
			if(pack)
			{
				string_hash<fileinfo*> m_areas =pack->GetPacketFileList();
				for (packet::AreaHash::iterator itr = m_areas.begin(); itr != m_areas.end(); ++itr)//只增加有用的
				{
					//检查文件名
					char szEffectFile[_MAX_PATH + 1] = {0};
					sprintf_s(szEffectFile, sizeof(szEffectFile) - 1, "%s\\%s", GetRootPath(), itr->second->area.name);
					ReadInEffectSetting(szEffectFile,NULL);
				}
			}
			else
			{
				EnumFile(sourceFilePath.toNarrowString().c_str(),(swFileOperation)ReadInEffectSetting,NULL,true);
			}
	}

}