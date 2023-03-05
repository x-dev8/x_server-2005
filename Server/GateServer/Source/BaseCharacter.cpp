#include "BaseCharacter.h"
#include "FuncPerformanceLog.h"

BaseCharacter::BaseCharacter()
{
    m_stCurrentTile  = -1;
    m_dwStageID      = -1;
    m_bIsPlayer      = false;
    m_dwLastReqAlloc = 0;

    ClearCharPosInfo();
    ClearFirstID();
}

BaseCharacter::~BaseCharacter()
{
}

void BaseCharacter::ClearCharPosInfo()
{
    for (unsigned int i=0; i<MAX_CHARACTER_POS_SAVE; ++i)
    { m_CharPosInfoList[i].nID = InvalidGameObjectId;}
}

bool BaseCharacter::MakePosChangePackage(CPosChangePackage& package)
{   
    //for (unsigned int i=0; i<MAX_CHARACTER_POS_SAVE; i++)
    //{
    //    if (m_CharPosInfoList[i].nID != InvalidGameObjectId )
    //    {
    //        //如果插入消息失败了，则说明package已满，已经能制造足够量的消息了 所以可以返回true;
    //        if (!package.PushPosChangeInfo(m_CharPosInfoList[i]))
    //        {
    //            return true;
    //        }
    //    }
    //}
    //return true;

    unsigned int nCnt = 0;
    __int64 nSelfPos = m_floatX*m_floatX + m_floatY*m_floatY;

    int nCharCnt = 0;
    for (unsigned int i=0; i<MAX_CHARACTER_POS_SAVE; ++i)
    {
        if (m_CharPosInfoList[i].nID != InvalidGameObjectId)
        {
            ++nCharCnt;
        }
    }

    bool bDISCARD_VERIFY = false;
    bool bDISCARD_VEER = false;

    // 检查视野里的所有角色数量，以决定精减哪些消息
    // 减掉验证
    if (nCharCnt > DISCARD_VERIFY)
    { bDISCARD_VERIFY = true; }

    // 减掉转向
    //if (nCharCnt > DISCARD_VEER)
    //    bDISCARD_VEER = true;

    //先搜索一遍离自己近的
    for (unsigned int i=0; i<MAX_CHARACTER_POS_SAVE; i++)
    {
        if (m_CharPosInfoList[i].nID != InvalidGameObjectId)
        {
            if ((m_CharPosInfoList[i].nType == CPosChangePackage::PACK_MSG_PLAYERVERIFYPOS ||
                m_CharPosInfoList[i].nType == CPosChangePackage::PACK_MSG_UNPLAYERVERIFYPOS) && 
                bDISCARD_VERIFY)
            {
                continue;
            }

            if (m_CharPosInfoList[i].nType == CPosChangePackage::PACK_MSG_PLAYERDIR && bDISCARD_VEER)
            {
                continue;
            }

            //不需要太高的精度，所以强转成int相乘
            int nDisX = abs(int(m_CharPosInfoList[i].vPos.x-GetFloatX()));
            int nDisY = abs(int(m_CharPosInfoList[i].vPos.y-GetFloatY()));
            if ((nDisX*nDisX + nDisY*nDisY) <= NEAR_DISTANCE*NEAR_DISTANCE)
            {
                nCnt++;
                //如果插入消息失败了，则说明package已满，已经能制造足够量的消息了 所以可以返回true;
                if (!package.PushPosChangeInfo(m_CharPosInfoList[i]))
                {
                    return true;
                }
                m_CharPosInfoList[i].nID = InvalidGameObjectId;
            }
        }
    }

    //再搜索一遍离自己中等的
    for (unsigned int i=0; i<MAX_CHARACTER_POS_SAVE; i++)
    {
        if (m_CharPosInfoList[i].nID != InvalidGameObjectId )
        {
            if (m_CharPosInfoList[i].nType == CPosChangePackage::PACK_MSG_PLAYERPOS && bDISCARD_VERIFY)
            {
                continue;
            }

            if (m_CharPosInfoList[i].nType == CPosChangePackage::PACK_MSG_PLAYERDIR && bDISCARD_VEER)
            {
                continue;
            }

            //不需要太高的精度，所以强转成int相乘
            int nDisX = abs(int(m_CharPosInfoList[i].vPos.x-GetFloatX()));
            int nDisY = abs(int(m_CharPosInfoList[i].vPos.y-GetFloatY()));
            if ((nDisX*nDisX + nDisY*nDisY) <= MIDDLE_DISTANCE*MIDDLE_DISTANCE)
            {
                nCnt++;
                //如果插入消息失败了，则说明package已满，已经能制造足够量的消息了 所以可以返回true;
                if (!package.PushPosChangeInfo(m_CharPosInfoList[i]))
                {
                    return true;
                }
                m_CharPosInfoList[i].nID = InvalidGameObjectId;
            }
        }
    }

    //最后搜索一遍离自己最远的
    for (unsigned int i=0; i<MAX_CHARACTER_POS_SAVE; i++)
    {
        if (m_CharPosInfoList[i].nID != InvalidGameObjectId)
        {
            if (m_CharPosInfoList[i].nType == CPosChangePackage::PACK_MSG_PLAYERPOS && bDISCARD_VERIFY)
            {
                continue;
            }

            if (m_CharPosInfoList[i].nType == CPosChangePackage::PACK_MSG_PLAYERDIR && bDISCARD_VEER)
            {
                continue;
            }

            //不需要太高的精度，所以强转成int相乘
            int nDisX = abs(int(m_CharPosInfoList[i].vPos.x-GetFloatX()));
            int nDisY = abs(int(m_CharPosInfoList[i].vPos.y-GetFloatY()));
            if ((nDisX*nDisX + nDisY*nDisY) <= FAR_DISTANCE*FAR_DISTANCE)
            {
                nCnt++;
                //如果插入消息失败了，则说明package已满，已经能制造足够量的消息了 所以可以返回true;
                if (!package.PushPosChangeInfo(m_CharPosInfoList[i]))
                {
                    return true;
                }
                m_CharPosInfoList[i].nID = InvalidGameObjectId;
            }
        }
    }

    if (nCnt > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
uint32 BaseCharacter::FindEmptyPos( GameObjectId nID)
{
    uint32 nListEmptyPos = ErrorUnsignedLongID;
    for (unsigned int i=0; i<MAX_CHARACTER_POS_SAVE; i++)
    {
        if (m_CharPosInfoList[i].nID == InvalidGameObjectId )
        {
            nListEmptyPos = i;
        }

        if (m_CharPosInfoList[i].nID == nID)
        {
            nListEmptyPos = i;
            break;
        }
    }
    return nListEmptyPos;
}

bool BaseCharacter::AddFirstIDToList( GameObjectId nID)
{
    int nPos = -1;
    for (unsigned int i = 0; i < MAX_FIRSTID; i++)
    {
        if (m_FirstList[i] == InvalidGameObjectId)
        {
            nPos = i;
        }

        if (m_FirstList[i] == nID)
        {
            return true;
        }
    }

    if (nPos == -1)
    {
        return false;
    }
    else
    {
        m_FirstList[nPos] = nID;
        return true;
    }
}

void BaseCharacter::RemoveFirstIDFromList( GameObjectId nID )
{
    for (unsigned int i = 0; i < MAX_FIRSTID; i++)
    {
        if (m_FirstList[i] == nID)
        {
            m_FirstList[i] = InvalidGameObjectId;
            return;
        }
    }
}

bool BaseCharacter::IDIsInFirstList( GameObjectId nID )
{
    for (unsigned int i = 0; i < MAX_FIRSTID; i++)
    {
        if (m_FirstList[i] == nID)
        {
            return true;
        }
    }
    return false;
}

void BaseCharacter::ClearFirstID()
{
    for (unsigned int i = 0; i < MAX_FIRSTID; i++)
    {
        m_FirstList[i] = InvalidGameObjectId;
    }
}