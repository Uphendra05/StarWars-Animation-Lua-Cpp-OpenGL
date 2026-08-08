#include "GameObject.h"
#include "../LuaManager/CommandManager/CommandGroup.h"

void GameObject::AddCollisionGroup(const std::string& tag, CommandGroup* group)
{
	this;
	listOfCollisionGroups[tag] = group;
}
