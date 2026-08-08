#include "LuaManager.h"
#include <iostream>
#include "CommandManager/CommandManager.h"
#include "Commands/MoveToPosWithTime.h"
#include "Commands/MoveWithSpeed.h"
#include "Commands/RotateWithTime.h"
#include "Commands/WaitForSeconds.h"
#include "Commands/ScaleWithTime.h"
#include "Commands/FollowCurveWithTime.h"
#include "Commands/CreateGameObject.h"
#include "Commands/FollowObject.h"
#include "Commands/LookAt.h"
#include "LuaBindingFunction.h"
#include "../Asteroid/AsteroidManager.h"
#include "../Fighters/FighterManager.h"

LuaManager::LuaManager()
{
	globalState = luaL_newstate();

	if (globalState == nullptr)
	{
		Debugger::Print("Global State Not Created");
		return;
	}

	luaL_openlibs(globalState);

	SetGlobalBinding(globalState);

}

LuaManager& LuaManager::GetInstance()
{
	static LuaManager instance;
	return instance;
}

lua_State* LuaManager::CreateLuaState(GameObject* gameObject)
{
	lua_State* newState = luaL_newstate();

	if (newState == nullptr)
	{
		return nullptr;
	}

	luaL_openlibs(newState);

	SetBindingsToState(newState);

	if (gameObject == nullptr) return newState;

	gameObjectsWithState[newState] = gameObject;
	gameObjectsWithString[gameObject->entityId] = gameObject;

	return newState;
}

void LuaManager::CloseLuaState(lua_State* luaState)
{
	lua_close(luaState);
}

void LuaManager::ExecuteGlobalState()
{
	if (luaL_loadfile(globalState, path.c_str()) != LUA_OK)
	{
		Debugger::Print("Error Loading Lua Script :");
		return;
	}

	SetBindingsToState(globalState);

	int result = lua_pcall(globalState, 0, 0, 0);

	if (result != LUA_OK)
	{
		const char* errorMsg = lua_tostring(globalState, -1);
		Debugger::Print("Global State Execution Failed : ", errorMsg);
		lua_pop(globalState, 1);
	}

}

GameObject* LuaManager::GetGameObjectWithState(lua_State* state)
{
	std::unordered_map <lua_State*, GameObject*>::iterator it = gameObjectsWithState.find(state);

	if (it != gameObjectsWithState.end())
	{
		return it->second;
	}

	return nullptr;
}

GameObject* LuaManager::GetGameObjectWithID(std::string id)
{
	std::unordered_map <std::string, GameObject*>::iterator it = gameObjectsWithString.find(id);

	if (it != gameObjectsWithString.end())
	{
		return it->second;
	}
	return nullptr;
}

void LuaManager::AddGameObject(const std::string& id, GameObject* gameObject)
{
	gameObjectsWithString[id] = gameObject;
}



void LuaManager::SetBindingsToState(lua_State* luaState)
{

#pragma region BeginCommandGroup

	lua_pushcfunction(luaState, [](lua_State* luaState)->int
		{
			int argCount = lua_gettop(luaState);
			if (argCount >= 3)
			{
				std::string friendlyName = luaL_checkstring(luaState, 1);
				std::string commandGroupType = luaL_checkstring(luaState, 2);
				int repeatCount = luaL_checknumber(luaState, 3);

				CommandManager::GetInstance().
					BeginCommandGroup(friendlyName, commandGroupType, repeatCount);

			}
			else if (argCount == 2)
			{
				std::string friendlyName = luaL_checkstring(luaState, 1);
				std::string commandGroupType = luaL_checkstring(luaState, 2);
				CommandManager::GetInstance().
					BeginCommandGroup(friendlyName, commandGroupType);
			}

			GetCommandGroupTable(luaState);

			return 1;
		});

	lua_setglobal(luaState, "BeginCommandGroup");

#pragma endregion

#pragma region EndCommandGroup

	lua_pushcfunction(luaState, [](lua_State* luaState)->int
		{

			CommandManager::GetInstance().EndCommandGroup();

			return 0;
		});

	lua_setglobal(luaState, "EndCommandGroup");

#pragma endregion

#pragma region WaitForSeconds

	lua_pushcfunction(luaState, [](lua_State* luaState)->int
		{
			int argCount = lua_gettop(luaState);

			if (argCount >= 1)
			{
				float time = luaL_checknumber(luaState, 1);

				BaseCommand* command = new WaitForSeconds(time);

				CommandManager::GetInstance().AddCommand(command);
			}

			return 0;
		});

	lua_setglobal(luaState, "WaitForSeconds");

#pragma endregion

#pragma region MoveWithTime

	lua_pushcfunction(luaState, [](lua_State* luaState)->int
		{
			int argCount = lua_gettop(luaState);

			if (argCount >= 4)
			{
				glm::vec3 pos;
				pos.x = luaL_checknumber(luaState, 1);
				pos.y = luaL_checknumber(luaState, 2);
				pos.z = luaL_checknumber(luaState, 3);

				float time = luaL_checknumber(luaState, 4);

				BaseCommand* command = new MoveToPosWithTime(
					CommandManager::GetInstance().GetBoundGameObject(),
					pos, time);

				CommandManager::GetInstance().AddCommand(command);

				GetEaseTable(luaState);

				return 1;

			}
			return 0;
		});

	lua_setglobal(luaState, "MoveWithTime");


#pragma endregion

#pragma region MoveWithSpeed

	lua_pushcfunction(luaState, [](lua_State* luaState)->int
		{
			int argCount = lua_gettop(luaState);

			if (argCount >= 4)
			{
				glm::vec3 pos;
				pos.x = luaL_checknumber(luaState, 1);
				pos.y = luaL_checknumber(luaState, 2);
				pos.z = luaL_checknumber(luaState, 3);

				float speed = luaL_checknumber(luaState, 4);

				BaseCommand* command = new MoveWithSpeed(
					CommandManager::GetInstance().GetBoundGameObject(),
					pos, speed);

				CommandManager::GetInstance().AddCommand(command);
			}
			return 0;
		});

	lua_setglobal(luaState, "MoveWithSpeed");


#pragma endregion

#pragma region RotateWithTime

	lua_pushcfunction(luaState, [](lua_State* luaState)->int
		{
			int argCount = lua_gettop(luaState);

			if (argCount >= 4)
			{
				glm::vec3 rot;
				rot.x = luaL_checknumber(luaState, 1);
				rot.y = luaL_checknumber(luaState, 2);
				rot.z = luaL_checknumber(luaState, 3);

				float time = luaL_checknumber(luaState, 4);

				BaseCommand* command = new RotateWithTime(
					CommandManager::GetInstance().GetBoundGameObject(),
					rot, time);

				CommandManager::GetInstance().AddCommand(command);

				GetEaseTable(luaState);

				return 1;
			}
			return 0;
		});

	lua_setglobal(luaState, "RotateWithTime");


#pragma endregion

#pragma region ScaleWithTime

	lua_pushcfunction(luaState, [](lua_State* luaState)->int
		{
			int argCount = lua_gettop(luaState);

			if (argCount >= 4)
			{
				glm::vec3 scale;
				scale.x = luaL_checknumber(luaState, 1);
				scale.y = luaL_checknumber(luaState, 2);
				scale.z = luaL_checknumber(luaState, 3);

				float time = luaL_checknumber(luaState, 4);

				BaseCommand* command = new ScaleWithTime(
					CommandManager::GetInstance().GetBoundGameObject(),
					scale, time);

				CommandManager::GetInstance().AddCommand(command);

				GetEaseTable(luaState);

				return 1;

			}
			return 0;
		});

	lua_setglobal(luaState, "ScaleWithTime");


#pragma endregion

#pragma region FollowCurve

	lua_pushcfunction(luaState, [](lua_State* luaState)->int
		{
			int argCount = lua_gettop(luaState);

			if (argCount >= 1)
			{
				float time = luaL_checknumber(luaState, 1);

				FollowCurveWithTime* command = new FollowCurveWithTime(
					CommandManager::GetInstance().GetBoundGameObject(), time);

				command->SetBezierCurve(new CubicBezierCurve());

				CommandManager::GetInstance().AddCommand(command);

				GetCurveTable(luaState);

				return 1;

			}
			return 0;
		});

	lua_setglobal(luaState, "FollowCurveWithTime");


#pragma endregion

#pragma region SpawnGameObject

	lua_pushcfunction(luaState, [](lua_State* luaState)->int
		{
			int argCount = lua_gettop(luaState);

			if (argCount == 2)
			{
				std::string objectType = luaL_checkstring(luaState, 1);
				std::string objectId = luaL_checkstring(luaState, 2);

				if (objectType == "Fighter")
				{
					FighterManager::GetInstance().SpawnFighter(objectId);
				}

				CreateGameObject* command = new CreateGameObject(objectId);

				CommandManager::GetInstance().AddCommand(command);

				return 0;

			}
			else if (argCount >= 3)
			{
				std::string objectType = luaL_checkstring(luaState, 1);
				std::string objectId = luaL_checkstring(luaState, 2);
				int type = luaL_checknumber(luaState, 3);

				Debugger::Print("Type :", objectType);
				if (objectType == "Asteroid")
				{
					GameObject* asteroid = AsteroidManager::GetInstance().SpawnAsteroid(objectId, type);
				}

				CreateGameObject* command = new CreateGameObject(objectId);

				CommandManager::GetInstance().AddCommand(command);

				return 0;

			}
			return 0;
		});

	lua_setglobal(luaState, "SpawnGameObject");


#pragma endregion

#pragma region FollowObject

	lua_pushcfunction(luaState, [](lua_State* luaState)->int
		{
			int argCount = lua_gettop(luaState);

			if (argCount >= 2)
			{
				std::string objectId = luaL_checkstring(luaState, 1);
				float time = luaL_checknumber(luaState, 2);
				
				GameObject* targetObj = LuaManager::GetInstance().GetGameObjectWithID(objectId);


				FollowObject* command = new FollowObject(

					CommandManager::GetInstance().GetBoundGameObject(), targetObj, time
				);

				CommandManager::GetInstance().AddCommand(command);

				GetFollowObjectTable(luaState);

				return 1;
			}
			return 0;
		});

	lua_setglobal(luaState, "FollowObject");


#pragma endregion

#pragma region LookAt

	lua_pushcfunction(luaState, [](lua_State* luaState)->int
		{
			int argCount = lua_gettop(luaState);

			if (argCount >= 1)
			{
				std::string objectId = luaL_checkstring(luaState, 1);
				float time = luaL_checknumber(luaState, 2);

				GameObject* targetObj = LuaManager::GetInstance().GetGameObjectWithID(objectId);

				LookAt* command = new LookAt(

					CommandManager::GetInstance().GetBoundGameObject(), targetObj, time
				);

				CommandManager::GetInstance().AddCommand(command);

				GetLookAtTable(luaState);

				return 1;
			}
			return 0;
		});

	lua_setglobal(luaState, "LookAt");


#pragma endregion

//
//#pragma region SpawnTriggerZone
//
//	lua_pushcfunction(luaState, [](lua_State* luaState)->int
//		{
//			int argCount = lua_gettop(luaState);
//
//			if (argCount >= 4)
//			{
//				std::string zoneId = luaL_checkstring(luaState, 1);
//
//				glm::vec3 scale;
//				scale.x = luaL_checknumber(luaState, 2);
//				scale.y = luaL_checknumber(luaState, 3);
//				scale.z = luaL_checknumber(luaState, 4);
//
//				GameObject* zone = TriggerZoneManager::GetInstance().SpawnZone(zoneId, scale);
//				LuaManager::GetInstance().AddGameObject(zoneId, zone);
//
//				return 0;
//
//			}
//			return 0;
//		});
//
//	lua_setglobal(luaState, "SpawnTriggerZone");
//
//
//#pragma endregion
//



}

void LuaManager::SetGlobalBinding(lua_State* luaState)
{
#pragma region BindGameObject

	lua_pushcfunction(luaState, [](lua_State* luaState)->int
		{
			int argCount = lua_gettop(luaState);

			if (argCount >= 1)
			{
				std::string gameObjectId = luaL_checkstring(luaState, 1);

				GameObject* gameObject = LuaManager::GetInstance().GetGameObjectWithID(gameObjectId);

				if (gameObject == nullptr)
				{
					Debugger::Print("GameObject Bindig failed : ", gameObjectId);
					return -1;
				}

				CommandManager::GetInstance().BindGameObject(gameObject);
			}
			return 0;
		});

	lua_setglobal(luaState, "BindGameObject");

#pragma endregion

#pragma region GetFloat

	lua_pushcfunction(luaState, [](lua_State* luaState)->int
		{
			lua_pushnumber(luaState, 5);

			return 1;
		});

	lua_setglobal(luaState, "GetFloat");

#pragma endregion

}




