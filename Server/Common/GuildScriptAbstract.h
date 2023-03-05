

public:
    virtual int GetGuildId() = 0;
    virtual bool IsHaveGuild() = 0;
    virtual bool IsGuildMaster() = 0;

    virtual bool RecordGuildTimeVar( int nVarID ) = 0;       
    virtual bool IsGuildTimeVarPassOneDay( int nVarID ) = 0; 
    virtual void ClearGuildTimeVar( int nVarID, int nClearVarID ) = 0; 

    virtual int32 GetGuildOffer()               = 0;
    virtual void  AddGuildOffer( int nOffer )   = 0;
    virtual void  DecGuildOffer( int nOffer )   = 0;

    virtual int32 GetGuildActivity()            = 0;           
    virtual void  AddGuildActivity( int nOffer) = 0;
    virtual void  DecGuildActivity( int nOffer) = 0;

    virtual int32 GetGuildBuild()               = 0;
    virtual void  AddGuildBuild(int nCredit)    = 0;
    virtual void  DecGuildBuild(int nCredit)    = 0;
                                              
    virtual int32 GetGuildMoney()               = 0;
    virtual void  AddGuildMoney(int nValue )    = 0;
    virtual void  DecGuildMoney(int nValue )    = 0;
                                              
    virtual int16 GetGuildLevel()               = 0;
    virtual void  SetGuildLevel( int nValue )   = 0;

    virtual int32 GetGuildMission()             = 0;         
    virtual void  AddGuildMission( int nValue ) = 0;    
    virtual void  DecGuildMission( int nValue ) = 0;

    virtual int32 GetGuildSalary()             = 0;         
    virtual void  AddGuildSalary( int nValue ) = 0;    
    virtual void  DecGuildSalary( int nValue ) = 0;

    virtual void GuildLevelUp() = 0;                    // �����������
    virtual void GuildOfferBuild() = 0;                 // �ﹱ����
    virtual void GuildCollect() = 0;                    // ����ļ��
    virtual void GuildMasterDelate() = 0;               // ���ɵ���
    virtual void GuildDonate() = 0;                     // ���ɾ���
    virtual bool GuildQuestRelease( int nValue ) = 0;   // �������񷢲�
	virtual int16 GetGuildReleaseQuest()	= 0;			// ��õ�ǰ�����İ�������ID
    virtual bool GuildShopLevelUp( int nValue ) = 0;    // ��������̵�ȼ�
    virtual bool GuildConvene() = 0;                    // �����ټ�

    // �����������
    virtual void AddGuildVar( int nIndex, int nValue ) = 0;
    virtual void SetGuildVar( int nIndex, int nValue ) = 0;
    virtual void DecGuildVar( int nIndex, int nValue ) = 0;
    virtual int GetGuildVar( int nIndex ) = 0;

	virtual int GetGuildMemberPosition() = 0;
