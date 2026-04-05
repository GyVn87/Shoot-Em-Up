#include "Entity.hpp"

Entity::Entity() : SceneNode(), mVelocity({0.f, 0.f}) {}

Entity::Entity(sf::Vector2f velocity) : mVelocity(velocity) {}

void Entity::setVelocity(sf::Vector2f velocity) {
    mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy) {
    mVelocity.x = vx;
    mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const {
    return mVelocity;
}

void Entity::updateCurrent(sf::Time dt) {
    move(mVelocity * dt.asSeconds()); 
}