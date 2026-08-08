#pragma once

#include "../CommandManager/BaseCommand.h"
#include "../CommandManager/EaseCommand.h"

class MoveToPosWithTime : public BaseCommand, public EaseCommand
{

public:
	MoveToPosWithTime(GameObject* gameObject, glm::vec3 pos, float time);

	// Inherited via BaseCommand
	void StartCommand() override;
	void Update() override;
	void EndCommand() override;
	bool IsCommandCompleted() override;

private:

	float time;
	float timeStep = 0;
	float deltaTime = 0;
	float lerpValue = 0;

	glm::vec3 startPos;
	glm::vec3 targetPos;

	GameObject* gameObject;
};

