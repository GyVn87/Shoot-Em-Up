#include "Entity.hpp"

#include "SceneNode.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

Entity::Entity() : SceneNode(), mVelocity({0.f, 0.f}) {}

Entity::Entity(sf::Vector2f velocity) : mVelocity(velocity) {}

void Entity::setVelocity(sf::Vector2f velocity) {
    mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy) {
    mVelocity.x = vx;
    mVelocity.y = vy;
}

void Entity::accelerate(sf::Vector2f velocity) {
    mVelocity += velocity;
}

sf::Vector2f Entity::getVelocity() const {
    return mVelocity;
}

void Entity::updateCurrent(sf::Time dt) {
    move(mVelocity * dt.asSeconds()); 
}