/*************************************************************************************
        ��������Ʒ Enable Disable �任����    by zhuomeng.hu		[12/30/2010]
          ���л�ı䱳������Ʒ Enable ̬��ϵͳ����̳д���
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
