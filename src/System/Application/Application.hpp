#ifndef APPLICATION_H 
#define APPLICATION_H

#include "StateStack.hpp"
#include "Player.hpp"
#include "TextureHolder.hpp"
#include "FontHolder.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Application {
    public:
        Application();
        void run();

        void registerStates(); 

        void processEvents();
        void update(sf::Time dt);
        void render();
    private:
        void loadResources();
    private:
        sf::RenderWindow mWindow;
        TextureHolder mTextures;
        FontHolder mFonts;
        Player mPlayer;
        StateStack mStateStack;
};

#endif