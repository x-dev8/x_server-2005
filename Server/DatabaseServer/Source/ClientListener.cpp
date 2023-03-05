//#include "ClientListener.h"
//#include "DatabaseClient.h"
//#include "DatabaseServerApp.h"
//
//ClientListener::ClientListener(void)
//{
//}
//
//ClientListener::~ClientListener(void)
//{
//}
//
//BOOL ClientListener::Init()
//{
//    SetNoteType( NT_Server );
//    SetListenPort( GetDatabaseServerApp()->m_wListenPort );
//    return TRUE;
//}
//
//INetworkNode* ClientListener::CreateChildNode()
//{
//    INetworkNode* pNode = new DatabaseClient;
//    if ( pNode  )
//    {
//        pNode->SetNoteType( NT_AcceptNode );
//        pNode->SetPermanence( FALSE );
//    }
//
//    return pNode;
//}
