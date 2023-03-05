#ifndef __CENTERSERVER_SESSIONMANAGER_H__
#define __CENTERSERVER_SESSIONMANAGER_H__

#pragma once

#include "MeRTLibsServer.h"
#include "Session.h"
#include "StaticArray.h"

class SessionManager
{
public:
    static SessionManager& GetInstance();

	unsigned int TeamSessionCount();
	unsigned long CreateTeamSession();
	unsigned long GetTeamSessionId(unsigned long dwPlayerDataBaseId);
	void GetTeamSessionMember(unsigned long dwSessionId, std::vector<unsigned long>& vecSessionMember);
	bool AddPlayerTeamSession(unsigned long dwSessionId, unsigned long dwPlayerDataBaseId);
	bool RemovePlayerTeamSessionBySessionId(unsigned long dwSessionId);
	bool RemovePlayerTeamSessionByPlayerDataBaseId(unsigned long dwPlayerDataBaseId);
	bool AddTeamSession(unsigned long dwSessionId, unsigned long dwPlayerDataBaseId);
	bool RemoveTeamSessionBySessionId(unsigned long dwSessionId);
	bool RemoveTeamSessionByPlayerDataBaseId(unsigned long dwSessionId, unsigned long dwPlayerDataBaseId);

    void ChangeTeamHeader(unsigned long dwSessionId, unsigned long dwDataBaseId);            //更换队长

protected:
    SessionManager();
    SessionManager( const SessionManager& ){}
    SessionManager& operator=( const SessionManager& ){}   
    
    void _Release();

private:
    typedef std::map< unsigned long, Session* > SessionContainer;

    SessionContainer            _sessions;
	//CStaticArray<unsigned long> m_saID; // Id

	std::map<unsigned long, std::vector<unsigned long > > m_mapTeamSessionPlayer;  //会话和玩家的对应关系
	std::map<unsigned long, unsigned long> m_mapPlayerTeamSession;					//玩家与会话的对应关系

public:
	typedef std::map<unsigned long, std::vector<unsigned long> >::iterator TeamSessionPlayerIter;
	typedef std::map<unsigned long, unsigned long>::iterator PlayerTeamSessionIter;

};

inline unsigned int SessionManager::TeamSessionCount()
{
	return static_cast<unsigned int>(m_mapTeamSessionPlayer.size());
}

#endif // __CENTERSERVER_SESSIONMANAGER_H__
