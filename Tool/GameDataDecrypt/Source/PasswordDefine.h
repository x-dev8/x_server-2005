#ifndef __PASSWORDDEFINE_H__
#define __PASSWORDDEFINE_H__

namespace PasswordDefine
{
    enum EConstDefine
    {
        ClearSecondPasswordTime = 3,    // ǿ��ɾ��2������ 3 �����Ч
        MinWealthProtectLength  = 6,    // �Ʋ�����������С����
        MaxWealthProtectLength  = 8,    // �Ʋ�����������󳤶�

        // ���ñ������
        ESetProtect_NonePassword = 1,       // û������
        ESetProtect_PasswordSucc    ,       // ������ȷ
        ESetProtect_PasswordError   ,       // �������

        // ��������
        OP_InitAction        = 0,     // �������ж�
        OP_OpenStorage          ,     // �򿪲ֿ�
        OP_OpenMountStorage     ,     // ������ֿ�
        OP_DelRelation          ,	  // ɾ������
        OP_HandleAuction        ,     // �򿪽𶧽��׽���
        OP_CheckPassword        ,     // ��������֤����
        OP_SetProtect           ,     // �򿪲Ʋ���������

        // ��������ö��
        EProtect_BuyStoreItem = 0,       // �޷�ʹ��Ԫ���ͽ�Ʊ�����̳ǵ���
        EProtect_OpenStorage     ,       // �޷��Ӳֿ���ȡ����Ʒ������
        EProtect_OpenMountStorage,       // �޷�������ֿ���ȡ����Ʒ
        EProtect_Bargaining      ,       // �޷����н�Ǯ���ף��繺��ͽ��ף�
        EProtect_Stall           ,       // �޷����а�̯
        EProtect_ThrowAway       ,       // �޷�����
        EProtect_SellItem        ,       // �޷������̵�
        EProtect_UseItemInBag    ,       // �޷�ʹ�ð����ڵĵ���
        EProtect_UnpackEquip     ,       // �޷�ж���������װ��
        EProtect_FreeMount       ,       // �޷���������
        EProtectFlagInit         ,       // ����Ҫ�жϵ�

        MaxLength = 32,                 // ������󳤶�
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

    const char* GetPassword() const { return szPassword; }      // �������
    bool HavePassword() const { return szPassword[ 0 ] != 0; }  // �ж��Ƿ�������
    bool CheckPassword( const char* szValue ) const             // �ж������Ƿ���Ч
    {
        if ( szValue == NULL )
        { return false; }

        return strcmp( szPassword, szValue ) == 0 ;
    }
private:
    char szPassword[ PasswordDefine::MaxLength + 1 ];
};

// 2������
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
    bool bHaveCheck;        // ���ε�¼�Ƿ���֤��, ��֤����, �´β�����֤
    __int64 n64RemoveTime;  // ǿ��ɾ��2������ĵ���ʱ�� ( ��Ϊ0ʱ, ˵�������ǿ�ƽ�� )
    unsigned int nProtectFlag;  // ���ñ������͵ı�־λ(��������ö�ٴ���ñ�־��ÿһλ)
};

#endif