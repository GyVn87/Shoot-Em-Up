add_library(SpriteNode)

target_sources(SpriteNode
    PRIVATE
        SpriteNode.cpp
    PUBLIC
        FILE_SET HEADERS
        FILES
            SpriteNode.hpp
)

target_link_libraries(SpriteNode 
    PUBLIC 
        SceneNode  
)