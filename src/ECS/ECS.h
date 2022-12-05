#ifndef  ECS_H
#define ECS_H

#include <bitset>
#include <vector>
#include <iterator>
#include <unordered_map>
#include <type_index>

const unsigned int MAX_COMPONENTS = 32;

///////////////////////////////////////////////////////////////////////////////////////
// Signature
///////////////////////////////////////////////////////////////////////////////////////
// We use a bitset to keep track of which component an entity has,
// and also helps keep track of which entites a system is interested in
///////////////////////////////////////////////////////////////////////////////////////
using Signature = std::bitset<MAX_COMPONENTS>;

struct IComponent {
protected:
	static int nextId;
};

template <typename T>
class Component : public IComponent {
	//Return the unique id of Comonent<T>
	static int GetId() {
		static auto id = nextId++;
		return id;
	}
};

class Entity {
private:
	int id;

public:
	Entity(int id) : id(id) {};
	Entity(const Entity& entity) = default;
	int GetId() const;

	Entity& operator =(const Entity& other) = default;
	bool operator ==(const Entity& other) const { return id == other.id; }
	bool operator !=(const Entity& other) const { return id != other.id; }
	bool operator >(const Entity& other) const { return id > other.id; }
	bool operator <(const Entity& other) const { return id < other.id; }
};

///////////////////////////////////////////////////////////////////////////////////////
/// System
///////////////////////////////////////////////////////////////////////////////////////
// The system process entites that contain a specific signature
///////////////////////////////////////////////////////////////////////////////////////

class System {
private:
	Signature componentSignature;
	std::vector<Entity> entites;

public:
	System() = default;
	~System() = default;

	void AddEntity2System(Entity entity);
	void RemoveEntityFromSystem(Entity entity);
	std::vector<Entity> GetSystemEntyties() const;
	const Signature& GetComponentSignature() const;

	//Define the component type the entity must have to be 
	//considered by the system
	template <typename IComponent> void RequireComponent();
};

///////////////////////////////////////////////////////////////////////////////////////
// Pool
///////////////////////////////////////////////////////////////////////////////////////
// A pool is just a vector (contiguous data) of object of type T
///////////////////////////////////////////////////////////////////////////////////////
class IPool {
public:
	virtual ~IPool() {  }
};


template <typename T>
class Pool :public IPool{
private:
	std::vector<T> data;

public:
	Pool(int size = 100) { data.resize(size); }

	virtual ~Pool() = default;

	bool isEmpty() const { return data.empty(); }
	int GetSize() const { return data.size(); }
	void Resize(int n) { data.resize(n); }
	void Clear() { data.clear(); }
	void Add(T object) { data.push_back(object); }
	void Set(int index, T object) { data[index] = object; }
	T& Get(int index) { return static_cast<T&>(data[index]); }

	T& operator [](unsigned int index) { return data[index]; }
};


///////////////////////////////////////////////////////////////////////////////////////
// Registry
///////////////////////////////////////////////////////////////////////////////////////
// The registry manages the creation and destruction of entities, add systems 
// and componenets
///////////////////////////////////////////////////////////////////////////////////////
class Registry {
private:
	int numEntities = 0;

	//Vector of component pools, each pool contains all the data for a certain
	//component type.
	//Vector index == componenet id
	//Pool index == entity id
	std::vector<IPool*> componentPools;

	//Vector index == entity id
	std::vector<Signature> entityComponentSignature;

	//Map of active system [index == system typeid]
	std::unordered_map<std::type_index, System*> systems;

};

template <typename IComponent>
void System::RequireComponent() {
	const auto componentId = Component<IComponent>::GetId();
	componentSignature.set(componentId);
}

#endif // ! ECS_H
