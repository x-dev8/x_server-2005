/*----------------------------------------------------------
desc	: 一个通用的命令处理类，以及相关的命令定义。
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
	e_command_fail,			//执行失败
	e_command_paramWrong,	//参数错误
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
	std::string m_name;	//命令名
	TString m_param;	//参数描述
};

class CCommand
{
public:
	CCommand(){};
	virtual ~CCommand(){};

	/*----------------------------------------------
	desc	: 执行命令。
	In		: content_, 命令参数。
	out		:
	return	: 
	----------------------------------------------*/
	virtual BOOL Excute(const char * content_) = 0;

	/*----------------------------------------------
	desc	: 得到命令的描述内容。
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
