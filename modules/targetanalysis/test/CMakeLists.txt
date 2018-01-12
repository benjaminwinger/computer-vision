enable_testing()

if(Boost_FOUND AND OpenCV_FOUND)
    ADD_DEFINITIONS("-DBOOST_LOG_DYN_LINK")
    add_executable(target_loader_test test.cpp)
    add_executable(gps_test gps_test.cpp)

    target_link_libraries(target_loader_test ${OpenCV_LIBS} ${Boost_LIBRARIES} Core TargetAnalysis)
    target_link_libraries(gps_test ${OpenCV_LIBS} ${Boost_LIBRARIES} Core TargetAnalysis)

    # Tests
    add_test("SimpleLoad" target_loader_test "${TESTDATA_DIR}/sample.json" "Simple Load" --log_format=XML --log_sink=TEST_LOADER.xml --log_level=all --report_level=no)

    add_test("GpsTest" gps_test --log_format=XML --log_sink=TEST_GPS.xml
        --log_level=all --report_level=no)
endif()
