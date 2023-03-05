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

    // 获取字串
    DWORD GetStringError = 0;

    //此字符串对应数据库 t_game_character 表 DataInfo 字段
    GetStringError = GetPrivateProfileString(APPNAME,"BaseInfo","",tempString,size,path.c_str());
    if (GetStringError != 0)
    {
        strBaseInfo = tempString;
        ZeroMemory(tempString,sizeof(tempString));
    }

    //此字符串对应数据库 t_game_character 表 OtherData 字段
    GetStringError = GetPrivateProfileString(APPNAME,"OtherData","",tempString,size,path.c_str());
    if (GetStringError != 0)
    {
        strOtherData = tempString;
        ZeroMemory(tempString,sizeof(tempString));
    }

    //此字符串对应数据库 t_game_character 表 ExtenData 字段
    GetStringError = GetPrivateProfileString(APPNAME,"ExtenData","",tempString,size,path.c_str());
    if (GetStringError != 0)
    {
        strExtenData = tempString;
        ZeroMemory(tempString,sizeof(tempString));
    }

    //此字符串对应数据库 t_game_visualinfo 表 DataInfo 字段
    GetStringError = GetPrivateProfileString(APPNAME,"VisualInfo","",tempString,size,path.c_str());
    if (GetStringError != 0)
    {
        strVisualInfo = tempString;
        ZeroMemory(tempString,sizeof(tempString));
    }

    //此字符串对应数据库 t_game_item 表 ItemData 字段
    GetStringError = GetPrivateProfileString(APPNAME,"ItemData","",tempString,size,path.c_str());
    if (GetStringError != 0)
    {
        strItemData = tempString;
        ZeroMemory(tempString,sizeof(tempString));
    }

    //此字符串对应数据库 t_game_mount 表 DataInfo 字段
    GetStringError = GetPrivateProfileString(APPNAME,"MountData","",tempString,size,path.c_str());
    if (GetStringError != 0)
    {
        strMountData = tempString;
        ZeroMemory(tempString,sizeof(tempString));
    }

    //解析
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
    printf("角色名称 : %s \n", BaseInfo.aptotic.szCharacterName);
     
    printf("性别 : %s \n", (BaseInfo.aptotic.ucSex == 0) ? "男":"女");
 
    printf("职业 : %d \n", BaseInfo.aptotic.usProfession);
 
    printf("头像 : %d \n", BaseInfo.aptotic.ucHeadPic);
 
    printf("国家 : %d \n", BaseInfo.aptotic.ucCountry);
        
    printf("等级 : %d \n", BaseInfo.liveinfo.ustLevel);
    
    printf("游戏金钱 : %ld \n", BaseInfo.liveinfo.dwMoney);
    
    printf("当前声望值 : %ld \n", BaseInfo.liveinfo.reputation);
    
    printf("当前功勋值 : %ld \n", BaseInfo.liveinfo.exploit);
    
    printf("金锭 : %ld \n", BaseInfo.liveinfo.jinDing);
    
    printf("金票 : %ld \n", BaseInfo.liveinfo.jinPiao);
        
    printf("血量 : %d \n", BaseInfo.liveinfo.nHp);
    
    printf("魔量 : %d \n", BaseInfo.liveinfo.nMp);
    
    printf("当前经验 : %lld \n", BaseInfo.liveinfo.dwExp);
    
    printf("未使用的经验 : %ld \n", BaseInfo.liveinfo.dwExpNotUsed);
        
    printf("实际普通背包的开放个数 : %d \n", BaseInfo.liveinfo.ucNormalBagSize);
    
    printf("实际材料背包的开放个数 : %d \n", BaseInfo.liveinfo.ucMaterialBagSize);
    
    printf("坐骑个数 : %d \n", BaseInfo.liveinfo.ucMountCount);
    
    printf("活力 (生产消耗) : %d \n", BaseInfo.liveinfo.activity);
    
    printf("活力最大值 : %d \n", BaseInfo.liveinfo.activityMax);
    
    printf("采药熟练度 : %d \n", BaseInfo.liveinfo.nSkillPoint[ERT_CaiYao]);
 
    printf("世界喊话冷却剩余时间  : %ld \n", OtherData.dwHighShoutCDTime);
 
    printf("杀怪的最后时间 : %d \n", OtherData.dwRecordKillMonsterTime);
 
    printf("玩家2级密码 : %s \n", OtherData.xSecondPassword.GetPassword());
 
    printf("加入帮派的时间 : %d \n", OtherData.dwLeaveGuildTime);
    
}