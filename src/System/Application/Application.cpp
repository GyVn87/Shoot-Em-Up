#include "Application.hpp"

#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "StateStack.hpp"
#include "TitleState.hpp"
#include "MenuState.hpp"
#include "GameState.hpp"
#include "LoadingState.hpp"
#include "PauseState.hpp"
#include "Player.hpp"
#include "TextureHolder.hpp"
#include "TextureIDs.hpp"
#include "FontHolder.hpp"
#include "FontIDs.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

Application::Application() : 
        mWindow(sf::VideoMode({640, 480}), "Shoot 'Em Up"), 
        mTextures(), 
        mFonts(), 
        mPlayer(), 
        mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer)) {
    mWindow.setKeyRepeatEnabled(false);
    loadResources();
    registerStates();
    mStateStack.pushState(States::Title);
}

void Application::run() {
    const sf::Time mTimePerFrame = sf::seconds(1.f / 60.f);
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {
        sf::Time deltaTime = clock.restart();
        timeSinceLastUpdate += deltaTime;
        while (timeSinceLastUpdate >= mTimePerFrame) {
            timeSinceLastUpdate -= mTimePerFrame;
            processEvents();
            update(mTimePerFrame);
            if (mStateStack.isEmpty())
                mWindow.close();
        }
        render();
    }
}

void Application::registerStates() {
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<PauseState>(States::Pause);
    mStateStack.registerState<LoadingState>(States::Loading);
}

void Application::processEvents() {
    while (const std::optional<sf::Event> event = mWindow.pollEvent()) {
        mStateStack.processEvents(*event);
        if (event->is<sf::Event::Closed>())
            mWindow.close(); 
    }
}

void Application::update(sf::Time dt) {
    mStateStack.update(dt);
}

void Application::render() {
    mWindow.clear();
    mStateStack.draw();
    mWindow.display();
}

void Application::loadResources() {
    mTextures.load(Textures::Background_Title, "assets/images/Background/Title.png");
    mTextures.load(Textures::Others_Loading_Circle, "assets/images/Others/Loading_Circle.png");
    mFonts.load(Fonts::ARLRDBD, "assets/fonts/ARLRDBD.ttf");
}