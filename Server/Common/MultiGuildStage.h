#ifndef __MULTIGUILDSTAGE_H__
#define __MULTIGUILDSTAGE_H__

/************************************************************************
        // ����ɸ���
************************************************************************/
#include "EctypeStage.h"

class MultiGuildStage : public EctypeStage, INHERIT_POOL_PARAM( MultiGuildStage, 20 )
{
public:
    MultiGuildStage();
    virtual ~MultiGuildStage(){};

    // �ͷų���
    virtual void Release();

    // �Ƿ��и���ҵİ���
    bool HaveGuild( uint32 nGuildID );

protected:
    // �ж��Ƿ���ҪT�����
    eEctypeKickType WhyKickOutPlayer( GamePlayer* pPlayer );

    // ���볡��
    bool ProcessEnterStage( GamePlayer* pPlayer );

    // �ж��Ƿ��ܽ��볡��
    bool CheckCanEnterStage( GamePlayer* pPlayer );

    // ���¸��������б�
    void UpdateStageGuild();

private:
    typedef std::set< uint32 > GuildList;
    typedef GuildList::iterator GuildListIter;

    // �����б�
    GuildList m_setGuild;
};

///////////////////////////////////////////////////////////////////
inline void MultiGuildStage::Release()
{
    ReleaseStage< MultiGuildStage >( this );
}

#endif
