#pragma once

extern "C"
{
#include <Lua/lua.h>
#include <Lua/lauxlib.h>
#include <Lua/lualib.h>
}

#include <string>
#include <unordered_map>

#include "../GameObject/GameObject.h"

class LuaManager
{
public:
	
	LuaManager();

	static LuaManager& GetInstance();

	lua_State* CreateLuaState(GameObject* gameObject);
	void CloseLuaState(lua_State* luaState);

	void ExecuteGlobalState();

	GameObject* GetGameObjectWithState(lua_State* state);
	GameObject* GetGameObjectWithID(std::string id);

	void AddGameObject(const std::string& id, GameObject* gameObject);
	void SetGlobalBinding(lua_State* luaState);

private:

	std::string path = "LuaScripts/World.lua";

	void SetBindingsToState(lua_State* luaState);

	lua_State* globalState;

	std::unordered_map <lua_State*, GameObject*> gameObjectsWithState;
	std::unordered_map <std::string, GameObject*> gameObjectsWithString;
};

