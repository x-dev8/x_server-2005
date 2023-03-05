#include "Skillbag.h"
#include "..\ItemDetail.h"
#include "FuncPerformanceLog.h"
#include "BuffStatusManager.h"
#include "GameTime.h"

SkillBag::SkillBag() : m_iSize( 0 ), m_iSkillNum( 0 ),m_pSkills( 0 )
{
	memset( m_stSkillColdTime, 0, sizeof( SColdTime ) * More_iMaxSkillKnown );
}

SkillBag::~SkillBag()
{
}

bool SkillBag::IsSkillCoolDownByIndex( short stIndex )
{   
    SColdTime* pTime = GetColdTimeByIndex( stIndex );
    if ( !pTime )
    {
        return true;
    }
    return pTime->bCooldowning;
}

bool SkillBag::IsSkillCoolDownById( int nId )
{
    SColdTime* pTime = GetColdTimeById( nId );
    if ( !pTime )
    {
        return true;
    }
    return pTime->bCooldowning;
}

void SkillBag::Init( SCharSkill* pSkill, int iSize, bool bFixedSize )
{
    m_iSize = iSize;
    m_pSkills = pSkill; 
    
    if (bFixedSize)
    { m_iSkillNum = iSize; }
    else
    { m_iSkillNum = 0; }
        
    memset(m_stSkillColdTime, 0, sizeof(m_stSkillColdTime));

    unsigned long dwCurrentTime = HQ_TimeGetTime();
    for( int iLoop = 0 ; iLoop < m_iSize; ++iLoop, ++pSkill )
    {
        if( pSkill->ustSkillID != InvalidLogicNumber && pSkill->ustSkillID != 0 )
        {
			pSkill->bAvailable = true;

            if (!bFixedSize)
            { m_iSkillNum ++; }
            
            if ( pSkill->nColdTime > 0 )
            {
                m_stSkillColdTime[iLoop].bCooldowning    = true;
                m_stSkillColdTime[iLoop].dwColdStartTime = dwCurrentTime;
                m_stSkillColdTime[iLoop].dwColdTime      = pSkill->nColdTime;

                // 纠正一下 cd时间
                ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID( pSkill->ustSkillID, pSkill->stSkillLevel );
                if ( pItemSkill != NULL )
                {
                    if ( pSkill->nColdTime > pItemSkill->dwSkillCoolDownTime )
                    {
                        m_stSkillColdTime[iLoop].Clear();
                    }
                }
            }
			PrepareSelfSkillEffect(pSkill->ustSkillID,pSkill->stSkillLevel);
        }
    }
}

//获取指定索引的技能信息
SCharSkill* SkillBag::GetSkillByIndex( unsigned short stIndex )
{
    if( stIndex >= m_iSkillNum )
        return NULL;
    return &m_pSkills[stIndex];
}

SCharSkill* SkillBag::GetSkillByID(unsigned short ustSkillID)
{
    for( int iLoop = 0;iLoop < m_iSkillNum;iLoop++ )
    {
        if (m_pSkills[iLoop].ustSkillID==ustSkillID)
        {
            return &m_pSkills[iLoop];
        }
    }
    return NULL;
}

//ClearSkills
bool SkillBag::ClearAllSkills()
{
    SCharSkill* pSkill = m_pSkills;

    int iLoop;
    for( iLoop=0; iLoop < m_iSkillNum; iLoop++, pSkill++ )
    {
        memset(pSkill, 0, sizeof(SCharSkill));
        pSkill->ustSkillID = InvalidLogicNumber;
    }
    m_iSkillNum = 0;
    return true;
}
extern int LoadSkillEffect(ItemDefine::SItemSkill *pSkill);
bool SkillBag::AddSkill( unsigned short ustSkillID, short stSkillLevel )
{
    if( m_iSkillNum >= m_iSize||m_iSkillNum < 0 )
        return false;

    if( GetSkillByID(ustSkillID) )
        return false;

    // 在尾部插入
    m_pSkills[m_iSkillNum].ustSkillID   = ustSkillID;
    m_pSkills[m_iSkillNum].stSkillLevel = stSkillLevel; 
    ++m_iSkillNum;

	PrepareSelfSkillEffect(ustSkillID, stSkillLevel);

	return true;
}

bool SkillBag::RemoveSkill( unsigned short ustSkillID )
{
    // 保证是连续的
    int nIndex = -1;
    SCharSkill* pSkill = m_pSkills;

    // 找到位置
    for( int i = 0 ; i < m_iSkillNum ; ++i, ++pSkill)
    {
        if( ustSkillID == pSkill->ustSkillID )
        {
            nIndex = i;
            break;
        }
    }

    if ( nIndex == -1)
    { return false; }

    m_pSkills[ nIndex ].ustSkillID = InvalidLogicNumber;
    
    m_stSkillColdTime[ nIndex ].Clear(); // CD

    pSkill = m_pSkills;
    for ( int i=nIndex, I=nIndex+1; I<m_iSkillNum; ++i, ++I )
    {
        if ( pSkill[I].ustSkillID == InvalidLogicNumber )
        { break; }

        pSkill[i]            = pSkill[I];
        m_stSkillColdTime[i] = m_stSkillColdTime[I];

        memset(&pSkill[I], 0x00, sizeof(SCharSkill));
        pSkill[I].ustSkillID = InvalidLogicNumber;

        m_stSkillColdTime[I].Clear();
    }

    --m_iSkillNum;

    return true;
}

void SkillBag::Update()
{
    SCharSkill* pSkill = m_pSkills;
    if ( !pSkill || m_iSkillNum <= 0 )
        return;

    DWORD dwTime = HQ_TimeGetTime();
    for( int iLoop = 0; iLoop < GetSkillNum(); iLoop++,pSkill++ )
    {
        SColdTime *pColdTime = GetColdTimeByIndex( iLoop );
        if ( !pColdTime )
        {
            continue;
        }
        if( pSkill->ustSkillID != InvalidLogicNumber && pColdTime->bCooldowning )
        {
            //检查技能CoolDown
            if( dwTime - pColdTime->dwColdStartTime >= pColdTime->dwColdTime )
            {
               pColdTime->Clear();
            }
            else
            {
                if( pColdTime->dwColdStartTime > dwTime )
                {
                    pColdTime->Clear();
                    //ToLog
                }
            }
        }
    }
}

int SkillBag::GetSkillIndexById( int nSkillID )
{
    for( int iLoop = 0; iLoop<m_iSkillNum; iLoop++ )
    {
        if( m_pSkills[iLoop].ustSkillID == nSkillID  )
        {
            return iLoop;
        }
    }
    return -1;
}

SkillBag::SColdTime* SkillBag::GetColdTimeByIndex( unsigned int nIndex )
{
    if ( nIndex >= More_iMaxSkillKnown ||
        nIndex >= m_iSkillNum )
    {
        return NULL;
    }
    return &m_stSkillColdTime[nIndex];
}

SkillBag::SColdTime* SkillBag::GetColdTimeById( unsigned int nID )
{
    int nIndex = GetSkillIndexById( nID );
    if ( nIndex == -1 )
    {
        return NULL;
    }
    return GetColdTimeByIndex( nIndex );
}

CDTIME SkillBag::StartSkillCoolDown( unsigned short ustSkillID, short stSkillLevel, DWORD dwDelay )
{
    CDTIME result( 0, 0 );

    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( ustSkillID, stSkillLevel );
    if ( pSkill == NULL )
    { return result; }

    if ( pSkill->specialSkillType >= ItemDefine::ESST_Team && pSkill->specialSkillType < ItemDefine::ESST_TeamMax )
    {
        if ( pSkill->nSkillCoolDownType == -1 )
        { return result; }
    }

    DWORD dwCoolDownTime = 0;
    if ( pSkill->dwSkillCoolDownTime > 0 )
    {
        dwCoolDownTime = pSkill->dwSkillCoolDownTime + dwDelay;
    }
    // 技能CoolDown
    if( dwCoolDownTime > 0 )
    {
        if( pSkill->nSkillCoolDownType == -1 )
        {
            SCharSkill* pCharSkill = GetSkillByID( ustSkillID );
            if ( pCharSkill == NULL )
            { return result; }

            SColdTime* pColdTime = GetColdTimeById( ustSkillID );
            if ( pColdTime == NULL )
            { return result; }

            pColdTime->bCooldowning    = true;
            pColdTime->dwColdStartTime = HQ_TimeGetTime();
            pColdTime->dwColdTime      = dwCoolDownTime;
        }
        else
        {
            for ( int n = 0; n < GetSkillNum(); ++n )  
            {
                SCharSkill* pCharSkill = GetSkillByIndex( n );
                SColdTime* pColdTime = GetColdTimeByIndex( n );
                if ( pCharSkill == NULL || pColdTime == NULL || pCharSkill->ustSkillID == InvalidLogicNumber )
                { continue; }

                ItemDefine::SItemSkill *pOtherSkill = GettheItemDetail().GetSkillByID( pCharSkill->ustSkillID,pCharSkill->stSkillLevel );
                if ( pOtherSkill == NULL )
                { continue; }

                if ( pSkill->nSkillCoolDownType == pOtherSkill->nSkillCoolDownType )
                {
                    pColdTime->bCooldowning    = true;
                    pColdTime->dwColdStartTime = HQ_TimeGetTime();
                    pColdTime->dwColdTime      = dwCoolDownTime;
                }
            }
        }
    }

    // 公共CoolDown
    for ( int n = 0; n < GetSkillNum(); ++n )
    {
        SCharSkill* pCharSkill = GetSkillByIndex( n );
        SColdTime*pColdTime = GetColdTimeByIndex( n );

        if ( pCharSkill == NULL || pColdTime == NULL || pCharSkill->ustSkillID == InvalidLogicNumber )
        { continue; }

        unsigned int nColdTime = GameTime::GetLeftKeepTime( HQ_TimeGetTime(), pColdTime->dwColdStartTime, pColdTime->dwColdTime );
        if( nColdTime < pSkill->dwCommonCoolDownTime )
        {
            pColdTime->bCooldowning    = true;
            pColdTime->dwColdStartTime = HQ_TimeGetTime();

            pColdTime->dwColdTime      = pSkill->dwCommonCoolDownTime;
        }
    }
    result.first  = dwCoolDownTime;
    result.second = pSkill->dwCommonCoolDownTime;
    return result;
}

CDTIME SkillBag::StartSkillCoolDown( BuffStatusManager& _buffManager, unsigned short ustSkillID, short stSkillLevel, DWORD dwDelay )
{
    CDTIME result( 0, 0 );

    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( ustSkillID, stSkillLevel );
    if ( pSkill == NULL )
    { return result; }

    if ( pSkill->specialSkillType >= ItemDefine::ESST_Team && pSkill->specialSkillType < ItemDefine::ESST_TeamMax )
    {
        if ( pSkill->nSkillCoolDownType == -1 )
        { return result; }
    }

    DWORD dwCoolDownTime = 0;
    if ( pSkill->dwSkillCoolDownTime > 0 )
    {
        dwCoolDownTime = pSkill->dwSkillCoolDownTime + dwDelay;
    }

    if (_buffManager.GetChangeSkillId(0) != 0)
    {
        for ( int i=0; i<ItemDefine::SItemStatus::ECD_ChangeSkillMaxSize; ++i)
        {
            if(_buffManager.GetChangeSkillId(i) == pSkill->ustItemID )
            {
                dwCoolDownTime -= _buffManager.GetChangeSkillTime(i);
            }
        }

        if (dwCoolDownTime < 0)
        { dwCoolDownTime = 0;}
    }

    // 技能CoolDown
    if( dwCoolDownTime > 0 )
    {
        if( pSkill->nSkillCoolDownType == -1 )
        {
            SCharSkill* pCharSkill = GetSkillByID( ustSkillID );
            if ( pCharSkill == NULL )
            { return result; }

            SColdTime* pColdTime = GetColdTimeById( ustSkillID );
            if ( pColdTime == NULL )
            { return result; }

            pColdTime->bCooldowning    = true;
            pColdTime->dwColdStartTime = HQ_TimeGetTime();
            pColdTime->dwColdTime      = dwCoolDownTime;
        }
        else
        {
            for ( int n = 0; n < GetSkillNum(); ++n )  
            {
                SCharSkill* pCharSkill = GetSkillByIndex( n );
                SColdTime* pColdTime = GetColdTimeByIndex( n );
                if ( pCharSkill == NULL || pColdTime == NULL || pCharSkill->ustSkillID == InvalidLogicNumber )
                { continue; }

                ItemDefine::SItemSkill *pOtherSkill = GettheItemDetail().GetSkillByID( pCharSkill->ustSkillID,pCharSkill->stSkillLevel );
                if ( pOtherSkill == NULL )
                { continue; }

                if ( pSkill->nSkillCoolDownType == pOtherSkill->nSkillCoolDownType )
                {
                    pColdTime->bCooldowning    = true;
                    pColdTime->dwColdStartTime = HQ_TimeGetTime();
                    pColdTime->dwColdTime      = dwCoolDownTime;
                }
            }
        }
    }

    // 公共CoolDown
    for ( int n = 0; n < GetSkillNum(); ++n )
    {
        SCharSkill* pCharSkill = GetSkillByIndex( n );
        SColdTime*pColdTime = GetColdTimeByIndex( n );

        if ( pCharSkill == NULL || pColdTime == NULL || pCharSkill->ustSkillID == InvalidLogicNumber )
        { continue; }

        unsigned int nColdTime = GameTime::GetLeftKeepTime( HQ_TimeGetTime(), pColdTime->dwColdStartTime, pColdTime->dwColdTime );
        if( nColdTime < pSkill->dwCommonCoolDownTime )
        {
            pColdTime->bCooldowning    = true;
            pColdTime->dwColdStartTime = HQ_TimeGetTime();

            pColdTime->dwColdTime      = pSkill->dwCommonCoolDownTime;
        }
    }
    result.first  = dwCoolDownTime;
    result.second = pSkill->dwCommonCoolDownTime;
    return result;
}

 // -1 清除所有技能的colldown时间
bool SkillBag::ClearSkillCollDown( unsigned short ustSkillID /* = ErrorUnsignedShortID */ )
{
    if ( ustSkillID != InvalidLogicNumber )
    {
        SColdTime* pColdTime = GetColdTimeById( ustSkillID );
        if ( pColdTime == NULL )
        { return false; }

        pColdTime->Clear();
    }
    else
    {
        for ( int i = 0; i < GetSkillNum(); ++i )  
        {
            SColdTime* pColdTime = GetColdTimeByIndex( i );
            if ( pColdTime == NULL )
                continue;

            SCharSkill* pCharSkill = GetSkillByIndex( i );
            if ( pCharSkill == NULL || pCharSkill->ustSkillID == InvalidLogicNumber )
                continue;

            ItemDefine::SItemSkill *pOtherSkill = GettheItemDetail().GetSkillByID( pCharSkill->ustSkillID,pCharSkill->stSkillLevel );
            if ( pOtherSkill == NULL )
                continue;

            if ( pOtherSkill->cLearnProfessionReq != -1 )       // 只清除职业技能cd时间
            {
                pColdTime->Clear();
            }
        }
    }

    return true;
}

void SkillBag::SaveSkillColdTime()
{
    unsigned long dwCurrentTime = HQ_TimeGetTime();
    for ( int i = 0; i < GetSkillNum(); ++i )  
    {
        SColdTime* pColdTime = GetColdTimeByIndex( i );
        if ( pColdTime == NULL )
            continue;

        SCharSkill* pCharSkill = GetSkillByIndex( i );
        if ( pCharSkill == NULL || pCharSkill->ustSkillID == InvalidLogicNumber )
            continue;

        pCharSkill->nColdTime = 0;
        if ( pColdTime->bCooldowning )
        { pCharSkill->nColdTime = GameTime::GetLeftKeepTime( dwCurrentTime, pColdTime->dwColdStartTime, pColdTime->dwColdTime ); }
    }
}

bool SkillBag::PrepareSelfSkillEffect( unsigned short ustSkillID, short stSkillLevel )
{
#ifdef _CLIENT_
	ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(ustSkillID, stSkillLevel);
	if ( NULL == pSkill )
		return false;

	LoadSkillEffect(pSkill);
#endif
	return true;
}