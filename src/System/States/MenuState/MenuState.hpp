#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "State.hpp"
#include "SpriteNode.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

#include <vector>

class StateStack;

class MenuState : public State {
    public: 
        enum OptionNames {
            Play,
            Exit
        };
    public:
        MenuState(StateStack& stack, Context context);
        bool processEvents(const sf::Event& event) override;
        bool update(sf::Time dt) override;
        void draw() const override; 
        void changeState() const;
    private: 
        SpriteNode mBackground;
        std::vector<sf::Text> mOptions;
        std::size_t mCurrentIndex;
};

#endif