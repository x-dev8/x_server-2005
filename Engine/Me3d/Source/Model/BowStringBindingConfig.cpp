#include <assert.h>
#include "Me3d/Model/BowStringBindingConfig.h"
#include "RapidXml/MeRapidXml.h"
#include "FilePath.h"
#include "../filepacket/packet_interface.h"
void CBowStringBindingMgr::LoadBindingListFromFile( int nModelId,const char* pBindingListFile )
{
// 	WIN32_FIND_DATAA data;
// 	HANDLE hFind = FindFirstFileA(pBindingListFile,&data);
// 	bool bFind = (hFind != INVALID_HANDLE_VALUE);
// 	if (!bFind)
// 		return;
    std::string strtarget_cipher = pBindingListFile;  // ¼ÓÃÜÎÄ¼þ
    strtarget_cipher += 'c';
    if( !packet_namespace::IsOpen( strtarget_cipher.c_str() ) && !packet_namespace::IsOpen( pBindingListFile ) )
        return;

	MeXmlDocument	m_doc;
	if (!m_doc.LoadFile(pBindingListFile))
	{
// 		OutputDebugString("error *.BowString in world !\n");
		return ;
	}
	CBowStringBindingList* pList = MeNew CBowStringBindingList;
	MeXmlElement* pRoot = m_doc.FirstChildElement("Project")->FirstChildElement("BowStringBindingList");

	if (!pRoot)
	{
		return;
	}
	MeXmlElement* pMapNode = pRoot->FirstChildElement( "BowStringBinding");
	while (pMapNode)
	{
		int startFrame = 0;
		int endFrame = 0;
		pMapNode->QueryIntAttribute("Start",&startFrame);
		pMapNode->QueryIntAttribute("End",&endFrame);
		if (endFrame >= startFrame)
		{
			pList->AddBindingInterval(startFrame,endFrame);
		}
		pMapNode = pMapNode->NextSiblingElement("BowStringBinding");
	}
	m_BindingListMap.insert(pair<int,CBowStringBindingList*>(nModelId,pList));
}

bool CBowStringBindingMgr::IsNeedBinding( int nModelId,int nFrame )
{
	map<int,CBowStringBindingList*>::iterator iter	= m_BindingListMap.find(nModelId);
	if (iter!= m_BindingListMap.end())
	{
		return (*iter).second->IsNeedBinding(nFrame);
	}
	return false;
}

CBowStringBindingMgr::~CBowStringBindingMgr()
{
	map<int,CBowStringBindingList*>::iterator iter	= m_BindingListMap.begin();
	while(iter != m_BindingListMap.end())
	{
		delete (*iter).second;
		++iter;
	}
}

bool CBowStringBindingMgr::IsExist( int nModelId )
{
	map<int,CBowStringBindingList*>::iterator iter	= m_BindingListMap.find(nModelId);
	return iter != m_BindingListMap.end();
}
void CBowStringBindingList::AddBindingInterval( int start, int end )
{
	m_beginList.push_back(start);
	m_endList.push_back(end);
}

bool CBowStringBindingList::IsNeedBinding( int nFrame )
{
	assert(m_endList.size() == m_beginList.size());
	for (size_t i = 0; i < m_beginList.size(); ++i)
	{
		if ( nFrame >= m_beginList[i] && nFrame <= m_endList[i])
		{
			return true;
		}
	}
	return false;
}
