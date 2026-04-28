#include "LoadingState.hpp"

#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "SpriteNode.hpp"
#include "TextureHolder.hpp"
#include "TextureIDs.hpp"
#include "GameTextures.hpp"
#include "FontHolder.hpp"
#include "FontIDs.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>
#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>
#include <utility>

LoadingState::LoadingState(StateStack& stack, Context context) :
        State(stack, context),
        loadingCircle(context.mTextures->get(Textures::Others_Loading_Circle)),
        mProgressBar(),
        mProgressBarBackground(),
        mProgress(0.f),
        mCurrentLoadingResource(context.mFonts->get(Fonts::ARLRDBD)),
        mCurrentPath(),
        mFinished(false),
        mMutex(),
        mThread() {
    loadResources();

    sf::RenderWindow& window = *getContext().mWindow;
    sf::Vector2f progressBarSize = {window.getSize().x - 40.f, 20.f};
    window.setView(window.getDefaultView());
    sf::Vector2f viewCenter = window.getView().getCenter();

    mCurrentLoadingResource.setCharacterSize(10);

    loadingCircle.setPosition({viewCenter.x, viewCenter.y - 20.f});
    loadingCircle.setScale({0.1f, 0.1f});

    mProgressBarBackground.setSize(progressBarSize);
    Utility::centerOrigin(mProgressBarBackground);
    mProgressBarBackground.setPosition({viewCenter.x, viewCenter.y + 20.f});
    mProgressBarBackground.setFillColor(sf::Color(192, 192, 192)); // light grey
    
    mProgressBar.setSize(progressBarSize);
    Utility::centerOrigin(mProgressBar);
    mProgressBar.setPosition({viewCenter.x, viewCenter.y + 20.f});
    mProgressBar.setFillColor(sf::Color::Green);
    mProgressBar.setScale({0.f, 1.f});
}

LoadingState::~LoadingState() {
    if (mThread.joinable())
        mThread.join();
}

bool LoadingState::processEvents(const sf::Event& event) {
    return true;
}

bool LoadingState::update(sf::Time dt) {
    if (mFinished) {
        requestStackPop();
        requestStackPush(States::Game);
        return true;
    }
    loadingCircle.rotate(sf::degrees(180.f * dt.asSeconds()));
    mProgressBar.setScale({mProgress, 1.f}); 
    {
        std::lock_guard<std::mutex> lock(mMutex);
        mCurrentLoadingResource.setString(mCurrentPath);
    }
    Utility::centerOrigin(mCurrentLoadingResource);
    mCurrentLoadingResource.setPosition(getContext().mWindow->getView().getCenter());
    return true;
}

void LoadingState::draw() const {
    sf::RenderWindow& window = *getContext().mWindow;
    window.setView(window.getDefaultView());
    window.draw(loadingCircle);
    window.draw(mCurrentLoadingResource);
    window.draw(mProgressBarBackground);
    window.draw(mProgressBar);
}

void LoadingState::loadResources() {
    mThread = std::thread([this] () {
        TextureHolder& textures = *getContext().mTextures;
        float total = GameTextures::texturesArray.size();
        float current = 0;
        for (const auto& texture : GameTextures::texturesArray) {
            std::string textureName(texture.path);
            textures.load(texture.id, textureName);
            current++;
            {
                std::lock_guard<std::mutex> lock(mMutex);
                mCurrentPath = "Loading: " + textureName;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // do quá ít tài nguyên nên làm chậm để dễ thấy thanh tiến độ nạp
            mProgress = current / total;
        }
        mFinished = true;
    });
}