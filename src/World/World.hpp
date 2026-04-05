#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include "TextureHolder.hpp"
#include "SceneNode.hpp"
#include "Aircraft.hpp"
#include <array>

class World {
    public:
        explicit World(sf::RenderWindow& window);
        World(const World&) = delete;
        World operator=(const World&) = delete;
        void draw();
        void update(sf::Time dt);
    private:
        void loadTextures();
        void buildScene();
    private:
        enum Layers {
            BACKGROUND,
            AIR,
            LAYERCOUNT
        };
    private:
        sf::RenderWindow& mWindow;
        sf::View mWorldView;
        TextureHolder mTextures;
        SceneNode mSceneGraph;
        std::array<SceneNode*, LAYERCOUNT> mSceneLayers;
        float mWorldBoundsHeight;
        sf::FloatRect mWorldBounds;
        sf::Vector2f mSpawnPosition;
        float mScrollSPeed;
        Aircraft* mPlayerAircraft;
};

#endif