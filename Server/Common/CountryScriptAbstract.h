
virtual bool IsHaveCountryMaster( unsigned char uchType, unsigned char uchCountry ) = 0;
virtual bool ReceiveCountryMount(unsigned char uchType ) = 0;
virtual bool CountryConenve() = 0;
virtual bool IsCountryMaster( unsigned char uchType ) = 0;
virtual bool IsCountryQueen() = 0;
virtual void AddCountryResource( unsigned char uchType, unsigned int nValue ) = 0;
virtual void SubCountryResource( unsigned char uchType, unsigned int nValue ) = 0;
virtual int GetCountryID() = 0;
virtual bool IsCountryQuestOpen( unsigned char uchType ) = 0;

virtual uint32 GetCountryScore() = 0;
virtual void AddCountryScore( int nValue ) = 0;
virtual void SubCountryScore( int nValue ) = 0;
virtual void SetCountryScore( int nValue ) = 0;

virtual bool IsCountryGuild( unsigned char uchType ) = 0;
virtual int GetCountryOfficial() = 0;
virtual int GetWarSortIndex() = 0;
virtual bool IsInCountryWarFight() = 0;
virtual bool SetCountryKing() = 0;
virtual void SetCountryTribute(int nValue,int countryid,int operType) = 0;
virtual int GetCountryTribute(int countryid) = 0;
virtual bool IsPlayerKing() = 0;
virtual void AddCountryInfo(const char * Info,bool IsUseName,int Value) = 0;