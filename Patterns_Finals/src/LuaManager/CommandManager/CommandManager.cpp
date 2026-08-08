#include <Graphics/Debugger.h>

#include "CommandManager.h"

CommandManager& CommandManager::GetInstance()
{
	static CommandManager instance;
	return instance;
}

void CommandManager::BeginCommandGroup(
	const std::string& friendlyName, const std::string& groupType, int repeatCount)
{

	CommandGroup* newCommandGroup = new CommandGroup();

	if (currentCommandGroup != nullptr)
	{
		newCommandGroup->parentGroup = currentCommandGroup;
	}

	newCommandGroup->id = currentGroupIndex;
	newCommandGroup->friendlyName = friendlyName;
	newCommandGroup->repeatCount = repeatCount;
	newCommandGroup->SetCommandGroupType(groupType);

	listOfCommandGroups.push_back(newCommandGroup);

	Debugger::Print("Begin Command Group : ", friendlyName);

	currentCommandGroup = newCommandGroup;
	currentGroupIndex++;
}

void CommandManager::EndCommandGroup()
{
	currentCommandGroup->Start();

	currentCommandGroup = currentCommandGroup->parentGroup;
}

void CommandManager::AddCommand(BaseCommand* command)
{
	if (currentCommandGroup == nullptr)
	{
		std::cout << "No Command Group Available!!!" << std::endl;
		return;
	}

	currentCommandGroup->AddCommand(command);
	currentCommand = command;

	command->commandGroup = currentCommandGroup;
}

void CommandManager::BindGameObject(GameObject* gameObject)
{
	currentGameObject = gameObject;
}

GameObject* CommandManager::GetBoundGameObject()
{
	if (currentGameObject == nullptr)
	{
		Debugger::Print("No Game Object Bound!!");
	}

	return currentGameObject;
}

void CommandManager::Update(float deltaTime)
{
	if (isPaused) return;

	for (CommandGroup* commandGroup : listOfCommandGroups)
	{
		if (commandGroup->conditionMet)
		{
			commandGroup->Update();
		}
	}

	
}

void CommandManager::TogglePaused()
{
	isPaused = !isPaused;
}
