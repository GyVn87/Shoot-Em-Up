#ifndef AIRCRAFT_H
#define AIRCRAFT_H
#include "Entity.hpp"

class Aircraft : public Entity {
    public:
        enum Type {
            Eagle,
            Owl
        };
        explicit Aircraft(Type type, const TextureHolder& textures);
    private:
        void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        Type mType;
        sf::Sprite mSprite;
};
#endif