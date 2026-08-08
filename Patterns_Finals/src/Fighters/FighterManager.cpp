#include "FighterManager.h"
#include "../LuaManager/LuaManager.h"


FighterManager::FighterManager()
{
	factory = new FighterFactory();
	InitializeEntity(this);

}

FighterManager& FighterManager::GetInstance()
{
	static FighterManager instance;
	return instance;
}

void FighterManager::SpawnFighter(const std::string& id)
{
	Fighter* fighter = factory->CreateFighter(id);
	LuaManager::GetInstance().AddGameObject(id, fighter);

}

void FighterManager::Start()
{
}

void FighterManager::Update(float deltaTime)
{
}

void FighterManager::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	factory->AssignComponents(renderer, shader, physicsEngine);
}

void FighterManager::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
