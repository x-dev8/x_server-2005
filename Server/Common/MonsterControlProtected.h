#ifndef __MONSTERCONTROLPROTECTED_H__
#define __MONSTERCONTROLPROTECTED_H__

/********************************************************************
            �����ͱ�����, ���ɹ���, ���Ʋſ��ƶ�
            Filename:     MonsterControlProtected.h
            MaintenanceMan Mail: lori227@live.cn
*********************************************************************/
#include "MonsterProtectedEx.h"

class MonsterControlProtected : public MonsterProtectedEx, INHERIT_POOL_PARAM( MonsterControlProtected, 20 )
{
public:
    DECLARE_POOL_FUNC( MonsterControlProtected )

    MonsterControlProtected();
    virtual ~MonsterControlProtected(){};

protected:

private:
    
};

#endif