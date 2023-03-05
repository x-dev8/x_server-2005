#include "CommandProcessor.h"
#include "WordParser.h"		//for WordParser

namespace NHelper
{

BOOL CCommandProcessor::Excute(const char *content_)
{
	if(content_ == NULL)
		return e_command_paramWrong;

// 	if(content_[0] == 0 )
// 		return e_command_paramWrong;

	WordParser words;
	if(0 == words.Parse(content_))
		return e_command_paramWrong;

	CCommand *pCommand = CCommandFactory::GetInstance().CreateCommand(words.GetWord(1));
	if(pCommand != NULL)
	{
		return pCommand->Excute(content_);
		delete pCommand;
	}

	return e_command_paramWrong;
}

CCommand *CCommandFactory::CreateCommand(TCommandType type_)
{
	TCreateMethods::const_iterator it = m_methods.find(type_);
	if(it != m_methods.end())
	{
		return (it->second)();
	}

	return NULL;
}

bool CCommandFactory::Register(TCommandType type_, TCreateCommandFun fun_)
{
	return m_methods.insert(TCreateMethods::value_type(type_, fun_)).second;
}

//----------------------
namespace 
{
	CCommand *CreateCommand_brightcontrast(void)
	{
		return new CCommand_brightcontrast;
	}

	const bool ret_brightcontrast = CCommandFactory::GetInstance().Register("brightcontrast", CreateCommand_brightcontrast);
}

BOOL CCommand_brightcontrast::Excute(const char * content_)
{
	return e_command_success;
}

namespace
{
	CCommand *CreateCommand_locate(void)
	{
		return new CCommand_locate;
	}

	const bool ret_locate = CCommandFactory::GetInstance().Register("locate", CreateCommand_locate);
}

BOOL CCommand_locate::Excute(const char * content_)
{
	return e_command_success;
}

}

