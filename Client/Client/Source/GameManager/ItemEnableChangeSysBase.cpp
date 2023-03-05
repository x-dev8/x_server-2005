/*************************************************************************************
        背包内物品 Enable Disable 变换基类    by zhuomeng.hu		[12/30/2010]
          所有会改变背包内物品 Enable 态的系统均须继承此类
*************************************************************************************/

#include "ItemEnableChangeSysBase.h"
#include "PackItemEnableManager.h"

CItemEnableChangeSysBase::CItemEnableChangeSysBase()
{
    CPackItemEnableManager::Instance()->AddItemEnableChangeSys( this );
}

CItemEnableChangeSysBase::~CItemEnableChangeSysBase()
{
    CPackItemEnableManager::Instance()->RemoveItemEnableChangeSys( this );
}
