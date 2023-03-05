#include "WaitReleaseStage.h"

const DWORD RELEASE_DELAY = 1000;

CWaitReleaseStage& GettheWaitReleaseStage()
{
    static CWaitReleaseStage s_stagelist;
    return s_stagelist;
}

CWaitReleaseStage::CWaitReleaseStage()
{
}

CWaitReleaseStage::~CWaitReleaseStage()
{
    while (!m_stagelist.empty())
    {
        SReleaseStageInfo& info = m_stagelist.front();
        GameStage* pStage = info.pStage;
        if (pStage != NULL)
        { pStage->Release(); }
        m_stagelist.pop_front();
    }
}

bool CWaitReleaseStage::AddReleaseStage( GameStage* pStage, DWORD dwDelayTime)
{
    if (pStage == NULL)
    { return false; }

    SReleaseStageInfo info;
    info.pStage = pStage;
    info.dwDelayTime = HQ_TimeGetTime() + dwDelayTime;
    CSALocker locker( this );
    m_stagelist.push_back(info);
    return true;
}

uint32 CWaitReleaseStage::GetReleaseStageListSize() const
{
    return static_cast<uint32>(m_stagelist.size());
}
// 如果多线程的话 被释放的时候要确保那个线程确实是关闭了..才行
void CWaitReleaseStage::Run()
{
    static uint32 dwLastReleaseTime = HQ_TimeGetTime();

    if ( !GameTime::IsPassCurrentTime( dwLastReleaseTime, RELEASE_DELAY ))
    { return; }

    ReleaseStageInfoContainer tmplist;

    {
        CSALocker locker(this);
        tmplist = m_stagelist;
        m_stagelist.clear();
    }

    while (!tmplist.empty())
    {
        SReleaseStageInfo info = tmplist.front();
        if (HQ_TimeGetTime() >= info.dwDelayTime)
        {
            if (info.pStage != NULL)
            {  info.pStage->Release(); }
        }
        else
        {
            CSALocker locker( this );
            m_stagelist.push_back(info);
        }
        tmplist.pop_front();
    }

    dwLastReleaseTime = HQ_TimeGetTime();
}
