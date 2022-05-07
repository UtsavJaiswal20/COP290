#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

const std::size_t maxcomponents = 32;
const std::size_t maxgroups = 32;

using ComponentBitSet = std::bitset<maxcomponents>;
using GroupBitSet = std::bitset<maxgroups>;

using ComponentArray = std::array<Component*, maxcomponents>;

class Component
{
public:
	Entity* entity;

	virtual void initialize() {}
	virtual void update() {}
	virtual void draw() {}
	virtual ~Component() {}
};

class Entity
{
private:
	Manager& manager;
	bool isactive = true;
	std::vector<std::unique_ptr<Component>> components;
	ComponentBitSet compbitset;
	ComponentArray comparray;
	GroupBitSet grobitset;
public:
	Entity(Manager& mmanager) : manager(mmanager) {}
	void update() {
		for (auto& c : components) {
			c->update();
		}
	}
	void draw() {
		for (auto& c : components) {
			c->draw();
		}
	}
	bool check() const {
		return isactive;
	}
	void destroy() {
		isactive = false;
	}
	bool hasGroup(Group mGroup) {
		return grobitset[mGroup];
	}
	void addGroup(Group mGroup);
	void delGroup(Group mGroup) {
		grobitset[mGroup] = false;
	}
	template <typename T> bool hascomponent() const {
		return compbitset[getComponentTypeID<T>()];
	}
	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		comparray[getComponentTypeID<T>()] = c;
		compbitset[getComponentTypeID<T>()] = true;

		c->initialize();
		return *c;
	}
	template<typename T> T& getComponent() const {
		auto ptr(comparray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxgroups> entitygroup;
public:
	void update(){
		for (auto& e : entities) e->update();
	}
	void draw() {
		for (auto& e : entities) e->draw();
	}
	void refresh() {
		for (auto i(0u); i < maxgroups; i++) {
			auto& v(entitygroup[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
					{
						return !mEntity->check() || !mEntity->hasGroup(i);
					}),
				std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->check();
			}),
			std::end(entities));
	}
	void Addtogroup(Entity* mEntity, Group mGroup) {
		entitygroup[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup) {
		return entitygroup[mGroup];
	}

	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};