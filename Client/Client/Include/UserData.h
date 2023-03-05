#pragma once
#include <windows.h>
#include "GlobalDef.h"

#define MAXSUITNUM 5  //最大套装数量

class CUserData : public MeCommonAllocObj<CUserData>
{
public://public static functions	
    static CUserData*   Instance();	
    static bool		    Destroy();

public:
            CUserData(void);
            ~CUserData(void){};
    
    BOOL    WriteLoginData();
    BOOL    LoadLoginData();
	BOOL	WriteViewSet();
	BOOL	LoadViewSet();//2.5d or 3d
    BOOL    CreateUserData();
    BOOL    ReadUserData();
    const char* GetUserDataPath();
	const char* GetAccountDataPath();

    void    SetAccountString(const char* string) { if(string) strncpy(m_strAccount, string, 64); }
    void    SetArea(const char* string/*, int id*/) { if(string) strncpy(m_strArea, string, 64); }
    void    SetServerString(const char* string) { if(string) strncpy(m_strServer, string, 64); }
    void    SetRoleString(const char* string) { if(string) strncpy(m_strRole, string, 64); }

    const char* GetAccount() { return m_strAccount; }
    const char* GetArea() { return m_strArea; }
    const char* GetServer() { return m_strServer; }
    const char* GetRole() { return m_strRole; }

	void SetViewSet( int nViewSet ){ m_nViewSet = nViewSet; }
	int GetViewSet(){ return m_nViewSet; }

    void SetSoftKeyboard( bool bEnable ) { m_bSoftKeyboard = bEnable; }
    bool IsSoftKeyboardEnable() { return m_bSoftKeyboard; }

    void InitSuit();
    bool SaveSuit();
    bool ReadSuit();
    bool AddSuit(int nIndex);
    void ClearSuit(int nIndex);
    __int64 GetGUID(int nIndex,int nPart){return m_SuitData[nIndex].m_ItemGuid[nPart];}
    int   GetSuitIndex(int nIndex);
    void  SetSuitTip(int nIndex,const char* pszWord);
    const char* GetSuitTip(int nIndex);
    bool  IsShowSuitUI(){return m_suitSetting.bSuitShow;}
    int   GetSuitLastIndex(){return m_suitSetting.nLastIndex;}

    void SetShowSuitUI(bool bShow){m_suitSetting.bSuitShow = bShow;}
    void SetSuitLastIndex(int nIndex){m_suitSetting.nLastIndex = nIndex;}
#ifdef _DEBUG
    void DebugInfo();
#endif

    //struct SSuit
    //{
    //   int     m_nIndex;    //第几套
    //   __int64 m_ItemGuid[EPT_TotalWearCount];  //当前套装
    //};

	//add by yanli  2010-9-27
	struct SSuit
	{
		__int64 m_ItemGuid[EEquipPartType_MaxEquitPart];  //当前套装
	};

    struct SSuitSetting 
    {
        bool bSuitShow;  //上次界面是否关闭
        int nLastIndex;  //上次退出时选择了那个界面 
        SSuitSetting()
        {
            bSuitShow = false;
            nLastIndex = 0;
        }
    };

protected://protected static members
    static CUserData* ms_pThis;

    char    m_strAccount[65];
    char    m_strArea[65];
    char    m_strServer[65];
    char    m_strRole[65];
    char    m_strUserDataPath[MAX_PATH];
	char    m_strAccountDataPath[MAX_PATH];
	int		m_nViewSet;
    bool    m_bSoftKeyboard;

    SSuitSetting m_suitSetting;
    SSuit    m_SuitData[MAXSUITNUM];
};