#ifndef COMMAND_H
#define COMMAND_H

#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>

class SceneNode;

struct Command {
    Command();
    std::function<void(SceneNode&, sf::Time)> action;
    unsigned int category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode& node, sf::Time dt)> derivedAction(Function func) {
    return [func] (SceneNode& node, sf::Time dt) {
        assert(dynamic_cast<GameObject*>(&node) != nullptr);
        func(static_cast<GameObject&>(node), dt);
    };
}

#endif