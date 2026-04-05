cmake_minimum_required(VERSION 4.2.1)

project(ShootEmUp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CACHE{BUILD_SHARED_LIBS} TYPE BOOL HELP "Build using shared libraries" FORCE VALUE OFF)

include(FetchContent)
FetchContent_Declare(
	SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 3.0.2
	GIT_SHALLOW ON
	EXCLUDE_FROM_ALL
	SYSTEM
)
FetchContent_MakeAvailable(SFML)

add_subdirectory(src)

set(CACHE{CMAKE_INSTALL_PREFIX} TYPE STRING FORCE VALUE ${CMAKE_BINARY_DIR}/install)

install(TARGETS Main  
		RUNTIME DESTINATION .)
install(DIRECTORY "${CMAKE_SOURCE_DIR}/assets" DESTINATION .)