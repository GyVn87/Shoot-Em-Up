#include "Utility.hpp"

void Utility::centerOrigin(sf::Sprite& sprite) {
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.getCenter());
}