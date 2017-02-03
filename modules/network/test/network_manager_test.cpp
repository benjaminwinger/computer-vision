/**
 * @file network_manager.cpp
 * @author WARG
 *
 * @section LICENSE
 *
 *  Copyright (c) 2015, Waterloo Aerial Robotics Group (WARG)
 *  All rights reserved.
 *
 *  This software is licensed under a modified version of the BSD 3 clause license
 *  that should have been included with this software in a file called COPYING.txt
 *  Otherwise it is available at:
 *  https://raw.githubusercontent.com/UWARG/computer-vision/master/COPYING.txt
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Network
#include <boost/test/unit_test.hpp>
#include "network_manager.h"

BOOST_AUTO_TEST_SUITE(NetworkManagerTest);

BOOST_AUTO_TEST_CASE(TestName) {
    NetworkManager manager(13);
    Json::Value root;
    root["foo"] = bar;
    manager.send(root);
}

BOOST_AUTO_TEST_SUITE_END();
