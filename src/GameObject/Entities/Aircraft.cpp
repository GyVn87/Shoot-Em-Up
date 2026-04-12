#include "Aircraft.hpp"

#include "Utility.hpp"
#include "TextureHolder.hpp"
#include "TextureIDs.hpp"
#include "Category.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>

Textures::ID toTextureID(Aircraft::Type type) {
    switch (type) {
        case Aircraft::Eagle: return Textures::Aircraft_Eagle;
        case Aircraft::Owl: return Textures::Aircraft_Owl;
        case Aircraft::Vulture: return Textures::Aircraft_Vulture;
        case Aircraft::Phoenix: return Textures::Aircraft_Phoenix;
    }
    return Textures::Aircraft_Eagle; //default
}

Aircraft::Aircraft(Type type, const TextureHolder& textures) : Entity(), mType(type), mSprite(textures.get(toTextureID(type))) {
    Utility::centerOrigin(mSprite);
    mSprite.setPosition({0.f, 0.f});
}

unsigned int Aircraft::getCategory() const {
    switch (mType) {
        case Aircraft::Eagle: return Category::PlayerAircraft;
        case Aircraft::Owl: return Category::AlliedAircraft;
        case Aircraft::Vulture: return Category::EnemyAircraft;
        case Aircraft::Phoenix: return Category::EnemyAircraft;
        default: return Category::None;
    }
}

void Aircraft::drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const {
    target.draw(mSprite, states);
}
