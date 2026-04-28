add_library(PauseState)

target_sources(PauseState
    PRIVATE 
        PauseState.cpp
    PUBLIC 
        FILE_SET HEADERS
        FILES 
            PauseState.hpp
)

target_link_libraries(PauseState 
    PUBLIC 
        State
        SFML::Graphics
        SFML::System
    PRIVATE 
        ResourceHolder
        Utility
        SFML::Window
)