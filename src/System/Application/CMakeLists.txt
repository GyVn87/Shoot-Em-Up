add_library(Application)

target_sources(Application
    PRIVATE 
        Application.cpp
    PUBLIC 
        FILE_SET HEADERS
        FILES 
            Application.hpp
)

target_link_libraries(Application
    PUBLIC 
        StateStack
        Player
        ResourceHolder
        SFML::Graphics
        SFML::System
    PRIVATE
        State
        TitleState
        MenuState
        GameState
        PauseState
        LoadingState
        SFML::System
)