#ifndef TEXTUREHOLDER_H
#define TEXTUREHOLDER_H

#include "ResourceHolder.hpp"
#include "TextureIDs.hpp"

#include <SFML/Graphics/Texture.hpp>

using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;

#endif