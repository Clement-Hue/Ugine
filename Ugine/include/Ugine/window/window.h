#pragma once

#include "ugine/pch.h"
#include "ugine/core.h"
#include "ugine/event/event.h"
#include "ugine/renderer.h"
#include "ugine/input.h"
#include "ugine/ui/ui.h"

struct SDL_Window;
struct SDL_Renderer;

namespace ugine::window {

    struct UGINE_API WindowProps {
        std::string title = "Default title";
        int height = 650;
        int width = 650;
    };


    class UGINE_API Window
    {
    public:
        using event_callback_type = std::function<void(const ugine::event::Event&)>;
        Window() = default;
        virtual ~Window() = default;
        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;
        [[nodiscard]] virtual void* get_native_window() const noexcept = 0;
        [[nodiscard]] virtual const ui::UI& get_ui() const noexcept = 0;
        /**
         * Dispatch window event
         * @param callback: callback call when an event occurred
         */
        virtual void on_event(event_callback_type callback) noexcept {
            this->event_cb = std::move(callback);
        }
        /**
         * Create a new OS window, if the window is already created a
         * WindowAlreadyCreated exception is thrown, to recreate the window you
         * must call close before.
         * @param props Property of the window
         */
        virtual void create(const WindowProps& props = {}) = 0;
        /**
         * Close the window if it has been created, otherwise does nothing
         */
        virtual void close() const = 0;
        virtual void render() const = 0;
        /**
         * Poll window's events
         */
        virtual void on_update() const = 0;
        [[nodiscard]] virtual const Input& get_input() const noexcept = 0;
    protected:
        void dispatch(const ugine::event::Event& event) const noexcept {
            this->event_cb(event);
        }
    private:
        event_callback_type event_cb = nullptr;
    };


}
