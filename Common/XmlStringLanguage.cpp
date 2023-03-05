#include "XmlStringLanguage.h"
#include "tstring.h"
#include "application_config.h"
#include "packet_interface.h"
// modify by@lemon [5/10/2012] for packet
//#include "Launcher/DataLauncher.h"
// modify end
// modify by@lemon [5/10/2012] for packet
//#include "IPacketLib.h"
// modify end
#include "RapidXml/MeRapidXml.h"
#include <atlstr.h>
 


XmlString::XmlString()
{
	m_mapString.clear();
	m_mapString.insert(make_pair(Empty_String_Id, Empty_String_Value));
}

XmlString::~XmlString()
{
	m_mapString.clear();
}

bool XmlString::LoadStringPath(const char* pszPath, bool bClear /* = false*/, bool bEncrypt/* = false*/, bool bReplace /* = false*/, bool bWarning /* = true*/)
{
	if (pszPath == NULL || *pszPath == 0)
	{
		return false;
	}

	if (bClear) { m_mapString.clear(); }
	

	char szFile[_MAX_PATH + 1] = "";
	// 如果是加密文件，优先加载二进制格式，找不到再加载加密格式
	sprintf_s(szFile, sizeof(szFile) - 1, "%s\\*%s", pszPath, Bin_String_Ext);

	WIN32_FIND_DATA xFindData;         
	HANDLE hFile = FindFirstFile(szFile, &xFindData);   	
	if(hFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			char szStringFile[_MAX_PATH + 1] = "";
			sprintf_s(szStringFile, sizeof(szStringFile) - 1, "%s\\%s", pszPath, xFindData.cFileName);

			LoadBinStringFile(szStringFile, false, bReplace, bWarning); //加载

		}while(FindNextFile(hFile, &xFindData));                      
		FindClose(hFile);
	}
	else
	{
		if(bEncrypt)
		{
			//// modify by@lemon [4/11/2012] for packet
			sprintf_s(szFile, sizeof(szFile) - 1, "%s\\", pszPath);
			std::vector<std::string> vecFile;
			//g_pPacketMgr->SearchFile(szFile,String_Ext,vecFile);
			for (UINT n = 0; n < vecFile.size(); ++n)
			{
				char szStringFile[_MAX_PATH + 1] = "";
				sprintf_s(szStringFile, sizeof(szStringFile) - 1, "%s\\%s", pszPath, vecFile[n].c_str());

				LoadStringFile(szStringFile, false, bReplace, bWarning); //加载
			}
			//sprintf_s(szFile, sizeof(szFile) - 1, "%s\\*%s", pszPath, Encrypt_String_Ext);

			//hFile = FindFirstFile(szFile, &xFindData);   	
			//if(hFile != INVALID_HANDLE_VALUE)
			//{
			//	do
			//	{
			//		char szStringFile[_MAX_PATH + 1] = "";
			//		sprintf_s(szStringFile, sizeof(szStringFile) - 1, "%s\\%s", pszPath, xFindData.cFileName);

			//		if (bEncrypt) { szStringFile[strlen(szStringFile) - 1] = 0; }  //加密的去掉后缀 c

			//		LoadStringFile(szStringFile, false, bReplace, bWarning); //加载

			//	}while(FindNextFile(hFile, &xFindData));                      
			//	FindClose(hFile);
			//}
			// modify end
		}
		else
		{
			sprintf_s(szFile, sizeof(szFile) - 1, "%s\\*%s", pszPath, String_Ext);
			WIN32_FIND_DATA xFindData;         
			HANDLE hFile = FindFirstFile(szFile, &xFindData);   	
			if(hFile != INVALID_HANDLE_VALUE)
			{
				do
				{
					char szStringFile[_MAX_PATH + 1] = "";
					sprintf_s(szStringFile, sizeof(szStringFile) - 1, "%s\\%s", pszPath, xFindData.cFileName);

					LoadStringFile(szStringFile, false, bReplace, bWarning); //加载

				}while(FindNextFile(hFile, &xFindData));                      
				FindClose(hFile);
			}
		}
	}

	return true;
}

//pszFile  = FileList索引文件路径  里面存放的都是相对于pszFile的文件路径
bool XmlString::LoadStringFileList(const char* pszFile, bool bClear /* = false*/, bool bReplace /* = false*/, bool bWarning /* = true*/)
{
	if(pszFile == NULL || *pszFile == 0) { return false; }

	if (bClear) { m_mapString.clear(); }

	///////////////////////////////////////////////////////////////得到目录名
	char szDir[_MAX_DIR] = "";
	char szDrive[_MAX_DRIVE] = "";	
	_tsplitpath(pszFile, szDrive, szDir, NULL, NULL);
	std::string strPath = szDrive;
	strPath += szDir;
	///////////////////////////////////////////////////////////////

	ifstream infile;
	infile.open(pszFile);
	if (!infile) { return false; }

	while (!infile.eof())
	{
		string strFile = "";
		getline(infile, strFile);
		if (strFile.empty()) { continue; }
		//格式化路径
		strFile.insert(strFile.begin(), strPath.begin(), strPath.end());

		if(!LoadStringFile(strFile.c_str(), false, bReplace, bWarning)) { return false; }
	}

	return true;
}

bool XmlString::LoadStringFile(const char* pszFile, bool bClear /* = true */, bool bReplace /* = false */, bool bWarning /* = true*/)
{
	if (pszFile == NULL || *pszFile == 0)
	{
		return false;
	}

	if (bClear)
	{
		m_mapString.clear();

		m_mapString.insert(make_pair(Empty_String_Id, Empty_String_Value));
	}

	MeXmlDocument xMeXmlDoc;
	if (!xMeXmlDoc.LoadFile(pszFile, 1))
	{	
		return false;
	}

	MeXmlElement* pRoot = xMeXmlDoc.FirstChildElement("Project");
	if (pRoot)
	{
		pRoot = pRoot->FirstChildElement("Strings");
	}
	else
	{
		pRoot = xMeXmlDoc.FirstChildElement("Strings");
	}
	if ( NULL == pRoot ) return false;

	MeXmlElement* pElement  = pRoot->FirstChildElement("String");
	while (pElement != NULL)
	{			
		int nId = -1;
		pElement->Attribute("Id", &nId);

		Common::_tstring strValue;
		strValue.fromUTF8(pElement->Attribute("Value"));

		if(bReplace)
		{
			//判断相同ID情况
			mapiter iter = m_mapString.find(nId);
			if (iter != m_mapString.end())
			{
				(*iter).second = strValue;
	
				if(bWarning)
				{
					char szDebug[101] = "";
					sprintf_s(szDebug, sizeof(szDebug) - 1, "警告:字串ID【%d】相同!", nId);
					OutputDebugString(szDebug);
				}
			}
			else
				m_mapString.insert(make_pair(nId, strValue));
		}
		else
		{
			m_mapString.insert(make_pair(nId, strValue));
		}

		pElement = pElement->NextSiblingElement();
	}

	return true;
}

bool XmlString::SaveStringFile(const char* pszFile, std::vector<int> &vecStringId /* = vector<int> */ , bool bSaveEmpty /* = true*/)
{
	if (pszFile == NULL || *pszFile == 0)
	{
		return false;
	}

	MeXmlDocument xMeXmlDoc;
	xMeXmlDoc.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));


	MeXmlElement* pRoot = xMeXmlDoc.InsertEndChild(("Project"));

	pRoot->SetAttribute("Name", "X-Game");
	pRoot->SetAttribute("Version", ""/*ApplicationConfig::Instance().GetFullVersion()*/);
	MeXmlElement* pStrings = pRoot->InsertEndChild(("Strings"));
	if(pStrings == NULL) return false;

	mapiter iter = m_mapString.begin();
	mapiter end = m_mapString.end();

    std::multimap<int, string> mapString;
	if (!vecStringId.empty())  //保存指定的ID
	{		
		mapString.empty();
		
		std::vector<int>::iterator viter = vecStringId.begin();
		std::vector<int>::iterator vend = vecStringId.end();

		for ( ; viter != vend; ++viter)
		{
			if ((*viter) != Empty_String_Id)
			{
				mapString.insert(make_pair(*viter, GetString(*viter)));
			}			
		}
		
		iter = mapString.begin();
		end = mapString.end();
	}

	for (; iter != end; ++iter)
	{
		if (!bSaveEmpty && (*iter).second.empty())
		{
			continue; //设置不保存空ID
		}

		MeXmlElement* pElement = pStrings->InsertEndChild(("String"));

		pElement->SetAttribute("Id", (*iter).first);

		Common::_tstring strValue = (*iter).second;		
		pElement->SetAttribute("Value", strValue.toUTF8().c_str());
	}

	return xMeXmlDoc.SaveFile(pszFile);
}


const char* XmlString::GetString(const int nId)
{
	std::multimap<int, std::string>::size_type nSize = m_mapString.count(nId);
	if(nSize == 0)
	    return Empty_String_Value;

	if(nSize == 1)
	{
		mapiter iter = m_mapString.find(nId);

		if (iter != m_mapString.end())
		{
			return (*iter).second.c_str();
		}
	}
	else if(nSize > 1)
	{
		int nCount = rand()%nSize;
		std::multimap<int, std::string>::const_iterator it = m_mapString.lower_bound(nId);
		std::advance(it,nCount);
		return (*it).second.c_str();
	}

#ifdef _CLIENT_
	//char temp[129];
	//sprintf_s(temp,sizeof( temp ) - 1,"XmlString%d获取失败！",nId);
	//LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, temp);
#endif

	return Empty_String_Value;
}

//返回索引
int XmlString::GetId(std::string strName)
{
	mapiter iter = m_mapString.begin();
	mapiter end = m_mapString.end();
	for (int i = 0 ; iter != end; ++i, ++iter)
	{
		if ((*iter).second == strName)
		{
			return i;
		}
	}

	return Empty_String_Id;
}

int XmlString::AddString(std::string strName)
{	
	int nId = Empty_String_Id;

    std::multimap<int, string>::reverse_iterator riter = m_mapString.rbegin();

	if(riter != m_mapString.rend())
	{
		nId = (*riter).first;
	}

	m_mapString.insert(make_pair(++nId, strName));

	return nId;
}

int XmlString::AddString(int nId, std::string strName, bool Replace /* = false */)
{
	if (nId == -1 || nId == Empty_String_Id)
	{
		return AddString(strName);
	}
	
	int nInsertId = -1;
	if(Replace)
	{
		mapiter iter = m_mapString.find(nId);
		if ( iter != m_mapString.end())  //相同的
		{
			(*iter).second = strName;
			nInsertId = (*iter).first;
			return nInsertId;
		}
	}

	m_mapString.insert(make_pair(nId, strName));
	nInsertId = nId;
	
	return nInsertId;
}

bool XmlString::DeleteString(const int nId)
{
//	bool bDelete = false;
// 	mapiter iter = m_mapString.find(nId);
// 
// 	if (iter != m_mapString.end())
// 	{
// 		(*iter).second.clear();
// 		bDelete = true;
// 	}

	return m_mapString.erase(nId) > 0;
	
//	return bDelete;
}

const char* XmlString::GetStringWithAccountIDAndName( int nIndex )
{
    strWithNameFormat_= "%d\t[%s]\t";
    strWithNameFormat_ += GetString( nIndex );
    return strWithNameFormat_.c_str();
}

const char* XmlString::GetStringWithAccountID( int nIndex )
{
    strWithNameFormat_= "%d\t";
    strWithNameFormat_ += GetString( nIndex );
    return strWithNameFormat_.c_str();
}

const char* XmlString::GetStringWithName( int nIndex )
{
    strWithNameFormat_= "[%s]\t";
    strWithNameFormat_ += GetString( nIndex );
    return strWithNameFormat_.c_str();
}

bool XmlString::SaveBinFile( const char* pszFileName )
{
    FILE* fp = fopen( pszFileName, "wb" );
    if( !fp )
        return FALSE;   

    int nCount = m_mapString.size();
    fwrite( &nCount, sizeof( int ), 1, fp );
    /*for( std::string::size_type i = 0 ; i < m_mapString.size(); ++ i )
    {
        int nStringCount = m_mapString[i].size() + 1;
        fwrite( &nStringCount, sizeof( int ), 1, fp );
        fwrite( m_mapString[i].c_str(), nStringCount, 1, fp );
    }	

    if( fp )
        fclose( fp );
		*/
    return TRUE;
}

bool XmlString::LoadBinFile( const char* pszFileName )
{
    FILE* fp = fopen( pszFileName, "rb" );
    if( !fp )
        return FALSE;    
    int nCount = 0;
    fread( &nCount, sizeof( int ), 1, fp );
    int nStringCount = 0;
    char szTemp[256];
    for( int i = 0 ; i < nCount ; ++ i )
    {
        fread( &nStringCount, sizeof( int ), 1, fp );
        fread( &szTemp, nStringCount, 1, fp );
        //m_mapString[i] = szTemp ;
		AddString(i,szTemp);
    }

    if( fp )
        fclose( fp );

    return TRUE;
}

char* XmlString::ParseAtString(const char * szText )
{
	static char szTemp[1024] = {0};
	char szNumber[24] = {0};
	char* pPos = strstr((char*)szText,"@");
	if (pPos)
	{
		int nBeginLength = pPos - szText;
		strncpy(szTemp,szText,nBeginLength);
		int numberPos = nBeginLength + 1;
		while ( (szText[ numberPos] >= '0') && (szText[ numberPos] <= '9'))
		{
			szNumber[numberPos - nBeginLength - 1] = szText[numberPos];
			++numberPos;
		}
		if (numberPos != nBeginLength + 1)
		{
			int stringId = atoi(szNumber);
			strcpy(&szTemp[nBeginLength],GetString(stringId));
			int nLenght = strlen(szTemp);
			strcpy(&szTemp[nLenght],&szText[ numberPos]);
			return szTemp;
		}
	}
	strcpy(szTemp,szText);
	return szTemp;
}

// 检查文件大小并读给定大小数据，若检查失败并bCloseFile为true，则关闭文件
static bool ReadAndCheckFileSize(FILE* fp, void* pData, int nReadSize, const DWORD dwTotalSize, DWORD& dwCurrentSize, bool bCloseFile)
{
	if( !fp || !pData )
	{
		if( fp && bCloseFile )
			fclose(fp);
		return false;
	}

	if( dwCurrentSize + nReadSize > dwTotalSize )
	{
		if( fp && bCloseFile )
			fclose(fp);
		return false;
	}

	fread( pData, nReadSize, 1, fp );
	dwCurrentSize += nReadSize;
	return true;
}

bool XmlString::LoadBinStringFile( const char* pszFile, bool bClear /*= false*/, bool bReplace /*= false*/, bool bWarning /*= true*/, bool bInsertEmpty /*= true*/ )
{
	if (pszFile == NULL || *pszFile == 0)
	{
		return false;
	}

	if (bClear)
	{
		m_mapString.clear();
		if( bInsertEmpty )
			m_mapString.insert(make_pair(Empty_String_Id, Empty_String_Value));
	}


	FILE* fp = fopen( pszFile, "rb" );
	if( !fp )
		return false;  

	fseek(fp,0,SEEK_END);
	DWORD dwFileSize = ftell(fp);
	rewind(fp);
	DWORD dwSizeCount = 0;

	// 检查数据标识和版本号
	int nIdLength = 0;
	if( !ReadAndCheckFileSize( fp, &nIdLength, sizeof(int), dwFileSize, dwSizeCount, true ) )
		return false;
	if( nIdLength <= 0 )
		return false;

	char szIdentifier[256] = {0};
	if( !ReadAndCheckFileSize( fp, szIdentifier, nIdLength, dwFileSize, dwSizeCount, true ) )
		return false;
	if( 0 != strcmp(szIdentifier, STRING_DATA_ID) )
		return false;

	int nVersion = 0;
	if( !ReadAndCheckFileSize( fp, &nVersion, sizeof(int), dwFileSize, dwSizeCount, true ) )
		return false;
	if( nVersion < STRING_DATA_BASE_VERSION )
		return false;


	int nCount = 0;
	if( !ReadAndCheckFileSize( fp, &nCount, sizeof( int ), dwFileSize, dwSizeCount, true ) )
		return false;
	int nStringCount = 0;
	int nId = 0;
	char szTemp[1024] = {0};
	char szDebug[256] = {0};
	std::string strValue = "";
	for( int i = 0 ; i < nCount ; ++ i )
	{
		if( !ReadAndCheckFileSize( fp, &nId, sizeof( int ), dwFileSize, dwSizeCount, true ) )
			return false;
		if( !ReadAndCheckFileSize( fp, &nStringCount, sizeof( int ), dwFileSize, dwSizeCount, true ) )
			return false;
		if( nStringCount > 1024 )
		{
			if(bWarning)
			{
				sprintf_s(szDebug, sizeof(szDebug) - 1, "【警告】:字串ID:%d 超1024字节!\n", nId);
				OutputDebugString(szDebug);
			}
			char *szTempBig = new char[nStringCount];
			if( szTempBig )
			{
				memset(szTempBig, 0, sizeof(szTempBig));
				if( !ReadAndCheckFileSize( fp, &szTempBig, nStringCount, dwFileSize, dwSizeCount, true ) )
					return false;
				strValue = szTempBig;
				delete[] szTempBig;
			}
			else
			{
				// 没内存
				if(bWarning)
				{
					sprintf_s(szDebug, sizeof(szDebug) - 1, "【警告】:加载字串表%s ID:%d 内存不够\n", pszFile, nId);
					OutputDebugString(szDebug);
				}
				return false;
			}
		}
		else
		{
			memset(szTemp, 0, sizeof(szTemp));
			if( !ReadAndCheckFileSize( fp, &szTemp, nStringCount, dwFileSize, dwSizeCount, true ) )
				return false;
			strValue = szTemp;
		}

		if(bReplace)
		{
			mapiter iter = m_mapString.find(nId);
			if (iter != m_mapString.end())
			{				
				(*iter).second = strValue;
					
				if(bWarning)
				{
					sprintf_s(szDebug, sizeof(szDebug) - 1, "【警告】:字串ID:%d 相同!\n", nId);
					OutputDebugString(szDebug);
				}
			}
			else
			   m_mapString.insert(make_pair(nId, strValue));
		}
		else
		{
			m_mapString.insert(make_pair(nId, strValue));
		}
	}

	if( fp )
		fclose( fp );
	return true;
}

bool XmlString::SaveBinStringFile( const char* pszFile )
{
	if (pszFile == NULL || *pszFile == 0)
	{
		return false;
	}

	FILE* fp = fopen( pszFile, "wb" );
	if( !fp )
		return false;   

	// 写数据标示和版本号
	char szIdentifier[256] = {0};
	sprintf_s(szIdentifier, sizeof(szIdentifier)-1, "%s", STRING_DATA_ID);
	int nIdLength = strlen(szIdentifier);
	fwrite( &nIdLength, sizeof(int), 1, fp );
	fwrite( szIdentifier, nIdLength, 1, fp );
	int nVersion = STRING_DATA_VERSION;
	fwrite( &nVersion, sizeof(int), 1, fp );

	int nCount = m_mapString.size();
	mapiter iter = m_mapString.begin();
	if( iter->first == -1 )	// 去掉key为-1的项
	{
		++iter;
		--nCount;
	}
	fwrite( &nCount, sizeof( int ), 1, fp );
	for( ; iter != m_mapString.end(); ++iter )
	{
		// string id
		fwrite( &iter->first, sizeof( int ), 1, fp );

		// string长度
		int nStringCount = iter->second.size() + 1;
		fwrite( &nStringCount, sizeof( int ), 1, fp );

		// string内容
		fwrite( iter->second.c_str(), nStringCount, 1, fp );
	}	

	if( fp )
		fclose( fp );
	return true;
}