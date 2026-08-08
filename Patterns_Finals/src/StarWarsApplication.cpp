#include "StarWarsApplication.h"
#include "Utilities/RendererInstance.h"
#include "EntityManager/EntityManager.h"
#include "Falcon/Falcon.h"
#include "LuaManager/LuaManager.h"
#include "Camera/CameraObject.h"
#include "LuaManager/CommandManager/CommandManager.h"


void StarWarsApplication::SetUp()
{
	physicsEngine.fixedStepTime = 0.01f;
	physicsEngine.gravity.y = 0;
	moveSpeed = 1;

	stopKeyCallback = true;
	stopMouseCallback = true;

	RendererInstance::GetInstance().SetRenderer(&renderer);

	camera->InitializeCamera(PERSPECTIVE, windowWidth, windowHeight, 0.01f, 1000.0f, 65.0f);

	camera->transform.SetPosition(glm::vec3(0, 0, 3));
	camera->transform.SetRotation(glm::vec3(0, 0, 0));

	EntityManager::GetInstance().AddToRendererAndPhysics(&renderer, &defShader, &physicsEngine);

#pragma region Skybox

	skyBox->meshes[0]->material = new SkyBoxMaterial();
	SkyBoxMaterial* skyboxMat = skyBox->meshes[0]->material->AsSkyBoxMaterial();

	skyboxMat->skyBoxTexture->LoadTexture({
		"Assets/Textures/Skybox/Right.jpg",
		"Assets/Textures/Skybox/Left.jpg",
		"Assets/Textures/Skybox/Up.jpg",
		"Assets/Textures/Skybox/Down.jpg",
		"Assets/Textures/Skybox/Front.jpg",
		"Assets/Textures/Skybox/Back.jpg",
		});

#pragma endregion

#pragma region Light

	Model* lightModel = new Model("res/Models/DefaultSphere.fbx", false);
	lightModel->transform.SetScale(glm::vec3(0.01f));
	renderer.AddModel(lightModel, &solidColorShader);

	Light* dirLight = new Light();
	dirLight->InitializeLight(lightModel, Directional);
	dirLight->intensity = 0.7f;
	dirLight->transform->SetRotation(glm::vec3(-30, 0, 0));

	lightManager.AddLight(dirLight);

#pragma endregion

	CameraObject* cameraObject = new CameraObject();
	cameraObject->camera = camera;
	
	Falcon* falcon = new Falcon();
	LuaManager::GetInstance().ExecuteGlobalState();

	EntityManager::GetInstance().Start();

}

void StarWarsApplication::PreRender()
{
	physicsEngine.Update(Timer::GetInstance().deltaTime);
	EntityManager::GetInstance().Update(Timer::GetInstance().deltaTime);
	CommandManager::GetInstance().Update(Timer::GetInstance().deltaTime);
}

void StarWarsApplication::PostRender()
{
}

void StarWarsApplication::ProcessInput(GLFWwindow* window)
{
	std::stringstream ssTitle;
	ssTitle << "Camera Pos : "
		<< camera->transform.position.x << " , "
		<< camera->transform.position.y << " , "
		<< camera->transform.position.z
		<< "  Camera Pitch : "
		<< camera->transform.rotation.x
		<< "  Camera Yaw : "
		<< camera->transform.rotation.y;

	std::string theTitle = ssTitle.str();

	glfwSetWindowTitle(window, theTitle.c_str());
}

void StarWarsApplication::KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_SPACE)
		{
			CommandManager::GetInstance().TogglePaused();
			ToggleFreeCam();
		}

	}
}

void StarWarsApplication::MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods)
{
}


void StarWarsApplication::ToggleFreeCam()
{
	isFreeCam = !isFreeCam;

	stopKeyCallback = !isFreeCam;
	stopMouseCallback = !isFreeCam;


	if (isFreeCam)
	{
		lastCameraPos = camera->transform.position;
		lastCameraRot = camera->transform.rotation;
	}
	else
	{
		camera->transform.SetPosition(lastCameraPos);
		camera->transform.SetRotation(lastCameraRot);
	}

	
}
