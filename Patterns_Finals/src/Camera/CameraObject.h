#pragma once

#include "../GameObject/GameObject.h"
#include <Graphics/Camera.h>

class CameraObject : public GameObject
{

public:
	Camera* camera;

	CameraObject();

	// Inherited via GameObject
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

	// Inherited via GameObject
	Transform* GetTransform() override;
};

