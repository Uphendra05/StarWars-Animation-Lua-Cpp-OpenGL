#pragma once

#include "CommandGroup.h"
#include <unordered_map>

class CommandManager
{
public:

	static CommandManager& GetInstance();

	//Commands
	void BeginCommandGroup(
		const std::string& friendlyName, const std::string& groupType, int repeatCount = 0);
	void EndCommandGroup();
	void AddCommand(BaseCommand* command);
	void BindGameObject(GameObject* gameObject);

	GameObject* GetBoundGameObject();

	void Update(float deltaTime);

	BaseCommand* currentCommand;
	CommandGroup* currentCommandGroup = nullptr;

	void TogglePaused();


private:

	int currentGroupIndex = 0;

	bool isPaused = false;

	GameObject* currentGameObject = nullptr;

	std::vector<CommandGroup*> listOfCommandGroups;

};

