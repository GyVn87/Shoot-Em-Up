#ifndef STATE_H
#define STATE_H

#include "StateIdentifiers.hpp"
#include "TextureIDs.hpp"
#include "FontIDs.hpp"

#include <SFML/System/Time.hpp>

#include <memory>

namespace sf {
    class Event;
    class Texture;
    class Font;
    class RenderWindow;
}

template <typename Resource, typename Identifier>
class ResourceHolder;

using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;
using FontHolder = ResourceHolder<sf::Font, Fonts::ID>;

class Player;
class StateStack;

class State {
    public:
        typedef std::unique_ptr<State> SPtr;
        struct Context {
            Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player);
            sf::RenderWindow* mWindow;
            TextureHolder* mTextures;
            FontHolder* mFonts;
            Player* mPlayer;
        };
    public:
        State(StateStack& stack, Context context);
        virtual ~State() = default;
        virtual bool processEvents(const sf::Event& event) = 0;
        virtual bool update(sf::Time dt) = 0;
        virtual void draw() const = 0;
    protected:
        void requestStackPush(States::ID stateID) const;
        void requestStackPop() const;
        void requestStackClear() const;
        Context getContext() const;
    private: 
        StateStack* mStack;
        Context mContext;
};

#endif