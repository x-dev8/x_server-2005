//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#pragma once

template< typename Tt/*type*/, unsigned Ts/*size*/ >
class MEFOUNDATION_ENTRY MeDynamicAllocBuffer
{
	// public member functions
public:
	// ctor
	MeDynamicAllocBuffer()
	{
		m_size = Ts;
		m_pt = new Tt[ m_size ];
		memset(m_pt, 0, Ts * sizeof( Tt ) );
	}
	// ~ctor
	~MeDynamicAllocBuffer()
	{
		m_size = 0;
		delete [] m_pt;
		m_pt = NULL;
	}
	// cpy buff to m_pt
	void MemCpyToBuff( void* pSrc, size_t tSize )
	{
		if( !pSrc || !m_pt )
			return;

		CheckSize( tSize / sizeof( Tt ) );
		memcpy_s( m_pt, m_size * sizeof( Tt ), pSrc, tSize );
	}
	// cpy to buff from m_pt
	void MemCpyFromBuff( void* pDes, size_t tDesSize, size_t tSize )
	{
		if( !pDes || !m_pt )
			return;

		if( ( tSize / sizeof( Tt ) ) > m_size )
			return;

		memcpy_s( pDes, tDesSize, m_pt, tSize );
	}

	// protected member functions
protected:
	void CheckSize( size_t size ) 
	{ 
		if ( m_size > size )
			return;

		m_size = 2 * size; 
		delete [] m_pt;
		m_pt = NULL;
		m_pt = new Tt[ m_size ];
		memset(m_pt, 0, m_size * sizeof( Tt ) );
	}
	
	// protected members
protected:
	size_t m_size;
	Tt* m_pt;
};