#include "pch.h"
#include "Ugine/Application.h"
#include "Ugine/Exception/Exception.h"

class Player final: public ugine::Component2D {
public:
    Player(): ugine::Component2D("player") {};
    [[nodiscard]] std::tuple<std::string, ugine::AssetProps> initial_rendering() const noexcept override {
        return {"attack", {0,0, 100, 100, 1 }};
    }
};

TEST(SceneManager, AddGetRemoveScene) {
    auto scene_manager = ugine::SceneManager();
    scene_manager.add_scene(
            ugine::Scene("menu")
        );
    auto& retrieved_scene = scene_manager.get_scene("menu");
    EXPECT_EQ(retrieved_scene.get_name(), "menu");
    EXPECT_THROW(
            scene_manager.get_scene("not_existing_scene"),
            ugine::SceneNotFound
            );
    scene_manager.remove_scene("menu");
    EXPECT_THROW(
            scene_manager.get_scene("menu"),
            ugine::SceneNotFound
    );
}

TEST(Scene, AddComponent) {
    auto scene_manager = ugine::SceneManager();
    auto scene = ugine::Scene2D("menu");
    scene.add_component(std::make_unique<Player>());
    EXPECT_EQ(scene.get_component_list().size(), 1);
    EXPECT_EQ(scene.get_component_list()[0]->get_name() , "player");
}