/**
 * @file gps_test.cpp
 * @author WARG
 *
 * @section LICENSE
 *
 *  Copyright (c) 2015-2017, Waterloo Aerial Robotics Group (WARG)
 *  All rights reserved.
 *
 *  This software is licensed under a modified version of the BSD 3 clause license
 *  that should have been included with this software in a file called COPYING.txt
 *  Otherwise it is available at:
 *  https://raw.githubusercontent.com/UWARG/computer-vision/master/COPYING.txt
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TargetAnalysis

#include <boost/test/unit_test.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include "gps.h"

using namespace std;
using namespace boost;

namespace logging = boost::log;

void gps_check(cv::Point2d point, cv::Point2d expected, Frame *f) {
    cv::Point2d result;
    if (get_gps(point, f, &result)) {
        BOOST_TEST_MESSAGE("Result: " << result);
        BOOST_TEST_MESSAGE("Expected: " << expected);
        BOOST_TEST_MESSAGE("Error distance: " << gps_dist(result, expected));
        BOOST_CHECK(norm(result - expected) < GPS_TOLERANCE);
    } else {
        BOOST_TEST_FAIL("get_gps returned failure");
    }
}

BOOST_AUTO_TEST_CASE(GpsTest){
    Metadata m;
    m.lat = 43.47181;
    m.lon = -80.54366;
    m.altitude = 100;
    m.heading = 0;
    Camera testcamera = Camera::TestCamera();
    Frame f(
        new cv::Mat(6000, 4000, CV_32F),
        "test_image",
        m,
        testcamera
    );

    gps_check(cv::Point2d(3000, 2000), cv::Point2d(43.47181, -80.54366), &f);

    gps_check(cv::Point2d(1500, 1000), cv::Point2d(43.47158517, -80.54412471), &f);

    m.heading = 180;
    Frame f2(
        new cv::Mat(6000, 4000, CV_32F),
        "test_image",
        m,
        testcamera
    );
    gps_check(cv::Point2d(4500, 3000), cv::Point2d(43.47158517, -80.54412471), &f2);

    m.heading = 90;
    Frame f3(
        new cv::Mat(6000, 4000, CV_32F),
        "test_image",
        m,
        testcamera
    );
    gps_check(cv::Point2d(4000, 500), cv::Point2d(43.47158517, -80.54412471), &f3);
}
