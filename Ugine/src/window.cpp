#include "Ugine/window.h"
#include "Ugine/log.h"
#include "SDL.h"
#include "Ugine/Exception/exception.h"

static int i_count = 0;

static void init_sdl() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        throw ugine::WindowInitError(SDL_GetError());
    }
    UGINE_CORE_INFO("SDL initialized");
}


void ugine::SDLWindow::init()  {
    if (i_count++ == 0) {
        init_sdl();
    }
    this->sdl_window = SDL_CreateWindow(props.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                     props.width, props.height, SDL_WINDOW_OPENGL);
    this->sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    UGINE_CORE_INFO("SDLWindow {0} of {1}x{2}px created", this->props.title, this->props.height, this->props.width);
}

ugine::SDLWindow::~SDLWindow() {
    SDL_DestroyRenderer(this->sdl_renderer);
    SDL_DestroyWindow(this->sdl_window);
    UGINE_CORE_INFO("SDLWindow closed");
    if (--i_count == 0) {
        SDL_Quit();
        UGINE_CORE_INFO("SDL cleaned up");
    }
}

void ugine::SDLWindow::render() const {
    SDL_RenderPresent(this->sdl_renderer);
}