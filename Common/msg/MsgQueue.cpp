#include "MsgQueue.h"

Common::TAllocator<unsigned char, MSGMAXSIZE, 200> MsgQueue::s_theMsgMemAllocator;
Common::TAllocator<unsigned char, MSGMAXSIZE, 200> MsgQueueNotLock::s_theMsgMemAllocator;

MsgQueueNotLock::MsgQueueNotLock()
{
	//m_listAdditional.clear();
	m_iSize = 0;
}

MsgQueueNotLock::~MsgQueueNotLock()
{
	Clear();
}

bool MsgQueueNotLock::PushMsg( Msg* pMsg, uint8 encryptMode)
{
	if (pMsg == NULL || pMsg->GetLength() <= 0 || pMsg->GetLength() > MSGMAXSIZE)
	{
		assert(false);
		return false;
	}

	unsigned char* pBlock = /*msgpool.*/s_theMsgMemAllocator.allocate(pMsg->GetLength());
	memcpy(pBlock, pMsg, pMsg->GetLength());

	/*CSALocker locker(this);*/
	m_listAdditional.push_back(pBlock);

	m_iSize ++;
	return true;
}

bool MsgQueueNotLock::PeekMsg( Msg* pMsg, uint32 stSize)
{
	if (m_listAdditional.empty())
	{
		return false;
	}

	unsigned char* pBlock;

	{
		//CSALocker locker(this);
		if (m_listAdditional.empty())
		{
			return false;
		}
		pBlock = m_listAdditional.front();
	}

	Msg* pListMsg = (Msg*)pBlock;

	if (pListMsg->GetLength() > stSize || pListMsg->GetLength() <= 0)
	{
		return false;
	}

	memcpy(pMsg, pBlock, pListMsg->GetLength());
	return true;
}

bool MsgQueueNotLock::PopMsg ( Msg* pMsg, uint32 stSize)
{
	unsigned char* pBlock;
	Msg* pListMsg;

	if (m_listAdditional.empty())
	{
		return false;
	}

	{
		//CSALocker locker(this);

		//再次判断
		if (m_listAdditional.empty())
		{
			return false;
		}

		pBlock = m_listAdditional.front();
		pListMsg = (Msg*)pBlock;
		if (pListMsg->GetLength() > stSize || pListMsg->GetLength() <= 0)
		{
			return false;
		}

		m_listAdditional.pop_front();
		m_iSize --;
	}

	memcpy(pMsg, pBlock, pListMsg->GetLength());
	/*msgpool.*/s_theMsgMemAllocator.deallocate(pBlock);

	return true;
}

void MsgQueueNotLock::Clear(void)
{
	//guardfunc;
	//CSALocker locker(this);
	while( !m_listAdditional.empty()  )
	{	
		unsigned char* pBlock = m_listAdditional.back();
		/*msgpool.*/s_theMsgMemAllocator.deallocate(pBlock);
		m_listAdditional.pop_back();
	}
	m_iSize = 0;
	//unguard;
}

MsgQueue::MsgQueue() : m_iSize(0)
{
}

MsgQueue::~MsgQueue(void)
{
	Clear();
}

bool MsgQueue::PushMsg(Msg* pMsg,uint8 encryptMode)
{
	//guardfunc;
	if (pMsg == NULL || pMsg->GetLength() <= 0 || pMsg->GetLength() > MSGMAXSIZE)
	{
		assert(false);
		return false;
	}

	unsigned char* pBlock = /*msgpool.*/s_theMsgMemAllocator.allocate(pMsg->GetLength());
	memcpy(pBlock, pMsg, pMsg->GetLength());

	CSALocker locker(this);
	m_listAdditional.push_back(pBlock);

	m_iSize ++;
	return true;
	//unguard;
}

bool MsgQueue::PeekMsg(Msg* pMsg, uint32 stSize)
{
	//guardfunc;

	if (m_listAdditional.empty())
	{
		return false;
	}

	unsigned char* pBlock;

	{
		CSALocker locker(this);
		if (m_listAdditional.empty())
		{
			return false;
		}
		pBlock = m_listAdditional.front();
	}

	Msg* pListMsg = (Msg*)pBlock;

	if (pListMsg->GetLength() > stSize || pListMsg->GetLength() <= 0)
	{
		return false;
	}

	memcpy(pMsg, pBlock, pListMsg->GetLength());
	return true;
	//unguard;
}

bool MsgQueue::PopMsg(Msg*pMsg, uint32 stSize)
{
	//guardfunc;
	unsigned char* pBlock;
	Msg* pListMsg;

	if (m_listAdditional.empty())
	{
		return false;
	}

	{
		CSALocker locker(this);

		//再次判断
		if (m_listAdditional.empty())
		{
			return false;
		}

		pBlock = m_listAdditional.front();
		pListMsg = (Msg*)pBlock;
		if (pListMsg->GetLength() > stSize || pListMsg->GetLength() <= 0)
		{
			return false;
		}

		m_listAdditional.pop_front();
		m_iSize --;
	}

	memcpy(pMsg, pBlock, pListMsg->GetLength());
	/*msgpool.*/s_theMsgMemAllocator.deallocate(pBlock);

	return true;
	//unguard;
}


void MsgQueue::Clear(void)
{
	//guardfunc;
	CSALocker locker(this);
	while( !m_listAdditional.empty()  )	
	{	
		unsigned char* pBlock = m_listAdditional.back();
		/*msgpool.*/s_theMsgMemAllocator.deallocate(pBlock);
		m_listAdditional.pop_back();
	}
	m_iSize = 0;
	//unguard;
}