#include "LuaState.h"
#include <Graphics/Debugger.h>


LuaState::LuaState( GameObject* gameObject)
{
	luaState = LuaManager::GetInstance().CreateLuaState( gameObject);
}

void LuaState::LoadScript(const char* path)
{
	this->path = path;


	if (luaL_loadfile(luaState, path) != LUA_OK)
	{
		isLoaded = false;
		PrintError("Error Loading Lua Script : ");
		return;
	}

	isLoaded = true;
}

lua_State* LuaState::GetState()
{
	return luaState;
}

void LuaState::SetState(lua_State* luaState)
{
	this->luaState = luaState;
}

void LuaState::Execute()
{
	if (!isLoaded) return;

	int stackSizeBefore = lua_gettop(luaState);

	luaL_loadfile(luaState, path);

	int resutlt = lua_pcall(luaState, 0, 0, 0);

	if (resutlt != LUA_OK)
	{
		PrintError("Executing Failed : ");
	}

	int stackSizeAfter = lua_gettop(luaState);

}

void LuaState::CloseState()
{
	LuaManager::GetInstance().CloseLuaState(luaState);
}

void LuaState::PrintError(const char* message)
{
	const char* errorMsg = lua_tostring(luaState, -1);
	Debugger::Print(message, errorMsg);
	lua_pop(luaState, 1);
}
