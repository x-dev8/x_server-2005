#pragma once

extern "C" 
{
#include "Luaplus/lua/lua.h"
#include "Luaplus/lua/lauxlib.h"
#include "Luaplus/lua/lualib.h"
}

#include "LuaScript.h"
#include "tolua++/tolua++.h"

#include <map>

class ScriptManager
{
public:
    ~ScriptManager(void);

    static ScriptManager& instance()
    {
        static ScriptManager s;
        return s;
    }

    void compile();
	void executeFile( const std::string& filename );
	void executeFile( const std::string& filename, LuaStateOwner& luaStateOwner );
	void executeFileDefault( const std::string& filename ) { executeFile(filename, getLuaStateOwner()); }

	LuaStateOwner& getLuaStateOwner() { return *states["Default"]; }
	LuaStateOwner& getLuaStateOwner(const std::string& filename)
	{
		std::map<std::string, LuaStateOwner*>::iterator it = states.find(filename);
		if (it == states.end())
			states[filename] = new LuaStateOwner();
		return *states[filename];
	}

protected:
    ScriptManager(void);
    ScriptManager( const ScriptManager& );
    void operator = ( const ScriptManager& );

	std::map<std::string, LuaStateOwner*> states;
};
