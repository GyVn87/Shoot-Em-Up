add_library(SceneNode)

target_sources(SceneNode
    PRIVATE SceneNode.cpp
    PUBLIC
        FILE_SET HEADERS
        FILES SceneNode.hpp
)

target_link_libraries(SceneNode PUBLIC SFML::Graphics)