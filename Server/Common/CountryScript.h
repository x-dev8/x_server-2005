
/************************************************************************
            Include in ServerVarInterface.h
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
// 是否有国王( 朱雀之主 或者 青龙之主 )
virtual bool IsHaveCountryMaster( unsigned char uchType, unsigned char uchCountry );
// 领取国家坐骑
virtual bool ReceiveCountryMount( unsigned char uchType );
// 国家召集
virtual bool CountryConenve();
// 是否是城主( 朱雀之主 或者 青龙之主 )
virtual bool IsCountryMaster( unsigned char uchType );
// 是否是国王
virtual bool IsCountryQueen();
// 添加国家资源
virtual void AddCountryResource( unsigned char uchType, unsigned int nValue );
// 减少国家资源
virtual void SubCountryResource( unsigned char uchType, unsigned int nValue );
// 获得国家类型
virtual int GetCountryID();
// 国家任务是否处于开启状态
virtual bool IsCountryQuestOpen( unsigned char uchType );

// 获得国战积分
virtual uint32 GetCountryScore();

// 添加国战积分
virtual void AddCountryScore( int nValue );

// 减少国战积分
virtual void SubCountryScore( int nValue );

// 设置国战积分
virtual void SetCountryScore( int nValue );

// 判断是否国王帮, 守护帮
virtual bool IsCountryGuild( unsigned char uchType );

// 获得国家官员职位
virtual int GetCountryOfficial();

// 获得国战杀人排行, 返回0 ( 表示尚未排行, 如果要领取, 按默认俸禄领取 ) 其余 返回( 1, 2, 3 )
virtual int GetWarSortIndex();

// 获得是否在国战期间
virtual bool IsInCountryWarFight();

//设置国王
virtual bool SetCountryKing();

//zhuxincong 设置贡品
virtual void SetCountryTribute (int nValue,int countryid,int operType);		// 国家贡品
//获得贡品
virtual int GetCountryTribute (int countryid);		// 国家贡品

virtual bool IsPlayerKing();			//判断玩家是否是国王

virtual void AddCountryInfo(const char * Info,bool IsUseName,int Value);