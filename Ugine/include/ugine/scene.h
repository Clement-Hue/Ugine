#pragma once

#include "ugine/pch.h"
#include "ugine/core.h"
#include "ugine/component.h"
#include "ugine/exception/exception.h"

namespace ugine {

    template<typename C>
    class Scene {
    public:
        using component_list_type = std::vector<std::unique_ptr<C>>;

        explicit Scene(std::string name) : m_name(std::move(name)) {}

        Scene(Scene &&) noexcept = default;

        Scene(const Scene &) = delete;

        Scene &operator=(Scene &&) noexcept = default;

        Scene &operator=(const Scene &) = delete;

        virtual ~Scene() = default;

        [[nodiscard]] const std::string &get_name() const noexcept { return m_name; }

        [[nodiscard]] component_list_type &get_component_list() noexcept { return this->m_component_list; }

        void add_component(std::unique_ptr<C> component) {
            this->m_component_list.emplace_back(std::move(component));
        }

    private:
        std::string m_name;
        component_list_type m_component_list;
    };

    class UGINE_API Scene2D : public Scene<Component2D> {
    public:
        explicit Scene2D(std::string name) : Scene(std::move(name)) {}
    };

    template<typename S>
    class SceneManager {
    public:
        SceneManager() = default;

        SceneManager(const SceneManager &) = default;

        SceneManager(SceneManager &&) noexcept = default;

        SceneManager &operator=(const SceneManager &) = default;

        SceneManager &operator=(SceneManager &&) noexcept = default;

        virtual ~SceneManager() = default;

        void add_scene(S scene) {
            this->m_scenes_map.insert({scene.get_name(), std::move(scene)});
        }

        void remove_scene(const std::string &name) {
            this->m_scenes_map.erase(name);
        }

        S &get_scene(const std::string &name) {
            const auto &elem = this->m_scenes_map.find(name);
            if (elem == this->m_scenes_map.end()) {
                throw ugine::exception::SceneNotFound(name);
            }
            return this->m_scenes_map.find(name)->second;
        }

    private:
        std::map<std::string, S> m_scenes_map;
    };

    class SceneManager2D final : public SceneManager<Scene2D> {
    public:
        SceneManager2D() = default;
    };
}