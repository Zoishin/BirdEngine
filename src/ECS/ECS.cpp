#include "ECS.h"




int Entity::GetId() const {
	return id;
}

void System::AddEntity2System(Entity entity){
	entites.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity){
	entites.erase(std::remove_if(entites.begin(), entites.end(), [&entity](Entity other) {
		return entity == other; }), entites.end());
}

std::vector<Entity> System::GetSystemEntyties() const{
	return entites;
}

const Signature& System::GetComponentSignature() const{
	return componentSignature;
}
