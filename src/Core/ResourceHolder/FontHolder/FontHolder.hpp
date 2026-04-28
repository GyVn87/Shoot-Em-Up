#ifndef FONT_HOLDER_H
#define FONT_HOLDER_H

#include "ResourceHolder.hpp"
#include "FontIDs.hpp"

#include <SFML/Graphics/Font.hpp>

using FontHolder = ResourceHolder<sf::Font, Fonts::ID>;

#endif