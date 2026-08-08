#include "FighterFactory.h"
#include "../EntityManager/EntityManager.h"


FighterFactory::FighterFactory()
{
	CacheAsteroidModels();
}

Fighter* FighterFactory::CreateFighter(const std::string& id)
{
	Fighter* newFighter = new Fighter();

	newFighter->CreateInstance(*fighter);

	newFighter->tag = id;

	renderer->AddModel(newFighter->model, shader);
	physicsEngine->AddPhysicsObject(newFighter->phyObj);

	EntityManager::GetInstance().AddEntity(id, newFighter);

	return newFighter;
}

void FighterFactory::AssignComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	this->renderer = renderer;
	this->shader = shader;
	this->physicsEngine = physicsEngine;
}

void FighterFactory::CacheAsteroidModels()
{
	fighter = new Model("Assets/Models/Fighter/TIE-fighter_xyz_n_rgba_130744_verts.ply");
	fighter->transform.SetScale(glm::vec3(0.001f));

}
