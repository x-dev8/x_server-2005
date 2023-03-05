
public:

    void    SetPKValue( int nValue, char chOp = PKValueOp_Add, unsigned char chSendMessage = BV_SendMessage );     // ����PKֵ
    int     GetPKValue() { return m_nPKValue; }                                                     // ���PKֵ 

    bool    SetPKMode( unsigned char nMode, unsigned char chSendMessage = BV_SendMessage );         // ����PKģʽ
    uint8   GetPKMode() { return m_nPKMode; }                                                       // ���PKģʽ

    bool    GMSetPKMode( unsigned char nMode );                                                     // GM����PKģʽ

    bool    CheckCanAttackPlayer( GamePlayer* pTarget );                                        // �Ƿ��ܹ���ĳ���
    void    AttackChar(BaseCharacter* pChar);                                                   // ����ĳ��ɫ
    void    AttackPlayer( GamePlayer* pTarget, bool bSummonPet = false );                       // ����ĳ���
	void    AttactOrAssistChar(BaseCharacter* pChar);											// ���� ���߸��� ��ɫ

    void    KillChar( BaseCharacter* pChar );                           // ɱ��ĳ��ɫ
    void    KillPlayer( GamePlayer* pTarget );                          // ɱ��ĳ���
    bool    IsEffectKill( unsigned int dwPlayerDBID );                  // �Ƿ�����Чɱ�����

    void    EnterCriticalMode();                                        // �����ģʽ

    void    PKProcessRun( unsigned int dwCostTime );                    // ����
    void    ProcessPKPunish();                                          // PKֵ�ͷ�

    void    TellClientPKValue( bool bSendToView = true );               // ֪ͨ�ͻ���PKֵ

    int     GetHonourTopLimit();                                        // ���PKֵ����

	bool    IsInOneGuild(GamePlayer* pTarget);							//�ж�Ŀ������Ƿ���Լ�����ͬһ����
	void    OnPkDead();													//����ұ�PK������ʱ��
	bool	IsInNormalMap();											//�ж�����Ƿ�����ͨ��ͼ
protected:
    void    _ProcessPKValue( GamePlayer* pTarget );                     // ����PKֵ
    void    _ProcessHonour ( GamePlayer* pTarget );                     // ��������ֵ
protected:      // ����

    uint8  m_nPKMode;                       // PK����ģʽ
    int16  m_nPKValue;                      // ��ǰ��ɫPKֵ

    GameTimerEx m_gtUpdatePKValueTimer;       // ��ʱ����PKֵ
    GameTimerEx m_gtUpdatePKModeTimer ;       // ��ֹƵ���л�PKģʽ
    GameTimerEx m_gtUpdateCriticalModeTimer;  // ��ʱˢ�¿�ģʽ
private:
	struct KillPlayerMap
	{
		struct KillPlayerInfo
		{
			//һСʱ��ͬһ��ҷ�����ɱ3�κ�����������
			unsigned int		m_KillID;//��ɱ���ID
			unsigned int		m_KillNum;//��ɱ��Ҵ���
			DWORD				m_LogTime;//����ɱʱ��
			KillPlayerInfo():m_KillID(0),m_KillNum(0),m_LogTime(0)
			{}
		};
		enum KillPlayerDate
		{
			KillPlayerMaxTime = 3600000,//1Сʱ
			KillPlayerMaxSum  = 3,//��󷴸���ɱ3��
			KillAddMaxTime	  = 300000,//�ۼ�ɱ�������ۼƼ���ʱ��
		};
		typedef map<unsigned int,KillPlayerInfo>	 KillOtherCountryPlayerMap;
		KillOtherCountryPlayerMap		m_KillMap;//��ɱ����������ҵ��б�
		unsigned int					m_KillAddSum;//�ۼƻ�ɱ����
		DWORD							m_LastSkillPlayerTime;//������ɱ�˵�ʱ��
		KillPlayerMap()
		{
			m_KillAddSum = 0;
			m_LastSkillPlayerTime = 0;
			m_KillMap.clear();
		}
		bool OnKillPlayer(GamePlayer* pMe,GamePlayer* pTarget)//��ɱ��һ����ҵ�ʱ�� ����ֵΪ�Ƿ���Ի�ȡ����
		{
			//����һ�ɱһ����ҵ�ʱ��
			if (pMe->GetCountry() == pTarget->GetCountry())
				return false;
			//�жϵ�ͼ ֻ����Ұ��ż�¼
			if(!pTarget->IsInNormalMap())
				return false;
			if(HQ_TimeGetTime() - m_LastSkillPlayerTime > KillAddMaxTime)
			{
				m_KillAddSum = 1;
			}
			else
			{
				++m_KillAddSum;
				if(m_KillAddSum > 0)
				{
					//ͨ�� ͨ��ͻ�����ɱ����Ϣ
					MsgConKillPlayerAck msg;
					msg.KillNum = m_KillAddSum;
					pMe->SendMessageToClient(&msg);
					if(m_KillAddSum >=50)
					{
						//���óɾ� ���˿ɵ�

					}
				}
			}
			m_LastSkillPlayerTime = HQ_TimeGetTime();

			KillOtherCountryPlayerMap::iterator Iter= m_KillMap.find(pTarget->GetDBCharacterID());
			
			//KillOtherCountryPlayerMap::iterator Iter= find(m_KillMap.begin(),m_KillMap.end(),pTarget->GetDBCharacterID());
			if(Iter != m_KillMap.end())
			{
				KillPlayerInfo& info = m_KillMap[pTarget->GetDBCharacterID()];
				bool isStates = false;
				if(HQ_TimeGetTime() - info.m_LogTime > KillPlayerMaxTime)
				{
					isStates= true;
					info.m_KillNum = 1;
					info.m_LogTime= HQ_TimeGetTime();
				}
				else if(info.m_KillNum < KillPlayerMaxSum)
				{
					isStates= true;
					++info.m_KillNum;
					info.m_LogTime= HQ_TimeGetTime();
				}
				else
				{
					isStates= false;
					++info.m_KillNum;
					info.m_LogTime= HQ_TimeGetTime();
				}
				return isStates;
			}
			else
			{
				KillPlayerInfo info;
				info.m_KillID = pTarget->GetDBCharacterID();
				info.m_KillNum = 1;
				info.m_LogTime = HQ_TimeGetTime();
				m_KillMap.insert(KillOtherCountryPlayerMap::value_type(pTarget->GetDBCharacterID(),info));
				return true;
			}
		}
		void Update()
		{
			//������Ѿ����ڵĻ�ɱ��¼
			if(!m_KillMap.empty())
			{
				KillOtherCountryPlayerMap::iterator Iter = m_KillMap.begin();
				for(;Iter != m_KillMap.end();)
				{
					if(HQ_TimeGetTime() - Iter->second.m_LogTime > KillPlayerMaxTime)
						Iter = m_KillMap.erase(Iter);
					else
						++Iter;
				}
			}
			if(HQ_TimeGetTime() - m_LastSkillPlayerTime > KillAddMaxTime && m_KillAddSum !=0)
			{
				m_KillAddSum = 0;
			}
		}
		void OnDead()
		{
			//�����������ʱ��
			m_KillAddSum = 0;
		}
		unsigned int GetKillNumByTime()
		{
			return m_KillAddSum;
		}
	};
	KillPlayerMap					m_KillPlayerMap;//��һ�ɱ�Ǳ�����ҵļ�¼��Ϣ

	GameTimerEx						m_AttertUpdateTime;
	bool							m_IsUpdateLevelPKAttMode;
private:
	void	OnAddKillPlayerSum(GamePlayer* pTarget);
	void    OnUpdateClearKillPlayerWeekSum();
	void	OnPlayerLeaveAttack();//������뿪ս��״̬��ʱ��
	void    OnLevelAttackMode();
	void    OnAttactOrAssistPlayer(GamePlayer* pPlayer);//����ҷ�����������ս�����߸���(���� +Buff)��
	void    OnCheckKillPlayerSum();