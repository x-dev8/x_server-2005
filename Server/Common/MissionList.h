/********************************************************************
    Filename:     MissionList.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __MISSIONLIST_H__
#define __MISSIONLIST_H__

#include "MeRTLibsServer.h"

struct SMissionStore
{
    char szScriptVarName[32];
    char szMissionName[64];
    char szMissionIntro[256];
};

class CMissionIntroMgr
{
public:
    CMissionIntroMgr() {}
    virtual ~CMissionIntroMgr() {}
    
    SMissionStore *GetMission(char *szName,int index);
    bool Load( const char *szFile );

protected:

    std::vector<SMissionStore> m_MissionList;

};

extern CMissionIntroMgr theMissionIntroMgr;

#endif // __MISSIONLIST_H__