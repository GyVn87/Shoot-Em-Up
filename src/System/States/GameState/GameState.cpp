#include "GameState.hpp"

#include "State.hpp"
#include "World.hpp"
#include "Player.hpp"
#include "CommandQueue.hpp"
#include "TextureIDs.hpp"
#include "GameTextures.hpp"
#include "TextureHolder.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>

GameState::GameState(StateStack& stack, Context context) : 
    State(stack, context), 
    mWorld(*context.mWindow, *context.mTextures), 
    mPlayer(*context.mPlayer) {}

GameState::~GameState() {
    TextureHolder& textures = *getContext().mTextures;
    for (const auto& texture : GameTextures::texturesArray)
        textures.unload(texture.id);
}

bool GameState::processEvents(const sf::Event& event) {
    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleEvent(event, commands);
    
    if (event.is<sf::Event::KeyPressed>() &&
            event.getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scancode::Escape)
        requestStackPush(States::Pause);

    return true;
}

bool GameState::update(sf::Time dt) {
    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleRealTimeInput(commands);
    mWorld.update(dt);
    return true;
}

void GameState::draw() const {
    mWorld.draw();
}