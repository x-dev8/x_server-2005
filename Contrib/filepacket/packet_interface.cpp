#include "include/packet_interface.h"
#include <stdio.h>
#include <Windows.h>
#include "include/datafile.h"
#include <io.h>
//#include "tinyxml.h"
#include "RapidXml/MeRapidXml.h"

#define Log_Debug log_error
//
namespace packet_namespace
{
	bool g_bReadPacket;
	//仿fread
	int w_fread(void * buf,int len, int count,f_Handle *f)
	{
		if(f->t1)
		{
			return ((file_h *)f->t1)->read(buf,len*count);
		}
		else if(f->t2)
		{
			return fread(buf,len,count,f->t2);
		}
		return -1;
	}
	//仿fopen
	f_Handle* w_fopen(const char * name,char * type)
	{
		f_Handle *handle=new f_Handle;
		if(g_bReadPacket)
		{
			file_h * f= new file_h;
			f->f=GetFileInfo(name);
			if(f->f)
			{
				handle->t1=f;
				return handle;
			}
			delete f;
		}
		
		handle->t2=fopen( name, type );if(handle->t2)return handle;
		delete handle;
		return NULL;
	}
	//仿fopen_s
	int w_fopen_s(f_Handle** f,const char * name,char * type)
	{
		*f=w_fopen(name,type);
		if(*f)return 0;
		return -1;
	}
	//仿fclose
	void w_fclose(f_Handle * f)
	{
		if(f->t2)
			fclose( f->t2 );

		delete f;
		f=NULL;
	}
	//仿fseek
	int w_fseek(f_Handle * _File, long _Offset, __in int _Origin)
	{
		if(_File->t1)
		{
			return ((file_h *)_File->t1)->seek(_Offset,_Origin);
		}
		else if(_File->t2)
		{
			return fseek(_File->t2,_Offset,_Origin);
		}
		return 0;
	}
	//仿getc
	int w_getc(f_Handle *f)
	{
		char buf;
		w_fread(&buf,1, 1,f);
		return (int)buf;
	}
	
	int str_f(char *s, char *a)
	{
		int ls,la,i;
		int flag = -1;
		ls = strlen(s);
		la = strlen(a);
		if (la > ls) return -1;
		for (i=0;i<=ls-la;i++){
			if  (strncmp(s+i,a,la)==0) return i;
		}
		return flag;
	};

	
	
	int w_fgets(char * buf,int count,f_Handle *f)
	{
		int iread=w_fread(&buf,count, 1,f);
		if(iread>0)
		{
			int pos=str_f(buf,"\r\n");
			if(pos)
			{
				pos+=2;
				*(buf+pos)='\0';
			}
			if(pos>0)
			{
				w_fseek(f,pos-iread,SEEK_CUR);
				return pos;
			}

			return iread;
		}
		return -1;
	}
	void w_rewind(f_Handle *f)
	{
		w_fseek(f,0,SEEK_SET);
	}
	int w_ftell(f_Handle *f)
	{
		if(f->t1)
		{
			return ((file_h *)f->t1)->f->area.size;
		}
		else if(f->t2)
		{
			return ftell(f->t2);
		}
		return -1;
	}
	packet*  getpacket(const char *name)
	{
		if(!name)return NULL;

		packet* pPacket = filemgr::Instance().FindPacket(name);
		if(pPacket)
			return pPacket;

		pPacket = new packet;
		if(!pPacket)
		{
			//Log_Debug("new packet err");
			return false;
		}
		filemgr::Instance().AddPacket(pPacket);

		if(!pPacket->OpenPakcet(name))
			pPacket->CreatePacket(enum_packet_type_not_release, name);			

		return pPacket;
	}
	packet*  findpacket(const char *name)
	{
		if(!name)return NULL;

		return  filemgr::Instance().FindPacket(name);
	}
	void    SavePacket()
	{
		return filemgr::Instance().SavePacket();
	}
	void    AfreshAllPacket()
	{
		return filemgr::Instance().AfreshAllPacket();
	}
	void    GetAllFileName()
	{
		filemgr::Instance().WriteFileToLog("data.log");
	}
	bool openpacket (const char *name)
	{
		if(!name)return false;

		packet* pPacket = new packet;
		if(!pPacket)
		{
			//Log_Debug("new packet err");
			return false;
		}

		filemgr::Instance().AddPacket(pPacket);

		return pPacket->OpenPakcet(name);
	}
	//
	bool readfiletobuf(const char *name, char *buf, size_t buflen)
	{
		if(!name || !buf)
			return false;

		fileinfo* pInfo = filemgr::Instance().FindFile(name);

		if(!pInfo)
			return false;
		
		return pInfo->pk->ReadFileToBuf(pInfo,buf,buflen);
	}

	size_t GetFileSize (struct fileinfo *info)
	{
		if (info)
			return info->area.size;
		else
			return 0;
	}
	//
	bool readfiletobuf(fileinfo* pInfo,char *buf, size_t buflen)
	{
		if(!pInfo || !buf)
			return false;

		return pInfo->pk->ReadFileToBuf(pInfo,buf,buflen);
	}
	//
	char* readfile (const char *name, size_t *buflen)
	{
		return NULL;
	}

	static void string_replace( std::string &strBig, const std::string &strsrc, const std::string &strdst )
	{
		std::string::size_type pos = 0;
		std::string::size_type srclen = strsrc.size();
		std::string::size_type dstlen = strdst.size();

		while( (pos=strBig.find(strsrc, pos)) != std::string::npos )
		{
			strBig.replace( pos, srclen, strdst );
			pos += dstlen;
		}
	} 

	std::string s_PacketRootPath;
	fileinfo*  GetFileInfo(const char *name)
	{
		//绝对路径与..\data\config\xx的相对路径 ----> data\congi\xx
		std::string path=name;
		string_replace(path,"/","\\");
		string_replace(path,"\\\\","\\");
		if(!s_PacketRootPath.empty())string_replace(path,s_PacketRootPath+"\\","");
		


		string_replace(path,"..\\","");
		string_replace(path,".\\","");
		if(path.substr(0,1)=="\\")path=path.substr(1,path.length()-1);
		return 	filemgr::Instance().FindFile(path.c_str(),true); 
	}
// 	int   GetFileSize(const char *name)
// 	{
// 		if(!name)
// 			return 0;
// 
// 		fileinfo* pInfo = filemgr::Instance().FindFile(name);
// 
// 		if(!pInfo)
// 			return 0;
// 
// 		return pInfo->area.size;    
// 	}
	void  release ()
	{
		filemgr::Instance().Destroy();
	}

	bool    LoadXML(MeXmlDocument& doc,const char * filename)
	{
		if(!g_bReadPacket)
		{
			if(!doc.LoadFromFile(filename))
			{
				fileinfo* pFileInfo = GetFileInfo(filename);
				if(!pFileInfo)
				{
					//Log_Debug("g_breadpacket 假 找到不文件%s",filename);
					return false;
				}
				char* buffer = new char[pFileInfo->area.size+1];
				if(!readfiletobuf(pFileInfo,buffer,pFileInfo->area.size))
				{
					//Log_Debug("g_breadpacket 假 if(!readfiletobuf(pFileInfo,buffer,pFileInfo->area.size)) %s",filename);
					return doc.LoadFromFile(filename);
				}
				buffer[pFileInfo->area.size]='\0';
				bool bSuc = true;
					doc.Parse(buffer);//doc.LoadFromBuffer(buffer,pFileInfo->area.size);

		//		delete[] buffer;

				return bSuc;

			}
			return true;	

		}else
		{
			fileinfo* pFileInfo = GetFileInfo(filename);
			if(!pFileInfo)
			{

				//Log_Debug("g_breadpacket 真 fileinfo* pFileInfo = GetFileInfo(filename)找到不文件%s",filename);
				return doc.LoadFromFile(filename);
			}
			char* buffer = new char[pFileInfo->area.size+1];
			if(!readfiletobuf(pFileInfo,buffer,pFileInfo->area.size))
			{
				//Log_Debug("g_breadpacket 真 readfiletobuf(pFileInfo,buffer,pFileInfo->area.size) %s",filename);
				return doc.LoadFromFile(filename);
			}
		//	::MessageBox(NULL,buffer,"",MB_OK);
			buffer[pFileInfo->area.size]='\0';
			bool bSuc = true;
			doc.Parse(buffer);//doc.LoadFromBuffer(buffer,pFileInfo->area.size);

	//		delete[] buffer;

			return bSuc;

		}

	}
	
/*
	bool    LoadXML(TiXmlDocument& doc,const char * filename)
	{
        if(!g_bReadPacket)
		{
			if(!doc.LoadFile(filename))
			{
				fileinfo* pFileInfo = GetFileInfo(filename);
				if(!pFileInfo)
				{
					//Log_Debug("g_breadpacket 假 找到不文件%s",filename);
					return false;
				}
				char* buffer = new char[pFileInfo->area.size+1];
				if(!readfiletobuf(pFileInfo,buffer,pFileInfo->area.size))
				{
					//Log_Debug("g_breadpacket 假 if(!readfiletobuf(pFileInfo,buffer,pFileInfo->area.size)) %s",filename);
					return doc.LoadFile(filename);
				}
				buffer[pFileInfo->area.size]='0';
				bool bSuc = doc.Parse(buffer);//doc.LoadFromBuffer(buffer,pFileInfo->area.size);

				delete[] buffer;

				return bSuc;

			}
			return true;	

		}else
		{
			fileinfo* pFileInfo = GetFileInfo(filename);
			if(!pFileInfo)
			{

				//Log_Debug("g_breadpacket 真 fileinfo* pFileInfo = GetFileInfo(filename)找到不文件%s",filename);
				return doc.LoadFile(filename);
			}
			char* buffer = new char[pFileInfo->area.size+1];
			if(!readfiletobuf(pFileInfo,buffer,pFileInfo->area.size))
			{
				//Log_Debug("g_breadpacket 真 readfiletobuf(pFileInfo,buffer,pFileInfo->area.size) %s",filename);
				return doc.LoadFile(filename);
			}
			buffer[pFileInfo->area.size]='0';
			bool bSuc = doc.Parse(buffer);//doc.LoadFromBuffer(buffer,pFileInfo->area.size);

			delete[] buffer;

			return bSuc;

		}

	}*/
	//读文件中转
	size_t    LoadFile(const char* filename,char*& pData,int nSize)
	{
          
		if(!g_bReadPacket)
		{
		    FILE *fp;
			fp = fopen( filename,"rb" );
			if( !fp )
			{
				int nerr = GetLastError();
				//Log_Debug("fopen%s errorcode%d",filename,nerr);

				fileinfo* pFileInfo = GetFileInfo(filename);
				if(!pFileInfo)
				{
					//Log_Debug(" g_bReadPacket 假 找到不文件%s",filename);
					return 0;
				}
				pData = new char[pFileInfo->area.size+1];
				if(!pData)
					return 0;
				pData[pFileInfo->area.size] = 0;
				if(!readfiletobuf(pFileInfo,pData,pFileInfo->area.size))
				{
					//Log_Debug(" g_bReadPacket 假 readfiletobuf(pFileInfo,pData,pFileInfo->area.size)%s",filename);
					delete[] pData;
					pData = NULL;
					return 0;
				}
				return pFileInfo->area.size;
			}
			size_t nfSize;
			fseek( fp,0,SEEK_END );
			nfSize = ftell(fp);
			fseek( fp,0,SEEK_SET );
			pData = new char[nfSize+1];
			if(!pData)
			{
				fclose(fp);
				return 0;
			}
			pData[nfSize] = 0;

			if( 1 !=fread( pData,nfSize,1,fp ) )
			{
				int nerr = GetLastError();
				//Log_Debug("fread%s errorcode%d",filename,nerr);
				fclose(fp);
				return 0;
			}	
			fclose(fp);
			return nfSize; 
		}
		else
		{
			fileinfo* pFileInfo = GetFileInfo(filename);

			if(!pFileInfo)//如果不存在就直接读文件
			{
				//Log_Debug(" g_bReadPacket 真 找到不文件 %s",filename);
file_read:
				FILE *fp;
				fp = fopen( filename,"rb" );
				if( !fp )
					return 0;

				size_t nSize;
				fseek( fp,0,SEEK_END );
				nSize = ftell(fp);
				fseek( fp,0,SEEK_SET );
				pData = new char[nSize+1];
				if(!pData)
				{
					fclose(fp);
					return 0;
				}
				pData[nSize] = 0;

				if( 1 !=fread( pData,nSize,1,fp ) )
				{
					fclose(fp);
					return 0;
				}	
				fclose(fp);
				return nSize; 
			}
			pData = new char[pFileInfo->area.size+1];
			if(!pData)
				return 0;
			pData[pFileInfo->area.size] = 0;
			if(!readfiletobuf(pFileInfo,pData,pFileInfo->area.size))
			{
				//Log_Debug(" g_bReadPacket 真 readfiletobuf(pFileInfo,pData,pFileInfo->area.size) %s",filename);
				delete[] pData;
				pData = NULL;
				goto file_read;
			}
			return pFileInfo->area.size;

		}


	}
	bool    IsOpen(const char* filename)
	{
		fileinfo* pFileInfo = GetFileInfo(filename);

		if(!pFileInfo)//如果不存在就直接读文件
		{
		/*	FILE *fp;
			fp = fopen( filename,"rb" );
			if( !fp )
				return false;*/
			if( _access_s( filename, 0 ) != 0 )
				return false;

		}
		return true;
	}
	void    SetReadPacket(bool bRead)
	{
		g_bReadPacket = bRead;
	}
}
