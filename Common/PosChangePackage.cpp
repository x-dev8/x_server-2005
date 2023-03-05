#include "PosChangePackage.h"
#include "zlib/zlib.h"

const unsigned int NEED_COMPRESS_SIZE = 50; //数据包超过这个长度就进行压缩

CPosChangePackage::CPosChangePackage()
{
    m_nMaxSize = MsgPosChange::MAX_CHARACTER;
}

CPosChangePackage::~CPosChangePackage()
{
}

bool CPosChangePackage::LoadPackMsg(MsgPosChange &msg)
{
    Clear();
    if (msg.nCharNum > MsgPosChange::MAX_CHARACTER)
    {
        return false;
    }

    unsigned int nDataLength;
    static char sBuffer[MsgPosChange::MAX_CHARACTER*sizeof(SMoveUnitHead) + MsgPosChange::MAX_CHARACTER*40];
    uLongf destsize = sizeof(sBuffer);
    if (msg.nIsCompress == 1)
    {
        uncompress((Bytef*)sBuffer, &destsize, (const Bytef*)msg.szBuff, sizeof(msg.szBuff) - (sizeof(MsgPosChange)-msg.GetLength()));
        if (destsize <= msg.nCharNum*sizeof(SMoveUnitHead))
        {
            return false;
        }
        nDataLength = (destsize - (msg.nCharNum*sizeof(SMoveUnitHead)));
    }
    else
    {
        unsigned int nMsgLength = sizeof(msg.szBuff) - (sizeof(MsgPosChange)-msg.GetLength());
        if (nMsgLength <= msg.nCharNum*sizeof(SMoveUnitHead))
        {
            return false;
        }
        nDataLength = (nMsgLength - msg.nCharNum*sizeof(SMoveUnitHead));
        memcpy(sBuffer, msg.szBuff, nMsgLength);
    }

    SMoveUnitHead* pHead = (SMoveUnitHead*)sBuffer;
    char* szData = &sBuffer[msg.nCharNum*sizeof(SMoveUnitHead)];
    unsigned int nPos = 0;

    for (unsigned int i=0; i<msg.nCharNum; i++)
    {
        SPosChangeInfo info;
        info.nID        = pHead[i].shID;
        info.nType      = pHead[i].chType;
        info.chOptimize = pHead[i].chOptimize;
        
        switch (info.nType)
        {
        case PACK_MSG_PLAYERMOVINGPOS:
            {
                if (nPos + sizeof(tagPACK_MSG_PLAYERMOVINGPOS) > nDataLength)
                {
                    return false;
                }
                tagPACK_MSG_PLAYERMOVINGPOS* p = (tagPACK_MSG_PLAYERMOVINGPOS*)&szData[nPos];
                info.vPos = p->vPos;
                nPos += sizeof(tagPACK_MSG_PLAYERMOVINGPOS);
            }
            break;
        case PACK_MSG_PLAYERMOVINGPOSANDDIR:
            {
                if (nPos + sizeof(tagPACK_MSG_PLAYERMOVINGPOSANDDIR) > nDataLength)
                {
                    return false;
                }
                tagPACK_MSG_PLAYERMOVINGPOSANDDIR* p = (tagPACK_MSG_PLAYERMOVINGPOSANDDIR*)&szData[nPos];
                info.chDirX = p->chDirX;
                info.chDirY = p->chDirY;
                info.chDirZ = p->chDirZ;
                info.vPos = p->vPos;
                nPos += sizeof(tagPACK_MSG_PLAYERMOVINGPOSANDDIR);
            }
            break;
        case PACK_MSG_PLAYERPOS:
            {
                if (nPos + sizeof(tagPACK_MSG_PLAYERPOS) > nDataLength)
                {
                    return false;
                }
                tagPACK_MSG_PLAYERPOS* p = (tagPACK_MSG_PLAYERPOS*)&szData[nPos];
                info.vPos = p->vPos;
                nPos += sizeof(tagPACK_MSG_PLAYERPOS);
            }
            break;
        case PACK_MSG_PLAYERDIR:
            {
                if (nPos + sizeof(tagPACK_MSG_PLAYERDIR) > nDataLength)
                {
                    return false;
                }
                tagPACK_MSG_PLAYERDIR* p = (tagPACK_MSG_PLAYERDIR*)&szData[nPos];
                info.chDirX = p->chDirX;
                info.chDirY = p->chDirY;
                info.chDirZ = p->chDirZ;
                nPos += sizeof(tagPACK_MSG_PLAYERDIR);
            }
            break;
        case PACK_MSG_PLAYERPOSANDDIR:
            {
                if (nPos + sizeof(tagPACK_MSG_PLAYERPOSANDDIR) > nDataLength)
                {
                    return false;
                }
                tagPACK_MSG_PLAYERPOSANDDIR* p = (tagPACK_MSG_PLAYERPOSANDDIR*)&szData[nPos];
                info.chDirX = p->chDirX;
                info.chDirY = p->chDirY;
                info.chDirZ = p->chDirZ;
                info.vPos = p->vPos;
                nPos += sizeof(tagPACK_MSG_PLAYERPOSANDDIR);
            }
            break;
        case PACK_MSG_PLAYERVERIFYPOS:
            {
                if (nPos + sizeof(tagPACK_MSG_PLAYERVERIFYPOS) > nDataLength)
                {
                    return false;
                }
                tagPACK_MSG_PLAYERVERIFYPOS* p = (tagPACK_MSG_PLAYERVERIFYPOS*)&szData[nPos];
                info.vPos = p->vPos;
                nPos += sizeof(tagPACK_MSG_PLAYERVERIFYPOS);
            }
            break;
        case PACK_MSG_UNPLAYERMOVINGTOPOS:
            {
                if (nPos + sizeof(tagPACK_MSG_UNPLAYERMOVINGTOPOS) > nDataLength)
                {
                    return false;
                }
                tagPACK_MSG_UNPLAYERMOVINGTOPOS* p = (tagPACK_MSG_UNPLAYERMOVINGTOPOS*)&szData[nPos];
                info.vPos = p->vStartPos;
                info.vEndPos = p->vEndPos;
                nPos += sizeof(tagPACK_MSG_UNPLAYERMOVINGTOPOS);
            }
            break;
        case PACK_MSG_UNPLAYERVERIFYPOS:
            {
                if (nPos + sizeof(tagPACK_MSG_UNPLAYERVERIFYPOS) > nDataLength)
                {
                    return false;
                }
                tagPACK_MSG_UNPLAYERVERIFYPOS* p = (tagPACK_MSG_UNPLAYERVERIFYPOS*)&szData[nPos];
                info.chDirX = p->chDirX;
                info.chDirY = p->chDirY;
                info.chDirZ = p->chDirZ;
                info.vPos = p->vPos;
                nPos += sizeof(tagPACK_MSG_UNPLAYERVERIFYPOS);
            }
            break;
        case PACK_MSG_UNPLAYERCLOSINGTOLOCKTARGET:
            {
                if (nPos + sizeof(tagPACK_MSG_UNPLAYERCLOSINGTOLOCKTARGET) > nDataLength)
                {
                    return false;
                }
                tagPACK_MSG_UNPLAYERCLOSINGTOLOCKTARGET* p = (tagPACK_MSG_UNPLAYERCLOSINGTOLOCKTARGET*)&szData[nPos];
                info.vPos = p->vPos;
                info.nTargetID = p->shTargetID;
                nPos += sizeof(tagPACK_MSG_UNPLAYERCLOSINGTOLOCKTARGET);
            }
            break;
        default:
            break;
        }
        m_msglist.push_back(info);
    }

    return true;
}

bool CPosChangePackage::MakePackMsg(MsgPosChange &msg)
{
    if (m_msglist.empty())
        return false;

    int nSize       = m_msglist.size();
    msg.nCharNum    = nSize;
    static SMoveUnitHead sHead[MsgPosChange::MAX_CHARACTER];
    const unsigned int nsBufferSize = MsgPosChange::MAX_CHARACTER*40;
    static char sBuffer[nsBufferSize]; // 为每个消息留40个字节的数据
    unsigned int nPos = 0;

    msg.nIsCompress = 0;
    for (unsigned int i = 0; i < nSize; ++i)
    {
        SPosChangeInfo& info = m_msglist[i];
        sHead[i].chType     = info.nType;
        sHead[i].shID       = info.nID;
        sHead[i].chOptimize = info.chOptimize;
        switch (info.nType)
        {
        case PACK_MSG_PLAYERMOVINGPOS:
            {
                if (nPos + sizeof(tagPACK_MSG_PLAYERMOVINGPOS) > nsBufferSize)
                {
                    return false;
                }
                tagPACK_MSG_PLAYERMOVINGPOS* p = (tagPACK_MSG_PLAYERMOVINGPOS*)&sBuffer[nPos];
                p->vPos = info.vPos;
                nPos += sizeof(tagPACK_MSG_PLAYERMOVINGPOS);
            }
            break;
        case PACK_MSG_PLAYERMOVINGPOSANDDIR:
            {
                if (nPos + sizeof(tagPACK_MSG_PLAYERMOVINGPOSANDDIR) > nsBufferSize)
                {
                    return false;
                }
                tagPACK_MSG_PLAYERMOVINGPOSANDDIR* p = (tagPACK_MSG_PLAYERMOVINGPOSANDDIR*)&sBuffer[nPos];
                p->chDirX = info.chDirX;
                p->chDirY = info.chDirY;
                p->chDirZ = info.chDirZ;
                p->vPos = info.vPos;
                nPos += sizeof(tagPACK_MSG_PLAYERMOVINGPOSANDDIR);
            }
            break;
        case PACK_MSG_PLAYERPOS:
            {
                if (nPos + sizeof(tagPACK_MSG_PLAYERPOS) > nsBufferSize)
                {
                    return false;
                }
                tagPACK_MSG_PLAYERPOS* p = (tagPACK_MSG_PLAYERPOS*)&sBuffer[nPos];
                p->vPos = info.vPos;
                nPos += sizeof(tagPACK_MSG_PLAYERPOS);
            }
            break;
        case PACK_MSG_PLAYERDIR:
            {
                if (nPos + sizeof(tagPACK_MSG_PLAYERDIR) > nsBufferSize)
                {
                    return false;
                }
                tagPACK_MSG_PLAYERDIR* p = (tagPACK_MSG_PLAYERDIR*)&sBuffer[nPos];
                p->chDirX = info.chDirX;
                p->chDirY = info.chDirY;
                p->chDirZ = info.chDirZ;
                nPos += sizeof(tagPACK_MSG_PLAYERDIR);
            }
            break;
        case PACK_MSG_PLAYERPOSANDDIR:
            {
                if (nPos + sizeof(tagPACK_MSG_PLAYERPOSANDDIR) > nsBufferSize)
                {
                    return false;
                }
                tagPACK_MSG_PLAYERPOSANDDIR* p = (tagPACK_MSG_PLAYERPOSANDDIR*)&sBuffer[nPos];
                p->chDirX = info.chDirX;
                p->chDirY = info.chDirY;
                p->chDirZ = info.chDirZ;
                p->vPos = info.vPos;
                nPos += sizeof(tagPACK_MSG_PLAYERPOSANDDIR);
            }
            break;
        case PACK_MSG_PLAYERVERIFYPOS:
            {
                if (nPos + sizeof(tagPACK_MSG_PLAYERVERIFYPOS) > nsBufferSize)
                {
                    return false;
                }
                tagPACK_MSG_PLAYERVERIFYPOS* p = (tagPACK_MSG_PLAYERVERIFYPOS*)&sBuffer[nPos];
                p->vPos = info.vPos;
                nPos += sizeof(tagPACK_MSG_PLAYERVERIFYPOS);
            }
            break;
        case PACK_MSG_UNPLAYERMOVINGTOPOS:
            {
                if (nPos + sizeof(tagPACK_MSG_UNPLAYERMOVINGTOPOS) > nsBufferSize)
                {
                    return false;
                }
                tagPACK_MSG_UNPLAYERMOVINGTOPOS* p = (tagPACK_MSG_UNPLAYERMOVINGTOPOS*)&sBuffer[nPos];
                p->vStartPos = info.vPos;
                p->vEndPos = info.vEndPos;
                nPos += sizeof(tagPACK_MSG_UNPLAYERMOVINGTOPOS);
            }
            break;
        case PACK_MSG_UNPLAYERVERIFYPOS:
            {
                if (nPos + sizeof(tagPACK_MSG_UNPLAYERVERIFYPOS) > nsBufferSize)
                {
                    return false;
                }
                tagPACK_MSG_UNPLAYERVERIFYPOS* p = (tagPACK_MSG_UNPLAYERVERIFYPOS*)&sBuffer[nPos];
                p->chDirX = info.chDirX;
                p->chDirY = info.chDirY;
                p->chDirZ = info.chDirZ;
                p->vPos = info.vPos;
                nPos += sizeof(tagPACK_MSG_UNPLAYERVERIFYPOS);
            }
            break;
        case PACK_MSG_UNPLAYERCLOSINGTOLOCKTARGET:
            {
                if (nPos + sizeof(tagPACK_MSG_UNPLAYERCLOSINGTOLOCKTARGET) > nsBufferSize)
                {
                    return false;
                }
                tagPACK_MSG_UNPLAYERCLOSINGTOLOCKTARGET* p = (tagPACK_MSG_UNPLAYERCLOSINGTOLOCKTARGET*)&sBuffer[nPos];
                p->vPos = info.vPos;
                p->shTargetID = info.nTargetID;
                nPos += sizeof(tagPACK_MSG_UNPLAYERCLOSINGTOLOCKTARGET);
            }
            break;
        default:
            break;
        }
    }

    const unsigned int MAXSIZE = nsBufferSize + MsgPosChange::MAX_CHARACTER*sizeof(SMoveUnitHead);
    static char szTmpBuff[ MAXSIZE ] = {0};
    static char szCompressTmpBuff[ MAXSIZE * 2] = {0}; // 给压缩的buffer两倍长度

    //把数据包添完后进行长度判断，判断是否需要压缩
    unsigned int nMsgSize = nPos + sizeof(SMoveUnitHead)*nSize;
    uLongf destsize = MAXSIZE*2; 
    uLongf srcsize = nMsgSize;

    if (nMsgSize >= NEED_COMPRESS_SIZE)
    { // 在这里进行压缩 先集合在一个buffer内再压缩
        memcpy_s( szTmpBuff, sizeof(szTmpBuff), sHead, nSize*sizeof(SMoveUnitHead) );
        memcpy_s( &szTmpBuff[nSize*sizeof(SMoveUnitHead)], sizeof(szTmpBuff), sBuffer, nPos);
        compress((Bytef*)szCompressTmpBuff, &destsize, (const Bytef*)szTmpBuff, srcsize);
        
        //在这里判断一下压缩后的长度 如果大于未压缩的长度，就不启用压缩
        if (destsize < nMsgSize)
        {
            msg.nIsCompress = 1;
        }
    }

    if (msg.nIsCompress == 1)
    {
        if (sizeof(msg.szBuff) < destsize)
            return false;

        memcpy_s(msg.szBuff, sizeof(msg.szBuff), szCompressTmpBuff, destsize);
        msg.header.stLength = sizeof(MsgPosChange)-sizeof(msg.szBuff)+destsize;
        return true;
    }
    else
    {
        if (sizeof(msg.szBuff) < nMsgSize)
            return false;

        memcpy_s(msg.szBuff, sizeof(msg.szBuff), sHead, nSize*sizeof(SMoveUnitHead));
        memcpy_s(&msg.szBuff[nSize*sizeof(SMoveUnitHead)], sizeof(msg.szBuff), sBuffer, nPos);
        msg.header.stLength = sizeof(MsgPosChange)-sizeof(msg.szBuff)+nMsgSize;
        return true;
    }
    return true;
}

bool CPosChangePackage::PushPosChangeInfo( const SPosChangeInfo& info)
{
    if (m_msglist.size() >= m_nMaxSize)
        return false;

    m_msglist.push_back(info);
    return true;
}


SPosChangeInfo* CPosChangePackage::PopPosChangeInfo()
{
    if (m_msglist.empty())
    {
        return NULL;
    }
    static SPosChangeInfo posinfo;
    posinfo = m_msglist.back();
    m_msglist.pop_back();
    return &posinfo;
}

void CPosChangePackage::SetMaxSize(unsigned int nSize)
{
    if (nSize > MsgPosChange::MAX_CHARACTER)
        nSize = MsgPosChange::MAX_CHARACTER;
    m_nMaxSize = nSize;
}

void CPosChangePackage::Clear()
{
    m_msglist.clear();
}