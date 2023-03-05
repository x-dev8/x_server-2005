#pragma once

#include <vector>
#include <string>
#include <map>
using std::vector;
using std::string;
using std::map;
/*

   此类功能是将文件夹的空间结构信息生成xml文档,此文档作为id为1号文件写进程序资源节，将文件夹内所有文件写进程序资源节
   同时在需要写出时，先将1号文件写出，读取其中文件ID信息，将此ID文件写出。



   打包
1。将打包文件夹，生成xml结构信息
2。压缩
3。写入
   解包



    注意传入的路径

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
      PackPath为打包的路径C:\PublishPack\PublishPack\tinyxml\src，要打包的文件都在src内
	  AppName为要打包进的程序绝对路径C:\\PublishPack\\Debug\\1.exe，不支持对自身进行打包
	*/
	 bool PackIn(CString PackPath,CString AppName); 
	/*
	name为解包的路径C:\123\21321或者C:\123\21321，只要格式正确，会将包所在的文件夹写进此目录
   .此函数由所在资源程序执行
	*/
	bool PackOut(char * name);
private:
	//遍历文件夹，将文件写入程序资源部分，资源id，文件md5，相对文件路径信息放入FileList1，相对文件夹路径放入FileList
	bool EnumFolder(char *  lpPath,char * path,CString AppName); 
	bool savedirxml();
	typedef vector<string> FileList;      //返回的文件或目录列表
    typedef vector<fileinfo*> FileList1;      //返回的文件或目录列表
	FileList1 m_file;      //文件列表
	FileList m_folder;    //目录列表

	int iFileID;
	
	string strXMLDoc;	
};
