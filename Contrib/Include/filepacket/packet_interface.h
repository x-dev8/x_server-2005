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
	///��һ����Դ�����ļ�
	packet*  getpacket(const char *name);
	//��һ����Դ�����ļ�
	bool	openpacket (const char *name);
	//ͨ���ļ����ֻ�õ��ļ����ݻ��嵽������
	bool	readfiletobuf(const char *name, char *buf, size_t buflen);
	//��û��ʵ��
	char*	readfile (const char *name, size_t *buflen);
	//ͨ���ļ����õ�һ���ļ��ڵ���Ϣ
	fileinfo*  GetFileInfo(const char *name);
	//ͨ��fileinfoһ���ļ��ڵ���Ϣ��õ��ļ���С
	size_t	GetFileSize (struct fileinfo *info);
	//ͨ��fileinfoһ���ļ��ڵ���Ϣ��õ��ļ����ݻ��嵽������
	bool	readfiletobuf(fileinfo* pInfo,char *buf, size_t buflen);
	//�ͷ����а��Ľڵ���Ϣ
	void	release ();
    ///��xml��ת
//	bool    LoadXML(TiXmlDocument& doc,const char * filename);
	
	bool    LoadXML(MeXmlDocument& doc,const char * filename);
	
	//���ļ���תpData���ڲ�new �ⲿʹ�����Ժ�delete
	size_t   LoadFile(const char* filename,char*& pData,int nSize);
	//ȫ�����е���Դ��
	void    SavePacket();
	//��ͼ�ع���������һ���ع��ɹ�
	void    AfreshAllPacket();
	//�ļ��Ƿ����
	bool    IsOpen(const char* filename);
	//�����õ�
	void    GetAllFileName();

	void    SetReadPacket(bool bRead);

 	extern  bool g_bReadPacket;

	extern std::string s_PacketRootPath;


	packet*  findpacket(const char *name);
	
	//��fread
	int w_fread(void * buf,int len, int count,f_Handle *f);
	//��fopen
	f_Handle* w_fopen(const char * name,char * type);
	//��fclose
	void w_fclose(f_Handle * f);
	//��fopen_s
	int w_fopen_s(f_Handle** f,const char * name,char * type);
	//��fseek
	int w_fseek(f_Handle * _File, long _Offset, __in int _Origin);

	//��getc
	int w_getc(f_Handle *f);

	int w_fgets(char * buf,int count,f_Handle *f);
	void w_rewind(f_Handle *f);

	int w_ftell(f_Handle *f);

}
#endif

