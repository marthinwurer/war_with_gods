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

/**
 * @brief The manager for the ECS system. The only calls the user should make 
 * should be to this object.
 */
class ECSManager {
private:
    Entity m_last_entity;
    std::unordered_map<Entity, std::set<uint32_t>> m_entities;
    std::map<uint32_t, IComponentStore::Ptr> m_stores;
    std::vector<System::Ptr> m_systems;

public:
    /**
     * @brief Construct a new ECSManager object
     */
    ECSManager();

    /**
     * @brief Destroy the ECSManager object
     */
    virtual ~ECSManager() = default;

    /**
     * @brief Gets a ComponentStore of a specific type.
     * 
     * @tparam C                    Type of component.
     * @return ComponentStore<C>&   ComponentStore of type C
     */
    template<typename C> ComponentStore<C>& component_store() {
        static_assert(std::is_base_of<Component, C>::value, "C must be derived from the Component struct");
        static_assert(C::m_type != INVALID_COMPONENT, "C must define a valid non-zero m_Type");

        auto store = m_stores.find(C::m_type);
        if (m_stores.end() == store) {
            throw std::runtime_error("The ComponentStore does not exist");
        }
        return reinterpret_cast<ComponentStore<C>&>(*(store->second));
    }

    /**
     * @brief Create a component store object. Uses smart pointers so there is 
     * no need to manually release any memory.
     * 
     * @tparam C        Type of component to create a ComponentStore for.
     * @return true     If the store was created sucessfully.
     * @return false    If the store failed to be created.
     */
    template<class C> bool create_component_store() {
        static_assert(std::is_base_of<Component, C>::value, "C must be derived from the Component struct");
        static_assert(C::m_type != INVALID_COMPONENT, "C must define a valid non-zero m_type");
    
        return m_stores.insert(std::make_pair(C::m_type, IComponentStore::Ptr(new ComponentStore<C>()))).second;
    }

    /**
     * @brief Add a component to a specific entity.
     * 
     * @tparam C        Type of component to add.
     * @param entity    Entity to add component to.
     * @param component Component to add.
     * @return true     If the component was successfully added.
     * @return false    If the component failed to be added.
     */
    template<class C> bool add_component(const Entity entity, C&& component) {
        static_assert(std::is_base_of<Component, C>::value, "C must be derived from the Component struct");
        static_assert(C::m_type != INVALID_COMPONENT, "C must define a valid non-zero m_Type");
    
        auto e = m_entities.find(entity);
        if (m_entities.end() == e) {
            throw std::runtime_error("The Entity does not exist");
        }

        (*e).second.insert(C::m_type);
        return component_store<C>().add(entity, std::move(component));
    }
    
    /**
     * @brief Get a specific component of an entity.
     * 
     * @tparam C        Type of component to get.
     * @param entity    Entitiy to get component from.
     * @return C&       The component object.
     */
    template<class C> C& get_component(const Entity entity) {
        static_assert(std::is_base_of<Component, C>::value, "C must be derived from the Component struct");
        static_assert(C::m_type != INVALID_COMPONENT, "C must define a valid non-zero m_Type");

        return component_store<C>().get(entity);
    }

    /**
     * @brief Adds a System object to the ECSManager.
     * 
     * @param system    New System object to add to the manager.
     */
    void add_system(const System::Ptr& system);
    
    /**
     * @brief Create a new entity
     * 
     * @return Entity   The entity created.
     */
    Entity create_entity();

    /**
     * @brief After all components have been added to an entity and all systems 
     * added to the ECSManager, register an entity with the ECSManager.
     * 
     * @param entity    Entity to register
     * @return size_t   The number of systems the entity was registered to.
     */
    size_t register_entity(const Entity entity);

    /**
     * @brief Removes an entity from the ECSManager.
     * 
     * @param entity    Entity to remove.
     * @return size_t   Number of Systems the entity was registered to.
     */
    size_t unregister_entity(const Entity entity);

    /**
     * @brief Updates all the entities by running all the systems added to the 
     * ECSManager.
     * 
     * @param delta     Time passed since last update.
     * @return size_t   Number of entities updated.
     */
    size_t update_entities(double delta);
};

#endif