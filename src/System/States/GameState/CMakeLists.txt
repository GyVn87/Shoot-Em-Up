add_library(GameState)

target_sources(GameState
    PRIVATE GameState.cpp
    PUBLIC
        FILE_SET HEADERS
        FILES 
            GameState.hpp
)

target_link_libraries(GameState 
    PUBLIC
        State
        World
        SFML::System
    PRIVATE 
        Player
        CommandQueue
        ResourceHolder
        SFML::Window
)
