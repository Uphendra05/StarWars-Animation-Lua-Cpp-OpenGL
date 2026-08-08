#pragma once

#include "../CommandManager/BaseCommand.h"

class FollowObject : public BaseCommand
{

public:

	FollowObject(GameObject* followObject, GameObject* targetObject, float time);

	// Inherited via BaseCommand
	void StartCommand() override;
	void Update() override;
	void EndCommand() override;
	bool IsCommandCompleted() override;

	void SetFollowDistance(const float& followDistance);
	void SetMaxSpeed(const float& maxSpeed);
	void SetFollowOffset(const glm::vec3& offset);
	void SetAccelerationRange(const float& range);
	void SetDeaccelerationRange(const float& range);
	void SetSimpleFollow(bool state);
	void SetFollowAxis(const glm::vec3& followAxis);

private:

	float time = 0;
	float timeStep = 0;
	float timeElapsed = 0;
	float deltaTime = 0;
	float followDistance = 10;
	float speed = 0;
	float maxSpeed = 0.01;
	float accelerationRange = 0;
	float deaccelerationRange = 0;

	float sqDist = 0;
	float sqAcceleration = 0;
	float sqDeacceleration = 0;

	bool simpleFollow = false;

	glm::vec3 followOffset = glm::vec3(0);
	glm::vec3 startPos = glm::vec3(0);
	glm::vec3 targetPos = glm::vec3(0);
	glm::vec3 startDir = glm::vec3(0);
	glm::vec3 followAxis = glm::vec3(1);

	GameObject* followObject;
	GameObject* targetObject;

};

