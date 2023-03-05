// packettool.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "datafile.h"
#include <string>
/*#include <Windows.h>*/

using namespace std;
// struct _tp_integer
// {
// 	int isinit;
// 	LARGE_INTEGER liCounter;
// };
// static struct _tp_integer s_larget_int = {0};
// static __inline long long __GetSecondCount__()
// {
// 	if (0 == s_larget_int.isinit)
// 	{
// 		QueryPerformanceFrequency(&s_larget_int.liCounter);
// 		s_larget_int.isinit = 1;
// 	}
// 	return s_larget_int.liCounter.QuadPart;
// }
// unsigned long _highGetTime_()
// {
// 	LARGE_INTEGER liCurrent;
// 	QueryPerformanceCounter(&liCurrent);
// 	return (DWORD)(liCurrent.QuadPart * 1000 / __GetSecondCount__());
// }
int _tmain(int argc, _TCHAR* argv[])
{
  //	packet pkt;
// 	pkt.OpenPakcet("Res\\config.data");
//     
// 
// 	pkt.FileInfoSaveToFile("data1\\info.info");
// 	pkt.Close();
// 
// // 	pkt1.OpenPakcet("Res\\config.data.tmp");
// // 	pkt1.FileInfoSaveToFile("data2\\info.info");
// // 	pkt1.Close();
// 
//      pkt.OpenPakcet("Res\\try.data");
// 	 pkt.AddFile("10.txt","10.txt");
// 	// pkt.UpdateFile("ss.txt","c:\\ss");
// 	 pkt.SaveFileList();
// 	 pkt.Close();
	if(argc <3)
		return 0;	

	char bufferXML[256];
	char bufferData[256];

	strcpy(bufferXML,argv[1]);
	strcpy(bufferData,argv[2]);


	printf("进行中\n");
	printf("通过%s生成资源包%s\n",bufferXML,bufferData);


	packet  t;

	TiXmlDocument doc;
	if(!doc.LoadFile((const char *)bufferXML))
      return 0;
	TiXmlElement *pconfiginfo = doc.FirstChildElement("mapping");

	TiXmlElement *pconfiginfo1 = pconfiginfo->FirstChildElement("fileMd5");
	

	if(!t.OpenPakcet((const char *)bufferData))
		t.CreatePacket(enum_packet_type_not_release, (const char *)bufferData);
	while (pconfiginfo1)
	{
		std::string strname = pconfiginfo1->Attribute("fileName");
		int  nfilename,nfilesize;
		pconfiginfo1->QueryIntAttribute("md5",&nfilename);
		pconfiginfo1->QueryIntAttribute("file",&nfilesize);
  		t.AddFile(strname.c_str());
		pconfiginfo1=pconfiginfo1->NextSiblingElement("fileMd5");
	}

	doc.SaveFile();


	t.SaveFileList();
	t.Close();
	printf("完成按任意一键结束\n");
	getchar();
	return 0;
}

