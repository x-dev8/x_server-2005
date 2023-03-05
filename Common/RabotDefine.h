#ifndef __GAMEPROTECTDEFINE_H__
#define __GAMEPROTECTDEFINE_H__

#define Version        0x100032         // 版本号
#define MaxClientCount 5                // 每台机器上最多能开5个客户端

///////////////////////////////////////////////////////////////////////////////////////
// 定义的正确返回值 ,每个版本都不一样,从0x2000起开始定义
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
//系统错误信息
#define Result_AllocMemoryError      0x1      // 申请内存失败
#define Result_WriteMemotyError      0x2      // 写内存失败
#define Result_RunFuncError          0x3      // 执行代码检测函数失败
#define Result_NotPEImage            0x4      // 不是PE文件头
#define Result_NoGetProcAddress      0x5      // 找不到 GetProcAddress 函数
#define Result_NoLoadLibrary         0x6      // 找不到 LoadLibrary 函数
#define Result_NoGetCurrentProcess   0x7      // 找不到 GetCurrentProcess 函数
#define Result_NoFreeLibrary         0x8      // 找不到 FreeLibrary  函数
#define Result_NoPsapidll            0x9      // 找不到 Psapi.dll 文件
#define Result_NoEnumProcessModules  0xA      // 找不到 EnumProcessModules 函数
#define Result_NoGetModuleFileNameEx 0xB      // 找不到 GetModuleFileNameEx 函数
#define Result_EnumError             0xC      // 执行 EnumProcessModules 或者 EnumProcess 错误
#define Result_NoEnumProcess         0xD      // 找不到 EnumProcess 函数
#define Result_NoGetModuleBaseName   0xE      // 找不到 GetModuleBaseName 函数
#define Result_NoOpenProcess         0xF      // 找不到 OpenProcess 函数
#define Result_NoCloseHandle         0x10     // 找不到 CloseHandle 函数

#define Result_MaxSystemError        0xFF      // 最大的系统错误码
#define Result_GetProcessList        0xFFF     // 获得进程信息
#define Result_NotResult             0xFFFF    // 客户端没有回应

/////////////////////////////////////////////////////////////////////////////////////////
// 找到外挂以后返回的验证码 从0x1000起开始定义 这些值都是固定的

#define Result_FindDream            0x1000      // 找到Dream.dll ( 类似按键精灵 )
#define Result_FindWshh             0x1001      // 找到wshh.dll  
#define Result_FindShenDll          0x1002      // 找到5ShenDllMod.dll
#define Result_FindHook             0x1003      // 找到hook.dll
#define Result_FindWshy             0x1004      // 找到ws.dll  ( 武神幻影 )
#define Result_FindWoniu            0x1005      // 找到woniu.dll( 蜗牛 )

#define Result_ManyClient           0x1FFD      // 进程列表中Client.exe个数大于5个
#define Result_NotClient            0x1FFE      // 当前进程不是Client.exe ( 脱机外挂 )
#define Result_NotFindClient        0x1FFF      // 进程列表没有找到Client.exe ( 脱机外挂 )

//////////////////////////////////////////////////////////////////////////////////////////////

#define CheckFunc( x )      "CheckFunc_"#x

#endif