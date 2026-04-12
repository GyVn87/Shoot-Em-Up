add_library(Utility)

target_sources(Utility
    PRIVATE
        Utility.cpp
    PUBLIC
        FILE_SET HEADERS
        FILES
            Utility.hpp
)

target_link_libraries(Utility PRIVATE SFML::Graphics)