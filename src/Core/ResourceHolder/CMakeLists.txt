add_library(ResourceHolder INTERFACE)

target_sources(ResourceHolder 
	INTERFACE 
		FILE_SET HEADERS
		FILES 
			ResourceHolder.hpp 
			ResourceHolder.inl 
)

add_subdirectory(TextureHolder)
add_subdirectory(FontHolder)
add_subdirectory(ShaderHolder)

target_link_libraries(ResourceHolder INTERFACE SFML::Graphics)

target_compile_features(ResourceHolder INTERFACE cxx_std_20)