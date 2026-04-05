add_library(World)

target_sources(World
    PRIVATE 
        World.cpp
    PUBLIC
        FILE_SET HEADERS
        FILES
            World.hpp
)

target_link_libraries(World
    PUBLIC
        SFML::Graphics
        ResourceHolder
        SceneNode
        Entities
    PRIVATE
        SpriteNode
)