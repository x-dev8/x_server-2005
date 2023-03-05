
long OnProcessGlobalDBMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage );
virtual void _OnCS2GSUpdateGlobalDBAck      ( NetClient* pNetClient, CS2GSUpdateGlobalDBAck* pMessage );
virtual void _OnCS2GSLoadGlobalDBAck		( NetClient* pNetClient, CS2GSLoadGlobalDBAck* pMessage );