/*++

Copyright (c) 2006

Module Name:
FileBackup.h

Abstract:

提供一个用磁盘文件备份数据的模板
通过一个唯一的数据ID可以在磁盘中较快速的存储，读取，删除相应的数据
FileBackup本身并不保证ID的唯一性，需要使用者自行保证

Author:
skinny 2005-10-25

Revision History:

--*/
#pragma once
#include <string>
#include <map>
#include <list>
#include <fstream>

template<class T> class CFileBackup
{
public:
    CFileBackup() : m_sFileEndPos(0), m_strDataFile(""), m_strIndexFile("") 
    {
        m_mapDataPosIndex.clear();
        m_listFreePos.clear();
    }
    ~CFileBackup(void)
    {
        m_mapDataPosIndex.clear();
        m_listFreePos.clear();
    }

public:
    //初始化
    bool Init(std::string strDataFile, std::string strIndexFile, bool bCreateFile = false);

    //随机读写
    bool LoadData(int nIndex, T& data);
    bool LoadData(std::map<unsigned int, T>& mapData);
    bool SaveData(int nIndex, const T& data);
    bool DelData(int nIndex);

private:
    std::map<unsigned int, unsigned int> m_mapDataPosIndex; // 偏移量索引
    std::list<unsigned int> m_listFreePos;
    std::size_t m_sFileEndPos;

    std::string m_strDataFile; // 数据文件文件名
    std::string m_strIndexFile; // 索引文件文件名
};

template<class T> bool CFileBackup<T>::Init(std::string strDataFile, std::string strIndexFile, bool bCreateFile)
{
    if (strDataFile == "" || strIndexFile == "")
    {
        return false;
    }

    m_strDataFile = strDataFile;
    m_strIndexFile = strIndexFile;

    //打开文件
    std::ifstream ifData(m_strDataFile.c_str(), std::ios::in | std::ios::binary | std::ios::out);
    std::ifstream ifIndex(m_strIndexFile.c_str(), std::ios::in | std::ios::binary | std::ios::out);

    //如果文件不存在
    if(!ifData.is_open() || !ifIndex.is_open())
    {
        //是否创建文件
        if(bCreateFile)
        {
            //如果创建失败则返回失败
            std::ofstream ofIdx(m_strIndexFile.c_str(), std::ios::app);
            std::ofstream ofData(m_strDataFile.c_str(), std::ios::app);
            if (ofIdx.is_open() && ofData.is_open())
            {
                ofIdx.close();
                ofData.close();
                return true;
            }
            return false;
        }
        return false;    
    }

    //读取文件内容
    ifIndex.seekg(0, std::ios::end);
    std::size_t filesize = ifIndex.tellg();
    char* pData = new char[filesize];

    ifIndex.seekg(0, std::ios.beg);
    ifIndex.read(pData, static_cast<std::streamsize>(filesize));

    ifData.close();
    ifIndex.close();

    //如果文件内容大小与存储单元大小*单元数 不符，则表示文件可能已被损坏
    if (filesize%(sizeof(unsigned int)) != 0)
    {
        return false;
    }
    //获取当前文件中可写的位置
    m_sFileEndPos = filesize;

    //将索引IDX文件中的值依次读入map
    for (unsigned int i=0; i<filesize; i+=(sizeof(unsigned int)))
    {
        int nID = *((unsigned int*)&pData[i]);
        if (nID != 0)
        {
            m_mapDataPosIndex.insert(std::pair<unsigned int, unsigned int>(nID, i));
        }
        else
        {
            //将nID为0的位置添加至空闲位置列表当中
            m_listFreePos.push_back(i);
        }
    }
    return true;
}

template<class T> bool CFileBackup<T>::LoadData(int nIndex, T& data)
{
    std::map<unsigned int, unsigned int>::iterator itr = m_mapDataPosIndex.find(nIndex);
    if (itr == m_mapDataPosIndex.end())
    {
        return false;
    }

    //从文件当中读取附加属性
    std::ifstream fData(m_strDataFile.c_str(), std::ios::in | std::ios::out | std::ios::binary);

    if (!fData.is_open())
    {
        return false;
    }

    //计算偏移位置;
    unsigned int nDataPos = (itr->second/(sizeof(unsigned int)))*sizeof(T);
    
    //将数据文件中的附加属性读入itemattrib
    fData.seekg(nDataPos, std::ios::beg);
    fData.read((char*)&data, sizeof(T));
    fData.close();

    return true;   
}

template<class T> bool CFileBackup<T>::LoadData(std::map<unsigned int, T>& mapData)
{
    //打开文件
    std::ifstream ifData(m_strDataFile.c_str(), std::ios::in | std::ios::binary | std::ios::out);
    std::ifstream ifIndex(m_strIndexFile.c_str(), std::ios::in | std::ios::binary | std::ios::out);

    //如果文件不存在
    if(!ifData.is_open() || !ifIndex.is_open())
    {
        return false;    
    }

    //读取文件内容
    ifIndex.seekg(0, std::ios::end);
    std::size_t filesize = ifIndex.tellg();
    char* pData = new char[filesize];

    ifIndex.seekg(0, std::ios.beg);
    ifIndex.read(pData, static_cast<std::streamsize>(filesize));

    //将索引IDX文件中的值依次读入map
    T data;
    unsigned int nDataPos = 0;
    for (unsigned int i=0; i<filesize; i+=(sizeof(unsigned int)))
    {
        int nID = *((unsigned int*)&pData[i]);
        if (nID != 0)
        {
            //计算偏移位置;
            unsigned int nDataPos = (i/sizeof(unsigned int))*sizeof(T);

            //将数据文件中的附加属性读入itemattrib
            ifData.seekg(nDataPos, std::ios::beg);
            ifData.read((char*)&data, sizeof(T));

            mapData.insert(std::pair<unsigned int, T>(nID, data));
        }
    }

    ifIndex.close();
    ifData.close();
    return true;  
}

template<class T> bool CFileBackup<T>::SaveData(int nIndex, const T& data)
{
    std::ofstream fIdx(m_strIndexFile.c_str(), std::ios::in | std::ios::out | std::ios::binary);
    std::ofstream fData(m_strDataFile.c_str(), std::ios::in | std::ios::out | std::ios::binary);
    
    if (!fIdx.is_open() || !fData.is_open())
    {
        return false;
    }
    
    int nfilepos = 0;
    unsigned int nDataPos = 0;
    std::map<unsigned int, unsigned int>::iterator itr = m_mapDataPosIndex.find(nIndex);

    //nIndex是已经保存过的数据编号，覆盖原来数据
    if (itr != m_mapDataPosIndex.end())
    {
        nfilepos = itr->second;
        nDataPos = (nfilepos/(sizeof(unsigned int)))*sizeof(T);

        fData.seekp(nDataPos, std::ios::beg);
        fData.write((const char*)&data, sizeof(T));
    }
    //nIndex还未保存过，在文件中插入新数据
    else
    {
        if (m_listFreePos.size() != 0)
        {
            std::list<unsigned int>::iterator itr = m_listFreePos.begin();
            nfilepos = *itr;
            m_listFreePos.pop_front();
        }
        else
        {
            nfilepos = static_cast<unsigned int>(m_sFileEndPos);
            m_sFileEndPos += sizeof(unsigned int);
        }

        fIdx.seekp(nfilepos, std::ios::beg);
        fIdx.write((const char*)&nIndex, sizeof(int));

        nDataPos = (nfilepos/sizeof(unsigned int))*sizeof(T);
        fData.seekp(nDataPos, std::ios::beg);
        fData.write((const char*)&data, sizeof(T));

        m_mapDataPosIndex.insert(std::pair<int, int>(nIndex, nfilepos));
    }

    fIdx.close();
    fData.close();
    return true;
}

template<class T> bool CFileBackup<T>::DelData(int nIndex)
{
    std::map<unsigned int, unsigned int>::iterator itr = m_mapDataPosIndex.find(nIndex);
    if (itr == m_mapDataPosIndex.end())
    {
        return false;
    }
    
    std::ofstream fIdx(m_strIndexFile.c_str(), std::ios::in | std::ios::out | std::ios::binary);
    if(!fIdx.is_open())
    {
        return false;
    }

    int nID = 0;
    fIdx.seekp(itr->second, std::ios::beg);
    fIdx.write((const char*)&nID, sizeof(nID));
    fIdx.close();

    m_listFreePos.push_back(itr->second);
    m_mapDataPosIndex.erase(nIndex);
    return true;
}