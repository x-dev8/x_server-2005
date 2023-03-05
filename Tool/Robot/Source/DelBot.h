#pragma once

class CDelBot : public BaseRobot
{
public:
    CDelBot(void);
public:
    virtual ~CDelBot(void);

    void OnMsg_EndAckChar( Msg* pMsg );
};
