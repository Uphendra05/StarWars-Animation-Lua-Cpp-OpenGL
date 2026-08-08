#include "ScaleWithTime.h"
#include "../../Utilities/Lerp.h"
#include "../../Utilities/Remap.h"
#include "../CommandManager/CommandManager.h"

ScaleWithTime::ScaleWithTime(GameObject* gameObject, glm::vec3 scale, float time)
{
	this->time = time;
	this->targetScale = scale;
	this->gameObject = gameObject;
}

void ScaleWithTime::StartCommand()
{
	this->startScale = gameObject->GetTransform()->scale;

	easeInRatio = easeInTime / time;
	easeOutRatio = easeOutTime / time;

	easeOutStart = 1 - easeOutRatio;

	timeStep = 0;
}

void ScaleWithTime::Update()
{
	deltaTime = Timer::GetInstance().deltaTime;
	timeStep += deltaTime / time;

	if (time == 0)
	{
		lerpValue = 1;
		timeStep = 1;
	}
	else if (easeInTime != 0 && timeStep <= easeInRatio)
	{
		lerpValue = EaseIn(easeInMode, timeStep / easeInRatio);
		lerpValue *= easeInRatio;
	}
	else if (easeOutTime != 0 && timeStep >= easeOutStart)
	{
		lerpValue = EaseOut(easeOutMode, (timeStep - easeOutStart) / easeOutRatio);
		lerpValue *= easeOutRatio;
		lerpValue += easeOutStart;
	}
	else
	{
		lerpValue = timeStep;
	}

	gameObject->GetTransform()->SetScale(
		Lerp(startScale, targetScale, lerpValue)
	);
}

void ScaleWithTime::EndCommand()
{
}

bool ScaleWithTime::IsCommandCompleted()
{
	if (!updatedOnce) return false;

	if (lerpValue >= 1)
	{
		return true;
	}

	return false;
}
