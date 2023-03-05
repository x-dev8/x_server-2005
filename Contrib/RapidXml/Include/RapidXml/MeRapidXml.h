
#ifndef MERAPIDXML_INCLUDED
#define MERAPIDXML_INCLUDED

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4530 )
#pragma warning( disable : 4786 )
#endif

#include "stdio.h"
#include "RapidXml/rapidxml.h"

/** Always the top level node. A document binds together all the
	XML pieces. It can be saved, loaded, and printed to the screen.
	The 'value' of a document node is the xml file name.
*/
using namespace rapidxml;
typedef xml_node<> MeXmlElement;
typedef xml_attribute<> MeXmlAttribute;
struct MeXmlDeclaration
{
	MeXmlDeclaration(const char* _version,
		const char* _encoding,
		const char* _standalone)
	{
		if (_version)
		{
			strcpy_s(m_version,256,_version);
		}
		if (_encoding)
		{
			strcpy_s(m_encoding,256,_encoding);
		}
		if (_standalone)
		{
			strcpy_s(m_standalone,256,_standalone);
		}
	}
	char m_version[256];
	char m_encoding[256];
	char m_standalone[256];
};



class MeXmlDocument 
{
public:
	static const int Me_parse_Default = rapidxml::parse_no_data_nodes;
	static const int Me_parse_fastest = rapidxml::parse_no_string_terminators;
	enum EPaserFlag{
		EPaserFlag_Default = 0,
		EPaserFlag_Fastest,//见rapidxml::parse_no_string_terminators 说明

		EPaserFlag_Total,
	};
	/// Create an empty document, that has no name.
	MeXmlDocument(int flag = EPaserFlag_Default):
	  fp(NULL),pdata(NULL),mFlag(flag)
	{;}



	~MeXmlDocument();

	/// Load a file using the given filename. Returns true if successful.
	bool			LoadFromFile( const char * filename,int nEncodeType = 1);
	bool			LoadFile( const char * filename,int nEncodeType = 1);
	bool			SaveFile(const char * filename);
	MeXmlElement*	FirstChildElement(const char *name = 0, std::size_t name_size = 0, bool case_sensitive = true) ;
	MeXmlElement*	NextSiblingElement( const char *name = 0, std::size_t name_size = 0, bool case_sensitive = true) ;
	MeXmlElement*	RootElement() ;
	void			Parse(char* p);
	void			Clear();
	MeXmlElement*	InsertEndChild( MeXmlDeclaration& xmlDeclaration);
	MeXmlElement*	InsertEndChild(const char* name);
	void			RemoveChild(MeXmlElement* pElement);
	MeXmlElement*	RetriveCommentElement(const char* comment);
private:
	FILE* fp ;
	char* pdata ;
	int		mFlag;
	xml_document<> xDoc;
};


#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif

