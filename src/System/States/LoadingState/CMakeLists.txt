add_library(LoadingState)

target_sources(LoadingState
    PRIVATE 
        LoadingState.cpp
    PUBLIC 
        FILE_SET HEADERS
        FILES 
            LoadingState.hpp
)

target_link_libraries(LoadingState
    PUBLIC
        State
        SpriteNode
        SFML::Graphics
        SFML::System
    PRIVATE 
        ResourceHolder
        Utility
)