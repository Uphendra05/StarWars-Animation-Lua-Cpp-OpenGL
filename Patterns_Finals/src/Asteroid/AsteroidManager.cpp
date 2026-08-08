#include "AsteroidManager.h"
#include "../LuaManager/LuaManager.h"

AsteroidManager::AsteroidManager()
{
	factory = new AsteroidFactory();

	InitializeEntity(this);
}

AsteroidManager& AsteroidManager::GetInstance()
{
	static AsteroidManager instance;
	return instance;
}

Asteroid* AsteroidManager::SpawnAsteroid(const std::string& id, int type)
{
	Asteroid* asteroid = factory->CreateAsteroid(id, type);
	LuaManager::GetInstance().AddGameObject(id, asteroid);

	return asteroid;
}

void AsteroidManager::Start()
{
}

void AsteroidManager::Update(float deltaTime)
{
}

void AsteroidManager::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	factory->AssignComponents(renderer, shader, physicsEngine);
}

void AsteroidManager::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
