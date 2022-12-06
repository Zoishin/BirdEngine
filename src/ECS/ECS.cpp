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

Entity Registry::CreateEntity(){
	int entityId = numEntities++;
	Entity entity(entityId);

	entitesToBeAdded.insert(entity);
	Logger::Log("Entity created with id = " + std::to_string(entityId));
	return entity;
}

void Registry::Update() {
	//TODO: Add the entites that are waiting to be created to the active systems
	//TODO: Remove the entites that are waiting to be killed from the active systems
}