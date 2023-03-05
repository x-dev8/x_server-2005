/********************************************************************
	Filename: 	SystemConfig.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_SYSTEMCONFIG_H__
#define __COMMON_SYSTEMCONFIG_H__

#pragma once

#include "MeRTLibs.h"
#include "Dxsdk/D3DX9Math.h"
#include "IOXMLObject.h"

using namespace std;

class CProfessionInfo
{
public:
    CProfessionInfo()
    {
        nID = -1;
        m_strProShow = "NULL";
        m_strCreateShow = "NULL";
        m_strNote = "NULL";
    }
public:
    int			nID;
    string		m_strProShow;
    string		m_strCreateShow;
    string		m_strNote;
};

class CWindowConfig
{
public:
    CWindowConfig()
    {
        bFullSrceen = false;
        nPosX		= 0;
        nPosY		= 0;
        nWidth		= 800;
        nHeight		= 600;
        m_strCaption = "NoCatpion";
    }
public:
    string		m_strCaption;
    bool		bFullSrceen;
    int			nPosX;
    int			nPosY;
    int			nWidth;
    int			nHeight;
};
//
//class CCameraConfig
//{
//public:
//	CCameraConfig():m_fDist(0), m_fRotateX(0), m_vPos(0,0,0), m_bRenderInfo(TRUE)
//	{
//		
//	}
//public:
//	FLOAT		m_fDist;
//	FLOAT		m_fRotateX;
//	D3DXVECTOR3	m_vPos;
//	BOOL		m_bRenderInfo;	//是否显示渲染信息
//	BOOL		m_bContrl;		//是否能控制摄像机
//};
class CViewportConfig
{
public:
    CViewportConfig():m_fX(0.0f),m_fY(0.0f),m_fWidth(0.0f),m_fHeight(0.0f)
    {
		m_fRoleScaleMale = 1.0f;
		m_fRoleScaleFemale = 1.0f;
    }
public:
    FLOAT		m_fX;
    FLOAT		m_fY;
    FLOAT		m_fWidth;
    FLOAT		m_fHeight;
	FLOAT		m_fRoleScaleMale;
	FLOAT		m_fRoleScaleFemale;
};

class CPackConfig
{
public:
    CPackConfig():nPackType(0),nPackCnt(0)
    {
    }
    INT nPackType;
    INT nPackCnt;
};

struct RankDescription
{
	std::string type;
	std::string description;
};

class CSystemConfig: public IOXMLObjectInstance
{
public:
    enum
    {
        eModelPack,
        eSlkPack,
        eTexturesPack,
        eWorldPack,
        eUIPack,		
        eMusicPack,
        eSoundPack,
        eEffectPack,
        eCfgPack,
        eMaxPack
    };
    CSystemConfig(void);
    ~CSystemConfig(void);
public:
    virtual bool loadXMLSettings(const char *path  );
    virtual bool loadXMLSettings(XMLElement *element);

    virtual bool exportXMLSettings(std::ofstream &xmlFile  );
    virtual bool exportXMLSettings(const char* xmlPath);
public:
    CProfessionInfo*		GetProessionInfoFromID(int nID );
    //	CCameraConfig*			GetSelectUICamera() {return &m_SelUICamera;}
    FLOAT					GetUIRoleScale()	{ return m_fSelectUIRoleScale;}
	CViewportConfig*		GetPackViewportCfg() { return &m_ViewportCfg; }
	CViewportConfig*		GetTargetPackViewportCfg() { return &m_targetViewportCfg; }
    int						GetProfessionCount();
    int						GetPackSize()		{ return m_vtPackConfig.size(); }
    int						GetPackCnt( INT nType )		
    { 
        if( m_vtPackConfig.size() > 0 )
            return m_vtPackConfig[nType].nPackCnt; 
        return 0;
    }

	const RankDescription& GetRankDescription(const std::string& type)
	{
		return m_rankDescriptions[type];
	}

public:
    vector<CProfessionInfo>	m_vtProfession;
    vector<CPackConfig>		m_vtPackConfig;
    vector<std::string>		m_vtPackType;
    CWindowConfig			m_WindowsConifg;
    //	CCameraConfig			m_SelUICamera;
	CViewportConfig			m_ViewportCfg;
	CViewportConfig			m_targetViewportCfg;
    FLOAT					m_fSelectUIRoleScale;

    DWORD					m_dwTipColor0;
    DWORD					m_dwTipColor1;

    DWORD 					m_dwWhite;
    DWORD 					m_dwGrayed;
    DWORD 					m_dwBlue;
    DWORD 					m_dwGreen;
    DWORD 					m_dwGold;
    DWORD 					m_dwYellow;
    DWORD 					m_dwRed;
    DWORD                   m_dwPurple/*= 0xFF800080*/;

    D3DLIGHT9				m_PackRoleLight;

 /*   BOOL					m_bLinkPage;
    ///char					m_szLinkWeb[MAX_PATH];
    std::string				m_LinkWeb;*/

	std::map<std::string, RankDescription> m_rankDescriptions;
};

extern CSystemConfig* GetSystemConfig();
extern CSystemConfig gs_Config;

#endif // __COMMON_SYSTEMCONFIG_H__
