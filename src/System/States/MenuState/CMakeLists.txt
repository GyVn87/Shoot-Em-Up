add_library(MenuState)

target_sources(MenuState
    PRIVATE 
        MenuState.cpp
    PUBLIC 
        FILE_SET HEADERS
        FILES 
            MenuState.hpp
)

target_link_libraries(MenuState 
    PUBLIC 
        State
        SpriteNode
        SFML::Graphics
        SFML::System
    PRIVATE 
        ResourceHolder
        Utility
        SFML::Window

)