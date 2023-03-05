/********************************************************************
	Filename: 	WaitReleaseChar.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_WAITRELEASECHAR_H__
#define __GAMESERVER_WAITRELEASECHAR_H__

#include "MeRTLibsServer.h"
#include "BaseCharacter.h"
#include "Mutex.h"

#define DelayTime 5000

class CWaitReleaseChar : public CSemiAutoIntLock
{
public:
    CWaitReleaseChar();
    virtual ~CWaitReleaseChar();

    //�����Ҫɾ���Ľ�ɫ���趨ɾ����ʱ��Ĭ����ʱ10�룩
    bool AddReleaseChar(BaseCharacter* pChar);

    //��ȡɾ�����г���
    unsigned int GetReleaseCharListSize() const;

    void Run();

protected:
    typedef struct tagReleaseCharInfo
    {
        BaseCharacter* pChar;
        DWORD dwDelayTime;
    }
    RELEASECHARINFO;
    std::list<RELEASECHARINFO> m_charlist;
};

extern CWaitReleaseChar& GettheWaitReleaseChar();

#endif //__GAMESERVER_WAITRELEASECHAR_H__
