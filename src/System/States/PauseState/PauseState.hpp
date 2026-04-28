#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "State.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

class StateStack;

namespace sf {
    class Event;
}

class PauseState : public State {
    public:
        PauseState(StateStack& stack, Context context);
        bool processEvents(const sf::Event& event) override;
        bool update(sf::Time dt) override;
        void draw() const override; 
    private:
        sf::RectangleShape mBackgroundShape;
        sf::Text mPauseText;
        sf::Text mInstructionText;
};

#endif