enable_testing()

if(Boost_FOUND)
    add_executable(network_manager_test network_manager_test.cpp)
    target_link_libraries(network_manager_test ${Boost_LIBRARIES} Core)

    # Tests
    add_test("network_manager_test" network_manager_test --log_format=XML --log_sink=TEST_PICTURE.xml --log_level=all --report_level=no)
endif()
