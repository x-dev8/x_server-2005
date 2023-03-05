virtual void OnLoadGlobalDBReq(BaseSqlMessage* pSqlMessage);
virtual void OnSaveGlobalDBReq(BaseSqlMessage* pSqlMessage);
void ReadGlobalDBByte(BYTE* bybuff,DWORD dwsize,GlobalDB& info);
bool WriteGlobalDBByte(uint8* pOutBuffer,uint32 outBufferSize,GlobalDB& info,uint32& nActualSize);