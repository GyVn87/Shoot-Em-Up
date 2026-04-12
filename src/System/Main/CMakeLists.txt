if (CMAKE_BUILD_TYPE STREQUAL "Release")
	add_executable(Main WIN32 MACOSX_BUNDLE)
else()
    add_executable(Main)
endif()

target_sources(Main PRIVATE Main.cpp)

target_link_libraries(Main PRIVATE Game)

if (TARGET SFML::Main)
    target_link_libraries(Main PRIVATE SFML::Main)
endif()