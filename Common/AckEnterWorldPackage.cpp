#include "AckEnterWorldPackage.h"
#include "zlib/zlib.h"

CAckEnterWorldPackage::CAckEnterWorldPackage()
{
}

CAckEnterWorldPackage::~CAckEnterWorldPackage()
{
}

MsgAckEnterWorldPack* CAckEnterWorldPackage::MakePackageMsg(MsgAckEnterWorld& msg)
{
    static unsigned char szBuff[sizeof(msg)*2];
    unsigned int nDstSize = sizeof(szBuff);
    compress((Bytef*)szBuff, (uLongf*)&nDstSize, (const Bytef*)&msg, (uLong)sizeof(MsgAckEnterWorld));
    if (nDstSize < sizeof(MsgAckEnterWorld) && nDstSize < sizeof(m_pack.szBuff))
    {
        memcpy(m_pack.szBuff, szBuff, nDstSize);
        m_pack.header.stLength = sizeof(m_pack) - sizeof(m_pack.szBuff) + nDstSize;
        return &m_pack;
    }
    return NULL;
}

MsgAckEnterWorld* CAckEnterWorldPackage::UnPackageMsg(MsgAckEnterWorldPack& msg)
{
    unsigned int nDstSize = sizeof(m_msg);
    uncompress((Bytef*)&m_msg, (uLongf*)&nDstSize, (const Bytef*)msg.szBuff, (uLong)sizeof(msg.szBuff) + (sizeof(msg) - msg.GetLength()));
    if (nDstSize == sizeof(m_msg))
    {
        return &m_msg;
    }
    else
    {
        return NULL;
    }
}
