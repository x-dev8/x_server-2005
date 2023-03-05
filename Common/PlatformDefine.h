/********************************************************************
Filename:    PlatformDefine.h
MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __COMMON_PLATFORMDEFINE_H__
#define __COMMON_PLATFORMDEFINE_H__

#pragma once

#pragma pack( push, 1 )

// �ɵ�,�µ�����ͷ���
struct SAddPoints
{
	uint32 guid;          // �û�id
	uint32 gssid;         // ��ֵ��Ϸ��������id  
	uint8  typeId;        // 1--paycard  2--paynet  3--esales
	int8   typesn[32];    // ������
	uint32 points;        // �ӵ���
	uint16 discount;      // �ۿ�
	uint32 addamount;     // ��ֵǮ��
	uint32 netincome;     // ������
	int8   signstr[32+1]; // ǩ��
	int8   remark[32+1];  // ��ע
	int8   userip[17];    // ip��ַ 
	int8   gateway[17];   // ���� 
	uint8  channel;       // ͨ��
	uint32 paytime;       // ������Чʱ��
};

// ƽ̨����PayInfo��Ϣ
enum EPayFlagType
{
	EPayFlagType_WaitingProcess, // �ȴ�����
	EPayFlagType_Processing    , // ������
	EPayFlagType_ProcessOver   , // �������
};

enum EAccountPointOpType
{
	EAPOT_Sub, // ����
	EAPOT_Add, // �ӵ�
	EAPOT_Set, // ���õ�
};

struct SPayInfo
{ // �������ݽṹ������,ֻ��Ҫ��log����
	int32  pid         ;
	int32  gssid       ;
	int8   passport[33];
	uint32 guid        ; // �˺�id
	int16  typeId      ; // ������ȫ��Ψһ
	int8   typesn[31]  ;
	int32  addpoint    ; // Ҫ�ӵĵ���
	int32  discount    ;
	int32  addamount   ;
	int32  netincome   ;
	int8   remark[32]  ;
	int8   userip[21]  ;
	int8   gateway[21] ;
	int16  channel     ;
	int    paytime     ;
	int8   flag        ; // Ĭ��Ϊ0---δ�ӵ� 1---�ӵ�ɹ�
	int    ctime       ; // ��ֵʱ��
};

//struct SGMTaskInfo
//{
//    uint32 id         ; // taskid
//    uint8  type       ; // task���� Э���ʾ��
//    int8   values[256]; // ����ֵ
//    int32  ctime      ; // ʱ��
//    int8   result[31] ; // �������ֵ
//    int32  stateTime  ; // ״̬ʱ��
//    int8   flag       ; // ��ʾλ Ĭ��Ϊ0-δ���� 1-����ɹ� 2-������
//};

enum eTaskResult
{
	eTaskResult_ConntenMax = 256,
	eTaskResult_ResNo	   = -1,//��Ҫ����
	eTaskResult_ResSucc	   = 0,//�Ѿ����
	eTaskResult_ResWaiting = 1,//�ȴ����	
	eTaskResult_ResFail	   = 2,//ִ��ʧ��
	eTaskResult_ResFail2	   = 3,//ִ��ʧ��
	eTaskResult_ResFail3	   = 4,//ִ��ʧ��
	eTaskResult_AllServer  = -1,//�����е�server��ִ��
};

struct SGMTaskInfo
{
	SGMTaskInfo(){memset(this, 0, sizeof(*this));}
	~SGMTaskInfo(){}
	uint32 id								;//id
	char   content[eTaskResult_ConntenMax]	;//��������,��Ҫ����
	int16 serverid							;//����
	int16  result							;//���
};

enum ETaskInfo
{  
	ETaskInfo_NameMaxLength		 = 33,					//�ռ��˵����ִ�С
	ETaskInfo_MoneySendMax        = 200 * 10000,      // ����200��
	ETaskInfo_MailMaxCount        = 100,              // �ռ���ɱ����ʼ�������Ϊ100��    
	ETaskInfo_MailFullNotifyCount = 90,               // ������������90��ϵͳ��ʾ��������    
	ETaskInfo_AddressNameSize     = 32+1,			  // ��ַ
	ETaskInfo_HoldMailDays        = 30,               // ������Ĵ��ʱ��
	ETaskInfo_MailFee             = 50,               // ÿ���ʼ�������    
	ETaskInfo_MailContentMax      = 50 * 2,           // ÿ���ʼ�������ַ���    
	ETaskInfo_TileMaxCount        = 32,               // �ʼ�����
	ETaskInfo_MailAccessorySize   = 300,              // ������С
	ETaskInfo_FromMaxCount        = 1,                // �����˵ĸ���
	ETaskInfo_ToMaxCount          = 1,                // Ŀ��������
	ETaskInfo_OtherSendMaxCount   = 6,                // ����
	ETaskInfo_TargetMaxCount      = ETaskInfo_ToMaxCount + ETaskInfo_OtherSendMaxCount,
	ETaskInfo_OwnerMaxCount       = ETaskInfo_FromMaxCount + ETaskInfo_TargetMaxCount,

	ETaskInfo_FromIndex           = 0,                              // �������������е�λ��
	ETaskInfo_ToIndex             = ETaskInfo_FromIndex + ETaskInfo_FromMaxCount, // �������������е�λ��
	ETaskInfo_OtherIndex          = ETaskInfo_ToIndex + ETaskInfo_ToMaxCount,     // �������������е�λ��

	ETaskInfo_ActivityIDArray	  = 30,				//����id������
};

enum eMailType
{
	eMailType_maillist = 0, //�����ݿ��л�õ��ʼ�����
	eMailType_Present = 1, //��present�������ʼ�
	eMailType_Activity = 2, //��Activity�������ʼ�
};

struct SMailTaskInfo
{
	SMailTaskInfo(){memset(this, 0, sizeof(*this));}
	~SMailTaskInfo(){}
	uint32 id				;//id
	uint32 characterid		;//��ɫDB ID
	char   charactername[ETaskInfo_NameMaxLength]	;//��ɫ����
	char   title[ETaskInfo_TileMaxCount]			;//�ʼ�����
	char   content[ETaskInfo_MailContentMax]			;//�ʼ�����
	uint32 money			;//����
	uint16 itemid			;//��ƷID
	uint16 itemcount		;//��Ʒ����
	int16  serverid			;//������id
	int16  result			;//���
	uint8  _type			;//�ʼ�����
};

///////////////////////////////////////////////////////////////
enum eWorkSpaceTask
{
	eWorkSpaceTask_SNLength   = 33,//sn����

	eWorkSpaceTask_AskPresent = 0,//����present
	eWorkSpaceTask_AskActivity = 1,//����
	eWorkSpaceTask_EpistarPoint = 2,//��Ϸ�Ծ�Ԫ���ֵ�Ĳ��� by cloud
};

struct SAskPresent
{
	char   charactername[ETaskInfo_NameMaxLength];
	uint32 characterid;
	uint32 accountid;
	char   sn[eWorkSpaceTask_SNLength];	
};

struct SAskAvtivity
{
	char   charactername[ETaskInfo_NameMaxLength];
	uint32 characterid;
	uint32 accountid;
	int32  _type;
	uint32 idArray[ETaskInfo_ActivityIDArray];
};
struct SEpistarPoint
{
	char   charactername[ETaskInfo_NameMaxLength];
	uint32 characterid;
	uint32 accountid;
	int32  _type;
	uint16 nItemId;
	uint16 nPoint;
};

struct SWorkSpaceTask
{
	SWorkSpaceTask(){memset(this, 0, sizeof(*this));}
	~SWorkSpaceTask(){}

	union
	{
		SAskPresent		askpresent;
		SAskAvtivity	askactivity;
		SEpistarPoint   askEpistarPoint;
	}s;

	uint16 tasktype;
	uint16 serverid;
	int16  result;
};

enum eError
{	
	eError_NoActivity = 0,//�޻���������Ѿ���ȡ����
	eError_SNError = 1,//���кŴ���
	eError_AccountError = 2,//�ʺ��Ѿ���ȡ����
	eError_CharacterError = 3,//��ɫ�Ѿ���ȡ����
	eError_PresentSucc = 4,//��ȡ�����ɹ�
	eError_ActivitySucc = 5,//��ȡ�����ɹ�
	eError_EpistarPointSucc = 6,//��Ԫ����ӳɹ�
	eError_EpistarPointError = 7,//��Ԫ�����ʧ��
	eError_Unkown//δ֪����
};

struct SErrorInfo
{
	SErrorInfo()
	{
		memset(this, 0, sizeof(*this));
		result = eError_Unkown;
	}
	~SErrorInfo(){}
	uint32 accountid		;//�ʺ�ID
	uint32 characterid		;//��ɫDB ID
	int16  serverid			;//������id
	int16  result			;//���
};

#pragma pack( pop )

#endif // __COMMON_PLATFORMDEFINE_H__
