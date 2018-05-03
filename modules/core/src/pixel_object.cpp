/**
 * @file pixel_object.cpp
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

#include "pixel_object.h"

using namespace cv;
using std::string;

PixelObject::PixelObject(cv::Mat & crop, std::vector<Point> & contour, Point2d centroid, double area, double perimeter, Scalar colour, Point2d error, double errorAngle):
    crop(crop), contour(contour), centroid(centroid), area(area), perimeter(perimeter), colour(colour), error(error), errorAngle(errorAngle){

}

std::vector<Point> & PixelObject::get_contour() {
    return contour;
}

cv::Point2d PixelObject::get_centroid(){
    return centroid;
}

double PixelObject::get_area(){
    return area;
}

double PixelObject::get_perimeter(){
    return perimeter;
}

cv::Scalar PixelObject::get_colour(){
    return colour;
}

cv::Point2d PixelObject::get_gps_centroid(){
    return gps_centroid;
}

void PixelObject::set_gps_centroid(cv::Point2d gps){
    gps_centroid = gps;
}

double PixelObject::get_gps_area(){
    return gps_area;
}


cv::Point2d PixelObject::get_error(){
    return error;
}

double PixelObject::get_error_angle(){
    return errorAngle;
}

Frame * PixelObject::get_image(){
    return image;
}

Mat & PixelObject::get_cropped_image(){
    return crop;
}
