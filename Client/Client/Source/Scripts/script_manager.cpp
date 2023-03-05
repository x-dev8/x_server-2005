#include "script_manager.h"
#include "client_tolua.h"
#include "../filepacket/packet_interface.h"

//#include "Cipher/cipher_factory.h"
//#include "Launcher/DataLauncher.h"
ScriptManager::ScriptManager(void)
{
	states["Default"] = new LuaStateOwner();
}

ScriptManager::~ScriptManager(void)
{
	std::map<std::string, LuaStateOwner*>::iterator it, end = states.end();
	for (it = states.begin(); it != end; ++it)
	{
		delete it->second;
	}
	states.clear();
}

void ScriptManager::compile()
{
    tolua_compile_open( getLuaStateOwner().Get()->GetCState() );
}

void ScriptManager::executeFile(const std::string& filename )
{
	executeFile(filename, getLuaStateOwner(filename));
}

void ScriptManager::executeFile( const std::string& filename, LuaStateOwner& luaStateOwner )
{
	f_Handle* fp = packet_namespace::w_fopen(filename.c_str(), "rb" );

	if (fp)
	{
		int abc = GetCurrentThreadId();
		packet_namespace::w_fseek ( fp, 0, SEEK_END );
		long nSize = packet_namespace::w_ftell( fp ) + 1;
		packet_namespace::w_rewind( fp );

		char* buffer = new char[nSize];
		memset(buffer, 0, sizeof(char) * nSize);
		packet_namespace::w_fread(buffer, sizeof(char), nSize - 1, fp);
	
		packet_namespace::w_fclose(fp);

		luaStateOwner->DoString(buffer);

		delete[] buffer;
	}
}