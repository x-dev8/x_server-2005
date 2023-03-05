public:
    //系统变量存入数据库的相关函数
    enum EnumCompressDefine
    {
        DecodeFieldBufferSize = 1024 * 10,
        UnZipTempBufferSize   = 1024 * 20,
        ZipTempBufferSize     = 1024 * 40,
        EncodeFieldBufferSize = 1024 * 10,
    };
    virtual void OnLoadSysVarReq( BaseSqlMessage* pSqlMsg ); // 加载系统变量
    virtual void OnSaveSysVarReq( BaseSqlMessage* pSqlMsg ); // 保存系统变量