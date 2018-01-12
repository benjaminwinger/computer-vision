/**
 * @file gps.cpp
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

#ifndef GPS_H
#define GPS_H

#include "frame.h"

static const double GPS_TOLERANCE = 0.0000001;

/**
 * @brief Determines GPS location of a point in an image
 * @param point Location in the image (pixels)
 * @param f Image
 * @param returnResult Resulting location in the image (in latitude and longitude)
 *
 * @return true on success, false on failure
 */
int get_gps(cv::Point2d point, Frame *f, cv::Point2d *returnResult);

/**
 * @brief Calculates the distance (in metres) between two sets of GPS co-ordinates
 *
 * Calculates distance in metres between two sets of GPS co-ordinates.
 * Inaccurate for long distances since it calculates the direct distance rather than the distance along the surface of the earth.
 */
double gps_dist(cv::Point2d p1, cv::Point2d p2);

#endif // GPS_H
