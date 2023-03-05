/********************************************************************
	Filename: 	MapArea.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_MAPAREA_H__
#define __COMMON_MAPAREA_H__

#pragma once

#include "MeRTLibs.h"
#include "IOXMLObject.h"
#include "StageDataLoader.h"
#include "Mutex.h"

// 区域
struct SArea 
{
#ifdef _CLIENT_
	struct ActionData
	{
		std::string strAnimName;    // 动作名称
		short shProbability;        // 概率
		ActionData()
		{
			strAnimName.clear();
			shProbability = 0;
		}
	};
	struct TalkData
	{
		int shStringId;       // 对应
		short shProbability;    // 概率
		TalkData()
		{
			shStringId = 0;
			shProbability = 0;
		}
	};
	struct AreaActionData
	{
		short shId;
		short shElapseTime;
		short shNextId;         // 完成后下个ActionData对应shId
		std::vector<ActionData> vctActions; // 动作列表
		std::vector<TalkData> vctTalks;     // 说话列表
		AreaActionData()
		{
			vctActions.clear();
			vctTalks.clear();
			shId = 0;
			shElapseTime = 0;
			shNextId = 0;
		}
	};
	std::vector<AreaActionData> vctActionData;
#endif
    std::string m_strName;
    RECT        m_rcArea;        // 格子坐标
    int         m_istep;
    int         m_nPKMode;
	bool        m_bCanDuel;
    //bool        m_bMapGuildPK;
    bool        m_bPrivateShop;  // 怪物是否随机范围刷出 为真则为随机，为否则定点刷
    std::string m_strEnterScript;
    std::string m_strLeaveScript;
    SArea()
    {
        m_strName.clear();
        memset( &m_rcArea, NULL, sizeof(RECT) );
        m_istep = 0;
        m_nPKMode = 0;
		m_bCanDuel = 1;
        //m_bMapGuildPK=false;
        m_bPrivateShop = false;
        m_strEnterScript.clear();
        m_strLeaveScript.clear();
#ifdef _CLIENT_
		vctActionData.clear();
#endif
    }
};

// 区域管理器
class CMapAreaManager
{
public:
    CMapAreaManager();
    virtual ~CMapAreaManager();

    int AddArea( SArea sa );
    int AddArea( const char *szName, LPRECT rect );
    int AddArea( const char *szName, LPRECT rect, int istep );

    void loadXML( CStageDataLoader* pStageDataLoader, XMLElement* element, int nZoneNumber );
    void exportXML( CStageDataLoader* pStageDataLoader, int i );

    bool loadXMLSettings( const char *path  );
    bool exportXMLSettings( const char* xmlPath );

    int    GetMaxArea();
    SArea* GetAreaByID( int id );
    SArea* GetAreaByName( const char *szName );
    void   Clear();

#ifdef _CLIENT_
	void LoadMonserAction(XMLElement *element,SArea &area);
#endif
public:
    std::vector< SArea > m_vectorAreaStore;
    std::map< std::string, int > m_mapAreaStore;

private:
    CStageDataLoader* m_pStageDataLoader;
    CSemiAutoIntLock  _lock;
};

#endif // __COMMON_MAPAREA_H__
