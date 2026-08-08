#include "RotateWithTime.h"
#include "../../Utilities/Lerp.h"

RotateWithTime::RotateWithTime(GameObject* gameObject, glm::vec3 rotation, float time)
{
    this->gameObject = gameObject;
    this->targetRotation = rotation;
    this->time = time;
}

void RotateWithTime::StartCommand()
{
    startRotation = gameObject->GetTransform()->rotation;
    timeStep = 0;
}

void RotateWithTime::Update()
{
    float lerpValue;

    if (time == 0)
    {
        timeStep = time;
        lerpValue = 1;
    }
    else
    {
        timeStep += Timer::GetInstance().deltaTime;

        if (easeInTime != 0 && timeStep <= easeInTime)
        {
            lerpValue = EaseIn(easeInMode, timeStep / easeInTime);
            lerpValue *= easeInTime / time;
        }
        else if (easeOutTime != 0 && timeStep > time - easeOutTime)
        {
            lerpValue = EaseOut(easeOutMode, (timeStep - (time - easeOutTime)) / easeOutTime);
            lerpValue *= easeOutTime / time;
            lerpValue += 1 - (easeOutTime / time);
        }
        else
        {
            lerpValue = timeStep / time;
        }
    }

    gameObject->GetTransform()->SetRotation(
        Lerp(startRotation, targetRotation, lerpValue)
    );
}

void RotateWithTime::EndCommand()
{
}

bool RotateWithTime::IsCommandCompleted()
{
    if (!updatedOnce) return false;

    if (timeStep >= time)
    {
        return true;
    }

    return false;
}
