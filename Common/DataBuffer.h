/********************************************************************
	Filename: 	DataBuffer.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_DATABUFFER_H__
#define __COMMON_DATABUFFER_H__

#include "MeRTLibs.h"
//#include "g_assert.h"
#include "Mutex.h"
#include "MsgBase.h"

#ifndef HAVE_BYTE
typedef unsigned char byte;
#endif // HAVE_BYTE

#pragma warning( push )
#pragma warning( disable : 4996)
//////////////////////////////////////////////////////////////////////////
//数据队列管理类
template <const int _max_line, const int _max_size>
class DataBufferTPL
{
public:

    bool Add( byte *data )        // 加入队列数据
    {
        assert( data );
        m_ControlStatus = false;
        
        if( IsFull() ) 
        {
            //// ToLog( false );
            return false;
        }
        
        memcpy( m_s_ptr, data, _max_size );
        
        NextSptr();
        m_NumData++;
        
        m_ControlStatus = true;
        return true;
    }    
    

    bool Get( byte *data )        // 从队列中取出数据
    {
        assert( data );
        m_ControlStatus = false;
        
        if( IsNull() ) 
            return false;
        
        memcpy( data, m_e_ptr, _max_size );
        
        NextEptr();
        m_NumData--;
        
        m_ControlStatus = true;
        return true;
    }
    
    
    bool CtrlStatus()            // 获取操作成功结果
    {
        return m_ControlStatus;
    }
    
    
    int GetNumber()                // 获得现在的数据大小
    {
        return m_NumData;
    }

public:

    DataBufferTPL()
    {
        m_NumData    = 0;
        m_start_ptr    = m_DataTeam[0];
        m_end_ptr    = m_DataTeam[_max_line-1];
        m_s_ptr        = m_start_ptr;
        m_e_ptr        = m_start_ptr;
    }
    ~DataBufferTPL()
    {
        m_NumData    = 0;
        m_s_ptr        = m_start_ptr;
        m_e_ptr        = m_start_ptr;
    }

private:

    bool IsFull()        // 是否队列满
    {
        assert( m_NumData >=0 && m_NumData <= _max_line );
        if( m_NumData == _max_line ) 
            return true; 
        else 
            return false;
    }
    bool IsNull()        // 是否队列空
    {
        assert( m_NumData >=0 && m_NumData <= _max_line );
        if( m_NumData == 0 )
            return true;
        else
            return false;
    }
    void NextSptr()        // 头位置增加
    {
        // ToLog(m_start_ptr);
        // ToLog(m_end_ptr);
        // ToLog(m_s_ptr);
        // ToLog(m_e_ptr);
        m_s_ptr += _max_size;
        if( m_s_ptr > m_end_ptr )
            m_s_ptr = m_start_ptr;
    }
    void NextEptr()        // 尾位置增加
    {
        // ToLog(m_start_ptr);
        // ToLog(m_end_ptr);
        // ToLog(m_s_ptr);
        // ToLog(m_e_ptr);
        m_e_ptr += _max_size;
        if( m_e_ptr > m_end_ptr )
            m_e_ptr = m_start_ptr;
    }

private:

    byte    m_DataTeam[_max_line][_max_size];    //数据缓冲
    int        m_NumData;                            //数据个数
    bool    m_ControlStatus;                    //操作结果

    byte    *m_start_ptr;                        //起始位置
    byte    *m_end_ptr;                            //结束位置
    byte    *m_s_ptr;                            //排队起始位置
    byte    *m_e_ptr;                            //排队结束位置
};

//////////////////////////////////////////////////////////////////////////
// ID自动补位列表模板，用于自动列表，无间空顺序列表。
template < class IdType, const int nMaxCount>
class IDListTPL : public CSemiAutoIntLock
{
public:    
    void Reset() 
    { // 清除重置
        memset( m_wList, 0, sizeof(m_wList) );
        m_counter = 0;
        m_nPlayerCounter = 0;
    }

    int MaxSize()     const { return nMaxCount; }
    int Count()       const { return m_counter; }
    int PlayerCount() const { return m_nPlayerCounter; } //玩家的数量

    // 获得删除的index
    int  GetDeleteIndex()             { return m_nDeleteIndex; }
    void SetDeleteIndex( int nIndex ) { m_nDeleteIndex = nIndex; }

    const IdType operator[]( int iIndex ) 
    { 
        if ( iIndex < 0 || iIndex >= m_counter)
        { return 0;}

        return m_wList[ iIndex ]; 
    }

    bool AddNoCheckOnly( IdType id, bool bPlayer)
    {
        if( m_counter < 0 || m_counter >= nMaxCount ) 
        { return false; }

        m_wList[m_counter] = id;
        m_counter++;

        if( bPlayer )
        { m_nPlayerCounter++; }

        return true;
    }

    bool New( IdType id, bool bPlayer)
    {
        CSALocker locker(this);
        assert( m_counter >= 0 && m_counter < nMaxCount );
        
        //ID 唯一性，不能存在相同ID
        if ( Find( id ) != -1 ) 
        { return false; }

        m_wList[m_counter] = id;
        m_counter++;

        if( bPlayer )
        { m_nPlayerCounter++; }

        return true;
    }
    
    bool Add( IdType id, bool bPlayer)
    { // 没有Assert的加入ID功能
        CSALocker locker(this);
        if ( m_counter <0 || m_counter >= nMaxCount) 
        { return false; }

        //ID 唯一性，不能存在相同ID
        if ( Find( id ) != -1) 
        { return false; }

        m_wList[m_counter] = id;
        m_counter++;

        if( bPlayer )
        { m_nPlayerCounter++; }

        return true;
    }

    bool Del( int iIndex, bool bPlayer )
    {
        CSALocker locker(this);
        assert( iIndex >= 0 && iIndex < m_counter );
        if (iIndex < 0 || iIndex >= m_counter)
        { return false; }

        // 将最后的元素移动到删除点
        if( iIndex < m_counter - 1 && iIndex >= 0)
        { m_wList[ iIndex ] = m_wList[ m_counter-1 ]; }

        m_wList[ m_counter-1 ] = 0;
        m_counter--;

        if( bPlayer )
        {
            if( m_nPlayerCounter > 0 )
            { m_nPlayerCounter--; }
        }

        SetDeleteIndex( iIndex );
        return true;
    }
    
    bool Del( IdType id )
    {
        CSALocker locker(this);
        int iIndex = Find( id );
        return Del( iIndex, false );
    }

    int Find( IdType id )
    {
        for( int i=0; i < m_counter; i++ )
        {
            if( m_wList[i] == id ) 
            { return i; }
        }
        return -1;
    }

    bool CopyCharList( IdType* pustList, int nSize )
    {
        if ( pustList == NULL || nSize < m_counter )
        { return false; }

        memcpy_s( pustList, nSize * sizeof( IdType ), m_wList, m_counter * sizeof( IdType ) );

        return true;
    }

    IDListTPL() : m_counter(0), m_nPlayerCounter(0)
    { // 根据m_counter来加没有必要Reset
        // Reset();
        m_nDeleteIndex = -1;
    }

    virtual ~IDListTPL(){}

private:
    IdType m_wList[nMaxCount]; // 为节省内存，这里使用WORD (此处能为地图带来节省近一半的内存开销)
    int    m_nPlayerCounter  ; // 玩家的数量
    int    m_counter         ;
    int    m_nDeleteIndex    ;
};

//////////////////////////////////////////////////////////////////////////
template< typename _DataType, const int _MaxCount >
class TDataQueue
{
public:
    TDataQueue()
    {
        m_Counter = 0;
        m_Pointer = 0;
    }
    
    void Reset()
    {
        m_Counter = 0;
        m_Pointer = 0;
    }
    
    void Copy( _DataType &Dst, _DataType &Src )
    {
        memcpy( &Dst, &Src, sizeof(_DataType) );
    }

    void Join( _DataType &Data )
    {
        Copy( m_DataQ[m_Pointer], Data );
        m_Pointer++;
        m_Counter++;
        if( m_Pointer >= _MaxCount )
            m_Pointer = 0;
        if( m_Counter >= _MaxCount )
            m_Counter = _MaxCount;
    }
    
    _DataType *KickOut()
    {
        if( m_Counter <= 0 )
            return NULL;

        m_Pointer--;
        if( m_Pointer < 0 )
            m_Pointer = _MaxCount - 1;
        m_Counter--;
        return &m_DataQ[m_Pointer];
    }
    int Count() { return m_Counter; }

protected:

private:

    // 数据区
    _DataType m_DataQ[_MaxCount];
    // 当前总数
    int m_Counter;
    // 当前指向的位置，就是增加时加入到的位置
    int m_Pointer;
};

#pragma warning( pop )

#endif //__DATABUFFER_H__