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
        ResourceHolder
        SceneNode
        CommandQueue
        SFML::Graphics
        SFML::System
    PRIVATE
        SpriteNode
        Entities
)