#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "World.hpp"

class Game {
    public:
        Game();
        void run();

    private:
        void processEvents();
        void update(sf::Time);
        void render();
        void handlePlayerInput(sf::Keyboard::Scancode, bool);

    private:
        sf::RenderWindow mWindow;
        World mWorld;
        const sf::Time mTimePerFrame = sf::seconds(1.f / 60.f);
};

#endif