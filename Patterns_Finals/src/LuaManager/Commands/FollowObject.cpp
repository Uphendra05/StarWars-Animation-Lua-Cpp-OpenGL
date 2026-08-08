#include "FollowObject.h"
#include "../../Utilities/Lerp.h"
#include "../../Utilities/Remap.h"

FollowObject::FollowObject(GameObject* followObject, GameObject* targetObject, float time)
{
	this->followObject = followObject;
	this->targetObject = targetObject;
	this->time = time;
	
}

void FollowObject::StartCommand()
{
	timeStep = 0;

	glm::vec3 diff = targetObject->GetTransform()->position - followObject->GetTransform()->position;
	//followDistance = glm::length(diff);

	startDir = glm::normalize(diff);

	sqDeacceleration = deaccelerationRange * deaccelerationRange;
	sqAcceleration = accelerationRange * accelerationRange;
}

void FollowObject::Update()
{
	deltaTime = Timer::GetInstance().deltaTime;

	timeElapsed += deltaTime;

	startPos = followObject->GetTransform()->position;
	targetPos = targetObject->GetTransform()->position + followOffset;

	glm::vec3 diff = targetPos - startPos;

	if (simpleFollow)
	{
		targetPos -= startDir * followDistance;
		//followObject->GetTransform()->SetPosition(targetPos);

	}
	else
	{
		glm::vec3 dir = glm::normalize(diff);
		targetPos -= dir * followDistance;
	}


	diff = targetPos - startPos;
	sqDist = glm::dot(diff, diff);

	targetPos.x = followAxis.x == 1 ? targetPos.x : startPos.x;
	targetPos.y = followAxis.y == 1 ? targetPos.y : startPos.y;
	targetPos.z = followAxis.z == 1 ? targetPos.z : startPos.z;

	float remapedValue;
	if (sqAcceleration != 0 && sqDist >= sqAcceleration)
	{
		remapedValue = 1;
	}
	else if (sqDeacceleration != 0 && sqDist <= sqDeacceleration)
	{
		remapedValue = remap(sqDist, 0, sqDeacceleration, 0, 1);
	}
	else if(sqDeacceleration != 0 && sqAcceleration != 0)
	{
		remapedValue = remap(sqDist, sqDeacceleration, sqAcceleration, 0.5, 1.0f);
	}
	else
	{
		remapedValue = 1;
	}

	timeStep = CalculateTForSpeed(timeStep, deltaTime, maxSpeed * remapedValue);



	followObject->GetTransform()->SetPosition(
		Lerp(startPos, targetPos, timeStep)
	);
}

void FollowObject::EndCommand()
{
}

bool FollowObject::IsCommandCompleted()
{
	if (timeElapsed >= time)
	{
		return true;
	}
	
	return false;
}

void FollowObject::SetFollowDistance(const float& followDistance)
{
	this->followDistance = followDistance;
}

void FollowObject::SetMaxSpeed(const float& maxSpeed)
{
	this->maxSpeed = maxSpeed;
}

void FollowObject::SetFollowOffset(const glm::vec3& offset)
{
	this->followOffset = offset;
}

void FollowObject::SetAccelerationRange(const float& range)
{
	accelerationRange = range;
}

void FollowObject::SetDeaccelerationRange(const float& range)
{
	deaccelerationRange = range;
}

void FollowObject::SetSimpleFollow(bool state)
{
	simpleFollow = state;
}

void FollowObject::SetFollowAxis(const glm::vec3& followAxis)
{
	this->followAxis = followAxis;
}

