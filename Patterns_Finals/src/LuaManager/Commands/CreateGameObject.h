#pragma once

#include "../CommandManager/BaseCommand.h"

class CreateGameObject : public BaseCommand
{

public:
	CreateGameObject(const std::string& objectId);

	// Inherited via BaseCommand
	void StartCommand() override;
	void Update() override;
	void EndCommand() override;
	bool IsCommandCompleted() override;

private:

	bool spawned = false;

	std::string objectId;
};

