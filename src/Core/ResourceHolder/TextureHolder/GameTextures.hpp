#ifndef GAME_TEXTURES
#define GAME_TEXTURES

#include "TextureIDs.hpp"

#include <string_view>
#include <array>

namespace GameTextures {
    struct TextureData {
        Textures::ID id;
        std::string_view path;   
    };
    inline constexpr auto texturesArray = std::to_array<TextureData>({
        {Textures::ID::Background_Desert, "assets/images/Background/Desert.png"},
        {Textures::ID::Aircraft_Eagle, "assets/images/Aircraft/Eagle.png"},
        {Textures::ID::Aircraft_Owl, "assets/images/Aircraft/Owl.png"},
        {Textures::ID::Aircraft_Vulture, "assets/images/Aircraft/Vulture.png"},
        {Textures::ID::Aircraft_Phoenix, "assets/images/Aircraft/Phoenix.png"}
    });
}

#endif