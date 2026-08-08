#pragma once

#include "../GameObject/GameObject.h"

class Asteroid : public GameObject
{

public:

	Asteroid();

	void CreateInstance(Model& model);


	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

	// Inherited via GameObject
	Transform* GetTransform() override;
};

