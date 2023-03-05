#include "IOXMLObject.h"
#include "MediaPathManager.h"
#include "FuncPerformanceLog.h"

#pragma warning(disable:4706)

//IOXMLObjectInstance GOXMLObjectInstance;
IOXMLObject::IOXMLObject(const char *ionameArg)
{
	if( ionameArg )
		strncpy_s( ioname, eMaxName, ionameArg, eMaxName-1 );
}

bool IOXMLObject::loadXMLBuffer( char *pBuffer, int nSize  )
{
	if( strlen(ioname) == 0 )
		return Logger::writeErrorLog("Cannot load XML settings -> NULL element name");
	XMLElement  *child  = NULL;
	XMLStack     xmlStack;

	if( !xmlStack.loadXMLBuffer( pBuffer, nSize ) )
		return Logger::writeErrorLog(string("Invalid XML file -> ") + "Buffer");

	if(!(child = xmlStack.getChildByName(ioname)))
		return Logger::writeErrorLog(string("Need a <") + ioname + "> tag in the XML file");

	return loadXMLSettings(child);
}

bool IOXMLObject::loadXMLSettings(const char* path)
{
	guardfunc
  if( strlen(ioname) == 0 )
    return Logger::writeErrorLog("Cannot load XML settings -> NULL element name");

//  const char *verified = MediaPathManager::lookUpMediaPath(path);
  const char *verified = (path);

  if(!verified)
    return Logger::writeErrorLog(string("Couldn't locate the <") +
                                 ioname + "> XML file at \""       +
                                 path   + "\" even with a look up");
	
  XMLElement  *child  = NULL;
  XMLStack     xmlStack;

  if(!xmlStack.loadXMLFile(verified))
    return Logger::writeErrorLog(string("Invalid XML file -> ") + verified);

  if(!(child = xmlStack.getChildByName(ioname)))
    return Logger::writeErrorLog(string("Need a <") + ioname + "> tag in the XML file");

  return loadXMLSettings(child);
  unguard;
}

bool IOXMLObject::exportXMLSettings(const char* xmlPath)
{
	ofstream xmlFile(xmlPath, ios::app | ios::binary);
	bool result = exportXMLSettings(xmlFile);
	xmlFile.close();
	return result;
}

bool IOXMLObject::isSuitable(XMLElement *element)
{
  if(!element)
    return  Logger::writeErrorLog(string("NULL <") + ioname +  "> node");

  if(element->getName() != ioname)
    return Logger::writeErrorLog(string("Need a <") + ioname + "> tag in the XML Node");

  return true;
}

std::ofstream  IOXMLObjectInstance::m_xmlFile;
void IOXMLObjectInstance::beginFlagNoParam(string str)
{
	m_xmlFile<< "<" << str << ">" <<endl;
}
void IOXMLObjectInstance::beginFlagNoParam( std::ofstream &xmlFile, string str)
{
	xmlFile<< "<" << str << ">" <<endl;
}


void IOXMLObjectInstance::EndFlag(std::ofstream &xmlFile,string str)
{
	xmlFile<< "</" << str << ">" <<endl;
}

void IOXMLObjectInstance::EndFlag(string str)
{
	m_xmlFile<< "</" << str << ">" <<endl;
}
void IOXMLObjectInstance::beginFlag(std::ofstream &xmlFile,string str)
{
	xmlFile<< "<" << str;
}
void IOXMLObjectInstance::beginFlag(string str)
{
	m_xmlFile<< "<" << str;
}
void IOXMLObjectInstance::writeInt(std::ofstream &xmlFile,string str, int nValues )
{
	xmlFile<< " " << str << " = " << '"'<<nValues << '"';
}
void IOXMLObjectInstance::writeInt(string str, int nValues )
{
	m_xmlFile<< " " << str << " = " << '"'<<nValues << '"';
}

void IOXMLObjectInstance::writeFloat(std::ofstream &xmlFile,string str, float fValues )
{
	xmlFile<< " " << str << " = " << '"'<<fValues << '"';
}

void IOXMLObjectInstance::writeFloat(string str, float fValues )
{
	m_xmlFile<< " " << str << " = " << '"'<<fValues << '"';
}

//void IOXMLObjectInstance::writeDword(string str, DWORD dwValues )
//{
//	m_xmlFile<< " " << str << " = " << '"'<< dwValues << '"';
//}
//
//void IOXMLObjectInstance::writeWord(string str, Word wValues )
//{
//	m_xmlFile<< " " << str << " = " << '"'<< wValues << '"';
//}
void IOXMLObjectInstance::writeDouble(std::ofstream &xmlFile,string str, double dbValues )
{
	xmlFile<< " " << str << " = " << '"'<< dbValues << '"';
}
void IOXMLObjectInstance::writeDouble(string str, double dbValues )
{
	m_xmlFile<< " " << str << " = " << '"'<< dbValues << '"';
}

//void IOXMLObjectInstance::write(string str, double dbValues )
//{
	//m_xmlFile<< " " << str << " = " << '"'<< dbValues << '"';
//}
void IOXMLObjectInstance::writeBool(std::ofstream &xmlFile,string str, bool bValues )
{
	xmlFile<< " " << str << " = " << '"'<< ( bValues ? "true":"false" )<< '"';
}
void IOXMLObjectInstance::writeBool(string str, bool bValues )
{
	m_xmlFile<< " " << str << " = " << '"'<< ( bValues ? "true":"false" )<< '"';
}

void IOXMLObjectInstance::writeString( std::ofstream &xmlFile,string str, const char *Buffer, int nLegth )
{
	xmlFile<< " " << str << " = " << '"';
	if ( !strcmp( Buffer, "" ) )
	{
		xmlFile.write( "NULL", 4 );
	}
	else
	{
		xmlFile.write( Buffer, nLegth );
	}
	xmlFile<< '"';
}

void IOXMLObjectInstance::writeString( string str, const char *Buffer, int nLegth )
{
	m_xmlFile<< " " << str << " = " << '"';
	if ( !strcmp( Buffer, "" ) )
	{
		m_xmlFile.write( "NULL", 4 );
	}
	else
	{
		m_xmlFile.write( Buffer, nLegth );
	}
	m_xmlFile<< '"';
}
void IOXMLObjectInstance::EndParam(std::ofstream &xmlFile)
{
	xmlFile<< ">" <<endl;
}
void IOXMLObjectInstance::EndParam()
{
	m_xmlFile<< ">" <<endl;
}
void IOXMLObjectInstance::closeFile()
{
	m_xmlFile.rdstate();
	m_xmlFile.clear();
	m_xmlFile.close();
}

void IOXMLObjectInstance::writeBuffer(std::ofstream &xmlFile,const char *Buffer, int nLegth )
{	
	xmlFile.write( Buffer, nLegth );
}

void IOXMLObjectInstance::writeBuffer(const char *Buffer, int nLegth )
{	
	m_xmlFile.write( Buffer, nLegth );
}

void IOXMLObjectInstance::endFlag(std::ofstream &xmlFile,string str)
{
	xmlFile<< "</" << str << ">"<<endl;
}

void IOXMLObjectInstance::endFlag(string str)
{
	m_xmlFile<< "</" << str << ">"<<endl;
}

























