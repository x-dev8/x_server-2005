public:
    //ϵͳ�����������ݿ����غ���
    enum EnumCompressDefine
    {
        DecodeFieldBufferSize = 1024 * 10,
        UnZipTempBufferSize   = 1024 * 20,
        ZipTempBufferSize     = 1024 * 40,
        EncodeFieldBufferSize = 1024 * 10,
    };
    virtual void OnLoadSysVarReq( BaseSqlMessage* pSqlMsg ); // ����ϵͳ����
    virtual void OnSaveSysVarReq( BaseSqlMessage* pSqlMsg ); // ����ϵͳ����