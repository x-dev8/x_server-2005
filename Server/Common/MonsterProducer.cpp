#include "MonsterProducer.h"
#include "InfoText.h"
#include "ShareData.h"
#include "Configure.h"
//#include "LogFileObjectName.h"

CMonsterProducer::CMonsterProducer()
{
}

CMonsterProducer::~CMonsterProducer()
{
}

CMonsterProducer::TagMonsterData* CMonsterProducer::GetMonsterData( unsigned int nIndex )
{
    //CSALocker locker(this);
	if( nIndex >= m_vtMonsterData.size() )
		return NULL;
    return &m_vtMonsterData[nIndex];
}

BOOL CMonsterProducer::GetMonsterData( unsigned int nIndex, int &nMonsterIndex, float &x, float &y)
{
    //CSALocker locker(this);
	if ( nIndex >= m_vtMonsterData.size() )
		return FALSE;

    nMonsterIndex = m_vtMonsterData[nIndex].nMonsterIndex;
    x             = m_vtMonsterData[nIndex].x;
    y             = m_vtMonsterData[nIndex].y;
    return TRUE;
}

//增加一个死的npc到堆里面
BOOL CMonsterProducer::PushDeadMonster( int index )
{
    CSALocker locker(this);
	m_qeDeadMonster.push( index );
	return TRUE;
}

// 提取出一个死人
int CMonsterProducer::PopDeadMonster()
{
    CSALocker locker(this);
	if ( m_qeDeadMonster.empty() )
		return -1;
	int ret = m_qeDeadMonster.front();
	m_qeDeadMonster.pop();
	return ret;
}

int	CMonsterProducer::PeekReliveDeadMonster()
{
    //CSALocker locker(this);
	if ( m_qeDeadMonster.empty() )
    { return -1; }

	int index = m_qeDeadMonster.front();
    if ( index < 0 || index >= m_vtMonsterData.size() )
	{ return -1;}

	TagMonsterData* pMonsterData = &m_vtMonsterData[index];

	if ( pMonsterData->dwDeadTime == 0 )
    { return index; }

    if ( GameTime::IsPassCurrentTime( pMonsterData->dwDeadTime, pMonsterData->dwReliveTime ) )
    { return index; }

	int nMonsterIndex = PopDeadMonster();
	PushDeadMonster( nMonsterIndex );
	return -1;
}

int CMonsterProducer::AddMonster( SMapMonsterInfo* pMonsterStruct, int nBornPosX, int nBornPosY, RECT &rcBronArea, const char *szFilePath, unsigned short ustMapLevel/* = 0*/)
{
    if ( pMonsterStruct == NULL )
    { return -1; }

    int nID = pMonsterStruct->m_nId;
    if (ustMapLevel != 0)
    { // 要判断等级的
        nID = FormatEctypeMonsterID( nID, ustMapLevel );
    }

    ItemDefine::SMonster* pMonster = GettheItemDetail().GetMonsterById( nID );
    if ( pMonster == NULL )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "CMonsterProducer::AddMonster->GetMonsterById(%d) Fail", nID );
        return -1;
    }

    if ( pMonster->iMonsterContainerIndex < 0 )
    { return -1; }

    TagMonsterData stMonsterData;
    stMonsterData.nMonsterIndex = pMonster->iMonsterContainerIndex;		
    stMonsterData.bRandRange    = pMonsterStruct->m_bRandRange;
    // 是否地点 
    if (pMonsterStruct->m_bRandRange)
    { // 范围
        stMonsterData.x = nBornPosX; // 这里的nBornX 是在外面随机生成的
        stMonsterData.y = nBornPosY;
    }
    else
    { // 出身点的坐标
        stMonsterData.x = /*TileToFloat*/(pMonsterStruct->m_nX);
        stMonsterData.y = /*TileToFloat*/(pMonsterStruct->m_nY);
    }

    stMonsterData.rcBron       = rcBronArea;
    stMonsterData.nDirection   = pMonsterStruct->m_nDir;
    stMonsterData.CreateFlag   = FALSE;
    stMonsterData.dwDeadTime   = 0;
    stMonsterData.dwReliveTime = pMonster->nReliveTime;
    stMonsterData.stZoneID     = pMonsterStruct->m_iZone;
    stMonsterData.bHide        = pMonsterStruct->m_bHide;    // 表示是否为隐藏怪
    stMonsterData.stAiValue    = pMonsterStruct->m_iAiValue; // 用来记录怪物的思考时间间隔

    //用来记录怪物的追击距离
    //stMonsterData.stCatchRange = iCatchRange;
    stMonsterData.eCountry = pMonsterStruct->m_iCountry;
    stMonsterData.nFightCamp = pMonsterStruct->m_nFightCamp;
    stMonsterData.nForce     = pMonsterStruct->m_nForce;
    stMonsterData.nRouteID   = pMonsterStruct->m_nRouteID;
    stMonsterData.m_strDeadScriptName = pMonsterStruct->m_strScriptName;
    stMonsterData.m_strLuaScript = pMonsterStruct->m_strLuaScript;
    stMonsterData.szMonsterNameCorrect = pMonsterStruct->m_strMonsterName;
    stMonsterData.iModelIDCorrect = pMonsterStruct->m_iModelIDCorrect;
    stMonsterData.szCreatureSound = pMonsterStruct->m_strCreatureSound;
    stMonsterData.stMonsterTypeCorrect = pMonsterStruct->m_iMonsterTypeCorrect;
    stMonsterData.stBodySizeCorrect = pMonsterStruct->m_iBodySizeCorrect;
    stMonsterData.stLevelCorrect = pMonsterStruct->m_iLevelCorrect;
    stMonsterData.stRewardExpCorrect = pMonsterStruct->m_iLevelCorrect;
    stMonsterData.stStrengthCorrect = pMonsterStruct->m_iStrengthCorrect;
    stMonsterData.stConstitutionCorrect = pMonsterStruct->m_iConstitutionCorrect;
    stMonsterData.stAgilityCorrect = pMonsterStruct->m_iAgilityCorrect;
    stMonsterData.stMagicCorrect = pMonsterStruct->m_iMagicCorrect;
    stMonsterData.stIntelligenceCorrect = pMonsterStruct->m_iIntelligenceCorrect;
    stMonsterData.stCharmCorrect = pMonsterStruct->m_iCharmCorrect;
    stMonsterData.stHpMaxCorrect = pMonsterStruct->m_iHpMaxCorrect;
    stMonsterData.stMpMaxCorrect = pMonsterStruct->m_iMpMaxCorrect;
    stMonsterData.stHpRestoreCorrect = pMonsterStruct->m_iHpRestoreCorrect;
    stMonsterData.stMpRestoreCorrect = pMonsterStruct->m_iMpRestoreCorrect;
    stMonsterData.stExactCorrect = pMonsterStruct->m_iExactCorrect;
    stMonsterData.stDodgeCorrect = pMonsterStruct->m_iDodgeCorrect;
    stMonsterData.stViewSightCorrect = pMonsterStruct->m_iViewCorrect;
    stMonsterData.dwCatchTimeCorrect = pMonsterStruct->m_iCatchTimeCorrect;
    stMonsterData.fMoveSpeedCorrect = pMonsterStruct->m_fMoveSpeedCorrect;
    stMonsterData.stPhysicsAtkMinCorrect = pMonsterStruct->m_iPhysicsMinCorrect;
    stMonsterData.stPhysicsAtkMaxCorrect = pMonsterStruct->m_iPhysicsMaxCorrect;
    stMonsterData.stMagicAtkMinCorrect = pMonsterStruct->m_iMagicMinCorrect;
    stMonsterData.stMagicAtkMaxCorrect = pMonsterStruct->m_iMagicMaxCorrect;
    stMonsterData.stPhysicsDefCorrect = pMonsterStruct->m_iPhysicsDefCorrect;
    stMonsterData.stMagicDefCorrect = pMonsterStruct->m_iMagicDefCorrect;
    stMonsterData.stCriticalRateCorrect = pMonsterStruct->m_iCriticalRateCorrect;
    stMonsterData.stAttackRateCorrect = pMonsterStruct->m_iAttackRateCorrect;
    stMonsterData.stFrostAttCorrect = pMonsterStruct->m_iFrostAttCorrect;
    stMonsterData.stBlazeAttCorrect = pMonsterStruct->m_iBlazeAttCorrect;
    stMonsterData.stThunderAttCorrect = pMonsterStruct->m_iThunderAttCorrect;
    stMonsterData.stPoisonAttCorrect = pMonsterStruct->m_iPoisonAttCorrect;
    stMonsterData.stFrostDefCorrect = pMonsterStruct->m_iFrostDefCorrect;
    stMonsterData.stBlazeDefCorrect = pMonsterStruct->m_iBlazeDefCorrect;
    stMonsterData.stThunderDefCorrect = pMonsterStruct->m_iThunderDefCorrect;
    stMonsterData.stPoisonDefCorrect = pMonsterStruct->m_iPoisonDefCorrect;
    stMonsterData.iSkillIDCorrect[0] = pMonsterStruct->m_iSkill1Correct;
    stMonsterData.iSkillIDCorrect[1] = pMonsterStruct->m_iSkill2Correct;
    stMonsterData.iSkillIDCorrect[2] = pMonsterStruct->m_iSkill3Correct;
    stMonsterData.stSkillLevelCorrect[0] = pMonsterStruct->m_iSkill1LevelCorrect;
    stMonsterData.stSkillLevelCorrect[1] = pMonsterStruct->m_iSkill2LevelCorrect;
    stMonsterData.stSkillLevelCorrect[2] = pMonsterStruct->m_iSkill3LevelCorrect;
    stMonsterData.stSkillRateCorrect[0] = pMonsterStruct->m_iSkill1RateCorrect;
    stMonsterData.stSkillRateCorrect[1] = pMonsterStruct->m_iSkill2RateCorrect;
    stMonsterData.stSkillRateCorrect[2] = pMonsterStruct->m_iSkill3RateCorrect;
    stMonsterData.iGoodDropIDCorrect[0] = pMonsterStruct->m_iItem1Correct;
    stMonsterData.iGoodDropIDCorrect[1] = pMonsterStruct->m_iItem2Correct;
    stMonsterData.iGoodDropIDCorrect[2] = pMonsterStruct->m_iItem3Correct;
    stMonsterData.iGoodDropIDCorrect[3] = pMonsterStruct->m_iItem4Correct;
    stMonsterData.iGoodDropIDCorrect[4] = pMonsterStruct->m_iItem5Correct;
    stMonsterData.iGoodDropIDCorrect[5] = pMonsterStruct->m_iItem6Correct;
    stMonsterData.stGoodDropRateCorrect[0] = pMonsterStruct->m_iItem1RateCorrect;
    stMonsterData.stGoodDropRateCorrect[1] = pMonsterStruct->m_iItem1RateCorrect;
    stMonsterData.stGoodDropRateCorrect[2] = pMonsterStruct->m_iItem1RateCorrect;
    stMonsterData.stGoodDropRateCorrect[3] = pMonsterStruct->m_iItem1RateCorrect;
    stMonsterData.stGoodDropRateCorrect[4] = pMonsterStruct->m_iItem1RateCorrect;
    stMonsterData.stGoodDropRateCorrect[5] = pMonsterStruct->m_iItem1RateCorrect;
    stMonsterData.stDropMinMoneyCorrect = pMonsterStruct->m_iDropMoneyMinCorrect;
    stMonsterData.stDropMaxMoneyCorrect = pMonsterStruct->m_iDropMoneyMaxCorrect;
    stMonsterData.fItemDropMultipleRateCorrect = pMonsterStruct->m_fDropMultipleRateCorrect;
    m_vtMonsterData.push_back( stMonsterData );

    int nMonsterIndex = m_vtMonsterData.size() - 1;

    if( !pMonsterStruct->m_bHide )
    { // 如果不是隐藏怪
        PushDeadMonster( nMonsterIndex );
    }
    return nMonsterIndex;
}

//判断该地图上是否有死去的monster ,,需要刷出来
BOOL CMonsterProducer::IsHaveDeadMonster()
{
    //CSALocker locker(this);
	if ( m_qeDeadMonster.empty() )
		return FALSE;
    return TRUE;
}

BOOL CMonsterProducer::ReliveMonster()
{ // 某个位置的monster活了
    //CSALocker locker(this);
    int index = PopDeadMonster();
    if (index <0 || index >= m_vtMonsterData.size() )
        return FALSE;
    m_vtMonsterData[index].CreateFlag = TRUE;
    return TRUE;
}
//某个位置的monster死了
BOOL CMonsterProducer::KillMonster(int index)
{
    //CSALocker locker(this);
    if (index <0 || index >= m_vtMonsterData.size() )
        return FALSE;
    m_vtMonsterData[index].CreateFlag = FALSE;
    m_vtMonsterData[index].dwDeadTime = HQ_TimeGetTime();
    //
    PushDeadMonster(index);
    //
    return TRUE;
}

uint32 CMonsterProducer::GetDeadMonsterNumber()
{
    //CSALocker locker(this);
    return m_qeDeadMonster.size();
}

void CMonsterProducer::AllMonsterDeadTimeClear()
{
    //CSALocker locker(this);
    unsigned int nSize = m_qeDeadMonster.size();
    for (int i=0; i<nSize; i++)
    {
        int nIndex = m_qeDeadMonster.front();
        m_qeDeadMonster.pop();
        if (nIndex >=0 && nIndex <= m_vtMonsterData.size())
        {
            TagMonsterData *pMonsterData = &m_vtMonsterData[nIndex];
            if (pMonsterData != NULL)
            {
                pMonsterData->dwDeadTime = 0;
                m_qeDeadMonster.push(nIndex);
            }
        }
    }
}