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

#include <iomanip>
#include <boost/log/trivial.hpp>
#include "frame.h"

#define RAD2DEG(rad) ((rad)*180.0/M_PI)
#define DEG2RAD(deg) ((deg)*M_PI/180.0)
#define EARTH_RADIUS 6371000

//Based on the GPS location of the image, calculates the
//GPS location of a certain pixel in the image.
bool get_gps(cv::Point2d point, Frame* f, cv::Point2d* returnResult){
    if (f == NULL) {
        BOOST_LOG_TRIVIAL(error) << "Frame is null";
        return false;
    }
    BOOST_LOG_TRIVIAL(trace) << "get_gps(" << point << ", " << f->get_id() << ")";

    const Metadata* m = f->get_metadata();
    cv::Mat img = f->get_img();
    int h = img.cols;
    int w = img.rows;

    if (w <= 0 || h <= 0){
        BOOST_LOG_TRIVIAL(error) << "Invalid frame size w:" << w << " h:" << h;
        return false;
    }

    cv::Point2d imgCenter(w/2, h/2);

    //(0,0) is in the center of the image
    cv::Point2d biasedPoint = point - imgCenter;

    double altitude = m->altitude;
    double heading = m->heading;
    double latitude = m->lat;
    double longitude = m->lon;

    BOOST_LOG_TRIVIAL(trace) << "Camera FOV: " << f->get_camera().get_fov();

    BOOST_LOG_TRIVIAL(trace) << "Dist from Center (pixels: " << biasedPoint;

    double cameraXEdge = altitude * tan(DEG2RAD(f->get_camera().get_fov().width/2)); //meters from center of photo to edge
    double cameraYEdge = altitude * tan(DEG2RAD(f->get_camera().get_fov().height/2)); //meters from center of photo to edge

    BOOST_LOG_TRIVIAL(trace) << "X Edge: " << cameraXEdge << " Y Edge: " << cameraYEdge;

    //Rotation Matrix - Heading
    //Note: The '-heading' compensates for the fact that directional heading is
    //a clockwise quantity, but cos(theta) assumes theta is a counterclockwise
    //quantity.
    double realX = cos(DEG2RAD(-heading)) * biasedPoint.x/(w/2)*cameraXEdge - sin(DEG2RAD(-heading)) * biasedPoint.y/(h/2)*cameraYEdge;
    double realY = sin(DEG2RAD(-heading)) * biasedPoint.x/(w/2)*cameraXEdge + cos(DEG2RAD(-heading)) * biasedPoint.y/(h/2)*cameraYEdge;

    BOOST_LOG_TRIVIAL(trace) << "Real X: " << realX << " Real Y: " << realY;
    BOOST_LOG_TRIVIAL(trace) << "Cos:" << cos(DEG2RAD(-heading));
    BOOST_LOG_TRIVIAL(trace) << "Sin:" << sin(DEG2RAD(-heading));
    BOOST_LOG_TRIVIAL(trace) << "X:" << biasedPoint.x/(w/2)*cameraXEdge;
    BOOST_LOG_TRIVIAL(trace) << "Y:" << biasedPoint.y/(h/2)*cameraYEdge;

    double lon = RAD2DEG(realX/EARTH_RADIUS)/cos(DEG2RAD(latitude)) + longitude;
    double lat = RAD2DEG(realY/EARTH_RADIUS) + latitude;

    BOOST_LOG_TRIVIAL(trace) << "Distance from centre: " << RAD2DEG(realY/EARTH_RADIUS) << " " << RAD2DEG(realX/EARTH_RADIUS)/cos(DEG2RAD(latitude));

    BOOST_LOG_TRIVIAL(trace) << std::setprecision(10) << "Result: " << lat << " " << lon;

    *returnResult = cv::Point2d(lat,lon);
    return true;
}

double gps_dist(cv::Point2d p1, cv::Point2d p2) {
    double dLat = DEG2RAD(p2.x-p1.x);
    double dLon = DEG2RAD(p2.y-p1.y);

    double rLat1 = DEG2RAD(p1.x);
    double rLat2 = DEG2RAD(p2.x);

    double a = sin(dLat/2) * sin(dLat/2) +
          sin(dLon/2) * sin(dLon/2) * cos(rLat1) * cos(rLat2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return EARTH_RADIUS * c;
}
