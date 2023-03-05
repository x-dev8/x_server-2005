#pragma once

#include <vector>
#include <string>
#include <map>
using std::vector;
using std::string;
using std::map;
/*

   ���๦���ǽ��ļ��еĿռ�ṹ��Ϣ����xml�ĵ�,���ĵ���ΪidΪ1���ļ�д��������Դ�ڣ����ļ����������ļ�д��������Դ��
   ͬʱ����Ҫд��ʱ���Ƚ�1���ļ�д������ȡ�����ļ�ID��Ϣ������ID�ļ�д����



   ���
1��������ļ��У�����xml�ṹ��Ϣ
2��ѹ��
3��д��
   ���



    ע�⴫���·��

*/

class FolderFileList
{
public:
	FolderFileList(void);
	~FolderFileList(void);

	struct fileinfo
	{
		string name;
		CString md5;
		int ID;
	};
public:
	/*
      PackPathΪ�����·��C:\PublishPack\PublishPack\tinyxml\src��Ҫ������ļ�����src��
	  AppNameΪҪ������ĳ������·��C:\\PublishPack\\Debug\\1.exe����֧�ֶ�������д��
	*/
	 bool PackIn(CString PackPath,CString AppName); 
	/*
	nameΪ�����·��C:\123\21321����C:\123\21321��ֻҪ��ʽ��ȷ���Ὣ�����ڵ��ļ���д����Ŀ¼
   .�˺�����������Դ����ִ��
	*/
	bool PackOut(char * name);
private:
	//�����ļ��У����ļ�д�������Դ���֣���Դid���ļ�md5������ļ�·����Ϣ����FileList1������ļ���·������FileList
	bool EnumFolder(char *  lpPath,char * path,CString AppName); 
	bool savedirxml();
	typedef vector<string> FileList;      //���ص��ļ���Ŀ¼�б�
    typedef vector<fileinfo*> FileList1;      //���ص��ļ���Ŀ¼�б�
	FileList1 m_file;      //�ļ��б�
	FileList m_folder;    //Ŀ¼�б�

	int iFileID;
	
	string strXMLDoc;	
};
