
virtual void OnRequestQuestEntrustDataReq ( BaseSqlMessage* pSqlMessage );
virtual void OnAddQuestEntrustDataReq( BaseSqlMessage* pSqlMessage );
virtual void OnDelQuestEntrustDataReq(BaseSqlMessage* pSqlMessage );
virtual void OnUpdateQuestEntrustDataReq(BaseSqlMessage* pSqlMessage );

void ReadQuestEntrustByteData(BYTE* bybuff,DWORD dwsize,SCharItem& info);
bool WriteQuestEntrustByteData(uint8* pOutBuffer,uint32 outBufferSize,SCharItem& info,uint32& nActualSize);