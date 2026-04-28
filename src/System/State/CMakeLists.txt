add_library(State)

target_sources(State
    PRIVATE 
        State.cpp
    PUBLIC
        FILE_SET HEADERS
        FILES 
            State.hpp
            StateIdentifiers.hpp
)

target_link_libraries(State
    PUBLIC
        SFML::System
        ResourceHolder
    PRIVATE 
        StateStack
)