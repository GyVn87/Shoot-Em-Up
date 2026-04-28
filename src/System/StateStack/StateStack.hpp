#ifndef STACK_STATE_H
#define STACK_STATE_H

#include "State.hpp"
#include "StateIdentifiers.hpp"

#include <SFML/System/Time.hpp>

#include <unordered_map>
#include <functional>
#include <utility>
#include <vector>

namespace sf {
    class Event;
}

class StateStack {
    public:
        enum Action {
            Push,
            Pop,
            Clear
        };
    public:
        StateStack(State::Context context);

        template <typename T>
        void registerState(States::ID id);

        void pushState(States::ID stateID);
        void popState();
        void clearStates();
        bool isEmpty() const;

        void processEvents(const sf::Event& event);
        void update(sf::Time dt);
        void draw() const;
    private:
        struct PendingChange {
            explicit PendingChange(Action action, States::ID stateID = States::ID::None);
            Action mAction;
            States::ID mStateID;
        };
    private:
        State::SPtr createState(States::ID id) const;
        void applyPendingChange();
    private:
        std::vector<State::SPtr> mStack; 
        std::vector<PendingChange> mPendingList;
        State::Context mContext;
        std::unordered_map<States::ID, std::function<State::SPtr()>> mFactories;
};

template <typename T>
void StateStack::registerState(States::ID id) {
    mFactories[id] = [this] () {
        return std::make_unique<T>(*this, mContext);};
}

#endif