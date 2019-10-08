#include <Catch2/catch.hpp>

#include "../../../src/engine/ecs/include/component.h"
#include "../../../src/engine/ecs/include/system.h"
#include "../../../src/engine/ecs/include/manager.h"

struct TestComponentOne : public Component {
    static const ComponentType m_type;

    float x; 
    float y;

    TestComponentOne(float aX, float aY) : x(aX), y(aY) {}
};

struct TestComponentTwo : public Component {
    static const ComponentType m_type;

    float vx; 
    float vy;

    TestComponentTwo(float aX, float aY) : vx(aX), vy(aY) {}
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

    SECTION("FUNCTION register_entity()") {
        Entity e = 2;

        bool ret = system.register_entity(e);
        REQUIRE(ret == true);
        REQUIRE(system.has_entity(e) == true);

        ret = system.register_entity(e);
        REQUIRE(ret == false);
    }

    SECTION("FUNCTION unregister_entity()") {
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

    SECTION("FUNCTION update()") {
        bool ret = manager.create_component_store<TestComponentOne>();
        REQUIRE(ret == true);
        ret = manager.create_component_store<TestComponentTwo>();
        REQUIRE(ret == true);

        manager.add_system(System::Ptr(new SystemMove(manager)));

        Entity particle = manager.create_entity();
        REQUIRE(particle == 1);

        ret = manager.add_component(particle, TestComponentOne(1.0f, 1.0f));
        REQUIRE(ret == true);
        ret = manager.add_component(particle, TestComponentTwo(2.0f, 3.0f));
        REQUIRE(ret == true);

        size_t n = manager.register_entity(particle);
        REQUIRE(n == 1);

        n = manager.update_entities(0.5f);
        REQUIRE(n == 1);

        TestComponentOne& position = manager.component_store<TestComponentOne>().get(particle);
        REQUIRE(position.x == Approx(2.0f));
        REQUIRE(position.y == Approx(2.5f));
    }
}