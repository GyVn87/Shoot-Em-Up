#include "TitleState.hpp"

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
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

TitleState::TitleState(StateStack& stack, Context context) : 
        State(stack, context), 
        mBackground(context.mTextures->get(Textures::Background_Title)),
        mText(context.mFonts->get(Fonts::ARLRDBD), "Press any button to start!"),
        mShowText(true), 
        mTextEffectTime(sf::Time::Zero) {
    Utility::centerOrigin(mText);
    sf::Vector2f viewCenter = context.mWindow->getView().getCenter();        
    mText.setPosition({viewCenter.x, viewCenter.y + context.mWindow->getSize().y / 4.f});
    mText.setFillColor(sf::Color::Yellow);
}

bool TitleState::processEvents(const sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        requestStackPop();
        requestStackPush(States::Menu);
    }
    return true;
}

bool TitleState::update(sf::Time dt) {
    const sf::Time textDisplayInterval = sf::seconds(0.5f);
    mTextEffectTime += dt;
    if (mTextEffectTime >= textDisplayInterval) {
        mShowText = !mShowText;
        mTextEffectTime -= textDisplayInterval;
    }
    return true;
}

void TitleState::draw() const {
    sf::RenderWindow& window = *getContext().mWindow;
    window.setView(window.getDefaultView());
    window.draw(mBackground);
    if (mShowText)
        window.draw(mText);
}