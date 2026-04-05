add_library(Entities)

target_sources(Entities
    PRIVATE
        Aircraft.cpp
    PUBLIC
        FILE_SET HEADERS
        FILES
            Aircraft.hpp  
)

target_link_libraries(Entities PUBLIC Entity)
target_link_libraries(Entities PRIVATE Utility)