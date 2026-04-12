#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "Entity.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace Textures { enum ID : short; }

namespace sf { 
    class Texture; 
    class RenderTarget;
    class RenderStates;
}

template <typename Resource, typename Identifier>
class ResourceHolder;
using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;

class Aircraft : public Entity {
    public:
        enum Type {
            Eagle,
            Owl,
            Vulture,
            Phoenix
        };
    public:
        explicit Aircraft(Type type, const TextureHolder& textures);
        unsigned int getCategory() const override;
    private:
        void drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const override;
    private:
        Type mType;
        sf::Sprite mSprite;
};
#endif