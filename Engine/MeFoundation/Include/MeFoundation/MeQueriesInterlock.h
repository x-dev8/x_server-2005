#pragma once
/**
* @brief Use DirectX9's asynchronous query functionality
* to force CPU never gets more than a specified frames 
* ahead of the GPU.
*/
template< unsigned int LimitFrames >
class MEFOUNDATION_ENTRY MeQueriesInterlock
{
// Construction.
public:
	/// Constructor.
	MeQueriesInterlock( IDirect3DDevice9* pDevice ){
		m_uiFrames = 0;
		m_pD3d9Device = pDevice;
		m_pFirstQuery = 0;
		m_pSecondQuery = 0;
		if( m_pD3d9Device->CreateQuery( D3DQUERYTYPE_EVENT, &m_pFirstQuery ) != D3D_OK )
			m_pFirstQuery = 0;
		if( m_pD3d9Device->CreateQuery( D3DQUERYTYPE_EVENT, &m_pSecondQuery ) != D3D_OK )
			m_pSecondQuery = 0;
	}
	
	/// Destructor.
	~MeQueriesInterlock(){
		m_pD3d9Device = 0;
		if( m_pFirstQuery )
		{
			m_pFirstQuery->Release();
			m_pFirstQuery = 0;
		}
		if( m_pSecondQuery )
		{
			m_pSecondQuery->Release();
			m_pSecondQuery = 0;
		}		
	}

// Overload operator.
private:
	/// Disable default constructor.
	MeQueriesInterlock(){}

	/// Disable assignment operator.
	const MeQueriesInterlock& operator=( const MeQueriesInterlock& kClass ){ return *this; }

	/// Disable copy constructor.
	MeQueriesInterlock( const MeQueriesInterlock& kClass ){}

// Override.
public:

// Methods.
public:
	/// Update in main loop.
	inline void UpdateQueries(){
		if( !m_pFirstQuery || !m_pSecondQuery )
			return;

		int nLoopCount = 0;
		static const int cnMaxLoopCount = 1000000;
		if( m_uiFrames == 0 )
		{
			while( S_FALSE == m_pSecondQuery->GetData( NULL, 0, D3DGETDATA_FLUSH ) ){
				if( ++nLoopCount >= cnMaxLoopCount )
					break;
			}
			m_pFirstQuery->Issue( D3DISSUE_END );
		}
		else if( m_uiFrames == LimitFrames )
		{
			while( S_FALSE == m_pFirstQuery->GetData( NULL, 0, D3DGETDATA_FLUSH ) ){		
				if( ++nLoopCount >= cnMaxLoopCount )
					break;
			}
			m_pSecondQuery->Issue( D3DISSUE_END );
			m_uiFrames = 0;
			return;
		}
		++ m_uiFrames;
	}

// Members.
protected:
	/// Current frames [ 0 - LimitFrames ].
	unsigned int m_uiFrames;

	/// IDirect3DQuery9 objects.
	IDirect3DQuery9* m_pFirstQuery;
	IDirect3DQuery9* m_pSecondQuery;

	/// Device.
	IDirect3DDevice9* m_pD3d9Device;
};