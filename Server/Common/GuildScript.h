
public:
    int GetGuildId();
    bool IsHaveGuild();
    bool IsGuildMaster();

    // �µ�ʱ�亯��
    virtual bool RecordGuildTimeVar( int nVarID );       
    virtual bool IsGuildTimeVarPassOneDay( int nVarID ); 
    virtual void ClearGuildTimeVar( int nVarID, int nClearVarID ); 

    // ����
    virtual int32 GetGuildOffer();            // ��Ա�ﹱ
    virtual void  AddGuildOffer( int nOffer);
    virtual void  DecGuildOffer( int nOffer);

    virtual int32 GetGuildActivity();            // ��Ա��Ծ��
    virtual void  AddGuildActivity( int nOffer);
    virtual void  DecGuildActivity( int nOffer);

    virtual int32 GetGuildBuild();              // ����� , ����
    virtual void  AddGuildBuild( int nCredit );
    virtual void  DecGuildBuild( int nCredit );

    virtual int32 GetGuildMoney();              // ���ɽ�Ǯ
    virtual void  AddGuildMoney( int nValue );
    virtual void  DecGuildMoney( int nValue );

    virtual int32 GetGuildMission();              // ʹ����
    virtual void  AddGuildMission( int nValue );    
    virtual void  DecGuildMission( int nValue );

    virtual int32 GetGuildSalary();         
    virtual void  AddGuildSalary( int nValue );    
    virtual void  DecGuildSalary( int nValue );

    virtual int16 GetGuildLevel();              // �ȼ�
    virtual void  SetGuildLevel( int nValue );

    virtual void GuildLevelUp();                    // �����������
    virtual void GuildOfferBuild();                 // ���װﹱ
    virtual void GuildCollect();                    // ����ļ��
    virtual void GuildMasterDelate();               // ���ɵ���
    virtual void GuildDonate();                     // ���ɾ���
    virtual bool GuildQuestRelease( int nValue );   // �������񷢲�
    virtual bool GuildShopLevelUp( int nValue );    // �����̵�ȼ�����
    virtual bool GuildConvene();                    // �����ټ�
	virtual	int16 GetGuildReleaseQuest();			// �������񷢲�

    // �����������
    virtual void AddGuildVar( int nIndex, int nValue );
    virtual void SetGuildVar( int nIndex, int nValue );
    virtual void DecGuildVar( int nIndex, int nValue );
    virtual int GetGuildVar( int nIndex );

	virtual void AddGuildBuffByMapID(int MapID,int BuffID,int Level);

	virtual int GetGuildMemberPosition();

