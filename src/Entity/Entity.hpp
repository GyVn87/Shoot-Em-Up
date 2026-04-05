#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include "SceneNode.hpp"
#include "TextureHolder.hpp"

class Entity : public SceneNode {
    public:
        Entity();
        Entity(sf::Vector2f velocity);
        void setVelocity(sf::Vector2f velocity);
        void setVelocity(float vx, float vy);
        sf::Vector2f getVelocity() const;
    private:
        virtual void updateCurrent(sf::Time dt) override;
    private:
        sf::Vector2f mVelocity;
};

#endif