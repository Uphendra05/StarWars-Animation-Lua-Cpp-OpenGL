#pragma once

#include "../../GameObject/GameObject.h"
#include <Graphics/Timer.h>

class CommandGroup;

class BaseCommand
{
public:
	bool inProgress = false;
	bool updatedOnce = false;

	CommandGroup* commandGroup = nullptr;

	virtual ~BaseCommand() {};

	virtual void StartCommand() = 0;
	virtual void Update() = 0;
	virtual void EndCommand() = 0;
	virtual bool IsCommandCompleted() = 0;
};

