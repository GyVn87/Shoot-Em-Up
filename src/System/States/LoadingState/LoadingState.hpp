#ifndef LOADING_STATE_H
#define LOADING_STATE_H

#include "State.hpp"
#include "SpriteNode.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

#include <string>
#include <atomic>
#include <mutex>
#include <thread>

class StateStack;

namespace sf {
    class Event;
}

class LoadingState : public State {
    public:
        LoadingState(StateStack& stack, Context context);
        ~LoadingState();
        bool processEvents(const sf::Event& event) override;
        bool update(sf::Time dt) override;
        void draw() const override; 
    private:
        void loadResources();
    private:
        SpriteNode loadingCircle;
        sf::RectangleShape mProgressBar;
        sf::RectangleShape mProgressBarBackground;
        std::atomic<float> mProgress;
        sf::Text mCurrentLoadingResource;
        std::string mCurrentPath; 
        bool mFinished;
        std::mutex mMutex;
        std::thread mThread;    
};

#endif