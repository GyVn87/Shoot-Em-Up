add_library(Command)

target_sources(Command
    PRIVATE 
        Command.cpp
    PUBLIC 
    FILE_SET HEADERS
    FILES 
        Command.hpp
)

target_link_libraries(Command
    PUBLIC
        SFML::System
    PRIVATE 
        Category
)