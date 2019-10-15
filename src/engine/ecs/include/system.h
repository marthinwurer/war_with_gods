#ifndef SYSTEM_H
#define SYSTEM_H

#include "component.h"
#include "entity.h"

class ECSManager;

/**
 * @brief Abstract class for an ECS System.
 */
class System {
public:
    typedef std::shared_ptr<System> Ptr;

private:
    std::set<uint32_t> m_required;
    std::set<Entity> m_entities;

protected:
    ECSManager& m_manager;

public:

    /**
     * @brief Construct a new System object
     * 
     * @param manager   ECSManager
     */
    explicit System(ECSManager& manager);

    /**
     * @brief Default destructor. Can be overridden.
     */
    virtual ~System() = default;

    /**
     * @brief Return the set of required components for this System.
     * 
     * @return const std::set<uint32_t>&    Set of required components.
     */
    inline const std::set<uint32_t>& required_components() const {
        return m_required;
    }

    /**
     * @brief Registers an entity with the systems. This should never be 
     * called directly.
     * 
     * @param entity    Entity to register.
     * @return true     If successfully registered.
     * @return false    If failed to register.
     */
    inline bool register_entity(Entity entity) {
        return m_entities.insert(entity).second;
    }

    /**
     * @brief Unregisters an entity from the System. This should never be 
     * called directly.
     * 
     * @param entity    Entity to unregister.
     * @return true     If successfully unregistered.
     * @return false    If failed to unregister.
     */
    inline bool unregister_entity(Entity entity) {
        return m_entities.erase(entity);
    }

    /**
     * @brief Check if the system has an entity.
     * 
     * @param entity    Entity to check for.
     * @return true     If it exists.
     * @return false    If it does not exist.
     */
    inline bool has_entity(Entity entity) const {
        return (m_entities.end() != m_entities.find(entity));
    }

    /**
     * @brief Updates all entities registered with the System.
     * 
     * @param delta     Time since last update.
     * @return size_t   Number of entites updated.
     */
    size_t update_entities(double delta);
    
    /**
     * @brief Abstract update function.
     * 
     * @param delta     Time since last update.
     * @param entity    Number of entities updated.
     */
    virtual void update(double delta, Entity entity) = 0;

protected:
    inline void set_required(std::set<uint32_t>&& required) {
        m_required = std::move(required);
    }
};

#endif