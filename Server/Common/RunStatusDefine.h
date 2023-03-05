#ifndef __SERVERSTATUSDEFINE_H__
#define __SERVERSTATUSDEFINE_H__

namespace RunStatusDefine
{
    enum ERunStatus
    {
        RunStatus_PrepareData,       // ׼������
        RunStatus_Running,           // ��ʼ����
        RunStatus_PrepareStop,       // ׼��ֹͣ
        RunStatus_GameThreadStopped, // ��Ϸֹͣ
        RunStatus_DBThreadStopped,   // ���ݿ�ֹͣ


        ////////////////////////////////////////////////////////
        CheckVersionSuccess = 0,   // �汾��֤�ɹ�
        LoadContrySuccess,         // ���ع������ݳɹ�
        LoadGuildSuccess,          // ���ذ�����ݳɹ�
        LoadRelationSuccess,       // ���ع�ϵ���ݳɹ�
        LoadConsignmentSuccess,    // ���ؼ������ݳɹ�
        LoadItemDropuccess,        // ������Ʒ�������ݳɹ�
        LoadSystemVarSuccess,      // ����ϵͳȫ�ֱ������ݳɹ�
		LoadFamilySuccess,		   // ���ؼ������ݳɹ�
		LoadQuestEntrustSuccess,   // ��������ί�����ݳɹ�
		LoadCampBattleSuccess,	   // ������Ӫս�����ݳɹ�	
		LoadGlobalDBSuccess,	   // ����ȫ�����ݳɹ�	
        //TODO
        LoadResourceSuccess,       // ���м������
    };

    static char* g_szStatusArray[11] = 
    {// ��Ӧ�����6��״̬
        "�汾��֤",
        "��������",
        "�������",
        "��ϵ����",
        "��������",
        "��Ʒ��������",
        "ϵͳȫ�ֱ�������",
		"��������",
		"����ί������",
		"��Ӫս������",
		"ȫ������",
    };
}



#endif // __SERVERSTATUSDEFINE_H__
