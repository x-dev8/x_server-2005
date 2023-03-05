#ifndef _H_DATA_FILE_H_
#define _H_DATA_FILE_H_
#include "string_hashmap.h"
#include <stdio.h>

//////////////////////////////////////////////////
//	包头附带识别信息，以及一个偏移（用来标记包中文件列表所处位置）
//	文件列表中为区域信息描述
//////////////////////////////////////////////////
enum filepacketsome
{
	epacket_space_type_unknow = 0,			//未知的类型
	epacket_space_type_no_file,				//无文件，比如被删除文件后，
	epacket_space_type_has_file,			//此区域有文件
	epacket_file_name_max_length = 256,		//文件名为128字节
	e_all_packet_file_num = 16000,			//所有文件数目
	

	enum_packet_type_not_release = 0,		//直到退出时才释放
	enum_packet_type_create_and_release = 1,//参与运行中释放申请

	enum_file_max_size = (1024*1024*1024*2)-1,	//文件最大4G

	max_nouse_area    =  20,
};
//包后缀
#define PACKET_TYPE 'FPMO'

static char  ENCRYPT_KEY='d'; 
#define ENCRYPT_PACKET_FILE(buf ,size) do\
{\
	for(int i=0;i <size;i++)\
	buf[i]^=ENCRYPT_KEY;\
	\
}while(0);
//文件区域信息
struct file_area
{
	long filetype;						//此文件类型
	char name[epacket_file_name_max_length];//文件名，带路径
	unsigned size;							//文件长度
	long offset;							//此区域在包中的位置
	long space;							//此区域大小，区域开始于 offset，结束于 offset + space
	file_area()
	{
		filetype = epacket_space_type_unknow;
		name[0] = 0;
		size = 0;
		offset = 0;
		space = 0;
	}

	//获取可用大小
	size_t GetCanUseSpace () { return space; }

	//重置，为加入到空闲区
	void ResetForAddEmpty ()
	{
		filetype = epacket_space_type_no_file;
		memset(name, 0, sizeof(name));
		size = 0;
	}
};
class packet;
//文件信息
struct fileinfo
{
	packet *pk;				//所在的包
	struct file_area area;	//所属的区域
	fileinfo()
	{
		pk = NULL;
		
	}
	

	char *GetFileName () { return area.name; }
};

struct file_h
{
	file_h()
	{
		f=NULL;
		poscur=0;
	}
	~file_h()
	{
		poscur=0;
		if(f)
		{
			delete f;
			f=NULL;
		}
	}
	fileinfo *f;
	int poscur;
	int seek(long _Offset, __in int _Origin)
	{
		switch( _Origin )
		{
		case SEEK_SET:
			poscur = _Offset;
			break;
		case SEEK_CUR:
			poscur += _Offset;
			break;
		case SEEK_END:
			poscur = f->area.size-_Offset;
			break;
		}
		if( poscur > f->area.size )
			return -1;

		return 0;
	}

	size_t read(void * buf,int buflen);

};


//文件头信息，描述文件类型，以及此已打包文件的文件列表所存储位置
struct file_header
{
	size_t type;							//记录此文件类型（后缀）
	size_t mag_type;						//记录此文件管理方式
	long offset;							//此包的文件列表存放的位置

	file_header() : type(PACKET_TYPE) {};
};
struct Thread_IO
{
	unsigned long   dwCurrentThreadID;
	FILE *m_fp;
	char  m_filename[epacket_file_name_max_length];
};
class packet;
class filemgr
{
public:
	typedef string_hash<fileinfo*> FileCenter;
	typedef std::list<packet*>     CListPacket;
	typedef std::vector<Thread_IO>   CThreadIO;
	filemgr();
	~filemgr();
	void Destroy ();

	void      AddPacket(packet* p);

	void      SavePacket();

	void      AfreshAllPacket();

	packet*   FindPacket(const char *name);
	//查找文件
	fileinfo *FindFile (const char *name,bool b=false);

	//增加一个文件(加入到哈希中)
	bool AddFile (packet *pk, fileinfo *info);

	//移除一个文件(从哈希中)
	bool RemoveFile (const char *name);

	void WriteFileToLog(const char* name);

	static filemgr &Instance ()
	{
		static filemgr gm;
		return gm;
	}
	Thread_IO*  GetDataForThreadID(unsigned long  threadid,const char* pFileName);
	void        AddThradIO(Thread_IO& thData);
private:
	FileCenter    m_filetable;
	CListPacket   m_setPacket;
	CThreadIO     m_setThreadIO;
};
//包
class packet
{
public:
	typedef string_hash<fileinfo*> AreaHash;
private:
	FILE *m_fp;								//文件指针
	file_header m_headerinfo;				//包头信息
	std::string m_packetname;				//此包文件名
	AreaHash m_areas;						//所有的含有文件的区域(同时加入到全局性的哈希索引中)
	std::list<fileinfo*> m_empty_areas;		//所有的无文件的区域。

	//重构包相关的比较值
	size_t m_filesizetotal;					//此包中有效文件的大小
	size_t m_emptysizetotal;				//此包中空闲空间的大小
private:
	////////////////////////////////////////////////////
	//增加一个含有文件的区域
	bool AddHasFileArea (fileinfo *area);

	//移除一个含有文件的区域
	fileinfo *RemoveHasFileArea (const char *name);

	//通过文件名获取含有文件的区域
	fileinfo *FindHasFileArea (const char *name);


	////////////////////////////////////////////////////
	//根据所需的大小，获取可用的区域
	fileinfo *GetCanUseArea (size_t needsize);

	//增加一个可用的区域
	bool AddCanUseArea (fileinfo *info);

	//查找此区域是否已经在可用的区域中
	bool FindCanUseArea (fileinfo *info);

	//写包头
	bool WriteHeader ();

	//读包头
	bool ReadHeader ();
public:
	packet();
	~packet();
	
	//获取当前包名字
	const char *GetPakcetName () { return m_packetname.c_str(); }
	////////////////////////////////////////////////////

	string_hash<fileinfo*> & GetPacketFileList(){ return m_areas;}
	//关闭包
	void Close ();
    
	//打开指定的包。
	bool OpenPakcet (const char *packetname);

	//创建指定的包
	bool CreatePacket (short type, const char *packetname);
private:
	//载入此包的文件列表，若数据错误则返回false
	bool LoadFileList ();
public:
	//写入文件列表到指定的包中
	void SaveFileList ();

	//重新组合必须先保证已完全保存
	void AfreshPacket();

	////////////////////////////////////////////////////

	//读指定的文件到指定的缓冲中
	bool ReadFileToBuf (fileinfo *info, char *buf, size_t buflen);

	//读指定的文件读指定文件偏移大小
    size_t ReadFileToBuf (fileinfo *info, char *buf, size_t buflen,size_t nStart,size_t nSize);
    
	////////////////////////////////////////////////////
	//增加一个文件到包中
	fileinfo *AddFile (const char *path,const char* pDstPath = NULL);

	//更新指定的文件
	fileinfo *UpdateFile (const char *path,const char* pDstPath = NULL);

	//通另一个包来文件信息增加

	fileinfo* AddFile(fileinfo* pfileinfo,char* pSrcData,size_t nSize);

	//删除指定的文件
	bool DelFile (const char *path);

	//将包数据分别成各子文件
	void CreateSubFile(const char* strDir);

	//将文件布局信息输入文件中
	void FileInfoSaveToFile(const char* strDir);

	//闲空分布
	void CreateNoUserInfo(fileinfo* pFatherInfo,size_t nFileSize);

private:
	
};


#endif

