add_library(ResourceHolder INTERFACE)

target_sources(ResourceHolder INTERFACE 
	FILE_SET HEADERS
	FILES 
		ResourceHolder.hpp 
		ResourceHolder.inl 
		TextureHolder.hpp
		ShaderHolder.hpp
		TextureIDs.hpp
)

target_link_libraries(ResourceHolder INTERFACE SFML::Graphics)