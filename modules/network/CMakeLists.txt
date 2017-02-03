include_directories(include)
add_library(Network src/network_manager.cpp, src/connection.cpp)
target_link_libraries(Network Core ${jsoncpp_LIBRARIES})
