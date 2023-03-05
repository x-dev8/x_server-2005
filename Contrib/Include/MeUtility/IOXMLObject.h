#ifndef XML_IO_H
#define XML_IO_H

#include "XMLParser.h"
#include <STRING>

using namespace std;

class IOObject
{
public:
	IOObject()
	{
	}
//public:
//	virtual bool Read( const char *path );
//	virtual bool Read( const char *path );
};
class IOXMLObject// :public IOObject
{
public:

	enum
	{
		eMaxName = 64
	};
 // public:
	//ofstream  m_xmlFile;
	//
 //public:
	//void beginFlag(string str);
	//void endFlag(string str);
  public:
    IOXMLObject(const char *ioname);
	virtual ~IOXMLObject(){}

	virtual bool loadXMLBuffer( char *pBuffer , int nSize  );
	virtual bool loadXMLSettings(const char *path  );
	virtual bool loadXMLSettings(XMLElement *element)   = 0;

	virtual bool exportXMLSettings(std::ofstream &xmlFile  ) = 0;
	virtual bool exportXMLSettings(const char* xmlPath);

    bool    isSuitable(XMLElement *element);
  protected:
    char ioname[eMaxName];
};

class IOXMLObjectInstance :public IOXMLObject
{
public:
	IOXMLObjectInstance(const char *ioname)
		:IOXMLObject(ioname)
	{


	}
	virtual ~IOXMLObjectInstance()
	{}

public:
//	virtual bool loadXMLBuffer( const char *path, INT nSize  )
//	{
//
//	}
	virtual bool loadXMLSettings(const char *path  )
	{
		return IOXMLObject::loadXMLSettings(path);
	}
	virtual bool loadXMLSettings(XMLElement *element)   = 0;
	virtual bool exportXMLSettings(std::ofstream &xmlFile  ) = 0;
	virtual bool exportXMLSettings(const char* xmlPath)
	{
		return IOXMLObject::exportXMLSettings( xmlPath );
	}
public:
	static std::ofstream  m_xmlFile;	
	std::ofstream  *m_pFile;
public:
	
	
	void closeFile();

	void endFlag(std::ofstream &xmlFile,string str);
	void writeBuffer(std::ofstream &xmlFile,const char *Buffer, int nLegth );
	void EndParam(std::ofstream &xmlFile);
	void writeFloat(std::ofstream &xmlFile,string str, float fValues );
	void writeInt(std::ofstream &xmlFile,string str, int nValues );
	void writeBool(std::ofstream &xmlFile,string str, bool bValues );
	void writeDouble(std::ofstream &xmlFile,string str, double dbValues );
	void writeString(std::ofstream &xmlFile, string str, const char *Buffer, int nLegth );
	//void writeWord(string str, WORD wValues );
	//void writeDword(string str, DWORD dwValues );
	void beginFlag(std::ofstream &xmlFile,string str);
	void EndFlag(std::ofstream &xmlFile,string str);
	void beginFlagNoParam(std::ofstream &xmlFile,string str);

	void endFlag(string str);
	void writeBuffer(const char *Buffer, int nLegth );
	void EndParam();
	void writeFloat(string str, float fValues );
	void writeInt(string str, int nValues );
	void writeBool(string str, bool bValues );
	void writeDouble(string str, double dbValues );
	void writeString( string str, const char *Buffer, int nLegth );
	//void writeWord(string str, WORD wValues );
	//void writeDword(string str, DWORD dwValues );
	void beginFlag(string str);
	void EndFlag(string str);
	void beginFlagNoParam(string str);
};
extern char *nullChar;
#endif
























