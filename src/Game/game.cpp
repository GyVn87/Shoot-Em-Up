#include "game.hpp"

Game::Game() : mWindow(sf::VideoMode({640, 480}), "Shoot 'Em Up"), mWorld(mWindow) {} // update later

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {
        sf::Time deltaTime = clock.restart();
        timeSinceLastUpdate += deltaTime;
        processEvents();
        while (timeSinceLastUpdate >= mTimePerFrame) {
            update(mTimePerFrame);
            timeSinceLastUpdate -= mTimePerFrame;
        }
        render();
    }
}

void Game::processEvents() {
    while (const std::optional<sf::Event> event = mWindow.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            mWindow.close();
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            handlePlayerInput(keyPressed->scancode, true);
        else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
            handlePlayerInput(keyReleased->scancode, false);
    }
}

void Game::update(sf::Time deltaTime) {
    mWorld.update(deltaTime);
}

void Game::render() {
    mWindow.clear();
    mWorld.draw();
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Scancode key, bool isPressed) {
    // default
}