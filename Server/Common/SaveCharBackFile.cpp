#include "DatabaseConnectors.h"
#include "MsgCutAndRebuild.h"
#include "SaveCharBackFile.h"

#define DBMSGBACKDIR "DBBackup"
#define DBMSGBACKFILE "DBBackup\\DBMsgUnhandled.bak"

CSaveCharBackFile::CSaveCharBackFile(void)
{
}

CSaveCharBackFile::~CSaveCharBackFile(void)
{
}

void CSaveCharBackFile::SaveMsgToFile( DBMsgSaveCharacter *pSave )
{	
	//������Ϣ
	FILE *fp;
	//
	fp = fopen( DBMSGBACKFILE,"ab" );	
	if( !fp )
	{
		//����Ŀ¼				
		CreateDirectory( DBMSGBACKDIR,NULL );

		fp = fopen( DBMSGBACKFILE,"ab" );
		if( !fp )
			return;
	}	
	fwrite( pSave,pSave->header.stLength,1,fp );
	fclose( fp );
}

void CSaveCharBackFile::LoadMsgFromFile( void )
{
	//������Ϣ
	FILE *fp;

	char szMsg[ MSGCANCUTMAXSIZE ];	
	//
	fp = fopen( DBMSGBACKFILE,"rb" );
	if( !fp )
	{
		//����Ŀ¼				
		CreateDirectory( DBMSGBACKDIR,NULL );
		return;
	}

	Msg *pMsg = (Msg*)szMsg;
	while( 0 != fread( pMsg,sizeof(Msg),1,fp ) )
	{
		if( pMsg->header.stLength > MSGCANCUTMAXSIZE )
			break;
		if( pMsg->header.stLength > sizeof( Msg ) )
		{
			if( 1 != fread( szMsg + sizeof( Msg ),pMsg->header.stLength - sizeof( Msg ),1,fp ) )
				break;
			//
			if (DBMSG_SAVECHARACTER == pMsg->header.dwType)
			{
				DBMsgSaveCharacter *pSave = (DBMsgSaveCharacter *)pMsg;
				if( sizeof(DBMsgSaveCharacter) == pSave->header.stLength )
				{
					//��Сһ��
					GettheDBCon().SendMsg( pSave,rand() );
				}
			}
			else
			{
				//��Ϣ����ı��ˣ�
			}

		}
	}
	fclose( fp );

	//ɾ����������ļ�
	DeleteFile( DBMSGBACKFILE );
}