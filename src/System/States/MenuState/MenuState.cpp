#include "MenuState.hpp"

#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "SpriteNode.hpp"
#include "TextureHolder.hpp"
#include "TextureIDs.hpp"
#include "FontHolder.hpp"
#include "FontIDs.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

MenuState::MenuState(StateStack& stack, Context context) : 
        State(stack, context), 
        mBackground(context.mTextures->get(Textures::Background_Title)),
        mOptions(),
        mCurrentIndex(0) {
    sf::Font& font = context.mFonts->get(Fonts::ARLRDBD);       
    sf::Vector2f viewCenter = context.mWindow->getView().getCenter();
    const float buttonOffset = 30.f;

    sf::Text playOption(font, "Play");
    Utility::centerOrigin(playOption);
    mOptions.push_back(playOption);

    sf::Text exitOption(font, "Exit");
    Utility::centerOrigin(exitOption);
    mOptions.push_back(exitOption);

    for (std::size_t i = 0; i < mOptions.size(); i++)
        mOptions[i].setPosition({viewCenter.x, viewCenter.y + buttonOffset * i});
}

bool MenuState::processEvents(const sf::Event& event) {
    if (!event.is<sf::Event::KeyPressed>())
        return true;

    sf::Keyboard::Scancode pressedKey = event.getIf<sf::Event::KeyPressed>()->scancode;
    switch (pressedKey) {
        case sf::Keyboard::Scancode::Up:
            if (mCurrentIndex > 0)
                mCurrentIndex--;
            else
                mCurrentIndex = mOptions.size() - 1;
            break;
        case sf::Keyboard::Scancode::Down:
            if (mCurrentIndex < mOptions.size() - 1)
                mCurrentIndex++;
            else
                mCurrentIndex = 0;
            break;
        case sf::Keyboard::Scancode::Enter:
            changeState();
            break;
    }
    return true;
}

bool MenuState::update(sf::Time dt) {
    for (sf::Text& option : mOptions)
        option.setFillColor(sf::Color::White);
    mOptions[mCurrentIndex].setFillColor(sf::Color::Yellow);
    return true;
}

void MenuState::draw() const {
    sf::RenderWindow& window = *getContext().mWindow;
    window.setView(window.getDefaultView());
    window.draw(mBackground);
    for (const sf::Text& option : mOptions)
        window.draw(option);
} 

void MenuState::changeState() const {
    switch (mCurrentIndex) {
        case OptionNames::Play:
            requestStackPop();
            requestStackPush(States::Loading);
            break;
        case OptionNames::Exit:
            requestStackPop();
            break;
    }
}