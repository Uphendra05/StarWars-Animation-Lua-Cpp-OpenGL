#pragma once

#include "../CommandManager/BaseCommand.h"
#include "../CommandManager/EaseCommand.h"

class MoveWithSpeed : public BaseCommand, public EaseCommand
{
public:

	MoveWithSpeed(GameObject* gameObject, glm::vec3 pos, float speed);

	// Inherited via BaseCommand
	void StartCommand() override;
	void Update() override;
	void EndCommand() override;
	bool IsCommandCompleted() override;

private:
	double speed;
	double timeStep = 0;

	glm::vec3 startPos;
	glm::vec3 targetPos;

	GameObject* gameObject;
};

