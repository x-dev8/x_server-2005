/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SlkReader.h
* Create: 	10/06/06
* Desc:		SLK文件读取
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

	// NOTE:这个字符串指针由你来分配，我来释放。
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
	// 同一时刻一个 CSlkReader 只能对应一个文件。
	// 因为每调用一次 LoadFromFile 就要打开一次文件，所以比较慢。
	bool				LoadFromFile( const char* pFileName );

	// 关闭 Slk 文件，并且清空 buffer.
	void				Close();

	// 返回行和列的个数。
	unsigned int		GetRowCount() const{ return m_row; };
	unsigned int		GetColCount() const{ return m_col; };

	// access straight. 没有边界检查。.
	const TSLKValue*	GetValue( unsigned int pRow, unsigned int pCol ) const;
	TSLKValue*			GetValue( unsigned int pRow, unsigned int pCol );

	// 遍历取值。如果返回值为 SLK_EOF 则文件结束。.
	unsigned int		GetFirstRow();
	unsigned int		GetNextRow();
	unsigned int		GetLastRow();

	//const TSLKValue* GetData( const char* pColName );
	// NOTE:返回的值生命期和 CSlkReader 相同。
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
