#ifndef __PLAYERSCRIPTHANDLE_H__
#define __PLAYERSCRIPTHANDLE_H__

public:

    int        PushScript( SScript* p );
    bool       PopScript(); // 返回值 标示是否还有脚本需要执行
    SScript*   GetScript();
    BOOL       RegisterVar( short stVarId );
    void       CancelCurScript( const char* szFile, const char* szFun ); // 中止当前脚本
    void       CancelAllScript();
    void       SetScriptSleepTime( DWORD dwTime );
    void       CheckScriptSleep();
    void       SetScriptNpc( const int nId ){ m_nScriptNpcId = nId; }
    int        GetScirptNpc(){ return m_nScriptNpcId;}
    void       SetVar( int nKey, int nVar, int nOp = SKW_SET, unsigned char uchSendMessage = BV_SendMessage );
    int        GetVar( int i );

    void   Script_SetCon( int nCon, int nOp );  // 体质
    void   Script_SetStr( int nStr, int nOp );  // 力量
    void   Script_SetDex( int nDex, int nOp );  // 敏捷
    void   Script_SetInt( int nInt, int nOp );  // 智力
    void   Script_SetMgc( int nMgc, int nOp );  // 魔力
    void   Script_SetLky( int nLky, int nOp );  // 魅力
    int    Script_GetCon();                     // 体质
    int    Script_GetStr();                     // 力量
    int    Script_GetDex();                     // 敏捷
    int    Script_GetInt();                     // 智力
    int    Script_GetMgc();                     // 魔力
    int    Script_GetLky();                     // 魅力
    void   Script_SetExp( __int64 nExp, int nOp, char* szFunction, int nLine ); // 经验
    void   Script_SetSkillExp( int nExp, int nOp ); // 技能经验
    void   Script_SetHp( int nHp, int nOp );
    void   Script_SetTp( int nTp, int nOp );
    void   Script_SetMp( int nMp, int nOp );
    void   Script_SetEnergy( int nInte, int nOp );
    void   Script_SetVigor( int value, int nOp );

    void   Script_SetVigorMax( int value, int nOp );
    void   Script_SetSkillPoint( int nType, int nValue, int nOp );  // 生产生活技能点

    void   Script_SetProfession( int nProfession ); // 职业
    void   Script_SetSex( int nSex ){}
    void   Script_Skill( int iWhichSkill, int nOp );// 技能
    void   Script_SetBornPoint( DWORD dwMapID, int iPosX, int iPosY ); // 设置出生点
    int    Script_GetExp( );      // 经验
    int    Script_GetSkillExp( ); // 技能经验
    int    Script_GetHp( );    
    int    Script_GetMp( );
    bool   Script_IsThisItemEquipped( unsigned short ustItemId );
    bool   Script_IsThisSkillActived( unsigned short ustSkillItemID,unsigned short ustSkillLevel );

    bool Script_IsInArea(int Lx,int Ly,int Rx,int Ry); // 人物坐标
    int  Script_SelfPosX();
    int  Script_SelfPosY();
    void Script_DropItemOnMonsterDead(int ItemId,int ItemNum,bool nobelong = true); // 掉落道具
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