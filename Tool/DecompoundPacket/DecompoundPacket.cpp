// DecompoundPacket.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <fstream>
#include "filepacket/packet_interface.h"
#include "filepacket/datafile.h"
#include "string_hashmap.h"
#include <direct.h>
#include <Windows.h>
#include <io.h>

using namespace std;

#define PACKET_DATA "data\\audio.data"

char tempForld[256];

bool CheckForld(const char* forldname)
{
	if (!forldname)
	{
		return false;
	}
	sprintf_s(tempForld,256,"%s\\%s",tempForld,forldname);

	int res = access(tempForld,0);
	if (res == 0)
	{
		return true;
	}
	_mkdir(tempForld);
	return true;
}
//char* _filename = new char[512];
bool ParseFileName(const char* filename)
{
	if (!filename)
	{
		return false;
	}
	memset(tempForld,0,256*sizeof(char));
	//memset(_filename,0,512*sizeof(char));
	//sprintf_s(_filename,512,"%s",filename);
	/*strncpy_s(_filename,strlen(_filename),filename,strlen(_filename) - 1);*/
	char* _filename = (char*)filename;
	char* comma = NULL;
	while(true)
	{
		comma = strchr(_filename,'\\');
		if (!comma)
		{
			break;
		}
		*comma = '\0';
		CheckForld(_filename);
		_filename = comma+1;
	}
	//memset(_filename,0,512*sizeof(char));
	return true;
}
FILE *m_fp = NULL;
char* gbuffer = new char[128*1024*1024];//128M
bool Descompound(const char* packetname)
{
	packet_namespace::SetReadPacket(true);
	packet_namespace::openpacket(packetname);

	packet* pPacket = packet_namespace::findpacket(packetname);
	if (pPacket)
	{
		if (0)
		{//单文件测试模块
			packet::AreaHash::iterator itr = pPacket->GetPacketFileList().find("data\\audio\\monster\\zhu\\zhu_attack0.wav");
			if (itr != pPacket->GetPacketFileList().end())
			{
				fileinfo* pFileInfo = itr->second;
				if (pFileInfo)
				{
					if (ParseFileName(pFileInfo->GetFileName()))
					{
						memset(gbuffer,0,128*1024*1024);
						if(!packet_namespace::readfiletobuf(pFileInfo,gbuffer,pFileInfo->area.size))
						{
							return false;
						}

						//ofstream _out(pFileInfo->GetFileName(),ios::binary);
						//_out.write(buffer,pFileInfo->area.size);
						//_out.close();						
						m_fp = fopen(pFileInfo->GetFileName(), "wb+");
						if (!m_fp)
						{
							printf("file open error:%s\n",pFileInfo->GetFileName());
							fclose(m_fp);
							return false;
						}
						fwrite(gbuffer, pFileInfo->area.size, sizeof(char), m_fp);
						fclose(m_fp);						
						/*delete [] gbuffer;
						gbuffer = NULL;*/
					}
				}
			}
		}
		else
		{
			char tempFile[512] = "0";
			packet::AreaHash::iterator itr = pPacket->GetPacketFileList().begin();
			while(itr != pPacket->GetPacketFileList().end())
			{
				fileinfo* pFileInfo = itr->second;
				if (pFileInfo)
				{
					strncpy_s(tempFile,512,pFileInfo->GetFileName(),511);
					if (ParseFileName(tempFile))
					{
						memset(gbuffer,0,128*1024*1024);
						if(!packet_namespace::readfiletobuf(pFileInfo,gbuffer,pFileInfo->area.size))
						{
							printf("file error:%s\n",pFileInfo->GetFileName());
							system("pause");
							return false;
						}

						//ofstream _out(pFileInfo->GetFileName(),ios::binary|ios::trunc);
						//_out.write(buffer,pFileInfo->area.size);
						//_out.close();
						
						m_fp = fopen(pFileInfo->GetFileName(), "wb+");
						if (!m_fp)
						{
							printf("file open error:%s\n",pFileInfo->GetFileName());
							fclose(m_fp);
							return false;
						}
						fwrite(gbuffer, pFileInfo->area.size, sizeof(char), m_fp);
						fclose(m_fp);
						printf("file done:%s\n",pFileInfo->GetFileName());
					}					
				}
				Sleep(1);
				itr++;
			}
		}		
	}
	packet_namespace::release();
	return true;
}

void Testing()
{
	
	for (int n = 0; n < 1000;n++)
	{
		char tempF[64];
		char tempF1[64];
		sprintf_s(tempF,64,"test\\%d.txt",n);
		sprintf_s(tempF1,64,"test\\%d.txt",n);
		ParseFileName(tempF1);
		FILE* m_p = fopen(tempF, "wb+");
		if (!m_p)
		{
			printf("file open error:%s\n",tempF);
			fclose(m_p);
			return;
		}
		fwrite(tempF, strlen(tempF), sizeof(char), m_p);
		fclose(m_p);
		printf("file done:%s\n",tempF);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	system("pause");

	/*Testing();
	return 0;*/


	if(argc >=2)
	{
		char bufferData[256];
		strcpy(bufferData,argv[1]);
		Descompound(bufferData);
	}
	else
	{
		Descompound(PACKET_DATA);
	}
	system("pause");
	return 0;
}