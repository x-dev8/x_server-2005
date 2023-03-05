#ifndef __GM_CONSTROL_H__
#define __GM_CONSTROL_H__

#include <string>

class GamePlayer;

class GmControl
{
public:
    enum RESULT_CODE
    {
        RC_SUCCESS,
        RC_PARAM_ERROR,
        RC_NOT_FIND_CHAR,
    };
       
    enum GM_PERMISSION
    {   
        GP_FLYTOMAP       = 1<<0,
        GP_BECKONPLAYER   = 1<<1,
        GP_FLYTOPLAYER    = 1<<2,
        GP_KILLTARGET     = 1<<3,
        GP_SUNMMONMONSTER = 1<<4,
        GP_BULL           = 1<<5,
        GP_SHOWPOS        = 1<<6,

        GP_SETADDEXP      = 1<<7,
        GP_NPCLIST        = 1<<8,
        GP_CREATEGUILD    = 1<<9,
        GP_LEARNSKILL     = 1<<10,
        GP_ADDITEM        = 1<<11,

        GP_IAMGOD         = 1<<12,
        GP_SETMONEY       = 1<<13,
        GP_ADDEXP         = 1<<14,
        GP_CAPTURE        = 1<<15,
        GP_ADDSKILLEXP    = 1<<16,

        GP_GETYUANBAO     = 1<<17,
        GP_UPDATEYUANBAO  = 1<<18,  
        GP_KICKCHAR       = 1<<19,        
        
        GP_LOW     = GP_FLYTOMAP + GP_BECKONPLAYER + GP_FLYTOPLAYER + GP_KILLTARGET + GP_BULL + GP_SHOWPOS,
        GP_MEDIUN  = GP_LOW + GP_SETADDEXP +  GP_NPCLIST + GP_CREATEGUILD + GP_LEARNSKILL + GP_ADDITEM,
        GP_HIGH    = GP_MEDIUN + GP_IAMGOD + GP_SETMONEY + GP_ADDEXP + GP_CAPTURE + GP_ADDSKILLEXP,
        GP_HIGHEST = GP_HIGH + GP_GETYUANBAO + GP_UPDATEYUANBAO,
    };

    static GmControl& getIns() 
    {
        static GmControl instance;
        return instance;
    }
    
    // 游戏世界中角色GM
    long gameWorldGmCommand( GamePlayer* pGameGm, const char* szCommand );

    // 游戏服务器GM
    long gameServerGmCommand( const char* szCommand );

protected:
    long _changeGameWorldGmPermission( const std::string& strName, unsigned int uiPermission );

private:
    explicit GmControl();

    explicit GmControl( const GmControl& );

    const GmControl& operator=( const GmControl& );
};

#endif // __GM_CONSTROL_H__
