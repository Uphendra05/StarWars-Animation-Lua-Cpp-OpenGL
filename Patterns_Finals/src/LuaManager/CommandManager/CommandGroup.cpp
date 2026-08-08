#include "CommandGroup.h"
#include "../Commands/WaitForSeconds.h"

void CommandGroup::SetCommandGroupType(const std::string& type)
{
	if (type == "Serial")
	{
		this->groupType = SEQUENCE;
	}
	else if (type == "Parallel")
	{
		this->groupType = PARALLEL;
	}
	else
	{
		this->groupType = SEQUENCE;
	}
}

void CommandGroup::Start()
{
	if (groupType == SEQUENCE)
	{
		for (BaseCommand* command : listOfCommands)
		{
			if (command->IsCommandCompleted()) continue;

			command->StartCommand();
			command->inProgress = true;

			return;
		}
	}
	else if (groupType == PARALLEL)
	{
		for (BaseCommand* command : listOfCommands)
		{
			if (command == nullptr) continue;

			if (WaitForSeconds* waitCommand = dynamic_cast<WaitForSeconds*>(command))
			{
				command->StartCommand();
				command->inProgress = true;
				if (!command->IsCommandCompleted()) return;
			}

			command->StartCommand();
			command->inProgress = true;


		}
	}
}

void CommandGroup::Update()
{
	if (groupType == SEQUENCE)
	{
		for (BaseCommand* command : listOfCommands)
		{
			if (command->IsCommandCompleted()) continue;

			if (!command->inProgress)
			{
				command->StartCommand();
				command->inProgress = true;
			}

			command->Update();
			command->updatedOnce = true;

			return;
		}
	}
	else if (groupType == PARALLEL)
	{
		for (BaseCommand* command : listOfCommands)
		{
			if (command == nullptr) continue;

			if (WaitForSeconds* waitCommand = dynamic_cast<WaitForSeconds*>(command))
			{
				if (!command->IsCommandCompleted())
				{
					command->Update();
					command->updatedOnce = true;
					command->inProgress = true;
					return;
				}
			}

		

			if (!command->inProgress)
			{
				
				command->StartCommand();
				command->inProgress = true;
			}

			if (command->IsCommandCompleted()) continue;


			command->Update();
			command->updatedOnce = true;
		}
	}
}

void CommandGroup::AddCommand(BaseCommand* command)
{
	listOfCommands.push_back(command);
}

BaseCommand* CommandGroup::GetLastCommand()
{
	return listOfCommands[listOfCommands.size() - 1];
}
