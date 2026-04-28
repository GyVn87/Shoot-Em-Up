#include "StateStack.hpp"

#include "State.hpp"
#include "StateIdentifiers.hpp"

#include <SFML/System/Time.hpp>

#include <cassert>

StateStack::StateStack(State::Context context) :
        mStack(),
        mPendingList(),
        mContext(context),
        mFactories() {}

void StateStack::pushState(States::ID stateID) {
    mPendingList.emplace_back(Push, stateID);
}

void StateStack::popState() {
    mPendingList.emplace_back(Pop);
}

void StateStack::clearStates() {
    mPendingList.emplace_back(Clear);
}

bool StateStack::isEmpty() const {
    return mStack.empty();
}

void StateStack::processEvents(const sf::Event& event) {
    for (auto it = mStack.rbegin(); it != mStack.rend(); it++) 
        if (!(*it)->processEvents(event))
            break;
    applyPendingChange();
}

void StateStack::update(sf::Time dt) {
    for (auto it = mStack.rbegin(); it != mStack.rend(); it++) 
        if (!(*it)->update(dt))
            break;
    applyPendingChange();
}

void StateStack::draw() const {
    for (auto it = mStack.begin(); it != mStack.end(); it++)
        (*it)->draw();
}

State::SPtr StateStack::createState(States::ID id) const {
    auto it = mFactories.find(id);
    assert(it != mFactories.end() && "StateStack::createState - State ID was not found");
    return it->second();
}

void StateStack::applyPendingChange() {
    for (PendingChange change : mPendingList) {
        switch (change.mAction) {
            case Push:
                mStack.push_back(createState(change.mStateID));
                break;
            case Pop:
                mStack.pop_back();
                break;
            case Clear:
                mStack.clear();
                break;
        }
    }
    mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID) : mAction(action), mStateID(stateID) {}