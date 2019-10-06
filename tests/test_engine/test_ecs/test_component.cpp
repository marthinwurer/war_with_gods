#include <Catch2/catch.hpp>

#include "../../../src/engine/ecs/include/component.h"

struct TestComponent : public Component {
    static const ComponentType m_type;

    float x; 
    float y;
};

const ComponentType TestComponent::m_type = 1;

TEST_CASE("Component Unit Tests", "[ecs][component]") {
    
    ComponentStore<TestComponent> store = ComponentStore<TestComponent>();
    REQUIRE(store.components().size() == 0);

    SECTION("add()") {
        Entity entity = 1;
        TestComponent position;

        bool added = store.add(entity, std::move(position));

        REQUIRE(added == true);
        REQUIRE(store.components().size() == 1);
    }

    SECTION("remove()") {
        Entity entity = 1;
        TestComponent position;

        bool ret = store.add(entity, std::move(position));
        REQUIRE(ret == true);
        REQUIRE(store.components().size() == 1);

        // Remove doesn't exist
        ret = store.remove(2);
        REQUIRE(ret == false);
        REQUIRE(store.components().size() == 1);

        // Remove
        ret = store.remove(entity);
        REQUIRE(ret == true);
        REQUIRE(store.components().size() == 0);

        // Remove from empty
        ret = store.remove(entity);
        REQUIRE(ret == false);
        REQUIRE(store.components().size() == 0);
    }

    SECTION("has()") {
        Entity entity = 3;
        TestComponent position;

        bool ret = store.add(entity, std::move(position));
        REQUIRE(ret == true);
        REQUIRE(store.components().size() == 1);

        ret = store.has(entity);
        REQUIRE(ret == true);

        ret = store.has(55);
        REQUIRE(ret == false);
    }

    SECTION("get()") {
        Entity entity = 3;
        TestComponent position;
        position.x = 253;

        bool ret = store.add(entity, std::move(position));
        REQUIRE(ret == true);
        REQUIRE(store.components().size() == 1);

        TestComponent p = store.get(entity);
        REQUIRE(p.x == position.x);

        REQUIRE_THROWS(store.get(53));
    }
}