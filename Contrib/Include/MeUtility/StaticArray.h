/********************************************************************
    Filename:     StaticArray.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#pragma once

#include "MeRTLibs.h"
#include "Mutex.h"

template<class T >
class CStaticArray : public ::CSemiAutoIntLock
{	
protected:
    
    T		*m_pData;
	char	*m_pUsed;						//1-used else empty
	int		m_iUsed,m_iSize;
    int     m_iAllocLastID;

public:

	CStaticArray(int iSize)
	{
		m_pData = new T[iSize];
		m_pUsed = new char[iSize];
		memset( m_pUsed,0,iSize );
        memset(m_pData, 0, sizeof(T)*iSize);
		m_iUsed = 0;
		m_iSize = iSize;
        m_iAllocLastID = 0;
	}
    void GetNextID()
    {
        m_iAllocLastID++;
        if( m_iAllocLastID >= m_iSize )
        {
            m_iAllocLastID = 0;
        }
    }
	int MallocID(int BeginID)
	{
        CSALocker locker(this);
		int count = BeginID;
		while((count>=0) && (count < m_iSize))
		{
			if( 1 != m_pUsed[count] )
			{
                __asm {sfence}
				m_pUsed[count] = 1;
				m_iUsed ++;
				return count;
			}
			count++;
		}
		return -1;
	}
	//
    int MallocLoopID()
    {
        CSALocker locker(this);
        int count = 0;
        while( count < m_iSize )
        {
            if( 1 != m_pUsed[ m_iAllocLastID ] )
            {
                __asm {sfence}
                m_pUsed[ m_iAllocLastID ] = 1;
                m_iUsed ++;
                return m_iAllocLastID;
            }
            GetNextID();
            count++;
        }
        return -1;
    }

	int Malloc()
	{
        CSALocker locker(this);
		int i;
		for( i = 0 ; i < m_iSize ; i ++ )
		{
			if( 1 != m_pUsed[ i ] )
			{
                __asm {sfence}
				m_pUsed[ i ] = 1;
				m_iUsed ++;
				return i;
			}
		}
		return -1;
	}
	//请求分配某一个位置上的
	int Malloc( int iPos )
	{
        CSALocker locker(this);
		if( iPos < 0 || iPos >= m_iSize )
			return -1;
		if( 1 != m_pUsed[ iPos ] )
		{
            __asm {sfence}
			m_pUsed[ iPos ] = 1;
			m_iUsed ++;
			return iPos;
		}		
		return -1;
	}
	void Free( int iID )
	{
        CSALocker locker(this);
		if( iID < 0 || iID >= m_iSize )
			return;
		if( 0 == m_pUsed[iID] )
			return;
        memset(&m_pData[iID], 0, sizeof(T));
		m_pUsed[iID] = 0;
		m_iUsed --;
	}
	T* operator[]( int iID )
	{
		if( iID < 0 || iID >= m_iSize )
			return 0;
		//没有使用，返回0
        __asm {lfence}
		if( 0 == m_pUsed[ iID ] )
			return 0;
		return (m_pData + iID);
	}
	
	int GetIDFromData( T* pT )
	{
		int iID =  pT-m_pData;
		return iID;
	}

	int GetUsed()
	{
		return m_iUsed;
	}
	int GetSize()
	{
		return m_iSize;
	}
	bool IsUsed(int iID)
	{
		if( iID < 0 || iID >= m_iSize )
			return false;

        __asm {lfence}
		if( 1 == m_pUsed[ iID ] )
			return true;
		return false;
	}
	// debugcommand added 2003.05.11
	bool Set( int iID, T t )
	{
		if( iID < 0 || iID >= m_iSize )
			return false;

        __asm {lfence}
		m_pData[ iID ] = t;
		return true;
	}
	
	void Destory()
	{
		if( m_pData )
			delete[] m_pData;
		if( m_pUsed )
			delete[] m_pUsed;
	}
	~CStaticArray(void)
	{
        Destory();
		//if( m_pData )
		//	delete[] m_pData;
		//if( m_pUsed )
		//	delete[] m_pUsed;
	}
};

















template<class T,const int tArraySize>
class CStaticArray2
{	
	T		m_pData[tArraySize];
	char	m_pUsed[tArraySize];						//1-used else empty
	int		m_iUsed,m_iSize;
	int     m_iAllocLastID;

public:

	CStaticArray2()
	{
		//m_pData = new T[iSize];
		//m_pUsed = new char[iSize];
		memset( m_pUsed,0,tArraySize );
		m_iUsed = 0;
		m_iSize = tArraySize;
		m_iAllocLastID = 0;
	}
	void GetNextID()
	{
		m_iAllocLastID++;
		if( m_iAllocLastID >= m_iSize )
		{
			m_iAllocLastID = 0;
		}
	}
	int MallocID(int BeginID)
	{
		int count = BeginID;
		while((count>=0) && (count < m_iSize))
		{
			if( 1 != m_pUsed[count] )
			{
				m_pUsed[count] = 1;
				m_iUsed ++;
				return count;
			}
			count++;
		}
		return -1;
	}
	//
	int MallocLoopID()
	{

		int count = 0;
		while( count < m_iSize )
		{
			if( 1 != m_pUsed[ m_iAllocLastID ] )
			{
				m_pUsed[ m_iAllocLastID ] = 1;
				m_iUsed ++;
				return m_iAllocLastID;
			}
			GetNextID();
			count++;
		}
		return -1;
	}
	int Malloc()
	{
		int i;
		for( i = 0 ; i < m_iSize ; i ++ )
		{
			if( 1 != m_pUsed[ i ] )
			{
				m_pUsed[ i ] = 1;
				m_iUsed ++;
				return i;
			}
		}
		return -1;
	}
	//请求分配某一个位置上的
	int Malloc( int iPos )
	{
		if( iPos < 0 || iPos >= m_iSize )
			return -1;
		if( 1 != m_pUsed[ iPos ] )
		{
			m_pUsed[ iPos ] = 1;
			m_iUsed ++;
			return iPos;
		}		
		return -1;
	}
	void Free( int iID )
	{
		if( iID < 0 || iID >= m_iSize )
			return;
		if( 0 == m_pUsed[iID] )
			return;
		m_pUsed[iID] = 0;
		m_iUsed --;
	}
	T* operator[]( int iID )
	{
		if( iID < 0 || iID >= m_iSize )
			return 0;
		//没有使用，返回0
		if( 0 == m_pUsed[ iID ] )
			return 0;
		return (m_pData + iID);
	}

	int GetIDFromData( T* pT )
	{
		int iID =  pT-m_pData;
		return iID;
	}

	int GetUsed()
	{
		return m_iUsed;
	}
	int GetSize()
	{
		return m_iSize;
	}
	bool IsUsed(int iID)
	{
		if( iID < 0 || iID >= m_iSize )
			return false;
		if( 1 == m_pUsed[ iID ] )
			return true;
		return false;
	}
	// debugcommand added 2003.05.11
	bool Set( int iID, T t )
	{
		if( iID < 0 || iID >= m_iSize )
			return false;
		m_pData[ iID ] = t;
		return true;
	}


	~CStaticArray2(void)
	{
		//if( m_pData )
		//	delete[] m_pData;
		//if( m_pUsed )
		//	delete[] m_pUsed;
	}
};
//#pragma message ( " g_staticarray.h [->]")