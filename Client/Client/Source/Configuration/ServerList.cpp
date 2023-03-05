#include <windows.h>
#include "serverlist.h"
#include "WordParser.h"
#include "UI\Login.h"
#include "FuncPerformanceLog.h"
#include "Cfg.h"
#include "tstring.h"
//#include "Launcher/DataLauncher.h"
#include "RapidXml/MeRapidXml.h"
#include "ICMPPing.h"

#define XML_SERVERLIST_FILE ".\\ServerList.config"

DWORD WINAPI GetServerListPingThreadProc( LPVOID lpParam )
{
	CServerList::ServerData* pServer = ( CServerList::ServerData* )lpParam;
	if ( !pServer )
		return 0;

	CICMPPing cicmp;
	int nPing = cicmp.GetPingTime(const_cast< char* >(pServer->strIpAddr.c_str()));

	pServer->nPing = nPing;

	return 0;
}

CServerList::CServerList(void) : bLoad(false)
{
	guardfunc;
    m_vctBigAreaList.clear();
	unguard;
}

CServerList::~CServerList(void)
{
	guardfunc;
    m_vctBigAreaList.clear();
	unguard;
}

template< class T > 
inline T Clamp( const T&V, const T& minV, const T& maxV )
{
    if( V<minV ) 
        return minV;
    else if( V>maxV )
        return maxV;
    return V;
}

bool CServerList::LoadFromGlobalConfig()
{
	if( bLoad )
		return true;

    m_vctBigAreaList.clear();
	MeXmlDocument ServerListXMLDocument;
	if( !ServerListXMLDocument.LoadFile( XML_SERVERLIST_FILE ) )
	{
		assert( 0 && "没有server list" );
		return false;
	}
    MeXmlElement* pProjectRoot = ServerListXMLDocument.FirstChildElement("Project");
    if ( !pProjectRoot )
        return false;

    // 大区
	MeXmlElement* pBigAreaElement = pProjectRoot->FirstChildElement( "BigArea" );
    while( pBigAreaElement )
    {
        BigAreaData kBigAreaData;
        const char* pszBigArea = pBigAreaElement->Attribute( "Name" );
        kBigAreaData.strBigArea = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszBigArea).c_str());

        MeXmlElement* pBroadcast = pBigAreaElement->FirstChildElement("Broadcast");
        if(pBroadcast != NULL)
        {
           const char* pszBroadcast = pBroadcast->Attribute("String");
           kBigAreaData.strBroadCast = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszBroadcast).c_str());
        }

        MeXmlElement* pAreas = pBigAreaElement->FirstChildElement("Areas");  //Areas
        if(pAreas == NULL)
            return false;

        // 区
        MeXmlElement* pAreaElement = pAreas->FirstChildElement( "Area" );
        while( pAreaElement )
        {
            AreaData kAreaData;
            const char* pszArea = pAreaElement->Attribute( "Name" );
            kAreaData.strArea = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszArea).c_str());
                          
            // 服务器
            MeXmlElement* pServerElement = pAreaElement->FirstChildElement( "Server" );
            while( pServerElement )
            {
                ServerData kServerData;
                const char* pszServer = pServerElement->Attribute( "Name" );
                kServerData.strServer = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszServer).c_str());

                const char* pszStatus = pServerElement->Attribute( "StatusStr" );
                if( pszStatus )
                {
                    kServerData.strStatus = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszStatus).c_str());
                    int color = 0;
                    int R = 0;
                    int G = 0;
                    int B = 0;
                    pServerElement->QueryIntAttribute( "ColorR", &color );
                    R = Clamp<int>( color, 0x0, 0xFF );
                    pServerElement->QueryIntAttribute( "ColorG", &color );
                    G = Clamp<int>( color, 0x0, 0xFF );
                    pServerElement->QueryIntAttribute( "ColorB", &color );
                    B = Clamp<int>( color, 0x0, 0xFF );
                    kServerData.dwStatusColor = (0xff << 24) | ((R&0xff) << 16) | ((G&0xff) << 8) | (B&0xff);
                }
                else
                {
                    kServerData.strStatus = "";
                    kServerData.dwStatusColor = 0xffffffff;
                }
                const char* pszCommon = pServerElement->Attribute("Comment");
                kServerData.strCommon = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszCommon).c_str());

                const char* pszIp = pServerElement->Attribute( "Ip" );
                kServerData.strIpAddr = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszIp).c_str());
                
                int nPort;
                pServerElement->QueryIntAttribute( "Port", &nPort );
                kServerData.wPort = (WORD)nPort;

				const char* pszHttp = pServerElement->Attribute( "http" );
				kServerData.strHttpAddr = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszHttp).c_str());

				int nStatus;
				pServerElement->QueryIntAttribute( "Status", &nStatus );
				kServerData.unStatus = nStatus;

				int nIsNew;
				pServerElement->QueryIntAttribute( "IsNew", &nIsNew );
				kServerData.unIsNew = nIsNew;

				int nIsRecommend;
				pServerElement->QueryIntAttribute( "IsRecommend", &nIsRecommend );
				kServerData.unIsRecommend = nIsRecommend;

				int nIsVehemence;
				pServerElement->QueryIntAttribute( "IsVehemence", &nIsVehemence );
				kServerData.unIsVehemence = nIsVehemence;

                kAreaData.vctServerList.push_back(kServerData);
                pServerElement = pServerElement->NextSiblingElement( "Server" );

            }

            kBigAreaData.vctAreaList.push_back(kAreaData);
            pAreaElement = pAreaElement->NextSiblingElement( "Area" );
        }

        m_vctBigAreaList.push_back(kBigAreaData);
        pBigAreaElement = pBigAreaElement->NextSiblingElement( "BigArea" );
    }

	RefreshPing();

	bLoad = true;

	return true;
}

void CServerList::RefreshPing()
{
	for ( int i=0; i<m_vctBigAreaList.size(); ++i )
	{
		std::vector<AreaData>* pAreaList = &m_vctBigAreaList[i].vctAreaList;
		if ( pAreaList )
		{
			for(int j=0; j<pAreaList->size(); ++j)
			{
				std::vector<ServerData>* pServerList = &(*pAreaList)[j].vctServerList;
				if( pServerList )
				{
					for(int k=0; k<pServerList->size(); ++k)
					{
						HANDLE handle = CreateThread( NULL, 0, GetServerListPingThreadProc, &(*pServerList)[k], 0, NULL );
					}
				}
			}
		}
	}
}

std::vector<CServerList::AreaData>* CServerList::GetAreaList( const char* strBigArea )
{
    if( m_vctBigAreaList.size() )
    {
        for(int i=0; i<m_vctBigAreaList.size(); ++i)
        {
            if( !m_vctBigAreaList[i].strBigArea.compare(strBigArea) )
                return &m_vctBigAreaList[i].vctAreaList;
        }
    }
    return NULL;
}

std::vector<CServerList::ServerData>* CServerList::GetServerList( const char* strBigArea, const char* strArea )
{
    std::vector<AreaData>* pAreaList = GetAreaList(strBigArea);
    if( pAreaList )
    {
        for(int i=0; i<pAreaList->size(); ++i)
        {
            if( !(*pAreaList)[i].strArea.compare(strArea) )
            {
                return &(*pAreaList)[i].vctServerList;
            }
        }
    }
    return NULL;
}

CServerList::ServerData* CServerList::GetServerData( const char* strBigArea, const char* strArea, const char* strServer )
{
    std::vector<ServerData>* pServerList = GetServerList(strBigArea, strArea);
    if( pServerList )
    {
        for(int i=0; i<pServerList->size(); ++i)
        {
            if( !(*pServerList)[i].strServer.compare(strServer) )
            {
                return &(*pServerList)[i];
            }
        }
    }
    return NULL;
}

const char* CServerList::GetBigAreaName( int id )
{
	if( !bLoad )
		return NULL;

    if( m_vctBigAreaList.size() > id )
    {
        return m_vctBigAreaList[id].strBigArea.c_str();
    }
    return NULL;
}

const char* CServerList::GetBigAreaBroadcast(int id)
{
	if( !bLoad )
		return NULL;

    if(m_vctBigAreaList.size() > id)
        return m_vctBigAreaList[id].strBroadCast.c_str();
    return NULL;
}
