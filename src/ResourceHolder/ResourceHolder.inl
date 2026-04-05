#include <cassert>
#include <type_traits>
#include <utility>

template <typename Resource, typename Identifier>
template <typename... Types>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &fileName, Types&&... args) {
    std::unique_ptr<Resource> resource = std::make_unique<Resource>();
    if constexpr (std::is_same_v<Resource, sf::Shader>) {
        if (!resource->loadFromFile(fileName, std::forward<Types>(args)...))
            throw std::runtime_error("ResourceHolder<sf::Shader, Identifier>::load - Failed to load " + fileName);
    }
    else {
        if (!resource->loadFromFile(fileName))
            throw std::runtime_error("ResourceHolder<Resource, Identifier>::load - Failed to load " + fileName);
    }
    auto inserted = mResourceMap.emplace(id, std::move(resource));
    assert(inserted.second && "ResourceHolder::load - ID already exists!");
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) {
    auto it = mResourceMap.find(id);
    assert(it != mResourceMap.end() && "ResourseHolder::get - Resource ID was not found!");
    return *it->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const {
    auto it = mResourceMap.find(id);
    assert(it != mResourceMap.end() && "ResourseHolder::get - Resource ID was not found!");
    return *it->second;
}