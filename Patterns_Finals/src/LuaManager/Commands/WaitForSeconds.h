#pragma once

#include "../CommandManager/BaseCommand.h"

class WaitForSeconds : public BaseCommand
{

public:
	WaitForSeconds(float time);

	// Inherited via BaseCommand
	void StartCommand() override;
	void Update() override;
	void EndCommand() override;
	bool IsCommandCompleted() override;

private:
	float time = 0;
	float timeStep = 0;
};

