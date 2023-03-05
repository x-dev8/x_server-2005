// testUnzipLib.cpp : Defines the entry point for the console application.
//
#include "GameDataDecrypt.h"
#include <string>
#include <Windows.h>
#include <iostream>
#include <stdio.h>

#define APPNAME "Test"

void ShowCharBaseInfo(SCharBaseInfo &BaseInfo,SCharOtherData &OtherData);

int _tmain(int argc, _TCHAR* argv[])
{
    char runPath[MAX_PATH];
    ZeroMemory(runPath,sizeof(runPath));
    DWORD errorNo = GetModuleFileName(NULL,runPath,MAX_PATH);

    std::string path = runPath;
    path = path.substr(0,path.find_last_of(_T("\\"))+1);
    
    std::string strBaseInfo;
    std::string strOtherData;
    std::string strExtenData;
    std::string strVisualInfo;
    std::string strItemData;
    std::string strMountData;

    char tempString  [ CharChunkWR::CD_UnZipTempBufferSize_Char   ] = {0};
    ZeroMemory(tempString,sizeof(tempString));
    DWORD size = 4000;
    path += "config.ini";

    // ��ȡ�ִ�
    DWORD GetStringError = 0;

    //���ַ�����Ӧ���ݿ� t_game_character �� DataInfo �ֶ�
    GetStringError = GetPrivateProfileString(APPNAME,"BaseInfo","",tempString,size,path.c_str());
    if (GetStringError != 0)
    {
        strBaseInfo = tempString;
        ZeroMemory(tempString,sizeof(tempString));
    }

    //���ַ�����Ӧ���ݿ� t_game_character �� OtherData �ֶ�
    GetStringError = GetPrivateProfileString(APPNAME,"OtherData","",tempString,size,path.c_str());
    if (GetStringError != 0)
    {
        strOtherData = tempString;
        ZeroMemory(tempString,sizeof(tempString));
    }

    //���ַ�����Ӧ���ݿ� t_game_character �� ExtenData �ֶ�
    GetStringError = GetPrivateProfileString(APPNAME,"ExtenData","",tempString,size,path.c_str());
    if (GetStringError != 0)
    {
        strExtenData = tempString;
        ZeroMemory(tempString,sizeof(tempString));
    }

    //���ַ�����Ӧ���ݿ� t_game_visualinfo �� DataInfo �ֶ�
    GetStringError = GetPrivateProfileString(APPNAME,"VisualInfo","",tempString,size,path.c_str());
    if (GetStringError != 0)
    {
        strVisualInfo = tempString;
        ZeroMemory(tempString,sizeof(tempString));
    }

    //���ַ�����Ӧ���ݿ� t_game_item �� ItemData �ֶ�
    GetStringError = GetPrivateProfileString(APPNAME,"ItemData","",tempString,size,path.c_str());
    if (GetStringError != 0)
    {
        strItemData = tempString;
        ZeroMemory(tempString,sizeof(tempString));
    }

    //���ַ�����Ӧ���ݿ� t_game_mount �� DataInfo �ֶ�
    GetStringError = GetPrivateProfileString(APPNAME,"MountData","",tempString,size,path.c_str());
    if (GetStringError != 0)
    {
        strMountData = tempString;
        ZeroMemory(tempString,sizeof(tempString));
    }

    //����
    SCharBaseInfo testBaseInfo;
    long result = GameDataDecrypt::GetInstance().ParseCharBaseInfo(strBaseInfo.c_str(),sizeof(tempString),&testBaseInfo);
    if ( GameDataDecrypt::Error_Succeed != result)
    {
        printf("ParseCharBaseData ErrorCode = %d",result);
    }


    SCharOtherData testOtherData;
    result = GameDataDecrypt::GetInstance().ParseCharOtherData(strOtherData.c_str(),sizeof(tempString),&testOtherData);
    if ( GameDataDecrypt::Error_Succeed != result)
    {
        printf("ParseCharOtherData ErrorCode = %d",result);
    }


    SExtendData testExtendData;
    result = GameDataDecrypt::GetInstance().ParseCharExtenData(strExtenData.c_str(),sizeof(tempString),&testExtendData);
    if ( GameDataDecrypt::Error_Succeed != result)
    {
        printf("ParesrError ErrorCode = %d",result);
    }


    SCharVisual testCharVisual;
    result = GameDataDecrypt::GetInstance().ParseCharVirsualData(strVisualInfo.c_str(),sizeof(tempString),&testCharVisual);
    if ( GameDataDecrypt::Error_Succeed != result)
    {
        printf("ParseCharVirsualData ErrorCode = %d",result);
    }

    SCharItem testCharItem;
    result = GameDataDecrypt::GetInstance().ParseCharItemData(strItemData.c_str(),sizeof(tempString),&testCharItem);
    if ( GameDataDecrypt::Error_Succeed != result)
    {
        printf("ParseCharItemData ErrorCode = %d",result);
    }

    SMountItem testMountItem;
    result = GameDataDecrypt::GetInstance().ParseCharMountData(strMountData.c_str(),sizeof(tempString),&testMountItem);
    if ( GameDataDecrypt::Error_Succeed != result)
    {
        printf("ParseCharItemData ErrorCode = %d",result);
    }


    ShowCharBaseInfo(testBaseInfo,testOtherData);

    system("pause");
	return 0;
}

void ShowCharBaseInfo(SCharBaseInfo &BaseInfo , SCharOtherData &OtherData)
{
    printf("��ɫ���� : %s \n", BaseInfo.aptotic.szCharacterName);
     
    printf("�Ա� : %s \n", (BaseInfo.aptotic.ucSex == 0) ? "��":"Ů");
 
    printf("ְҵ : %d \n", BaseInfo.aptotic.usProfession);
 
    printf("ͷ�� : %d \n", BaseInfo.aptotic.ucHeadPic);
 
    printf("���� : %d \n", BaseInfo.aptotic.ucCountry);
        
    printf("�ȼ� : %d \n", BaseInfo.liveinfo.ustLevel);
    
    printf("��Ϸ��Ǯ : %ld \n", BaseInfo.liveinfo.dwMoney);
    
    printf("��ǰ����ֵ : %ld \n", BaseInfo.liveinfo.reputation);
    
    printf("��ǰ��ѫֵ : %ld \n", BaseInfo.liveinfo.exploit);
    
    printf("�� : %ld \n", BaseInfo.liveinfo.jinDing);
    
    printf("��Ʊ : %ld \n", BaseInfo.liveinfo.jinPiao);
        
    printf("Ѫ�� : %d \n", BaseInfo.liveinfo.nHp);
    
    printf("ħ�� : %d \n", BaseInfo.liveinfo.nMp);
    
    printf("��ǰ���� : %lld \n", BaseInfo.liveinfo.dwExp);
    
    printf("δʹ�õľ��� : %ld \n", BaseInfo.liveinfo.dwExpNotUsed);
        
    printf("ʵ����ͨ�����Ŀ��Ÿ��� : %d \n", BaseInfo.liveinfo.ucNormalBagSize);
    
    printf("ʵ�ʲ��ϱ����Ŀ��Ÿ��� : %d \n", BaseInfo.liveinfo.ucMaterialBagSize);
    
    printf("������� : %d \n", BaseInfo.liveinfo.ucMountCount);
    
    printf("���� (��������) : %d \n", BaseInfo.liveinfo.activity);
    
    printf("�������ֵ : %d \n", BaseInfo.liveinfo.activityMax);
    
    printf("��ҩ������ : %d \n", BaseInfo.liveinfo.nSkillPoint[ERT_CaiYao]);
 
    printf("���纰����ȴʣ��ʱ��  : %ld \n", OtherData.dwHighShoutCDTime);
 
    printf("ɱ�ֵ����ʱ�� : %d \n", OtherData.dwRecordKillMonsterTime);
 
    printf("���2������ : %s \n", OtherData.xSecondPassword.GetPassword());
 
    printf("������ɵ�ʱ�� : %d \n", OtherData.dwLeaveGuildTime);
    
}