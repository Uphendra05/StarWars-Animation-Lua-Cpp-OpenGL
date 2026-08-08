#pragma once

#include "../EntityManager/EntityManager.h"
#include "FighterFactory.h"

class FighterManager : public Entity
{
public:
	FighterFactory* factory;

	FighterManager();

	static FighterManager& GetInstance();

	void SpawnFighter(const std::string& id);

private:
	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

