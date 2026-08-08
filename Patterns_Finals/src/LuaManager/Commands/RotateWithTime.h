#pragma once

#include "../CommandManager/BaseCommand.h"
#include "../CommandManager/EaseCommand.h"

class RotateWithTime : public BaseCommand , public EaseCommand
{
public:
	RotateWithTime(GameObject* gameObject, glm::vec3 rotation, float time);

	// Inherited via BaseCommand
	void StartCommand() override;
	void Update() override;
	void EndCommand() override;
	bool IsCommandCompleted() override;

private:
	float time = 0;
	float timeStep = 0;

	GameObject* gameObject;
	glm::vec3 startRotation;
	glm::vec3 targetRotation;
};

