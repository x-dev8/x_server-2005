#include "MeRTLibs.h"
#include "Me3d/Md5Manager.h"
#include "RapidXml/MeRapidXml.h"
#include "md5.h"
#include <fstream>
#include <algorithm>
#include <sys/stat.h>

Md5Manager::Md5Manager(void) : _bEnabled( false )
{
	m_bIsCheckRightMap = true;
	m_bIsCheckRightCScene = true;
	m_bIsCheckRightTerrain = true;
}

Md5Manager::~Md5Manager(void)
{
}

Md5Manager& Md5Manager::Instance()
{
    static Md5Manager mm;
    return mm;
}

void Md5Manager::Initialize(const std::string &filename)
{
    std::ifstream ifile( filename.c_str(), std::ios::binary );
    if( !ifile )
    {
        m_bIsCheckRightMap = false;
        m_bIsCheckRightCScene = false;
        m_bIsCheckRightTerrain = false;
        return ;
    }

    ifile.seekg( 0, std::ios::end );
    size_t len = ifile.tellg();
    ifile.seekg( 0, std::ios::beg );

    char* buf = new char[len];
    ifile.read( buf, len );
    ifile.close();

    for ( size_t i = 0; i < len; ++i )
    {
        buf[i] = buf[i] ^ 0x88;
    }

    MeXmlDocument doc;
	doc.Parse( buf ) ;
//     if( !doc.Parse( buf ) )
//     {
//         assert(false && "Md5Manager::Initialize 读取文件失误");
//         return;
//     }

    MeXmlElement* pRootNode = doc.FirstChildElement( "mapping" );
    if ( pRootNode )
    {
#if USE_MD5_VALIDATE
        MeXmlElement* md5Node = pRootNode->FirstChildElement( "fileMd5" );
        while ( md5Node )
        {
            const char* temp = md5Node->Attribute( "fileName" );
            if ( temp == NULL )
                continue;
            std::string name = temp;

            temp = md5Node->Attribute( "md5" );
            if ( temp == NULL )
                continue;
            std::string md5Value = temp;

            // 转换为全小写。
            std::transform( name.begin(), name.end(), name.begin(), tolower );

            _md5Map.insert( MD5Map::value_type( name, md5Value ) );

            md5Node = md5Node->NextSiblingElement( "fileMd5" );
        }
#else
        MeXmlElement* md5Node = pRootNode->FirstChildElement( "file" );
        while ( md5Node )
        {
            const char* temp = md5Node->Attribute( "fileName" );
            if ( temp == NULL )
            {
                md5Node = md5Node->NextSiblingElement( "file" );
                continue;
            }
            std::string name = temp;

            const char* ret = md5Node->Attribute( "size" );
            if ( ret == NULL )
            {
                md5Node = md5Node->NextSiblingElement( "file" );
                continue;
            }

            // 转换为全小写。
            std::transform( name.begin(), name.end(), name.begin(), tolower );

            long fileSize = atol( ret );
            _md5Map.insert( MD5Map::value_type( name, fileSize ) );

            md5Node = md5Node->NextSiblingElement( "file" );
        }
#endif
    }

    delete[] buf;
}

//void FileTimeToTime_t( const FILETIME&  ft, time_t *t )  
//{  
//    LONGLONG ll;  
//    ULARGE_INTEGER ui;  
//    ui.LowPart  = ft.dwLowDateTime;  
//    ui.HighPart = ft.dwHighDateTime;  
//
//    ll = ft.dwHighDateTime << 32 + ft.dwLowDateTime;  
//
//    *t = ((LONGLONG)(ui.QuadPart - 116444736000000000) / 10000000);  
//}

bool Md5Manager::ValidateMD5(const std::string& filename )
{
	return true;

    if ( !_bEnabled )
    {
        return true;
    }

    // 转换为全小写。
    std::string str = filename;
    std::transform( str.begin(), str.end(), str.begin(), tolower );

    MD5Map::const_iterator it = _md5Map.find( str );
    assert( it != _md5Map.end() );

    bool valided = true;
#if USE_MD5_VALIDATE
    std::ifstream file(filename.c_str(), std::ios::binary);
    if( !file )
    {
        _errorFilename = filename;
        return false;
    }

    // 验证MD5。
    if ( it != _md5Map.end() )
    {
        const std::string& md5Value = it->second;
        std::string newMd5Value = MD5(file).toString();

        valided = newMd5Value == md5Value;
    }
#else
    if ( it != _md5Map.end() )
    {
        struct _stat st;
        if( ::_stat( filename.c_str(), &st ) != -1 )
            valided = st.st_size == it->second;
        else
            valided = false;

        //HANDLE hFile = CreateFile( filename.c_str(), GENERIC_READ, 0,
        //    NULL, OPEN_EXISTING, 
        //    FILE_ATTRIBUTE_READONLY | FILE_FLAG_OVERLAPPED,
        //    NULL );
        //if ( INVALID_HANDLE_VALUE != hFile )
        //{
        //    FILETIME lastFileTime;
        //    SYSTEMTIME stUTCLast;
        //    GetFileTime( (HANDLE)hFile, NULL, NULL, &lastFileTime );
        //    CloseHandle( (HANDLE)hFile );

        //    time_t newTime;
        //    FileTimeToTime_t( lastFileTime, &newTime );
        //    valided = newTime == oldTime;
        //    assert( valided );
        //}
    }

#endif

    if ( !valided )
        _errorFilename = filename;
    else
        _errorFilename = "";
    return valided;
}

void Md5Manager::EnableMD5Validate( bool bEnabled )
{
	// 暂时关闭验证，测试用[QL]
	//_bEnabled = bEnabled;
}

void Md5Manager::SetMD5CheckRetMap(bool bRet)
{
	m_bIsCheckRightMap = bRet;
}

void Md5Manager::SetMD5CheckRetCScene(bool bRet)
{
	m_bIsCheckRightCScene = bRet;
}

void Md5Manager::SetMD5CheckRetTerrain(bool bRet)
{
	m_bIsCheckRightTerrain = bRet;
}
