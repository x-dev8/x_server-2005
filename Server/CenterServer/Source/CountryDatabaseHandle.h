
/************************************************************************
            Include in NormalLogicWorkThread.h
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/


virtual void OnRequestCountryDataReq ( BaseSqlMessage* pSqlMessage );   // 请求读取国家信息
virtual void OnRequestCountryInfoReq(BaseSqlMessage* pSqlMessage);
virtual void OnCountryDataSaveReq    ( BaseSqlMessage* pSqlMessage );   // 请求保存国家信息
virtual void OnGetCountryOfficeFaceInfo ( BaseSqlMessage* pSqlMessage );
virtual void OnSaveCountryInfoReq(BaseSqlMessage* pSqlMessage);
void OnLoadCountryOfficialFace(uint32 RoleID,uint8& Sex,uint16& FaceID,uint16& HeaderID,uint16& ProfessionID);	//读取官员头部信息