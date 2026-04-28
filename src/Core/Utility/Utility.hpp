#ifndef UTILITY_H
#define UTILITY_H

namespace sf { 
    class Sprite; 
    class Text;
    class RectangleShape;
}

namespace Utility {
    void centerOrigin(sf::Sprite& sprite);
    void centerOrigin(sf::Text& text);
    void centerOrigin(sf::RectangleShape& rect);
}

#endif