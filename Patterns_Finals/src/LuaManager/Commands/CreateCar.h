#pragma once

#include "../CommandManager/BaseCommand.h"

class CreateCar : public BaseCommand
{

public:
	CreateCar(const std::string& carId, int type = 0);

	// Inherited via BaseCommand
	void StartCommand() override;
	void Update() override;
	void EndCommand() override;
	bool IsCommandCompleted() override;

private:

	int type = 0;
	bool spawned = false;

	std::string carId;
};

