#include "game.hpp"

Game::Game() : mWindow(sf::VideoMode({640, 480}), "Shoot 'Em Up"), mPlayer() {
    mPlayer.setRadius(40.f);
    mPlayer.setPosition({100.f, 100.f});
    mPlayer.setFillColor(sf::Color::Cyan);
}

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
    sf::Vector2f movement({0.f, 0.f});
    if (mIsMovingUp)
        movement.y -= mPlayerSpeed;
    if (mIsMovingLeft)
        movement.x -= mPlayerSpeed;
    if (mIsMovingDown)
        movement.y += mPlayerSpeed;
    if (mIsMovingRight)
        movement.x += mPlayerSpeed;
    if (movement.x != 0.f && movement.y != 0) {
        movement.x *= 0.7071f;
        movement.y *= 0.7071f;
    }
    mPlayer.move(movement * deltaTime.asSeconds());
}

void Game::render() {
     mWindow.clear();
     mWindow.draw(mPlayer);
     mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Scancode key, bool isPressed) {
    if (key == sf::Keyboard::Scancode::W)
        mIsMovingUp = isPressed;
    if (key == sf::Keyboard::Scancode::A)
        mIsMovingLeft = isPressed;
    if (key == sf::Keyboard::Scancode::S)
        mIsMovingDown = isPressed;
    if (key == sf::Keyboard::Scancode::D)
        mIsMovingRight = isPressed;
}