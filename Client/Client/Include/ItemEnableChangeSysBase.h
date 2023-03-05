/*************************************************************************************
        背包内物品 Enable Disable 变换基类    by zhuomeng.hu		[12/30/2010]
          所有会改变背包内物品 Enable 态的系统均须继承此类
*************************************************************************************/

#pragma once

class CItemEnableChangeSysBase
{
public:
    CItemEnableChangeSysBase();
    ~CItemEnableChangeSysBase();

    virtual bool IsPackItemBeUsing( __int64 nGuid ) = 0;

};
