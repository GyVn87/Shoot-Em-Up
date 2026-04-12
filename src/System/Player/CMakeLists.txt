add_library(Player)

target_sources(Player
    PRIVATE 
        Player.cpp
    PUBLIC 
        FILE_SET HEADERS 
        FILES 
            Player.hpp
)

target_link_libraries(Player
    PUBLIC
        Command
        SFML::Window
    PRIVATE 
        CommandQueue
        Entities
        Category
        SFML::System
)