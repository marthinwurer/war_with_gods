#ifndef ECS_MANAGER_H
#define ECS_MANAGER_H

#include "component.h"
#include "entity.h"
#include "system.h"

#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <memory>   
#include <cassert>
#include <limits>
#include <stdexcept>

class ECSManager {

private:
    Entity m_last_entity;
    std::unordered_map<Entity, ComponentTypeSet> m_entities;
    std::map<ComponentType, IComponentStore::Ptr> m_stores;
    std::vector<System::Ptr> m_systems;

public:
    ECSManager();
    virtual ~ECSManager() = default;

    template<typename C> ComponentStore<C>& component_store() {
        static_assert(std::is_base_of<Component, C>::value, "C must be derived from the Component struct");
        static_assert(C::m_type != invalid_component_type, "C must define a valid non-zero m_Type");

        auto store = m_stores.find(C::m_type);
        if (m_stores.end() == store) {
            throw std::runtime_error("The ComponentStore does not exist");
        }
        return reinterpret_cast<ComponentStore<C>&>(*(store->second));
    }

    template<class C> bool create_component_store() {
        static_assert(std::is_base_of<Component, C>::value, "C must be derived from the Component struct");
        static_assert(C::m_type != invalid_component_type, "C must define a valid non-zero m_type");
    
        return m_stores.insert(std::make_pair(C::m_type, IComponentStore::Ptr(new ComponentStore<C>()))).second;
    }

    template<class C> bool add_component(const Entity entity, C&& component) {
        static_assert(std::is_base_of<Component, C>::value, "C must be derived from the Component struct");
        static_assert(C::m_type != invalid_component_type, "C must define a valid non-zero m_Type");
    
        auto e = m_entities.find(entity);
        if (m_entities.end() == e) {
            throw std::runtime_error("The Entity does not exist");
        }

        (*e).second.insert(C::m_type);
        return component_store<C>().add(entity, std::move(component));
    }
    
    void add_system(const System::Ptr& system);
    
    Entity create_entity() {
        m_entities.insert(std::make_pair((m_last_entity + 1), ComponentTypeSet()));
        return (++m_last_entity);
    }

    size_t register_entity(const Entity entity);
    size_t unregister_entity(const Entity entity);
    size_t update_entities(double delta);
};

#endif