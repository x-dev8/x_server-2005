#include "UserLoger.h"
#include "Mutex.h"
#include "Configure.h"
#include "ResourcePath.h"
#include <process.h>
#include <cassert>

CPlayerLogger& GetthePlayerLogger()
{
	static CPlayerLogger s_logger;
	return s_logger;
}

CPlayerLogger::CPlayerLogger()
{
	_beginthread(CPlayerLogger::SaveThread, 0, this);
}

CPlayerLogger::~CPlayerLogger()
{
}

bool CPlayerLogger::PushLogger(std::string& strLog)
{
	CSALocker locker(this);
	if (m_LogStr.size() >= MAX_LOG_NUM)
	{
		return false;
	}
	m_LogStr.push_back(strLog);
    return true;
}
bool CPlayerLogger::PopLoggers(vecLogStr& vecStrLog)
{
	CSALocker locker(this);
	vecStrLog = m_LogStr;
	m_LogStr.clear();
	return true;
}

void CPlayerLogger::SaveThread(void* pLogger)
{
	if (pLogger != NULL)
	{
		CPlayerLogger* pPlayerLogger = static_cast<CPlayerLogger*>(pLogger);

        // 第一级 Output 目录
		/*char LogDirectory[256] = {0};
		sprintf_s( LogDirectory, sizeof(LogDirectory)-1, GAMESERVER_USERLOG, g_Cfg.szGameServerName);*/
        _mkdir(OUTPUT_DIRECTORY);

        // 第二级 玩家游戏log目录
        char szPlayerGameLogFolder[MAX_PATH] = {0};
        ::memset( szPlayerGameLogFolder, 0, MAX_PATH);
        _snprintf(szPlayerGameLogFolder, sizeof(szPlayerGameLogFolder)-1, PLAYER_LOGDIRECTORY_FORMAT, OUTPUT_DIRECTORY, g_Cfg.dwServerID, g_Cfg.dwAreaId );
		_mkdir(szPlayerGameLogFolder);

		while (true)
		{
			static FILE* fLog = NULL;
			static DWORD dwTime = 0;
			if (::GetTickCount() - dwTime >= 60*1000)
			{
                char szLogFolder[MAX_PATH];
				char szFile[MAX_PATH];
				char szDate[128];
				char szTime[128];
                int nRet = 0;
				
                // 得到时间
				SYSTEMTIME systime;
				GetLocalTime(&systime);
				_snprintf(szDate, sizeof(szDate)-1, "%04d-%02d-%02d", systime.wYear, systime.wMonth, systime.wDay);
				_snprintf(szTime, sizeof(szTime)-1, "%02d-%02d", systime.wHour, systime.wMinute);

                // 第三级 时间目录
				_snprintf(szLogFolder, sizeof(szLogFolder)-1, "%s\\%s", szPlayerGameLogFolder, szDate);
				_mkdir(szLogFolder);

                // 第四级 log文件
				_snprintf(szFile, sizeof(szFile)-1, "%s\\%s.log", szLogFolder, szTime);

				if (fLog != NULL)
				{
					fclose(fLog);
					fLog = NULL;
				}

				fLog = fopen(szFile, "at");
				dwTime = ::GetTickCount();
			}

			vecLogStr logVS;
			pPlayerLogger->PopLoggers(logVS);
			for ( int i = 0; i < logVS.size(); ++i )
			{
				if (fLog != NULL)
				{
					fwrite(logVS[i].c_str(), logVS[i].size(), 1, fLog);
				}
			}
			
			Sleep(1000);
		}
	}
}