add_library(Game)

target_sources(Game
    PRIVATE game.cpp
    PUBLIC
        FILE_SET HEADERS
        FILES game.hpp
)

target_compile_features(Game PUBLIC cxx_std_17)
target_link_libraries(Game PUBLIC SFML::Graphics)