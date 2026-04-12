#ifndef ENTITY_H
#define ENTITY_H

#include "SceneNode.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

class Entity : public SceneNode {
    public:
        Entity();
        Entity(sf::Vector2f velocity);
        void setVelocity(sf::Vector2f velocity);
        void setVelocity(float vx, float vy);
        void accelerate(sf::Vector2f velocity);
        sf::Vector2f getVelocity() const;
    private:
        virtual void updateCurrent(sf::Time dt) override;
    private:
        sf::Vector2f mVelocity;
};

#endif