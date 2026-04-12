add_library(CommandQueue)

target_sources(CommandQueue
    PRIVATE 
        CommandQueue.cpp
    PUBLIC 
        FILE_SET HEADERS 
        FILES 
            CommandQueue.hpp
)

target_link_libraries(CommandQueue
    PUBLIC 
        Command
)