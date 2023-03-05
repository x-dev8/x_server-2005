#include "Bot.h"
#include "MessageDefine.h"

#include "Bot.h"
#include "DelBot.h"

CDelBot::CDelBot(void)
{
}

CDelBot::~CDelBot(void)
{
}

void CDelBot::OnMsg_EndAckChar( Msg* pMsg )
{
    for(int i=0;i<3;i++)
    {
        if(m_vCharacterID[i] != 0)
        {
            MsgDeleteChar del;
            del.stWhichSlot = i;
            SendMsg(&del);
        }
    }
}
