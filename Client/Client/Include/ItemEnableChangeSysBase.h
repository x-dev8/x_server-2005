/*************************************************************************************
        ��������Ʒ Enable Disable �任����    by zhuomeng.hu		[12/30/2010]
          ���л�ı䱳������Ʒ Enable ̬��ϵͳ����̳д���
*************************************************************************************/

#pragma once

class CItemEnableChangeSysBase
{
public:
    CItemEnableChangeSysBase();
    ~CItemEnableChangeSysBase();

    virtual bool IsPackItemBeUsing( __int64 nGuid ) = 0;

};
