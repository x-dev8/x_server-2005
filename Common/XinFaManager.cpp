#include "XinFaManager.h"
#include "XinFaConfig.h"

XinFaManager::XinFaManager() : m_iSize( 0 ), m_iXinFaNum( 0 ), m_pXinFaArray( NULL )
{
}

XinFaManager::~XinFaManager()
{
}

void XinFaManager::Init( SCharXinFa *pCharXinFa,int iSize )
{
    m_iSize = iSize;
    m_pXinFaArray = pCharXinFa; 

    m_iXinFaNum = 0;
    for( int iLoop = 0 ; iLoop < m_iSize; ++iLoop, ++pCharXinFa )
    {
        if( pCharXinFa->nXinFaID != InvalidLogicNumber && pCharXinFa->nXinFaLevel != 0 )
        {
            XinFaConfig::STalentXinFa* pTalentXinFa = theXinFaConfig.GetXinFaByID( pCharXinFa->nXinFaID, pCharXinFa->nXinFaLevel );
            if ( pTalentXinFa == NULL )
            { continue; }

            ++m_iXinFaNum;
        }
    }
}

bool XinFaManager::ClearAllXinFa()
{
    SCharXinFa* pCharXinFa = m_pXinFaArray;

    for(int iLoop=0; iLoop < m_iXinFaNum; iLoop++, pCharXinFa++ )
    {
        memset(pCharXinFa, 0, sizeof(SCharXinFa));
        pCharXinFa->nXinFaID = InvalidLogicNumber;
    }
    m_iXinFaNum = 0;
    return true;
}

SCharXinFa* XinFaManager::GetXinFaByID(unsigned short nID)
{
    for( int iLoop = 0;iLoop < m_iXinFaNum;iLoop++ )
    {
        if (m_pXinFaArray[iLoop].nXinFaID ==nID)
        {
            return &m_pXinFaArray[iLoop];
        }
    }
    return NULL;
}

SCharXinFa* XinFaManager::GetXinFaByIndex( unsigned short nIndex )
{
    if( nIndex >= m_iXinFaNum )
        return NULL;

    return &m_pXinFaArray[nIndex];
}

bool XinFaManager::AddXinFa( unsigned short nID, unsigned char nLevel )
{
    if( m_iXinFaNum >= m_iSize|| m_iXinFaNum < 0 )
        return false;

    if( GetXinFaByID(nID) )
        return false;

    // 在尾部插入
    m_pXinFaArray[m_iXinFaNum].nXinFaID    = nID;
    m_pXinFaArray[m_iXinFaNum].nXinFaLevel = nLevel; 
    ++m_iXinFaNum;

    return true;
}

int XinFaManager::GetXinFaIndexById( int nID )
{
    for( int iLoop = 0; iLoop<m_iXinFaNum; iLoop++ )
    {
        if( m_pXinFaArray[iLoop].nXinFaID == nID  )
        {
            return iLoop;
        }
    }
    return -1;
}

bool XinFaManager::RemoveXinFa( unsigned short nID )
{
    // 保证是连续的
    int nIndex = -1;
    SCharXinFa* pTalent = m_pXinFaArray;

    // 找到位置
    for( int i = 0 ; i < m_iXinFaNum ; ++i, ++pTalent)
    {
        if( nID == pTalent->nXinFaID )
        {
            nIndex = i;
            break;
        }
    }

    if ( nIndex == -1)
    { return false; }

    m_pXinFaArray[ nIndex ].nXinFaID = InvalidLogicNumber;

    pTalent = m_pXinFaArray;
    for ( int i=nIndex, I=nIndex+1; I<m_iXinFaNum; ++i, ++I )
    {
        if ( pTalent[I].nXinFaID == InvalidLogicNumber )
        { break; }

        pTalent[i] = pTalent[I];

        memset(&pTalent[I], 0x00, sizeof(SCharSkill));
        pTalent[I].nXinFaID = InvalidLogicNumber;
    }

    --m_iXinFaNum;

    return true;
}
