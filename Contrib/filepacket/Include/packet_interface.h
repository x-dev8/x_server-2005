#ifndef _H_PACKET_INTERFACE_H_
#define _H_PACKET_INTERFACE_H_
#include <string>
struct fileinfo;
//class  TiXmlDocument;
class  MeXmlDocument;
class  packet;
struct f_Handle
{
	f_Handle()
	{
		t1=NULL;
		t2=NULL;
	}
	void * t1;
	//	fileinfo * t1;
	FILE * t2;
};

namespace packet_namespace
{
	///打一个资源包的文件
	packet*  getpacket(const char *name);
	//打一个资源包的文件
	bool	openpacket (const char *name);
	//通过文件名字获得到文件内容缓冲到缓冲区
	bool	readfiletobuf(const char *name, char *buf, size_t buflen);
	//暂没有实现
	char*	readfile (const char *name, size_t *buflen);
	//通过文件名得到一个文件节点信息
	fileinfo*  GetFileInfo(const char *name);
	//通过fileinfo一个文件节点信息获得到文件大小
	size_t	GetFileSize (struct fileinfo *info);
	//通过fileinfo一个文件节点信息获得到文件内容缓冲到缓冲区
	bool	readfiletobuf(fileinfo* pInfo,char *buf, size_t buflen);
	//释放所有包的节点信息
	void	release ();
    ///读xml中转
//	bool    LoadXML(TiXmlDocument& doc,const char * filename);
	
	bool    LoadXML(MeXmlDocument& doc,const char * filename);
	
	//读文件中转pData由内部new 外部使用完以后delete
	size_t   LoadFile(const char* filename,char*& pData,int nSize);
	//全存所有的资源包
	void    SavePacket();
	//试图重构。不过不一定重构成功
	void    AfreshAllPacket();
	//文件是否存在
	bool    IsOpen(const char* filename);
	//测试用的
	void    GetAllFileName();

	void    SetReadPacket(bool bRead);

 	extern  bool g_bReadPacket;

	extern std::string s_PacketRootPath;


	packet*  findpacket(const char *name);
	
	//仿fread
	int w_fread(void * buf,int len, int count,f_Handle *f);
	//仿fopen
	f_Handle* w_fopen(const char * name,char * type);
	//仿fclose
	void w_fclose(f_Handle * f);
	//仿fopen_s
	int w_fopen_s(f_Handle** f,const char * name,char * type);
	//仿fseek
	int w_fseek(f_Handle * _File, long _Offset, __in int _Origin);

	//仿getc
	int w_getc(f_Handle *f);

	int w_fgets(char * buf,int count,f_Handle *f);
	void w_rewind(f_Handle *f);

	int w_ftell(f_Handle *f);

}
#endif

