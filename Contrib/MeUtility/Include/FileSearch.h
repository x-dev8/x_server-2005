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
	
	//--�ļ�����
	class CFileSearch
	{
	public:
		typedef vector<_tstring> FileList;      //���ص��ļ���Ŀ¼�б�
    
    public:
        CFileSearch();
        virtual ~CFileSearch();

        FileList& GetFolder() {return m_folder;}
        FileList& GetFile() {return m_file;}
        size_t Find(_tstring strPath, _tstring strFileExtName = _T(""), bool bSearchChildFolder = false); //�����ļ�����������ƥ����ļ����ļ���

    private:
        CFileSearch(const CFileSearch&);
        CFileSearch& operator = (const CFileSearch&);

        bool Match(_tstring strFileExtName, _tstring strFileName);
        _tstring Uppercase(_tstring str);

    private:
        FileList m_file;      //�ļ��б�
        FileList m_folder;    //Ŀ¼�б�
	};
};

#endif	// __UTILITY_FILESEARCH_H__
