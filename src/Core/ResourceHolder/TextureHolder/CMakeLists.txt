target_sources(ResourceHolder
    INTERFACE
        FILE_SET texture_holder
        TYPE HEADERS 
        FILES 
            TextureHolder.hpp
            TextureIDs.hpp
            GameTextures.hpp
)