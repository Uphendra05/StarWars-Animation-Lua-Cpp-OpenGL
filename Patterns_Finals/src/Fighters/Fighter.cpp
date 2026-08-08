#include "Fighter.h"
#include "../LuaManager/CommandManager/CommandGroup.h"

Fighter::Fighter()
{
	model = new Model();
	phyObj = new PhysicsObject();
}

void Fighter::CreateInstance(Model& model)
{
	this->model->CopyFromModel(model);
	phyObj->Initialize(this->model, SPHERE, DYNAMIC, TRIGGER, true);
	phyObj->userData = this;
	phyObj->AssignCollisionCallback([this](PhysicsObject* other)
		{
			Entity* entity = (Entity*)other->userData;


			std::unordered_map <std::string, CommandGroup*>::iterator it = listOfCollisionGroups.find(entity->tag);

			if (it != listOfCollisionGroups.end())
			{
				Debugger::Print("Collided With : ", entity->tag);
				it->second->conditionMet = true;
			}
		});
}

void Fighter::Start()
{
}

void Fighter::Update(float deltaTime)
{
}

void Fighter::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
}

void Fighter::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

Transform* Fighter::GetTransform()
{
	return &model->transform;
}
