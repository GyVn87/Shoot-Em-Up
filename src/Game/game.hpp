#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

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
    sf::CircleShape mPlayer;
    float mPlayerSpeed = 60.f;
    sf::Time mTimePerFrame = sf::seconds(1.f / 60.f);
    bool mIsMovingUp = false;
    bool mIsMovingDown = false;
    bool mIsMovingLeft = false;
    bool mIsMovingRight = false;
};

#endif