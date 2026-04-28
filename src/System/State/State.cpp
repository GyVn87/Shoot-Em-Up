#include "State.hpp"

#include "StateStack.hpp"

State::State(StateStack& stack, Context context) : mStack(&stack), mContext(context) {}

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player) : 
    mWindow(&window),
    mTextures(&textures),
    mFonts(&fonts),
    mPlayer(&player) {}

void State::requestStackPush(States::ID stateID) const {
    mStack->pushState(stateID);
}

void State::requestStackPop() const {
    mStack->popState();
}

void State::requestStackClear() const {
    mStack->clearStates();
}

State::Context State::getContext() const {
    return mContext;
}