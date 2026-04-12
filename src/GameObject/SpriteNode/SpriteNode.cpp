#include "SpriteNode.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

SpriteNode::SpriteNode(const sf::Texture& texture) : mSprite(texture) {}

SpriteNode::SpriteNode(const sf::Texture& texture, sf::IntRect bounds) : mSprite(texture, bounds) {}

void SpriteNode::drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const {
    target.draw(mSprite, states);
}