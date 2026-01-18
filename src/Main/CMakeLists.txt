add_executable(Main)

target_sources(Main PRIVATE main.cpp)

target_link_libraries(Main PRIVATE Game)