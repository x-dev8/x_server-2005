#ifndef _H_DATA_FILE_H_
#define _H_DATA_FILE_H_
#include "string_hashmap.h"
#include <stdio.h>

//////////////////////////////////////////////////
//	��ͷ����ʶ����Ϣ���Լ�һ��ƫ�ƣ�������ǰ����ļ��б�����λ�ã�
//	�ļ��б���Ϊ������Ϣ����
//////////////////////////////////////////////////
enum filepacketsome
{
	epacket_space_type_unknow = 0,			//δ֪������
	epacket_space_type_no_file,				//���ļ������类ɾ���ļ���
	epacket_space_type_has_file,			//���������ļ�
	epacket_file_name_max_length = 256,		//�ļ���Ϊ128�ֽ�
	e_all_packet_file_num = 16000,			//�����ļ���Ŀ
	

	enum_packet_type_not_release = 0,		//ֱ���˳�ʱ���ͷ�
	enum_packet_type_create_and_release = 1,//�����������ͷ�����

	enum_file_max_size = (1024*1024*1024*2)-1,	//�ļ����4G

	max_nouse_area    =  20,
};
//����׺
#define PACKET_TYPE 'FPMO'

static char  ENCRYPT_KEY='d'; 
#define ENCRYPT_PACKET_FILE(buf ,size) do\
{\
	for(int i=0;i <size;i++)\
	buf[i]^=ENCRYPT_KEY;\
	\
}while(0);
//�ļ�������Ϣ
struct file_area
{
	long filetype;						//���ļ�����
	char name[epacket_file_name_max_length];//�ļ�������·��
	unsigned size;							//�ļ�����
	long offset;							//�������ڰ��е�λ��
	long space;							//�������С������ʼ�� offset�������� offset + space
	file_area()
	{
		filetype = epacket_space_type_unknow;
		name[0] = 0;
		size = 0;
		offset = 0;
		space = 0;
	}

	//��ȡ���ô�С
	size_t GetCanUseSpace () { return space; }

	//���ã�Ϊ���뵽������
	void ResetForAddEmpty ()
	{
		filetype = epacket_space_type_no_file;
		memset(name, 0, sizeof(name));
		size = 0;
	}
};
class packet;
//�ļ���Ϣ
struct fileinfo
{
	packet *pk;				//���ڵİ�
	struct file_area area;	//����������
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


//�ļ�ͷ��Ϣ�������ļ����ͣ��Լ����Ѵ���ļ����ļ��б����洢λ��
struct file_header
{
	size_t type;							//��¼���ļ����ͣ���׺��
	size_t mag_type;						//��¼���ļ�����ʽ
	long offset;							//�˰����ļ��б��ŵ�λ��

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
	//�����ļ�
	fileinfo *FindFile (const char *name,bool b=false);

	//����һ���ļ�(���뵽��ϣ��)
	bool AddFile (packet *pk, fileinfo *info);

	//�Ƴ�һ���ļ�(�ӹ�ϣ��)
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
//��
class packet
{
public:
	typedef string_hash<fileinfo*> AreaHash;
private:
	FILE *m_fp;								//�ļ�ָ��
	file_header m_headerinfo;				//��ͷ��Ϣ
	std::string m_packetname;				//�˰��ļ���
	AreaHash m_areas;						//���еĺ����ļ�������(ͬʱ���뵽ȫ���ԵĹ�ϣ������)
	std::list<fileinfo*> m_empty_areas;		//���е����ļ�������

	//�ع�����صıȽ�ֵ
	size_t m_filesizetotal;					//�˰�����Ч�ļ��Ĵ�С
	size_t m_emptysizetotal;				//�˰��п��пռ�Ĵ�С
private:
	////////////////////////////////////////////////////
	//����һ�������ļ�������
	bool AddHasFileArea (fileinfo *area);

	//�Ƴ�һ�������ļ�������
	fileinfo *RemoveHasFileArea (const char *name);

	//ͨ���ļ�����ȡ�����ļ�������
	fileinfo *FindHasFileArea (const char *name);


	////////////////////////////////////////////////////
	//��������Ĵ�С����ȡ���õ�����
	fileinfo *GetCanUseArea (size_t needsize);

	//����һ�����õ�����
	bool AddCanUseArea (fileinfo *info);

	//���Ҵ������Ƿ��Ѿ��ڿ��õ�������
	bool FindCanUseArea (fileinfo *info);

	//д��ͷ
	bool WriteHeader ();

	//����ͷ
	bool ReadHeader ();
public:
	packet();
	~packet();
	
	//��ȡ��ǰ������
	const char *GetPakcetName () { return m_packetname.c_str(); }
	////////////////////////////////////////////////////

	string_hash<fileinfo*> & GetPacketFileList(){ return m_areas;}
	//�رհ�
	void Close ();
    
	//��ָ���İ���
	bool OpenPakcet (const char *packetname);

	//����ָ���İ�
	bool CreatePacket (short type, const char *packetname);
private:
	//����˰����ļ��б������ݴ����򷵻�false
	bool LoadFileList ();
public:
	//д���ļ��б�ָ���İ���
	void SaveFileList ();

	//������ϱ����ȱ�֤����ȫ����
	void AfreshPacket();

	////////////////////////////////////////////////////

	//��ָ�����ļ���ָ���Ļ�����
	bool ReadFileToBuf (fileinfo *info, char *buf, size_t buflen);

	//��ָ�����ļ���ָ���ļ�ƫ�ƴ�С
    size_t ReadFileToBuf (fileinfo *info, char *buf, size_t buflen,size_t nStart,size_t nSize);
    
	////////////////////////////////////////////////////
	//����һ���ļ�������
	fileinfo *AddFile (const char *path,const char* pDstPath = NULL);

	//����ָ�����ļ�
	fileinfo *UpdateFile (const char *path,const char* pDstPath = NULL);

	//ͨ��һ�������ļ���Ϣ����

	fileinfo* AddFile(fileinfo* pfileinfo,char* pSrcData,size_t nSize);

	//ɾ��ָ�����ļ�
	bool DelFile (const char *path);

	//�������ݷֱ�ɸ����ļ�
	void CreateSubFile(const char* strDir);

	//���ļ�������Ϣ�����ļ���
	void FileInfoSaveToFile(const char* strDir);

	//�пշֲ�
	void CreateNoUserInfo(fileinfo* pFatherInfo,size_t nFileSize);

private:
	
};


#endif

