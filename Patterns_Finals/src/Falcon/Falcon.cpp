#include "Falcon.h"

Falcon::Falcon()
{
	InitializeEntity(this);

	entityId = "Falcon";
	tag = "Falcon";

	luaState = new LuaState(this);
}

Transform* Falcon::GetTransform()
{
	return &model->transform;
}

void Falcon::Start()
{
}

void Falcon::Update(float deltaTime)
{
}

void Falcon::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	model = new Model("Assets/Models/Falcon/Falcon_Body_281291_verts.ply");
	model->transform.SetPosition(glm::vec3(0));
	model->transform.SetRotation(glm::vec3(0, 0, -90));
	model->transform.SetScale(glm::vec3(0.01f));
	model->meshes[0]->material->AsMaterial()->SetBaseColor(glm::vec4(0.8, 0.8, 0.8, 1.0));

	renderer->AddModel(model, shader);
}

void Falcon::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
