#include "CameraObject.h"
#include "../LuaManager/LuaManager.h"

CameraObject::CameraObject()
{
	LuaManager::GetInstance().AddGameObject("Camera", this);
	entityId = "Camera";
}

void CameraObject::Start()
{
}

void CameraObject::Update(float deltaTime)
{
}

void CameraObject::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
}

void CameraObject::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

Transform* CameraObject::GetTransform()
{
	return &camera->transform;
}
