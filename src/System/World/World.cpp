#include "World.hpp"

#include "TextureHolder.hpp"
#include "TextureIDs.hpp"
#include "SceneNode.hpp"
#include "CommandQueue.hpp"
#include "Aircraft.hpp"
#include "SpriteNode.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

#include <array>
#include <memory>
#include <utility>

World::World(sf::RenderWindow& window, TextureHolder& textures) : 
        mWindow(window),
        mWorldView(window.getDefaultView()),
        mTextures(textures), 
        mSceneGraph(), 
        mSceneLayers(),
        mCommandQueue(),
        mWorldBoundsHeight(2000.f),
        mWorldBounds({0.f, -mWorldBoundsHeight}, {mWorldView.getSize().x, mWorldBoundsHeight}), 
        mSpawnPosition({mWorldView.getSize().x / 2.f, -mWorldView.getSize().y / 2.f}), 
        mScrollSPeed(-50.f), 
        mPlayerAircraft(nullptr) { 
    buildScene();    
    mWorldView.setCenter(mSpawnPosition);
}

CommandQueue& World::getCommandQueue() {
    return mCommandQueue;
}

void World::draw() const {
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

void World::update(sf::Time dt) {
    mWorldView.move({0.f, mScrollSPeed * dt.asSeconds()});

    mPlayerAircraft->setVelocity({0.f, mScrollSPeed});

    while (!mCommandQueue.isEmpty())
        mSceneGraph.executeCommand(mCommandQueue.pop(), dt);

    mSceneGraph.update(dt);
    keepInBounds();
}

void World::buildScene() {
    for(int i = 0; i < World::LAYERCOUNT; i++) {
        SceneNode::SNPtr layer = std::make_unique<SceneNode>();
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }

    sf::Texture& desertTexture = mTextures.get(Textures::ID::Background_Desert);
    desertTexture.setRepeated(true);
    sf::IntRect backgroundRect(mWorldBounds);
    backgroundRect.position.y = 0;
    std::unique_ptr<SpriteNode> backgroundSprite = std::make_unique<SpriteNode>(desertTexture, backgroundRect);
    backgroundSprite->setPosition({0.f, -mWorldBoundsHeight});
    mSceneLayers[BACKGROUND]->attachChild(std::move(backgroundSprite));

    std::unique_ptr<Aircraft> leader = std::make_unique<Aircraft>(Aircraft::Type::Eagle, mTextures);
    mPlayerAircraft = leader.get();
    mPlayerAircraft->setPosition(mSpawnPosition);
    mSceneLayers[AIR]->attachChild(std::move(leader));

    std::unique_ptr<Aircraft> leftEscort = std::make_unique<Aircraft>(Aircraft::Type::Owl, mTextures);
    leftEscort->setPosition({-45.f, 25.f});
    mPlayerAircraft->attachChild(std::move(leftEscort));

    std::unique_ptr<Aircraft> rightEscort = std::make_unique<Aircraft>(Aircraft::Type::Phoenix, mTextures);
    rightEscort->setPosition({45.f, 25.f});
    mPlayerAircraft->attachChild(std::move(rightEscort));
}

void World::keepInBounds() {
    sf::FloatRect bounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
    sf::Vector2f position = mPlayerAircraft->getGlobalPosition();
    const float borderDistance = 16.f;
    
    position.x = std::max(position.x, bounds.position.x + borderDistance);
    position.x = std::min(position.x, bounds.position.x + bounds.size.x - borderDistance);
    position.y = std::max(position.y, bounds.position.y + borderDistance);
    position.y = std::min(position.y, bounds.position.y + bounds.size.y - borderDistance);
    
    mPlayerAircraft->setPosition(position);
}