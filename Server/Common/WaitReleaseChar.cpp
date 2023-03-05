#include "WaitReleaseChar.h"
#include "BaseCharacter.h"

const DWORD RELEASE_DELAY = 1000;

CWaitReleaseChar& GettheWaitReleaseChar()
{
    static CWaitReleaseChar s_charlist;
    return s_charlist;
}

CWaitReleaseChar::CWaitReleaseChar()
{
}

CWaitReleaseChar::~CWaitReleaseChar()
{
    {
        CSALocker locker(this);
        while (!m_charlist.empty())
        {
            RELEASECHARINFO& info = m_charlist.front();
            BaseCharacter* pChar = info.pChar;
            if (pChar != NULL)
            {
                pChar->Release();
            }
            m_charlist.pop_front();
        }
    }
}

bool CWaitReleaseChar::AddReleaseChar(BaseCharacter* pChar)
{
    if (pChar == NULL)
        return false;

    RELEASECHARINFO info;
    info.pChar = pChar;
    info.dwDelayTime = HQ_TimeGetTime();

    CSALocker locker(this);
    m_charlist.push_back(info);
    return true;
}

unsigned int CWaitReleaseChar::GetReleaseCharListSize() const
{
    return static_cast<unsigned int>(m_charlist.size());
}

void CWaitReleaseChar::Run()
{
    static DWORD dwLastReleaseTime = HQ_TimeGetTime();
    if ( GameTime::IsPassCurrentTime( dwLastReleaseTime, RELEASE_DELAY ) )
    {
        std::list<RELEASECHARINFO> tmplist;

        {
            CSALocker locker(this);
            tmplist = m_charlist;
            m_charlist.clear();
        }

        while (!tmplist.empty())
        {
            RELEASECHARINFO info = tmplist.front();

            if ( GameTime::IsPassCurrentTime( info.dwDelayTime, DelayTime ) )
            {
                if (info.pChar != NULL)
                {
                    IBaseControl* pControl = info.pChar->GetControl();

                    //在释放完Character后再释放Control，因为像CNpc中需要control才能释放Character
                    //顺序反了会出错
                    try
                    {
                        info.pChar->Release();
                        if (pControl != NULL)
                        {
                            pControl->Release();
                        }
                    }
                    catch (...)
                    {
                    }
                }
            }
            else
            {
                CSALocker locker(this);
                m_charlist.push_back(info);
            }

            tmplist.pop_front();
        }

        dwLastReleaseTime = HQ_TimeGetTime();
    }
}