#ifndef __PLAYERSCRIPTHANDLE_H__
#define __PLAYERSCRIPTHANDLE_H__

public:

    int        PushScript( SScript* p );
    bool       PopScript(); // ����ֵ ��ʾ�Ƿ��нű���Ҫִ��
    SScript*   GetScript();
    BOOL       RegisterVar( short stVarId );
    void       CancelCurScript( const char* szFile, const char* szFun ); // ��ֹ��ǰ�ű�
    void       CancelAllScript();
    void       SetScriptSleepTime( DWORD dwTime );
    void       CheckScriptSleep();
    void       SetScriptNpc( const int nId ){ m_nScriptNpcId = nId; }
    int        GetScirptNpc(){ return m_nScriptNpcId;}
    void       SetVar( int nKey, int nVar, int nOp = SKW_SET, unsigned char uchSendMessage = BV_SendMessage );
    int        GetVar( int i );

    void   Script_SetCon( int nCon, int nOp );  // ����
    void   Script_SetStr( int nStr, int nOp );  // ����
    void   Script_SetDex( int nDex, int nOp );  // ����
    void   Script_SetInt( int nInt, int nOp );  // ����
    void   Script_SetMgc( int nMgc, int nOp );  // ħ��
    void   Script_SetLky( int nLky, int nOp );  // ����
    int    Script_GetCon();                     // ����
    int    Script_GetStr();                     // ����
    int    Script_GetDex();                     // ����
    int    Script_GetInt();                     // ����
    int    Script_GetMgc();                     // ħ��
    int    Script_GetLky();                     // ����
    void   Script_SetExp( __int64 nExp, int nOp, char* szFunction, int nLine ); // ����
    void   Script_SetSkillExp( int nExp, int nOp ); // ���ܾ���
    void   Script_SetHp( int nHp, int nOp );
    void   Script_SetTp( int nTp, int nOp );
    void   Script_SetMp( int nMp, int nOp );
    void   Script_SetEnergy( int nInte, int nOp );
    void   Script_SetVigor( int value, int nOp );

    void   Script_SetVigorMax( int value, int nOp );
    void   Script_SetSkillPoint( int nType, int nValue, int nOp );  // ��������ܵ�

    void   Script_SetProfession( int nProfession ); // ְҵ
    void   Script_SetSex( int nSex ){}
    void   Script_Skill( int iWhichSkill, int nOp );// ����
    void   Script_SetBornPoint( DWORD dwMapID, int iPosX, int iPosY ); // ���ó�����
    int    Script_GetExp( );      // ����
    int    Script_GetSkillExp( ); // ���ܾ���
    int    Script_GetHp( );    
    int    Script_GetMp( );
    bool   Script_IsThisItemEquipped( unsigned short ustItemId );
    bool   Script_IsThisSkillActived( unsigned short ustSkillItemID,unsigned short ustSkillLevel );

    bool Script_IsInArea(int Lx,int Ly,int Rx,int Ry); // ��������
    int  Script_SelfPosX();
    int  Script_SelfPosY();
    void Script_DropItemOnMonsterDead(int ItemId,int ItemNum,bool nobelong = true); // �������
    void Script_GetPlayerCountVar( short stQuestId, short stVarId );
    void Script_AddRecipe( unsigned short ustRecipeID );

    void SetAreaRepulation( SAreaRepulation& xArea );
    SAreaRepulation* GetAreaRepulation( int nMapID );
    void Script_SetAreaCurrentReputation( int nMapID, int nValue, int nOp );
    int Script_GetAreaCurrentReputation( int nMapID );
    void Script_SetAreaMaxReputation( int nMapID, int nValue, int nOp );
    int Script_GetAreaMaxReputation( int nMapID );

	int Script_GetWeekKillNum();
	int Script_GetAllKillNum();
	int Script_GetSeriesKillNum();
	void Script_ProcTimeStep(int StringID,int TimeStep);
#endif