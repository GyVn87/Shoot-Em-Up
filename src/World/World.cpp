#include "World.hpp"
#include "SpriteNode.hpp"
#include <utility>

World::World(sf::RenderWindow& window) : 
    mWindow(window),
    mWorldView(window.getDefaultView()),
    mTextures(), 
    mSceneGraph(), 
    mSceneLayers(),
    mWorldBoundsHeight(2000.f),
    mWorldBounds({0.f, -mWorldBoundsHeight}, {mWorldView.getSize().x, mWorldBoundsHeight}), 
    mSpawnPosition({mWorldView.getSize().x / 2.f, -mWorldView.getSize().y / 2.f}), 
    mScrollSPeed(-50.f), 
    mPlayerAircraft(nullptr) 
{ 
    loadTextures();
    buildScene();    
    mWorldView.setCenter(mSpawnPosition);
}

void World::draw() {
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

void World::update(sf::Time dt) {
    mWorldView.move({0.f, mScrollSPeed * dt.asSeconds()});
    sf::Vector2f currentPosition = mPlayerAircraft->getPosition();
    if (currentPosition.x > mWorldBounds.size.x + 150.f || currentPosition.x < -150.f) {
        sf::Vector2f currentVelocity = mPlayerAircraft->getVelocity();
        currentVelocity.x *= -1.f;
        mPlayerAircraft->setVelocity(currentVelocity);
    }
    mSceneGraph.update(dt);
}

void World::loadTextures() {
    mTextures.load(Textures::ID::Aircraft_Eagle, "assets/images/Aircraft/Eagle.png");
    mTextures.load(Textures::ID::Background_Desert, "assets/images/Background/Desert.png");
    mTextures.load(Textures::ID::Aircraft_Owl, "assets/images/Aircraft/Owl.png");
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

    std::unique_ptr<Aircraft> leader = std::make_unique<Aircraft>(Aircraft::Type::Owl, mTextures);
    mPlayerAircraft = leader.get();
    mPlayerAircraft->setPosition(mSpawnPosition);
    mPlayerAircraft->setVelocity({80.f, mScrollSPeed});
    mPlayerAircraft->setScale({2.f, 2.f});
    mSceneLayers[AIR]->attachChild(std::move(leader));

    std::unique_ptr<Aircraft> leftEscort = std::make_unique<Aircraft>(Aircraft::Type::Eagle, mTextures);
    leftEscort->setPosition({-45.f, 25.f});
    mPlayerAircraft->attachChild(std::move(leftEscort));

    std::unique_ptr<Aircraft> rightEscort = std::make_unique<Aircraft>(Aircraft::Type::Eagle, mTextures);
    rightEscort->setPosition({45.f, 25.f});
    mPlayerAircraft->attachChild(std::move(rightEscort));
}