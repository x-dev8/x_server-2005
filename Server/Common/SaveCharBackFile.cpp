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
	//保存消息
	FILE *fp;
	//
	fp = fopen( DBMSGBACKFILE,"ab" );	
	if( !fp )
	{
		//创建目录				
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
	//保存消息
	FILE *fp;

	char szMsg[ MSGCANCUTMAXSIZE ];	
	//
	fp = fopen( DBMSGBACKFILE,"rb" );
	if( !fp )
	{
		//创建目录				
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
					//大小一致
					GettheDBCon().SendMsg( pSave,rand() );
				}
			}
			else
			{
				//消息定义改变了！
			}

		}
	}
	fclose( fp );

	//删除处理完的文件
	DeleteFile( DBMSGBACKFILE );
}