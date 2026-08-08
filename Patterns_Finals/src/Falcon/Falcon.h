#pragma once

#include "../GameObject/GameObject.h"
#include "../LuaManager/LuaState.h"

class Falcon : public GameObject
{
public:

	Falcon();

	LuaState* luaState;

private:
	// Inherited via GameObject
	Transform* GetTransform() override;
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

