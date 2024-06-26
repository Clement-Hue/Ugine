#include "ugine/renderer.h"
#include "ugine/exception/exception.h"
#include "ugine/log.h"
#include <SDL.h>
#include <SDL_image.h>


void ugine::SDLTextureManager::load_asset(const std::string &asset_path, const std::string &asset_name) {
    SDL_Surface *assert_surface = IMG_Load(asset_path.c_str());
    if (assert_surface == nullptr) {
        UGINE_CORE_ERROR("Error loading asset '{0}', details: {1}", asset_name, SDL_GetError());
        return;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->m_sdl_renderer, assert_surface);
    if (texture == nullptr) {
        UGINE_CORE_ERROR("Error creating texture of the asset '{0}', details: {1}", asset_name, SDL_GetError());
        return;
    }
    this->m_textures[asset_name] = texture;
    SDL_FreeSurface(assert_surface);
}


void ugine::SDLTextureManager::render_component(const Component2D &component, const AssetProps &asset_props) const {
    const SDL_Rect src_rect{asset_props.x + asset_props.col * asset_props.width,
                      asset_props.y + asset_props.row * asset_props.height, asset_props.width, asset_props.height};
    const SDL_Rect dest_rect{static_cast<int>(component.get_position().get_x()), static_cast<int>(component.get_position().get_y()),
                       static_cast<int>(static_cast<float>(asset_props.width) * asset_props.zoom),
                       static_cast<int>(static_cast<float>(asset_props.height) * asset_props.zoom)};
    if (SDL_RenderCopy(this->m_sdl_renderer, this->m_textures.at(asset_props.name), &src_rect, &dest_rect) < 0) {
        UGINE_CORE_ERROR("Error while rendering component '{0}', details: {1}", component.get_name(), SDL_GetError());
        return;
    }
}

ugine::SDLTextureManager::~SDLTextureManager() {
    for (const auto &[name, texture]: this->m_textures) {
        SDL_DestroyTexture(texture);
        UGINE_CORE_INFO("Free texture '{0}'", name);
    }
}

