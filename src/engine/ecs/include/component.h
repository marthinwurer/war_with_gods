#ifndef COMPONENT_H
#define COMPONENT_H

#include "entity.h"

#include <cstdint>
#include <memory>
#include <set>
#include <unordered_map>

typedef uint32_t ComponentType;
typedef std::set<ComponentType> ComponentTypeSet;

static const ComponentType invalid_component_type = 0;

struct Component {
    static const ComponentType m_type = invalid_component_type;
};

class IComponentStore {
public:
    typedef std::unique_ptr<IComponentStore> Ptr;
};

template<class C>
class ComponentStore: public IComponentStore {
    static_assert(std::is_base_of<Component, C>::value, "C must be derived from the Component struct");
    static_assert(C::m_type != invalid_component_type, "C must define a valid non-zero m_type");

private:
    std::unordered_map<Entity, C> m_store;
    static const ComponentType m_type = C::m_type;

public:
    ComponentStore() = default;
    ~ComponentStore() = default;

    bool add(const Entity entity, C&& component) {
        return m_store.insert(std::make_pair(entity, std::move(component))).second;
    }

    bool remove(Entity entity) {
        return (0 < m_store.erase(entity));
    }

    bool has(Entity entity) const {
        return (m_store.end() != m_store.find(entity));
    }

    C& get(Entity entity) {
        return m_store.at(entity);
    }

    const std::unordered_map<Entity, C>& components() {
        return m_store;
    }
};

#endif