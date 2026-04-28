#ifndef TITLE_STATE_H
#define TITLE_STATE_H

#include "State.hpp"
#include "SpriteNode.hpp"

#include "SFML/Graphics/Text.hpp"
#include <SFML/System/Time.hpp>

class StateStack;

namespace sf {
    class Event;
}

class TitleState : public State {
    public:
        TitleState(StateStack& stack, Context context);
        bool processEvents(const sf::Event& event) override;
        bool update(sf::Time dt) override;
        void draw() const override; 
    private:
        SpriteNode mBackground;
        sf::Text mText;
        bool mShowText;
        sf::Time mTextEffectTime;
};

#endif