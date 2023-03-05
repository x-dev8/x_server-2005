/********************************************************************
	Filename: 	FindFile.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#pragma once

#include "MeRTLibs.h"

using namespace std;

class CFindFile
{
public:
	CFindFile(void);
	virtual ~CFindFile(void);
public:
	DWORD GetLength() const;
	string GetFileName() const;
	string GetFilePath() const;
	string GetFileTitleName() const;
	string GetFileURL() const;
	string GetRoot() const;
	//
	//virtual BOOL GetLastWriteTime(FILETIME* pTimeStamp) const;
	//virtual BOOL GetLastAccessTime(FILETIME* pTimeStamp) const;
	//virtual BOOL GetCreationTime(FILETIME* pTimeStamp) const;
	//virtual BOOL GetLastWriteTime(CTime& refTime) const;
	//virtual BOOL GetLastAccessTime(CTime& refTime) const;
	//virtual BOOL GetCreationTime(CTime& refTime) const;

	BOOL MatchesMask(DWORD dwMask) const;

	BOOL IsDots() const;
	// these aren't virtual because they all use MatchesMask(), which is
	//BOOL IsReadOnly() const;
	BOOL IsDirectory() const;
	//BOOL IsCompressed() const;
	//BOOL IsSystem() const;
	//BOOL IsHidden() const;
	//BOOL IsTemporary() const;
	//BOOL IsNormal() const;
	//BOOL IsArchived() const;
protected:
	void CloseContext();
	// Implementation
protected:
	void*	m_pFoundInfo;
	void*	m_pNextInfo;
	HANDLE	m_hContext;
	char	m_strRoot[MAX_PATH];
	TCHAR	m_chDirSeparator;     // not '\\' for Internet classes
	
public:
	void		Close();
	BOOL FindFile(LPCSTR pstrName = NULL, DWORD dwUnused = 0);
	BOOL FindNextFile();
};














