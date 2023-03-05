#include "CommondBot.h"


CommondBot::CommondBot()
:IsReplaceCommond(false),
CurRunnTime(HQ_TimeGetTime()),
AutoMove(false)
{
    //m_BotType = Bot_Commond;
    CurRunItr = _CommondStructs.begin();
}

CommondBot::~CommondBot()
{

}

void CommondBot::InitPlayGame()
{
    BaseRobot::InitPlayGame();
}

void CommondBot::PlayGame()
{
    BaseRobot::PlayGame();

    if (IsReplaceCommond)
    {
        IsReplaceCommond = false;
        CurRunItr = _CommondStructs.begin();
        return;
    }

    DWORD PlayGameTime = HQ_TimeGetTime();
    RunOperation(PlayGameTime);

    if (++CurRunItr == _CommondStructs.end())
        CurRunItr = _CommondStructs.begin();

    PlayGameTime = HQ_TimeGetTime() - PlayGameTime;
}

void CommondBot::RunOperation(DWORD time)
{
    // ��鵱ǰִ�е�ָ��ʱ���Ƿ����û����ᣬ����ִ��
    // CurRunItr
    // ִ������ȡ�¸�ָ��,���û��ָ����
}

void CommondBot::AddCommond(const CommondBot::CommondStruct &CommondStruct_)
{
    ItrCommondStructContainer Itr = find(_CommondStructs.begin(),_CommondStructs.end(),CommondStruct_);
    if (Itr == _CommondStructs.end())
    {
        // addcomm
        _CommondStructs.push_back(CommondStruct_);
    }
}

void CommondBot::SubCommond(const CommondBot::CommondStruct &CommondStruct_)
{
    ItrCommondStructContainer Itr = find(_CommondStructs.begin(),_CommondStructs.end(),CommondStruct_);
    if (Itr != _CommondStructs.end())
    {
        _CommondStructs.erase(Itr);
    }
}