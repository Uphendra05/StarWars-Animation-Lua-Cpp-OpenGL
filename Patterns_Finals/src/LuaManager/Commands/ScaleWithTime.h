#pragma once


#include "../CommandManager/BaseCommand.h"
#include "../CommandManager/EaseCommand.h"


class ScaleWithTime : public BaseCommand, public EaseCommand
{

public:
	ScaleWithTime(GameObject* gameObject, glm::vec3 scale, float time);


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

	glm::vec3 startScale;
	glm::vec3 targetScale;

	GameObject* gameObject;

};
