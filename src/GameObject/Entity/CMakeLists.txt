add_library(Entity)

target_sources(Entity
    PRIVATE 
        Entity.cpp
    PUBLIC 
        FILE_SET HEADERS
        FILES Entity.hpp
)

target_link_libraries(Entity 
    PUBLIC 
        SceneNode
        SFML::System
)