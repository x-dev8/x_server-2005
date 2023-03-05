#ifndef __SERVERSTATUSDEFINE_H__
#define __SERVERSTATUSDEFINE_H__

namespace RunStatusDefine
{
    enum ERunStatus
    {
        RunStatus_PrepareData,       // 准备数据
        RunStatus_Running,           // 开始服务
        RunStatus_PrepareStop,       // 准备停止
        RunStatus_GameThreadStopped, // 游戏停止
        RunStatus_DBThreadStopped,   // 数据库停止


        ////////////////////////////////////////////////////////
        CheckVersionSuccess = 0,   // 版本验证成功
        LoadContrySuccess,         // 加载国家数据成功
        LoadGuildSuccess,          // 加载帮会数据成功
        LoadRelationSuccess,       // 加载关系数据成功
        LoadConsignmentSuccess,    // 加载寄售数据成功
        LoadItemDropuccess,        // 加载物品掉落数据成功
        LoadSystemVarSuccess,      // 加载系统全局变量数据成功
		LoadFamilySuccess,		   // 加载家族数据成功
		LoadQuestEntrustSuccess,   // 加载任务委托数据成功
		LoadCampBattleSuccess,	   // 加载阵营战场数据成功	
		LoadGlobalDBSuccess,	   // 加载全局数据成功	
        //TODO
        LoadResourceSuccess,       // 所有加载完成
    };

    static char* g_szStatusArray[11] = 
    {// 对应上面的6种状态
        "版本验证",
        "国家数据",
        "帮会数据",
        "关系数据",
        "寄售数据",
        "物品掉落数据",
        "系统全局变量数据",
		"家族数据",
		"任务委托数据",
		"阵营战场数据",
		"全局数据",
    };
}



#endif // __SERVERSTATUSDEFINE_H__
