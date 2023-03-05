#pragma once
#include <string>
#include <windows.h>

extern "C" {
#include "Luaplus/lua/lua.h"
	extern int luaopen_base (lua_State *L);
	extern int luaopen_io(lua_State *L);
	extern int luaopen_string(lua_State *L);
	extern int luaopen_math(lua_State *L);
	extern int luaopen_debug(lua_State *L);
}
#include "LuaPlus/LuaPlus.h"

using namespace LuaPlus;

//////////////////////////////////////////////////////////////////////////
// Lua注册 基本函数结构， 本地全局函数
typedef struct 
{
	const char *name;
	lua_CFunction func;
}TNativeFun;

//////////////////////////////////////////////////////////////////////////
// 
class IScript
{
public:
	virtual ~IScript(){};
	virtual BOOL Init() = 0;
	virtual void Exit() = 0;
	virtual BOOL Load(char* FileName) = 0;
	virtual	BOOL Compile(char* FileName) = 0;
	virtual	BOOL Execute() = 0;
	//virtual	BOOL CallFunction(LPSTR cFuncName, int nResults, LPSTR cFormat, ...) = 0;
	virtual BOOL RegisterFunction(LPSTR FuncName, void* Func) = 0;
	virtual void SetScriptName(LPSTR scpname) = 0;
};

class LuaConvert
{
public:
	LuaConvert(LuaObject& obj)
		: refobj(obj)
	{
	}
	operator int()
	{
		return refobj.GetInteger();
	}
	operator float()
	{
		return refobj.GetFloat();
	}
	operator double()
	{
		return refobj.GetDouble();
	}
	operator const char* ()
	{
		return refobj.GetString();
	}
	operator const wchar_t* ()
	{
		return (wchar_t*)refobj.GetWString();
	}
	operator std::string()
	{
		return std::string(refobj.GetString());
	}
	//operator std::wstring()
	//{
	//	return std::wstring(refobj.GetWString());
	//}
	operator void* ()
	{
		return refobj.GetUserData();
	}
	template<typename T>
	operator T* ()
	{
		return (T*)refobj.GetUserData();
	}
	template<typename R>
	operator LuaFunction<R> ()
	{
		return LuaFunction<R>(refobj);
	}
private:
	LuaObject refobj;
};
template<typename Object>
class LuaConstructor
{
private:

	static	int ConstructorHelper(LuaState* state, Object* pObj)
	{
		std::string metaname("MetaClass_");
		metaname += typeid(Object).raw_name();

		LuaObject obj(state);
		obj.AssignUserData(state, pObj);
		obj.SetMetaTable(state->GetGlobal(metaname.c_str()));
		obj.PushStack();
		return 1;
	}

public:

	static	int Constructor(LuaState* state)
	{
		return ConstructorHelper(state, new Object());
	}

	template<typename A1>
	static	int Constructor(LuaState* state)
	{
		LuaConvert a1 = LuaObject(state, 1);
		return ConstructorHelper(state, new Object((A1)a1) );
	}

	template<typename A1, typename A2>
	static	int Constructor(LuaState* state)
	{
		LuaConvert a1 = LuaObject(state, 1);
		LuaConvert a2 = LuaObject(state, 2);
		return ConstructorHelper(state, new Object((A1)a1, (A2)a2) );
	}

	template<typename A1, typename A2, typename A3>
	static	int Constructor(LuaState* state)
	{
		LuaConvert a1 = LuaObject(state, 1);
		LuaConvert a2 = LuaObject(state, 2);
		LuaConvert a3 = LuaObject(state, 3);
		return ConstructorHelper(state, new Object((A1)a1, (A2)a2, (A3)a3) );
	}

	template<typename A1, typename A2, typename A3, typename A4>
	static	int Constructor(LuaState* state)
	{
		LuaConvert a1 = LuaObject(state, 1);
		LuaConvert a2 = LuaObject(state, 2);
		LuaConvert a3 = LuaObject(state, 3);
		LuaConvert a4 = LuaObject(state, 4);
		return ConstructorHelper(state, new Object((A1)a1, (A2)a2, (A3)a3, (A4)a4) );
	}

	template<typename A1, typename A2, typename A3, typename A4, typename A5>
	static	int Constructor(LuaState* state)
	{
		LuaConvert a1 = LuaObject(state, 1);
		LuaConvert a2 = LuaObject(state, 2);
		LuaConvert a3 = LuaObject(state, 3);
		LuaConvert a4 = LuaObject(state, 4);
		LuaConvert a5 = LuaObject(state, 5);
		return ConstructorHelper(state, new Object((A1)a1, (A2)a2, (A3)a3, (A4)a4, (A5)a5) );
	}

	static int Destructor(LuaState* state)
	{
		LuaObject o(state, 1);

		delete (Object*)o.GetUserData();

		LuaObject meta = state->GetGlobal("MetaClass_Nil");
		if(meta.IsNil())
		{
			meta = state->GetGlobals().CreateTable("MetaClass_Nil");
		}

		o.SetMetaTable(meta);
		return 0;
	}
};

template<typename Object>
class LuaClass
{
public:
	LuaClass(LuaState* state)
	{
		luaGlobals = state->GetGlobals();

		std::string metaname("MetaClass_");
		metaname += typeid(Object).raw_name();

		metaTableObj = luaGlobals.CreateTable(metaname.c_str());
		metaTableObj.SetObject("__index", metaTableObj);
	}

	template<typename Func>
	inline LuaClass& def(const char* name, Func func)
	{
		metaTableObj.RegisterObjectDirect(name, (Object*) 0, func);
		return *this;
	}

	inline LuaClass& create(const char* name)
	{
		luaGlobals.Register(name, LuaConstructor<Object>::Constructor);
		return *this;
	}

	template<typename A1>
	inline LuaClass& create(const char* name)
	{
		luaGlobals.Register(name, LuaConstructor<Object>::Constructor<A1>);
		return *this;
	}
	template<typename A1, typename A2>
	inline LuaClass& create(const char* name)
	{
		luaGlobals.Register(name, LuaConstructor<Object>::Constructor<A1, A2>);
		return *this;
	}
	template<typename A1, typename A2, typename A3>
	inline LuaClass& create(const char* name)
	{
		luaGlobals.Register(name, LuaConstructor<Object>::Constructor<A1, A2, A3>);
		return *this;
	}
	template<typename A1, typename A2, typename A3, typename A4>
	inline LuaClass& create(const char* name)
	{
		luaGlobals.Register(name, LuaConstructor<Object>::Constructor<A1, A2, A3, A4>);
		return *this;
	}
	template<typename A1, typename A2, typename A3, typename A4, typename A5>
	inline LuaClass& create(const char* name)
	{
		luaGlobals.Register(name, LuaConstructor<Object>::Constructor<A1, A2, A3, A4, A5>);
		return *this;
	}
	inline LuaClass& destroy(const char* name)
	{
		metaTableObj.Register(name, LuaConstructor<Object>::Destructor);
		return *this;
	}

private:
	LuaObject metaTableObj;
	LuaObject luaGlobals;
};
class LuaModule
{
public:
	LuaModule(LuaState* state)
	{
		luaModuleObj = state->GetGlobals();
	}

	LuaModule(LuaState* state, const char* name)
	{
		luaModuleObj = state->GetGlobals().CreateTable(name);
	}

	template<typename Func>
	inline LuaModule& def(const char* name, Func func)
	{
		luaModuleObj.RegisterDirect(name, func);
		return *this;
	}

	template<typename Object, typename Func>
	inline LuaModule& def(const char* name, Object& o, Func func)
	{
		luaModuleObj.RegisterDirect(name, o, func);
		return *this;
	}

private:
	LuaObject luaModuleObj;
};
class LuaScript :public IScript
{
public:
	LuaStateOwner m_LuaOwner;
	char m_szScriptName[100];
public:
	LuaScript(void);
public:
	~LuaScript(void);
public:
	//////////////////////////////////////////////////////////////////////////
	//返回函数指针
	LuaFunction<int> GetGlobalFun( LPSTR cFuncName )
	{	
		//LuaObject testobject = m_LuaOwner->GetGlobal(cFuncName);
		//if(testobject.IsFunction())
		//{
		//	int x = 0;
		//}
		return m_LuaOwner->GetGlobal(cFuncName);
	}
	LuaStateOwner*	 GetOwner() { return &m_LuaOwner; }
public:
	// IScript Interface
	virtual BOOL Init();
	virtual void Exit();
	virtual BOOL Load(char* FileName);
	virtual	BOOL Compile(char* FileName);
	virtual	BOOL Execute();
	//virtual	BOOL CallFunction(LPSTR cFuncName, int nResults, LPSTR cFormat, ...);
	virtual BOOL RegisterFunction(LPSTR FuncName, void* Func);
	virtual void SetScriptName(LPSTR scpname) { strncpy( m_szScriptName, scpname, sizeof(m_szScriptName)-1 ); }

public:
	void		SetInt(LPSTR cValName, int nVals)			{ m_LuaOwner->GetGlobals().SetInteger(cValName, nVals); }
	void		SetString(LPSTR cValName,const char* Vals)	{ m_LuaOwner->GetGlobals().SetString(cValName, Vals); }
	void		SetDouble(LPSTR cValName,double Vals)		{ m_LuaOwner->GetGlobals().SetNumber(cValName, (lua_Number)Vals); }
	const char*	GetString( LPSTR cValName )					{ return m_LuaOwner->GetGlobal(cValName).GetString(); }
	int			GetInt( LPSTR cValName )					{ return m_LuaOwner->GetGlobal(cValName).GetInteger(); }
	double		GetNumber( LPSTR cValName )					{ return m_LuaOwner->GetGlobal(cValName).GetNumber(); }
	LuaObject	GetGlobalObject(LPSTR cValName)				{ return m_LuaOwner->GetGlobal(cValName); }
	LuaObject	GetGlobals()								{ return m_LuaOwner->GetGlobals(); }
public:
	//	BOOL	CallFunction(LPSTR cFuncName, int nResults, LPSTR cFormat, va_list vlist);
	BOOL		RegisterFunctions( TNativeFun Funcs[], int n );
	void		RegisterStandardFunctions();

	template<typename Object, typename Func>
	inline void RegisterClassFun(const char* name, Object& o, Func func)
	{
		m_LuaOwner->GetGlobals().RegisterDirect(name, o, func);
	}
};
