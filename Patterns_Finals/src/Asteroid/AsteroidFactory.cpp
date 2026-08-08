#include "AsteroidFactory.h"
#include "../EntityManager/EntityManager.h"

AsteroidFactory::AsteroidFactory()
{
	CacheAsteroidModels();
}

Asteroid* AsteroidFactory::CreateAsteroid(const std::string& id, int type)
{
	Asteroid* asteroid = new Asteroid();

	switch (type)
	{
	case 0:
		asteroid->CreateInstance(*asteroid1);
		asteroid->GetTransform()->SetPosition(glm::vec3(-64, -1.0, 0));
		
		break;

	case 1:
		asteroid->CreateInstance(*asteroid2);
		break;

	case 2:
		asteroid->CreateInstance(*asteroid3);
		break;
	case 3:
		asteroid->CreateInstance(*asteroid4);
		asteroid->GetTransform()->SetPosition(glm::vec3(-43.2, 0.25, 1));
		break;
	case 4:
		asteroid->CreateInstance(*explodeSphere);
		break;
	}


	asteroid->tag = id;

	renderer->AddModel(asteroid->model, shader);
	physicsEngine->AddPhysicsObject(asteroid->phyObj);


	EntityManager::GetInstance().AddEntity(id, asteroid);

	return asteroid;
}

void AsteroidFactory::AssignComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	this->renderer = renderer;
	this->shader = shader;
	this->physicsEngine = physicsEngine;
}

void AsteroidFactory::CacheAsteroidModels()
{
	asteroid1 = new Model("Assets/Models/Asteroids/Asteroid_001.ply");
	asteroid2 = new Model("Assets/Models/Asteroids/Asteroid_007.ply");
	asteroid3 = new Model("Assets/Models/Asteroids/asteroid_group_375084_verts.ply");
	asteroid4 = new Model("Assets/Models/Asteroids/Asteroid_004.ply");
	explodeSphere = new Model("res/Models/DefaultSphere.fbx");

	asteroid1->transform.SetScale(glm::vec3(0.001f));
	asteroid2->transform.SetScale(glm::vec3(0.001f));
	asteroid3->transform.SetScale(glm::vec3(0.001f));
	asteroid4->transform.SetScale(glm::vec3(0.002f));
	explodeSphere->transform.SetScale(glm::vec3(0.0f));
	

	asteroid1->meshes[0]->material->AsMaterial()->SetBaseColor(asteroidColor);
	asteroid2->meshes[0]->material->AsMaterial()->SetBaseColor(asteroidColor);
	asteroid3->meshes[0]->material->AsMaterial()->SetBaseColor(asteroidColor);
	asteroid4->meshes[0]->material->AsMaterial()->SetBaseColor(asteroidColor);
	explodeSphere->meshes[0]->material->AsMaterial()->SetBaseColor(glm::vec4(1,0,0,1));

}
