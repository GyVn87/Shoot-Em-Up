#include "Game.hpp"

#include "World.hpp"
#include "Player.hpp"
#include "CommandQueue.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>


Game::Game() : mWindow(sf::VideoMode({640, 480}), "Shoot 'Em Up"), mWorld(mWindow), mPlayer() {}

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
    CommandQueue& commands = mWorld.getCommandQueue();
    while (const std::optional<sf::Event> event = mWindow.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            mWindow.close();
        else
            mPlayer.handleEvent(*event, commands); 
    }
    mPlayer.handleRealTimeInput(commands);
}

void Game::update(sf::Time deltaTime) {
    mWorld.update(deltaTime);
}

void Game::render() {
    mWindow.clear();
    mWorld.draw();
    mWindow.display();
}