#include "WaitReleaseConnect.h"
#include "FuncPerformanceLog.h"

const DWORD RELEASE_DELAY = 1000;

CWaitReleaseConnect& GettheWaitReleaseConnect()
{
    static CWaitReleaseConnect s_theReleaseConnect;
    return s_theReleaseConnect;
}

CWaitReleaseConnect::CWaitReleaseConnect()
{
}

CWaitReleaseConnect::~CWaitReleaseConnect()
{
}

bool CWaitReleaseConnect::AddReleaseConnect(/*IMeConnector*/Socketer* pConnetor, DWORD dwDelayTime)
{
    if (!pConnetor)
        return false;

    RELEASECONNECTINFO info;
    info.pConnetor = pConnetor;
    info.dwDelayTime = HQ_TimeGetTime() + dwDelayTime;
    CSALocker locker(this);
    m_conlist.push_back(info);
    return true;
}

unsigned int CWaitReleaseConnect::GetReleaseConnectListSize() const
{
    return static_cast<unsigned int>(m_conlist.size());
}

void CWaitReleaseConnect::Run()
{
    static DWORD dwLastReleaseTime = HQ_TimeGetTime();
    if (HQ_TimeGetTime() - dwLastReleaseTime >RELEASE_DELAY)
    {
        std::list<RELEASECONNECTINFO> tmplist;

        {
            CSALocker locker(this);
            tmplist = m_conlist;
            m_conlist.clear();
        }

        while (!tmplist.empty())
        {
            RELEASECONNECTINFO info = tmplist.front();

            if (HQ_TimeGetTime() >= info.dwDelayTime)
            {
                if (info.pConnetor)
                {
					Socketer_release(info.pConnetor);
                    /*GetMeNetwork().ReleaseMeConnector( info.pConnetor->GetKey());*/
                }
            }
            else
            {
                CSALocker locker(this);
                m_conlist.push_back(info);
            }

            tmplist.pop_front();
        }
        dwLastReleaseTime = HQ_TimeGetTime();
    }
}

void CWaitReleaseConnect::UnInit()
{
    while (!m_conlist.empty())
    {
        RELEASECONNECTINFO& info = m_conlist.front();
        /*IMeConnector*/Socketer* pCon = info.pConnetor;
        if (pCon != NULL)
        {
			Socketer_release(pCon);
            /*GetMeNetwork().ReleaseMeConnector( info.pConnetor->GetKey());*/
        }
        m_conlist.pop_front();
    }
}
