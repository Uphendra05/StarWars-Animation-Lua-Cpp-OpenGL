#include "CreateCar.h"
#include "../LuaManager.h"

CreateCar::CreateCar(const std::string& carId, int type)
{
    this->carId = carId;
    this->type = type;
}

void CreateCar::StartCommand()
{
    LuaManager::GetInstance().GetGameObjectWithID(carId)->model->isActive = true;
    spawned = true;
}

void CreateCar::Update()
{
}

void CreateCar::EndCommand()
{
}

bool CreateCar::IsCommandCompleted()
{
    return spawned;
}
