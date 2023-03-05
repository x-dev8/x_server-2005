#include "SessionManager.h"

SessionManager& SessionManager::GetInstance()
{
    static SessionManager instance;
    return instance;
}

SessionManager::SessionManager()
{
}

void SessionManager::_Release()
{
}

unsigned long SessionManager::CreateTeamSession()
{
	return HQ_TimeGetTime();		//直接用时间来得到sessionid
}

unsigned long SessionManager::GetTeamSessionId(unsigned long dwPlayerDataBaseId)
{
	PlayerTeamSessionIter iter = m_mapPlayerTeamSession.find(dwPlayerDataBaseId);
	if (iter == m_mapPlayerTeamSession.end())
	{
		return 0;
	}

	return iter->second;
}

void SessionManager::GetTeamSessionMember(unsigned long dwSessionId, std::vector<unsigned long>& vecSessionMember)
{
	vecSessionMember.clear();

	TeamSessionPlayerIter iter = m_mapTeamSessionPlayer.find(dwSessionId);
	if(iter != m_mapTeamSessionPlayer.end())
	{
		vecSessionMember = iter->second;
	}
}

bool SessionManager::AddPlayerTeamSession(unsigned long dwSessionId, unsigned long dwPlayerDataBaseId)
{
	if (dwSessionId < 0 || dwPlayerDataBaseId < 0) { return false; }

	PlayerTeamSessionIter iter = m_mapPlayerTeamSession.find(dwPlayerDataBaseId);
	if (iter != m_mapPlayerTeamSession.end())
	{
		if (dwSessionId != iter->second)
		{
			iter->second = dwSessionId;
			return true;
		}

		return false;
	}

	m_mapPlayerTeamSession.insert(make_pair(dwPlayerDataBaseId, dwSessionId));
	return true;
}

bool SessionManager::RemovePlayerTeamSessionBySessionId(unsigned long dwSessionId)
{
	for (PlayerTeamSessionIter iter = m_mapPlayerTeamSession.begin(); iter != m_mapPlayerTeamSession.end(); )
	{
		if (iter->second == dwSessionId)
		{
			iter = m_mapPlayerTeamSession.erase(iter);
		}
		else
		{
			++iter;
		}
	}	

	return true;
}

bool SessionManager::RemovePlayerTeamSessionByPlayerDataBaseId(unsigned long dwPlayerDataBaseId)
{
	PlayerTeamSessionIter iter = m_mapPlayerTeamSession.find(dwPlayerDataBaseId);
	if (iter != m_mapPlayerTeamSession.end())
	{
		m_mapPlayerTeamSession.erase(iter);

		return true;
	}

	return false;
}


bool SessionManager::AddTeamSession(unsigned long dwSessionId, unsigned long dwPlayerDataBaseId)
{
	if (dwSessionId < 0 || dwPlayerDataBaseId < 0) { return false; }
	TeamSessionPlayerIter iter = m_mapTeamSessionPlayer.find(dwSessionId);
	if (iter == m_mapTeamSessionPlayer.end())
	{
		vector<unsigned long> vecPlayerDataBase;
		vecPlayerDataBase.clear();
		vecPlayerDataBase.push_back(dwPlayerDataBaseId);

		m_mapTeamSessionPlayer.insert(make_pair(dwSessionId, vecPlayerDataBase));
	}
	else
	{
		std::vector<unsigned long>::iterator viter = find(iter->second.begin(), iter->second.end(), dwPlayerDataBaseId);
		if (viter != iter->second.end())
		{
			return false;
		}
		iter->second.push_back(dwPlayerDataBaseId);
	}

	AddPlayerTeamSession(dwSessionId, dwPlayerDataBaseId);

	return true;
}

bool SessionManager::RemoveTeamSessionBySessionId(unsigned long dwSessionId)
{
	TeamSessionPlayerIter iter = m_mapTeamSessionPlayer.find(dwSessionId);
	if (iter != m_mapTeamSessionPlayer.end())
	{
		m_mapTeamSessionPlayer.erase(iter);

		RemovePlayerTeamSessionBySessionId(dwSessionId);
		return true;
	}

	return false;
}

bool SessionManager::RemoveTeamSessionByPlayerDataBaseId(unsigned long dwSessionId, unsigned long dwPlayerDataBaseId)
{
	TeamSessionPlayerIter iter = m_mapTeamSessionPlayer.find(dwSessionId);
	if (iter == m_mapTeamSessionPlayer.end())
	{
		return false;
	}

	std::vector<unsigned long>::iterator viter = find(iter->second.begin(), iter->second.end(), dwPlayerDataBaseId);
	if (viter == iter->second.end())
	{
		return false;
	}

	RemovePlayerTeamSessionByPlayerDataBaseId(dwPlayerDataBaseId);
	iter->second.erase(viter);

	return true;
}

void SessionManager::ChangeTeamHeader(unsigned long dwSessionId, unsigned long dwDataBaseId)
{
    if (dwSessionId == 0 || dwDataBaseId == 0) { return; }

    TeamSessionPlayerIter iter = m_mapTeamSessionPlayer.find(dwSessionId);
    if(iter == m_mapTeamSessionPlayer.end())
    {
        return;
    }
    
    if (iter->second.empty()) { return; }

    std::vector<unsigned long>::iterator viter = iter->second.begin();
    std::vector<unsigned long>::iterator vend = iter->second.end();

    unsigned long dwOldTeamHeader = *viter;             //原先的队长
    *viter = dwDataBaseId;

    ++viter;            //从第2个开始找
    for ( ; viter != vend; ++viter)
    {
        if (*viter == dwDataBaseId)
        {
           *viter = dwOldTeamHeader;
           break;
        }
    }

}