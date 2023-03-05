#include "EnterMySightPackage.h"
#include "zlib/zlib.h"

const unsigned int NEED_COMPRESS_SIZE = 50; // 数据包超过这个长度就进行压缩

CEnterMySightPackage::CEnterMySightPackage()
{
}

CEnterMySightPackage::~CEnterMySightPackage()
{
}

bool CEnterMySightPackage::MakePackMsg(MsgEnterMySightPack& msg)
{
    if (m_list.size()*sizeof(MsgPlayerEnterMySight) > sizeof(msg.szBuff))
    {
        return false;
    }

    msg.nCharNum = m_list.size();
    msg.nIsCompress = 0;
    
    static unsigned char szBuff[MsgEnterMySightPack::MAX_CHARACTER*sizeof(MsgPlayerEnterMySight)*2];
    unsigned int nDestSize = sizeof(szBuff);

    if (m_list.size()*sizeof(MsgPlayerEnterMySight) >= NEED_COMPRESS_SIZE)
    {
        compress((Bytef*)szBuff, (uLongf*)&nDestSize, (const Bytef*)&m_list[0], m_list.size()*sizeof(MsgPlayerEnterMySight));
        if (nDestSize < m_list.size()*sizeof(MsgPlayerEnterMySight))
        {
            msg.nIsCompress = 1;
        }
    }

    if (msg.nIsCompress == 1)
    {
        memcpy(msg.szBuff, szBuff, min(sizeof(msg.szBuff), nDestSize));
        msg.header.stLength = sizeof(msg) - sizeof(msg.szBuff) + min(nDestSize, sizeof(msg.szBuff));
        return true;
    }
    else
    {
        memcpy(msg.szBuff, &m_list[0], min(m_list.size()*sizeof(MsgPlayerEnterMySight), sizeof(msg.szBuff)));
        msg.header.stLength = sizeof(msg) - sizeof(msg.szBuff) + min(m_list.size()*sizeof(MsgPlayerEnterMySight), sizeof(msg.szBuff));
        return true;
    }
}

bool CEnterMySightPackage::LoadPackMsg(MsgEnterMySightPack& msg)
{
    if (msg.nCharNum > MsgEnterMySightPack::MAX_CHARACTER)
    {
        return false;
    }
    m_list.resize(msg.nCharNum);

    static unsigned char szBuff[MsgEnterMySightPack::MAX_CHARACTER*sizeof(MsgPlayerEnterMySight)*2];
    unsigned int nDestSize = sizeof(szBuff);

    if (msg.nIsCompress == 1)
    {
        uncompress((Bytef*)szBuff, (uLongf*)&nDestSize, (const Bytef*)msg.szBuff, msg.GetLength()-(sizeof(msg)-sizeof(msg.szBuff)));
        memcpy(&m_list[0], szBuff, min(m_list.size()*sizeof(MsgPlayerEnterMySight), nDestSize));
        return true;
    }
    else
    {
        memcpy(&m_list[0], msg.szBuff, min(m_list.size()*sizeof(MsgPlayerEnterMySight), msg.GetLength()-(sizeof(msg)-sizeof(msg.szBuff))));
        return true;
    }
}

MsgPlayerEnterMySight* CEnterMySightPackage::PopEnterMySight()
{
    if (m_list.empty())
    {
        return NULL;
    }
    else
    {
        static MsgPlayerEnterMySight msg;
        msg = m_list.back();
        m_list.pop_back();
        return &msg;
    }
}

bool CEnterMySightPackage::PushEnterMySight(MsgPlayerEnterMySight& msg)
{
    if (m_list.size() >= MsgEnterMySightPack::MAX_CHARACTER)
    {
        return false;
    }
    m_list.push_back(msg);
    return true;
}

void CEnterMySightPackage::Clear()
{
    m_list.clear();
}

bool CEnterMySightPackage::IsEmpty() const
{
    return m_list.empty();
}