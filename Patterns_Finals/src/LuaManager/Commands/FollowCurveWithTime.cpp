#include "FollowCurveWithTime.h"
#include "../../Utilities/Lerp.h"


FollowCurveWithTime::FollowCurveWithTime(GameObject* gameObject, float time)
{
	this->gameObject = gameObject;
	this->time = time;
}

void FollowCurveWithTime::StartCommand()
{
	curve->CalculateCurve();

	currentPointIndex = 1;
	lerpTime = time * curve->spacing;

	easeInRatio = easeInTime / time;
	easeOutRatio = easeOutTime / time;

	easeOutStart = 1 - easeOutRatio;

	startPos = curve->GetCachedPointOnCurve(0);
	targetPos = curve->GetCachedPointOnCurve(currentPointIndex);

	dir = glm::normalize(targetPos.point - startPos.point);

}

void FollowCurveWithTime::Update()
{

	if (currentPointIndex >= curve->GetCurveCount()) return;

	deltaTime = Timer::GetInstance().deltaTime;

	timeStep += deltaTime / lerpTime;

	//timeStepCurve += deltaTime;
	timeStepCurve = timeStep * curve->spacing * currentPointIndex;

	if (time == 0)
	{
		lerpValue = 1;
		timeStep = 1;
	}
	else if (easeInTime != 0 && timeStepCurve <= easeInRatio)
	{
		lerpValue = EaseIn(easeInMode, timeStepCurve / easeInRatio);
		lerpValue *= easeInRatio;
		lerpValue /= (curve->spacing * currentPointIndex);
	}
	else if (easeOutTime != 0 && timeStepCurve >= easeOutStart)
	{
		lerpValue = EaseOut(easeOutMode, (timeStepCurve - easeOutStart) / easeOutRatio);
		lerpValue *= easeOutRatio;
		lerpValue += easeOutStart;
		lerpValue /= (curve->spacing * currentPointIndex);
	}
	else
	{
		lerpValue = timeStep;
	}



	gameObject->GetTransform()->SetPosition(
		Lerp(startPos.point, targetPos.point, lerpValue)
	);

	glm::vec3 rotationOffset = Lerp(startPos.rotationOffset, targetPos.rotationOffset, lerpValue);

	//curve->DrawCurve();
	//Debugger::Print("Rotation		:", gameObject->GetTransform()->rotation);

	if (!lookAtTangent) return;

	if (currentPointIndex >= curve->GetCurveCount() - 2) return;

	gameObject->GetTransform()->SetOrientationFromDirections(up, right);
	glm::vec3 totalRotation;
	totalRotation.x = gameObject->GetTransform()->rotation.x + lookAtOffset.x + rotationOffset.x;
	totalRotation.y = gameObject->GetTransform()->rotation.y + lookAtOffset.y + rotationOffset.y;
	totalRotation.z = gameObject->GetTransform()->rotation.z + lookAtOffset.z + rotationOffset.z;

	/*Debugger::Print("LookAtOffset   :", lookAtOffset);
	Debugger::Print("RotationOffset :", rotationOffset);
	Debugger::Print("Total			:", totalRotation);
	std::cout << std::endl;*/

	gameObject->GetTransform()->SetRotation(totalRotation);

}

void FollowCurveWithTime::EndCommand()
{
}

bool FollowCurveWithTime::IsCommandCompleted()
{
	if (!updatedOnce) return false;

	if (lerpValue >= 1.0f)
	{
		currentPointIndex++;

		if (currentPointIndex >= curve->GetCurveCount())
		{
			return true;
		}

		timeStep = 0;
		lerpValue = 0;
		startPos = targetPos;
		targetPos = curve->GetCachedPointOnCurve(currentPointIndex);

		dir = glm::normalize(targetPos.point - startPos.point);
		right = glm::cross(glm::vec3(0, 1, 0), dir);
		up = glm::cross(dir, right);
	}

	return false;
}

void FollowCurveWithTime::SetBezierCurve(CubicBezierCurve* curve)
{
	this->curve = curve;
}

void FollowCurveWithTime::AddPoint(const glm::vec3& point, const glm::vec3& controlPoint, const glm::vec3& rotationOffset)
{
	if (curve == nullptr) return;
	curve->AddPoint(CubicBezierPoint{ point,controlPoint, rotationOffset });
}

void FollowCurveWithTime::SetLookAtTangent(bool state)
{
	this->lookAtTangent = state;
}

void FollowCurveWithTime::SetLookAtOffset(const glm::vec3& offset)
{
	this->lookAtOffset = offset;
}
