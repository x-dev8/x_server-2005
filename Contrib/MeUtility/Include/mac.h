// SNMP.cpp : Defines the entry point for the console application.
//
/**
 * 
 *          Compiles with Visual C++-8.0 SP1 on Windows-XP-SP3.
 */
#pragma once
#pragma comment( lib, "Snmpapi.lib")

#include <tchar.h>
#include <snmp.h>
#include <conio.h>
#include <stdio.h>
#include <string>

typedef bool(WINAPI * pSnmpExtensionInit) (
    IN DWORD dwTimeZeroReference,
    OUT HANDLE * hPollForTrapEvent,
    OUT AsnObjectIdentifier * supportedView);
typedef bool(WINAPI * pSnmpExtensionTrap) (
    OUT AsnObjectIdentifier * enterprise,
    OUT AsnInteger * genericTrap,
    OUT AsnInteger * specificTrap,
    OUT AsnTimeticks * timeStamp,
    OUT RFC1157VarBindList * variableBindings);
typedef bool(WINAPI * pSnmpExtensionQuery) (
    IN BYTE requestType,
    IN OUT RFC1157VarBindList * variableBindings,
    OUT AsnInteger * errorStatus,
    OUT AsnInteger * errorIndex);
typedef bool(WINAPI * pSnmpExtensionInitEx) (
    OUT AsnObjectIdentifier * supportedView);

/*��ȡ����mac��  **:**:**:**:**:***/
inline BOOL GetMac(/*out*/std::string &mac)
{
    HINSTANCE m_hInst;
    pSnmpExtensionInit m_Init;
    pSnmpExtensionInitEx m_InitEx;
    pSnmpExtensionQuery m_Query;
    pSnmpExtensionTrap m_Trap;
    HANDLE PollForTrapEvent;
    AsnObjectIdentifier SupportedView;
    UINT OID_ifEntryType[] = {1, 3, 6, 1, 2, 1, 2, 2, 1, 3};
    UINT OID_ifEntryNum[] = {1, 3, 6, 1, 2, 1, 2, 1};
    UINT OID_ipMACEntAddr[] = {1, 3, 6, 1, 2, 1, 2, 2, 1, 6};
    AsnObjectIdentifier MIB_ifMACEntAddr ={sizeof(OID_ipMACEntAddr)/sizeof(UINT), OID_ipMACEntAddr};
    AsnObjectIdentifier MIB_ifEntryType ={sizeof(OID_ifEntryType)/sizeof(UINT), OID_ifEntryType};
    AsnObjectIdentifier MIB_ifEntryNum ={sizeof(OID_ifEntryNum)/sizeof(UINT), OID_ifEntryNum};
    RFC1157VarBindList varBindList;
    RFC1157VarBind varBind[2];
    AsnInteger errorStatus;
    AsnInteger errorIndex;
    AsnObjectIdentifier MIB_NULL = {0, 0};
    int ret;
    int dtmp;
    int  j = 0;
    //bool found = false;
    char TempEthernet[30];
    m_Init = NULL;
    m_InitEx = NULL;
    m_Query = NULL;
    m_Trap = NULL;
    /* ����SNMP DLL��ȡ��ʵ����� */

    m_hInst = LoadLibrary(_T("inetmib1.dll"));
    if (m_hInst < (HINSTANCE) HINSTANCE_ERROR)
    {
        m_hInst = NULL;
        return FALSE;
    }
    m_Init =(pSnmpExtensionInit) GetProcAddress(m_hInst, "SnmpExtensionInit");
    m_InitEx =(pSnmpExtensionInitEx) GetProcAddress(m_hInst,"SnmpExtensionInitEx");
    m_Query =(pSnmpExtensionQuery) GetProcAddress(m_hInst,"SnmpExtensionQuery");
    m_Trap =(pSnmpExtensionTrap) GetProcAddress(m_hInst, "SnmpExtensionTrap");
    m_Init(GetTickCount(), &PollForTrapEvent, &SupportedView);
    ///* ��ʼ����������m_Query��ѯ����ı����б� */
    varBindList.list = varBind;
    varBind[0].name = MIB_NULL;
    varBind[1].name = MIB_NULL;
    ///* ��OID�п��������ҽӿڱ��е�������� */
    varBindList.len = 1;/* Only retrieving one item */
    SNMP_oidcpy(&varBind[0].name, &MIB_ifEntryNum);
    ret =m_Query(ASN_RFC1157_GETNEXTREQUEST, &varBindList, &errorStatus,&errorIndex);

#ifdef _DEBUG
    printf("# of adapters in this system : %in", varBind[0].value.asnValue.number);
#endif
    
    varBindList.len = 2;
    //* ����OID��ifType���ӿ����� */
    SNMP_oidcpy(&varBind[0].name, &MIB_ifEntryType);
    //* ����OID��ifPhysAddress�������ַ */
    SNMP_oidcpy(&varBind[1].name, &MIB_ifMACEntAddr);
    do
    {
        /* �ύ��ѯ����������� varBindList��
        ����Ԥ�����ѭ�����õĴ�����ϵͳ�еĽӿڿ�������� */
        ret =  m_Query(ASN_RFC1157_GETNEXTREQUEST, &varBindList, &errorStatus,        &errorIndex);
        if (!ret)
            ret = 1;
        else
            /* ȷ����ȷ�ķ������� */
            ret = SNMP_oidncmp(&varBind[0].name, &MIB_ifEntryType,MIB_ifEntryType.idLength); 
        if (!ret) 
        {
            j++;
            dtmp = varBind[0].value.asnValue.number;
            //printf("Interface #%i type : %in", j, dtmp);
            /* Type 6 describes ethernet interfaces */
            if (dtmp == 6)
            {
                /* ȷ�������Ѿ��ڴ�ȡ�õ�ַ */
                ret =  SNMP_oidncmp(&varBind[1].name, &MIB_ifMACEntAddr, MIB_ifMACEntAddr.idLength);
                if ((!ret) && (varBind[1].value.asnValue.address.stream != NULL))
                {
                    if((varBind[1].value.asnValue.address.stream[0] == 0x44)
                    && (varBind[1].value.asnValue.address.stream[1] == 0x45)
                    && (varBind[1].value.asnValue.address.stream[2] == 0x53)
                    && (varBind[1].value.asnValue.address.stream[3] == 0x54)
                    && (varBind[1].value.asnValue.address.stream[4] == 0x00))
                    {
                        /* �������еĲ�������ӿڿ� */
                        //printf("Interface #%i is a DUN adaptern", j);
                        continue;
                    }
                    if ((varBind[1].value.asnValue.address.stream[0] == 0x00)
                    && (varBind[1].value.asnValue.address.stream[1] == 0x00)
                    && (varBind[1].value.asnValue.address.stream[2] == 0x00)
                    && (varBind[1].value.asnValue.address.stream[3] == 0x00)
                    && (varBind[1].value.asnValue.address.stream[4] == 0x00)
                    && (varBind[1].value.asnValue.address.stream[5] == 0x00))
                    {
                        /* ����������������ӿڿ����ص�NULL��ַ */
                        //printf("Interface #%i is a NULL addressn", j);
                        continue;
                    }

                    sprintf_s(TempEthernet, "%02x-%02x-%02x-%02x-%02x-%02x",
                    varBind[1].value.asnValue.address.stream[0],
                    varBind[1].value.asnValue.address.stream[1],
                    varBind[1].value.asnValue.address.stream[2],
                    varBind[1].value.asnValue.address.stream[3],
                    varBind[1].value.asnValue.address.stream[4],
                    varBind[1].value.asnValue.address.stream[5]);
                    mac = TempEthernet;

#ifdef _DEBUG
                    printf("MAC Address of interface #%i: %s", j, TempEthernet);
#endif      
                }
            }
        }
    } while (!ret);/* ����������ֹ�� */
    
    FreeLibrary(m_hInst);
    //* ����� */
    SNMP_FreeVarBind(&varBind[0]);
    SNMP_FreeVarBind(&varBind[1]);
    return TRUE;
}

inline BOOL GetMacByIpconfig(std::string &str_mac)
{
	char _mac [1024] = {0};
	system("ipconfig/all >config.txt");                /// ipconfig/all
	//WinExec("cmd /c ipconfig/all >config.txt", SW_HIDE);
	Sleep(100);
	///||||||||||||||||||
	/// C++ FILE
	///||||||||||||||||||
	ifstream        file;
	file.open("config.txt");
	string contents;
	int count = 0;
	while ( !file.eof() )
	{
		count++;
		getline(file,contents);
		//cout/*<<"�ļ�����->"*/<<contents.c_str()<<endl;                /// test print
		int flag_mac = 1;
		if (flag_mac)
		{
			char *pMacE = (char *)strstr(contents.c_str(),"Physical Address");
			char *pMacC = (char *)strstr(contents.c_str(),"�����ַ");
			char *pMacD = (char *)strstr(contents.c_str(),"���w��ַ");
			char *pMacF = (char *)strstr(contents.c_str(),"ʵ��λַ");
			char *pMacG = (char *)strstr(contents.c_str(),"�����} ");
			char *pMacH = (char *)strstr(contents.c_str(),"�����}");
			if (NULL != pMacC)
			{
				char *pMac = strstr(pMacC,":");
				pMac += sizeof(":");
				int mac_len = (int)strlen(pMac);
				memcpy(_mac,pMac,mac_len);
				break;
			}
			if (NULL != pMacE)
			{
				char *pMac = strstr(pMacE,":");
				pMac += sizeof(":");
				int mac_len = (int)strlen(pMac);
				memcpy(_mac,pMac,mac_len);
				break;
			}
			if (NULL != pMacD)
			{
				char *pMac = strstr(pMacD,":");
				pMac += sizeof(":");
				int mac_len = (int)strlen(pMac);
				memcpy(_mac,pMac,mac_len);
				break;
			}
			if (NULL != pMacF)
			{
				char *pMac = strstr(pMacF,":");
				pMac += sizeof(":");
				int mac_len = (int)strlen(pMac);
				memcpy(_mac,pMac,mac_len);
				break;
			}
			if (NULL != pMacG)
			{
				char *pMac = strstr(pMacG,":");
				pMac += sizeof(":");
				int mac_len = (int)strlen(pMac);
				memcpy(_mac,pMac,mac_len);
				break;
			}
			if (NULL != pMacH)
			{
				char *pMac = strstr(pMacH,":");
				pMac += sizeof(":");
				int mac_len = (int)strlen(pMac);
				memcpy(_mac,pMac,mac_len);
				break;
			}
			flag_mac = 0;
		}
	}
	file.close();
	char *str = "config.txt";

	int strnum = strlen(_mac); 
	int loop = 0;
	for (; loop < strnum; ++loop)
	{
		if (_mac[loop] == 13)
		{
			_mac[loop] = 0;
		}
	}

	str_mac.clear();
	str_mac.append(_mac,strlen(_mac));

	if (0 != remove(str))
	{
		return FALSE;
	}

	if (str_mac.empty())
	{
		return FALSE;
	}
	return TRUE;
}
