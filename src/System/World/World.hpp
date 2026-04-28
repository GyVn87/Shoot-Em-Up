#ifndef WORLD_H
#define WORLD_H

#include "SceneNode.hpp"
#include "CommandQueue.hpp"

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

#include <array>

class Aircraft;

namespace Textures {
    enum ID : short;
}

template <typename Resource, typename Identifier>
class ResourceHolder;
using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;

namespace sf { class RenderWindow; }

class World {
    public:
        World(sf::RenderWindow& window, TextureHolder& textures);
        World(const World&) = delete;
        World operator=(const World&) = delete;
        CommandQueue& getCommandQueue();
        void draw() const ;
        void update(sf::Time dt);
    private:
        void buildScene();
        void keepInBounds();
    private:
        enum Layers {
            BACKGROUND,
            AIR,
            LAYERCOUNT
        };
    private:
        sf::RenderWindow& mWindow;
        sf::View mWorldView;
        TextureHolder& mTextures;
        SceneNode mSceneGraph;
        std::array<SceneNode*, LAYERCOUNT> mSceneLayers;
        CommandQueue mCommandQueue;
        float mWorldBoundsHeight;
        sf::FloatRect mWorldBounds;
        sf::Vector2f mSpawnPosition;
        float mScrollSPeed;
        Aircraft* mPlayerAircraft;
};

#endif