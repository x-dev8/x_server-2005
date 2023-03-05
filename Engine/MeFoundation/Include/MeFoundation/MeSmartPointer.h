#pragma once

#include "MeRefObject.h"

/**
@desc:使用方法：MeSmartPointer(classname)即可，传入的类需要派生自
MeRefObject。可参考Gamebryo的使用。
*/
template< class T >
class MEFOUNDATION_ENTRY MePointer : public MeCommonAlloc<T>
{
public:
	inline MePointer( T* pObject = 0 );
	inline MePointer( const MePointer& rkPointer );
	inline ~MePointer();

	inline operator T*() const;
	inline T& operator*() const;
	inline T* operator->() const;

	inline MePointer& operator=( T* pObject );
	inline MePointer& operator=( const MePointer& rkPointer );

	inline bool operator==( T* pObject ) const;
	inline bool operator!=( T* pObject ) const;
	inline bool operator==( const MePointer& rkPointer ) const;
	inline bool operator!=( const MePointer& rkPointer ) const;

protected:
	T* m_pObject;
};
//////////////////////////////////////////////////////////////////////////
#define MeSmartPointer( classname ) \
	class classname; \
	typedef MePointer<classname> classname##Ptr;
//////////////////////////////////////////////////////////////////////////
template< class T > 
inline MePointer<T>::MePointer( T* pObject /* = 0 */ )
{
	m_pObject = pObject;
	if( m_pObject )
		m_pObject->IncRefCount();
}
//////////////////////////////////////////////////////////////////////////
template< class T > 
inline MePointer<T>::MePointer(const MePointer<T> &rkPointer)
{
	m_pObject = rkPointer.m_pObject;
	if( m_pObject )
		m_pObject->IncRefCount();
}
//////////////////////////////////////////////////////////////////////////
template< class T >
MePointer<T>::~MePointer()
{
	if( m_pObject )
		m_pObject->DecRefCount();
}
//////////////////////////////////////////////////////////////////////////
template< class T >
inline MePointer<T>::operator T*() const
{
	return m_pObject;
}
//////////////////////////////////////////////////////////////////////////
template< class T >
inline T& MePointer<T>::operator*() const
{
	return *m_pObject;
}
//////////////////////////////////////////////////////////////////////////
template< class T >
inline T* MePointer<T>::operator->() const
{
	return m_pObject;
}
//////////////////////////////////////////////////////////////////////////
template< class T >
inline MePointer<T>& MePointer<T>::operator=( T* pObject )
{
	if( m_pObject != pObject )
	{
		if( m_pObject )
			m_pObject->DecRefCount();

		m_pObject = pObject;

		if( m_pObject )
			m_pObject->IncRefCount();
	}
	return *this;	
}
//////////////////////////////////////////////////////////////////////////
template< class T >
inline MePointer<T>& MePointer<T>::operator=( const MePointer& rkPointer )
{
	if( m_pObject != rkPointer.m_pObject )
	{
		if( m_pObject )
			m_pObject->DecRefCount();

		m_pObject = rkPointer.m_pObject;

		if( m_pObject )
			m_pObject->IncRefCount();
	}
	return *this;	
}
//////////////////////////////////////////////////////////////////////////
template< class T >
inline bool MePointer<T>::operator==( T* pObject ) const
{
	return m_pObject == pObject;
}
//////////////////////////////////////////////////////////////////////////
template< class T >
inline bool MePointer<T>::operator!=( T* pObject ) const
{
	return m_pObject != pObject;
}
//////////////////////////////////////////////////////////////////////////
template< class T >
inline bool MePointer<T>::operator==( const MePointer& rkPointer ) const
{
	return m_pObject == rkPointer.m_pObject;
}
//////////////////////////////////////////////////////////////////////////
template< class T >
inline bool MePointer<T>::operator!=( const MePointer& rkPointer ) const
{
	return m_pObject != rkPointer.m_pObject;
}
//////////////////////////////////////////////////////////////////////////
