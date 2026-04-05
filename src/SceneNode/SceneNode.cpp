#include "SceneNode.hpp"
#include <utility>
#include <algorithm>

SceneNode::SceneNode() : mParent(nullptr) {}

void SceneNode::attachChild(SNPtr child) {
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::SNPtr SceneNode::detachChild(const SceneNode& child) {
    auto func = [&](SNPtr& ptr) -> bool {
        return ptr.get() == &child;};
    auto it = std::find_if(mChildren.begin(), mChildren.end(), func);
    assert(it != mChildren.end() && "SceneNode::detachChild - Node was not found");
    SNPtr result = std::move(*it);
    result->mParent = nullptr;
    mChildren.erase(it);
    return result;
}

void SceneNode::update(sf::Time dt) {
    updateCurrent(dt);
    updateChildren(dt);
}

sf::Transform SceneNode::getGlobalTransform() const {
    sf::Transform transform = sf::Transform::Identity;
    const SceneNode *current = this;
    while (this != nullptr) {
        transform = this->getTransform() * transform;
        current = this->mParent;
    }
    return transform;
} 

sf::Vector2f SceneNode::getGlobalPosition() const {
    return getGlobalTransform() * sf::Vector2f({0.f, 0.f});
}

void SceneNode::updateCurrent(sf::Time dt) {
    // default
}

void SceneNode::updateChildren(sf::Time dt) {
    for (const SNPtr& child : mChildren)
        child->update(dt);
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    drawCurrent(target, states);
    drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    // default
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const SNPtr& child : mChildren)
        child->draw(target, states);
}