#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.hpp"
#include "World.hpp"

#include <SFML/System/Time.hpp>

class Player;
class StateStack;

namespace sf {
    class Event;
}

class GameState : public State {
    public:
        GameState(StateStack& stack, Context context);
        ~GameState();
        bool processEvents(const sf::Event& event) override;
        bool update(sf::Time dt) override;
        void draw() const override; 
    private:
        World mWorld;
        Player& mPlayer;
};

#endif