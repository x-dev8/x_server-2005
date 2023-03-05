/********************************************************************
	created:	2008/05/05
	created:	5:5:2008   13:21
	filename: 	e:\TJ\Me3d\Md5Manager.h
	file path:	e:\TJ\Me3d
	file base:	Md5Manager
	file ext:	h
	author:		huwen
	
	purpose:	
*********************************************************************/

#pragma once
#include <hash_map>
#include <string>
#include <windows.h>

//#define USE_MD5_VALIDATE

/** MD5管理器。
*/
class Md5Manager
{
#if USE_MD5_VALIDATE
    typedef stdext::hash_map< std::string, std::string > MD5Map;
#else
    typedef stdext::hash_map< std::string, long > MD5Map;
#endif

public:
    ~Md5Manager(void);

    static Md5Manager& Instance();

    /** 初始化MD5资源。
    */
    void Initialize( const std::string& md5Config );

    /** 验证filename文件MD5是否正确。
	*/
    bool ValidateMD5( const std::string& filename );

    /** 激活MD5验证功能。
    */
    void EnableMD5Validate( bool bEnabled );

	void SetMD5CheckRetMap(bool bRet);
	bool GetMD5CheckRetMap(){return true;/*m_bIsCheckRightMap*/;}

	void SetMD5CheckRetCScene(bool bRet);
	bool GetMD5CheckRetCScene(){return true/*m_bIsCheckRightCScene*/;}

	void SetMD5CheckRetTerrain(bool bRet);
	bool GetMD5CheckRetTerrain(){return true/*m_bIsCheckRightTerrain*/;}

	bool IsMD5Validate(){return _bEnabled;}

    const std::string& getErrorFilename() const { return _errorFilename; }

private:
    Md5Manager(void);

    MD5Map  _md5Map;
    bool    _bEnabled;
	bool    m_bIsCheckRightMap;
	bool    m_bIsCheckRightCScene;
	bool    m_bIsCheckRightTerrain;
    std::string _errorFilename;

};
