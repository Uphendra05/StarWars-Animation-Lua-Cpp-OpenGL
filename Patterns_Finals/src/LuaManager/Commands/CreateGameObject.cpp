#include "CreateGameObject.h"
#include "../LuaManager.h"

CreateGameObject::CreateGameObject(const std::string& objectId)
{
    this->objectId = objectId;
}

void CreateGameObject::StartCommand()
{
    LuaManager::GetInstance().GetGameObjectWithID(objectId)->model->isActive = true;
    spawned = true;
}

void CreateGameObject::Update()
{
}

void CreateGameObject::EndCommand()
{
}

bool CreateGameObject::IsCommandCompleted()
{
    return spawned;
}
