
public:

    void    SetPKValue( int nValue, char chOp = PKValueOp_Add, unsigned char chSendMessage = BV_SendMessage );     // 设置PK值
    int     GetPKValue() { return m_nPKValue; }                                                     // 获得PK值 

    bool    SetPKMode( unsigned char nMode, unsigned char chSendMessage = BV_SendMessage );         // 设置PK模式
    uint8   GetPKMode() { return m_nPKMode; }                                                       // 获得PK模式

    bool    GMSetPKMode( unsigned char nMode );                                                     // GM设置PK模式

    bool    CheckCanAttackPlayer( GamePlayer* pTarget );                                        // 是否能攻击某玩家
    void    AttackChar(BaseCharacter* pChar);                                                   // 攻击某角色
    void    AttackPlayer( GamePlayer* pTarget, bool bSummonPet = false );                       // 攻击某玩家
	void    AttactOrAssistChar(BaseCharacter* pChar);											// 攻击 或者辅助 角色

    void    KillChar( BaseCharacter* pChar );                           // 杀死某角色
    void    KillPlayer( GamePlayer* pTarget );                          // 杀死某玩家
    bool    IsEffectKill( unsigned int dwPlayerDBID );                  // 是否是有效杀死玩家

    void    EnterCriticalMode();                                        // 进入狂暴模式

    void    PKProcessRun( unsigned int dwCostTime );                    // 更新
    void    ProcessPKPunish();                                          // PK值惩罚

    void    TellClientPKValue( bool bSendToView = true );               // 通知客户端PK值

    int     GetHonourTopLimit();                                        // 获得PK值上限

	bool    IsInOneGuild(GamePlayer* pTarget);							//判断目标玩家是否和自己处于同一军团
	void    OnPkDead();													//当玩家被PK死亡的时候
	bool	IsInNormalMap();											//判断玩家是否在普通地图
protected:
    void    _ProcessPKValue( GamePlayer* pTarget );                     // 更新PK值
    void    _ProcessHonour ( GamePlayer* pTarget );                     // 更新荣誉值
protected:      // 属性

    uint8  m_nPKMode;                       // PK保护模式
    int16  m_nPKValue;                      // 当前角色PK值

    GameTimerEx m_gtUpdatePKValueTimer;       // 定时减少PK值
    GameTimerEx m_gtUpdatePKModeTimer ;       // 防止频繁切换PK模式
    GameTimerEx m_gtUpdateCriticalModeTimer;  // 定时刷新狂暴模式
private:
	struct KillPlayerMap
	{
		struct KillPlayerInfo
		{
			//一小时内同一玩家反复击杀3次后无荣誉奖励
			unsigned int		m_KillID;//击杀玩家ID
			unsigned int		m_KillNum;//击杀玩家次数
			DWORD				m_LogTime;//最后击杀时间
			KillPlayerInfo():m_KillID(0),m_KillNum(0),m_LogTime(0)
			{}
		};
		enum KillPlayerDate
		{
			KillPlayerMaxTime = 3600000,//1小时
			KillPlayerMaxSum  = 3,//最大反复击杀3次
			KillAddMaxTime	  = 300000,//累计杀人数的累计极限时间
		};
		typedef map<unsigned int,KillPlayerInfo>	 KillOtherCountryPlayerMap;
		KillOtherCountryPlayerMap		m_KillMap;//击杀其他国家玩家的列表
		unsigned int					m_KillAddSum;//累计击杀数量
		DWORD							m_LastSkillPlayerTime;//玩家最后杀人的时间
		KillPlayerMap()
		{
			m_KillAddSum = 0;
			m_LastSkillPlayerTime = 0;
			m_KillMap.clear();
		}
		bool OnKillPlayer(GamePlayer* pMe,GamePlayer* pTarget)//当杀死一个玩家的时候 返回值为是否可以获取荣誉
		{
			//当玩家击杀一个玩家的时候
			if (pMe->GetCountry() == pTarget->GetCountry())
				return false;
			//判断地图 只有在野外才记录
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
					//通告 通告客户端连杀的消息
					MsgConKillPlayerAck msg;
					msg.KillNum = m_KillAddSum;
					pMe->SendMessageToClient(&msg);
					if(m_KillAddSum >=50)
					{
						//设置成就 无人可档

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
			//清理掉已经过期的击杀记录
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
			//当玩家死亡的时候
			m_KillAddSum = 0;
		}
		unsigned int GetKillNumByTime()
		{
			return m_KillAddSum;
		}
	};
	KillPlayerMap					m_KillPlayerMap;//玩家击杀非本国玩家的记录信息

	GameTimerEx						m_AttertUpdateTime;
	bool							m_IsUpdateLevelPKAttMode;
private:
	void	OnAddKillPlayerSum(GamePlayer* pTarget);
	void    OnUpdateClearKillPlayerWeekSum();
	void	OnPlayerLeaveAttack();//当玩家离开战斗状态的时候
	void    OnLevelAttackMode();
	void    OnAttactOrAssistPlayer(GamePlayer* pPlayer);//与玩家发生交互比如战斗或者辅助(治疗 +Buff)的
	void    OnCheckKillPlayerSum();