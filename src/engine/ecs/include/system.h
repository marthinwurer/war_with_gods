#ifndef SYSTEM_H
#define SYSTEM_H

#include "component.h"
#include "entity.h"

class ECSManager;

class System {
public:
    typedef std::shared_ptr<System> Ptr;

private:
    ComponentTypeSet m_required;
    std::set<Entity> m_entities;

protected:
    ECSManager& m_manager;

public:
    explicit System(ECSManager& manager);
    virtual ~System() = default;

    inline const ComponentTypeSet& required_components() const {
        return m_required;
    }

    inline bool register_entity(Entity entity) {
        return m_entities.insert(entity).second;
    }

    inline bool unregister_entity(Entity entity) {
        return m_entities.erase(entity);
    }

    inline bool has_entity(Entity entity) const {
        return (m_entities.end() != m_entities.find(entity));
    }

    size_t update_entities(double delta);
    
    virtual void update(double delta, Entity entity) = 0;

protected:
    inline void set_required(ComponentTypeSet&& required) {
        m_required = std::move(required);
    }
};

#endif