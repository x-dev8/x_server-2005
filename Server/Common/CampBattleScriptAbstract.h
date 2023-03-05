
public:
    
    // ��������nBattleType( ս������, ��������ս( nType = 1 ) )

    // ���ս����Ӫ
    virtual int GetBattleCamp() = 0;   

    // ���ս��״̬
    virtual int GetCampBattleStatus( int nBattleType,int countryid ) = 0;

    // ��ʾ��������
    virtual bool ShowCampBattleSignUp( int nBattleType ) = 0;

    // ��ѯ������Ϣ( ��������ս, ��������ս, ��ȸ����ս��Ч )
    virtual void QueryCampBattleSignUp( unsigned char nBattleType ) = 0;

    // ������Ӫս�� 
    virtual bool SignUpCampBattle( int nBattleType ) = 0;

    // ��ʾ������Ӫս������
    virtual bool ShowCampBattleEnter( int nBattleType ) = 0;

    // ������Ӫս��
    virtual bool EnterCampBattle( int nBattleType ) = 0;

    // ���ս������
    virtual void AddCampBattleResource( int nAddValue ) = 0;

    // ���ս������
    virtual int GetCampBattleResource() = 0;

    // ɱ����Ӫ����
    virtual void KillCampBattleMonster( int nMonsterID ) = 0;

    // ˢ����Ӫ��
    virtual void CreateCampMonster( int nMonsterID, int nCount, int nMapId, float fPosX, float fPosY, int nFightCamp, float fRadius, float fBodySize, int nRouteID ) = 0;
    virtual void CreateCampMonster( int nMonsterID, int nCount, float fRadius, float fBodySize, int nRouteID ) = 0;

	//����ս��˫��������һ���Ļ���
	virtual void ChangeCampBattleScore(int IsRadOrBlue,int ChangeType,int Value) = 0;

	virtual int GetCampBattleFight() = 0;