
/************************************************************************
            Include in CenterServerNetEvent.h
************************************************************************/

long OnProcessFamilyMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage );

virtual void _OnCS2GSFamilyDetail( NetClient* pNetClient, CS2GSFamilyDetail* pMessage );
virtual void _OnCS2GSAllFamiliesSendEnd( NetClient* pNetClient, CS2GSAllFamiliesSendEnd* pMessage );
virtual void _OnCS2GSCreateFamilyAck( NetClient* pNetClient, CS2GSCreateFamilyAck* pMessage );
virtual void _OnCS2GSJoinFamilyAck( NetClient* pNetClient, CS2GSJoinFamilyAck* pMessage );
virtual void _OnCS2GSLeaveFamilyAck( NetClient* pNetClient, CS2GSLeaveFamilyAck* pMessage );
virtual void _OnCS2GSFamilyNoticeAck( NetClient* pNetClient, CS2GSFamilyNoticeAck* pMessage );
virtual void _OnCS2GSFamilyTransferAck( NetClient* pNetClient, CS2GSFamilyTransferAck* pMessage );
virtual void _OnCS2GSFamilyDonateAck( NetClient* pNetClient, CS2GSFamilyDonateAck* pMessage );
virtual void _OnCS2GSFamilyUpgradeAck( NetClient* pNetClient, CS2GSFamilyUpgradeAck* pMessage );
virtual void _OnCS2GSTellFamilyDisband( NetClient* pNetClient, CS2GSTellFamilyDisband* pMessage );
virtual void _OnCS2GSFamilyPlayerLvToTen( NetClient* pNetClient, GS2CSFamilyPlayerLvUpToTenMessage* pMessage );
virtual void _OnCS2GSFamilyMemberDataUpdate( NetClient* pNetClient, CS2GSFamilyMemberDataUpdate* pMessage );
virtual void _OnCS2GSFamilyMessage( NetClient* pNetClient, CS2GSFamilyMessage* pMessage );
virtual void _OnCS2GSFamilyProsperityUpdate( NetClient* pNetClient, CS2GSFamilyProsperityUpdate* pMessage );
virtual void _OnCS2GSFamilyAimAck( NetClient* pNetClient, CS2GSFamilyAimAck* pMessage );