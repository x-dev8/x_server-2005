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

    //添加需要删除的角色并设定删除延时（默认延时10秒）
    bool AddReleaseChar(BaseCharacter* pChar);

    //获取删除队列长度
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
