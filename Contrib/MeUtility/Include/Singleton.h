#ifndef _SW_SINGLETON_h
#define _SW_SINGLETON_h

#include <vector>

class CSingletonBase
{
public:
	static void ReleaseAll()
	{
		for(std::vector<CSingletonBase*>::reverse_iterator rIter = GetSingleVector()->rbegin(); rIter != GetSingleVector()->rend();++rIter)
		{
			delete (*rIter);
		}
		GetSingleVector()->clear();
		delete m_SingleVector;
		m_SingleVector = NULL;
	}
protected:
	CSingletonBase()
	{
		GetSingleVector()->push_back(this);
	}
	virtual ~CSingletonBase()
	{
	}
	static std::vector<CSingletonBase*>*		 GetSingleVector()
	{
		if (m_SingleVector == NULL)
		{
			m_SingleVector = new std::vector<CSingletonBase*>;
		}
		return m_SingleVector;
	}
	static std::vector<CSingletonBase*>*   m_SingleVector;

};


template <class T>
class Singleton :public CSingletonBase
{
public:
	static T*	Instance()
	{
		if ( 0==s_pInstance )
		{
			s_pInstance = new T;
		}

		return s_pInstance;
	}

	static void Release()
	{
		if ( 0!=s_pInstance )
		{
			for (std::vector<CSingletonBase*>::iterator iter = GetSingleVector()->begin(); iter != GetSingleVector()->end(); ++iter)
			{
				if (*iter == s_pInstance)
				{
					delete s_pInstance;
					s_pInstance = 0;

					GetSingleVector()->erase(iter);
					break;
				}
			}
		}
	}

protected:
	Singleton() {}
	virtual ~Singleton() {}

private:
	static T* s_pInstance;
};

template <class T>
T *Singleton<T>::s_pInstance = 0;


// ʵ�ָ��������˵��߳�ʹ�õĵ��� ( ��ģʽ )
// ���̺߳Ϳ���ʧЧ���ô�����Ӱ��, ��ο�Loki��ĵ���ģʽ
template< typename T >
class ISingletion
{
public:
	virtual ~ISingletion() {}

	static T& Instance()
	{
		static T s_xInstance;
		return s_xInstance;
	}

protected:
	ISingletion() {}

private:
	ISingletion( const ISingletion& );
	ISingletion& operator = ( const ISingletion& );
};

/////////////////////////////////////////////////////////////////////////////
//// ����һ����Դ�൥��ģʽ ����֧���ȼ��� 
//   �Ͳ���cpp������static������
class ICfgSingletionBase
{
public:
	// ���������ļ��õ�
	virtual bool LoadResourceConfig(const char* pszConfig) = 0;

	// �������������õ� 
	virtual bool MultiReloadConfig(const char* pszConfig)  = 0;

	// �����̵߳��õ�
	virtual bool ReplaceInstance()    = 0;

	// �����̵߳��õ� ��ɻص�
	virtual void OnReloadFinished(){};

protected:
	ICfgSingletionBase(){}
	virtual ~ICfgSingletionBase(){}
};
// ֻ���Լ�new �Լ�delete
template< typename T >
class ICfgSingletion :public ICfgSingletionBase
{
public:
	static T& Instance()
	{
		if ( 0==s_pInstance )
		{
			s_pInstance = new T;
		}
		return *s_pInstance;
	}

	virtual bool MultiReloadConfig(const char* pszConfig)//ʵ��
	{
		if ( s_pReInstance )
		{ delete s_pReInstance; }

		s_pReInstance = new T;
		return s_pReInstance->LoadResourceConfig(pszConfig);//����һ��
	}

	virtual bool ReplaceInstance()//ʵ��
	{
		if (!s_pReInstance)	return false;

		if ( s_pInstance ){ delete s_pInstance; }

		s_pInstance = s_pReInstance;
		s_pReInstance = 0;
		s_pInstance->OnReloadFinished();
		return true;
	}

protected:
	ICfgSingletion(){}
	virtual ~ICfgSingletion() {}

private:
	ICfgSingletion( const ICfgSingletion& );//ICfgSingletion A(b)
	ICfgSingletion& operator = ( const ICfgSingletion& );//ICfgSingletion A = b

	static T* s_pInstance;
	static T* s_pReInstance;//������¼����ʱʵ��ָ��

};

template <typename T>
T *ICfgSingletion<T>::s_pInstance = 0;

template <typename T>
T *ICfgSingletion<T>::s_pReInstance = 0;

#endif _SW_SINGLETON_h