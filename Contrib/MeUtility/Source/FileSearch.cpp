#include "FileSearch.h"

using Common::_tstring;

namespace FileIO
{
    CFileSearch::CFileSearch()
    {
    }

    CFileSearch::~CFileSearch()
    {
    }

    size_t CFileSearch::Find(_tstring strPath, _tstring strFileExtName, bool bSearchChildFolder)
    {
        m_file.clear();
        m_folder.clear();

        _tstring path = strPath;

        //如果路径最后面没有跟上"\\"则加上
        if (path.size() > 0 && c_pathSeparator != path[path.size() - 1])
        {
            path.append(s_pathSeparator);
        }

        //m_folder.push_back(path);
        _tstring fext = strFileExtName;
        if (0 == fext.compare(_T("*")) || 0 == fext.compare(_T("*.*")))
        {
            fext = _T("");
        }
        ////string file = fext;
        _tstring file = _T("*");
        _tstring s = path + file;

        WIN32_FIND_DATA fileinfo = {0};
        HANDLE handle = FindFirstFile(s.c_str(), &fileinfo);

        if (NULL != handle && INVALID_HANDLE_VALUE != handle)
        {

            do {

                if (_T('.') != fileinfo.cFileName[0])	//--skip./..
                    if ((FILE_ATTRIBUTE_DIRECTORY & fileinfo.dwFileAttributes)
                        == FILE_ATTRIBUTE_DIRECTORY)	//--目录
                    {
                        m_folder.push_back( path + fileinfo.cFileName + s_pathSeparator );

                        //搜索子目录
                        if (bSearchChildFolder)
                        {
                            CFileSearch search;
                            search.Find(path + fileinfo.cFileName, fext, bSearchChildFolder);

                            //添加目录
                            FileList o_dir = search.GetFolder();
                            for (FileList::iterator it_dir = o_dir.begin();
                                o_dir.end() != it_dir;
                                it_dir ++)
                            {
                                m_folder.push_back(*it_dir);
                            }

                            //添加文件
                            FileList o_file = search.GetFile();
                            for (FileList::iterator it_file = o_file.begin();
                                o_file.end() != it_file;
                                it_file ++)
                            {
                                m_file.push_back(*it_file);
                            }
                        }
                    }
                    else
                    {
                        if ((0 == fext.size() || Match(fext, fileinfo.cFileName)))
                        {
                            m_file.push_back(path + fileinfo.cFileName);
                        }
                    }

            } while (FindNextFile(handle, &fileinfo));

            FindClose(handle);
        }

        return m_file.size() + m_folder.size();
    }


    bool CFileSearch::Match(_tstring strFileExtName, _tstring strFileName)
    {
        _tstring fext = Uppercase(strFileExtName);
        _tstring file = Uppercase(strFileName);

        size_t pos = file.find_last_of(_T('.'));
        if (_tstring::npos != pos)
        {
            file = file.substr(pos);
        }

        return (_tstring::npos != fext.find(file));
    }

    _tstring CFileSearch::Uppercase(_tstring str)
    {
        const TCHAR aazz = _T('z') - _T('Z');
        _tstring rs;
        for (_tstring::iterator it = str.begin(); str.end() != it; it++)
        {
            if (_T('a') <= *it && *it <= _T('z'))
            {
                rs.append(1, *it - aazz);
            }
            else 
            {
                rs.append(1, *it);
            }
        }
        return rs;
    }

};
