#include "MoveToPosWithTime.h"
#include "../../Utilities/Lerp.h"
#include "../../Utilities/Remap.h"
#include "../CommandManager/CommandManager.h"

float startTime = 0;

MoveToPosWithTime::MoveToPosWithTime(GameObject* gameObject, glm::vec3 pos, float time)
{
	this->time = time;
	this->targetPos = pos;
	this->gameObject = gameObject;
}

void MoveToPosWithTime::StartCommand()
{
	
	this->startPos = gameObject->GetTransform()->position;

	easeInRatio = easeInTime / time;
	easeOutRatio = easeOutTime / time;

	easeOutStart = 1 - easeOutRatio;

	timeStep = 0;

	startTime = Timer::GetInstance().currentTime;
}


void MoveToPosWithTime::Update()
{
	deltaTime = Timer::GetInstance().deltaTime;

    /*if (time == 0)
    {
        timeStep = time;
        lerpValue = 1;
    }
    else
    {
        timeStep += Time::GetInstance().deltaTime; //Time Step 0 - time

        if (easeInTime != 0 &&  timeStep <= easeInTime) 
        {
            lerpValue = EaseIn(easeInMode ,timeStep / easeInTime);
            lerpValue *= easeInTime / time;
        }
        else if (easeOutTime != 0 && timeStep > time - easeOutTime)
        {
            lerpValue = EaseOut(easeOutMode ,( timeStep - (time - easeOutTime) )/ easeOutTime);
            lerpValue *= easeOutTime / time;
            lerpValue += 1 - (easeOutTime / time);
        }
        else
        {
            lerpValue = timeStep/time;
        }
    }
	*/

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

    gameObject->GetTransform()->SetPosition(
        Lerp(startPos, targetPos, lerpValue)
    );
}

void MoveToPosWithTime::EndCommand()
{
}

bool MoveToPosWithTime::IsCommandCompleted()
{
	if (!updatedOnce) return false;

	if (lerpValue >= 1)
	{
		return true;
	}

	return false;
}
