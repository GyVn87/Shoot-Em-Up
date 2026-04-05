#include "Aircraft.hpp"
#include "Utility.hpp"

Textures::ID toTextureID(Aircraft::Type type) {
    switch (type) {
        case Aircraft::Eagle: return Textures::Aircraft_Eagle;
        case Aircraft::Owl: return Textures::Aircraft_Owl;
    }
    return Textures::Aircraft_Eagle; //default
}

Aircraft::Aircraft(Type type, const TextureHolder& textures) : Entity(), mType(type), mSprite(textures.get(toTextureID(type))) {
    Utility::centerOrigin(mSprite);
    mSprite.setPosition({0.f, 0.f});
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}
