#ifndef SPRITENODE_H
#define SPRITENODE_H

#include "SceneNode.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace sf { 
    class Texture; 
    class RenderTarget;
    class RenderStates;
}

class SpriteNode : public SceneNode {
    public:
        SpriteNode(const sf::Texture& texture);
        SpriteNode(const sf::Texture& texture, sf::IntRect bounds); 
    private:
       void drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const override;
    private:
        sf::Sprite mSprite;
};

#endif