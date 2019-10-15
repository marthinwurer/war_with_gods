#include "include/manager.h"

ECSManager::ECSManager() :
    m_last_entity(INVALID_ENTITY),
    m_entities(),
    m_stores(),
    m_systems() {
}

void ECSManager::add_system(const System::Ptr& system) {
    if (!system || system->required_components().empty()) {
        throw std::runtime_error("System should specify required components");
    }
    m_systems.push_back(system);
}

Entity ECSManager::create_entity() {
    m_entities.insert(std::make_pair((m_last_entity + 1), std::set<uint32_t>()));
    return (++m_last_entity);
}

size_t ECSManager::register_entity(const Entity entity) {
    size_t n = 0;

    auto e = m_entities.find(entity);
    if (m_entities.end() == e) {
        throw std::runtime_error("Entity does not exist");
    }
    auto components = (*e).second;

    for (auto system : m_systems) {
        auto required = system->required_components();
        if (std::includes(components.begin(), components.end(), required.begin(), required.end())) {
            system->register_entity(entity);
            n++;
        }
    }

    return n;
}

size_t ECSManager::unregister_entity(const Entity entity) {
    size_t n = 0;

    auto e = m_entities.find(entity);
    if (m_entities.end() == e) {
        throw std::runtime_error("Entity does not exist");
    }

    for (auto system: m_systems) {
        n += system->unregister_entity(entity);
    }

    return n;
}

size_t ECSManager::update_entities(double delta) {
    size_t n = 0;

    for (auto system: m_systems) {
        n += system->update_entities(delta);
    }

    return n;
}