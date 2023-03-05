#include "SystemMail.h"

CSystemMail::CSystemMail(void)
{
    m_FilterType = MailFilter_ALL;
}

CSystemMail::~CSystemMail(void)
{
    Clear();
}

bool CSystemMail::IsHaveMoney(uint32 uMailID)
{
    int nSize = m_VecMail.size();
    for (int n = nSize - 1; n >= 0;--n)
    {
        if(m_VecMail[n].id == uMailID)
        {
            if(m_VecMail[n].money > 0)	
                return true;
        }
    }

    return false;
}

bool CSystemMail::IsHaveItem(uint32  uMailID)
{
    if(uMailID < 0)
        return false;

    int nSize = m_VecMail.size();
    for (int n = nSize - 1; n >= 0;--n)
    {
        if(m_VecMail[n].id == uMailID)
        {
            if(m_VecMail[n].accessory.type == SMail::EAT_Item)
                return true;
        }
    }

    return false;
}

const char* CSystemMail::GetMailTitle(uint32 uMailID)
{
    if(uMailID < 0)
        return NULL;

    int nSize = m_VecMail.size();
    for (int n = nSize - 1; n >= 0;--n)
    {
        if(m_VecMail[n].id == uMailID)
            return m_VecMail[n].title;
    }

    return NULL;
}

const char* CSystemMail::GetMailSender(uint32 uMailID)
{
    if(uMailID < 0)
        return NULL;

    int nSize = m_VecMail.size();
    for (int n = nSize - 1; n >= 0;--n)
    {
        if(m_VecMail[n].id == uMailID)
            return m_VecMail[n].owners[EM_FromIndex].addressName;
    }

    return NULL;
}

const char* CSystemMail::GetMailContent(uint32 uMailID)
{
    if(uMailID < 0)
        return NULL;

    int nSize = m_VecMail.size();
    for (int n = nSize - 1; n >= 0;--n)
    {
        if(m_VecMail[n].id == uMailID)
            return m_VecMail[n].content;
    }

    return NULL;
}

void  CSystemMail::UpdateMailByID(uint32 uMailID,SMail &mail)
{
    if(uMailID < 0)
        return;

    int nSize = m_VecMail.size();
    for (int n = nSize -1; n >= 0;--n)
    {
        if(m_VecMail[n].id == uMailID)
        {
            SMail *pMail = &m_VecMail[n];
            if(pMail)
            {
                memcpy(pMail,&mail,sizeof(SMail));
                break;
            }
        }
    }
}

void  CSystemMail::Clear()
{
    m_VecMail.clear();
    m_vecFilterMail.clear();
}

void CSystemMail::AddMail(SMail& mail)
{
    m_VecMail.push_back(mail);
}

void CSystemMail::DeleteByID(uint32 uID)
{
    std::vector<SMail>::iterator it = m_VecMail.begin();
    std::vector<SMail>::iterator itEnd = m_VecMail.end();

    for (;it != itEnd;++it)
    {
        if((*it).id == uID)
        {
            m_VecMail.erase(it);
            break;
        }
    }
}

void CSystemMail::DeleteByTime(__int64 dwTime)
{
    std::vector<SMail>::iterator iter = m_VecMail.begin();
    for(;iter != m_VecMail.end();)
    {
        SMail mail = *iter;
        if(mail.sendTime > dwTime)
            iter = m_VecMail.erase(iter);
        else
            ++iter;
    }
}

void CSystemMail::FilterMail(MailFilter filterType)
{
    if(m_VecMail.size() <= 0)
        return;

    m_vecFilterMail.clear();

    m_FilterType = filterType;
    int nSize = m_VecMail.size();
    for (int n = nSize - 1;n >= 0; --n)
    {
        switch(m_FilterType)
        {
        case MailFilter_ALL:
            {
                m_vecFilterMail.push_back(n);
            }
            break;
        case MailFlter_Player:
            {
                if(m_VecMail[n].type == SMail::EMT_Player)
                    m_vecFilterMail.push_back(n);
            }
            break;
        case MailFilter_System:
            {
                if(m_VecMail[n].type == SMail::EMT_System)
                   m_vecFilterMail.push_back(n);
            }
            break;
        case MailFilter_Read:
            {
                if(m_VecMail[n].state != SMail::EMS_NotOpen)
                    m_vecFilterMail.push_back(n);
            }
            break;
        case MailFilter_NoRead:
            {
                if(m_VecMail[n].state == SMail::EMS_NotOpen)
                    m_vecFilterMail.push_back(n);
            }
            break;
        case MailFilter_Addtriad:
            {
                if((m_VecMail[n].state != SMail::EMS_HaveGetItem&&m_VecMail[n].accessory.type != SMail::EAT_None)
                    ||m_VecMail[n].money > 0)
                    m_vecFilterMail.push_back(n);
            }
            break;
        }
    }
}

SMail* CSystemMail::ReadMail(int nIndex)
{
    if(nIndex < 0 || nIndex >= m_vecFilterMail.size())
    {
        assert(0&&"数组越界");
        return NULL;
    }

    if(m_VecMail.size() <= 0)
        return NULL;

    int nCount = m_vecFilterMail[nIndex];
    if(nCount < 0 || nCount >= m_VecMail.size())
    {
        assert(0&&"数组越界");
        return NULL;
    }
    return &m_VecMail[nCount];
}

bool CSystemMail::RefreshReadStateByID(uint32 uMailID)
{
    if(uMailID < 0)
        return false;

    int nSize = m_VecMail.size();
    for (int n = nSize -1; n >= 0;--n)
    {
        if(m_VecMail[n].id == uMailID)
        {
            SMail *pMail = &m_VecMail[n];
            if(pMail)
            {
                pMail->state = SMail::EMS_Open;
                return true;
            }
        }
    }
    return false;
}

bool CSystemMail::RefreshMoneyByID(uint32 uMailID)
{
    if(uMailID < 0)
        return false;

    int nSize = m_VecMail.size();
    for (int n = nSize -1; n >= 0;--n)
    {
        if(m_VecMail[n].id == uMailID)
        {
            SMail *pMail = &m_VecMail[n];
            if(pMail)
            {
                pMail->money = 0;
                return true;
            }
        }
    }

    return false;
}

bool CSystemMail::RefreshItemByID(uint32 uMailID)
{
    if(uMailID < 0)
        return false;

    int nSize = m_VecMail.size();
    for (int n = nSize -1; n >= 0;--n)
    {
        if(m_VecMail[n].id == uMailID)
        {
            SMail *pMail = &m_VecMail[n];
            if(pMail)
            {
                pMail->accessory.type = SMail::EAT_None;
                pMail->state = SMail::EMS_HaveGetItem;
                return true;
            }
        }
    }

    return false;
}

bool CSystemMail::IsHaveNewMail()
{
    int nSize = m_VecMail.size();
    for (int n = nSize -1; n >= 0;--n)
    {
        SMail *pMail = &m_VecMail[n];
        if(!pMail)
            continue;

        if(pMail->state == SMail::EMS_NotOpen)
            return true;        
    }

    return false;
}
