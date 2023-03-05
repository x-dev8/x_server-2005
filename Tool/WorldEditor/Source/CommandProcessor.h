/*----------------------------------------------------------
desc	: һ��ͨ�õ�������࣬�Լ���ص�����塣
author	: zilong
version	: 1.0
date	: 2011-01-12

revision:

----------------------------------------------------------*/

#pragma once

#include <map>
#include <string>

namespace NHelper
{
typedef int BOOL;

#ifdef _UNICODE 
typedef std::wstring TString;
#else
typedef std::string TString;
#endif

template<class T>
class CSingletonBase
{
public:
	static T &GetInstance(void)
	{
		static T instance;
		return instance;
	}

protected:
	CSingletonBase()
	{

	}

	~CSingletonBase()
	{

	}
};

enum ECommandResult
{
	e_command_success = 0,
	e_command_fail,			//ִ��ʧ��
	e_command_paramWrong,	//��������
	e_command_end,
};

class CCommand;

class CCommandProcessor: public CSingletonBase<CCommandProcessor>
{
public:
	BOOL Excute(const char *content_);
};

class CCommandVisitor
{
public:
	void Visit(CCommand &command_);
};

class CCommandFactory: public CSingletonBase<CCommandFactory>
{
public:
	typedef CCommand * (*TCreateCommandFun)();
	typedef const char *TCommandType;

public:
	CCommand *CreateCommand(TCommandType type_);

	bool Register(TCommandType type_, TCreateCommandFun fun_);
	bool UnRegister(TCommandType type_);

	/*----------------------------------------------
	desc	: 
	In		: 
	out		:
	return	: 
	----------------------------------------------*/
	void Travel(void (*visitor)(CCommand &));
private:

private:
	typedef std::map<TCommandType, TCreateCommandFun> TCreateMethods;
private:
	TCreateMethods m_methods;
};

class CCommandDesc
{
private:
	std::string m_name;	//������
	TString m_param;	//��������
};

class CCommand
{
public:
	CCommand(){};
	virtual ~CCommand(){};

	/*----------------------------------------------
	desc	: ִ�����
	In		: content_, ���������
	out		:
	return	: 
	----------------------------------------------*/
	virtual BOOL Excute(const char * content_) = 0;

	/*----------------------------------------------
	desc	: �õ�������������ݡ�
	In		: 
	out		:
	return	: 
	----------------------------------------------*/
	//virtual CCommandDesc GetDesc(void) = 0;
};

class CCommand_brightcontrast: public CCommand
{
public:
	CCommand_brightcontrast(){};
	virtual ~CCommand_brightcontrast(){};

	virtual BOOL Excute(const char * content_);
	//virtual CCommandDesc GetDesc(void);
};

class CCommand_locate: public CCommand
{
public: 
	CCommand_locate(){};
	virtual ~CCommand_locate(){};

	virtual BOOL Excute(const char * content_);
};

}
