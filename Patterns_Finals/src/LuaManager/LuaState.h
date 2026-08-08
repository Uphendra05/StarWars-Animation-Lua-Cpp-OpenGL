#pragma once

#include "LuaManager.h"
#include "../GameObject/GameObject.h"

class LuaState
{
public:
	LuaState( GameObject* gameObject);

	void LoadScript(const char* path );
	lua_State* GetState();
	void SetState(lua_State* luaState);
	void Execute();
	void CloseState();

private:
	
	const char* path;
	bool isLoaded = false;

	lua_State* luaState = nullptr;

	void PrintError(const char* message);
};

