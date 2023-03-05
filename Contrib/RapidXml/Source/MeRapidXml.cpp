#include "RapidXml/MeRapidXml.h"
/*
#ifdef DATA_LAUNCHER
#include "Cipher/cipher_factory.h"
#include "Launcher/DataLauncher.h"
#endif*/
#include "filepacket/packet_interface.h"
#include "RapidXml/rapidxml_print.h"
extern bool g_DirectReadInPackage;

bool MeXmlDocument::LoadFile( const char * filename,int nEncodeType /*= 1*/ )
{
	{
		/*
#ifdef DATA_LAUNCHER
		if (g_DirectReadInPackage)
		{
			fp = Cipher::CipherFactory::OpenCipherFile(filename);
			if (fp)
			{
				Parse(fp->_ptr);
				return true;
			}
		}
#endif
		{
			errno_t err = fopen_s( &fp, filename, "rb" );
			if (fp)
			{
				fseek(fp,0,SEEK_END);
				size_t dwSize = ftell(fp);
				rewind(fp);
				pdata = new char[dwSize + 1];
				fread(pdata,1,dwSize,fp);
				pdata[dwSize] = '\0';
				Parse(pdata);
				fclose(fp);
				fp = NULL;
				return true;
			}
		}*/

		return packet_namespace::LoadXML(*this,filename);
	
	}
	return false;
}

bool MeXmlDocument::LoadFromFile(const char * filename,int nEncodeType /*= 1*/ )
{
	errno_t err = fopen_s( &fp, filename, "rb" );
	if (fp)
	{
		fseek(fp,0,SEEK_END);
		size_t dwSize = ftell(fp);
		rewind(fp);
		pdata = new char[dwSize + 1];
		fread(pdata,1,dwSize,fp);
		pdata[dwSize] = '\0';
		Parse(pdata);
		fclose(fp);
		fp = NULL;
		return true;
	}
	return false;

}

MeXmlDocument::~MeXmlDocument()
{
	if (fp)
	{
		fclose(fp);
		fp = NULL;
	}
	if (pdata)
	{
		delete [] pdata;
	}
}

MeXmlElement* MeXmlDocument::FirstChildElement( const char *name , std::size_t name_size, bool case_sensitive  )
{
	return xDoc.first_node(name,name_size,case_sensitive);
}

MeXmlElement* MeXmlDocument::NextSiblingElement( const char *name, std::size_t name_size, bool case_sensitive  )
{
	return xDoc.next_sibling(name,name_size,case_sensitive);
}

MeXmlElement* MeXmlDocument::RootElement()
{
	return xDoc.first_node();
}

void MeXmlDocument::Parse(  char* p )
{
	
	switch (mFlag) 
	{
		case EPaserFlag_Default:
			{
				xDoc.parse<Me_parse_Default>(p);
			}
			break;
		case EPaserFlag_Fastest:
			{
				xDoc.parse<Me_parse_fastest>(p);
			}
			break;
		default:;
	}

}

MeXmlElement* MeXmlDocument::InsertEndChild( MeXmlDeclaration& xmlDeclaration )
{
	MeXmlElement* pXmlDeclaration = xDoc.allocate_node(node_declaration);
	MeXmlAttribute* pNewAttr = xDoc.allocate_attribute(xDoc.allocate_string("version"),xDoc.allocate_string(xmlDeclaration.m_version));
	pXmlDeclaration->append_attribute(pNewAttr);
	pNewAttr = xDoc.allocate_attribute(xDoc.allocate_string("encoding"),xDoc.allocate_string(xmlDeclaration.m_encoding));
	pXmlDeclaration->append_attribute(pNewAttr);
	pNewAttr = xDoc.allocate_attribute(xDoc.allocate_string("standalone"),xDoc.allocate_string(xmlDeclaration.m_standalone));
	pXmlDeclaration->append_attribute(pNewAttr);
	xDoc.append_node(pXmlDeclaration);
	return pXmlDeclaration;
}

MeXmlElement* MeXmlDocument::InsertEndChild( const char* name )
{
	MeXmlElement* pXmlElement = xDoc.allocate_node(node_element,xDoc.allocate_string(name));
	xDoc.append_node(pXmlElement);
	return pXmlElement;

}

bool MeXmlDocument::SaveFile( const char * filename )
{
	std::string s;
	print(std::back_inserter(s), xDoc, 0);

	FILE* fp = NULL;
	fopen_s(&fp, filename, "w" );
	if ( fp )
	{
		fprintf(fp,"%s",s.c_str());
		fclose( fp );
		return true;
	}
	return false;
}

void MeXmlDocument::Clear()
{
	xDoc.clear();
}

void MeXmlDocument::RemoveChild( MeXmlElement* pElement )
{
	xDoc.remove_node(pElement);
}

MeXmlElement* MeXmlDocument::RetriveCommentElement( const char* comment )
{
	return xDoc.allocate_node(node_comment,NULL,xDoc.allocate_string(comment));
}