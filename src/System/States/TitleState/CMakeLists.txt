add_library(TitleState)

target_sources(TitleState
    PRIVATE 
        TitleState.cpp
    PUBLIC 
        FILE_SET HEADERS
        FILES 
            TitleState.hpp
)

target_link_libraries(TitleState 
    PUBLIC 
        State
        SpriteNode
        SFML::Graphics
        SFML::System
    PRIVATE 
        Utility
        SFML::Window
)