#include "include/system.h"
#include "include/manager.h"

System::System(ECSManager& manager) :
    m_manager(manager) {
}

size_t System::update_entities(double delta) {
    size_t n = 0;

    for (auto e = m_entities.begin(); e != m_entities.end(); e++) {
        update(delta, *e);
        n++;
    }

    return n;
}