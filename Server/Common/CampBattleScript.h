
public:

    // ��������nBattleType( ս������ )
    // ��������ս( nType = 1 )
    // ��������ս( nType = 2 )
    // ��������ս( nType = 3 )
    // ��ȸ����ս( nType = 4 )
    // Ұ�����ս( nType = 5 )

    // ���ս����Ӫ
    virtual int GetBattleCamp();  

    // ���ս��״̬
    // 0     // ��ʼ״̬ 
    // 1     // ����״̬
    // 2     // ׼��״̬
    // 3     // ����ս��״̬
    // 4     // ս��ս��״̬
    // 5     // ����״̬
    // 6     // ս������, �ͷ���Դ
    virtual int GetCampBattleStatus( int nBattleType ,int countryid);

    // ��ʾ�������� �ɹ�����1, ʧ�ܷ���0
    virtual bool ShowCampBattleSignUp( int nBattleType );

    // ������Ӫս�� �ɹ�����1, ʧ�ܷ���0
    virtual bool SignUpCampBattle( int nBattleType );

    // ��ѯ����ս������( ��������ս, ��������ս, ��ȸ����ս��Ч )
    virtual void QueryCampBattleSignUp( unsigned char nBattleType );

    // ��ʾ������Ӫս������ �ɹ�����1, ʧ�ܷ���0
    virtual bool ShowCampBattleEnter( int nBattleType );

    // ������Ӫս��
    virtual bool EnterCampBattle( int nBattleType );

    // ���ս������
    virtual void AddCampBattleResource( int nAddValue );

    // ���ս������
    virtual int GetCampBattleResource();

    // ɱ����Ӫ����( nAddResource ��ӻ��� )
    virtual void KillCampBattleMonster( int nMonsterID );

    // ˢ����Ӫ��
    virtual void CreateCampMonster( int nMonsterID, int nCount, int nMapId, float fPosX, float fPosY, int nFightCamp, float fRadius, float fBodySize, int nRouteID );
    virtual void CreateCampMonster( int nMonsterID, int nCount, float fRadius, float fBodySize, int nRouteID );

	virtual void ChangeCampBattleScore(int IsRadOrBlue,int ChangeType,int Value);

	virtual int GetCampBattleFight();
