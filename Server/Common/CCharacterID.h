/********************************************************************
    Filename:     CCharacterID.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __CHARACTERID_H__
#define __CHARACTERID_H__

#include "BaseCharacter.h"
#include "Mutex.h"

//Player's ID Alloc CD Time 1 Min
#define PLAYERID_CDTIME (1000*60)
#define MONSTERID_CDTIME 20000

// ToDo Id ����
#define BeginCharacterID 1
#define BeginOtherCharacterID 65535

template <typename T>
class CCharacterID : public CSemiAutoIntLock
{
protected:
    T*     m_pData;
	char*  m_pUsed;       // 1-used else empty
	DWORD* m_pCDTime;
	int	   m_iUsed;       // һ�����˶���
    int    m_iPlayerUsed; // һ���ж���player
    int    m_iSize;
    GameObjectId    m_iAllocLastCharID;
    GameObjectId    m_iAllocLastOtherID;

public:
	CCharacterID(int iSize)
	{
		m_pData   = new T[iSize];
		m_pUsed   = new char[iSize];
		m_pCDTime = new DWORD[iSize];

		memset(m_pUsed,0,iSize);
        memset(m_pData, 0, sizeof(T)*iSize);
		memset(m_pCDTime, 0, sizeof(DWORD)*iSize);
		m_iUsed       = 0;
        m_iPlayerUsed = 0;
		m_iSize       = iSize;
        m_iAllocLastCharID = BeginCharacterID;
        m_iAllocLastOtherID = BeginOtherCharacterID;
	}

    void GetNextOtherID()
    {
        //������ɫID�����dr_worldMaxPlayers��m_iSize
        ++m_iAllocLastOtherID;
        if(m_iAllocLastOtherID < BeginOtherCharacterID || m_iAllocLastOtherID >= m_iSize )
        {
            m_iAllocLastOtherID = BeginOtherCharacterID;
        }
    }

    void GetNextCharID()
    {
        //��ҽ�ɫID�����0��dr_worldMaxPlayers-1(4999)
        ++m_iAllocLastCharID;
        if(m_iAllocLastCharID < 0 || m_iAllocLastCharID >= dr_worldMaxPlayers )
        {
            m_iAllocLastCharID = BeginCharacterID;
        }
    }

    GameObjectId MallocLoopID(int nType)
    { //��������ID����Ĭ�ϣ���ֻ��ѡ��dr_worldMaxPlayers�Ժ��ID

        CSALocker locker(this);

        if (nType != Object_Player)
        { // ��������ID   
            int nCount = 0;     
            while( nCount < m_iSize - BeginOtherCharacterID )
            {
                if( 1 != m_pUsed[ m_iAllocLastOtherID ] && HQ_TimeGetTime() - m_pCDTime[m_iAllocLastOtherID] >= MONSTERID_CDTIME )
                {
                    __asm { sfence }
                    memset(static_cast<T*>(m_pData+m_iAllocLastOtherID), 0, sizeof(T));
                    m_pUsed[ m_iAllocLastOtherID ] = 1;
                    m_iUsed ++;
                    return m_iAllocLastOtherID;
                }

                GetNextOtherID();
                ++nCount;
            }
        }
        else
        { // �������ID
            int nCount = 0; 
            while( nCount < dr_worldMaxPlayers )
            {
                if( 1 != m_pUsed[ m_iAllocLastCharID ] && HQ_TimeGetTime() - m_pCDTime[m_iAllocLastCharID] >= PLAYERID_CDTIME )
                {
                    __asm { sfence }
                    memset(static_cast<T*>(m_pData+m_iAllocLastCharID), 0, sizeof(T));
                    m_pUsed[ m_iAllocLastCharID ] = 1;

                    ++m_iUsed;
                    ++m_iPlayerUsed;
                    return m_iAllocLastCharID;
                }
                GetNextCharID();
                ++nCount;
            }
        }
        return -1;
    }

	void Free( GameObjectId iID )
	{
        CSALocker locker(this);
		if( iID < 0 || iID >= m_iSize )
			return;

		if( 0 == m_pUsed[iID] )
			return;

        __asm {sfence}
        memset(static_cast<T*>(m_pData+iID), 0, sizeof(T));
        m_pUsed[iID] = 0;
		m_pCDTime[iID] = HQ_TimeGetTime();

        if ( iID>=0 && iID < dr_worldMaxPlayers)
        {
            if ( m_iPlayerUsed > 0)
            {
                --m_iPlayerUsed;
            }
        }

        if ( m_iUsed>0)
        {
		    --m_iUsed;
        }
	}

	T* operator[]( GameObjectId iID )
	{
		if( iID < 0 || iID >= m_iSize )
			return 0;

        __asm {lfence}
		//û��ʹ�ã�����0
		if( 0 == m_pUsed[ iID ] )
			return 0;
		return (m_pData + iID);
	}
	
	int GetIDFromData( T* pT )
	{
		int iID =  pT-m_pData;
		return iID;
	}

	int GetUsed()       { return m_iUsed; }
    int GetPlayerUsed() { return m_iPlayerUsed; }
	int GetSize()       { return m_iSize; }

	bool IsUsed(GameObjectId iID)
	{
		if( iID < 0 || iID >= m_iSize )
			return false;
		if( 1 == m_pUsed[ iID ] )
			return true;
		return false;
	}

	bool Set( GameObjectId iID, T t )
	{
		if( iID < 0 || iID >= m_iSize )
			return false;
		m_pData[ iID ] = t;
		return true;
	}
	
    const char* GetUseStateMemory() { return m_pUsed;}

	~CCharacterID(void)
	{
		if( m_pData )
			delete[] m_pData;

		if( m_pUsed )
			delete[] m_pUsed;

		if (m_pCDTime)
			delete [] m_pCDTime;
	}	
};

#endif // __CHARACTERID_H__
