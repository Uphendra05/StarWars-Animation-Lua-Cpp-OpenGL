#include "Asteroid.h"

Asteroid::Asteroid()
{
	model = new Model();
	phyObj = new PhysicsObject();
}

void Asteroid::CreateInstance(Model& model)
{
	this->model->CopyFromModel(model);
	phyObj->Initialize(this->model, SPHERE, DYNAMIC, TRIGGER, true);
	phyObj->userData = this;
	phyObj->AssignCollisionCallback([this](PhysicsObject* other)
		{
			Entity* entity = (Entity*)other->userData;

			//Debugger::Print("Tag : ", entity->tag);
		});

}

void Asteroid::Start()
{
}

void Asteroid::Update(float deltaTime)
{
}

void Asteroid::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
}

void Asteroid::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

Transform* Asteroid::GetTransform()
{
	return &model->transform;
}
