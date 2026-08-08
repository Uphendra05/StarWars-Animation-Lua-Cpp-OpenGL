#pragma once

#include "Fighter.h"

class FighterFactory
{
public:
	FighterFactory();
	Fighter* CreateFighter(const std::string& id);
	void AssignComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine);


private:

	Renderer* renderer;
	Shader* shader;
	PhysicsEngine* physicsEngine;

	Model* fighter;

	void CacheAsteroidModels();

};

