#pragma once

#include "Asteroid.h"

class AsteroidFactory
{

public:
	AsteroidFactory();
	Asteroid* CreateAsteroid(const std::string& id, int type = 0);
	void AssignComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine);

private:

	Renderer* renderer;
	Shader* shader;
	PhysicsEngine* physicsEngine;

	Model* asteroid1;
	Model* asteroid2;
	Model* asteroid3;
	Model* asteroid4;
	Model* explodeSphere;

	glm::vec4 asteroidColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);

	void CacheAsteroidModels();
};

