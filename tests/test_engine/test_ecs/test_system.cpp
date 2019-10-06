#include <Catch2/catch.hpp>

#include "../../../src/engine/ecs/include/component.h"
#include "../../../src/engine/ecs/include/system.h"
#include "../../../src/engine/ecs/include/manager.h"

struct TestComponentOne : public Component {
    static const ComponentType m_type;

    float x; 
    float y;
};

struct TestComponentTwo : public Component {
    static const ComponentType m_type;

    float vx; 
    float vy;
};

const ComponentType TestComponentOne::m_type = 1;
const ComponentType TestComponentTwo::m_type = 2;

class SystemMove: public System {
public:
    SystemMove(ECSManager& manager) :
        System(manager) {
        ComponentTypeSet required;
        required.insert(TestComponentOne::m_type);
        required.insert(TestComponentTwo::m_type);
        set_required(std::move(required));
    }

    virtual void update(double delta, Entity entity) {
        const TestComponentTwo& velocity = m_manager.component_store<TestComponentTwo>().get(entity);
        TestComponentOne& position = m_manager.component_store<TestComponentOne>().get(entity);

        position.x += (velocity.vx * delta);
        position.y += (velocity.vy * delta);
    }    
};

TEST_CASE("System Unit Tests", "[ecs][system]") {

    ECSManager manager;
    SystemMove system = SystemMove(manager);

    REQUIRE(system.required_components().size() == 2);

    SECTION("register_entity()") {
        Entity e = 2;

        bool ret = system.register_entity(e);
        REQUIRE(ret == true);
        REQUIRE(system.has_entity(e) == true);

        ret = system.register_entity(e);
        REQUIRE(ret == false);
    }

    SECTION("unregister_entity()") {
        Entity e = 2;

        bool ret = system.register_entity(e);
        REQUIRE(ret == true);
        REQUIRE(system.has_entity(e) == true);

        ret = system.unregister_entity(44);
        REQUIRE(ret == false);
        REQUIRE(system.has_entity(e) == true);

        ret = system.unregister_entity(e);
        REQUIRE(ret == true);
        REQUIRE(system.has_entity(e) == false);

        ret = system.unregister_entity(e);
        REQUIRE(ret == false);
    }
}