add_library(Category INTERFACE)

target_sources(Category
    PUBLIC 
        FILE_SET HEADERS 
        FILES 
            Category.hpp
)