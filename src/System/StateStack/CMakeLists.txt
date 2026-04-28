add_library(StateStack)

target_sources(StateStack
    PRIVATE 
        StateStack.cpp
    PUBLIC
        FILE_SET HEADERS
        FILES 
            StateStack.hpp
)

target_link_libraries(StateStack
    PUBLIC 
        State
        SFML::System
)