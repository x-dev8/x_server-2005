#include "Influence.h"
#include "SlkReader.h"
#include "NewWithDebug.h"

using std::string;
using std::vector;
//////////////////////////////////////////////////////////////////////
// Class CInfluence
CInfluence::CInfluence()
{
	m_vFriendList.clear();
	m_vFriendList.resize(MaxInfluence, 1);
}

CInfluence::~CInfluence()
{
	m_vFriendList.clear();
}

// 初始化
void CInfluence::Init(int nID, string strName, int nRight, int nKill, int nHuiren, int nMojia, int nNoGuild, int nGuard, int nAttack, int nNormal, string strFriend)
{
	m_nID = nID;
	m_strName = strName;

    m_nRight = nRight;
    m_nKill = nKill;
    m_nHuiren = nHuiren;
    m_nMojia = nMojia;
    m_nNoGuild = nNoGuild;
    m_nCityGuard = nGuard;
    m_nCityAttack = nAttack;
    m_nCityNormal = nNormal;

	// 用传入的strFriend字符串初始化友好度列表
	string::size_type stStartPos = 0; //分割字符串起始位置
	string::size_type stEndPos = 0; //分割字符串结束位置
	int nValue = 0;						
	int nCnt = 0;

	stEndPos = strFriend.find(",", stStartPos);
	while (TRUE)
	{
		nValue = atoi( strFriend.substr(stStartPos, stEndPos).c_str() );
		m_vFriendList[nCnt] = nValue;
		nCnt++;
		
		stStartPos = stEndPos+1;
		stEndPos = strFriend.find(",", stStartPos);
		if (stEndPos == string::npos)
		{
			nValue = atoi( strFriend.substr(stStartPos, strFriend.length()).c_str() );
			m_vFriendList[nCnt] = nValue;
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Class CInfluenceManager
CInfluenceManager::CInfluenceManager()
{
	m_vInfluenceList.clear();
}

CInfluenceManager::~CInfluenceManager()
{
	// Delete 所有阵营指针
	if( !m_vInfluenceList.empty() )
	{
		std::vector<CInfluence*>::iterator FreeIt;
		while(m_vInfluenceList.empty())
		{
			FreeIt = m_vInfluenceList.end();

            CNewWithDebug<CInfluence>::Free(*FreeIt);

			m_vInfluenceList.pop_back();
		}
	}
	m_vInfluenceList.clear();
}

// 从slk配置文件载入各阵营
bool CInfluenceManager::InitFromSlkFile(const char* szFile)
{
	CSlkReader reader;
	if( !reader.ReadFromFile(szFile) )
	{
		return false;
	}
	
	int iRet = 0;
	int iRow = 2;
	int iCol = 1;

	int nID = 0;
	string strName;
	int nRight = 1;
    int nKill = 1;
    int nHuiren = 1;
    int nMojia = 1;
    int nNoGuild = 1;
    int nGuard = 1;
    int nAttack = 1;
    int nNormal = 1;
	string strFriend;

	while( CSlkReader::ret_readover != (iRet = reader.GotoNextLine(iRow ++)) )
	{
        iCol = 1;

		if(CSlkReader::ret_nothisline == iRet)
		{
			continue;
		}

		//阵营编号
		if( !reader.GetIntField( iCol ++,nID ) )
		{
			continue;
		}

		//阵营名称
		if( !reader.GetStringField(iCol ++, strName) )
		{
			continue;
		}

        //阵营友好度列表
        if( !reader.GetStringField(iCol ++, strFriend) )
        {
            continue;
        }

        //与蓝名关系
        if( !reader.GetIntField(iCol ++, nRight) )
        {
            continue;
        }

        //与红名关系
        if( !reader.GetIntField(iCol ++, nKill) )
        {
            continue;
        }

        //与会任关系
        if( !reader.GetIntField(iCol ++, nHuiren) )
        {
            continue;
        }

        //与墨家关系
        if( !reader.GetIntField(iCol ++, nMojia) )
        {
            continue;
        }

        //与无公会玩家关系
        if( !reader.GetIntField(iCol ++, nNoGuild) )
        {
            continue;
        }

        //与平民玩家关系
        if( !reader.GetIntField(iCol ++, nNormal) )
        {
            continue;
        }

        //与守城玩家关系
        if( !reader.GetIntField(iCol ++, nGuard) )
        {
            continue;
        }

        //与攻城玩家关系
        if( !reader.GetIntField(iCol ++, nAttack) )
        {
            continue;
        }

        CInfluence* pNewInfluence =  CNewWithDebug<CInfluence>::Alloc(1, "CInfluenceManager::InitFromSlkFile中创建CInfluence");
		pNewInfluence->Init(nID, strName, nRight, nKill, nHuiren, nMojia, nNoGuild, nGuard, nAttack, nNormal, strFriend);

		m_vInfluenceList.push_back(pNewInfluence);
	}
	return true;
}

// 从ID获取阵营指针
CInfluence* CInfluenceManager::GetInfluenceByID(int nID)
{
	std::vector<CInfluence*>::iterator ItGet;
	for(ItGet = m_vInfluenceList.begin(); ItGet != m_vInfluenceList.end(); ItGet++)
	{
		if( (*ItGet)->GetID() == nID )
		{
			return (*ItGet);
		}
	}
	return NULL;
}

// 从名字获取阵营指针
CInfluence* CInfluenceManager::GetInfluenceByName(const std::string& strName)
{
	std::vector<CInfluence*>::iterator ItGet;
	for(ItGet = m_vInfluenceList.begin(); ItGet != m_vInfluenceList.end(); ++ItGet)
	{
		if( (*ItGet)->GetName().compare(strName) == 0 )
		{
			return (*ItGet);	
		}
	}
	return NULL;
}