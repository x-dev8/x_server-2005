/*******************************************************************************
*  Copyright ZWS (C) 2007 - All Rights Reserved
*
* File: 	HashTable.h
* Date: 	11/19/2007
* Desc:		<< Inside MoPaQ >>
*
*******************************************************************************/
#ifndef _COMMON_HASHTABLE_H__
#define _COMMON_HASHTABLE_H__
#include "MeTerrain/SwType.h"
////////////////////////////////////////////////////////////////////////////////
#define HASH_INVALID		(0xFFFFFFFF)
////////////////////////////////////////////////////////////////////////////////
class _HashBuffer
{
public:
	_HashBuffer() {  
		unsigned long seed = 0x00100001, index1 = 0, index2 = 0, i;
		for(index1 = 0; index1 < 0x100; index1++) { 
			for(index2 = index1, i = 0; i < 5; i++, index2 += 0x100) { 
				unsigned long temp1, temp2;
				seed = (seed * 125 + 3) % 0x2AAAAB;
				temp1 = (seed & 0xFFFF) << 0x10;
				seed = (seed * 125 + 3) % 0x2AAAAB;
				temp2 = (seed & 0xFFFF);
				m_hashBuffer[index2] = (temp1 | temp2); 
			} 
		} 
	};
	sInt32	m_hashBuffer[0x500];
};

static _HashBuffer _s_hashBuffer;

////////////////////////////////////////////////////////////////////////////////
template< class T >
struct _PtHashValue
{
	sInt32					hashA;
	sInt32					hashB;
	bool					isExists;
	T						value;
};

////////////////////////////////////////////////////////////////////////////////
template< class T >
class PtHashString
{
public:
	PtHashString( uInt32 hashTableSize, const T& nullValue )
	{
		Assert( hashTableSize > 0 );
		m_nullValue		= nullValue;
		m_hashTableSize	= hashTableSize;
		m_hashTable		= new _PtHashValue<T>[m_hashTableSize];
		for( uInt32 i=0; i< m_hashTableSize; i++ ) {
			m_hashTable[i].isExists	= false;
			m_hashTable[i].value	= nullValue;
		}
	}

	~PtHashString()
	{
		SAFE_DELETE_ARRAY( m_hashTable );
	}
	
	// 返回值必须马上获得,否则有可能被更改.
	T& Remove( sInt32 hashPos )
	{
		Assert( true == m_hashTable[hashPos].isExists );
		m_hashTable[hashPos].isExists	= false;
		return m_hashTable[hashPos].value;
	}

	void Clear()
	{
		for( uInt32 i=0; i< m_hashTableSize; i++ ) {
			m_hashTable[i].isExists = false;
		}
	}

	// 不区分 String 大小写.
	sInt32 Put( const char* hashString, const T& value )
	{
		const sInt32 HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;

		sInt32 hash		= HashString(hashString, HASH_OFFSET)
			, hashA		= HashString(hashString, HASH_A)
			, hashB		= HashString(hashString, HASH_B)
			, hashStart	= hash % m_hashTableSize
			, hashPos	= hashStart;

		for(;;) { 
			if( m_hashTable[hashPos].isExists ) {
				if( m_hashTable[hashPos].hashA == hashA && m_hashTable[hashPos].hashB == hashB ) {
					return hashPos; 
				}
				else {
					hashPos = (hashPos + 1) % m_hashTableSize;
				}
			}
			else {
				m_hashTable[hashPos].isExists	= true;
				m_hashTable[hashPos].hashA		= hashA;
				m_hashTable[hashPos].hashB		= hashB;
				m_hashTable[hashPos].value		= value;
				return hashPos;
			}
			if( hashPos == hashStart ) 
				break;
		}
		return HASH_INVALID; //Error value 
	}

	T& Get( const char* hashString )
	{
		sInt32 hashId = Find( hashString );
		
		if( HASH_INVALID != hashId ) {
			return m_hashTable[hashId].value;
		}
		return m_nullValue;
	}

	T& operator[]( const uInt32 hashPos )
	{
		Assert( hashPos >= 0 && hashPos < m_hashTableSize );
		if( m_hashTable[hashPos].isExists )
			return m_hashTable[hashPos].value;
		else 
			return m_nullValue;
	}

	const T& operator[]( const uInt32 hashPos ) const
	{
		Assert( hashPos >= 0 && hashPos < m_hashTableSize );
		if( m_hashTable[hashPos].isExists )
			return m_hashTable[hashPos].value;
		else 
			return m_nullValue;
	}

	sInt32 Size() const
	{
		return m_hashTableSize;
	}
	
	// 没有搜索到则搜索完所有项.(速度很慢)
	sInt32 Find( const char *hashString )
	{
		const sInt32 HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;

		sInt32 hash		= HashString(hashString, HASH_OFFSET)
			, hashA		= HashString(hashString, HASH_A)
			, hashB		= HashString(hashString, HASH_B)
			, hashStart	= hash % m_hashTableSize
			, hashPos	= hashStart;

		for(;;){
			if( m_hashTable[hashPos].isExists && m_hashTable[hashPos].hashA == hashA && m_hashTable[hashPos].hashB == hashB) {
				return hashPos; 
			}
			hashPos = (hashPos + 1) % m_hashTableSize;

			if( hashPos == hashStart ) {
				break;
			}
		}
		return HASH_INVALID; //Error value 
	}
protected:
	PtHashString()
	{
		m_hashTable		= NULL;
		m_hashTableSize	= 0;
	}
	uInt32 HashString( const char* hashString, uInt32 hashType )
	{
		uInt32 seed1 = 0x7FED7FED;
		uInt32 seed2 = 0xEEEEEEEE;
		uInt32 ch;			/* One key character */

		/* Prepare seeds */
		while( *hashString != 0 ) {
			ch		= toupper( *hashString++ );
			seed1	= _s_hashBuffer.m_hashBuffer[(hashType<<8) + ch] ^ (seed1 + seed2);
			seed2	= ch + seed1 + seed2 + (seed2 << 5) + 3;
		}
		return seed1;
	}
protected:
	uInt32				m_hashTableSize;
	_PtHashValue<T>*	m_hashTable;
	T					m_nullValue;
};

#endif	// _COMMON_HASHTABLE_H__
