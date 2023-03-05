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

// ��ʼ��
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

	// �ô����strFriend�ַ�����ʼ���Ѻö��б�
	string::size_type stStartPos = 0; //�ָ��ַ�����ʼλ��
	string::size_type stEndPos = 0; //�ָ��ַ�������λ��
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
	// Delete ������Ӫָ��
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

// ��slk�����ļ��������Ӫ
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

		//��Ӫ���
		if( !reader.GetIntField( iCol ++,nID ) )
		{
			continue;
		}

		//��Ӫ����
		if( !reader.GetStringField(iCol ++, strName) )
		{
			continue;
		}

        //��Ӫ�Ѻö��б�
        if( !reader.GetStringField(iCol ++, strFriend) )
        {
            continue;
        }

        //��������ϵ
        if( !reader.GetIntField(iCol ++, nRight) )
        {
            continue;
        }

        //�������ϵ
        if( !reader.GetIntField(iCol ++, nKill) )
        {
            continue;
        }

        //����ι�ϵ
        if( !reader.GetIntField(iCol ++, nHuiren) )
        {
            continue;
        }

        //��ī�ҹ�ϵ
        if( !reader.GetIntField(iCol ++, nMojia) )
        {
            continue;
        }

        //���޹�����ҹ�ϵ
        if( !reader.GetIntField(iCol ++, nNoGuild) )
        {
            continue;
        }

        //��ƽ����ҹ�ϵ
        if( !reader.GetIntField(iCol ++, nNormal) )
        {
            continue;
        }

        //���س���ҹ�ϵ
        if( !reader.GetIntField(iCol ++, nGuard) )
        {
            continue;
        }

        //�빥����ҹ�ϵ
        if( !reader.GetIntField(iCol ++, nAttack) )
        {
            continue;
        }

        CInfluence* pNewInfluence =  CNewWithDebug<CInfluence>::Alloc(1, "CInfluenceManager::InitFromSlkFile�д���CInfluence");
		pNewInfluence->Init(nID, strName, nRight, nKill, nHuiren, nMojia, nNoGuild, nGuard, nAttack, nNormal, strFriend);

		m_vInfluenceList.push_back(pNewInfluence);
	}
	return true;
}

// ��ID��ȡ��Ӫָ��
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

// �����ֻ�ȡ��Ӫָ��
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