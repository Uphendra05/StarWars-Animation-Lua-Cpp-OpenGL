#include "LookAt.h"

LookAt::LookAt(GameObject* gameObject, GameObject* lookAtObject, float time)
{
	this->gameObject = gameObject;
	this->lookAtObject = lookAtObject;
	this->time = time;
}

void LookAt::StartCommand()
{
}

void LookAt::Update()
{
	timeElapsed += Timer::GetInstance().deltaTime;

	diff = lookAtObject->GetTransform()->position - gameObject->GetTransform()->position;
	dir = glm::normalize(diff);

	right = glm::cross(glm::vec3(0, 1, 0), dir);
	up = glm::cross(dir, right);

	gameObject->GetTransform()->SetOrientationFromDirections(up, right);

	if (gameObject->entityId == "Camera")
	{
		float pitch = gameObject->GetTransform()->rotation.x;
		pitch = glm::clamp(pitch, -89.0f, 89.0f);
		gameObject->GetTransform()->SetRotation(glm::vec3(pitch,
			gameObject->GetTransform()->rotation.y,0));

		return;
	}

	gameObject->GetTransform()->SetRotation(gameObject->GetTransform()->rotation + lookAtOffset);
}

void LookAt::EndCommand()
{
}

bool LookAt::IsCommandCompleted()
{
	if (timeElapsed >= time)
	{
		return true;
	}
	return false;
}

void LookAt::SetLookAtOffset(const glm::vec3& offset)
{
	this->lookAtOffset = offset;
}
