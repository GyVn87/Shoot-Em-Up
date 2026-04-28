#include "PauseState.hpp"

#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "FontHolder.hpp"
#include "FontIDs.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

PauseState::PauseState(StateStack& stack, Context context) :
        State(stack, context),
        mBackgroundShape(context.mWindow->getView().getSize()),
        mPauseText(context.mFonts->get(Fonts::ARLRDBD), "GAME PAUSED"),
        mInstructionText(context.mFonts->get(Fonts::ARLRDBD), "Press Escape to return to Main Menu \n Press Space to continue") {
    sf::RenderWindow& window = *getContext().mWindow;
    window.setView(window.getDefaultView());
    sf::Vector2f viewCenter = window.getView().getCenter();        

    mBackgroundShape.setFillColor(sf::Color(160, 160, 160, 100));
    mBackgroundShape.setSize(sf::Vector2f(window.getSize()));

    mPauseText.setCharacterSize(40);
    Utility::centerOrigin(mPauseText);
    mPauseText.setPosition({viewCenter.x, viewCenter.y - window.getSize().y / 4.f});

    mInstructionText.setCharacterSize(15);
    Utility::centerOrigin(mInstructionText);
    mInstructionText.setPosition(viewCenter);
}

bool PauseState::processEvents(const sf::Event& event) {
    if (!event.is<sf::Event::KeyPressed>())
        return false;
    
    sf::Keyboard::Scancode pressedKey = event.getIf<sf::Event::KeyPressed>()->scancode;
    switch (pressedKey) {
        case sf::Keyboard::Scancode::Escape: 
            requestStackClear();
            requestStackPush(States::Menu);
            break;
        case sf::Keyboard::Scancode::Space: 
            requestStackPop();
            break;
    }
    return false;
}

bool PauseState::update(sf::Time dt) {
    return false;
}

void PauseState::draw() const {
    sf::RenderWindow& window = *getContext().mWindow;
    window.setView(window.getDefaultView());
    window.draw(mBackgroundShape);
    window.draw(mPauseText);
    window.draw(mInstructionText);
}