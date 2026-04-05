#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H
#include <unordered_map>
#include <memory>
#include <string>

template <typename Resource, typename Identifier>
class ResourceHolder {
    public:
        template <typename... Types>
        void load(Identifier id, const std::string &fileName, Types&&... args);
        Resource& get(Identifier id);
        const Resource& get(Identifier id) const;

    private:
        std::unordered_map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "ResourceHolder.inl"

#endif