#include "include/datafile.h"
#include <windows.h>
//#include "FuncPerformanceLog.h"
#include "objectpool.h"
#include <io.h>
#include <fcntl.h>

#pragma comment(lib,"winmm.lib")
#pragma comment(lib, "shlwapi.lib")

//#define Log_Debug debug_log
#define Log_Debug log_writelog
void MakeLower( char* string ,int nSize)
{
	//guardfunc;
	for( int i = 0;i<nSize ; i++ )
	{
		if( string[i] == 0 )
			return;

		if( string[i] >= 'A' && string[i] <= 'Z' )
		{
			string[i] += 32;
		}
		if(string[i] =='/')
			string[i] ='\\';
	}
	//unguard;
}
static poolmgr<fileinfo> &FileInfoPool ()
{
	//guardfunc;
	static poolmgr<fileinfo> m(e_all_packet_file_num, "fileinfo pools");
	return m;
	//unguard;
}

size_t file_h::read(void * buf,int buflen)
{
	if( poscur+buflen > f->area.size)
		return 0;
	int nReadSize=f->pk->ReadFileToBuf (f, (char *)buf, buflen,poscur,buflen);

	if(nReadSize > 0)
	{
		poscur+=nReadSize;
	}
	return nReadSize;
}

fileinfo *CreateFileInfo ()
{
	//guardfunc;
	fileinfo *self = FileInfoPool().GetObject();
	if (!self)
		return self;
	self->fileinfo::fileinfo();
	return self;
	//unguard;
}
void ReleaseFileInfo (fileinfo *self)
{
	//guardfunc;
	if (!self)
		return;
	FileInfoPool().FreeObject(self);
	//unguard;
}

filemgr::filemgr()
{
	//guardfunc;
	m_filetable.clear();
	m_setPacket.clear();
	//unguard;
}
filemgr::~filemgr()
{
	Destroy();
}
void filemgr::Destroy ()
{
	//guardfunc;
	CListPacket::iterator itb = m_setPacket.begin();
	for (;itb != m_setPacket.end();++itb)
	{
		packet* p = (*itb);
		delete p;
		p = NULL;
	}
	m_setPacket.clear();		
	m_filetable.clear();
	for (int i=0;i<m_setThreadIO.size();++i)
	{
		fclose(m_setThreadIO[i].m_fp);
	}
	//unguard;
}

void    filemgr::AddPacket(packet* p)
{
	//guardfunc;
	m_setPacket.push_back(p);
	//unguard;
}
void     filemgr::SavePacket()
{
	//guardfunc;
	CListPacket::iterator itb = m_setPacket.begin();
	for (;itb!=m_setPacket.end();++itb)
	{
	   (*itb)->SaveFileList();
	}
	//unguard;
}
void    filemgr::AfreshAllPacket()
{
	//guardfunc;
	CListPacket::iterator itb = m_setPacket.begin();
	for (;itb!=m_setPacket.end();++itb)
	{
		(*itb)->AfreshPacket();
	}
	//unguard;
}
packet*   filemgr::FindPacket(const char *name)
{
	//guardfunc;
	CListPacket::iterator itb = m_setPacket.begin();
	for (;itb!=m_setPacket.end();++itb)
	{
		if(0==strcmp((*itb)->GetPakcetName(),name))
			return (*itb);
	}
	return NULL;
	//unguard;
}
fileinfo *filemgr::FindFile (const char *name,bool b)
{
	//guardfunc;
	char filename[epacket_file_name_max_length];
	strcpy(filename,name);
	MakeLower(filename,strlen(filename));
FileCenter::iterator itr = m_filetable.find(filename);

// std::string s;
// s=filename;
// if(s.find("world")!=std::string::npos)
// {
// 	if(b)
// 		log_writelog1("GetFileInfo file name %s fail\n",filename);
// }
	if (itr != m_filetable.end())
		return itr->second;
	
	return NULL;
	//unguard;
}
void filemgr::WriteFileToLog(const char* name)
{
	//guardfunc;
#ifdef _DEBUG //lyh屏蔽日志

	FILE* pFile = fopen(name,"wb+");

	if(!pFile)
		return ;

	FileCenter::iterator itr = m_filetable.begin();
	
	for (;itr != m_filetable.end();++itr)
	{
		fileinfo* info = itr->second;
		fwrite(info->GetFileName(),strlen(info->GetFileName()),1,pFile);
		fwrite("\t\n",strlen("\t\n"),1,pFile);
	}
	fclose(pFile);
#endif // _DEBUG
	//unguard;
}

bool filemgr::AddFile(packet *pk, fileinfo *info)
{
	//guardfunc;
	if (strcmp(info->GetFileName(), "") == 0)
	{
		//Log_Debug("this file name is '', error!");
		return false;
	}
	if (strlen(info->GetFileName()) >= epacket_file_name_max_length)
	{
		//Log_Debug("this file name length is big to :%d !", epacket_file_name_max_length);
		return false;
	}
	if (FindFile(info->GetFileName()))
	{
		//Log_Debug("this file already in hash!, file name:%s", info->GetFileName());
		return false;
	}
	info->pk = pk;
	m_filetable.insert(std::make_pair(info->GetFileName(), info));
	return true;
	//unguard;
}

bool filemgr::RemoveFile (const char *name)
{
	//guardfunc;
	if (!name)
	{
		//Log_Debug("name is null!");
		return false;
	}
	if (strlen(name) >= epacket_file_name_max_length)
	{
		//Log_Debug("name length is over big to :%d", epacket_file_name_max_length);
		return false;
	}
	FileCenter::iterator itr = m_filetable.find(name);
	if (itr != m_filetable.end())
	{
		m_filetable.erase(itr);
		return true;
	}
	return false;
	//unguard;
}
Thread_IO*  filemgr::GetDataForThreadID(unsigned long threadid,const char* pFileName)
{
	//guardfunc;
	for (int i=0;i< m_setThreadIO.size();++i)
	{
		if(m_setThreadIO[i].dwCurrentThreadID == threadid && (0 == strcmp(m_setThreadIO[i].m_filename,pFileName)))
			return &m_setThreadIO[i];
	}
	return NULL;
	//unguard;
}
void        filemgr::AddThradIO(Thread_IO& thData)
{
	//guardfunc;

	m_setThreadIO.push_back(thData);
	//Log_Debug("threadio:%d  %d \n",thData.dwCurrentThreadID,(DWORD)(thData.m_fp));
	//unguard;
}
/* 获取文件的大小---单位:字节*/
static long file_size (const char *filename)
{
	//guardfunc;
	FILE *fp = fopen(filename, "rb");
	if (!fp)
		return 0;
	long int save_pos;
	long size_of_file;
	/* Save the current position. */
	save_pos = ftell( fp );
	/* Jump to the end of the file. */
	fseek( fp, 0L, SEEK_END );
	/* Get the end position. */
	size_of_file = ftell( fp );
	/* Jump back to the original position. */
	fseek( fp, save_pos, SEEK_SET );
	fclose(fp);
	return( size_of_file );
	//unguard;
}

packet::packet()
{
	//guardfunc;
	m_fp = NULL;
	memset(&m_headerinfo, 0, sizeof(m_headerinfo));
	m_packetname = "";
	m_areas.clear();
	m_empty_areas.clear();

	m_filesizetotal = 0;
	m_emptysizetotal = 0;
	//unguard;

}
packet::~packet()
{
	Close();
	
}


//增加一个含有文件的区域
bool packet::AddHasFileArea (fileinfo *info)
{
	//guardfunc;
	if (!info)
		return false;
	if (FindHasFileArea(info->GetFileName()))
	{
		//Log_Debug("this file is already in hash! file name:%s", info->GetFileName());
		return false;
	}
	m_areas.insert(std::make_pair(info->GetFileName(), info));
	return true;
	//unguard;
}

//移除一个含有文件的区域
fileinfo *packet::RemoveHasFileArea (const char *name)
{
	//guardfunc;
	if (!name)
		return NULL;
	fileinfo *info = NULL;
	AreaHash::iterator itr = m_areas.find(name);
	if (itr != m_areas.end())
	{
		info = itr->second;
		m_areas.erase(itr);
	}
	return info;
	//unguard;
}

//通过文件名获取含有文件的区域
fileinfo *packet::FindHasFileArea (const char *name)
{
	//guardfunc;
	if (!name)
		return NULL;
	AreaHash::iterator itr = m_areas.find(name);
	if (itr != m_areas.end())
		return itr->second;
	return NULL;
	//unguard;
}


////////////////////////////////////////////////////
//根据所需的大小，获取可用的区域
fileinfo *packet::GetCanUseArea (size_t needsize)
{
	//guardfunc;
	fileinfo *info;
	for (std::list<fileinfo*>::iterator itr = m_empty_areas.begin(); itr != m_empty_areas.end(); ++itr)
	{
		if (needsize <= (*itr)->area.GetCanUseSpace())
		{
			info = (*itr);
			m_empty_areas.erase(itr);
			return info;
		}
	}
	return NULL;
	//unguard;
}

//增加一个可用的区域
bool packet::AddCanUseArea (fileinfo *info)
{
	//guardfunc;
	if (!info)
		return false;
	if (FindCanUseArea(info))
	{
		//Log_Debug("this fileinfo already in empty list!, error!");
		return false;
	}
	if (info->area.filetype != epacket_space_type_no_file)
	{
		///Log_Debug("file type error!, file type;%d", info->area.filetype);
		return false;
	}
	m_empty_areas.push_back(info);
	return true;
	//unguard;
}

//查找此区域是否已经在可用的区域中
bool packet::FindCanUseArea (fileinfo *info)
{
	//guardfunc;
	if (!info)
		return false;
	for (std::list<fileinfo*>::iterator itr = m_empty_areas.begin(); itr != m_empty_areas.end(); ++itr)
	{
		if ((*itr) == info)
			return true;
	}
	return false;
	//unguard;
}
//写包头
bool packet::WriteHeader ()
{
	//guardfunc;
	fseek(m_fp, 0, SEEK_SET);
	size_t writesize = fwrite(&m_headerinfo, 1, sizeof(m_headerinfo), m_fp);
	if (writesize == 0)
	{
		///Log_Debug("create new packet, but fwrite falied!, new packet name:%s", m_packetname.c_str());
		return false;
	}
	fflush(m_fp);
	return true;
	//unguard;
}

//读包头
bool packet::ReadHeader ()
{
	//guardfunc;
	//读包头
	size_t readsize = fread((void *)&m_headerinfo, 1, sizeof(m_headerinfo), m_fp);
	if (readsize == 0)
	{
		//Log_Debug("fread return 0");
		return false;
	}
	if (m_headerinfo.offset > file_size(m_packetname.c_str()))
	{
		//Log_Debug("packet offset error!, offset:%u, file size:%u", m_headerinfo.offset, file_size(m_packetname.c_str()));
		return false;
	}
	if (m_headerinfo.type != PACKET_TYPE)
	{
		//Log_Debug("packet type error!");
		return false;
	}
	fflush(m_fp);
	return true;
	//unguard;
}

//关闭包
void packet::Close ()
{
	//guardfunc;
	if (m_fp)
	{
		fclose(m_fp);
		m_fp = NULL;
	}
	for (AreaHash::iterator itr = m_areas.begin(); itr != m_areas.end(); ++itr)
	{
		filemgr::Instance().RemoveFile(itr->second->GetFileName());
		ReleaseFileInfo(itr->second);
	}
	for (std::list<fileinfo*>::iterator itr = m_empty_areas.begin(); itr != m_empty_areas.end(); ++itr)
	{
		ReleaseFileInfo((*itr));
	}
	m_areas.clear();
	m_empty_areas.clear();
	memset(&m_headerinfo, 0, sizeof(m_headerinfo));
	m_packetname = "";
	m_filesizetotal = 0;
	m_emptysizetotal = 0;
	//unguard;
}

//打开指定的包。
bool packet::OpenPakcet (const char *packetname)
{
	//guardfunc;
	if (!packetname)
		return false;
	if (m_fp)
	{
		//Log_Debug("packet file pointer is not null, error!, packet name:%s", GetPakcetName());
		return false;
	}
	m_fp = fopen(packetname, "rb+");
	if (!m_fp)
	{
		//Log_Debug("open file error! file:%s", packetname);
		return false;
	}
	
	m_packetname = packetname;
	if (!ReadHeader())
		goto failed;

	LoadFileList();
	Thread_IO io_data;
	io_data.dwCurrentThreadID = GetCurrentThreadId();
	io_data.m_fp = m_fp;
	strcpy(io_data.m_filename,GetPakcetName());
	filemgr::Instance().AddThradIO(io_data);
	return true;
failed:
	if (m_fp)
	{
		fclose(m_fp);
		m_fp = NULL;
	}
	memset(&m_headerinfo, 0, sizeof(m_headerinfo));
	m_packetname = "";
  
	return false;
	//unguard;
}

//创建指定的包
bool packet::CreatePacket (short type, const char *packetname)
{
	//guardfunc;
	switch (type)
	{
	case enum_packet_type_not_release:
		break;
	case enum_packet_type_create_and_release:
		break;
	default:
		{
			//Log_Debug("create packet, but packet type is error!, type:%d", type);
			return false;
		}
	}
	if (strcmp(packetname, "") == 0)
	{
		//Log_Debug("create packet, but packet name is '', error!");
		return false;
	}
	if (strlen(packetname) >= epacket_file_name_max_length)
	{
		//Log_Debug("create packet, but packet name length is big to :%d", epacket_file_name_max_length);
		return false;
	}
	if (strcmp(m_packetname.c_str(), "") != 0)
	{
		//Log_Debug("create packet, but this object is not new!, old packet name:%s", m_packetname.c_str());
		return false;
	}
	if (m_fp != NULL)
	{
		//Log_Debug("create packet, but this object is not new!, file pointer is not null!");
		return false;
	}

	m_fp = fopen(packetname, "wb+");
	if (!m_fp)
	{
		//Log_Debug("create new packet failed, new packet name:%s", packetname);
		return false;
	}

	m_headerinfo.mag_type = type;
	m_headerinfo.type = PACKET_TYPE;
	m_headerinfo.offset = sizeof(m_headerinfo);
	m_packetname = packetname;

	if (!WriteHeader())
		goto createfailed;

	return true;
createfailed:
	if (m_fp)
	{
		fclose(m_fp);
		m_fp = NULL;
	}
	memset(&m_headerinfo, 0, sizeof(m_headerinfo));
	m_packetname = "";
	return false;
	//unguard;
}

//载入此包的文件列表，若数据错误则返回false
bool packet::LoadFileList ()
{
	//guardfunc;
	if (!m_fp)
	{
		//Log_Debug("packet pointer is null, packet name:%s", GetPakcetName());
		return false;
	}
	int packetsize = file_size(m_packetname.c_str());
	if ((packetsize - m_headerinfo.offset)%sizeof(struct file_area) != 0)
	{
		//Log_Debug("packet is failed!, packet name:%s", GetPakcetName());
		return false;
	}
	int filenum = ((packetsize - m_headerinfo.offset)/sizeof(struct file_area));
	fseek(m_fp, m_headerinfo.offset, SEEK_SET);
	fileinfo *info = NULL;
	while (filenum > 0)
	{
		info = CreateFileInfo();
		if (!info)
		{
			//Log_Debug("load file list, create file info return null, packet name:%s", GetPakcetName());
			return false;
		}
		if (fread(&info->area, 1, sizeof(struct file_area), m_fp) == 0)
		{
			//Log_Debug("load file list, fread error!, packet name:%s", GetPakcetName());
			ReleaseFileInfo(info);
			return false;
		}
		if (epacket_space_type_no_file == info->area.filetype)
		{
			if (info->area.size != 0)
			{
				//Log_Debug("this area is not has file, but size is not equal 0, error!, packet name:%s", GetPakcetName());
				ReleaseFileInfo(info);
				return false;
			}
			if (info->area.space == 0 || info->area.space > packetsize || (info->area.space + info->area.offset) > m_headerinfo.offset)
			{
				//Log_Debug("this area is bad, area space:%u, packetsize:%u, area offset:%u, packet offset:%u", info->area.space, packetsize, info->area.offset, m_headerinfo.offset);
				ReleaseFileInfo(info);
				return false;
			}
			if (!AddCanUseArea(info))
			{
				//Log_Debug("add this area to can use area list error!, packet name:%s", GetPakcetName());
				ReleaseFileInfo(info);
				return false;
			}
		}
		else if (epacket_space_type_has_file == info->area.filetype)
		{
			if (!filemgr::Instance().AddFile(this, info) || !AddHasFileArea(info))
			{
				//Log_Debug("add file to hash table, error!, packet name:%s, file name:%s", GetPakcetName(), info->GetFileName());
				ReleaseFileInfo(RemoveHasFileArea(info->GetFileName()));
				return false;
			}
		}
		else
		{
			//Log_Debug("error!, file type is not valid!, packet name:%s, file name:%s", GetPakcetName(), info->GetFileName());
			ReleaseFileInfo(info);
			return false;
		}
		--filenum;
	}
	fflush(m_fp);
	return true;
	//unguard;
}

//写入文件列表到指定的包中
void packet::SaveFileList ()
{
	//guardfunc;
	if (!m_fp)
	{
		//Log_Debug("packet pointer is null!, packet name:%s", GetPakcetName());
		return;
	}
	
	fseek(m_fp, m_headerinfo.offset, SEEK_SET);
	for (AreaHash::iterator itr = m_areas.begin(); itr != m_areas.end(); ++itr)
	{
		assert(itr->second->pk == this);
		fwrite(&itr->second->area, 1, sizeof(struct file_area), m_fp);
	}
	for (std::list<fileinfo*>::iterator itr = m_empty_areas.begin(); itr != m_empty_areas.end(); ++itr)
	{
		fwrite(&(*itr)->area, 1, sizeof(struct file_area), m_fp);
	}
	fflush(m_fp);
	//变更文件大小，需要时才变更
	long packetsize = file_size(m_packetname.c_str());
	long realsize = m_headerinfo.offset + (m_areas.size()+m_empty_areas.size())*sizeof(struct file_area);
	if (packetsize > realsize)
	{
		int handle = open("changsize.txt", O_BINARY | O_RDWR);
		chsize(handle, realsize);
	}
	WriteHeader();
	//unguard;
}
void packet::AfreshPacket()
{
	//guardfunc;
	std::list<fileinfo*>::iterator itb = m_empty_areas.begin();
	size_t nFree =0;
	for (;itb != m_empty_areas.end();++itb)
	{
		nFree+= (*itb)->area.size;
	}

	fseek(m_fp,0,SEEK_END);
	size_t filesize = ftell(m_fp);
	size_t freesize = nFree / filesize;

   	if(freesize >= max_nouse_area)//须要重构	
   	{
		char temp[epacket_file_name_max_length];
		strcpy(temp,GetPakcetName());
		strcat(temp,".tmp");
	
		packet newpacket;
		if(!newpacket.CreatePacket(enum_packet_type_not_release,temp))
		{
			//Log_Debug("create %s",temp);
			return ;
		}
#define D_SRCDATA_SIZE 4*1024*1024
		char* pSrcData = new char[D_SRCDATA_SIZE]; 
		for (AreaHash::iterator itr = m_areas.begin(); itr != m_areas.end(); ++itr)//只增加有用的
		{
			fileinfo* pInfo = itr->second;
			if(pInfo->area.filetype == epacket_space_type_has_file)
			{
				newpacket.AddFile(itr->second,pSrcData,D_SRCDATA_SIZE);
			}			
		}
        delete []pSrcData;
		newpacket.SaveFileList();
		newpacket.Close();
		
		char packetname[epacket_file_name_max_length];
		strncpy(packetname,GetPakcetName(), sizeof(packetname)-1);
		packetname[sizeof(packetname)-1] = 0;
		this->Close();
		remove(packetname);
		rename(temp,packetname);		
	}
	//unguard;
}
bool packet::ReadFileToBuf (fileinfo *info, char *buf, size_t buflen)
{
	//guardfunc;
	if(!info || !buf)
		return false;
	if(info->area.size > buflen)
	{
		//Log_Debug("info->area.size > buflen");
		return false;
	}
	Thread_IO* pThread = filemgr::Instance().GetDataForThreadID(GetCurrentThreadId(),GetPakcetName());
	if(!pThread)
	{
		Thread_IO thread_io;
		thread_io.m_fp = fopen(GetPakcetName(),"rb+");
		if(!thread_io.m_fp)
		{
			if(GetLastError() == ERROR_JOIN_TO_JOIN)
			{
				thread_io.m_fp = fopen(GetPakcetName(),"rb");

			}
			if(!thread_io.m_fp)
			{
				//Log_Debug("thread_io.m_fp = fopen(GetPakcetName(),'rb+')\n");
				return false;
			}			
		}
		thread_io.dwCurrentThreadID = GetCurrentThreadId();
		strcpy(thread_io.m_filename,GetPakcetName());

		filemgr::Instance().AddThradIO(thread_io);

		fseek(thread_io.m_fp,info->area.offset,SEEK_SET);
		fread(buf,info->area.size,1,thread_io.m_fp);

	}else
	{
		int nErr = fseek(pThread->m_fp,info->area.offset,SEEK_SET);
		fread(buf,info->area.size,1,pThread->m_fp);
	}	
#ifdef  USE_FILE_PACKET_ENCRYPT
	ENCRYPT_PACKET_FILE(buf,info->area.size);
#endif
	return true;
	//unguard;
}
size_t packet::ReadFileToBuf (fileinfo *info, char *buf, size_t buflen,size_t nStart,size_t nSize)
{
	//guardfunc;
	if(!info || !buf)
		return 0;
	if(nSize < buflen)
	{
		//Log_Debug("nSize < buflen");
		return 0;
	}
	size_t nOffset = info->area.offset+nStart;//取当前读的位置
	if(nOffset > (info->area.offset+info->area.size))//是不是超过文件大小
	{
		//Log_Debug("nOffset  > filesize");
		return 0;
	}
	size_t nFileOffset = info->area.offset+info->area.size;//文件偏移+文件大小就是这个文件占的最后偏移位置
	size_t nFileSize = 0;
	if(nFileOffset > nOffset)//当前读的位置是不是文件最后偏位位置
	{
		size_t nFsize = nOffset+nSize;//设置读的位置+要读的大小看看偏移的位置
		if(nFileOffset > nFsize)//读完偏移位置如果小于等于文件最后偏移位置
			nFileSize = nSize;//就读当前大小
		else
			nFileSize = nFileOffset - nOffset;//否则就读剩下的内容
	}else
		return 0;
	
	
	fseek(m_fp,nOffset,SEEK_SET);

	nFileSize =  fread(buf,1,nFileSize,m_fp);
#ifdef   USE_FILE_PACKET_ENCRYPT
	ENCRYPT_PACKET_FILE(buf,nFileSize);
#endif
	return nFileSize;
	//unguard;
}
////////////////////////////////////////////////////
//查找指定的文件
fileinfo *FindFile (const char *name);

//读指定的文件到指定的缓冲中
bool ReadFileToBuf (fileinfo *info, char *buf, size_t buflen);

//获取指定区域中文件的大小------断言此区域一定有文件
size_t GetFileSize (fileinfo *info);

//增加一个文件到包中
fileinfo *packet::AddFile (const char *path,const char* pDstPath)
{
	//guardfunc;
	bool bDst = false;//是否用别名
	char filename[epacket_file_name_max_length];
	char DstFileName[epacket_file_name_max_length];
	strcpy(filename,path);
	MakeLower(filename,strlen(filename));
	if(pDstPath)//如果不为null就是用别名
	{
		strcpy(DstFileName,pDstPath);
		MakeLower(DstFileName,strlen(DstFileName));
		bDst = true;
	}

	long newfilesize, packetsize;
	bool bDstIf = (bDst?strcmp(DstFileName, "") == 0:false);//别名是否为空
	if (strcmp(filename, "") == 0 || bDstIf)
	{
		//Log_Debug("add new file, but new file name is ''!, error!");
		return NULL;
	}
	bDstIf =(bDst?strlen(DstFileName) >=epacket_file_name_max_length : false);//别名是否大于最大数
	if (strlen(filename) >= epacket_file_name_max_length ||bDstIf)
	{
		//Log_Debug("add new file, but new file name length is big to %d", epacket_file_name_max_length);
		return NULL;
	}

	fileinfo *info = NULL;
	if(bDst)//如果别名就用别名查找
		info = filemgr::Instance().FindFile(DstFileName);
	else
		info = filemgr::Instance().FindFile(filename);

	if (info != NULL)
	{
		//Log_Debug("add new file, but new file already in packet, packet name:%s, new file name:%s", info->pk->GetPakcetName(), info->GetFileName());
		return NULL;
	}

	newfilesize = file_size(filename);
	if (newfilesize <= 0)
	{
		//Log_Debug("add new file, but new file size <= 0, size:%ld", newfilesize);
		return NULL;
	}
	if (!m_fp)
	{
		//Log_Debug("add file to packet, but packet file pointer is null, packet name:%s, new file:%s", m_packetname.c_str(), path);
		return NULL;
	}
	if (strcmp(m_packetname.c_str(), "") == 0)
	{
		//Log_Debug("add file to packet, but packet name is '', error! new file name:%s", path);
		return NULL;
	}
	packetsize = file_size(m_packetname.c_str());
	if (packetsize >= enum_file_max_size)
	{
		//Log_Debug("add file to packet, but packet size is big to :%ld", enum_file_max_size);
		return NULL;
	}
	if (packetsize + newfilesize >= enum_file_max_size)
	{
		//Log_Debug("add file to packet, but add new file to packet, then, packet size is big to :%ld", enum_file_max_size);
		return NULL;
	}
	FILE *src = fopen(filename, "rb");
	if (!src)
	{
		//Log_Debug("add file to packet, but open new file error!, new file name:%s, packet name:%s", path, m_packetname.c_str());
		return NULL;
	}
	long oldoffset = m_headerinfo.offset;
	bool isnewinfo = false;
	info = GetCanUseArea(newfilesize);
	if (!info)
	{
		info = CreateFileInfo();
		if (!info)
			return NULL;
		info->area.offset = m_headerinfo.offset;
		info->area.space = newfilesize;
		m_headerinfo.offset = info->area.offset + info->area.space;
		isnewinfo = true;
	}else
	{
		if(info->area.space > newfilesize)
			CreateNoUserInfo(info,newfilesize);
	}

	size_t count = 0;
	static char buf[1024];
	fseek(m_fp, info->area.offset, SEEK_SET);
	do 
	{
		count = fread(buf, 1, sizeof(buf), src);
#ifdef   USE_FILE_PACKET_ENCRYPT
		ENCRYPT_PACKET_FILE(buf,count);
#endif
		
		fwrite(buf, 1, count, m_fp);
	} while (count == sizeof(buf));
	fclose(src);

	info->area.filetype = epacket_space_type_has_file;
	info->area.size = newfilesize;
	if(bDst)//包中增加别名
		strncpy(info->area.name, DstFileName, sizeof(info->area.name));
	else
		strncpy(info->area.name, filename, sizeof(info->area.name));

	info->area.name[sizeof(info->area.name)-1] = 0;

	if (!filemgr::Instance().AddFile(this, info) || !AddHasFileArea(info))
	{
		//Log_Debug("filemgr add file error or add hash file area error!, new file name:%s, packet name:%s", path, GetPakcetName());
		m_headerinfo.offset = oldoffset;
		if (isnewinfo)
			ReleaseFileInfo(info);
		else
		{
			info->area.ResetForAddEmpty();
			AddCanUseArea(info);
		}
		return NULL;
	}
	return info;
	//unguard;
}


fileinfo* packet::AddFile(fileinfo* pfileinfo,char* pSrcData,size_t nSize)
{
	//guardfunc;
	if(!pfileinfo)
		return NULL;

	size_t newfilesize = pfileinfo->area.size;
	if (newfilesize <= 0)
	{
			//Log_Debug("add new file, but new file size <= 0, size:%ld", newfilesize);
			return NULL;
	}

	if (strcmp(m_packetname.c_str(), "") == 0)
	{
		//Log_Debug("add file to packet, but packet name is '', error! new file name:%s", pfileinfo->GetFileName());
		return NULL;
	}
	size_t	packetsize = file_size(m_packetname.c_str());
	if (packetsize >= enum_file_max_size)
	{
		//Log_Debug("add file to packet, but packet size is big to :%ld", enum_file_max_size);
		return NULL;
	}
	if (packetsize + newfilesize >= enum_file_max_size)
	{
		//Log_Debug("add file to packet, but add new file to packet, then, packet size is big to :%ld", enum_file_max_size);
		return NULL;
	}
	long oldoffset = m_headerinfo.offset;
	bool isnewinfo = false;
	fileinfo* info = CreateFileInfo();//因为是重构是不可能有空闲的
	if (!info)
		return NULL;
	info->area.offset = m_headerinfo.offset;
	info->area.space = newfilesize;
	m_headerinfo.offset = info->area.offset + info->area.space;
	isnewinfo = true;
	
	size_t count = 0;
	fseek(m_fp, info->area.offset, SEEK_SET);

	size_t  nOffset =0;
	do 
	{
		if(nSize <= pfileinfo->area.size)
			DWORD dd =0;
		size_t nReadSize = pfileinfo->pk->ReadFileToBuf(pfileinfo,pSrcData,nSize,nOffset,nSize);
		
		if(nReadSize > 0)
		{
			nOffset+=nReadSize;
#ifdef   USE_FILE_PACKET_ENCRYPT
			ENCRYPT_PACKET_FILE(pSrcData,nReadSize);
#endif
			fwrite(pSrcData,nReadSize, 1,m_fp);
		}else
		{
			//Log_Debug("read file 出错\n");
			break;
		}
		
	} while (pfileinfo->area.size > nOffset);

	info->area.filetype = epacket_space_type_has_file;
	info->area.size = newfilesize;
	strncpy(info->area.name, pfileinfo->GetFileName(), sizeof(info->area.name));
	info->area.name[sizeof(info->area.name)-1] = 0;
	info->pk = this;
	if (!AddHasFileArea(info))
	{
		//Log_Debug("filemgr add file error or add hash file area error!, new file name:%s, packet name:%s", pfileinfo->GetFileName(), GetPakcetName());
		m_headerinfo.offset = oldoffset;
		if (isnewinfo)
			ReleaseFileInfo(info);
		else
		{
			info->area.ResetForAddEmpty();
			AddCanUseArea(info);
		}
		return NULL;
	}
	return info;
	//unguard;
}
//更新指定的文件
fileinfo *packet::UpdateFile (const char *path,const char* pDstPath)
{
	//guardfunc;
	bool bDst = false;//是否用别名
	char DstFileName[epacket_file_name_max_length];
	char filename[epacket_file_name_max_length];
	strcpy(filename,path);
	MakeLower(filename,strlen(filename));
	if(pDstPath)
	{
		strcpy(DstFileName,pDstPath);
		MakeLower(DstFileName,strlen(DstFileName));
		bDst = true;
	}

	long newfilesize, packetsize;
	bool bDstIf = (bDst?strcmp(DstFileName, "")==0:true);//别名是否为空
	if (strcmp(filename, "") == 0|| bDstIf)
	{
		//Log_Debug("update file, but file name is ''!, error!");
		return NULL;
	}
    bDstIf =(bDst?strlen(DstFileName) >=epacket_file_name_max_length : true);//别名是否大于最大数
	if (strlen(filename) >= epacket_file_name_max_length)
	{
		//Log_Debug("update file, but file name length is big to %d", epacket_file_name_max_length);
		return NULL;
	}
	fileinfo *info =NULL;
	if(bDst)
		info= FindHasFileArea(DstFileName);
	else
		info = FindHasFileArea(filename);

	if (!info)
	{
		if(bDst)//如果别名就用别名查找
			info = filemgr::Instance().FindFile(DstFileName);
		else
			info = filemgr::Instance().FindFile(filename);

		if (!info)
		{
			//Log_Debug("update file, the file in the packet, but not in filemgr hash_table!, packet name:%s, file name:%s", GetPakcetName(), path);
			return NULL;
		}
		//Log_Debug("update file, but file not in the packet, packet name:%s, file name:%s", GetPakcetName(), path);
		return NULL;
	}

	newfilesize = file_size(filename);
	if (newfilesize <= 0)
	{
		//Log_Debug("update file, but file size <= 0, size:%ld", newfilesize);
		return NULL;
	}
	if (!m_fp)
	{
		//Log_Debug("update file in packet, but packet file pointer is null, packet name:%s, file:%s", m_packetname.c_str(), path);
		return NULL;
	}
	if (strcmp(m_packetname.c_str(), "") == 0)
	{
		//Log_Debug("update file in packet, but packet name is '', error! file name:%s", path);
		return NULL;
	}
	packetsize = file_size(m_packetname.c_str());
	if (packetsize >= enum_file_max_size)
	{
		//Log_Debug("update file in packet, but packet size is big to :%ld", enum_file_max_size);
		return NULL;
	}
	if (newfilesize > info->area.space)
	{
		//原来的装不下了，
		//先移除，然后调用增加文件函数
		fileinfo *newinfo = NULL;
		if(bDst)
		{
			filemgr::Instance().RemoveFile(DstFileName);
			newinfo = RemoveHasFileArea(DstFileName);
		}else
		{
			filemgr::Instance().RemoveFile(filename);
			newinfo = RemoveHasFileArea(filename);
		}
		
		if (info != newinfo)
		{
			//Log_Debug("why info != newinfo??? packet name:%s, file name:%s", GetPakcetName(), path);
			return NULL;
		}
		info->area.ResetForAddEmpty();
		if (!AddCanUseArea(info))
		{
			//Log_Debug("why add info to can use area error?? packet name:%s, update file name:%s  .(need rebulid this packet.)", GetPakcetName(), path);
			ReleaseFileInfo(info);
			return NULL;
		}
		return AddFile(filename,pDstPath);
	}
	//原来的还可装下，则
	FILE *src = fopen(filename, "rb");
	if (!src)
	{
		//Log_Debug("update file to packet, but open file error!, file name:%s, packet name:%s", path, m_packetname.c_str());
		return NULL;
	}
	size_t count = 0;
	static char buf[1024];
	fseek(m_fp, info->area.offset, SEEK_SET);
	do 
	{
		count = fread(buf, 1, sizeof(buf), src);
#ifdef   USE_FILE_PACKET_ENCRYPT
		ENCRYPT_PACKET_FILE(buf,count);
#endif
		fwrite(buf, 1, count, m_fp);
	} while (count == sizeof(buf));
	fclose(src);
	if(info->area.space > newfilesize)
		CreateNoUserInfo(info,newfilesize);
	info->area.size = newfilesize;
	return info;
	//unguard;
}
//删除指定的文件
bool packet::DelFile (const char *path)
{
	//guardfunc;
	char filename[epacket_file_name_max_length];
	strcpy(filename,path);
	MakeLower(filename,strlen(filename));

	fileinfo *info = FindHasFileArea(filename);
	if (!info)
	{
		info = filemgr::Instance().FindFile(filename);
		if (info)
		{
			//Log_Debug("find file in packet not find, but in filemgr finded!, file name:%s, in: %s packet.", path, info->pk->GetPakcetName());
			return false;
		}
		//Log_Debug("not find file, delete file failed!, file name:%s", path);
		return false;
	}
	filemgr::Instance().RemoveFile(filename);
	fileinfo *newinfo = RemoveHasFileArea(filename);
	if (newinfo != info)
	{
		//Log_Debug("delete file, why info != newinfo??? packet name:%s, file name:%s", GetPakcetName(), path);
		return false;
	}
	info->area.ResetForAddEmpty();
	if (!AddCanUseArea(info))
	{
		//Log_Debug("delete file, why add info to can use area error?? packet name:%s, delete file name:%s. (need rebulid this packet.)", GetPakcetName(), path);
		ReleaseFileInfo(info);
		return false;
	}
	return true;
	//unguard;
}
void packet::CreateSubFile(const char* strDir)
{
	//guardfunc;

	for (AreaHash::iterator itr = m_areas.begin(); itr != m_areas.end(); ++itr)//只增加有用的
	{
		char strfile[epacket_file_name_max_length];
		strcpy(strfile,strDir);
		strcat(strfile,"\\");
		strcat(strfile,itr->second->area.name);
	
		FILE* p = fopen(strfile,"wb+");
		if(p)
		{
			char* buffer = new char[itr->second->area.size+1];
			ReadFileToBuf(itr->second,buffer,itr->second->area.size);
			fwrite(buffer,itr->second->area.size,1,p);
			delete[] buffer;
		}
		fclose(p);
	}
	//unguard;
}
void packet::FileInfoSaveToFile(const char* strDir)
{
	//guardfunc;
	FILE* p = fopen(strDir,"wb+");

	char buffer[1024];
	for (AreaHash::iterator itr = m_areas.begin(); itr != m_areas.end(); ++itr)//只增加有用的
	{
		
		sprintf(buffer,"文件名:%s-类型:%d-长度:%d-位置:%d-区域大小:%d \n",itr->second->area.name,itr->second->area.filetype,itr->second->area.size,itr->second->area.offset,itr->second->area.space);
        fwrite(buffer,strlen(buffer),1,p);	  
	}
	fclose(p);
	//unguard;
}
void packet::CreateNoUserInfo(fileinfo* pFatherInfo,size_t nFileSize)
{
	//guardfunc;
	if(pFatherInfo->area.space <= nFileSize )
		return ;
    if((pFatherInfo->area.space - nFileSize) <= 1024)//如果小于1K不计
		return ;
	

	fileinfo* info = CreateFileInfo();
	if(!info)
		return ;

	memset(info->area.name,0,sizeof(info->area.name));
	info->area.filetype = epacket_space_type_no_file;
	info->area.offset = pFatherInfo->area.offset+nFileSize;
	info->area.size = 0;
	info->area.space = pFatherInfo->area.space-nFileSize;
	info->pk = this;
	if (!AddCanUseArea(info))
	{
		ReleaseFileInfo(info);
		return ;
	}
	pFatherInfo->area.space = nFileSize;
	return ;
	//unguard;
}
