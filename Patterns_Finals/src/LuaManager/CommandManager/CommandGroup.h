#pragma once

#include <vector>
#include <string>
#include "BaseCommand.h"

enum CommandGroupType
{
	SEQUENCE,
	PARALLEL,
};

struct CommandGroup
{

public:

	int id;
	int repeatCount = 0;

	bool conditionMet = true;

	std::string friendlyName;
	CommandGroupType groupType;
	
	std::vector<BaseCommand*> listOfCommands;

	void SetCommandGroupType(const std::string& type);

	void Start();
	void Update();

	void AddCommand(BaseCommand* command);
	BaseCommand* GetLastCommand();

	CommandGroup* parentGroup = nullptr;

};

