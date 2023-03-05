#include "DumpInfo.h"
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"

#include "tstring.h"

static const char* g_pszDumpInfoTempFile = "DumpInfoTempFile";

static const char* g_pszRootName = "DumpInfo";
static const char* g_pszDumpFilename = "DumpFilename";
static const char* g_pszContent = "Content";
static const char* g_pszCustomSystemFilename = "CustomSystemFilename";
static const char* g_pszCustomGameFilename = "CustomGameFilename";
//--------------------------------------------------------------------
DumpInfo::DumpInfo()
{}
//--------------------------------------------------------------------
DumpInfo::~DumpInfo()
{}
//--------------------------------------------------------------------
bool DumpInfo::SaveDumpInfo()
{
	MeXmlDocument doc;
	doc.InsertEndChild(	
		MeXmlDeclaration( "1.0","utf-8","yes" ) );

	MeXmlElement* pRoot = doc.InsertEndChild( 
		( g_pszRootName ) );
	if( !pRoot )
		return false;

	// save dumper file path
	pRoot->ToElement()->SetAttribute( g_pszDumpFilename, 
		m_strDumpFileName.c_str() );

	// save dump content
	pRoot->ToElement()->SetAttribute( g_pszContent,
		m_strContent.c_str() );

	if( m_strCustomSystemSettingFile != "" )
	{
		// save custom system setting file path	
		pRoot->ToElement()->SetAttribute( g_pszCustomSystemFilename,
			m_strCustomSystemSettingFile.c_str() );
	}

	if( m_strCustomGameSettingFile != "" )
	{
		// save custom game setting file path
		pRoot->ToElement()->SetAttribute( g_pszCustomGameFilename,
			m_strCustomGameSettingFile.c_str() );
	}

	if( !doc.SaveFile( g_pszDumpInfoTempFile ) )
		return false;

	return true;
}
//--------------------------------------------------------------------
bool DumpInfo::LoadDumpInfo()
{

	MeXmlDocument doc;
	if( !doc.LoadFile( g_pszDumpInfoTempFile ) )
		return false;

	MeXmlElement* pRoot = doc.FirstChildElement( 
		g_pszRootName );
	if( !pRoot )
		return false;

	// read dumper file path
	const char* pszTemp = pRoot->ToElement()->Attribute( 
		g_pszDumpFilename );
	if( pszTemp )
		m_strDumpFileName = pszTemp;

	// read content
	pszTemp = pRoot->ToElement()->Attribute( g_pszContent );
	if( pszTemp )
		m_strContent = pszTemp;

	// read custom system setting file path
	pszTemp = pRoot->ToElement()->Attribute( g_pszCustomSystemFilename );
	if( pszTemp )
		m_strCustomSystemSettingFile = pszTemp;
	// read custom game setting file path
	pszTemp = pRoot->ToElement()->Attribute( g_pszCustomGameFilename );
	if( pszTemp )
		m_strCustomGameSettingFile = pszTemp;

	return true;
}
//--------------------------------------------------------------------
void DumpInfo::DeleteTempFile()
{
	::DeleteFile( g_pszDumpInfoTempFile );
}
//--------------------------------------------------------------------
bool DumpInfo::CheckDumpTempFile()
{
	// check dump temp file
	WIN32_FIND_DATAA data;
	HANDLE hFind = FindFirstFile( g_pszDumpInfoTempFile,&data);
	return (hFind != INVALID_HANDLE_VALUE);
}