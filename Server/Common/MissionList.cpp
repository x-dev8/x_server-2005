#include "MissionList.h"
#include "InfoText.h"

CMissionIntroMgr theMissionIntroMgr;
 
bool CMissionIntroMgr::Load( const char *szFile )
{
    CInfoText InfoReader;
    if( InfoReader.Open( (char*)szFile, 259 ) )
    {
        SMissionStore sms;
        InfoReader.ReadAvailableLine(InfoReader.GetBuffer());
        while( InfoReader.NextKeyword() )
        {
            InfoReader.GetDataStr(InfoReader.GetBuffer(),sms.szScriptVarName);
            InfoReader.NextData(sms.szMissionName,"Name");
            std::string str="";
            while( InfoReader.ReadLine(InfoReader.GetBuffer()) )
            {
                if( strlen(InfoReader.GetBuffer())==0 )
                    break;
                str +=InfoReader.GetBuffer();
            }
            strncpy(sms.szMissionIntro,str.c_str(),256);
            InfoReader.ReadAvailableLine(InfoReader.GetBuffer());
            m_MissionList.push_back(sms);
        }
        InfoReader.Close();
        return true;
    }
    return false;
}


SMissionStore *CMissionIntroMgr::GetMission( char *szName, int index )
{
    if( index >= (int)m_MissionList.size() || index < 0 )
        return NULL;
	char szTemp[128];
	strncpy_s( szTemp, sizeof( szTemp ), m_MissionList[index].szMissionIntro, sizeof( szTemp ) - 1 );
    if( strncmp(m_MissionList[index].szScriptVarName,szName,32) == 0 )
        return &m_MissionList[index];
    else
        return NULL;
}
