#ifndef __MULTITEAMSTAGE_H__
#define __MULTITEAMSTAGE_H__

/************************************************************************
        // ����鸱��
************************************************************************/
#include "EctypeStage.h"

class MultiTeamStage : public EctypeStage, INHERIT_POOL_PARAM( MultiTeamStage, 20 )
{
public:
    MultiTeamStage();
    virtual ~MultiTeamStage(){};

    // �ͷų���
    virtual void Release();

    // �Ƿ��и���ҵĶ���
    bool HaveTeam( uint32 nTeamID );

protected:
    // �ж��Ƿ���ҪT�����
    eEctypeKickType WhyKickOutPlayer( GamePlayer* pPlayer );

    // ���볡��
    bool ProcessEnterStage( GamePlayer* pPlayer );

    // �ж��Ƿ��ܽ��볡��
    bool CheckCanEnterStage( GamePlayer* pPlayer );

    // ���¸��������б�
    void UpdateStageTeam();

private:
    typedef std::set< uint32 > TeamList;
    typedef TeamList::iterator TeamListIter;

    // �����б�
    TeamList m_setTeam;
};

///////////////////////////////////////////////////////////////////
inline void MultiTeamStage::Release()
{
    ReleaseStage< MultiTeamStage >( this );
}

#endif
