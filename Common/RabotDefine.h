#ifndef __GAMEPROTECTDEFINE_H__
#define __GAMEPROTECTDEFINE_H__

#define Version        0x100032         // �汾��
#define MaxClientCount 5                // ÿ̨����������ܿ�5���ͻ���

///////////////////////////////////////////////////////////////////////////////////////
// �������ȷ����ֵ ,ÿ���汾����һ��,��0x2000��ʼ����
#define RightCheckResult_0      0
#define RightCheckResult_1      0xBC73
#define RightCheckResult_2      0x74C6
#define RightCheckResult_3      0xAC27
#define RightCheckResult_4      0xCB28
#define RightCheckResult_5      0x2B3C 
#define RightCheckResult_6      0x27BC
#define RightCheckResult_7      0xC7B2
#define RightCheckResult_8      0x4C2B
#define RightCheckResult_9      0x4BC0
#define RightCheckResult_10     0xB3CA
#define RightCheckResult_11     0xB2C4
#define RightCheckResult_12     0xB32C
#define RightCheckResult_13     0x8B7C
#define RightCheckResult_14     0x3ACE
#define RightCheckResult_15     0x3CB2
#define RightCheckResult_16     0x7C2B
#define RightCheckResult_17     0x2CB7
#define RightCheckResult_18     0x7CB2


////////////////////////////////////////////////////////////////////////////
//ϵͳ������Ϣ
#define Result_AllocMemoryError      0x1      // �����ڴ�ʧ��
#define Result_WriteMemotyError      0x2      // д�ڴ�ʧ��
#define Result_RunFuncError          0x3      // ִ�д����⺯��ʧ��
#define Result_NotPEImage            0x4      // ����PE�ļ�ͷ
#define Result_NoGetProcAddress      0x5      // �Ҳ��� GetProcAddress ����
#define Result_NoLoadLibrary         0x6      // �Ҳ��� LoadLibrary ����
#define Result_NoGetCurrentProcess   0x7      // �Ҳ��� GetCurrentProcess ����
#define Result_NoFreeLibrary         0x8      // �Ҳ��� FreeLibrary  ����
#define Result_NoPsapidll            0x9      // �Ҳ��� Psapi.dll �ļ�
#define Result_NoEnumProcessModules  0xA      // �Ҳ��� EnumProcessModules ����
#define Result_NoGetModuleFileNameEx 0xB      // �Ҳ��� GetModuleFileNameEx ����
#define Result_EnumError             0xC      // ִ�� EnumProcessModules ���� EnumProcess ����
#define Result_NoEnumProcess         0xD      // �Ҳ��� EnumProcess ����
#define Result_NoGetModuleBaseName   0xE      // �Ҳ��� GetModuleBaseName ����
#define Result_NoOpenProcess         0xF      // �Ҳ��� OpenProcess ����
#define Result_NoCloseHandle         0x10     // �Ҳ��� CloseHandle ����

#define Result_MaxSystemError        0xFF      // ����ϵͳ������
#define Result_GetProcessList        0xFFF     // ��ý�����Ϣ
#define Result_NotResult             0xFFFF    // �ͻ���û�л�Ӧ

/////////////////////////////////////////////////////////////////////////////////////////
// �ҵ�����Ժ󷵻ص���֤�� ��0x1000��ʼ���� ��Щֵ���ǹ̶���

#define Result_FindDream            0x1000      // �ҵ�Dream.dll ( ���ư������� )
#define Result_FindWshh             0x1001      // �ҵ�wshh.dll  
#define Result_FindShenDll          0x1002      // �ҵ�5ShenDllMod.dll
#define Result_FindHook             0x1003      // �ҵ�hook.dll
#define Result_FindWshy             0x1004      // �ҵ�ws.dll  ( �����Ӱ )
#define Result_FindWoniu            0x1005      // �ҵ�woniu.dll( ��ţ )

#define Result_ManyClient           0x1FFD      // �����б���Client.exe��������5��
#define Result_NotClient            0x1FFE      // ��ǰ���̲���Client.exe ( �ѻ���� )
#define Result_NotFindClient        0x1FFF      // �����б�û���ҵ�Client.exe ( �ѻ���� )

//////////////////////////////////////////////////////////////////////////////////////////////

#define CheckFunc( x )      "CheckFunc_"#x

#endif