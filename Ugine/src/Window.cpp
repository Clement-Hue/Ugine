#include "Ugine/Window.h"
#include "Ugine/Log.h"
#include "SDL.h"
#include "Ugine/Exception/WindowException.h"

static int i_count = 0;

static void init_sdl() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        throw WindowInitError(SDL_GetError());
    }
    UGINE_CORE_INFO("SDL initialized");
}

void Window::init()  {
    if (i_count++ == 0) {
        init_sdl();
    }
    this->sdl_window = SDL_CreateWindow(props.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                     props.width, props.height, SDL_WINDOW_OPENGL);
    this->sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    UGINE_CORE_INFO("Window created");
}

Window::~Window() {
    SDL_DestroyRenderer(this->sdl_renderer);
    SDL_DestroyWindow(this->sdl_window);
    UGINE_CORE_INFO("Window closed");
    if (--i_count == 0) {
        SDL_Quit();
        UGINE_CORE_INFO("SDL cleaned up");
    }
}