#pragma once

#include "ugine/pch.h"
#include "ugine/window/window_impl.h"
#include "sdl_input.h"
#include <SDL.h>


namespace ugine::window {

    class SDLWindow : public WindowImpl {
        using sdl_event_cb_type = std::function<void(const SDL_Event &)>;
    public:
        SDLWindow();

        SDLWindow(const SDLWindow &) = delete;

        SDLWindow(SDLWindow &&) = delete;

        SDLWindow &operator=(const SDLWindow &) = delete;

        SDLWindow &operator=(SDLWindow &&) = delete;

        ~SDLWindow() override;

        void on_update() const override;

        void close() const override;

        /**
         * Listen to the native sdl event before they are converting to ugine's events
         * @param callback: Call at each new event
         */
        void on_sdl_event(sdl_event_cb_type callback) noexcept;

        [[nodiscard]] const ugine::window::Input &get_input() const noexcept override {
            return this->m_input;
        }

        [[nodiscard]] SDL_Window *get_sdl_window() const noexcept { return this->m_sdl_window; }

    protected:
        void dispatch_sdl_event(const SDL_Event &sdl_event) const noexcept;
        void set_sdl_window(SDL_Window* sdl_window) noexcept {this->m_sdl_window = sdl_window;}

    private:
        SDL_Window *m_sdl_window{nullptr};
        ugine::window::SDLInput m_input;
        std::vector<sdl_event_cb_type> m_sdl_event_cb;
    };

    class SDLGlWindow final : public SDLWindow {
    public:
        SDLGlWindow() = default;

        SDLGlWindow(const SDLGlWindow &) = delete;

        SDLGlWindow(SDLGlWindow &&) = delete;

        SDLGlWindow &operator=(const SDLGlWindow &) = delete;

        SDLGlWindow &operator=(SDLGlWindow &&) = delete;

        ~SDLGlWindow() override {
            this->close();
        }

        void accept(const WindowImplVisitor &visitor) override {
            visitor.visit(*this);
        }

        [[nodiscard]] SDL_GLContext get_gl_context() const noexcept { return this->m_gl_context; }

        void open(const window::WindowProps &props) override;

        void render() const override;

        void close() const override;

    private:
        SDL_GLContext m_gl_context{nullptr};
    };
}