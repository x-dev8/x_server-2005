/********************************************************************
    Filename:    PlayerAntiAddictionModule.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

public:
    void               UpdateAntiAddiction();                                  // ����������Update
    void               UpdateAntiAddictionNotify();                            // ��ʱ֪ͨ��������ʾ���ͻ���
    void               UpdateSaveAntiAddiction();                              // ���������ʱ�䵽ƽ̨    
    void               ExitSaveAntiAddiction();                                // �˳����������ʱ�䵽ƽ̨
    AntiAddictionState CalcAntiAddictionStatus( uint32 totalTime );            // ����ʱ���ж���ҷ�����״̬
    uint32             GetAntiAddictionLimitTime( uint8 nAntiAddictionStatus );// ����ʱ���õ������״̬��ʱ��
    uint32             GetAntiAddictionOnlineTime();                           // �õ�������Total����ʱ��
    void               ResetAntiAddictionNotifyIndex();                        // ��ֵ�����Զ�ʱ֪ͨ����
    void               SendMsgWallowAbout( uint8 nType );                      // ����������Ϣ

protected:
    bool               IsRunAntiAddiction(); // �Ƿ���з������߼�

protected:
    bool                _bNeedAntiAddiction           ; // �Ƿ���Ҫ������ ����ǳ�����
    uint32              _nHaveSaveAntiAddtionDuration ; // �Ѿ����浽ƽ̨����ʧʱ�� ��λ����
    __int64             _nAntiAddtionStatusChangeStamp; // ������״̬�ı�ʱ���ʱ���
    uint32              _nAntiAddtionNotifyIndex      ; // ������֪ͨ����
    GameTimerEx         _xUpdateAntiAddictionTimer    ; // ��ѵAntiAddiction��ʱ��
    uint32              _nAntiAddtionTimeCount        ; // �ύ��ƽ̨�ļ��ʱ�����