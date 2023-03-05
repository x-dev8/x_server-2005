
/************************************************************************
            Include in ServerVarInterface.h
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
// �Ƿ��й���( ��ȸ֮�� ���� ����֮�� )
virtual bool IsHaveCountryMaster( unsigned char uchType, unsigned char uchCountry );
// ��ȡ��������
virtual bool ReceiveCountryMount( unsigned char uchType );
// �����ټ�
virtual bool CountryConenve();
// �Ƿ��ǳ���( ��ȸ֮�� ���� ����֮�� )
virtual bool IsCountryMaster( unsigned char uchType );
// �Ƿ��ǹ���
virtual bool IsCountryQueen();
// ��ӹ�����Դ
virtual void AddCountryResource( unsigned char uchType, unsigned int nValue );
// ���ٹ�����Դ
virtual void SubCountryResource( unsigned char uchType, unsigned int nValue );
// ��ù�������
virtual int GetCountryID();
// ���������Ƿ��ڿ���״̬
virtual bool IsCountryQuestOpen( unsigned char uchType );

// ��ù�ս����
virtual uint32 GetCountryScore();

// ��ӹ�ս����
virtual void AddCountryScore( int nValue );

// ���ٹ�ս����
virtual void SubCountryScore( int nValue );

// ���ù�ս����
virtual void SetCountryScore( int nValue );

// �ж��Ƿ������, �ػ���
virtual bool IsCountryGuild( unsigned char uchType );

// ��ù��ҹ�Աְλ
virtual int GetCountryOfficial();

// ��ù�սɱ������, ����0 ( ��ʾ��δ����, ���Ҫ��ȡ, ��Ĭ��ٺ»��ȡ ) ���� ����( 1, 2, 3 )
virtual int GetWarSortIndex();

// ����Ƿ��ڹ�ս�ڼ�
virtual bool IsInCountryWarFight();

//���ù���
virtual bool SetCountryKing();

//zhuxincong ���ù�Ʒ
virtual void SetCountryTribute (int nValue,int countryid,int operType);		// ���ҹ�Ʒ
//��ù�Ʒ
virtual int GetCountryTribute (int countryid);		// ���ҹ�Ʒ

virtual bool IsPlayerKing();			//�ж�����Ƿ��ǹ���

virtual void AddCountryInfo(const char * Info,bool IsUseName,int Value);