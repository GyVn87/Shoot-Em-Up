#ifndef SPRITENODE_H
#define SPRITENODE_H

#include "SceneNode.hpp"

class SpriteNode : public SceneNode {
    public:
        SpriteNode(const sf::Texture& texture);
        SpriteNode(const sf::Texture& texture, const sf::IntRect& bounds); 
    private:
       void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        sf::Sprite mSprite;
};

#endif