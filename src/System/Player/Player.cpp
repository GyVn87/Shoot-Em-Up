#include "Player.hpp"

#include "Aircraft.hpp"
#include "Command.hpp"
#include "CommandQueue.hpp"
#include "Category.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

#include <unordered_map>
#include <iostream>

struct AircraftMover {
    AircraftMover(sf::Vector2f velocity) : mVelocity(velocity) {};

    void operator()(Aircraft& aircraft, sf::Time) const {
        aircraft.accelerate(mVelocity);
    }

    sf::Vector2f mVelocity;
};

Player::Player() : mKeyBinding(), mActionBinding() {
    initializeKeyBinding();
    initializeActionBinding();
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands) const {
    if (!event.is<sf::Event::KeyPressed>()) return;
    auto found = mKeyBinding.find(event.getIf<sf::Event::KeyPressed>()->scancode);
    if (found != mKeyBinding.end() && !isRealTimeAction(found->second))
        commands.push(mActionBinding.at(found->second));
}

void Player::handleRealTimeInput(CommandQueue& commands) const {
    for (const auto& pair : mKeyBinding) 
        if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second))
            commands.push(mActionBinding.at(pair.second));
}

void Player::initializeKeyBinding() {
    mKeyBinding[sf::Keyboard::Scancode::Up] = MoveUp;
    mKeyBinding[sf::Keyboard::Scancode::Down] = MoveDown;
    mKeyBinding[sf::Keyboard::Scancode::Left] = MoveLeft;
    mKeyBinding[sf::Keyboard::Scancode::Right] = MoveRight;
    mKeyBinding[sf::Keyboard::Scancode::P] = OutputPosition;    
}

void Player::initializeActionBinding() {
    const float playerSpeed = 30.f;
    
    mActionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover({0.f, -playerSpeed}));    
    mActionBinding[MoveDown].action = derivedAction<Aircraft>(AircraftMover({0.f, playerSpeed}));    
    mActionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover({-playerSpeed, 0.f}));    
    mActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover({playerSpeed, 0.f}));    
    mActionBinding[OutputPosition].action = derivedAction<Aircraft>([] (Aircraft& node, sf::Time dt) {
            std::cout << "x: " << node.getGlobalPosition().x << ", y: " << node.getGlobalPosition().y << '\n';});

    for (auto& pair : mActionBinding)
        pair.second.category = Category::PlayerAircraft;        
}

bool Player::isRealTimeAction(Action action) const {
    switch (action) {
        case MoveLeft:
        case MoveRight:
        case MoveUp:
        case MoveDown:
            return true;
    }
    return false;
}