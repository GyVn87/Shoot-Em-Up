#ifndef GAME_H
#define GAME_H

#include "World.hpp"
#include "Player.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

class Game {
    public:
        Game();
        void run();

    private:
        void processEvents();
        void update(sf::Time);
        void render();

    private:
        sf::RenderWindow mWindow;
        World mWorld;
        Player mPlayer;
        const sf::Time mTimePerFrame = sf::seconds(1.f / 60.f);
};

#endif