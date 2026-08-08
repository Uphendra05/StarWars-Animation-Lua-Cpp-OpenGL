#pragma once

#include "../CommandManager/BaseCommand.h"
#include "../../Utilities/BezierCurve/CubicBezierCurve.h"
#include "../CommandManager/EaseCommand.h"

class FollowCurveWithTime : public BaseCommand, public EaseCommand
{
public:

	FollowCurveWithTime(GameObject* gameObject, float time);

	// Inherited via BaseCommand
	void StartCommand() override;
	void Update() override;
	void EndCommand() override;
	bool IsCommandCompleted() override;

	void SetBezierCurve(CubicBezierCurve* curve);
	void AddPoint(const glm::vec3& point, const glm::vec3& controlPoint, const glm::vec3& rotationOffset);
	void SetLookAtTangent(bool state);
	void SetLookAtOffset(const glm::vec3& offset);

private:

	int currentPointIndex = 0;

	bool lookAtTangent = 0;

	float time;
	float lerpTime = 0;
	float lerpValue= 0;
	float timeStep = 0;
	float deltaTime = 0;

	float timeStepCurve = 0;

	PointOnCurve startPos{ glm::vec3(0), glm::vec3(0),  glm::vec3(0) };
	PointOnCurve targetPos{ glm::vec3(0), glm::vec3(0),glm::vec3(0) };

	glm::vec3 right;
	glm::vec3 dir;
	glm::vec3 up = glm::vec3(0,1,0);
	glm::vec3 lookAtOffset = glm::vec3(0);

	GameObject* gameObject;
	CubicBezierCurve* curve = nullptr;

};

