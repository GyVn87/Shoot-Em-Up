#ifndef PLAYER_H
#define PLAYER_H

#include "Command.hpp"

#include <SFML/Window/Keyboard.hpp>

#include <unordered_map>

class CommandQueue;

namespace sf { class Event; }

class Player {
    public:
        enum Action {
            MoveLeft,
            MoveRight,
            MoveUp,
            MoveDown,
            OutputPosition
        };
    public:
        Player();
        void handleEvent(const sf::Event& event, CommandQueue& commands) const;
        void handleRealTimeInput(CommandQueue& commands) const;
    private:
        void initializeKeyBinding();
        void initializeActionBinding();
        bool isRealTimeAction(Action action) const;
    private:
        std::unordered_map<sf::Keyboard::Scancode, Action> mKeyBinding;
        std::unordered_map<Action, Command> mActionBinding;
};

#endif