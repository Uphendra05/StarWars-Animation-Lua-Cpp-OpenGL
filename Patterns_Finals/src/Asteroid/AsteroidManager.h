#pragma once

#include "../EntityManager/EntityManager.h"
#include "AsteroidFactory.h"

class AsteroidManager : public Entity
{

public:
	AsteroidFactory* factory;

	AsteroidManager();

	static AsteroidManager& GetInstance();

	Asteroid* SpawnAsteroid(const std::string& id, int type);


private:
	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

