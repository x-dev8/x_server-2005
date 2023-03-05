#ifndef __PASSWORDDEFINE_H__
#define __PASSWORDDEFINE_H__

namespace PasswordDefine
{
    enum EConstDefine
    {
        ClearSecondPasswordTime = 3,    // 强制删除2级密码 3 天后生效
        MinWealthProtectLength  = 6,    // 财产保护密码最小长度
        MaxWealthProtectLength  = 8,    // 财产保护密码最大长度

        // 设置保护结果
        ESetProtect_NonePassword = 1,       // 没有密码
        ESetProtect_PasswordSucc    ,       // 密码正确
        ESetProtect_PasswordError   ,       // 密码错误

        // 操作类型
        OP_InitAction        = 0,     // 无类型判断
        OP_OpenStorage          ,     // 打开仓库
        OP_OpenMountStorage     ,     // 打开坐骑仓库
        OP_DelRelation          ,	  // 删除好友
        OP_HandleAuction        ,     // 打开金锭交易界面
        OP_CheckPassword        ,     // 打开密码验证界面
        OP_SetProtect           ,     // 打开财产保护界面

        // 保护类型枚举
        EProtect_BuyStoreItem = 0,       // 无法使用元宝和金票购买商城道具
        EProtect_OpenStorage     ,       // 无法从仓库中取出物品或银两
        EProtect_OpenMountStorage,       // 无法从坐骑仓库中取出物品
        EProtect_Bargaining      ,       // 无法进行金钱交易（如购买和交易）
        EProtect_Stall           ,       // 无法进行摆摊
        EProtect_ThrowAway       ,       // 无法丢弃
        EProtect_SellItem        ,       // 无法卖入商店
        EProtect_UseItemInBag    ,       // 无法使用包裹内的道具
        EProtect_UnpackEquip     ,       // 无法卸下玩家自身装备
        EProtect_FreeMount       ,       // 无法放生坐骑
        EProtectFlagInit         ,       // 不需要判断的

        MaxLength = 32,                 // 密码最大长度
    };
}

using namespace PasswordDefine;

class Password
{
public:
    Password()
    {
        ClearPassword();
    }

    bool SetPassword( const char* szValue )
    {
        if ( szValue == NULL || strlen( szValue ) > PasswordDefine::MaxLength )
        { return false; }   

        ClearPassword();
        strncpy_s( szPassword, sizeof( szPassword ), szValue, strlen( szValue ) );

        return true;
    }

    void ClearPassword()
    {
        memset( szPassword, 0, sizeof( szPassword ) );
    }

    const char* GetPassword() const { return szPassword; }      // 获得密码
    bool HavePassword() const { return szPassword[ 0 ] != 0; }  // 判断是否有密码
    bool CheckPassword( const char* szValue ) const             // 判断密码是否有效
    {
        if ( szValue == NULL )
        { return false; }

        return strcmp( szPassword, szValue ) == 0 ;
    }
private:
    char szPassword[ PasswordDefine::MaxLength + 1 ];
};

// 2级密码
class SecondPassword : public Password
{
public:
    SecondPassword() : Password(), bHaveCheck( false ), n64RemoveTime( 0 )
    {
        nProtectFlag = 0xffffffff;
    }

    void SetHaveCheck( bool bValue ) { bHaveCheck = bValue; }
    bool GetHaveCheck() const { return bHaveCheck; }

    void SetRemoveTime( __int64 n64Value ) { n64RemoveTime = n64Value; }
    __int64 GetRemoveTime() const { return n64RemoveTime; }

    unsigned int GetProtectFlag() { return nProtectFlag;}
    void         SetProtectFlag(unsigned int nValue) { nProtectFlag = nValue;}

private:
    bool bHaveCheck;        // 本次登录是否验证过, 验证过后, 下次不再验证
    __int64 n64RemoveTime;  // 强制删除2级密码的到期时间 ( 不为0时, 说明玩家有强制解除 )
    unsigned int nProtectFlag;  // 设置保护类型的标志位(保护类型枚举代表该标志的每一位)
};

#endif