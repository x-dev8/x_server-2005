#include "NewWithDebug.h"

map<const char*, ALLOCMEMORYINFO>& GetAllocInfo()
{
	static map<const char*, ALLOCMEMORYINFO>* s_pAllocInfo = new map<const char*, ALLOCMEMORYINFO>;
	return *s_pAllocInfo;

    //static map<const char*, ALLOCMEMORYINFO> instance;
    //return instance;
}

map<void*, POINTERINFO>& GetPointerInfo()
{
	static map<void*, POINTERINFO>* s_pPointerInfo = new map<void*, POINTERINFO>;
	return *s_pPointerInfo;

 //   static map<void*, POINTERINFO> s_pPointerInfo;
	//return s_pPointerInfo;
}

//CSemiAutoIntLock& GetAutoIntLock()
//{
//	static CSemiAutoIntLock* s_pnewcs = new CSemiAutoIntLock;
//	return *s_pnewcs;
//    //static CSemiAutoIntLock s_pnewcs;
//	//return s_pnewcs;
//}


//����ʹ���ڴ���Ϣ������ļ�
void OutHeapMemoryInfoToFile(const char* szFileName)
{
	char szDate[256] = {0};
	char szTime[256] = {0};
	char szFile[256] = {0};
	//char szLog[1024] = {0};

	SYSTEMTIME systime;
	GetLocalTime( &systime );

	_snprintf(szDate, sizeof(szDate)-1, "%04d-%02d-%02d", systime.wYear, systime.wMonth, systime.wDay);
	_snprintf(szTime, sizeof(szTime)-1, "%02d:%02d:%02d", systime.wHour, systime.wMinute, systime.wSecond);
//	_snprintf(szFile, sizeof(szTime)-1, "%02d.log", systime.wHour);

    char szPath[256] = {0};
    _snprintf(szPath, sizeof(szPath)-1, "Log\\%s", szDate);
    _mkdir("Log");
    _mkdir(szPath);

    _snprintf(szFile, sizeof(szFile)-1, "%s\\%s", szPath, szFileName);

    std::ofstream fLog(szFile, std::ios::app);
    if (!fLog.is_open())
    {
        return;
    }

    fLog << szDate << " " << szTime << std::endl;
    fLog << "---------------heapmemoryinfostart---------------" << std::endl;

    unsigned int nAllMemory = 0;
    for (map<const char*, ALLOCMEMORYINFO>::iterator itr = GetAllocInfo().begin();
        itr != GetAllocInfo().end(); itr++)
    {
        nAllMemory += itr->second.nAllUseMemory;
        fLog << (itr->first!=NULL?itr->first:"δ������;") << " ռ���ڴ�[" << itr->second.nAllUseMemory << "]�ֽ�" << "  Ŀǰδ�ͷŹ�����[" << itr->second.nExistCount << "]��  ��ʷ������[" << itr->second.nAllocCount << "]��" << std::endl;
    }

    fLog << "ȫ�������ڴ� " << nAllMemory << " Byte ���� " << nAllMemory/(1024*1024) << " MByte" << std::endl;
    fLog << "---------------heapmemoryinfoend---------------" << std::endl;

	fLog.close();
};