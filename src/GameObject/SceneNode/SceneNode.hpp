#ifndef SCENENODE_H
#define SCENENODE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include <memory>
#include <vector>

struct Command;

namespace sf { class RenderTarget; }

class SceneNode : public sf::Drawable, public sf::Transformable {
    public:
        typedef std::unique_ptr<SceneNode> SNPtr;

        SceneNode();
        SceneNode(const SceneNode&) = delete;
        SceneNode operator=(const SceneNode&) = delete;
        virtual ~SceneNode() = default;

        void attachChild(SNPtr child);
        SNPtr detachChild(const SceneNode& child);

        void update(sf::Time dt);

        sf::Transform getGlobalTransform() const;
        sf::Vector2f getGlobalPosition() const;

        virtual unsigned int getCategory() const;
        void executeCommand(const Command& command, sf::Time dt);
    private:
        virtual void updateCurrent(sf::Time dt);
        virtual void updateChildren(sf::Time dt) const;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override; // bỏ vào trong private vẫn dùng được, vì có thể gọi bằng cách "target.draw(node);"
        virtual void drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const;
        virtual void drawChildren(sf::RenderTarget& target, const sf::RenderStates& states) const;
    private:
        std::vector<SNPtr> mChildren;
        SceneNode* mParent;
};

#endif