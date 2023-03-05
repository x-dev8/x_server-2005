/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SlkReader.h
* Create: 	10/06/06
* Desc:		SLK�ļ���ȡ
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef __SLKREADER_H__
#define __SLKREADER_H__

#include <vector>


#define SLK_EOF	0xFFFFFFFF
#define SLK_ERR 0xFFFFFFFF

#define MAX_SLK_NUM_STRING_LEN	64
#define MAX_SLK_COL_NAME_LEN	128
#define MAX_SLK_VALUE_STRING	2048

//************************************************
struct TSLKValue
{
	friend class SlkReader;
	friend struct TSLKRow;

public:
	TSLKValue();
	virtual ~TSLKValue();

	int			ToInt32() const;
	double		Todouble() const;
	const char*	ToString() const;

protected:
	int			intValue;
	double		floatValue;

	// NOTE:����ַ���ָ�����������䣬�����ͷš�
	char*		stringValue;
};

//************************************************
struct TSLKColumn
{
	char name[MAX_SLK_COL_NAME_LEN]; 	
};

//************************************************
struct TSLKRow
{
	friend class SlkReader;

public:
	TSLKRow();
	virtual ~TSLKRow();

	const TSLKValue*	GetValue( unsigned int pColumn ) const;
	const bool			SetValue( unsigned int pColumn, TSLKValue* pValue );

private:
	TSLKValue*	value;
};

//************************************************
class SlkReader
{
public:
	SlkReader();
	virtual ~SlkReader();

	// Slow. you must call at initialize time.
	// ͬһʱ��һ�� CSlkReader ֻ�ܶ�Ӧһ���ļ���
	// ��Ϊÿ����һ�� LoadFromFile ��Ҫ��һ���ļ������ԱȽ�����
	bool				LoadFromFile( const char* pFileName );

	// �ر� Slk �ļ���������� buffer.
	void				Close();

	// �����к��еĸ�����
	unsigned int		GetRowCount() const{ return m_row; };
	unsigned int		GetColCount() const{ return m_col; };

	// access straight. û�б߽��顣.
	const TSLKValue*	GetValue( unsigned int pRow, unsigned int pCol ) const;
	TSLKValue*			GetValue( unsigned int pRow, unsigned int pCol );

	// ����ȡֵ���������ֵΪ SLK_EOF ���ļ�������.
	unsigned int		GetFirstRow();
	unsigned int		GetNextRow();
	unsigned int		GetLastRow();

	//const TSLKValue* GetData( const char* pColName );
	// NOTE:���ص�ֵ�����ں� CSlkReader ��ͬ��
	TSLKValue*			GetData( const char* pColName );
	const TSLKValue*	GetData( unsigned int pColumn ) const;	
	TSLKValue*			GetData( unsigned int pColumn );	

private:
	char*				FetchKnownKeyValue( char* pData, bool& pIsEnd );
	char*				EvalFKeyValue( char* pData, bool& pIsEnd );
	char*				EvalCKeyValue( char* pData, bool& pIsEnd );
	char*				EvalUnknowKey( char* pData, bool& pIsEnd );
	void				EvalKeyLine( char* pData );
	bool				GetInfoFromMemory( void* pMemory, unsigned int pSize );
	unsigned int		GetColByName( const char* pName );

private:
	TSLKColumn*			m_column;
	TSLKRow*			m_data;
	unsigned int		m_curPos;

	unsigned int		m_row;
	unsigned int		m_col;

	unsigned int		m_curRow;
	unsigned int		m_curCol;

	struct _TSLKValue
	{
		unsigned int	row;
		unsigned int	col;
		TSLKValue		value;
	};

	std::vector< _TSLKValue* >	_TSLKValueArray;
};


#endif	// __SLKREADER_H__
