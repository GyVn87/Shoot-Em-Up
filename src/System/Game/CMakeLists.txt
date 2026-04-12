add_library(Game)

target_sources(Game
    PRIVATE Game.cpp
    PUBLIC
        FILE_SET HEADERS
        FILES 
            Game.hpp
)

target_link_libraries(Game 
    PUBLIC
        World
        Player
        SFML::Graphics
        SFML::System
    PRIVATE 
        CommandQueue
        SFML::Window
)
