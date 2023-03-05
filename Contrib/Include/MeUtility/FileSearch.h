/********************************************************************
    Filename:     FileSearch.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef	__UTILITY_FILESEARCH_H__
#define __UTILITY_FILESEARCH_H__

#pragma once

#include "MeRTLibs.h"
#include "tstring.h"

using Common::_tstring;

namespace FileIO
{
	const TCHAR c_pathSeparator = _T('\\');
	const _tstring s_pathSeparator = _T("\\");
	
	//--文件搜索
	class CFileSearch
	{
	public:
		typedef vector<_tstring> FileList;      //返回的文件或目录列表
    
    public:
        CFileSearch();
        virtual ~CFileSearch();

        FileList& GetFolder() {return m_folder;}
        FileList& GetFile() {return m_file;}
        size_t Find(_tstring strPath, _tstring strFileExtName = _T(""), bool bSearchChildFolder = false); //查找文件，返回所有匹配的文件及文件夹

    private:
        CFileSearch(const CFileSearch&);
        CFileSearch& operator = (const CFileSearch&);

        bool Match(_tstring strFileExtName, _tstring strFileName);
        _tstring Uppercase(_tstring str);

    private:
        FileList m_file;      //文件列表
        FileList m_folder;    //目录列表
	};
};

#endif	// __UTILITY_FILESEARCH_H__
