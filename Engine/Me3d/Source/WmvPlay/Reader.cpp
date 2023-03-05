//*****************************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// FileName:            Reader.cpp
//
// Abstract:            Implementation of class CReader, which provides the
//                      functionality of reading from an IStream.
//
//*****************************************************************************

#include "Me3d/WmvPlay/StdAfx.h"
#include "Me3d/WmvPlay/Reader.h"
#include "Me3d/WmvPlay/AsyWmvStreamManager.h"
//#include "Launcher/DataLauncher.h"

//------------------------------------------------------------------------------
// Name: CReader()
// Desc: Constructor.
//------------------------------------------------------------------------------
CReader::CReader()
{
    m_cRef      = 1;
    m_pReader   = NULL;
    m_pReader2  = NULL;
    m_hEvent    = INVALID_HANDLE_VALUE;
    m_pStream   = NULL;
    m_hrAsync   = S_OK;
}

//------------------------------------------------------------------------------
// Name: ~CReader()
// Desc: Destructor.
//------------------------------------------------------------------------------
CReader::~CReader()
{
    SAFE_RELEASE( m_pReader );
    SAFE_RELEASE( m_pReader2 );
    SAFE_RELEASE( m_pStream );

    if( NULL != m_hEvent )
    {
        CloseHandle( m_hEvent );
        m_hEvent = INVALID_HANDLE_VALUE;
    }
}

//------------------------------------------------------------------------------
// Implementation of IUnknown methods
//------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CReader::QueryInterface( /* [in] */ REFIID riid,
                                                   /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject ) 
{
    if( ( IID_IWMReaderCallback == riid ) ||
        ( IID_IUnknown == riid ) )
    {
        *ppvObject = static_cast< IWMReaderCallback* >( this );
        AddRef();
        return( S_OK );
    }

    *ppvObject = NULL;
    return( E_NOINTERFACE );
}

ULONG STDMETHODCALLTYPE CReader::AddRef()
{
    return( InterlockedIncrement( &m_cRef ) );
}

ULONG STDMETHODCALLTYPE CReader::Release()
{
    if( 0 == InterlockedDecrement( &m_cRef ) )
    {
        delete this;
        return( 0 );
    }

    return( m_cRef );
}

//------------------------------------------------------------------------------
// Name: CReader::OnSample()
// Desc: Implementation of IWMReaderCallback::OnSample.
//------------------------------------------------------------------------------
HRESULT CReader::OnSample( /* [in] */ DWORD dwOutputNum,
                           /* [in] */ QWORD cnsSampleTime,
                           /* [in] */ QWORD cnsSampleDuration,
                           /* [in] */ DWORD dwFlags,
                           /* [in] */ INSSBuffer __RPC_FAR *pSample,
                           /* [in] */ void __RPC_FAR *pvContext )
{
    CAsyWmvStreamManager::Instance()->OnSample( dwOutputNum, cnsSampleTime, cnsSampleDuration, dwFlags, pSample, pvContext );

    return( S_OK );
}

//------------------------------------------------------------------------------
// Name: CReader::OnStatus()
// Desc: Implementation of IWMStatusCallback::OnStatus.
//------------------------------------------------------------------------------
HRESULT CReader::OnStatus( /* [in] */ WMT_STATUS Status,
                           /* [in] */ HRESULT hr,
                           /* [in] */ WMT_ATTR_DATATYPE dwType,
                           /* [in] */ BYTE __RPC_FAR *pValue,
                           /* [in] */ void __RPC_FAR *pvContext )
{
    switch( Status )
    {
    case WMT_OPENED:
    case WMT_STARTED:
    case WMT_STOPPED:
    case WMT_CLOSED:
    case WMT_EOF:
        {
            m_hrAsync = hr;
            SetEvent( m_hEvent );
            CAsyWmvStreamManager::Instance()->OnStatus( Status );
        }
        break;
    }

    return( S_OK );
}

//------------------------------------------------------------------------------
// Name: CReader::Open()
// Desc: Creates the reader and opens the file.
//------------------------------------------------------------------------------
HRESULT CReader::Open( /* [in] */ const TCHAR *ptszFile, OUT IWMReader** ppWMReader )
{
    HRESULT hr = S_OK;

    do
    {
        m_hrAsync = S_OK;

        //
        // Open input file
        //
        if( !OpenBuffer( ptszFile ) )
        {
            hr = E_FAIL;
            break;
        }

        //
        // Create the event handle as automatic reset; initial state is not set.
        //
        if( INVALID_HANDLE_VALUE == m_hEvent )
        {
            m_hEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
            if( NULL == m_hEvent )
            {
                hr = HRESULT_FROM_WIN32( GetLastError() );
                printf( "Could not Create Event. (hr=%#X)\n", hr );
                break;
            }
        }

        ResetEvent( m_hEvent );

        //
        // Create reader object
        //
        SAFE_RELEASE( m_pReader );
        SAFE_RELEASE( m_pReader2 );

        hr = WMCreateReader( NULL, WMT_RIGHT_PLAYBACK, &m_pReader );
        if( FAILED( hr ) )
        {
            printf( "Could not create reader (hr=%#X).\n", hr );
            break;
        }

        //
        // QI for IWMReaderAdvanced2 
        //
        hr = m_pReader->QueryInterface( IID_IWMReaderAdvanced2, ( void** )&m_pReader2 );
        if( FAILED( hr ) )
        {
            printf( "Could not QI for IWMReaderAdvanced2 (hr=%#X).\n", hr );
            break;
        }

        //
        // Open the stream
        //
        hr = m_pReader2->OpenStream( m_pStream, this, NULL );
        if( FAILED( hr ) )
        {
            printf( "Could not open reader from stream (hr=%#X).\n", hr );
            break;
        }
    
        //
        // Wait for the open to finish
        //
        hr = WaitForEvent();
        if( FAILED( hr ) )
        {
            printf( "Stream open failed (hr=%#X).\n", hr );
            break;
        }

        //
        // Check open operation result
        //
        if( FAILED( m_hrAsync ) )
        {
            hr = m_hrAsync;
            printf( "Open failed (hr=%#X).\n", m_hrAsync );
            break;
        }

        if( ppWMReader )
        {
            *ppWMReader = m_pReader;
        }
    }
    while( FALSE );

    return( hr );
}

// 增加读Buffer的接口，为了统一北京打包的接口         added by zhuomeng.hu		[4/11/2011]
bool CReader::OpenBuffer( const char* pszFile )
{
    FILE* pFile( NULL );
    fopen_s( &pFile, pszFile, "rb" );
    if( !pFile )
    {
        return false;
    }

    // 读取文件Buffer
    fseek( pFile, 0, SEEK_END );
    ULONG nLength = ftell( pFile );
    fseek( pFile, 0, SEEK_SET );
    BYTE* pBuffer = new BYTE[ nLength ];
    fread( pBuffer, nLength, 1, pFile );
    fclose( pFile );

    // 分配可移动内存空间
    HGLOBAL hGlobal = GlobalAlloc( GMEM_MOVEABLE, nLength );
    if( !hGlobal )
    {
        SAFE_DELETE_ARRAY( pBuffer );
        return false;
    }
    
    void* pData = GlobalLock( hGlobal );
    if( !pData )
    {
        GlobalFree( hGlobal );
        hGlobal = NULL;
        SAFE_DELETE_ARRAY( pBuffer );
        return false;
    }
    memcpy( pData, pBuffer, nLength );
    GlobalUnlock( hGlobal );

    // 创建IStream
    SAFE_DELETE_ARRAY( pBuffer );
    SAFE_RELEASE( m_pStream );
    m_pStream = new CROStream;
    HRESULT hr = CreateStreamOnHGlobal( hGlobal, TRUE, &m_pStream );
    if( FAILED( hr ) )
    {
        GlobalFree( hGlobal );
        hGlobal = NULL;
        SAFE_DELETE_ARRAY( pBuffer );
        return false;
    }

    return true;
}

//------------------------------------------------------------------------------
// Name: CReader::Start()
// Desc: Plays the file.
//------------------------------------------------------------------------------
HRESULT CReader::Start()
{
    HRESULT hr = S_OK;

    if( NULL == m_pReader )
    {
        return( E_UNEXPECTED );
    }

    //
    // Start the reader to play the stream normally
    //
    m_hrAsync = S_OK;

    hr = m_pReader->Start( 0, 0, 1.0, NULL );
    if( FAILED( hr ) )
    {
        printf( "Could not start IWMReader (hr=%#X).\n", hr );
        return( hr );
    }

    printf( "Playing......\n" );

    //
    // Wait until all data has been sent to output.
    // We don't know the file's duration, so simply wait forever and hope for the best.
    // In a real application, you might want to query for the file's duration.
    //
    hr = WaitForEvent( INFINITE );
    if( FAILED( hr ) )
    {
        printf( "Read operation failed (hr=%#X).\n", hr );
        return( hr );
    }

    //
    // Check playback results
    //
    if( FAILED( m_hrAsync ) )
    {
        printf( "IWMReader playback failed (hr=%#X).\n", m_hrAsync );
        return( hr );
    }

    printf( "Playback finished.\n" );

    return( S_OK );
}

//------------------------------------------------------------------------------
// Name: CReader::Close()
// Desc: Closes the reader.
//------------------------------------------------------------------------------
HRESULT CReader::Close()
{
    HRESULT hr = S_OK;

    if( NULL == m_pReader )
    {
        return( S_FALSE );
    }

    hr = m_pReader->Stop();
    hr = m_pReader->Close();
    if( FAILED ( hr ) )
    {
        printf( "Could not close Reader (hr=%#X).\n", hr );
        return hr;
    }

    hr = WaitForEvent();
    if( FAILED( hr ) )
    {
        printf( "Close operation failed (hr=%#X).\n", hr );
        return( hr );
    }

    return( hr );
}

//------------------------------------------------------------------------------
// Name: CReader::WaitForEvent()
// Desc: Waits for the event to be signaled.
//------------------------------------------------------------------------------
HRESULT CReader::WaitForEvent( /* [in] */ DWORD msWait )
{
    DWORD   dwRet = 0;
    DWORD   dwLastError = 0;
    HRESULT hr = S_OK;

    dwRet = WaitForSingleObject( m_hEvent, msWait );
    if( WAIT_OBJECT_0 == dwRet )
    {
        return( S_OK );
    }

    if( WAIT_TIMEOUT == dwRet )
    {
        printf( "Time out waiting for the event.\n" );
        return( HRESULT_FROM_WIN32( WAIT_TIMEOUT ) );
    }

    if( WAIT_FAILED == dwRet )
    {
        dwLastError = GetLastError();
        printf( "WaitForSingleObject() failed (LastError=%ld).\n", dwLastError );
        return( HRESULT_FROM_WIN32( dwLastError ) );
    }

    return( S_OK );
}

