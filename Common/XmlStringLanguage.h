#pragma once
#include <string>
#include <map>
// #include "Tinyxml\tinyxml.h"
#include "MeRTLibs.h"
#include "core/Name.h"

#pragma warning( push, 0 )
#pragma warning( disable : 4239)

#define String_Ext ".string"
#define Encrypt_String_Ext ".stringc"
#define Bin_String_Ext ".stringb"

#define Empty_String_Id -1
#define Empty_String_Value ""

#define STRING_DATA_ID				"M.E.S.T"	// �ַ����ļ����������ݸ�ʽ��ʶ
#define STRING_DATA_VERSION			10000		// �ַ����ļ����������ݰ汾����ʼ�汾��10000��ÿ�ε����汾�ŵ���1
#define STRING_DATA_BASE_VERSION	10000		// �ַ����ļ���ʼ�汾��


#define theXmlString XmlString::Instance()

class XmlString
{
public:
	XmlString();
	~XmlString();

	bool LoadStringPath(const char* pszPath, bool bClear = false, bool bEncrypt = false, bool bReplace = false, bool bWarning = true);  //�����ļ��������е�string�ļ�

	//pszPath = �ļ���·��  pszFile  = FileList�����ļ�����·��  �����ŵĶ��������pszFile���ļ�·��
	bool LoadStringFileList(const char* pszFile, bool bClear = false, bool bReplace = false, bool bWarning = true);  //����list�������ļ�

	//����String�ļ� ,�Ƿ����, ��ͬ�Ƿ񸲸�
	bool LoadStringFile(const char* pszFile, bool bClear = false, bool bReplace = false, bool bWarning = true); 

	//���ض�����stringb�ļ�
	bool LoadBinStringFile(const char* pszFile, bool bClear = false, bool bReplace = false, bool bWarning = true, bool bInsertEmpty = true);

	// ����ɶ�����stringb�ļ�
	bool SaveBinStringFile(const char* pszFile);

	//�����ļ�
	bool SaveStringFile(const char* pszFile, std::vector<int> &vecStringId = std::vector<int>() , bool bSaveEmpty = true);

	const char* GetString(const int nId);
	int GetId(std::string strName);

	int AddString(std::string strName);	//��ӣ����ظ��ִ�����
	int AddString(int nId, std::string strName, bool Replace = false);

	bool DeleteString(const int nId);

	void ClearString() { m_mapString.clear(); }

    const char* GetStringWithName( int nIndex );
    const char* GetStringWithAccountID( int nIndex );
    const char* GetStringWithAccountIDAndName( int nIndex );

	inline static XmlString& Instance()
	{
		static XmlString s_StringLanguage;

		return s_StringLanguage;
	}

    bool SaveBinFile( const char* pszFileName );

    bool LoadBinFile( const char* pszFileName );

	char*	ParseAtString(const char * szText );

private:
    typedef std::multimap<int, std::string>::iterator mapiter;
    std::multimap<int,std::string> m_mapString;
    std::string strWithNameFormat_;
};

#pragma warning( pop )
