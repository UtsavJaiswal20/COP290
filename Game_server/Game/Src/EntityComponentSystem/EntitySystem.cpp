#include "EntitySystem.h"

void Entity::addGroup(Group mGroup) {
	grobitset[mGroup] = true;
	manager.Addtogroup(this, mGroup);
}