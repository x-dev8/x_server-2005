
/************************************************************************
            Include in NormalLogicWorkThread.h
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/


virtual void OnRequestCountryDataReq ( BaseSqlMessage* pSqlMessage );   // �����ȡ������Ϣ
virtual void OnRequestCountryInfoReq(BaseSqlMessage* pSqlMessage);
virtual void OnCountryDataSaveReq    ( BaseSqlMessage* pSqlMessage );   // ���󱣴������Ϣ
virtual void OnGetCountryOfficeFaceInfo ( BaseSqlMessage* pSqlMessage );
virtual void OnSaveCountryInfoReq(BaseSqlMessage* pSqlMessage);
void OnLoadCountryOfficialFace(uint32 RoleID,uint8& Sex,uint16& FaceID,uint16& HeaderID,uint16& ProfessionID);	//��ȡ��Աͷ����Ϣ