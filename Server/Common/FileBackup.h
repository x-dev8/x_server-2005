/*++

Copyright (c) 2006

Module Name:
FileBackup.h

Abstract:

�ṩһ���ô����ļ��������ݵ�ģ��
ͨ��һ��Ψһ������ID�����ڴ����нϿ��ٵĴ洢����ȡ��ɾ����Ӧ������
FileBackup��������֤ID��Ψһ�ԣ���Ҫʹ�������б�֤

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
    //��ʼ��
    bool Init(std::string strDataFile, std::string strIndexFile, bool bCreateFile = false);

    //�����д
    bool LoadData(int nIndex, T& data);
    bool LoadData(std::map<unsigned int, T>& mapData);
    bool SaveData(int nIndex, const T& data);
    bool DelData(int nIndex);

private:
    std::map<unsigned int, unsigned int> m_mapDataPosIndex; // ƫ��������
    std::list<unsigned int> m_listFreePos;
    std::size_t m_sFileEndPos;

    std::string m_strDataFile; // �����ļ��ļ���
    std::string m_strIndexFile; // �����ļ��ļ���
};

template<class T> bool CFileBackup<T>::Init(std::string strDataFile, std::string strIndexFile, bool bCreateFile)
{
    if (strDataFile == "" || strIndexFile == "")
    {
        return false;
    }

    m_strDataFile = strDataFile;
    m_strIndexFile = strIndexFile;

    //���ļ�
    std::ifstream ifData(m_strDataFile.c_str(), std::ios::in | std::ios::binary | std::ios::out);
    std::ifstream ifIndex(m_strIndexFile.c_str(), std::ios::in | std::ios::binary | std::ios::out);

    //����ļ�������
    if(!ifData.is_open() || !ifIndex.is_open())
    {
        //�Ƿ񴴽��ļ�
        if(bCreateFile)
        {
            //�������ʧ���򷵻�ʧ��
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

    //��ȡ�ļ�����
    ifIndex.seekg(0, std::ios::end);
    std::size_t filesize = ifIndex.tellg();
    char* pData = new char[filesize];

    ifIndex.seekg(0, std::ios.beg);
    ifIndex.read(pData, static_cast<std::streamsize>(filesize));

    ifData.close();
    ifIndex.close();

    //����ļ����ݴ�С��洢��Ԫ��С*��Ԫ�� ���������ʾ�ļ������ѱ���
    if (filesize%(sizeof(unsigned int)) != 0)
    {
        return false;
    }
    //��ȡ��ǰ�ļ��п�д��λ��
    m_sFileEndPos = filesize;

    //������IDX�ļ��е�ֵ���ζ���map
    for (unsigned int i=0; i<filesize; i+=(sizeof(unsigned int)))
    {
        int nID = *((unsigned int*)&pData[i]);
        if (nID != 0)
        {
            m_mapDataPosIndex.insert(std::pair<unsigned int, unsigned int>(nID, i));
        }
        else
        {
            //��nIDΪ0��λ�����������λ���б���
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

    //���ļ����ж�ȡ��������
    std::ifstream fData(m_strDataFile.c_str(), std::ios::in | std::ios::out | std::ios::binary);

    if (!fData.is_open())
    {
        return false;
    }

    //����ƫ��λ��;
    unsigned int nDataPos = (itr->second/(sizeof(unsigned int)))*sizeof(T);
    
    //�������ļ��еĸ������Զ���itemattrib
    fData.seekg(nDataPos, std::ios::beg);
    fData.read((char*)&data, sizeof(T));
    fData.close();

    return true;   
}

template<class T> bool CFileBackup<T>::LoadData(std::map<unsigned int, T>& mapData)
{
    //���ļ�
    std::ifstream ifData(m_strDataFile.c_str(), std::ios::in | std::ios::binary | std::ios::out);
    std::ifstream ifIndex(m_strIndexFile.c_str(), std::ios::in | std::ios::binary | std::ios::out);

    //����ļ�������
    if(!ifData.is_open() || !ifIndex.is_open())
    {
        return false;    
    }

    //��ȡ�ļ�����
    ifIndex.seekg(0, std::ios::end);
    std::size_t filesize = ifIndex.tellg();
    char* pData = new char[filesize];

    ifIndex.seekg(0, std::ios.beg);
    ifIndex.read(pData, static_cast<std::streamsize>(filesize));

    //������IDX�ļ��е�ֵ���ζ���map
    T data;
    unsigned int nDataPos = 0;
    for (unsigned int i=0; i<filesize; i+=(sizeof(unsigned int)))
    {
        int nID = *((unsigned int*)&pData[i]);
        if (nID != 0)
        {
            //����ƫ��λ��;
            unsigned int nDataPos = (i/sizeof(unsigned int))*sizeof(T);

            //�������ļ��еĸ������Զ���itemattrib
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

    //nIndex���Ѿ�����������ݱ�ţ�����ԭ������
    if (itr != m_mapDataPosIndex.end())
    {
        nfilepos = itr->second;
        nDataPos = (nfilepos/(sizeof(unsigned int)))*sizeof(T);

        fData.seekp(nDataPos, std::ios::beg);
        fData.write((const char*)&data, sizeof(T));
    }
    //nIndex��δ����������ļ��в���������
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