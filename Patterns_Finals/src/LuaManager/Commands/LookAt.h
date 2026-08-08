#pragma once

#include "../CommandManager/BaseCommand.h"

class LookAt : public BaseCommand
{

public:

	LookAt(GameObject* gameObject, GameObject* lookAtObject, float time);

	// Inherited via BaseCommand
	void StartCommand() override;
	void Update() override;
	void EndCommand() override;
	bool IsCommandCompleted() override;

	void SetLookAtOffset(const glm::vec3& offset);

private:

	float time = 0;
	float timeElapsed = 0;

	glm::vec3 diff = glm::vec3(0);
	glm::vec3 dir = glm::vec3(0);
	glm::vec3 right = glm::vec3(0);
	glm::vec3 up = glm::vec3(0);

	glm::vec3 lookAtOffset = glm::vec3(0);


	GameObject* gameObject;
	GameObject* lookAtObject;
};

